"""brom.py -- 芯片无关的 BROM 外设模型

所有芯片相关的地址都从 `ChipProfile` 读，本文件不含任何机型号。

外设语义（与芯片无关的部分）：
    UART   —— 数据寄存器 + 状态（bit0=RX ready / bit5=TX ready）
    timer  —— 自由运行计数器，每次读自增
    USB    —— 端点 FIFO（芯片发出的数据走这里）
    eFuse  —— 一块只读区，内容由实测提供
"""
from __future__ import annotations

from .chips.base import ChipProfile


class BromModel:
    def __init__(self, chip: ChipProfile, transport=None,
                 efuse: bytes = None, bootmode: int = 1,
                 timer_step: int = 1, verbose: bool = True):
        self.chip = chip
        self.tp = transport
        self.bootmode = bootmode
        self.timer = 1
        self.timer_step = timer_step
        self.verbose = verbose

        # eFuse 内容：默认全 0，由调用方按实机填
        self.efuse = bytearray(efuse if efuse else b"\x00" * 0x1000)

        self.tx_bytes = bytearray()
        self.uart_bytes = bytearray()
        self.mmio_reads = {}
        self.mmio_writes = {}
        self.usb_injected = 0
        self._rx_pending = b""

        self._log("%s：启动模式=%d，下载魔数=%s"
                  % (chip.name, bootmode, chip.dl_magic.hex(" ")))

    def _log(self, s):
        if self.verbose:
            print("[brom] " + s)

    # ---------------- RX 注入 ----------------
    def inject_rx(self, data: bytes):
        self._rx_pending = bytes(data)
        self.usb_injected += len(data)
        self._log("注入 RX %d 字节：%s" % (len(data), data.hex(" ")))

    def take_rx(self) -> bytes:
        d = self._rx_pending
        self._rx_pending = b""
        return d

    # ---------------- MMIO 读 ----------------
    def read(self, addr: int, size: int) -> int:
        c = self.chip
        self.mmio_reads[addr] = self.mmio_reads.get(addr, 0) + 1

        if addr == c.timer_reg:
            v = self.timer & 0xFFFFFFFF
            self.timer += self.timer_step
            return v

        if addr == c.uart_base + c.uart_status_off:
            return c.uart_status_value

        if c.usb_base <= addr < c.usb_base + 0x1000:
            return 0                       # 无事件

        if c.efuse_base <= addr < c.efuse_base + 0x1000:
            off = addr - c.efuse_base
            return int.from_bytes(self.efuse[off:off + size], "little")

        return 0

    # ---------------- MMIO 写 ----------------
    def write(self, addr: int, size: int, value: int) -> bool:
        c = self.chip
        self.mmio_writes[addr] = self.mmio_writes.get(addr, 0) + 1

        # UART 数据寄存器
        if c.uart_base <= addr < c.uart_base + 0x100 and size == 1:
            self.uart_bytes.append(value & 0xFF)
            return True

        # USB 端点 FIFO：0x11201000 + 16*ep + 768
        fifo0 = c.usb_base + 0x300
        if fifo0 <= addr < fifo0 + 0x100:
            b = bytes([value & 0xFF])
            self.tx_bytes.extend(b)
            if self.tp:
                self.tp.tx(b)
            return True

        return False

    # ---------------- 便捷 ----------------
    def uart_text(self) -> str:
        return bytes(self.uart_bytes).decode("latin-1", errors="replace")

    def stats(self) -> str:
        return "\n".join([
            "芯片：%s" % self.chip.name,
            "串口 %d 字节" % len(self.uart_bytes),
            "USB 发出 %d 字节" % len(self.tx_bytes),
            "USB 注入 %d 字节" % self.usb_injected,
            "timer 走了 %d" % self.timer,
            "MMIO 读 %d 个地址 / 写 %d 个地址"
            % (len(self.mmio_reads), len(self.mmio_writes)),
        ])

