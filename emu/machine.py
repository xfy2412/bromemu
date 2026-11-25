"""machine.py -- Unicorn 封装（芯片无关）

职责边界
--------
    machine.py   只做"CPU + 内存 + 钩子"的胶水
    chips/*.py   芯片相关的地址与常量
    brom.py      外设语义
    transport.py 对外的字节流
"""
from __future__ import annotations

from unicorn import *
from unicorn.arm_const import *

from .brom import BromModel
from .chips.base import ChipProfile


#: 旁白里可引用的寄存器（名字 → Unicorn 常量）
_REGS = [("r%d" % i, globals()["UC_ARM_REG_R%d" % i]) for i in range(13)]
_REGS += [("sp", UC_ARM_REG_SP), ("lr", UC_ARM_REG_LR), ("pc", UC_ARM_REG_PC)]

class BromMachine:
    def __init__(self, rom: bytes, chip: ChipProfile, model: BromModel):
        self.chip = chip
        self.model = model
        self.rom = rom

        mu = Uc(UC_ARCH_ARM, UC_MODE_ARM)
        self.mu = mu
        for r in chip.region_list():
            mu.mem_map(r.base, r.size)
        # 兜底区间：MTK BROM 里会出现别名的低地址区，未映射会打断流程
        for base, size, _name in model.chip.extra_regions:
            try:
                mu.mem_map(base, size)
            except Exception:
                pass
        mu.mem_write(chip.rom_base, rom)

        mu.mem_write(chip.bootmode_addr, bytes([model.bootmode & 0xFF]))
        # 让外设模型能只读访问内存（判断回调指针是否已安装）
        model.mem_read = lambda a, n: mu.mem_read(a, n)

        # 对 ROM 的非法写尝试（诊断用：真机上 ROM 只读，这些写本该失败）
        self.rom_write_attempts = []

        # ★★★ ROM 写保护（opt-in，默认关闭）
        #     Unicorn 的 UC_HOOK_MEM_WRITE 只是"通知"，在回调里 return 并不能阻止写入；
        #     要真正拦截必须 mem_protect 设成 UC_PROT_READ|EXEC，
        #     代价是写操作会抛 UC_ERR_WRITE_PROT，得靠 run() 里的容错循环跳过。
        #     ⚠️ 打开它会让执行流变化（写被忽略 vs 写生效），排查别的问题时先别开。
        #     启用方式：环境变量 BROMEMU_PROTECT_ROM=1
        rom_end = chip.rom_base + chip.rom_size
        self._rom_range = (chip.rom_base, rom_end)
        import os
        if os.environ.get("BROMEMU_PROTECT_ROM") == "1":
            mu.mem_protect(chip.rom_base, chip.rom_size,
                           UC_PROT_READ | UC_PROT_EXEC)

        mu.hook_add(UC_HOOK_MEM_READ, self._on_read)
        mu.hook_add(UC_HOOK_MEM_WRITE, self._on_write)
        mu.hook_add(UC_HOOK_MEM_WRITE_UNMAPPED, self._on_write_unmapped)
        mu.hook_add(UC_HOOK_CODE, self._on_code)

        # 关键地址旁白：给没有日志的 BootROM 加"日志"
        for addr, msg in (getattr(chip, "log_points", None) or {}).items():
            mu.hook_add(UC_HOOK_CODE, self._make_log_hook(msg),
                        begin=addr, end=addr + 1)

    @staticmethod
    def _make_log_hook(msg):
        """把一条旁白变成 Unicorn 代码钩子。

        文案里可以用 {r0}..{r12} / {sp} / {lr} / {pc} 引用当时的寄存器，
        例如 "解析容器块 r0=0x{r0:X} type={r1}"。
        """
        def _hook(uc, address, size, user_data):
            if "{" in msg:
                vals = {name: uc.reg_read(reg) for name, reg in _REGS}
                text = msg.format(**vals)
            else:
                text = msg
            print("[rom] %s" % text, flush=True)
        return _hook

    # ---------------- CP15 等待循环的绕过 ----------------
    # 某些 BROM 版本里有这种代码：
    #     mcr p15, 0, r1, c15, c3, #5     写 cache size selection
    #     mrc p15, 0, r1, c15, c3, #7     读回
    #     cmp r2, r0 ; bne 读回处          读回不匹配就死等
    # Unicorn 不实现 CP15，读回恒为 0 ⇒ 无限循环。
    # 这里在 cmp 之前把"读回值"对齐到"期望值"，让循环立刻结束。
    CP15_WAIT_PATCHES = {
        0x00117E0: (0x117D8, 0),   # MT6853: cmp r2, r0 之前，令 r2 := r0
    }

    def _on_code(self, mu, address, size, ud):
        patch = self.CP15_WAIT_PATCHES.get(address)
        if patch is None:
            return
        # r2 ← r0（把"读回值"对齐到"期望值"）
        mu.reg_write(UC_ARM_REG_R2, mu.reg_read(UC_ARM_REG_R0))

    # ---------------- 钩子 ----------------
    def _on_read(self, mu, access, address, size, value, ud):
        c = self.chip

        # 启动模式：读时强制 1（模拟"真机复位配置给了 1"）
        if c.bootmode_addr <= address < c.bootmode_addr + 4:
            mu.mem_write(c.bootmode_addr, b"\x01")
            return

        # USB TX 完成：读时恒为 1
        if c.tx_done_addr <= address < c.tx_done_addr + 4:
            mu.mem_write(c.tx_done_addr, b"\x01\x00\x00\x00")
            return

        # RX 长度：顺便尝试从传输层取数据
        if c.rx_len_addr <= address < c.rx_len_addr + 4:
            self._feed_rx()
            return

        # 芯片专有的动态寄存器（每次读都会变的等待位/邮箱/计数器）
        rv = self.chip.read_mmio(self, address, size)
        if rv is not None:
            mu.mem_write(address, int(rv).to_bytes(4, "little")[:size])
            return

        # 设备寄存器（可能落在普通内存区间里）
        rw = self.chip.ready_window
        if address in self.chip.device_regs or (rw and rw[0] <= address < rw[1]):
            v = self.model.read(address, size)
            mu.mem_write(address, v.to_bytes(4, "little")[:size])
            return

        # MMIO
        if address >= 0x10000000:
            # USB 事件/状态寄存器：一律返回 0（不触发未安装的回调表）。
            # 注意：这里【不要】顺手 _feed_rx()。sub_F81C 在命令循环开头会清
            # 0x1054xx 一带的缓冲；如果在它清之前就把字节搬进 RX 缓冲，字节会被
            # 清掉，而 transport 里那一块已经消费掉了 ⇒ 命令循环永远等不到数据。
            # 数据只在 BROM 真正读 0x1054D8 时补（见上面的 rx_len 分支）。
            if c.usb_base <= address < c.usb_base + 0x1000:
                mu.mem_write(address, (0).to_bytes(4, "little")[:size])
                return
            v = self.model.read(address, size)
            mu.mem_write(address, v.to_bytes(4, "little")[:size])

    def _on_write_unmapped(self, mu, access, address, size, value, ud):
        """接住对 ROM 的写（ROM 已 mem_protect 为只读）。
        真机上掩膜 ROM 写无效，这里直接忽略并继续。"""
        lo, hi = self._rom_range
        if lo <= address < hi:
            self.rom_write_attempts.append((address, size, value,
                                            mu.reg_read(UC_ARM_REG_PC)))
            return False          # False = 不跳过指令？ Unicorn 里返回 True 表示已处理
        return None

    def _on_write(self, mu, access, address, size, value, ud):
        # 调试字符设备：芯片把字节写到这里就等于 printf
        putc = getattr(self.chip, "debug_putc_addr", None)
        if putc is not None and address == putc:
            import sys
            sys.stdout.write(chr(value & 0xFF))
            sys.stdout.flush()
            return
        # ★ ROM 是只读的：真机上对 0x00000~0x20000 的写要么被忽略、要么 fault。
        #   不拦住的话，BROM 会把自己的数据表写到代码区，
        #   把跳转指令（比如 0xE88 的 `b 0xC9C`）覆盖成指针，
        #   随后执行流就跳进字符串里 —— 这正是之前那次 PC=0xE9C 崩溃的原因。
        if address < self.chip.rom_base + self.chip.rom_size:
            self.rom_write_attempts.append((address, size, value,
                                            mu.reg_read(UC_ARM_REG_PC)))
            return

        if self.chip.write_mmio(self, address, size, value):
            return

        if address in self.chip.device_regs or address >= 0x10000000:
            self.model.write(address, size, value)
        else:
            # 落在 SRAM 里的设备寄存器 / 普通内存：交给模型
            self.model.write(address, size, value)

    def _feed_rx(self):
        """把主机侧的一批字节搬进 BROM 的 RX 缓冲。

        真机语义（sub_520E / sub_5B26）：
            · RX 缓冲 = 0x1054DC，长度 ≤ usb_max_packet（MT6853 = 512）
            · 0x1054D8 = 本批长度；BROM 用完最后 1 字节后清 0
            · 0x1054DC + 0x200 = 0x1056DC 是 RC/key 结构（"RC_INIT"）
              ⇒ 一次搬超过 512 B 会覆盖它和 0x105748 的验签钥缓冲
        所以这里只在 rx_len == 0 时搬“一包”，剩下的留在 model._host_pending。
        """
        c = self.chip
        mu = self.mu
        # 还有没读完的就先不管
        if int.from_bytes(mu.mem_read(c.rx_len_addr, 4), "little"):
            return

        if not self.model.poll_host():
            return
        pkt = self.model.take_rx_packet(c.usb_max_packet)
        if not pkt:
            return
        # 双保险：模型层已经按 usb_max_packet 切过，这里再截一次
        if len(pkt) > c.usb_max_packet:
            pkt = pkt[:c.usb_max_packet]

        mu.mem_write(c.rx_buf_addr, pkt)
        mu.mem_write(c.rx_len_addr, len(pkt).to_bytes(4, "little"))
        mu.mem_write(c.rx_idx_addr, b"\x00\x00\x00\x00")
        self.model.log_rx_packet(pkt)

    # ---------------- 执行 ----------------
    def run(self, max_ins: int = 8_000_000):
        """执行，遇到"写只读 ROM"的 fault 时跳过该指令继续。

        真机上 BROM 是掩膜 ROM，对它的写只会静默无效；Unicorn 则会直接
        抛 UC_ERR_WRITE_PROT 停住。这里模拟真机行为：记一笔，跳过，继续跑。
        """
        c = self.chip
        done = 0
        first = True
        while done < max_ins:
            pc = self.mu.reg_read(UC_ARM_REG_PC)
            if first:
                # 第一次调用：从芯片入口开始（与 debugger 的行为一致）
                # CPU 初始状态（SP / Thumb / 预填寄存器）交给 profile 的 init_cpu 钩子
                pc = c.init_cpu(self.mu, c.entry)
                self.mu.reg_write(UC_ARM_REG_PC, pc)
                first = False
            cpsr = self.mu.reg_read(UC_ARM_REG_CPSR)
            start = (pc | 1) if (cpsr & 0x20) else (pc & ~1)
            try:
                self.mu.emu_start(start, 0, count=max_ins - done)
                return "指令数用尽"
            except UcError as e:
                if e.errno == UC_ERR_WRITE_PROT:
                    # 记录并跳过这条写指令
                    try:
                        self.rom_write_attempts.append(
                            (0, 0, 0, pc))
                    except Exception:
                        pass
                    # 估算指令长度：Thumb 多为 2/4，ARM 固定 4
                    step = 4 if not (cpsr & 0x20) else self._thumb_len(pc)
                    self.mu.reg_write(UC_ARM_REG_PC, pc + step)
                    continue
                return "停在 PC=0x%08X : %s" % (pc, e)
        return "指令数用尽"

    def _thumb_len(self, pc: int) -> int:
        """粗判 Thumb 指令长度：看高 5 位是否是 11101/11110/11111"""
        try:
            hw = int.from_bytes(self.mu.mem_read(pc, 2), "little")
        except Exception:
            return 2
        top = hw >> 11
        return 4 if top in (0b11101, 0b11110, 0b11111) else 2

    def state(self) -> str:
        mu = self.mu
        cpsr = mu.reg_read(UC_ARM_REG_CPSR)
        return ("PC=0x%08X  CPSR=0x%08X  %s  模式=%d\n"
                "SP=0x%08X  LR=0x%08X  R0=0x%08X\n"
                % (mu.reg_read(UC_ARM_REG_PC), cpsr,
                   "Thumb" if cpsr & 0x20 else "ARM", cpsr & 0x1F,
                   mu.reg_read(UC_ARM_REG_SP), mu.reg_read(UC_ARM_REG_LR),
                   mu.reg_read(UC_ARM_REG_R0)))










