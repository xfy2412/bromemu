"""debug.py -- BROM 模拟器的调试器

能力
----
    · 地址断点（可带条件）
    · 内存读/写断点（watchpoint）
    · 单步
    · 寄存器 / 内存查看
    · 反汇编上下文
    · 调用栈（用 LR 粗判）
    · 执行轨迹（最近 N 条）

用法
----
    from emu.chips import get
    from emu.brom import BromModel
    from emu.machine import BromMachine
    from emu.debug import Debugger

    chip = get("mt6853")
    rom  = open(chip.rom_path(), "rb").read()
    model = BromModel(chip)
    m = BromMachine(rom, chip, model)
    dbg = Debugger(m)

    dbg.bp(0xE84C)                    # 到 0xE84C 停
    dbg.watch(0x1027BC, "w")          # 0x1027BC 被写时停
    dbg.run_until_hit(5_000_000)      # 跑，直到命中或超时
    print(dbg.regs())
    print(dbg.disasm(5))
"""
from __future__ import annotations

from collections import deque

from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_HOOK_MEM_WRITE_UNMAPPED
from unicorn.arm_const import *
import capstone

ARM_REGS = [
    (UC_ARM_REG_R0, "R0"), (UC_ARM_REG_R1, "R1"), (UC_ARM_REG_R2, "R2"),
    (UC_ARM_REG_R3, "R3"), (UC_ARM_REG_R4, "R4"), (UC_ARM_REG_R5, "R5"),
    (UC_ARM_REG_R6, "R6"), (UC_ARM_REG_R7, "R7"), (UC_ARM_REG_R8, "R8"),
    (UC_ARM_REG_R9, "R9"), (UC_ARM_REG_R10, "R10"), (UC_ARM_REG_R11, "R11"),
    (UC_ARM_REG_R12, "R12"), (UC_ARM_REG_SP, "SP"), (UC_ARM_REG_LR, "LR"),
    (UC_ARM_REG_PC, "PC"),
]


class Breakpoint:
    def __init__(self, addr, cond=None, text=""):
        self.addr = addr
        self.cond = cond          # callable(mu) -> bool
        self.text = text
        self.hits = 0


class Watchpoint:
    def __init__(self, addr, size=4, kind="w", cond=None):
        self.addr = addr
        self.size = size
        self.kind = kind          # "r" / "w" / "rw"
        self.cond = cond
        self.hits = 0


