"""transport.py -- 模拟器对外的 USB 传输抽象

设计目标
--------
让 mtkclient / bromd / 脚本 都能"对着模拟器发命令"，就像对着真芯片一样。

BROM 侧的接口（反编译确认）
--------------------------
RX（外部 → 芯片）
    SRAM 0x001054D8  u32  数据长度（0 = 无数据）
    SRAM 0x001054DC  buf  数据
    SRAM 0x001027B8  u32  读指针

TX（芯片 → 外部）
    sub_5A70 逐字节攒进 0x1052D8，攒满 64/512 由 sub_5ADC 提交
    sub_5212 把数据写进 EP FIFO（0x11201000 + 16*ep + 768）
    sub_5E42 是"发送完成"中断，把 0x1027BC 置 1

本模块把这两端抽成统一的 ByteTransport：
    .poll_rx()      -> bytes | None    模拟器向传输层要数据
    .tx(data)                           模拟器把芯片发的数据交给传输层
"""
from __future__ import annotations

import queue
import socket
import threading
from typing import Optional


class ByteTransport:
    """字节流传输基类"""

    def poll_rx(self) -> Optional[bytes]:
        """模拟器请求：有没有新数据？返回 None 表示没有"""
        raise NotImplementedError

    def tx(self, data: bytes) -> None:
        """模拟器交付：芯片发出这些字节"""
        raise NotImplementedError

    def close(self) -> None:
        pass


# --------------------------------------------------------------------------
# 1. 脚本式：预置一段字节，按需吐出（用于回归测试）
# --------------------------------------------------------------------------
class ScriptedTransport(ByteTransport):
    """按脚本喂数据：预设一串响应，每次 poll_rx 吐一块

    典型用法：喂握手魔数 + 一串命令字节
        t = ScriptedTransport([b"\\xa0\\x0a\\x50\\x05", b"\\xfc", b"\\xfd"])
    """

    def __init__(self, chunks):
        self._chunks = [bytes(c) for c in chunks]
        self._i = 0
        self.sent = bytearray()          # 芯片发出来的所有字节

    def poll_rx(self) -> Optional[bytes]:
        if self._i < len(self._chunks):
            c = self._chunks[self._i]
            self._i += 1
            return c
        return None

    def tx(self, data: bytes) -> None:
        self.sent.extend(data)


# --------------------------------------------------------------------------
# 2. 文件式：从二进制文件读所有输入
# --------------------------------------------------------------------------
class FileTransport(ByteTransport):
    def __init__(self, path, chunk=64):
        self._data = open(path, "rb").read()
        self._off = 0
        self._chunk = chunk
        self.sent = bytearray()

    def poll_rx(self) -> Optional[bytes]:
        if self._off >= len(self._data):
            return None
        c = self._data[self._off:self._off + self._chunk]
        self._off += len(c)
        return c

    def tx(self, data: bytes) -> None:
        self.sent.extend(data)


# --------------------------------------------------------------------------
# 3. 交互式：stdin/stdout（手工调试）
# --------------------------------------------------------------------------
class StdioTransport(ByteTransport):
    def __init__(self):
        self._q = queue.Queue()
        self.sent = bytearray()
        self._stop = False
        t = threading.Thread(target=self._reader, daemon=True)
        t.start()

    def _reader(self):
        import sys
        while not self._stop:
            line = sys.stdin.readline()
            if not line:
                break
            s = line.strip()
            if not s:
                continue
            try:
                # 支持 "a0 0a 50 05" 或 "a00a5005"
                b = bytes.fromhex(s.replace(" ", "").replace("0x", ""))
            except ValueError:
                print("[transport] 用法：输入十六进制字节，如 'fc' 或 'a0 0a 50 05'")
                continue
            self._q.put(b)

    def poll_rx(self) -> Optional[bytes]:
        try:
            return self._q.get_nowait()
        except queue.Empty:
            return None

    def tx(self, data: bytes) -> None:
        import sys
        self.sent.extend(data)
        sys.stdout.write("\n<< 芯片发出 %d 字节: %s\n" % (len(data), data.hex(" ")))
        sys.stdout.flush()

    def close(self):
        self._stop = True


# --------------------------------------------------------------------------
# 4. socket：给 mtkclient / bromd 之类的真程序连
# --------------------------------------------------------------------------
class SocketTransport(ByteTransport):
    """监听一个 TCP 端口，客户端连上后即可双向收发

    协议（简单长度前缀）：
        客户端 → 模拟器：  u32 长度(BE) + 数据
        模拟器 → 客户端：  u32 长度(BE) + 数据
    """

    def __init__(self, host="127.0.0.1", port=28734):
        self.srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.srv.bind((host, port))
        self.srv.listen(1)
        self._q = queue.Queue()
        self.sent = bytearray()
        self.conn = None
        self.port = port
        threading.Thread(target=self._accept, daemon=True).start()

    def _accept(self):
        try:
            conn, _ = self.srv.accept()
        except OSError:
            return
        self.conn = conn
        print("[transport] 客户端已连接")

        def recv_loop():
            import struct
            while True:
                try:
                    hdr = self._recvn(conn, 4)
                    if not hdr:
                        break
                    n = struct.unpack(">I", hdr)[0]
                    body = self._recvn(conn, n) if n else b""
                    if n and not body:
                        break
                    self._q.put(body)
                except OSError:
                    break
            print("[transport] 客户端断开")

        threading.Thread(target=recv_loop, daemon=True).start()

    @staticmethod
    def _recvn(conn, n):
        buf = b""
        while len(buf) < n:
            c = conn.recv(n - len(buf))
            if not c:
                return b""
            buf += c
        return buf

    def poll_rx(self):
        try:
            return self._q.get_nowait()
        except queue.Empty:
            return None

    def tx(self, data: bytes):
        import struct
        self.sent.extend(data)
        if self.conn:
            try:
                self.conn.sendall(struct.pack(">I", len(data)) + data)
            except OSError:
                pass

    def close(self):
        try:
            self.srv.close()
        except OSError:
            pass


# --------------------------------------------------------------------------
# 5. 录制/回放包装
# --------------------------------------------------------------------------
class RecordingTransport(ByteTransport):
    """包一层，记录所有收发（便于回放和做回归测试）"""

    def __init__(self, inner: ByteTransport):
        self.inner = inner
        self.log = []          # [(方向, bytes)]

    def poll_rx(self):
        d = self.inner.poll_rx()
        if d:
            self.log.append(("rx", bytes(d)))
        return d

    def tx(self, data: bytes):
        self.log.append(("tx", bytes(data)))
        self.inner.tx(data)

    def close(self):
        self.inner.close()
