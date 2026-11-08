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
        for base, size, _name in getattr(model, "EXTRA_REGIONS", []):
            try:
                mu.mem_map(base, size)
            except Exception:
                pass
        mu.mem_write(chip.rom_base, rom)

        mu.mem_write(chip.bootmode_addr, bytes([model.bootmode & 0xFF]))
        # 让外设模型能只读访问内存（判断回调指针是否已安装）
        model.mem_read = lambda a, n: mu.mem_read(a, n)

        mu.hook_add(UC_HOOK_MEM_READ, self._on_read)
        mu.hook_add(UC_HOOK_MEM_WRITE, self._on_write)
        mu.hook_add(UC_HOOK_CODE, self._on_code)

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

        # 设备寄存器（可能落在普通内存区间里）
        if address in self.model.DEVICE_REGS:
            v = self.model.read(address, size)
            mu.mem_write(address, v.to_bytes(4, "little")[:size])
            return

        # MMIO
        if address >= 0x10000000:
            v = self.model.read(address, size)
            mu.mem_write(address, v.to_bytes(4, "little")[:size])

    def _on_write(self, mu, access, address, size, value, ud):
        if address >= 0x10000000:
            self.model.write(address, size, value)

    def _feed_rx(self):
        c = self.chip
        mu = self.mu
        # 还有没读完的就先不管
        if int.from_bytes(mu.mem_read(c.rx_len_addr, 4), "little"):
            return

        data = None
        if self.model.tp is not None:
            data = self.model.tp.poll_rx()
        if not data:
            data = self.model.take_rx()
        if not data:
            return

        mu.mem_write(c.rx_buf_addr, data)
        mu.mem_write(c.rx_len_addr, len(data).to_bytes(4, "little"))
        mu.mem_write(c.rx_idx_addr, b"\x00\x00\x00\x00")

    # ---------------- 执行 ----------------
    def run(self, max_ins: int = 8_000_000):
        try:
            self.mu.emu_start(self.chip.entry, 0, count=max_ins)
            return "指令数用尽"
        except UcError as e:
            pc = self.mu.reg_read(UC_ARM_REG_PC)
            return "停在 PC=0x%08X : %s" % (pc, e)

    def state(self) -> str:
        mu = self.mu
        cpsr = mu.reg_read(UC_ARM_REG_CPSR)
        return ("PC=0x%08X  CPSR=0x%08X  %s  模式=%d\n"
                "SP=0x%08X  LR=0x%08X  R0=0x%08X\n"
                % (mu.reg_read(UC_ARM_REG_PC), cpsr,
                   "Thumb" if cpsr & 0x20 else "ARM", cpsr & 0x1F,
                   mu.reg_read(UC_ARM_REG_SP), mu.reg_read(UC_ARM_REG_LR),
                   mu.reg_read(UC_ARM_REG_R0)))




