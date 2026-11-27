"""venice.py -- HiSilicon Kirin 970（Venice）BootROM profile

数值来自对 `sources/venice/brom.bin` 的反汇编：ROM 头的 SP/复位向量、
`movw/movt` 扫出的外设基址、以及启动/校验路径的关键地址。
原始逆向笔记属于私有项目，未随本仓库发布；本文件只保留能从 dump 复现的事实。

验证状态
--------
    ✅ 从复位向量（0x48）跑过 2000 万条指令不崩
    ⏸ 未到 USB 下载态 / 命令循环（需要建模 SEB / eFuse / USB 控制器）

已知事实（反汇编）
------------------
* ROM 头：`0x0` = 0x0004DBFC（初始 SP）；`0x4` = 0x00000049（复位向量，Thumb @0x48）
* `0x8` 起是一串 `0x000000B1` —— 指向 `0xB0` 的 `b 0xB0` 死循环，即默认异常处理
* 引导主线在 `0x620`；VCOM 帧分发器 `0x35f8`；策略分发 `0x40e0`；
  校验 `0x3f40`（内部 `0x43cc` 逐段 → `0x4a88`）
* 镜像装载区 `0x20000+0x2000`（即 `0x22000`）；校验长度上限 `0x4DC00`
* SRAM 全局：状态字 `0x21e04`、`0x21e08`/`0x21e0c`/`0x21e10`、`0x21200`
* 外设（`movw/movt` 扫描）：
    - `0x4020a3a0` 启动源（bit15：0=flash / 1=USB 下载）
    - `0x4020a008` bit15（与上者同名的另一位）
    - `0x40201e04` 状态字镜像（与 SRAM `0x21e04` 同值）
    - `0xbc182000`–`0xbc1831xx` USB 控制器（约 30 个寄存器被访问）
    - `0xbdf0e004` SEB（`0xBDF0F000` 块内的入口之一）
"""
from .base import ChipProfile, MemRegion

from pathlib import Path

from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE

from unicorn.arm_const import (UC_ARM_REG_CPSR, UC_ARM_REG_R0, UC_ARM_REG_R1,
                              UC_ARM_REG_PC, UC_ARM_REG_R2, UC_ARM_REG_R3,
                              UC_ARM_REG_LR, UC_ARM_REG_SP)


