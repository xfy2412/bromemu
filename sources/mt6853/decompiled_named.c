#include "ida_compat.h"
#include "ida_globals.h"

/*
 * MT6853 BROM —— 反编译结果（已重命名）
 *
 * 来源：IDA Hex-Rays 对 brom.bin 的输出（883 个函数）。
 *
 * 本文件把【已确认语义】的函数从 sub_XXXX 改成有意义的名字：
 *   · 函数头注释：// === brom_download_entry (sub_E244) @0xE244 size=326 ===
 *   · 定义行尾：  void brom_download_entry(...)  /* sub_E244 *\/
 *   ⇒ 文档/笔记里的 sub_E244 仍然能在本文件里搜到。
 *
 * 未确认语义的函数保持 sub_XXXX。
 *
 * 命名前缀：
 *   brom_   主流程        usb_    USB 相关      uart_   UART 相关
 *   auth_   SEND_AUTH     efuse_  eFuse 读取    mem_    内存操作
 *   time_   时间/延时     board_  板级配置      cmd_    命令处理
 *   hash_   哈希原语      periph_ 外设          trace_  调试区间
 *
 * 关键 SRAM / MMIO 变量对照表见文件末尾。
 */

// MT6853 BROM full decompile

// ==================== sub_4 @0x4 size=4 ====================
// attributes: thunk
void __noreturn sub_4()
{
  while ( 1 )
    ;
}


// ==================== sub_8 @0x8 size=4 ====================
// attributes: thunk
void __noreturn sub_8()
{
  while ( 1 )
    ;
}


// ==================== sub_C @0xC size=4 ====================
// attributes: thunk
void __noreturn sub_C()
{
  while ( 1 )
    ;
}


// ==================== sub_10 @0x10 size=4 ====================
// attributes: thunk
void __noreturn sub_10()
{
  while ( 1 )
    ;
}


// ==================== sub_14 @0x14 size=4 ====================
// attributes: thunk
void __noreturn sub_14()
{
  while ( 1 )
    ;
}


// ==================== sub_18 @0x18 size=4 ====================
// attributes: thunk
void __noreturn sub_18()
{
  while ( 1 )
    ;
}


// ==================== sub_1C @0x1C size=4 ====================
// attributes: thunk
void __noreturn sub_1C()
{
  while ( 1 )
    ;
}


// ==================== sub_C4 @0xC4 size=60 ====================
int sub_C4()
{
  return start(-1145324613, -1145324613, -1145324613, -1145324613);
}


// ==================== start @0x100 size=4 ====================
void start()
{
  JUMPOUT(0x846);
}


// ==================== sub_104 @0x104 size=16 ====================
void sub_104()
{
  ;
}


// ==================== sub_114 @0x114 size=60 ====================
void __fastcall __noreturn sub_114(int a1)
{
  MEMORY[0xC53C900] = a1;
  __mcr(15, 0, __mrc(15, 0, 12, 0, 2) | 1, 12, 0, 2);
  __dsb(0xFu);
  __isb(0xFu);
  __mcr(15, 0, __mrc(15, 0, 12, 0, 2) | 2, 12, 0, 2);
  __dsb(0xFu);
  __isb(0xFu);
  while ( 1 )
    __wfi();
}


// ==================== sub_160 @0x160 size=48 ====================
int sub_160()
{
  int v0; // r2
  unsigned int v1; // r12
  int v2; // r0
  unsigned int v3; // r2

  v0 = MEMORY[0x102D7C];
  v1 = MEMORY[0x102D78] + 4;
  v2 = IDAW_MEM[0x102D7C] + IDAW_MEM[0x102D78];
  IDAW_MEM[0x102D7C] = v2;
  v3 = v0 + 4;
  if ( v1 >= 0x102D78 )
    v1 = 1059996;
  if ( v3 >= 0x102D78 )
    v3 = 1059996;
  MEMORY[0x102D78] = v1;
  MEMORY[0x102D7C] = v3;
  return v2 & 0x7FFFFFFF;
}


// ==================== brom_periph_reset_sequence (sub_1AC) @0x1AC size=24 ====================
int brom_periph_reset_sequence()
{
  MEMORY[0x10008040] = 2;
  return 268468224;
}


// ==================== brom_early_periph_init (sub_1C4) @0x1C4 size=44 ====================
int __fastcall brom_early_periph_init(int a1)
{
  int result; // r0

  nullsub_1(1);
  result = brom_periph_reset_sequence();
  if ( a1 )
  {
    MEMORY[0x10008044] = 1;
    MEMORY[0x10008040] = 49;
    return 268468224;
  }
  return result;
}


// ==================== time_get_tick (sub_1F0) @0x1F0 size=12 ====================
int time_get_tick()
{
  return MEMORY[0x10008048];
}


// ==================== time_wait_ticks (sub_1FC) @0x1FC size=60 ====================
BOOL time_wait_ticks()
{
  unsigned int v0; // r0
  unsigned int v1; // r1
  unsigned int v2; // r2
  unsigned int v3; // r0

  v0 = time_get_tick();
  if ( v2 > v0 )
    v3 = v0 + ~v2;
  else
    v3 = v0 - v2;
  return v1 <= v3;
}


// ==================== sub_238 @0x238 size=16 ====================
unsigned int __fastcall sub_238(int a1)
{
  return (a1 + 5) / 6u;
}


// ==================== time_get_ms_count (sub_248) @0x248 size=56 ====================
unsigned int __fastcall time_get_ms_count(unsigned int a1)
{
  if ( a1 < 0x27620EE8 )
    return (500 * a1 + 999) / 0x3E8 + 6 * a1;
  else
    return -1;
}


// ==================== sub_280 @0x280 size=20 ====================
unsigned int __fastcall sub_280(int a1)
{
  return (a1 + 6499) / 0x1964u;
}


// ==================== time_ms_to_ticks (sub_294) @0x294 size=56 ====================
unsigned int __fastcall time_ms_to_ticks(unsigned int a1)
{
  if ( a1 < 0xA1501 )
    return (260 * a1 + 999) / 0x3E8 + 6500 * a1;
  else
    return -1;
}


// ==================== time_delay_ms (sub_2CC) @0x2CC size=44 ====================
BOOL __fastcall time_delay_ms(unsigned int a1)
{
  BOOL result; // r0

  time_get_ms_count(a1);
  time_get_tick();
  do
    result = time_wait_ticks();
  while ( !result );
  return result;
}


// ==================== time_delay_ms_v2 (sub_2F8) @0x2F8 size=44 ====================
BOOL __fastcall time_delay_ms_v2(unsigned int a1)
{
  BOOL result; // r0

  time_ms_to_ticks(a1);
  time_get_tick();
  do
    result = time_wait_ticks();
  while ( !result );
  return result;
}


// ==================== nullsub_1 @0x330 size=4 ====================
void nullsub_1()
{
  ;
}


// ==================== sub_334 @0x334 size=14 ====================
int sub_334()
{
  int result; // r0

  result = sub_584();
  if ( result )
  {
    while ( 1 )
      ;
  }
  return result;
}


// ==================== sub_342 @0x342 size=4 ====================
// attributes: thunk
int sub_342()
{
  return sub_4E6();
}


// ==================== sub_346 @0x346 size=34 ====================
int sub_346()
{
  int v0; // r0

  v0 = sub_342();
  if ( v0 )
  {
    if ( !MEMORY[0x102750] )
    {
      sub_506();
      MEMORY[0x102750] = 1;
    }
    v0 = sub_552();
  }
  return sub_598(v0);
}


// ==================== sub_368 @0x368 size=24 ====================
int sub_368()
{
  int result; // r0

  sub_5C0();
  result = sub_342();
  if ( result )
    return sub_56C();
  return result;
}


// ==================== sub_380 @0x380 size=4 ====================
// attributes: thunk
int sub_380()
{
  return sub_584();
}


// ==================== sub_384 @0x384 size=20 ====================
int sub_384()
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_5DC();
  return result;
}


// ==================== sub_398 @0x398 size=4 ====================
// attributes: thunk
int sub_398()
{
  return sub_5EA();
}


// ==================== sub_39C @0x39C size=20 ====================
int sub_39C()
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_5EE();
  return result;
}


// ==================== sub_3B0 @0x3B0 size=28 ====================
int __fastcall sub_3B0(int a1, int a2)
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_5FC(a1, a2);
  return result;
}


// ==================== sub_3CC @0x3CC size=28 ====================
int __fastcall sub_3CC(int a1, int a2)
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_600(a1, a2);
  return result;
}


// ==================== sub_3E8 @0x3E8 size=28 ====================
int __fastcall sub_3E8(int a1, int a2)
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_604(a1, a2);
  return result;
}


// ==================== sub_404 @0x404 size=4 ====================
// attributes: thunk
int sub_404()
{
  return sub_608();
}


// ==================== sub_408 @0x408 size=4 ====================
// attributes: thunk
int sub_408()
{
  return sub_60C();
}


// ==================== sub_40C @0x40C size=4 ====================
// attributes: thunk
int sub_40C()
{
  return sub_4F6();
}


// ==================== sub_410 @0x410 size=20 ====================
int sub_410()
{
  int result; // r0

  result = sub_608();
  if ( result )
    return sub_610();
  return result;
}


// ==================== sub_424 @0x424 size=4 ====================
// attributes: thunk
int sub_424()
{
  return sub_622();
}


// ==================== sub_428 @0x428 size=112 ====================
int __fastcall sub_428(int a1, _BYTE *a2)
{
  int v2; // r5

  v2 = 0;
  if ( !a2 )
    return 42001;
  *a2 = 0;
  switch ( a1 )
  {
    case 176:
      sub_346();
      break;
    case 177:
      sub_368();
      break;
    case 178:
      sub_424();
      break;
    case 179:
      sub_384();
      break;
    case 180:
      sub_398();
      break;
    case 181:
      sub_39C();
      break;
    case 182:
      sub_410();
      break;
    case 183:
      *a2 = sub_380();
      break;
    case 184:
      *a2 = sub_408();
      break;
    case 185:
      *a2 = sub_404();
      break;
    default:
      v2 = 42000;
      break;
  }
  return v2;
}


// ==================== sub_498 @0x498 size=4 ====================
// attributes: thunk
int sub_498()
{
  return sub_6C4();
}


// ==================== sub_4A0 @0x4A0 size=70 ====================
int sub_4A0()
{
  int v0; // r1
  unsigned int v1; // r0
  unsigned int v2; // r4

  v0 = 0;
  do
  {
    v1 = dword_12218[2 * v0];
    v2 = dword_12218[2 * v0 + 1];
    while ( v2 > v1 )
    {
      *(_DWORD *)(4 * v1 + 0x108000) = (v1 << 20) + 197650;
      ++v1;
    }
    ++v0;
  }
  while ( !v0 );
  MEMORY[0x108008] = 2229262;
  MEMORY[0x108004] = 1180686;
  return 1;
}


// ==================== sub_4E6 @0x4E6 size=16 ====================
BOOL sub_4E6()
{
  return sub_10F0E() == 0;
}


// ==================== sub_4F6 @0x4F6 size=16 ====================
BOOL sub_4F6()
{
  return sub_10F04() == 0;
}


// ==================== sub_506 @0x506 size=76 ====================
int sub_506()
{
  unsigned int i; // r0
  unsigned int j; // r0

  for ( i = 0; i < 0x1000; ++i )
    *(_DWORD *)(4 * i + 0x108000) = (i << 20) + 197650;
  for ( j = 1024; j < 0x500; ++j )
    *(_DWORD *)(4 * j + 0x108000) = (j << 20) + 132110;
  MEMORY[0x108000] = 164878;
  return sub_4A0();
}


// ==================== sub_552 @0x552 size=26 ====================
int sub_552()
{
  sub_11C08(0, 3);
  sub_11BF8(1081344);
  return sub_11DCC(1);
}


// ==================== sub_56C @0x56C size=24 ====================
int sub_56C()
{
  sub_11BC8(0);
  sub_11C34(0);
  return sub_11DD4(0);
}


// ==================== sub_584 @0x584 size=20 ====================
int sub_584()
{
  int result; // r0

  if ( sub_11810() )
    return 1;
  result = sub_11838();
  if ( result )
    return 1;
  return result;
}


// ==================== sub_598 @0x598 size=40 ====================
int sub_598()
{
  BOOL v0; // r5
  BOOL v1; // r4
  int v2; // r0

  v0 = sub_4F6();
  v1 = sub_4E6();
  v2 = sub_11BB8();
  if ( v0 )
    v2 = sub_117F0(1);
  if ( v1 )
    v2 = sub_1184C(v2);
  return sub_11DDC(v2);
}


// ==================== sub_5C0 @0x5C0 size=28 ====================
int sub_5C0()
{
  int v0; // r0
  int v1; // r0
  int v2; // r0

  v0 = sub_11A70();
  sub_11BB8(v0);
  v1 = sub_117F0(0);
  v2 = sub_11824(v1);
  return sub_11DDC(v2);
}


// ==================== sub_5DC @0x5DC size=14 ====================
int sub_5DC()
{
  int v0; // r0

  v0 = sub_11930();
  return sub_11DE4(v0);
}


// ==================== sub_5EA @0x5EA size=4 ====================
// attributes: thunk
int sub_5EA(void)
{
  return sub_11DEC();
}


// ==================== sub_5EE @0x5EE size=14 ====================
int sub_5EE()
{
  int v0; // r0

  v0 = sub_119D0();
  return sub_11DE4(v0);
}


// ==================== sub_5FC @0x5FC size=4 ====================
// attributes: thunk
int __fastcall sub_5FC(int a1, int a2)
{
  return sub_11DF4(a1, a2);
}


// ==================== sub_600 @0x600 size=4 ====================
// attributes: thunk
int __fastcall sub_600(int a1, int a2)
{
  return sub_11DFC(a1, a2);
}


// ==================== sub_604 @0x604 size=4 ====================
// attributes: thunk
int __fastcall sub_604(int a1, int a2)
{
  return sub_11E04(a1, a2);
}


// ==================== sub_608 @0x608 size=4 ====================
// attributes: thunk
int sub_608(void)
{
  return sub_11E0C();
}


// ==================== sub_60C @0x60C size=4 ====================
// attributes: thunk
int sub_60C(void)
{
  return sub_11E14();
}


// ==================== sub_610 @0x610 size=18 ====================
int sub_610()
{
  int v0; // r0
  int v1; // r0

  v0 = sub_11A70();
  v1 = sub_11BB8(v0);
  return sub_11DDC(v1);
}


// ==================== sub_622 @0x622 size=16 ====================
int sub_622()
{
  int v0; // r0

  v0 = sub_117F0(0);
  return sub_11E1C(v0);
}


// ==================== sub_632 @0x632 size=146 ====================
int __fastcall sub_632(int a1, _BYTE *a2)
{
  int v2; // r4
  int v3; // r0

  v2 = 0;
  if ( !a2 )
    return 42001;
  *a2 = 0;
  v3 = a1 - 186;
  switch ( v3 )
  {
    case 0:
      sub_56C();
      break;
    case 6:
      sub_11BC8(0);
      break;
    case 7:
      sub_11C34(0);
      break;
    case 8:
      sub_11BF8(0);
      break;
    case 9:
      sub_11C6C();
      break;
    case 10:
      sub_11890();
      break;
    case 11:
      sub_11930();
      break;
    case 12:
      sub_11824(v3);
      break;
    case 13:
      sub_11BB8(v3);
      break;
    case 14:
      sub_11BC0();
      break;
    case 15:
      sub_11868();
      break;
    case 16:
      sub_117F0(0);
      break;
    case 17:
      sub_119D0();
      break;
    case 18:
      sub_11A70();
      break;
    default:
      v2 = 42000;
      break;
  }
  return v2;
}


// ==================== sub_6C4 @0x6C4 size=34 ====================
int sub_6C4()
{
  int v0; // r0
  int v1; // r0

  v0 = sub_4E6();
  if ( v0 )
    v0 = sub_11930();
  sub_11BB8(v0);
  v1 = sub_4F6();
  if ( v1 )
    v1 = sub_11824(v1);
  return sub_11DDC(v1);
}


// ==================== sub_70C @0x70C size=8 ====================
int sub_70C()
{
  return MEMORY[0x10281C]();
}


// ==================== sub_714 @0x714 size=36 ====================
int __fastcall sub_714(int a1)
{
  int v2; // r4
  int v3; // r0

  sub_E7D4();
  v2 = MEMORY[0x102824](a1);
  v3 = sub_70C();
  sub_E7FC(v3, 115200);
  return v2;
}


// ==================== sub_738 @0x738 size=8 ====================
int sub_738()
{
  return MEMORY[0x102820]();
}


// ==================== sub_740 @0x740 size=8 ====================
int sub_740()
{
  return MEMORY[0x102828]();
}


// ==================== sub_748 @0x748 size=18 ====================
int sub_748()
{
  if ( sub_738() )
    return MEMORY[0x102754];
  else
    return 26000000;
}


// ==================== sub_75A @0x75A size=20 ====================
int sub_75A()
{
  if ( sub_738() )
    return MEMORY[0x102758];
  else
    return 6500;
}


// ==================== sub_77C @0x77C size=14 ====================
int sub_77C()
{
  MEMORY[0x1000C000] |= 2u;
  return 0;
}


// ==================== sub_78A @0x78A size=4 ====================
int sub_78A()
{
  return 0;
}


// ==================== sub_78E @0x78E size=300 ====================
void __fastcall sub_78E(int a1, int a2)
{
  int v3; // r0
  int v4; // r5
  int v5; // [sp+0h] [bp-8h]

  v5 = sub_10F80(0, a2);
  v3 = sub_10F9E();
  v4 = v3;
  if ( a1 )
  {
    MEMORY[0x1000C214] |= 1u;
    MEMORY[0x1000C264] |= 1u;
    MEMORY[0x1000C34C] |= 1u;
    time_delay_ms(0x1Eu);
    MEMORY[0x1000C214] &= ~2u;
    MEMORY[0x1000C264] &= ~2u;
    MEMORY[0x1000C34C] &= ~2u;
    if ( v5 )
    {
      MEMORY[0x1000C20C] = -2112605893;
      MEMORY[0x1000C25C] = -2112668909;
    }
    else
    {
      MEMORY[0x1000C20C] = -2129382341;
      MEMORY[0x1000C25C] = -2112076564;
    }
    MEMORY[0x1000C344] = -2146107392;
    MEMORY[0x1000C208] |= 1u;
    MEMORY[0x1000C258] |= 1u;
    MEMORY[0x1000C340] |= 1u;
    time_delay_ms(0x14u);
    time_delay_ms(0x14u);
    MEMORY[0x1000C208] |= 0x800000u;
    MEMORY[0x1000C258] |= 0x800000u;
    MEMORY[0x1000C340] |= 0x800000u;
    MEMORY[0x10001070] &= ~1u;
    MEMORY[0x10022034] &= ~0x10000000u;
    MEMORY[0x10001074] &= ~1u;
    MEMORY[0x10022038] &= ~0x4000000u;
    MEMORY[0x10022034] |= 2u;
    MEMORY[0x10000018] = 117440512;
    MEMORY[0x10000014] = 50331648;
    MEMORY[0x10000004] = 8;
    MEMORY[0x100000C8] = 50331648;
    MEMORY[0x100000C4] = 0x2000000;
    MEMORY[0x10000008] = 0x10000;
    MEMORY[0xC53A2A0] &= 0xFFC1FFFF;
    MEMORY[0xC53A2E0] &= 0xFFC1FFFF;
    MEMORY[0xC53A2A0] ^= 0x10000u;
    MEMORY[0xC53A2E0] ^= 0x10000u;
    MEMORY[0xC53A2A0] |= 0x200u;
    MEMORY[0xC53A2E0] |= 0x200u;
    if ( v4 )
    {
      MEMORY[0x1000C39C] |= 1u;
      time_delay_ms(0x1Eu);
      MEMORY[0x1000C39C] &= ~2u;
      MEMORY[0x1000C394] = -2078277632;
      MEMORY[0x1000C390] |= 1u;
      MEMORY[0x1023851C] = 368643;
      MEMORY[0x1024851C] = 368643;
      time_delay_ms(1u);
      MEMORY[0x1024851C] = 892931;
      time_delay_ms(2u);
      MEMORY[0x102384EC] = 258;
      time_delay_ms(1u);
      MEMORY[0x102384EC] = 256;
      time_delay_ms(1u);
      MEMORY[0x102384EC] = 305;
      time_delay_ms(1u);
      MEMORY[0x102384EC] = 432;
      time_delay_ms(1u);
    }
  }
  else
  {
    if ( v3 )
    {
      MEMORY[0x102384EC] = 257;
      time_delay_ms(1u);
      MEMORY[0x102384EC] = 256;
      time_delay_ms(1u);
      MEMORY[0x1023851C] = 360448;
      MEMORY[0x1024851C] = 360448;
      time_delay_ms(1u);
      MEMORY[0x1024851C] = 360448;
      time_delay_ms(1u);
      MEMORY[0x1000C390] &= ~1u;
      MEMORY[0x1000C39C] |= 2u;
      MEMORY[0x1000C39C] &= ~1u;
    }
    MEMORY[0x10001070] &= ~1u;
    MEMORY[0x10022034] &= ~0x10000000u;
    MEMORY[0x10001074] &= ~1u;
    MEMORY[0x10022038] &= ~0x4000000u;
    MEMORY[0x10022034] &= ~2u;
    MEMORY[0xC53A2A0] &= 0xFFFFF9FF;
    MEMORY[0xC53A2E0] &= 0xFFFFF9FF;
    MEMORY[0xC53A2A0] &= 0xFFC1FFFF;
    MEMORY[0xC53A2E0] &= 0xFFC1FFFF;
    MEMORY[0xC53A2A0] ^= 0x10000u;
    MEMORY[0xC53A2E0] ^= 0x10000u;
    MEMORY[0x100000C8] = 50331648;
    MEMORY[0x10000008] = 0x10000;
    MEMORY[0x10000018] = 117440519;
    MEMORY[0x10000004] = 9;
    MEMORY[0x1000C340] &= ~0x800000u;
    MEMORY[0x1000C208] &= ~1u;
    MEMORY[0x1000C258] &= ~1u;
    MEMORY[0x1000C340] &= ~1u;
    MEMORY[0x1000C214] |= 2u;
    MEMORY[0x1000C264] |= 2u;
    MEMORY[0x1000C34C] |= 2u;
    MEMORY[0x1000C214] &= ~1u;
    MEMORY[0x1000C264] &= ~1u;
    MEMORY[0x1000C34C] &= ~1u;
  }
  JUMPOUT(0xB10);
}


// ==================== sub_B20 @0xB20 size=326 ====================
int __fastcall sub_B20(int a1)
{
  if ( a1 )
  {
    MEMORY[0x1000C314] |= 1u;
    MEMORY[0x1000C3CC] |= 1u;
    time_delay_ms(0x1Eu);
    MEMORY[0x1000C314] &= ~2u;
    MEMORY[0x1000C30C] = -2145910784;
    MEMORY[0x1000C308] |= 1u;
    MEMORY[0x1000C3CC] &= 0xFFFFFFF9;
    MEMORY[0x1000C3C4] = -2145910784;
    MEMORY[0x1000C3CC] |= 5u;
    time_delay_ms(0x14u);
    time_delay_ms(0x14u);
    MEMORY[0x1000C308] |= 0x800000u;
    MEMORY[0x100000A8] = 117440512;
    MEMORY[0x100000A4] = 0x1000000;
    MEMORY[0x100000B8] = 7;
    MEMORY[0x100000B4] = 1;
    MEMORY[0x10000008] = 512;
  }
  else
  {
    MEMORY[0x100000A8] = 117440512;
    MEMORY[0x100000B8] = 7;
    MEMORY[0x10000008] = 512;
    MEMORY[0x1000C308] &= ~0x800000u;
    MEMORY[0x1000C308] &= ~1u;
    MEMORY[0x1000C3CC] &= ~4u;
    MEMORY[0x1000C314] |= 2u;
    MEMORY[0x1000C314] &= ~1u;
    MEMORY[0x1000C3CC] |= 2u;
    MEMORY[0x1000C3CC] &= ~1u;
  }
  return 0;
}


// ==================== sub_C66 @0xC66 size=6 ====================
int sub_C66()
{
  return MEMORY[0x10275C];
}


// ==================== sub_C70 @0xC70 size=50 ====================
unsigned int __fastcall sub_C70(unsigned int result, int a2, int a3)
{
  unsigned int v3; // r4
  int v5; // r5

  v3 = result;
  v5 = a3;
  if ( a3 )
    v5 = a3 - 1;
  if ( result >= 0xA || v5 )
  {
    result = sub_C70(result / 0xA, a2, v5);
    v3 %= 0xAu;
  }
  *(_BYTE *)(a2 + v5) = v3 + 48;
  return result;
}


// ==================== sub_CA2 @0xCA2 size=104 ====================
int __fastcall sub_CA2(_DWORD *a1)
{
  sub_C70(*(unsigned __int8 *)a1, 1058996, 3);
  sub_E4FA(a1[1], 1059000, 8);
  sub_E4FA(a1[2], 1059009, 8);
  sub_E4FA(a1[3], 1059018, 8);
  sub_E4FA(a1[4], 1059027, 8);
  sub_E4FA(a1[5], 1059036, 8);
  sub_C70(a1[5] - a1[4], 1059045, 5);
  return sub_EA46(1058996, 60, 0);
}


// ==================== sub_D0A @0xD0A size=80 ====================
_DWORD *sub_D0A()
{
  unsigned int i; // r4
  _DWORD *result; // r0

  MEMORY[0x1028C9] = 32;
  MEMORY[0x1028C0] = 32;
  MEMORY[0x1028B7] = 32;
  MEMORY[0x1028E4] = 32;
  MEMORY[0x1028DB] = 32;
  MEMORY[0x1028D2] = 32;
  MEMORY[0x1028EA] = 10;
  MEMORY[0x1028EB] = 13;
  MEMORY[0x1028EC] = 0;
  for ( i = 0; i < 0x46; ++i )
  {
    result = (_DWORD *)(MEMORY[0x102764] + 24 * i + 4);
    if ( MEMORY[0x103751] << 31 || *(unsigned __int8 *)result != 255 )
      result = (_DWORD *)sub_CA2(result);
  }
  return result;
}


// ==================== sub_D5A @0xD5A size=92 ====================
int sub_D5A()
{
  int result; // r0
  unsigned int v1; // r0
  int v2; // r2

  result = MEMORY[0x10375C];
  if ( MEMORY[0x103754] == 1162692948 && MEMORY[0x103758] == 1347245139 && MEMORY[0x10375C] )
    MEMORY[0x102760] = 1;
  if ( MEMORY[0x102760] )
  {
    MEMORY[0x102764] = MEMORY[0x10375C];
    mem_set_bytes();
    v1 = 0;
    v2 = MEMORY[0x102764];
    do
      *(_BYTE *)(v2 + 24 * v1++ + 4) = -1;
    while ( v1 < 0x46 );
    result = MEMORY[0x103750];
    if ( MEMORY[0x103750] )
    {
      if ( MEMORY[0x103750] != 1 && MEMORY[0x103750] != 2 )
      {
        MEMORY[0x103750] = 2;
        return 2;
      }
    }
  }
  return result;
}


// ==================== trace_begin (sub_DB6) @0xDB6 size=72 ====================
int __fastcall trace_begin(unsigned int a1, int a2)
{
  int result; // r0
  int v5; // r2
  int v6; // r2

  result = MEMORY[0x102760];
  if ( MEMORY[0x102760] && a1 < 0x46 )
  {
    result = time_get_tick();
    v5 = (unsigned __int8)IDAW_MEM[0x102764];
    if ( IDAW_MEM[0x102764] )
    {
      if ( v5 == 1 )
      {
        result = sub_238(result);
      }
      else if ( v5 == 2 )
      {
        result = sub_280(result);
      }
    }
    v6 = MEMORY[0x102764] + 24 * a1 + 4;
    *(_BYTE *)v6 = a1;
    if ( a2 )
      *(_DWORD *)(v6 + 20) = result;
    else
      *(_DWORD *)(v6 + 16) = result;
  }
  return result;
}


// ==================== trace_end (sub_DFE) @0xDFE size=40 ====================
unsigned int __fastcall trace_end(unsigned int result, int a2, int a3, int a4)
{
  if ( MEMORY[0x102760] && result < 0x46 )
  {
    result = MEMORY[0x102764] + 24 * result + 4;
    if ( *(unsigned __int8 *)result != 255 )
    {
      *(_DWORD *)(result + 4) = a2;
      *(_DWORD *)(result + 8) = a3;
      *(_DWORD *)(result + 12) = a4;
    }
  }
  return result;
}


// ==================== sub_E26 @0xE26 size=100 ====================
_DWORD *sub_E26()
{
  unsigned int i; // r5
  int v1; // r4

  if ( !MEMORY[0x102760] || IDAW_MEM[0x102764] )
    JUMPOUT(0xC9E);
  IDAW_MEM[0x102764] = MEMORY[0x103750];
  for ( i = 0; i < 0x46; ++i )
  {
    v1 = MEMORY[0x102764] + 24 * i + 4;
    if ( MEMORY[0x103750] == 1 )
    {
      *(_DWORD *)(v1 + 16) = sub_238(*(_DWORD *)(MEMORY[0x102764] + 24 * i + 20));
      *(_DWORD *)(v1 + 20) = sub_238(*(_DWORD *)(v1 + 20));
    }
    else if ( MEMORY[0x103750] == 2 )
    {
      *(_DWORD *)(v1 + 16) = sub_280(*(_DWORD *)(MEMORY[0x102764] + 24 * i + 20));
      *(_DWORD *)(v1 + 20) = sub_280(*(_DWORD *)(v1 + 20));
    }
  }
  return sub_D0A();
}


// ==================== sub_EA0 @0xEA0 size=16 ====================
int __fastcall sub_EA0(unsigned int a1)
{
  if ( ((a1 >> 8) & 0xF) == 2 )
    return 2;
  else
    return 0;
}


// ==================== sub_EB0 @0xEB0 size=136 ====================
int __fastcall sub_EB0(unsigned int a1)
{
  int v1; // r4
  int v2; // r7
  unsigned __int8 v3; // r1
  int v4; // r6
  BOOL v5; // r5
  int v6; // r0

  v1 = 0;
  v2 = sub_EA0(a1);
  v4 = v3 >> 4;
  v5 = sub_10E72() == 0;
  if ( !v4 )
    v4 = 0;
  MEMORY[0x102769] = 0;
  MEMORY[0x10276C] = 0;
  if ( !sub_1208(v4) )
    return 4097;
  if ( sub_10E68() == 1 && v2 == 2 )
    return 16396;
  trace_begin(0xCu, 0);
  v6 = sub_1392(v2, 8, v4);
  if ( v5 )
    sub_1B1A(v6);
  else
    sub_1A6C(v6);
  sub_150E(0);
  trace_begin(0xCu, 1);
  return v1;
}


// ==================== sub_F38 @0xF38 size=34 ====================
int sub_F38()
{
  int v0; // r0

  trace_begin(0xEu, 0);
  v0 = sub_1696(MEMORY[0x102768]);
  sub_14BA(v0);
  trace_begin(0xEu, 1);
  return 0;
}


// ==================== sub_F5A @0xF5A size=104 ====================
int __fastcall sub_F5A(unsigned int a1, int a2, unsigned int a3, _BYTE *a4)
{
  int v8; // r5
  unsigned int v9; // r0

  v8 = 0;
  v9 = 0;
  if ( a1 << 23 )
  {
    v8 = 16395;
  }
  else if ( MEMORY[0x10276C] >= a1 || (v9 = sub_1812(a1 - MEMORY[0x10276C], 0, 1), v9 < 0x30) )
  {
    v9 = sub_1812(a3, a2, 0);
    if ( v9 < 0x30 )
    {
      if ( a3 << 23 )
        a3 = ((a3 >> 9) + 1) << 9;
      MEMORY[0x10276C] = a1 + a3;
    }
    else
    {
      v8 = 16393;
    }
  }
  else
  {
    v8 = 16394;
  }
  MEMORY[0x10287C] = v9;
  *a4 = v9;
  return v8;
}


// ==================== sub_FC2 @0xFC2 size=314 ====================
int __fastcall sub_FC2(_DWORD *a1, void (__fastcall *a2)(int, _DWORD, int, int))
{
  int v4; // r10
  int v5; // r7
  int v6; // r9
  int v7; // r0
  unsigned int v8; // r4
  int v9; // r6
  unsigned int v10; // r0
  unsigned int v11; // r4
  unsigned int v12; // r0
  int v14; // [sp+0h] [bp-4h] BYREF

  v4 = (int)(a1 + 1);
  v5 = (int)(a1 + 129);
  v6 = (int)(a1 + 385);
  trace_begin(0xDu, 0);
  v7 = sub_1572(MEMORY[0x102768]);
  v14 = sub_177A(v7);
  MEMORY[0x10287C] = v14;
  trace_begin(0xDu, 1);
  trace_end(0xDu, (unsigned __int8)v14, 0, 0);
  if ( (unsigned __int8)v14 < 0x30u )
  {
    v9 = MEMORY[0x1028A8] << 11;
    v10 = MEMORY[0x1028A8] << 11;
    *a1 = MEMORY[0x1028A8] << 11;
    v11 = sub_F5A(v10, v4, 0x14u, &v14);
    if ( a2 )
      a2(0, (unsigned __int8)v14, v4, 20);
    if ( v11 < 0xFF )
    {
      if ( sub_116D8(v4, "EMMC_BOOT") && sub_116D8(v4, "COMBO_BOOT") )
      {
        v8 = 16386;
      }
      else
      {
        v12 = *(_DWORD *)(v4 + 16);
        if ( v12 < 0x200 || v12 << 23 )
        {
          v8 = 16387;
        }
        else
        {
          v8 = sub_F5A(v9 + 512, v5, 0xB4u, &v14);
          if ( a2 )
            a2(1, (unsigned __int8)v14, v5, 180);
          if ( v8 < 0xFF )
          {
            if ( sub_116D8(v5, "BRLYT") )
            {
              v8 = 16389;
            }
            else if ( *(_DWORD *)(v5 + 12) > (unsigned int)(v9 + 1536) )
            {
              v8 = sub_F5A(v9 + 1536, v6, 0x200u, &v14);
              if ( a2 )
                a2(3, (unsigned __int8)v14, v6, 512);
              if ( v8 >= 0xFF )
                v8 = 16390;
            }
          }
          else
          {
            v8 = 16388;
          }
        }
      }
    }
    else
    {
      v8 = 16385;
    }
  }
  else
  {
    v8 = 0x4000;
  }
  if ( (unsigned __int8)v14 == 55 || (unsigned __int8)v14 == 51 )
  {
    MEMORY[0x102769] = 1;
    return 4102;
  }
  return v8;
}


// ==================== sub_10FC @0x10FC size=88 ====================
unsigned int __fastcall sub_10FC(int a1, _DWORD *a2, int a3)
{
  unsigned int result; // r0
  int v5; // r1
  int v6; // [sp+0h] [bp-8h] BYREF
  int v7; // [sp+4h] [bp-4h] BYREF

  v6 = a3;
  v7 = 0;
  if ( (unsigned int)sub_F5A(*(_DWORD *)(a2[2] + 8), 1064648, 0x200u, &v7) < 0xFF )
  {
    result = auth_find_block_by_type(1064648, 0, &v6);
    if ( result < 0xFF )
    {
      result = auth_check_block_header(v6);
      if ( result < 0xFF )
      {
        v5 = v6;
        *a2 = *(_DWORD *)(v6 + 28);
        a2[1] = *(_DWORD *)(v5 + 32);
      }
    }
  }
  else
  {
    result = 16391;
  }
  if ( (unsigned __int8)v7 == 51 )
  {
    MEMORY[0x102769] = 1;
    return 4102;
  }
  return result;
}


// ==================== sub_1154 @0x1154 size=132 ====================
void __fastcall sub_1154(int a1, int *a2, void (__fastcall *a3)(int, _DWORD, int, unsigned int))
{
  unsigned int v5; // r6
  int v6; // r8
  int v7; // r11
  int v8; // r7
  unsigned int v9; // r5
  unsigned int v10; // r2
  int v11; // [sp+0h] [bp-4h] BYREF

  v11 = 0;
  v5 = 0;
  v6 = 0;
  v7 = *(_DWORD *)(a2[2] + 8);
  v8 = *a2;
  v9 = a2[1];
  if ( v9 <= 0x200 )
  {
    mem_copy_bytes(v8, 1064648, v9);
    v10 = 0;
  }
  else
  {
    mem_copy_bytes(v8, 1064648, 512);
    v5 = v7 + 512;
    v6 = v8 + 512;
    v10 = v9 - 512;
  }
  if ( v10 )
    sub_F5A(v5, v6, v10, &v11);
  if ( a3 )
    a3(a1, (unsigned __int8)v11, v8, v9);
  if ( (unsigned __int8)v11 == 51 )
    MEMORY[0x102769] = 1;
  JUMPOUT(0x10F8);
}


// ==================== sub_1208 @0x1208 size=34 ====================
BOOL sub_1208()
{
  return sub_10E5E() != 1 && ((MEMORY[0x100056F0] >> 17) & 3) == 1;
}


// ==================== sub_1230 @0x1230 size=56 ====================
int __fastcall sub_1230(unsigned int a1)
{
  int v1; // r1

  v1 = 1;
  if ( !a1 )
    return 0;
  if ( !(_WORD)a1 )
  {
    a1 >>= 16;
    v1 = 17;
  }
  if ( !(_BYTE)a1 )
  {
    a1 >>= 8;
    v1 += 8;
  }
  if ( !(a1 << 28) )
  {
    a1 >>= 4;
    v1 += 4;
  }
  if ( !(a1 << 30) )
  {
    a1 >>= 2;
    v1 += 2;
  }
  if ( !(a1 << 31) )
    ++v1;
  return v1;
}


// ==================== sub_1268 @0x1268 size=30 ====================
int __fastcall sub_1268(int *a1, unsigned int a2)
{
  int result; // r0
  int v4; // r4
  int v5; // r3

  result = a2;
  if ( a2 )
  {
    v4 = *a1 & ~a2;
    result = sub_1230(a2) - 1;
    *a1 = (v5 << result) | v4;
  }
  return result;
}


// ==================== sub_1286 @0x1286 size=28 ====================
int __fastcall sub_1286(int result, unsigned int a2, unsigned int *a3)
{
  int v4; // r4
  unsigned int v5; // r3

  v4 = *(_DWORD *)result;
  if ( a2 )
  {
    result = sub_1230(a2) - 1;
    *a3 = (v4 & v5) >> result;
  }
  return result;
}


// ==================== sub_12A2 @0x12A2 size=128 ====================
int __fastcall sub_12A2(int a1, int a2, unsigned int a3)
{
  int *v3; // r5
  int v4; // r4
  unsigned int v5; // r3
  unsigned int v6; // r6
  int result; // r0
  int v8; // r4

  v3 = *(int **)a1;
  v4 = 4 * a3 - 1;
  v5 = *(_DWORD *)(a1 + 4);
  v6 = 4 * a3;
  if ( a2 )
  {
    if ( a3 < v5 >> 2 )
      v5 = (v5 >> 2) / ((v5 + v4) / v6);
    else
      v5 >>= 2;
  }
  else if ( v5 != a3 )
  {
    if ( a3 < v5 >> 1 )
      v5 = (v5 >> 2) / ((v5 + v4) / v6);
    else
      v5 >>= 1;
  }
  *(_DWORD *)(a1 + 8) = v5;
  sub_1268(v3, 0x300000u);
  result = sub_1268(v3, 0xFFF00u);
  v8 = 20;
  while ( v8-- != 0 )
  {
    result = *v3 << 24;
    if ( (*v3 & 0x80) != 0 )
      break;
    result = time_delay_ms(0xC8u);
  }
  return result;
}


// ==================== sub_1322 @0x1322 size=22 ====================
unsigned int __fastcall sub_1322(int a1, unsigned int a2, int a3, unsigned int a4)
{
  return (a2 / (0x3B9ACA00u / *(_DWORD *)(a1 + 8)) + a3) / a4;
}


// ==================== sub_1368 @0x1368 size=42 ====================
int sub_1368()
{
  MEMORY[0x11230000] &= ~8u;
  sub_1268((int *)0x11230098, 0x7000u);
  return sub_1268((int *)0x11230098, 0x100u);
}


// ==================== sub_1392 @0x1392 size=296 ====================
int __fastcall sub_1392(int a1, int a2, char a3)
{
  int v7; // r0
  int v8; // r5
  bool v9; // cf
  int v10; // r5
  int savedregs; // [sp+0h] [bp+0h]
  int savedregs_36; // [sp+24h] [bp+24h]

  sub_10E72();
  MEMORY[0x102774] = a2;
  if ( !a1 && MEMORY[0x102778] == 1 )
  {
    MEMORY[0x102780] = 0;
    MEMORY[0x102770] = 0;
    MEMORY[0x102772] = 1;
    MEMORY[0x102778] = 2;
  }
  mem_set_bytes(1059056, 0, 16);
  MEMORY[0x1028F0] = 287506432;
  MEMORY[0x1028F4] = 26000000;
  MEMORY[0x1028FD] = a3;
  sub_39F0();
  v7 = nullsub_10(0);
  nullsub_11(v7);
  sub_1268((int *)0x11230000, 1u);
  sub_1268((int *)0x112300B8, 0x10000000u);
  sub_1268((int *)0x112300B8, 0x8000u);
  MEMORY[0x11230000] |= 4u;
  v8 = 20;
  while ( 1 )
  {
    v9 = v8-- != 0;
    if ( !v9 || (MEMORY[0x11230000] & 4) == 0 )
      break;
    time_delay_ms(0xC8u);
  }
  MEMORY[0x11230014] |= 0x80000000;
  v10 = 20;
  while ( 1 )
  {
    v9 = v10-- != 0;
    if ( !v9 || MEMORY[0x11230014] >= 0 )
      break;
    time_delay_ms(0xC8u);
  }
  sub_1268((int *)0x11230030, 0x30000u);
  MEMORY[0x11230000] |= 8u;
  if ( !sub_10E7C() )
  {
    MEMORY[0x102784] = 1;
    sub_1368();
  }
  MEMORY[0x11230078] |= 0x2Fu;
  sub_12A2(1059056, 0, MEMORY[0x10277C]);
  savedregs_36 = savedregs;
  return sub_1268((int *)(MEMORY[0x1028F0] + 48), 0xFF000000);
}


// ==================== sub_14BA @0x14BA size=84 ====================
int sub_14BA()
{
  _DWORD *v0; // r4
  int v1; // r5
  bool v2; // cf
  int v3; // r5

  v0 = (_DWORD *)MEMORY[0x1028F0];
  IDAW_MEM[0x1028F0] |= 4u;
  v1 = 20;
  while ( 1 )
  {
    v2 = v1-- != 0;
    if ( !v2 || (*v0 & 4) == 0 )
      break;
    time_delay_ms(0xC8u);
  }
  v0[5] |= 0x80000000;
  v3 = 20;
  while ( 1 )
  {
    v2 = v3-- != 0;
    if ( !v2 || (int)v0[5] >= 0 )
      break;
    time_delay_ms(0xC8u);
  }
  v0[3] = v0[3];
  nullsub_10(1);
  return nullsub_12(MEMORY[0x1028FD]);
}


// ==================== sub_150E @0x150E size=100 ====================
unsigned int __fastcall sub_150E(unsigned int result)
{
  unsigned int *v1; // r4

  v1 = (unsigned int *)MEMORY[0x1028F0];
  if ( result )
  {
    *(_DWORD *)(MEMORY[0x1028F0] + 56) = -252645136;
    v1[13] = 0;
  }
  else
  {
    *(_DWORD *)(MEMORY[0x1028F0] + 124) |= 1u;
    time_delay_ms(0x64u);
    v1[31] &= ~1u;
    *v1 |= 2u;
    time_delay_ms(0x190u);
    *v1 &= ~2u;
    v1[14] = -252645136;
    v1[13] = 0;
    *v1 |= 2u;
    time_delay_ms(0x190u);
    result = *v1 & 0xFFFFFFFD;
    *v1 = result;
  }
  return result;
}


// ==================== sub_1572 @0x1572 size=292 ====================
BOOL __fastcall sub_1572(int a1)
{
  _DWORD *v1; // r4
  BOOL v2; // r9
  int v3; // r5
  int v4; // r7
  int v5; // r6
  bool v6; // cf
  int v7; // r5
  BOOL result; // r0

  v1 = (_DWORD *)MEMORY[0x1028F0];
  v2 = a1 != 0;
  sub_1322(1059056, 0x2FAF080u, 0, 0x10000u);
  sub_1322(1059056, 0x3B9ACA00u, 0, 0x10000u);
  time_get_tick();
  v3 = 1000;
  v4 = 0;
  v5 = 1000;
  do
  {
    do
    {
      if ( !(v1[15] << 31) )
      {
        v4 = 1;
        break;
      }
      v6 = v3-- != 0;
    }
    while ( v6 );
    v3 = 1000;
    time_ms_to_ticks(0x64u);
  }
  while ( !time_wait_ticks() && !v4 );
  v1[28] |= 0x8000u;
  sub_1268(v1 + 28, 8u);
  sub_1268(v1 + 28, 4u);
  v1[20] = -1;
  sub_1268(v1 + 29, 0xFFF00000);
  sub_1268(v1 + 29, 0xFFFFFu);
  if ( v2 )
    v1[14] = -6;
  else
    v1[14] = 0;
  v1[13] = 33558528;
  time_delay_ms(0x28u);
  v1[28] |= 1u;
  time_get_tick();
  v7 = 0;
  do
  {
    while ( 2 )
    {
      if ( (v1[30] & 0x10) != 0 )
      {
        v7 = 1;
      }
      else
      {
        v6 = v5-- != 0;
        if ( v6 )
          continue;
      }
      break;
    }
    v5 = 1000;
    time_ms_to_ticks(5u);
    result = time_wait_ticks();
    if ( result )
      break;
    result = v7;
  }
  while ( !v7 );
  return result;
}


// ==================== sub_1696 @0x1696 size=214 ====================
BOOL sub_1696()
{
  _DWORD *v0; // r4
  int v1; // r6
  int v2; // r7
  int v3; // r5
  bool v4; // cf
  __int64 v5; // r6
  BOOL result; // r0

  v0 = (_DWORD *)MEMORY[0x1028F0];
  *(_DWORD *)(MEMORY[0x1028F0] + 56) = 0;
  v0[13] = 4096;
  sub_1268((int *)(MEMORY[0x1028F0] + 112), 0x7000u);
  v0[28] |= 2u;
  time_get_tick();
  v1 = 1000;
  v2 = 0;
  v3 = 1000;
  do
  {
    while ( (v0[30] & 0x10) != 0 )
    {
      v4 = v1-- != 0;
      if ( !v4 )
        goto LABEL_5;
    }
    v2 = 1;
LABEL_5:
    v1 = 1000;
    time_ms_to_ticks(5u);
  }
  while ( !time_wait_ticks() && !v2 );
  v0[28] &= ~0x8000u;
  time_get_tick();
  v5 = 0;
  do
  {
    do
    {
      if ( !(v0[15] << 31) )
      {
        LODWORD(v5) = 1;
        break;
      }
      v4 = v3-- != 0;
    }
    while ( v4 );
    v3 = 1000;
    time_ms_to_ticks(0x64u);
    result = time_wait_ticks();
    if ( result )
      break;
    result = v5;
  }
  while ( !v5 );
  return result;
}


// ==================== sub_176C @0x176C size=14 ====================
int sub_176C()
{
  if ( MEMORY[0x102772] )
    return 55;
  else
    return 224;
}


// ==================== sub_177A @0x177A size=88 ====================
int sub_177A()
{
  __int64 v0; // r6
  int v1; // r8
  int v2; // r5
  int v3; // r4

  v0 = 0;
  v1 = MEMORY[0x1028F0];
  time_get_tick();
  v2 = 1000;
  while ( 1 )
  {
    do
    {
      v3 = *(_DWORD *)(v1 + 120);
      if ( (v3 & 0x6E) != 0 )
      {
        HIDWORD(v0) = 1;
        break;
      }
    }
    while ( v2-- != 0 );
    v2 = 1000;
    time_ms_to_ticks(0x3E8u);
    if ( time_wait_ticks() )
      break;
    if ( v0 )
      goto LABEL_8;
  }
  LODWORD(v0) = 1;
LABEL_8:
  *(_DWORD *)(v1 + 120) = v3 & 0x6E;
  if ( (_DWORD)v0 )
    return 227;
  if ( (v3 & 8) != 0 )
    return 54;
  if ( (v3 & 2) != 0 )
    return sub_176C();
  if ( (v3 & 4) != 0 )
    return 52;
  if ( (v3 & 0x20) != 0 )
    return 1;
  if ( (v3 & 0x40) != 0 )
    return 1;
  return 56;
}


// ==================== sub_1804 @0x1804 size=14 ====================
int sub_1804()
{
  if ( MEMORY[0x102772] )
    return 51;
  else
    return 224;
}


// ==================== sub_1812 @0x1812 size=602 ====================
int __fastcall sub_1812(unsigned int a1, int a2, int a3, int *a4)
{
  unsigned int v4; // r5
  int v5; // r10
  int v7; // r6
  int *v8; // r4
  BOOL v9; // r8
  unsigned int v11; // r7
  int v12; // r0
  int v13; // r8
  unsigned int v14; // r7
  int v15; // r0
  int v16; // r0
  int v17; // [sp+0h] [bp-10h] BYREF
  int v18; // [sp+4h] [bp-Ch] BYREF
  int v19; // [sp+8h] [bp-8h]
  int *v20; // [sp+Ch] [bp-4h]

  v17 = a1;
  v18 = a2;
  v19 = a3;
  v20 = a4;
  v4 = a1;
  v5 = a2;
  v7 = a2;
  v8 = (int *)MEMORY[0x1028F0];
  v9 = 0;
  if ( a3 && a1 << 23 )
    return 49;
  if ( a2 << 30 )
    return 48;
  if ( a3 )
  {
    if ( MEMORY[0x102784] )
      v7 = 1062784;
    else
      v7 = (int)&v18;
  }
  v19 = time_get_tick();
  if ( !MEMORY[0x102784] )
  {
    v14 = (v4 + 511) >> 9 << 9;
    while ( v14 )
    {
      do
      {
        if ( (unsigned __int8)v8[5] )
          break;
        if ( (v8[30] & 5) != 0 )
          break;
        time_ms_to_ticks(0x3E8u);
        v9 = time_wait_ticks();
      }
      while ( !v9 );
      if ( v9 )
        return 53;
      v15 = v8[30];
      if ( v15 << 31 )
        return sub_1804();
      if ( (v15 & 4) != 0 )
        return 52;
      if ( v4 >= 0x80 && (unsigned __int8)v8[5] == 128 )
      {
        v16 = 32;
        if ( a3 )
        {
          do
          {
            *(_DWORD *)v7 = v8[7];
            --v16;
          }
          while ( v16 );
        }
        else
        {
          do
          {
            *(_DWORD *)v7 = v8[7];
            v7 += 4;
            --v16;
          }
          while ( v16 );
        }
        v14 -= 128;
        v4 -= 128;
      }
      else if ( v4 && v4 < 0x80 && (unsigned __int8)v8[5] >= v4 )
      {
        while ( v4 )
        {
          if ( v4 <= 3 )
          {
            v17 = v8[7];
            mem_copy_bytes(v7, &v17, v4);
            v4 = 0;
          }
          else
          {
            *(_DWORD *)v7 = v8[7];
            if ( !a3 )
              v7 += 4;
            v4 -= 4;
          }
          v14 -= 4;
        }
      }
      else if ( !v4 )
      {
        while ( v14 && (unsigned __int8)v8[5] )
        {
          v18 = v8[7];
          v14 -= 4;
        }
      }
    }
    do
    {
      if ( (unsigned __int8)v8[5] )
        break;
      if ( (v8[30] & 5) != 0 )
        break;
      time_ms_to_ticks(0x3E8u);
      v9 = time_wait_ticks();
    }
    while ( !v9 );
    if ( v9 )
      return 53;
    v13 = v8[30];
LABEL_78:
    if ( !(v13 << 31) )
    {
      if ( (v13 & 4) != 0 )
        return 52;
      else
        return 0;
    }
    return sub_1804();
  }
  if ( !a3 )
    sub_3CC(v5, v4);
  v20 = v8 + 38;
LABEL_14:
  if ( a3 )
    v11 = 512;
  else
    v11 = v4 >> 9 << 9;
  if ( !v11 )
  {
    v11 = (v4 + 3) & 0xFFFFFFFC;
    sub_3CC(1062784, v4);
    v7 = 1062784;
  }
  v8[36] = v7;
  v12 = 512;
  if ( v11 >= 0x200 )
    v12 = v11;
  v8[42] = v12;
  sub_1268(v20, 1u);
  while ( 1 )
  {
    if ( (v8[3] & 0x2000) == 0 || v8[30] << 31 )
    {
      v13 = v8[30] & 5;
      if ( v13 )
      {
        sub_1268(v20, 2u);
        goto LABEL_78;
      }
      time_ms_to_ticks(0x3E8u);
      v9 = time_wait_ticks();
      goto LABEL_33;
    }
    sub_1268(v8 + 3, 0x2000u);
    sub_1268(v20, 2u);
    if ( v11 >= v4 )
      break;
    v4 -= v11;
    if ( !a3 )
      goto LABEL_34;
    sub_1268(v20, 1u);
LABEL_33:
    if ( v9 )
    {
LABEL_34:
      if ( v9 )
      {
        sub_1268(v20, 2u);
        return 53;
      }
      if ( !a3 )
      {
        v7 = 1062784;
        v5 += v11;
      }
      goto LABEL_14;
    }
  }
  if ( v11 < 0x200 )
    mem_copy_bytes(v5, 1062784, v4);
  return 0;
}


// ==================== sub_1A6C @0x1A6C size=174 ====================
int sub_1A6C()
{
  int v0; // r4
  int v1; // r6
  int result; // r0

  v0 = MEMORY[0x1028F0];
  v1 = MEMORY[0x1028FD];
  sub_38DC(MEMORY[0x1028FD], 1);
  sub_38DC(v1, 2);
  sub_38DC(v1, 3);
  sub_3936(v1, 1, MEMORY[0x102771]);
  sub_3936(v1, 2, MEMORY[0x102771]);
  sub_3936(v1, 3, MEMORY[0x102771]);
  sub_1268((int *)(v0 + 4), 8u);
  sub_1268((int *)(v0 + 240), 0x1F00u);
  sub_1268((int *)(v0 + 4), 2u);
  sub_1268((int *)(v0 + 4), 4u);
  result = MEMORY[0x102772];
  if ( MEMORY[0x102772] )
  {
    if ( MEMORY[0x102772] << 31 )
    {
      MEMORY[0x102770] = 1;
    }
    else
    {
      MEMORY[0x102770] = 0;
      MEMORY[0x102780] += MEMORY[0x102774];
    }
    ++MEMORY[0x102772];
    result = MEMORY[0x102780];
    if ( MEMORY[0x102780] > 0x1Fu )
    {
      MEMORY[0x102780] = 0;
      MEMORY[0x102770] = 0;
      result = MEMORY[0x102771];
      if ( MEMORY[0x102771] == 7 )
      {
        MEMORY[0x102772] = 0;
        MEMORY[0x102771] = 0;
      }
      else
      {
        MEMORY[0x102772] = 1;
        result = MEMORY[0x102771] + 1;
        ++MEMORY[0x102771];
      }
    }
  }
  return result;
}


// ==================== sub_1B1A @0x1B1A size=114 ====================
int sub_1B1A()
{
  int v0; // r4
  int v1; // r5
  int result; // r0

  v0 = MEMORY[0x1028F0];
  v1 = MEMORY[0x1028FD];
  sub_38DC(MEMORY[0x1028FD], 1);
  sub_38DC(v1, 2);
  sub_38DC(v1, 3);
  sub_1268((int *)(v0 + 4), 8u);
  sub_1268((int *)(v0 + 4), 2u);
  sub_1268((int *)(v0 + 4), 4u);
  sub_1268((int *)(v0 + 176), 8u);
  result = MEMORY[0x102772];
  if ( MEMORY[0x102772] )
  {
    if ( MEMORY[0x102770] == 1 )
    {
      MEMORY[0x102772] = 0;
      return 0;
    }
    else
    {
      result = 1;
      MEMORY[0x102770] = 1;
    }
  }
  return result;
}


// ==================== sub_1B8C @0x1B8C size=4 ====================
unsigned int sub_1B8C()
{
  return sub_150E(1u);
}


// ==================== nullsub_10 @0x1B90 size=2 ====================
void nullsub_10()
{
  ;
}


// ==================== sub_1B92 @0x1B92 size=16 ====================
int __fastcall sub_1B92(int a1)
{
  if ( a1 == 1 )
    return sub_39F0(0);
  else
    return nullsub_12(0);
}


// ==================== nullsub_11 @0x1BA2 size=2 ====================
void nullsub_11()
{
  ;
}


// ==================== sub_1BA4 @0x1BA4 size=164 ====================
int __fastcall sub_1BA4(int a1, int a2, unsigned int a3, _WORD *a4)
{
  int v8; // r6
  unsigned int v10; // r5

  v8 = 0;
  if ( a1 << 20 )
  {
    v8 = 19466;
    *a4 = 21;
  }
  else if ( a3 )
  {
    if ( sub_10EDC() )
    {
      v8 = MEMORY[0x102918](a1, a2, a3, a4);
    }
    else if ( a3 << 20 )
    {
      v10 = a3 >> 12;
      if ( (!(a3 >> 12) || (v8 = MEMORY[0x10291C](a1, a2, v10 << 12, a4)) == 0) && (a3 & 0xFFF) != 0 )
      {
        v8 = MEMORY[0x10291C](a1, 1065160, 4096, a4);
        mem_copy_bytes(a2 + (v10 << 12), 1065160, a3);
      }
    }
    else
    {
      v8 = MEMORY[0x10291C](a1, a2, a3, a4);
    }
  }
  else
  {
    *a4 = 0;
  }
  MEMORY[0x10287C] = (unsigned __int16)*a4;
  return v8;
}


// ==================== sub_1C48 @0x1C48 size=70 ====================
int sub_1C48()
{
  int v0; // r5
  int v1; // r4
  int v2; // r0
  int v3; // r0

  v0 = 0;
  v1 = 0;
  if ( sub_1EC8() )
  {
    v2 = trace_begin(0x2Bu, 0);
    v1 = sub_2E66(v2);
    v3 = trace_begin(0x2Bu, 1);
    if ( v1 )
    {
      sub_2F86(v3);
      v0 = 19467;
    }
  }
  else
  {
    v0 = 4141;
  }
  MEMORY[0x10287C] = v1;
  trace_end(0x2Bu, v1, 0, 0);
  return v0;
}


// ==================== sub_1C8E @0x1C8E size=10 ====================
int __fastcall sub_1C8E(int a1)
{
  sub_2F86(a1);
  return 0;
}


// ==================== sub_1C98 @0x1C98 size=260 ====================
int __fastcall sub_1C98(_DWORD *a1, void (__fastcall *a2)(int, _DWORD, _DWORD *, int))
{
  _DWORD *v3; // r8
  _DWORD *v4; // r9
  unsigned int v5; // r6
  unsigned int v6; // r4
  int v7; // r7
  unsigned int v8; // r0
  unsigned int v9; // r7
  _DWORD *v11; // [sp+0h] [bp-8h]
  int v12; // [sp+4h] [bp-4h] BYREF

  v12 = 0;
  v3 = a1 + 1;
  v4 = a1 + 129;
  v11 = a1 + 385;
  v5 = MEMORY[0x1028A8] << 11;
  *a1 = MEMORY[0x1028A8] << 11;
  v6 = sub_1BA4(v5 >> 12 << 12, 1065160, 0x1000u, &v12);
  if ( v6 >= 0xFF )
    return 19456;
  v7 = v5 & 0xFFF;
  mem_copy_bytes(v3, v7 + 1065160, 20);
  if ( a2 )
    a2(0, (unsigned __int16)v12, v3, 20);
  if ( sub_116D8(v3, "UFS_BOOT") && sub_116D8(v3, "COMBO_BOOT") )
    return 19457;
  v8 = v3[4];
  if ( v8 < 0x1000 || v8 << 20 )
    return 19458;
  if ( (unsigned int)(v7 + 512) >= 0x1000 )
    return 19459;
  mem_copy_bytes(v4, v7 + 1065672, 180);
  if ( a2 )
    a2(1, (unsigned __int16)v12, v4, 180);
  if ( sub_116D8(v4, "BRLYT") )
    return 19460;
  v9 = v7 + 1536;
  if ( v9 >= 0x1000 )
    return 19461;
  if ( v4[3] > v5 + 1536 )
  {
    mem_copy_bytes(v11, v9 + 1065160, 512);
    if ( a2 )
      a2(3, (unsigned __int16)v12, v11, 512);
  }
  return v6;
}


// ==================== sub_1D9C @0x1D9C size=80 ====================
unsigned int __fastcall sub_1D9C(int a1, _DWORD *a2, int a3)
{
  int v4; // r0
  unsigned int result; // r0
  int v6; // r1
  int v7; // [sp+0h] [bp-8h] BYREF
  int v8; // [sp+4h] [bp-4h] BYREF

  v7 = a3;
  v8 = 0;
  v4 = *(_DWORD *)(a2[2] + 8);
  if ( v4 << 20 )
    return 19458;
  if ( (unsigned int)sub_1BA4(v4, 1065160, 0x1000u, &v8) >= 0xFF )
    return 19462;
  result = auth_find_block_by_type(1065160, 0, &v7);
  if ( result < 0xFF )
  {
    result = auth_check_block_header(v7);
    if ( result < 0xFF )
    {
      v6 = v7;
      *a2 = *(_DWORD *)(v7 + 28);
      a2[1] = *(_DWORD *)(v6 + 32);
    }
  }
  return result;
}


// ==================== sub_1DEC @0x1DEC size=170 ====================
int __fastcall sub_1DEC(int a1, _DWORD *a2, void (__fastcall *a3)(_DWORD, _DWORD, _DWORD, _DWORD))
{
  unsigned int v4; // r5
  int v5; // r8
  int v6; // r7
  int v7; // r4
  int v8; // r10
  unsigned int v9; // r9
  unsigned int v10; // r4
  unsigned int v11; // r6
  unsigned int v12; // r4
  int v14; // [sp+4h] [bp-10h] BYREF
  int v15; // [sp+8h] [bp-Ch]
  _DWORD *v16; // [sp+Ch] [bp-8h]
  void (__fastcall *v17)(_DWORD, _DWORD, _DWORD, _DWORD); // [sp+10h] [bp-4h]

  v15 = a1;
  v16 = a2;
  v17 = a3;
  v4 = 0;
  v14 = 0;
  v5 = 0;
  v6 = 0;
  v7 = *(_DWORD *)(a2[2] + 8);
  v8 = *a2;
  v9 = a2[1];
  if ( v9 <= 0x1000 )
  {
    mem_copy_bytes(v8, 1065160, v9);
    v10 = 0;
  }
  else
  {
    mem_copy_bytes(v8, 1065160, 4096);
    v5 = v7 + 4096;
    v6 = v8 + 4096;
    v10 = v9 - 4096;
  }
  if ( v10 )
  {
    v11 = v10 >> 12;
    v12 = v10 & 0xFFF;
    if ( v11 )
    {
      v4 = sub_1BA4(v5, v6, v11 << 12, &v14);
      if ( v4 >= 0xFF )
        return 19463;
      v5 += v11 << 12;
      v6 += v11 << 12;
    }
    if ( v12 )
    {
      MEMORY[0x102900] = 0;
      v4 = sub_1BA4(v5, v6, v12, &v14);
    }
  }
  if ( a3 )
    a3(v15, (unsigned __int16)v14, v8, v9);
  if ( v4 >= 0xFF )
    return 19463;
  return v4;
}


// ==================== sub_1EC8 @0x1EC8 size=32 ====================
BOOL sub_1EC8()
{
  return sub_10E86() != 1 && (MEMORY[0x100056F0] & 0x60000) == 0;
}


// ==================== sub_1EEC @0x1EEC size=54 ====================
int __fastcall sub_1EEC(int result)
{
  unsigned int v1; // r2

  if ( MEMORY[0x102914] != result )
  {
    if ( result == 1 )
    {
      v1 = MEMORY[0x112700D0] | 0x10000000;
      MEMORY[0x102912] &= ~0x400u;
    }
    else
    {
      v1 = MEMORY[0x112700D0] & 0xEFFFFFFF;
      MEMORY[0x102912] |= 0x400u;
    }
    MEMORY[0x112700D0] = v1;
    MEMORY[0x102914] = result;
  }
  return result;
}


// ==================== sub_1F22 @0x1F22 size=12 ====================
int sub_1F22()
{
  return MEMORY[0x102910] | (MEMORY[0x102912] << 16);
}


// ==================== sub_1F2E @0x1F2E size=14 ====================
int sub_1F2E()
{
  return MEMORY[0x102904] | (MEMORY[0x102908] << 8);
}


// ==================== sub_1F3C @0x1F3C size=240 ====================
int __fastcall sub_1F3C(int a1, unsigned int a2, int a3, unsigned int a4)
{
  int v7; // r4
  int v9; // r1
  int v10; // r2
  int v11; // r0

  v7 = 0;
  sub_1EEC(1);
  if ( a2 % 8 )
  {
    MEMORY[0x102910] |= 0x4000u;
    return 5;
  }
  time_ms_to_ticks(a4);
  time_get_tick();
  if ( !(a2 / 8) )
    return 0;
LABEL_17:
  if ( v7 >= a2 )
    return 0;
  if ( a1 )
  {
    v9 = *(_DWORD *)(a1 + ((v7 + ((unsigned int)(v7 >> 31) >> 30)) & 0xFFFFFFFC));
    v10 = *(_DWORD *)(a1 + ((v7 + 4 + ((unsigned int)((v7 + 4) >> 31) >> 30)) & 0xFFFFFFFC));
    v11 = 805371648;
    if ( a2 - 8 <= v7 && a3 )
      v11 = 805437184;
    MEMORY[0x112700D0] = v11;
    MEMORY[0x112700D4] = v9;
    MEMORY[0x112700D8] = v10;
    do
    {
      if ( (MEMORY[0x112700E4] & 0x380000) == 0 )
      {
        v7 += 8;
        goto LABEL_17;
      }
      if ( (MEMORY[0x112700E4] & 0x300000) != 0 && (MEMORY[0x112700E4] & 0x80000) == 0 )
      {
        MEMORY[0x102910] |= 0x2000u;
        return 6;
      }
    }
    while ( !time_wait_ticks() );
    MEMORY[0x102910] |= 0x1000u;
    return 7;
  }
  else
  {
    MEMORY[0x102910] |= 0x8000u;
    return 6;
  }
}


// ==================== sub_202C @0x202C size=238 ====================
int __fastcall sub_202C(int a1, unsigned int a2, unsigned int *a3, unsigned int a4, int a5, unsigned int a6)
{
  unsigned int v10; // r4
  int v11; // r0
  int v13; // lr

  v10 = 0;
  *a3 = 0;
  sub_1EEC(1);
  time_ms_to_ticks(a4);
  time_get_tick();
  while ( 1 )
  {
    v11 = MEMORY[0x112700E4];
    if ( (MEMORY[0x112700E4] & 0x40000) != 0 )
      break;
    if ( time_wait_ticks() )
    {
      MEMORY[0x102910] |= 0x1000u;
      return 7;
    }
  }
  while ( (v11 & 0x40000) != 0 && v10 < a2 )
  {
    v13 = MEMORY[0x112700E0];
    if ( BYTE1(v11) << 31 )
    {
      if ( a5 == 1 && MEMORY[0x102900] >= a6 )
      {
        v10 += 4;
        MEMORY[0x102900] += 4;
      }
      else
      {
        *(_DWORD *)(a1 + (v10 & 0xFFFFFFFC)) = MEMORY[0x112700DC];
        v10 += 4;
        if ( a5 == 1 )
          MEMORY[0x102900] += 4;
      }
    }
    if ( v10 >= a2 )
      break;
    if ( BYTE1(v11) >> 4 << 31 )
    {
      if ( a5 == 1 && MEMORY[0x102900] >= a6 )
      {
        v10 += 4;
        MEMORY[0x102900] += 4;
      }
      else
      {
        *(_DWORD *)(a1 + (v10 & 0xFFFFFFFC)) = v13;
        v10 += 4;
        if ( a5 == 1 )
          MEMORY[0x102900] += 4;
      }
    }
    if ( v10 < a2 )
    {
      while ( 1 )
      {
        v11 = MEMORY[0x112700E4];
        if ( (MEMORY[0x112700E4] & 0x40000) != 0 )
          break;
        if ( time_wait_ticks() )
        {
          MEMORY[0x102910] |= 0x1000u;
          return 7;
        }
      }
    }
  }
  *a3 = v10;
  return 0;
}


// ==================== nullsub_13 @0x211A size=2 ====================
void nullsub_13()
{
  ;
}


// ==================== sub_211C @0x211C size=156 ====================
int __fastcall sub_211C(int a1, int a2, int a3, int a4, _DWORD *a5, unsigned int a6)
{
  int v6; // r1

  if ( a5 )
    *a5 = 0;
  MEMORY[0x11270094] = a3 | (a2 << 16);
  MEMORY[0x11270098] = 0;
  MEMORY[0x1127009C] = a4;
  MEMORY[0x11270090] = a1;
  time_ms_to_ticks(a6);
  time_get_tick();
  while ( (MEMORY[0x11270020] & 0x400) == 0 )
  {
    if ( time_wait_ticks() )
    {
      MEMORY[0x102910] |= 0x400u;
      return 3;
    }
  }
  MEMORY[0x11270020] = 1024;
  if ( !MEMORY[0x11270098] )
    return 0;
  nullsub_13();
  nullsub_13();
  nullsub_13();
  nullsub_13();
  nullsub_13();
  if ( a5 )
    *a5 = v6;
  MEMORY[0x102910] |= 0x800u;
  MEMORY[0x102908] = v6;
  return 4;
}


// ==================== sub_21B8 @0x21B8 size=164 ====================
int __fastcall sub_21B8(int a1, int a2, int a3, _DWORD *a4, _DWORD *a5, unsigned int a6)
{
  int v7; // r1

  if ( a5 )
    *a5 = 0;
  MEMORY[0x11270094] = a3 | (a2 << 16);
  MEMORY[0x11270098] = 0;
  MEMORY[0x1127009C] = 0;
  MEMORY[0x11270090] = a1;
  time_ms_to_ticks(a6);
  time_get_tick();
  while ( (MEMORY[0x11270020] & 0x400) == 0 )
  {
    if ( time_wait_ticks() )
    {
      MEMORY[0x102910] |= 0x400u;
      return 3;
    }
  }
  MEMORY[0x11270020] = 1024;
  if ( MEMORY[0x11270098] )
  {
    nullsub_13();
    nullsub_13();
    nullsub_13();
    nullsub_13();
    nullsub_13();
    if ( a5 )
      *a5 = v7;
    MEMORY[0x102910] |= 0x800u;
    MEMORY[0x102908] = v7;
    return 4;
  }
  else
  {
    *a4 = MEMORY[0x1127009C];
    return 0;
  }
}


// ==================== sub_225C @0x225C size=54 ====================
int sub_225C()
{
  MEMORY[0x11270034] = 0;
  time_ms_to_ticks(0x64u);
  time_get_tick();
  while ( MEMORY[0x11270034] << 31 )
  {
    if ( time_wait_ticks() )
      return 69;
  }
  time_delay_ms_v2(1u);
  return 0;
}


// ==================== sub_2292 @0x2292 size=58 ====================
int sub_2292()
{
  MEMORY[0x11270034] = 1;
  time_ms_to_ticks(0x64u);
  time_get_tick();
  do
  {
    if ( MEMORY[0x11270034] << 31 )
    {
      MEMORY[0x102912] &= ~0x200u;
      return 0;
    }
  }
  while ( !time_wait_ticks() );
  return 2;
}


// ==================== sub_22E0 @0x22E0 size=30 ====================
int sub_22E0()
{
  if ( sub_211C(22, 0, 0, 0, 0, 0x64u) )
    return 8;
  else
    return 0;
}


// ==================== sub_22FE @0x22FE size=114 ====================
int __fastcall sub_22FE(int a1, int a2, int a3, int a4)
{
  int v5; // [sp+8h] [bp-4h] BYREF

  v5 = a4;
  if ( sub_21B8(3, 5471, 0, &v5, 0, 0x3E8u) )
    return 24;
  if ( v5 && sub_211C(4, 44, 0, 0, 0, 0x3E8u) )
    return 24;
  if ( sub_211C(4, 5470, 0, 0, 0, 0x3E8u) )
    return 24;
  if ( v5 && sub_211C(4, 5470, 0, 0, 0, 0x3E8u) )
    return 25;
  return 0;
}


// ==================== sub_2370 @0x2370 size=94 ====================
int sub_2370()
{
  int result; // r0
  unsigned int v1; // [sp+8h] [bp-44h] BYREF
  _BYTE v2[32]; // [sp+Ch] [bp-40h] BYREF
  _BYTE v3[32]; // [sp+2Ch] [bp-20h] BYREF

  v1 = 0;
  mem_set_bytes(v3, 0, 32);
  mem_set_bytes(v2, 0, 32);
  if ( sub_1F3C((int)v3, 0x20u, 1, 0x3E8u) )
    return 10;
  result = sub_202C((int)v2, 0x20u, &v1, 0x3E8u, 0, 0);
  if ( result )
    return 11;
  if ( v2[0] != 32 || v2[6] )
    return 9;
  return result;
}


// ==================== sub_23CE @0x23CE size=72 ====================
int __fastcall sub_23CE(unsigned __int16 a1, int a2, unsigned __int16 a3, int a4)
{
  int v6; // r0
  int result; // r0
  int v8; // r0
  int v9; // [sp+8h] [bp-4h] BYREF

  v9 = a4;
  if ( a4 )
    v6 = 3;
  else
    v6 = 1;
  if ( sub_21B8(v6, a3, 0, &v9, 0, 0x3E8u) )
    return 26;
  if ( a2 )
    v8 = 4;
  else
    v8 = 2;
  result = sub_211C(v8, a1, 0, v9, 0, 0x3E8u);
  if ( result )
    return 27;
  return result;
}


// ==================== sub_2416 @0x2416 size=56 ====================
void sub_2416()
{
  unsigned __int64 i; // r4
  _QWORD v1[3]; // [sp+0h] [bp-18h] BYREF

  sub_11610(v1, &dword_12218[2], 24);
  for ( i = 0; i < 3; LODWORD(i) = i + 1 )
    HIDWORD(i) = sub_23CE(v1[i], 0, HIDWORD(v1[i]), 0);
  JUMPOUT(0x22CA);
}


// ==================== sub_244E @0x244E size=28 ====================
int __fastcall sub_244E(int a1)
{
  if ( a1 == 1 )
    return 1;
  if ( a1 != 2 )
  {
    if ( a1 != 4 )
    {
      if ( a1 != 5 )
        return 0;
      return 0;
    }
    return 1;
  }
  return 0;
}


// ==================== sub_246A @0x246A size=210 ====================
int __fastcall sub_246A(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v10; // r11
  int result; // r0
  int v12; // [sp+8h] [bp-4h]

  v10 = sub_244E(a1);
  v12 = sub_244E(a2);
  if ( sub_211C(2, 5481, 0, v10, 0, 0x3E8u) )
    return 28;
  if ( sub_211C(2, 5508, 0, v12, 0, 0x3E8u) )
    return 40;
  if ( sub_211C(2, 5480, 0, a3, 0, 0x3E8u) )
    return 41;
  if ( sub_211C(2, 5507, 0, a4, 0, 0x3E8u) )
    return 42;
  if ( sub_211C(2, 5472, 0, a5, 0, 0x3E8u) )
    return 43;
  if ( sub_211C(2, 5504, 0, a6, 0, 0x3E8u) )
    return 44;
  result = sub_211C(2, 5482, 0, a7, 0, 0x3E8u);
  if ( result )
    return 45;
  return result;
}


// ==================== sub_253C @0x253C size=98 ====================
int __fastcall sub_253C(int a1)
{
  if ( sub_211C(2, 5489, 0, a1, 0, 0x3E8u) )
    return 30;
  time_ms_to_ticks(0x3E8u);
  time_get_tick();
  while ( (MEMORY[0x11270020] & 0x10) == 0 )
  {
    if ( time_wait_ticks() )
      return 31;
  }
  MEMORY[0x11270020] = 16;
  if ( ((MEMORY[0x11270030] >> 8) & 7) == 1 )
    return 0;
  else
    return 32;
}


// ==================== sub_259E @0x259E size=82 ====================
int __fastcall sub_259E(int a1, int a2, int a3, int a4, int a5, int a6)
{
  int v10; // r0
  int result; // r0

  sub_2416();
  if ( v10 )
    return 29;
  result = sub_246A(a1, a2, a3, a4, a6, a6, a5);
  if ( !result )
  {
    result = sub_253C((unsigned __int8)(a1 | (16 * a2)));
    if ( result )
    {
      if ( result != 31 )
      {
        MEMORY[0x102910] |= 0x10u;
        return 0;
      }
    }
  }
  return result;
}


// ==================== sub_25F0 @0x25F0 size=150 ====================
int __fastcall sub_25F0(int a1, int a2)
{
  int v2; // r2
  int result; // r0

  if ( sub_10ED2(a1, a2) )
  {
    v2 = sub_10EC8() & 3;
    if ( v2 )
    {
      if ( v2 == 1 )
      {
        MEMORY[0x102910] |= 0x20u;
        MEMORY[0x10294C] = 10672;
      }
      else if ( v2 == 2 )
      {
        MEMORY[0x102910] |= 0x40u;
        MEMORY[0x10294C] = 5336;
      }
      else
      {
        MEMORY[0x102910] |= 0x80u;
        MEMORY[0x10294C] = 2668;
      }
    }
    else
    {
      v2 = 4;
      MEMORY[0x102910] |= 0x100u;
      MEMORY[0x10294C] = 1334;
    }
    return sub_259E(2, 2, v2, v2, 1, 1);
  }
  else
  {
    MEMORY[0x102910] |= 0x60u;
    result = sub_259E(1, 1, 1, 1, 2, 1);
    MEMORY[0x10294C] = 1000;
  }
  return result;
}


// ==================== sub_2686 @0x2686 size=176 ====================
int sub_2686()
{
  int result; // r0
  _BYTE v1[256]; // [sp+8h] [bp-144h] BYREF
  _BYTE v2[32]; // [sp+108h] [bp-44h] BYREF
  _BYTE v3[32]; // [sp+128h] [bp-24h] BYREF
  unsigned int v4; // [sp+148h] [bp-4h] BYREF

  v4 = 0;
  mem_set_bytes(v3, 0, 32);
  mem_set_bytes(v2, 0, 32);
  mem_set_bytes(v1, 0, 256);
  v3[0] = 22;
  v3[3] = 0;
  v3[5] = 1;
  v3[12] = 1;
  v3[13] = 0;
  v3[14] = 0;
  v3[18] = 0;
  v3[19] = 64;
  if ( sub_1F3C((int)v3, 0x20u, 1, 0x3E8u) )
    return 13;
  if ( sub_202C((int)v2, 0x20u, &v4, 0x3E8u, 0, 0) )
    return 14;
  if ( v2[0] != 54 || v2[6] )
    return 12;
  result = sub_202C((int)v1, v2[19] | (v2[18] << 8), &v4, 0x3E8u, 0, 0);
  if ( result )
    return 14;
  return result;
}


// ==================== sub_2736 @0x2736 size=176 ====================
void sub_2736()
{
  _BYTE v0[256]; // [sp+Ch] [bp-144h] BYREF
  _BYTE v1[10]; // [sp+10Ch] [bp-44h] BYREF
  unsigned __int8 v2; // [sp+116h] [bp-3Ah]
  unsigned __int8 v3; // [sp+117h] [bp-39h]
  _BYTE v4[32]; // [sp+12Ch] [bp-24h] BYREF
  unsigned int v5; // [sp+14Ch] [bp-4h] BYREF

  v5 = 0;
  mem_set_bytes(v4, 0, 32);
  v4[0] = 1;
  v4[2] = -80;
  time_ms_to_ticks(0x3E8u);
  time_get_tick();
  do
  {
    mem_set_bytes(v1, 0, 32);
    mem_set_bytes(v0, 0, 256);
  }
  while ( !sub_1F3C((int)v4, 0x20u, 1, 0x3E8u)
       && !sub_202C((int)v1, 0x20u, &v5, 0x3E8u, 0, 0)
       && (!(v3 | (v2 << 8)) || !sub_202C((int)v0, v3 | (v2 << 8), &v5, 0x3E8u, 0, 0))
       && v1[7]
       && !time_wait_ticks() );
  JUMPOUT(0x2198);
}


// ==================== sub_27E6 @0x27E6 size=756 ====================
int __fastcall sub_27E6(unsigned int a1, unsigned int a2, unsigned int a3, unsigned __int16 *a4)
{
  int v6; // r5
  unsigned __int16 v7; // r4
  unsigned int v8; // r6
  unsigned int v9; // r0
  unsigned int v10; // r1
  int v11; // r7
  int v12; // r0
  int v13; // r0
  unsigned int v14; // r8
  int v15; // r0
  int v16; // r0
  int v17; // r0
  _BYTE v19[7]; // [sp+Ch] [bp-58h] BYREF
  unsigned __int8 v20; // [sp+13h] [bp-51h]
  unsigned __int8 v21; // [sp+16h] [bp-4Eh]
  unsigned __int8 v22; // [sp+17h] [bp-4Dh]
  unsigned __int16 v23; // [sp+1Ah] [bp-4Ah]
  unsigned int v24; // [sp+1Ch] [bp-48h]
  _BYTE v25[32]; // [sp+2Ch] [bp-38h] BYREF
  unsigned int v26; // [sp+4Ch] [bp-18h]
  unsigned int v27[4]; // [sp+50h] [bp-14h] BYREF
  unsigned __int16 *v28; // [sp+60h] [bp-4h]

  v27[1] = a1;
  v27[2] = a2;
  v27[3] = a3;
  v28 = a4;
  v6 = 0;
  v7 = 0;
  v27[0] = 0;
  v8 = 0;
  v26 = a2;
  sub_1153C(v25, dword_2824, 32);
  sub_1168A(v19, 32);
  v9 = a1 >> 12;
  v10 = a3 >> 12;
  if ( a3 << 20 )
    LOWORD(v10) = v10 + 1;
  v11 = (unsigned __int16)v10;
  v25[12] = (unsigned __int16)v10 >> 12;
  v25[13] = (unsigned __int16)v10 >> 4;
  v25[14] = 16 * v10;
  v25[15] = 0;
  v25[18] = HIBYTE(v9);
  v25[19] = BYTE2(v9);
  v25[20] = BYTE1(v9);
  v25[21] = v9;
  v25[23] = BYTE1(v10);
  v25[24] = v10;
  v12 = sub_1F3C((int)v25, 0x20u, 1, 0x3E8u);
  if ( v12 )
  {
    MEMORY[0x102912] |= 1u;
    v7 = v12;
    v6 = 19464;
  }
  else
  {
    while ( 1 )
    {
      v15 = sub_202C((int)v19, 0x20u, v27, 0x3E8u, 0, 0);
      if ( !v27[0] || v15 || v8 >= v11 << 12 )
      {
LABEL_32:
        if ( v15 )
        {
          MEMORY[0x102912] |= 2u;
          v7 = v15;
          v6 = 19464;
        }
        else
        {
          v16 = sub_202C((int)v19, 0x20u, v27, 0x3E8u, 0, 0);
          if ( v16 )
          {
            MEMORY[0x102912] |= 4u;
            v7 = v16;
            v6 = 19464;
          }
          else if ( v19[0] == 33 )
          {
            if ( v20 )
            {
              if ( v22 | (v21 << 8) )
              {
                MEMORY[0x102912] |= 0x40u;
                v17 = sub_202C((int)v19, v22 | (v21 << 8), v27, 0x3E8u, 0, 0);
                if ( v17 )
                {
                  MEMORY[0x102912] |= 8u;
                  v7 = v17;
                  v6 = 19464;
                }
                else
                {
                  v7 = _byteswap_ushort(v23);
                  v6 = 19464;
                }
              }
              else
              {
                MEMORY[0x102912] |= 8u;
                v7 = v20;
                v6 = 19464;
              }
            }
          }
          else
          {
            MEMORY[0x102912] |= 8u;
            v7 = v19[0];
            v6 = 19464;
          }
        }
        goto LABEL_45;
      }
      if ( v19[0] != 34 && v19[0] != 33 )
      {
        MEMORY[0x102912] |= 0x10u;
        v7 = v19[0];
        v6 = 19464;
        goto LABEL_45;
      }
      if ( v19[0] == 33 && v20 )
        break;
      if ( v19[0] == 33 && !v20 )
      {
        MEMORY[0x102912] |= 0x80u;
        v7 = 21;
        v6 = 19464;
        goto LABEL_45;
      }
      v14 = _byteswap_ulong(v24);
      if ( v14 )
      {
        if ( a3 << 20 )
          v15 = sub_202C(v26 + v8, v14, v27, 0x3E8u, 1, a3);
        else
          v15 = sub_202C(v26 + v8, v14, v27, 0x3E8u, 0, 0);
        if ( v15 )
        {
          MEMORY[0x102912] |= 0x20u;
          v7 = v15;
          v6 = 19464;
          goto LABEL_45;
        }
        if ( v27[0] != v14 )
        {
          v7 = 22;
          v6 = 19464;
          goto LABEL_45;
        }
        v8 += v14;
        if ( v8 >= v11 << 12 )
          goto LABEL_32;
      }
    }
    if ( v22 | (v21 << 8) )
    {
      MEMORY[0x102912] |= 0x40u;
      v13 = sub_202C((int)v19, v22 | (v21 << 8), v27, 0x3E8u, 0, 0);
      if ( v13 )
      {
        MEMORY[0x102912] |= 0x10u;
        v7 = v13;
      }
      else
      {
        v7 = _byteswap_ushort(v23);
      }
      v6 = 19464;
    }
    else
    {
      MEMORY[0x102912] |= 0x10u;
      v7 = v20;
      v6 = 19464;
    }
  }
LABEL_45:
  *v28 = v7;
  return v6;
}


// ==================== sub_2ADA @0x2ADA size=12 ====================
int __fastcall sub_2ADA(int a1, int a2, int a3)
{
  if ( a3 == 2 )
    return sub_3CC(a1, a2);
  else
    return sub_3B0(a1, a2);
}


// ==================== sub_2AE6 @0x2AE6 size=10 ====================
int __fastcall sub_2AE6(int a1, int a2, int a3)
{
  if ( a3 != 1 )
    return sub_3CC(a1, a2);
  return a1;
}


// ==================== sub_2AF0 @0x2AF0 size=52 ====================
int __fastcall sub_2AF0(int **a1, _DWORD *a2, int a3)
{
  int *v3; // r3
  int v4; // r0

  v3 = *a1;
  if ( a3 == 2 )
  {
    v4 = 0x4000000;
    *a2 = 64;
  }
  else if ( a3 == 1 )
  {
    v4 = 0x2000000;
    *a2 = 32;
  }
  else
  {
    v4 = 0;
    *a2 = 0;
  }
  *v3 = v4 | 0x11000000;
  v3[2] = 15;
  return 15;
}


// ==================== sub_2B24 @0x2B24 size=110 ====================
int __fastcall sub_2B24(_DWORD *a1, int a2)
{
  unsigned int *v3; // r0
  int v4; // r5
  unsigned int v5; // r3
  int v6; // r1
  unsigned int v7; // r2

  v3 = (unsigned int *)a1[1];
  v4 = a1[6];
  v5 = a1[5] | (a2 << 16) | (v4 << 8) | 0x1000000;
  *v3 = (v5 << 24)
      | (((v4 << 8) & 0xFF00 | a1[5] & 0xFF00) << 8)
      | ((((a2 << 16) | (v4 << 8) | a1[5]) & 0xFF0000u) >> 8)
      | HIBYTE(v5);
  v3[1] = 0;
  v3[2] = 0;
  v3[3] = (*(_DWORD *)(a1[4] + 28) << 24)
        | ((*(_DWORD *)(a1[4] + 28) & 0xFF00) << 8)
        | ((*(_DWORD *)(a1[4] + 28) & 0xFF0000u) >> 8)
        | HIBYTE(*(_DWORD *)(a1[4] + 28));
  v6 = a1[4];
  v7 = *(unsigned __int16 *)(v6 + 26);
  if ( v7 >= 0x10 )
    v7 = 16;
  return sub_1152C(v3 + 4, v6 + 9, v7);
}


// ==================== sub_2B92 @0x2B92 size=36 ====================
int __fastcall sub_2B92(int a1, int a2, int a3, int a4)
{
  int v6; // [sp+0h] [bp-4h] BYREF

  v6 = a4;
  sub_2AF0((int **)a1, &v6, *(unsigned __int8 *)(*(_DWORD *)(a1 + 16) + 8));
  sub_2B24((_DWORD *)a1, v6);
  return sub_2ADA(*(_DWORD *)(a1 + 8), 52, 2);
}


// ==================== sub_2BB6 @0x2BB6 size=136 ====================
int __fastcall sub_2BB6(int *a1)
{
  int v2; // r1
  unsigned int v3; // r7
  int v4; // r0
  int v5; // r5
  unsigned int v6; // r2
  unsigned int i; // r1
  _DWORD *v8; // r6

  v2 = a1[4];
  v3 = (*(_DWORD *)(v2 + 28) + 0x3FFFF) / 0x40000u;
  *(_WORD *)(*a1 + 28) = v3;
  v4 = a1[3];
  v5 = *(_DWORD *)(a1[4] + 32);
  v6 = *(_DWORD *)(v2 + 28);
  for ( i = 0; i < v3; i = (unsigned __int16)(i + 1) )
  {
    if ( v6 <= 0x40000 )
      *(_DWORD *)(v4 + 16 * i + 12) = v6 - 1;
    else
      *(_DWORD *)(v4 + 16 * i + 12) = 0x3FFFF;
    v8 = (_DWORD *)(v4 + 16 * i);
    *v8 = v5;
    v8[1] = 0;
    v5 += 0x40000;
    v6 -= 0x40000;
  }
  sub_2ADA(a1[1], 32, 1);
  sub_2ADA(a1[3], 16 * v3, 1);
  sub_2ADA(*a1, 32, 0);
  return sub_2ADA(*(_DWORD *)(a1[4] + 32), *(_DWORD *)(a1[4] + 28), 2);
}


// ==================== sub_2C3E @0x2C3E size=174 ====================
int __fastcall sub_2C3E(int *a1, unsigned int a2)
{
  int v3; // r6
  int v4; // r5
  int v6; // r0
  int v7; // r1

  v3 = 0;
  v4 = 1 << a1[5];
  time_ms_to_ticks(a2);
  time_get_tick();
  while ( (v4 & MEMORY[0x11270058]) != 0 )
  {
    if ( time_wait_ticks() )
      return 208;
  }
  sub_2AE6(*(_DWORD *)(a1[4] + 32), *(_DWORD *)(a1[4] + 28), 2);
  sub_2AE6(a1[1], 32, 1);
  sub_2AE6(*a1, 32, 0);
  v6 = *(_DWORD *)(*a1 + 8) & 0xF;
  if ( v6 )
  {
    if ( v6 == 15 )
      return 232;
    else
      return v6 + 224;
  }
  else
  {
    sub_2AE6(a1[2], 52, 2);
    v7 = a1[2];
    if ( (unsigned __int16)(((*(_DWORD *)(v7 + 4) & 0xFF0000u) >> 8) | HIBYTE(*(_DWORD *)(v7 + 4))) >> 8 )
    {
      v3 = *(unsigned __int8 *)(v7 + 47) | (*(unsigned __int8 *)(v7 + 46) << 8);
      MEMORY[0x102912] |= 0x8000u;
    }
    return v3;
  }
}


// ==================== sub_2CEC @0x2CEC size=48 ====================
int __fastcall sub_2CEC(int *a1, int a2, int a3, int a4)
{
  int v4; // r5
  int v5; // r1

  v4 = a1[1];
  v5 = *a1;
  MEMORY[0x102940] = a1;
  MEMORY[0x102944] = v4;
  MEMORY[0x102948] = v5;
  sub_2B92(1059120, v5, a3, a4);
  sub_2BB6((int *)0x102930);
  MEMORY[0x11270058] = 1 << v4;
  return sub_2C3E((int *)0x102930, MEMORY[0x10294C]);
}


// ==================== sub_2D1C @0x2D1C size=86 ====================
unsigned int __fastcall sub_2D1C(int a1, int a2, unsigned int a3, int a4)
{
  mem_set_bytes(a1 + 9, 0, 16);
  *(_DWORD *)a1 = 176;
  *(_DWORD *)(a1 + 4) = MEMORY[0x10292C];
  *(_BYTE *)(a1 + 8) = 2;
  *(_DWORD *)(a1 + 28) = a3;
  *(_WORD *)(a1 + 26) = 10;
  *(_BYTE *)(a1 + 9) = 40;
  *(_BYTE *)(a1 + 10) = 8;
  *(_BYTE *)(a1 + 11) = HIBYTE(a2);
  *(_BYTE *)(a1 + 12) = BYTE2(a2);
  *(_BYTE *)(a1 + 13) = BYTE1(a2);
  *(_BYTE *)(a1 + 14) = a2;
  *(_BYTE *)(a1 + 15) = 0;
  *(_BYTE *)(a1 + 16) = a3 >> 20;
  *(_BYTE *)(a1 + 17) = a3 >> 12;
  *(_BYTE *)(a1 + 18) = 0;
  *(_DWORD *)(a1 + 32) = a4;
  return a3 >> 12;
}


// ==================== sub_2D72 @0x2D72 size=54 ====================
void __fastcall sub_2D72(unsigned int a1, int a2, unsigned int a3, _WORD *a4)
{
  int v8; // r1
  int v9; // r2
  int v10; // r3
  int v11[9]; // [sp+4h] [bp-24h] BYREF

  sub_1EEC(2);
  sub_2D1C((int)v11, a1 >> 12, a3, a2);
  *a4 = sub_2CEC(v11, v8, v9, v10);
  JUMPOUT(0x2D6E);
}


// ==================== sub_2DA8 @0x2DA8 size=134 ====================
int sub_2DA8()
{
  int v1; // r0

  if ( MEMORY[0x102920] )
    return 0;
  mem_set_bytes(1063296, 0, 416);
  MEMORY[0x102788] = 1063296;
  MEMORY[0x10278C] = 1063680;
  MEMORY[0x102924] = 1063296;
  MEMORY[0x102928] = 1063680;
  MEMORY[0x10292C] = 24;
  if ( !sub_10EDC() )
    MEMORY[0x102912] |= MEMORY[0x10292C];
  v1 = MEMORY[0x102928];
  *(_DWORD *)(MEMORY[0x102928] + 16) = MEMORY[0x102924];
  *(_DWORD *)(v1 + 20) = 0;
  *(_WORD *)(v1 + 26) = 16;
  *(_WORD *)(v1 + 30) = 32;
  *(_WORD *)(v1 + 24) = 16;
  MEMORY[0x102930] = v1;
  MEMORY[0x102934] = MEMORY[0x102924];
  MEMORY[0x102938] = MEMORY[0x102924] + 64;
  MEMORY[0x10293C] = MEMORY[0x102924] + 128;
  MEMORY[0x102920] = 1;
  MEMORY[0x102912] |= 0x100u;
  return 0;
}


// ==================== sub_2E2E @0x2E2E size=34 ====================
int sub_2E2E()
{
  int result; // r0

  MEMORY[0x11270024] |= 0x30805u;
  MEMORY[0x11270050] = MEMORY[0x102928] & 0xFFFFFC00;
  MEMORY[0x11270060] = 1;
  result = MEMORY[0x102912] | 0x200;
  MEMORY[0x102912] |= 0x200u;
  return result;
}


// ==================== sub_2E50 @0x2E50 size=22 ====================
int sub_2E50()
{
  sub_2E2E();
  MEMORY[0x10291C] = (int (__fastcall *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_2D72;
  MEMORY[0x102918] = (int (__fastcall *)(_DWORD, _DWORD, _DWORD, _DWORD))sub_27E6;
  return 1059072;
}


// ==================== sub_2E66 @0x2E66 size=288 ====================
int sub_2E66()
{
  int v0; // r4
  int v1; // r0
  int v2; // r0
  int v3; // r1
  int v4; // r2
  int v5; // r3
  int v6; // r0
  int v7; // r1
  int v8; // r0

  ++MEMORY[0x10290E];
  v0 = sub_2FF0();
  if ( !v0 )
  {
    while ( 1 )
    {
      v0 = sub_2DA8();
      if ( v0 )
        break;
      v0 = sub_225C();
      if ( v0 )
        break;
      v1 = MEMORY[0x10290E] < 2u ? sub_3766(MEMORY[0x102904]) : sub_36FE(MEMORY[0x10290C]);
      v2 = sub_3012(v1);
      v0 = sub_3036(v2);
      if ( v0 )
        break;
      v0 = sub_2292();
      if ( v0 )
        break;
      v0 = sub_338A();
      if ( v0 )
        break;
      v0 = sub_22E0();
      if ( !v0 )
      {
        v6 = sub_22FE(0, v3, v4, v5);
        v0 = v6;
        if ( !v6 )
        {
          v0 = sub_2370();
          if ( !v0 )
          {
            v0 = sub_25F0(0, v7);
            if ( !v0 )
            {
              v0 = sub_2686();
              if ( !v0 )
              {
                sub_2736();
                v0 = v8;
                if ( !v8 )
                  sub_2E50();
              }
            }
          }
        }
        return v0;
      }
      ++MEMORY[0x102904];
      MEMORY[0x102910] |= 0x200u;
      if ( MEMORY[0x10290E] >= 2u )
        return v0;
      if ( (!sub_10E9A() || sub_10E90() || MEMORY[0x102904] >= 2u)
        && (sub_10E9A() || !sub_10E90() || MEMORY[0x102904] >= 4u)
        && (sub_10E9A() || sub_10E90() || MEMORY[0x102904] >= 8u) )
      {
        if ( MEMORY[0x102904] <= 2u )
          return 33;
        switch ( MEMORY[0x102904] )
        {
          case 3:
            return 34;
          case 4:
            return 35;
          case 5:
            return 36;
          case 6:
            return 37;
          case 7:
            return 38;
          case 8:
            return 39;
        }
        return v0;
      }
    }
  }
  return v0;
}


// ==================== sub_2F86 @0x2F86 size=30 ====================
int sub_2F86()
{
  BOOL v0; // r0

  if ( sub_2FFA() )
  {
    MEMORY[0x11270034] = 0;
    v0 = time_delay_ms(0xAu);
    sub_36E8(v0);
  }
  return 0;
}


// ==================== sub_2FB8 @0x2FB8 size=56 ====================
int sub_2FB8()
{
  int result; // r0

  sub_10EA4(1059152);
  result = MEMORY[0x102950] << 25;
  if ( (MEMORY[0x102950] & 0x40) != 0 )
  {
    MEMORY[0x11FA1000] &= ~2u;
    MEMORY[0x11FA001C] |= 4u;
    MEMORY[0x11FA001C] &= ~4u;
    return sub_11E24(1u);
  }
  return result;
}


// ==================== sub_2FF0 @0x2FF0 size=10 ====================
int sub_2FF0()
{
  sub_2FB8();
  return 0;
}


// ==================== sub_2FFA @0x2FFA size=24 ====================
BOOL sub_2FFA()
{
  sub_10EA4(1059152);
  return (MEMORY[0x102950] & 0x80) != 0;
}


// ==================== sub_3012 @0x3012 size=36 ====================
BOOL sub_3012()
{
  MEMORY[0x10003448] &= ~8u;
  time_delay_ms(0xAu);
  MEMORY[0x10003448] |= 8u;
  return sub_11E24(0xAu);
}


// ==================== sub_3036 @0x3036 size=852 ====================
int sub_3036()
{
  unsigned int v0; // r0

  sub_10EA4(1059152);
  if ( (MEMORY[0x102950] & 0x10) != 0 )
  {
    MEMORY[0x11FA1004] = MEMORY[0x11FA1004] & 0xC0FFFFFF | (((MEMORY[0x102950] >> 8) & 0x3F) << 24);
    MEMORY[0x11FAA02C] = MEMORY[0x11FAA02C] & 0xFFFFCFFF | (MEMORY[0x102950] >> 14 << 12);
    MEMORY[0x11FA8030] = MEMORY[0x11FA8030] & 0xE0E0FFFF
                       | ((HIWORD(MEMORY[0x102950]) & 0x1F) << 16)
                       | (((MEMORY[0x102950] >> 21) & 0x1F) << 24);
    MEMORY[0x11FAB000] = MEMORY[0x11FAB000] & 0xFFC0FFFF | (MEMORY[0x102950] >> 26 << 16);
  }
  if ( MEMORY[0x102950] << 31 )
  {
    MEMORY[0x11FA0058] = MEMORY[0x11FA0058] & 0xFFFFFFF0 | (MEMORY[0x102954] >> 1) & 0xF;
    MEMORY[0x11FA2008] = MEMORY[0x11FA2008] & 0xFFFFF0FF | (((MEMORY[0x102954] >> 5) & 0xF) << 8);
    MEMORY[0x11FA2028] = MEMORY[0x11FA2028] & 0xFFF0FFFF | (((MEMORY[0x102954] >> 9) & 0xF) << 16);
    MEMORY[0x11FA202C] = MEMORY[0x11FA202C] & 0xFFFF00FE
                       | (MEMORY[0x102954] >> 13) & 1
                       | ((unsigned __int8)(MEMORY[0x102954] >> 14) << 8);
    MEMORY[0x11FA2084] = MEMORY[0x11FA2084] & 0xFFFEFFFF | (((MEMORY[0x102954] >> 22) & 1) << 16);
    MEMORY[0x11FA208C] = MEMORY[0x11FA208C] & 0xFFE0F0FF
                       | (((MEMORY[0x102954] >> 23) & 0xF) << 8)
                       | (MEMORY[0x102954] >> 27 << 16);
  }
  if ( (MEMORY[0x102950] & 2) != 0 )
  {
    v0 = MEMORY[0x102958];
    MEMORY[0x11FA20C4] = MEMORY[0x11FA20C4] & 0xFFFFE7FF | ((MEMORY[0x102958] & 3) << 11);
    MEMORY[0x11FA20C8] = MEMORY[0x11FA20C8] & 0xFFFFFFEF | (16 * ((MEMORY[0x102958] >> 2) & 1));
    MEMORY[0x11FA20D0] = MEMORY[0x11FA20D0] & 0xFFFFE5FF
                       | (((MEMORY[0x102958] >> 3) & 1) << 9)
                       | (((MEMORY[0x102958] >> 4) & 3) << 11);
    MEMORY[0x11FA8004] = MEMORY[0x11FA8004] & 0xFFFFEFEF | (16 * ((v0 >> 6) & 1)) | (((v0 >> 7) & 1) << 12);
    MEMORY[0x11FA80A4] = MEMORY[0x11FA80A4] & 0xFFFFFFF8 | (MEMORY[0x102958] >> 8) & 7;
    MEMORY[0x11FAA008] = MEMORY[0x11FAA008] & 0xFFFFBFF3 | (4 * ((v0 >> 11) & 3)) | (((v0 >> 13) & 1) << 14);
    MEMORY[0x11FAA01C] = MEMORY[0x11FAA01C] & 0xFFCFFFFF | (MEMORY[0x102958] >> 14 << 20);
    MEMORY[0x11FAA020] = MEMORY[0x11FAA020] & 0x3FFFFFFF | (MEMORY[0x10295A] << 30);
    MEMORY[0x11FAA080] = MEMORY[0x11FAA080] & 0xFE00FFFF | (((MEMORY[0x102958] >> 18) & 0x1FF) << 16);
    MEMORY[0x11FAA084] = MEMORY[0x11FAA084] & 0xFFFEFFFF | (((MEMORY[0x102958] >> 27) & 1) << 16);
    MEMORY[0x11FAA048] = MEMORY[0x11FAA048] & 0xFFFFF1FF | (((MEMORY[0x102958] >> 28) & 7) << 9);
    MEMORY[0x11FAA184] = MEMORY[0x11FAA184] & 0xFFFEFFFF | (MEMORY[0x102958] >> 31 << 16);
  }
  if ( (MEMORY[0x102950] & 8) != 0 )
    MEMORY[0x11FA0080] = MEMORY[0x11FA0080] & 0xFFFF3FFF | (MEMORY[0x102960] >> 30 << 14);
  if ( MEMORY[0x102964] << 31 )
  {
    MEMORY[0x11FA8030] = MEMORY[0x11FA8030] & 0xFF1FFFFF | (((MEMORY[0x102964] >> 1) & 7) << 21);
    MEMORY[0x11FA8030] = MEMORY[0x11FA8030] & 0x1FFFFFFF | ((unsigned __int8)(MEMORY[0x102964] >> 4) << 29);
    MEMORY[0x11FA8130] = MEMORY[0x11FA8130] & 0xFF1FFFFF | (((MEMORY[0x102964] >> 7) & 7) << 21);
    MEMORY[0x11FA100C] = MEMORY[0x11FA100C] & 0xFFFFF0FF | (((MEMORY[0x102964] >> 10) & 0xF) << 8);
    MEMORY[0x11FAA12C] = MEMORY[0x11FAA12C] & 0xFFFFCFFF | (MEMORY[0x102964] >> 14 << 12);
    MEMORY[0x11FA8130] = MEMORY[0x11FA8130] & 0xFFE0FFFF | ((HIWORD(MEMORY[0x102964]) & 0x1F) << 16);
    MEMORY[0x11FA8130] = MEMORY[0x11FA8130] & 0xE0FFFFFF | (((MEMORY[0x102964] >> 21) & 0x1F) << 24);
    MEMORY[0x11FAB100] = MEMORY[0x11FAB100] & 0xFFC0FFFF | (MEMORY[0x102964] >> 26 << 16);
  }
  if ( MEMORY[0x102968] << 31 )
  {
    MEMORY[0x11FA8130] = MEMORY[0x11FA8130] & 0x1FFFFFFF | ((unsigned __int8)(MEMORY[0x102968] >> 1) << 29);
    MEMORY[0x11FA0058] = MEMORY[0x11FA0058] & 0xFFFFFF0F | (16 * (MEMORY[0x102968] >> 4));
    MEMORY[0x11FA81A4] = MEMORY[0x11FA81A4] & 0xFFFFFFF8 | (MEMORY[0x102968] >> 8) & 7;
    MEMORY[0x11FAA108] = MEMORY[0x11FAA108] & 0xFFFFFFF3 | (4 * ((MEMORY[0x102968] >> 11) & 3));
    MEMORY[0x11FAA108] = MEMORY[0x11FAA108] & 0xFFFFBFFF | (((MEMORY[0x102968] >> 13) & 1) << 14);
    MEMORY[0x11FAA11C] = MEMORY[0x11FAA11C] & 0xFFCFFFFF | (MEMORY[0x102968] >> 14 << 20);
    MEMORY[0x11FAA120] = MEMORY[0x11FAA120] & 0x3FFFFFFF | (MEMORY[0x10296A] << 30);
    MEMORY[0x11FAA180] = MEMORY[0x11FAA180] & 0xFE00FFFF | (((MEMORY[0x102968] >> 18) & 0x1FF) << 16);
    MEMORY[0x11FA8104] = MEMORY[0x11FA8104] & 0xFFFFEFFF | (((MEMORY[0x102968] >> 27) & 1) << 12);
    MEMORY[0x11FAA148] = MEMORY[0x11FAA148] & 0xFFFFF1FF | (((MEMORY[0x102968] >> 28) & 7) << 9);
    MEMORY[0x11FA8104] = MEMORY[0x11FA8104] & 0xFFFFFFEF | (16 * (MEMORY[0x102968] >> 31));
  }
  return 0;
}


// ==================== sub_338A @0x338A size=862 ====================
int __fastcall sub_338A(int a1, int a2, int a3, unsigned int a4)
{
  unsigned int v5; // [sp+8h] [bp-4h] BYREF

  v5 = a4;
  sub_10EA4(1059152);
  if ( (MEMORY[0x102950] & 4) != 0 )
  {
    if ( sub_21B8(1, 5470, 0, &v5, 0, 0x3E8u) )
      return 23;
    if ( sub_211C(2, 5470, 0, v5 & 0xFFFFFFFE | MEMORY[0x10295C] & 1, 0, 0x3E8u) )
      return 46;
    if ( sub_21B8(1, 5471, 0, &v5, 0, 0x3E8u) )
      return 47;
    if ( sub_211C(2, 5471, 0, v5 & 0xFFFFFFFE | (MEMORY[0x10295C] >> 1) & 1, 0, 0x3E8u) )
      return 48;
    if ( sub_21B8(1, 53380, 0, &v5, 0, 0x3E8u) )
      return 49;
    if ( sub_211C(2, 53380, 0, v5 & 0xFFFFFF00 | (unsigned __int8)(MEMORY[0x10295C] >> 2), 0, 0x3E8u) )
      return 50;
    if ( sub_21B8(1, 53382, 0, &v5, 0, 0x3E8u) )
      return 51;
    if ( sub_211C(2, 53382, 0, v5 & 0xFFFFFF00 | (unsigned __int8)(MEMORY[0x10295C] >> 10), 0, 0x3E8u) )
      return 52;
    if ( sub_21B8(1, 53406, 0, &v5, 0, 0x3E8u) )
      return 53;
    if ( sub_211C(2, 53406, 0, v5 & 0xFFFFFFFE | (MEMORY[0x10295C] >> 18) & 1, 0, 0x3E8u) )
      return 54;
    if ( sub_21B8(1, 53408, 0, &v5, 0, 0x3E8u) )
      return 55;
    if ( sub_211C(2, 53408, 0, v5 & 0xFFFFFFF8 | (MEMORY[0x10295C] >> 19) & 7, 0, 0x3E8u) )
      return 56;
    if ( sub_21B8(1, 53413, 0, &v5, 0, 0x3E8u) )
      return 57;
    if ( sub_211C(2, 53413, 0, v5 & 0xFFFFFC00 | (MEMORY[0x10295C] >> 22), 0, 0x3E8u) )
      return 58;
  }
  if ( (MEMORY[0x102950] & 8) == 0 )
    return 0;
  if ( sub_21B8(1, 53413, 0, &v5, 0, 0x3E8u) )
    return 57;
  if ( sub_211C(2, 53413, 0, v5 & 0xFFFE03FF | ((MEMORY[0x102960] & 0x7F) << 10), 0, 0x3E8u) )
    return 58;
  if ( sub_21B8(1, 53414, 0, &v5, 0, 0x3E8u) )
    return 59;
  if ( sub_211C(
         2,
         53414,
         0,
         (2 * ((MEMORY[0x102960] >> 7) & 1)) | (16 * ((MEMORY[0x102960] >> 8) & 1)) | v5 & 0xFFFFFFED,
         0,
         0x3E8u) )
  {
    return 60;
  }
  if ( sub_21B8(1, 53421, 0, &v5, 0, 0x3E8u) )
    return 61;
  if ( sub_211C(2, 53421, 0, v5 & 0xFFFFFFF3 | (4 * ((MEMORY[0x102960] >> 9) & 3)), 0, 0x3E8u) )
    return 62;
  if ( sub_21B8(1, 53422, 0, &v5, 0, 0x3E8u) )
    return 63;
  if ( sub_211C(2, 53422, 0, v5 & 0xFFFFFFFC | (MEMORY[0x102960] >> 11) & 3, 0, 0x3E8u) )
    return 64;
  if ( sub_21B8(1, 53423, 0, &v5, 0, 0x3E8u) )
    return 65;
  if ( sub_211C(2, 53423, 0, v5 & 0xFFFFFF00 | (unsigned __int8)(MEMORY[0x102960] >> 13), 0, 0x3E8u) )
    return 66;
  if ( sub_21B8(1, 53429, 0, &v5, 0, 0x3E8u) )
    return 67;
  if ( sub_211C(2, 53429, 0, (v5 >> 9 << 9) | (MEMORY[0x102960] >> 21) & 0x1FF, 0, 0x3E8u) )
    return 68;
  else
    return 0;
}


// ==================== sub_36E8 @0x36E8 size=22 ====================
int sub_36E8()
{
  MEMORY[0x11FA8010] &= 0xFFFF3FFF;
  MEMORY[0x11FAB000] &= ~0x8000000u;
  return 301641728;
}


// ==================== sub_36FE @0x36FE size=104 ====================
int __fastcall sub_36FE(int a1)
{
  int result; // r0

  result = sub_10E9A();
  if ( !result )
  {
    result = 301641728;
    if ( !a1 )
    {
      MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
      MEMORY[0x11FAB000] &= ~0x8000000u;
    }
    if ( a1 == 1 )
    {
      MEMORY[0x11FA8010] |= 0xC000u;
      MEMORY[0x11FAB000] &= ~0x8000000u;
    }
    if ( a1 == 2 )
    {
      MEMORY[0x11FA8010] |= 0xC000u;
      MEMORY[0x11FAB000] |= 0x8000000u;
    }
    if ( a1 == 3 )
    {
      MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
      MEMORY[0x11FAB000] |= 0x8000000u;
    }
  }
  return result;
}


// ==================== sub_3766 @0x3766 size=320 ====================
int __fastcall sub_3766(unsigned int a1)
{
  int result; // r0
  bool v3; // zf

  result = sub_10E9A();
  if ( !result )
  {
    v3 = sub_10E90() == 0;
    result = 1059072;
    if ( v3 )
    {
      if ( a1 <= 1 )
      {
        MEMORY[0x10290C] = 0;
        MEMORY[0x102910] |= 1u;
        MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
        MEMORY[0x11FAB000] &= ~0x8000000u;
      }
      if ( a1 == 2 || a1 == 3 )
      {
        MEMORY[0x10290C] = 1;
        MEMORY[0x102910] |= 2u;
        MEMORY[0x11FA8010] |= 0xC000u;
        MEMORY[0x11FAB000] &= ~0x8000000u;
      }
      if ( a1 == 4 || a1 == 5 )
      {
        MEMORY[0x10290C] = 2;
        MEMORY[0x102910] |= 4u;
        MEMORY[0x11FA8010] |= 0xC000u;
        MEMORY[0x11FAB000] |= 0x8000000u;
      }
      if ( a1 == 6 || a1 == 7 )
      {
        MEMORY[0x10290C] = 3;
        MEMORY[0x102910] |= 8u;
        MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
        result = MEMORY[0x11FAB000] | 0x8000000;
        MEMORY[0x11FAB000] |= 0x8000000u;
      }
    }
    else
    {
      if ( !a1 )
      {
        MEMORY[0x10290C] = 0;
        MEMORY[0x102910] |= 1u;
        MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
        MEMORY[0x11FAB000] &= ~0x8000000u;
      }
      if ( a1 == 1 )
      {
        MEMORY[0x10290C] = 1;
        MEMORY[0x102910] |= 2u;
        MEMORY[0x11FA8010] |= 0xC000u;
        MEMORY[0x11FAB000] &= ~0x8000000u;
      }
      if ( a1 == 2 )
      {
        MEMORY[0x10290C] = 2;
        MEMORY[0x102910] |= 4u;
        MEMORY[0x11FA8010] |= 0xC000u;
        MEMORY[0x11FAB000] |= 0x8000000u;
      }
      if ( a1 == 3 )
      {
        MEMORY[0x10290C] = 3;
        MEMORY[0x102910] |= 8u;
        MEMORY[0x11FA8010] = MEMORY[0x11FA8010] & 0xFFFF3FFF | 0x4000;
        result = MEMORY[0x11FAB000] | 0x8000000;
        MEMORY[0x11FAB000] |= 0x8000000u;
      }
    }
  }
  return result;
}


// ==================== sub_38B4 @0x38B4 size=12 ====================
int sub_38B4()
{
  MEMORY[0x10005710] |= 1u;
  return 268457744;
}


// ==================== sub_38C0 @0x38C0 size=10 ====================
_WORD *__fastcall sub_38C0(_WORD *result, __int16 a2, __int16 a3)
{
  *result = *result & ~a2 | a3;
  return result;
}


// ==================== sub_38CA @0x38CA size=10 ====================
int *__fastcall sub_38CA(int *result, int a2, int a3)
{
  *result = *result & ~a2 | a3;
  return result;
}


// ==================== sub_38D4 @0x38D4 size=8 ====================
int __fastcall sub_38D4(int result)
{
  if ( result )
    return 255;
  return result;
}


// ==================== sub_38DC @0x38DC size=46 ====================
int *__fastcall sub_38DC(int a1)
{
  int *result; // r0
  int v2; // r1
  int v3; // r2

  result = (int *)sub_38D4(a1);
  if ( result != (int *)((char *)&loc_FC + 3) && (v2 == 1 || v2 == 2 || v2 == 3) && !v3 )
    return sub_38CA((int *)0x11F300E0, 4095, 4095);
  return result;
}


// ==================== sub_390A @0x390A size=44 ====================
int *__fastcall sub_390A(int a1)
{
  int *result; // r0
  int v2; // r1
  int v3; // r2

  result = (int *)sub_38D4(a1);
  if ( result != (int *)((char *)&loc_FC + 3) && (v2 == 1 || v2 == 2 || v2 == 3) && !v3 )
    return sub_38CA((int *)0x11F300E0, 4095, 0);
  return result;
}


// ==================== sub_3936 @0x3936 size=186 ====================
int __fastcall sub_3936(int a1)
{
  int result; // r0
  int v2; // r1
  int v3; // r2
  int v4; // r3
  int v5; // r4
  int v6; // r5
  int v7; // r2

  result = sub_38D4(a1);
  if ( !v4 && result != 255 )
  {
    v5 = v3 & 7;
    result = 301137920;
    if ( v2 == 1 )
    {
      sub_38CA((int *)0x11F30000, 7, v3 & 7);
      return (int)sub_38CA((int *)0x11F30010, 7, v5);
    }
    else
    {
      v6 = (8 * v3) & 0x3F;
      if ( v2 == 2 )
      {
        v7 = (8 * v3) & 0x3F;
      }
      else
      {
        if ( v2 != 3 )
          return result;
        sub_38CA((int *)0x11F30000, 448, v5 << 6);
        sub_38CA((int *)0x11F30000, 3584, v5 << 9);
        sub_38CA((int *)0x11F30000, 28672, v5 << 12);
        sub_38CA((int *)0x11F30000, 229376, v5 << 15);
        sub_38CA((int *)0x11F30000, 1835008, v5 << 18);
        sub_38CA((int *)0x11F30000, 14680064, v5 << 21);
        sub_38CA((int *)0x11F30000, 117440512, v5 << 24);
        sub_38CA((int *)0x11F30000, 939524096, v5 << 27);
        v7 = v6;
        result = 301137936;
      }
      return (int)sub_38CA((int *)result, 56, v7);
    }
  }
  return result;
}


// ==================== sub_39F0 @0x39F0 size=236 ====================
int *__fastcall sub_39F0(int *result)
{
  if ( result )
  {
    if ( result == (int *)((char *)sub_4 + 3) )
    {
      sub_38CA((int *)0x10005300, -256, 1431655680);
      sub_38CA((int *)0x11D400B4, 401408, 401408);
      return sub_38CA((int *)0x11D40098, 401408, 401408);
    }
  }
  else
  {
    sub_38CA((int *)0x11F30040, 262080, 262080);
    sub_38CA((int *)0x11F300E0, 4095, 4095);
    sub_38CA((int *)0x11F30060, 4095, 1025);
    sub_38CA((int *)0x11F30080, 4095, 3070);
    sub_38CA((int *)0x11F30090, 4095, 1025);
    sub_38CA((int *)0x11F300F0, -1, 0);
    sub_38CA((int *)0x11F30100, 0xFFFF, 0);
    sub_38CA((int *)0x11F300A0, 0x3FFFFFFF, 0);
    sub_38CA((int *)0x11F300B0, 0x3FFFFFFF, 0);
    sub_38CA((int *)0x11F300C0, 4095, 0);
    sub_38CA((int *)0x10005380, -16, 286331152);
    sub_38CA((int *)0x10005390, 0xFFFFF, 69905);
    sub_38CA((int *)0x11F30000, 0x3FFFFFFF, 153391689);
    return sub_38CA((int *)0x11F30010, 63, 9);
  }
  return result;
}


// ==================== nullsub_12 @0x3ADC size=2 ====================
void nullsub_12()
{
  ;
}


// ==================== sub_3B04 @0x3B04 size=56 ====================
int __fastcall sub_3B04(int a1)
{
  int v2; // r4
  int *v3; // r0

  v2 = 0;
  if ( !sub_3D04() )
    return 4100;
  v3 = sub_39F0((int *)((char *)sub_4 + 3));
  if ( sub_10EF0(v3) )
    sub_3D68();
  if ( a1 )
    MEMORY[0x113000CC] = 16;
  else
    MEMORY[0x113000CC] = 0;
  return v2;
}


// ==================== sub_3B3C @0x3B3C size=14 ====================
int sub_3B3C()
{
  nullsub_12();
  return 0;
}


// ==================== nullsub_14 @0x3B4A size=2 ====================
void nullsub_14()
{
  ;
}


// ==================== sub_3B4C @0x3B4C size=302 ====================
int __fastcall sub_3B4C(_DWORD *a1, void (__fastcall *a2)(int, _DWORD, _DWORD *, int))
{
  int v4; // r5
  _DWORD *v5; // r6
  _DWORD *v6; // r8
  unsigned int v7; // r1
  int v8; // r0
  unsigned int i; // r2
  int v10; // r1
  unsigned int v11; // r0
  unsigned int v12; // r1
  _DWORD *v14; // [sp+0h] [bp-4h]

  v4 = 0;
  v5 = a1 + 1;
  v6 = a1 + 129;
  v14 = a1 + 385;
  MEMORY[0x102790] = 167772160;
  if ( MEMORY[0xA000000] == 0x455A49532041424CLL )
    v7 = MEMORY[0xA000008];
  else
    v7 = 512;
  if ( v7 < 0x800000 && *(_QWORD *)(v7 + 167772160) == 0x5452415020494645LL )
  {
    v8 = (*(_DWORD *)(v7 + 167772232) - 1) * v7 + v7 + 167772160;
    for ( i = 0; i < *(_DWORD *)(v7 + 167772240); ++i )
    {
      if ( (*(_DWORD *)(v8 + 48) & 4) != 0 )
      {
        MEMORY[0x102790] = *(_DWORD *)(v8 + 32) * v7 + 167772160;
        break;
      }
      v8 += *(_DWORD *)(v7 + 167772244);
    }
  }
  v10 = MEMORY[0x102790];
  *a1 = MEMORY[0x102790];
  mem_copy_bytes(v5, v10, 20);
  if ( a2 )
    a2(0, 0, v5, 20);
  if ( sub_116D8(v5, "SF_BOOT") )
  {
    v4 = 20480;
  }
  else
  {
    v11 = v5[4];
    if ( v11 >= 0x200 )
    {
      mem_copy_bytes(v6, MEMORY[0x102790] + v11, 180);
      if ( a2 )
        a2(1, 0, v6, 180);
      if ( sub_116D8(v6, "BRLYT") )
      {
        v4 = 20482;
      }
      else
      {
        v12 = MEMORY[0x102790] + 3 * v5[4];
        if ( v6[3] > v12 )
        {
          mem_copy_bytes(v14, v12, 512);
          if ( a2 )
            a2(3, 0, v14, 512);
        }
      }
    }
    else
    {
      v4 = 20481;
    }
  }
  if ( v4 )
    MEMORY[0x10287C] = 4102;
  return v4;
}


// ==================== sub_3C7A @0x3C7A size=48 ====================
unsigned int __fastcall sub_3C7A(int a1, _DWORD *a2, int a3, int a4)
{
  unsigned int result; // r0
  int v6; // r1
  int v7; // [sp+0h] [bp-4h] BYREF

  v7 = a4;
  result = auth_find_block_by_type(*(_DWORD *)(a2[2] + 8) + MEMORY[0x102790], 0, &v7);
  if ( result < 0xFF )
  {
    result = auth_check_block_header(v7);
    if ( result < 0xFF )
    {
      v6 = v7;
      *a2 = *(_DWORD *)(v7 + 28);
      a2[1] = *(_DWORD *)(v6 + 32);
    }
  }
  return result;
}


// ==================== sub_3CAA @0x3CAA size=46 ====================
int __fastcall sub_3CAA(int a1, _DWORD *a2, void (__fastcall *a3)(int, _DWORD, _DWORD, _DWORD))
{
  mem_copy_bytes(*a2, MEMORY[0x102790] + *(_DWORD *)(a2[2] + 8), a2[1]);
  if ( a3 )
    a3(a1, 0, *a2, a2[1]);
  return 0;
}


// ==================== sub_3D04 @0x3D04 size=34 ====================
BOOL sub_3D04()
{
  return sub_10EE6() != 1 && ((MEMORY[0x100056F0] >> 17) & 3) == 2;
}


// ==================== sub_3D2C @0x3D2C size=60 ====================
int __fastcall sub_3D2C(int a1, int a2)
{
  int v4; // r6
  _DWORD *v5; // r5

  v4 = 20737;
  time_ms_to_ticks(1u);
  time_get_tick();
  v5 = (_DWORD *)(a1 + 288358400);
  while ( !time_wait_ticks() )
  {
    if ( (*v5 & a2) == 0 )
      return 0;
  }
  return v4;
}


// ==================== sub_3D68 @0x3D68 size=58 ====================
void sub_3D68()
{
  MEMORY[0x113000C4] = 48;
  MEMORY[0x11300034] = 102;
  MEMORY[0x11300030] = 0;
  MEMORY[0x1130002C] = 0;
  MEMORY[0x11300004] = 8;
  MEMORY[0x11300000] = 4;
  sub_3D2C(0, 4);
  MEMORY[0x11300034] = 153;
  MEMORY[0x11300004] = 8;
  MEMORY[0x11300000] = 4;
  sub_3D2C(0, 4);
  MEMORY[0x11300000] = 0;
  JUMPOUT(0x3D60);
}


// ==================== sub_3DA8 @0x3DA8 size=40 ====================
BOOL sub_3DA8()
{
  int v0; // r0

  v0 = brom_get_descriptor(7);
  if ( v0 && (*(_DWORD *)(v0 + 8) & 0x800) != 0 )
    return *(_BYTE *)(v0 + 87) & 1;
  else
    return sub_10F8A() != 0;
}


// ==================== sub_3DD0 @0x3DD0 size=50 ====================
int sub_3DD0()
{
  int result; // r0
  unsigned int v1; // r0

  result = MEMORY[0x10298F];
  if ( !MEMORY[0x10298F] )
  {
    v1 = sub_3DA8();
    if ( !v1 )
    {
      v1 = sub_738();
      if ( !v1 )
      {
        v1 = sub_714(1);
        if ( v1 >= 0xFF )
          v1 = usb_report_error((unsigned __int16)v1, 0);
      }
    }
    sub_58DA(v1);
    MEMORY[0x10298F] = 1;
    return 1;
  }
  return result;
}


// ==================== sub_3E02 @0x3E02 size=32 ====================
int sub_3E02()
{
  int result; // r0

  result = MEMORY[0x10298F];
  if ( MEMORY[0x10298F] )
  {
    sub_5A18();
    if ( sub_738() )
      sub_714(0);
    MEMORY[0x10298F] = 0;
    return 0;
  }
  return result;
}


// ==================== sub_3E22 @0x3E22 size=74 ====================
_BYTE *__fastcall sub_3E22(_BYTE *result)
{
  int v1; // r2
  _BYTE *i; // r4
  _BYTE v3[64]; // [sp+0h] [bp-40h] BYREF

  if ( MEMORY[0x1029B4] )
  {
    v1 = *(_DWORD *)(MEMORY[0x1029B4] + 8);
    if ( (v1 & 4) != 0 )
      return result;
    if ( (v1 & 8) != 0 && *(_BYTE *)(MEMORY[0x1029B4] + 16) )
    {
      mem_copy_bytes(v3, MEMORY[0x1029B4] + 16, 64);
      v3[63] = 0;
      result = v3;
    }
  }
  for ( i = result; *i; ++i )
    ((void (*)(void))uart_putc)();
  uart_putc(10);
  return (_BYTE *)uart_putc(13);
}


// ==================== usb_wait_download_magic_usb (sub_3E6C) @0x3E6C size=202 ====================
int __fastcall usb_wait_download_magic_usb(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  int v5; // r6
  int v6; // r0
  int v7; // r0
  int v9; // [sp+0h] [bp-4h] BYREF

  v9 = a4;
  v4 = 0;
  v5 = 0;
  trace_begin(0x14u, 0);
  time_get_tick();
  time_ms_to_ticks(0x2710u);
  usb_init_endpoints();
  while ( !MEMORY[0x102991] || !time_wait_ticks() )
  {
    if ( usb_rx_poll_byte(&v9) == 1 )
    {
      if ( *((unsigned __int8 *)&dword_12218[8] + v4) == (unsigned __int8)v9 )
      {
        v6 = usb_tx_put_byte((unsigned __int8)~(_BYTE)v9);
        usb_tx_flush(v6);
        v4 = (unsigned __int8)(v4 + 1);
        if ( v4 == 4 )
        {
          v5 = 1;
          goto LABEL_14;
        }
      }
      else
      {
        v7 = usb_tx_put_byte((unsigned __int8)(v9 + 1));
        usb_tx_flush(v7);
        v4 = 0;
      }
    }
    if ( time_wait_ticks() )
    {
      sub_C02C();
      time_get_tick();
    }
    if ( time_wait_ticks() )
    {
      sub_3E22("[USBDL] Waiting for start cmd over 1 min ...");
      MEMORY[0x102994] = time_get_tick();
    }
  }
  sub_3E02();
  sub_E852(0);
LABEL_14:
  trace_begin(0x14u, 1);
  trace_end(0x14u, v5, MEMORY[0x1029B0], 0);
  return v5;
}


// ==================== sub_3F36 @0x3F36 size=196 ====================
int sub_3F36()
{
  int v0; // r4
  unsigned int v1; // r0
  int result; // r0

  mem_set_bytes(1059212, 0, 44);
  v0 = brom_get_descriptor(7);
  MEMORY[0x10298C] = 7;
  if ( v0 && (*(_DWORD *)(v0 + 8) & 0x10) != 0 )
  {
    MEMORY[0x10298C] = *(_BYTE *)(v0 + 82) | 3;
  }
  else if ( sub_10F18() )
  {
    MEMORY[0x10298C] &= ~4u;
  }
  MEMORY[0x102998] = time_ms_to_ticks(0xEA60u);
  MEMORY[0x102991] = 1;
  MEMORY[0x10299C] = 40000;
  MEMORY[0x1029A0] = 40000;
  MEMORY[0x1029A4] = 40000;
  if ( v0 )
  {
    if ( (*(_DWORD *)(v0 + 8) & 0x80) != 0 )
    {
      MEMORY[0x10299C] = *(_DWORD *)(v0 + 88);
      if ( MEMORY[0x10299C] < 0xBB8u )
        MEMORY[0x10299C] = 3000;
    }
  }
  v1 = sub_4396();
  if ( v1 )
  {
    if ( v1 < 0x3FFF )
      MEMORY[0x1029A0] = 1000 * v1;
    else
      MEMORY[0x1029A0] = -1;
  }
  else if ( v0 && (*(_DWORD *)(v0 + 8) & 0x100) != 0 )
  {
    MEMORY[0x1029A0] = *(_DWORD *)(v0 + 92);
  }
  if ( MEMORY[0x1029A0] < 0xBB8u )
    MEMORY[0x1029A0] = 3000;
  if ( v0 && (*(_DWORD *)(v0 + 8) & 2) != 0 )
    MEMORY[0x1029A4] = *(_DWORD *)(v0 + 12);
  if ( MEMORY[0x102874] == 3 )
    MEMORY[0x102990] = 1;
  MEMORY[0x1029B4] = v0;
  result = time_get_tick();
  MEMORY[0x102994] = result;
  MEMORY[0x1029A8] = result;
  return result;
}


// ==================== sub_3FFA @0x3FFA size=4 ====================
int sub_3FFA()
{
  return 1;
}


// ==================== sub_3FFE @0x3FFE size=178 ====================
int sub_3FFE()
{
  int result; // r0
  int v1; // r4
  int v2; // r0
  int v3; // r0

  if ( MEMORY[0x102898] << 31 || (result = MEMORY[0x1008E8] << 25, (MEMORY[0x1008E8] & 0x40) != 0) )
  {
    if ( MEMORY[0x103EC0] == 1414676821 && MEMORY[0x103EC4] == 1313169201
      || !MEMORY[0x1029B4]
      || !(*(_DWORD *)(MEMORY[0x1029B4] + 8) << 31)
      || (result = MEMORY[0x102878]) != 0 )
    {
      v1 = 1059180;
      MEMORY[0x10296C] = 91;
      MEMORY[0x10296D] = 68;
      MEMORY[0x10296E] = 76;
      MEMORY[0x10296F] = 93;
      MEMORY[0x102970] = 32;
      v2 = sub_E4FA(MEMORY[0x1029B0], 1059185, 8);
      MEMORY[0x102979] = 32;
      v3 = sub_43A0(v2);
      sub_E4FA(v3, 1059194, 8);
      MEMORY[0x102982] = 32;
      sub_E4FA(MEMORY[0x102991], 1059203, 2);
      sub_E4FA(MEMORY[0x10298C], 1059205, 2);
      sub_E4FA(MEMORY[0x102874], 1059207, 2);
      MEMORY[0x102989] = 10;
      MEMORY[0x10298A] = 13;
      MEMORY[0x10298B] = 0;
      while ( 1 )
      {
        result = *(unsigned __int8 *)v1;
        if ( !*(_BYTE *)v1 )
          break;
        uart_putc(result);
        ++v1;
      }
    }
  }
  return result;
}


// ==================== sub_40B0 @0x40B0 size=186 ====================
void sub_40B0()
{
  unsigned int v0; // r6
  unsigned int v1; // r7
  unsigned int v2; // r5
  int v3; // r0
  int v4; // r0
  int v5; // r0
  int v6; // r0

  v0 = 0;
  v1 = 0;
  v2 = 0;
  trace_begin(0x41u, 0);
  sub_3F36();
  if ( MEMORY[0x10298C] << 31 && MEMORY[0x102990] )
  {
    sub_3DD0();
    MEMORY[0x1029B0] = MEMORY[0x10299C];
  }
  else if ( (MEMORY[0x10298C] & 2) != 0 && sub_4370(MEMORY[0x10298C] << 30) )
  {
    sub_3DD0();
    MEMORY[0x1029B0] = MEMORY[0x1029A0];
  }
  else
  {
    if ( (MEMORY[0x10298C] & 4) == 0 )
    {
LABEL_16:
      trace_begin(0x41u, 1);
      trace_end(0x41u, v0, v1, v2);
      JUMPOUT(0x3FF6);
    }
    MEMORY[0x1029B0] = MEMORY[0x1029A4];
    if ( !sub_3FFA() )
    {
LABEL_15:
      sub_3E02();
      goto LABEL_16;
    }
    sub_3DD0();
  }
  MEMORY[0x1029AC] = time_ms_to_ticks(MEMORY[0x1029B0]);
  if ( MEMORY[0x1029B0] == -1 )
    MEMORY[0x102991] = 0;
  v3 = time_get_tick();
  v0 = sub_280(v3);
  sub_3FFE();
  v4 = time_get_tick();
  v1 = sub_280(v4);
  v5 = sub_5980();
  MEMORY[0x10298E] = v5;
  if ( v5 )
  {
    v6 = time_get_tick();
    v2 = sub_280(v6);
    sub_E852(1);
    MEMORY[0x10298D] = 1;
    goto LABEL_16;
  }
  MEMORY[0x10298D] = 2;
  goto LABEL_15;
}


// ==================== sub_416A @0x416A size=52 ====================
BOOL sub_416A()
{
  if ( time_wait_ticks() )
  {
    sub_3E22("[USBDL] Waiting for host's response over 1 min ...");
    MEMORY[0x102994] = time_get_tick();
  }
  return !MEMORY[0x102991] || !time_wait_ticks();
}


// ==================== sub_419E @0x419E size=24 ====================
void __fastcall sub_419E(int a1, unsigned int a2)
{
  unsigned int i; // r4

  for ( i = 0; i < a2; ++i )
    *(_BYTE *)(a1 + i) = sub_5B52();
  JUMPOUT(0x41B6);
}


// ==================== sub_4244 @0x4244 size=92 ====================
int __fastcall sub_4244(int a1, unsigned int a2)
{
  unsigned int i; // r4
  unsigned int v5; // r0

  for ( i = 0; i < a2; ++i )
    usb_tx_put_byte(*(unsigned __int8 *)(a1 + i));
  if ( !usb_is_suspended() )
  {
    if ( usb_is_high_speed() == 1 )
      v5 = 512;
    else
      v5 = 64;
    if ( !(a2 % v5) )
    {
      usb_tx_flush(0);
      MEMORY[0x1027BC] = 0;
      usb_ep_kick((unsigned __int8)IDAW_MEM[0x102AA0]);
      while ( !MEMORY[0x1027BC] )
        usb_poll_events();
    }
  }
  return 0;
}


// ==================== sub_42A0 @0x42A0 size=24 ====================
BOOL sub_42A0()
{
  BOOL v0; // r4

  v0 = sub_10F22() != 0;
  if ( sub_10F2C() )
    return 0;
  return v0;
}


// ==================== sub_42B8 @0x42B8 size=42 ====================
unsigned int sub_42B8()
{
  unsigned int v0; // r4

  v0 = 0;
  if ( MEMORY[0x1029B4] && (*(_DWORD *)(MEMORY[0x1029B4] + 8) & 0x20) != 0 )
  {
    v0 = *(unsigned __int8 *)(MEMORY[0x1029B4] + 81);
  }
  else if ( sub_42A0() )
  {
    v0 = 1;
  }
  if ( v0 >= 2 )
    return 0;
  return v0;
}


// ==================== sub_42E2 @0x42E2 size=78 ====================
int __fastcall sub_42E2(_WORD *a1, _WORD *a2)
{
  int v4; // r4
  int v5; // r0

  if ( MEMORY[0x1027B4] == 1 )
  {
    LOWORD(v4) = 4100;
    LOWORD(v5) = 24576;
    goto LABEL_9;
  }
  if ( MEMORY[0x1029B4] && (*(_DWORD *)(MEMORY[0x1029B4] + 8) & 0x40) != 0 )
  {
    LOWORD(v4) = *(_WORD *)(MEMORY[0x1029B4] + 96);
    LOWORD(v5) = *(_WORD *)(MEMORY[0x1029B4] + 98);
LABEL_9:
    *a1 = v4;
    *a2 = v5;
    return 1;
  }
  if ( sub_10F36() == 1 )
  {
    v4 = sub_10F48();
    v5 = sub_10F40();
    if ( v4 )
    {
      if ( v5 )
        goto LABEL_9;
    }
  }
  return 0;
}


// ==================== sub_4330 @0x4330 size=46 ====================
BOOL sub_4330()
{
  int v0; // r0

  v0 = brom_get_descriptor(7);
  if ( v0 && (*(_DWORD *)(v0 + 8) & 0x400) != 0 )
    return *(unsigned __int8 *)(v0 + 86) == 1;
  else
    return sub_10F50() != 0;
}


// ==================== sub_4370 @0x4370 size=38 ====================
BOOL sub_4370()
{
  return HIWORD(MEMORY[0x1001A080]) == 17484 && MEMORY[0x1001A080] << 31 && (MEMORY[0x1001A080] & 2) == 0;
}


// ==================== sub_4396 @0x4396 size=10 ====================
int sub_4396()
{
  return MEMORY[0x1001A080] >> 2;
}


// ==================== sub_43A0 @0x43A0 size=6 ====================
int sub_43A0()
{
  return MEMORY[0x1001A080];
}


// ==================== sub_43AC @0x43AC size=106 ====================
BOOL sub_43AC()
{
  MEMORY[0x11E40368] &= ~0x4000000u;
  MEMORY[0x11E4036C] &= ~0x10000u;
  MEMORY[0x11E40320] &= ~0x200u;
  MEMORY[0x11E40320] &= ~0x100u;
  MEMORY[0x11E40318] &= ~0x800000u;
  MEMORY[0x11E40300] |= 0x20u;
  MEMORY[0x11E40368] |= 8u;
  MEMORY[0x11E40368] |= 0x40000u;
  time_delay_ms_v2(2u);
  MEMORY[0x11E4036C] = MEMORY[0x11E4036C] & 0xFFFFFFC1 | 0x2E;
  MEMORY[0x11E4036C] |= 0x3E00u;
  return sub_11E24(2u);
}


// ==================== sub_4416 @0x4416 size=86 ====================
BOOL sub_4416()
{
  MEMORY[0x11E4036C] = MEMORY[0x11E4036C] & 0xFFFFFFC1 | 0x12;
  MEMORY[0x11203E00] |= 1u;
  MEMORY[0x11203E50] |= 0x20u;
  time_delay_ms(1u);
  MEMORY[0x11203E50] &= ~0x20u;
  MEMORY[0x11E4036C] &= 0xFFFFC1FF;
  MEMORY[0x11E40368] &= ~8u;
  MEMORY[0x11E40368] |= 0x40000u;
  return sub_11E24(2u);
}


// ==================== sub_447C @0x447C size=10 ====================
int sub_447C()
{
  return MEMORY[0x102794]++;
}


// ==================== usb_debug_event (sub_4486) @0x4486 size=58 ====================
int __fastcall usb_debug_event(int result, int a2)
{
  __int16 v3; // r3
  int v4; // r4
  int v5; // r0
  int v6; // r2
  int v7; // r4
  __int16 v8; // r3

  if ( MEMORY[0x102798] )
  {
    v3 = *(_WORD *)(MEMORY[0x102798] + 768);
    v4 = 3 * (v3 & 0x3F);
    *(_BYTE *)(MEMORY[0x102798] + 12 * (v3 & 0x3F)) = result;
    v5 = sub_447C();
    v6 = MEMORY[0x102798];
    v7 = MEMORY[0x102798] + 4 * v4;
    *(_DWORD *)(v7 + 4) = v5;
    *(_DWORD *)(v7 + 8) = a2;
    result = (unsigned __int16)(v8 + 1);
    if ( result == 64 )
      result = 0;
    *(_WORD *)(v6 + 768) = result;
  }
  return result;
}


// ==================== sub_44C0 @0x44C0 size=40 ====================
int sub_44C0()
{
  int result; // r0

  result = MEMORY[0x103B48];
  if ( MEMORY[0x103B48] && MEMORY[0x103B40] == 1145197397 && MEMORY[0x103B44] == 1195525196 )
  {
    MEMORY[0x102798] = MEMORY[0x103B48];
    return mem_set_bytes(MEMORY[0x103B48], 0, 772);
  }
  return result;
}


// ==================== sub_44F8 @0x44F8 size=4 ====================
_UNKNOWN **sub_44F8()
{
  return &off_12248;
}


// ==================== sub_44FC @0x44FC size=6 ====================
int *sub_44FC()
{
  return &dword_12250[3];
}


// ==================== sub_4502 @0x4502 size=6 ====================
_UNKNOWN **sub_4502()
{
  return &off_12240;
}


// ==================== sub_450C @0x450C size=192 ====================
unsigned int sub_450C()
{
  unsigned int v0; // r4
  unsigned int i; // r4
  unsigned int j; // r4
  int v3; // r4
  unsigned int result; // r0

  v0 = 0;
  mem_set_bytes(1069276, 0, 16);
  do
  {
    mem_set_bytes(52 * v0 + 1069292, 0, 52);
    v0 = (unsigned __int8)(v0 + 1);
  }
  while ( v0 < 3 );
  for ( i = 0; i < 2; i = (unsigned __int8)(i + 1) )
    mem_set_bytes(36 * i + 1069448, 0, 36);
  for ( j = 0; j < 3; j = (unsigned __int8)(j + 1) )
    mem_set_bytes(36 * j + 1069520, 0, 36);
  v3 = 0;
  do
  {
    mem_set_bytes(36 * v3 + 1069628, 0, 36);
    v3 = (unsigned __int8)(v3 + 1);
  }
  while ( !v3 );
  for ( result = 0; result < 0xA; result = (unsigned __int8)(result + 1) )
    *(_DWORD *)(4 * result + 0x105260) = 0;
  MEMORY[0x1052A0] = 0;
  MEMORY[0x1052AC] = 0;
  MEMORY[0x1052AD] = 0;
  MEMORY[0x1052AE] = 0;
  MEMORY[0x1052AF] = 0;
  MEMORY[0x1052B1] = 0;
  MEMORY[0x1052B2] = 0;
  MEMORY[0x1052C4] = 0;
  MEMORY[0x1052C8] = 0;
  MEMORY[0x1052C9] = 0;
  MEMORY[0x1052CA] = 0;
  MEMORY[0x1052CB] = 0;
  MEMORY[0x1052CC] = 0;
  return result;
}


// ==================== sub_45CC @0x45CC size=10 ====================
int __fastcall sub_45CC(int result)
{
  MEMORY[0x1052C4] = result;
  return result;
}


// ==================== sub_45D6 @0x45D6 size=24 ====================
int __fastcall sub_45D6(int a1, int a2, int a3, int a4)
{
  int v4; // r1

  *(_DWORD *)(a1 + 4) = a4;
  *(_DWORD *)(a1 + 8) = a3;
  v4 = *(unsigned __int16 *)(a2 + 6);
  if ( v4 < a4 )
    *(_DWORD *)(a1 + 4) = v4;
  MEMORY[0x1052B3] = 2;
  return 2;
}


// ==================== sub_45EE @0x45EE size=232 ====================
int sub_45EE()
{
  int v0; // r0
  unsigned int i; // r4
  unsigned int j; // r5
  unsigned int k; // r4

  v0 = sub_570A(0);
  sub_54DC(v0);
  MEMORY[0x1052AD] = 0;
  for ( i = 0; MEMORY[0x1052C8] > i; i = (unsigned __int8)(i + 1) )
  {
    usb_ep_configure(
      *(_BYTE *)(36 * i + 0x10518A) & 0x7F,
      *(unsigned __int8 *)(36 * i + 0x10518C) | (*(unsigned __int8 *)(36 * i + 0x10518D) << 8),
      1);
    *(_DWORD *)(36 * i + 0x1051A4) = -1;
  }
  for ( j = 0; MEMORY[0x1052C9] > j; j = (unsigned __int8)(j + 1) )
  {
    sub_50E2(
      *(_BYTE *)(36 * j + 0x1051D2) & 0x7F,
      *(unsigned __int8 *)(36 * j + 0x1051D4) | (*(unsigned __int8 *)(36 * j + 0x1051D5) << 8),
      1);
    *(_DWORD *)(36 * j + 0x1051EC) = 0;
    *(_DWORD *)(36 * j + 0x1051F0) = 0;
  }
  for ( k = 0; MEMORY[0x1052CA] > k; k = (unsigned __int8)(k + 1) )
  {
    usb_ep_configure(
      *(_BYTE *)(36 * k + 0x10523E) & 0x7F,
      *(unsigned __int8 *)(36 * k + 0x105240) | (*(unsigned __int8 *)(36 * k + 0x105241) << 8),
      2);
    *(_DWORD *)(36 * k + 0x105258) = -1;
  }
  MEMORY[0x1052AF] = 0;
  MEMORY[0x1052AE] = 0;
  MEMORY[0x1052B1] = 0;
  MEMORY[0x1052B2] = 0;
  MEMORY[0x1052B3] = 0;
  MEMORY[0x1052B4] = -1;
  return sub_5892();
}


// ==================== sub_46D6 @0x46D6 size=106 ====================
int sub_46D6()
{
  int v0; // r4

  if ( MEMORY[0x1052B8] > 64 )
  {
    v0 = 64;
    MEMORY[0x1052B8] -= 64;
  }
  else
  {
    v0 = MEMORY[0x1052B8];
    MEMORY[0x1052B8] = 0;
  }
  sub_5212(0, (unsigned __int16)v0, MEMORY[0x1052BC]);
  MEMORY[0x1052BC] += v0;
  if ( v0 )
    return sub_538E(3, 0);
  MEMORY[0x1052B3] = 0;
  return sub_538E(4, 0);
}


// ==================== sub_4740 @0x4740 size=20 ====================
int sub_4740()
{
  int result; // r0

  result = 1069256;
  if ( MEMORY[0x1052C4] )
    return MEMORY[0x1052C4](1069748);
  return result;
}


// ==================== sub_4754 @0x4754 size=126 ====================
int __fastcall sub_4754(int a1, unsigned __int8 *a2)
{
  int v4; // r6
  int v5; // r1
  __int16 v7; // r1

  v4 = 0;
  v5 = *a2;
  switch ( v5 )
  {
    case 128:
      MEMORY[0x10279C] = MEMORY[0x1052AF] | (unsigned __int16)(2 * MEMORY[0x1052AE]);
      sub_45D6(a1, (int)a2, 1058716, 2);
      break;
    case 129:
      sub_45D6(a1, (int)a2, 1058716, 2);
      break;
    case 130:
      v7 = *((_WORD *)a2 + 2);
      if ( (v7 & 0x80) != 0 )
        MEMORY[0x10279C] = sub_4CEA(v7 & 0xF, 0);
      else
        MEMORY[0x10279C] = sub_4CEA(v7 & 0xF, 1);
      sub_45D6(a1, (int)a2, 1058716, 2);
      break;
    default:
      return 1;
  }
  return v4;
}


// ==================== sub_47D2 @0x47D2 size=116 ====================
int __fastcall sub_47D2(int a1, char a2)
{
  int v2; // r4
  int v4; // r0

  v2 = 0;
  if ( *(_BYTE *)a1 )
  {
    if ( *(_BYTE *)a1 == 2 )
    {
      if ( *(_WORD *)(a1 + 2) )
      {
        return 1;
      }
      else
      {
        v4 = *(unsigned __int16 *)(a1 + 4);
        if ( v4 )
        {
          if ( (v4 & 0x80) != 0 )
          {
            if ( (v4 & 0xFu) <= 4 && v4 << 28 )
              sub_5282(v4 & 0xF, 0, a2, 0);
            else
              return 1;
          }
          else if ( (v4 & 0xFu) <= 3 && v4 << 28 )
          {
            sub_5282(v4 & 0xF, 1, a2, 0);
          }
          else
          {
            return 1;
          }
        }
      }
    }
    else
    {
      return 1;
    }
  }
  else if ( *(_WORD *)(a1 + 2) == 1 )
  {
    MEMORY[0x1052AE] = a2;
  }
  else
  {
    return 1;
  }
  return v2;
}


// ==================== sub_4846 @0x4846 size=16 ====================
int __fastcall sub_4846(int a1, int a2)
{
  sub_45D6(a1, a2, 1069746, 1);
  return 0;
}


// ==================== sub_4856 @0x4856 size=52 ====================
int __fastcall sub_4856(int a1, int a2)
{
  int v2; // r4

  v2 = 0;
  if ( MEMORY[0x1052AD] == 2 && !*(_WORD *)(a2 + 2) )
  {
    sub_45D6(a1, a2, a2 + 2, 1);
  }
  else if ( MEMORY[0x1052AD] == 3 )
  {
    sub_45D6(a1, a2, 1069745, 1);
  }
  else
  {
    return 1;
  }
  return v2;
}


// ==================== sub_488A @0x488A size=14 ====================
int __fastcall sub_488A(int a1, int a2)
{
  MEMORY[0x1052B2] = *(_WORD *)(a2 + 2);
  return 0;
}


// ==================== sub_4898 @0x4898 size=58 ====================
int __fastcall sub_4898(int a1, int a2)
{
  int result; // r0
  unsigned int v3; // r1

  result = 0;
  v3 = (unsigned __int8)*(_WORD *)(a2 + 2);
  if ( !MEMORY[0x1052AD] )
    return 1;
  if ( MEMORY[0x1050D9] < v3 )
    return 1;
  if ( v3 )
  {
    MEMORY[0x1052AD] = 3;
    MEMORY[0x1052B1] = v3;
  }
  else
  {
    MEMORY[0x1052AD] = 2;
    MEMORY[0x1052B1] = 0;
  }
  return result;
}


// ==================== sub_48D2 @0x48D2 size=150 ====================
void __fastcall sub_48D2(int a1, unsigned __int8 *a2)
{
  __int16 v4; // r1
  int v5; // r0

  if ( *a2 == 128 )
  {
    v4 = *((_WORD *)a2 + 1);
    v5 = v4 & 0xFF00;
    if ( v5 == 256 )
    {
      sub_45D6(a1, (int)a2, 1069256, 18);
    }
    else if ( v5 == 512 )
    {
      sub_570A(0);
      if ( MEMORY[0x1050D9] > (unsigned int)(unsigned __int8)*((_WORD *)a2 + 1) )
        sub_45D6(a1, (int)a2, MEMORY[0x1052A0], *(unsigned __int16 *)(MEMORY[0x1052A0] + 2));
    }
    else if ( v5 == 768 && MEMORY[0x1052CC] > (unsigned int)(unsigned __int8)v4 )
    {
      sub_45D6(
        a1,
        (int)a2,
        *(_DWORD *)(4 * (unsigned __int8)v4 + 0x105260),
        **(unsigned __int8 **)(4 * (unsigned __int8)v4 + 0x105260));
    }
  }
  JUMPOUT(0x4772);
}


// ==================== sub_4968 @0x4968 size=70 ====================
int __fastcall sub_4968(_BYTE *a1, int a2)
{
  int v3; // r4
  unsigned int v4; // r0

  v3 = 0;
  if ( *(_BYTE *)a2 )
    return 1;
  if ( MEMORY[0x1052AD] > 2u )
    return 1;
  v4 = (unsigned __int8)*(_WORD *)(a2 + 2);
  *a1 = v4;
  if ( MEMORY[0x1052AD] || v4 > 0x7F )
  {
    MEMORY[0x1052AD] = 0;
  }
  else
  {
    MEMORY[0x1052AD] = 1;
    sub_4FC8((unsigned __int8)*a1, 0);
  }
  return v3;
}


// ==================== sub_49AE @0x49AE size=222 ====================
int __fastcall sub_49AE(_BYTE *a1, int a2)
{
  int v4; // r4
  int v5; // r0
  int v6; // r0

  switch ( *(_BYTE *)(a2 + 1) )
  {
    case 0:
      v4 = sub_4754((int)a1, (unsigned __int8 *)a2);
      break;
    case 1:
      v4 = sub_47D2(a2, 0);
      break;
    case 3:
      v4 = sub_47D2(a2, 1);
      break;
    case 5:
      v4 = sub_4968(a1, a2);
      break;
    case 6:
      sub_48D2((int)a1, (unsigned __int8 *)a2);
      v4 = v5;
      break;
    case 8:
      v4 = sub_4856((int)a1, a2);
      break;
    case 9:
      usb_debug_event(1, *(unsigned __int16 *)(a2 + 2));
      v4 = sub_4898((int)a1, a2);
      break;
    case 0xA:
      v4 = sub_4846((int)a1, a2);
      break;
    case 0xB:
      v4 = sub_488A((int)a1, a2);
      break;
    default:
      usb_debug_event(5, *(unsigned __int16 *)(a2 + 2));
      v4 = 1;
      break;
  }
  if ( MEMORY[0x1052B3] )
  {
    if ( MEMORY[0x1052B3] == 2 )
      v6 = 1;
    else
      v6 = 2;
    return sub_538E(v6, v4);
  }
  else
  {
    if ( MEMORY[0x1052AD] == 1 )
    {
      sub_4FC8(MEMORY[0x1052B4], 1);
      MEMORY[0x1052AD] = 2;
    }
    return sub_538E(0, v4);
  }
}


// ==================== sub_4A8C @0x4A8C size=122 ====================
int sub_4A8C()
{
  int v0; // r0
  int v1; // r2
  int (__fastcall *v3)(int, int); // r2

  v0 = 1069732;
  v1 = 8;
  do
  {
    *(_DWORD *)v0 = MEMORY[0x11201300];
    v0 += 4;
    v1 -= 4;
  }
  while ( v1 );
  if ( (MEMORY[0x1052A4] & 0x60) == 0 )
    return sub_49AE((_BYTE *)0x1052B4, 1069732);
  if ( (MEMORY[0x1052A4] & 0x60) == 0x20 && (MEMORY[0x1052A4] == 161 || MEMORY[0x1052A4] == 33) && MEMORY[0x1052A8] < 3u )
  {
    v3 = *(int (__fastcall **)(int, int))(52 * MEMORY[0x1052A8] + 0x1050F0);
    if ( v3 )
      return v3(1069748, 1069732);
  }
  return sub_538E(0, 1);
}


// ==================== sub_4B06 @0x4B06 size=100 ====================
int __fastcall sub_4B06(int a1, int a2, int a3, int a4)
{
  int result; // r0
  int v5; // [sp+0h] [bp-8h] BYREF
  int v6; // [sp+4h] [bp-4h] BYREF

  v5 = a3;
  v6 = a4;
  sub_5364(&v6, &v5);
  if ( (unsigned __int8)v5 == 1 )
  {
    sub_538E(8, 0);
    MEMORY[0x1052B3] = 0;
  }
  if ( (unsigned __int8)v6 == 1 )
  {
    sub_538E(7, 0);
    MEMORY[0x1052B3] = 0;
  }
  if ( MEMORY[0x1052B3] )
  {
    if ( MEMORY[0x1052B3] == 1 )
      sub_4740();
  }
  else if ( sub_5432() )
  {
    sub_4A8C();
  }
  result = MEMORY[0x1052B3];
  if ( MEMORY[0x1052B3] == 2 )
    return sub_46D6();
  return result;
}


// ==================== sub_4B6A @0x4B6A size=114 ====================
int sub_4B6A()
{
  int v0; // r0
  unsigned int i; // r4
  void (*v2)(void); // r0
  unsigned int j; // r4
  void (*v4)(void); // r0
  unsigned int k; // r4
  void (*v6)(void); // r0
  int result; // r0

  v0 = sub_4C84();
  sub_4FA0(v0);
  sub_45EE();
  for ( i = 0; MEMORY[0x1052C8] > i; i = (unsigned __int8)(i + 1) )
  {
    v2 = *(void (**)(void))(36 * i + 0x105198);
    if ( v2 )
      v2();
  }
  for ( j = 0; MEMORY[0x1052C9] > j; j = (unsigned __int8)(j + 1) )
  {
    v4 = *(void (**)(void))(36 * j + 0x1051E0);
    if ( v4 )
      v4();
  }
  for ( k = 0; ; k = (unsigned __int8)(k + 1) )
  {
    result = MEMORY[0x1052CA];
    if ( MEMORY[0x1052CA] <= k )
      break;
    v6 = *(void (**)(void))(36 * k + 0x10524C);
    if ( v6 )
      v6();
  }
  return result;
}


// ==================== sub_4BDC @0x4BDC size=82 ====================
int __fastcall sub_4BDC(int a1, int a2, int a3)
{
  unsigned int v4; // r0
  int v5; // r0
  int v6; // r0
  int v8; // r0
  int v9; // r0

  sub_4C4E(0);
  v4 = sub_450C();
  sub_60C4(v4);
  MEMORY[0x1052AC] = 1;
  sub_4CA8(0, 0, sub_4B6A);
  v5 = sub_4CA8(3, 0, sub_4B06);
  v6 = sub_57AE(v5);
  if ( a3 != 1 )
    return sub_5892(v6);
  v8 = sub_4F10(v6);
  sub_4FA0(v8);
  v9 = sub_45EE();
  return sub_4EF4(v9);
}


// ==================== nullsub_2 @0x4C48 size=2 ====================
void nullsub_2()
{
  ;
}


// ==================== sub_4C4A @0x4C4A size=4 ====================
// attributes: thunk
BOOL sub_4C4A()
{
  return sub_4330();
}


// ==================== sub_4C4E @0x4C4E size=54 ====================
unsigned int sub_4C4E()
{
  unsigned int i; // r0
  unsigned int result; // r0

  MEMORY[0x1029B8] = 0;
  MEMORY[0x1029BC] = 0;
  MEMORY[0x1029C8] = 0;
  for ( i = 0; i < 4; ++i )
  {
    *(_DWORD *)(4 * i + 0x1029CC) = 0;
    *(_BYTE *)(i + 1059304) = 0;
  }
  for ( result = 0; result < 3; ++result )
  {
    *(_DWORD *)(4 * result + 0x1029DC) = 0;
    *(_BYTE *)(result + 1059308) = 0;
  }
  MEMORY[0x102A00] = 0;
  return result;
}


// ==================== sub_4C84 @0x4C84 size=36 ====================
unsigned int sub_4C84()
{
  unsigned int i; // r0
  unsigned int result; // r0

  MEMORY[0x1029B8] = 0;
  for ( i = 0; i < 4; ++i )
    *(_BYTE *)(i + 1059304) = 0;
  for ( result = 0; result < 3; ++result )
    *(_BYTE *)(result + 1059308) = 0;
  return result;
}


// ==================== sub_4CA8 @0x4CA8 size=66 ====================
void __fastcall sub_4CA8(int a1, int a2, int a3)
{
  int v4; // r5

  if ( a1 )
  {
    if ( a1 == 3 )
    {
      MEMORY[0x1029C8] = a3;
    }
    else
    {
      v4 = 4 * (a2 - 1) + 1059256;
      if ( a1 == 4 )
      {
        nullsub_2();
        *(_DWORD *)(v4 + 20) = a3;
      }
      else if ( a1 == 5 )
      {
        nullsub_2();
        *(_DWORD *)(v4 + 36) = a3;
      }
    }
  }
  else
  {
    MEMORY[0x1029BC] = a3;
  }
}


// ==================== sub_4CEA @0x4CEA size=34 ====================
int __fastcall sub_4CEA(int a1, int a2)
{
  nullsub_2();
  if ( a2 )
    return *(unsigned __int8 *)(a1 + 1059307);
  else
    return *(unsigned __int8 *)(a1 + 1059303);
}


// ==================== sub_4D0C @0x4D0C size=66 ====================
unsigned int __fastcall sub_4D0C(int a1)
{
  unsigned int result; // r0
  unsigned int v2; // r0

  if ( a1 == 1 )
  {
    if ( sub_4C4A() )
    {
      MEMORY[0x11203404] |= 0x20u;
      v2 = MEMORY[0x11203404] | 0x40;
    }
    else
    {
      v2 = MEMORY[0x11203404] & 0xFFFFFF9F | 0x40;
    }
    MEMORY[0x11203404] = v2;
    MEMORY[0x1120241C] = 0;
    MEMORY[0x11201800] = 0;
    return 0;
  }
  else
  {
    result = MEMORY[0x11203404] & 0xFFFFFF9F;
    MEMORY[0x11203404] &= 0xFFFFFF9F;
  }
  return result;
}


// ==================== sub_4D4E @0x4D4E size=30 ====================
int __fastcall sub_4D4E(_DWORD *a1, int a2, int a3, unsigned int a4, unsigned int a5)
{
  unsigned int i; // r4

  for ( i = 0; i < a5; ++i )
  {
    if ( (*a1 & a2) == a3 )
      return 0;
    time_delay_ms_v2(a4);
  }
  return 1;
}


// ==================== sub_4D80 @0x4D80 size=140 ====================
int sub_4D80()
{
  int result; // r0

  MEMORY[0x11203E98] = 0;
  if ( !(MEMORY[0x11203E50] << 31) && sub_4D4E((_DWORD *)0x11203E14, 1, 1, 1u, 0xAu) == 1 )
    MEMORY[0x102A00] |= 8u;
  if ( sub_4D4E((_DWORD *)0x11203E10, 2, 2, 1u, 0xAu) == 1 )
    MEMORY[0x102A00] |= 0x20u;
  if ( sub_4D4E((_DWORD *)0x11203E10, 4, 4, 1u, 0xAu) == 1 )
    MEMORY[0x102A00] |= 0x40u;
  result = sub_4D4E((_DWORD *)0x11203E10, 8, 8, 1u, 0xAu);
  if ( result == 1 )
  {
    result = MEMORY[0x102A00] | 0x80;
    MEMORY[0x102A00] |= 0x80u;
  }
  return result;
}


// ==================== sub_4E0C @0x4E0C size=66 ====================
int sub_4E0C()
{
  if ( sub_4D4E((_DWORD *)0x11203E10, 1024, 1024, 1u, 0xAu) == 1 )
    MEMORY[0x102A00] |= 1u;
  if ( sub_4D4E((_DWORD *)0x11203E14, 1, 1, 1u, 0xAu) == 1 )
    MEMORY[0x102A00] |= 4u;
  return 0;
}


// ==================== sub_4E4E @0x4E4E size=84 ====================
int sub_4E4E()
{
  MEMORY[0x11E40B04] &= ~0x20000000u;
  MEMORY[0x11203E00] &= ~1u;
  MEMORY[0x11203E08] &= ~1u;
  MEMORY[0x11203E50] &= 0xFFFFFFFC;
  MEMORY[0x11203E50] |= 0x20u;
  time_delay_ms(1u);
  MEMORY[0x11203E50] &= ~0x20u;
  MEMORY[0x11203E50] &= ~4u;
  return sub_4E0C();
}


// ==================== sub_4EA2 @0x4EA2 size=74 ====================
int __fastcall sub_4EA2(int a1)
{
  if ( a1 )
  {
    sub_740();
    nullsub_16(0);
    sub_5608(1);
    time_delay_ms(0xFAu);
    sub_43AC();
    sub_4E4E();
    return sub_4D80();
  }
  else
  {
    sub_4D0C(0);
    sub_4416();
    sub_5608(0);
    nullsub_15(0);
    return sub_740();
  }
}


// ==================== sub_4EEC @0x4EEC size=8 ====================
int sub_4EEC()
{
  return MEMORY[0x10282C]();
}


// ==================== sub_4EF4 @0x4EF4 size=4 ====================
unsigned int sub_4EF4()
{
  return sub_4D0C(1);
}


// ==================== sub_4EF8 @0x4EF8 size=12 ====================
int sub_4EF8()
{
  MEMORY[0x11203404] |= 0x40u;
  return 287323140;
}


// ==================== sub_4F04 @0x4F04 size=12 ====================
int sub_4F04()
{
  MEMORY[0x11203404] |= 0x6000u;
  return 287323140;
}


// ==================== sub_4F10 @0x4F10 size=54 ====================
int sub_4F10()
{
  unsigned int v0; // r0
  int result; // r0

  if ( sub_4C4A() )
    v0 = MEMORY[0x11203404] | 0x20;
  else
    v0 = MEMORY[0x11203404] & 0xFFFFFFDF;
  MEMORY[0x11203404] = v0;
  result = MEMORY[0x102A00];
  if ( MEMORY[0x102A00] )
    return usb_write_debug_status(HIWORD(MEMORY[0x102A00]), MEMORY[0x102A00], 28, 85);
  return result;
}


// ==================== sub_4F46 @0x4F46 size=48 ====================
int sub_4F46()
{
  int result; // r0

  result = 287313920;
  if ( (MEMORY[0x11201800] & 7) == 4 )
  {
    MEMORY[0x11201100] = 512;
    MEMORY[0x1050CF] = 9;
  }
  else
  {
    MEMORY[0x11201100] = 64;
    MEMORY[0x1050CF] = 64;
  }
  MEMORY[0x11201088] = 65537;
  return result;
}


// ==================== sub_4F76 @0x4F76 size=42 ====================
int sub_4F76()
{
  MEMORY[0x1120108C] = MEMORY[0x11201084];
  MEMORY[0x1120109C] = MEMORY[0x11201094];
  MEMORY[0x11203418] = 951;
  MEMORY[0x11201850] = 1;
  return 1;
}


// ==================== sub_4FA0 @0x4FA0 size=40 ====================
int sub_4FA0()
{
  MEMORY[0x11201008] = -1;
  MEMORY[0x11203404] &= 0xFFFFFCFF;
  MEMORY[0x11201C84] = 3;
  sub_4F76();
  return sub_4F46();
}


// ==================== sub_4FC8 @0x4FC8 size=12 ====================
int __fastcall sub_4FC8(int result, int a2)
{
  if ( a2 == 1 )
  {
    result <<= 24;
    MEMORY[0x11201800] = result;
  }
  return result;
}


// ==================== usb_ep_configure (sub_4FD4) @0x4FD4 size=270 ====================
int __fastcall usb_ep_configure(int a1, int a2, int a3)
{
  int v4; // r3
  unsigned int v5; // r9
  int v6; // r6
  int v7; // r12
  unsigned int *v8; // r5
  int result; // r0

  v4 = 6;
  if ( a2 == 128 )
  {
    v4 = 7;
  }
  else if ( a2 > 128 )
  {
    switch ( a2 )
    {
      case 256:
        v4 = 8;
        break;
      case 512:
        v4 = 9;
        break;
      case 1024:
        v4 = 10;
        break;
    }
  }
  else
  {
    switch ( a2 )
    {
      case 8:
        v4 = 4;
        break;
      case 16:
        v4 = 4;
        break;
      case 32:
        v4 = 5;
        break;
    }
  }
  v5 = a2 & 0x7FF | *(_DWORD *)(16 * (a1 - 1) + 0x11201110) & 0xDFFFF800;
  v6 = 0;
  v7 = (MEMORY[0x1027A0] >> 4) & 0x1FFF;
  if ( a3 != 1 )
  {
    if ( a3 == 2 )
    {
      v6 = 16;
    }
    else if ( a3 == 3 )
    {
      v6 = 32;
    }
  }
  MEMORY[0x1120108C] |= 1 << a1;
  v8 = (unsigned int *)(16 * (a1 - 1) + 287314192);
  *v8 = v5;
  v8[1] = v6;
  v8[2] = (v4 << 16) & 0xF0000 | v7;
  usb_debug_event(18, *(_DWORD *)(16 * (a1 - 1) + 0x11201110));
  usb_debug_event(18, v8[1]);
  usb_debug_event(18, v8[2]);
  result = MEMORY[0x1027A0] + a2;
  MEMORY[0x1027A0] += a2;
  return result;
}


// ==================== sub_50E2 @0x50E2 size=212 ====================
int __fastcall sub_50E2(int a1, int a2, int a3)
{
  int v4; // r3
  unsigned int v5; // r12
  int v6; // r6
  int v7; // r1
  unsigned int *v8; // r5
  int result; // r0

  v4 = 6;
  if ( a2 == 128 )
  {
    v4 = 7;
  }
  else if ( a2 > 128 )
  {
    switch ( a2 )
    {
      case 256:
        v4 = 8;
        break;
      case 512:
        v4 = 9;
        break;
      case 1024:
        v4 = 10;
        break;
    }
  }
  else
  {
    switch ( a2 )
    {
      case 8:
        v4 = 4;
        break;
      case 16:
        v4 = 4;
        break;
      case 32:
        v4 = 5;
        break;
    }
  }
  v5 = a2 & 0x7FF | (*(_DWORD *)(16 * (a1 - 1) + 0x11201210) >> 11 << 11) & 0xDFFFFFFF;
  v6 = 0;
  v7 = (v4 << 16) & 0xF0000 | (MEMORY[0x1027A4] >> 4) & 0x1FFF;
  if ( a3 != 1 )
  {
    if ( a3 == 2 )
    {
      v6 = 16;
    }
    else if ( a3 == 3 )
    {
      v6 = 32;
    }
  }
  MEMORY[0x1120108C] |= 0x10000 << a1;
  v8 = (unsigned int *)(16 * (a1 - 1) + 287314448);
  *v8 = v5;
  v8[1] = v6;
  v8[2] = v7;
  usb_debug_event(18, *(_DWORD *)(16 * (a1 - 1) + 0x11201210));
  usb_debug_event(18, v8[1]);
  usb_debug_event(18, v8[2]);
  result = MEMORY[0x1027A4] + a2;
  MEMORY[0x1027A4] += a2;
  return result;
}


// ==================== sub_51B6 @0x51B6 size=20 ====================
char __fastcall sub_51B6(char result)
{
  MEMORY[0x11201088] = (1 << result) | MEMORY[0x11201084];
  return result;
}


// ==================== sub_51CA @0x51CA size=20 ====================
char __fastcall sub_51CA(char result)
{
  MEMORY[0x11201088] = (0x10000 << result) | MEMORY[0x11201084];
  return result;
}


// ==================== sub_51DE @0x51DE size=48 ====================
int __fastcall sub_51DE(int a1, unsigned int a2, int a3)
{
  int v3; // r3
  int v4; // r0

  v3 = 16 * a1 + 287314688;
  while ( a2 )
  {
    v4 = *(_DWORD *)v3;
    *(_WORD *)a3 = *(_DWORD *)v3;
    *(_BYTE *)(a3 + 2) = BYTE2(v4);
    *(_BYTE *)(a3 + 3) = HIBYTE(v4);
    a3 += 4;
    if ( a2 <= 4 )
      a2 = 0;
    else
      a2 = (unsigned __int16)(a2 - 4);
  }
  return *(_DWORD *)v3;
}


// ==================== sub_520E @0x520E size=4 ====================
int __fastcall sub_520E(int a1, unsigned int a2, int a3)
{
  return sub_51DE(a1, a2, a3);
}


// ==================== sub_5212 @0x5212 size=112 ====================
int __fastcall sub_5212(int a1, int a2, unsigned __int8 *a3)
{
  int result; // r0
  char v4; // t1
  unsigned __int8 v5; // r1

  result = 16 * a1 + 287313920;
  while ( a2 )
  {
    switch ( a2 )
    {
      case 1:
        v4 = *a3++;
        *(_BYTE *)(result + 768) = v4;
        a2 = 0;
        break;
      case 2:
        *(_WORD *)(result + 768) = *a3 + (a3[1] << 8);
        a3 += 2;
        a2 = 0;
        break;
      case 3:
        *(_WORD *)(result + 768) = *a3 + (a3[1] << 8);
        v5 = a3[2];
        a3 += 3;
        *(_BYTE *)(result + 768) = v5;
        a2 = 0;
        break;
      default:
        *(_DWORD *)(result + 768) = *a3 + (a3[1] << 8) + (a3[2] << 16) + (a3[3] << 24);
        a3 += 4;
        a2 = (unsigned __int16)(a2 - 4);
        break;
    }
  }
  return result;
}


// ==================== sub_5282 @0x5282 size=226 ====================
unsigned int __fastcall sub_5282(int a1, int a2, int a3)
{
  int v6; // r4
  unsigned int result; // r0
  int v8; // r0

  nullsub_2();
  v6 = 0x10000 << a1;
  if ( a3 == 1 )
  {
    if ( a2 == 1 )
    {
      result = *(_DWORD *)(16 * (a1 - 1) + 0x11201210) & 0xFF9EFFFF | 0x200000;
      *(_DWORD *)(16 * (a1 - 1) + 0x11201210) = result;
      *(_BYTE *)(a1 + 1059307) = 1;
    }
    else
    {
      v8 = *(_DWORD *)(16 * (a1 - 1) + 0x11201110);
      if ( (v8 & 0x1000000) == 0 )
      {
        MEMORY[0x11201804] |= v6;
        MEMORY[0x11201804] &= ~v6;
      }
      result = v8 & 0xFF9FFFFF | 0x200000;
      *(_DWORD *)(16 * (a1 - 1) + 0x11201110) = result;
      *(_BYTE *)(a1 + 1059303) = 1;
    }
  }
  else if ( a2 == 1 )
  {
    *(_DWORD *)(16 * (a1 - 1) + 0x11201210) = *(_DWORD *)(16 * (a1 - 1) + 0x11201210) & 0xFF9EFFFF | 0x400000;
    MEMORY[0x11201804] |= 1 << a1;
    result = MEMORY[0x11201804] & ~(1 << a1);
    MEMORY[0x11201804] = result;
    *(_BYTE *)(a1 + 1059307) = 0;
  }
  else
  {
    *(_DWORD *)(16 * (a1 - 1) + 0x11201110) = *(_DWORD *)(16 * (a1 - 1) + 0x11201110) & 0xFF9FFFFF | 0x400000;
    MEMORY[0x11201804] |= v6;
    result = MEMORY[0x11201804] & ~v6;
    MEMORY[0x11201804] = result;
    *(_BYTE *)(a1 + 1059303) = 0;
  }
  return result;
}


// ==================== sub_5364 @0x5364 size=42 ====================
bool *__fastcall sub_5364(bool *result, bool *a2)
{
  *a2 = (MEMORY[0x11201100] & 0x400000) != 0;
  *result = (MEMORY[0x11201080] & 0x10000) != 0;
  return result;
}


// ==================== sub_538E @0x538E size=164 ====================
unsigned int __fastcall sub_538E(int a1, int a2, int a3)
{
  int v3; // r3
  unsigned int result; // r0

  v3 = 0;
  if ( a1 == 8 )
  {
    result = MEMORY[0x11201100] | 0x400000;
    MEMORY[0x11201100] |= 0x400000u;
  }
  else if ( a1 == 7 )
  {
    result = MEMORY[0x11201080] | 0x10000;
    MEMORY[0x11201080] |= 0x10000u;
  }
  else
  {
    if ( a1 )
    {
      switch ( a1 )
      {
        case 1:
          v3 = 1179648;
          break;
        case 2:
          v3 = 0x20000;
          break;
        case 3:
          v3 = 0x40000;
          break;
        case 5:
        case 6:
          MEMORY[0x11201100] |= 0x10000u;
          v3 = 0;
          break;
      }
    }
    else
    {
      v3 = 0x20000;
    }
    if ( a2 == 1 )
    {
      MEMORY[0x11201804] |= 1u;
      MEMORY[0x11201804] &= ~1u;
      result = MEMORY[0x11201100] | 0x2000000;
      MEMORY[0x11201100] |= 0x2000000u;
    }
    else
    {
      if ( a3 == 1 )
        v3 |= 0x80000u;
      result = MEMORY[0x11201100] & 0xFFBCFFFF | v3;
      MEMORY[0x11201100] = result;
    }
  }
  return result;
}


// ==================== sub_5432 @0x5432 size=26 ====================
int sub_5432()
{
  int result; // r0

  result = 0;
  if ( (MEMORY[0x11201100] & 0x30000) != 0 )
    return MEMORY[0x11201108];
  return result;
}


// ==================== usb_ep_kick (sub_544C) @0x544C size=36 ====================
int __fastcall usb_ep_kick(int a1)
{
  nullsub_2();
  *(_DWORD *)(16 * (a1 - 1) + 0x11201110) |= 0x10000u;
  return 16 * (a1 - 1) + 287314192;
}


// ==================== usb_ep_get_pending (sub_5470) @0x5470 size=50 ====================
int __fastcall usb_ep_get_pending(int a1)
{
  int v2; // r5
  int v3; // r4

  v2 = 0;
  nullsub_2();
  v3 = a1 - 1;
  if ( (*(_DWORD *)(16 * v3 + 0x11201210) & 0x10000) != 0 )
    return HIWORD(*(_DWORD *)(16 * v3 + 0x1120121C));
  return v2;
}


// ==================== sub_54A2 @0x54A2 size=36 ====================
int __fastcall sub_54A2(int a1)
{
  nullsub_2();
  *(_DWORD *)(16 * (a1 - 1) + 0x11201210) |= 0x10000u;
  return 16 * (a1 - 1) + 287314448;
}


// ==================== usb_is_high_speed (sub_54C6) @0x54C6 size=22 ====================
BOOL usb_is_high_speed()
{
  return (MEMORY[0x11201800] & 7) == 3;
}


// ==================== sub_54DC @0x54DC size=14 ====================
int sub_54DC()
{
  MEMORY[0x1027A0] = 64;
  MEMORY[0x1027A4] = 2112;
  return 1058720;
}


// ==================== sub_54EA @0x54EA size=22 ====================
BOOL sub_54EA()
{
  return (MEMORY[0x11201800] & 7) == 3;
}


// ==================== sub_5500 @0x5500 size=22 ====================
BOOL sub_5500()
{
  return (MEMORY[0x11201800] & 7) == 4;
}


// ==================== usb_poll_events (sub_5516) @0x5516 size=224 ====================
void usb_poll_events()
{
  char v0; // r1
  int v1; // r5
  unsigned int v2; // r6
  unsigned int i; // r4
  void (*v4)(void); // r0
  unsigned int j; // r4
  void (*v6)(void); // r0

  MEMORY[0x11201854] &= MEMORY[0x11201850];
  if ( (MEMORY[0x11201000] & 0x10) != 0 )
  {
    v0 = MEMORY[0x1120341C] & MEMORY[0x11203418];
    MEMORY[0x1120341C] &= MEMORY[0x11203418];
  }
  else
  {
    v0 = 0;
  }
  v1 = (unsigned __int16)(MEMORY[0x11201080] & MEMORY[0x11201084]);
  v2 = (unsigned int)(MEMORY[0x11201080] & MEMORY[0x11201084]) >> 16;
  MEMORY[0x11201080] &= MEMORY[0x11201084];
  if ( (v0 & 4) != 0 )
  {
    MEMORY[0x1029BC]();
    v1 = 0;
    v2 = 0;
  }
  if ( v1 | v2 )
  {
    if ( v1 << 31 )
    {
      MEMORY[0x1029C8]();
      v1 &= ~1u;
    }
    if ( v1 )
    {
      for ( i = 1; i <= 4; ++i )
      {
        if ( ((1 << i) & v1) != 0 )
        {
          v4 = *(void (**)(void))(4 * (i - 1) + 0x1029CC);
          if ( v4 )
            v4();
        }
      }
    }
    if ( v2 )
    {
      for ( j = 1; j <= 3; ++j )
      {
        if ( ((1 << j) & v2) != 0 && (*(_DWORD *)(16 * (j - 1) + 0x11201210) & 0x10000) != 0 )
        {
          v6 = *(void (**)(void))(4 * (j - 1) + 0x1029DC);
          if ( v6 )
            v6();
        }
      }
    }
  }
  JUMPOUT(0x50E0);
}


// ==================== sub_55F6 @0x55F6 size=6 ====================
int sub_55F6()
{
  return MEMORY[0x102A00];
}


// ==================== nullsub_15 @0x5604 size=2 ====================
void nullsub_15()
{
  ;
}


// ==================== nullsub_16 @0x5606 size=2 ====================
void nullsub_16()
{
  ;
}


// ==================== sub_5608 @0x5608 size=28 ====================
int __fastcall sub_5608(int result)
{
  if ( result == 1 )
  {
    MEMORY[0x10006000] |= 0xB160001u;
    MEMORY[0x10006390] &= 0xFFFFFE00;
    return 268460032;
  }
  return result;
}


// ==================== sub_562C @0x562C size=26 ====================
int __fastcall sub_562C(int result, int a2, int a3, int a4)
{
  char v4; // r5
  _DWORD *v5; // r4

  v4 = MEMORY[0x1027A8];
  v5 = (_DWORD *)(16 * MEMORY[0x1027A8] + 1059332);
  *v5 = result;
  v5[1] = a2;
  v5[2] = a3;
  v5[3] = a4;
  MEMORY[0x1027A8] = v4 + 1;
  return result;
}


// ==================== sub_5646 @0x5646 size=20 ====================
int __fastcall sub_5646(char a1, char a2, char a3, __int16 a4)
{
  MEMORY[0x1027AA] = a1;
  MEMORY[0x1027AB] = a2;
  MEMORY[0x1027AC] = a3;
  MEMORY[0x1027AE] = a4;
  MEMORY[0x1027B0] = 1;
  return 1;
}


// ==================== sub_565A @0x565A size=8 ====================
int sub_565A()
{
  MEMORY[0x1027A8] = 0;
  return 0;
}


// ==================== sub_5662 @0x5662 size=10 ====================
int sub_5662()
{
  MEMORY[0x1027B0] = 0;
  return 0;
}


// ==================== sub_566C @0x566C size=20 ====================
int __fastcall sub_566C(_BYTE *a1)
{
  ++MEMORY[0x1052CA];
  *a1 = 3;
  return 1069628;
}


// ==================== sub_5680 @0x5680 size=32 ====================
int __fastcall sub_5680(_BYTE *a1)
{
  *a1 = ++MEMORY[0x1052C8];
  return 36 * (MEMORY[0x1052C8] - 1) + 1069448;
}


// ==================== sub_56A0 @0x56A0 size=34 ====================
int __fastcall sub_56A0(_BYTE *a1)
{
  *a1 = ++MEMORY[0x1052C9];
  return 36 * (MEMORY[0x1052C9] - 1) + 1069520;
}


// ==================== sub_56C2 @0x56C2 size=38 ====================
int __fastcall sub_56C2(_BYTE *a1)
{
  *a1 = MEMORY[0x1052CB]++;
  return 52 * (MEMORY[0x1052CB] - 1) + 1069292;
}


// ==================== sub_56E8 @0x56E8 size=34 ====================
int __fastcall sub_56E8(int a1)
{
  ++MEMORY[0x1052CC];
  *(_DWORD *)(4 * (MEMORY[0x1052CC] - 1) + 0x105260) = a1;
  return (unsigned __int8)(MEMORY[0x1052CC] - 1);
}


// ==================== sub_570A @0x570A size=146 ====================
int __fastcall sub_570A(int a1)
{
  unsigned int i; // r4
  void (__fastcall *v3)(int); // r1
  int v4; // r4
  unsigned int j; // r6
  unsigned int k; // r5
  int result; // r0

  for ( i = 0; i < MEMORY[0x1027A8]; ++i )
  {
    v3 = *(void (__fastcall **)(int))(16 * i + 0x102A10);
    if ( v3 )
      v3(a1);
  }
  mem_copy_bytes(MEMORY[0x1052A0], 1069280, 9);
  v4 = 9;
  for ( j = 0; ; ++j )
  {
    result = MEMORY[0x1052CB];
    if ( MEMORY[0x1052CB] <= j )
      break;
    mem_copy_bytes(MEMORY[0x1052A0] + v4, 52 * j + 1069302, *(unsigned __int16 *)(52 * j + 0x1050F4));
    v4 += *(unsigned __int16 *)(52 * j + 0x1050F4);
    for ( k = 0; *(unsigned __int8 *)(52 * j + 0x1050FA) > k; ++k )
    {
      mem_copy_bytes(
        MEMORY[0x1052A0] + v4,
        *(_DWORD *)(52 * j + 0x1050C8 + 4 * k + 76),
        *(unsigned __int16 *)(*(_DWORD *)(52 * j + 0x1050C8 + 4 * k + 76) + 12));
      v4 += *(unsigned __int16 *)(*(_DWORD *)(52 * j + 0x1050C8 + 4 * k + 76) + 12);
    }
  }
  return result;
}


// ==================== sub_579C @0x579C size=18 ====================
int sub_579C()
{
  MEMORY[0x1052C8] = 0;
  MEMORY[0x1052C9] = 0;
  MEMORY[0x1052CA] = 0;
  MEMORY[0x1052CB] = 0;
  MEMORY[0x1052CC] = 0;
  return 1069768;
}


// ==================== sub_57AE @0x57AE size=228 ====================
int __fastcall sub_57AE(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  unsigned int i; // r5
  unsigned int j; // r1
  unsigned int k; // r0
  int v9; // [sp+0h] [bp-8h] BYREF
  int v10; // [sp+4h] [bp-4h] BYREF

  v9 = a3;
  v10 = a4;
  v4 = 0;
  sub_579C();
  sub_56E8((int)&dword_12290[4]);
  for ( i = 0; i < MEMORY[0x1027A8]; ++i )
    (*(void (__fastcall **)(_DWORD))(16 * i + 0x102A08))(*(_DWORD *)(16 * i + 0x102A04));
  MEMORY[0x1050C8] = 18;
  MEMORY[0x1050C9] = 1;
  MEMORY[0x1050CA] = 272;
  MEMORY[0x1050CC] = MEMORY[0x1027AA];
  MEMORY[0x1050CD] = MEMORY[0x1027AB];
  MEMORY[0x1050CE] = MEMORY[0x1027AC];
  MEMORY[0x1050CF] = 64;
  if ( sub_42E2(&v9, &v10) == 1 )
  {
    MEMORY[0x1050D0] = v9;
    MEMORY[0x1050D2] = v10;
  }
  else
  {
    MEMORY[0x1050D0] = IDAW_MEM[0x1052D0];
    MEMORY[0x1050D2] = MEMORY[0x1027AE];
  }
  MEMORY[0x1050D4] = 256;
  MEMORY[0x1050D6] = 0;
  MEMORY[0x1050D7] = 0;
  MEMORY[0x1050D8] = 0;
  MEMORY[0x1050D9] = 1;
  MEMORY[0x1050E0] = 9;
  MEMORY[0x1050E1] = 2;
  MEMORY[0x1050E4] = MEMORY[0x1052CB];
  MEMORY[0x1050E5] = 1;
  MEMORY[0x1050E6] = 0;
  MEMORY[0x1050E7] = 0x80;
  MEMORY[0x1050E8] = 0;
  for ( j = 0; MEMORY[0x1052CB] > j; ++j )
  {
    v4 += *(unsigned __int16 *)(52 * j + 0x1050F4);
    for ( k = 0; *(unsigned __int8 *)(52 * j + 0x1050FA) > k; ++k )
      v4 += *(unsigned __int16 *)(*(_DWORD *)(52 * j + 0x1050C8 + 4 * k + 76) + 12);
  }
  MEMORY[0x1050E2] = v4 + 9;
  MEMORY[0x1052A0] = 1059380;
  return sub_570A(0);
}


// ==================== sub_5892 @0x5892 size=32 ====================
int sub_5892()
{
  unsigned int i; // r4
  void (*v1)(void); // r0
  int result; // r0

  for ( i = 0; ; i = (unsigned __int8)(i + 1) )
  {
    result = MEMORY[0x1027A8];
    if ( i >= MEMORY[0x1027A8] )
      break;
    v1 = *(void (**)(void))(16 * i + 0x102A0C);
    if ( v1 )
      v1();
  }
  return result;
}


// ==================== sub_58C8 @0x58C8 size=18 ====================
BOOL sub_58C8()
{
  return sub_416A();
}


// ==================== sub_58DA @0x58DA size=20 ====================
int sub_58DA()
{
  int v0; // r0

  v0 = sub_44C0();
  nullsub_3(v0);
  return sub_4EEC();
}


// ==================== sub_58EE @0x58EE size=146 ====================
int __fastcall sub_58EE(int a1)
{
  int v2; // r4
  int (**v3)(void); // r0
  _UNKNOWN **v4; // r0

  v2 = MEMORY[0x1027B4];
  v3 = (int (**)(void))sub_4502();
  MEMORY[0x1052D0] = (*v3)();
  v4 = sub_4502();
  MEMORY[0x102AD8] = ((int (*)(void))v4[1])();
  if ( a1 != 1 )
    return sub_4BDC(1, 1, 0);
  sub_562C((int)"ACM COMMU.", (int)sub_5CCE, (int)sub_5DD8, (int)sub_5DE2);
  sub_562C((int)"ACM DATA", (int)sub_5E4A, (int)sub_5F1E, (int)sub_5F58);
  if ( v2 == 1 )
    sub_562C((int)"ACM VIRTUALCOM", (int)sub_5FA6, (int)sub_6090, (int)nullsub_17);
  sub_5646(2, 0, 0, IDAW_MEM[0x102AD8]);
  return sub_4BDC(1, 1, 1);
}


// ==================== sub_5980 @0x5980 size=152 ====================
int sub_5980()
{
  int v0; // r4

  v0 = 0;
  MEMORY[0x1027B4] = sub_42B8();
  MEMORY[0x1052D4] = 0;
  MEMORY[0x1054D8] = 0;
  MEMORY[0x1052AD] = 0;
  sub_C02C();
  sub_58EE(1);
  while ( sub_58C8() && MEMORY[0x1052AD] != 3 )
  {
    ++v0;
    usb_poll_events();
    if ( v0 == 5000 )
    {
      sub_C02C();
      v0 = 0;
    }
  }
  sub_C02C();
  if ( MEMORY[0x1052AD] != 3 )
    return 0;
  MEMORY[0x102AAC] = 115200;
  MEMORY[0x102AB0] = 0;
  MEMORY[0x102AB1] = 0;
  MEMORY[0x102AB2] = 8;
  MEMORY[0x102A90] = 1;
  sub_51B6(IDAW_MEM[0x102AA0]);
  sub_51CA(IDAW_MEM[0x102AA4]);
  return 1;
}


// ==================== sub_5A18 @0x5A18 size=36 ====================
int sub_5A18()
{
  int v0; // r0
  int v1; // r0

  v0 = usb_debug_event(12, 0);
  sub_60D6(v0);
  sub_565A();
  sub_5662();
  v1 = sub_4EEC();
  return nullsub_4(v1);
}


// ==================== sub_5A3C @0x5A3C size=4 ====================
int sub_5A3C()
{
  return 0;
}


// ==================== usb_poll_events_alias (sub_5A40) @0x5A40 size=4 ====================
// attributes: thunk
void usb_poll_events_alias()
{
  usb_poll_events();
}


// ==================== usb_init_endpoints (sub_5A44) @0x5A44 size=44 ====================
int usb_init_endpoints()
{
  int v0; // r0

  v0 = usb_ep_get_pending((unsigned __int8)IDAW_MEM[0x102AA4]);
  if ( v0 )
  {
    sub_520E((unsigned __int8)IDAW_MEM[0x102AA4], (unsigned __int16)v0, 1070300);
    sub_54A2((unsigned __int8)IDAW_MEM[0x102AA4]);
  }
  MEMORY[0x1054D8] = 0;
  return 0;
}


// ==================== usb_tx_put_byte (sub_5A70) @0x5A70 size=108 ====================
int __fastcall usb_tx_put_byte(char a1)
{
  int v2; // r4
  int result; // r0
  int v4; // r1
  int v5; // r7

  if ( usb_is_high_speed() )
    v2 = 512;
  else
    v2 = 64;
  result = MEMORY[0x1052AD];
  if ( MEMORY[0x1052AD] == 3 )
  {
    v4 = MEMORY[0x1052D4];
    *(_BYTE *)(MEMORY[0x1052D4] + 1069784) = a1;
    MEMORY[0x1052D4] = v4 + 1;
    usb_debug_event(9, v4 + 1);
    result = MEMORY[0x1052D4];
    if ( MEMORY[0x1052D4] == v2 )
    {
      v5 = (unsigned __int8)IDAW_MEM[0x102AA0];
      MEMORY[0x1027BC] = 0;
      sub_5212(v5, (unsigned __int16)v2, (unsigned __int8 *)0x1052D8);
      usb_ep_kick(v5);
      while ( 1 )
      {
        result = MEMORY[0x1027BC];
        if ( MEMORY[0x1027BC] )
          break;
        usb_poll_events();
      }
      MEMORY[0x1052D4] = 0;
    }
  }
  return result;
}


// ==================== usb_tx_flush (sub_5ADC) @0x5ADC size=74 ====================
void usb_tx_flush()
{
  int v0; // r5

  if ( MEMORY[0x1052AD] == 3 && MEMORY[0x1052D4] )
  {
    usb_debug_event(10, MEMORY[0x1052D4]);
    v0 = (unsigned __int8)IDAW_MEM[0x102AA0];
    MEMORY[0x1027BC] = 0;
    sub_5212(v0, MEMORY[0x1052D4], (unsigned __int8 *)0x1052D8);
    usb_ep_kick(v0);
    while ( !MEMORY[0x1027BC] )
      usb_poll_events();
    MEMORY[0x1052D4] = 0;
  }
  JUMPOUT(0x5AD8);
}


// ==================== usb_rx_get_byte (sub_5B26) @0x5B26 size=44 ====================
int __fastcall usb_rx_get_byte(_BYTE *a1)
{
  int result; // r0
  int v3; // r0
  int v4; // r1

  result = 0;
  if ( MEMORY[0x1054D8] )
  {
    v3 = MEMORY[0x1027B8]++;
    v4 = MEMORY[0x1027B8];
    *a1 = *(_BYTE *)(v3 + 1070300);
    result = 1;
    if ( MEMORY[0x1054D8] == v4 )
    {
      MEMORY[0x1054D8] = 0;
      MEMORY[0x1027B8] = 0;
    }
  }
  return result;
}


// ==================== sub_5B52 @0x5B52 size=40 ====================
int sub_5B52()
{
  int v1; // [sp+0h] [bp-4h] BYREF

  v1 = 0;
  while ( !MEMORY[0x1054D8] )
    usb_poll_events();
  usb_debug_event(11, MEMORY[0x1054D8]);
  usb_rx_get_byte(&v1);
  return (unsigned __int8)v1;
}


// ==================== usb_rx_poll_byte (sub_5B7A) @0x5B7A size=16 ====================
int __fastcall usb_rx_poll_byte(_BYTE *a1)
{
  usb_poll_events();
  return usb_rx_get_byte(a1);
}


// ==================== sub_5BF4 @0x5BF4 size=20 ====================
int __fastcall sub_5BF4(int a1, int a2)
{
  int result; // r0

  *(_DWORD *)a2 = *(_DWORD *)a1;
  *(_BYTE *)(a2 + 5) = *(_BYTE *)(a1 + 4) + 1;
  *(_BYTE *)(a2 + 6) = *(_BYTE *)(a1 + 5);
  result = *(unsigned __int8 *)(a1 + 6);
  *(_BYTE *)(a2 + 4) = result;
  return result;
}


// ==================== sub_5C08 @0x5C08 size=34 ====================
int __fastcall sub_5C08(int a1, int a2, int a3, int a4)
{
  int v5; // [sp+0h] [bp-4h] BYREF

  v5 = a4;
  if ( MEMORY[0x102AD4] == 255 )
  {
    MEMORY[0x102ACC] = sub_56C2(&v5);
    MEMORY[0x102AD4] = v5;
  }
  return MEMORY[0x102AD4];
}


// ==================== sub_5C2A @0x5C2A size=58 ====================
unsigned int sub_5C2A()
{
  unsigned int result; // r0

  result = sub_5432();
  if ( result )
  {
    sub_520E(0, (unsigned __int16)result, 1059500);
    sub_5BF4(1059500, 1059476);
    MEMORY[0x1052B3] = 0;
    return sub_538E(6, 0, 1);
  }
  return result;
}


// ==================== sub_5C64 @0x5C64 size=106 ====================
unsigned int __fastcall sub_5C64(int a1, int a2)
{
  int v2; // r4
  int v3; // r2

  v2 = 0;
  v3 = *(unsigned __int8 *)(a2 + 1);
  if ( v3 == 32 )
  {
    sub_45CC((int)sub_5C2A);
    MEMORY[0x1052B3] = 1;
  }
  else
  {
    if ( *(unsigned __int8 *)(a2 + 1) <= 0x20u )
    {
LABEL_6:
      v2 = 1;
      goto LABEL_7;
    }
    if ( v3 != 33 )
    {
      if ( v3 == 34 || v3 == 35 )
        goto LABEL_7;
      goto LABEL_6;
    }
    sub_45D6(a1, a2, 1059500, 7);
  }
LABEL_7:
  if ( !MEMORY[0x1052B3] )
    return sub_538E(0, v2, 1);
  if ( MEMORY[0x1052B3] == 1 )
    return sub_538E(2, v2, 0);
  return sub_538E(1, v2, 0);
}


// ==================== sub_5CCE @0x5CCE size=266 ====================
int __fastcall sub_5CCE(int a1, int a2, int a3, int a4)
{
  int v5; // r4
  int v6; // r0
  int v7; // r1
  char v8; // r0
  int v9; // r2
  int v10; // r3
  int v11; // r1
  int v12; // r0
  char v13; // r0
  _BYTE *v14; // r0
  int result; // r0
  char v16; // r1
  int v17; // [sp+0h] [bp-8h] BYREF
  int v18; // [sp+4h] [bp-4h] BYREF

  v17 = a3;
  v18 = a4;
  v5 = MEMORY[0x1027B4];
  MEMORY[0x102AC8] = sub_56C2(&v17);
  v6 = sub_566C(&v18);
  MEMORY[0x102AB4] = v6;
  v7 = MEMORY[0x102AC8];
  IDAW_MEM[0x102AC8] = a1;
  *(_WORD *)(v7 + 8) = 28;
  *(_WORD *)(v6 + 12) = 7;
  *(_DWORD *)(v7 + 40) = v6;
  *(_DWORD *)(v7 + 4) = sub_5C64;
  *(_BYTE *)(v7 + 10) = 9;
  *(_BYTE *)(v7 + 11) = 4;
  *(_BYTE *)(v7 + 12) = v17;
  *(_BYTE *)(v7 + 13) = 0;
  *(_BYTE *)(v7 + 14) = 1;
  *(_BYTE *)(v7 + 15) = 2;
  *(_BYTE *)(v7 + 16) = 2;
  *(_BYTE *)(v7 + 17) = 1;
  v8 = sub_56E8(*(_DWORD *)(MEMORY[0x102AD8] + 4));
  v11 = MEMORY[0x102AC8];
  *(_BYTE *)(MEMORY[0x102AC8] + 18) = v8;
  *(_BYTE *)(v11 + 19) = 5;
  *(_BYTE *)(v11 + 20) = 36;
  *(_BYTE *)(v11 + 21) = 0;
  *(_WORD *)(v11 + 22) = 272;
  *(_BYTE *)(v11 + 24) = 4;
  *(_BYTE *)(v11 + 25) = 36;
  *(_BYTE *)(v11 + 26) = 2;
  *(_BYTE *)(v11 + 27) = 15;
  *(_BYTE *)(v11 + 28) = 5;
  *(_BYTE *)(v11 + 29) = 36;
  *(_BYTE *)(v11 + 30) = 6;
  v12 = (unsigned __int8)v17;
  *(_BYTE *)(v11 + 31) = v17;
  if ( v5 == 1 )
  {
    *(_BYTE *)(v11 + 32) = 1;
  }
  else
  {
    v13 = sub_5C08(v12, v11, v9, v10);
    v11 = MEMORY[0x102AC8];
    *(_BYTE *)(MEMORY[0x102AC8] + 32) = v13;
  }
  v14 = (_BYTE *)MEMORY[0x102AC8];
  *(_BYTE *)(MEMORY[0x102AC8] + 33) = 5;
  v14[34] = 36;
  v14[35] = 1;
  v14[36] = 3;
  if ( v5 == 1 )
    v14[37] = 1;
  else
    *(_BYTE *)(MEMORY[0x102AC8] + 37) = sub_5C08((int)v14, v11, v9, v10);
  sub_4CA8(4, (unsigned __int8)v18, 0);
  result = MEMORY[0x102AB4];
  *(_DWORD *)(MEMORY[0x102AB4] + 16) = 0;
  *(_BYTE *)result = 7;
  *(_BYTE *)(result + 1) = 5;
  v16 = v18;
  *(_BYTE *)(result + 2) = v18 | 0x80;
  *(_BYTE *)(result + 3) = 3;
  *(_BYTE *)(result + 6) = 1;
  *(_BYTE *)(result + 20) = v16;
  *(_DWORD *)(result + 28) = -1;
  return result;
}


// ==================== sub_5DD8 @0x5DD8 size=10 ====================
int sub_5DD8()
{
  MEMORY[0x102AA8] = MEMORY[0x102AB4] + 20;
  return 1059488;
}


// ==================== sub_5DE2 @0x5DE2 size=14 ====================
int sub_5DE2()
{
  int result; // r0

  result = MEMORY[0x102AB4];
  *(_BYTE *)(MEMORY[0x102AB4] + 4) = 64;
  *(_BYTE *)(result + 5) = 0;
  return result;
}


// ==================== sub_5DF0 @0x5DF0 size=16 ====================
int sub_5DF0()
{
  MEMORY[0x102AA4] = MEMORY[0x102ABC] + 20;
  MEMORY[0x1054D8] = 0;
  return 0;
}


// ==================== sub_5E00 @0x5E00 size=50 ====================
int sub_5E00()
{
  int result; // r0

  result = MEMORY[0x1054D8];
  if ( !MEMORY[0x1054D8] )
  {
    MEMORY[0x1054D8] = usb_ep_get_pending((unsigned __int8)IDAW_MEM[0x102AA4]);
    sub_520E((unsigned __int8)IDAW_MEM[0x102AA4], MEMORY[0x1054D8], 1070300);
    return sub_54A2((unsigned __int8)IDAW_MEM[0x102AA4]);
  }
  return result;
}


// ==================== sub_5E32 @0x5E32 size=16 ====================
int sub_5E32()
{
  MEMORY[0x102AA0] = MEMORY[0x102AB8] + 20;
  MEMORY[0x1052D4] = 0;
  return 0;
}


// ==================== sub_5E42 @0x5E42 size=8 ====================
int sub_5E42()
{
  MEMORY[0x1027BC] = 1;
  return 1;
}


// ==================== sub_5E4A @0x5E4A size=212 ====================
_BYTE *__fastcall sub_5E4A(int a1, int a2, int a3, int a4)
{
  int v5; // r8
  int v6; // r0
  int v7; // r1
  int v8; // r2
  _BYTE *result; // r0
  int v10; // r1
  char v11; // r2
  _BYTE v12[4]; // [sp+0h] [bp-Ch] BYREF
  int v13; // [sp+4h] [bp-8h] BYREF
  int v14; // [sp+8h] [bp-4h] BYREF

  v13 = a3;
  v14 = a4;
  v5 = MEMORY[0x1027B4];
  if ( MEMORY[0x102AD4] == 255 )
  {
    MEMORY[0x102ACC] = sub_56C2(v12);
    MEMORY[0x102AD4] = v12[0];
  }
  MEMORY[0x102AB8] = sub_5680(&v14);
  v6 = sub_56A0(&v13);
  MEMORY[0x102ABC] = v6;
  v7 = MEMORY[0x102ACC];
  IDAW_MEM[0x102ACC] = a1;
  *(_WORD *)(v7 + 8) = 9;
  v8 = MEMORY[0x102AB8];
  *(_WORD *)(MEMORY[0x102AB8] + 12) = 7;
  *(_WORD *)(v6 + 12) = 7;
  *(_DWORD *)(v7 + 40) = v8;
  *(_DWORD *)(v7 + 44) = v6;
  *(_DWORD *)(v7 + 4) = 0;
  *(_BYTE *)(v7 + 10) = 9;
  *(_BYTE *)(v7 + 11) = 4;
  *(_BYTE *)(v7 + 12) = MEMORY[0x102AD4];
  *(_BYTE *)(v7 + 13) = 0;
  *(_BYTE *)(v7 + 14) = 2;
  *(_BYTE *)(v7 + 15) = 10;
  if ( v5 == 1 )
    *(_BYTE *)(v7 + 16) = -1;
  else
    *(_BYTE *)(v7 + 16) = 0;
  *(_BYTE *)(v7 + 17) = 0;
  *(_BYTE *)(MEMORY[0x102ACC] + 18) = sub_56E8(*(_DWORD *)(MEMORY[0x102AD8] + 12));
  sub_4CA8(4, (unsigned __int8)v14, (int)sub_5E42);
  *(_DWORD *)(MEMORY[0x102AB8] + 16) = sub_5E32;
  sub_4CA8(5, (unsigned __int8)v13, (int)sub_5E00);
  result = (_BYTE *)MEMORY[0x102ABC];
  *(_DWORD *)(MEMORY[0x102ABC] + 16) = sub_5DF0;
  v10 = MEMORY[0x102AB8];
  IDAW_MEM[0x102AB8] = 7;
  *(_BYTE *)(v10 + 1) = 5;
  v11 = v14;
  *(_BYTE *)(v10 + 2) = v14 | 0x80;
  *(_BYTE *)(v10 + 3) = 2;
  *(_BYTE *)(v10 + 6) = 0;
  *(_BYTE *)(v10 + 20) = v11;
  *(_DWORD *)(v10 + 28) = -1;
  *result = 7;
  result[1] = 5;
  LOBYTE(v10) = v13;
  result[2] = v13;
  result[3] = 2;
  result[6] = 0;
  result[20] = v10;
  return result;
}


// ==================== sub_5F1E @0x5F1E size=58 ====================
int sub_5F1E()
{
  int result; // r0

  result = MEMORY[0x1027B4];
  if ( !MEMORY[0x1027B4] )
  {
    MEMORY[0x102AA0] = MEMORY[0x102AB8] + 20;
    MEMORY[0x102AA4] = MEMORY[0x102ABC] + 20;
    sub_51B6(*(_BYTE *)(MEMORY[0x102AB8] + 20));
    return sub_51CA(IDAW_MEM[0x102AA4]);
  }
  return result;
}


// ==================== sub_5F58 @0x5F58 size=46 ====================
int sub_5F58()
{
  int v0; // r0
  int result; // r0
  int v2; // r0

  if ( usb_is_high_speed() )
  {
    v2 = MEMORY[0x102AB8];
    *(_BYTE *)(MEMORY[0x102AB8] + 4) = 0;
    *(_BYTE *)(v2 + 5) = 2;
    result = MEMORY[0x102ABC];
    *(_BYTE *)(MEMORY[0x102ABC] + 4) = 0;
    *(_BYTE *)(result + 5) = 2;
  }
  else
  {
    v0 = MEMORY[0x102AB8];
    *(_BYTE *)(MEMORY[0x102AB8] + 4) = 64;
    *(_BYTE *)(v0 + 5) = 0;
    result = MEMORY[0x102ABC];
    *(_BYTE *)(MEMORY[0x102ABC] + 4) = 64;
    *(_BYTE *)(result + 5) = 0;
  }
  return result;
}


// ==================== sub_5F86 @0x5F86 size=16 ====================
int sub_5F86()
{
  MEMORY[0x102AA4] = MEMORY[0x102AC4] + 20;
  MEMORY[0x1054D8] = 0;
  return 0;
}


// ==================== sub_5F96 @0x5F96 size=16 ====================
int sub_5F96()
{
  MEMORY[0x102AA0] = MEMORY[0x102AC0] + 20;
  MEMORY[0x1052D4] = 0;
  return 0;
}


// ==================== sub_5FA6 @0x5FA6 size=234 ====================
_BYTE *__fastcall sub_5FA6(int a1, int a2, int a3, int a4)
{
  int v5; // r0
  int v6; // r1
  int v7; // r2
  int v8; // r0
  char v9; // r1
  _BYTE *result; // r0
  char v11; // r1
  _BYTE v12[4]; // [sp+0h] [bp-Ch] BYREF
  int v13; // [sp+4h] [bp-8h] BYREF
  int v14; // [sp+8h] [bp-4h] BYREF

  v13 = a3;
  v14 = a4;
  MEMORY[0x102AD0] = sub_56C2(v12);
  MEMORY[0x102AC0] = sub_5680(&v14);
  v5 = sub_56A0(&v13);
  MEMORY[0x102AC4] = v5;
  v6 = MEMORY[0x102AD0];
  IDAW_MEM[0x102AD0] = a1;
  *(_WORD *)(v6 + 8) = 9;
  v7 = MEMORY[0x102AC0];
  *(_WORD *)(MEMORY[0x102AC0] + 12) = 7;
  *(_WORD *)(v5 + 12) = 7;
  *(_DWORD *)(v6 + 40) = v7;
  *(_DWORD *)(v6 + 44) = v5;
  *(_DWORD *)(v6 + 4) = 0;
  *(_BYTE *)(v6 + 10) = 9;
  *(_BYTE *)(v6 + 11) = 4;
  *(_BYTE *)(v6 + 12) = v12[0];
  *(_BYTE *)(v6 + 13) = 0;
  *(_BYTE *)(v6 + 14) = 2;
  *(_BYTE *)(v6 + 15) = -1;
  *(_BYTE *)(v6 + 16) = -1;
  *(_BYTE *)(v6 + 17) = 0;
  *(_BYTE *)(MEMORY[0x102AD0] + 18) = sub_56E8(*(_DWORD *)(MEMORY[0x102AD8] + 12));
  sub_4CA8(4, (unsigned __int8)v14, (int)sub_5E42);
  *(_DWORD *)(MEMORY[0x102AB8] + 16) = sub_5F96;
  sub_4CA8(5, (unsigned __int8)v13, (int)sub_5E00);
  *(_DWORD *)(MEMORY[0x102ABC] + 16) = sub_5F86;
  v8 = MEMORY[0x102AC0];
  IDAW_MEM[0x102AC0] = 7;
  *(_BYTE *)(v8 + 1) = 5;
  v9 = v14;
  *(_BYTE *)(v8 + 2) = v14 | 0x80;
  *(_BYTE *)(v8 + 3) = 2;
  *(_BYTE *)(v8 + 4) = 0;
  *(_BYTE *)(v8 + 5) = 2;
  *(_BYTE *)(v8 + 6) = 0;
  *(_BYTE *)(v8 + 20) = v9;
  *(_DWORD *)(v8 + 28) = -1;
  result = (_BYTE *)MEMORY[0x102AC4];
  IDAW_MEM[0x102AC4] = 7;
  result[1] = 5;
  v11 = v13;
  result[2] = v13;
  result[3] = 2;
  result[4] = 0;
  result[5] = 2;
  result[6] = 0;
  result[20] = v11;
  return result;
}


// ==================== sub_6090 @0x6090 size=50 ====================
int sub_6090()
{
  MEMORY[0x102AA0] = MEMORY[0x102AC0] + 20;
  MEMORY[0x102AA4] = MEMORY[0x102AC4] + 20;
  sub_51B6(*(_BYTE *)(MEMORY[0x102AC0] + 20));
  return sub_51CA(IDAW_MEM[0x102AA4]);
}


// ==================== nullsub_17 @0x60C2 size=2 ====================
void nullsub_17()
{
  ;
}


// ==================== sub_60C4 @0x60C4 size=18 ====================
int sub_60C4()
{
  MEMORY[0x102AA0] = 0;
  MEMORY[0x102AA4] = 0;
  MEMORY[0x102AA8] = 0;
  MEMORY[0x102AD4] = -1;
  return 1059488;
}


// ==================== sub_60D6 @0x60D6 size=16 ====================
int sub_60D6()
{
  MEMORY[0x102AA0] = 0;
  MEMORY[0x102AA4] = 0;
  MEMORY[0x102AA8] = 0;
  MEMORY[0x102AD4] = 0;
  return 1059488;
}


// ==================== nullsub_3 @0x60FC size=2 ====================
void nullsub_3()
{
  ;
}


// ==================== nullsub_4 @0x60FE size=2 ====================
void nullsub_4()
{
  ;
}


// ==================== sub_6100 @0x6100 size=26 ====================
int sub_6100()
{
  int v0; // r0

  v0 = MEMORY[0x102874];
  if ( MEMORY[0x102874] == 1 || MEMORY[0x102874] == 3 )
    v0 = sub_81DA();
  return sub_81CE(v0);
}


// ==================== sub_611A @0x611A size=14 ====================
int sub_611A()
{
  if ( MEMORY[0x102B0C] )
    return MEMORY[0x102B14];
  else
    return 0;
}


// ==================== sub_6128 @0x6128 size=22 ====================
int sub_6128()
{
  int v0; // r2

  sub_8430();
  if ( (sub_611A() & 8) != 0 )
    return 0;
  return v0;
}


// ==================== sub_613E @0x613E size=36 ====================
int sub_613E()
{
  int v0; // r2

  efuse_get_bit3();
  if ( sub_611A() << 31 )
    v0 = 0;
  if ( MEMORY[0x1027C4] && *(_DWORD *)(MEMORY[0x1027C4] + 40) << 31 )
    return 0;
  return v0;
}


// ==================== sub_6162 @0x6162 size=54 ====================
int sub_6162()
{
  int v0; // r4
  int v2; // r0

  v0 = sub_843A();
  if ( MEMORY[0x1027C0] )
  {
    v0 = MEMORY[0x1027C0];
  }
  else
  {
    v2 = brom_get_descriptor(8);
    if ( v2 && *(_DWORD *)(v2 + 44) == 1111769409 )
    {
      v0 = 1;
      MEMORY[0x1027C0] = 1;
    }
  }
  if ( (sub_611A() & 2) != 0 )
    return 0;
  return v0;
}


// ==================== sub_6198 @0x6198 size=18 ====================
BOOL sub_6198()
{
  return (sub_611A() & 8) != 0;
}


// ==================== get_brom_key_table_entry (sub_61AA) @0x61AA size=22 ====================
char *get_brom_key_table_entry()
{
  return (char *)&unk_123CC + 524 * efuse_get_key_slot();
}


// ==================== sub_61C0 @0x61C0 size=22 ====================
int *sub_61C0()
{
  return &dword_12BFC[131 * sub_848E()];
}


// ==================== auth_hash_key_region (sub_61D6) @0x61D6 size=52 ====================
int __fastcall auth_hash_key_region(int a1, int a2)
{
  int v3; // r0
  _DWORD v5[2]; // [sp+4h] [bp-24h] BYREF
  _BYTE v6[28]; // [sp+Ch] [bp-1Ch] BYREF

  v5[0] = a1;
  v5[1] = 524;
  v3 = sub_864A();
  mem_copy_bytes(v6, v3, 28);
  return sub_9064(1070920, 1070936, v5, a2, 0);
}


// ==================== auth_compare_key_hash (sub_620A) @0x620A size=62 ====================
int __fastcall auth_compare_key_hash(int a1)
{
  unsigned int v2; // r4
  int v3; // r0
  _BYTE v5[32]; // [sp+0h] [bp-40h] BYREF
  _BYTE v6[32]; // [sp+20h] [bp-20h] BYREF

  efuse_read_pubk_hash(v6);
  v2 = auth_hash_key_region(a1, (int)v5);
  if ( v2 < 0xFF )
  {
    v3 = sub_8696();
    if ( mem_cmp(v6, v5, v3) )
      return 28681;
  }
  else
  {
    MEMORY[0x10287C] = v2;
    return 28682;
  }
  return v2;
}


// ==================== auth_check_key_hash (sub_6248) @0x6248 size=32 ====================
int __fastcall auth_check_key_hash(int a1, int a2)
{
  if ( sub_84A2() )
    return sub_76E6(a1, a2);
  else
    return auth_compare_key_hash(a1);
}


// ==================== sub_6268 @0x6268 size=128 ====================
int __fastcall sub_6268(int a1, int a2, int a3, int a4, int a5, int a6, int a7)
{
  int v11; // r4
  _DWORD v13[3]; // [sp+0h] [bp-30h] BYREF
  char v14; // [sp+Ch] [bp-24h]
  _DWORD v15[7]; // [sp+10h] [bp-20h] BYREF
  int v16; // [sp+2Ch] [bp-4h]

  mem_set_bytes(v15, 0, 32);
  v15[0] = a1;
  v15[1] = a2;
  v15[2] = v13;
  v13[1] = a3;
  v13[2] = 16;
  v14 = 1;
  v15[3] = 16;
  v15[4] = a5;
  v15[5] = a6;
  v15[6] = a7;
  v16 = 3;
  if ( !sub_84C2() )
  {
    v16 |= 4u;
    if ( sub_84CC() )
      v16 |= 8u;
  }
  sub_8196(a4);
  v11 = sub_9448(1070920, 1070936, v15);
  sub_81AE();
  return v11;
}


// ==================== nullsub_5 @0x62E8 size=2 ====================
void nullsub_5()
{
  ;
}


// ==================== sub_62EA @0x62EA size=8 ====================
int sub_62EA()
{
  return 2104912;
}


// ==================== sub_62F2 @0x62F2 size=80 ====================
int __fastcall sub_62F2(int a1)
{
  unsigned int v2; // r4

  usb_status_reset(2);
  mem_copy_bytes(a1, dword_122A8, 16);
  v2 = sub_6268(
         a1,
         16,
         (int)&dword_122A8[4],
         (int)&dword_122A8[8],
         (int)&dword_122A8[16],
         (int)&dword_122A8[20],
         (int)&dword_122A8[24]);
  if ( v2 >= 0xFF )
  {
    mem_set_bytes(a1, 0, 16);
    MEMORY[0x10287C] = v2;
    return 28684;
  }
  return v2;
}


// ==================== sub_6342 @0x6342 size=72 ====================
unsigned int sub_6342()
{
  int v0; // r0
  unsigned int result; // r0

  v0 = sub_62EA();
  sub_76B8(v0);
  nullsub_5();
  sub_85A8(1070920, 1074616, 256, trace_begin);
  sub_6100();
  result = sub_62F2(1059704);
  if ( result >= 0xFF )
  {
    usb_report_error((unsigned __int16)result, MEMORY[0x10287C]);
    return usb_status_reset(2);
  }
  return result;
}


// ==================== usb_install_callbacks (sub_638A) @0x638A size=26 ====================
int usb_install_callbacks()
{
  int result; // r0

  MEMORY[0x102880] = 0;
  result = sub_83EC();
  if ( result )
    return sub_8180();
  return result;
}


// ==================== sub_63A4 @0x63A4 size=126 ====================
unsigned int __fastcall sub_63A4(int a1)
{
  unsigned int result; // r0
  int v3; // r0
  int v4; // r0
  int v5; // r0

  result = time_get_ms_count(0x1F4u);
  if ( a1 != 1 )
  {
    if ( a1 )
      return result;
    return sub_7F6A(result);
  }
  if ( sub_83EC(result) )
    sub_8180();
  v3 = brom_get_descriptor(8);
  if ( v3 )
    v4 = sub_8196(v3 + 12);
  else
    v4 = sub_81AE();
  if ( !sub_84C2(v4) )
  {
    MEMORY[0x1000A008] |= 0x40000000u;
    time_get_tick();
    while ( MEMORY[0x1000A008] >= 0 && !time_wait_ticks() )
      ;
  }
  MEMORY[0x1000A00C] = 16;
  v5 = sub_81C2();
  result = sub_84F4(v5);
  if ( !result )
    return sub_7F6A(result);
  return result;
}


// ==================== sub_6422 @0x6422 size=24 ====================
int __fastcall sub_6422(int a1)
{
  int v1; // r4

  v1 = 0;
  if ( mem_cmp(1059704, a1, 16) )
    return 28683;
  return v1;
}


// ==================== auth_resolve_key_source (sub_643A) @0x643A size=64 ====================
int __fastcall auth_resolve_key_source(int a1, char **a2)
{
  unsigned int v3; // r4
  char *v4; // r6

  v3 = 0;
  *a2 = 0;
  if ( (*(_DWORD *)(a1 + 64) & 0x80) != 0 )
  {
    if ( efuse_get_bit17() )
      return 28795;
    else
      *a2 = get_brom_key_table_entry();
  }
  else
  {
    v4 = (char *)(a1 + 68);
    v3 = auth_check_key_hash(a1 + 68, 0);
    if ( v3 < 0xFF )
      *a2 = v4;
    else
      return 28688;
  }
  return v3;
}


// ==================== sub_647A @0x647A size=22 ====================
int __fastcall sub_647A(unsigned int a1)
{
  if ( a1 && a1 <= 0xA50 )
    return 0;
  else
    return 28687;
}


// ==================== auth_check_cert_type3_4 (sub_6490) @0x6490 size=52 ====================
int __fastcall auth_check_cert_type3_4(int a1, int a2)
{
  int result; // r0

  result = 0;
  if ( !a1 )
    return 32816;
  if ( (unsigned __int16)*(_DWORD *)(a1 + 8) != 840 )
    return 32817;
  if ( !a2 )
    return 32824;
  if ( (unsigned __int16)*(_DWORD *)(a2 + 8) != 316 )
    return 32825;
  return result;
}


// ==================== auth_check_cert_type3_4_v7 (sub_64C4) @0x64C4 size=138 ====================
int __fastcall auth_check_cert_type3_4_v7(int a1, int a2)
{
  int result; // r0

  result = 0;
  if ( !a1 )
    return 32816;
  if ( (unsigned __int16)*(_DWORD *)(a1 + 8) != 848 )
    return 32817;
  if ( !a2 )
    return 32824;
  if ( (unsigned __int16)*(_DWORD *)(a2 + 8) != 324 )
    return 32825;
  return result;
}


// ==================== auth_compare_with_key_table (sub_654E) @0x654E size=118 ====================
int __fastcall auth_compare_with_key_table(_DWORD *a1, _DWORD *a2)
{
  int v2; // r6
  int i; // r2
  char *v4; // r4
  int j; // r2
  char *v6; // r4
  unsigned int v7; // r3

  v2 = a2[1];
  if ( a1[1] != 2 * v2 || *a1 != 2 * *a2 )
    return 0;
  for ( i = 0; v2 > i; ++i )
  {
    v4 = (char *)a1 + 2 * i;
    if ( (unsigned __int8)v4[269] != (unsigned __int8)*((_WORD *)a2 + i + 134)
      || (unsigned __int8)v4[268] != HIBYTE(*((unsigned __int16 *)a2 + i + 134)) )
    {
      return 0;
    }
  }
  for ( j = 0; *a2 > j; ++j )
  {
    v6 = (char *)a1 + 2 * j;
    v7 = *((unsigned __int16 *)a2 + j + 6);
    if ( (unsigned __int8)v6[13] != (unsigned __int8)v7 || (unsigned __int8)v6[12] != v7 >> 8 )
      return 0;
  }
  return 1;
}


// ==================== sub_65C4 @0x65C4 size=18 ====================
void __fastcall sub_65C4(int a1)
{
  int v1; // r1

  v1 = 0;
  while ( a1 )
  {
    a1 &= a1 - 1;
    ++v1;
  }
  JUMPOUT(0x64D8);
}


// ==================== auth_check_cert_size_range (sub_65D6) @0x65D6 size=206 ====================
int __fastcall auth_check_cert_size_range(int a1, unsigned __int16 *a2)
{
  int v4; // r0
  unsigned int v6; // r0
  unsigned int v7; // r2
  int v8; // r0
  int v9; // r6
  int v10; // r0
  int v11; // r6
  int v12; // r0
  int v13; // r6
  int v14; // r0
  int v15; // r6
  int v16; // r0
  int v17; // r6
  int v18; // r0
  int v19; // r6
  int v20; // r0
  unsigned int v21; // r1

  v4 = *a2;
  if ( v4 == 1 )
  {
    sub_65C4(MEMORY[0x11C10810]);
    v7 = 31;
  }
  else
  {
    if ( v4 != 2 )
    {
      if ( a1 == 5 )
        return 32868;
      if ( a1 == 1 )
        return 32788;
      return 32804;
    }
    sub_65C4(MEMORY[0x11C10814]);
    v9 = v8;
    sub_65C4(MEMORY[0x11C10818]);
    v11 = v9 + v10;
    sub_65C4(MEMORY[0x11C1081C]);
    v13 = v11 + v12;
    sub_65C4(MEMORY[0x11C10820]);
    v15 = v13 + v14;
    sub_65C4(MEMORY[0x11C10824]);
    v17 = v15 + v16;
    sub_65C4(MEMORY[0x11C10828]);
    v19 = v17 + v18;
    sub_65C4(MEMORY[0x11C1082C]);
    v6 = v20 + v19;
    v7 = 223;
  }
  v21 = a2[1];
  if ( v21 >= v6 )
  {
    if ( v21 <= v7 )
    {
      return 0;
    }
    else if ( a1 == 5 )
    {
      return 32867;
    }
    else if ( a1 == 1 )
    {
      return 32787;
    }
    else
    {
      return 32803;
    }
  }
  else if ( a1 == 5 )
  {
    return 32866;
  }
  else if ( a1 == 1 )
  {
    return 32786;
  }
  else
  {
    return 32802;
  }
}


// ==================== auth_check_cert_type1 (sub_66A4) @0x66A4 size=110 ====================
int __fastcall auth_check_cert_type1(int a1, int a2)
{
  unsigned int v4; // r4
  _DWORD *v5; // r5
  char *v6; // r0

  if ( !a1 )
    return 32784;
  if ( (unsigned __int16)*(_DWORD *)(a1 + 8) != 1324 )
    return 32785;
  v4 = auth_check_cert_size_range(1, (unsigned __int16 *)(a1 + 1064));
  if ( v4 < 0xFF )
  {
    v5 = (_DWORD *)(a1 + 16);
    if ( (a2 & 0x80) != 0 )
    {
      if ( efuse_get_bit17(a2 << 24) )
      {
        return 28795;
      }
      else
      {
        v6 = get_brom_key_table_entry();
        if ( !auth_compare_with_key_table(v5, v6) )
          return 28783;
      }
    }
    else
    {
      v4 = auth_check_key_hash((int)v5, 0);
      if ( v4 >= 0xFF )
        return 28688;
    }
  }
  return v4;
}


// ==================== sub_6712 @0x6712 size=426 ====================
unsigned int __fastcall sub_6712(_DWORD *a1)
{
  int v2; // r7
  unsigned int result; // r0
  int v4; // r6
  _DWORD *v5; // r5
  unsigned int i; // r0
  _DWORD *v7; // r2
  int v8; // r1
  int v9; // r8
  _DWORD *v10; // r6
  int v11; // r2
  int v12; // r1
  int v13; // r6
  _DWORD *v14; // r5
  unsigned int j; // r0
  _DWORD *v16; // r1
  int v17; // r2
  int v18; // r8
  _DWORD *v19; // r6
  int v20; // r2
  int v21; // r1
  _DWORD *v22; // [sp+0h] [bp-38h] BYREF
  unsigned int v23; // [sp+4h] [bp-34h]

  v2 = 0;
  result = auth_parse_cert_blocks(*a1, &v22);
  if ( result < 0xFF )
  {
    if ( *v22 == 5 )
    {
      v4 = 0;
      v5 = 0;
      for ( i = 0; v23 > i; ++i )
      {
        v7 = &(&v22)[3 * i];
        v8 = *((unsigned __int16 *)v7 + 4);
        switch ( v8 )
        {
          case 1:
            v2 = *a1 + v7[3];
            break;
          case 3:
            v4 = *a1 + v7[3];
            break;
          case 4:
            v5 = (_DWORD *)(*a1 + v7[3]);
            break;
        }
      }
      v9 = a1[3];
      result = auth_check_cert_type1(v2, *(_DWORD *)(v9 + 48));
      if ( result < 0xFF )
      {
        result = auth_check_cert_type3_4(v4, (int)v5);
        if ( result < 0xFF )
        {
          a1[4] = v5 + 4;
          v10 = (_DWORD *)(v4 + 540);
          v11 = v10[2] & v5[14] | *(_DWORD *)(v9 + 48);
          a1[5] = v11;
          v12 = *v10 & v5[12];
          a1[6] = v12;
          a1[7] = v10[1] & v5[13];
          a1[8] = 0;
          a1[9] = 0;
          if ( (v12 & 0x11) != 0 )
            a1[5] = v11 | 4;
          if ( (v12 & 0x44) != 0 )
            a1[5] |= 0x10u;
          a1[5] |= 0x80000000;
        }
      }
    }
    else if ( *v22 == 7 )
    {
      v13 = 0;
      v14 = 0;
      for ( j = 0; v23 > j; ++j )
      {
        v16 = &(&v22)[3 * j];
        v17 = *((unsigned __int16 *)v16 + 4);
        switch ( v17 )
        {
          case 1:
            v2 = *a1 + v16[3];
            break;
          case 3:
            v13 = *a1 + v16[3];
            break;
          case 4:
            v14 = (_DWORD *)(*a1 + v16[3]);
            break;
        }
      }
      v18 = a1[3];
      result = auth_check_cert_type1(v2, *(_DWORD *)(v18 + 48));
      if ( result < 0xFF )
      {
        result = auth_check_cert_type3_4_v7(v13, (int)v14);
        if ( result < 0xFF )
        {
          a1[4] = v14 + 4;
          v19 = (_DWORD *)(v13 + 540);
          v20 = v19[4] & v14[16] | *(_DWORD *)(v18 + 48);
          a1[5] = v20;
          v21 = *v19 & v14[12];
          a1[6] = v21;
          a1[7] = v19[1] & v14[13];
          a1[8] = v19[2] & v14[14];
          a1[9] = v19[3] & v14[15];
          if ( (v21 & 0x11) != 0 )
            a1[5] = v20 | 4;
          if ( (v21 & 0x44) != 0 )
            a1[5] |= 0x10u;
          a1[5] |= 0x80000000;
        }
      }
    }
    else
    {
      return 24629;
    }
  }
  return result;
}


// ==================== sub_68BC @0x68BC size=24 ====================
int __fastcall sub_68BC(int a1)
{
  int v1; // r4

  v1 = 0;
  if ( mem_cmp(1059720, a1, 32) )
    return 28785;
  return v1;
}


// ==================== auth_verify_file (sub_68D4) @0x68D4 size=462 ====================
unsigned int __fastcall auth_verify_file(int a1, int a2)
{
  unsigned int v4; // r5
  unsigned int v5; // r4
  _DWORD *v6; // r6
  int v7; // r0
  _DWORD *v9; // [sp+4h] [bp-18h] BYREF
  int v10; // [sp+8h] [bp-14h] BYREF
  _BYTE v11[12]; // [sp+Ch] [bp-10h] BYREF
  char *v12; // [sp+18h] [bp-4h] BYREF

  v4 = 0;
  usb_status_reset(2);
  v5 = auth_find_block_by_type(a1, 0, &v10);
  if ( v5 >= 0xFF )
  {
    v4 = 28690;
    goto LABEL_32;
  }
  v5 = auth_check_block_header(v10);
  if ( v5 >= 0xFF )
  {
    v4 = 28691;
    goto LABEL_32;
  }
  v5 = auth_find_block_by_type(a1, 4, &v9);
  if ( v5 >= 0xFF )
  {
    v4 = 33028;
    goto LABEL_32;
  }
  v5 = auth_check_block_consistency(v10, v9);
  if ( v5 >= 0xFF )
  {
    v4 = 28692;
    goto LABEL_32;
  }
  MEMORY[0x102B00] = a1;
  MEMORY[0x102B04] = *(_DWORD *)(v10 + 32);
  MEMORY[0x102B08] = v10;
  MEMORY[0x102B0C] = v9;
  auth_build_descriptor(v11, a1);
  v6 = v9;
  if ( HIBYTE(*v9) == 2 )
  {
    v5 = sub_6712((_DWORD *)0x102B00);
    if ( v5 >= 0xFF )
    {
      v4 = 28780;
      goto LABEL_32;
    }
  }
  else
  {
    v5 = auth_resolve_key_source((int)v9, &v12);
    if ( v5 >= 0xFF )
    {
      v4 = 28780;
      goto LABEL_32;
    }
    if ( (v6[16] & 0x80) != 0 && (*(_DWORD *)(v10 + 52) & 0x2000000) != 0 && auth_compare_with_key_table(v6 + 17, v12) )
      v12 = (char *)(v6 + 17);
    MEMORY[0x102B10] = v6 + 12;
    MEMORY[0x102B14] = v6[16];
  }
  trace_begin(4u, 0);
  v5 = auth_dispatch_by_block_type(1070920, 1070936, v11, 0);
  trace_begin(4u, 1);
  trace_end(4u, 0, *(_DWORD *)(v10 + 32), a1);
  if ( v5 >= 0xFF )
  {
    v4 = 28686;
    goto LABEL_32;
  }
  if ( *(_BYTE *)(v10 + 27) == 5 )
  {
    if ( sub_DAFC() != 3 )
    {
      v5 = sub_68BC(MEMORY[0x102B10]);
      if ( v5 >= 0xFF )
      {
        v4 = 28689;
        goto LABEL_32;
      }
    }
  }
  else
  {
    v5 = sub_6422(MEMORY[0x102B10]);
    if ( v5 >= 0xFF )
    {
      v4 = 28689;
      goto LABEL_32;
    }
  }
  if ( efuse_get_secure_boot() )
  {
    v7 = MEMORY[0x102B28] | 3;
    MEMORY[0x102B28] |= 3u;
    if ( a2 )
    {
      MEMORY[0x102B28] = v7 | 4;
      MEMORY[0x103B4C] = 996942908;
      MEMORY[0x103B50] = 260324874;
    }
    else
    {
      MEMORY[0x102B28] = v7 & 0xFFFFFFFB;
    }
  }
  else
  {
    MEMORY[0x103B4C] = 996942908;
    MEMORY[0x103B50] = 260324874;
  }
LABEL_32:
  MEMORY[0x10287C] = v5;
  if ( v4 >= 0xFF )
  {
    MEMORY[0x103B4C] = 0;
    MEMORY[0x103B50] = 0;
    if ( efuse_get_secure_boot() )
      MEMORY[0x102B28] &= ~2u;
    mem_set_bytes(1059584, 0, 44);
  }
  return v4;
}


// ==================== sub_6AA2 @0x6AA2 size=54 ====================
_DWORD *__fastcall sub_6AA2(_DWORD *result, _DWORD *a2, _DWORD *a3, _DWORD *a4)
{
  if ( result && a2 && a3 && a4 )
  {
    if ( MEMORY[0x102B0C] )
    {
      *result = MEMORY[0x102B18];
      *a2 = MEMORY[0x102B1C];
      *a3 = MEMORY[0x102B20];
      result = (_DWORD *)MEMORY[0x102B24];
      *a4 = MEMORY[0x102B24];
    }
    else
    {
      *a4 = 0;
      *a3 = 0;
      *a2 = 0;
      *result = 0;
    }
  }
  return result;
}


// ==================== sub_6AD8 @0x6AD8 size=16 ====================
void sub_6AD8()
{
  JUMPOUT(0x64D8);
}


// ==================== sub_6AE8 @0x6AE8 size=18 ====================
int sub_6AE8()
{
  int v0; // r2

  if ( (sub_611A() & 0x100) != 0 )
    return 0;
  return v0;
}


// ==================== sub_6AFA @0x6AFA size=166 ====================
int __fastcall sub_6AFA(int a1, int *a2)
{
  unsigned int v4; // r6
  int v5; // r10
  int v6; // r8
  int v7; // r9
  int v8; // r7
  int v9; // r4

  v4 = 0;
  *a2 = 0;
  v5 = brom_get_descriptor(8);
  v6 = brom_get_descriptor(3);
  v7 = sub_10C34(1);
  v8 = sub_10C34(5);
  v9 = a1 + 372;
  if ( v5 && *(_DWORD *)(v5 + 44) == 1111769409 )
  {
    if ( v6 && !mem_cmp(v6 + 8, v9, 524) )
    {
      *a2 = v9;
    }
    else if ( v7 && !mem_cmp(v7 + 16, v9, 524) )
    {
      *a2 = v9;
    }
    else if ( v8 && !mem_cmp(v8 + 20, v9, 524) )
    {
      *a2 = v9;
    }
    else
    {
      return 28782;
    }
  }
  else
  {
    v4 = auth_check_key_hash(v9, 0);
    if ( v4 < 0xFF )
      *a2 = v9;
  }
  return v4;
}


// ==================== sub_6BA0 @0x6BA0 size=22 ====================
void sub_6BA0()
{
  JUMPOUT(0x64D8);
}


// ==================== auth_verify_cert (sub_6BB6) @0x6BB6 size=158 ====================
void __fastcall auth_verify_cert(int a1)
{
  unsigned int v2; // r0
  int v3; // [sp+4h] [bp-18h] BYREF
  int v4; // [sp+8h] [bp-14h] BYREF
  _BYTE v5[12]; // [sp+Ch] [bp-10h] BYREF
  int v6; // [sp+18h] [bp-4h] BYREF

  v2 = auth_find_block_by_type(a1, 0, &v4);
  if ( v2 < 0xFF )
  {
    v2 = auth_check_block_header(v4);
    if ( v2 < 0xFF )
    {
      if ( *(_BYTE *)(v4 + 27) != 2 )
        return;
      v2 = auth_find_block_by_type(a1, 5, &v3);
      if ( v2 < 0xFF )
      {
        v2 = sub_FB84(v4, v3);
        if ( v2 < 0xFF )
        {
          sub_6BA0();
          if ( v2 < 0xFF )
          {
            auth_build_descriptor(v5, a1);
            v2 = sub_6AFA(v3, &v6);
            if ( v2 < 0xFF )
            {
              v2 = auth_dispatch_by_block_type(1070920, 1070936, v5, 0);
              if ( v2 < 0xFF )
              {
                MEMORY[0x1027C4] = v3;
                MEMORY[0x1027C8] = a1;
                MEMORY[0x1027CC] = *(_DWORD *)(v4 + 32);
              }
              else
              {
                v2 = 28693;
              }
            }
          }
        }
      }
    }
  }
  if ( v2 >= 0xFF )
  {
    MEMORY[0x1027C4] = 0;
    MEMORY[0x1027C8] = 0;
    MEMORY[0x1027CC] = 0;
  }
}


// ==================== sub_6C54 @0x6C54 size=138 ====================
int __fastcall sub_6C54(int *a1)
{
  int v2; // r0
  int v3; // r5
  int v4; // r0
  int v5; // r6
  int v6; // r6
  int v8; // [sp+4h] [bp-4Ch] BYREF
  _DWORD v9[2]; // [sp+Ch] [bp-44h] BYREF
  _BYTE v10[28]; // [sp+14h] [bp-3Ch] BYREF
  _DWORD v11[8]; // [sp+30h] [bp-20h] BYREF

  v9[0] = 1062736;
  v9[1] = 13404;
  v2 = sub_864A();
  mem_copy_bytes(v10, v2, 28);
  v3 = sub_9064(1070920, 1070936, v9, v11, 0);
  sub_10F68(&v8);
  v4 = time_get_tick() ^ v8;
  *a1 = v4;
  *a1 = v4 ^ (2 * ((v11[0] >> 1) & 0x7FFFFF));
  v5 = time_get_tick() & 1;
  *a1 |= v5 | (time_get_tick() << 24);
  *a1 ^= sub_1104C(0);
  v6 = sub_10FF6(0);
  *a1 = v6 ^ sub_10FF6(*a1);
  return v3;
}


// ==================== sub_6CDE @0x6CDE size=100 ====================
int __fastcall sub_6CDE(int *a1, _DWORD *a2)
{
  int v4; // r4
  int v5; // r4
  int result; // r0
  int v7; // [sp+Ch] [bp-14h] BYREF
  _DWORD v8[4]; // [sp+10h] [bp-10h] BYREF

  sub_6C54(&v7);
  v4 = v7 & 3;
  MEMORY[0x1027D0] = v4;
  sub_11498();
  v8[0] = sub_160();
  v8[2] = sub_160();
  v8[1] = sub_160();
  v8[3] = sub_160();
  v5 = 16 * v4 + 1058772;
  result = sub_6268(v5, 16, (int)v8, (int)&dword_122A8[28], (int)&dword_12338, (int)dword_12348, (int)dword_12358);
  *a1 = v5;
  *a2 = 16;
  return result;
}


// ==================== sub_6D42 @0x6D42 size=214 ====================
unsigned int __fastcall sub_6D42(int a1, int a2)
{
  int v4; // r5
  int v5; // r3
  unsigned int v6; // r0
  int v7; // r0
  unsigned int v8; // r4
  int v10; // [sp+0h] [bp-2Ch] BYREF
  int v11; // [sp+4h] [bp-28h]
  int v12; // [sp+8h] [bp-24h]
  int v13; // [sp+Ch] [bp-20h]
  int v14; // [sp+10h] [bp-1Ch]
  int v15; // [sp+14h] [bp-18h]
  _BYTE v16[20]; // [sp+18h] [bp-14h] BYREF

  v4 = MEMORY[0x1027D0];
  trace_begin(6u, 0);
  usb_status_reset(2);
  if ( MEMORY[0x1027C4] )
  {
    v10 = a1;
    v11 = a2;
    v12 = 1074616;
    v13 = 256;
    v15 = MEMORY[0x1027C4] + 896;
    v14 = 0;
    v6 = *(_DWORD *)(MEMORY[0x1027C4] + 40);
    if ( v6 >> 28 == 12 )
      v7 = sub_86B2((unsigned __int16)v6 >> 12);
    else
      v7 = sub_86AE(v6, 12, MEMORY[0x1027C4], v5, v10, v11);
    mem_copy_bytes(v16, v7, 20);
    v8 = sub_904C(1070920, 1070936, &v10, 0);
    if ( v8 < 0xFF )
    {
      if ( *(_WORD *)(MEMORY[0x1027C4] + 906) )
      {
        if ( mem_cmp(16 * v4 + 1058772, 2 * *(unsigned __int16 *)(MEMORY[0x1027C4] + 906) + 1074600, 16) )
          v8 = 28704;
      }
      else if ( mem_cmp(16 * v4 + 1058772, 1074856, 16) )
      {
        v8 = 28704;
      }
    }
    else
    {
      MEMORY[0x10287C] = v8;
      v8 = 28703;
    }
  }
  else
  {
    v8 = 28695;
  }
  trace_begin(6u, 1);
  return v8;
}


// ==================== sub_6E50 @0x6E50 size=398 ====================
void __fastcall sub_6E50(unsigned int a1, int a2, int a3, int a4)
{
  int v6; // r7
  int v7; // r0
  unsigned int v8; // r0
  int v9; // r0
  int v10; // r2
  int v11; // r3
  unsigned int v12; // r0
  int v13; // r0
  unsigned int v14; // r4
  int v15; // r0
  int v16; // r0
  int v17; // [sp+0h] [bp-9Ch]
  _DWORD v18[2]; // [sp+4h] [bp-98h] BYREF
  _BYTE v19[28]; // [sp+Ch] [bp-90h] BYREF
  int v20; // [sp+28h] [bp-74h]
  int v21; // [sp+2Ch] [bp-70h]
  int v22; // [sp+30h] [bp-6Ch]
  int v23; // [sp+34h] [bp-68h]
  int v24; // [sp+38h] [bp-64h]
  int v25; // [sp+3Ch] [bp-60h]
  int v26; // [sp+40h] [bp-5Ch]
  int v27; // [sp+44h] [bp-58h]
  _DWORD v28[2]; // [sp+48h] [bp-54h] BYREF
  _BYTE v29[28]; // [sp+50h] [bp-4Ch] BYREF
  _DWORD v30[6]; // [sp+6Ch] [bp-30h] BYREF
  _BYTE v31[20]; // [sp+84h] [bp-18h] BYREF
  _BYTE *v32; // [sp+98h] [bp-4h]

  v6 = a2 + a3 - a4;
  if ( !MEMORY[0x1027C4] )
    goto LABEL_20;
  v28[0] = a2;
  v28[1] = a3 - a4;
  v7 = sub_864A();
  v32 = v29;
  mem_copy_bytes(v29, v7, 28);
  v8 = *(_DWORD *)(MEMORY[0x1027C4] + 40);
  if ( v8 >> 28 == 12 )
  {
    v9 = sub_8660(HIWORD(v8) & 0xF);
    mem_copy_bytes(v32, v9, 28);
  }
  if ( (unsigned int)sub_9064(1070920, 1070936, v28, 1059648, 0) >= 0xFF )
    goto LABEL_20;
  v30[0] = v6;
  v30[1] = a4;
  v30[2] = 1074616;
  v30[3] = 256;
  v30[5] = MEMORY[0x1027C4] + 1420;
  v30[4] = 0;
  v12 = *(_DWORD *)(MEMORY[0x1027C4] + 40);
  v13 = v12 >> 28 == 12 ? sub_86B2((v12 >> 20) & 0xF) : sub_86AE(v12, 0, v10, v11, v17, v18[0]);
  mem_copy_bytes(v31, v13, 20);
  if ( (unsigned int)sub_904C(1070920, 1070936, v30, 0) >= 0xFF )
    goto LABEL_20;
  if ( (*(_DWORD *)(MEMORY[0x1027C4] + 40) & 0x2000000) != 0 )
  {
    v18[0] = 1070920;
    v18[1] = 1070936;
    mem_copy_bytes(v19, v32, 28);
    v20 = 0;
    v21 = 1059648;
    v22 = 32;
    v23 = 1074616;
    v24 = a4;
    v25 = 32;
    v26 = 2048;
    v14 = auth_rsa_verify(v18);
    if ( v14 >= 0xFF )
    {
      MEMORY[0x10287C] = v14;
      goto LABEL_20;
    }
    if ( v27 != 1 )
LABEL_20:
      JUMPOUT(0x6A9E);
  }
  else
  {
    v15 = sub_8696();
    if ( mem_cmp(1059648, 1074616, v15) )
      goto LABEL_20;
  }
  if ( *(_DWORD *)(MEMORY[0x1027C4] + 40) << 31 )
  {
    if ( *(_DWORD *)(MEMORY[0x1027C4] + 44) > a1 )
    {
      v16 = sub_8696();
      mem_cmp(1059648, MEMORY[0x1027C4] + 32 * a1 + 52, v16);
    }
  }
  goto LABEL_20;
}


// ==================== sub_6FDE @0x6FDE size=28 ====================
unsigned int __fastcall sub_6FDE(int a1, int a2)
{
  unsigned int result; // r0

  result = sub_DD78(a1, a2, 415);
  if ( result < 0xFF )
  {
    if ( result == 1 )
      return 0;
    else
      return 28698;
  }
  return result;
}


// ==================== sub_6FFA @0x6FFA size=280 ====================
void __fastcall sub_6FFA(int a1)
{
  unsigned int v2; // r5
  unsigned int v3; // r4
  int v4; // r0
  int v5; // [sp+4h] [bp-18h] BYREF
  int v6; // [sp+8h] [bp-14h] BYREF
  _BYTE v7[12]; // [sp+Ch] [bp-10h] BYREF
  int *v8; // [sp+18h] [bp-4h]

  v2 = 0;
  usb_status_reset(2);
  v3 = auth_find_block_by_type(a1, 0, &v6);
  if ( v3 < 0xFF )
  {
    v3 = auth_check_block_header(v6);
    if ( v3 < 0xFF )
    {
      if ( *(_WORD *)(v6 + 24) == 6 )
      {
        if ( *(_DWORD *)(v6 + 48) )
        {
          if ( *(_BYTE *)(v6 + 27) != 2 )
            goto LABEL_24;
          v3 = auth_find_block_by_type(a1, 6, &v5);
          if ( v3 < 0xFF )
          {
            v3 = sub_FC30(v6, v5);
            if ( v3 < 0xFF )
            {
              v4 = auth_build_descriptor(v7, a1);
              if ( sub_84E0(v4) )
              {
                v3 = 28793;
                v2 = 28794;
              }
              else
              {
                v8 = sub_61C0();
                trace_begin(5u, 0);
                v3 = auth_dispatch_by_block_type(1070920, 1070936, v7, 0);
                trace_begin(5u, 1);
                trace_end(5u, 0, *(_DWORD *)(v6 + 32), a1);
                if ( v3 < 0xFF )
                {
                  v3 = sub_6422(v5 + 16);
                  if ( v3 < 0xFF )
                  {
                    MEMORY[0x103B54] = 1374181413;
                    MEMORY[0x103B58] = -1755804480;
                    MEMORY[0x103B5C] = a1;
                    ((void (*)(void))(*(_DWORD *)(v6 + 48) + a1))();
                  }
                  else
                  {
                    v2 = 28697;
                  }
                }
                else
                {
                  v2 = 28696;
                }
              }
            }
            else
            {
              v2 = 28701;
            }
          }
          else
          {
            v2 = 33035;
          }
        }
        else
        {
          v2 = 28702;
        }
      }
      else
      {
        v2 = 28772;
      }
    }
    else
    {
      v2 = 28700;
    }
  }
  else
  {
    v2 = 28699;
  }
  MEMORY[0x10287C] = v3;
  if ( v2 >= 0xFF )
  {
    MEMORY[0x103B54] = 0;
    MEMORY[0x103B58] = 0;
    MEMORY[0x103B5C] = 0;
  }
LABEL_24:
  JUMPOUT(0x6E16);
}


// ==================== sub_712E @0x712E size=68 ====================
unsigned int __fastcall sub_712E(int a1, int a2, int a3, int a4)
{
  unsigned int result; // r0

  if ( !a2 )
    return 28746;
  result = sub_DD78(a1, a2, 415);
  if ( result >= 0xFF )
    return result;
  if ( result != 1 )
    return 28714;
  if ( !a4 )
    return 0;
  result = sub_DD78(a3, a4, 415);
  if ( result < 0xFF )
  {
    if ( result != 1 )
      return 28744;
    return 0;
  }
  return result;
}


// ==================== sub_7172 @0x7172 size=254 ====================
void __fastcall sub_7172(int a1, int a2, int a3, int a4, _DWORD *a5)
{
  unsigned int v9; // r5
  int v10; // r0
  int v11; // r0
  int v12; // [sp+0h] [bp-18h] BYREF
  int v13; // [sp+4h] [bp-14h] BYREF
  _BYTE v14[12]; // [sp+8h] [bp-10h] BYREF
  char *v15; // [sp+14h] [bp-4h]

  usb_status_reset(2);
  *a5 = 0;
  v12 = 0;
  v9 = auth_find_block_by_type(a1, 0, &v13);
  if ( v9 < 0xFF )
  {
    v9 = auth_check_block_header(v13);
    if ( v9 < 0xFF
      && *(_WORD *)(v13 + 24) == 7
      && *(_BYTE *)(v13 + 27) == 2
      && *(_DWORD *)(v13 + 32) == a2
      && *(_DWORD *)(v13 + 48) )
    {
      v10 = board_check_flag3(&v12);
      if ( sub_84B8(v10) )
        goto LABEL_13;
      v11 = auth_build_descriptor(v14, a1);
      if ( efuse_get_bit17(v11) )
      {
        v9 = 28796;
        goto LABEL_14;
      }
      v15 = get_brom_key_table_entry();
      v9 = auth_dispatch_by_block_type(1070920, 1070936, v14, 0);
      if ( v9 < 0xFF )
      {
LABEL_13:
        *a5 = ((int (__fastcall *)(int, int, int, _UNKNOWN ***))(*(_DWORD *)(v13 + 48) + a1))(a3, a4, v12, off_133D4);
        time_delay_ms(0x3E8u);
      }
    }
  }
LABEL_14:
  MEMORY[0x10287C] = v9;
  if ( a2 )
    mem_set_bytes(a1, 69, a2);
  if ( a4 )
    mem_set_bytes(a3, 69, a4);
  JUMPOUT(0x6B9C);
}


// ==================== sub_72A8 @0x72A8 size=58 ====================
int __fastcall sub_72A8(int a1, int a2)
{
  int result; // r0
  unsigned int v4; // r2

  result = 0;
  if ( !a1 )
    return 33044;
  v4 = *(_DWORD *)(a1 + 12);
  if ( !v4 || v4 > 0xFF )
    return 33045;
  if ( !*(_DWORD *)(a1 + 16) )
    return 33046;
  if ( !a2 )
    return 33047;
  if ( v4 != *(unsigned __int16 *)(a2 + 4) - 8 )
    return 33048;
  return result;
}


// ==================== sub_72E4 @0x72E4 size=174 ====================
int __fastcall sub_72E4(_DWORD *a1, _DWORD *a2, int a3)
{
  unsigned int v4; // r6
  unsigned int v5; // r8
  unsigned int v6; // r10
  int (__fastcall *v7)(unsigned int, _DWORD *); // r7
  unsigned int v8; // r11
  unsigned int i; // r5
  unsigned int v10; // r4
  _DWORD v12[3]; // [sp+4h] [bp-10h] BYREF
  int v13; // [sp+10h] [bp-4h]

  v12[1] = a1;
  v12[2] = a2;
  v13 = a3;
  v4 = 0;
  v5 = a1[7] + a1[10];
  v6 = a1[7] + a1[8] - a1[11];
  v7 = (int (__fastcall *)(unsigned int, _DWORD *))a2[4];
  if ( v5 > (unsigned int)v7 || v6 <= (unsigned int)v7 )
    return 28752;
  v8 = a2[3];
  for ( i = 0; i < v8; i = (unsigned __int8)(i + 1) )
  {
    if ( *(_BYTE *)(v13 + i + 8) == 80 )
    {
      if ( i < 8 )
      {
        v12[0] = 0;
        v10 = v7(i, v12);
        if ( !v10 )
        {
          if ( v12[0] )
          {
            if ( v5 <= v12[0] && v6 > v12[0] )
              *(_DWORD *)(4 * i + 0x102814) = v12[0];
            else
              v10 = 28754;
          }
          else
          {
            v10 = 28753;
          }
        }
      }
      else
      {
        v10 = 242;
      }
      if ( !v10 || v10 >= 0xFF || !(a2[2] << 31) )
        usb_write_debug_status((unsigned __int16)v10, i, 25, 82);
      if ( v10 >= 0xFF )
        v4 = v10;
    }
  }
  return v4;
}


// ==================== sub_7392 @0x7392 size=144 ====================
int __fastcall sub_7392(int a1, _DWORD *a2, _DWORD *a3, int *a4, int *a5, int a6)
{
  int v10; // r4
  unsigned int v11; // r0
  unsigned int v12; // r0
  unsigned int v13; // r0

  v10 = 0;
  *a2 = 0;
  *a3 = 0;
  *a4 = 0;
  *a5 = 0;
  v11 = auth_find_block_by_type(a1, 0, a2);
  if ( v11 >= 0xFF )
    return v11;
  v12 = auth_check_block_header(*a2);
  if ( v12 >= 0xFF )
    return v12;
  auth_find_block_by_type(a1, 14, a3);
  auth_find_block_by_type(a1, 3, a6);
  if ( (unsigned int)auth_find_block_by_type(a1, 10, a4) >= 0xFF )
    return 33044;
  if ( (unsigned int)auth_find_block_by_type(a1, 15, a5) >= 0xFF )
    return 33047;
  v13 = sub_72A8(*a4, *a5);
  if ( v13 >= 0xFF )
    return v13;
  return v10;
}


// ==================== sub_7422 @0x7422 size=52 ====================
unsigned int __fastcall sub_7422(int a1, _DWORD *a2)
{
  int v4; // r5
  unsigned int result; // r0

  if ( sub_84E0(a1) )
  {
    if ( a1 )
    {
      v4 = a1 + 8;
      result = auth_check_key_hash(v4, 0);
      if ( result < 0xFF )
      {
        *a2 = v4;
        return 0;
      }
    }
    else
    {
      return 28791;
    }
  }
  else
  {
    *a2 = sub_61C0();
    return 0;
  }
  return result;
}


// ==================== sub_7456 @0x7456 size=254 ====================
unsigned int __fastcall sub_7456(int a1)
{
  unsigned int v2; // r4
  unsigned int v3; // r5
  int v5; // [sp+8h] [bp-24h] BYREF
  int v6; // [sp+Ch] [bp-20h] BYREF
  _DWORD *v7; // [sp+10h] [bp-1Ch] BYREF
  int v8; // [sp+14h] [bp-18h] BYREF
  _DWORD *v9; // [sp+18h] [bp-14h] BYREF
  _BYTE v10[12]; // [sp+1Ch] [bp-10h] BYREF
  int v11; // [sp+28h] [bp-4h] BYREF

  v2 = 0;
  usb_status_reset(2);
  v3 = sub_7392(a1, &v9, &v8, (int *)&v7, &v6, (int)&v5);
  if ( v3 < 0xFF )
  {
    if ( *((_WORD *)v9 + 12) == 9 )
    {
      if ( *((_BYTE *)v9 + 27) == 2 )
      {
        if ( (unsigned int)(v9[10] + v9[11]) < v9[8] )
        {
          auth_build_descriptor(v10, a1);
          v3 = sub_7422(v5, &v11);
          if ( v3 < 0xFF )
          {
            trace_begin(2u, 0);
            v3 = auth_dispatch_by_block_type(1070920, 1070936, v10, 0);
            trace_begin(2u, 1);
            trace_end(2u, 0, v9[8], a1);
            if ( v3 < 0xFF )
            {
              v3 = sub_72E4(v9, v7, v6);
              if ( v3 < 0xFF )
              {
                MEMORY[0x106B90] = v9;
                MEMORY[0x106B94] = v8;
                MEMORY[0x106B98] = v7;
                MEMORY[0x106B9C] = v6;
                MEMORY[0x106BA0] = v5;
              }
              else
              {
                v2 = 28755;
              }
            }
            else
            {
              v2 = 28751;
            }
          }
          else
          {
            v2 = 28792;
          }
        }
        else
        {
          v2 = 28747;
        }
      }
      else
      {
        v2 = 28750;
      }
    }
    else
    {
      v2 = 28749;
    }
  }
  else
  {
    v2 = 28748;
  }
  MEMORY[0x10287C] = v3;
  if ( v2 >= 0xFF )
  {
    MEMORY[0x106B90] = 0;
    MEMORY[0x106B94] = 0;
    MEMORY[0x106B98] = 0;
    MEMORY[0x106B9C] = 0;
    MEMORY[0x106BA0] = 0;
  }
  return v2;
}


// ==================== sub_7568 @0x7568 size=126 ====================
int sub_7568()
{
  unsigned int v0; // r5
  _DWORD *v1; // r4
  unsigned int v2; // r6

  v0 = 0;
  usb_status_reset(2);
  v1 = (_DWORD *)MEMORY[0x106B8C];
  if ( MEMORY[0x106B8C] )
  {
    if ( *(unsigned __int8 *)(MEMORY[0x106B8C] + 13) >= 3u && *(unsigned __int16 *)(MEMORY[0x106B8C] + 14) < 0xFFu )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(MEMORY[0x106B8C] + 8) + 16) & 2) != 0 )
        sub_10DB0();
      v2 = (unsigned __int8)(2 * *((_BYTE *)v1 + 12) + 22);
      trace_begin(v2, 0);
      v0 = sub_7456(*v1);
      trace_begin(v2, 1);
      trace_end(v2, 0, v1[1], *v1);
      if ( v0 < 0xFF )
        sub_DD7C(*v1, v1[1]);
      *((_BYTE *)v1 + 13) = 4;
      *((_WORD *)v1 + 7) = v0;
      if ( !*((_WORD *)v1 + 8) )
        *((_WORD *)v1 + 8) = MEMORY[0x10287C];
    }
    else
    {
      return 4128;
    }
  }
  return v0;
}


// ==================== sub_75F0 @0x75F0 size=60 ====================
int __fastcall sub_75F0(_DWORD *a1, int a2)
{
  unsigned int v2; // r1

  if ( !a1 )
    return 32773;
  if ( !a2 )
    return 33049;
  v2 = *(unsigned __int16 *)(a2 + 42);
  if ( !v2 || v2 > 4 )
    return 33050;
  if ( a1[8] - a1[10] - a1[11] >= 32 * v2 )
    return 0;
  return 33051;
}


// ==================== sub_762C @0x762C size=4 ====================
int sub_762C()
{
  return 1056080;
}


// ==================== sub_7630 @0x7630 size=20 ====================
BOOL sub_7630()
{
  return MEMORY[0x1056E4] << 31 && (MEMORY[0x1056E4] & 2) != 0;
}


// ==================== sub_7644 @0x7644 size=24 ====================
BOOL sub_7644()
{
  return MEMORY[0x1056E4] << 31 && (MEMORY[0x1056E4] & 2) != 0 && (MEMORY[0x1056E4] & 4) != 0;
}


// ==================== sub_765C @0x765C size=34 ====================
BOOL sub_765C()
{
  return sub_84A2() && (sub_8430() || efuse_get_bit3() || sub_843A());
}


// ==================== sub_767E @0x767E size=22 ====================
int __fastcall sub_767E(unsigned int a1)
{
  if ( a1 && a1 <= 0x440 )
    return 0;
  else
    return 28758;
}


// ==================== sub_7694 @0x7694 size=36 ====================
int __fastcall sub_7694(_DWORD *a1)
{
  int v2; // r2
  _DWORD *v3; // r3

  if ( !sub_7630() )
    return MEMORY[0x1056E8];
  *v3 = MEMORY[0x1056EC];
  *a1 = 1070864;
  return v2;
}


// ==================== sub_76B8 @0x76B8 size=46 ====================
int sub_76B8()
{
  int result; // r0

  sub_762C();
  if ( MEMORY[0x1056DC] != 1230979922 || (result = MEMORY[0x1056E0], MEMORY[0x1056E0] != 5523790) )
  {
    mem_set_bytes(1070812, 0, 108);
    MEMORY[0x1056E8] = 28757;
    strcpy((char *)0x1056DC, "RC_INIT");
    return 28757;
  }
  return result;
}


// ==================== sub_76E6 @0x76E6 size=110 ====================
int __fastcall sub_76E6(int a1, int a2)
{
  int v3; // r2
  unsigned int v4; // r5
  int v5; // r6
  unsigned int i; // r4
  int v7; // r0
  _BYTE v9[32]; // [sp+0h] [bp-20h] BYREF

  if ( !sub_7630() )
    return MEMORY[0x1056E8];
  v4 = auth_hash_key_region(v3, (int)v9);
  if ( v4 >= 0xFF )
    return 28764;
  v5 = MEMORY[0x105744];
  for ( i = 0; ; ++i )
  {
    if ( MEMORY[0x10573A] <= i )
      return 28766;
    v7 = sub_8696();
    if ( !mem_cmp(v9, v5, v7) )
      break;
    v5 += 32;
  }
  if ( MEMORY[0x1056EC] > i )
    return 28765;
  if ( a2 )
    MEMORY[0x1056EC] = i;
  return v4;
}


// ==================== sub_7754 @0x7754 size=96 ====================
void __fastcall sub_7754(int a1, int a2, _DWORD *a3)
{
  int v6; // r0
  int v7; // r6

  *a3 = 0;
  if ( efuse_get_bit2_1120() )
  {
    v6 = *(_DWORD *)(a1 + 44) << 31;
    if ( v6 )
    {
      if ( !efuse_get_bit17(v6) )
        *a3 = get_brom_key_table_entry();
    }
  }
  else if ( !(*(_DWORD *)(a1 + 44) << 31) )
  {
    if ( a2 )
    {
      v7 = a2 + 8;
      if ( (unsigned int)auth_compare_key_hash(v7) < 0xFF )
        *a3 = v7;
    }
  }
  JUMPOUT(0x773A);
}


// ==================== sub_77B4 @0x77B4 size=120 ====================
void __fastcall sub_77B4(int a1, _DWORD *a2, _DWORD *a3, int *a4)
{
  *a2 = 0;
  *a3 = 0;
  *a4 = 0;
  if ( (unsigned int)auth_find_block_by_type(a1, 0, a2) < 0xFF
    && (unsigned int)auth_check_block_header(*a2) < 0xFF
    && ((unsigned int)auth_find_block_by_type(a1, 3, a3) < 0xFF || efuse_get_bit2_1120())
    && (unsigned int)auth_find_block_by_type(a1, 11, a4) < 0xFF )
  {
    sub_75F0((_DWORD *)*a2, *a4);
  }
  JUMPOUT(0x773A);
}


// ==================== sub_782C @0x782C size=372 ====================
unsigned int __fastcall sub_782C(int a1, int a2)
{
  int v3; // r6
  unsigned int v4; // r4
  unsigned int v5; // r0
  unsigned int v6; // r5
  unsigned int v7; // r0
  unsigned int v8; // r0
  int v9; // r0
  int v10; // r0
  unsigned int v11; // r0
  _BYTE v13[32]; // [sp+0h] [bp-44h] BYREF
  int v14; // [sp+20h] [bp-24h] BYREF
  int v15; // [sp+24h] [bp-20h] BYREF
  int v16; // [sp+28h] [bp-1Ch] BYREF
  _BYTE v17[12]; // [sp+2Ch] [bp-18h] BYREF
  _DWORD v18[2]; // [sp+38h] [bp-Ch] BYREF
  int v19; // [sp+40h] [bp-4h]

  v18[1] = a1;
  v19 = a2;
  v3 = 0;
  v4 = 0;
  usb_status_reset(2);
  sub_77B4(a1, &v16, &v15, &v14);
  v6 = v5;
  if ( v5 >= 0xFF )
  {
    v4 = 28759;
    goto LABEL_26;
  }
  if ( *(_WORD *)(v16 + 24) != 10 )
  {
    v4 = 28760;
    goto LABEL_26;
  }
  if ( *(_BYTE *)(v16 + 27) != 2 )
  {
    v4 = 28761;
    goto LABEL_26;
  }
  auth_init_descriptor(v17, a1, 3);
  sub_7754(v14, v15, v18);
  v6 = v7;
  if ( v7 >= 0xFF )
  {
    v4 = 28762;
    goto LABEL_26;
  }
  trace_begin(3u, 0);
  v6 = auth_dispatch_by_block_type(1070920, 1070936, v17, v13);
  trace_begin(3u, 1);
  trace_end(3u, 0, *(_DWORD *)(v16 + 32), a1);
  if ( v6 >= 0xFF )
  {
    v4 = 28763;
    goto LABEL_26;
  }
  if ( MEMORY[0x1056E4] << 31 )
  {
    if ( mem_cmp(v14 + 8, 1070872, 32) )
    {
      v4 = 28767;
      goto LABEL_26;
    }
    v8 = *(unsigned __int16 *)(v14 + 40);
    if ( v8 == MEMORY[0x105738] )
    {
      v9 = sub_8696();
      if ( mem_cmp(1070832, v13, v9) )
      {
        v4 = 28768;
        goto LABEL_26;
      }
      v3 = 1;
    }
    else if ( v8 < MEMORY[0x105738] )
    {
      v4 = 28769;
      goto LABEL_26;
    }
  }
  mem_copy_bytes(1070832, v13, 32);
  mem_copy_bytes(1070864, v14, 48);
  MEMORY[0x105740] = v15;
  MEMORY[0x105744] = *(_DWORD *)(v16 + 40) + a1;
  if ( !v3 )
    MEMORY[0x1056EC] = 0;
  MEMORY[0x102834] = a1;
  MEMORY[0x102838] = *(_DWORD *)(v16 + 32);
  v10 = MEMORY[0x1056E4] | 3;
  MEMORY[0x1056E4] |= 3u;
  if ( v19 )
    v11 = v10 | 4;
  else
    v11 = v10 & 0xFFFFFFFB;
  MEMORY[0x1056E4] = v11;
LABEL_26:
  MEMORY[0x1056E8] = v4;
  MEMORY[0x10287C] = v6;
  if ( v4 >= 0xFF )
  {
    MEMORY[0x1056E4] &= ~2u;
    mem_set_bytes(1070912, 0, 8);
    MEMORY[0x102834] = 0;
    MEMORY[0x102838] = 0;
  }
  return v4;
}


// ==================== sub_79C8 @0x79C8 size=120 ====================
int sub_79C8()
{
  unsigned int v0; // r5
  int v1; // r4
  unsigned int v2; // r6

  v0 = 0;
  usb_status_reset(2);
  v1 = MEMORY[0x106BA4];
  if ( MEMORY[0x106BA4] )
  {
    if ( *(unsigned __int8 *)(MEMORY[0x106BA4] + 13) >= 3u && *(unsigned __int16 *)(MEMORY[0x106BA4] + 14) < 0xFFu )
    {
      sub_10DB0();
      v2 = (unsigned __int8)(2 * *(_BYTE *)(v1 + 12) + 22);
      trace_begin(v2, 0);
      v0 = sub_782C(*(_DWORD *)v1, 0);
      trace_begin(v2, 1);
      trace_end(v2, 0, *(_DWORD *)(v1 + 4), *(_DWORD *)v1);
      *(_BYTE *)(v1 + 13) = 4;
      *(_WORD *)(v1 + 14) = v0;
      if ( !*(_WORD *)(v1 + 16) )
        *(_WORD *)(v1 + 16) = MEMORY[0x10287C];
    }
    else
    {
      return 4132;
    }
  }
  else if ( sub_765C() )
  {
    return 28757;
  }
  return v0;
}


// ==================== sub_7A48 @0x7A48 size=108 ====================
int sub_7A48()
{
  unsigned int v0; // r5
  int v1; // r4
  unsigned int v2; // r6

  v0 = 0;
  usb_status_reset(2);
  v1 = MEMORY[0x106BA8];
  if ( MEMORY[0x106BA8] )
  {
    if ( *(unsigned __int8 *)(MEMORY[0x106BA8] + 13) >= 3u && *(unsigned __int16 *)(MEMORY[0x106BA8] + 14) < 0xFFu )
    {
      sub_10DB0();
      v2 = (unsigned __int8)(2 * *(_BYTE *)(v1 + 12) + 22);
      trace_begin(v2, 0);
      v0 = auth_verify_file(*(_DWORD *)v1, 0);
      trace_begin(v2, 1);
      trace_end(v2, 0, *(_DWORD *)(v1 + 4), *(_DWORD *)v1);
      *(_BYTE *)(v1 + 13) = 4;
      *(_WORD *)(v1 + 14) = v0;
      if ( !*(_WORD *)(v1 + 16) )
        *(_WORD *)(v1 + 16) = MEMORY[0x10287C];
    }
    else
    {
      return 4146;
    }
  }
  return v0;
}


// ==================== sub_7ABC @0x7ABC size=448 ====================
unsigned int __fastcall sub_7ABC(int a1, int a2, int a3)
{
  int v6; // r6
  unsigned int v7; // r4
  BOOL v8; // r7
  bool v9; // zf
  int v10; // r7
  int v11; // r0
  unsigned int v12; // r0
  _DWORD v14[3]; // [sp+4h] [bp-40h] BYREF
  char v15; // [sp+10h] [bp-34h]
  _BYTE v16[16]; // [sp+14h] [bp-30h] BYREF
  int v17; // [sp+24h] [bp-20h] BYREF
  int v18; // [sp+28h] [bp-1Ch]
  _DWORD *v19; // [sp+2Ch] [bp-18h]
  int v20; // [sp+30h] [bp-14h]
  int *v21; // [sp+34h] [bp-10h]
  int *v22; // [sp+38h] [bp-Ch]
  int *v23; // [sp+3Ch] [bp-8h]
  int v24; // [sp+40h] [bp-4h]

  v6 = 0;
  v7 = 0;
  v8 = sub_6198();
  if ( MEMORY[0x102874] == 2 )
    v8 = 1;
  if ( v8 )
  {
    v9 = a3 == 0;
    while ( !v9 )
    {
      if ( !*(_BYTE *)(a3 + 9) )
      {
        v9 = *(_BYTE *)(a3 + 8) == 0;
        if ( !*(_BYTE *)(a3 + 8) )
          continue;
      }
      v7 = 28680;
      break;
    }
  }
  else
  {
    v10 = sub_83EC(MEMORY[0x102874]);
    v11 = sub_83F6();
    if ( a3 )
    {
      if ( v10 && !*(_BYTE *)(a3 + 8) || !v10 && *(_BYTE *)(a3 + 8) )
      {
        v7 = 28672;
        goto LABEL_46;
      }
      if ( v11 && !*(_BYTE *)(a3 + 9) )
      {
        v7 = 28673;
        goto LABEL_46;
      }
    }
    else if ( v10 | v11 && *(_WORD *)(a2 + 24) == 1 )
    {
      v7 = 33025;
      goto LABEL_46;
    }
    if ( a3 )
    {
      if ( *(_BYTE *)(a3 + 8) )
        v6 = 1;
      if ( *(_BYTE *)(a3 + 9) )
        v6 |= 2u;
      if ( v6 )
      {
        v7 = sub_FB30(a2, a3);
        if ( v7 < 0xFF )
        {
          mem_set_bytes(&v17, 0, 32);
          v17 = *(_DWORD *)(a2 + 28) + *(_DWORD *)(a2 + 40) + *(_DWORD *)(a3 + 12);
          v18 = *(_DWORD *)(a3 + 16);
          v19 = v14;
          v14[1] = dword_1238C;
          v14[2] = 16;
          v15 = 1;
          v20 = 16;
          v21 = &dword_1238C[4];
          v22 = &dword_1238C[8];
          v23 = &dword_1238C[12];
          if ( (v6 & 2) == 0 )
            goto LABEL_49;
          sub_8196(dword_1236C);
          v24 = 3;
          if ( !sub_84C2(3) )
          {
            v24 |= 4u;
            if ( sub_84CC() )
              v24 |= 8u;
          }
          trace_begin(0xFu, 0);
          v7 = sub_9448(1070920, 1070936, &v17);
          trace_begin(0xFu, 1);
          v12 = trace_end(0xFu, a1, v18, v17);
          sub_81AE(v12);
          if ( v7 >= 0xFF )
          {
            MEMORY[0x10287C] = v7;
            v7 = 28674;
          }
          else
          {
LABEL_49:
            if ( v6 << 31 )
            {
              if ( sub_818C(v6 << 31) )
              {
                v7 = 28678;
              }
              else if ( sub_8416() )
              {
                v7 = 28677;
              }
              else
              {
                sub_8400(v16);
                v14[0] = v16;
                v24 = 0;
                trace_begin(0x10u, 0);
                v7 = sub_9448(1070920, 1070936, &v17);
                trace_begin(0x10u, 1);
                trace_end(0x10u, a1, v18, v17);
                if ( v7 >= 0xFF )
                {
                  MEMORY[0x10287C] = v7;
                  v7 = 28675;
                }
              }
            }
          }
        }
      }
    }
  }
LABEL_46:
  mem_set_bytes(v16, 0, 16);
  return v7;
}


// ==================== sub_7C90 @0x7C90 size=26 ====================
int sub_7C90()
{
  nullsub_6();
  MEMORY[0x1000A0D8] |= 0x140u;
  MEMORY[0x1000A0D8] |= 0x20u;
  return 268476632;
}


// ==================== sub_7CAA @0x7CAA size=26 ====================
int sub_7CAA()
{
  nullsub_6();
  MEMORY[0x1000A0D8] &= 0xFFFFFEBF;
  MEMORY[0x1000A0D8] &= ~0x20u;
  return 268476632;
}


// ==================== sub_7CC4 @0x7CC4 size=26 ====================
int sub_7CC4()
{
  nullsub_6();
  MEMORY[0x1000A0DC] |= 0x140u;
  MEMORY[0x1000A0DC] |= 0x20u;
  return 268476636;
}


// ==================== nullsub_6 @0x7CE8 size=2 ====================
void nullsub_6()
{
  ;
}


// ==================== sub_7CEC @0x7CEC size=4 ====================
// attributes: thunk
int sub_7CEC()
{
  return sub_7CF0();
}


// ==================== sub_7CF0 @0x7CF0 size=48 ====================
BOOL __fastcall sub_7CF0(int a1, unsigned int a2)
{
  sub_8258(1);
  if ( a1 )
    sub_8344(1);
  return time_delay_ms(a2);
}


// ==================== sub_7D20 @0x7D20 size=24 ====================
int sub_7D20()
{
  sub_8258(0);
  return sub_8344(0);
}


// ==================== sub_7D38 @0x7D38 size=16 ====================
int sub_7D38()
{
  int v0; // r0

  v0 = sub_82C4();
  return sub_83B0(v0);
}


// ==================== brom_check_stage_marker (sub_7D48) @0x7D48 size=112 ====================
BOOL brom_check_stage_marker()
{
  BOOL result; // r0

  if ( MEMORY[0x103B60] == 1247035719 && MEMORY[0x103B64] == 1145848153 )
  {
    time_ms_to_ticks(MEMORY[0x103B68]);
    do
      result = time_wait_ticks();
    while ( !result );
  }
  else
  {
    time_ms_to_ticks(0xFu);
    do
      result = time_wait_ticks();
    while ( !result );
  }
  return result;
}


// ==================== sub_7DB8 @0x7DB8 size=52 ====================
int sub_7DB8()
{
  if ( MEMORY[0x103B60] == 1247035719 && MEMORY[0x103B64] == 1145848153 )
    return MEMORY[0x103B68];
  else
    return 15;
}


// ==================== sub_7DEC @0x7DEC size=196 ====================
void __fastcall __spoils<R2,R3,R12,LR> sub_7DEC(int a1, unsigned int a2, int a3, int a4)
{
  int v6; // [sp+0h] [bp-10h] BYREF
  int v7; // [sp+4h] [bp-Ch] BYREF
  int v8; // [sp+8h] [bp-8h] BYREF
  int v9; // [sp+Ch] [bp-4h] BYREF

  v8 = a3;
  v9 = a4;
  sub_6AA2(&v6, &v7, &v8, &v9);
  if ( !v6 && !v7 && !v8 )
  {
    v6 = MEMORY[0x10210A64];
    v7 = MEMORY[0x1001A220];
    v8 = MEMORY[0x1001A22C];
  }
  v6 |= 0x11u;
  if ( a1 )
    v6 |= 0x44u;
  v6 |= 0xB000u;
  MEMORY[0x10210A64] = v6;
  MEMORY[0x1001A220] = v7;
  MEMORY[0x1001A22C] = v8;
  MEMORY[0x1000A000] |= 0x20000u;
  time_delay_ms(a2);
}


// ==================== sub_7EB0 @0x7EB0 size=40 ====================
int sub_7EB0()
{
  MEMORY[0x10210A64] &= 0xFFFF4FAA;
  MEMORY[0x1000A000] |= 0x20000u;
  return 268476416;
}


// ==================== sub_7ED8 @0x7ED8 size=24 ====================
int sub_7ED8()
{
  int result; // r0

  result = MEMORY[0x1001A204] | 0xB055;
  MEMORY[0x1001A204] |= 0xB055u;
  return result;
}


// ==================== sub_7F08 @0x7F08 size=56 ====================
int __fastcall sub_7F08(int a1, unsigned int a2)
{
  int v4; // r2
  int v5; // r3

  MEMORY[0x10283C] = 1;
  MEMORY[0x102840] = a2;
  if ( sub_856A() || sub_611A() >= 0 )
  {
    sub_7C90();
    return sub_7CEC();
  }
  else
  {
    sub_11E2C(a1, a2, v4, v5);
    return a1;
  }
}


// ==================== sub_7F40 @0x7F40 size=42 ====================
int sub_7F40()
{
  MEMORY[0x10283C] = 0;
  if ( !sub_856A() && sub_611A() < 0 )
    return sub_11E34();
  sub_7D20();
  return sub_7CAA();
}


// ==================== sub_7F6A @0x7F6A size=24 ====================
int sub_7F6A()
{
  if ( !sub_856A() )
    sub_7ED8();
  sub_7D38();
  return sub_7CC4();
}


// ==================== sub_7F82 @0x7F82 size=6 ====================
int sub_7F82()
{
  return MEMORY[0x10283C];
}


// ==================== sub_7F88 @0x7F88 size=6 ====================
int sub_7F88()
{
  return MEMORY[0x102840];
}


// ==================== sub_7F8E @0x7F8E size=102 ====================
BOOL sub_7F8E()
{
  if ( !sub_8508() )
    return 1;
  if ( !MEMORY[0x10283D] )
  {
    if ( MEMORY[0x100020] == 1176814887
      && MEMORY[0x100024] == -861389635
      && MEMORY[0x100028] == 1815030690
      && MEMORY[0x10002C] == -1063203184 )
    {
      MEMORY[0x100024] = 0;
      MEMORY[0x100020] = 0;
      MEMORY[0x10002C] = 0;
      MEMORY[0x100028] = 0;
      MEMORY[0x10283D] = 1;
    }
    else
    {
      MEMORY[0x10283D] = 2;
    }
  }
  return MEMORY[0x10283D] == 1;
}


// ==================== sub_7FF4 @0x7FF4 size=356 ====================
unsigned int __fastcall sub_7FF4(int a1, int a2, int a3)
{
  BOOL v6; // r8
  BOOL v7; // r11
  unsigned int v8; // r10
  unsigned int v9; // r6
  int v10; // r5
  unsigned int v11; // r0
  int v13; // r0
  int v14; // r0
  int v15; // r0
  int v16; // r4
  int v17; // r0
  int v18; // r0
  unsigned int v19; // r5
  int v20; // r0
  unsigned int v21; // [sp+0h] [bp-10h]
  int v22; // [sp+4h] [bp-Ch]
  __int64 v23; // [sp+8h] [bp-8h]

  v6 = 0;
  v7 = sub_7F8E();
  v8 = 0;
  v21 = 0;
  v9 = 0;
  v22 = sub_8430();
  LODWORD(v23) = sub_83EC(v22);
  HIDWORD(v23) = sub_83F6();
  v10 = sub_611A();
  if ( (v10 & 4) != 0 )
  {
    v6 = (v10 & 0x10) != 0;
  }
  else
  {
    if ( sub_84FE() )
      return 0;
    if ( !v22 )
    {
      v11 = v23 | HIDWORD(v23);
      if ( !v23 )
      {
        if ( a1 )
        {
          v11 = *(unsigned __int8 *)(a1 + 13);
          switch ( *(_BYTE *)(a1 + 13) )
          {
            case 1:
              return 0;
            case 3:
              v11 = *(unsigned __int16 *)(a1 + 14);
              if ( v11 < 0xFF )
                return 0;
              break;
            case 4:
              v11 = sub_8512();
              if ( v11 )
              {
                if ( a2 )
                {
                  if ( *(_BYTE *)(a2 + 8) )
                    goto LABEL_14;
                  v11 = *(unsigned __int8 *)(a2 + 9);
                  if ( *(_BYTE *)(a2 + 9) )
                    goto LABEL_14;
                }
              }
              break;
            default:
              break;
          }
        }
        if ( !sub_851C(v11) && v7 )
          v6 = 1;
        goto LABEL_27;
      }
    }
LABEL_14:
    if ( !a1 )
      return 0;
    if ( *(unsigned __int8 *)(a1 + 13) < 4u )
      return 0;
    if ( *(unsigned __int16 *)(a1 + 14) >= 0xFFu )
      return 0;
    if ( !a3 )
      return 0;
    v13 = *(_DWORD *)(a3 + 8);
    if ( !(v13 << 31) )
      return 0;
    if ( (v13 & 2) != 0 && !((int (*)(void))sub_851C)() && v7 )
      v6 = 1;
  }
LABEL_27:
  v14 = trace_begin(1u, 1);
  if ( sub_8200(v14) && !sub_84EA() )
  {
    if ( (v10 & 4) != 0 && (v10 & 0x10) != 0 )
    {
      v9 = 1000 * BYTE2(v10);
    }
    else if ( a3 )
    {
      v15 = *(_DWORD *)(a3 + 8);
      if ( v15 << 31 )
      {
        if ( (v15 & 2) != 0 )
          v9 = 1000 * BYTE2(v15);
      }
    }
    if ( !v9 )
      v9 = 8000;
  }
  else
  {
    v9 = 500;
  }
  v16 = sub_380();
  if ( v16 )
  {
    sub_368();
    v17 = time_get_tick();
    v8 = sub_280(v17);
  }
  sub_7F08(v6, v9);
  v18 = time_get_tick();
  v19 = sub_280(v18);
  if ( v16 )
  {
    sub_346();
    v20 = time_get_tick();
    v21 = sub_280(v20);
  }
  return trace_end(1u, v8, v19, v21);
}


// ==================== sub_8158 @0x8158 size=8 ====================
int sub_8158()
{
  return MEMORY[0x102830]();
}


// ==================== sub_8180 @0x8180 size=12 ====================
int sub_8180()
{
  int result; // r0

  result = MEMORY[0x1000A000] | 0x20;
  MEMORY[0x1000A000] |= 0x20u;
  return result;
}


// ==================== sub_818C @0x818C size=10 ====================
int sub_818C()
{
  return (MEMORY[0x1000A000] >> 5) & 1;
}


// ==================== sub_8196 @0x8196 size=24 ====================
int __fastcall sub_8196(int result)
{
  unsigned int i; // r1

  for ( i = 0; i < 8; ++i )
    *(_DWORD *)(4 * i + 0x1000A060) = *(_DWORD *)(result + 4 * i);
  return result;
}


// ==================== sub_81AE @0x81AE size=20 ====================
unsigned int sub_81AE()
{
  unsigned int result; // r0

  for ( result = 0; result < 8; ++result )
    *(_DWORD *)(4 * result + 0x1000A060) = 0;
  return result;
}


// ==================== sub_81C2 @0x81C2 size=12 ====================
int sub_81C2()
{
  int result; // r0

  result = MEMORY[0x1000A000] | 0x10;
  MEMORY[0x1000A000] |= 0x10u;
  return result;
}


// ==================== sub_81CE @0x81CE size=12 ====================
int sub_81CE()
{
  int result; // r0

  result = MEMORY[0x1000A000] | 0x40;
  MEMORY[0x1000A000] |= 0x40u;
  return result;
}


// ==================== sub_81DA @0x81DA size=16 ====================
int sub_81DA()
{
  MEMORY[0x1000A080] = -1375024150;
  MEMORY[0x1000A084] = -845844456;
  MEMORY[0x1000A088] = 1177106705;
  return 268476544;
}


// ==================== sub_8200 @0x8200 size=16 ====================
int sub_8200()
{
  return HIWORD(MEMORY[0x1000A000]) & 1;
}


// ==================== sub_8210 @0x8210 size=72 ====================
BOOL sub_8210()
{
  return (MEMORY[0x1000A0E8] & 0xF | MEMORY[0x1000A0C0] & 0xF | MEMORY[0x1000A0C8] & 0xF | MEMORY[0x1000A0E0] & 0xF) != 0;
}


// ==================== sub_8258 @0x8258 size=108 ====================
unsigned int __fastcall sub_8258(int a1)
{
  unsigned int v1; // r1
  unsigned int v2; // r1
  unsigned int v3; // r1
  unsigned int result; // r0

  if ( a1 )
    v1 = MEMORY[0x1000A0E8] | 0xF;
  else
    v1 = MEMORY[0x1000A0E8] & 0xFFFFFFF0;
  MEMORY[0x1000A0E8] = v1;
  if ( a1 )
    v2 = MEMORY[0x1000A0E0] | 0xF;
  else
    v2 = MEMORY[0x1000A0E0] & 0xFFFFFFF0;
  MEMORY[0x1000A0E0] = v2;
  if ( a1 )
    v3 = MEMORY[0x1000A0C8] | 0xF;
  else
    v3 = MEMORY[0x1000A0C8] & 0xFFFFFFF0;
  MEMORY[0x1000A0C8] = v3;
  if ( a1 )
    result = MEMORY[0x1000A0C0] | 0xF;
  else
    result = MEMORY[0x1000A0C0] & 0xFFFFFFF0;
  MEMORY[0x1000A0C0] = result;
  return result;
}


// ==================== sub_82C4 @0x82C4 size=56 ====================
int sub_82C4()
{
  MEMORY[0x1000A0EC] |= 1u;
  MEMORY[0x1000A0E4] |= 1u;
  MEMORY[0x1000A0CC] |= 1u;
  MEMORY[0x1000A0C4] |= 1u;
  return 268476416;
}


// ==================== sub_82FC @0x82FC size=72 ====================
BOOL sub_82FC()
{
  return (MEMORY[0x1000A0E8] & 0xF00
        | MEMORY[0x1000A0C0] & 0xF00
        | MEMORY[0x1000A0C8] & 0xF00
        | MEMORY[0x1000A0E0] & 0xF00) != 0;
}


// ==================== sub_8344 @0x8344 size=108 ====================
unsigned int __fastcall sub_8344(int a1)
{
  unsigned int v1; // r1
  unsigned int v2; // r1
  unsigned int v3; // r1
  unsigned int result; // r0

  if ( a1 )
    v1 = MEMORY[0x1000A0E8] | 0xF00;
  else
    v1 = MEMORY[0x1000A0E8] & 0xFFFFF0FF;
  MEMORY[0x1000A0E8] = v1;
  if ( a1 )
    v2 = MEMORY[0x1000A0E0] | 0xF00;
  else
    v2 = MEMORY[0x1000A0E0] & 0xFFFFF0FF;
  MEMORY[0x1000A0E0] = v2;
  if ( a1 )
    v3 = MEMORY[0x1000A0C8] | 0xF00;
  else
    v3 = MEMORY[0x1000A0C8] & 0xFFFFF0FF;
  MEMORY[0x1000A0C8] = v3;
  if ( a1 )
    result = MEMORY[0x1000A0C0] | 0xF00;
  else
    result = MEMORY[0x1000A0C0] & 0xFFFFF0FF;
  MEMORY[0x1000A0C0] = result;
  return result;
}


// ==================== sub_83B0 @0x83B0 size=56 ====================
int sub_83B0()
{
  MEMORY[0x1000A0EC] |= 0x100u;
  MEMORY[0x1000A0E4] |= 0x100u;
  MEMORY[0x1000A0CC] |= 0x100u;
  MEMORY[0x1000A0C4] |= 0x100u;
  return 268476416;
}


// ==================== sub_83EC @0x83EC size=10 ====================
int sub_83EC()
{
  return (MEMORY[0x11C10060] >> 4) & 1;
}


// ==================== sub_83F6 @0x83F6 size=10 ====================
int sub_83F6()
{
  return (MEMORY[0x11C10060] >> 5) & 1;
}


// ==================== sub_8400 @0x8400 size=22 ====================
int __fastcall sub_8400(int result)
{
  unsigned int i; // r1

  for ( i = 0; i < 4; ++i )
    *(_DWORD *)(result + 4 * i) = *(_DWORD *)(4 * i + 0x11C10070);
  return result;
}


// ==================== sub_8416 @0x8416 size=26 ====================
int sub_8416()
{
  unsigned int i; // r0

  for ( i = 0; i < 4; ++i )
  {
    if ( *(_DWORD *)(4 * i + 0x11C10070) )
      return 0;
  }
  return 1;
}


// ==================== sub_8430 @0x8430 size=10 ====================
int sub_8430()
{
  return (MEMORY[0x11C10060] >> 1) & 1;
}


// ==================== sub_843A @0x843A size=10 ====================
int sub_843A()
{
  return (MEMORY[0x11C10060] >> 2) & 1;
}


// ==================== efuse_get_bit3 (sub_8444) @0x8444 size=10 ====================
int efuse_get_bit3()
{
  return (MEMORY[0x11C10060] >> 3) & 1;
}


// ==================== efuse_get_usb_boot_bit (sub_844E) @0x844E size=10 ====================
int efuse_get_usb_boot_bit()
{
  return (MEMORY[0x11C10060] >> 8) & 1;
}


// ==================== sub_8458 @0x8458 size=10 ====================
int sub_8458()
{
  return (MEMORY[0x11C10130] >> 10) & 1;
}


// ==================== sub_8462 @0x8462 size=10 ====================
int sub_8462()
{
  return (MEMORY[0x11C10130] >> 8) & 1;
}


// ==================== efuse_read_pubk_hash (sub_846C) @0x846C size=24 ====================
int __fastcall efuse_read_pubk_hash(int result)
{
  unsigned int i; // r1

  for ( i = 0; i < 8; ++i )
    *(_DWORD *)(result + 4 * i) = *(_DWORD *)(4 * i + 0x11C10090);
  return result;
}


// ==================== efuse_get_key_slot (sub_8484) @0x8484 size=10 ====================
int efuse_get_key_slot()
{
  return MEMORY[0x11C10130] & 3;
}


// ==================== sub_848E @0x848E size=10 ====================
int sub_848E()
{
  return (MEMORY[0x11C10130] >> 7) & 1;
}


// ==================== efuse_get_bit2_1120 (sub_8498) @0x8498 size=10 ====================
int efuse_get_bit2_1120()
{
  return (MEMORY[0x11C10120] >> 2) & 1;
}


// ==================== sub_84A2 @0x84A2 size=22 ====================
int sub_84A2()
{
  if ( efuse_get_bit2_1120() )
    return 1;
  else
    return (MEMORY[0x11C10060] >> 7) & 1;
}


// ==================== sub_84B8 @0x84B8 size=10 ====================
int sub_84B8()
{
  return MEMORY[0x11C10120] & 1;
}


// ==================== sub_84C2 @0x84C2 size=10 ====================
int sub_84C2()
{
  return (MEMORY[0x11C10130] >> 5) & 1;
}


// ==================== sub_84CC @0x84CC size=10 ====================
int sub_84CC()
{
  return (MEMORY[0x11C10130] >> 2) & 1;
}


// ==================== efuse_get_bit17 (sub_84D6) @0x84D6 size=10 ====================
int efuse_get_bit17()
{
  return (MEMORY[0x11C10060] >> 17) & 1;
}


// ==================== sub_84E0 @0x84E0 size=10 ====================
int sub_84E0()
{
  return (MEMORY[0x11C10060] >> 18) & 1;
}


// ==================== sub_84EA @0x84EA size=10 ====================
int sub_84EA()
{
  return MEMORY[0x11C10060] & 1;
}


// ==================== sub_84F4 @0x84F4 size=10 ====================
int sub_84F4()
{
  return (MEMORY[0x11C10060] >> 9) & 1;
}


// ==================== sub_84FE @0x84FE size=10 ====================
int sub_84FE()
{
  return (MEMORY[0x11C10060] >> 10) & 1;
}


// ==================== sub_8508 @0x8508 size=10 ====================
int sub_8508()
{
  return (MEMORY[0x11C10060] >> 11) & 1;
}


// ==================== sub_8512 @0x8512 size=10 ====================
int sub_8512()
{
  return (MEMORY[0x11C10130] >> 9) & 1;
}


// ==================== sub_851C @0x851C size=10 ====================
int sub_851C()
{
  return (MEMORY[0x11C10060] >> 12) & 1;
}


// ==================== sub_8526 @0x8526 size=10 ====================
int sub_8526()
{
  return (MEMORY[0x11C10130] >> 6) & 1;
}


// ==================== efuse_get_boot_strap_bit (sub_8530) @0x8530 size=10 ====================
int efuse_get_boot_strap_bit()
{
  return (MEMORY[0x11C10130] >> 12) & 1;
}


// ==================== efuse_get_secure_boot (sub_853A) @0x853A size=14 ====================
int efuse_get_secure_boot()
{
  return ((int)(MEMORY[0x11C10130] << 18) >> 31) + 1;
}


// ==================== sub_8548 @0x8548 size=24 ====================
BOOL sub_8548()
{
  return (MEMORY[0x11C10130] & 0x10) != 0 || (MEMORY[0x11C10060] & 0x2000) != 0;
}


// ==================== sub_8560 @0x8560 size=10 ====================
int sub_8560()
{
  return (MEMORY[0x11C10060] >> 14) & 1;
}


// ==================== sub_856A @0x856A size=10 ====================
int sub_856A()
{
  return (MEMORY[0x11C10060] >> 15) & 1;
}


// ==================== efuse_get_misc_bit? (sub_8574) @0x8574 size=10 ====================
int efuse_get_misc_bit?()
{
  return (MEMORY[0x11C10130] >> 11) & 1;
}


// ==================== sub_857E @0x857E size=10 ====================
int sub_857E()
{
  return HIWORD(MEMORY[0x11C10060]) & 1;
}


// ==================== sub_8594 @0x8594 size=20 ====================
int __fastcall sub_8594(unsigned int a1, _DWORD *a2)
{
  if ( a1 >= 0x10 )
    return 0;
  if ( a2 )
    *a2 = 16;
  return 24615;
}


// ==================== sub_85A8 @0x85A8 size=80 ====================
int __fastcall sub_85A8(_DWORD *a1, int a2, unsigned int a3, int a4, int a5)
{
  if ( !a1 )
    return 24614;
  mem_set_bytes(a1, 0, 16);
  if ( a2 )
  {
    if ( !a3 )
      return 24610;
    if ( a3 <= 0xFF )
      return 24609;
    if ( a2 << 30 )
      return 24611;
    *a1 = a2;
    a1[1] = a3;
  }
  a1[2] = a4;
  a1[3] = a5;
  return 0;
}


// ==================== sub_85F8 @0x85F8 size=22 ====================
int __fastcall sub_85F8(unsigned int a1, _DWORD *a2)
{
  if ( a1 >= 0xE60 )
    return 0;
  if ( a2 )
    *a2 = 3680;
  return 24618;
}


// ==================== sub_8610 @0x8610 size=58 ====================
int __fastcall sub_8610(_DWORD *a1)
{
  int result; // r0

  result = sub_8594(0x10u, a1);
  if ( !result )
  {
    result = sub_90B8(3680, a1);
    if ( !result )
    {
      result = sub_8708(3680, a1);
      if ( !result )
        return sub_85F8(0xE60u, a1);
    }
  }
  return result;
}


// ==================== sub_864A @0x864A size=22 ====================
int *sub_864A()
{
  if ( sub_8548() || sub_856A() )
    return &dword_130C4;
  else
    return &dword_131E0;
}


// ==================== sub_8660 @0x8660 size=54 ====================
int *__fastcall sub_8660(char a1)
{
  int v1; // r0

  v1 = a1 & 3;
  if ( v1 )
  {
    if ( (v1 & 2) == 0 || sub_8548() || sub_856A() )
      return &dword_130C4;
    else
      return &dword_131E0;
  }
  else if ( sub_8548() || sub_856A() )
  {
    return &dword_130C4;
  }
  else
  {
    return &dword_131E0;
  }
}


// ==================== sub_8696 @0x8696 size=24 ====================
int sub_8696()
{
  int *v0; // r0

  if ( sub_8548() || sub_856A() )
    v0 = &dword_130C4;
  else
    v0 = &dword_131E0;
  return *v0;
}


// ==================== sub_86AE @0x86AE size=4 ====================
int *sub_86AE()
{
  return &dword_13084;
}


// ==================== sub_86B2 @0x86B2 size=46 ====================
int *__fastcall sub_86B2(char a1)
{
  char v1; // r4

  v1 = a1 & 7;
  if ( (a1 & 7) == 0 )
    return &dword_13084;
  if ( (a1 & 4) != 0 && !sub_8560() && !sub_856A() )
    return &dword_1309C;
  if ( (v1 & 2) != 0 )
    return &dword_130B0;
  return &dword_13084;
}


// ==================== sub_86E0 @0x86E0 size=4 ====================
int *sub_86E0()
{
  return &dword_131FC;
}


// ==================== sub_86E4 @0x86E4 size=6 ====================
int sub_86E4()
{
  return 16;
}


// ==================== sub_8704 @0x8704 size=4 ====================
int sub_8704()
{
  return 0;
}


// ==================== sub_8708 @0x8708 size=22 ====================
int __fastcall sub_8708(unsigned int a1, _DWORD *a2)
{
  if ( a1 >= 0xE60 )
    return 0;
  if ( a2 )
    *a2 = 3680;
  return 24617;
}


// ==================== auth_verify_with_descriptor (sub_871E) @0x871E size=574 ====================
unsigned int __fastcall auth_verify_with_descriptor(_DWORD *a1, int a2, _DWORD *a3, int a4, int a5)
{
  int v9; // r7
  int v10; // r10
  bool v11; // zf
  unsigned int v12; // r5
  int v13; // r0
  int v14; // r0
  int v15; // r0
  unsigned int v16; // r0
  int v17; // r1
  int v18; // r1
  int v19; // r1
  unsigned int v20; // r1
  void (__fastcall *v21)(int, _DWORD); // r2
  void (__fastcall *v22)(int, int); // r2
  int v23; // r0
  void (__fastcall *v24)(int, _DWORD); // r2
  void (__fastcall *v25)(int, int); // r2
  void (__fastcall *v26)(int, int); // r2
  void (__fastcall *v27)(int, int); // r2
  void (__fastcall *v28)(int, _DWORD, int, int, _DWORD *, int); // r4
  void (__fastcall *v29)(int, _DWORD, int, int); // r4
  _DWORD *v31; // [sp+0h] [bp-84h] BYREF
  int v32; // [sp+4h] [bp-80h]
  _BYTE v33[28]; // [sp+8h] [bp-7Ch] BYREF
  int v34; // [sp+24h] [bp-60h]
  _BYTE *v35; // [sp+28h] [bp-5Ch]
  int v36; // [sp+2Ch] [bp-58h]
  int v37; // [sp+30h] [bp-54h]
  int v38; // [sp+34h] [bp-50h]
  int v39; // [sp+38h] [bp-4Ch]
  int v40; // [sp+3Ch] [bp-48h]
  int v41; // [sp+40h] [bp-44h]
  _BYTE v42[32]; // [sp+44h] [bp-40h] BYREF
  int v43; // [sp+64h] [bp-20h] BYREF
  int v44; // [sp+68h] [bp-1Ch]
  int v45; // [sp+6Ch] [bp-18h] BYREF
  int v46; // [sp+70h] [bp-14h]
  int v47; // [sp+74h] [bp-10h]
  int v48; // [sp+78h] [bp-Ch]
  int v49; // [sp+7Ch] [bp-8h]
  _BYTE v50[4]; // [sp+80h] [bp-4h] BYREF

  v9 = 0;
  v10 = 0;
  mem_set_bytes(&v43, 0, 8);
  mem_set_bytes(&v45, 0, 24);
  v11 = a3 == 0;
  v12 = 24576;
  while ( 1 )
  {
    if ( v11 )
      goto LABEL_58;
    v13 = a3[7];
    v11 = v13 == 0;
    if ( v13 )
    {
      v14 = a3[8];
      v11 = v14 == 0;
      if ( v14 )
      {
        v15 = a3[9];
        v11 = v15 == 0;
        if ( v15 )
        {
          v16 = a3[18];
          v11 = v16 == 0;
          if ( v16 )
          {
            if ( !(a3[17] << 31) )
              goto LABEL_16;
            v11 = *a3 == 0;
            if ( *a3 )
            {
              v17 = a3[2];
              v11 = v17 == 0;
              if ( v17 )
              {
                v18 = a3[3];
                v11 = v18 == 0;
                if ( v18 )
                {
                  if ( a4 )
                    break;
                  v19 = a3[5];
                  v11 = v19 == 0;
                  if ( v19 )
                    break;
                }
              }
            }
          }
        }
      }
    }
  }
  v9 = *a1;
  if ( *a1 && !a4 )
  {
    v20 = a1[1];
    if ( !v20 || v20 < a3[16] )
    {
      v12 = 24609;
      goto LABEL_58;
    }
  }
  else
  {
    v9 = a3[15];
  }
LABEL_16:
  if ( v16 > a3[16] )
  {
    v12 = 24605;
    goto LABEL_58;
  }
  v43 = a3[13];
  v44 = a3[14];
  v21 = (void (__fastcall *)(int, _DWORD))a1[2];
  if ( v21 )
    v21(7, 0);
  v12 = ((int (__fastcall *)(_DWORD *, int, int *, int))a3[7])(a1, a2, &v43, a5);
  if ( v12 >= 0xFF )
    goto LABEL_54;
  v12 = ((int (__fastcall *)(_DWORD *, int, int *, _BYTE *, int))a3[9])(a1, a2, &v43, v42, a5);
  if ( v12 >= 0xFF )
  {
    ((void (__fastcall *)(_DWORD *, int, int *, int))a3[8])(a1, a2, &v43, a5);
    goto LABEL_54;
  }
  v12 = ((int (__fastcall *)(_DWORD *, int, int *, int))a3[8])(a1, a2, &v43, a5);
  if ( v12 >= 0xFF )
  {
LABEL_54:
    v26 = (void (__fastcall *)(int, int))a1[2];
    if ( v26 )
      v26(7, 1);
    goto LABEL_58;
  }
  v22 = (void (__fastcall *)(int, int))a1[2];
  if ( v22 )
    v22(7, 1);
  if ( (a3[17] & 2) != 0 )
  {
    if ( !a5 )
    {
      v12 = 24619;
      goto LABEL_58;
    }
    v23 = sub_8696();
    mem_copy_bytes(a5, v42, v23);
  }
  if ( a4 )
    goto LABEL_58;
  if ( a3[17] << 31 )
  {
    v45 = a3[15];
    v46 = a3[16];
    v47 = v9;
    v48 = a3[16];
    mem_copy_bytes(v50, a3, 4);
    v49 = 1;
    v24 = (void (__fastcall *)(int, _DWORD))a1[2];
    if ( v24 )
      v24(8, 0);
    v12 = ((int (__fastcall *)(_DWORD *, int, int *, int))a3[2])(a1, a2, &v45, a5);
    if ( v12 >= 0xFF )
      goto LABEL_56;
    v12 = ((int (__fastcall *)(_DWORD *, int, int *, int))a3[5])(a1, a2, &v45, a5);
    if ( v12 >= 0xFF )
    {
      ((void (__fastcall *)(_DWORD *, int, int *, int))a3[3])(a1, a2, &v45, a5);
      goto LABEL_56;
    }
    v12 = ((int (__fastcall *)(_DWORD *, int, int *, int))a3[3])(a1, a2, &v45, a5);
    if ( v12 >= 0xFF )
    {
LABEL_56:
      v27 = (void (__fastcall *)(int, int))a1[2];
      if ( v27 )
        v27(8, 1);
      goto LABEL_58;
    }
    v10 = (a3[17] >> 25) & 1;
    v25 = (void (__fastcall *)(int, int))a1[2];
    if ( v25 )
      v25(8, 1);
  }
  else
  {
    v9 = a3[15];
  }
  if ( v10 )
  {
    v31 = a1;
    v32 = a2;
    mem_copy_bytes(v33, a3 + 6, 28);
    v34 = a5;
    v35 = v42;
    v36 = 32;
    v37 = v9;
    v38 = a3[16];
    v39 = 32;
    v40 = 2048;
    v12 = auth_rsa_verify(&v31);
    if ( v12 < 0xFF && v41 != 1 )
      v12 = 24582;
  }
  else if ( mem_cmp(v9, v42, a3[18]) )
  {
    v12 = 24582;
  }
LABEL_58:
  v28 = (void (__fastcall *)(int, _DWORD, int, int, _DWORD *, int))a1[3];
  if ( v28 )
    v28(7, 0, v44, v43, v31, v32);
  v29 = (void (__fastcall *)(int, _DWORD, int, int))a1[3];
  if ( v29 )
    v29(8, 0, v46, v45);
  return v12;
}


// ==================== auth_verify_case123 (sub_895C) @0x895C size=12 ====================
unsigned int __fastcall auth_verify_case123(_DWORD *a1, int a2, _DWORD *a3, int a4)
{
  return auth_verify_with_descriptor(a1, a2, a3, 0, a4);
}


// ==================== auth_compute_hash (sub_8968) @0x8968 size=90 ====================
unsigned int __fastcall auth_compute_hash(int a1, int a2, int a3, int a4, int a5, int a6)
{
  unsigned int v10; // r4

  v10 = (*(int (__fastcall **)(int, int, int, int))(a3 + 28))(a1, a2, a4, a6);
  if ( v10 < 0xFF )
  {
    v10 = (*(int (__fastcall **)(int, int, int, int))(a3 + 36))(a1, a2, a4, a5);
    if ( v10 >= 0xFF || (v10 = (*(int (__fastcall **)(int, int, int, int))(a3 + 32))(a1, a2, a4, a6), v10 < 0xFF) )
      (*(void (__fastcall **)(int, int, int, int))(a3 + 32))(a1, a2, a4, a6);
  }
  return v10;
}


// ==================== sub_89C2 @0x89C2 size=88 ====================
unsigned int __fastcall sub_89C2(int a1, int a2, int a3, int a4, int a5)
{
  unsigned int v9; // r4

  v9 = (*(int (__fastcall **)(int, int, int, int))(a3 + 8))(a1, a2, a4, a5);
  if ( v9 < 0xFF )
  {
    v9 = (*(int (__fastcall **)(int, int, int, int))(a3 + 20))(a1, a2, a4, a5);
    if ( v9 >= 0xFF || (v9 = (*(int (__fastcall **)(int, int, int, int))(a3 + 12))(a1, a2, a4, a5), v9 < 0xFF) )
      (*(void (__fastcall **)(int, int, int, int))(a3 + 12))(a1, a2, a4, a5);
  }
  return v9;
}


// ==================== auth_verify_sub_blocks (sub_8A1A) @0x8A1A size=220 ====================
void __fastcall auth_verify_sub_blocks(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11)
{
  unsigned int v13; // r8
  unsigned int v14; // r9
  void (__fastcall *v15)(int, _DWORD); // r2
  int v16; // r0
  int v17; // r0
  void (__fastcall *v18)(int, unsigned int, unsigned int); // r6
  void (__fastcall *v19)(int, int); // r2
  _DWORD v20[2]; // [sp+8h] [bp-94h] BYREF
  _BYTE v21[28]; // [sp+10h] [bp-8Ch] BYREF
  int v22; // [sp+2Ch] [bp-70h]
  _BYTE *v23; // [sp+30h] [bp-6Ch]
  int v24; // [sp+34h] [bp-68h]
  int v25; // [sp+38h] [bp-64h]
  int v26; // [sp+3Ch] [bp-60h]
  int v27; // [sp+40h] [bp-5Ch]
  int v28; // [sp+44h] [bp-58h]
  _BYTE v29[32]; // [sp+4Ch] [bp-50h] BYREF
  _DWORD v30[2]; // [sp+6Ch] [bp-30h] BYREF
  _DWORD v31[7]; // [sp+74h] [bp-28h] BYREF
  int v32; // [sp+90h] [bp-Ch]
  int v33; // [sp+94h] [bp-8h]
  int v34; // [sp+98h] [bp-4h]

  v31[6] = a1;
  v32 = a2;
  v33 = a3;
  v34 = a4;
  v13 = 0;
  v14 = 0;
  v15 = *(void (__fastcall **)(int, _DWORD))(a1 + 8);
  if ( v15 )
    v15(a11, 0);
  v30[0] = a7;
  v30[1] = a8;
  if ( auth_compute_hash(a1, v32, v33, (int)v30, (int)v29, a4) < 0xFF )
  {
    v16 = time_get_tick();
    v13 = sub_280(v16);
    v31[0] = a9;
    v31[1] = a10;
    v31[2] = a5;
    v31[3] = a10;
    v31[5] = a6;
    v31[4] = 0;
    if ( sub_89C2(a1, v32, v33, (int)v31, a4) < 0xFF )
    {
      v17 = time_get_tick();
      v14 = sub_280(v17);
      v20[0] = a1;
      v20[1] = v32;
      mem_copy_bytes(v21, v33 + 24, 28);
      v22 = a4;
      v23 = v29;
      v24 = 32;
      v25 = a5;
      v26 = a10;
      v27 = 32;
      v28 = 2048;
      auth_rsa_verify(v20);
    }
  }
  v18 = *(void (__fastcall **)(int, unsigned int, unsigned int))(a1 + 12);
  if ( v18 )
    v18(a11, v13, v14);
  v19 = *(void (__fastcall **)(int, int))(a1 + 8);
  if ( v19 )
    v19(a11, 1);
  JUMPOUT(0x8958);
}


// ==================== auth_verify_type5 (sub_8AF6) @0x8AF6 size=940 ====================
void __fastcall auth_verify_type5(int *a1, int a2, _DWORD *a3, int a4)
{
  int v7; // r7
  unsigned int v8; // r0
  int *v9; // r8
  int v10; // r0
  void (__fastcall *v11)(int, _DWORD, int, int); // r5
  int v12; // r8
  int v13; // r9
  void (__fastcall *v14)(int, _DWORD); // r2
  unsigned int v15; // r4
  void (__fastcall *v16)(int, int); // r2
  unsigned int v17; // r0
  unsigned int v18; // r0
  int v19; // r11
  int v20; // r8
  int v21; // r9
  int v22; // r11
  void (__fastcall *v23)(int, _DWORD); // r2
  unsigned int v24; // r4
  void (__fastcall *v25)(int, int); // r2
  unsigned int v26; // r0
  unsigned int v27; // r0
  unsigned int v28; // r0
  int v29; // r8
  void (__fastcall *v30)(int, _DWORD); // r2
  unsigned int v31; // r4
  void (__fastcall *v32)(int, int); // r2
  unsigned int v33; // r0
  int v34; // r11
  int v35; // r8
  int v36; // r9
  int v37; // r11
  void (__fastcall *v38)(int, _DWORD); // r2
  unsigned int v39; // r4
  void (__fastcall *v40)(int, int); // r2
  unsigned int v41; // r0
  unsigned int v42; // r0
  unsigned int v43; // r0
  _BYTE v44[32]; // [sp+1Ch] [bp-38h] BYREF
  int v45; // [sp+3Ch] [bp-18h] BYREF
  int v46; // [sp+40h] [bp-14h]
  int *v47; // [sp+44h] [bp-10h]
  int v48; // [sp+48h] [bp-Ch]
  _DWORD *v49; // [sp+4Ch] [bp-8h]
  int v50; // [sp+50h] [bp-4h]

  v47 = a1;
  v48 = a2;
  v49 = a3;
  v50 = a4;
  v7 = 0;
  mem_set_bytes(&v45, 0, 8);
  if ( !a3 )
    goto LABEL_20;
  if ( !a3[7] )
    goto LABEL_20;
  if ( !a3[8] )
    goto LABEL_20;
  if ( !a3[9] )
    goto LABEL_20;
  v8 = a3[18];
  if ( !v8 )
    goto LABEL_20;
  if ( a3[17] << 31 )
  {
    if ( !a3[2] || !a3[3] || !a3[5] )
      goto LABEL_20;
    v7 = *a1;
    if ( *a1 )
    {
      if ( (unsigned int)a1[1] < 0x100 )
        goto LABEL_20;
    }
    else
    {
      v7 = a3[15];
    }
  }
  if ( v8 <= a3[16] )
  {
    v9 = (int *)a3[15];
    v10 = *v9;
    if ( *v9 == 2 )
    {
      v12 = (int)(v9 + 1);
      v13 = a3[15] + 1328;
      v45 = a3[13];
      v46 = a3[14];
      v14 = (void (__fastcall *)(int, _DWORD))a1[2];
      if ( v14 )
        v14(7, 0);
      v15 = auth_compute_hash((int)a1, v48, (int)a3, (int)&v45, (int)v44, a4);
      v16 = (void (__fastcall *)(int, int))a1[2];
      if ( v16 )
        v16(7, 1);
      if ( v15 < 0xFF )
      {
        if ( !(a3[17] << 31)
          || (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v12 + 16, v12, 1068, v12 + 1068, 256, 45), v17 < 0xFF)
          && (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v12 + 540, v13, 60, v13 + 60, 256, 46), v18 < 0xFF) )
        {
          mem_cmp(v13 + 28, v44, a3[18]);
        }
      }
    }
    else
    {
      switch ( v10 )
      {
        case 5:
          v19 = a3[15];
          v20 = (int)(v9 + 1);
          v21 = v19 + 1328;
          v22 = v19 + 2168;
          v45 = a3[13];
          v46 = a3[14];
          v23 = (void (__fastcall *)(int, _DWORD))a1[2];
          if ( v23 )
            v23(7, 0);
          v24 = auth_compute_hash((int)a1, v48, (int)a3, (int)&v45, (int)v44, a4);
          v25 = (void (__fastcall *)(int, int))a1[2];
          if ( v25 )
            v25(7, 1);
          if ( v24 < 0xFF )
          {
            if ( !(a3[17] << 31)
              || (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v20 + 16, v20, 1068, v20 + 1068, 256, 47), v26 < 0xFF)
              && (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v20 + 540, v21, 584, v21 + 584, 256, 48), v27 < 0xFF)
              && (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v21 + 16, v22, 60, v22 + 60, 256, 49), v28 < 0xFF) )
            {
              mem_cmp(v21 + 552, v44, a3[18]);
            }
          }
          break;
        case 6:
          v29 = (int)(v9 + 1);
          v45 = a3[13];
          v46 = a3[14];
          v30 = (void (__fastcall *)(int, _DWORD))a1[2];
          if ( v30 )
            v30(7, 0);
          v31 = auth_compute_hash((int)a1, v48, (int)a3, (int)&v45, (int)v44, a4);
          v32 = (void (__fastcall *)(int, int))a1[2];
          if ( v32 )
            v32(7, 1);
          if ( v31 < 0xFF )
          {
            if ( !(a3[17] << 31)
              || (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v29 + 20, v29, 584, v29 + 584, 256, 52), v33 < 0xFF) )
            {
              mem_cmp(v29 + 552, v44, a3[18]);
            }
          }
          break;
        case 7:
          v34 = a3[15];
          v35 = (int)(v9 + 1);
          v36 = v34 + 1328;
          v37 = v34 + 2176;
          v45 = a3[13];
          v46 = a3[14];
          v38 = (void (__fastcall *)(int, _DWORD))a1[2];
          if ( v38 )
            v38(7, 0);
          v39 = auth_compute_hash((int)a1, v48, (int)a3, (int)&v45, (int)v44, a4);
          v40 = (void (__fastcall *)(int, int))a1[2];
          if ( v40 )
            v40(7, 1);
          if ( v39 < 0xFF )
          {
            if ( !(a3[17] << 31)
              || (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v35 + 16, v35, 1068, v35 + 1068, 256, 67), v41 < 0xFF)
              && (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v35 + 540, v36, 592, v36 + 592, 256, 68), v42 < 0xFF)
              && (auth_verify_sub_blocks((int)a1, v48, (int)a3, a4, v7, v36 + 16, v37, 68, v37 + 68, 256, 69), v43 < 0xFF) )
            {
              mem_cmp(v36 + 560, v44, a3[18]);
            }
          }
          break;
      }
    }
  }
LABEL_20:
  v11 = (void (__fastcall *)(int, _DWORD, int, int))a1[3];
  if ( v11 )
    v11(7, 0, v46, v45);
  JUMPOUT(0x8958);
}


// ==================== sub_8EA2 @0x8EA2 size=330 ====================
void __fastcall sub_8EA2(int a1, int a2, int a3, int a4, int a5)
{
  int (__fastcall *v9)(int, int, int, int); // r5
  unsigned int i; // r6
  _DWORD v11[4]; // [sp+0h] [bp-28h] BYREF
  unsigned int v12; // [sp+10h] [bp-18h]
  char v13; // [sp+18h] [bp-10h] BYREF

  if ( a3 )
  {
    if ( *(_DWORD *)(a3 + 20) )
    {
      v9 = *(int (__fastcall **)(int, int, int, int))(a3 + 28);
      if ( v9 )
      {
        if ( *(_DWORD *)(a3 + 32) && (!a4 || *(_DWORD *)(a3 + 36)) && (a4 || *(_DWORD *)(a3 + 40)) )
        {
          if ( *(_BYTE *)(a3 + 44) )
          {
            mem_copy_bytes(v11, a3, 24);
            v11[0] = *(_DWORD *)(a3 + 52);
            v11[1] = *(_DWORD *)(a3 + 48);
            v11[2] = &v13;
            v11[3] = *(_DWORD *)(a3 + 48);
            v12 = 91;
            if ( (unsigned int)(*(int (__fastcall **)(int, int, _DWORD *, int))(a3 + 28))(a1, a2, v11, a5) >= 0xFF )
              goto LABEL_27;
            for ( i = 0; i < 3; ++i )
            {
              if ( *(_DWORD *)(a3 + 4 * i + 52) )
              {
                v11[0] = *(_DWORD *)(a3 + 4 * i + 52);
                if ( (unsigned int)(*(int (__fastcall **)(int, int, _DWORD *, int))(a3 + 40))(a1, a2, v11, a5) < 0xFF )
                  continue;
              }
              (*(void (__fastcall **)(int, int, _DWORD *, int))(a3 + 32))(a1, a2, v11, a5);
              goto LABEL_27;
            }
            if ( (unsigned int)(*(int (__fastcall **)(int, int, _DWORD *, int))(a3 + 32))(a1, a2, v11, a5) < 0xFF )
            {
              mem_copy_bytes(v11, a3, 24);
              v12 = v12 & 0xFFFFFFFA | 4;
              if ( (unsigned int)(*(int (__fastcall **)(int, int, _DWORD *, int))(a3 + 28))(a1, a2, v11, a5) < 0xFF )
                goto LABEL_23;
            }
          }
          else if ( (unsigned int)v9(a1, a2, a3, a5) < 0xFF )
          {
LABEL_23:
            if ( a4 )
              (*(int (__fastcall **)(int, int, int, int))(a3 + 36))(a1, a2, a3, a5);
            else
              (*(int (__fastcall **)(int, int, int, int))(a3 + 40))(a1, a2, a3, a5);
            (*(void (__fastcall **)(int, int, int, int))(a3 + 32))(a1, a2, a3, a5);
          }
        }
      }
    }
  }
LABEL_27:
  JUMPOUT(0x8A16);
}


// ==================== sub_8FEC @0x8FEC size=12 ====================
void __fastcall sub_8FEC(int a1, int a2, int a3, int a4)
{
  sub_8EA2(a1, a2, a3, 0, a4);
}


// ==================== sub_8FF8 @0x8FF8 size=12 ====================
void __fastcall sub_8FF8(int a1, int a2, int a3, int a4)
{
  sub_8EA2(a1, a2, a3, 1, a4);
}


// ==================== sub_9004 @0x9004 size=72 ====================
void __fastcall sub_9004(int a1, int a2, int a3, int a4)
{
  _BYTE v8[24]; // [sp+4h] [bp-40h] BYREF
  _BYTE v9[40]; // [sp+1Ch] [bp-28h] BYREF

  mem_copy_bytes(v8, a3, 24);
  mem_copy_bytes(v9, a3 + 24, 20);
  v9[20] = 0;
  if ( a4 )
    sub_8FF8(a1, a2, (int)v8, 0);
  else
    sub_8FEC(a1, a2, (int)v8, 0);
}


// ==================== sub_904C @0x904C size=12 ====================
void __fastcall sub_904C(int a1, int a2, int a3)
{
  sub_9004(a1, a2, a3, 0);
}


// ==================== sub_9058 @0x9058 size=12 ====================
void __fastcall sub_9058(int a1, int a2, int a3)
{
  sub_9004(a1, a2, a3, 1);
}


// ==================== sub_9064 @0x9064 size=82 ====================
unsigned int __fastcall sub_9064(int a1, int a2, int (__fastcall **a3)(_DWORD, _DWORD, _DWORD, _DWORD), int a4, int a5)
{
  unsigned int result; // r0

  mem_set_bytes(a4, 0, 32);
  result = a3[3](a1, a2, a3, a5);
  if ( result < 0xFF )
  {
    result = a3[5](a1, a2, a3, a4);
    if ( result < 0xFF )
      return a3[4](a1, a2, a3, a5);
  }
  return result;
}


// ==================== sub_90B8 @0x90B8 size=22 ====================
int __fastcall sub_90B8(unsigned int a1, _DWORD *a2)
{
  if ( a1 >= 0xE60 )
    return 0;
  if ( a2 )
    *a2 = 3680;
  return 24616;
}


// ==================== auth_init_descriptor (sub_90CE) @0x90CE size=12 ====================
int __fastcall auth_init_descriptor(int result, int a2, int a3)
{
  *(_DWORD *)result = a2;
  *(_DWORD *)(result + 4) = a3;
  *(_BYTE *)(result + 8) = 0;
  *(_DWORD *)(result + 12) = 0;
  return result;
}


// ==================== auth_build_descriptor (sub_90DA) @0x90DA size=4 ====================
int __fastcall auth_build_descriptor(int a1, int a2)
{
  return auth_init_descriptor(a1, a2, 1);
}


// ==================== auth_dispatch_by_block_type (sub_90DE) @0x90DE size=726 ====================
int __fastcall auth_dispatch_by_block_type(int *a1, int a2, _DWORD *a3, int a4)
{
  unsigned int v5; // r4
  bool v6; // cf
  int v7; // r8
  unsigned int v8; // r7
  unsigned int v9; // r10
  int v10; // r9
  unsigned int v11; // r5
  int *v12; // r0
  unsigned int v13; // r0
  int *v14; // r0
  _DWORD *v15; // r1
  int *v16; // r0
  unsigned int v17; // r0
  int *v18; // r0
  int *v19; // r0
  unsigned int v20; // r0
  int *v21; // r0
  int v22; // r0
  unsigned int v23; // r2
  unsigned int v24; // r0
  int *v25; // r0
  int *v26; // r0
  unsigned int v27; // r0
  int v29; // [sp+4h] [bp-68h] BYREF
  _BYTE v30[20]; // [sp+8h] [bp-64h] BYREF
  _BYTE v31[28]; // [sp+1Ch] [bp-50h] BYREF
  int v32; // [sp+38h] [bp-34h]
  unsigned int v33; // [sp+3Ch] [bp-30h]
  _DWORD *v34; // [sp+40h] [bp-2Ch]
  int v35; // [sp+44h] [bp-28h]
  int v36; // [sp+48h] [bp-24h]
  int v37; // [sp+4Ch] [bp-20h]
  int v38; // [sp+50h] [bp-1Ch] BYREF
  int v39; // [sp+54h] [bp-18h]
  _BYTE *v40; // [sp+58h] [bp-14h]
  int *v41; // [sp+5Ch] [bp-10h]
  int v42; // [sp+60h] [bp-Ch]
  _DWORD *v43; // [sp+64h] [bp-8h]
  int v44; // [sp+68h] [bp-4h]

  v41 = a1;
  v42 = a2;
  v43 = a3;
  v44 = a4;
  v39 = a2;
  if ( !a3 )
    return 24576;
  v5 = auth_find_block_by_type(*a3, 0, &v38);
  v6 = v5 >= 0xFF;
  while ( !v6 )
  {
    v5 = auth_check_block_header(v38);
    v6 = v5 >= 0xFF;
    if ( v5 < 0xFF )
    {
      v7 = *(unsigned __int8 *)(v38 + 27);
      v8 = *(_DWORD *)(v38 + 44);
      v9 = *(_DWORD *)(v38 + 32) - v8;
      v10 = *a3;
      v11 = *a3 + v9;
      mem_set_bytes(&v29, 0, 76);
      v12 = sub_864A();
      v40 = v31;
      mem_copy_bytes(v31, v12, 28);
      v32 = v10;
      v33 = v9;
      v34 = (_DWORD *)v11;
      v35 = v8;
      v37 = sub_8696();
      v13 = *(_DWORD *)(v38 + 52);
      if ( v13 >> 28 == 12 )
      {
        v14 = sub_8660(BYTE2(v13) & 0xF);
        mem_copy_bytes(v40, v14, 28);
      }
      v15 = a3 + 3;
      switch ( v7 )
      {
        case 0:
          v5 = 24599;
          break;
        case 1:
          if ( sub_8696() <= v8 )
          {
            mem_copy_bytes(v30, dword_13014, 20);
            v36 = 0;
            goto LABEL_56;
          }
          v5 = 32776;
          break;
        case 2:
          if ( v8 > 0xFF )
          {
            mem_copy_bytes(&v29, v15, 4);
            v16 = sub_86AE();
            mem_copy_bytes(v30, v16, 20);
            v36 = 1;
            v17 = *(_DWORD *)(v38 + 52);
            if ( v17 >> 28 == 12 )
            {
              v18 = sub_86B2((v17 >> 20) & 0xF);
              mem_copy_bytes(v30, v18, 20);
              if ( (*(_DWORD *)(v38 + 52) & 0x2000000) != 0 )
                v36 |= 0x2000000u;
            }
            goto LABEL_56;
          }
          v5 = 32776;
          break;
        case 3:
          if ( v11 << 30 )
          {
            v5 = 24628;
          }
          else if ( *(_DWORD *)v11 == 1 )
          {
            if ( v8 >= 0x124 )
            {
              if ( a3[1] << 31 )
              {
                mem_copy_bytes(&v29, v15, 4);
                v19 = sub_86AE();
                mem_copy_bytes(v30, v19, 20);
                v34 = (_DWORD *)(v11 + 36);
                v35 = 256;
                v36 = 1;
                v20 = *(_DWORD *)(v38 + 52);
                if ( v20 >> 28 == 12 )
                {
                  v21 = sub_86B2((v20 >> 20) & 0xF);
                  mem_copy_bytes(v30, v21, 20);
                  if ( (*(_DWORD *)(v38 + 52) & 0x2000000) != 0 )
                    v36 |= 0x2000000u;
                }
              }
              else
              {
                mem_copy_bytes(v30, dword_13014, 20);
                v34 = (_DWORD *)(v11 + 4);
                v35 = 32;
                v36 = 0;
              }
              goto LABEL_56;
            }
            v5 = 32776;
          }
          else
          {
            v5 = 24612;
          }
          break;
        case 5:
          if ( v11 << 30 )
          {
            v5 = 24628;
          }
          else
          {
            v22 = *(_DWORD *)v11;
            if ( *(_DWORD *)v11 == 2 || v22 == 5 || v22 == 6 || v22 == 7 )
            {
              v23 = 0;
              switch ( v22 )
              {
                case 2:
                  v23 = 1644;
                  break;
                case 5:
                  v23 = 2484;
                  break;
                case 6:
                  v23 = 844;
                  break;
                case 7:
                  v23 = 2500;
                  break;
              }
              if ( v23 <= v8 )
              {
                v34 = (_DWORD *)v11;
                v35 = v23;
                if ( a3[1] << 31 )
                {
                  mem_copy_bytes(&v29, v15, 4);
                  v36 = 1;
                  v24 = *(_DWORD *)(v38 + 52);
                  if ( v24 >> 28 == 12 )
                  {
                    v25 = sub_86B2((v24 >> 20) & 0xF);
                    mem_copy_bytes(v30, v25, 20);
                    if ( (*(_DWORD *)(v38 + 52) & 0x2000000) != 0 )
                      v36 |= 0x2000000u;
                  }
                  else
                  {
                    v26 = sub_86B2(6);
                    mem_copy_bytes(v30, v26, 20);
                  }
                }
                else
                {
                  mem_copy_bytes(v30, dword_13014, 20);
                  v36 = 0;
                }
LABEL_56:
                if ( v7 == 1 || v7 == 2 || v7 == 3 )
                {
                  if ( (a3[1] & 2) != 0 )
                    v36 |= 2u;
                  v5 = auth_verify_case123(v41, v39, &v29, v44);
                }
                else if ( v7 == 5 )
                {
                  auth_verify_type5(v41, v39, &v29, 0);
                  v5 = v27;
                }
              }
              else
              {
                v5 = 32776;
              }
            }
            else
            {
              v5 = 24629;
            }
          }
          break;
        default:
          v5 = 24600;
          break;
      }
      return v5;
    }
  }
  return v5;
}


// ==================== sub_93B4 @0x93B4 size=148 ====================
void __fastcall sub_93B4(int a1, int a2, int *a3, int a4)
{
  int *v8; // r0
  int v9; // r3
  int v10; // [sp+4h] [bp-58h] BYREF
  int v11; // [sp+8h] [bp-54h]
  int v12; // [sp+Ch] [bp-50h]
  int v13; // [sp+10h] [bp-4Ch]
  int v14; // [sp+14h] [bp-48h]
  _BYTE v15[4]; // [sp+18h] [bp-44h] BYREF
  _BYTE v16[24]; // [sp+1Ch] [bp-40h] BYREF
  _BYTE v17[24]; // [sp+34h] [bp-28h] BYREF
  int v18; // [sp+4Ch] [bp-10h]
  int v19; // [sp+50h] [bp-Ch]
  int v20; // [sp+54h] [bp-8h]
  int v21; // [sp+58h] [bp-4h]

  if ( a3 )
  {
    mem_set_bytes(&v10, 0, 24);
    mem_set_bytes(v16, 0, 64);
    v10 = *a3;
    v11 = a3[1];
    v12 = v10;
    v13 = v11;
    mem_copy_bytes(v15, a3 + 2, 4);
    v14 = 51;
    mem_copy_bytes(v16, &v10, 24);
    v8 = sub_86E0();
    mem_copy_bytes(v17, v8, 20);
    v17[20] = 1;
    v18 = a3[3];
    v19 = a3[4];
    v20 = a3[5];
    v21 = a3[6];
    v9 = (int)(a3 + 7);
    if ( a4 )
      sub_8FF8(a1, a2, (int)v16, v9);
    else
      sub_8FEC(a1, a2, (int)v16, v9);
  }
}


// ==================== sub_9448 @0x9448 size=4 ====================
void __fastcall sub_9448(int a1, int a2, int *a3)
{
  sub_93B4(a1, a2, a3, 0);
}


// ==================== sub_944C @0x944C size=4 ====================
void __fastcall sub_944C(int a1, int a2, int *a3)
{
  sub_93B4(a1, a2, a3, 1);
}


// ==================== sub_9454 @0x9454 size=196 ====================
int __fastcall sub_9454(int a1, int a2, _DWORD *a3)
{
  int v5; // r5
  int v6; // r0
  int v8; // r1
  int v9; // r0

  v5 = a3[5];
  mem_set_bytes(a2, 0, 36);
  mem_set_bytes(a2 + 36, 0, 8);
  if ( !v5 )
    return 24577;
  v6 = *(_DWORD *)(v5 + 4);
  if ( v6 == 64 )
  {
    if ( *(_WORD *)(v5 + 10) != 63 )
      return 24620;
  }
  else
  {
    if ( v6 != 128 )
      return 24590;
    if ( *(_WORD *)(v5 + 10) != 127 )
      return 24621;
  }
  if ( *a3 << 30 || a3[2] << 30 )
    return 24583;
  v8 = a3[1];
  if ( !v8 )
    return 24586;
  v9 = a3[3];
  if ( !v9 )
    return 24586;
  if ( v8 << 31 || v9 << 31 )
    return 24585;
  if ( (a3[4] & 8) != 0 )
    return 24602;
  *(_DWORD *)(a2 + 4) = *(unsigned __int16 *)(v5 + 10);
  *(_DWORD *)(a2 + 8) = a3[1] >> 1;
  *(_WORD *)(a2 + 12) = *(_WORD *)(v5 + 8);
  *(_DWORD *)(a2 + 16) = *a3;
  *(_DWORD *)(a2 + 20) = *(_DWORD *)(v5 + 4);
  *(_DWORD *)(a2 + 24) = v5 + 268;
  *(_DWORD *)(a2 + 28) = *(_DWORD *)v5;
  *(_DWORD *)(a2 + 32) = v5 + 12;
  *(_DWORD *)(a2 + 36) = a3[3] >> 1;
  *(_DWORD *)(a2 + 40) = a3[2];
  sub_A584(a2 + 44);
  return 0;
}


// ==================== sub_9518 @0x9518 size=4 ====================
int sub_9518()
{
  return 0;
}


// ==================== sub_951C @0x951C size=6 ====================
int sub_951C()
{
  return 24580;
}


// ==================== sub_9522 @0x9522 size=86 ====================
int __fastcall sub_9522(int a1, int a2)
{
  unsigned int v2; // r0
  unsigned int v3; // r2

  v2 = *(_DWORD *)(a2 + 20);
  v3 = *(_DWORD *)(a2 + 8);
  if ( v2 != v3 )
  {
    if ( v2 >= v3 )
    {
      if ( v2 == 64 )
        return 24622;
      if ( v2 == 128 )
        return 24623;
    }
    else
    {
      v3 = *(_DWORD *)(a2 + 20);
    }
  }
  if ( v3 / v2 * *(_DWORD *)(a2 + 4) > *(_DWORD *)(a2 + 36) )
    return 24594;
  *(_DWORD *)(a2 + 8) = v3;
  *(_BYTE *)a2 = 0;
  if ( sub_A304(a2 + 44, a2, a2 + 36) )
    return 24592;
  else
    return 0;
}


// ==================== sub_9578 @0x9578 size=24 ====================
_WORD *__fastcall sub_9578(_WORD *result, __int16 *a2, int a3)
{
  __int16 v3; // t1

  while ( a3-- != 0 )
  {
    v3 = *a2++;
    *result++ = v3;
  }
  return result;
}


// ==================== sub_9590 @0x9590 size=76 ====================
int __fastcall sub_9590(int a1, int a2, int a3)
{
  int i; // r3
  unsigned int v4; // r4
  unsigned int v5; // r5

  for ( i = 0; i < a3; ++i )
  {
    v4 = *(unsigned __int16 *)(a1 + 2 * i);
    v5 = *(unsigned __int16 *)(a2 + 2 * i);
    if ( v4 > v5 )
      return 1;
    if ( v4 < v5 )
      return -1;
  }
  return 0;
}


// ==================== sub_95DC @0x95DC size=152 ====================
int __fastcall sub_95DC(int result, int a2, int a3, int a4)
{
  int v4; // r1
  int i; // r5
  unsigned int v6; // r4
  unsigned int v7; // r6

  v4 = a2 - 1;
  for ( i = 0; v4 >= 0; --v4 )
  {
    v6 = *(unsigned __int16 *)(result + 2 * v4);
    if ( i )
    {
      if ( *(_WORD *)(result + 2 * v4) )
      {
        --v6;
        i = 0;
      }
      else
      {
        v6 = 0xFFFF;
      }
    }
    v7 = *(unsigned __int16 *)(a3 + 2 * v4);
    if ( v7 > v6 )
    {
      if ( i )
      {
        while ( 1 )
          ;
      }
      i = 1;
      *(_WORD *)(a4 + 2 * v4) = v6 - v7;
    }
    else
    {
      *(_WORD *)(a4 + 2 * v4) = v6 - v7;
    }
  }
  if ( i )
  {
    while ( 1 )
      ;
  }
  return result;
}


// ==================== sub_9674 @0x9674 size=20 ====================
_WORD *__fastcall sub_9674(_WORD *result, __int16 a2, int a3)
{
  while ( a3-- != 0 )
    *result++ = a2;
  return result;
}


// ==================== sub_9688 @0x9688 size=232 ====================
_WORD *__fastcall sub_9688(int *a1, int *a2, int a3)
{
  int v6; // r8
  int v7; // r7
  int v8; // r9
  _WORD *result; // r0
  int i; // r5
  int v11; // r12
  unsigned int v12; // r0
  int v13; // r4
  int j; // r3
  _WORD *v15; // r2
  unsigned int v16; // r1
  _WORD *v17; // r1

  v6 = *a1;
  v7 = *a2;
  v8 = *(_DWORD *)a3;
  if ( *a1 <= 0 )
  {
    while ( 1 )
      ;
  }
  if ( v7 <= 0 )
  {
    while ( 1 )
      ;
  }
  if ( v6 + v7 > v8 )
  {
    while ( 1 )
      ;
  }
  result = sub_9674(*(_WORD **)(a3 + 4), 0, *(_DWORD *)a3);
  for ( i = v7 - 1; i >= 0; --i )
  {
    result = (_WORD *)(a2[1] + 2 * i);
    v11 = (unsigned __int16)*result;
    if ( *result )
    {
      v12 = 0;
      v13 = v8 - (v7 - i);
      for ( j = v6 - 1; j >= 0; --j )
      {
        v15 = (_WORD *)(*(_DWORD *)(a3 + 4) + 2 * v13);
        v16 = (unsigned __int16)*v15 + v11 * *(unsigned __int16 *)(a1[1] + 2 * j) + v12;
        v12 = HIWORD(v16);
        *v15 = v16;
        --v13;
      }
      v17 = (_WORD *)(*(_DWORD *)(a3 + 4) + 2 * v13);
      result = (_WORD *)(v12 + (unsigned __int16)*v17);
      *v17 = (_WORD)result;
    }
  }
  return result;
}


// ==================== sub_9770 @0x9770 size=540 ====================
int __fastcall sub_9770(int a1, int *a2, int *a3, int a4)
{
  int *v7; // r6
  int v8; // r9
  __int16 *v9; // r7
  int *v10; // r5
  int v11; // r4
  int i; // r3
  int v13; // r0
  unsigned int v14; // r2
  int v15; // lr
  int j; // r1
  _WORD *v17; // r12
  unsigned int v18; // r2
  _WORD *v19; // r12
  unsigned int v20; // r1
  int v21; // r10
  int v22; // r2
  int result; // r0
  __int16 v24; // [sp+0h] [bp-Ch]
  int v25; // [sp+4h] [bp-8h] BYREF
  int v26; // [sp+8h] [bp-4h]

  v25 = (int)a3;
  v26 = a4;
  v7 = (int *)(a1 + 8);
  v8 = a1 + 788;
  if ( *(_DWORD *)(a1 + 8) )
  {
    while ( 1 )
      ;
  }
  v24 = *(_WORD *)(a1 + 12);
  *v7 = 1;
  v9 = (__int16 *)(a1 + 14);
  v10 = *(int **)(a1 + 804);
  v11 = *v10;
  v25 = *a2 + *a3;
  v26 = a1 + 14 + 2 * (2 * v11 + 1) - 2 * v25;
  sub_9674((_WORD *)(a1 + 14), 0, 2 * v11 - v25 + 1);
  sub_9688(a2, a3, (int)&v25);
  v26 = (int)v7 + 6;
  for ( i = 2 * v11; i > v11; --i )
  {
    v13 = 0;
    v14 = 0;
    v15 = (unsigned __int16)(*(_WORD *)(v26 + 2 * i) * v24);
    for ( j = v11 - 1; j >= 0; --j )
    {
      v13 = i + j - v11 + 1;
      v17 = (_WORD *)(v26 + 2 * v13);
      v18 = v14 + (unsigned __int16)*v17 + v15 * *(unsigned __int16 *)(v10[1] + 2 * j);
      *v17 = v18;
      v14 = HIWORD(v18);
    }
    while ( v14 )
    {
      if ( v13 <= 0 )
      {
        while ( 1 )
          ;
      }
      --v13;
      v19 = (_WORD *)(v26 + 2 * v13);
      v20 = (unsigned __int16)*v19 + v14;
      *v19 = v20;
      v14 = HIWORD(v20);
    }
  }
  if ( *v9 || sub_9590((int)(v7 + 2), v10[1], v11) >= 0 )
  {
    v21 = v11;
    if ( *v9 )
    {
      v22 = v8 + 534;
      v21 = v11 + 1;
    }
    else
    {
      v22 = v10[1];
      v9 = (__int16 *)(v7 + 2);
    }
    sub_95DC((int)v9, v21, v22, (int)v9);
    if ( v21 == v11 + 1 )
    {
      if ( *v9 )
      {
        while ( 1 )
          ;
      }
      ++v9;
    }
  }
  else
  {
    v9 = (__int16 *)(v7 + 2);
  }
  if ( sub_9590((int)v9, v10[1], v11) == 1 )
  {
    while ( 1 )
      ;
  }
  if ( *(_DWORD *)a4 < v11 )
  {
    while ( 1 )
      ;
  }
  sub_9578(*(_WORD **)(a4 + 4), v9, v11);
  *(_DWORD *)a4 = v11;
  result = *v7 - 1;
  *v7 = result;
  return result;
}


// ==================== sub_998C @0x998C size=76 ====================
int __fastcall sub_998C(int *a1, int a2)
{
  if ( a2 / 16 < *a1 )
    return *(unsigned __int16 *)(a1[1] + 2 * (*a1 - a2 / 16 - 1)) & (1 << (a2 % 16));
  else
    return 0;
}


// ==================== sub_99D8 @0x99D8 size=148 ====================
int __fastcall sub_99D8(int *a1)
{
  unsigned int v1; // r4
  int v2; // r5
  int i; // r1
  _WORD *v4; // r2
  int v6; // r0
  int v7; // r3
  unsigned int v8; // r2

  v1 = 0;
  v2 = *a1;
  for ( i = 0; i < v2; ++i )
  {
    v4 = (_WORD *)(a1[1] + 2 * i);
    v1 = (unsigned __int16)*v4;
    if ( *v4 )
      break;
  }
  if ( i == v2 )
    return 0;
  v6 = 8;
  v7 = 8;
  v8 = 256;
  do
  {
    v6 >>= 1;
    if ( v1 <= v8 )
    {
      if ( v1 >= v8 )
        return v7 + 16 * (v2 - i - 1) + 1;
      v7 -= v6;
      v8 >>= v6;
    }
    else
    {
      v7 += v6;
      v8 = (unsigned __int16)(v8 << v6);
    }
  }
  while ( v6 > 1 );
  return v7 + 16 * (v2 - i - 1) + 1;
}


// ==================== sub_9A6C @0x9A6C size=80 ====================
int __fastcall sub_9A6C(int result, int a2, int a3, _WORD *a4)
{
  unsigned int v4; // r4
  int i; // r1
  unsigned int v6; // r4

  if ( a2 <= 0 )
  {
    while ( 1 )
      ;
  }
  v4 = 0;
  for ( i = a2 - 1; i >= 0; --i )
  {
    v6 = v4 + *(unsigned __int16 *)(result + 2 * i) * a3;
    a4[i + 1] = v6;
    v4 = HIWORD(v6);
  }
  *a4 = v4;
  return result;
}


// ==================== sub_9ABC @0x9ABC size=72 ====================
int __fastcall sub_9ABC(int result, int a2, int a3, int a4)
{
  int v4; // r1
  unsigned int i; // r4
  unsigned int v6; // r4

  v4 = a2 - 1;
  for ( i = 0; v4 >= 0; --v4 )
  {
    v6 = i + *(unsigned __int16 *)(result + 2 * v4) + *(unsigned __int16 *)(a3 + 2 * v4);
    *(_WORD *)(a4 + 2 * v4) = v6;
    i = HIWORD(v6);
  }
  return result;
}


// ==================== sub_9B04 @0x9B04 size=652 ====================
int __fastcall sub_9B04(_DWORD *a1, unsigned __int16 *a2, _WORD *a3)
{
  __int16 *v4; // r9
  _DWORD *v5; // r11
  int v6; // r5
  unsigned int v7; // r0
  unsigned int v8; // r1
  unsigned int v9; // r7
  unsigned int v10; // r10
  unsigned int v11; // r4
  unsigned int v12; // r8
  int v13; // r0
  int v14; // r0
  int result; // r0
  _WORD *v16; // [sp+4h] [bp-18h]
  __int16 *v17; // [sp+8h] [bp-14h]
  _WORD *v18; // [sp+Ch] [bp-10h]

  v4 = (__int16 *)(a1 + 197);
  v5 = a1 + 395;
  v6 = a1[198];
  v16 = (_WORD *)(*(_DWORD *)(a1[201] + 4) + 2 * *(_DWORD *)a1[201] - 2 * v6);
  if ( !*v16 )
  {
    while ( 1 )
      ;
  }
  if ( *v5 )
  {
    while ( 1 )
      ;
  }
  *v5 = 1;
  v18 = a1 + 396;
  v17 = (__int16 *)a1 + 921;
  v7 = a2[1] + (*a2 << 16);
  v8 = (unsigned __int16)*v16;
  v9 = (v7 + 1) / v8 + 2;
  if ( v9 > 0x10000 )
    v9 = 0x10000;
  v10 = (unsigned __int16)(v7 / (v8 + 1));
  v11 = (unsigned __int16)((v9 + v10) >> 1);
  a1[1] = 0;
  v12 = v11;
  while ( 1 )
  {
    while ( 1 )
    {
      v13 = 1;
      if ( v11 )
      {
        if ( v12 <= v11 )
        {
          if ( v12 < v11 && (int)(v11 - v12) < 1 )
          {
            sub_9ABC((int)v18, v6 + 1, (int)&v4[129 * (v11 - v12) + 138], (int)v18);
            v13 = 0;
          }
        }
        else if ( (int)(v12 - v11) < 1 )
        {
          sub_95DC((int)v18, v6 + 1, (int)&v4[129 * (v12 - v11) + 138], (int)v18);
          v13 = 0;
        }
      }
      else
      {
        sub_9578(v18, v4 + 138, v6 + 1);
        v13 = 0;
      }
      if ( v13 )
        sub_9A6C((int)v16, v6, v11, v18);
      v12 = v11;
      ++a1[1];
      v14 = sub_9590((int)a2, (int)v18, v6 + 1);
      if ( v14 <= 0 )
        break;
      sub_95DC((int)a2, v6 + 1, (int)v18, (int)v17);
      if ( !*v17 && sub_9590((int)(v5 + 66), (int)v16, v6) < 0 )
      {
        *a3 = v11;
        sub_9578(a2, v17, v6 + 1);
        goto LABEL_27;
      }
      if ( v11 >= v9 - 1 )
      {
        while ( 1 )
          ;
      }
      v10 = v11 + 1;
      v11 = (unsigned __int16)((v11 + v9) >> 1);
    }
    if ( !v14 )
      break;
    if ( v11 <= v10 )
    {
      while ( 1 )
        ;
    }
    v9 = v11;
    v11 = (unsigned __int16)((v11 + v10) >> 1);
  }
  sub_9674(a2, 0, v6 + 1);
  *a3 = v11;
LABEL_27:
  --*v5;
  result = a1[1];
  if ( result > *a1 )
    *a1 = result;
  return result;
}


// ==================== sub_9D90 @0x9D90 size=44 ====================
int __fastcall sub_9D90(int *a1)
{
  int result; // r0
  unsigned __int16 *v3; // r1

  result = *a1;
  v3 = (unsigned __int16 *)a1[1];
  while ( result )
  {
    if ( *v3++ )
      break;
    --result;
  }
  return result;
}


// ==================== sub_9DBC @0x9DBC size=156 ====================
int __fastcall sub_9DBC(int *a1, int *a2)
{
  int v4; // r0
  int v5; // r3
  int v7; // r2
  int v8; // r3
  unsigned int v9; // r5
  unsigned int v10; // r6

  sub_9D90(a1);
  v4 = sub_9D90(a2);
  if ( v5 > v4 )
    return 1;
  if ( v5 < v4 )
    return -1;
  v7 = *a1 - v5;
  v8 = *a2 - v4;
  while ( v7 < *a1 )
  {
    v9 = *(unsigned __int16 *)(a1[1] + 2 * v7);
    v10 = *(unsigned __int16 *)(a2[1] + 2 * v8);
    if ( v9 > v10 )
      return 1;
    if ( v9 < v10 )
      return -1;
    ++v7;
    ++v8;
  }
  return 0;
}


// ==================== sub_9E58 @0x9E58 size=504 ====================
int __fastcall sub_9E58(_DWORD *a1, int *a2, int *a3, int a4)
{
  int *v5; // r6
  int v6; // r7
  _WORD *v7; // r9
  int v8; // r10
  _WORD *v9; // r5
  int v10; // r4
  __int16 *v11; // r1
  int i; // r4
  int v13; // r0
  int result; // r0
  __int16 v15; // [sp+0h] [bp-1Ch] BYREF
  int *v16; // [sp+4h] [bp-18h]
  int v17; // [sp+8h] [bp-14h]
  _DWORD *v18; // [sp+Ch] [bp-10h]
  int *v19; // [sp+10h] [bp-Ch]
  int *v20; // [sp+14h] [bp-8h]
  int v21; // [sp+18h] [bp-4h]

  v18 = a1;
  v19 = a2;
  v20 = a3;
  v21 = a4;
  v5 = a1 + 197;
  v16 = (int *)a1[201];
  v6 = *a3;
  v7 = (_WORD *)a3[1];
  if ( *a2 > *a3 )
  {
    while ( 1 )
      ;
  }
  if ( *(_DWORD *)a4 < *v16 )
  {
    while ( 1 )
      ;
  }
  if ( *v5 )
  {
    while ( 1 )
      ;
  }
  if ( *a2 > 256 )
  {
    while ( 1 )
      ;
  }
  *v5 = 1;
  v8 = a1[198];
  v9 = a1 + 202;
  sub_9674(v7, 0, v6);
  sub_9674(*(_WORD **)(a4 + 4), 0, *(_DWORD *)a4);
  v10 = sub_9D90(v19);
  v11 = (__int16 *)(v19[1] + 2 * *v19 - 2 * v10);
  if ( v10 >= v8 )
  {
    if ( v8 )
    {
      v17 = v8 + 1;
      v5[2] = v8 + 1;
      *v9 = 0;
      sub_9578((_WORD *)v5 + 11, v11, v10);
      for ( i = v10 - v8; i >= 0; --i )
      {
        v5[3] = (int)v9;
        v13 = sub_9DBC(v5 + 2, v16);
        if ( v13 <= 0 )
        {
          if ( v13 )
          {
            v7[v6 - i - 1] = 0;
          }
          else
          {
            v7[v6 - i - 1] = 1;
            sub_9674(v9, 0, v17);
          }
        }
        else
        {
          sub_9B04(v18, v9, &v15);
          v7[v6 - i - 1] = v15;
        }
        if ( !i )
          break;
        ++v9;
      }
      if ( *v9 )
      {
        while ( 1 )
          ;
      }
      sub_9578((_WORD *)(*(_DWORD *)(a4 + 4) + 2 * (*(_DWORD *)a4 - v8)), v9 + 1, v8);
    }
  }
  else if ( v10 > 0 )
  {
    sub_9578((_WORD *)(*(_DWORD *)(a4 + 4) + 2 * (*(_DWORD *)a4 - v10)), v11, v10);
  }
  result = *v5 - 1;
  *v5 = result;
  return result;
}


// ==================== sub_A050 @0xA050 size=484 ====================
int __fastcall sub_A050(int a1, int a2, int *a3, int *a4)
{
  int v8; // r4
  int v9; // r6
  int i; // r5
  _BYTE v12[4]; // [sp+4h] [bp-3Ch] BYREF
  int v13[2]; // [sp+8h] [bp-38h] BYREF
  int v14; // [sp+10h] [bp-30h] BYREF
  _WORD *v15; // [sp+14h] [bp-2Ch]
  int v16; // [sp+18h] [bp-28h] BYREF
  __int16 *v17; // [sp+1Ch] [bp-24h]
  int v18; // [sp+20h] [bp-20h] BYREF
  _WORD *v19; // [sp+24h] [bp-1Ch]
  int v20[2]; // [sp+28h] [bp-18h] BYREF
  int v21; // [sp+30h] [bp-10h] BYREF
  __int16 *v22; // [sp+34h] [bp-Ch]
  int v23; // [sp+38h] [bp-8h] BYREF
  _WORD *v24; // [sp+3Ch] [bp-4h]

  sub_11610(v12, &dword_13098, 2);
  v13[0] = 1;
  v13[1] = (int)v12;
  v8 = **(_DWORD **)(a1 + 804);
  if ( *(int *)a2 <= 0 )
  {
    while ( 1 )
      ;
  }
  if ( *a3 <= 0 )
  {
    while ( 1 )
      ;
  }
  if ( *a4 <= 0 )
  {
    while ( 1 )
      ;
  }
  if ( v8 != *a4 )
  {
    while ( 1 )
      ;
  }
  v23 = **(_DWORD **)(a1 + 804);
  v18 = v8;
  v21 = v8;
  v16 = v8;
  v24 = (_WORD *)(a1 + 2612);
  v19 = (_WORD *)(a1 + 2868);
  v22 = (__int16 *)(a1 + 3124);
  v17 = (__int16 *)(a1 + 3124);
  v15 = (_WORD *)(a1 + 3124);
  v20[1] = a1 + 2100;
  v14 = *(_DWORD *)a2 + v8;
  sub_9578((_WORD *)(a1 + 3124), *(__int16 **)(a2 + 4), *(_DWORD *)a2);
  sub_9674(&v15[*(_DWORD *)a2], 0, v14 - *(_DWORD *)a2);
  v20[0] = 2 * v8;
  sub_9E58((_DWORD *)a1, &v14, v20, (int)&v23);
  v14 = v8 + 1;
  *v15 = 1;
  sub_9674(v15 + 1, 0, v14 - 1);
  sub_9E58((_DWORD *)a1, &v14, v20, (int)&v18);
  v9 = sub_99D8(a3);
  for ( i = 0; i < v9; ++i )
  {
    if ( sub_998C(a3, i) )
    {
      sub_9770(a1, &v23, &v18, (int)&v16);
      sub_9578(v19, v17, v8);
    }
    sub_9770(a1, &v23, &v23, (int)&v21);
    sub_9578(v24, v22, v8);
  }
  return sub_9770(a1, &v18, v13, (int)a4);
}


// ==================== sub_A234 @0xA234 size=208 ====================
_WORD *__fastcall sub_A234(int a1, int *a2, __int16 a3)
{
  int v5; // r8
  int v6; // r6
  int v7; // r5
  _DWORD *v8; // r3
  __int16 *v9; // r4
  _WORD *v10; // r7
  _WORD *result; // r0

  v5 = a1 + 8;
  v6 = a1 + 788;
  v7 = sub_9D90(a2);
  v9 = (__int16 *)(v8[1] + 2 * *v8 - 2 * v7);
  *(_DWORD *)(v6 + 16) = v8;
  v10 = (_WORD *)(a1 + 1322);
  if ( *(_DWORD *)(v6 + 4) != v7 || (result = (_WORD *)sub_9590((int)(v10 + 1), (int)v9, v7)) != 0 )
  {
    *(_DWORD *)(v6 + 4) = v7;
    *(_WORD *)(v5 + 4) = a3;
    *v10 = 0;
    return sub_9578(v10 + 1, v9, v7);
  }
  return result;
}


// ==================== sub_A304 @0xA304 size=640 ====================
int __fastcall sub_A304(int a1, int a2, _DWORD *a3)
{
  _DWORD *v6; // r10
  int v7; // r8
  int v8; // r5
  int v9; // r0
  int v10; // r4
  int v11; // r2
  int v12; // r0
  int v13; // r7
  int v14; // r3
  int v15; // r2
  int v16; // r0
  int v17; // r0
  int v18; // r7
  int v20; // [sp+0h] [bp-24h] BYREF
  int i; // [sp+4h] [bp-20h]
  int v22; // [sp+8h] [bp-1Ch] BYREF
  int v23; // [sp+Ch] [bp-18h]
  int v24; // [sp+10h] [bp-14h] BYREF
  int v25; // [sp+14h] [bp-10h]
  int v26[2]; // [sp+18h] [bp-Ch] BYREF
  int v27; // [sp+20h] [bp-4h]

  v6 = (_DWORD *)(a1 + 528);
  v7 = 0;
  if ( *(_DWORD *)(a1 + 528) )
  {
    v7 = 4;
  }
  else
  {
    *v6 = 1;
    v8 = *(_DWORD *)(a2 + 4);
    v9 = *(_DWORD *)(a2 + 20);
    v26[0] = *(_DWORD *)(a2 + 28);
    v26[1] = *(_DWORD *)(a2 + 32);
    v24 = v9;
    v25 = *(_DWORD *)(a2 + 24);
    v10 = sub_9D90(&v24);
    if ( v24 > v10 )
    {
      v25 = v25 + 2 * v24 - 2 * v10;
      v24 = v10;
    }
    if ( v8 >= 1 && sub_99D8(v26) && sub_99D8(&v24) )
    {
      if ( v8 <= v10 )
      {
        sub_A234(a1, &v24, *(_WORD *)(a2 + 12));
        if ( *(_BYTE *)a2 )
        {
          v11 = *(_DWORD *)(a2 + 8);
          v12 = (v11 + v8 - 1) / v8;
          if ( v10 * v12 <= *a3 )
          {
            v27 = v12 - 1;
            v13 = (v12 - 1) * v8;
            if ( v11 - v13 >= v8 )
            {
              v23 = *(_DWORD *)(a2 + 16) + 2 * v13;
            }
            else
            {
              v23 = a1 + 532;
              sub_9674((_WORD *)(a1 + 532 + 2 * (v11 - v13)), 0, v8 - (v11 - v13));
              sub_9578((_WORD *)(a1 + 532), (__int16 *)(*(_DWORD *)(a2 + 16) + 2 * v13), v14);
            }
            v22 = v8;
            v20 = v10;
            for ( i = a3[1] + 2 * v27 * v10; ; i -= 2 * v10 )
            {
              sub_A050(a1, (int)&v22, v26, &v20);
              if ( !v13 )
                break;
              v13 -= v8;
              v23 = *(_DWORD *)(a2 + 16) + 2 * v13;
            }
          }
          else
          {
            v7 = 3;
          }
        }
        else
        {
          v15 = *(_DWORD *)(a2 + 8);
          v16 = v15 / v10;
          if ( v15 % v10 )
          {
            v7 = 5;
          }
          else if ( v8 * v16 <= *a3 )
          {
            v22 = v10;
            v20 = v10;
            v17 = v16 - 1;
            v18 = v17 * v8;
            v23 = *(_DWORD *)(a2 + 16) + 2 * v17 * v10;
            i = a1 + 532;
            while ( 1 )
            {
              sub_A050(a1, (int)&v22, v26, &v20);
              sub_9578((_WORD *)(a3[1] + 2 * v18), (__int16 *)(a1 + 532 + 2 * (v10 - v8)), v8);
              if ( !v18 )
                break;
              v18 -= v8;
              v23 -= 2 * v10;
            }
          }
          else
          {
            v7 = 3;
          }
        }
      }
      else
      {
        v7 = 2;
      }
    }
    else
    {
      v7 = 5;
    }
  }
  --*v6;
  return v7;
}


// ==================== sub_A584 @0xA584 size=80 ====================
_DWORD *__fastcall sub_A584(_DWORD *a1)
{
  _DWORD *v1; // r1
  _DWORD *v2; // r4
  _DWORD *v3; // r5
  _DWORD *result; // r0

  v1 = a1 + 197;
  v2 = a1 + 2;
  v3 = a1 + 395;
  *a1 = 0;
  a1[1] = -1;
  a1[132] = 0;
  a1[197] = 0;
  a1[199] = 0;
  result = a1 + 202;
  v1[3] = result;
  v1[1] = 0;
  v1[4] = 0;
  *v2 = 0;
  *v3 = 0;
  return result;
}


// ==================== sub_A5D8 @0xA5D8 size=164 ====================
int __fastcall sub_A5D8(int a1, int a2, _DWORD *a3, int a4)
{
  _DWORD *v6; // r4
  int v8; // r0
  int v9; // r1
  int v10; // [sp+0h] [bp-4h] BYREF

  v10 = a4;
  sub_1153C(&v10, &dword_A6F0, 4);
  v6 = (_DWORD *)a3[5];
  mem_set_bytes(a2, 0, 788);
  if ( !v6 )
    return 24577;
  if ( v6[1] != 256 )
    return 24632;
  if ( (*v6 != 3 || mem_cmp(v6 + 3, (char *)&v10 + 1, 3)) && (*v6 != 4 || mem_cmp(v6 + 3, &v10, 4)) )
    return 24630;
  if ( *a3 << 30 || a3[2] << 30 )
    return 24583;
  v8 = a3[1];
  if ( !v8 )
    return 24586;
  v9 = a3[3];
  if ( !v9 )
    return 24586;
  if ( v8 << 30 || v9 << 30 )
    return 24633;
  if ( (a3[4] & 8) != 0 )
    return 24602;
  return 0;
}


// ==================== sub_A67C @0xA67C size=4 ====================
int sub_A67C()
{
  return 0;
}


// ==================== sub_A680 @0xA680 size=6 ====================
int sub_A680()
{
  return 24580;
}


// ==================== sub_A686 @0xA686 size=106 ====================
int __fastcall sub_A686(int a1, int a2, int *a3)
{
  int v4; // r3
  int v5; // r5
  int v6; // r0
  int i; // r1
  int j; // r1

  v4 = *a3;
  v5 = a3[2];
  v6 = a3[5];
  for ( i = 0; i <= 255; ++i )
  {
    *(_BYTE *)(a2 + i) = *(_BYTE *)(v4 + 255 - i);
    *(_BYTE *)(a2 + i + 256) = *(_BYTE *)(255 - i + v6 + 268);
  }
  sub_D7D8(270598144);
  sub_D5BE(270598144, a2, a2 + 256, a2 + 512);
  for ( j = 0; j <= 255; ++j )
    *(_BYTE *)(v5 + j) = *(_BYTE *)(255 - j + a2 + 532);
  return 0;
}


// ==================== sub_A6F8 @0xA6F8 size=164 ====================
int __fastcall sub_A6F8(int a1, int a2, _DWORD *a3, int a4)
{
  _DWORD *v6; // r4
  int v8; // r0
  int v9; // r1
  int v10; // [sp+0h] [bp-4h] BYREF

  v10 = a4;
  sub_1153C(&v10, &dword_A7F8, 4);
  v6 = (_DWORD *)a3[5];
  mem_set_bytes(a2, 0, 2560);
  if ( !v6 )
    return 24577;
  if ( v6[1] != 256 )
    return 24632;
  if ( (*v6 != 3 || mem_cmp(v6 + 3, (char *)&v10 + 1, 3)) && (*v6 != 4 || mem_cmp(v6 + 3, &v10, 4)) )
    return 24630;
  if ( *a3 << 30 || a3[2] << 30 )
    return 24583;
  v8 = a3[1];
  if ( !v8 )
    return 24586;
  v9 = a3[3];
  if ( !v9 )
    return 24586;
  if ( v8 << 30 || v9 << 30 )
    return 24633;
  if ( (a3[4] & 8) != 0 )
    return 24602;
  return 0;
}


// ==================== sub_A79C @0xA79C size=4 ====================
int sub_A79C()
{
  return 0;
}


// ==================== sub_A7A0 @0xA7A0 size=6 ====================
int sub_A7A0()
{
  return 24580;
}


// ==================== sub_A7A6 @0xA7A6 size=82 ====================
int __fastcall sub_A7A6(int a1, int a2, int *a3)
{
  int v4; // r0
  int v5; // r6
  int v6; // r7
  int i; // r2
  int v8; // r4
  int j; // r2

  v4 = *a3;
  v5 = a3[2];
  v6 = a3[5];
  for ( i = 0; i <= 255; ++i )
  {
    v8 = a2 + i;
    *(_BYTE *)(v8 + 1792) = *(_BYTE *)(v4 + 255 - i);
    *(_BYTE *)(v8 + 2048) = *(_BYTE *)(255 - i + v6 + 268);
  }
  if ( sub_B198(a2) )
    return 24592;
  for ( j = 0; j <= 255; ++j )
    *(_BYTE *)(v5 + j) = *(_BYTE *)(255 - j + a2 + 2304);
  return 0;
}


// ==================== sub_A7FC @0xA7FC size=112 ====================
int __fastcall sub_A7FC(int *a1, unsigned int a2, unsigned int a3)
{
  unsigned int v3; // r3
  unsigned int v4; // r4
  int v5; // r6
  int v6; // r5
  unsigned int v7; // r2
  unsigned int v8; // r1
  unsigned int v9; // r2

  v3 = HIWORD(a2);
  v4 = HIWORD(a3);
  v5 = (unsigned __int16)a2 * (unsigned __int16)a3;
  *a1 = v5;
  v6 = (unsigned __int16)a2 * HIWORD(a3);
  v7 = HIWORD(a2) * (unsigned __int16)a3;
  v8 = v6 + v7;
  v9 = ((v6 + v7 < v7) << 16) + ((v6 + v7) >> 16);
  v8 <<= 16;
  *a1 = v5 + v8;
  if ( v5 + v8 < v8 )
    ++v9;
  a1[1] = v3 * v4 + v9;
  return 0;
}


// ==================== sub_A86C @0xA86C size=244 ====================
int __fastcall sub_A86C(int a1, int a2, unsigned int a3, unsigned int a4)
{
  unsigned int i; // r0
  unsigned int j; // r4
  unsigned int v10; // r7
  unsigned int k; // r5
  unsigned int v13; // [sp+0h] [bp-8h] BYREF
  unsigned int v14; // [sp+4h] [bp-4h]

  v13 = a3;
  v14 = a4;
  for ( i = 0; i < 2 * a4; ++i )
    *(_DWORD *)(a1 + 4 * i) = 0;
  for ( j = 0; j < a4; ++j )
  {
    if ( *(_DWORD *)(a3 + 4 * j) )
    {
      v10 = 0;
      for ( k = 0; k < a4; ++k )
      {
        sub_A7FC((int *)&v13, *(_DWORD *)(a2 + 4 * k), *(_DWORD *)(a3 + 4 * j));
        v13 += v10;
        if ( v13 < v10 )
          ++v14;
        v13 += *(_DWORD *)(a1 + 4 * (k + j));
        if ( v13 < *(_DWORD *)(a1 + 4 * (k + j)) )
          ++v14;
        *(_DWORD *)(a1 + 4 * (k + j)) = v13;
        v10 = v14;
      }
      *(_DWORD *)(a1 + 4 * (j + a4)) = v10;
    }
    else
    {
      *(_DWORD *)(a1 + 4 * (j + a4)) = 0;
    }
  }
  return 0;
}


// ==================== sub_A960 @0xA960 size=24 ====================
int __fastcall sub_A960(int result, int a2)
{
  while ( a2-- != 0 )
    *(_DWORD *)(result + 4 * a2) = 0;
  return result;
}


// ==================== sub_A978 @0xA978 size=180 ====================
int __fastcall sub_A978(int a1, int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v5; // r6
  unsigned int j; // r4
  int v7; // r2
  int v8; // r4
  int i; // r1
  unsigned int v11; // r4

  if ( a3 < 0x20 )
  {
    for ( i = 0; a4-- != 0; i = (v11 & ~(-1 << a3)) << (32 - a3) )
    {
      v11 = *(_DWORD *)(a2 + 4 * a4);
      *(_DWORD *)(a1 + 4 * a4) = i | (v11 >> a3);
    }
    return i;
  }
  else
  {
    v5 = a3 >> 5;
    for ( j = 0; j < a4; ++j )
    {
      if ( j + v5 >= a4 )
        *(_DWORD *)(a1 + 4 * j) = 0;
      else
        *(_DWORD *)(a1 + 4 * j) = *(_DWORD *)(a2 + 4 * (j + v5));
    }
    v7 = a3 & 0x1F;
    v8 = *(_DWORD *)(a2 + 4 * (v5 - 1)) >> v7;
    if ( v7 )
      return v8 | sub_A978(a1, a1);
    return v8;
  }
}


// ==================== sub_AA2C @0xAA2C size=40 ====================
int __fastcall sub_AA2C(int a1, int a2)
{
  while ( a2-- != 0 )
  {
    if ( *(_DWORD *)(a1 + 4 * a2) )
      return a2 + 1;
  }
  return 0;
}


// ==================== sub_AA54 @0xAA54 size=36 ====================
int __fastcall sub_AA54(int result, int a2, unsigned int a3)
{
  unsigned int i; // r3

  for ( i = 0; i < a3; ++i )
    *(_DWORD *)(result + 4 * i) = *(_DWORD *)(a2 + 4 * i);
  return result;
}


// ==================== sub_AA78 @0xAA78 size=180 ====================
unsigned int __fastcall sub_AA78(int a1, int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v5; // r1
  unsigned int v6; // r4
  int v8; // r2
  int v9; // r4
  unsigned int v11; // r1
  unsigned int i; // r4
  int v13; // r5

  if ( a3 < 0x20 )
  {
    v11 = 0;
    for ( i = 0; i < a4; ++i )
    {
      v13 = *(_DWORD *)(a2 + 4 * i);
      *(_DWORD *)(a1 + 4 * i) = v11 | (v13 << a3);
      v11 = (v13 & ~(0xFFFFFFFF >> a3)) >> (32 - a3);
    }
    return v11;
  }
  else
  {
    v5 = a3 >> 5;
    v6 = a4;
    while ( v6-- != 0 )
    {
      if ( v6 < v5 )
        *(_DWORD *)(a1 + 4 * v6) = 0;
      else
        *(_DWORD *)(a1 + 4 * v6) = *(_DWORD *)(a2 + 4 * (v6 - v5));
    }
    v8 = a3 & 0x1F;
    v9 = *(_DWORD *)(a2 + 4 * (a4 - v5)) << v8;
    if ( v8 )
      return v9 | sub_AA78(a1, a1);
    return v9;
  }
}


// ==================== sub_AB2C @0xAB2C size=84 ====================
int __fastcall sub_AB2C(_DWORD *a1, _DWORD *a2, __int64 *a3, int a4)
{
  __int64 v7; // r4
  __int64 v8; // r6
  int v9; // r2

  v7 = *a3;
  v8 = sub_11168(v7, HIDWORD(v7), a4, 0);
  sub_11168(v7, HIDWORD(v7), a4, 0);
  *a1 = v8;
  *a2 = v9;
  return HIDWORD(v8);
}


// ==================== sub_AB80 @0xAB80 size=172 ====================
unsigned int __fastcall sub_AB80(int a1, int a2, __int64 a3)
{
  int v4; // r4
  unsigned int v5; // r0
  unsigned int i; // r5
  int v8; // r8
  unsigned int j; // [sp+0h] [bp-Ch] BYREF
  __int64 v11; // [sp+4h] [bp-8h] BYREF

  j = a2;
  v11 = a3;
  v4 = HIDWORD(a3);
  if ( !HIDWORD(a3) )
    return 0;
  if ( !(_DWORD)a3 )
    return 0;
  v5 = 0x80000000;
  for ( i = 0; i < 0x20; ++i )
  {
    if ( ((unsigned int)a3 & v5) != 0 )
      break;
    v5 >>= 1;
  }
  v8 = (_DWORD)a3 << i;
  for ( j = sub_AA78(a1, a2, i, HIDWORD(a3)); v4-- != 0; sub_AB2C((_DWORD *)(a1 + 4 * v4), &j, &v11, v8) )
  {
    HIDWORD(v11) = j;
    LODWORD(v11) = *(_DWORD *)(a1 + 4 * v4);
  }
  return j >> i;
}


// ==================== sub_AC2C @0xAC2C size=72 ====================
int __fastcall sub_AC2C(int a1, int a2, int a3)
{
  unsigned int v4; // r3
  unsigned int v5; // r4

  if ( !a3 )
    return 0;
  while ( a3-- != 0 )
  {
    v4 = *(_DWORD *)(a1 + 4 * a3);
    v5 = *(_DWORD *)(a2 + 4 * a3);
    if ( v4 > v5 )
      return 1;
    if ( v4 < v5 )
      return -1;
  }
  return 0;
}


// ==================== sub_AC74 @0xAC74 size=40 ====================
_DWORD *__fastcall sub_AC74(_DWORD *result, int a2, unsigned int a3)
{
  unsigned int i; // r3

  for ( i = 1; i < a3; ++i )
    result[i] = 0;
  *result = a2;
  return result;
}


// ==================== sub_AC9C @0xAC9C size=84 ====================
BOOL __fastcall sub_AC9C(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  unsigned int v7; // [sp+0h] [bp-8h] BYREF
  unsigned int v8; // [sp+4h] [bp-4h]

  v7 = a3;
  v8 = a4;
  sub_A7FC((int *)&v7, a1, a3);
  if ( v8 < a2 )
    return 0;
  if ( v8 <= a2 )
    return v7 > a4;
  return 1;
}


// ==================== sub_ACF0 @0xACF0 size=164 ====================
int __fastcall sub_ACF0(int result, int a2, int a3, unsigned int a4, unsigned int a5)
{
  int v5; // r8
  int v9; // r5
  unsigned int i; // r4
  unsigned int v11; // r0
  int v12; // r1
  unsigned int v13; // r0
  int v14; // [sp+0h] [bp-8h] BYREF
  unsigned int v15; // [sp+4h] [bp-4h]

  v14 = a3;
  v15 = a4;
  v5 = result;
  if ( a4 )
  {
    v9 = 0;
    for ( i = 0; i < a5; ++i )
    {
      sub_A7FC(&v14, a4, *(_DWORD *)(a3 + 4 * i));
      v11 = *(_DWORD *)(a2 + 4 * i) - v9;
      *(_DWORD *)(a2 + 4 * i) = v11;
      v12 = v11 > ~v9;
      v13 = v11 - v14;
      *(_DWORD *)(a2 + 4 * i) = v13;
      if ( v13 > ~v14 )
        ++v12;
      v9 = v15 + v12;
    }
    return v5 - v9;
  }
  return result;
}


// ==================== sub_AD94 @0xAD94 size=96 ====================
unsigned int __fastcall sub_AD94(int a1, int a2, int a3, unsigned int a4)
{
  unsigned int result; // r0
  unsigned int i; // r4
  unsigned int v7; // r5
  unsigned int v8; // r5

  result = 0;
  for ( i = 0; i < a4; ++i )
  {
    v7 = *(_DWORD *)(a2 + 4 * i) + result;
    *(_DWORD *)(a1 + 4 * i) = v7;
    result = v7 < result;
    v8 = v7 + *(_DWORD *)(a3 + 4 * i);
    *(_DWORD *)(a1 + 4 * i) = v8;
    if ( v8 < *(_DWORD *)(a3 + 4 * i) )
      ++result;
  }
  return result;
}


// ==================== sub_ADF4 @0xADF4 size=792 ====================
int __fastcall sub_ADF4(_DWORD *a1, unsigned int *a2, int a3, unsigned int a4, _DWORD *a5, int a6)
{
  unsigned int v9; // r7
  __int64 v11; // r2
  int v12; // r0
  unsigned int v13; // r0
  unsigned int v14; // r9
  unsigned int v15; // r8
  int i; // r5
  BOOL v17; // r10
  int v18; // r11
  unsigned int v19; // r10
  unsigned int v20; // r3
  unsigned int v21; // r1
  int v22; // r1
  unsigned int v23; // r0
  signed int v24; // r0
  signed int v25; // r1
  __int64 v26; // [sp+8h] [bp-2Ch] BYREF
  unsigned int v27; // [sp+10h] [bp-24h] BYREF
  unsigned int v28; // [sp+14h] [bp-20h] BYREF
  int v29; // [sp+18h] [bp-1Ch]
  unsigned int v30; // [sp+1Ch] [bp-18h]
  unsigned int v31; // [sp+20h] [bp-14h]
  _DWORD *v32; // [sp+24h] [bp-10h]
  unsigned int *v33; // [sp+28h] [bp-Ch]
  int v34; // [sp+2Ch] [bp-8h]
  unsigned int v35; // [sp+30h] [bp-4h]

  v32 = a1;
  v33 = a2;
  v34 = a3;
  v35 = a4;
  sub_A960((int)a1, a4);
  sub_A960((int)a2, a4);
  v9 = sub_AA2C((int)a5, a6);
  v29 = sub_AA2C(a3, a4) - v9;
  if ( !v9 )
    return -1;
  if ( v9 == 1 )
  {
    LODWORD(v11) = *a5;
    HIDWORD(v11) = a4;
    *a2 = sub_AB80((int)v32, a3, v11);
    return 0;
  }
  else
  {
    if ( v29 < 0 )
    {
LABEL_4:
      sub_AA54((int)a2, a3, a4);
      return 0;
    }
    if ( v29 )
      goto LABEL_11;
    v12 = sub_AC2C(a3, (int)a5, v9);
    if ( v12 < 0 )
      goto LABEL_4;
    if ( v12 )
    {
LABEL_11:
      v13 = 0x80000000;
      v14 = 0;
      v15 = v9 - 1;
      do
      {
        if ( (a5[v9 - 1] & v13) != 0 )
          break;
        v13 >>= 1;
        ++v14;
      }
      while ( v14 < 0x20 );
      sub_AA78((int)a5, (int)a5, v14, v9);
      LODWORD(v26) = sub_AA78((int)a2, a3, v14, v9 + v29);
      for ( i = v29; i >= 0; --i )
      {
        v17 = 0;
        HIDWORD(v26) = v26;
        v18 = i + v9 - 1;
        v31 = i + v9;
        LODWORD(v26) = a2[v18];
        if ( sub_AB2C(&v28, &v27, &v26, a5[v15]) )
        {
          v28 = -1;
          v27 = a2[v18] + a5[v15];
          v17 = a5[v15] > v27;
        }
        if ( v28 )
        {
          if ( !v17 )
          {
            v19 = v31 - 2;
            v20 = a2[v31 - 2];
            v30 = v9 - 2;
            if ( sub_AC9C(v28, v27, a5[v9 - 2], v20) )
            {
              --v28;
              v21 = v27 + a5[v15];
              v27 = v21;
              if ( a5[v15] <= v21 )
              {
                if ( sub_AC9C(v28, v21, a5[v30], a2[v19]) )
                  --v28;
              }
            }
          }
        }
        v22 = sub_ACF0(SHIDWORD(v26), (int)&a2[i], (int)a5, v28, v9);
        v23 = v28;
        v32[i] = v28;
        if ( v22 )
        {
          v32[i] = v23 - 1;
          sub_AD94((int)&a2[i], (int)&a2[i], (int)a5, v9);
        }
        LODWORD(v26) = a2[v18];
      }
      v24 = v9;
      v25 = v29 + v9;
      while ( v25 > v24 )
        a2[v24++] = 0;
      sub_A978((int)a2, (int)a2, v14, v9);
      sub_A978((int)a5, (int)a5, v14, v9);
      return 0;
    }
    else
    {
      sub_AC74(v32, 1, a4);
      return 0;
    }
  }
}


// ==================== sub_B10C @0xB10C size=64 ====================
int __fastcall sub_B10C(int a1, int a2, unsigned int a3, _DWORD *a4, unsigned int a5, _DWORD *a6, unsigned int *a7)
{
  sub_ADF4(a6, a7, a2, a3, a4, a5);
  sub_AA54(a1, (int)a7, a5);
  return 0;
}


// ==================== sub_B14C @0xB14C size=76 ====================
int __fastcall sub_B14C(
        int a1,
        int a2,
        unsigned int a3,
        _DWORD *a4,
        unsigned int a5,
        int a6,
        _DWORD *a7,
        unsigned int *a8)
{
  sub_A86C(a6, a2, a3, a5);
  sub_B10C(a1, a6, 2 * a5, a4, a5, a7, a8);
  return 0;
}


// ==================== sub_B198 @0xB198 size=176 ====================
int __fastcall sub_B198(_DWORD *a1)
{
  int v2; // r5
  _DWORD *v3; // r6
  unsigned int *v4; // r7
  unsigned int v5; // r10
  _DWORD *v6; // r11
  int v7; // r4
  _DWORD *v9; // [sp+10h] [bp-4h]

  v2 = (int)(a1 + 64);
  v3 = a1 + 192;
  v4 = a1 + 320;
  v5 = (unsigned int)(a1 + 448);
  v9 = a1 + 512;
  v6 = a1 + 576;
  v7 = 0;
  sub_B14C((int)a1, (int)(a1 + 448), (unsigned int)(a1 + 448), a1 + 512, 0x40u, (int)(a1 + 64), a1 + 192, a1 + 320);
  while ( v7 < 15 )
  {
    sub_B14C((int)a1, (int)a1, (unsigned int)a1, v9, 0x40u, v2, v3, v4);
    ++v7;
  }
  sub_B14C((int)a1, (int)a1, v5, v9, 0x40u, v2, v3, v4);
  mem_copy_bytes(v6, a1, 256);
  return 0;
}


// ==================== hash_init (sub_B248) @0xB248 size=16 ====================
int __fastcall hash_init(int a1)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, _DWORD))(a1 + 24))(
           *(_DWORD *)a1,
           *(_DWORD *)(a1 + 4),
           *(_DWORD *)(a1 + 36));
}


// ==================== hash_update (sub_B258) @0xB258 size=32 ====================
int __fastcall hash_update(int a1, int a2, int a3)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, int, int))(a1 + 28))(*(_DWORD *)a1, *(_DWORD *)(a1 + 4), a2, a3);
}


// ==================== hash_final (sub_B278) @0xB278 size=20 ====================
int __fastcall hash_final(int a1, int a2)
{
  return (*(int (__fastcall **)(_DWORD, _DWORD, int, _DWORD))(a1 + 32))(
           *(_DWORD *)a1,
           *(_DWORD *)(a1 + 4),
           a2,
           *(_DWORD *)(a1 + 36));
}


// ==================== auth_xor_mask_generate (sub_B28C) @0xB28C size=160 ====================
int __fastcall auth_xor_mask_generate(int a1, int a2, int a3, _BYTE *a4, int a5)
{
  _BYTE *v7; // r6
  int v9; // r4
  int v11; // r7
  unsigned int v12; // r0

  v7 = a4;
  if ( !a2 || !a4 )
    return 24576;
  v9 = 0;
  while ( a5 )
  {
    MEMORY[0x103B80] = HIBYTE(v9);
    MEMORY[0x103B81] = BYTE2(v9);
    MEMORY[0x103B82] = BYTE1(v9);
    MEMORY[0x103B83] = v9++;
    v11 = hash_init(a1);
    if ( v11 )
      return v11;
    v11 = hash_update(a1, a2, a3);
    if ( v11 )
      goto LABEL_15;
    v11 = hash_update(a1, 1063808, 4);
    if ( v11 )
      goto LABEL_15;
    v12 = hash_final(a1, 1063808);
    v11 = v12;
    if ( v12 )
      return v11;
    while ( v12 < 0x20 && a5 )
    {
      *v7++ = *(_BYTE *)(v12 + 1063808);
      ++v12;
      --a5;
    }
  }
  v11 = 0;
LABEL_15:
  hash_final(a1, 1063808);
  return v11;
}


// ==================== auth_rsa_verify (sub_B32C) @0xB32C size=418 ====================
int __fastcall auth_rsa_verify(int *a1)
{
  unsigned int v2; // r5
  unsigned int v4; // r6
  unsigned int v5; // r0
  int v6; // r0
  unsigned __int8 *v7; // r7
  unsigned int v8; // r0
  int v9; // r7
  unsigned int i; // r5

  mem_set_bytes(1063872, 0, 256);
  mem_set_bytes(1064384, 0, 256);
  mem_set_bytes(1064128, 0, 256);
  if ( !a1 || !a1[10] )
    return 24576;
  a1[16] = 0;
  v2 = a1[15];
  v4 = (v2 << 29 != 0) + (v2 >> 3);
  if ( v4 > 0x100 )
    return 24579;
  v5 = a1[14];
  if ( v5 > v4 )
    return 24576;
  if ( v5 + 34 > v4 )
    return 24576;
  v6 = a1[13];
  if ( v6 != v4 )
    return 24576;
  v7 = (unsigned __int8 *)a1[12];
  if ( v7[v6 - 1] != 188 )
    return 24640;
  mem_copy_bytes(1063872, a1[12], v4 - 33);
  mem_copy_bytes(1064128, &v7[v4 - 33], 32);
  if ( (*v7 & ~(0xFFu >> (8 * v4 - v2 + 1))) != 0 )
    return 24641;
  v8 = auth_xor_mask_generate((int)a1, 1064128, 32, (_BYTE *)0x103DC0, v4 - 33);
  v9 = v8;
  if ( !v8 )
  {
    while ( v4 - 33 > v8 )
    {
      *(_BYTE *)(v8 + 1063872) ^= *(_BYTE *)(v8 + 1064384);
      ++v8;
    }
    MEMORY[0x103BC0] &= 0xFFu >> (8 * v4 - a1[15] + 1);
    for ( i = 0; v4 - a1[14] - 34 > i; ++i )
    {
      if ( *(_BYTE *)(i + 1063872) )
        return 24642;
    }
    if ( *(_BYTE *)(i + 1063872) != 1 )
      return 24643;
    mem_set_bytes(1064384, 0, 8);
    v9 = hash_init((int)a1);
    if ( !v9 )
    {
      v9 = hash_update((int)a1, 1064384, 8);
      if ( !v9 )
      {
        v9 = hash_update((int)a1, a1[10], a1[11]);
        if ( !v9 )
        {
          v9 = hash_update((int)a1, i + 1063873, a1[14]);
          if ( !v9 )
          {
            v9 = hash_final((int)a1, 1064384);
            if ( !v9 && !mem_cmp(1064384, 1064128, 32) )
              a1[16] = 1;
          }
        }
      }
    }
  }
  return v9;
}


// ==================== sub_B4DC @0xB4DC size=50 ====================
int __fastcall sub_B4DC(int a1, int a2, _DWORD *a3)
{
  mem_set_bytes(a2, 0, 112);
  if ( *a3 << 30 )
    return 24583;
  if ( !a3[1] )
    return 24586;
  sub_B56C(a2);
  return 0;
}


// ==================== sub_B50E @0xB50E size=4 ====================
int sub_B50E()
{
  return 0;
}


// ==================== sub_B512 @0xB512 size=30 ====================
int __fastcall sub_B512(int a1, int a2, _DWORD *a3, int a4)
{
  sub_B818(a2, *a3, a3[1]);
  sub_B944(a4, a2);
  return 0;
}


// ==================== sub_B530 @0xB530 size=24 ====================
int __fastcall sub_B530(int a1, int a2)
{
  mem_set_bytes(a2, 0, 112);
  sub_B56C(a2);
  return 0;
}


// ==================== sub_B548 @0xB548 size=24 ====================
int __fastcall sub_B548(int a1, int a2, int a3, int a4)
{
  if ( !a4 )
    return 24586;
  sub_B818(a2, a3, a4);
  return 0;
}


// ==================== sub_B560 @0xB560 size=12 ====================
int __fastcall sub_B560(int a1, int a2, int a3)
{
  sub_B944(a3, a2);
  return 0;
}


// ==================== sub_B56C @0xB56C size=96 ====================
int __fastcall sub_B56C(_DWORD *a1)
{
  *a1 = 1779033703;
  a1[1] = -1150833019;
  a1[2] = 1013904242;
  a1[3] = -1521486534;
  a1[4] = 1359893119;
  a1[5] = -1694144372;
  a1[6] = 528734635;
  a1[7] = 1541459225;
  a1[8] = 0;
  a1[9] = 0;
  a1[26] = 0;
  a1[27] = 32;
  return 1;
}


// ==================== sub_B5CC @0xB5CC size=588 ====================
_DWORD *__fastcall sub_B5CC(_DWORD *result, unsigned __int8 *a2, int a3)
{
  int v3; // r2
  int v4; // r6
  int v5; // r5
  int v6; // lr
  int v7; // r3
  int v8; // r12
  int v9; // r7
  int v10; // r8
  int i; // r4
  unsigned __int8 *v12; // r1
  int v13; // t1
  int v14; // r9
  int v15; // t1
  int v16; // r9
  int v17; // t1
  int v18; // r9
  int v19; // t1
  int v20; // r9
  int v21; // r9
  int v22; // r10
  unsigned int v23; // r9
  unsigned int v24; // r9
  int v25; // r10
  int v26; // r9
  int v27; // r10
  _DWORD v29[16]; // [sp+0h] [bp-70h]
  int v30; // [sp+40h] [bp-30h]
  int v31; // [sp+44h] [bp-2Ch]
  int v32; // [sp+48h] [bp-28h]
  int v33; // [sp+4Ch] [bp-24h]
  int v34; // [sp+50h] [bp-20h]
  int v35; // [sp+54h] [bp-1Ch]
  int v36; // [sp+58h] [bp-18h]
  int v37; // [sp+5Ch] [bp-14h]
  int v38; // [sp+60h] [bp-10h]
  _DWORD *v39; // [sp+64h] [bp-Ch]
  unsigned __int8 *v40; // [sp+68h] [bp-8h]
  int v41; // [sp+6Ch] [bp-4h]

  v39 = result;
  v40 = a2;
  v41 = a3;
  while ( v41-- != 0 )
  {
    v3 = *result;
    v38 = *result;
    v4 = result[1];
    v37 = v4;
    v5 = result[2];
    v36 = v5;
    v6 = result[3];
    v35 = v6;
    v7 = result[4];
    v34 = v7;
    v8 = result[5];
    v33 = v8;
    v9 = result[6];
    v32 = v9;
    v10 = result[7];
    v31 = v10;
    for ( i = 0; i < 16; ++i )
    {
      v13 = *a2;
      v12 = a2 + 1;
      v14 = v13 << 24;
      v15 = *v12++;
      v16 = v14 | (v15 << 16);
      v17 = *v12++;
      v18 = v16 | (v17 << 8);
      v19 = *v12;
      a2 = v12 + 1;
      v20 = v18 | v19;
      v29[i] = v20;
      v21 = v20 + dword_130E0[i] + (v7 & v8 ^ v9 & ~v7) + v10 + (__ROR4__(v7, 6) ^ __ROR4__(v7, 11) ^ __ROR4__(v7, 25));
      v22 = (v3 & v4 ^ v3 & v5 ^ v4 & v5) + (__ROR4__(v3, 2) ^ __ROR4__(v3, 13) ^ __ROR4__(v3, 22));
      v10 = v9;
      v9 = v8;
      v8 = v7;
      v7 = v6 + v21;
      v6 = v5;
      v5 = v4;
      v4 = v3;
      v3 = v21 + v22;
    }
    while ( i < 64 )
    {
      v23 = v29[((_BYTE)i + 1) & 0xF];
      v30 = __ROR4__(v23, 7) ^ __ROR4__(v23, 18) ^ (v23 >> 3);
      v24 = v29[((_BYTE)i + 14) & 0xF];
      v25 = v29[i & 0xF] + v30 + (__ROR4__(v24, 17) ^ __ROR4__(v24, 19) ^ (v24 >> 10)) + v29[((_BYTE)i + 9) & 0xF];
      v29[i & 0xF] = v25;
      v26 = dword_130E0[i] + (v7 & v8 ^ v9 & ~v7) + v10 + (__ROR4__(v7, 6) ^ __ROR4__(v7, 11) ^ __ROR4__(v7, 25)) + v25;
      v27 = (v3 & v4 ^ v3 & v5 ^ v4 & v5) + (__ROR4__(v3, 2) ^ __ROR4__(v3, 13) ^ __ROR4__(v3, 22));
      v10 = v9;
      v9 = v8;
      v8 = v7;
      v7 = v6 + v26;
      v6 = v5;
      v5 = v4;
      v4 = v3;
      v3 = v26 + v27;
      ++i;
    }
    *result = v3 + v38;
    result[1] = v37 + v4;
    result[2] = v36 + v5;
    result[3] = v35 + v6;
    result[4] = v34 + v7;
    result[5] = v33 + v8;
    result[6] = v32 + v9;
    result[7] = v31 + v10;
  }
  return result;
}


// ==================== sub_B818 @0xB818 size=292 ====================
int __fastcall sub_B818(int a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned int v5; // r5
  unsigned int v6; // r1
  unsigned int v7; // r0
  int v8; // r6
  int v9; // r8
  unsigned int v10; // r6

  v5 = a3;
  if ( !a3 )
    return 1;
  v6 = *(_DWORD *)(a1 + 32);
  v7 = v6 + 8 * a3;
  if ( v6 > v7 )
    ++*(_DWORD *)(a1 + 36);
  *(_DWORD *)(a1 + 36) += a3 >> 29;
  *(_DWORD *)(a1 + 32) = v7;
  v8 = *(_DWORD *)(a1 + 104);
  if ( v8 )
  {
    v9 = a1 + 40;
    if ( a3 < 0x40 && a3 + v8 < 0x40 )
    {
      mem_copy_bytes(v9 + v8, a2, a3);
      *(_DWORD *)(a1 + 104) += v5;
      return 1;
    }
    mem_copy_bytes(v9 + v8, a2, 64 - v8);
    sub_B5CC((_DWORD *)a1, (unsigned __int8 *)(a1 + 40), 1);
    a2 += 64 - v8;
    v5 -= 64 - v8;
    *(_DWORD *)(a1 + 104) = 0;
    mem_set_bytes(a1 + 40, 0, 64);
  }
  v10 = v5 >> 6;
  if ( v5 >> 6 )
  {
    sub_B5CC((_DWORD *)a1, a2, v5 >> 6);
    a2 += 64 * v10;
    v5 -= v10 << 6;
  }
  if ( v5 )
  {
    *(_DWORD *)(a1 + 104) = v5;
    mem_copy_bytes(a1 + 40, a2, v5);
  }
  return 1;
}


// ==================== sub_B93C @0xB93C size=8 ====================
_DWORD *__fastcall sub_B93C(_DWORD *a1, unsigned __int8 *a2)
{
  return sub_B5CC(a1, a2, 1);
}


// ==================== sub_B944 @0xB944 size=452 ====================
int __fastcall sub_B944(_BYTE *a1, _DWORD *a2)
{
  unsigned __int8 *v4; // r7
  int v5; // r0
  int v6; // r6
  unsigned int v7; // r0
  unsigned int i; // r1
  int v10; // r0
  unsigned int j; // r1
  int v12; // r0
  unsigned int k; // r1
  int v14; // r0

  v4 = (unsigned __int8 *)(a2 + 10);
  v5 = a2[26];
  *((_BYTE *)a2 + v5 + 40) = 0x80;
  v6 = v5 + 1;
  if ( (unsigned int)(v5 + 1) > 0x38 )
  {
    mem_set_bytes(&v4[v6], 0, 63 - v5);
    v6 = 0;
    sub_B5CC(a2, v4, 1);
  }
  mem_set_bytes(&v4[v6], 0, 56 - v6);
  v4[56] = HIBYTE(a2[9]);
  v4[57] = BYTE2(a2[9]);
  v4[58] = BYTE1(a2[9]);
  v4[59] = a2[9];
  v4[60] = HIBYTE(a2[8]);
  v4[61] = BYTE2(a2[8]);
  v4[62] = BYTE1(a2[8]);
  v4[63] = a2[8];
  sub_B5CC(a2, v4, 1);
  a2[26] = 0;
  mem_set_bytes(v4, 0, 64);
  v7 = a2[27];
  if ( v7 == 28 )
  {
    for ( i = 0; i < 7; ++i )
    {
      v10 = a2[i];
      *a1 = HIBYTE(v10);
      a1[1] = BYTE2(v10);
      a1[2] = BYTE1(v10);
      a1[3] = v10;
      a1 += 4;
    }
  }
  else if ( v7 == 32 )
  {
    for ( j = 0; j < 8; ++j )
    {
      v12 = a2[j];
      *a1 = HIBYTE(v12);
      a1[1] = BYTE2(v12);
      a1[2] = BYTE1(v12);
      a1[3] = v12;
      a1 += 4;
    }
  }
  else
  {
    if ( v7 > 0x20 )
      return 0;
    for ( k = 0; k < a2[27] >> 2; ++k )
    {
      v14 = a2[k];
      *a1 = HIBYTE(v14);
      a1[1] = BYTE2(v14);
      a1[2] = BYTE1(v14);
      a1[3] = v14;
      a1 += 4;
    }
  }
  return 1;
}


// ==================== sub_BB2C @0xBB2C size=46 ====================
int __fastcall sub_BB2C(int a1, int a2, _DWORD *a3)
{
  if ( *a3 << 30 )
    return 24583;
  if ( !a3[1] )
    return 24586;
  sub_C4D8(270598144, a2, 0, 0);
  return 0;
}


// ==================== sub_BB5A @0xBB5A size=4 ====================
int sub_BB5A()
{
  return 0;
}


// ==================== sub_BB5E @0xBB5E size=58 ====================
int __fastcall sub_BB5E(int a1, int a2, int a3, int a4)
{
  int result; // r0

  result = sub_C572(270598144);
  if ( !result )
    return sub_C69A(270598144, a4);
  return result;
}


// ==================== sub_BB98 @0xBB98 size=24 ====================
__int64 __fastcall sub_BB98(int a1, int a2)
{
  sub_C4D8(270598144, a2, 0, 0);
  return 0;
}


// ==================== sub_BBB0 @0xBBB0 size=52 ====================
int __fastcall sub_BBB0(int a1, int a2, int a3, int a4)
{
  if ( a4 )
    return sub_C572(270598144);
  else
    return 24586;
}


// ==================== sub_BBE4 @0xBBE4 size=8 ====================
int __fastcall sub_BBE4(int a1, int a2, int a3)
{
  return sub_C69A(270598144, a3);
}


// ==================== sub_BBF0 @0xBBF0 size=144 ====================
int __fastcall sub_BBF0(int a1, int a2, _DWORD *a3, int a4, char a5)
{
  int v7; // r0
  int v8; // r3
  unsigned int v9; // r1
  unsigned int i; // r2

  if ( a4 )
    v7 = MEMORY[0x1000A004] | 1;
  else
    v7 = MEMORY[0x1000A004];
  MEMORY[0x1000A004] = v7;
  if ( (a3[4] & 8) != 0 && (a5 & 2) != 0 )
    MEMORY[0x1000A00C] |= 0x100u;
  else
    MEMORY[0x1000A00C] &= ~0x100u;
  sub_11C84(*a3, a3[2], a3[1], 268476432);
  if ( (a3[4] & 8) != 0 && (a5 & 2) == 0 )
  {
    v8 = a3[2];
    v9 = *(_DWORD *)(a3[5] + 8) >> 2;
    for ( i = 0; i < v9; ++i )
      *(_DWORD *)(4 * i + 0x1000A020) = *(_DWORD *)(a2 + 4 * i) ^ *(_DWORD *)(v8 + 4 * i);
  }
  return 0;
}


// ==================== sub_BC80 @0xBC80 size=416 ====================
int __fastcall sub_BC80(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  int v7; // r7
  int v8; // r4
  int *v9; // r5
  int v10; // r0
  int v11; // r0
  int v12; // r0
  unsigned int i; // r0
  int v14; // r3
  unsigned int v15; // r2
  unsigned int j; // r0
  int v17; // r1
  int v18; // r1
  unsigned int k; // r0

  v7 = 0;
  v8 = 0;
  v9 = (int *)a3[5];
  if ( !v9 )
    return 24577;
  v10 = a3[4];
  if ( v10 << 31 && !(*a4 << 31) && !*v9 )
    return 24577;
  if ( !v9[1] && (*((_BYTE *)v9 + 12) == 1 || (v10 & 2) != 0) )
    return 24578;
  if ( *a3 << 30 || a3[2] << 30 )
    return 24583;
  v11 = a3[1];
  if ( !v11 )
    return 24586;
  if ( v11 != a3[3] )
    return 24576;
  if ( v11 << 28 )
    return 24584;
  mem_set_bytes(a2, 0, 32);
  if ( (a3[4] & 4) == 0 )
    sub_8704();
  if ( *((_BYTE *)v9 + 12) )
    v7 = 2;
  v12 = v9[2];
  if ( v12 != 16 )
  {
    if ( v12 == 24 )
    {
      v7 |= 0x10u;
    }
    else
    {
      if ( v12 != 32 )
        return 24579;
      v7 |= 0x20u;
    }
  }
  MEMORY[0x1000A004] = v7;
  if ( a3[4] << 31 )
  {
    for ( i = 0; i < 8; ++i )
      *(_DWORD *)(4 * i + 0x1000A020) = 0;
    if ( *a4 << 31 )
    {
      time_get_ms_count(0x1F4u);
      if ( (*a4 & 8) != 0 )
        MEMORY[0x1000A0BC] &= ~2u;
      else
        MEMORY[0x1000A0BC] |= 2u;
      if ( (*a4 & 4) != 0 )
      {
        MEMORY[0x1000A008] |= 0x40000000u;
        time_get_tick();
        while ( MEMORY[0x1000A008] >= 0 )
        {
          if ( time_wait_ticks() )
            return 24644;
        }
        MEMORY[0x1000A0BC] &= ~1u;
      }
      else
      {
        MEMORY[0x1000A0BC] |= 1u;
      }
      MEMORY[0x1000A00C] = 16;
    }
    else
    {
      v14 = *v9;
      v15 = (unsigned int)v9[2] >> 2;
      for ( j = 0; j < v15; ++j )
      {
        v17 = *(_DWORD *)(v14 + 4 * j);
        *(_DWORD *)(a2 + 4 * j) = v17;
        *(_DWORD *)(4 * j + 0x1000A020) = v17;
      }
    }
  }
  if ( (a3[4] & 2) != 0 )
  {
    MEMORY[0x1000A008] = 2;
    v18 = v9[1];
    for ( k = 0; k < 4; ++k )
      *(_DWORD *)(4 * k + 0x1000A040) = *(_DWORD *)(v18 + 4 * k);
  }
  return v8;
}


// ==================== sub_BE20 @0xBE20 size=52 ====================
int __fastcall sub_BE20(int a1, int a2, int a3)
{
  unsigned int i; // r0

  if ( (*(_DWORD *)(a3 + 16) & 0x10) != 0 )
    MEMORY[0x1000A008] = 2;
  if ( (*(_DWORD *)(a3 + 16) & 0x20) != 0 )
  {
    for ( i = 0; i < 8; ++i )
      *(_DWORD *)(4 * i + 0x1000A020) = 0;
  }
  if ( (*(_DWORD *)(a3 + 16) & 0x40) == 0 )
    sub_8704();
  return 0;
}


// ==================== sub_BE54 @0xBE54 size=14 ====================
int __fastcall sub_BE54(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  return sub_BBF0(a1, a2, a3, 1, *a4);
}


// ==================== sub_BE62 @0xBE62 size=14 ====================
int __fastcall sub_BE62(int a1, int a2, _DWORD *a3, _DWORD *a4)
{
  return sub_BBF0(a1, a2, a3, 0, *a4);
}


// ==================== sub_BE74 @0xBE74 size=50 ====================
unsigned int __fastcall sub_BE74(unsigned int result, int a2)
{
  if ( MEMORY[0x102844] == 1347241293 )
  {
    if ( MEMORY[0x1021405C] == 1347241293 )
      MEMORY[0x1021405C] = 0;
    if ( result )
      MEMORY[0x1021405C] = MEMORY[0x1021405C] | ((unsigned __int16)result << 16);
    if ( a2 )
    {
      result = MEMORY[0x1021405C] & 0xFFFF0000 | a2;
      MEMORY[0x1021405C] = result;
    }
  }
  return result;
}


// ==================== sub_BEA6 @0xBEA6 size=44 ====================
int sub_BEA6()
{
  if ( MEMORY[0x102844] == 1347241293 )
    return 1;
  if ( sub_BFE0() != 1 || MEMORY[0x1021405C] != 1347241293 )
    return 0;
  MEMORY[0x102844] = 1347241293;
  return 1;
}


// ==================== sub_BED2 @0xBED2 size=42 ====================
int sub_BED2()
{
  if ( !sub_BFE0() )
    return 4136;
  if ( MEMORY[0x1021405C] == 1347241293 || MEMORY[0x1021405C] == 1380209483 )
    return 0;
  return 4139;
}


// ==================== sub_BEFC @0xBEFC size=4 ====================
int sub_BEFC()
{
  return 0;
}


// ==================== sub_BF00 @0xBF00 size=82 ====================
unsigned int __fastcall sub_BF00(_DWORD *a1, int a2, int a3, int a4)
{
  char *v4; // r4
  int v5; // r5
  unsigned int v6; // r6
  int v7; // r0
  int v9; // [sp+0h] [bp-4h] BYREF

  v9 = a4;
  v4 = (char *)(a1 + 129);
  v5 = MEMORY[0x10214058];
  *a1 = MEMORY[0x10214058];
  v6 = auth_find_block_by_type(v5, 0, &v9);
  if ( v6 < 0xFF )
  {
    v6 = auth_check_block_header(v9);
    if ( v6 < 0xFF )
    {
      *((_DWORD *)v4 + 3) = v5;
      strcpy(v4 + 20, "BBBB");
      *((_DWORD *)v4 + 9) = 1;
      *((_DWORD *)v4 + 7) = v5;
      v7 = v9;
      *((_DWORD *)v4 + 8) = *(_DWORD *)(v9 + 32) + v5;
      *((_WORD *)v4 + 13) = *(_WORD *)(v7 + 24);
    }
  }
  sub_BE74(v6, 0);
  return v6;
}


// ==================== sub_BF52 @0xBF52 size=56 ====================
unsigned int __fastcall sub_BF52(int a1, _DWORD *a2, int a3, int a4)
{
  unsigned int v5; // r4
  int v6; // r0
  int v8; // [sp+0h] [bp-4h] BYREF

  v8 = a4;
  v5 = auth_find_block_by_type(*(_DWORD *)(a2[2] + 8), 0, &v8);
  if ( v5 < 0xFF )
  {
    v5 = auth_check_block_header(v8);
    if ( v5 < 0xFF )
    {
      v6 = v8;
      *a2 = *(_DWORD *)(v8 + 28);
      a2[1] = *(_DWORD *)(v6 + 32);
    }
  }
  sub_BE74(v5, 0);
  return v5;
}


// ==================== sub_BF8A @0xBF8A size=58 ====================
unsigned int __fastcall sub_BF8A(int a1, unsigned int *a2)
{
  unsigned int v2; // r5
  unsigned int v3; // r0
  unsigned int v4; // r3
  unsigned int v5; // r4
  unsigned int i; // r2

  v2 = 0;
  v3 = a2[2];
  v4 = *a2;
  v5 = *(_DWORD *)(v3 + 8);
  if ( *a2 != v5 )
  {
    if ( v5 > v4 || v4 >= *(_DWORD *)(v3 + 12) )
    {
      for ( i = 0; a2[1] > i; ++i )
        *(_BYTE *)(v4 + i) = *(_BYTE *)(v5 + i);
    }
    else
    {
      v2 = 4137;
    }
  }
  sub_BE74(v2, 0);
  return v2;
}


// ==================== sub_BFC4 @0xBFC4 size=12 ====================
int __fastcall sub_BFC4(int a1, int a2)
{
  sub_BE74(0, a2);
  return 0;
}


// ==================== sub_BFE0 @0xBFE0 size=4 ====================
int sub_BFE0()
{
  return 1;
}


// ==================== sub_BFE4 @0xBFE4 size=30 ====================
int __fastcall sub_BFE4(int a1)
{
  if ( a1 )
    MEMORY[0x10007010] = a1 | 0x66000000;
  MEMORY[0x10007000] = MEMORY[0x10007000] & 0xDDFFFFF7 | 0x22000000;
  MEMORY[0x10007014] = 4617;
  return 4617;
}


// ==================== sub_C002 @0xC002 size=42 ====================
int sub_C002()
{
  __int64 v0; // r0
  int v1; // r0
  int v2; // r1

  v0 = sub_1214A();
  v1 = sub_11E3C(v0, HIDWORD(v0), 858993459, 1076835123);
  v2 = (32 * sub_120EC(v1)) | 8;
  MEMORY[0x10007004] = v2;
  MEMORY[0x10007008] = 6513;
  MEMORY[0x10007000] = 570425349;
  return 268464128;
}


// ==================== sub_C02C @0xC02C size=10 ====================
int sub_C02C()
{
  MEMORY[0x10007008] = 6513;
  return 6513;
}


// ==================== sub_C036 @0xC036 size=22 ====================
BOOL sub_C036()
{
  return (MEMORY[0x10007040] & 0x10000) != 0 && (MEMORY[0x10007000] & 0x80) != 0;
}


// ==================== sub_C04C @0xC04C size=30 ====================
unsigned int __fastcall sub_C04C(int a1)
{
  unsigned int result; // r0

  if ( a1 )
    result = MEMORY[0x10007000] | 0x22000080;
  else
    result = MEMORY[0x10007000] & 0xDDFFFF7F | 0x22000000;
  MEMORY[0x10007000] = result;
  return result;
}


// ==================== periph_set_bit30_100070A4 (sub_C06A) @0xC06A size=14 ====================
int periph_set_bit30_100070A4()
{
  MEMORY[0x100070A4] |= 0x66000001u;
  return 268464292;
}


// ==================== sub_C08C @0xC08C size=32 ====================
int *__fastcall sub_C08C(int *result, unsigned int a2)
{
  int *v2; // r2
  unsigned int i; // r3
  int v4; // r4

  v2 = &result[a2 - 1];
  for ( i = 0; i < a2 >> 1; ++i )
  {
    v4 = *v2;
    *v2-- = *result;
    *result++ = v4;
  }
  return result;
}


// ==================== sub_C0AC @0xC0AC size=32 ====================
char *__fastcall sub_C0AC(char *result, unsigned int a2)
{
  char *v2; // r2
  unsigned int i; // r3
  char v4; // r4

  v2 = &result[a2 - 1];
  for ( i = 0; i < a2 >> 1; ++i )
  {
    v4 = *v2;
    *v2-- = *result;
    *result++ = v4;
  }
  return result;
}


// ==================== sub_C0CC @0xC0CC size=18 ====================
int __fastcall sub_C0CC(int result, int a2, unsigned int a3)
{
  unsigned int i; // r3

  for ( i = 0; i < a3; ++i )
    *(_BYTE *)(result + i) = *(_BYTE *)(a2 + i);
  return result;
}


// ==================== sub_C0DE @0xC0DE size=30 ====================
int __fastcall sub_C0DE(int result, int a2, unsigned int a3)
{
  unsigned int v3; // r3
  int v4; // r5
  unsigned int i; // r4
  int v6; // r6
  char v7; // r7
  int v8; // r6

  v3 = a3 - 1;
  v4 = 0;
  for ( i = 0; i < a3; ++i )
  {
    v6 = v4++;
    v7 = *(_BYTE *)(a2 + v6);
    v8 = v3--;
    *(_BYTE *)(result + v8) = v7;
  }
  return result;
}


// ==================== sub_C0FC @0xC0FC size=14 ====================
int __fastcall sub_C0FC(int result, char a2, unsigned int a3)
{
  unsigned int i; // r3

  for ( i = 0; i < a3; ++i )
    *(_BYTE *)(result + i) = a2;
  return result;
}


// ==================== sub_C10A @0xC10A size=28 ====================
int __fastcall sub_C10A(int a1, int a2, unsigned int a3)
{
  unsigned int i; // r3

  for ( i = 0; i < a3; ++i )
  {
    if ( *(unsigned __int8 *)(a1 + i) != *(unsigned __int8 *)(a2 + i) )
      return 0;
  }
  return 1;
}


// ==================== sub_C126 @0xC126 size=52 ====================
int __fastcall sub_C126(int result, int a2, int a3, int a4)
{
  BOOL v4; // r4
  unsigned int v5; // lr
  unsigned int i; // r2
  unsigned int v7; // r7
  unsigned int v8; // r6
  unsigned int v9; // r12

  v4 = 0;
  v5 = 8 * a3;
  for ( i = 0; i <= v5; ++i )
  {
    v7 = *(_DWORD *)(result + 4 * i);
    v8 = *(_DWORD *)(a2 + 4 * i);
    v9 = v7 - v4 - v8;
    v4 = v7 < v4 || v7 - v4 < v8;
    *(_DWORD *)(a4 + 4 * i) = v9;
  }
  return result;
}


// ==================== sub_C15A @0xC15A size=124 ====================
int __fastcall sub_C15A(int result, int a2, unsigned int a3)
{
  unsigned int i; // r4
  unsigned int v4; // r3
  unsigned int v5; // r1
  unsigned int j; // r3
  unsigned int v7; // r1
  unsigned int k; // r1

  for ( i = 0; i < a3; ++i )
    *(_DWORD *)(result + 4 * i) = HIBYTE(*(_DWORD *)(result + 4 * i))
                                | ((*(_DWORD *)(result + 4 * i) & 0xFF0000u) >> 8)
                                | ((*(_DWORD *)(result + 4 * i) & 0xFF00) << 8)
                                | (*(_DWORD *)(result + 4 * i) << 24);
  v4 = *(_DWORD *)(result + 4 * (a3 - 1));
  v5 = a2 + v4;
  *(_DWORD *)(result + 4 * (a3 - 1)) = v5;
  if ( v5 < v4 )
  {
    for ( j = a3 - 2; ; --j )
    {
      v7 = *(_DWORD *)(result + 4 * j);
      *(_DWORD *)(result + 4 * j) = v7 + 1;
      if ( v7 + 1 >= v7 || !j )
        break;
    }
  }
  for ( k = 0; k < a3; ++k )
    *(_DWORD *)(result + 4 * k) = HIBYTE(*(_DWORD *)(result + 4 * k))
                                | ((*(_DWORD *)(result + 4 * k) & 0xFF0000u) >> 8)
                                | ((*(_DWORD *)(result + 4 * k) & 0xFF00) << 8)
                                | (*(_DWORD *)(result + 4 * k) << 24);
  return result;
}


// ==================== sub_C1D8 @0xC1D8 size=38 ====================
_DWORD *__fastcall sub_C1D8(int a1, _DWORD *a2)
{
  _DWORD *result; // r0

  while ( !(*(_DWORD *)(a1 + 3740) << 28) )
    ;
  result = (_DWORD *)(a1 + 3712);
  *result = *a2;
  result[1] = a2[1];
  result[2] = a2[2];
  result[3] = a2[3];
  result[4] = a2[4];
  result[5] = a2[5];
  return result;
}


// ==================== sub_C1FE @0xC1FE size=302 ====================
int __fastcall sub_C1FE(int a1, int a2, int a3, int a4, int a5, unsigned __int16 a6, int a7)
{
  unsigned __int16 v8; // r5
  int v9; // r3
  int v10; // r3
  int v12; // [sp+8h] [bp-50h] BYREF
  int v13; // [sp+Ch] [bp-4Ch]
  _BYTE v14[32]; // [sp+10h] [bp-48h] BYREF
  int v15; // [sp+30h] [bp-28h] BYREF
  int v16; // [sp+34h] [bp-24h]
  int v17; // [sp+38h] [bp-20h]
  int v18; // [sp+3Ch] [bp-1Ch]
  unsigned int v19; // [sp+40h] [bp-18h]
  int v20; // [sp+44h] [bp-14h]
  int v21; // [sp+48h] [bp-10h]
  int v22; // [sp+4Ch] [bp-Ch]
  int v23; // [sp+50h] [bp-8h]
  int v24; // [sp+54h] [bp-4h]

  v21 = a1;
  v22 = a2;
  v23 = a3;
  v24 = a4;
  v8 = a4;
  sub_11610(v14, dword_13210, 32);
  v12 = 0;
  v13 = 0;
  sub_DAB8(v14, 0, &v12, 32, 1, 0);
  sub_C738(v21);
  v9 = 2048;
  if ( !a7 || a7 == 2 )
  {
    v17 = 0;
    v18 = 0;
    v19 = 16779301;
    v15 = v12;
    v20 = (unsigned __int16)v13;
    v16 = 130;
    sub_C1D8(v21, &v15);
    v15 = 0;
    v17 = 0;
    v18 = 0;
    v20 = 0;
    v19 = 67110949;
    v16 = 134217793;
    sub_C1D8(v21, &v15);
  }
  if ( a7 == 1 || a7 == 2 )
  {
    v17 = 0;
    v18 = 0;
    v15 = a5;
    v20 = a6;
    v16 = 66;
    v19 = v9 & 0xF03FFFC0 | 0x2000020;
    sub_C1D8(v21, &v15);
    v17 = 0;
    v18 = 0;
    v15 = a3;
    v20 = v8;
    v16 = 66;
    v19 = v10 & 0xF03FFFC0 | 0x4000020;
    sub_C1D8(v21, &v15);
  }
  return sub_DADE(v14, 0, &v12, 32, 1, 0);
}


// ==================== sub_C32C @0xC32C size=358 ====================
void __fastcall sub_C32C(int a1, int a2, int a3, int a4, int a5, unsigned __int16 a6, int a7, int a8, int a9, int a10)
{
  unsigned __int16 v11; // r7
  int v12; // r8
  int v13; // r3
  _DWORD v14[2]; // [sp+8h] [bp-50h] BYREF
  _BYTE v15[32]; // [sp+10h] [bp-48h] BYREF
  int v16; // [sp+30h] [bp-28h] BYREF
  int v17; // [sp+34h] [bp-24h]
  int v18; // [sp+38h] [bp-20h]
  int v19; // [sp+3Ch] [bp-1Ch]
  int v20; // [sp+40h] [bp-18h]
  int v21; // [sp+44h] [bp-14h]
  int v22; // [sp+48h] [bp-10h]
  int v23; // [sp+4Ch] [bp-Ch]
  int v24; // [sp+50h] [bp-8h]
  int v25; // [sp+54h] [bp-4h]

  v22 = a1;
  v23 = a2;
  v24 = a3;
  v25 = a4;
  v11 = a4;
  v12 = 0;
  sub_DAB8(v15, 0, v14, 32, 1, 0);
  if ( a10 == 2 )
    v12 = sub_C73C(v22);
  if ( v12 )
LABEL_21:
    JUMPOUT(0xC326);
  v13 = 2;
  if ( a8 == 1 && (!a9 || a9 == 2) )
  {
    v16 = 0;
    v17 = 0;
    v20 = 151521323;
    v18 = v14[0];
    v21 = v14[1] << 16;
    v19 = 66;
    sub_C1D8(v22, &v16);
  }
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v16 = a3;
  v21 = v11;
  v17 = v13 & 0x38000003 | (4 * (a7 & 0xFFFFFF)) & 0x3BFFFFFF;
  if ( a9 )
  {
    if ( a9 == 1 )
    {
      v20 = 1;
      v18 = a5;
      v21 = (unsigned __int16)v21 | (a6 << 16);
      v19 = v13 & 0x30000003 | (4 * (a7 & 0xFFFFFF)) & 0x33FFFFFF;
    }
    else if ( a9 == 2 )
    {
      v20 = 10;
      v18 = a5;
      v21 = (unsigned __int16)v21 | (a6 << 16);
      v19 = v13 & 0x30000003 | (4 * (a7 & 0xFFFFFF)) & 0x33FFFFFF;
    }
  }
  else
  {
    v20 = 7;
  }
  sub_C1D8(v22, &v16);
  if ( a10 )
  {
    if ( a10 == 1 || a10 == 2 )
    {
      if ( a8 == 1 )
        goto LABEL_18;
    }
    else if ( a10 != 3 )
    {
      goto LABEL_18;
    }
    sub_C73C(v22);
  }
LABEL_18:
  sub_DADE(v15, 0, v14, 32, 1, 0);
  goto LABEL_21;
}


// ==================== sub_C492 @0xC492 size=44 ====================
int __fastcall sub_C492(int a1, int a2, int a3, int a4)
{
  _DWORD v6[6]; // [sp+0h] [bp-18h] BYREF

  v6[0] = 0;
  v6[1] = 0;
  v6[4] = 135006251;
  v6[2] = a3;
  v6[5] = a4 << 16;
  v6[3] = 130;
  sub_C1D8(a1, v6);
  return sub_C73C(a1);
}


// ==================== sub_C4D8 @0xC4D8 size=154 ====================
int __fastcall sub_C4D8(int a1, __int64 a2, __int64 a3, int a4)
{
  int result; // r0
  int v8; // [sp+10h] [bp-14h] BYREF
  int v9; // [sp+14h] [bp-10h]
  int v10; // [sp+18h] [bp-Ch] BYREF
  int v11; // [sp+1Ch] [bp-8h]

  v10 = 0;
  v11 = 0;
  v8 = 0;
  v9 = 0;
  if ( a2 )
    sub_DAB8(a2, HIDWORD(a2), &v10, 16, 1, 0);
  if ( a3 )
    sub_DAB8(a3, HIDWORD(a3), &v8, 16, 1, 0);
  sub_C1FE(a1, v9, v10, v11, v8, v9, a4);
  if ( a2 )
    sub_DADE(a2, HIDWORD(a2), &v10, 16, 1, 0);
  result = a3 | HIDWORD(a3);
  if ( a3 )
    return sub_DADE(a3, HIDWORD(a3), &v8, 16, 1, 0);
  return result;
}


// ==================== sub_C572 @0xC572 size=296 ====================
int __fastcall sub_C572(int a1, int a2, __int64 a3, __int64 a4, int a5, int a6, int a7, int a8)
{
  int v9; // r0
  int v11; // [sp+18h] [bp-28h] BYREF
  int v12; // [sp+1Ch] [bp-24h]
  int v13; // [sp+20h] [bp-20h] BYREF
  int v14; // [sp+24h] [bp-1Ch]
  int v15; // [sp+2Ch] [bp-14h]
  int v16; // [sp+30h] [bp-10h]
  int v17; // [sp+34h] [bp-Ch]
  __int64 v18; // [sp+38h] [bp-8h]

  v16 = a1;
  v17 = a2;
  v18 = a3;
  v13 = 0;
  v14 = 0;
  v11 = 0;
  v12 = 0;
  if ( !a3 )
  {
    if ( !a4 )
      goto LABEL_8;
    goto LABEL_7;
  }
  if ( a3 != a4 )
  {
    sub_DAB8(a3, HIDWORD(a3), &v13, a5, 1, 0);
    if ( !a4 )
      goto LABEL_8;
LABEL_7:
    sub_DAB8(a4, HIDWORD(a4), &v11, a5, 2, 0);
    goto LABEL_8;
  }
  sub_DAB8(a3, HIDWORD(a3), &v13, a5, 3, 0);
  v11 = v13;
  v12 = v14;
LABEL_8:
  sub_C32C(v16, v12, v13, v14, v11, v12, a5, a6, a7, a8);
  v15 = v9;
  if ( a3 && a3 == a4 )
  {
    sub_DADE(a3, HIDWORD(a3), &v13, a5, 3, 0);
  }
  else if ( a3 )
  {
    sub_DADE(a3, HIDWORD(a3), &v13, a5, 1, 0);
  }
  if ( a4 && a4 != a3 )
    sub_DADE(a4, HIDWORD(a4), &v11, a5, 2, 0);
  return v15;
}


// ==================== sub_C69A @0xC69A size=74 ====================
int __fastcall sub_C69A(int a1, int a2)
{
  int v4; // r7
  int v6; // [sp+8h] [bp-8h] BYREF
  int v7; // [sp+Ch] [bp-4h]

  v6 = 0;
  v7 = 0;
  if ( a2 )
    sub_DAB8(a2, 0, &v6, 32, 2, 0);
  v4 = sub_C492(a1, a2, v6, v7);
  if ( a2 )
    sub_DADE(a2, 0, &v6, 32, 2, 0);
  return v4;
}


// ==================== sub_C6E4 @0xC6E4 size=84 ====================
int __fastcall sub_C6E4(int a1, __int64 a2, int a3, int a4)
{
  int result; // r0

  sub_C4D8(a1, 0, 0, 0);
  result = sub_C572(a1, 0, a2, 0, a3, 1, 0, 0);
  if ( !result )
    return sub_C69A(a1, a4);
  return result;
}


// ==================== sub_C738 @0xC738 size=4 ====================
// attributes: thunk
int __fastcall sub_C738(int a1)
{
  return sub_C7E4(a1);
}


// ==================== sub_C73C @0xC73C size=162 ====================
int __fastcall sub_C73C(int a1)
{
  int v2; // r0
  int v4; // [sp+8h] [bp-28h] BYREF
  int v5; // [sp+Ch] [bp-24h]
  _DWORD v6[6]; // [sp+10h] [bp-20h] BYREF
  _DWORD v7[2]; // [sp+28h] [bp-8h] BYREF

  v7[0] = 0;
  v4 = 0;
  v5 = 0;
  sub_C7E4(a1);
  sub_DAB8(v7, 0, &v4, 4, 3, 0);
  v6[0] = 0;
  v6[1] = 134217745;
  v6[2] = v4;
  v6[5] = v5 << 16;
  v6[3] = 134217746;
  v6[4] = 256;
  sub_C1D8(a1, v6);
  while ( (sub_C7EC(a1) & 4) == 0 )
    ;
  do
    v2 = *(_DWORD *)(a1 + 2976);
  while ( !v2 );
  if ( v2 == 1 )
  {
    sub_C7E4(a1);
    sub_DADE(v7, 0, &v4, 4, 3, 0);
    return 0;
  }
  else
  {
    sub_DADE(v7, 0, &v4, 4, 3, 0);
    return 47105;
  }
}


// ==================== sub_C7E4 @0xC7E4 size=8 ====================
int __fastcall sub_C7E4(int result)
{
  *(_DWORD *)(result + 2568) = 4;
  return result;
}


// ==================== sub_C7EC @0xC7EC size=12 ====================
int __fastcall sub_C7EC(int a1)
{
  int result; // r0

  do
    result = *(_DWORD *)(a1 + 2560);
  while ( !result );
  return result;
}


// ==================== sub_C7F8 @0xC7F8 size=62 ====================
int __fastcall sub_C7F8(_DWORD *a1)
{
  a1[643] = 0;
  while ( (a1[687] & 1) == 0 )
    ;
  if ( HIBYTE(a1[586]) != 223 )
    return 45067;
  if ( a1[649] == -708427520 )
    return 0;
  return 45068;
}


// ==================== sub_C836 @0xC836 size=130 ====================
int __fastcall sub_C836(int a1, _DWORD *a2)
{
  int v3; // r5
  int result; // r0
  int v5; // r0
  unsigned int v6; // [sp+0h] [bp-4h] BYREF

  v6 = 0;
  if ( !a2 )
    return 45057;
  while ( (*(_DWORD *)(a1 + 2748) & 1) == 0 )
    ;
  v3 = (unsigned __int8)*(_DWORD *)(a1 + 2772);
  *a2 = v3;
  result = sub_CDF4(a1, 10, &v6);
  if ( !result )
  {
    v5 = HIWORD(v6) & 0xF;
    switch ( v3 )
    {
      case 1:
        goto LABEL_17;
      case 3:
        if ( v5 != 12 && v5 != 3 )
          return 45061;
        break;
      case 5:
        if ( v5 != 3 )
          return 45061;
        if ( ((*(_DWORD *)(a1 + 2772) >> 8) & 1) != 0 )
          return 45058;
LABEL_17:
        if ( ((*(_DWORD *)(a1 + 2772) >> 9) & 1) != 0 )
          return 45059;
        break;
    }
    return 0;
  }
  return result;
}


// ==================== sub_C8B8 @0xC8B8 size=232 ====================
int __fastcall sub_C8B8(int a1, unsigned int a2, int a3, unsigned int a4)
{
  int v8; // r6
  int result; // r0
  int v10; // r10
  unsigned int i; // r4
  unsigned int v12; // r0
  int v13; // r5
  int v14; // [sp+0h] [bp-8h] BYREF
  unsigned int v15; // [sp+4h] [bp-4h] BYREF

  v15 = 0;
  v8 = 0;
  v14 = 0;
  result = 45057;
  if ( a3 )
  {
    if ( a4 == 4 )
    {
      if ( a2 > 1 )
        return result;
    }
    else if ( a4 != 8 || a2 != 2 )
    {
      return result;
    }
    result = sub_C836(a1, &v15);
    if ( !result )
    {
      if ( a2 == 1 )
        v10 = 20;
      else
        v10 = 16;
      for ( i = 0; i < a4; ++i )
      {
        result = sub_CDF4(a1, v10 + i, &v15);
        if ( result )
          return result;
        v12 = v15;
        *(_DWORD *)(a3 + 4 * i) = v15;
        v8 += 32
            - ((16843009
              * (((((v12 - ((v12 >> 1) & 0x55555555)) >> 2) & 0x33333333)
                + ((v12 - ((v12 >> 1) & 0x55555555)) & 0x33333333)
                + (((((v12 - ((v12 >> 1) & 0x55555555)) >> 2) & 0x33333333)
                  + ((v12 - ((v12 >> 1) & 0x55555555)) & 0x33333333)) >> 4))
               & 0xF0F0F0F)) >> 24);
      }
      result = sub_CDF4(a1, 11, &v14);
      if ( !result )
      {
        if ( a4 == 4 )
        {
          if ( a2 )
            v13 = BYTE1(v14);
          else
            v13 = (unsigned __int8)v14;
        }
        else if ( BYTE1(v14) == 255 )
        {
          v13 = (unsigned __int8)v14;
        }
        else
        {
          v13 = (unsigned __int8)v14 + BYTE1(v14);
        }
        if ( v13 == v8 )
          return 0;
        else
          return 45060;
      }
    }
  }
  return result;
}


// ==================== sub_C9A0 @0xC9A0 size=264 ====================
int __fastcall sub_C9A0(_DWORD *a1, int a2)
{
  int result; // r0
  int v5; // r4
  int v6; // [sp+14h] [bp-3Ch] BYREF
  _BYTE v7[16]; // [sp+18h] [bp-38h] BYREF
  _BYTE v8[8]; // [sp+28h] [bp-28h] BYREF
  _BYTE v9[32]; // [sp+30h] [bp-20h] BYREF

  sub_1153C(v8, "KEY PLATPROVISION KEY", 8);
  sub_1153C(v7, "PROVISION KEY", 13);
  v6 = 0;
  if ( !a2 )
    return 45057;
  result = sub_C836((int)a1, &v6);
  if ( !result )
  {
    if ( (a1[699] & 1) == 1 )
    {
      if ( v6 != 5 && v6 != 7 )
        return 45185;
      if ( v6 != 5 )
        goto LABEL_16;
      if ( (a1[692] & 1) == 1 )
        return 45062;
      result = sub_C8B8((int)a1, 2u, (int)v9, 8u);
      if ( !result )
      {
        result = sub_D2BE(a1, 2, v8, 8, v9, 32, 0, 0, 16);
        if ( !result )
        {
          while ( (a1[701] & 1) == 0 )
            ;
          result = sub_D2BE(a1, 5, v7, 13, v9, 32, a2, 0, 16);
          if ( !result )
          {
LABEL_16:
            a1[688] = 0;
            a1[689] = 0;
            a1[690] = 0;
            a1[691] = 0;
            v5 = sub_CFAC(a1);
            if ( v6 == 7 )
              sub_C0FC(a2, 0, 0x10u);
            return v5;
          }
        }
      }
    }
    else
    {
      sub_C0FC(a2, 0, 0x10u);
      return 45076;
    }
  }
  return result;
}


// ==================== sub_CAA8 @0xCAA8 size=212 ====================
int __fastcall sub_CAA8(_DWORD *a1)
{
  int result; // r0
  int v3; // [sp+14h] [bp-2Ch] BYREF
  _BYTE v4[8]; // [sp+18h] [bp-28h] BYREF
  _BYTE v5[32]; // [sp+20h] [bp-20h] BYREF

  sub_1153C(v4, "KEY PLATPROVISION KEY", 8);
  v3 = 0;
  result = sub_C836((int)a1, &v3);
  if ( !result )
  {
    if ( (a1[699] & 1) == 1 )
    {
      return 45076;
    }
    else if ( ((a1[693] >> 10) & 1) != 0 )
    {
      return 45077;
    }
    else if ( v3 == 5 || v3 == 7 )
    {
      if ( (a1[692] & 1) == 1 )
      {
        return 45062;
      }
      else
      {
        result = sub_C8B8((int)a1, 2u, (int)v5, 8u);
        if ( !result )
        {
          result = sub_D2BE(a1, 2, v4, 8, v5, 32, 0, 0, 16);
          if ( !result )
          {
            while ( (a1[701] & 1) == 0 )
              ;
            result = sub_D1AA(a1);
            if ( !result )
            {
              while ( (a1[700] & 1) == 0 )
                ;
              a1[688] = 0;
              a1[689] = 0;
              a1[690] = 0;
              a1[691] = 0;
              return sub_CFAC(a1);
            }
          }
        }
      }
    }
    else
    {
      return 45186;
    }
  }
  return result;
}


// ==================== sub_CB7C @0xCB7C size=200 ====================
int __fastcall sub_CB7C(int a1, int a2)
{
  int v4; // r5
  int result; // r0
  int v6; // r4
  unsigned int v7; // r2
  unsigned int v8; // [sp+0h] [bp-8h] BYREF
  unsigned int v9; // [sp+4h] [bp-4h] BYREF

  v9 = 0;
  v4 = 0;
  v8 = 0;
  if ( !a2 )
    return 45057;
  result = sub_C836(a1, &v9);
  if ( !result )
  {
    if ( v9 == 7 )
    {
      sub_C0FC(a2, 0, 0x10u);
      return 0;
    }
    else
    {
      v6 = 0;
      while ( 1 )
      {
        result = sub_CDF4(a1, v6 + 12, &v9);
        if ( result )
          break;
        v7 = v9;
        *(_DWORD *)(a2 + 4 * v6) = v9;
        v4 += 32
            - ((16843009
              * ((((v7 - ((v7 >> 1) & 0x55555555)) & 0x33333333)
                + (((v7 - ((v7 >> 1) & 0x55555555)) >> 2) & 0x33333333)
                + ((((v7 - ((v7 >> 1) & 0x55555555)) & 0x33333333)
                  + (((v7 - ((v7 >> 1) & 0x55555555)) >> 2) & 0x33333333)) >> 4))
               & 0xF0F0F0F)) >> 24);
        if ( (unsigned int)++v6 >= 4 )
        {
          result = sub_CDF4(a1, 11, &v8);
          if ( !result )
          {
            if ( v4 == HIBYTE(v8) )
              return 0;
            else
              return 45064;
          }
          return result;
        }
      }
    }
  }
  return result;
}


// ==================== sub_CC44 @0xCC44 size=158 ====================
int __fastcall sub_CC44(int a1, int a2)
{
  int result; // r0
  unsigned int v5; // [sp+14h] [bp-58h] BYREF
  _BYTE v6[4]; // [sp+18h] [bp-54h] BYREF
  _BYTE v7[32]; // [sp+1Ch] [bp-50h] BYREF
  _BYTE v8[32]; // [sp+3Ch] [bp-30h] BYREF
  _BYTE v9[16]; // [sp+5Ch] [bp-10h] BYREF

  sub_1168A(v8, 48);
  sub_1168A(v7, 32);
  sub_1153C(v6, &dword_CDF0, 1);
  if ( !a2 )
    return 45057;
  result = sub_C836(a1, &v5);
  if ( !result )
  {
    result = sub_C8B8(a1, 2u, (int)v8, 8u);
    if ( !result || (result == 45060 || v5 >= 2) && (result == 45065 || v5 != 3) )
    {
      result = sub_D2BE(a1, 1, v6, 1, v7, 32, v9, 0, 16);
      if ( !result )
        return sub_C6E4(a1, (unsigned int)v8, 48, a2);
    }
  }
  return result;
}


// ==================== sub_CCE2 @0xCCE2 size=54 ====================
int __fastcall sub_CCE2(_DWORD *a1)
{
  _DWORD *v1; // r0

  while ( (a1[687] & 1) == 0 )
    ;
  if ( (unsigned __int8)a1[693] == 7 )
    return 45187;
  v1 = a1 + 688;
  *v1 = 0;
  v1[1] = 0;
  v1[2] = 0;
  v1[3] = 0;
  v1[6] = 1;
  return 0;
}


// ==================== sub_CD18 @0xCD18 size=106 ====================
int __fastcall sub_CD18(int a1, int a2, _DWORD *a3)
{
  int result; // r0
  unsigned int v6; // r6
  int v7; // r7
  int v8; // r5
  unsigned int i; // r4
  int v10; // r1
  int v11; // r3
  int v12; // [sp+0h] [bp-4h] BYREF

  v12 = 0;
  result = 45057;
  if ( a3 )
  {
    if ( a2 == 1 )
    {
      v6 = 1;
      v7 = 24;
    }
    else
    {
      if ( a2 != 2 )
        return result;
      v6 = 7;
      v7 = 25;
    }
    while ( (*(_DWORD *)(a1 + 2748) & 1) == 0 )
      ;
    v8 = 0;
    for ( i = 0; i < v6; ++i )
    {
      result = sub_CDF4(a1, v7 + i, &v12);
      if ( result )
        return result;
      v10 = v12;
      v11 = 0;
      while ( v10 )
      {
        v10 &= v10 - 1;
        ++v11;
      }
      v8 += v11;
    }
    *a3 = v8;
    return 0;
  }
  return result;
}


// ==================== sub_CD82 @0xCD82 size=106 ====================
int __fastcall sub_CD82(int a1, int a2, unsigned int a3)
{
  unsigned int v4; // r4
  int result; // r0
  unsigned int v6; // r6
  int v7; // r7
  unsigned int i; // r5
  char v9; // r1
  unsigned int v10; // r2
  int v11; // r1

  v4 = a3;
  result = 45057;
  if ( a2 == 1 )
  {
    if ( a3 > 0x1F )
      return result;
    v6 = 1;
    v7 = 24;
  }
  else
  {
    if ( a2 != 2 || a3 > 0xDF )
      return result;
    v6 = 7;
    v7 = 25;
  }
  for ( i = 0; i < v6; ++i )
  {
    if ( v4 >= 0x20 )
      v9 = 32;
    else
      v9 = v4;
    v10 = 0xFFFFFFFF >> (32 - v9);
    if ( v4 >= 0x20 )
      v11 = 32;
    else
      v11 = v4;
    v4 -= v11;
    result = sub_CE2E(a1, v7 + i, v10);
    if ( result )
      return result;
  }
  return 0;
}


// ==================== sub_CDEC @0xCDEC size=2 ====================
// attributes: thunk
int __fastcall sub_CDEC(int a1, _DWORD *a2)
{
  return sub_C836(a1, a2);
}


// ==================== sub_CDF4 @0xCDF4 size=58 ====================
int __fastcall sub_CDF4(_DWORD *a1, unsigned int a2, _DWORD *a3)
{
  if ( !a3 )
    return 45057;
  if ( a2 > 0x24 )
    return 45057;
  while ( (a1[687] & 1) == 0 )
    ;
  a1[681] = (4 * a2) | 0x10000;
  while ( !(a1[685] << 31) )
    ;
  *a3 = a1[683];
  return 0;
}


// ==================== sub_CE2E @0xCE2E size=4 ====================
int sub_CE2E()
{
  return 0;
}


// ==================== sub_CE34 @0xCE34 size=376 ====================
int __fastcall sub_CE34(
        int a1,
        unsigned int a2,
        int a3,
        int a4,
        int a5,
        unsigned __int16 a6,
        int a7,
        int a8,
        int a9,
        int a10)
{
  __int16 v12; // r5
  int v13; // r0
  int v14; // r0
  unsigned int v16; // [sp+0h] [bp-30h]
  int v17; // [sp+4h] [bp-2Ch] BYREF
  int v18; // [sp+8h] [bp-28h]
  int v19; // [sp+Ch] [bp-24h]
  int v20; // [sp+10h] [bp-20h]
  unsigned int v21; // [sp+14h] [bp-1Ch]
  int v22; // [sp+18h] [bp-18h]
  int v23; // [sp+1Ch] [bp-14h]
  int v24; // [sp+20h] [bp-10h]
  unsigned int v25; // [sp+24h] [bp-Ch]
  int v26; // [sp+28h] [bp-8h]
  int v27; // [sp+2Ch] [bp-4h]

  v24 = a1;
  v25 = a2;
  v26 = a3;
  v27 = a4;
  v12 = a4;
  if ( a2 == 1 )
  {
    if ( ((*(_DWORD *)(v24 + 2720) >> 1) & 1) == 1 )
      v13 = 32;
    else
      v13 = 16;
    v16 = v13;
  }
  else
  {
    v16 = 16;
  }
  sub_C738(v24);
  v17 = 0;
  v19 = 0;
  v20 = 0;
  v22 = 0;
  v23 = (v16 >> 3) - 2;
  v18 = 134217793;
  v21 = ((v23 & 3) << 22) & 0xF0FFE3DF | 0x1001C20;
  sub_C1D8(v24, &v17);
  v17 = 0;
  v18 = 0;
  v19 = 0;
  v20 = 0;
  v21 = 0;
  v22 = 0;
  if ( !a2 )
  {
    v17 = a3;
    LOWORD(v14) = v12;
    HIWORD(v14) = v22;
    v22 = v14;
    v18 = 66;
  }
  v21 = v21 & 0xFFFE7FFF | ((a2 & 3) << 15);
  v21 = v21 & 0xFFCFFFFF | (((a2 >> 2) & 3) << 20);
  v21 = v21 & 0xFFFFC3FF | 0x1C00;
  v21 &= 0xFFF9FFFF;
  v21 = v21 & 0xFF3FFFFF | ((v23 & 3) << 22);
  v21 = v21 & 0xFFFFFFC0 | 0x20;
  v21 = v21 & 0xF0FFFFFF | 0x4000000;
  sub_C1D8(v24, &v17);
  v19 = 0;
  v20 = 0;
  v17 = a5;
  v22 = a6;
  v18 = (4 * (a7 & 0xFFFFFF)) & 0x3BFFFFFD | 2;
  v21 = 1;
  sub_C1D8(v24, &v17);
  if ( a2 != 2 )
  {
    v17 = 0;
    v18 = 0;
    v21 = 134224934;
    v19 = a9;
    v22 = a10 << 16;
    v20 = 66;
    sub_C1D8(v24, &v17);
  }
  return sub_C73C(v24);
}


// ==================== sub_CFAC @0xCFAC size=44 ====================
int __fastcall sub_CFAC(int a1)
{
  _DWORD v3[6]; // [sp+0h] [bp-18h] BYREF

  v3[0] = 0;
  v3[2] = 0;
  v3[3] = 0;
  v3[5] = 0;
  v3[1] = 134217857;
  v3[4] = 75504672;
  sub_C1D8(a1, v3);
  return sub_C73C(a1);
}


// ==================== sub_CFD8 @0xCFD8 size=108 ====================
int __fastcall sub_CFD8(int a1, int a2, int a3, int a4, int a5)
{
  _DWORD v7[6]; // [sp+4h] [bp-18h] BYREF

  if ( (a5 << 30) | (a2 << 30) )
    return 45057;
  v7[4] = 0;
  v7[0] = a2;
  v7[1] = (4 * (a5 & 0xFFFFFF)) & 0x3BFFFFFE | 1;
  v7[2] = a3;
  v7[5] = a4 << 16;
  v7[3] = (4 * (a5 & 0xFFFFFF)) & 0x33FFFFFD | 2;
  sub_C1D8(a1, v7);
  return sub_C73C(a1);
}


// ==================== sub_D044 @0xD044 size=110 ====================
int __fastcall sub_D044(int a1, int a2, int a3, unsigned __int16 a4, int a5, int a6, int a7)
{
  _DWORD v9[6]; // [sp+0h] [bp-18h] BYREF

  v9[4] = 0;
  v9[0] = a3;
  v9[1] = (4 * (a7 & 0xFFFFFF)) & 0x3BFFFFFD | 2;
  v9[2] = a5;
  v9[5] = a4 | (a6 << 16);
  v9[3] = (4 * (a7 & 0xFFFFFF)) & 0x33FFFFFD | 2;
  sub_C1D8(a1, v9);
  return sub_C73C(a1);
}


// ==================== sub_D0B2 @0xD0B2 size=248 ====================
void __fastcall sub_D0B2(int a1, int a2, int a3, int a4, int a5, unsigned __int16 a6, int a7, int a8, int a9, int a10)
{
  unsigned __int16 v11; // r5
  int v12; // [sp+0h] [bp-28h] BYREF
  int v13; // [sp+4h] [bp-24h]
  int v14; // [sp+8h] [bp-20h]
  int v15; // [sp+Ch] [bp-1Ch]
  int v16; // [sp+10h] [bp-18h]
  int v17; // [sp+14h] [bp-14h]
  int v18; // [sp+18h] [bp-10h]
  int v19; // [sp+1Ch] [bp-Ch]
  int v20; // [sp+20h] [bp-8h]
  int v21; // [sp+24h] [bp-4h]

  v18 = a1;
  v19 = a2;
  v20 = a3;
  v21 = a4;
  v11 = a4;
  sub_C738(a1);
  v12 = 0;
  v14 = 0;
  v15 = 0;
  v17 = 0;
  v13 = 134217793;
  v16 = 16780320;
  sub_C1D8(v18, &v12);
  v14 = 0;
  v15 = 0;
  v12 = a3;
  v17 = v11;
  v13 = 66;
  v16 = 67111968;
  sub_C1D8(v18, &v12);
  v14 = 0;
  v15 = 0;
  v12 = a5;
  v17 = a6;
  v13 = (4 * (a7 & 0xFFFFFF)) & 0x3BFFFFFD | 2;
  v16 = 1;
  sub_C1D8(v18, &v12);
  v12 = 0;
  v13 = 0;
  v16 = 134220838;
  v14 = a9;
  v17 = a10 << 16;
  v15 = 66;
  sub_C1D8(v18, &v12);
  sub_C73C(v18);
  JUMPOUT(0xCFA8);
}


// ==================== sub_D1AA @0xD1AA size=38 ====================
void __fastcall sub_D1AA(int a1)
{
  _DWORD v2[6]; // [sp+0h] [bp-18h] BYREF

  v2[0] = 0;
  memset(&v2[2], 0, 16);
  v2[1] = 67092480;
  sub_C1D8(a1, v2);
  sub_C73C(a1);
  JUMPOUT(0xCFD4);
}


// ==================== sub_D1E4 @0xD1E4 size=218 ====================
int __fastcall sub_D1E4(int a1, unsigned int a2, __int64 a3, __int64 a4, int a5, __int64 a6)
{
  int v8; // [sp+Ch] [bp-3Ch]
  int v9; // [sp+18h] [bp-30h] BYREF
  int v10; // [sp+1Ch] [bp-2Ch]
  int v11; // [sp+20h] [bp-28h] BYREF
  int v12; // [sp+24h] [bp-24h]
  int v13; // [sp+28h] [bp-20h] BYREF
  int v14; // [sp+2Ch] [bp-1Ch]
  int v15; // [sp+34h] [bp-14h]
  int v16; // [sp+38h] [bp-10h]
  unsigned int v17; // [sp+3Ch] [bp-Ch]
  __int64 v18; // [sp+40h] [bp-8h]

  v16 = a1;
  v17 = a2;
  v18 = a3;
  v13 = 0;
  v14 = 0;
  v11 = 0;
  v12 = 0;
  v9 = 0;
  v10 = 0;
  if ( a3 )
    sub_DAB8(a3, HIDWORD(a3), &v13, 16, 1, 0);
  if ( a4 )
    sub_DAB8(a4, HIDWORD(a4), &v11, a5, 1, 0);
  if ( a6 )
    sub_DAB8(a6, HIDWORD(a6), &v9, 16, 2, 0);
  v15 = sub_CE34(v16, v17, v13, v14, v11, v12, a5, v8, v9, v10);
  if ( a3 )
    sub_DADE(a3, HIDWORD(a3), &v13, 16, 1, 0);
  if ( a4 )
    sub_DADE(a4, HIDWORD(a4), &v11, a5, 1, 0);
  if ( a6 )
    sub_DADE(a6, HIDWORD(a6), &v9, 16, 2, 0);
  return v15;
}


// ==================== sub_D2BE @0xD2BE size=198 ====================
int __fastcall sub_D2BE(int a1, unsigned int a2, int a3, unsigned int a4, int a5, unsigned int a6, __int64 a7, int a8)
{
  int result; // r0
  int v12; // r0
  int v13; // r7
  char v14; // [sp+18h] [bp-54h] BYREF
  _BYTE v15[3]; // [sp+19h] [bp-53h] BYREF
  int v16; // [sp+5Ch] [bp-10h]
  unsigned int v17; // [sp+60h] [bp-Ch]
  int v18; // [sp+64h] [bp-8h]
  unsigned int v19; // [sp+68h] [bp-4h]

  v16 = a1;
  v17 = a2;
  v18 = a3;
  v19 = a4;
  sub_1168A(&v14, 67);
  if ( a2 != 1 && a2 != 2 && a2 != 3 && a2 != 5 )
    return 46082;
  result = 46083;
  if ( a8 == 16 && (!a4 || a3) && a4 <= 0x20 && (!a6 || a5) && a6 <= 0x20 )
  {
    v14 = 1;
    v12 = 1;
    if ( a4 )
    {
      sub_C0CC((int)v15, a3, a4);
      v12 = a4 + 1;
    }
    v13 = v12 + 1;
    v15[v12 - 1] = 0;
    if ( a6 )
    {
      sub_C0CC((int)&v15[v13 - 1], a5, a6);
      v13 += a6;
    }
    v15[v13 - 1] = 0x80;
    return sub_D1E4(v16, a2, 0, (unsigned int)&v14, a4 + a6 + 3, a7);
  }
  return result;
}


// ==================== sub_D384 @0xD384 size=100 ====================
int __fastcall sub_D384(int a1, int a2, __int64 a3, int a4)
{
  int v7; // r9
  int v9; // [sp+8h] [bp-8h] BYREF
  int v10; // [sp+Ch] [bp-4h]

  v9 = 0;
  v10 = 0;
  if ( a3 )
    sub_DAB8(a3, HIDWORD(a3), &v9, a4, 2, 0);
  v7 = sub_CFD8(a1, a2, v9, v10, a4);
  if ( a3 )
    sub_DADE(a3, HIDWORD(a3), &v9, a4, 2, 0);
  return v7;
}


// ==================== sub_D3E8 @0xD3E8 size=258 ====================
void __fastcall sub_D3E8(int a1, int a2, __int64 a3, __int64 a4, int a5)
{
  int v6; // [sp+10h] [bp-28h] BYREF
  int v7; // [sp+14h] [bp-24h]
  int v8; // [sp+18h] [bp-20h] BYREF
  int v9; // [sp+1Ch] [bp-1Ch]
  int v10; // [sp+24h] [bp-14h]
  int v11; // [sp+28h] [bp-10h]
  int v12; // [sp+2Ch] [bp-Ch]
  __int64 v13; // [sp+30h] [bp-8h]

  v11 = a1;
  v12 = a2;
  v13 = a3;
  v8 = 0;
  v9 = 0;
  v6 = 0;
  v7 = 0;
  if ( a3 && a3 == a4 )
  {
    sub_DAB8(a3, HIDWORD(a3), &v6, a5, 3, 0);
    v8 = v6;
    v9 = v7;
  }
  else if ( a3 )
  {
    sub_DAB8(a3, HIDWORD(a3), &v6, a5, 1, 0);
  }
  if ( a4 && a3 != a4 )
    sub_DAB8(a4, HIDWORD(a4), &v8, a5, 2, 0);
  v10 = sub_D044(v11, v9, v6, v7, v8, v9, a5);
  if ( a3 && a3 == a4 )
  {
    sub_DADE(a3, HIDWORD(a3), &v6, a5, 3, 0);
  }
  else if ( a3 )
  {
    sub_DADE(a3, HIDWORD(a3), &v6, a5, 1, 0);
  }
  if ( a4 )
  {
    if ( a3 != a4 )
      sub_DADE(a4, HIDWORD(a4), &v8, a5, 2, 0);
  }
  JUMPOUT(0xD2BA);
}


// ==================== sub_D4EA @0xD4EA size=212 ====================
void __fastcall sub_D4EA(int a1, int a2, __int64 a3, __int64 a4, int a5, __int64 a6)
{
  int v7; // r0
  int v8; // [sp+Ch] [bp-3Ch]
  int v9; // [sp+18h] [bp-30h] BYREF
  int v10; // [sp+1Ch] [bp-2Ch]
  int v11; // [sp+20h] [bp-28h] BYREF
  int v12; // [sp+24h] [bp-24h]
  int v13; // [sp+28h] [bp-20h] BYREF
  int v14; // [sp+2Ch] [bp-1Ch]
  int v15; // [sp+34h] [bp-14h]
  int v16; // [sp+38h] [bp-10h]
  int v17; // [sp+3Ch] [bp-Ch]
  __int64 v18; // [sp+40h] [bp-8h]

  v16 = a1;
  v17 = a2;
  v18 = a3;
  v13 = 0;
  v14 = 0;
  v11 = 0;
  v12 = 0;
  v9 = 0;
  v10 = 0;
  if ( a3 )
    sub_DAB8(a3, HIDWORD(a3), &v13, 16, 1, 0);
  if ( a4 )
    sub_DAB8(a4, HIDWORD(a4), &v11, a5, 1, 0);
  if ( a6 )
    sub_DAB8(a6, HIDWORD(a6), &v9, 16, 2, 0);
  sub_D0B2(v16, v12, v13, v14, v11, v12, a5, v8, v9, v10);
  v15 = v7;
  if ( a3 )
    sub_DADE(a3, HIDWORD(a3), &v13, 16, 1, 0);
  if ( a4 )
    sub_DADE(a4, HIDWORD(a4), &v11, a5, 1, 0);
  if ( a6 )
    sub_DADE(a6, HIDWORD(a6), &v9, 16, 2, 0);
  JUMPOUT(0xD2B8);
}


// ==================== sub_D5BE @0xD5BE size=144 ====================
int __fastcall sub_D5BE(int a1, int a2, int a3, int a4, int a5)
{
  int v10; // [sp+1Ch] [bp-4h] BYREF

  v10 = 65537;
  sub_D6A2(2048, 0, 0, a1);
  sub_D732(0, 1, a3, 64, a1);
  sub_D732(1, 1, a4, 5, a1);
  sub_D732(2, 1, a2, 64, a1);
  sub_D732(3, 1, &v10, 1, a1);
  sub_D6E4(19, 0, 0, 2, 0, 3, 0, 4, 0, a1);
  sub_D7AE(a5, 64, 4, a1);
  return sub_D6DC(a1);
}


// ==================== sub_D650 @0xD650 size=30 ====================
unsigned int __fastcall sub_D650(int a1, int a2, int a3)
{
  unsigned int result; // r0

  *(_DWORD *)(a3 + 144) = a1;
  *(_DWORD *)(a3 + 148) = a2 << 7;
  for ( result = 2; result < 8; ++result )
    *(_DWORD *)(a3 + 4 * result + 144) = -1;
  return result;
}


// ==================== sub_D66E @0xD66E size=52 ====================
int __fastcall sub_D66E(int a1, int a2, _DWORD *a3)
{
  int v3; // r4
  int v4; // r3
  int v5; // r0

  v3 = 0;
  v4 = 0;
  v5 = a1 - 2;
  do
  {
    if ( v4 >= v5 )
    {
      a3[v4] = 4092;
    }
    else
    {
      a3[v4] = v3;
      v3 += 4 * a2;
    }
    ++v4;
  }
  while ( v4 < 30 );
  a3[30] = v3;
  a3[31] = v3 + 4 * a2;
  a3[33] = 1046560;
  return 1046560;
}


// ==================== sub_D6A2 @0xD6A2 size=58 ====================
unsigned int __fastcall sub_D6A2(int a1, int a2, unsigned int *a3, _DWORD *a4)
{
  int v6; // r4
  unsigned int v7; // r0

  a4[519] = 1;
  v6 = ((unsigned int)(a1 + 127) >> 7) + 1;
  v7 = 0x1000u / (16 * v6);
  if ( v7 >= 0x20 )
    v7 = 32;
  if ( a3 )
    *a3 = v7;
  sub_D66E(v7, v6, a4);
  return sub_D650(a1, v6, (int)a4);
}


// ==================== sub_D6DC @0xD6DC size=8 ====================
int __fastcall sub_D6DC(int result)
{
  *(_DWORD *)(result + 2076) = 0;
  return result;
}


// ==================== sub_D6E4 @0xD6E4 size=78 ====================
int __fastcall sub_D6E4(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10)
{
  int v11; // r5
  int result; // r0
  int v14; // r2

  v11 = a8;
  result = 0;
  if ( a8 == 63 )
  {
    a7 = 1;
    v11 = 0;
  }
  v14 = (a1 << 27) | (a2 << 24) | (a3 << 23) | (a4 << 18) | (a5 << 17) | (a6 << 12) | (a7 << 11) | (v11 << 6) | a9;
  while ( !(*(_DWORD *)(a10 + 176) << 31) )
    ;
  *(_DWORD *)(a10 + 128) = v14;
  return result;
}


// ==================== sub_D732 @0xD732 size=124 ====================
unsigned int __fastcall sub_D732(int a1, int a2, int a3, unsigned int a4, _DWORD *a5)
{
  int v5; // r5
  unsigned int i; // r0
  unsigned int v7; // r2
  int v8; // r5
  unsigned int result; // r0
  unsigned int v10; // r1
  unsigned int v11; // r1
  unsigned int v12; // r1

  while ( !(a5[45] << 31) )
    ;
  v5 = a5[a1];
  a5[53] = v5;
  for ( i = 0; i < a4; ++i )
    a5[54] = *(_DWORD *)(a3 + 4 * i);
  v7 = (a4 + 3) & 0xFFFFFFFC;
  while ( v7 > i )
  {
    a5[54] = 0;
    ++i;
  }
  v8 = v5 + v7;
  while ( !(a5[45] << 31) )
    ;
  result = a5[a2 + 36] + 31;
  v10 = result >> 5;
  if ( result >> 5 > v7 )
  {
    a5[53] = v8;
    result = 0;
    v11 = v10 - v7;
    while ( v11 > result )
    {
      a5[54] = 0;
      ++result;
    }
    v12 = (v11 + 3) & 0xFFFFFFFC;
    while ( v12 > result )
    {
      a5[54] = 0;
      ++result;
    }
  }
  return result;
}


// ==================== sub_D7AE @0xD7AE size=38 ====================
int __fastcall sub_D7AE(int result, unsigned int a2, int a3, _DWORD *a4)
{
  unsigned int i; // r2

  while ( !(a4[45] << 31) )
    ;
  a4[57] = a4[a3];
  for ( i = 0; i < a2; ++i )
    *(_DWORD *)(result + 4 * i) = a4[55];
  return result;
}


// ==================== sub_D7D8 @0xD7D8 size=90 ====================
int __fastcall sub_D7D8(_DWORD *a1, int a2, int a3)
{
  sub_D6A2(2048, 0, 0, a1);
  sub_D732(0, 1, a2, 0x40u, a1);
  sub_D834(0, 2048, 0, 1);
  sub_D7AE(a3, 5u, 1, a1);
  return sub_D6DC((int)a1);
}


// ==================== sub_D834 @0xD834 size=638 ====================
int __fastcall sub_D834(char a1, unsigned int a2, int a3, int a4, int a5, int a6, _DWORD *a7)
{
  unsigned int v10; // r10
  unsigned int v11; // r0
  int v12; // r1
  int v13; // r3
  int v14; // r11
  int v15; // r10
  int v16; // r8
  int i; // r6

  sub_D6E4(8, 7, 0, a5, 1, 0, 0, a5, 0, (int)a7);
  sub_D6E4(8, 7, 0, a5, 1, 0, 0, a5, 0, (int)a7);
  sub_D6E4(8, 7, 0, a6, 1, 0, 0, a6, 0, (int)a7);
  sub_D6E4(8, 7, 0, a6, 1, 0, 0, a6, 0, (int)a7);
  sub_D6E4(8, 7, 0, a4, 1, 0, 0, a4, 0, (int)a7);
  sub_D6E4(8, 7, 0, a4, 1, 0, 0, a4, 0, (int)a7);
  sub_D6E4(9, 7, 0, a3, 1, 0, 0, a6, 0, (int)a7);
  if ( a2 > 0x110 )
  {
    while ( !(a7[45] << 31) )
      ;
    a7[53] = a7[a5] + 12;
    a7[54] = 0x800000;
    v14 = (int)(a2 - 272) / 32;
    v15 = (int)(a2 - 272) % 32;
    v16 = (unsigned __int8)(a1 + 1);
    sub_D6E4(5, v16, 0, a6, 1, 1, 0, a6, 0, (int)a7);
    for ( i = 0; i < v14; ++i )
      sub_D6E4(12, v16, 0, a6, 0, 31, 0, a6, 0, (int)a7);
    if ( v15 )
      sub_D6E4(12, v16, 0, a6, 0, (char)(v15 - 1), 0, a6, 0, (int)a7);
    sub_D6E4(4, v16, 0, a6, 1, 1, 0, a6, 0, (int)a7);
    sub_D6E4(20, v16, 0, a5, 0, a6, 0, a4, 0, (int)a7);
  }
  else
  {
    v10 = a2 + 136;
    v11 = (v10 + 30) >> 5;
    v12 = (v10 - 1) & 0x1F;
    if ( v12 )
    {
      v13 = 1 << v12;
    }
    else
    {
      ++v11;
      v13 = 1;
    }
    while ( !(a7[45] << 31) )
      ;
    a7[53] = v11 + a7[a5] - 1;
    a7[54] = v13;
    sub_D6E4(20, 7, 0, a5, 0, a6, 0, a4, 0, (int)a7);
  }
  sub_D6E4(8, 7, 0, a5, 1, 0, 0, a5, 0, (int)a7);
  sub_D6E4(8, 7, 0, a5, 1, 0, 0, a5, 0, (int)a7);
  sub_D6E4(8, 7, 0, a6, 1, 0, 0, a6, 0, (int)a7);
  sub_D6E4(8, 7, 0, a6, 1, 0, 0, a6, 0, (int)a7);
  return 0;
}


// ==================== sub_DAB8 @0xDAB8 size=38 ====================
int __fastcall sub_DAB8(int result, int a2, int *a3, int a4, int a5)
{
  *a3 = result;
  a3[1] = a2;
  if ( a5 == 1 || a5 == 3 )
    return sub_3B0(result, a4);
  if ( a5 == 2 )
    return sub_3CC(result, a4);
  return result;
}


// ==================== sub_DADE @0xDADE size=18 ====================
int __fastcall sub_DADE(int result, int a2, int a3, int a4, int a5)
{
  if ( a5 == 2 || a5 == 3 )
    return sub_3CC(result, a4);
  return result;
}


// ==================== nullsub_7 @0xDAF0 size=2 ====================
void nullsub_7()
{
  ;
}


// ==================== sub_DAFC @0xDAFC size=6 ====================
int sub_DAFC()
{
  return MEMORY[0x1066B8];
}


// ==================== sub_DB02 @0xDB02 size=222 ====================
int sub_DB02()
{
  int v1; // r1

  mem_set_bytes(1074872, 0, 24);
  if ( sub_856A() )
  {
    mem_set_bytes(1059720, 0, 32);
    mem_copy_bytes(1059720, 1059704, 16);
    return 0;
  }
  nullsub_7();
  v1 = sub_C7F8((_DWORD *)0x10210000);
  if ( v1 )
    goto LABEL_19;
  if ( (~MEMORY[0x10214050] & 0x42000001) == 0 )
  {
    v1 = sub_CCE2((_DWORD *)0x10210000);
    if ( v1 )
      goto LABEL_19;
  }
  if ( sub_CDEC(270598144, (_DWORD *)0x1066B8) )
  {
    v1 = sub_CCE2((_DWORD *)0x10210000);
    if ( v1 )
      goto LABEL_19;
  }
  if ( sub_C836(270598144, (_DWORD *)0x1066B8) )
  {
    v1 = sub_CCE2((_DWORD *)0x10210000);
    if ( v1 )
      goto LABEL_19;
  }
  if ( MEMORY[0x1066B8] == 5 )
  {
    if ( (MEMORY[0x10210AD0] & 1) == 1 )
    {
      MEMORY[0x1066BC] |= 2u;
    }
    else
    {
      if ( (MEMORY[0x10210AEC] & 1) == 1 )
      {
        v1 = sub_C9A0((_DWORD *)0x10210000, 1074880);
      }
      else
      {
        v1 = sub_CAA8((_DWORD *)0x10210000);
        MEMORY[0x1066BC] |= 1u;
      }
      if ( v1 )
        goto LABEL_19;
    }
  }
  v1 = sub_CC44(270598144, 1059720);
  if ( v1 )
  {
LABEL_19:
    MEMORY[0x102878] = 28928;
    MEMORY[0x10287C] = v1;
    return 28928;
  }
  return 0;
}


// ==================== brom_main_entry (sub_DC04) @0xDC04 size=24 ====================
void __noreturn brom_main_entry()
{
  int v0; // r0

  sub_334();
  sub_D5A();
  v0 = sub_E852(0);
  brom_download_entry(v0);
}


// ==================== sub_DC1C @0xDC1C size=126 ====================
int __fastcall sub_DC1C(unsigned int a1, int a2, unsigned int *a3, unsigned int a4, int a5)
{
  unsigned int v6; // r6
  unsigned int i; // r4
  int v8; // r1
  int v9; // r1

  if ( !a2 )
    return 28778;
  if ( __CFADD__(a1, a2) )
    return 28779;
  v6 = a1 + a2 - 1;
  for ( i = 0; ; ++i )
  {
    if ( i >= a4 )
      return 1;
    if ( *a3 <= a1 )
    {
      if ( a3[1] > a1 )
        v8 = 1;
      else
        v8 = 4;
    }
    else
    {
      v8 = 2;
    }
    if ( *a3 <= v6 )
    {
      if ( a3[1] > v6 )
        v9 = v8 | 8;
      else
        v9 = v8 | 0x20;
    }
    else
    {
      v9 = v8 | 0x10;
    }
    if ( v9 == 9 )
      return 3;
    if ( v9 == 34 )
      break;
    if ( (v9 & 9) != 0 )
      return 2;
    a3 += 2;
  }
  if ( a5 )
    return 4;
  else
    return 3;
}


// ==================== sub_DC9A @0xDC9A size=12 ====================
int __fastcall sub_DC9A(unsigned int a1, int a2, unsigned int *a3, unsigned int a4)
{
  return sub_DC1C(a1, a2, a3, a4, 0);
}


// ==================== sub_DCA6 @0xDCA6 size=64 ====================
int __fastcall sub_DCA6(unsigned int a1, int a2, int a3, unsigned int a4, int a5, int a6)
{
  int result; // r0
  unsigned int i; // r5

  result = 1;
  for ( i = 0; i < a4; ++i )
  {
    if ( (*(_DWORD *)a3 & a5) != 0 )
    {
      result = sub_DC1C(a1, a2, *(unsigned int **)(a3 + 4), *(_DWORD *)(a3 + 8), a6);
      if ( result != 1 )
        break;
    }
    a3 += 12;
  }
  return result;
}


// ==================== sub_DCE6 @0xDCE6 size=12 ====================
int sub_DCE6()
{
  return sub_DCE6();
}


// ==================== sub_DCF2 @0xDCF2 size=68 ====================
int __fastcall sub_DCF2(int a1, int a2, int a3, int a4)
{
  int v5; // [sp+0h] [bp-4h] BYREF

  v5 = a4;
  mem_copy_bytes(&v5, 0x100000, 4);
  if ( v5 != 1448297810 )
  {
    mem_set_bytes(0x100000, 0, 48);
    v5 = 1448297810;
    mem_copy_bytes(0x100000, &v5, 4);
  }
  mem_set_bytes(1048624, 0, 16);
  MEMORY[0x102848] = &dword_132FC;
  MEMORY[0x10284C] = 10;
  return 10;
}


// ==================== sub_DD36 @0xDD36 size=66 ====================
int __fastcall sub_DD36(unsigned int a1, int a2, int a3, int a4)
{
  int result; // r0

  result = sub_DCA6(a1, a2, MEMORY[0x102848], MEMORY[0x10284C], a3, a4);
  if ( result == 1 )
  {
    if ( MEMORY[0x102860] )
      return sub_DCA6(a1, a2, 1058904, 1u, a3, a4);
  }
  return result;
}


// ==================== sub_DD78 @0xDD78 size=4 ====================
int __fastcall sub_DD78(unsigned int a1, int a2, int a3)
{
  return sub_DD36(a1, a2, a3, 0);
}


// ==================== sub_DD7C @0xDD7C size=26 ====================
int __fastcall sub_DD7C(int result, int a2)
{
  if ( !MEMORY[0x102860] )
  {
    MEMORY[0x102850] = result;
    MEMORY[0x102854] = result + a2;
    MEMORY[0x102860] = 1;
    return 1;
  }
  return result;
}


// ==================== sub_DDBC @0xDDBC size=108 ====================
int sub_DDBC()
{
  usb_write_debug_event(HIWORD(MEMORY[0x11C10020]), MEMORY[0x11C10020], 12, (MEMORY[0x100056F0] & 0x70000u) >> 4, 69);
  MEMORY[0x10096C] = sub_1F22();
  MEMORY[0x100970] = sub_1F2E();
  usb_write_debug_event(HIWORD(MEMORY[0x10096C]), MEMORY[0x10096C], 7, MEMORY[0x100970], 83);
  return usb_write_debug_event(HIWORD(MEMORY[0x102B18]), MEMORY[0x102B18], 12, MEMORY[0x1066B8] | (MEMORY[0x1066BC] << 8), 67);
}


// ==================== sub_DE28 @0xDE28 size=8 ====================
int sub_DE28()
{
  return MEMORY[0x102818]();
}


// ==================== sub_DE30 @0xDE30 size=52 ====================
int sub_DE30()
{
  int v0; // r5
  int v1; // r4
  int v2; // r0
  unsigned int v3; // r0

  v0 = (unsigned __int8)(sub_7F88() / 0x1F4u);
  v1 = (unsigned __int8)sub_7DB8() | (v0 << 8);
  v2 = time_get_tick();
  v3 = sub_280(v2);
  return usb_write_debug_event(HIWORD(v3), (unsigned __int16)v3, 0, v1, 84);
}


// ==================== sub_DE64 @0xDE64 size=44 ====================
int sub_DE64()
{
  int result; // r0

  result = brom_get_descriptor(7);
  if ( result )
    return usb_write_debug_status(
             (unsigned __int16)*(_DWORD *)(result + 8),
             *(unsigned __int8 *)(result + 82) | (*(unsigned __int8 *)(result + 81) << 8),
             0,
             71);
  return result;
}


// ==================== sub_DE90 @0xDE90 size=40 ====================
int __fastcall sub_DE90(int a1)
{
  int v1; // r0

  if ( a1 == 1 )
  {
    v1 = brom_get_descriptor(7);
    if ( v1 && (*(_DWORD *)(v1 + 8) & 0x1000) != 0 )
      return *(unsigned __int8 *)(v1 + 85);
  }
  else if ( !a1 )
  {
    return MEMORY[0x102881];
  }
  return 0;
}


// ==================== sub_DEB8 @0xDEB8 size=178 ====================
int sub_DEB8()
{
  int v0; // r0
  int v1; // r1

  if ( sub_4330() )
    MEMORY[0x1008E8] |= 0x8000000u;
  if ( sub_3DA8() )
    MEMORY[0x1008E8] |= 0x10000000u;
  if ( !sub_342() )
    MEMORY[0x1008E8] |= 0x20000000u;
  v0 = sub_40C();
  if ( !v0 )
  {
    v0 = MEMORY[0x1008E8] | 0x40000000;
    MEMORY[0x1008E8] |= 0x40000000u;
  }
  if ( sub_10F80(v0, v1) )
    MEMORY[0x1008E8] |= 0x80000000;
  if ( MEMORY[0x1028A8] )
    MEMORY[0x1008E8] |= 0x80u;
  if ( !sub_82FC() )
    MEMORY[0x1008E8] |= 0x200u;
  if ( sub_DE90(1) == 100 )
    MEMORY[0x1008E8] |= 0x4000000u;
  return usb_write_debug_event(HIWORD(MEMORY[0x1008E8]), MEMORY[0x1008E8], 25, MEMORY[0x1028A8], 66);
}


// ==================== sub_DF6A @0xDF6A size=20 ====================
int sub_DF6A()
{
  sub_DEB8();
  sub_DE64();
  sub_DDBC();
  return sub_DE30();
}


// ==================== sub_DF7E @0xDF7E size=54 ====================
unsigned int sub_DF7E()
{
  int v0; // r0
  unsigned int v1; // r4

  trace_begin(0x32u, 0);
  v0 = time_get_tick();
  v1 = sub_280(v0);
  sub_368();
  sub_78A();
  trace_begin(0x32u, 1);
  return trace_end(0x32u, v1, 0, 0);
}


// ==================== brom_halt_forever (sub_DFB4) @0xDFB4 size=156 ====================
void __fastcall __noreturn brom_halt_forever(int a1)
{
  int v2; // r0
  _DWORD *v3; // r0
  unsigned int v4; // r0

  sub_DF7E();
  sub_DF6A();
  if ( a1 )
  {
    v2 = uart_puts("System halt!\n\r\n\r");
    sub_E662(v2);
  }
  trace_begin(0, 0);
  v3 = sub_E26();
  v4 = sub_10FB2(v3);
  if ( v4 == 1 )
  {
    if ( MEMORY[0x1001A08C] != 1112691540 || (v4 = MEMORY[0x1001A090], MEMORY[0x1001A090] != 1398034256) )
    {
      MEMORY[0x1001A108] |= 0x18u;
      MEMORY[0x1001A100] = 0;
      v4 = MEMORY[0x1001A090];
      if ( !MEMORY[0x1001A090] )
      {
        MEMORY[0x1001A08C] = MEMORY[0x1000700C];
        v4 = 1381171200;
      }
      if ( HIWORD(v4) == 21075 )
      {
        MEMORY[0x1001A090] = (unsigned __int16)(v4 + 1) | 0x52530000;
        time_delay_ms(0x3E8u);
        v4 = sub_BFE4(0);
      }
    }
  }
  if ( brom_get_boot_mode(v4) != 1 )
  {
    while ( 1 )
      ;
  }
  while ( 1 )
    usb_poll_events_alias();
}


// ==================== sub_E050 @0xE050 size=76 ====================
int sub_E050()
{
  int v0; // r4
  int v1; // r5

  v0 = 1;
  v1 = brom_get_descriptor(7);
  if ( brom_get_boot_mode(v1) )
    return 0;
  if ( (MEMORY[0x1008E8] & 0x20) != 0 )
    return 0;
  if ( (MEMORY[0x103EC0] != 1414676821 || MEMORY[0x103EC4] != 1313169201)
    && !MEMORY[0x102878]
    && v1
    && *(_DWORD *)(v1 + 8) << 31 )
  {
    return 0;
  }
  return v0;
}


// ==================== brom_enter_fallback (sub_E09C) @0xE09C size=72 ====================
int __fastcall brom_enter_fallback(int a1)
{
  int v2; // r0
  int result; // r0
  int v4; // r0

  v2 = usb_report_error(MEMORY[0x102878], MEMORY[0x10287C]);
  if ( (unsigned int)sub_10E16(v2) >= 0xFF || (unsigned int)sub_10CB2(a1) >= 0xFF )
    brom_halt_forever(1);
  sub_DF6A();
  result = sub_E050();
  if ( result )
  {
    v4 = uart_puts("Jump to BL\n\r\n\r");
    return sub_E662(v4);
  }
  return result;
}


// ==================== sub_E0E4 @0xE0E4 size=20 ====================
int sub_E0E4()
{
  int result; // r0

  result = sub_10F9E();
  if ( result )
    return sub_10DB0();
  return result;
}


// ==================== nullsub_8 @0xE0F8 size=2 ====================
void nullsub_8()
{
  ;
}


// ==================== brom_self_test (sub_E0FA) @0xE0FA size=330 ====================
unsigned int __fastcall brom_self_test(int a1, int a2, int a3, int a4)
{
  int v4; // r0
  int v5; // r0
  int v6; // r0
  int v7; // r0
  unsigned int v8; // r4
  unsigned int v9; // r0
  int v10; // r1
  int v11; // r2
  int v12; // r3
  int v13; // r0
  int v14; // r0
  unsigned int v15; // r5
  int v16; // r0
  unsigned int v17; // r6
  unsigned int v18; // r0
  int v20; // [sp+0h] [bp-4h] BYREF

  v20 = a4;
  trace_begin(0x33u, 0);
  nullsub_8();
  uart_puts("\n\r");
  v4 = usb_status_reset(0);
  usb_config_apply(v4);
  v5 = brom_read_boot_word(&v20);
  MEMORY[0x102874] = v5;
  if ( v5 == 255 || v5 == 4 )
  {
    usb_report_error(4117, (unsigned __int16)v20);
    if ( MEMORY[0x102874] == 4 )
      brom_halt_forever(1);
    if ( !sub_8462() && MEMORY[0x102874] == 255 )
      brom_halt_forever(1);
  }
  v6 = sub_77C();
  sub_110AA(v6);
  sub_E0E4();
  v7 = time_get_tick();
  v8 = sub_280(v7);
  v9 = sub_6342();
  v13 = sub_DCF2(v9, v10, v11, v12);
  sub_FCAC(v13);
  v14 = time_get_tick();
  v15 = sub_280(v14);
  sub_346();
  v16 = time_get_tick();
  v17 = sub_280(v16);
  v18 = sub_DB02();
  if ( v18 >= 0xFF )
  {
    usb_report_error((unsigned __int16)v18, MEMORY[0x10287C]);
    if ( !efuse_get_misc_bit?() )
      brom_halt_forever(1);
  }
  trace_begin(0x33u, 1);
  return trace_end(0x33u, v8, v15, v17);
}


// ==================== brom_download_entry (sub_E244) @0xE244 size=326 ====================
void __fastcall __noreturn brom_download_entry(int a1, int a2, int a3, int a4)
{
  int v4; // r0
  int v5; // r1
  int v6; // r2
  int v7; // r3
  int v8; // r0
  int v9; // r0
  int v10; // r0
  int v11; // r1
  int v12; // r2
  int v13; // r3
  int v14; // r0
  int v15; // [sp+0h] [bp-4h] BYREF

  v15 = a4;
  if ( !efuse_get_flag_11(a1) )
    periph_set_bit30_100070A4();
  v4 = efuse_get_boot_strap_bit();
  brom_self_test(v4, v5, v6, v7);
  v8 = trace_begin(9u, 0);
  MEMORY[0x102878] = usb_monitor_task(v8);
  v9 = trace_begin(9u, 1);
  if ( !usb_detect_mode(v9) )
  {
    if ( !(MEMORY[0x102898] << 31) )
    {
      if ( usb_wait_download_magic() )
      {
        MEMORY[0x1008E8] |= 0x20u;
LABEL_14:
        v14 = efuse_get_boot_strap_bit();
        brom_command_loop(v14);
        while ( 1 )
          ;
      }
      MEMORY[0x1008E8] |= 0x40u;
    }
    if ( (MEMORY[0x102898] & 2) == 0 )
    {
      sub_40B0();
      if ( v10 == 1 )
      {
        if ( usb_wait_download_magic_usb(1, v11, v12, v13) )
        {
          MEMORY[0x1008E8] |= 2u;
          goto LABEL_14;
        }
        MEMORY[0x1008E8] |= 0x10u;
        usb_report_error(4135, 1);
      }
      else if ( v10 == 2 )
      {
        MEMORY[0x1008E8] |= 0x10u;
        usb_report_error(4135, 2);
      }
    }
  }
  efuse_get_boot_strap_bit();
  brom_enter_fallback((int)&v15);
  sub_DE28();
  while ( 1 )
    ;
}


// ==================== sub_E38A @0xE38A size=138 ====================
int __fastcall sub_E38A(_DWORD *a1, _DWORD *a2)
{
  int v4; // r0

  MEMORY[0x1008FC] = MEMORY[0x102B00];
  MEMORY[0x100900] = MEMORY[0x102B04];
  MEMORY[0x100904] = MEMORY[0x1027C8];
  MEMORY[0x100908] = MEMORY[0x1027CC];
  MEMORY[0x10090C] = MEMORY[0x102834];
  MEMORY[0x100910] = MEMORY[0x102838];
  mem_copy_bytes(1050860, 1059704, 16);
  mem_copy_bytes(1050932, 1059720, 32);
  MEMORY[0x100964] = MEMORY[0x1066B8];
  MEMORY[0x100968] = MEMORY[0x1066BC];
  v4 = mem_copy_bytes(1050964, 1074880, 16);
  MEMORY[0x100974] = sub_10C76(v4);
  sub_110B8();
  *a1 = 1048640;
  *a2 = 2364;
  return 2364;
}


// ==================== sub_E414 @0xE414 size=94 ====================
void __fastcall __noreturn sub_E414(int a1, int a2, int a3, int a4)
{
  int v6; // [sp+0h] [bp-8h] BYREF
  int v7; // [sp+4h] [bp-4h] BYREF

  v6 = a3;
  v7 = a4;
  sub_63A4(a2);
  sub_DF7E();
  sub_E38A(&v7, &v6);
  MEMORY[0x102894]();
  trace_begin(0, 1);
  sub_E26();
  sub_38B4();
  if ( sub_DE90(a2) == 100 )
  {
    MEMORY[0x1021403C] = v7;
    MEMORY[0x10214040] = v6;
    sub_114(a1);
  }
  sub_C4();
  while ( 1 )
    ;
}


// ==================== sub_E4AC @0xE4AC size=44 ====================
int __fastcall sub_E4AC(int a1, int a2)
{
  int v3; // r4
  int v4; // r5
  int result; // r0

  v3 = a2;
  v4 = MEMORY[0x102868];
  result = MEMORY[0x102868] + a2;
  if ( (unsigned int)(MEMORY[0x102868] + a2) > 0x400 )
    v3 = 1024 - MEMORY[0x102868];
  if ( v3 )
  {
    mem_copy_bytes(MEMORY[0x102868] + 1074896, a1, v3);
    MEMORY[0x102868] = v4 + v3;
    return v4 + v3;
  }
  return result;
}


// ==================== sub_E4D8 @0xE4D8 size=20 ====================
int sub_E4D8()
{
  int i; // r0

  for ( i = 1059680; *(_BYTE *)i; ++i )
    ;
  return sub_E4AC(1059680, i - 1059680);
}


// ==================== sub_E4EC @0xE4EC size=14 ====================
unsigned int __fastcall sub_E4EC(unsigned int result)
{
  if ( result < 0xA )
    LOBYTE(result) = result + 48;
  else
    LOBYTE(result) = result + 55;
  return (unsigned __int8)result;
}


// ==================== sub_E4FA @0xE4FA size=50 ====================
unsigned int __fastcall sub_E4FA(unsigned int result, int a2, unsigned int a3)
{
  unsigned int v3; // r6
  unsigned int v5; // r4
  int v6; // r5

  v3 = result;
  if ( a3 > 8 )
    a3 = 8;
  v5 = a3;
  v6 = 0;
  while ( v5 )
  {
    result = sub_E4EC((v3 >> (4 * (v5 - 1))) & 0xF);
    *(_BYTE *)(a2 + v6) = result;
    --v5;
    ++v6;
  }
  return result;
}


// ==================== sub_E52C @0xE52C size=152 ====================
int __fastcall sub_E52C(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  int result; // r0

  if ( MEMORY[0x102870] << 31 )
  {
    sub_E4FA(MEMORY[0x10286C], 1059680, 2u);
    ++MEMORY[0x10286C];
  }
  else
  {
    MEMORY[0x102B60] = MEMORY[0x102864];
    MEMORY[0x102B61] = sub_E4EC(a3);
  }
  MEMORY[0x102B62] = 58;
  MEMORY[0x102B63] = 32;
  sub_E4FA(a1, 1059684, 4u);
  MEMORY[0x102B68] = 32;
  sub_E4FA(a2, 1059689, 4u);
  result = MEMORY[0x102870] << 30;
  if ( (MEMORY[0x102870] & 2) != 0 )
  {
    MEMORY[0x102B6D] = 32;
    MEMORY[0x102B6E] = 91;
    sub_E4FA(a4, 1059695, 4u);
    MEMORY[0x102B73] = 93;
    MEMORY[0x102B74] = 10;
    MEMORY[0x102B75] = 13;
    MEMORY[0x102B76] = 0;
    return 93;
  }
  else
  {
    MEMORY[0x102B6D] = 10;
    MEMORY[0x102B6E] = 13;
    MEMORY[0x102B6F] = 0;
  }
  return result;
}


// ==================== usb_report_error (sub_E5C4) @0xE5C4 size=22 ====================
int __fastcall usb_report_error(unsigned int a1, unsigned int a2)
{
  MEMORY[0x102870] = 1;
  sub_E52C(a1, a2, 0, 0);
  return sub_E4D8();
}


// ==================== sub_E5DA @0xE5DA size=100 ====================
void __fastcall sub_E5DA(unsigned int a1)
{
  int v1; // r0
  int v2; // r0

  time_get_ms_count(a1);
  time_get_tick();
  time_get_ms_count(0x64u);
  v1 = time_get_tick();
  while ( 1 )
  {
    v2 = sub_10E54(v1);
    if ( v2 )
      break;
    v2 = time_wait_ticks();
    if ( v2 )
      break;
    v1 = time_wait_ticks();
    if ( v1 )
    {
      sub_10E48();
      usb_report_error(0x101Bu, MEMORY[0x11C10000]);
      v1 = time_get_tick();
    }
  }
  sub_10E54(v2);
  JUMPOUT(0xE5B6);
}


// ==================== brom_read_boot_word (sub_E63E) @0xE63E size=34 ====================
int __fastcall brom_read_boot_word(int a1)
{
  int v2; // r0

  sub_E5DA(0x3E8u);
  if ( !v2 )
    usb_report_error(0x1014u, 0);
  return board_get_boot_source(a1);
}


// ==================== sub_E660 @0xE660 size=2 ====================
// attributes: thunk
void __noreturn sub_E660()
{
  while ( 1 )
    ;
}


// ==================== sub_E662 @0xE662 size=24 ====================
int sub_E662()
{
  int result; // r0

  if ( MEMORY[0x102868] )
  {
    sub_EA46(1074896, MEMORY[0x102868], 0);
    MEMORY[0x102868] = 0;
    return 0;
  }
  return result;
}


// ==================== uart_puts (sub_E67A) @0xE67A size=16 ====================
int __fastcall uart_puts(int a1)
{
  _BYTE *i; // r1

  for ( i = (_BYTE *)a1; *i; ++i )
    ;
  return sub_E4AC(a1, (int)&i[-a1]);
}


// ==================== sub_E68A @0xE68A size=28 ====================
int __fastcall sub_E68A(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4)
{
  int v4; // r4

  if ( a4 )
    v4 = 2;
  else
    v4 = 0;
  MEMORY[0x102870] = v4;
  MEMORY[0x102864] = 70;
  sub_E52C(a1, a2, a3, a4);
  return sub_E4D8();
}


// ==================== usb_write_debug_event (sub_E6A6) @0xE6A6 size=22 ====================
int __fastcall usb_write_debug_event(unsigned int a1, unsigned int a2, unsigned int a3, unsigned int a4, char a5)
{
  MEMORY[0x102870] = 2;
  MEMORY[0x102864] = a5;
  sub_E52C(a1, a2, a3, a4);
  return sub_E4D8();
}


// ==================== usb_write_debug_status (sub_E6BC) @0xE6BC size=22 ====================
int __fastcall usb_write_debug_status(unsigned int a1, unsigned int a2, unsigned int a3, char a4)
{
  MEMORY[0x102870] = 0;
  MEMORY[0x102864] = a4;
  sub_E52C(a1, a2, a3, 0);
  return sub_E4D8();
}


// ==================== usb_status_reset (sub_E6E4) @0xE6E4 size=28 ====================
__int64 __fastcall usb_status_reset(__int64 result)
{
  HIDWORD(result) = 0;
  if ( (_DWORD)result )
  {
    if ( (_DWORD)result == 1 )
    {
      MEMORY[0x102878] = 0;
    }
    else if ( (_DWORD)result == 2 )
    {
      MEMORY[0x10287C] = 0;
    }
  }
  else
  {
    MEMORY[0x102878] = 0;
    MEMORY[0x10287C] = 0;
  }
  return result;
}


// ==================== sub_E704 @0xE704 size=12 ====================
int sub_E704()
{
  while ( !(MEMORY[0x11002014] << 31) )
    ;
  return MEMORY[0x11002000];
}


// ==================== uart_putc (sub_E710) @0xE710 size=12 ====================
char __fastcall uart_putc(char result)
{
  while ( (MEMORY[0x11002014] & 0x20) == 0 )
    ;
  MEMORY[0x11002000] = result;
  return result;
}


// ==================== usb_wait_download_magic (sub_E71C) @0xE71C size=132 ====================
int usb_wait_download_magic()
{
  int v0; // r4
  int v1; // r7

  v0 = 0;
  v1 = 0;
  trace_begin(0x13u, 0);
  time_ms_to_ticks(0x96u);
  time_get_tick();
  MEMORY[0x11002008] = -109;
  while ( !time_wait_ticks() )
  {
    if ( MEMORY[0x11002014] << 31 )
    {
      if ( *((unsigned __int8 *)&dword_133DC + v0) == MEMORY[0x11002000] )
      {
        uart_putc(~MEMORY[0x11002000]);
        time_get_tick();
        v0 = (unsigned __int8)(v0 + 1);
        if ( v0 == 4 )
        {
          v1 = 1;
          break;
        }
      }
      else
      {
        uart_putc(MEMORY[0x11002000] + 1);
        v0 = 0;
      }
    }
  }
  trace_begin(0x13u, 1);
  trace_end(0x13u, v1, 150, 0);
  return v1;
}


// ==================== sub_E7A0 @0xE7A0 size=26 ====================
int __fastcall sub_E7A0(int a1, unsigned int a2)
{
  unsigned int i; // r2
  char v4; // r0
  int v5; // r2
  int v6; // r3

  for ( i = 0; i < a2; i = v5 + 1 )
  {
    v4 = sub_E704();
    *(_BYTE *)(v6 + v5) = v4;
  }
  return 0;
}


// ==================== sub_E7BA @0xE7BA size=26 ====================
int __fastcall sub_E7BA(int a1, unsigned int a2)
{
  unsigned int i; // r3
  int v5; // r3

  for ( i = 0; i < a2; i = v5 + 1 )
    uart_putc(*(_BYTE *)(a1 + i));
  return 0;
}


// ==================== sub_E7D4 @0xE7D4 size=40 ====================
int sub_E7D4()
{
  int result; // r0

  time_ms_to_ticks(2u);
  time_get_tick();
  do
  {
    result = time_wait_ticks();
    if ( result )
      break;
    result = MEMORY[0x11002014] << 25;
  }
  while ( (MEMORY[0x11002014] & 0x40) == 0 );
  return result;
}


// ==================== sub_E7FC @0xE7FC size=70 ====================
int __fastcall sub_E7FC(int a1, unsigned int a2)
{
  unsigned int v2; // r1
  unsigned int v3; // r0
  unsigned int v4; // r1

  MEMORY[0x11002024] = 3;
  v2 = (a1 + (a2 >> 1)) / a2;
  v3 = (v2 + 255) >> 8;
  v4 = v2 / v3 - 1;
  MEMORY[0x11002028] = v4;
  MEMORY[0x1100202C] = v4 >> 1;
  MEMORY[0x11002004] = BYTE1(v3);
  MEMORY[0x11002000] = v3;
  MEMORY[0x1100200C] = 3;
  MEMORY[0x11002010] = 3;
  MEMORY[0x11002008] = -105;
  return 151;
}


// ==================== brom_get_boot_mode (sub_E84C) @0xE84C size=6 ====================
int brom_get_boot_mode()
{
  return MEMORY[0x102884];
}


// ==================== sub_E852 @0xE852 size=62 ====================
int __fastcall sub_E852(int result)
{
  int v1; // r0

  if ( result )
  {
    if ( result == 1 )
    {
      MEMORY[0x102888] = sub_419E;
      MEMORY[0x10288C] = sub_4244;
      MEMORY[0x102890] = usb_tx_flush;
      MEMORY[0x102894] = (int (*)(void))usb_tx_flush;
      MEMORY[0x102884] = 1;
    }
  }
  else
  {
    MEMORY[0x102888] = sub_E7A0;
    MEMORY[0x10288C] = sub_E7BA;
    MEMORY[0x102890] = 0;
    MEMORY[0x102894] = sub_E7D4;
    MEMORY[0x102884] = 0;
    v1 = sub_70C();
    return sub_E7FC(v1, 0x1C200u);
  }
  return result;
}


// ==================== usb_read_byte (sub_E890) @0xE890 size=22 ====================
int __fastcall usb_read_byte(int a1, int a2, int a3, int a4)
{
  int v5; // [sp+0h] [bp-4h] BYREF

  v5 = a4;
  MEMORY[0x102888](&v5, 1, -1);
  return (unsigned __int8)v5;
}


// ==================== usb_write_byte (sub_E8A6) @0xE8A6 size=32 ====================
int __fastcall usb_write_byte(int a1, int a2)
{
  int (__fastcall *v3)(int); // r4
  int result; // r0
  _DWORD v5[2]; // [sp+0h] [bp-8h] BYREF

  v5[0] = a1;
  v5[1] = a2;
  v3 = (int (__fastcall *)(int))MEMORY[0x102890];
  result = ((int (__fastcall *)(_DWORD *, int, int))MEMORY[0x10288C])(v5, 1, -1);
  if ( a2 )
  {
    if ( v3 )
      return v3(result);
  }
  return result;
}


// ==================== sub_E8C6 @0xE8C6 size=56 ====================
int __fastcall sub_E8C6(int a1, int a2, int a3, int a4)
{
  void (__fastcall *v4)(int *, int, int); // r6
  int v5; // r5
  unsigned int v6; // r4
  int v8; // [sp+0h] [bp-4h] BYREF

  v8 = a4;
  v4 = (void (__fastcall *)(int *, int, int))MEMORY[0x102888];
  LOWORD(v5) = 0;
  LOBYTE(v6) = 0;
  do
  {
    v4(&v8, 1, -1);
    v5 = (unsigned __int16)(((unsigned __int8)v8 << (8 - 8 * v6)) | v5);
    v6 = (unsigned __int8)(v6 + 1);
  }
  while ( v6 < 2 );
  return v5;
}


// ==================== usb_write_status16 (sub_E8FE) @0xE8FE size=68 ====================
int __fastcall usb_write_status16(unsigned int a1, int a2, int a3, unsigned int a4)
{
  int (__fastcall *v6)(unsigned int *, int, int); // r7
  int (__fastcall *v7)(int); // r6
  unsigned int v8; // r4
  int result; // r0
  unsigned int v10; // [sp+0h] [bp-4h] BYREF

  v10 = a4;
  v6 = (int (__fastcall *)(unsigned int *, int, int))MEMORY[0x10288C];
  v7 = (int (__fastcall *)(int))MEMORY[0x102890];
  LOBYTE(v8) = 0;
  do
  {
    v10 = a1 >> (8 - 8 * v8);
    result = v6(&v10, 1, -1);
    v8 = (unsigned __int8)(v8 + 1);
  }
  while ( v8 < 2 );
  if ( a2 )
  {
    if ( v7 )
      return v7(result);
  }
  return result;
}


// ==================== sub_E942 @0xE942 size=52 ====================
void __fastcall sub_E942(int a1, int a2, int a3, int a4)
{
  void (__fastcall *v4)(int *, int, int); // r6
  int v5; // r5
  unsigned int v6; // r4
  int v7; // [sp+0h] [bp-4h] BYREF

  v7 = a4;
  v4 = (void (__fastcall *)(int *, int, int))MEMORY[0x102888];
  v5 = 0;
  LOBYTE(v6) = 0;
  do
  {
    v4(&v7, 1, -1);
    v5 |= (unsigned __int8)v7 << (24 - 8 * v6);
    v6 = (unsigned __int8)(v6 + 1);
  }
  while ( v6 < 4 );
  JUMPOUT(0xE8FA);
}


// ==================== usb_write_length (sub_E976) @0xE976 size=66 ====================
void __fastcall usb_write_length(unsigned int a1, int a2, int a3, unsigned int a4)
{
  int (__fastcall *v6)(unsigned int *, int, int); // r7
  void (__fastcall *v7)(int); // r6
  unsigned int v8; // r4
  int v9; // r0
  unsigned int v10; // [sp+0h] [bp-4h] BYREF

  v10 = a4;
  v6 = (int (__fastcall *)(unsigned int *, int, int))MEMORY[0x10288C];
  v7 = (void (__fastcall *)(int))MEMORY[0x102890];
  LOBYTE(v8) = 0;
  do
  {
    v10 = a1 >> (24 - 8 * v8);
    v9 = v6(&v10, 1, -1);
    v8 = (unsigned __int8)(v8 + 1);
  }
  while ( v8 < 4 );
  if ( a2 )
  {
    if ( v7 )
      v7(v9);
  }
  JUMPOUT(0xE93E);
}


// ==================== usb_read_buffer (sub_E9B8) @0xE9B8 size=142 ====================
int __fastcall usb_read_buffer(int a1, unsigned int a2, int a3)
{
  unsigned int v4; // r8
  unsigned int v6; // r3
  int v7; // r0
  unsigned int v8; // r5
  unsigned int v9; // r9
  unsigned int i; // r4
  int v11; // r6
  unsigned int j; // r5
  int v13; // r0
  int result; // r0
  unsigned int v15; // r2
  unsigned int v16; // r0
  unsigned int k; // r1

  v4 = a2;
  v6 = (unsigned int)MEMORY[0x102888];
  v7 = a3 << 30;
  if ( (a3 & 2) != 0 )
  {
    v8 = a2 >> 2;
    v9 = a2 & 3;
    for ( i = 0; i < v8; ++i )
    {
      sub_E942(v7, a2, a3, v6);
      *(_DWORD *)(a1 + 4 * i) = v7;
    }
    if ( v9 )
    {
      v11 = 0;
      for ( j = 0; j < v9; ++j )
      {
        v13 = usb_read_byte(v7, a2, a3, v6);
        a2 = 8 * j;
        v7 = v13 << (8 * j);
        v11 |= v7;
      }
      *(_DWORD *)(a1 + 4 * i) = v11;
    }
  }
  else
  {
    MEMORY[0x102888](a1, a2, -1);
  }
  result = a3 << 31;
  if ( a3 << 31 )
  {
    v15 = v4 >> 1;
    v16 = 0;
    for ( k = 0; k < v15; ++k )
    {
      v6 = *(unsigned __int16 *)(a1 + 2 * k);
      v16 ^= v6;
    }
    if ( (v4 & 1) != 0 )
      v16 ^= *(unsigned __int8 *)(a1 + 2 * v15);
    return usb_write_status16(v16, 1, v15, v6);
  }
  return result;
}


// ==================== sub_EA46 @0xEA46 size=28 ====================
int __fastcall sub_EA46(int a1, int a2)
{
  int (__fastcall *v2)(int); // r4
  int result; // r0

  v2 = (int (__fastcall *)(int))MEMORY[0x102890];
  result = ((int (__fastcall *)(_DWORD, _DWORD, _DWORD, _DWORD))MEMORY[0x10288C])(a1, a2, -1, MEMORY[0x10288C]);
  if ( v2 )
    return v2(result);
  return result;
}


// ==================== usb_detect_mode (sub_EA80) @0xEA80 size=136 ====================
int usb_detect_mode()
{
  unsigned int v0; // r4
  unsigned int v1; // r5
  int v2; // r6
  int v3; // r0
  int v4; // r0
  int v5; // r0

  v0 = 0;
  v1 = 0;
  v2 = 0;
  if ( efuse_get_usb_boot_bit() )
  {
    v0 = 0x8000;
    v2 = 1;
  }
  v3 = brom_get_descriptor(8);
  if ( v3 && *(_DWORD *)(v3 + 44) == -915021773 )
  {
    v0 |= 0x4000u;
    v2 = 1;
  }
  v4 = brom_get_descriptor(7);
  if ( v4 && *(_BYTE *)(v4 + 83) == 82 )
    v0 |= 1u;
  if ( v4 && *(_BYTE *)(v4 + 84) == 85 )
    v0 |= 2u;
  if ( sub_EB10() == 1 )
    v1 = 2;
  v5 = v0 | v1 | MEMORY[0x102898];
  MEMORY[0x102898] |= (unsigned __int16)v0 | (unsigned __int16)v1;
  if ( (v5 & 0xFFFF3FFF) == 3 )
    MEMORY[0x102898] = v5 & 0xFFFE;
  if ( v1 )
    usb_report_error(6u, v1);
  if ( v0 )
    usb_report_error(7u, v0);
  return v2;
}


// ==================== sub_EB10 @0xEB10 size=16 ====================
BOOL sub_EB10()
{
  return (MEMORY[0x100056F0] & 0x10000) != 0;
}


// ==================== sub_EB24 @0xEB24 size=60 ====================
int sub_EB24()
{
  int v0; // r0
  int v2; // r0

  v0 = brom_get_descriptor(8);
  if ( MEMORY[0x1027C4] && (*(_DWORD *)(MEMORY[0x1027C4] + 40) & 0x100) != 0 )
    return 0;
  if ( v0 )
  {
    v2 = *(_DWORD *)(v0 + 8);
    if ( v2 < 0 )
      return ((8 * v2) >> 31) + 1;
  }
  return sub_8458() || sub_8430();
}


// ==================== sub_EB60 @0xEB60 size=60 ====================
int sub_EB60()
{
  int v0; // r0
  int v2; // r0

  v0 = brom_get_descriptor(8);
  if ( MEMORY[0x1027C4] && (*(_DWORD *)(MEMORY[0x1027C4] + 40) & 0x200) != 0 )
    return 0;
  if ( v0 )
  {
    v2 = *(_DWORD *)(v0 + 8);
    if ( v2 < 0 )
      return ((4 * v2) >> 31) + 1;
  }
  return sub_8458() || sub_8430();
}


// ==================== sub_EB9C @0xEB9C size=60 ====================
int sub_EB9C()
{
  int v0; // r0
  int v2; // r0

  v0 = brom_get_descriptor(8);
  if ( MEMORY[0x1027C4] && (*(_DWORD *)(MEMORY[0x1027C4] + 40) & 0x400) != 0 )
    return 0;
  if ( v0 )
  {
    v2 = *(_DWORD *)(v0 + 8);
    if ( v2 < 0 )
      return ((2 * v2) >> 31) + 1;
  }
  return sub_8458() || sub_8430();
}


// ==================== sub_EBD8 @0xEBD8 size=42 ====================
unsigned int __fastcall sub_EBD8(unsigned int a1, int a2)
{
  unsigned int result; // r0

  if ( MEMORY[0x102BA8] >= 0xAu )
    return 7440;
  result = sub_DC9A(a1, a2, (unsigned int *)0x102C4C, MEMORY[0x102BA8]);
  if ( result < 0xFF )
  {
    if ( result == 1 )
      return 0;
    else
      return 7438;
  }
  return result;
}


// ==================== sub_EC02 @0xEC02 size=176 ====================
int __fastcall sub_EC02(unsigned int a1, int a2, int a3)
{
  unsigned int v6; // r0
  unsigned int v7; // r4
  unsigned int v8; // r0
  unsigned int v9; // r0

  v6 = sub_DD78(a1, a2, 415);
  v7 = v6;
  if ( v6 < 0xFF )
  {
    if ( v6 == 1 )
    {
      v7 = sub_FE8E(a1, a2);
      if ( v7 < 0xFF )
      {
        if ( a3 )
        {
          if ( sub_EB24() )
          {
            v8 = sub_DD36(a1, a2, 512, 1);
            v7 = v8;
            if ( v8 < 0xFF )
            {
              if ( v8 == 3 )
                return 0;
              else
                return 7432;
            }
          }
        }
        else
        {
          v7 = sub_EBD8(a1, a2);
          if ( v7 < 0xFF )
          {
            if ( sub_EB60() )
            {
              v9 = sub_DD36(a1, a2, 1024, 1);
              v7 = v9;
              if ( v9 < 0xFF )
              {
                if ( v9 == 3 )
                  return 0;
                else
                  return 7426;
              }
            }
          }
          else
          {
            return 7427;
          }
        }
      }
      else if ( a3 )
      {
        return 7434;
      }
      else
      {
        return 7428;
      }
    }
    else if ( a3 )
    {
      return 7432;
    }
    else
    {
      return 7426;
    }
  }
  return v7;
}


// ==================== sub_ECB2 @0xECB2 size=256 ====================
void __fastcall sub_ECB2(int a1, int a2, int a3, int a4)
{
  int v6; // r9
  unsigned int v7; // r0
  unsigned int v8; // r8
  int v9; // r2
  unsigned int v10; // r3
  int v11; // r0
  int v12; // r1
  int v13; // r2
  int v14; // r3
  unsigned int v15; // r0
  unsigned int v16; // r5
  int v17; // r2
  unsigned int v18; // r3
  int v19; // r2
  unsigned int v20; // r3
  unsigned int v21; // r4
  int v22; // r7
  unsigned int v23; // r0
  unsigned int *v24; // r0
  int v25; // r1
  unsigned int i; // r6
  unsigned int j; // r6
  unsigned int v28; // r0
  __int16 v29; // r7
  unsigned int v30; // r0
  unsigned int v31; // r7

  v6 = 0;
  MEMORY[0x10289A] = 1;
  sub_E942(1, 1058970, a3, a4);
  v8 = v7;
  usb_write_length(v7, 1, v9, v10);
  sub_E942(v11, v12, v13, v14);
  v16 = v15;
  usb_write_length(v15, 1, v17, v18);
  if ( !v16 )
  {
    LOWORD(v21) = 7429;
    goto LABEL_32;
  }
  LOWORD(v21) = 7448;
  if ( a1 )
  {
    if ( v8 << 30 )
    {
      LOWORD(v21) = 7425;
      goto LABEL_32;
    }
    if ( v16 >= 0x40000000 )
      goto LABEL_32;
    v22 = 4 * v16;
  }
  else
  {
    if ( v8 << 31 )
    {
      LOWORD(v21) = 7424;
      goto LABEL_32;
    }
    if ( v16 >= 0x80000000 )
      goto LABEL_32;
    v22 = 2 * v16;
  }
  v21 = sub_EC02(v8, v22, 0);
  if ( v21 < 0xFF )
  {
    v23 = sub_DD78(v8, v22, 96);
    LOWORD(v21) = v23;
    if ( v23 < 0xFF )
    {
      if ( v23 != 1 )
        v6 = 1;
      v24 = (unsigned int *)usb_write_status16((unsigned __int16)v23, 1, v19, v20);
      if ( a1 )
      {
        for ( i = 0; i < v16; ++i )
        {
          sub_E942((int)v24, v25, v19, v20);
          v31 = v30;
          if ( a2 )
            usb_write_length(v30, 1, v19, v20);
          v24 = (unsigned int *)(v8 + 4 * i);
          if ( v6 )
            v31 &= 0xFF00FFu;
          *v24 = v31;
        }
      }
      else
      {
        for ( j = 0; j < v16; ++j )
        {
          v28 = sub_E8C6((int)v24, v25, v19, v20);
          v29 = v28;
          if ( a2 )
            usb_write_status16(v28, 1, v19, v20);
          v24 = (unsigned int *)(v8 + 2 * j);
          if ( v6 )
            v29 = (unsigned __int8)v29;
          *(_WORD *)v24 = v29;
        }
      }
    }
  }
LABEL_32:
  usb_write_status16((unsigned __int16)v21, 1, v19, v20);
  JUMPOUT(0xECAE);
}


// ==================== sub_EDB2 @0xEDB2 size=186 ====================
int __fastcall sub_EDB2(int a1, int a2, int a3, int a4)
{
  unsigned int v6; // r0
  unsigned int v7; // r7
  int v8; // r2
  unsigned int v9; // r3
  int v10; // r0
  int v11; // r1
  int v12; // r2
  int v13; // r3
  unsigned int v14; // r0
  unsigned int v15; // r5
  int v16; // r2
  unsigned int v17; // r3
  int v18; // r2
  unsigned int v19; // r3
  int v20; // r4
  int v21; // r1
  unsigned int v22; // r0
  unsigned int i; // r6
  unsigned int j; // r6

  sub_E942(a1, a2, a3, a4);
  v7 = v6;
  usb_write_length(v6, 1, v8, v9);
  sub_E942(v10, v11, v12, v13);
  v15 = v14;
  usb_write_length(v14, 1, v16, v17);
  if ( !v15 )
  {
    v20 = 7433;
    goto LABEL_24;
  }
  v20 = 7449;
  if ( a1 )
  {
    if ( v7 << 30 )
    {
      v20 = 7431;
      goto LABEL_24;
    }
    if ( v15 < 0x40000000 )
    {
      v21 = 4 * v15;
LABEL_12:
      v22 = sub_EC02(v7, v21, 1);
      v20 = v22;
      if ( v22 < 0xFF )
      {
        if ( !a2 )
          usb_write_status16((unsigned __int16)v22, 1, v18, v19);
        if ( a1 )
        {
          for ( i = 0; i < v15; ++i )
            usb_write_length(*(_DWORD *)(v7 + 4 * i), 0, v18, v19);
        }
        else
        {
          for ( j = 0; j < v15; ++j )
            usb_write_status16(*(unsigned __int16 *)(v7 + 2 * j), 0, v18, v19);
        }
        MEMORY[0x102894]();
      }
    }
  }
  else
  {
    if ( v7 << 31 )
    {
      v20 = 7430;
      goto LABEL_24;
    }
    if ( v15 < 0x80000000 )
    {
      v21 = 2 * v15;
      goto LABEL_12;
    }
  }
LABEL_24:
  if ( !a2 )
    usb_write_status16((unsigned __int16)v20, 1, v18, v19);
  return v20;
}


// ==================== sub_EE6C @0xEE6C size=168 ====================
void __fastcall sub_EE6C(int a1, int a2, int a3, int a4)
{
  unsigned __int16 v4; // r4
  int v5; // r8
  unsigned int v6; // r0
  unsigned int v7; // r5
  int v8; // r2
  unsigned int v9; // r3
  int v10; // r0
  int v11; // r1
  int v12; // r2
  int v13; // r3
  unsigned int v14; // r0
  unsigned int v15; // r6
  int v16; // r2
  unsigned int v17; // r3
  int v18; // r0
  int v19; // r1
  int v20; // r2
  int v21; // r3
  unsigned int v22; // r0
  unsigned int v23; // r7
  int v24; // r2
  unsigned int v25; // r3
  int v26; // r2
  unsigned int v27; // r3
  int v28; // r5
  unsigned int v29; // r0

  v4 = 0;
  v5 = 1;
  sub_E942(a1, a2, a3, a4);
  v7 = v6;
  usb_write_length(v6, 1, v8, v9);
  sub_E942(v10, v11, v12, v13);
  v15 = v14;
  usb_write_length(v14, 1, v16, v17);
  sub_E942(v18, v19, v20, v21);
  v23 = v22;
  usb_write_length(v22, 1, v24, v25);
  if ( v7 << 31 )
  {
    v5 = 0;
    MEMORY[0x10289A] = 1;
  }
  if ( (v7 & 2) != 0 )
  {
    v28 = 1048580;
    v29 = 44;
  }
  else
  {
    v28 = 1048624;
    v29 = 16;
  }
  if ( v29 > v15 )
  {
    if ( v23 && v29 >= v23 )
    {
      if ( v15 + v23 <= v29 )
      {
        usb_write_status16(0, 1, v26, v27);
        if ( v5 )
          sub_EA46(v28 + v15, v23);
        else
          usb_read_buffer(v28 + v15, v23, 0);
      }
      else
      {
        v4 = 7452;
      }
    }
    else
    {
      v4 = 7451;
    }
  }
  else
  {
    v4 = 7450;
  }
  usb_write_status16(v4, 1, v26, v27);
  JUMPOUT(0xEE68);
}


// ==================== sub_EF30 @0xEF30 size=98 ====================
void __fastcall __noreturn sub_EF30(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r2
  unsigned int v5; // r3
  unsigned __int16 v6; // r4
  unsigned int v7; // r0
  unsigned int v8; // [sp+0h] [bp-4h] BYREF

  v8 = a4;
  usb_write_status16(MEMORY[0x102878], 1, a3, a4);
  if ( sub_613E() && !MEMORY[0x102880] && MEMORY[0x10289A] )
  {
    v6 = 7437;
  }
  else if ( MEMORY[0x1027C4] && (*(_DWORD *)(MEMORY[0x1027C4] + 40) & 2) != 0 )
  {
    v6 = 7435;
  }
  else
  {
    v7 = sub_10CB2(&v8);
    v6 = v7;
    if ( v7 < 0xFF )
    {
      usb_write_status16((unsigned __int16)v7, 1, v4, v5);
      sub_DE28();
    }
  }
  usb_write_status16(v6, 1, v4, v5);
  brom_halt_forever(0);
}


// ==================== sub_EF94 @0xEF94 size=76 ====================
int __fastcall sub_EF94(unsigned int a1)
{
  unsigned int i; // r1

  if ( !MEMORY[0x102BA8] )
    return 7446;
  if ( MEMORY[0x1027C4]
    && *(_DWORD *)(MEMORY[0x1027C4] + 40) << 31
    && *(_DWORD *)(MEMORY[0x1027C4] + 44) != MEMORY[0x102BA8] )
  {
    return 7447;
  }
  for ( i = 0; i < MEMORY[0x102BA8]; ++i )
  {
    if ( *(_DWORD *)(16 * i + 0x102BAC) <= a1 && *(_DWORD *)(16 * i + 0x102BB4) - 1 >= a1 )
      return 0;
  }
  return 7439;
}


// ==================== sub_EFE0 @0xEFE0 size=150 ====================
void __fastcall __noreturn sub_EFE0(int a1, int a2, int a3, int a4)
{
  char v5; // r5
  unsigned int v6; // r0
  unsigned int v7; // r7
  int v8; // r2
  unsigned int v9; // r3
  int v10; // r0
  int v11; // r1
  int v12; // r2
  int v13; // r3
  unsigned int v14; // r4
  int v15; // r2
  unsigned int v16; // r3
  unsigned __int16 v17; // r4
  int v18; // r0
  int v19; // r1
  int v20; // r2
  int v21; // r3
  int v22; // r0
  unsigned int v23; // r0

  v5 = 0;
  MEMORY[0x102881] = 0;
  sub_E942(a1, a2, a3, a4);
  v7 = v6;
  usb_write_length(v6, 1, v8, v9);
  if ( a1 == 1 )
  {
    v14 = usb_read_byte(v10, v11, v12, v13);
    usb_write_byte(v14, 1);
    if ( v14 >= 2 )
    {
      v17 = 7457;
      goto LABEL_10;
    }
    v18 = usb_write_status16(0, 1, v15, v16);
    if ( v14 == 1 )
    {
      v22 = usb_read_byte(v18, v19, v20, v21);
      v5 = v22;
      usb_write_byte(v22, 1);
    }
  }
  if ( sub_613E() && !MEMORY[0x102880] )
  {
    v17 = 7437;
  }
  else
  {
    v23 = sub_EF94(v7);
    v17 = v23;
    if ( v23 < 0xFF )
    {
      MEMORY[0x102881] = v5;
      usb_write_status16((unsigned __int16)v23, 1, v15, v16);
      sub_DE28();
    }
  }
LABEL_10:
  usb_write_status16(v17, 1, v15, v16);
  brom_halt_forever(0);
}


// ==================== sub_F076 @0xF076 size=74 ====================
unsigned int __fastcall sub_F076(unsigned int a1, unsigned int a2, unsigned int a3)
{
  unsigned int result; // r0

  if ( a1 << 31 )
    return 7441;
  if ( !a2 )
    return 7443;
  if ( a2 <= a3 )
    return 7444;
  if ( !a3 && sub_6162() )
    return 7445;
  result = sub_DD78(a1, a2, 415);
  if ( result < 0xFF && result != 1 )
    return 7442;
  return result;
}


// ==================== sub_F0C0 @0xF0C0 size=52 ====================
int __fastcall sub_F0C0(int a1, int a2, int a3)
{
  int v3; // r3
  _DWORD *v5; // r4

  v3 = MEMORY[0x102BA8];
  if ( MEMORY[0x102BA8] >= 0xAu )
    return 7440;
  v5 = (_DWORD *)(16 * MEMORY[0x102BA8] + 1059752);
  v5[1] = a1;
  v5[2] = a2;
  v5[3] = a1 + a2 - a3;
  v5[4] = a3;
  *(_DWORD *)(8 * v3 + 0x102C4C) = a1;
  *(_DWORD *)(8 * v3 + 0x102C50) = a1 + a2;
  ++MEMORY[0x102BA8];
  return 0;
}


// ==================== sub_F0F4 @0xF0F4 size=220 ====================
int __fastcall sub_F0F4(int a1, int a2, int a3, int a4)
{
  unsigned int v4; // r0
  unsigned int v5; // r6
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r0
  int v9; // r1
  int v10; // r2
  int v11; // r3
  unsigned int v12; // r0
  unsigned int v13; // r5
  int v14; // r2
  unsigned int v15; // r3
  int v16; // r0
  int v17; // r1
  int v18; // r2
  int v19; // r3
  unsigned int v20; // r0
  unsigned int v21; // r7
  int v22; // r2
  unsigned int v23; // r3
  int v24; // r2
  unsigned int v25; // r3
  unsigned int v26; // r0
  unsigned __int16 v27; // r4
  unsigned int v28; // r0
  int v29; // r2
  unsigned int v30; // r3
  unsigned int v31; // r0
  unsigned int v32; // r0
  int v33; // r2
  unsigned int v34; // r3

  sub_E942(a1, a2, a3, a4);
  v5 = v4;
  usb_write_length(v4, 1, v6, v7);
  sub_E942(v8, v9, v10, v11);
  v13 = v12;
  usb_write_length(v12, 1, v14, v15);
  sub_E942(v16, v17, v18, v19);
  v21 = v20;
  usb_write_length(v20, 1, v22, v23);
  if ( sub_613E() && !MEMORY[0x102880] )
  {
    v27 = 7437;
    goto LABEL_13;
  }
  v26 = sub_F076(v5, v13, v21);
  v27 = v26;
  if ( v26 >= 0xFF || (v28 = sub_EBD8(v5, v13), v27 = v28, v28 >= 0xFF) )
  {
LABEL_13:
    usb_write_status16(v27, 1, v24, v25);
    brom_halt_forever(0);
  }
  MEMORY[0x102878] = sub_10CD4();
  usb_write_status16(v27, 1, v29, v30);
  usb_read_buffer(v5, v13, 1);
  sub_498();
  if ( sub_6162() )
  {
    if ( !MEMORY[0x1027C4] )
    {
      v27 = 28695;
      goto LABEL_12;
    }
    sub_6E50(MEMORY[0x102BA8], v5, v13, v21);
    v27 = v31;
    if ( v31 >= 0xFF )
      goto LABEL_12;
  }
  v32 = sub_F0C0(v5, v13, v21);
  v27 = v32;
  if ( v32 >= 0xFF )
  {
LABEL_12:
    mem_set_bytes(v5, 68, v13);
    goto LABEL_13;
  }
  return usb_write_status16((unsigned __int16)v32, 1, v33, v34);
}


// ==================== cmd_e8_send_auth (sub_F1D0) @0xF1D0 size=138 ====================
unsigned int __fastcall cmd_e8_send_auth(int a1, int a2, int a3, int a4)
{
  unsigned int v5; // r0
  unsigned int v6; // r6
  int v7; // r2
  unsigned int v8; // r3
  int v9; // r2
  unsigned int v10; // r3
  unsigned int v11; // r4
  unsigned int v12; // r0
  __int64 v13; // r0
  int v14; // r2
  unsigned int v15; // r3

  sub_E942(a1, a2, a3, a4);
  v6 = v5;
  usb_write_length(v5, 1, v7, v8);
  if ( efuse_get_secure_boot() && !sub_6AE8() )
  {
    v11 = 7437;
  }
  else if ( MEMORY[0x10289B] )
  {
    v11 = 7436;
  }
  else
  {
    MEMORY[0x10289B] = 1;
    v12 = sub_647A(v6);
    v11 = v12;
    if ( v12 < 0xFF )
    {
      usb_write_status16((unsigned __int16)v12, 1, v9, v10);
      usb_read_buffer(1051136, v6, 1);
      v11 = auth_verify_file(1051136, 1);
      if ( v11 >= 0xFF )
        mem_set_bytes(1051136, 68, v6);
    }
  }
  usb_write_status16((unsigned __int16)v11, 1, v9, v10);
  if ( a1 )
    usb_write_status16(MEMORY[0x10287C], 1, v14, v15);
  LODWORD(v13) = 2;
  usb_status_reset(v13);
  return v11;
}


// ==================== cmd_send_cert (sub_F25A) @0xF25A size=102 ====================
int __fastcall cmd_send_cert(int a1, int a2, int a3, int a4)
{
  unsigned int v4; // r0
  unsigned int v5; // r5
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r2
  unsigned int v9; // r3
  int v10; // r4
  unsigned int v11; // r0
  unsigned int v12; // r0
  __int64 v13; // r0

  sub_E942(a1, a2, a3, a4);
  v5 = v4;
  usb_write_length(v4, 1, v6, v7);
  if ( MEMORY[0x10289C] )
  {
    v10 = 7436;
  }
  else
  {
    MEMORY[0x10289C] = 1;
    sub_6BA0();
    v10 = v11;
    if ( v11 < 0xFF )
    {
      usb_write_status16((unsigned __int16)v11, 1, v8, v9);
      usb_read_buffer(1053776, v5, 1);
      auth_verify_cert(1053776);
      v10 = v12;
      if ( v12 >= 0xFF )
        mem_set_bytes(1053776, 68, v5);
    }
  }
  usb_write_status16((unsigned __int16)v10, 1, v8, v9);
  LODWORD(v13) = 2;
  usb_status_reset(v13);
  return v10;
}


// ==================== sub_F2C0 @0xF2C0 size=216 ====================
int __fastcall sub_F2C0(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r3
  int result; // r0
  int v6; // r1
  int v7; // r2
  unsigned int i; // r4
  int v9; // r5
  unsigned int v10; // r0
  int v11; // r5
  int v12; // r2
  unsigned int v13; // r3
  int v14; // r0
  int v15; // r1
  int v16; // r2
  int v17; // r3
  unsigned int v18; // r0
  unsigned int v19; // r6
  int v20; // r2
  unsigned int v21; // r3
  unsigned int v22; // r0
  int v23; // r2
  unsigned int v24; // r3
  unsigned __int16 v25; // r4
  unsigned int v26; // r0
  int v27; // r2
  unsigned int v28; // [sp+0h] [bp-4h] BYREF

  v28 = a4;
  sub_1153C(&v28, &loc_F354, 4);
  result = 1058970;
  v6 = 1;
  MEMORY[0x10289A] = 1;
  v7 = MEMORY[0x10289D];
  if ( !MEMORY[0x10289D] )
  {
    MEMORY[0x10289D] = 1;
    for ( i = 0; i < 4; ++i )
    {
      v9 = usb_read_byte(result, v6, v7, v4);
      usb_write_byte(v9, 1);
      result = *((unsigned __int8 *)&v28 + i);
      if ( result != v9 )
        return result;
    }
    sub_E942(result, v6, v7, v4);
    v11 = v10;
    usb_write_length(v10, 1, v12, v13);
    sub_E942(v14, v15, v16, v17);
    v19 = v18;
    usb_write_length(v18, 1, v20, v21);
    v22 = sub_6FDE(v11, v19);
    v25 = v22;
    if ( v22 >= 0xFF )
    {
LABEL_8:
      usb_write_status16(v25, 1, v23, v24);
      brom_halt_forever(0);
    }
    usb_write_status16((unsigned __int16)v22, 1, v23, v24);
    usb_read_buffer(v11, v19, 1);
    sub_498();
    sub_6FFA(v11);
    v25 = v26;
    if ( v26 >= 0xFF )
    {
      mem_set_bytes(v11, 68, v19);
      goto LABEL_8;
    }
    return usb_write_status16((unsigned __int16)v26, 1, v27, v28);
  }
  return result;
}


// ==================== cmd_fd_get_hw_code (sub_F398) @0xF398 size=30 ====================
int __fastcall cmd_fd_get_hw_code(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r2
  unsigned int v5; // r3

  usb_write_status16(MEMORY[0x8000000], 1, a3, a4);
  usb_write_status16(0, 1, v4, v5);
  return 0;
}


// ==================== cmd_fc_get_hw_sw_ver (sub_F3B6) @0xF3B6 size=50 ====================
int __fastcall cmd_fc_get_hw_sw_ver(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r2
  unsigned int v5; // r3
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r2
  unsigned int v9; // r3

  usb_write_status16(MEMORY[0x8000004], 1, a3, a4);
  usb_write_status16(MEMORY[0x8000008], 1, v4, v5);
  usb_write_status16(MEMORY[0x800000C], 1, v6, v7);
  usb_write_status16(0, 1, v8, v9);
  return 0;
}


// ==================== sub_F3E8 @0xF3E8 size=34 ====================
int __fastcall sub_F3E8(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r2
  unsigned int v5; // r3

  usb_write_length(0x10u, 1, a3, a4);
  sub_EA46(1059704, 16);
  usb_write_status16(0, 1, v4, v5);
  return 0;
}


// ==================== cmd_e7_get_soc_id (sub_F40A) @0xF40A size=34 ====================
int __fastcall cmd_e7_get_soc_id(int a1, int a2, int a3, unsigned int a4)
{
  int v4; // r2
  unsigned int v5; // r3

  usb_write_length(0x20u, 1, a3, a4);
  sub_EA46(1059720, 32);
  usb_write_status16(0, 1, v4, v5);
  return 0;
}


// ==================== sub_F42C @0xF42C size=128 ====================
int sub_F42C()
{
  unsigned int v0; // r4
  int v1; // r0
  int v2; // r2
  unsigned int v3; // r3
  int v4; // r2
  unsigned int v5; // r3

  v0 = sub_6128() != 0;
  if ( sub_613E() )
    v0 |= 2u;
  if ( sub_6162() )
    v0 |= 4u;
  if ( sub_EB24() )
    v0 |= 0x20u;
  if ( sub_EB60() )
    v0 |= 0x40u;
  if ( sub_EB9C() )
    v0 |= 0x80u;
  if ( sub_765C() && !sub_7630() )
    v0 |= 0x10u;
  if ( efuse_get_secure_boot() )
  {
    sub_6AD8();
    if ( v1 )
      v0 |= 0x100u;
  }
  if ( board_check_flag3(0) )
    v0 |= 8u;
  usb_write_length(v0, 1, v2, v3);
  usb_write_status16(0, 1, v4, v5);
  return 0;
}


// ==================== sub_F4AC @0xF4AC size=242 ====================
unsigned int sub_F4AC()
{
  int v0; // r2
  unsigned int v1; // r3
  unsigned int v2; // r4
  unsigned int v3; // r1
  int v4; // r5
  unsigned __int16 v5; // r4
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r0
  int v9; // r1
  int v10; // r2
  int v11; // r3
  unsigned int v12; // r0
  unsigned int v13; // r9
  int v14; // r2
  unsigned int v15; // r3
  _BYTE v17[256]; // [sp+4h] [bp-108h] BYREF
  unsigned int v18; // [sp+104h] [bp-8h] BYREF
  int v19; // [sp+108h] [bp-4h] BYREF

  if ( !sub_613E() || MEMORY[0x102880] )
  {
    v2 = 7437;
    goto LABEL_21;
  }
  if ( MEMORY[0x10289E] )
  {
    v2 = 7436;
    goto LABEL_21;
  }
  MEMORY[0x10289E] = 1;
  if ( !MEMORY[0x1027C4] )
  {
    v2 = 28695;
    goto LABEL_21;
  }
  v3 = *(_DWORD *)(MEMORY[0x1027C4] + 40);
  v0 = 12;
  v2 = 28740;
  if ( v3 >> 28 == 12 && (v3 & 0x6000) != 0 )
  {
    v4 = *(_DWORD *)(MEMORY[0x1027C4] + 900);
    if ( v4 != 256 )
      goto LABEL_21;
    goto LABEL_14;
  }
  v4 = 2 * *(_DWORD *)(MEMORY[0x1027C4] + 900);
  if ( v4 == 128 || v4 == 256 )
  {
LABEL_14:
    usb_write_status16(0, 1, 12, v1);
    v5 = sub_6CDE(&v19, &v18);
    usb_write_length(v18, 1, v6, v7);
    v8 = sub_EA46(v19, v18);
    sub_E942(v8, v9, v10, v11);
    v13 = v12;
    usb_write_length(v12, 1, v14, v15);
    if ( v4 == v13 )
    {
      usb_write_status16(v5, 1, v0, v1);
      usb_read_buffer((int)v17, v13, 0);
      v2 = sub_6D42((int)v17, v13);
      if ( v2 < 0xFF )
        MEMORY[0x102880] = 1;
      else
        mem_set_bytes(v17, 68, v13);
    }
    else if ( v4 == 128 )
    {
      v2 = 28741;
    }
    else
    {
      v2 = 28742;
    }
  }
LABEL_21:
  usb_write_status16((unsigned __int16)v2, 1, v0, v1);
  return v2;
}


// ==================== cmd_e4 (sub_F59E) @0xF59E size=18 ====================
int __fastcall cmd_e4(int a1, int a2, int a3, unsigned int a4)
{
  usb_write_status16(0x703Au, 1, a3, a4);
  return 28730;
}


// ==================== cmd_e5 (sub_F5B0) @0xF5B0 size=104 ====================
unsigned int __fastcall cmd_e5(int a1, int a2, int a3, int a4)
{
  unsigned int v4; // r0
  unsigned int v5; // r5
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r2
  unsigned int v9; // r3
  unsigned int v10; // r4
  unsigned int v11; // r0
  __int64 v12; // r0

  sub_E942(a1, a2, a3, a4);
  v5 = v4;
  usb_write_length(v4, 1, v6, v7);
  if ( MEMORY[0x10289F] )
  {
    v10 = 7436;
  }
  else
  {
    MEMORY[0x10289F] = 1;
    v11 = sub_767E(v5);
    v10 = v11;
    if ( v11 < 0xFF )
    {
      usb_write_status16((unsigned __int16)v11, 1, v8, v9);
      usb_read_buffer(1056080, v5, 1);
      v10 = sub_782C(1056080, 1);
      if ( v10 >= 0xFF )
        mem_set_bytes(1056080, 68, v5);
    }
  }
  usb_write_status16((unsigned __int16)v10, 1, v8, v9);
  LODWORD(v12) = 2;
  usb_status_reset(v12);
  return v10;
}


// ==================== cmd_e6 (sub_F618) @0xF618 size=64 ====================
unsigned int __fastcall cmd_e6(int a1, int a2, unsigned int a3, int a4)
{
  unsigned int v4; // r0
  int v5; // r2
  unsigned int v6; // r3
  unsigned int v7; // r4
  int v8; // r2
  unsigned int v9; // r3
  int v10; // r2
  unsigned int v11; // r3
  int v14; // [sp+4h] [bp-4h] BYREF

  v14 = a4;
  v4 = sub_7694(&v14);
  v7 = v4;
  if ( v4 < 0xFF )
  {
    usb_write_status16((unsigned __int16)v4, 1, v5, v6);
    v7 = 0;
    usb_write_length(0x30u, 1, v8, v9);
    sub_EA46(v14, 48);
    usb_write_length(a3, 1, v10, v11);
  }
  usb_write_status16((unsigned __int16)v7, 1, v5, v6);
  return v7;
}


// ==================== sub_F658 @0xF658 size=212 ====================
unsigned int __fastcall sub_F658(int a1, int a2, int a3, int a4)
{
  unsigned int v4; // r0
  int v5; // r8
  int v6; // r2
  unsigned int v7; // r3
  int v8; // r0
  int v9; // r1
  int v10; // r2
  int v11; // r3
  unsigned int v12; // r0
  unsigned int v13; // r5
  int v14; // r2
  unsigned int v15; // r3
  int v16; // r0
  int v17; // r1
  int v18; // r2
  int v19; // r3
  unsigned int v20; // r0
  int v21; // r6
  int v22; // r2
  unsigned int v23; // r3
  int v24; // r0
  int v25; // r1
  int v26; // r2
  int v27; // r3
  unsigned int v28; // r0
  int v29; // r7
  int v30; // r2
  unsigned int v31; // r3
  int v32; // r2
  unsigned int v33; // r3
  unsigned int v34; // r4
  int v35; // r2
  unsigned int v36; // r3
  unsigned int v37; // r0
  int v38; // r2
  unsigned int v39; // r3
  int v41; // r2
  unsigned int v42; // r3
  unsigned int v43; // [sp+4h] [bp-4h] BYREF

  v43 = a4;
  sub_E942(a1, a2, a3, a4);
  v5 = v4;
  usb_write_length(v4, 1, v6, v7);
  sub_E942(v8, v9, v10, v11);
  v13 = v12;
  usb_write_length(v12, 1, v14, v15);
  sub_E942(v16, v17, v18, v19);
  v21 = v20;
  usb_write_length(v20, 1, v22, v23);
  sub_E942(v24, v25, v26, v27);
  v29 = v28;
  usb_write_length(v28, 1, v30, v31);
  if ( sub_613E() && !MEMORY[0x102880] )
  {
    v34 = 7437;
  }
  else if ( MEMORY[0x1028A0] )
  {
    v34 = 7436;
  }
  else
  {
    MEMORY[0x1028A0] = 1;
    v34 = sub_712E(v5, v13, v21, v29);
    if ( v34 < 0xFF )
    {
      MEMORY[0x102878] = sub_10CD4();
      usb_write_status16((unsigned __int16)v34, 1, v35, v36);
      usb_read_buffer(v5, v13, 1);
      MEMORY[0x102894]();
      sub_498();
      sub_7172(v5, v13, v21, v29, &v43);
      v34 = v37;
      if ( v37 < 0xFF )
      {
        usb_write_status16((unsigned __int16)v37, 1, v38, v39);
        usb_write_length(v43, 1, v41, v42);
        return v34;
      }
      mem_set_bytes(v5, 68, v13);
    }
  }
  usb_write_status16((unsigned __int16)v34, 1, v32, v33);
  return v34;
}


// ==================== sub_F72C @0xF72C size=26 ====================
int __fastcall sub_F72C(int a1, int a2, int a3, unsigned int a4)
{
  MEMORY[0x103EC0] = 1414676821;
  MEMORY[0x103EC4] = 1313169201;
  usb_write_status16(0, 1, a3, a4);
  return 0;
}


// ==================== cmd_reserved_dc (sub_F746) @0xF746 size=78 ====================
int __fastcall cmd_reserved_dc(int a1, int a2, int a3, int a4)
{
  int v4; // r4
  unsigned int v5; // r0
  unsigned int v6; // r5
  int v7; // r2
  unsigned int v8; // r3
  unsigned int v9; // r3
  int v10; // r0

  v4 = 0;
  sub_E942(a1, a2, a3, a4);
  v6 = v5;
  usb_write_length(v5, 1, v7, v8);
  if ( v6 - 110 < 0xE0F93 )
  {
    usb_write_status16(0, 1, 921491, v9);
    sub_E7D4();
    v10 = sub_70C();
    sub_E7FC(v10, v6);
    MEMORY[0x11002008] = -107;
  }
  else
  {
    v4 = 7453;
    usb_write_status16(0x1D1Du, 1, 921491, v9);
  }
  return v4;
}


// ==================== sub_F794 @0xF794 size=20 ====================
int __fastcall sub_F794(int a1, int a2, int a3, unsigned int a4)
{
  usb_write_length(MEMORY[0x102868], 1, a3, a4);
  sub_E662();
  return 0;
}


// ==================== sub_F7A8 @0xF7A8 size=60 ====================
unsigned int sub_F7A8()
{
  unsigned int v0; // r4
  int v1; // r1
  int v2; // r2
  int v3; // r3
  int v4; // r4
  int v5; // r2
  unsigned int v6; // r3
  int v8; // [sp+0h] [bp-4h] BYREF

  v0 = 0;
  v8 = 0;
  if ( !sub_EB9C() )
  {
    v4 = usb_read_byte(0, v1, v2, v3);
    usb_write_byte(v4, 1);
    v0 = (unsigned __int16)sub_428(v4, &v8);
    usb_write_byte((unsigned __int8)v8, 1);
    usb_write_status16(v0, 1, v5, v6);
  }
  return v0;
}


// ==================== brom_command_loop_init (sub_F81C) @0xF81C size=20 ====================
int brom_command_loop_init()
{
  mem_set_bytes(1059752, 0, 244);
  return usb_install_callbacks();
}


// ==================== brom_command_loop (sub_F830) @0xF830 size=396 ====================
void __noreturn brom_command_loop()
{
  int v0; // r0
  int v1; // r1
  unsigned int v2; // r2
  unsigned int v3; // r3
  int v4; // r0
  int v5; // r4
  int v6; // r2
  unsigned int v7; // r3

  v0 = brom_command_loop_init();
  while ( 1 )
  {
    while ( 1 )
    {
      while ( 1 )
      {
        v4 = usb_read_byte(v0, v1, v2, v3);
        v5 = v4;
        if ( v4 != 255 )
          break;
        v0 = usb_write_byte(5, 1);
      }
      v0 = usb_write_byte(v4, 1);
      if ( v5 != 220 )
        break;
      v0 = cmd_reserved_dc(v0, v1, v2, v3);
    }
    if ( v5 > 220 )
    {
      if ( v5 == 228 )
      {
        v0 = cmd_e4(v0, v1, v2, v3);
      }
      else if ( v5 > 228 )
      {
        if ( v5 == 232 )
        {
          cmd_e8_send_auth(1, v1, v2, v3);
          v0 = sub_384();
        }
        else if ( v5 > 232 )
        {
          if ( v5 == 252 )
          {
            v0 = cmd_fc_get_hw_sw_ver(v0, v1, v2, v3);
          }
          else if ( v5 == 253 )
          {
            v0 = cmd_fd_get_hw_code(v0, v1, v2, v3);
          }
        }
        else if ( v5 == 229 )
        {
          cmd_e5(v0, v1, v2, v3);
          v0 = sub_384();
        }
        else if ( v5 == 230 )
        {
          v0 = cmd_e6(v0, v1, v2, v3);
        }
        else
        {
          v0 = cmd_e7_get_soc_id(v0, v1, v2, v3);
        }
      }
      else
      {
        switch ( v5 )
        {
          case 221:
            v0 = sub_F794(v0, v1, v2, v3);
            break;
          case 222:
            sub_EFE0(1, v1, v2, v3);
          case 223:
            sub_F794(v0, v1, v2, v3);
            v0 = usb_write_status16(0, 1, v6, v7);
            break;
          case 224:
            cmd_e8_send_auth(0, v1, v2, v3);
            v0 = sub_384();
            break;
          case 225:
            v0 = sub_F3E8(v0, v1, v2, v3);
            break;
          case 226:
            cmd_send_cert(v0, v1, v2, v3);
            v0 = sub_384();
            break;
          case 227:
            v0 = sub_F4AC();
            break;
        }
      }
    }
    else if ( v5 == 212 )
    {
      sub_ECB2(1, 1, v2, v3);
    }
    else if ( v5 > 212 )
    {
      switch ( v5 )
      {
        case 213:
          sub_EFE0(0, v1, v2, v3);
        case 214:
          sub_EF30(v0, v1, v2, v3);
        case 215:
          v0 = sub_F0F4(v0, v1, v2, v3);
          break;
        case 216:
          v0 = sub_F42C();
          break;
        case 217:
          v0 = sub_F658(v0, v1, v2, v3);
          break;
        case 218:
          sub_EE6C(v0, v1, v2, v3);
          v0 = sub_384();
          break;
        case 219:
          sub_F72C(v0, v1, v2, v3);
          v0 = sub_384();
          break;
      }
    }
    else if ( v5 == 208 )
    {
      v0 = sub_EDB2(0, 0, v2, v3);
    }
    else if ( v5 > 208 )
    {
      if ( v5 == 209 )
      {
        v0 = sub_EDB2(1, 0, v2, v3);
      }
      else if ( v5 == 210 )
      {
        sub_ECB2(0, 1, v2, v3);
      }
      else
      {
        sub_ECB2(0, 0, v2, v3);
      }
    }
    else
    {
      switch ( v5 )
      {
        case 136:
          sub_F2C0(v0, v1, v2, v3);
          v0 = sub_384();
          break;
        case 162:
          v0 = sub_EDB2(0, 1, v2, v3);
          break;
        case 200:
          v0 = sub_F7A8();
          break;
      }
    }
  }
}


// ==================== auth_walk_tlv_chain (sub_F9C0) @0xF9C0 size=120 ====================
unsigned int __fastcall auth_walk_tlv_chain(int a1, int a2, int a3, _DWORD *a4, int a5)
{
  int v8; // r6
  unsigned int result; // r0
  unsigned int v10; // r2
  unsigned int v11; // r1
  int v12; // r4
  int v13; // r0
  unsigned int v14; // r5

  v8 = 0;
  if ( a1 << 30 )
    return 32780;
  result = auth_check_file_info(a1);
  if ( result < 0xFF )
  {
    v10 = *(_DWORD *)(a1 + 40);
    v11 = 0;
    while ( v11 < v10 )
    {
      v12 = a1 + v11;
      v13 = *(_DWORD *)(a1 + v11);
      if ( v13 == 1162167621 )
        break;
      if ( v13 << 8 != 1296911616 )
        return 32769;
      v14 = *(unsigned __int16 *)(v12 + 4);
      v11 += v14;
      if ( v14 < 8 || v10 < v11 || v14 << 30 )
        return 32772;
      if ( *(unsigned __int16 *)(v12 + 6) == a3 )
      {
        if ( v8 == a5 )
        {
          *a4 = v12;
          return 0;
        }
        ++v8;
      }
    }
    return 32769;
  }
  return result;
}


// ==================== auth_find_block_by_type (sub_FA38) @0xFA38 size=18 ====================
unsigned int __fastcall auth_find_block_by_type(int a1, int a2, _DWORD *a3)
{
  return auth_walk_tlv_chain(a1, 0, a2, a3, 0);
}


// ==================== sub_FA4A @0xFA4A size=28 ====================
unsigned int __fastcall sub_FA4A(int a1, int a2, _DWORD *a3, int a4)
{
  if ( !a3 )
    return 32770;
  *a3 = 0;
  return auth_walk_tlv_chain(a1, 0, a2, a3, a4);
}


// ==================== auth_check_file_info (sub_FA6C) @0xFA6C size=82 ====================
int __fastcall auth_check_file_info(int a1)
{
  unsigned int v3; // r0
  unsigned int v4; // r1

  if ( *(_DWORD *)a1 << 8 != 1296911616 || *(_WORD *)(a1 + 6) || sub_116D8(a1 + 8, "FILE_INFO") )
    return 32773;
  v3 = *(_DWORD *)(a1 + 40);
  if ( !v3 || v3 > 0x100000 )
    return 32774;
  v4 = *(_DWORD *)(a1 + 32);
  if ( !v4 || v4 > 0x80000000 )
    return 32775;
  if ( v3 <= v4 )
    return 0;
  return 32774;
}


// ==================== auth_check_block_header (sub_FABE) @0xFABE size=98 ====================
unsigned int __fastcall auth_check_block_header(int a1)
{
  unsigned int result; // r0
  unsigned int v3; // r0
  unsigned int v4; // r0
  unsigned int v5; // r1
  unsigned int v6; // r1

  result = auth_check_file_info(a1);
  if ( result < 0xFF )
  {
    v3 = *(_DWORD *)(a1 + 36);
    if ( v3 == -1 || v3 >= *(_DWORD *)(a1 + 32) )
    {
      v4 = *(_DWORD *)(a1 + 44);
      if ( *(_BYTE *)(a1 + 27) || !v4 )
      {
        if ( !*(_BYTE *)(a1 + 27) || v4 && (v5 = *(_DWORD *)(a1 + 32), v5 > v4) && *(_DWORD *)(a1 + 40) <= v5 - v4 )
        {
          v6 = *(_DWORD *)(a1 + 48);
          if ( v6 && (*(_DWORD *)(a1 + 40) > v6 || *(_DWORD *)(a1 + 32) - v4 <= v6) )
            return 32778;
          else
            return 0;
        }
        else
        {
          return 32776;
        }
      }
      else
      {
        return 32776;
      }
    }
    else
    {
      return 32777;
    }
  }
  return result;
}


// ==================== sub_FB30 @0xFB30 size=84 ====================
int __fastcall sub_FB30(int a1, int a2)
{
  unsigned int v3; // r2
  unsigned int v4; // r1
  __int64 v5; // kr00_8
  unsigned int v6; // r0
  unsigned int v7; // r0

  if ( !a1 )
    return 32773;
  if ( !a2 )
    return 33025;
  if ( !*(_BYTE *)(a2 + 8) && !*(_BYTE *)(a2 + 9) )
    return 0;
  v3 = *(_DWORD *)(a2 + 12);
  v4 = *(_DWORD *)(a2 + 16);
  v5 = *(_QWORD *)(a1 + 40);
  v6 = *(_DWORD *)(a1 + 32);
  if ( (int)v5 + HIDWORD(v5) >= v6 )
    return 28679;
  v7 = v6 - v5 - HIDWORD(v5);
  if ( v4 && v7 > v3 && v7 > v4 && v7 - v3 > v4 )
    return 0;
  else
    return 28676;
}


// ==================== sub_FB84 @0xFB84 size=54 ====================
int __fastcall sub_FB84(int a1, _DWORD *a2)
{
  int result; // r0
  unsigned int v4; // r2
  unsigned int v5; // r1

  result = 0;
  if ( !a1 )
    return 32773;
  if ( !a2 )
    return 33031;
  if ( a2[10] << 31 )
  {
    v4 = a2[12];
    if ( v4 && v4 <= 0xA )
    {
      v5 = a2[11];
      if ( !v5 || v4 < v5 )
        return 33033;
    }
    else
    {
      return 33032;
    }
  }
  return result;
}


// ==================== auth_check_block_consistency (sub_FBBC) @0xFBBC size=106 ====================
int __fastcall auth_check_block_consistency(int a1, int a2)
{
  if ( !a1 )
    return 32773;
  if ( !a2 )
    return 33028;
  if ( *(_DWORD *)(a2 + 8) != 1280590675 || *(_DWORD *)(a2 + 12) != 1414677827 )
    return 33029;
  if ( HIBYTE(*(_DWORD *)a2) == 2 )
  {
    if ( *(_WORD *)(a2 + 4) != 52 )
      return 33053;
    if ( *(_BYTE *)(a1 + 27) != 5 )
      return 33054;
  }
  else
  {
    if ( *(_WORD *)(a2 + 4) != 592 )
      return 33052;
    if ( *(_BYTE *)(a1 + 27) != 2 )
      return 28773;
  }
  return 0;
}


// ==================== sub_FC30 @0xFC30 size=42 ====================
int __fastcall sub_FC30(int a1, int a2)
{
  int result; // r0

  result = 0;
  if ( !a1 )
    return 32773;
  if ( !a2 )
    return 33035;
  if ( *(_DWORD *)(a2 + 8) != 1145194305 || *(_DWORD *)(a2 + 12) != 1297369951 )
    return 33036;
  return result;
}


// ==================== sub_FC64 @0xFC64 size=20 ====================
BOOL __fastcall sub_FC64(int a1)
{
  return a1 && !sub_116D8(a1, "EPP_PARAM");
}


// ==================== sub_FC84 @0xFC84 size=40 ====================
int sub_FC84()
{
  int result; // r0

  for ( result = 0; LOBYTE(dword_133E0[9 * result]) != 8; ++result )
  {
    if ( (unsigned int)LOWORD(dword_133E0[9 * result + 8]) > MEMORY[0x1028AC] )
      MEMORY[0x1028AC] = LOWORD(dword_133E0[9 * result + 8]);
  }
  return result;
}


// ==================== sub_FCAC @0xFCAC size=30 ====================
int sub_FCAC()
{
  int v0; // r0

  MEMORY[0x106AD0] = 0;
  MEMORY[0x106AD4] = 8;
  MEMORY[0x106AD8] = 0;
  MEMORY[0x106ADC] = 0;
  v0 = usb_config_apply(1075920);
  nullsub_9(v0);
  return sub_FC84();
}


// ==================== sub_FCCA @0xFCCA size=38 ====================
int *__fastcall sub_FCCA(int a1)
{
  int i; // r1
  int v3; // r2

  for ( i = 0; ; ++i )
  {
    v3 = LOBYTE(dword_133E0[9 * i]);
    if ( v3 == 8 )
      break;
    if ( v3 == a1 )
      return &dword_133E0[9 * i];
  }
  return 0;
}


// ==================== sub_FCF0 @0xFCF0 size=372 ====================
int __fastcall sub_FCF0(unsigned int *a1)
{
  int v2; // r6
  int v4; // r5
  unsigned int v5; // r0
  unsigned __int16 v6; // r1
  int v7; // r4
  unsigned int v8; // r0
  int v9; // r2
  unsigned int i; // r0
  _DWORD *v11; // r0
  int v12; // r1
  _DWORD *v13; // r0
  int v14; // [sp+4h] [bp-Ch] BYREF
  int v15; // [sp+8h] [bp-8h] BYREF
  _DWORD *v16; // [sp+Ch] [bp-4h] BYREF

  v16 = 0;
  v15 = 0;
  v14 = 0;
  v2 = 0;
  if ( MEMORY[0x106B8C] )
    return 0;
  if ( !MEMORY[0x106B64] )
    return 0;
  if ( *(unsigned __int8 *)(MEMORY[0x106B64] + 13) <= 2u )
    return 0;
  v4 = IDAW_MEM[0x106B64];
  while ( 1 )
  {
    if ( sub_FA4A(v4, 18, &v16, v2) >= 0xFF )
      return 0;
    v5 = auth_find_block_by_type(v16[4] + v4, 0, &v15);
    v6 = v5;
    if ( v5 < 0xFF )
    {
      if ( *(_WORD *)(v15 + 24) == 9 )
      {
        v8 = auth_find_block_by_type(v16[4] + v4, 14, &v14);
        v6 = v8;
        if ( v8 >= 0xFF )
        {
          v7 = 244;
        }
        else if ( *(unsigned __int16 *)(v14 + 12) == MEMORY[0x8000000]
               && ((v9 = *(_DWORD *)(v14 + 8), v9 << 31) || *(unsigned __int16 *)(v14 + 14) == MEMORY[0x8000008])
               && ((v9 & 2) != 0 || *(unsigned __int16 *)(v14 + 16) == MEMORY[0x800000C]) )
        {
          v7 = 244;
        }
        else
        {
          v7 = 243;
        }
      }
      else
      {
        v7 = 28749;
      }
    }
    else
    {
      v7 = 28788;
    }
    if ( !(v16[2] << 31) )
      usb_write_debug_event((unsigned __int16)v7, v6, 0x15u, (unsigned __int16)v2, 82);
    if ( v7 == 244 )
      break;
    ++v2;
  }
  for ( i = 0; i < 8; ++i )
  {
    if ( !*(_BYTE *)(20 * i + 0x100855) )
      break;
  }
  if ( i >= 8 )
    return 4142;
  if ( a1 )
    *a1 = i;
  v11 = (_DWORD *)(20 * i + 1050696);
  MEMORY[0x106B8C] = v11;
  v12 = v15;
  v11[1] = *(_DWORD *)(v15 + 32);
  *v11 = *(_DWORD *)(v12 + 28);
  *(_BYTE *)(v11[2] + 4) = 0;
  *(_DWORD *)(*(_DWORD *)(MEMORY[0x106B8C] + 8) + 16) = v16[3];
  *(_WORD *)(*(_DWORD *)(MEMORY[0x106B8C] + 8) + 6) = 9;
  **(_DWORD **)(MEMORY[0x106B8C] + 8) = 1111638594;
  v13 = v16;
  *(_DWORD *)(*(_DWORD *)(MEMORY[0x106B8C] + 8) + 8) = v16[4] + v4;
  *(_DWORD *)(*(_DWORD *)(MEMORY[0x106B8C] + 8) + 12) = v13[4] + *(_DWORD *)(v15 + 32) + v4;
  return 244;
}


// ==================== sub_FE64 @0xFE64 size=42 ====================
int __fastcall sub_FE64(int *a1)
{
  int v1; // r1
  int v2; // r3
  int v3; // r4
  int v4; // r1
  int v5; // r6
  _DWORD *v6; // r0

  v1 = a1[2];
  v2 = *(_DWORD *)(v1 + 8);
  v3 = *(_DWORD *)(v1 + 12);
  v4 = *a1;
  v5 = a1[1];
  v6 = (_DWORD *)(8 * MEMORY[0x106B60] + 1075920);
  v6[20] = v2;
  v6[21] = v3;
  v6[4] = v4;
  v6[5] = v4 + v5;
  return ++MEMORY[0x106B60];
}


// ==================== sub_FE8E @0xFE8E size=32 ====================
unsigned int __fastcall sub_FE8E(unsigned int a1, int a2)
{
  unsigned int result; // r0

  result = sub_DC9A(a1, a2, (unsigned int *)0x106AE0, MEMORY[0x106B60]);
  if ( result < 0xFF )
  {
    if ( result == 1 )
      return 0;
    else
      return 4107;
  }
  return result;
}


// ==================== sub_FEAE @0xFEAE size=266 ====================
unsigned int __fastcall sub_FEAE(int a1, int a2, int a3, int a4)
{
  unsigned int v8; // r10
  unsigned int v9; // r4
  int v10; // r2
  unsigned int v11; // r8
  int v12; // r9
  unsigned int v13; // r0
  unsigned int v14; // r0

  v8 = (unsigned __int8)(2 * a1 + 21);
  trace_begin(v8, 0);
  v9 = (*(int (__fastcall **)(int, int))(a3 + 20))(a1, a2);
  if ( v9 >= 0xFF )
    goto LABEL_19;
  if ( *(_WORD *)(*(_DWORD *)(a2 + 8) + 6) == 10 )
  {
    if ( sub_7644() )
    {
      v9 = 4131;
      goto LABEL_19;
    }
    *(_DWORD *)a2 = 1056080;
    v9 = sub_767E(*(_DWORD *)(a2 + 4));
    if ( v9 >= 0xFF )
      goto LABEL_19;
  }
  if ( efuse_get_secure_boot() && *(_WORD *)(*(_DWORD *)(a2 + 8) + 6) == 4 )
  {
    MEMORY[0x103B4C] = 0;
    MEMORY[0x103B50] = 0;
    *(_DWORD *)a2 = 1051136;
    v9 = sub_647A(*(_DWORD *)(a2 + 4));
    if ( v9 >= 0xFF )
      goto LABEL_19;
    v10 = 15;
  }
  else
  {
    v10 = 31;
  }
  v11 = *(_DWORD *)a2;
  v12 = *(_DWORD *)(a2 + 4);
  v13 = sub_DD78(*(_DWORD *)a2, v12, v10);
  v9 = v13;
  if ( v13 < 0xFF )
  {
    if ( v13 == 1 )
    {
      v14 = sub_DD36(v11, v12, 32, 1);
      v9 = v14;
      if ( v14 < 0xFF )
      {
        if ( v14 == 3 )
        {
          v9 = sub_FE8E(v11, v12);
          if ( v9 < 0xFF )
          {
            sub_FE64((int *)a2);
            v9 = (*(int (__fastcall **)(int, int, int))(a3 + 24))(a1, a2, a4);
            trace_end(v8, a1, v12, v11);
            *(_BYTE *)(a2 + 13) = 3;
            goto LABEL_20;
          }
        }
        else
        {
          v9 = 4126;
        }
      }
    }
    else
    {
      v9 = 4109;
    }
  }
LABEL_19:
  *(_BYTE *)(a2 + 13) = 2;
LABEL_20:
  *(_WORD *)(a2 + 14) = v9;
  if ( !*(_WORD *)(a2 + 16) )
    *(_WORD *)(a2 + 16) = MEMORY[0x10287C];
  trace_begin(v8, 1);
  return v9;
}


// ==================== sub_FFB8 @0xFFB8 size=20 ====================
int __fastcall sub_FFB8(int result, int *a2)
{
  if ( a2 && result != 9 && result != 10 )
  {
    result = *a2 + 1;
    *a2 = result;
  }
  return result;
}


// ==================== sub_FFCC @0xFFCC size=228 ====================
int sub_FFCC()
{
  unsigned int i; // r6
  int v1; // r0
  int result; // r0
  int v3; // [sp+0h] [bp-4h] BYREF

  v3 = 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( *(_DWORD *)(20 * i + 0x10025C) != 1111638594 || !(*(_DWORD *)(20 * i + 0x10026C) << 31) )
      continue;
    *(_BYTE *)(20 * i + 0x100855) = 1;
    sub_FFB8(*(unsigned __int16 *)(20 * i + 0x100262), &v3);
    v1 = *(unsigned __int16 *)(20 * i + 0x100262);
    switch ( v1 )
    {
      case 1:
        if ( !MEMORY[0x106B64] )
        {
          MEMORY[0x106B64] = 20 * i + 1050696;
          continue;
        }
        result = 4104;
        goto LABEL_21;
      case 9:
        if ( !MEMORY[0x106B8C] )
        {
          MEMORY[0x106B8C] = 20 * i + 1050696;
          continue;
        }
        result = 4127;
        goto LABEL_21;
      case 10:
        if ( !MEMORY[0x106BA4] )
        {
          MEMORY[0x106BA4] = 20 * i + 1050696;
          continue;
        }
        result = 4130;
LABEL_21:
        *(_WORD *)(20 * i + 0x100856) = result;
        return result;
    }
    if ( v1 == 4 && efuse_get_secure_boot() )
    {
      if ( MEMORY[0x106BA8] )
      {
        result = 4144;
        goto LABEL_21;
      }
      MEMORY[0x106BA8] = 20 * i + 1050696;
    }
  }
  if ( v3 )
    return 0;
  else
    return 4115;
}


// ==================== sub_100B0 @0x100B0 size=36 ====================
int sub_100B0()
{
  if ( (unsigned int)MEMORY[0x1028A4] - 53 < 0xC )
  {
    if ( MEMORY[0x1028A4] >= 0x40u )
      MEMORY[0x1028A4] = 64;
    else
      ++MEMORY[0x1028A4];
  }
  else
  {
    MEMORY[0x1028A4] = 53;
  }
  return MEMORY[0x1028A4];
}


// ==================== sub_100D4 @0x100D4 size=418 ====================
int __fastcall sub_100D4(int **a1, _DWORD *a2)
{
  int i; // r10
  __int64 v3; // r0
  int v4; // r7
  int v5; // r6
  int v6; // r8
  __int64 v7; // r0
  int *v8; // r4
  int v9; // r11
  int v10; // r5
  int v11; // r0
  unsigned int v13; // [sp+4h] [bp-18h]
  int v14; // [sp+8h] [bp-14h]
  int v15; // [sp+Ch] [bp-10h]

  v15 = 0;
  *a1 = 0;
  *a2 = 0;
  trace_begin(0xAu, 0);
  for ( i = 0; LOBYTE(dword_133E0[9 * i]) != 8; ++i )
  {
    v13 = sub_100B0();
    trace_begin(v13, 0);
    v4 = 0;
    v5 = 0;
    v6 = 0;
    do
    {
      LODWORD(v3) = 2;
      v7 = usb_status_reset(v3);
      sub_10D4C(v7, HIDWORD(v7));
      v8 = (int *)MEMORY[0x106AD0];
      if ( MEMORY[0x106AD0] )
        v15 = 1;
      else
        v8 = &dword_133E0[9 * i];
      if ( MEMORY[0x106AD4] == 8 || MEMORY[0x106AD4] != *(unsigned __int8 *)v8 )
      {
        v14 = 0;
        v9 = 0;
      }
      else
      {
        v14 = MEMORY[0x106AD8];
        v9 = MEMORY[0x106ADC];
      }
      if ( sub_10FA8()
        || (HIDWORD(v3) = MEMORY[0x1028A8], (unsigned int)*((unsigned __int16 *)v8 + 16) >= MEMORY[0x1028A8]) )
      {
        LODWORD(v3) = ((int (__fastcall *)(_DWORD))v8[1])(*((unsigned __int16 *)v8 + 17));
        v10 = v3;
        if ( (unsigned int)v3 >= 0xFF )
          goto LABEL_27;
        if ( v8[3] )
        {
          sub_39C();
          sub_498();
          ((void (__fastcall *)(_DWORD))v8[3])(0);
        }
        v11 = ((int (__fastcall *)(int, int))v8[4])(1048644, v14);
        v10 = v11;
        if ( v11 == 4102 )
        {
          if ( !v4 || v5 != 4102 || v6 != MEMORY[0x10287C] )
          {
            sub_E68A(0x1006u, MEMORY[0x10287C], *(unsigned __int8 *)v8, *((unsigned __int16 *)v8 + 17));
            v5 = 4102;
            v6 = MEMORY[0x10287C];
          }
          v4 = 1;
        }
        else
        {
          sub_E68A((unsigned __int16)v11, MEMORY[0x10287C], *(unsigned __int8 *)v8, *((unsigned __int16 *)v8 + 17));
        }
        if ( !v10 )
        {
          if ( !MEMORY[0x106AD0] )
            MEMORY[0x106AD0] = v8;
          *a1 = v8;
          *a2 = v9;
          trace_end(v13, *(unsigned __int8 *)v8, *((unsigned __int16 *)v8 + 17), 0);
          trace_begin(v13, 1);
          goto LABEL_36;
        }
        if ( v8[3] )
        {
          sub_39C();
          sub_498();
          ((void (__fastcall *)(int))v8[3])(1);
        }
        LODWORD(v3) = ((int (*)(void))v8[2])();
        if ( (unsigned int)v3 >= 0xFF )
LABEL_27:
          sub_E68A((unsigned __int16)v3, MEMORY[0x10287C], *(unsigned __int8 *)v8, *((unsigned __int16 *)v8 + 17));
      }
      else
      {
        v10 = 4138;
      }
    }
    while ( v10 == 4102 );
    trace_end(v13, *(unsigned __int8 *)v8, *((unsigned __int16 *)v8 + 17), 0);
    trace_begin(v13, 1);
    if ( v15 )
      goto LABEL_36;
  }
  v10 = 4101;
LABEL_36:
  trace_begin(0xAu, 1);
  return v10;
}


// ==================== sub_10276 @0x10276 size=362 ====================
void sub_10276()
{
  __int64 v0; // r0
  __int64 v1; // r0
  unsigned int v2; // r4
  __int64 v3; // r0
  unsigned int v4; // r5
  int v5; // r7
  unsigned int v6; // r6
  unsigned int v7; // r0
  int v8; // r5
  int v9; // r6
  int *v10; // r2
  int v11; // [sp+4h] [bp-10h] BYREF
  int v12; // [sp+8h] [bp-Ch] BYREF
  int *v13; // [sp+Ch] [bp-8h] BYREF
  unsigned int i; // [sp+10h] [bp-4h] BYREF

  LODWORD(v0) = 0;
  v11 = 0;
  while ( 1 )
  {
    v13 = 0;
    v12 = 0;
    usb_config_apply(v0);
    LODWORD(v1) = 2;
    usb_status_reset(v1);
    LODWORD(v0) = sub_100D4(&v13, &v12);
    v2 = v0;
    if ( (unsigned int)v0 < 0xFF )
    {
      v2 = sub_FFCC();
      if ( v2 >= 0xFF )
        goto LABEL_24;
      v11 = 0;
      for ( i = 0; i < 8; ++i )
      {
        LODWORD(v3) = 2;
        usb_status_reset(v3);
        v4 = 20 * i + 1050696;
        v5 = *(_DWORD *)(20 * i + 0x100850);
        HIDWORD(v3) = *(unsigned __int8 *)(20 * i + 0x100855);
        if ( *(_BYTE *)(20 * i + 0x100855) )
        {
          v6 = sub_FEAE(i, 20 * i + 1050696, (int)v13, v12);
          sub_FFB8(*(unsigned __int16 *)(v5 + 6), &v11);
          if ( v6 >= 0xFF )
          {
            usb_write_debug_event(
              *(unsigned __int16 *)(v4 + 14),
              *(unsigned __int16 *)(v4 + 16),
              (unsigned __int8)i,
              *(unsigned __int16 *)(v5 + 6),
              76);
            if ( v6 == 4102 )
            {
              v2 = 4102;
              goto LABEL_24;
            }
            if ( v6 != 4131 )
              v2 = 4114;
          }
        }
      }
      v7 = sub_FCF0(&i);
      if ( v7 != 244 )
      {
        if ( v7 >= 0xFF )
          usb_write_debug_event((unsigned __int16)v7, 0, (unsigned __int8)i, *(unsigned __int16 *)(v5 + 6), 76);
        goto LABEL_15;
      }
      if ( i >= 8 )
        goto LABEL_30;
      v8 = 20 * i + 1050696;
      v9 = *(_DWORD *)(20 * i + 0x100850);
      v10 = sub_FCCA(0);
      if ( v10 )
      {
        if ( sub_FEAE(i, v8, (int)v10, v12) >= 0xFF )
        {
          usb_write_debug_event(
            *(unsigned __int16 *)(v8 + 14),
            *(unsigned __int16 *)(v8 + 16),
            (unsigned __int8)i,
            *(unsigned __int16 *)(v9 + 6),
            76);
          v2 = 4114;
        }
      }
      else
      {
        v2 = 4143;
      }
LABEL_15:
      if ( !(v11 | v2) )
        v2 = 4120;
LABEL_24:
      if ( v13[3] )
      {
        sub_39C();
        sub_498();
        ((void (__fastcall *)(int))v13[3])(1);
      }
      LODWORD(v0) = ((int (*)(void))v13[2])();
      if ( (unsigned int)v0 >= 0xFF )
        LODWORD(v0) = sub_E68A(
                        (unsigned __int16)v0,
                        MEMORY[0x10287C],
                        *(unsigned __int8 *)v13,
                        *((unsigned __int16 *)v13 + 17));
    }
    if ( v2 != 4102 )
    {
      LODWORD(v0) = 2;
      usb_status_reset(v0);
LABEL_30:
      JUMPOUT(0x10272);
    }
  }
}


// ==================== sub_103E0 @0x103E0 size=62 ====================
int __fastcall sub_103E0(_DWORD *a1)
{
  int v2; // r4
  char *v4; // r0

  v2 = 0;
  if ( sub_6128() )
  {
    if ( MEMORY[0x102874] == 2 && !efuse_get_bit17() )
    {
      v4 = get_brom_key_table_entry();
      if ( !auth_compare_with_key_table(a1, v4) )
        return 28783;
    }
    else
    {
      return auth_check_key_hash((int)a1, 1);
    }
  }
  return v2;
}


// ==================== sub_1041E @0x1041E size=52 ====================
unsigned int __fastcall sub_1041E(int a1)
{
  unsigned int result; // r0

  if ( !a1 )
    return 32864;
  if ( (unsigned __int16)*(_DWORD *)(a1 + 8) != 840 )
    return 32865;
  result = auth_check_cert_size_range(5, (unsigned __int16 *)(a1 + 16));
  if ( result < 0xFF )
    return sub_103E0((_DWORD *)(a1 + 20));
  return result;
}


// ==================== sub_10452 @0x10452 size=66 ====================
int __fastcall sub_10452(int a1, int a2)
{
  unsigned int v3; // r4
  int v4; // r6

  if ( !a2 )
    return 32800;
  if ( (unsigned __int16)*(_DWORD *)(a2 + 8) != 316 )
    return 32801;
  v4 = a2 + 16;
  v3 = auth_check_cert_size_range(2, (unsigned __int16 *)(a2 + 16));
  if ( v3 < 0xFF && mem_cmp(a1 + 1064, v4, 4) )
    return 32805;
  return v3;
}


// ==================== sub_104AC @0x104AC size=54 ====================
unsigned int __fastcall sub_104AC(int a1)
{
  unsigned int result; // r0

  if ( !a1 )
    return 32784;
  if ( (unsigned __int16)*(_DWORD *)(a1 + 8) != 1324 )
    return 32785;
  result = auth_check_cert_size_range(1, (unsigned __int16 *)(a1 + 1064));
  if ( result < 0xFF )
    return sub_103E0((_DWORD *)(a1 + 16));
  return result;
}


// ==================== sub_104E2 @0x104E2 size=134 ====================
unsigned int __fastcall sub_104E2(int a1, int *a2, int *a3, int *a4)
{
  unsigned int result; // r0
  unsigned int i; // r0
  _DWORD *v10; // r3
  int v11; // r4
  _DWORD v12[2]; // [sp+4h] [bp-38h] BYREF
  __int16 v13; // [sp+Ch] [bp-30h]
  int v14; // [sp+10h] [bp-2Ch]

  result = auth_parse_cert_blocks(a1, v12);
  if ( result < 0xFF )
  {
    if ( *(_DWORD *)v12[0] == 2 )
    {
      for ( i = 0; v12[1] > i; ++i )
      {
        v10 = &v12[3 * i];
        v11 = *((unsigned __int16 *)v10 + 4);
        if ( v11 == 1 )
        {
          *a2 = v10[3] + a1;
        }
        else if ( v11 == 2 )
        {
          *a3 = v10[3] + a1;
        }
      }
      result = sub_104AC(*a2);
      if ( result < 0xFF )
        return sub_10452(*a2, *a3);
    }
    else if ( *(_DWORD *)v12[0] == 6 )
    {
      if ( v13 == 5 )
        *a4 = v14 + a1;
      return sub_1041E(*a4);
    }
    else
    {
      return 24629;
    }
  }
  return result;
}


// ==================== sub_10568 @0x10568 size=72 ====================
void __fastcall sub_10568(int a1, int a2, _DWORD *a3)
{
  int v5; // r6

  *a3 = 0;
  if ( sub_6128() )
  {
    if ( MEMORY[0x102874] == 2 && !efuse_get_bit17() )
    {
      *a3 = get_brom_key_table_entry();
    }
    else if ( a2 )
    {
      v5 = a2 + 8;
      if ( (unsigned int)auth_check_key_hash(v5, 1) < 0xFF )
        *a3 = v5;
    }
  }
  JUMPOUT(0x10492);
}


// ==================== sub_105B0 @0x105B0 size=78 ====================
int __fastcall sub_105B0(int a1)
{
  int v1; // r4
  int v3; // [sp+0h] [bp-4h] BYREF

  v3 = 0;
  v1 = 0;
  if ( auth_find_block_by_type(a1, 19, &v3) < 0xFF )
  {
    if ( *(_DWORD *)(v3 + 8) << 31 && mem_cmp(1059704, v3 + 12, 16) )
    {
      return 28789;
    }
    else if ( (*(_DWORD *)(v3 + 8) & 2) != 0 && mem_cmp(1059720, v3 + 12, 32) )
    {
      return 28790;
    }
  }
  return v1;
}


// ==================== sub_105FE @0x105FE size=108 ====================
int __fastcall sub_105FE(int a1)
{
  int v1; // r4
  BOOL v2; // r5
  int v3; // r0
  int v5; // [sp+0h] [bp-4h] BYREF

  v5 = 0;
  v1 = 0;
  v2 = 0;
  if ( MEMORY[0x102874] == 2 )
  {
    if ( auth_find_block_by_type(a1, 17, &v5) < 0xFF )
    {
      v3 = *(_DWORD *)(v5 + 8);
      if ( v3 << 31 )
        v2 = (~MEMORY[0x10214050] & 0x42000002) == 0;
      if ( (v3 & 2) != 0 && (~MEMORY[0x100008] & 0x42000002) == 0 )
        v2 = 1;
      if ( v2 )
      {
        if ( mem_cmp(1059720, v5 + 16, 32) )
          return 28787;
      }
      else
      {
        return 28786;
      }
    }
    else
    {
      return 32832;
    }
  }
  return v1;
}


// ==================== sub_1066A @0x1066A size=52 ====================
void __fastcall sub_1066A(int a1)
{
  if ( a1 != 3 )
    sub_6128();
  JUMPOUT(0x10492);
}


// ==================== sub_1069E @0x1069E size=198 ====================
void __fastcall sub_1069E(int *a1, int *a2, _DWORD *a3, _DWORD *a4, _DWORD *a5, _DWORD *a6)
{
  int v10; // r11
  int v11; // r5
  int v12; // r7

  *a2 = 0;
  *a3 = 0;
  *a4 = 0;
  *a5 = 0;
  *a6 = 0;
  v10 = *a1;
  if ( auth_find_block_by_type(*a1, 0, a2) < 0xFF && auth_check_block_header(*a2) < 0xFF )
  {
    v11 = a1[2];
    if ( *(unsigned __int16 *)(v11 + 6) == *(unsigned __int16 *)(*a2 + 24) )
    {
      auth_find_block_by_type(v10, 2, a3);
      if ( auth_find_block_by_type(v10, 7, a4) < 0xFF || *(_WORD *)(v11 + 6) != 1 )
      {
        v12 = sub_6128();
        if ( auth_find_block_by_type(v10, 8, a5) < 0xFF || !v12 || *(_WORD *)(v11 + 6) != 1 )
          auth_find_block_by_type(v10, 3, a6);
      }
    }
  }
  JUMPOUT(0xFFB4);
}


// ==================== sub_10764 @0x10764 size=364 ====================
unsigned int __fastcall sub_10764(int a1, int a2)
{
  int v4; // r5
  int v5; // r7
  unsigned int v6; // r0
  unsigned int v7; // r4
  unsigned int v8; // r0
  unsigned int v9; // r0
  int v10; // r0
  unsigned int v11; // r9
  int v13; // [sp+Ch] [bp-30h] BYREF
  int v14; // [sp+10h] [bp-2Ch] BYREF
  int v15; // [sp+14h] [bp-28h] BYREF
  int v16; // [sp+18h] [bp-24h] BYREF
  int v17; // [sp+1Ch] [bp-20h] BYREF
  int v18; // [sp+20h] [bp-1Ch] BYREF
  int v19; // [sp+24h] [bp-18h] BYREF
  int v20; // [sp+28h] [bp-14h] BYREF
  _DWORD v21[3]; // [sp+2Ch] [bp-10h] BYREF
  _DWORD *v22; // [sp+38h] [bp-4h] BYREF

  v15 = 0;
  v14 = 0;
  v13 = 0;
  v4 = *(_DWORD *)(a2 + 8);
  v5 = sub_6128();
  sub_1069E((int *)a2, &v20, &v19, &v18, &v17, &v16);
  v7 = v6;
  if ( v6 < 0xFF )
  {
    v7 = sub_7ABC(a1, v20, v19);
    if ( v7 < 0xFF )
    {
      auth_init_descriptor((int)v21, *(_DWORD *)(v20 + 28), v5 != 0);
      sub_1066A(*(unsigned __int16 *)(v4 + 6));
      v7 = v8;
      if ( v8 < 0xFF )
      {
        if ( !sub_857E() || (v7 = sub_105FE(*(_DWORD *)a2), v7 < 0xFF) )
        {
          v7 = sub_105B0(*(_DWORD *)a2);
          if ( v7 < 0xFF )
          {
            if ( *(_BYTE *)(v20 + 27) == 5 )
            {
              v7 = sub_104E2(*(_DWORD *)a2, &v15, &v14, &v13);
              if ( v7 >= 0xFF )
                goto LABEL_22;
            }
            else
            {
              sub_10568(*(unsigned __int16 *)(v4 + 6), v16, &v22);
              v7 = v9;
              if ( v9 >= 0xFF )
                goto LABEL_22;
              if ( (*(_DWORD *)(v20 + 52) & 4) != 0 && auth_compare_with_key_table((_DWORD *)(v16 + 8), v22) )
                v22 = (_DWORD *)(v16 + 8);
            }
            v10 = *(unsigned __int16 *)(v4 + 6);
            if ( v10 == 1 || v10 == 3 || v5 )
              sub_10DB0();
            v11 = (unsigned __int8)(2 * a1 + 22);
            trace_begin(v11, 0);
            v7 = auth_dispatch_by_block_type((int *)0x105748, 1070936, v21, 0);
            trace_begin(v11, 1);
            trace_end(v11, v5, *(_DWORD *)(v20 + 32), *(_DWORD *)(v20 + 28));
            if ( v7 < 0xFF )
            {
              if ( *(_WORD *)(v4 + 6) == 1 && !*(_DWORD *)(v20 + 48) )
                v7 = 4122;
            }
            else
            {
              MEMORY[0x10287C] = v7;
              v7 = 28711;
            }
          }
        }
      }
    }
  }
LABEL_22:
  if ( *(_WORD *)(v4 + 6) == 1 )
  {
    sub_10C20(v20, v19, v18, v17, v16);
    sub_10C6A(v15, v14, v13);
  }
  *(_BYTE *)(a2 + 13) = 4;
  *(_WORD *)(a2 + 14) = v7;
  if ( !*(_WORD *)(a2 + 16) )
    *(_WORD *)(a2 + 16) = MEMORY[0x10287C];
  return v7;
}


// ==================== sub_108D0 @0x108D0 size=8 ====================
int sub_108D0()
{
  return MEMORY[0x102814]();
}


// ==================== sub_108D8 @0x108D8 size=522 ====================
int sub_108D8()
{
  int v0; // r5
  __int64 v1; // r0
  unsigned int v2; // r4
  __int64 v3; // r0
  __int64 v4; // r0
  unsigned __int16 v5; // r0
  __int64 v6; // r0
  unsigned __int16 v7; // r0
  __int64 v8; // r0
  unsigned int i; // r6
  int v10; // r8
  unsigned int v11; // r7
  unsigned __int64 v12; // r0
  unsigned __int16 v13; // r0
  __int64 v14; // r0
  __int64 v15; // r0
  int v17; // [sp+4h] [bp-4h] BYREF

  v17 = 0;
  v0 = sub_7568();
  LODWORD(v1) = 2;
  usb_status_reset(v1);
  sub_108D0();
  if ( sub_7644() )
  {
    sub_10DB0();
    v2 = sub_782C(1056080, 1);
    usb_write_debug_status((unsigned __int16)v2, MEMORY[0x10287C], 0xCu, 82);
  }
  else
  {
    v2 = sub_79C8();
  }
  if ( !v0 )
    v0 = v2;
  LODWORD(v3) = 2;
  usb_status_reset(v3);
  v4 = (unsigned int)efuse_get_secure_boot() | 0xF843E0A00000000LL;
  if ( (_DWORD)v4 )
  {
    if ( MEMORY[0x103B4C] == 996942908 && MEMORY[0x103B50] == 260324874 )
    {
      sub_10DB0();
      v5 = auth_verify_file(1051136, 1);
      usb_write_debug_status(v5, MEMORY[0x10287C], 0xCu, 83);
    }
    else
    {
      LODWORD(v6) = sub_7A48();
      if ( !v0 )
        v0 = v6;
    }
    LODWORD(v6) = 2;
    v4 = usb_status_reset(v6);
  }
  else if ( MEMORY[0x103B4C] == 996942908 && MEMORY[0x103B50] == 260324874 )
  {
    sub_10DB0();
    v7 = auth_verify_file(1051136, 1);
    usb_write_debug_status(v7, MEMORY[0x10287C], 0xCu, 83);
    LODWORD(v8) = 2;
    v4 = usb_status_reset(v8);
  }
  v17 = 0;
  for ( i = 0; i < 8; ++i )
  {
    LODWORD(v4) = 2;
    v4 = usb_status_reset(v4);
    v10 = *(_DWORD *)(20 * i + 0x100850);
    LODWORD(v4) = *(unsigned __int8 *)(20 * i + 0x100855);
    if ( (_DWORD)v4 == 4 )
    {
      v11 = *(unsigned __int16 *)(20 * i + 0x100856);
    }
    else
    {
      if ( (unsigned int)v4 < 3 || *(unsigned __int16 *)(20 * i + 0x100856) >= 0xFFu )
        continue;
      v11 = sub_10764(i, 20 * i + 1050696);
    }
    usb_write_debug_event(
      *(unsigned __int16 *)(20 * i + 0x100856),
      *(unsigned __int16 *)(20 * i + 0x100858),
      (unsigned __int8)i,
      *(unsigned __int16 *)(v10 + 6),
      86);
    sub_FFB8(*(unsigned __int16 *)(v10 + 6), &v17);
    if ( v11 >= 0xFF && !v0 )
      v0 = 4119;
  }
  if ( !v0 )
  {
    if ( v17 )
    {
      if ( !MEMORY[0x106B64] )
        v0 = 4103;
    }
    else
    {
      v0 = 4121;
    }
  }
  v12 = MEMORY[0x103B54] | 0x51E8582500000000LL;
  if ( MEMORY[0x103B54] == 1374181413 )
  {
    v12 = MEMORY[0x103B58] | 0x97588CC000000000LL;
    if ( MEMORY[0x103B58] == -1755804480 )
    {
      sub_6FFA(MEMORY[0x103B5C]);
      usb_write_debug_status(v13, MEMORY[0x10287C], 0xDu, 77);
      LODWORD(v14) = 2;
      v12 = usb_status_reset(v14);
    }
  }
  sub_10DDA(v12, HIDWORD(v12));
  brom_get_descriptor(8);
  sub_8158();
  if ( sub_84EA() || sub_8200() && !sub_7F82() )
  {
    MEMORY[0x1008E8] |= 8u;
    sub_7F40();
  }
  LODWORD(v15) = 2;
  usb_status_reset(v15);
  return v0;
}


// ==================== sub_10AE2 @0x10AE2 size=8 ====================
int sub_10AE2()
{
  MEMORY[0x1028A4] = -1;
  return 255;
}


// ==================== sub_10AEA @0x10AEA size=86 ====================
BOOL __fastcall sub_10AEA(int a1, int a2, int a3, int a4)
{
  unsigned int v5; // r0
  int v6; // [sp+0h] [bp-4h] BYREF

  v6 = a4;
  if ( sub_10FA8(a1) )
    return 0;
  if ( MEMORY[0x1028AC] <= MEMORY[0x1028A8] )
  {
    usb_report_error(0x102Au, MEMORY[0x1028A8]);
    return 0;
  }
  else
  {
    v5 = ++MEMORY[0x1028A8];
    if ( MEMORY[0x106AD0] && *(unsigned __int16 *)(MEMORY[0x106AD0] + 32) < v5 )
      return 0;
    else
      return (unsigned int)sub_10E16(v5) >= 0xFF || (unsigned int)sub_10CB2(&v6) >= 0xFF;
  }
}


// ==================== usb_monitor_task (sub_10B40) @0x10B40 size=108 ====================
void usb_monitor_task()
{
  unsigned int v0; // r0
  unsigned int v1; // r5
  unsigned int v2; // r0
  int v3; // r1
  int v4; // r2
  int v5; // r3
  unsigned int v6; // r4

  sub_10AE2();
  while ( 1 )
  {
    sub_10276();
    v1 = v0;
    sub_384();
    v2 = sub_108D8();
    v6 = v2;
    if ( v1 < 0xFF && v2 < 0xFF )
      goto LABEL_12;
    if ( !sub_10AEA(v2, v3, v4, v5) )
      break;
    if ( v1 < 0xFF )
    {
      if ( v6 >= 0xFF )
        usb_report_error((unsigned __int16)v6, MEMORY[0x10287C]);
    }
    else
    {
      usb_report_error((unsigned __int16)v1, MEMORY[0x10287C]);
    }
  }
  if ( v1 < 0xFF && v6 < 0xFF )
LABEL_12:
    MEMORY[0x1008E8] |= 1u;
  JUMPOUT(0x10492);
}


// ==================== nullsub_18 @0x10BAC size=2 ====================
void nullsub_18()
{
  ;
}


// ==================== brom_get_descriptor (sub_10BD8) @0x10BD8 size=72 ====================
int __fastcall brom_get_descriptor(int a1)
{
  int result; // r0

  if ( !MEMORY[0x106B64]
    || *(unsigned __int8 *)(MEMORY[0x106B64] + 13) < 4u
    || *(unsigned __int16 *)(MEMORY[0x106B64] + 14) >= 0xFFu )
  {
    return 0;
  }
  switch ( a1 )
  {
    case 0:
      result = MEMORY[0x106B68];
      break;
    case 2:
      result = MEMORY[0x106B6C];
      break;
    case 3:
      result = MEMORY[0x106B78];
      break;
    case 7:
      result = MEMORY[0x106B70];
      break;
    case 8:
      result = MEMORY[0x106B74];
      break;
    default:
      return 0;
  }
  return result;
}


// ==================== sub_10C20 @0x10C20 size=20 ====================
int __fastcall sub_10C20(int result, int a2, int a3, int a4, int a5)
{
  MEMORY[0x106B68] = result;
  MEMORY[0x106B6C] = a2;
  MEMORY[0x106B70] = a3;
  MEMORY[0x106B74] = a4;
  MEMORY[0x106B78] = a5;
  return result;
}


// ==================== sub_10C34 @0x10C34 size=54 ====================
int __fastcall sub_10C34(int a1)
{
  if ( !MEMORY[0x106B64]
    || *(unsigned __int8 *)(MEMORY[0x106B64] + 13) < 4u
    || *(unsigned __int16 *)(MEMORY[0x106B64] + 14) >= 0xFFu )
  {
    return 0;
  }
  if ( a1 == 1 )
    return MEMORY[0x106B7C];
  if ( a1 == 2 )
    return MEMORY[0x106B80];
  if ( a1 != 5 )
    return 0;
  return MEMORY[0x106B84];
}


// ==================== sub_10C6A @0x10C6A size=12 ====================
int __fastcall sub_10C6A(int result, int a2, int a3)
{
  MEMORY[0x106B7C] = result;
  MEMORY[0x106B80] = a2;
  MEMORY[0x106B84] = a3;
  return result;
}


// ==================== sub_10C76 @0x10C76 size=42 ====================
int sub_10C76()
{
  if ( MEMORY[0x106B7C] )
    return *(unsigned __int16 *)(MEMORY[0x106B7C] + 1066) | (*(unsigned __int16 *)(MEMORY[0x106B7C] + 1064) << 16);
  if ( MEMORY[0x106B84] )
    return *(unsigned __int16 *)(MEMORY[0x106B84] + 18) | (*(unsigned __int16 *)(MEMORY[0x106B84] + 16) << 16);
  return 0;
}


// ==================== sub_10CA0 @0x10CA0 size=18 ====================
int sub_10CA0()
{
  if ( MEMORY[0x106B64] )
    return *(unsigned __int16 *)(MEMORY[0x106B64] + 14);
  else
    return 4103;
}


// ==================== sub_10CB2 @0x10CB2 size=34 ====================
int __fastcall sub_10CB2(_DWORD *a1)
{
  int v2; // r5
  int v3; // r0

  v2 = 0;
  v3 = brom_get_descriptor(0);
  if ( !v3 )
    return sub_10CA0();
  *a1 = *(_DWORD *)(v3 + 48) + *(_DWORD *)(v3 + 28);
  return v2;
}


// ==================== sub_10CD4 @0x10CD4 size=110 ====================
int sub_10CD4()
{
  unsigned int i; // r4
  int v1; // r1

  if ( !MEMORY[0x1028B0] )
  {
    mem_set_bytes(1075936, 0, 132);
    for ( i = 0; i < 8; ++i )
    {
      if ( *(unsigned __int8 *)(20 * i + 0x100855) >= 3u )
      {
        v1 = *(unsigned __int16 *)(*(_DWORD *)(20 * i + 0x100850) + 6);
        if ( v1 == 9 || v1 == 10 || v1 == 4 )
        {
          sub_FE64((int *)(20 * i + 1050696));
        }
        else
        {
          mem_set_bytes(*(_DWORD *)(20 * i + 0x100848), 66, *(_DWORD *)(20 * i + 0x10084C));
          *(_WORD *)(20 * i + 0x100856) = 4105;
        }
      }
    }
    sub_10C20(0, 0, 0, 0, 0);
    MEMORY[0x1028B0] = 1;
  }
  return 4118;
}


// ==================== sub_10D42 @0x10D42 size=10 ====================
char __fastcall sub_10D42(char result, int a2, int a3)
{
  MEMORY[0x106AD4] = result;
  MEMORY[0x106AD8] = a2;
  MEMORY[0x106ADC] = a3;
  return result;
}


// ==================== sub_10D4C @0x10D4C size=60 ====================
int sub_10D4C()
{
  unsigned int i; // r1
  int v1; // r2
  int result; // r0

  mem_set_bytes(1048640, 0, 2364);
  MEMORY[0x100040] = 5;
  for ( i = 0; i < 8; ++i )
  {
    v1 = 20 * i + 1048640;
    result = 20 * i + 1050696;
    *(_DWORD *)(v1 + 2064) = v1 + 540;
    *(_BYTE *)(v1 + 2068) = i;
    *(_BYTE *)(v1 + 2069) = 0;
    *(_WORD *)(v1 + 2070) = 255;
    *(_WORD *)(v1 + 2072) = 0;
  }
  return result;
}


// ==================== usb_config_apply (sub_10D88) @0x10D88 size=38 ====================
int __fastcall usb_config_apply(int a1, int a2, int a3, int a4)
{
  _DWORD v5[4]; // [sp+0h] [bp-10h] BYREF

  v5[0] = a1;
  v5[1] = a2;
  v5[2] = a3;
  v5[3] = a4;
  mem_copy_bytes(v5, 1075920, 16);
  mem_set_bytes(1075920, 0, 220);
  mem_copy_bytes(1075920, v5, 16);
  return sub_10D4C();
}


// ==================== nullsub_9 @0x10DAE size=2 ====================
void nullsub_9()
{
  ;
}


// ==================== sub_10DB0 @0x10DB0 size=42 ====================
unsigned int sub_10DB0()
{
  unsigned int result; // r0

  result = sub_8526();
  if ( result )
  {
    result = sub_738();
    if ( !result )
    {
      result = sub_714(1);
      if ( result >= 0xFF )
        return usb_report_error((unsigned __int16)result, 0);
    }
  }
  return result;
}


// ==================== sub_10DDA @0x10DDA size=30 ====================
int sub_10DDA()
{
  int result; // r0

  result = sub_8526();
  if ( result )
  {
    result = sub_738();
    if ( result )
      return sub_714(0);
  }
  return result;
}


// ==================== board_check_flag3 (sub_10DF8) @0x10DF8 size=30 ====================
int __fastcall board_check_flag3(int *a1)
{
  int v2; // r6
  int v3; // r4

  v2 = 0;
  v3 = 1050184;
  if ( !sub_FC64(1050184) )
    v3 = 0;
  if ( v3 )
    v2 = 1;
  if ( a1 )
    *a1 = v3;
  return v2;
}


// ==================== sub_10E16 @0x10E16 size=16 ====================
int sub_10E16()
{
  if ( MEMORY[0x106B8C] )
    return *(unsigned __int16 *)(MEMORY[0x106B8C] + 14);
  else
    return 0;
}


// ==================== sub_10E26 @0x10E26 size=18 ====================
int sub_10E26()
{
  if ( MEMORY[0x106BA8] )
    return *(_DWORD *)(*(_DWORD *)(MEMORY[0x106BA8] + 8) + 16);
  else
    return 0;
}


// ==================== sub_10E48 @0x10E48 size=12 ====================
int sub_10E48()
{
  MEMORY[0x11C10000] |= 4u;
  return 297861120;
}


// ==================== sub_10E54 @0x10E54 size=10 ====================
int sub_10E54()
{
  return MEMORY[0x11C10000] & 1;
}


// ==================== sub_10E5E @0x10E5E size=10 ====================
int sub_10E5E()
{
  return MEMORY[0x11C10020] & 1;
}


// ==================== sub_10E68 @0x10E68 size=10 ====================
int sub_10E68()
{
  return (MEMORY[0x11C10120] >> 8) & 1;
}


// ==================== sub_10E72 @0x10E72 size=10 ====================
int sub_10E72()
{
  return (MEMORY[0x11C10120] >> 9) & 1;
}


// ==================== sub_10E7C @0x10E7C size=10 ====================
int sub_10E7C()
{
  return (MEMORY[0x11C10020] >> 21) & 1;
}


// ==================== sub_10E86 @0x10E86 size=10 ====================
int sub_10E86()
{
  return (MEMORY[0x11C10020] >> 12) & 1;
}


// ==================== sub_10E90 @0x10E90 size=10 ====================
int sub_10E90()
{
  return (MEMORY[0x11C10020] >> 14) & 1;
}


// ==================== sub_10E9A @0x10E9A size=10 ====================
int sub_10E9A()
{
  return (MEMORY[0x11C10020] >> 15) & 1;
}


// ==================== sub_10EA4 @0x10EA4 size=36 ====================
_DWORD *__fastcall sub_10EA4(_DWORD *result)
{
  if ( result )
  {
    *result = MEMORY[0x11C10260];
    result[1] = MEMORY[0x11C10264];
    result[2] = MEMORY[0x11C10268];
    result[3] = MEMORY[0x11C1026C];
    result[4] = MEMORY[0x11C10270];
    result[5] = MEMORY[0x11C10274];
    result[6] = MEMORY[0x11C10278];
  }
  return result;
}


// ==================== sub_10EC8 @0x10EC8 size=10 ====================
int sub_10EC8()
{
  return HIWORD(MEMORY[0x11C10020]) & 3;
}


// ==================== sub_10ED2 @0x10ED2 size=10 ====================
int sub_10ED2()
{
  return (MEMORY[0x11C10020] >> 18) & 1;
}


// ==================== sub_10EDC @0x10EDC size=10 ====================
int sub_10EDC()
{
  return (MEMORY[0x11C10020] >> 19) & 1;
}


// ==================== sub_10EE6 @0x10EE6 size=10 ====================
int sub_10EE6()
{
  return (MEMORY[0x11C10020] >> 13) & 1;
}


// ==================== sub_10EF0 @0x10EF0 size=10 ====================
int sub_10EF0()
{
  return (MEMORY[0x11C10120] >> 10) & 1;
}


// ==================== efuse_get_flag_11 (sub_10EFA) @0x10EFA size=10 ====================
int efuse_get_flag_11()
{
  return (MEMORY[0x11C10120] >> 11) & 1;
}


// ==================== sub_10F04 @0x10F04 size=10 ====================
int sub_10F04()
{
  return (MEMORY[0x11C10120] >> 4) & 1;
}


// ==================== sub_10F0E @0x10F0E size=10 ====================
int sub_10F0E()
{
  return (MEMORY[0x11C10120] >> 5) & 1;
}


// ==================== sub_10F18 @0x10F18 size=10 ====================
int sub_10F18()
{
  return (MEMORY[0x11C10020] >> 2) & 1;
}


// ==================== sub_10F22 @0x10F22 size=10 ====================
int sub_10F22()
{
  return (MEMORY[0x11C10020] >> 3) & 1;
}


// ==================== sub_10F2C @0x10F2C size=10 ====================
int sub_10F2C()
{
  return (MEMORY[0x11C10020] >> 8) & 1;
}


// ==================== sub_10F36 @0x10F36 size=10 ====================
int sub_10F36()
{
  return (MEMORY[0x11C10020] >> 10) & 1;
}


// ==================== sub_10F40 @0x10F40 size=8 ====================
int sub_10F40()
{
  return MEMORY[0x11C10030];
}


// ==================== sub_10F48 @0x10F48 size=8 ====================
int sub_10F48()
{
  return MEMORY[0x11C10038];
}


// ==================== sub_10F50 @0x10F50 size=14 ====================
int sub_10F50()
{
  return ((int)(MEMORY[0x11C10120] << 30) >> 31) + 1;
}


// ==================== usb_is_suspended (sub_10F5E) @0x10F5E size=10 ====================
int usb_is_suspended()
{
  return (MEMORY[0x11C10020] >> 20) & 1;
}


// ==================== sub_10F68 @0x10F68 size=24 ====================
int __fastcall sub_10F68(int result)
{
  unsigned int i; // r1

  for ( i = 0; i < 2; ++i )
    *(_DWORD *)(result + 4 * i) = *(_DWORD *)(4 * i + 0x11C10140);
  return result;
}


// ==================== sub_10F80 @0x10F80 size=10 ====================
int sub_10F80()
{
  return (MEMORY[0x11C10120] >> 3) & 1;
}


// ==================== sub_10F8A @0x10F8A size=10 ====================
int sub_10F8A()
{
  return (MEMORY[0x11C10120] >> 6) & 1;
}


// ==================== sub_10F94 @0x10F94 size=10 ====================
int sub_10F94()
{
  return (MEMORY[0x11C10020] >> 7) & 1;
}


// ==================== sub_10F9E @0x10F9E size=10 ====================
int sub_10F9E()
{
  return (MEMORY[0x11C10120] >> 7) & 1;
}


// ==================== sub_10FA8 @0x10FA8 size=10 ====================
int sub_10FA8()
{
  return (MEMORY[0x11C10020] >> 11) & 1;
}


// ==================== sub_10FB2 @0x10FB2 size=10 ====================
int sub_10FB2()
{
  return (MEMORY[0x11C10020] >> 22) & 1;
}


// ==================== board_get_boot_source (sub_10FC8) @0x10FC8 size=46 ====================
int __fastcall board_get_boot_source(int *a1)
{
  int result; // r0
  int v3; // r1

  result = 255;
  v3 = MEMORY[0x1000A000] & 0xF;
  *a1 = v3;
  switch ( v3 )
  {
    case 1:
      return 1;
    case 2:
      return 2;
    case 3:
      return 3;
    case 7:
      return 4;
  }
  return result;
}


// ==================== sub_10FF6 @0x10FF6 size=86 ====================
int __fastcall sub_10FF6(int a1)
{
  int result; // r0

  while ( (MEMORY[0x1000A008] & 0x8000) == 0 )
    ;
  if ( a1 )
  {
    MEMORY[0x1000A110] = a1;
    MEMORY[0x1000A114] = __ROR4__(a1, 8);
    MEMORY[0x1000A118] = __ROR4__(a1, 16);
    MEMORY[0x1000A11C] = __ROR4__(a1, 24);
    MEMORY[0x1000A100] = 7;
  }
  else
  {
    MEMORY[0x1000A100] = 3;
  }
  MEMORY[0x1000A104] = 1;
  while ( (MEMORY[0x1000A104] & 0x8000) == 0 )
    ;
  result = MEMORY[0x1000A120];
  while ( (MEMORY[0x1000A008] & 0x8000) == 0 )
    ;
  MEMORY[0x1000A100] = 0;
  return result;
}


// ==================== sub_1104C @0x1104C size=40 ====================
int __fastcall sub_1104C(int a1)
{
  if ( a1 )
    MEMORY[0x1020F004] = a1;
  MEMORY[0x1020F00C] |= 0xC0000u;
  MEMORY[0x1020F000] |= 1u;
  while ( MEMORY[0x1020F000] >= 0 )
    ;
  MEMORY[0x1020F000] &= ~1u;
  return MEMORY[0x1020F008];
}


// ==================== sub_1107C @0x1107C size=46 ====================
int sub_1107C()
{
  MEMORY[0xC53C8D0] &= ~0x400u;
  MEMORY[0xC53C8D0] |= 0x100u;
  sub_11BB8(MEMORY[0xC53C8D0]);
  sub_117BC(3);
  MEMORY[0xC53C8D0] |= 0x200u;
  return sub_11DE4(MEMORY[0xC53C8D0]);
}


// ==================== sub_110AA @0x110AA size=2 ====================
// attributes: thunk
int __fastcall sub_110AA(int a1)
{
  return sub_1107C();
}


// ==================== sub_110B0 @0x110B0 size=8 ====================
int __fastcall sub_110B0(int result)
{
  MEMORY[0x100914] = result;
  return result;
}


// ==================== sub_110B8 @0x110B8 size=16 ====================
_UNKNOWN ***sub_110B8()
{
  MEMORY[0x10091C] = &off_13034;
  MEMORY[0x100920] = off_133D4;
  return off_133D4;
}


// ==================== auth_parse_cert_blocks (sub_110D4) @0x110D4 size=144 ====================
unsigned int __fastcall auth_parse_cert_blocks(int a1, _DWORD *a2)
{
  unsigned int v4; // r4
  unsigned int result; // r0
  int v6; // r2
  unsigned int v7; // r2
  unsigned int v8; // r3
  _DWORD *v9; // r6

  v4 = 0;
  if ( a1 << 30 )
    return 32780;
  result = auth_check_file_info(a1);
  if ( result < 0xFF )
  {
    if ( *(_BYTE *)(a1 + 27) == 5 )
    {
      v6 = *(_DWORD *)(a1 + 32) - *(_DWORD *)(a1 + 44);
      if ( v6 << 30 )
      {
        return 32848;
      }
      else
      {
        *a2 = a1 + v6;
        v7 = v6 + 4;
        result = 32782;
        while ( *(_DWORD *)(a1 + 32) > v7 )
        {
          if ( v7 << 30 )
            return 32849;
          v8 = a1 + v7;
          if ( *(_DWORD *)(a1 + v7) != -493751464 )
            return result;
          if ( v4 < 4 )
          {
            v9 = &a2[3 * v4];
            v9[3] = v7;
            *((_WORD *)v9 + 4) = HIWORD(*(_DWORD *)(v8 + 12)) & 0xF;
            v9[4] = (unsigned __int16)*(_DWORD *)(v8 + 8);
            ++v4;
            v7 += (unsigned __int16)*(_DWORD *)(v8 + 8);
          }
        }
        if ( v4 )
        {
          a2[1] = v4;
          return 0;
        }
      }
    }
    else
    {
      return 32781;
    }
  }
  return result;
}


// ==================== sub_11168 @0x11168 size=752 ====================
int __fastcall sub_11168(unsigned __int64 a1, unsigned int a2, int a3)
{
  unsigned __int64 v5; // r2
  bool v6; // zf
  bool v7; // nf
  unsigned int v8; // r12
  int v9; // lr
  unsigned int v10; // r12
  bool v11; // zf
  unsigned int v12; // r1
  unsigned int v13; // r6
  bool v14; // cc
  int v15; // r12
  char v16; // r6
  unsigned __int64 v17; // r0
  unsigned int v18; // r1
  unsigned int v19; // r12
  unsigned __int64 v20; // r0
  unsigned int v21; // r1
  unsigned int v22; // r12
  unsigned __int64 v23; // r0
  unsigned int v24; // r1
  __int64 v25; // r0
  __int64 v26; // r0
  unsigned __int64 v27; // r2
  char v28; // cf
  unsigned __int64 v29; // kr08_8
  unsigned int v30; // r6
  unsigned int v31; // r2
  int v32; // r0
  unsigned int v33; // r2
  bool v34; // cf
  __int64 v35; // r0
  __int64 v36; // r0
  unsigned int v37; // r1
  unsigned int v38; // r12
  __int64 v39; // r0
  __int64 v40; // r0
  unsigned int v41; // r1
  unsigned int v42; // r12
  int v43; // r0
  unsigned __int64 v44; // r2
  bool v45; // cf
  unsigned int v46; // r6
  unsigned __int64 v47; // r2
  bool v48; // cf
  __int64 v49; // r0
  unsigned int v50; // r12
  unsigned int v51; // r5
  unsigned int i; // r4

  v5 = a1;
  v6 = a3 == 0;
  v7 = a3 < 0;
  if ( a3 )
    v8 = a3;
  else
    v8 = a2;
  v9 = __clz(v8);
  v10 = v8 << (v9 + 1);
  if ( a3 )
  {
    v9 = 63 - v9;
    v6 = v9 == 0;
    v7 = v9 < 0;
  }
  if ( v6 )
  {
    v9 = 31 - v9;
    v7 = v9 < 0;
  }
  if ( v7 )
  {
    LODWORD(v49) = 0;
  }
  else
  {
    v11 = HIDWORD(a1) == 0;
    if ( HIDWORD(a1) )
      v12 = __clz(HIDWORD(a1));
    else
      v12 = __clz(a1);
    if ( HIDWORD(v5) )
    {
      v12 = 63 - v12;
      v11 = v12 == 0;
    }
    if ( v11 )
      v12 = 31 - v12;
    v13 = v12 - v9;
    if ( (int)(v12 - v9) < 0 )
    {
      LODWORD(v49) = 0;
    }
    else if ( (int)(4 - v13) < 0 )
    {
      if ( v9 - 32 <= 4 )
        v10 |= a2 >> (v9 - 32);
      v14 = (unsigned int)v9 > 0x1F;
      v15 = dword_11458[v10 >> 28];
      if ( (unsigned int)v9 > 0x1F )
        LOBYTE(v9) = v9 - 32;
      v16 = 32 - v9;
      if ( v14 )
      {
        LODWORD(v35) = 0;
        HIDWORD(v35) = v15 * a2;
        v36 = (unsigned int)v15 * (unsigned __int64)(unsigned int)a3 + v35;
        v37 = -((HIDWORD(v36) << v16) | ((unsigned int)v36 >> v9));
        if ( (_DWORD)v36 << (32 - v9) )
          --v37;
        v38 = v15 + (((unsigned int)v15 * (unsigned __int64)v37) >> 32);
        LODWORD(v39) = 0;
        HIDWORD(v39) = v38 * a2;
        v40 = v38 * (unsigned __int64)(unsigned int)a3 + v39;
        v41 = -((HIDWORD(v40) << (32 - v9)) | ((unsigned int)v40 >> v9));
        if ( (_DWORD)v40 << (32 - v9) )
          --v41;
        v42 = v38 + ((v38 * (unsigned __int64)v41) >> 32) - 1;
        v43 = 0;
        HIDWORD(v49) = v42 * v5;
        LODWORD(v49) = (unsigned int)((v42 * (unsigned __int64)HIDWORD(v5) + v49) >> 32) >> v9;
        v44 = v5 - __PAIR64__(a3, a2) * (unsigned int)v49;
        v45 = HIDWORD(v44) >= a3;
        if ( HIDWORD(v44) == a3 )
          v45 = (unsigned int)v44 >= a2;
        if ( v45 )
        {
          v46 = (unsigned int)((v42 * (unsigned __int64)HIDWORD(v44)
                              + ((v42 * (unsigned __int64)(unsigned int)v44) >> 32)) >> 32) >> v9;
          LODWORD(v49) = v49 + v46;
          v47 = v44 - __PAIR64__(a3, a2) * v46;
          v48 = HIDWORD(v47) >= a3;
          if ( HIDWORD(v47) == a3 )
            v48 = (unsigned int)v47 >= a2;
          if ( v48 )
            LODWORD(v49) = v49 + 1;
        }
      }
      else
      {
        v17 = (unsigned int)v15 * (unsigned __int64)a2;
        v18 = -((HIDWORD(v17) << v16) | ((unsigned int)v17 >> v9));
        if ( (_DWORD)v17 << v16 )
          --v18;
        v19 = v15 + (((unsigned int)v15 * (unsigned __int64)v18) >> 32);
        v20 = v19 * (unsigned __int64)a2;
        v21 = -((HIDWORD(v20) << v16) | ((unsigned int)v20 >> v9));
        if ( (_DWORD)v20 << v16 )
          --v21;
        v22 = v19 + ((v19 * (unsigned __int64)v21) >> 32);
        if ( HIDWORD(v5) )
        {
          v23 = v22 * (unsigned __int64)a2;
          v24 = -((HIDWORD(v23) << v16) | ((unsigned int)v23 >> v9));
          if ( (_DWORD)v23 << v16 )
            --v24;
          v22 += (v22 * (unsigned __int64)v24) >> 32;
        }
        LODWORD(v25) = 0;
        HIDWORD(v25) = v22 * v5;
        v26 = v22 * (unsigned __int64)HIDWORD(v5) + v25;
        LODWORD(v49) = ((unsigned int)v26 >> v9) | (HIDWORD(v26) << v16);
        HIDWORD(v49) = HIDWORD(v26) >> v9;
        v27 = v5 - v49 * a2;
        v28 = HIDWORD(v27) != 0;
        if ( !HIDWORD(v27) )
          v28 = (unsigned int)v27 >= a2;
        if ( v28 )
        {
          v29 = v22 * (unsigned __int64)HIDWORD(v27) + ((v22 * (unsigned __int64)(unsigned int)v27) >> 32);
          v30 = ((unsigned int)v29 >> v9) | (HIDWORD(v29) << (32 - v9));
          LODWORD(v49) = v49 + v30;
          v31 = v27 - v30 * a2;
          if ( v31 >= a2 )
          {
            v32 = v49 + 1;
            v33 = v31 - a2;
            v34 = v33 >= a2;
            if ( v33 >= a2 )
              v33 -= a2;
            LODWORD(v49) = v32 + v34 + (v33 >= a2);
          }
        }
      }
    }
    else
    {
      LODWORD(v49) = 0;
      v50 = a2 >> (32 - v13);
      v51 = a2 << v13;
      for ( i = (a3 << v13) | v50; ; i >>= 1 )
      {
        LODWORD(v49) = v49 + (v5 >= __PAIR64__(i, v51)) + (_DWORD)v49;
        if ( v5 >= __PAIR64__(i, v51) )
          v5 -= __PAIR64__(i, v51);
        v28 = v13-- != 0;
        if ( !v28 )
          break;
        v28 = i & 1;
        v51 = (v51 >> 1) | (v28 << 31);
      }
    }
  }
  return v49;
}


// ==================== sub_11498 @0x11498 size=42 ====================
unsigned int __fastcall sub_11498(unsigned int result)
{
  int v1; // r1

  MEMORY[0x102D78] = 1060120;
  MEMORY[0x102D7C] = 1059996;
  v1 = 55;
  while ( v1-- > 0 )
  {
    *(_DWORD *)(4 * v1 + 0x102C9C) = result + HIWORD(result);
    result = 69069 * result + 1725307361;
  }
  return result;
}


// ==================== sub_114C2 @0x114C2 size=4 ====================
unsigned int sub_114C2()
{
  return sub_11498(1u);
}


// ==================== mem_cmp (sub_114D4) @0x114D4 size=88 ====================
int __fastcall mem_cmp(unsigned int *a1, unsigned int *a2, unsigned int a3)
{
  unsigned int v3; // r4
  unsigned int v4; // r3
  int v6; // r3
  int v7; // t1
  int v8; // t1
  int v9; // r3
  int v10; // r3
  int v11; // t1
  int v12; // t1

  if ( !(((unsigned int)a1 | (unsigned int)a2) << 30) )
  {
    while ( a3 >= 4 )
    {
      v3 = *a1++;
      v4 = *a2++;
      a3 -= 4;
      if ( v3 != v4 )
      {
        if ( bswap32(v3) <= bswap32(v4) )
          return -1;
        else
          return 1;
      }
    }
  }
  if ( !a3 )
    return 0;
  if ( !(a3 << 31) )
    goto LABEL_11;
  ++a3;
  do
  {
    v11 = *(unsigned __int8 *)a1;
    a1 = (unsigned int *)((char *)a1 + 1);
    v10 = v11;
    v12 = *(unsigned __int8 *)a2;
    a2 = (unsigned int *)((char *)a2 + 1);
    v9 = v10 - v12;
    if ( v9 )
      break;
    a3 -= 2;
    if ( !a3 )
      break;
LABEL_11:
    v7 = *(unsigned __int8 *)a1;
    a1 = (unsigned int *)((char *)a1 + 1);
    v6 = v7;
    v8 = *(unsigned __int8 *)a2;
    a2 = (unsigned int *)((char *)a2 + 1);
    v9 = v6 - v8;
  }
  while ( !v9 );
  return v9;
}


// ==================== sub_1152C @0x1152C size=4 ====================
// attributes: thunk
int __fastcall sub_1152C(int a1, int a2, int a3)
{
  return mem_copy_bytes(a1, a2, a3);
}


// ==================== mem_copy_bytes (sub_11530) @0x11530 size=12 ====================
void __fastcall __spoils<R1,R2,R3,R12,LR> mem_copy_bytes(int a1, int a2, int a3)
{
  sub_1153C(a1, a2, a3);
}


// ==================== sub_1153C @0x1153C size=212 ====================
int __fastcall sub_1153C(int result, char *a2, unsigned int a3, unsigned int a4)
{
  unsigned int v4; // r12
  char v5; // r3
  char v6; // t1
  bool v7; // cf
  bool v8; // cc
  unsigned int v9; // r2
  char v10; // t1
  char v11; // t1
  char *v12; // r1
  unsigned int v13; // t1
  unsigned int v14; // r3
  unsigned int v15; // t1
  unsigned int v16; // r3
  unsigned int v17; // t1
  unsigned int v18; // r3
  unsigned int v19; // t1
  bool v20; // cf
  bool v21; // nf
  int v22; // r2
  char *v23; // r1
  char v24; // t1
  char v25; // t1
  _BYTE *v26; // r0

  if ( a3 > 3 )
  {
    v4 = result & 3;
    if ( (result & 3) != 0 )
    {
      v6 = *a2++;
      v5 = v6;
      v7 = v4 >= 2;
      v8 = (result & 3) == 3;
      v9 = a3 + v4;
      if ( (result & 3) != 3 )
      {
        v10 = *a2++;
        LOBYTE(v4) = v10;
      }
      *(_BYTE *)result++ = v5;
      if ( !v7 )
      {
        v11 = *a2++;
        v5 = v11;
      }
      if ( !v8 )
        *(_BYTE *)result++ = v4;
      a3 = v9 - 4;
      if ( !v7 )
        *(_BYTE *)result++ = v5;
    }
    a4 = (unsigned __int8)a2 & 3;
    if ( ((unsigned __int8)a2 & 3) == 0 )
      return sub_11610(result, a2, a3);
    v7 = a3 >= 4;
    a3 -= 4;
    if ( v7 )
    {
      v13 = *(_DWORD *)&a2[-a4];
      v12 = &a2[-a4];
      v4 = v13;
      if ( a4 == 2 )
      {
        do
        {
          v16 = HIWORD(v4);
          v17 = *((_DWORD *)v12 + 1);
          v12 += 4;
          v4 = v17;
          v7 = a3 >= 4;
          a3 -= 4;
          a4 = v16 | (v17 << 16);
          *(_DWORD *)result = a4;
          result += 4;
        }
        while ( v7 );
        a2 = v12 + 2;
      }
      else if ( a4 > 2 )
      {
        do
        {
          v18 = HIBYTE(v4);
          v19 = *((_DWORD *)v12 + 1);
          v12 += 4;
          v4 = v19;
          v7 = a3 >= 4;
          a3 -= 4;
          a4 = v18 | (v19 << 8);
          *(_DWORD *)result = a4;
          result += 4;
        }
        while ( v7 );
        a2 = v12 + 3;
      }
      else
      {
        do
        {
          v14 = v4 >> 8;
          v15 = *((_DWORD *)v12 + 1);
          v12 += 4;
          v4 = v15;
          v7 = a3 >= 4;
          a3 -= 4;
          a4 = v14 | (v15 << 24);
          *(_DWORD *)result = a4;
          result += 4;
        }
        while ( v7 );
        a2 = v12 + 1;
      }
    }
  }
  v20 = __CFSHL__(a3, 31);
  v22 = a3 << 31;
  v21 = v22 < 0;
  if ( v20 )
  {
    v24 = *a2;
    v23 = a2 + 1;
    LOBYTE(a4) = v24;
    v25 = *v23;
    a2 = v23 + 1;
    LOBYTE(v4) = v25;
  }
  if ( v22 < 0 )
    LOBYTE(v22) = *a2;
  if ( v20 )
  {
    *(_BYTE *)result = a4;
    v26 = (_BYTE *)(result + 1);
    *v26 = v4;
    result = (int)(v26 + 1);
  }
  if ( v21 )
    *(_BYTE *)result++ = v22;
  return result;
}


// ==================== sub_11610 @0x11610 size=100 ====================
_DWORD *__fastcall sub_11610(_DWORD *result, int *a2, unsigned int a3, int a4)
{
  unsigned int i; // r2
  int *v5; // r1
  int v6; // r3
  int v7; // r4
  int v8; // r12
  int v9; // lr
  _DWORD *v10; // r0
  int v11; // r4
  int v12; // r12
  int v13; // lr
  int v14; // r4
  int v15; // r12
  int v16; // lr
  int v17; // r4
  int v18; // t1
  bool v19; // cf
  bool v20; // nf
  int v21; // r2
  __int16 v22; // t1

  v19 = a3 >= 0x20;
  for ( i = a3 - 32; v19; result = v10 + 4 )
  {
    v6 = *a2;
    v7 = a2[1];
    v8 = a2[2];
    v9 = a2[3];
    v5 = a2 + 4;
    v19 = i >= 0x20;
    i -= 32;
    *result = v6;
    result[1] = v7;
    result[2] = v8;
    result[3] = v9;
    v10 = result + 4;
    a4 = *v5;
    v11 = v5[1];
    v12 = v5[2];
    v13 = v5[3];
    a2 = v5 + 4;
    *v10 = a4;
    v10[1] = v11;
    v10[2] = v12;
    v10[3] = v13;
  }
  if ( __CFSHL__(i, 28) )
  {
    a4 = *a2;
    v14 = a2[1];
    v15 = a2[2];
    v16 = a2[3];
    a2 += 4;
    *result = a4;
    result[1] = v14;
    result[2] = v15;
    result[3] = v16;
    result += 4;
  }
  if ( (i & 8) != 0 )
  {
    a4 = *a2;
    v17 = a2[1];
    a2 += 2;
    *result = a4;
    result[1] = v17;
    result += 2;
  }
  if ( __CFSHL__(i, 30) )
  {
    v18 = *a2++;
    LOWORD(a4) = v18;
    *result++ = v18;
  }
  if ( i << 30 )
  {
    v19 = __CFSHL__(i, 31);
    v21 = i << 31;
    v20 = v21 < 0;
    if ( v19 )
    {
      v22 = *(_WORD *)a2;
      a2 = (int *)((char *)a2 + 2);
      LOWORD(a4) = v22;
    }
    if ( v21 < 0 )
      LOBYTE(v21) = *(_BYTE *)a2;
    if ( v19 )
    {
      *(_WORD *)result = a4;
      result = (_DWORD *)((char *)result + 2);
    }
    if ( v20 )
    {
      *(_BYTE *)result = v21;
      return (_DWORD *)((char *)result + 1);
    }
  }
  return result;
}


// ==================== mem_set_bytes (sub_11674) @0x11674 size=22 ====================
int __fastcall mem_set_bytes(int a1, unsigned __int8 a2, int a3)
{
  sub_1177C(a1, a3, a2 | (a2 << 8) | ((a2 | (a2 << 8)) << 16));
  return a1;
}


// ==================== sub_1168A @0x1168A size=78 ====================
_DWORD *__fastcall sub_1168A(_DWORD *result, unsigned int a2)
{
  bool v2; // cf
  unsigned int v3; // r1
  _DWORD *v4; // r0
  int v5; // r1
  int v6; // r1

  v2 = a2 >= 0x20;
  v3 = a2 - 32;
  do
  {
    if ( !v2 )
      break;
    *result = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    v4 = result + 4;
    *v4 = 0;
    v4[1] = 0;
    v4[2] = 0;
    v4[3] = 0;
    result = v4 + 4;
    v2 = v3 >= 0x20;
    v3 -= 32;
  }
  while ( v2 );
  v2 = __CFSHL__(v3, 28);
  v5 = v3 << 28;
  if ( v2 )
  {
    *result = 0;
    result[1] = 0;
    result[2] = 0;
    result[3] = 0;
    result += 4;
  }
  if ( v5 < 0 )
  {
    *result = 0;
    result[1] = 0;
    result += 2;
  }
  v2 = __CFSHL__(v5, 2);
  v6 = 4 * v5;
  if ( v2 )
    *result++ = 0;
  if ( v6 )
  {
    if ( v6 < 0 )
    {
      *(_WORD *)result = 0;
      result = (_DWORD *)((char *)result + 2);
    }
    if ( (v6 & 0x40000000) != 0 )
    {
      *(_BYTE *)result = 0;
      return (_DWORD *)((char *)result + 1);
    }
  }
  return result;
}


// ==================== sub_116D8 @0x116D8 size=156 ====================
unsigned int __fastcall sub_116D8(unsigned __int8 *a1, unsigned __int8 *a2)
{
  bool v2; // zf
  unsigned int v3; // r2
  unsigned int v4; // t1
  unsigned int v5; // r3
  unsigned int v6; // t1
  bool v7; // zf
  unsigned int v8; // r12
  bool v9; // cf
  bool v10; // zf
  unsigned int result; // r0
  unsigned __int8 *v12; // r0
  int v13; // r2
  int v14; // t1
  unsigned __int8 *v15; // r1
  int v16; // r3
  int v17; // t1
  bool v18; // zf
  int v19; // t1
  int v20; // t1
  bool v21; // zf

  v2 = ((unsigned __int8)a1 & 3) == 0;
  if ( ((unsigned __int8)a1 & 3) == 0 )
    v2 = ((unsigned __int8)a2 & 3) == 0;
  if ( v2 )
  {
    do
    {
      v4 = *(_DWORD *)a1;
      a1 += 4;
      v3 = v4;
      v6 = *(_DWORD *)a2;
      a2 += 4;
      v5 = v6;
      v8 = (v3 - 16843009) & ~v3 & 0x80808080;
      v7 = v8 == 0;
      if ( !v8 )
        v7 = v3 == v5;
    }
    while ( v7 );
    v9 = v5 << 24 >= v3 << 24;
    result = (v5 << 24) - (v3 << 24);
    v10 = v5 << 24 == v3 << 24;
    if ( v5 << 24 == v3 << 24 )
    {
      v9 = 0;
      v10 = (v8 & 0xFF0) == 0;
    }
    if ( v10 )
    {
      v9 = v5 << 16 >= v3 << 16;
      result = (v5 << 16) - (v3 << 16);
      v10 = v5 << 16 == v3 << 16;
      if ( v5 << 16 == v3 << 16 )
      {
        v9 = 0;
        v10 = (v8 & 0xFF00) == 0;
      }
      if ( v10 )
      {
        v9 = v5 << 8 >= v3 << 8;
        result = (v5 << 8) - (v3 << 8);
        v10 = v5 << 8 == v3 << 8;
        if ( v5 << 8 == v3 << 8 )
        {
          v9 = 0;
          v10 = (v8 & 0xFF0000) == 0;
        }
        if ( v10 )
        {
          v9 = v5 >= v3;
          result = v5 - v3;
          v10 = v5 == v3;
        }
      }
    }
    if ( !v10 )
      return (result >> 1) | (v9 << 31);
  }
  else
  {
    do
    {
      v14 = *a1;
      v12 = a1 + 1;
      v13 = v14;
      v17 = *a2;
      v15 = a2 + 1;
      v16 = v17;
      v18 = v13 == 1;
      if ( v13 )
        v18 = v13 == v16;
      if ( !v18 )
        break;
      v19 = *v12;
      a1 = v12 + 1;
      v13 = v19;
      v20 = *v15;
      a2 = v15 + 1;
      v16 = v20;
      v21 = v13 == 1;
      if ( v13 )
        v21 = v13 == v16;
    }
    while ( v21 );
    return v13 - v16;
  }
  return result;
}


// ==================== sub_1177C @0x1177C size=64 ====================
_BYTE *__fastcall sub_1177C(_BYTE *result, unsigned int a2, __int16 a3)
{
  int v3; // r12
  _BYTE *v4; // r0

  if ( a2 >= 4 )
  {
    if ( ((unsigned __int8)result & 3) != 0 )
    {
      v3 = 4 - ((unsigned __int8)result & 3);
      if ( v3 != 2 )
        *result++ = a3;
      if ( v3 >= 2 )
        *(_WORD *)result = a3;
    }
    JUMPOUT(0x1168E);
  }
  if ( __CFSHL__(a2, 31) )
  {
    *result = a3;
    v4 = result + 1;
    *v4 = a3;
    result = v4 + 1;
  }
  if ( (a2 & 1) != 0 )
    *result++ = a3;
  return result;
}


// ==================== sub_117BC @0x117BC size=52 ====================
int __fastcall sub_117BC(char a1, int a2, int a3)
{
  int result; // r0

  result = a1 & 0xF;
  __mcr(15, 0, __mrc(15, 0, 15, 3, 5) & 0xFFFFFF0F | (16 * result), 15, 3, 5);
  while ( (unsigned __int8)__mrc(15, 0, 15, 3, 7) >> 4 != result )
    ;
  return result;
}


// ==================== sub_117F0 @0x117F0 size=32 ====================
int __fastcall sub_117F0(int result)
{
  int v1; // r3
  unsigned int v2; // r3

  v1 = __mrc(15, 0, 1, 0, 0);
  if ( result )
    v2 = v1 | 0x1000;
  else
    v2 = v1 & 0xFFFFEFFF;
  __mcr(15, 0, v2, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11810 @0x11810 size=20 ====================
BOOL sub_11810()
{
  return (__mrc(15, 0, 1, 0, 0) & 0x1000) != 0;
}


// ==================== sub_11824 @0x11824 size=20 ====================
void sub_11824()
{
  __mcr(15, 0, 0, 7, 1, 0);
  __dsb(0xFu);
  __isb(0xFu);
}


// ==================== sub_11838 @0x11838 size=20 ====================
BOOL sub_11838()
{
  return (__mrc(15, 0, 1, 0, 0) & 4) != 0;
}


// ==================== sub_1184C @0x1184C size=28 ====================
unsigned int sub_1184C()
{
  unsigned int result; // r0

  result = __mrc(15, 0, 1, 0, 0) | 4;
  __dsb(0xFu);
  __mcr(15, 0, result, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11868 @0x11868 size=40 ====================
unsigned int sub_11868()
{
  unsigned int result; // r0

  result = __mrc(15, 0, 1, 0, 0) & 0xFFFFFFFB;
  __dsb(0xFu);
  __mcr(15, 0, result, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  __mcr(15, 0, result, 8, 7, 1);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11890 @0x11890 size=160 ====================
void __spoils<> sub_11890()
{
  unsigned int v0; // r0
  unsigned int v1; // r10
  unsigned int v2; // r1
  char v3; // r5
  int v4; // r7
  int v5; // r9
  bool v6; // cc

  __dmb(0xFu);
  v0 = __mrc(15, 1, 0, 0, 1);
  if ( (v0 & 0x7000000) != 0 )
  {
    v1 = 0;
    do
    {
      if ( ((v0 >> (v1 + (v1 >> 1))) & 7) >= 2 )
      {
        __mcr(15, 2, v1, 0, 0, 0);
        __dsb(0xFu);
        __isb(0xFu);
        v2 = __mrc(15, 1, 0, 0, 0);
        v3 = __clz((v2 >> 3) & 0x3FF);
        v4 = (v2 >> 13) & 0x7FFF;
        do
        {
          v5 = (v2 >> 3) & 0x3FF;
          do
          {
            __mcr(15, 0, v1 | (v5 << v3) | (v4 << ((v2 & 7) + 4)), 7, 6, 2);
            v6 = v5-- < 1;
          }
          while ( !v6 );
          v6 = v4-- < 1;
        }
        while ( !v6 );
      }
      v1 += 2;
    }
    while ( (int)((v0 & 0x7000000) >> 23) > (int)v1 );
  }
  __mcr(15, 2, 0, 0, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
}


// ==================== sub_11930 @0x11930 size=160 ====================
void __spoils<> sub_11930()
{
  unsigned int v0; // r0
  unsigned int v1; // r10
  unsigned int v2; // r1
  char v3; // r5
  int v4; // r7
  int v5; // r9
  bool v6; // cc

  __dmb(0xFu);
  v0 = __mrc(15, 1, 0, 0, 1);
  if ( (v0 & 0x7000000) != 0 )
  {
    v1 = 0;
    do
    {
      if ( ((v0 >> (v1 + (v1 >> 1))) & 7) >= 2 )
      {
        __mcr(15, 2, v1, 0, 0, 0);
        __dsb(0xFu);
        __isb(0xFu);
        v2 = __mrc(15, 1, 0, 0, 0);
        v3 = __clz((v2 >> 3) & 0x3FF);
        v4 = (v2 >> 13) & 0x7FFF;
        do
        {
          v5 = (v2 >> 3) & 0x3FF;
          do
          {
            __mcr(15, 0, v1 | (v5 << v3) | (v4 << ((v2 & 7) + 4)), 7, 10, 2);
            v6 = v5-- < 1;
          }
          while ( !v6 );
          v6 = v4-- < 1;
        }
        while ( !v6 );
      }
      v1 += 2;
    }
    while ( (int)((v0 & 0x7000000) >> 23) > (int)v1 );
  }
  __mcr(15, 2, 0, 0, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
}


// ==================== sub_119D0 @0x119D0 size=160 ====================
void __spoils<> sub_119D0()
{
  unsigned int v0; // r0
  unsigned int v1; // r10
  unsigned int v2; // r1
  char v3; // r5
  int v4; // r7
  int v5; // r9
  bool v6; // cc

  __dmb(0xFu);
  v0 = __mrc(15, 1, 0, 0, 1);
  if ( (v0 & 0x7000000) != 0 )
  {
    v1 = 0;
    do
    {
      if ( ((v0 >> (v1 + (v1 >> 1))) & 7) >= 2 )
      {
        __mcr(15, 2, v1, 0, 0, 0);
        __dsb(0xFu);
        __isb(0xFu);
        v2 = __mrc(15, 1, 0, 0, 0);
        v3 = __clz((v2 >> 3) & 0x3FF);
        v4 = (v2 >> 13) & 0x7FFF;
        do
        {
          v5 = (v2 >> 3) & 0x3FF;
          do
          {
            __mcr(15, 0, v1 | (v5 << v3) | (v4 << ((v2 & 7) + 4)), 7, 14, 2);
            v6 = v5-- < 1;
          }
          while ( !v6 );
          v6 = v4-- < 1;
        }
        while ( !v6 );
      }
      v1 += 2;
    }
    while ( (int)((v0 & 0x7000000) >> 23) > (int)v1 );
  }
  __mcr(15, 2, 0, 0, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
}


// ==================== sub_11A70 @0x11A70 size=196 ====================
void __spoils<> sub_11A70()
{
  unsigned int v0; // r0
  unsigned int v1; // r0
  unsigned int v2; // r10
  unsigned int v3; // r1
  char v4; // r5
  int v5; // r7
  int v6; // r9
  bool v7; // cc

  v0 = __mrc(15, 0, 1, 0, 0) & 0xFFFFFFFB;
  __dsb(0xFu);
  __mcr(15, 0, v0, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  __mcr(15, 0, v0, 8, 7, 1);
  __dsb(0xFu);
  __isb(0xFu);
  __dmb(0xFu);
  v1 = __mrc(15, 1, 0, 0, 1);
  if ( (v1 & 0x7000000) != 0 )
  {
    v2 = 0;
    do
    {
      if ( ((v1 >> (v2 + (v2 >> 1))) & 7) >= 2 )
      {
        __mcr(15, 2, v2, 0, 0, 0);
        __dsb(0xFu);
        __isb(0xFu);
        v3 = __mrc(15, 1, 0, 0, 0);
        v4 = __clz((v3 >> 3) & 0x3FF);
        v5 = (v3 >> 13) & 0x7FFF;
        do
        {
          v6 = (v3 >> 3) & 0x3FF;
          do
          {
            __mcr(15, 0, v2 | (v6 << v4) | (v5 << ((v3 & 7) + 4)), 7, 14, 2);
            v7 = v6-- < 1;
          }
          while ( !v7 );
          v7 = v5-- < 1;
        }
        while ( !v7 );
      }
      v2 += 2;
    }
    while ( (int)((v1 & 0x7000000) >> 23) > (int)v2 );
  }
  __mcr(15, 2, 0, 0, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
}


// ==================== sub_11B34 @0x11B34 size=44 ====================
__int64 __fastcall sub_11B34(int a1, int a2)
{
  __int64 v2; // r4
  unsigned int v3; // r2
  unsigned int v4; // r0

  v3 = a1 + a2;
  v4 = a1 & 0xFFFFFFC0;
  do
  {
    __mcr(15, 0, v4, 7, 10, 1);
    v4 += 64;
  }
  while ( v4 < v3 );
  __mcr(15, 0, 0, 7, 10, 4);
  return v2;
}


// ==================== sub_11B60 @0x11B60 size=44 ====================
__int64 __fastcall sub_11B60(int a1, int a2)
{
  __int64 v2; // r4
  unsigned int v3; // r2
  unsigned int v4; // r0

  v3 = a1 + a2;
  v4 = a1 & 0xFFFFFFC0;
  do
  {
    __mcr(15, 0, v4, 7, 6, 1);
    v4 += 64;
  }
  while ( v4 < v3 );
  __mcr(15, 0, 0, 7, 10, 4);
  return v2;
}


// ==================== sub_11B8C @0x11B8C size=44 ====================
__int64 __fastcall sub_11B8C(int a1, int a2)
{
  __int64 v2; // r4
  unsigned int v3; // r2
  unsigned int v4; // r0

  v3 = a1 + a2;
  v4 = a1 & 0xFFFFFFC0;
  do
  {
    __mcr(15, 0, v4, 7, 14, 1);
    v4 += 64;
  }
  while ( v4 < v3 );
  __mcr(15, 0, 0, 7, 10, 4);
  return v2;
}


// ==================== sub_11BB8 @0x11BB8 size=8 ====================
void sub_11BB8()
{
  __dsb(0xFu);
}


// ==================== sub_11BC0 @0x11BC0 size=8 ====================
void sub_11BC0()
{
  __isb(0xFu);
}


// ==================== sub_11BC8 @0x11BC8 size=48 ====================
int __fastcall sub_11BC8(int result)
{
  int v1; // r3
  unsigned int v2; // r3

  __mcr(15, 0, 0, 8, 6, 0);
  __dsb(0xFu);
  __isb(0xFu);
  v1 = __mrc(15, 0, 1, 0, 0);
  if ( result )
    v2 = v1 | 1;
  else
    v2 = v1 & 0xFFFFFFFE;
  __mcr(15, 0, v2, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11BF8 @0x11BF8 size=16 ====================
unsigned int __fastcall sub_11BF8(unsigned int result)
{
  __mcr(15, 0, result, 2, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11C08 @0x11C08 size=44 ====================
int __fastcall sub_11C08(int a1, int a2)
{
  int result; // r0

  result = 2 * a1;
  __mcr(15, 0, ~(3 << result) | (a2 << result), 3, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11C34 @0x11C34 size=32 ====================
int __fastcall sub_11C34(int result)
{
  int v1; // r3
  unsigned int v2; // r3

  v1 = __mrc(15, 0, 1, 0, 0);
  if ( result )
    v2 = v1 | 2;
  else
    v2 = v1 & 0xFFFFFFFD;
  __mcr(15, 0, v2, 1, 0, 0);
  __dsb(0xFu);
  __isb(0xFu);
  return result;
}


// ==================== sub_11C6C @0x11C6C size=24 ====================
unsigned int __fastcall sub_11C6C(int a1)
{
  __asm { MRRC            p15, 1, R0,R1,c15 }
  __asm { MCRR            p15, 1, R0,R1,c15 }
  __dsb(0xFu);
  __isb(0xFu);
  return a1 & 0xFFFFFFBF;
}


// ==================== sub_11C84 @0x11C84 size=88 ====================
int *__fastcall sub_11C84(int *result, _DWORD *a2, int a3, _DWORD *a4, _DWORD *a5, _DWORD *a6)
{
  int v6; // r6
  int v7; // r7
  int v8; // r8
  int v9; // r9
  int v10; // r7
  int v11; // r8
  int v12; // r9

  do
  {
    v6 = *result;
    v7 = result[1];
    v8 = result[2];
    v9 = result[3];
    result += 4;
    *a4 = v6;
    a4[1] = v7;
    a4[2] = v8;
    a4[3] = v9;
    *a6 = 1;
    while ( (*a6 & 0x8000) == 0 )
      ;
    v10 = a5[1];
    v11 = a5[2];
    v12 = a5[3];
    *a2 = *a5;
    a2[1] = v10;
    a2[2] = v11;
    a2[3] = v12;
    a2 += 4;
    a3 -= 16;
  }
  while ( a3 );
  return result;
}


// ==================== brom_check_mpidr (sub_11CFC) @0x11CFC size=80 ====================
int brom_check_mpidr()
{
  int result; // r0
  int v1; // r10

  result = __mrc(15, 0, 0, 0, 5);
  if ( (result & 0x700) != 0 )
  {
    v1 = dword_11CDC[(__mrc(15, 0, 0, 0, 5) & 0x700u) >> 8];
    do
    {
      __isb(0xFu);
      __dsb(0xFu);
      __wfe();
    }
    while ( MEMORY[0x10214038] != v1 );
    return MEMORY[0x10214034]();
  }
  return result;
}


// ==================== brom_data_segment_init (sub_11D58) @0x11D58 size=56 ====================
void __spoils<R2,R3,R12,LR> brom_data_segment_init()
{
  mem_copy_words(&dword_134DC, 1058640, 0x1028B1u);
  mem_zero_words(1058996, 1060224);
}


// ==================== mem_copy_words (sub_11D90) @0x11D90 size=20 ====================
int *__fastcall mem_copy_words(int *result, _DWORD *a2, unsigned int a3)
{
  int v3; // t1

  while ( (unsigned int)a2 < a3 )
  {
    v3 = *result++;
    *a2++ = v3;
  }
  return result;
}


// ==================== mem_zero_words (sub_11DA4) @0x11DA4 size=20 ====================
_DWORD *__fastcall mem_zero_words(_DWORD *result, unsigned int a2)
{
  while ( (unsigned int)result < a2 )
    *result++ = 0;
  return result;
}


// ==================== sub_11DCC @0x11DCC size=8 ====================
// attributes: thunk
int __fastcall sub_11DCC(int result)
{
  return sub_11BC8(result);
}


// ==================== sub_11DD4 @0x11DD4 size=8 ====================
// attributes: thunk
unsigned int __fastcall sub_11DD4(unsigned int result)
{
  return sub_11BF8(result);
}


// ==================== sub_11DDC @0x11DDC size=8 ====================
// attributes: thunk
void __fastcall sub_11DDC(int a1)
{
  sub_11BC0();
}


// ==================== sub_11DE4 @0x11DE4 size=8 ====================
// attributes: thunk
void __fastcall sub_11DE4(int a1)
{
  sub_11BB8();
}


// ==================== sub_11DEC @0x11DEC size=8 ====================
// attributes: thunk
void sub_11DEC(void)
{
  sub_11890();
}


// ==================== sub_11DF4 @0x11DF4 size=8 ====================
// attributes: thunk
__int64 __fastcall sub_11DF4(int a1, int a2)
{
  return sub_11B34(a1, a2);
}


// ==================== sub_11DFC @0x11DFC size=8 ====================
// attributes: thunk
__int64 __fastcall sub_11DFC(int a1, int a2)
{
  return sub_11B60(a1, a2);
}


// ==================== sub_11E04 @0x11E04 size=8 ====================
// attributes: thunk
__int64 __fastcall sub_11E04(int a1, int a2)
{
  return sub_11B8C(a1, a2);
}


// ==================== sub_11E0C @0x11E0C size=8 ====================
// attributes: thunk
BOOL sub_11E0C(void)
{
  return sub_11838();
}


// ==================== sub_11E14 @0x11E14 size=8 ====================
// attributes: thunk
BOOL sub_11E14(void)
{
  return sub_11810();
}


// ==================== sub_11E1C @0x11E1C size=8 ====================
// attributes: thunk
void __fastcall sub_11E1C(int a1)
{
  sub_11824();
}


// ==================== sub_11E24 @0x11E24 size=8 ====================
// attributes: thunk
BOOL __fastcall sub_11E24(unsigned int a1)
{
  return time_delay_ms_v2(a1);
}


// ==================== sub_11E2C @0x11E2C size=8 ====================
// attributes: thunk
void __fastcall sub_11E2C(int a1, unsigned int a2, int a3, int a4)
{
  sub_7DEC(a1, a2, a3, a4);
}


// ==================== sub_11E34 @0x11E34 size=8 ====================
// attributes: thunk
int sub_11E34()
{
  return sub_7EB0();
}


// ==================== sub_11E3C @0x11E3C size=552 ====================
unsigned int __fastcall sub_11E3C(unsigned int result, unsigned int a2, unsigned int a3, unsigned int a4)
{
  bool v4; // zf
  int v5; // r5
  bool v6; // zf
  unsigned int v7; // r4
  bool v8; // zf
  int v9; // r4
  unsigned __int64 v10; // r0
  unsigned __int64 v11; // r2
  unsigned int v12; // r7
  unsigned int v13; // r8
  unsigned int v14; // r6
  int v15; // r12
  bool v16; // cf
  int v17; // r12
  unsigned int v18; // lr
  unsigned __int64 v19; // kr18_8
  unsigned __int64 v20; // kr20_8
  int v21; // lr
  unsigned int v22; // r7
  int v23; // r5
  unsigned int v24; // r1
  bool v25; // nf
  int v26; // r1
  unsigned __int64 v27; // r2
  unsigned __int64 v28; // r0
  int v29; // r6
  int v30; // r6
  int v31; // r1
  int v32; // r3
  int savedregs; // [sp+0h] [bp+0h]
  int savedregs_4; // [sp+4h] [bp+4h]
  int savedregs_8; // [sp+8h] [bp+8h]
  int savedregs_8a; // [sp+8h] [bp+8h]
  int savedregs_12; // [sp+Ch] [bp+Ch]
  int savedregs_16; // [sp+10h] [bp+10h]

  v4 = (~(a2 >> 4) & 0x7FF0000) == 0;
  if ( (~(a2 >> 4) & 0x7FF0000) != 0 )
    v4 = (~(a4 >> 4) & 0x7FF0000) == 0;
  if ( v4 )
  {
    v30 = savedregs_8;
    savedregs_8a = savedregs;
    savedregs_12 = savedregs_4;
    savedregs_16 = v30;
    result = sub_12170(result, a2, a3);
    v26 = *(unsigned __int8 *)(v31 + 24) ^ v32;
    return sub_1220C(result, v26);
  }
  v5 = a2 ^ a4;
  v6 = ((a2 >> 4) & 0x7FF0000) == 0;
  if ( ((a2 >> 4) & 0x7FF0000) != 0 )
  {
    v5 = (a4 >> 4) & 0x7FF0000;
    v6 = v5 == 0;
  }
  if ( v6 )
  {
    if ( (a2 & 0x7FF00000) == 0 )
      return 0;
    v26 = a2 ^ a4;
    return sub_1220C(result, v26);
  }
  v7 = ((a2 >> 4) & 0x7FF0000 | ((a2 ^ a4) >> 31)) - v5;
  HIDWORD(v10) = (a2 << 11) | 0x80000000 | (result >> 21);
  HIDWORD(v11) = (a4 << 11) | 0x80000000 | (a3 >> 21);
  v8 = HIDWORD(v10) == HIDWORD(v11);
  v9 = v7 + 66977792;
  LODWORD(v10) = result << 11;
  LODWORD(v11) = a3 << 11;
  if ( HIDWORD(v10) == HIDWORD(v11) )
    v8 = (_DWORD)v10 == (_DWORD)v11;
  if ( v8 )
  {
    v23 = 0x100000;
    v22 = 0;
  }
  else
  {
    v12 = (*((unsigned __int8 *)&loc_11FE4 + HIBYTE(HIDWORD(v11)))
         * (0x1000000 - (unsigned int)*((unsigned __int8 *)&loc_11FE4 + HIBYTE(HIDWORD(v11))) * HIWORD(HIDWORD(v11)))) >> 15;
    v13 = 0x10000 - ((v12 * (unsigned __int64)HIDWORD(v11)) >> 32);
    if ( v12 * HIDWORD(v11) )
      v13 = 0xFFFF - ((v12 * (unsigned __int64)HIDWORD(v11)) >> 32);
    v14 = (__PAIR64__(v13, -(v12 * HIDWORD(v11))) * v12) >> 32;
    v15 = (v11 * v14) >> 32;
    v16 = v15 == 0;
    v17 = -v15;
    v18 = 0x80000000
        - ((v14 * (unsigned __int64)HIDWORD(v11) + ((v14 * (unsigned __int64)(unsigned int)v11) >> 32)) >> 32);
    if ( !v16 )
      v18 = 0x7FFFFFFF
          - ((v14 * (unsigned __int64)HIDWORD(v11) + ((v14 * (unsigned __int64)(unsigned int)v11) >> 32)) >> 32);
    v19 = v14 * (unsigned __int64)v18 + ((v14 * (unsigned __int64)(unsigned int)v17) >> 32);
    v20 = HIDWORD(v10) * (unsigned __int64)HIDWORD(v19)
        + ((HIDWORD(v10) * (unsigned __int64)(unsigned int)v19) >> 32)
        + (((unsigned int)v10 * (unsigned __int64)HIDWORD(v19)) >> 32);
    v21 = HIDWORD(v20) + 1879048192;
    if ( !__OFADD__(HIDWORD(v20), 1879048192) )
    {
      v9 -= 0x10000;
      v20 = __PAIR64__(HIDWORD(v20) + (unsigned int)__CFSHL__(v20, 1) + HIDWORD(v20), 2 * (int)v20);
    }
    v22 = (__int64)(v20 + 128) >> 8;
    v23 = (unsigned int)((v20 + 128) >> 32) >> 8;
    if ( (unsigned int)(((_DWORD)v20 << 24) - 1862270976) <= 0x10000000 )
    {
      v27 = v11 >> 11;
      v28 = v10 >> 11;
      v29 = (__PAIR64__(v23, v22) * v27) >> 32;
      if ( v21 >= 0 )
        v29 -= (_DWORD)v28 << 20;
      if ( (signed int)((HIDWORD(v27) >> 1) + (BYTE4(v27) & 1) + v29 - ((_DWORD)v28 << 20)) < 0 )
        v23 = (__PAIR64__(v23, v22++) + 1) >> 32;
    }
  }
  result = v22;
  v24 = v23 + (v9 << 31) + 16 * (v9 & 0xFFFFFFFE);
  if ( (v9 & 0xFFFFFFFE) > 0x7F00000 )
  {
    v25 = v9 < 0;
    if ( v9 >= 0 )
      v25 = (((v24 + 0x100000) ^ (v9 << 31)) & 0x80000000) != 0;
    if ( v25 )
    {
      if ( v9 < 0 )
        return 0;
      v26 = v24 - 1610612736;
      return sub_1220C(result, v26);
    }
  }
  return result;
}


// ==================== sub_120EC @0x120EC size=92 ====================
int __fastcall sub_120EC(unsigned int a1, int a2, int a3)
{
  _WORD *v3; // r4
  bool v4; // cc
  signed int v5; // r3
  unsigned int v7; // r2

  v5 = 1054 - ((unsigned int)(2 * a2) >> 21);
  v4 = (int)(((unsigned int)(2 * a2) >> 21) - 1024) >= 30;
  if ( (int)(((unsigned int)(2 * a2) >> 21) - 1024) < 30 )
    v4 = v5 >= 33;
  if ( !v4 )
    return ((((a2 << 11) | 0x80000000 | (a1 >> 21)) >> v5) ^ (a2 >> 31)) - (a2 >> 31);
  if ( v5 > 16 )
    return 0;
  if ( v5 != -993 )
    return (a2 >> 31) ^ 0x7FFFFFFF;
  sub_12170(a1, a2, a3);
  STACK[0x114] = v7;
  *v3 = (_WORD)v3;
  return 0;
}


// ==================== sub_1214A @0x1214A size=38 ====================
unsigned int __fastcall sub_1214A(unsigned int a1)
{
  unsigned int v1; // r1

  v1 = a1 << __clz(a1);
  if ( v1 )
    return v1 << 21;
  else
    return 0;
}


// ==================== sub_12170 @0x12170 size=156 ====================
// positive sp value has been detected, the output may be wrong!
int __fastcall sub_12170(int a1, unsigned int a2, int a3, unsigned int a4)
{
  unsigned int v4; // r5
  int v5; // lr
  int *v6; // lr
  unsigned int v7; // r6
  _DWORD *v8; // lr
  int v9; // t1
  unsigned int v10; // r12
  int v11; // r12
  unsigned int v12; // r6
  int result; // r0
  char v14; // cc
  int (__fastcall *v15)(int, int); // [sp-4h] [bp-4h]

  v6 = (int *)((v5 + 2) & 0xFFFFFFFC);
  v9 = *v6;
  v8 = v6 + 1;
  v7 = v9;
  if ( v9 >= 0 && (v4 = a4 + (a3 != 0) + a4, v4 > 0xFFE00000) || (v10 = a2 + (a1 != 0) + a2, v10 > 0xFFE00000) )
  {
    LOBYTE(v11) = 8;
  }
  else if ( v10 == -2097152 )
  {
    v11 = 3 * (a2 >> 31) + 2;
    if ( v4 == -2097152 )
      v11 = (a4 >> 31) + 3 * (a2 >> 31) + 3;
  }
  else
  {
    v11 = a4 >> 31;
  }
  v12 = (v7 >> (3 * v11)) & 7;
  if ( v12 < 4 )
    return ((int (*)(void))((unsigned int)&v8[v12] | 1))();
  switch ( v12 )
  {
    case 4u:
      a2 = a4;
      a1 = a3;
      goto LABEL_15;
    case 5u:
LABEL_15:
      v14 = (a2 + (a1 != 0) + a2 != 0) & (__CFADD__(a1 != 0, a2) | __CFADD__(a2, (a1 != 0) + a2));
      if ( a2 + (a1 != 0) + a2 )
        v14 = a2 + (a1 != 0) + a2 < 0x200000;
      if ( v14 )
      {
        a1 = 0;
        a2 &= 0x80000000;
      }
      result = v15(a1, a2);
      break;
    case 6u:
    case 7u:
      result = v15(0, 2146959360);
      break;
  }
  return result;
}


// ==================== sub_1220C @0x1220C size=12 ====================
int sub_1220C()
{
  return 0;
}



/* ========================================================================
 * SRAM / MMIO 变量对照（反编译 + 实测整理）
 * ========================================================================
 *   0x1027B8     s_usb_rx_idx
 *   0x1027BC     s_usb_tx_done
 *   0x102818     s_stage_handler_fn
 *   0x102874     s_boot_source
 *   0x102884     s_boot_mode
 *   0x102888     s_usb_read_fn
 *   0x102898     s_usb_mode_flags
 *   0x1029C8     s_usb_cb_ep0_rx
 *   0x1029CC     s_usb_cb_table
 *   0x102B0C     s_auth_latch_ptr
 *   0x102B14     s_auth_status
 *   0x103B60     s_stage_marker_gatj
 *   0x103B64     s_stage_marker_yald
 *   0x103B68     s_stage_delay
 *   0x1054D8     s_usb_rx_len
 *   0x1054DC     s_usb_rx_buf
 *   0x106B64     s_descriptor_table
 *   0x106B74     s_desc_usb_dev
 *   0x10008048   TIMER_COUNTER
 *   0x1000A000   BOOT_SOURCE_SELECTOR
 *   0x10210ABC   PERIPH_READY_STATUS
 *   0x11002000   UART_DATA
 *   0x11002014   UART_STATUS
 *   0x11201080   USB_EVENT
 *   0x11201084   USB_EVENT_MASK
 *   0x11C10000   EFUSE_BASE
 *   0x11C10090   EFUSE_PUBK_HASH3
 * ======================================================================== */


