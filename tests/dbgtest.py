"""dbgtest.py -- 调试器冒烟测试

验证：
    · 断点命中
    · 内存写断点（watchpoint）
    · 单步
    · 寄存器/反汇编/内存查看
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from emu.chips import get
from emu.brom import BromModel
from emu.machine import BromMachine
from emu.debug import Debugger
from unicorn.arm_const import UC_ARM_REG_PC


def main():
    chip = get("mt6853")
    rom = (ROOT / chip.rom_path()).read_bytes()
    model = BromModel(chip, verbose=False)
    m = BromMachine(rom, chip, model)
    dbg = Debugger(m)

    print("=" * 72)
    print("测试 1：地址断点（入口 0x28 → 0x1C4）")
    print("=" * 72)
    dbg.bp(0x1C4, text="第一个初始化函数")
    r = dbg.run(200_000)
    print("  停止：%s" % r)
    print("  PC = 0x%08X" % m.mu.reg_read(UC_ARM_REG_PC))
    print()

    print("=" * 72)
    print("测试 2：连续单步 5 条 + 反汇编")
    print("=" * 72)
    dbg.clear()
    for i in range(5):
        pc = m.mu.reg_read(UC_ARM_REG_PC)
        print("  第 %d 步  PC=0x%05X" % (i + 1, pc))
        dbg.step(1)
    print()
    print(dbg.disasm(6))
    print()

    print("=" * 72)
    print("测试 3：寄存器")
    print("=" * 72)
    print(dbg.regs())
    print()

    print("=" * 72)
    print("测试 4：内存写断点（0x102884 启动模式）")
    print("=" * 72)
    dbg.clear()
    dbg.watch(0x00102884, "w", 4)
    r = dbg.run(3_000_000)
    print("  停止：%s" % r)
    if "内存写" in r:
        print("  ★ 抓到写入了！")
        print(dbg.mem(0x00102880, 32))
    print()

    print("=" * 72)
    print("测试 5：跑到 USB 下载态（用断点确认）")
    print("=" * 72)
    dbg.clear()
    dbg.bp(0x5A40, text="USB 下载主循环")
    r = dbg.run(8_000_000)
    print("  停止：%s" % r)
    print(dbg.state())
    print()
    print("  最后轨迹：")
    print(dbg.last_trace(10))


if __name__ == "__main__":
    main()