class Venice(ChipProfile):
    name = "venice"
    description = "HiSilicon Kirin 970 (Venice) BootROM"

    rom_file = "sources/{chip}/brom.bin"
    rom_base = 0x00000000
    rom_size = 0x00010000          # 64 KB

    # 复位向量：ROM[4] = 0x49 → Thumb @0x48
    entry = 0x48
    # ROM[0] = 0x0004DBFC
    init_sp = 0x0004DBFC

    def init_cpu(self, mu, entry: int) -> int:
        """Kirin BootROM 是 Thumb-2 代码。

        · ROM[0] 给了初始 SP（ROM 本身不设栈）
        · 入口是奇数地址（interworking 约定：LSB=1 表示目标是 Thumb）
        · 同时要置 CPSR.T，否则引擎会按 ARM 解码 → 第一条就崩
        """
        import os as _os_sp
        sp = int(_os_sp.environ.get("VENICE_SP", str(self.init_sp)), 0)
        mu.reg_write(UC_ARM_REG_SP, sp)
        mu.reg_write(UC_ARM_REG_CPSR, mu.reg_read(UC_ARM_REG_CPSR) | 0x20)

        # 诊断：VENICE_DUMP_SEB=1 时，打印 SEB 命令包装（0x5538）与描述符构造（0x6a70）的入参
        import os as _os_seb
        if _os_seb.environ.get("VENICE_DUMP_SEB"):

            def _dump_seb_cmd(uc, address, size, user_data):
                try:
                    print("[seb] 0x5538 cmd=0x%X out=0x%X"
                          % (uc.reg_read(UC_ARM_REG_R1), uc.reg_read(UC_ARM_REG_R2)),
                          flush=True)
                except Exception:
                    pass

            def _dump_desc(uc, address, size, user_data):
                try:
                    regs = [uc.reg_read(r) for r in (UC_ARM_REG_R0, UC_ARM_REG_R1,
                                                     UC_ARM_REG_R2, UC_ARM_REG_R3)]
                    print("[desc] 0x6a70 r0=0x%X r1=0x%X r2=0x%X r3=0x%X" % tuple(regs),
                          flush=True)
                    for tag, ptr in (("r1", regs[1]), ("r2", regs[2]), ("r3", regs[3])):
                        if 0xFFF00000 <= ptr < 0xFFF80000:
                            ptr = ptr - 0xFFF00000
                        if 0x10000 <= ptr < 0xFFFFFFFF:
                            raw = bytes(uc.mem_read(ptr, 0x40))
                            print("        %s@0x%X: %s" % (tag, ptr, raw.hex()), flush=True)
                except Exception as exc:
                    print("        dump failed:", exc, flush=True)

            mu.hook_add(UC_HOOK_CODE, _dump_seb_cmd, begin=0x5538, end=0x553A)
            mu.hook_add(UC_HOOK_CODE, _dump_desc, begin=0x6A70, end=0x6A72)

            def _dump_submit(uc, address, size, user_data):
                try:
                    ptr = uc.reg_read(UC_ARM_REG_R0)
                    ln = uc.reg_read(UC_ARM_REG_R3)
                    if ln > 0x200:
                        ln = 0x200
                    if 0x10000 <= ptr < 0x80000 and ln:
                        raw = bytes(uc.mem_read(ptr, ln))
                        print("[submit] 0x%X len=0x%X: %s" % (ptr, ln, raw.hex()), flush=True)
                except Exception:
                    pass

            mu.hook_add(UC_HOOK_CODE, _dump_submit, begin=0x4F0C, end=0x4F0E)
            print("[venice] SEB dump 已启用", flush=True)

        # 诊断：VENICE_SP_ADDR=0x... 时，在该地址打印 sp/lr（可多个，逗号分隔）
        import os as _os_sa
        _sa_spec = _os_sa.environ.get("VENICE_SP_ADDR")
        if _sa_spec:
            for _sa in _sa_spec.split(","):
                _sa_addr = int(_sa, 0)

                def _mk_sp_hook(a):
                    def _sp_hook(uc, address, size, user_data):
                        try:
                            print("[sp@0x%X] sp=0x%X lr=0x%X" % (
                                a, uc.reg_read(UC_ARM_REG_SP),
                                uc.reg_read(UC_ARM_REG_LR)), flush=True)
                        except Exception:
                            pass
                    return _sp_hook

                mu.hook_add(UC_HOOK_CODE, _mk_sp_hook(_sa_addr),
                            begin=_sa_addr, end=_sa_addr + 2)

        # 诊断/建模：VENICE_SKIP_DELAY=1 时，把纯 CPU 延时（0x243B0）的时长清零
        import os as _os_d
        if _os_d.environ.get("VENICE_SKIP_DELAY"):

            def _skip_delay(uc, address, size, user_data):
                try:
                    uc.reg_write(UC_ARM_REG_R0, 0)
                except Exception:
                    pass

            mu.hook_add(UC_HOOK_CODE, _skip_delay, begin=0x243B0, end=0x243B2)
            print("[venice] 延时跳过已启用", flush=True)

        # 诊断：VENICE_PC_HIST=1 时，统计 PC 热点（每 100 万条打印一次 top10）
        import os as _os_ph
        if _os_ph.environ.get("VENICE_PC_HIST"):
            _hist = {}
            _total = [0]

            def _pc_hist(uc, address, size, user_data):
                try:
                    pc = uc.reg_read(UC_ARM_REG_PC)
                    _hist[pc] = _hist.get(pc, 0) + 1
                    _total[0] += 1
                    if _total[0] % 1000000 == 0:
                        top = sorted(_hist.items(), key=lambda kv: -kv[1])[:10]
                        print("[pc-hist] %dM: %s" % (
                            _total[0] // 1000000,
                            ", ".join("0x%X×%d" % (a, c) for a, c in top)), flush=True)
                        _hist.clear()
                except Exception:
                    pass

            mu.hook_add(UC_HOOK_CODE, _pc_hist)
            print("[venice] PC 直方图已启用", flush=True)

        # 诊断：VENICE_DUMP_DIGEST=1 时，在 0x49b8（32 字节摘要比对）打印两侧指针与内容
        import os as _os_dg
        if _os_dg.environ.get("VENICE_DUMP_DIGEST"):

            def _dump_digest(uc, address, size, user_data):
                try:
                    regs = [uc.reg_read(r) for r in (UC_ARM_REG_R0, UC_ARM_REG_R1,
                                                     UC_ARM_REG_R2, UC_ARM_REG_R3)]
                    print("[digest] 0x49b8 r0=0x%X r1=0x%X r2=0x%X r3=0x%X" % tuple(regs),
                          flush=True)
                    for tag, ptr in (("r0", regs[0]), ("r1", regs[1])):
                        if 0x10000 <= ptr < 0x80000:
                            raw = bytes(uc.mem_read(ptr, 0x20))
                            print("        %s@0x%X: %s" % (tag, ptr, raw.hex()), flush=True)
                except Exception as exc:
                    print("        dump failed:", exc, flush=True)

            mu.hook_add(UC_HOOK_CODE, _dump_digest, begin=0x49B8, end=0x49BA)
            print("[venice] digest dump 已启用", flush=True)

        # 诊断：VENICE_PROBE_SP=1 时，进入 0x450 打印 SP 与 LR
        import os as _os_sp
        if _os_sp.environ.get("VENICE_PROBE_SP"):

            def _probe_sp(uc, address, size, user_data):
                try:
                    print("[sp] 0x450 entry sp=0x%X lr=0x%X"
                          % (uc.reg_read(UC_ARM_REG_SP), uc.reg_read(UC_ARM_REG_LR)),
                          flush=True)
                except Exception:
                    pass

            mu.hook_add(UC_HOOK_CODE, _probe_sp, begin=0x450, end=0x452)
            print("[venice] SP 探针已启用", flush=True)

        # 诊断：VENICE_WATCH=lo,hi 时，记录该区间内的每次写（默认 0x40000-0x80000 栈区）
        import os as _os_w
        _spec = _os_w.environ.get("VENICE_WATCH")
        if _spec:
            _lo, _hi = (0x40000, 0x80000)
            if _spec != "1":
                _parts = _spec.split(",")
                _lo, _hi = int(_parts[0], 0), int(_parts[1], 0)

            def _watch_write(uc, access, address, size, value, user_data):
                pc = uc.reg_read(UC_ARM_REG_PC)
                try:
                    print("[watch] pc=0x%X wr 0x%X size=%d val=0x%X"
                          % (pc, address, size, value), flush=True)
                except Exception:
                    pass

            mu.hook_add(UC_HOOK_MEM_WRITE, _watch_write, begin=_lo, end=_hi - 1)
            print("[venice] 写监视已启用 0x%X..0x%X" % (_lo, _hi), flush=True)

        # 诊断：VENICE_DUMP_HASH=1 时，打印 0x4964（哈希）的入参
        import os as _os_h
        if _os_h.environ.get("VENICE_DUMP_HASH"):
            def _dump_hash(uc, address, size, user_data):
                print("[hash] 0x4964(r0=0x%X, r1=0x%X, r2=0x%X, r3=0x%X)"
                      % (uc.reg_read(UC_ARM_REG_R0), uc.reg_read(UC_ARM_REG_R1),
                         uc.reg_read(UC_ARM_REG_R2), uc.reg_read(UC_ARM_REG_R3)),
                      flush=True)
                try:
                    for tag, ptr in (("r1", uc.reg_read(UC_ARM_REG_R1)), ("r2", uc.reg_read(UC_ARM_REG_R2))):
                        raw = bytes(uc.mem_read(ptr, 0x30))
                        print("        %s@0x%X: %s" % (tag, ptr, raw.hex()), flush=True)
                except Exception as exc:
                    print("        dump failed:", exc, flush=True)
            mu.hook_add(UC_HOOK_CODE, _dump_hash, begin=0x4964, end=0x4966)

        # 诊断：VENICE_DUMP_MEMCMP=1 时，把 0x47CC 的 (computed, expected, len) 打出来
        import os as _os_dump
        if _os_dump.environ.get("VENICE_DUMP_MEMCMP"):
            def _dump_cmp(uc, address, size, user_data):
                a = uc.reg_read(UC_ARM_REG_R0)
                b = uc.reg_read(UC_ARM_REG_R1)
                n = uc.reg_read(UC_ARM_REG_R2)
                try:
                    da = bytes(uc.mem_read(a, min(n, 64)))
                    db = bytes(uc.mem_read(b, min(n, 64)))
                    print("[memcmp] len=%d\\n  computed: %s\\n  expected: %s"
                          % (n, da.hex(), db.hex()), flush=True)
                except Exception as e:
                    print("[memcmp] dump failed:", e, flush=True)
            mu.hook_add(UC_HOOK_CODE, _dump_cmp, begin=0x47CC, end=0x47CE)

        # 研究用捷径：VENICE_SKIP_DIGEST=1 时，强制 0x49B8 的哈希比对"相等"
        # （我们伪造的 SEB 算不出真 SHA-256；跳过它才能继续观察加载/跳转）
        import os as _os_skip
        if _os_skip.environ.get("VENICE_SKIP_DIGEST"):
            def _force_equal(uc, address, size, user_data):
                uc.reg_write(UC_ARM_REG_R0, 1)
            mu.hook_add(UC_HOOK_CODE, _force_equal, begin=0x49D8, end=0x49DA)
            print("[venice] 已启用跳过摘要比对（VENICE_SKIP_DIGEST）", flush=True)
        return entry | 1

    #: BootROM 没有日志，这里给关键地址配"旁白"
    log_points = {
        0x000048: "BootROM 复位入口  sp=0x{sp:X}",
        0x000420: "取安全类型 / 策略  r0=0x{r0:X}",
        0x000450: "装载后处理（验签分发）  r0=0x{r0:X} len=0x{r1:X}",
        0x0005AC: "读取 flash（按 0x4020A3A0.bit15 选路）  r0=0x{r0:X}",
        0x0006AC: "设备初始化（0x4A8）  r0=0x{r0:X}",
        0x000726: "跳转到镜像 entry  0x{r3:X}",
        0x003E68: "解析容器链  base=0x{r0:X}",
        0x004484: "解析容器块（magic/版本/type）  blk=0x{r0:X}",
        0x0040E0: "策略分发（按安全类型）  r0=0x{r0:X} limit=0x{r1:X} r2=0x{r2:X}",
        0x003F40: "分段验签  r0=0x{r0:X}",
        0x004F58: "SEB 就绪 / 身份检查",
    }

    #: SEB 命令号 → 结果值（0x4fa4 会检查 bits16-19 == 3 等）
    #: SEB 命令号 → 结果值。BootROM 与 xloader 用到的命令（静态枚举）：
    #:   0x0A / 0x0B / 0x33 / 0x3F
    #: 结果位域由消费代码决定，例如 0x0A 要求 bits16-19 == 3。
    SEB_RESULTS = {
        0x0A: 0x00030000,   # 取配置：bits16-19 = 3
        0x0B: 0x00000000,   # 未知语义，先给 0（成功）
        0x33: 0x00000000,   # 0x3F 同族查询，先给 0
        0x3F: 0x00000000,
        # 熔丝字（0x5028 循环读取）：全 1 ⇒ popcount=32 ⇒ 贡献 0
        **{i: 0xFFFFFFFF for i in range(0x10, 0x18)},
        # 期望值 = 累计贡献（全 1 时为 0）
        0x0B: 0x00000000,
    }

    #: 调试字符设备：往 0x90000000 写一个字节 = 打印到终端
    debug_putc_addr = 0x90000000

    # ---------- 动态寄存器模型（等待位/响应寄存器） ----------
    def __init__(self):
        # 0x4023E004：0x3BC4 那段轮询"值有没有变"的响应寄存器
        self._resp = 0
        # 0x4023E000 / 0x4023E008：触发与命令/掩码
        self._trig = 0
        self._cmd = 0
        self._evt_injected = False
        self._evt_count = 0
        self._dumped = False
        self._img = None
        self._seb_cmd = 0

    def _image(self) -> bytes:
        """flash 里"应该读到"的数据：合成镜像（由 tools/make_xloader_shape.py 生成）。"""
        if self._img is None:
            import os as _os_img
            override = _os_img.environ.get("VENICE_IMAGE")
            p = (Path(override) if override
                 else Path(__file__).resolve().parents[2] / "sources/venice/xloader_synth.bin")
            raw = p.read_bytes() if p.exists() else b""
            # VENICE_LOAD=elf: 模拟真机加载布局
            #   分区 0x0..0x1000 = 容器头；0x1000 起 = ELF（大小 0x21000 主镜像）
            #   BootROM 把 ELF 放到 0x23000 ⇒ 映射成 "0x1000 零 + ELF 前 0x21000"
            mode = _os_img.environ.get("VENICE_LOAD")
            if mode == "elf" and len(raw) > 0x1000:
                body = raw[0x1000:0x1000 + 0x21000]
                raw = raw[:0x1000] + body
            self._img = raw
        return self._img

    # 安全 SRAM 别名窗口：0xFFF00000..0xFFF80000 ↔ 0x00000..0x80000
    ALIAS_BASE = 0xFFF00000
    ALIAS_SIZE = 0x80000

    @classmethod
    def _alias_offset(cls, address):
        if cls.ALIAS_BASE <= address < cls.ALIAS_BASE + cls.ALIAS_SIZE:
            return address - cls.ALIAS_BASE
        return None

    def read_mmio(self, machine, address: int, size: int):
        off = self._alias_offset(address)
        if off is not None:
            return int.from_bytes(bytes(machine.mu.mem_read(off, size)), "little")
        # 虚拟时间：某些延时循环反复读硬件计数器（0x4023Exxx），
        # 让每次读都前进，否则仿真会永远自旋
        if 0x4023E000 <= address < 0x4023F000:
            self._timer = getattr(self, "_timer", 0) + 0x100000
            return self._timer & ((1 << (size * 8)) - 1)
        return self._read_mmio_real(machine, address, size)

    def _read_mmio_real(self, machine, address: int, size: int):

        """0x4023E004 的轮询：先快照，再循环等它变（最多 0x1FFFF 次）。

        真机上是外设把响应写回该寄存器；仿真里让它每次读都变，
        使函数走"成功"分支（SRAM 0x21E08 = 1），先把启动流程推下去。
        等拿到真机该寄存器的实际语义再改成有意义的模型。
        """
        # SEB 命令结果：0x5538 把命令写进 +0xAA4，再从 +0xAAC 读结果
        if address == 0xBDF0FAAC:
            return self.SEB_RESULTS.get(self._seb_cmd, 0)

        # 安全类型可切换：VENICE_TYPE=5 走真机（SECURE）；0/7 走免验分支
        if address == 0xBDF0FAD4:
            import os as _os_t
            return int(_os_t.environ.get("VENICE_TYPE", "0"), 0)

        if address == 0x4023E004:
            v = self._resp
            self._resp = (self._resp + 1) & 0xFFFFFFFF
            return v

        # 0xBF10C40C：存储控制器的事件队列计数（0x2494 用它决定有没有完成事件）。
        # 真机由控制器 DMA 写入；仿真里注入一条"完成"事件（evt=1），看流程能走多远。
        import os as _os2
        if address == 0xBF10C40C and _os2.environ.get("VENICE_RESP"):
            # 模拟"命令完成、响应已就绪"：填 [ctx+0xe34]+4（0x2494 见此即返回 0）
            try:
                p = int.from_bytes(machine.mu.mem_read(0x20E34, 4), "little")
                if 0x10000 <= p < 0x80000:
                    # 0x4a8 要求返回 0x22000（它把返回值与自己的参数比较）
                    machine.mu.mem_write(p + 4, (0x22000).to_bytes(4, "little"))
                    # 把"flash 里读到的"合成镜像放进装载区
                    img = self._image()
                    if img:
                        machine.mu.mem_write(0x22000, img)
                    return 0
            except Exception:
                pass
        if address == 0xBF10C40C:
            # 注意：必须在 0x221c 的清零循环之后注入（它会把 0x20000-0x20E38 清掉）
            if self._evt_count < 8:
                try:
                    ctx = 0x20000
                    q = int.from_bytes(machine.mu.mem_read(ctx + 0xE30, 4), "little")
                    import os as _os
                    if _os.environ.get("VENICE_DEBUG"):
                        print("[venice] ctx+0xE30 -> q=0x%X" % q)
                    if 0x10000 <= q < 0x80000:
                        import os
                        words = [int(x, 0) for x in os.environ.get("VENICE_EVT", "0x40").split(",")]
                        for i, w in enumerate(words):
                            machine.mu.mem_write(q + 4 * i, w.to_bytes(4, "little"))
                        self._evt_count += 1
                        return len(words)
                except Exception:
                    pass
            return 0
        return None

    def write_mmio(self, machine, address: int, size: int, value: int) -> bool:
        off = self._alias_offset(address)
        if off is not None:
            machine.mu.mem_write(off, int(value).to_bytes(size, "little"))
            return True
        return self._write_mmio_real(machine, address, size, value)

    def _write_mmio_real(self, machine, address: int, size: int, value: int) -> bool:
        # SEB 命令寄存器：记下命令号，供 +0xAAC 的结果查询用
        if address == 0xBDF0FAA4:
            # value = 0x10000/0x20000 | (cmd<<2)；>>2 后要剥掉 0x4000/0x8000 标志
            self._seb_cmd = (value >> 2) & 0x3FFF
            return True

        import os as _os
        if _os.environ.get("VENICE_DUMP") and address in (0xBF10C700, 0xBF10C704) and not self._dumped:
            self._dumped = True
            try:
                blk = machine.mu.mem_read(0x20000, 0x100)
                print("[venice] ctx@0x20000: " + blk.hex(" "))
                blk2 = machine.mu.mem_read(0x20100, 0x100)
                print("[venice] ctx@0x20100: " + blk2.hex(" "))
            except Exception as e:
                print("[venice] dump failed:", e)
        if address == 0x4023E000:
            self._trig = value
            return True
        if address == 0x4023E008:
            self._cmd = value
            return True
        return False

    regions = [
        MemRegion("rom", 0x00000000, 0x00010000, "rom"),
        # 0x10000 起是 SRAM：栈顶 0x4DBFC、镜像区 0x22000、全局 0x21eXX
        MemRegion("sram", 0x00010000, 0x00070000, "ram"),
        MemRegion("mmio", 0x40000000, 0x90000000, "mmio"),
    ]

    # ---------- 以下为 UNKNOWN，待实测/仿真确认 ----------
    # UART：麒麟 970 的串口基址尚未定位（COM1.0 走 USB，不是串口）
    uart_base = 0x00000000
    uart_status_off = 0x14
    uart_status_value = 0x21

    # 自由运行计数器：未定位
    timer_reg = 0x00000000

    # USB 控制器：0xbc182000 与 0xbc183000 两块，寄存器密集
    usb_base = 0xBC182000
    usb_ep_fifo_off = 0x300          # UNKNOWN，照 MTK 惯例先占位
    usb_max_packet = 512

    efuse_base = 0x00000000          # UNKNOWN

    # ---------- BROM 内部 SRAM 变量 ----------
    bootmode_addr = 0x00021E04       # 状态字（INQUIRE 返回它的 4 字节）
    rx_len_addr = 0x00000000         # UNKNOWN
    rx_buf_addr = 0x00000000         # UNKNOWN
    rx_idx_addr = 0x00000000         # UNKNOWN
    tx_done_addr = 0x00000000        # UNKNOWN
    usb_cb_ep0_addr = 0x00000000     # UNKNOWN

    # ---------- 启动源选择器 ----------
    # 0x4020a3a0 bit15：0 = flash 启动，1 = USB 下载（与 xloader 共用同一位）
    boot_selector_addr = 0x4020A3A0
    boot_selector_value = 0

    # ---------- 需要给值的 MMIO ----------
    # 这些是 BootROM 会轮询/读取的外设寄存器。真机上有硬件置位，
    # 仿真里不给值就会死等。数值待真机/协议实测后补。
    device_regs = {
        # 0x3C60 的延时循环：r1 = [0x4020A000] & 0x78；==0x10 走 0x1900 次，否则 0x13880 次
        # 0x3952 的轮询要 (reg & 0x78) == 0x20；0x3C60 的延时循环要 0x10（这里取 0x20 优先满足轮询）
        0x4020A000: 0x00000020,
        # 0x388C 的轮询要 bit0 == 1
        0x4020A10C: 0x00000001,
        # SEB（0x4F58 的就绪/身份检查）
        0xBDF0FABC: 0x00000001,   # bit0 = 就绪
        0xBDF0FAB4: 0x00000001,   # bit0 = 命令完成（0x554c 的轮询）
        0xBDF0FAAC: 0x00000000,   # 命令结果（0 = 成功）
        0xBDF0FAD4: 0x00000000,
        0xBDF0FE9C: 0x00000008,
        0xBDF0FA00: 0x00000004,   # 0x6C2E 轮询：非 0 且 bit2=1（哈希/签名完成）
        0xBDF0FBA0: 0x00000001,   # 结果码 1 = 成功（0x6C38 轮询）   # 0x6938 轮询 bit3（密码引擎/哈希就绪）   # 安全类型（0/7 走"无需验签"分支；真机实测 SECURE=5，见文档）
        0xBDF0F928: 0xBF000000,   # 高字节须为 0xBF
        0xBDF0FA24: 0xD5C63000,   # 外设 ID 魔数
        0x4020A3A0: 0x00000000,   # bit15=0 → flash 路径
        0x4020A008: 0x00000000,
        0x40201E04: 0x00000000,   # 状态字
    }