class Debugger:
    def __init__(self, machine, trace_len=32):
        self.m = machine
        self.mu = machine.mu
        self.chip = machine.chip
        self.bps = []
        self.wps = []
        self.trace = deque(maxlen=trace_len)
        self.stopped = False
        self.stop_reason = ""
        self.ins_count = 0
        self.started = False          # 首次 run/step 从 chip.entry 开始
        self._md_arm = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_ARM)
        self._md_thumb = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
        self._install()

    # ---------------- 安装钩子 ----------------
    def _install(self):
        self.mu.hook_add(UC_HOOK_CODE, self._on_code)
        self.mu.hook_add(UC_HOOK_MEM_WRITE, self._on_write)

    def _is_thumb(self):
        return bool(self.mu.reg_read(UC_ARM_REG_CPSR) & 0x20)

    def _on_code(self, mu, address, size, ud):
        self.ins_count += 1
        self.trace.append(address)

        for bp in self.bps:
            if bp.addr == address:
                if bp.cond is None or bp.cond(mu):
                    bp.hits += 1
                    self.stop_reason = "断点 0x%X%s" % (bp.addr,
                                                        ("（%s）" % bp.text) if bp.text else "")
                    self.stopped = True
                    mu.emu_stop()
                    return

    def _on_write(self, mu, access, address, size, value, ud):
        for wp in self.wps:
            if wp.kind in ("w", "rw") and wp.addr <= address < wp.addr + wp.size:
                if wp.cond is None or wp.cond(mu):
                    wp.hits += 1
                    self.stop_reason = "内存写 0x%X = 0x%X（PC=0x%X）" % (
                        address, value, mu.reg_read(UC_ARM_REG_PC))
                    self.stopped = True
                    mu.emu_stop()
                    return

    # ---------------- 断点管理 ----------------
    def bp(self, addr, cond=None, text=""):
        self.bps.append(Breakpoint(addr, cond, text))
        return self

    def bp_func(self, enter_addr):
        """函数入口断点：命中时打印参数"""
        def _cond(mu):
            return True
        self.bps.append(Breakpoint(enter_addr, _cond, "函数入口"))
        return self

    def watch(self, addr, kind="w", size=4, cond=None):
        self.wps.append(Watchpoint(addr, size, kind, cond))
        return self

    def clear(self):
        self.bps.clear()
        self.wps.clear()
        return self

    # ---------------- 执行 ----------------
    def _start_pc(self):
        """首次从芯片入口开始，之后从当前 PC 继续

        ⚠️ Unicorn 用 PC 的最低位选 ARM/Thumb：
           bit0=1 ⇒ Thumb，bit0=0 ⇒ ARM。
           继续执行时必须把当前 CPSR 的 T 位带上，否则会把 Thumb 代码当 ARM 解。
        """
        if not self.started:
            self.started = True
            return self.chip.entry
        pc = self.mu.reg_read(UC_ARM_REG_PC)
        cpsr = self.mu.reg_read(UC_ARM_REG_CPSR)
        return (pc | 1) if (cpsr & 0x20) else (pc & ~1)

    def run(self, max_ins=1_000_000):
        """继续跑，直到命中断点或指令数用尽"""
        self.stopped = False
        self.stop_reason = ""
        try:
            self.mu.emu_start(self._start_pc(), 0, count=max_ins)
        except Exception as e:
            self.stop_reason = "异常：%s" % e
            return self.stop_reason
        if not self.stopped:
            self.stop_reason = "指令数用尽（%d）" % max_ins
        return self.stop_reason

    def step(self, n=1):
        """单步 n 条

        ⚠️ 单步时必须临时屏蔽断点：否则 PC 停在断点上时，
           每走一步都会被同一个断点立刻 emu_stop 掐断，永远前进不了。
        """
        saved = self.bps
        self.bps = []
        try:
            for _ in range(n):
                pc = self._start_pc()
                try:
                    self.mu.emu_start(pc, 0, count=1)
                except Exception as e:
                    return "异常：%s" % e
        finally:
            self.bps = saved
        return "单步 %d 条完成" % n

    def step_over(self):
        """步过：如果当前是 bl/blx，跑到返回地址"""
        pc = self.mu.reg_read(UC_ARM_REG_PC)
        ins = self._decode_at(pc)
        if ins and ins.mnemonic in ("bl", "blx", "bl.w"):
            lr = self.mu.reg_read(UC_ARM_REG_LR)
            # 粗略：跑一条，看 PC 是否跳走
            self.mu.emu_start(pc, 0, count=1)
            if self.mu.reg_read(UC_ARM_REG_PC) != pc + 4 and \
               self.mu.reg_read(UC_ARM_REG_PC) != pc + 2:
                # 在函数里了，继续跑到 LR
                try:
                    self.mu.emu_start(self.mu.reg_read(UC_ARM_REG_PC),
                                      self.mu.reg_read(UC_ARM_REG_LR), count=2_000_000)
                except Exception as e:
                    return "异常：%s" % e
            return "步过完成"
        return self.step(1)

    # ---------------- 观察 ----------------
    def regs(self):
        mu = self.mu
        lines = []
        for r, n in ARM_REGS:
            lines.append("%-4s = 0x%08X" % (n, mu.reg_read(r)))
        cpsr = mu.reg_read(UC_ARM_REG_CPSR)
        lines.append("CPSR = 0x%08X  %s  模式=%d  Z=%d N=%d C=%d V=%d"
                     % (cpsr, "Thumb" if cpsr & 0x20 else "ARM", cpsr & 0x1F,
                        (cpsr >> 30) & 1, (cpsr >> 31) & 1,
                        (cpsr >> 29) & 1, (cpsr >> 28) & 1))
        return "\n".join(lines)

    def _decode_at(self, pc):
        md = self._md_thumb if self._is_thumb() else self._md_arm
        base = self.chip.rom_base
        try:
            data = self.mu.mem_read(pc, 4)
        except Exception:
            return None
        for ins in md.disasm(bytes(data), pc):
            return ins
        return None

    def disasm(self, n=8, pc=None):
        """反汇编从 pc 开始的 n 条"""
        mu = self.mu
        pc = pc if pc is not None else mu.reg_read(UC_ARM_REG_PC)
        md = self._md_thumb if self._is_thumb() else self._md_arm
        out = []
        try:
            data = bytes(mu.mem_read(pc, n * 4 + 8))
        except Exception:
            return "(读不到 0x%X 处的内存)" % pc
        cur = pc
        for ins in md.disasm(data, pc):
            mark = "→" if ins.address == pc else " "
            out.append("%s %08X  %-9s %s" % (mark, ins.address, ins.mnemonic, ins.op_str))
            cur += ins.size
            if len(out) >= n:
                break
        return "\n".join(out)

    def mem(self, addr, n=64):
        try:
            d = bytes(self.mu.mem_read(addr, n))
        except Exception as e:
            return "(读不到：%s)" % e
        lines = []
        for i in range(0, n, 16):
            chunk = d[i:i + 16]
            hexs = " ".join("%02x" % b for b in chunk)
            asc = "".join(chr(b) if 32 <= b < 127 else "." for b in chunk)
            # 尝试按 u32 解释
            u32s = " ".join("%08x" % int.from_bytes(chunk[j:j + 4], "little")
                            for j in range(0, len(chunk) - 3, 4))
            lines.append("%08X  %-47s  |%-16s|  %s" % (addr + i, hexs, asc, u32s))
        return "\n".join(lines)

    def write_mem(self, addr, data: bytes):
        self.mu.mem_write(addr, data)

    def stack(self, n=16):
        sp = self.mu.reg_read(UC_ARM_REG_SP)
        return "SP=0x%08X\n" % sp + self.mem(sp, n * 4)

    def backtrace(self, depth=8):
        """用 LR 链粗判调用栈（对 leaf 函数不准）"""
        out = []
        lr = self.mu.reg_read(UC_ARM_REG_LR)
        out.append("PC=0x%08X  LR=0x%08X" % (self.mu.reg_read(UC_ARM_REG_PC), lr))
        return "\n".join(out)

    def state(self):
        return ("指令计数：%d\n停止原因：%s\n\n%s\n\n当前指令：\n%s"
                % (self.ins_count, self.stop_reason or "(未停)",
                   self.regs(), self.disasm(6)))

    def last_trace(self, n=16):
        return "\n".join("0x%08X" % a for a in list(self.trace)[-n:])


def attach(machine):
    """快捷函数：给一个 machine 挂上调试器"""
    return Debugger(machine)

