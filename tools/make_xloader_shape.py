"""make_xloader_shape.py -- 生成"xloader 形状"的合成容器

目的
----
给模拟器/真机实验准备一个**格式正确、签名错误**的 xloader 镜像：
BootROM 能解析头部（魔数/type/名字），然后在验签阶段失败 ——
正好是我们观察校验路径、构造边界用例的入口。

不包含任何厂商二进制：头部字段是文档化的格式常量，
载荷是我们自己写的 AArch32 ELF 桩。

用法
----
    python tools/make_xloader_shape.py [输出路径]

默认输出：sources/venice/xloader_synth.bin
布局：4 KB 容器头 + 0x6800 载荷（总 0x7800 字节）
"""
from __future__ import annotations

import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

MAGIC = 0xE291F358          # +0x80
VERSION = 0x00010000        # +0x84
COUNT = 0x73                # +0x88（官方值）
FLAGS = 0x00020102          # +0x8C：bit17-18 = 1 ⇒ 容器 type=1

NAME_OFF = 0x1C
HEADER_OFF = 0x80
PAYLOAD_OFF = 0x1000
PAYLOAD_SIZE = 0x6800       # 与 BootROM 里 xloader 的最小装载尺寸一致（0x6800）




def thumb_print(msg: str, putc: int = 0x90000000) -> bytes:
    """生成"把 msg 打到调试字符设备"的 Thumb 代码。

    模拟器把写入 0x90000000 的字节直接输出到终端（见 Venice.debug_putc_addr）。
    """
    def mov_imm16(movt: bool, rd: int, imm: int) -> bytes:
        i = (imm >> 11) & 1
        imm4 = (imm >> 12) & 0xF
        imm3 = (imm >> 8) & 7
        imm8 = imm & 0xFF
        hw1 = (0xF2C0 if movt else 0xF240) | (i << 10) | imm4
        hw2 = (rd << 8) | (imm3 << 12) | imm8
        return struct.pack("<HH", hw1, hw2)

    code = bytearray()
    code += mov_imm16(False, 2, putc & 0xFFFF)
    code += mov_imm16(True, 2, (putc >> 16) & 0xFFFF)
    for ch in msg:
        code += struct.pack("<H", 0x2100 | (ord(ch) & 0xFF))   # movs r1,#imm8
        code += struct.pack("<H", 0x7011)                       # strb r1,[r2]
    code += struct.pack("<H", 0x4770)                           # bx lr
    return bytes(code)

def build_elf(payload_off: int) -> bytes:
    """造一个最小 AArch32 ELF：头 + 一小段 Thumb 代码。

    代码就三条：movs r0,#0 / bx lr / 死循环（永远不会被执行，只为形状正确）。
    """
    code_off = 0x34                     # ELF 头 0x34 字节
    load_base = 0x22000                 # BootROM 把镜像装到 0x22000
    elf_base = load_base + payload_off  # ELF 自身落在 0x23000
    code = thumb_print("XLOADER! from synthetic image\r\n")
    entry = elf_base + code_off

    ehdr = bytearray(0x34)
    ehdr[0:4] = b"\x7fELF"
    ehdr[4] = 1                          # ELFCLASS32
    ehdr[5] = 1                          # ELFDATA2LSB
    ehdr[6] = 1                          # EV_CURRENT
    ehdr[16:18] = struct.pack("<H", 2)        # ET_EXEC
    ehdr[18:20] = struct.pack("<H", 40)       # EM_ARM
    ehdr[20:24] = struct.pack("<I", 1)        # e_version
    ehdr[24:28] = struct.pack("<I", entry)    # e_entry（Thumb）
    ehdr[28:32] = struct.pack("<I", 0x34)     # e_phoff
    ehdr[32:36] = struct.pack("<I", 0)        # e_shoff
    ehdr[36:40] = struct.pack("<I", 0x5000000)  # e_flags (EABI v5)
    ehdr[40:42] = struct.pack("<H", 0x34)     # e_ehsize
    ehdr[42:44] = struct.pack("<H", 0x20)     # e_phentsize
    ehdr[44:46] = struct.pack("<H", 1)        # e_phnum

    phdr = bytearray(0x20)
    phdr[0:4] = struct.pack("<I", 1)              # PT_LOAD
    phdr[4:8] = struct.pack("<I", code_off)       # p_offset
    phdr[8:12] = struct.pack("<I", elf_base)      # p_vaddr
    phdr[12:16] = struct.pack("<I", elf_base)     # p_paddr
    phdr[16:20] = struct.pack("<I", len(code))    # p_filesz
    phdr[20:24] = struct.pack("<I", len(code))    # p_memsz
    phdr[24:28] = struct.pack("<I", 5)            # p_flags (R|X)
    phdr[28:32] = struct.pack("<I", 4)            # p_align

    return bytes(ehdr) + bytes(phdr) + code


def main() -> int:
    out = Path(sys.argv[1]) if len(sys.argv) > 1 else (ROOT / "sources/venice/xloader_synth.bin")

    img = bytearray(PAYLOAD_OFF + PAYLOAD_SIZE)

    # ---- 容器：三个链式块（BootROM 的 0x3e68 会顺链解析） ----
    # 块大小公式（0x4484）：type=1 时 size = (0x40 + (word88 & 0xffff)) * 4
    struct.pack_into("<I", img, 0x08, 1)
    struct.pack_into("<I", img, 0x0C, 1)
    img[NAME_OFF:NAME_OFF + 16] = b"xloader\x00" + b"\x00" * 8

    # 块1 type=1（头部）；块2 type=2（证书表，链到此结束）
    blocks = ((0x000, FLAGS), (0x2CC, 0x00040102), (0x598, FLAGS))
    for base, flags in blocks:
        struct.pack_into("<I", img, base + HEADER_OFF + 0x00, MAGIC)
        struct.pack_into("<I", img, base + HEADER_OFF + 0x04, VERSION)
        struct.pack_into("<I", img, base + HEADER_OFF + 0x08, COUNT)
        struct.pack_into("<I", img, base + HEADER_OFF + 0x0C, flags)

    # ---- 载荷：自造 ELF ----
    elf = build_elf(PAYLOAD_OFF)
    img[PAYLOAD_OFF:PAYLOAD_OFF + len(elf)] = elf

    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(img)
    print("已生成 %s（%d 字节）" % (out, len(img)))
    print("  +0x1C 名字   = xloader")
    print("  +0x80 魔数   = 0x%08X" % MAGIC)
    print("  +0x84 版本   = 0x%08X" % VERSION)
    print("  +0x8C flags  = 0x%08X（type=%d）" % (FLAGS, (FLAGS >> 17) & 3))
    print("  +0x1000 载荷 = 自造 AArch32 ELF（e_entry=0x%X）" % (PAYLOAD_OFF + 0x34))
    return 0


if __name__ == "__main__":
    sys.exit(main())
