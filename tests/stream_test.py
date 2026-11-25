"""stream_test.py -- RX 字节流状态机的回归测试

验证（2026-11-08 改造后）：
    ① 一个 USB 包最多 usb_max_packet（MT6853 = 512）字节；
    ② 大块输入会被切成 512 B 包，剩下的留在待搬缓冲；
    ③ 不会覆盖 RX 缓冲后面的 RC/key 结构（0x1056DC / 0x105748）；
    ④ 分块方式不影响 BROM 的响应（1 B / 2 B / 整块 三种切法结果一致）；
    ⑤ 真实命令循环：未定义命令 0x00 / 0x11 的回显与预期一致。

用法：python tests/stream_test.py [--verbose]
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from unicorn.arm_const import (UC_ARM_REG_CPSR, UC_ARM_REG_PC,
                               UC_ARM_REG_SP)

from emu.chips import get
from emu.brom import BromModel
from emu.machine import BromMachine
from emu.transport import ScriptedTransport

CHIP = get("mt6853")
ROM = (ROOT / CHIP.rom_path()).read_bytes()
VERBOSE = "--verbose" in sys.argv

# sub_E852(1) 的副作用：comport 函数表 + 启动模式
COMPORT = ((0x102884, 1), (0x102888, 0x419F), (0x10288C, 0x4245),
           (0x102890, 0x5ADD), (0x102894, 0x5ADD))


def new_machine(chunks):
    tp = ScriptedTransport(chunks)
    model = BromModel(CHIP, transport=tp, timer_step=5000, verbose=VERBOSE)
    m = BromMachine(ROM, CHIP, model)
    import struct
    for addr, val in COMPORT:
        if addr == 0x102884:
            m.mu.mem_write(addr, bytes([val]))
        else:
            m.mu.mem_write(addr, struct.pack("<I", val))
    # USB TX 状态：usb_tx_put_byte / usb_tx_flush 要求 0x1052AD == 3，
    # 端点号在 0x102AA0。jump 路径里这两项不在文档的 5 个副作用里，
    # 但不设它们，命令回显会被 usb_tx_put_byte 直接丢掉（TX 恒空）。
    m.mu.mem_write(0x1052AD, b"\x03")
    m.mu.mem_write(0x102AA0, b"\x00")
    return m, model, tp


def run_cmdloop(chunks, max_ins=6_000_000):
    m, model, tp = new_machine(chunks)
    m.mu.reg_write(UC_ARM_REG_PC, 0xF830)
    m.mu.reg_write(UC_ARM_REG_SP, 0x00102700)
    m.mu.reg_write(UC_ARM_REG_CPSR, m.mu.reg_read(UC_ARM_REG_CPSR) | 0x20)
    try:
        m.mu.emu_start(0xF830 | 1, 0, count=max_ins)
    except Exception as e:
        return m, model, tp, "异常：%s" % e
    return m, model, tp, "指令数用尽"


def check(name, cond, detail=""):
    print("  %-46s %s%s" % (name, "PASS" if cond else "FAIL",
                            ("  " + detail) if detail else ""))
    return cond


def test_packetizer():
    print("[1] 包长上限 / 大块切包 / 不覆盖 RC 结构")
    m, model, tp = new_machine([])
    # 预置 RC/key 结构的哨兵
    m.mu.mem_write(0x1056DC, b"RC_I")
    m.mu.mem_write(0x105748, b"\xAA" * 16)

    data = bytes([0xFD]) + b"\x00" * 2847      # 2848 B
    model.feed_host(data)
    for _ in range(20):
        m._feed_rx()
        # 模拟 BROM 消费完一包
        m.mu.mem_write(CHIP.rx_len_addr, b"\x00\x00\x00\x00")
        if model.rx_pending_len() == 0:
            break

    lens = [p[0] for p in model.rx_packets]
    ok = True
    ok &= check("总字节数 = 2848", sum(lens) == 2848, str(sum(lens)))
    ok &= check("每包 <= 512", all(n <= 512 for n in lens), str(lens))
    ok &= check("切包 = 5×512 + 288", lens == [512, 512, 512, 512, 512, 288],
                str(lens))
    ok &= check("RC 结构未被覆盖",
                bytes(m.mu.mem_read(0x1056DC, 4)) == b"RC_I")
    ok &= check("0x105748 key 缓冲未被覆盖",
                bytes(m.mu.mem_read(0x105748, 16)) == b"\xAA" * 16)
    return ok


def test_chunk_invariance():
    print("[2] 分块方式不影响响应（0x00 + 0x11，未定义命令 → 回显自身）")
    seq = b"\x00\x11"
    results = []
    for name, chunks in (
        ("1 B 一块", [seq[0:1], seq[1:2]]),
        ("2 B 一整块", [seq]),
        ("每字节 + ZLP", [seq[0:1], b"", seq[1:2]]),
    ):
        m, model, tp, stop = run_cmdloop(chunks)
        tx = bytes(model.tx_bytes)
        results.append(tx)
        print("    %-12s tx=%s stop=%s" % (name, tx.hex(" "), stop))
    ok = check("三种切法 tx 完全一致",
               results[0] == results[1] == results[2],
               results[0].hex(" "))
    ok &= check("tx = 00 11",
                results[0] == bytes.fromhex("0011"),
                results[0].hex(" "))
    return ok


def test_single_command():
    print("[3] 单条 0x00 的基线响应")
    m, model, tp, stop = run_cmdloop([b"\x00"])
    tx = bytes(model.tx_bytes)
    ok = check("tx = 00", tx == bytes.fromhex("00"), tx.hex(" "))
    ok &= check("rx_packets = [1]", [p[0] for p in model.rx_packets] == [1],
                str([p[0] for p in model.rx_packets]))
    return ok


def test_hw_info():
    print("[4] 0xFD / 0xFC 响应（0x08000000 芯片信息寄存器）")
    m, model, tp, stop = run_cmdloop([b"\xFD\xFC"])
    tx = bytes(model.tx_bytes)
    print("    tx=%s" % tx.hex(" "))
    ok = check("0xFD = fd 14 71 00 00",
               tx[:5] == bytes.fromhex("fd14710000"), tx[:5].hex(" "))
    fc = tx[5:]
    ok &= check("0xFC = fc 8a00 ca01 0001 0000",
                fc == bytes.fromhex("fc8a00ca0100010000"), fc.hex(" "))
    return ok


def main():
    print("=== RX 字节流状态机测试 ===")
    ok = True
    ok &= test_packetizer()
    ok &= test_chunk_invariance()
    ok &= test_single_command()
    ok &= test_hw_info()
    print()
    print("结果：%s" % ("全部通过" if ok else "有失败"))
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
