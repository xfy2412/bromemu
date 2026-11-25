"""brom.py -- 芯片无关的 BROM 外设模型

所有芯片相关的地址都从 `ChipProfile` 读，本文件不含任何机型号。

外设语义（与芯片无关的部分）：
    UART     —— 数据寄存器 + 状态（bit0=RX ready / bit5=TX ready）
    timer    —— 自由运行计数器，每次读自增
    USB      —— 端点 FIFO（芯片发出的数据走这里）
    启动源    —— 有的芯片用一个 MMIO 寄存器的低位表示
    设备寄存器 —— 镜像在普通内存区的外设寄存器（由 profile 提供）
    eFuse    —— 一块只读区，内容由实测提供
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

        # ---- 主机 → 芯片：两层缓冲 ----
        # _host_pending = 主机已给、还没搬进 RX 缓冲的字节流；
        # RX 缓冲（machine 里的 rx_buf_addr）每次只装一个 <= usb_max_packet 的包，
        # 与真机 sub_520E(ep, len, 0x1054DC) 的语义一致。
        self._host_pending = bytearray()
        self.rx_packets = []          # [(len, first16_hex)]，回放/对照用
        self.rx_zlp = 0               # 收到的零长度包个数（只记录，不改 rx_len）
        # 由 machine 注入：只读访问芯片内存（判断回调指针是否已安装）
        self.mem_read = None

        self._log("%s：启动模式=%d，下载魔数=%s"
                  % (chip.name, bootmode, chip.dl_magic.hex(" ")))

    def _log(self, s):
        if self.verbose:
            print("[brom] " + s)

    # ---------------- 主机 → 芯片（两层缓冲）----------------
    def feed_host(self, data: bytes):
        """主机侧来的一串字节（一个 USB transfer 或更多）。"""
        if not data:
            # 零长度包：真机上是一个 ZLP；它不改变 rx_len，只记一笔
            self.rx_zlp += 1
            self._log("主机 ZLP")
            return
        self._host_pending.extend(data)
        self.usb_injected += len(data)
        self._log("主机 → 芯片 %d 字节（待搬 %d）"
                  % (len(data), len(self._host_pending)))

    # 兼容旧 API
    def inject_rx(self, data: bytes):
        self.feed_host(bytes(data))

    def poll_host(self) -> bool:
        """待搬缓冲空了就问 transport 要下一段；返回是否有新数据。"""
        if self._host_pending:
            return True
        if self.tp is None:
            return False
        # 最多吞 8 个 ZLP，避免 transport 异常时无限递归
        for _ in range(8):
            data = self.tp.poll_rx()
            if data is None:
                return False
            if len(data) == 0:
                self.feed_host(b"")
                continue
            self.feed_host(data)
            return True
        return False

    def take_rx_packet(self, max_len: int) -> bytes:
        """从待搬缓冲取一个 USB 包（<= max_len）。"""
        if not self._host_pending:
            return b""
        n = min(max_len, len(self._host_pending))
        pkt = bytes(self._host_pending[:n])
        del self._host_pending[:n]
        return pkt

    def log_rx_packet(self, pkt: bytes):
        self.rx_packets.append((len(pkt), pkt[:16].hex()))
        self._log("搬入 RX 包 %d 字节：%s%s"
                  % (len(pkt), pkt[:16].hex(" "),
                     " …" if len(pkt) > 16 else ""))

    def rx_pending_len(self) -> int:
        return len(self._host_pending)

    def reset_session(self):
        """复位/换会话：丢掉主机侧未搬完的数据。"""
        self._host_pending.clear()
        self.rx_zlp = 0

    def _peek(self, addr, n=4):
        if self.mem_read is None:
            return b"\x00" * n
        try:
            return bytes(self.mem_read(addr, n))
        except Exception:
            return b"\x00" * n

    # ---------------- 设备寄存器判定 ----------------
    def is_device_reg(self, addr: int) -> bool:
        """这个地址是不是"镜像在内存里的外设寄存器"？
        （machine 用它决定要不要走 read() 的默认值逻辑）"""
        if addr in self.chip.device_regs:
            return True
        return self.chip.in_ready_window(addr)

    # ---------------- MMIO 读 ----------------
    def read(self, addr: int, size: int) -> int:
        c = self.chip
        self.mmio_reads[addr] = self.mmio_reads.get(addr, 0) + 1

        # ---- 镜像在内存里的设备寄存器（最高优先级）----
        dv = c.device_regs.get(addr)
        if dv is None and c.in_ready_window(addr):
            dv = 1                       # 就绪窗口：默认"已就绪"
        if dv is not None:
            return dv

        # ---- 启动源选择器 ----
        if c.boot_selector_addr is not None and addr == c.boot_selector_addr:
            return c.boot_selector_value & 0xF

        # ---- timer ----
        if addr == c.timer_reg:
            v = self.timer & 0xFFFFFFFF
            self.timer += self.timer_step
            return v

        # ---- UART 状态 ----
        if addr == c.uart_base + c.uart_status_off:
            return c.uart_status_value

        # ---- USB 事件寄存器：一律返回 0（不上报事件）----
        #   原因：sub_5516 里如果 (EVENT & MASK) 非零，会调用 0x1029C8 等回调，
        #   那张表（0x1029B8 起）由 USB 端点初始化安装，直接跳命令循环时并没有装。
        #   而真正的取字节路径 sub_5B52 是【直接轮询 0x1054D8】的：
        #       while (*(u32*)0x1054D8 == 0) usb_poll_events();
        #   所以不报事件完全够用 —— 数据靠 machine 的 _feed_rx 填进 0x1054D8。
        if c.usb_base <= addr < c.usb_base + 0x1000:
            return 0

        # ---- eFuse ----
        if c.efuse_base <= addr < c.efuse_base + 0x1000:
            off = addr - c.efuse_base
            return int.from_bytes(self.efuse[off:off + size], "little")

        return 0

    # ---------------- MMIO 写 ----------------
    def write(self, addr: int, size: int, value: int) -> bool:
        """返回 True 表示已处理"""
        c = self.chip
        self.mmio_writes[addr] = self.mmio_writes.get(addr, 0) + 1

        # UART 数据寄存器
        if c.uart_base <= addr < c.uart_base + 0x100 and size == 1:
            self.uart_bytes.append(value & 0xFF)
            return True

        # USB 端点 FIFO：base + 0x300 + 16*ep
        fifo0 = c.usb_base + c.usb_ep_fifo_off
        if fifo0 <= addr < fifo0 + 0x100:
            # sub_5212 会按 1/2/3/4 字节写 FIFO；必须按 size 全部取出来，
            # 不能只取低字节（否则 0x7114 这类 2 字节写会丢掉 0x71）。
            n = max(1, min(size, 4))
            b = (value & ((1 << (8 * n)) - 1)).to_bytes(n, "little")
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
