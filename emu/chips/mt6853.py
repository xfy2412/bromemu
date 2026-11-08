"""mt6853.py -- MT6853 BROM profile

所有数值都来自 `sources/mt6853/decompiled.c` 的反编译 + Unicorn 实测，出处见注释。

验证状态
--------
    ✅ 从复位向量跑到 USB 下载态
    ✅ ROM 写保护（BROM 会试图把数据表写进代码区，真机上是掩膜 ROM 所以无效）
    ⏸ sub_F830 命令循环：USB 端点寄存器交互未完全建模
"""
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
    usb_ep_fifo_off = 0x300

    efuse_base = 0x11C10000

    # sub_E84C / sub_E852
    bootmode_addr = 0x00102884
    # sub_5B26
    rx_len_addr = 0x001054D8
    rx_buf_addr = 0x001054DC
    rx_idx_addr = 0x001027B8
    # sub_5E42
    tx_done_addr = 0x001027BC
    # sub_5516 里 EP0 RX 的回调指针
    usb_cb_ep0_addr = 0x001029C8

    # sub_10FC8: board_get_boot_source
    #   v3 = *(u32*)0x1000A000 & 0xF
    #   1/2/3 → 返回 1/2/3（继续）；7 → 返回 4（停机）；其它 → 255（停机）
    boot_selector_addr = 0x1000A000
    boot_selector_value = 1

    # 0x10210000 这块外设的寄存器"镜像"在普通内存区，Unicorn 不模拟它们。
    # 不给值就会在下面这些轮询循环里死等：
    #   sub_C7FE:  ldr r1,[r0,#0xabc]; and r1,#1; cmp r1,#0; beq 死等
    #   sub_CE1C:  ldr r1,[r0,#0xab4]; lsls r1,#31; beq 死等
    #   sub_C80A:  ldr r1,[r0,#0x928]; lsrs r1,#24; cmp r1,#0xDF
    #   sub_C81A:  ldr r1,[r0,#0xa24]; cmp r1,#0xD5C64100
    device_regs = {
        0x10210ABC: 0x00000001,     # 就绪位（sub_C7FE）
        0x10210AB4: 0x00000001,     # 就绪位（sub_CE1C）
        0x10210928: 0xDF000000,     # 高字节 0xDF = 外设版本
        0x10210A24: 0xD5C64100,     # 外设 ID 魔数
        # sub_C836:  ldr r0,[r4,#0xad4]; uxtb r5,r0; str r5,[r1]  ⇒ 低字节是"设备版本"
        #            sub_CC44 后面会 cmp r5,#3
        # sub_C8A4:  ldr r0,[r4,#0xad4]; ubfx r0,r0,#9,#1; cbz ⇒ bit9 必须为 0
        0x10210AD4: 0x00000005,     # 低字节=5（版本），bit9=0，bit8=0
        # sub_CDF4 读 0x10210AAC 当"数据"，sub_C836 取 bits[19:16] 判 0xC 或 3
        0x10210AAC: 0x00030000,     # bits[19:16] = 3
    }

    #: 0x10210000 外设的寄存器窗口：没显式指定的一律"已就绪"
    ready_window = (0x10210000, 0x10211000)

    # sub_3E6C（USB）/ sub_E71C（UART）逐字节比对
    dl_magic = bytes.fromhex("a00a5005")

    # eFuse 相关位（来自 sub_8444 / sub_84D6 / sub_84A2 / sub_8498 / sub_8484 …）
    efuse_bits = {
        0x00: "bit3=sub_8444(); bit7=sub_84A2(); bit8=sub_844E(); bit17=sub_84D6()",
        0x20: "bit2=sub_8498(); bit11=sub_10EFA()",
        0x30: "bit8=sub_8462(); bit12=sub_8530(); bit13=sub_853A(); &3=sub_8484()",
        0x90: "sbc_pubk_hash3（32 字节，SEND_AUTH 的锚）",
        0x60: "MT6993 的 D8=0xE7 反推：bit3=0",
    }

    # MTK BROM 里会出现 0x0Cxxxxxx 这类别名地址，用大块映射兜住
    extra_regions = [
        (0x0C000000, 0x01000000, "alias-0C"),
        (0x0D000000, 0x01000000, "alias-0D"),
        (0x02000000, 0x01000000, "alias-02"),
    ]



