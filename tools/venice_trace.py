"""venice_trace.py -- 跑 Venice BootROM 并统计 PC 热点与 MMIO 访问

用法：
    python tools/venice_trace.py [指令数]

产物（stdout）：
    · PC 命中前 25 名（判断卡在哪个循环）
    · MMIO 读/写地址表（判断缺哪些外设模型）
"""
from __future__ import annotations

import collections
import os
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT))

from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE  # noqa: E402
from unicorn.arm_const import (UC_ARM_REG_PC, UC_ARM_REG_R0, UC_ARM_REG_R1,
                              UC_ARM_REG_R2, UC_ARM_REG_R3)  # noqa: E402
from unicorn.arm_const import UC_ARM_REG_CPSR  # noqa: E402

from emu import chips  # noqa: E402
from emu.brom import BromModel  # noqa: E402
from emu.machine import BromMachine  # noqa: E402
from emu.transport import ScriptedTransport  # noqa: E402


def main() -> int:
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 2_000_000
    chip = chips.get("venice")
    rom = (ROOT / chip.rom_path()).read_bytes()
    tp = ScriptedTransport([bytes.fromhex(chip.dl_magic.hex())])
    model = BromModel(chip, transport=tp, bootmode=1, verbose=False)
    m = BromMachine(rom, chip, model)
    mu = m.mu

    pc_hits = collections.Counter()
    mmio_r = collections.Counter()
    mmio_w = collections.Counter()
    last_w = {}
    wpcs = {}
    rpcs = {}

    def on_code(uc, address, size, user):
        pc_hits[address & ~1] += 1

    def on_read(uc, access, address, size, value, user):
        if address >= 0x10000000:
            mmio_r[(address, size)] += 1

            pc = uc.reg_read(UC_ARM_REG_PC)
            rpcs.setdefault(address, []).append(pc & ~1)

    def on_write(uc, access, address, size, value, user):
        if address >= 0x10000000:
            mmio_w[(address, size)] += 1
            last_w[address] = value
            pc = uc.reg_read(UC_ARM_REG_PC)
            wpcs.setdefault(address, []).append((pc & ~1, value))

    probes = set()
    if os.environ.get("VENICE_PROBE"):
        probes = {int(x, 0) for x in os.environ["VENICE_PROBE"].split(",")}
    probe_hits = {}

    def on_code_probe(uc, address, size, user):
        a = address & ~1
        if a in probes:
            n = probe_hits.get(a, 0)
            if n < 8:
                probe_hits[a] = n + 1
                vals = [uc.reg_read(r) for r in
                        (UC_ARM_REG_R0, UC_ARM_REG_R1, UC_ARM_REG_R2, UC_ARM_REG_R3)]
                print("[probe] pc=0x%05X r0=0x%X r1=0x%X r2=0x%X r3=0x%X"
                      % (a, vals[0], vals[1], vals[2], vals[3]))

    mu.hook_add(UC_HOOK_CODE, on_code_probe)
    mu.hook_add(UC_HOOK_CODE, on_code)
    mu.hook_add(UC_HOOK_MEM_READ, on_read)
    mu.hook_add(UC_HOOK_MEM_WRITE, on_write)

    result = m.run(n)

    print("=== 结果 ===\n%s" % result)
    print(m.state())

    print("\n=== 关注点命中 ===")
    for a in (0x221C, 0x2328, 0x2330, 0x2494, 0x24B2, 0x2524, 0x252A, 0x17A4, 0x1BFC, 0x19E2, 0x1C08):
        print("  0x%05X  %d" % (a, pc_hits.get(a, 0)))
    print("\n=== PC 热点前 25 ===")
    for addr, cnt in pc_hits.most_common(25):
        print("  0x%05X  %8d" % (addr, cnt))

    print("\n=== MMIO 读（地址, 字节, 次数） ===")
    for (addr, size), cnt in sorted(mmio_r.items(), key=lambda kv: -kv[1])[:40]:
        print("  0x%08X  %d  %6d" % (addr, size, cnt))

    print("\n=== MMIO 写（地址, 字节, 次数, 最后值） ===")
    for (addr, size), cnt in sorted(mmio_w.items(), key=lambda kv: -kv[1])[:40]:
        print("  0x%08X  %d  %6d  last=0x%X" % (addr, size, cnt, last_w.get(addr, 0)))

    print("\n=== MMIO 读来源（地址 → 前 6 个 PC） ===")
    for addr in sorted(rpcs):
        print("  0x%08X: %s" % (addr, [hex(x) for x in rpcs[addr][:6]]))
    print("\n=== MMIO 写来源（地址 → 前 3 个 (PC, 值)） ===")
    for addr in sorted(wpcs)[:30]:
        print("  0x%08X: %s" % (addr, wpcs[addr][:3]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
