"""run_cmdloop.py -- 直接跑命令循环 sub_F830（跳过前置初始化）

为什么能这么做：
    sub_F830 开头就是 sub_F81C()（清 244 字节 + sub_638A() 安装 USB 回调），
    所以它自己会初始化，不依赖 sub_E244 的前置流程。

目标：验证 SEND_AUTH（0xE8）能不能被完整处理。

用法：python tests/run_cmdloop.py [--cmd E8] [--max-ins N]
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from unicorn import UC_HOOK_CODE
from unicorn.arm_const import *

from emu.chips import get
from emu.brom import BromModel
from emu.machine import BromMachine

CMDLoop = 0xF830


def main():
    chip = get("mt6853")
    rom = (ROOT / chip.rom_path()).read_bytes()
    model = BromModel(chip, timer_step=5000, verbose=False)
    m = BromMachine(rom, chip, model)

    # 把要发的命令放进 RX：先魔数握手，再跟一条命令
    cmd_hex = "e8"
    for a in sys.argv[1:]:
        if a.startswith("--cmd="):
            cmd_hex = a.split("=", 1)[1]
    cmds = bytes.fromhex(cmd_hex)
    model.inject_rx(cmds)

    # ★ 直接写 USB 回调指针（等价于 sub_E852(1) 的副作用）
    #    sub_E852(1) 会装：0x102888=0x419F 0x10288C=0x4245
    #                     0x102890=0x5ADD 0x102894=0x5ADD，且 0x102884=1
    print("=== 直接安装 USB 回调（sub_E852(1) 的副作用）===")
    import struct as _st
    for addr, val in ((0x102884, 1), (0x102888, 0x419F),
                      (0x10288C, 0x4245), (0x102890, 0x5ADD),
                      (0x102894, 0x5ADD)):
        if addr == 0x102884:
            m.mu.mem_write(addr, bytes([val]))
        else:
            m.mu.mem_write(addr, _st.pack("<I", val))
    print("  0x102888 = 0x%08X" % int.from_bytes(m.mu.mem_read(0x102888, 4), "little"))
    print("  0x10288C = 0x%08X" % int.from_bytes(m.mu.mem_read(0x10288C, 4), "little"))
    print("  0x102884 = 0x%02X" % int.from_bytes(m.mu.mem_read(0x102884, 1), "little"))

    # ★ 直接从命令循环入口开始
    m.mu.reg_write(UC_ARM_REG_PC, CMDLoop)
    m.mu.reg_write(UC_ARM_REG_SP, 0x00102700)
    m.mu.reg_write(UC_ARM_REG_CPSR, m.mu.reg_read(UC_ARM_REG_CPSR) | 0x20)

    seen = []
    uart = []

    def on_code(mu, addr, size, ud):
        if len(seen) < 4000:
            seen.append(addr)

    m.mu.hook_add(UC_HOOK_CODE, on_code)

    print("=== 从 sub_F830（命令循环）开始，注入 %s ===" % cmds.hex(" "))
    try:
        m.mu.emu_start(CMDLoop | 1, 0, count=60_000_000)
        print("  跑完")
    except Exception as e:
        print("  停在 PC=0x%05X : %s" % (m.mu.reg_read(UC_ARM_REG_PC), e))

    print()
    print(m.state())
    print(model.stats())
    print()
    print("=== 执行过的地址（前 60，去重保序）===")
    uniq = []
    for a in seen:
        if a not in uniq:
            uniq.append(a)
    print("  " + " ".join("%05X" % a for a in uniq[:60]))

    if model.uart_bytes:
        print()
        print("=== 串口 ===")
        print(model.uart_text())


if __name__ == "__main__":
    main()



