"""run.py -- bromemu 命令行入口

    # 脚本式：喂握手魔数 + 两个查询命令
    python -m emu.run --chip mt6853 --chunks a00a5005 fc fd

    # 文件式
    python -m emu.run --chip mt6853 --transport file --input rx.bin

    # socket 式：给 mtkclient / bromd 连
    python -m emu.run --chip mt6853 --transport socket --port 28734

    # 交互式
    python -m emu.run --chip mt6853 --transport stdio

    # 列出已支持的芯片
    python -m emu.run --list
"""
from __future__ import annotations

import argparse
import sys
from pathlib import Path

# 允许 `python -m emu.run` 与 `python emu/run.py` 两种跑法
if __package__ in (None, ""):
    sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
    from emu import chips
    from emu.brom import BromModel
    from emu.machine import BromMachine
    from emu.transport import (ScriptedTransport, FileTransport,
                               StdioTransport, SocketTransport,
                               RecordingTransport)
else:
    from . import chips
    from .brom import BromModel
    from .machine import BromMachine
    from .transport import (ScriptedTransport, FileTransport,
                            StdioTransport, SocketTransport,
                            RecordingTransport)

ROOT = Path(__file__).resolve().parents[1]


def main(argv=None):
    ap = argparse.ArgumentParser(description="MTK BROM 全系统模拟器")
    ap.add_argument("--chip", default="mt6853", help="芯片型号（见 --list）")
    ap.add_argument("--list", action="store_true", help="列出已支持的芯片")
    ap.add_argument("--rom", help="覆盖 BROM 镜像路径")
    ap.add_argument("--max-ins", type=int, default=8_000_000)
    ap.add_argument("--bootmode", type=int, default=1)
    ap.add_argument("--timer-step", type=int, default=1)
    ap.add_argument("--transport", default="script",
                    choices=["script", "file", "stdio", "socket"])
    ap.add_argument("--chunks", nargs="*", default=None,
                    help="script 模式：按顺序喂的十六进制块（默认只喂握手魔数）")
    ap.add_argument("--input", help="file 模式输入文件")
    ap.add_argument("--port", type=int, default=28734)
    ap.add_argument("--quiet", action="store_true")
    args = ap.parse_args(argv)

    if args.list:
        print("已支持的芯片：")
        for n in chips.names():
            c = chips.get(n)
            print("  %-10s %s" % (n, c.description))
        return 0

    chip = chips.get(args.chip)

    rom_path = Path(args.rom) if args.rom else (ROOT / chip.rom_path())
    if not rom_path.exists():
        print("✗ 找不到 BROM 镜像：%s" % rom_path, file=sys.stderr)
        return 2
    rom = rom_path.read_bytes()

    # ---- 传输层 ----
    if args.transport == "script":
        chunks = args.chunks if args.chunks is not None else [chip.dl_magic.hex()]
        parsed = []
        for c in chunks:
            s = c.replace(" ", "").replace("0x", "")
            parsed.append(bytes.fromhex(s))
        tp = ScriptedTransport(parsed)
    elif args.transport == "file":
        if not args.input:
            ap.error("file 模式需要 --input")
        tp = FileTransport(args.input)
    elif args.transport == "stdio":
        tp = StdioTransport()
    else:
        tp = SocketTransport(port=args.port)
        print("等待客户端连接 127.0.0.1:%d …" % args.port)

    tp = RecordingTransport(tp)

    model = BromModel(chip, transport=tp, bootmode=args.bootmode,
                      timer_step=args.timer_step, verbose=not args.quiet)
    m = BromMachine(rom, chip, model)

    print("=== %s：从入口 0x%X 开始 ===" % (chip.name, chip.entry))
    result = m.run(args.max_ins)
    print()
    print("=== 结束 ===")
    print("结果：%s" % result)
    print(m.state())
    print(model.stats())

    uart = model.uart_text()
    if uart:
        print()
        print("=== 串口输出 ===")
        print(uart)

    if model.tx_bytes:
        print()
        print("=== USB 发出（hex）===")
        print(bytes(model.tx_bytes).hex(" "))

    print()
    print("=== 传输层记录（前 40 条）===")
    for direction, data in tp.log[:40]:
        print("  %s %s" % ("←" if direction == "rx" else "→", data.hex(" ")))

    tp.close()
    return 0


if __name__ == "__main__":
    sys.exit(main())
