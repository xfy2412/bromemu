"""base.py -- 芯片 profile 的基类

设计原则
--------
1. **一切与芯片相关的常量都进 profile**，machine.py / transport.py 保持通用
2. 新机型只需继承 `ChipProfile` 并填字段，不改任何引擎代码
3. 字段缺失时有保守默认值（能跑起来，但行为可能不准）

贡献新机型的步骤
----------------
    1. 把 dump 放 sources/<chip>/brom.bin
    2. 新建 emu/chips/<chip>.py，继承 ChipProfile，填下面标了 [必填] 的
    3. 在 emu/chips/__init__.py 的 REGISTRY 里登记
    4. 运行 `python -m emu.run --chip <chip>` 看能跑到哪
"""
from __future__ import annotations

from abc import ABC
from dataclasses import dataclass, field
from typing import Dict, Optional


@dataclass
class MemRegion:
    """一段内存"""
    name: str
    base: int
    size: int
    kind: str = "ram"          # rom / ram / mmio


class ChipProfile(ABC):
    """一颗芯片的 BROM 特征"""

    # ---------- 身份 [必填] ----------
    name: str = "unknown"
    description: str = ""

    # ---------- 镜像 ----------
    rom_file: str = "sources/{chip}/brom.bin"
    rom_base: int = 0x00000000
    rom_size: int = 0x00020000

    # ---------- 入口 [必填] ----------
    entry: int = 0x28
    init_sp: Optional[int] = None

    # ---------- 内存布局 ----------
    regions: list = field(default_factory=list)

    # ---------- 外设 ----------
    uart_base: int = 0x11002000
    uart_status_off: int = 0x14
    uart_status_value: int = 0x21        # bit0=RX ready, bit5=TX ready
    timer_reg: int = 0x10008048
    usb_base: int = 0x11201000
    efuse_base: int = 0x11C10000

    # ---------- BROM 内部 SRAM 变量（用于注入/劫持） ----------
    bootmode_addr: int = 0x00102884
    rx_len_addr: int = 0x001054D8
    rx_buf_addr: int = 0x001054DC
    rx_idx_addr: int = 0x001027B8
    tx_done_addr: int = 0x001027BC

    # ---------- 协议常量 ----------
    dl_magic: bytes = bytes.fromhex("a00a5005")   # USB/UART 下载启动命令

    # ---------- 已知的 eFuse 位（键=寄存器偏移，值=说明） ----------
    efuse_bits: Dict[int, str] = field(default_factory=dict)

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

