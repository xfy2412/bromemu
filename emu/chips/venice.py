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

from unicorn.arm_const import UC_ARM_REG_CPSR, UC_ARM_REG_SP


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
        mu.reg_write(UC_ARM_REG_SP, self.init_sp)
        mu.reg_write(UC_ARM_REG_CPSR, mu.reg_read(UC_ARM_REG_CPSR) | 0x20)
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

    def _image(self) -> bytes:
        """flash 里"应该读到"的数据：合成镜像（由 tools/make_xloader_shape.py 生成）。"""
        if self._img is None:
            p = Path(__file__).resolve().parents[2] / "sources/venice/xloader_synth.bin"
            self._img = p.read_bytes() if p.exists() else b""
        return self._img

    def read_mmio(self, machine, address: int, size: int):
        """0x4023E004 的轮询：先快照，再循环等它变（最多 0x1FFFF 次）。

        真机上是外设把响应写回该寄存器；仿真里让它每次读都变，
        使函数走"成功"分支（SRAM 0x21E08 = 1），先把启动流程推下去。
        等拿到真机该寄存器的实际语义再改成有意义的模型。
        """
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
        0xBDF0FAD4: 0x00000000,   # 安全类型（0/7 走"无需验签"分支；真机实测 SECURE=5，见文档）
        0xBDF0F928: 0xBF000000,   # 高字节须为 0xBF
        0xBDF0FA24: 0xD5C63000,   # 外设 ID 魔数
        0x4020A3A0: 0x00000000,   # bit15=0 → flash 路径
        0x4020A008: 0x00000000,
        0x40201E04: 0x00000000,   # 状态字
    }
