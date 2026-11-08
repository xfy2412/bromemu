"""mt6853.py -- MT6853 BROM profile

所有数值都来自 `sources/mt6853/decompiled.c` 的反编译，出处见注释。

验证状态
--------
    ✅ 从复位向量跑到 USB 下载态（sub_5A40）
    ⏸ sub_F830 命令循环：USB 端点寄存器交互未完全建模
"""
from __future__ import annotations

from dataclasses import dataclass

from .base import ChipProfile, MemRegion


class MT6853(ChipProfile):
    name = "mt6853"
    description = "MediaTek MT6853 (Dimensity 700/720) BROM"

    rom_file = "sources/mt6853/brom.bin"
    rom_base = 0x00000000
    rom_size = 0x00020000

    # sub_0000: b 0x28（复位向量）；0x28 起清寄存器、设 SP
    entry = 0x28
    # 0xA8/0xAC: sp = *(0x13234) - 8 = 0x102750 - 8
    init_sp = 0x00102748

    regions = [
        MemRegion("rom", 0x00000000, 0x00020000, "rom"),
        MemRegion("sram", 0x00100000, 0x00040000, "ram"),
        MemRegion("mmio", 0x10000000, 0x10000000, "mmio"),
    ]

    # sub_E704 / sub_E710: UART 在 0x11002000，状态在 +0x14
    #   读: ldrb r0,[r1,#0x14]; lsls r0,r0,#31  → 判 bit0（RX）
    #   写: ldrb r1,[r2,#0x14]; lsls r1,r1,#26  → 判 bit5（TX）
    uart_base = 0x11002000
    uart_status_off = 0x14
    uart_status_value = 0x21

    # sub_1F0: ldr r0,[r0,#0x48]，基址 0x10008000 → 自由运行计数器
    timer_reg = 0x10008048

    # sub_5516: MEMORY[0x11201000]/[0x11201080]/[0x11201084]
    # sub_5212: FIFO = 0x11201000 + 16*ep + 768
    usb_base = 0x11201000

    efuse_base = 0x11C10000

    # sub_E84C / sub_E852
    bootmode_addr = 0x00102884
    # sub_5B26
    rx_len_addr = 0x001054D8
    rx_buf_addr = 0x001054DC
    rx_idx_addr = 0x001027B8
    # sub_5E42
    tx_done_addr = 0x001027BC

    # sub_3E6C（USB）/ sub_E71C（UART）逐字节比对
    dl_magic = bytes.fromhex("a00a5005")

    # eFuse 相关位（来自 sub_8444 / sub_84D6 / sub_84A2 / sub_8498 / sub_8484）
    efuse_bits = {
        0x00: "bit3=sub_8444() 参与 sub_613E();"
              "bit17=sub_84D6() 是 sub_643A 的捷径条件;"
              "bit7=sub_84A2()",
        0x20: "sub_11C10120 bit2=sub_8498()",
        0x30: "sub_11C10130 &3 = sub_8484()（选公钥表条目）",
        0x90: "sbc_pubk_hash3（32 字节，SEND_AUTH 的锚）",
    }


