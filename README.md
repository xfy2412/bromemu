# bromemu

用 [Unicorn](https://github.com/unicorn-engine/unicorn) 从**复位向量**开始跑真实的 MediaTek BROM 固件。

> **为什么需要它**：BROM 是 MTK 平台的信任根。它的很多行为取决于运行时的内存状态 ——
> 同一块 SRAM 会被不同阶段的函数反复覆盖。**纯静态反编译看不到这些覆盖**，
> 只有把固件真正跑起来、逐条指令地观察，才能确认"某个地址在某个时刻到底是什么"。

---

## 目录

- [状态](#状态)
- [快速开始](#快速开始)
- [命令行](#命令行)
- [传输后端](#传输后端)
- [支持的芯片](#支持的芯片)
- [架构](#架构)
- [贡献新机型](#贡献新机型)
- [只有真机能提供的东西](#-只有真机能提供的东西)
- [已知限制](#已知限制)
- [免责声明](#免责声明)

---

## 状态

**Alpha** —— 能跑，但还不能完整启动。

模拟器本身的完成度（与具体芯片无关的部分）：

| 能力 | 状态 |
|---|---|
| ARM32 复位向量启动 | ✅ |
| 内存映射 + MMIO 钩子 | ✅ |
| UART（数据 + 状态位） | ✅ |
| 自由运行 timer | ✅ |
| eFuse 只读区 | ✅ |
| USB 端点 FIFO（TX） | 🟡 最小建模 |
| USB 事件寄存器 | ⏸ 未建模 |
| ARM64 BROM | ⏸ 未支持 |
| MMU / cache | ⏸ 不建模（Unicorn 忽略 `mcr p15`） |

各芯片实际跑到哪，见 [`docs/chips/`](docs/chips/)。

---

## 快速开始

```bash
pip install -r requirements.txt
# 国内可加镜像：
#   pip install -i https://pypi.tuna.tsinghua.edu.cn/simple unicorn capstone

python -m emu.run --list
python -m emu.run --chip <chip> --max-ins 3000000
```

**输出长这样**（具体数值因芯片而异）：

```
[brom] <chip>：启动模式=1，下载魔数=<magic>
=== <chip>：从入口 0x28 开始 ===
=== 结束 ===
结果：指令数用尽
PC=0x...  CPSR=0x...  Thumb
SP=0x...  LR=0x...
串口 N 字节
timer 走了 N
```

> ⚠️ 每个芯片需要的**指令数下限不同**。跑不够会停在半路（比如 cache 维护循环里），
> 那是正常的 —— 看对应 `docs/chips/<chip>.md` 里的说明。

---

## 命令行

```
python -m emu.run [选项]

  --chip NAME          芯片（见 --list）
  --list               列出已支持芯片
  --rom PATH           覆盖 BROM 镜像路径
  --max-ins N          最大指令数（默认 8,000,000）
  --bootmode 0|1       启动模式（默认 1）
  --timer-step N       timer 每次读前进多少 tick（调试用）
  --transport T        script | file | stdio | socket
  --chunks A B C       script 模式的数据块（十六进制）
  --input PATH         file 模式的输入
  --port N             socket 端口（默认 28734）
  --quiet              不打印串口实时输出
```

---

## 传输后端

模拟器对外**只暴露一条字节流**，后端可替换。这是它能对接真实工具的关键。

| 后端 | 用途 |
|---|---|
| `script` | 预置一串响应，做回归测试 |
| `file` | 从文件批量喂数据 |
| `stdio` | stdin 敲十六进制，手工调试 |
| `socket` | **给 mtkclient / bromd 之类的真程序连** |
| `recording` | 包住任意后端，记录全部收发 |

**socket 协议**（简单长度前缀）：

```
客户端 → 模拟器：  u32 长度(BE) + 数据
模拟器 → 客户端：  u32 长度(BE) + 数据
```

```bash
# 终端 1
python -m emu.run --chip <chip> --transport socket --port 28734

# 终端 2：任何能连 TCP 的客户端都能当"刷机工具"
```

**自定义后端**只需继承 `ByteTransport` 并实现两个方法：

```python
from emu.transport import ByteTransport

class MyTransport(ByteTransport):
    def poll_rx(self):          # 模拟器问：有新数据吗？返回 bytes 或 None
        ...
    def tx(self, data: bytes):  # 模拟器说：芯片发出了这些字节
        ...
```

---

## 支持的芯片

| 芯片 | 说明 | 详细文档 |
|---|---|---|
| `mt6853` | MediaTek MT6853 (Dimensity 700/720) | [docs/chips/mt6853.md](docs/chips/mt6853.md) |

> 每份芯片文档里都有镜像指纹、已确认的内存布局、跑到哪一步、卡在哪个函数。

---

## 架构

```
emu/
  chips/
    base.py        ChipProfile：所有芯片相关字段的定义
    <chip>.py      某个芯片的具体取值
    __init__.py    注册表
  brom.py          外设语义（UART / timer / USB FIFO / eFuse）—— 无芯片常量
  machine.py       Unicorn 胶水（内存映射、钩子、执行）—— 无芯片常量
  transport.py     对外字节流
  run.py           命令行入口
sources/
  <chip>/          镜像 + 反编译 + 笔记
docs/
  chips/<chip>.md  每个机型的逆向笔记
```

**改动边界**：

| 你要做的事 | 只碰 |
|---|---|
| 加一个机型 | `emu/chips/` + `docs/chips/` |
| 加一种外设 | `emu/brom.py` |
| 换 CPU 后端（Unicorn → 别的） | `emu/machine.py` |
| 换对外接口（socket → USB/IP） | `emu/transport.py` |

---

## 贡献新机型

**两个文件就够：一个 profile，一份文档。**

### 1. 准备素材

```
sources/<chip>/
  brom.bin         BROM 镜像（真机 dump，必须有）
  brom.elf         可选：包装成 ELF，IDA 能直接加载
  decompiled.c     可选，但强烈建议：反编译结果对这个项目价值极大
  notes.md         可选：原始笔记
```

### 2. 写 profile

新建 `emu/chips/<chip>.py`，继承 `ChipProfile`。**必填项见 `base.py` 的注释**，
其余留空会走保守默认值（能跑，但行为可能不准）。

```python
from .base import ChipProfile


class MT6885(ChipProfile):
    name = "mt6885"
    description = "MediaTek MT6885"

    rom_file = "sources/mt6885/brom.bin"
    rom_base = 0x00000000
    rom_size = 0x00020000

    entry = 0x28                    # 复位向量跳到哪里
    init_sp = 0x00102748            # 入口设的初始 SP（可为 None）

    # 外设
    uart_base = 0x11002000
    uart_status_off = 0x14
    uart_status_value = 0x21        # bit0=RX ready, bit5=TX ready
    timer_reg = 0x10008048
    usb_base = 0x11201000
    efuse_base = 0x11C10000

    # BROM 内部 SRAM 变量（用于注入 / 劫持）
    bootmode_addr = 0x00102884
    rx_len_addr = 0x001054D8
    rx_buf_addr = 0x001054DC
    rx_idx_addr = 0x001027B8
    tx_done_addr = 0x001027BC

    # 协议常量
    dl_magic = bytes.fromhex("a00a5005")
```

### 3. 登记

```python
# emu/chips/__init__.py
from .mt6885 import MT6885
REGISTRY = {"mt6853": MT6853, "mt6885": MT6885}
```

### 4. 写文档

新建 `docs/chips/<chip>.md`，内容建议包含：

```
- 镜像指纹（SHA-256）
- 内存布局（ROM / SRAM / 外设地址）
- BROM 内部 SRAM 变量（哪个地址存什么）
- 关键函数的反编译摘要（sub_XXX 在干什么）
- 跑到哪一步、卡在哪个地址
- 待补的外设模型
```

模板见 [`docs/chips/TEMPLATE.md`](docs/chips/TEMPLATE.md)。

### 5. 跑起来，看卡在哪

```bash
python -m emu.run --chip mt6885 --max-ins 3000000
```

**卡住是正常的** —— 每个新机型都从这里开始。把 `PC=` 和串口日志发到 issue，
通常就能定位缺哪块外设。

---

## ⚠️ 只有真机能提供的东西

这些**无法从固件里推出来**，是社区的贡献重点：

| 项 | 从哪取 | 影响 |
|---|---|---|
| **eFuse 内容** | 芯片的 eFuse 区，部分型号有未认证读窗口 | 验签能否通过 |
| **公钥哈希** | eFuse 里的 32 字节锚点 | 验签锚点 |
| **启动模式来源** | 复位配置引脚 / boot strap | 模拟里默认强制成 1 |
| **存储设备** | eMMC/UFS 的 CID/CSD/EXT_CSD | 没有它 BROM 会停机 |
| **真机串口日志** | BROM 的 debug UART | 用来对照模拟输出是否正确 |

**有实机的话，一条 `brom.bin` + 一段串口日志就已经很有价值了。**

---

## 已知限制

1. **只支持 ARM（32 位）BROM** —— ARM64 BROM 需要扩展 `machine.py`
2. **不建模 MMU / cache** —— Unicorn 忽略 `mcr p15`，cache 维护循环是空转
3. **USB 端点寄存器只做了最小建模** —— 事件寄存器恒返回 0
4. **eFuse 默认全 0** —— 需要实测值才有意义
5. **串口输出是原始字节流** —— 可能含控制字符（乱码是正常的）

---

## 免责声明

本项目用于**安全研究**与**逆向工程学习**：

- 不含任何私钥或密钥材料
- 不提供绕过授权的方法
- 不保证对任何具体设备的适用性

**请勿用于未授权的设备。**
