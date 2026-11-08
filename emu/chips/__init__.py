"""chips -- 芯片 profile 注册表

新机型在这里登记一行即可被 `--chip` 选中。
"""
from __future__ import annotations

from .base import ChipProfile, MemRegion
from .mt6853 import MT6853

REGISTRY = {
    "mt6853": MT6853,
}


def get(name: str) -> ChipProfile:
    cls = REGISTRY.get(name)
    if cls is None:
        raise KeyError("未知芯片 %r；已注册：%s" % (name, ", ".join(sorted(REGISTRY))))
    return cls()


def names():
    return sorted(REGISTRY)


__all__ = ["ChipProfile", "MemRegion", "REGISTRY", "get", "names", "MT6853"]
