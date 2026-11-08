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
    #: 除 chip 声明之外，额外映射的"未知访问"兜底区间
    #: MTK BROM 里会出现 0x0Cxxxxxx / 0x0Dxxxxxx 这类别名地址，
    #: 直接用大块 MMIO 兜住，避免 UC_ERR_READ_UNMAPPED 打断流程。
    EXTRA_REGIONS = [
        (0x0C000000, 0x01000000, "alias-0C"),
        (0x0D000000, 0x01000000, "alias-0D"),
        (0x02000000, 0x01000000, "alias-02"),
    ]

    #: 藏在普通内存区间里的"设备寄存器"：地址 → 固定返回值
    #: 这些是反编译里识别出来的硬件状态位，Unicorn 不模拟它们，
    #: 不给值就会在轮询循环里死等。
    #:
    #: 0x10210ABC  sub_C7FE: ldr r1,[r0,#0xabc]; and r1,#1; cmp r1,#0; beq 死等
    #:             ⇒ bit0 = 1 表示就绪
    DEVICE_REGS = {
        0x10210ABC: 0x00000001,
    }

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
        # 由 machine 注入：只读访问芯片内存（用于判断回调指针是否已安装）
        self.mem_read = None
        # 启动模式选择器（0x1000A000 低 4 位）：1/2/3 = 正常，7/其它 = 停机
        self.boot_selector = 1

        self._log("%s：启动模式=%d，下载魔数=%s"
                  % (chip.name, bootmode, chip.dl_magic.hex(" ")))

    def _peek(self, addr, n=4):
        if self.mem_read is None:
            return b"\\x00" * n
        try:
            return bytes(self.mem_read(addr, n))
        except Exception:
            return b"\\x00" * n

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
        # 藏在内存区间里的设备寄存器（优先级最高）
        dv = self.DEVICE_REGS.get(addr)
        if dv is not None:
            self.mmio_reads[addr] = self.mmio_reads.get(addr, 0) + 1
            return dv
        self.mmio_reads[addr] = self.mmio_reads.get(addr, 0) + 1

        if addr == c.timer_reg:
            v = self.timer & 0xFFFFFFFF
            self.timer += self.timer_step
            return v

        if addr == c.uart_base + c.uart_status_off:
            return c.uart_status_value

        # USB 事件寄存器：0x11201080 = 事件，0x11201084 = 使能掩码
        #   sub_5516 里：v1 = (u16)(EVENT & MASK)
        #     bit0 ⇒ 调 MEMORY[0x1029C8]()      ← EP0 RX 回调
        #     bit1-4 ⇒ 调 MEMORY[0x1029CC+4*(i-1)]()
        #   ⚠️ 这些回调指针由 sub_F81C → sub_638A() 安装。
        #      如果还没安装（值为 0），上报事件会导致【调用地址 0】⇒ PC 飞掉。
        #      所以只有回调有效时才报事件。
        usb_event = c.usb_base + 0x80
        usb_mask = c.usb_base + 0x84
        if addr == usb_event or addr == usb_mask:
            if not self._rx_pending:
                return 0
            try:
                cb0 = int.from_bytes(self._peek(0x001029C8), "little")
            except Exception:
                cb0 = 0
            return 1 if cb0 else 0

        if c.usb_base <= addr < c.usb_base + 0x1000:
            return 0                       # 其它 USB 寄存器：无事件

        # ★ 启动模式选择器：0x1000A000 的低 4 位
        #   sub_10FC8：v3 = *(u32*)0x1000A000 & 0xF
        #     1/2/3 → 返回 1/2/3（继续）
        #     7     → 返回 4   （sub_E0FA 判为停机）
        #     其它  → 返回 255 （sub_E0FA 判为停机）
        if addr == 0x1000A000:
            return self.boot_selector & 0xF

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




