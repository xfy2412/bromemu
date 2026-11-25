"""chips/base.py -- 芯片 profile 的基类

设计原则
--------
1. **一切与芯片相关的常量都进 profile**，machine.py / brom.py 保持通用
2. 新机型只需继承 `ChipProfile` 并填字段，不改任何引擎代码
3. 字段缺失时有保守默认值（能跑起来，但行为可能不准）

贡献新机型的步骤
----------------
    1. 把 dump 放 sources/<chip>/brom.bin
    2. 新建 emu/chips/<chip>.py，继承 ChipProfile，填字段
    3. 在 emu/chips/__init__.py 的 REGISTRY 里登记
    4. 运行 `python -m emu.run --chip <chip>` 看能跑到哪
"""
from __future__ import annotations

from typing import Dict, Optional, Tuple


class MemRegion:
    """一段内存"""
    __slots__ = ("name", "base", "size", "kind")

    def __init__(self, name, base, size, kind="ram"):
        self.name = name
        self.base = base
        self.size = size
        self.kind = kind          # rom / ram / mmio

    def __repr__(self):
        return "MemRegion(%s, 0x%X, 0x%X, %s)" % (
            self.name, self.base, self.size, self.kind)


class ChipProfile:
    """一颗芯片的 BROM 特征

    子类用【类属性】覆盖即可（不要加 @dataclass —— 字段默认值会盖掉子类的覆盖）。
    """

    # ---------- 身份 ----------
    name: str = "unknown"
    description: str = ""

    # ---------- 镜像 ----------
    rom_file: str = "sources/{chip}/brom.bin"
    rom_base: int = 0x00000000
    rom_size: int = 0x00020000

    # ---------- 入口 ----------
    entry: int = 0x28
    init_sp: Optional[int] = None

    def init_cpu(self, mu, entry: int) -> int:
        """复位后、执行前的一次性 CPU 初始化；返回实际入口地址。

        通用引擎只调用这一个钩子，不认识任何芯片细节。需要设置初始 SP、
        切换 ARM/Thumb 状态或预填寄存器的芯片覆盖本方法。默认原样返回。
        """
        return entry

    #: 关键地址 → 旁白文案（仿真时打印；给没有日志的 BootROM "加日志"）
    log_points: dict = {}
    #: 调试字符输出地址：芯片往这里写一个字节，模拟器就打印到终端；None = 不支持
    debug_putc_addr: Optional[int] = None

    def read_mmio(self, machine, address: int, size: int):
        """芯片专有的 MMIO 读模型。

        返回 int 表示由本芯片提供该值（通用模型不再处理）；
        返回 None 表示交给默认的 `model.read()`。
        用于"每次读都会变"的寄存器（等待位、邮箱、计数器）——静态 device_regs 表达不了。
        """
        return None

    def write_mmio(self, machine, address: int, size: int, value: int) -> bool:
        """芯片专有的 MMIO 写模型；返回 True 表示已处理。"""
        return False

    # ---------- 内存布局 ----------
    regions: list = []

    # ---------- 外设 ----------
    uart_base: int = 0x11002000
    uart_status_off: int = 0x14
    uart_status_value: int = 0x21        # bit0=RX ready, bit5=TX ready
    timer_reg: int = 0x10008048
    usb_base: int = 0x11201000
    usb_ep_fifo_off: int = 0x300         # 端点 0 的 FIFO 偏移
    #: USB bulk 端点的单包上限。BROM 的 RX 缓冲就是这么大；
    #: 主机传输超过它时必须切包（真机由 USB 控制器切，模拟器在这里切）。
    usb_max_packet: int = 512
    efuse_base: int = 0x11C10000

    # ---------- BROM 内部 SRAM 变量 ----------
    bootmode_addr: int = 0x00102884
    rx_len_addr: int = 0x001054D8
    rx_buf_addr: int = 0x001054DC
    rx_idx_addr: int = 0x001027B8
    tx_done_addr: int = 0x001027BC
    usb_cb_ep0_addr: int = 0x001029C8      # EP0 RX 回调指针

    # ---------- 启动源选择器 ----------
    #: 有的芯片用一个 MMIO 寄存器的低位表示"从哪里启动"
    #: MT6853: 0x1000A000 & 0xF —— 1/2/3 继续，7/其它 停机
    boot_selector_addr: Optional[int] = 0x1000A000
    boot_selector_value: int = 1

    # ---------- 刻在内存区间里的设备寄存器 ----------
    #: 某些外设的寄存器并不在 MMIO 区，而是"镜像"在普通内存地址上。
    #: 地址 → 固定返回值。不给值就会在轮询循环里死等。
    #: 例（MT6853 的 0x10210000 外设）：
    #:     0x10210ABC  bit0 = 就绪
    #:     0x10210928  高字节 = 0xDF（版本）
    #:     0x10210A24  外设 ID 魔数
    device_regs: Dict[int, int] = {}

    #: "就绪类"寄存器的默认区间：区间内且 device_regs 没显式指定的，一律返回 1。
    #: None 表示不启用。
    ready_window: Optional[Tuple[int, int]] = None

    # ---------- 协议常量 ----------
    dl_magic: bytes = bytes.fromhex("a00a5005")

    # ---------- eFuse 位说明（仅文档用） ----------
    efuse_bits: Dict[int, str] = {}

    # ---------- 兜底映射（MTK 的别名地址区） ----------
    extra_regions: list = []

    # ---------- 方法 ----------
    def region_list(self) -> list:
        if self.regions:
            return self.regions
        return [
            MemRegion("rom", self.rom_base, self.rom_size, "rom"),
            MemRegion("sram", 0x00100000, 0x00040000, "ram"),
            MemRegion("mmio", 0x10000000, 0x10000000, "mmio"),
        ]

    def rom_path(self) -> str:
        return self.rom_file.format(chip=self.name)

    def in_ready_window(self, addr: int) -> bool:
        if self.ready_window is None:
            return False
        lo, hi = self.ready_window
        return lo <= addr < hi
