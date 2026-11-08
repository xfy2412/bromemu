/*
 * ida_compat.h -- IDA Hex-Rays 反编译输出的兼容层
 *
 * 目的：让 decompiled*.c 能被 gcc -fsyntax-only 接受、编辑器能正常索引。
 *
 * ⚠️ 这只是"语法兼容"，不是"可运行"：
 *     · MEMORY[addr]     在 IDA 里表示"地址 addr 处的 32 位值"，这里是空指针解引用；
 *     · IDAW_MEM[addr]   表示"地址 addr 处的指针"，对应 IDA 的 *MEMORY[addr]；
 *     · JUMPOUT(x)       表示"控制流跳到未知地址"，这里是死循环；
 *     · __mrc/__mcr      是 ARM 协处理器指令，x86 上退化成 0 / 空操作。
 *   真要跑起来，请用 emu/ 下的 Unicorn 模拟器。
 *
 * 用法：在 decompiled*.c 最前面加
 *          #include "ida_compat.h"
 */

#ifndef IDA_COMPAT_H
#define IDA_COMPAT_H

#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

/* ---------------- 属性 ---------------- */
#ifndef __fastcall
#define __fastcall
#endif
#ifndef __cdecl
#define __cdecl
#endif
#ifndef __stdcall
#define __stdcall
#endif
#ifndef __noreturn
#define __noreturn
#endif
#ifndef __spoils
#define __spoils(...)
#endif
#ifndef BYREF
#define BYREF
#endif

/* ---------------- IDA 基本类型 ---------------- */
typedef uint8_t  _BYTE;
typedef uint16_t _WORD;
typedef uint32_t _DWORD;
typedef uint64_t _QWORD;
typedef int8_t   _BYTE_s;
typedef int16_t  _WORD_s;
typedef int32_t  _DWORD_s;
typedef int64_t  _QWORD_s;
typedef uint8_t  _UNKNOWN;

/* Windows 风格 */
#ifndef BOOL
typedef int32_t BOOL;
#endif

/* ---------------- 位域宏 ---------------- */
#ifndef HIBYTE
#define HIBYTE(x)  ((uint8_t)(((uint32_t)(x) >> 24) & 0xFF))
#define BYTE1(x)   ((uint8_t)(((uint32_t)(x) >> 16) & 0xFF))
#define BYTE2(x)   ((uint8_t)(((uint32_t)(x) >> 8) & 0xFF))
#define LOBYTE(x)  ((uint8_t)((uint32_t)(x) & 0xFF))
#endif
#ifndef HIWORD
#define HIWORD(x)  ((uint16_t)(((uint32_t)(x) >> 16) & 0xFFFF))
#define LOWORD(x)  ((uint16_t)((uint32_t)(x) & 0xFFFF))
#endif
#ifndef BYTEn
#define BYTEn(x, n) ((uint8_t)(((uint32_t)(x) >> (8 * (n))) & 0xFF))
#endif
#ifndef HIDWORD
#define HIDWORD(x)  ((uint32_t)(((uint64_t)(x) >> 32) & 0xFFFFFFFF))
#define SHIDWORD(x) ((int32_t)(((uint64_t)(x) >> 32) & 0xFFFFFFFF))
#define LODWORD(x)  ((uint32_t)((uint64_t)(x) & 0xFFFFFFFF))
#endif

/* ---------------- IDA 伪内存访问 ---------------- */
/* MEMORY[addr]   —— 地址 addr 处的 32 位值 */
#define MEMORY ((uint32_t *)0)
/* IDAW_MEM[addr] —— 地址 addr 处的指针（对应 IDA 的 *MEMORY[addr]） */
#define IDAW_MEM ((uint32_t **)0)

/* IDA 的"跳转到未知地址" */
#define JUMPOUT(x) do { while (1) { } } while (0)

/* ---------------- ARM 指令（x86 上退化为空操作） ---------------- */
static inline uint32_t __mrc(int coproc, int opc1, int crn, int crm, int opc2)
{ (void)coproc;(void)opc1;(void)crn;(void)crm;(void)opc2; return 0; }

static inline void __mcr(int coproc, int opc1, uint32_t val, int crn, int crm, int opc2)
{ (void)coproc;(void)opc1;(void)val;(void)crn;(void)crm;(void)opc2; }

static inline void __dsb(unsigned int o) { (void)o; }
static inline void __isb(unsigned int o) { (void)o; }
static inline void __dmb(unsigned int o) { (void)o; }
static inline void __wfi(void) {}
static inline void __wfe(void) {}
static inline void __sev(void) {}
static inline void __nop(void) {}

/* ---------------- IDA 的 nullsub ---------------- */
static inline void nullsub_1(void) {}
static inline void nullsub_2(void) {}
static inline void nullsub_3(void) {}
static inline void nullsub_4(void) {}
static inline void nullsub_5(void) {}
static inline void nullsub_6(void) {}
static inline void nullsub_7(void) {}
static inline void nullsub_8(void) {}
static inline void nullsub_9(void) {}
static inline void nullsub_10(void) {}
static inline void nullsub_11(void) {}
static inline void nullsub_12(void) {}

#endif /* IDA_COMPAT_H */
