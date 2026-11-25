# sources/venice —— Kirin 970（Venice）引导链素材

本目录只放**能公开的东西**：BootROM dump 与自造的测试镜像。
厂商的 xloader / fastboot 镜像**不进仓库**（见文末"为什么要自造"）。

## 文件

| 文件 | 大小 | 说明 |
|---|---|---|
| `brom.bin` | 65,536 B | BootROM dump（ROM 本体，映射到 `0x0`） |
| `xloader_synth.bin` | 30,720 B | **自造**的"xloader 形状"容器（4 KB 头 + 0x6800 载荷） |

`xloader_synth.bin` 由 `tools/make_xloader_shape.py` 生成，布局：

```
0x0000  4 KB 容器头
        0x1C  "xloader"
        0x80  0xE291F358（魔数）
        0x84  0x00010000（版本）
        0x88  0x00000073（计数，官方值）
        0x8C  0x00020102（bit17-18 = 1 ⇒ 容器 type=1）
0x1000  AArch32 ELF 桩（e_entry = 0x1034 + 0x1000）
```

**签名必然是错的** —— 这正是用途：让 BootROM 走完解析、进入验签，
在"校验失败"那一层观察行为、构造边界用例（段表越界、0 长度段、计数下溢……）。

## 重新生成

```bash
python tools/make_xloader_shape.py
```

## 为什么要自造而不是放真镜像

- 真 xloader 是华为/海思的**专有固件**，公开分发有版权风险
- 研究校验路径根本不需要真签名：我们要的是"解析成功、验签失败"的输入
- 自造镜像可以**任意改字节**，构造畸形容器比拿官方镜像容易得多

需要真镜像做对照时，放在仓库外，用脚本参数或环境变量指过去即可，不要提交。

## 校验

```bash
python - <<'EOF'
import hashlib
for name in ("brom.bin", "xloader_synth.bin"):
    d = open("sources/venice/" + name, "rb").read()
    print(name, len(d), hashlib.sha256(d).hexdigest())
EOF
```
