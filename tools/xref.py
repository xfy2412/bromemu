"""xref.py -- BROM 交叉引用工具（省得每次写一次性脚本）

用法：
    python xref.py callers 0xCE34          # 谁 bl 到这里
    python xref.py func 0xD26C             # 这个地址属于哪个函数
    python xref.py disasm 0xD250 0xD290     # 反汇编区间（自动解析 ldr 字面量）
    python xref.py bl 0xD250 0xD290         # 只列区间里的 bl
    python xref.py findstr TIMESTMP         # 找字符串
    python xref.py dword 0x00102760         # 找哪里引用了这个常量
"""
import os
import re
import struct
import sys

import capstone

# 路径相对本文件：tools/ 的上一级就是项目根
_ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BROM = os.path.join(_ROOT, "sources", "mt6853", "brom.bin")
DEC = os.path.join(_ROOT, "sources", "mt6853", "decompiled.c")

_d = None


def brom():
    global _d
    if _d is None:
        _d = open(BROM, "rb").read()
    return _d


def md():
    m = capstone.Cs(capstone.CS_ARCH_ARM, capstone.CS_MODE_THUMB)
    m.detail = True
    return m


def func_of(addr):
    """返回 (name, base, size)"""
    txt = open(DEC, encoding="utf-8", errors="replace").read()
    for m in re.finditer(r"^// =+\s+(\S+)\s+@0x([0-9A-F]+)\s+size=(\d+)\s+=+$",
                         txt, re.M):
        a = int(m.group(2), 16)
        s = int(m.group(3))
        if a <= addr < a + s:
            return m.group(1), a, s
    return None, None, None


def _thumb_bl_dest(off, d):
    hw1 = struct.unpack_from("<H", d, off)[0]
    hw2 = struct.unpack_from("<H", d, off + 2)[0]
    if (hw1 & 0xF800) != 0xF000 or (hw2 & 0xD000) != 0xD000:
        return None
    S = (hw1 >> 10) & 1
    imm10 = hw1 & 0x3FF
    J1 = (hw2 >> 13) & 1
    J2 = (hw2 >> 11) & 1
    imm11 = hw2 & 0x7FF
    I1 = 1 - (J1 ^ S)
    I2 = 1 - (J2 ^ S)
    imm = (S << 24) | (I1 << 23) | (I2 << 22) | (imm10 << 12) | (imm11 << 1)
    if S:
        imm -= 0x2000000
    return (off + 4 + imm) & 0xFFFFFFFF


def callers(target):
    d = brom()
    out = []
    for off in range(0, len(d) - 4, 2):
        if _thumb_bl_dest(off, d) == target:
            out.append(off)
    return out


def disasm(start, end):
    d = brom()
    m = md()
    for ins in m.disasm(d[start:end], start):
        extra = ""
        if ins.mnemonic == "ldr" and "pc" in ins.op_str:
            mm = re.search(r"#0x([0-9a-f]+)", ins.op_str)
            if mm:
                lit = ((ins.address + 4) & ~3) + int(mm.group(1), 16)
                if lit < len(d):
                    extra = "   → @0x%X = 0x%08X" % (
                        lit, int.from_bytes(d[lit:lit + 4], "little"))
        elif ins.mnemonic in ("bl", "blx") and "#0x" in ins.op_str:
            dest = int(ins.op_str.split("#0x")[1], 16)
            n, b, s = func_of(dest)
            if n:
                extra = "   → %s" % n
        yield "  %05X  %-9s %-26s%s" % (
            ins.address, ins.mnemonic, ins.op_str, extra)


def findstr(s):
    d = brom()
    pat = s.encode() if isinstance(s, str) else s
    out = []
    i = 0
    while True:
        i = d.find(pat, i)
        if i < 0:
            break
        out.append(i)
        i += 1
    return out


def findref(val):
    """找哪里把 val 当 dword 引用（字面量池）"""
    d = brom()
    pat = struct.pack("<I", val)
    out = []
    i = 0
    while True:
        i = d.find(pat, i)
        if i < 0:
            break
        out.append(i)
        i += 1
    return out


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        return 1
    cmd = sys.argv[1]

    if cmd == "func":
        a = int(sys.argv[2], 0)
        n, b, s = func_of(a)
        print("  0x%05X → %s @0x%X size=%s" % (a, n, b or 0, s))

    elif cmd == "callers":
        a = int(sys.argv[2], 0)
        n, b, s = func_of(a)
        print("  %s @0x%X size=%s 的调用者：" % (n, b or 0, s))
        for c in callers(a):
            cn, cb, cs = func_of(c)
            print("    bl @0x%05X   在 %s" % (c, cn))

    elif cmd == "disasm":
        start = int(sys.argv[2], 0)
        end = int(sys.argv[3], 0)
        n, b, s = func_of(start)
        print("  === %s @0x%X size=%s ===" % (n, b or 0, s))
        for line in disasm(start, end):
            print(line)

    elif cmd == "bl":
        start = int(sys.argv[2], 0)
        end = int(sys.argv[3], 0)
        m = md()
        d = brom()
        for ins in m.disasm(d[start:end], start):
            if ins.mnemonic in ("bl", "blx"):
                dest = int(ins.op_str.split("#0x")[1], 16)
                n, b, s = func_of(dest)
                print("  0x%05X  bl 0x%05X  → %s" % (ins.address, dest, n))

    elif cmd == "findstr":
        for a in findstr(sys.argv[2]):
            n, b, s = func_of(a)
            print("  0x%05X  （在 %s）" % (a, n))

    elif cmd == "dword":
        v = int(sys.argv[2], 0)
        for a in findref(v):
            n, b, s = func_of(a)
            print("  0x%05X  （在 %s）" % (a, n))

    else:
        print(__doc__)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())

