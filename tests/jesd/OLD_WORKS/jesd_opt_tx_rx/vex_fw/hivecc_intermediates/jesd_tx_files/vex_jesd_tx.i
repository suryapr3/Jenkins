# 1 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 587 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop.h" 1



# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hive_macroutils.h" 1
# 5 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop.h" 2

# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hivetypes.h" 1




typedef char __int8;
typedef short __int16;
typedef int __int32;

typedef char __sint8;
typedef short __sint16;
typedef int __sint32;

typedef unsigned char __uint8;
typedef unsigned short __uint16;
typedef unsigned int __uint32;


# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hive_custom_types.h" 1





# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/custom_types_ve32.h" 1








typedef unsigned int __upacked32x1;

typedef int __packed2x32 __attribute__((ext_vector_type(2)));
typedef int __spacked2x32 __attribute__((ext_vector_type(2)));
typedef unsigned int __upacked2x32 __attribute__((ext_vector_type(2)));

typedef int vec2i32 __attribute__((ext_vector_type(2)));
typedef int vec2si32 __attribute__((ext_vector_type(2)));
typedef unsigned int vec2ui32 __attribute__((ext_vector_type(2)));

typedef int __packed32x32 __attribute__((ext_vector_type(32)));
typedef int __spacked32x32 __attribute__((ext_vector_type(32)));
typedef unsigned int __upacked32x32 __attribute__((ext_vector_type(32)));

typedef int vec32i32 __attribute__((ext_vector_type(32)));
typedef int vec32si32 __attribute__((ext_vector_type(32)));
typedef unsigned int vec32ui32 __attribute__((ext_vector_type(32)));

typedef char __packed128x8 __attribute__((ext_vector_type(128)));
typedef char __spacked128x8 __attribute__((ext_vector_type(128)));
typedef unsigned char __upacked128x8 __attribute__((ext_vector_type(128)));

typedef char vec128i8 __attribute__((ext_vector_type(128)));
typedef char vec128si8 __attribute__((ext_vector_type(128)));
typedef unsigned char vec128ui8 __attribute__((ext_vector_type(128)));

typedef __spacked128x8 __int1024;
typedef __spacked128x8 __sint1024;
typedef __upacked128x8 __uint1024;

typedef char __packed256x8 __attribute__((ext_vector_type(256)));
typedef char __spacked256x8 __attribute__((ext_vector_type(256)));
typedef unsigned char __upacked256x8 __attribute__((ext_vector_type(256)));

typedef char vec256i8 __attribute__((ext_vector_type(256)));
typedef char vec256si8 __attribute__((ext_vector_type(256)));
typedef unsigned char vec256ui8 __attribute__((ext_vector_type(256)));

typedef __spacked256x8 __int2048;
typedef __spacked256x8 __sint2048;
typedef __upacked256x8 __uint2048;

typedef __int20 __packed128x20 __attribute__((ext_vector_type(128)));
typedef __int20 __spacked128x20 __attribute__((ext_vector_type(128)));
typedef unsigned __int20 __upacked128x20 __attribute__((ext_vector_type(128)));

typedef __int20 vec128i20 __attribute__((ext_vector_type(128)));
typedef __int20 vec128si20 __attribute__((ext_vector_type(128)));
typedef unsigned __int20 vec128ui20 __attribute__((ext_vector_type(128)));

typedef __spacked128x20 __int2560;
typedef __spacked128x20 __sint2560;
typedef __upacked128x20 __uint2560;
# 7 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hive_custom_types.h" 2
# 18 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hivetypes.h" 2

# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hive_memory_types.h" 1





# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/memory_types_ve32.h" 1
# 7 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hive_memory_types.h" 2
# 20 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hivetypes.h" 2
# 7 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop.h" 2
# 25 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop__ve32.h" 1



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump)))
OP___dump(int __a, int __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, int __b)
{
  __builtin_hive_OP___dump((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, unsigned int __b)
{
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, unsigned int __b)
{
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, long __b)
{
  __builtin_hive_OP___dump(__a, (int)__b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void*__a, long __b)
{
  __builtin_hive_OP___dump((int)__a, (int)__b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, unsigned long __b)
{
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, unsigned long __b)
{
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, long long __b)
{
  __builtin_hive_OP___dump(__a, (int) (__b >> 32));
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, long long __b)
{
  __builtin_hive_OP___dump((int)__a, (int) (__b >> 32));
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, unsigned long long __b)
{
  __builtin_hive_OP___dump(__a, (int) (__b >> 32));
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, unsigned long long __b)
{
  __builtin_hive_OP___dump((int)__a, (int) (__b >> 32));
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, const void* __b)
{
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, const void* __b)
{
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, const void __attribute__((hivemem(1))) * __b) {
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, const void __attribute__((hivemem(1))) * __b) {
  __builtin_hive_OP___dump((int)__a, (int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, const void __attribute__((hivemem(2))) * __b) {
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, const void __attribute__((hivemem(2))) * __b) {
  __builtin_hive_OP___dump((int)__a, (int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, const void __attribute__((hivemem(3))) * __b) {
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, const void __attribute__((hivemem(3))) * __b) {
  __builtin_hive_OP___dump((int)__a, (int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, const void __attribute__((hivemem(4))) * __b) {
  __builtin_hive_OP___dump(__a, (int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, const void __attribute__((hivemem(4))) * __b) {
  __builtin_hive_OP___dump((int)__a, (int) __b);
}

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___udump)))
OP___udump(int __a, unsigned __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, unsigned __b)
{
  __builtin_hive_OP___udump((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, int __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, int __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, unsigned long __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, unsigned long __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, long __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, long __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, long long __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) (__b >> 32));
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, long long __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) (__b >> 32));
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, unsigned long long __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) (__b >> 32));
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, unsigned long long __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) (__b >> 32));
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, const void* __b)
{
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, const void* __b)
{
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, const void __attribute__((hivemem(1))) * __b) {
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, const void __attribute__((hivemem(1))) * __b) {
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, const void __attribute__((hivemem(2))) * __b) {
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, const void __attribute__((hivemem(2))) * __b) {
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, const void __attribute__((hivemem(3))) * __b) {
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, const void __attribute__((hivemem(3))) * __b) {
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(int __a, const void __attribute__((hivemem(4))) * __b) {
  __builtin_hive_OP___udump(__a, (unsigned int) __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___udump(void* __a, const void __attribute__((hivemem(4))) * __b) {
  __builtin_hive_OP___udump((int)__a, (unsigned int) __b);
}



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump_typev2i32)))
OP___dump(int __a, __spacked2x32 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __spacked2x32 __b)
{
  __builtin_hive_OP___dump_typev2i32((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, __upacked2x32 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __upacked2x32 __b)
{
  __builtin_hive_OP___dump_typev2i32((int)__a, __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __spacked2x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev2i32(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __upacked2x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev2i32(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __spacked2x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev2i32(__a, __b, (int)__c, __d, __e);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __upacked2x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev2i32(__a, __b, (int)__c, __d, __e);
}



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump_typev32i32)))
OP___dump(int __a, __spacked32x32 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __spacked32x32 __b)
{
  __builtin_hive_OP___dump_typev32i32((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, __upacked32x32 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __upacked32x32 __b)
{
  __builtin_hive_OP___dump_typev32i32((int)__a, __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __spacked32x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev32i32(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __upacked32x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev32i32(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __spacked32x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev32i32(__a, __b, (int)__c, __d, __e);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __upacked32x32 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev32i32(__a, __b, (int)__c, __d, __e);
}



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump_typev128i8)))
OP___dump(int __a, __spacked128x8 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __spacked128x8 __b)
{
  __builtin_hive_OP___dump_typev128i8((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, __upacked128x8 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __upacked128x8 __b)
{
  __builtin_hive_OP___dump_typev128i8((int)__a, __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __spacked128x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev128i8(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __upacked128x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev128i8(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __spacked128x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev128i8(__a, __b, (int)__c, __d, __e);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __upacked128x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev128i8(__a, __b, (int)__c, __d, __e);
}



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump_typev256i8)))
OP___dump(int __a, __spacked256x8 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __spacked256x8 __b)
{
  __builtin_hive_OP___dump_typev256i8((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, __upacked256x8 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __upacked256x8 __b)
{
  __builtin_hive_OP___dump_typev256i8((int)__a, __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __spacked256x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev256i8(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __upacked256x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev256i8(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __spacked256x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev256i8(__a, __b, (int)__c, __d, __e);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __upacked256x8 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev256i8(__a, __b, (int)__c, __d, __e);
}



static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___dump_typev128i20)))
OP___dump(int __a, __spacked128x20 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __spacked128x20 __b)
{
  __builtin_hive_OP___dump_typev128i20((int)__a, __b);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(int __a, __upacked128x20 __b);

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump(void* __a, __upacked128x20 __b)
{
  __builtin_hive_OP___dump_typev128i20((int)__a, __b);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __spacked128x20 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev128i20(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(int __a, __upacked128x20 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_typev128i20(__a, __b, (int)__c, __d, __e);
}

static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __spacked128x20 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev128i20(__a, __b, (int)__c, __d, __e);
}
static __inline__ void __attribute__((__nodebug__, overloadable, always_inline))
OP___dump_fmt(void* __a, __upacked128x20 __b, int __c, int __d, int __e)
{
  __builtin_hive_OP___dump_fmt_str_typev128i20(__a, __b, (int)__c, __d, __e);
}

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___printdec)))
OP___printdec(int __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___printhex)))
OP___printhex(int __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___printchar)))
OP___printchar(int __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___printstring)))
OP___printstring(char* __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___pragma)))
OP___pragma(char* __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___vcd_update)))
OP___vcd_update(char* __a, int __b);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___schedule)))
OP___schedule(void);

static __inline__ int
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___cycles)))
OP___cycles(void);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___listing_on)))
OP___listing_on(void);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___listing_off)))
OP___listing_off(void);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___warnings_on)))
OP___warnings_on(void);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___warnings_off)))
OP___warnings_off(void);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___csim_assert)))
OP___csim_assert(int __a);

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline, clang_builtin_alias(__builtin_hive_OP___csim_assert)))
OP___assert(int __a);

enum FUStateID_t {
    bp_s2_tsu_MulticoreFuState1Type = 0x20101,
    bp_s2_tsu_MulticoreFuState2Type = 0x20102,
    simd0_vcom0_vcom_VcomFuStateSbfType = 0x5030e
};

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline))
OP___dump_state(int __a, enum FUStateID_t __b) {
  __builtin_hive_OP___dump_state(__a, (int)__b);
}

static __inline__ void
__attribute__((__nodebug__, overloadable, always_inline))
OP___dump_state(char* __a, enum FUStateID_t __b) {
  __builtin_hive_OP___dump_state_str(__a, (int)__b);
}
# 26 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/clang_pseudoop.h" 2
# 2 "<built-in>" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c" 2
# 32 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/common_macros.h" 1
# 33 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 1
# 33 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include/ve32_params.h" 1
# 34 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 1
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_alu_c.h" 1
# 26 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_alu_c.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_unfied_op_c.h" 1
# 27 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_alu_c.h" 2
# 29 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2

# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_lut_c.h" 1
# 31 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2


# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_c.h" 1
# 34 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2

# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_fmt_c.h" 1
# 36 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2
# 35 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h" 1
# 29 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/common_types.h" 1
# 33 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/common_types.h"
typedef char Int8;
typedef short Int16;
typedef int Int32;
typedef long long Int64;





typedef unsigned char uInt8;
typedef unsigned short uInt16;
typedef unsigned int uInt32;
typedef unsigned long long uInt64;





typedef struct { Int64 L40, H40; } Int80;
# 60 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/common_types.h"
typedef struct { Int8 imag, real; } Complex16_t;
typedef struct { Int16 imag, real; } Complex32_t;
typedef struct { Int32 imag, real; } Complex64_t;
typedef struct { Int64 imag, real; } Complex128_t;



typedef Int16 Complex16;
typedef Int32 Complex32;
typedef Int64 Complex40;

typedef unsigned char uint8;
typedef signed char sint8;
typedef unsigned short int uint16;
typedef signed short int sint16;
typedef unsigned int uint32;
typedef signed int sint32;
# 30 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h" 2



typedef struct vec8_8_t { Int8 elem[8]; } vec8_8;
typedef struct vec4_16_t { Int16 elem[4]; } vec4_16;
typedef struct vec2_32_t { Int32 elem[2]; } vec2_32;
typedef struct vec1_64_t { Int64 elem[1]; } vec1_64;


typedef struct { unsigned char byte[10]; } uBit80_t;
typedef struct { char byte[10]; } sBit80_t;


typedef struct vec16_8_t { Int8 elem[16]; } vec16_8;
typedef struct vec8_16_t { Int16 elem[8]; } vec8_16;
typedef struct vec4_32_t { Int32 elem[4]; } vec4_32;
typedef struct vec2_64_t { Int64 elem[2]; } vec2_64;
typedef struct cpx8_16_t { Complex16 elem[8]; } cpx8_16;
typedef struct cpx4_32_t { Complex32 elem[4]; } cpx4_32;


typedef struct vec32_8_t { Int8 elem[32]; } vec32_8;
typedef struct vec16_16_t { Int16 elem[16]; } vec16_16;
typedef struct vec8_32_t { Int32 elem[8]; } vec8_32;
typedef struct vec4_64_t { Int64 elem[4]; } vec4_64;


typedef struct vec8_64_t { Int64 elem[8]; } vec8_64;
typedef struct vec16_32_t { Int32 elem[16]; } vec16_32;
typedef struct vec32_16_t { Int16 elem[32]; } vec32_16;
typedef struct vec64_8_t { Int8 elem[64]; } vec64_8;


typedef struct cpx32_16_t { Complex16 elem[32]; } cpx32_16;
typedef struct cpx16_32_t { Complex32 elem[16]; } cpx16_32;



typedef struct vec128_8_t { Int8 elem[128]; } vec128_8;
typedef struct vec64_16_t { Int16 elem[64]; } vec64_16;
typedef struct vec32_32_t { Int32 elem[32]; } vec32_32;
typedef struct vec16_64_t { Int64 elem[16]; } vec16_64;





typedef struct cpx64_16_t { Complex16 elem[64]; } cpx64_16;
typedef struct cpx32_32_t { Complex32 elem[32]; } cpx32_32;


typedef struct vec32_64_t { Int64 elem[32]; } vec32_64;
typedef struct cpx16_64_t { Complex128_t elem[16];} cpx16_64;
typedef struct cpx32_40_t { Complex40 elem[32];} cpx32_40;
typedef struct ubit16_80_s { uBit80_t elem[16]; } ubit16_80_t;
typedef struct sbit16_80_s { sBit80_t elem[16]; } sbit16_80_t;


typedef struct vec64_32_t { Int32 elem[64]; } vec64_32;
typedef struct vec128_16_t { Int16 elem[128]; } vec128_16;
typedef struct vec256_8_t { Int8 elem[256]; } vec256_8;
typedef struct cpx128_16_t { Complex16 elem[128];} cpx128_16;
typedef struct cpx64_32_t { Complex32 elem[64]; } cpx64_32;


typedef struct vec64_40_t { Int64 elem[40]; } vec64_40;
typedef struct cpx32_64_t { Complex128_t elem[32];} cpx32_64;
typedef struct cpx64_64_t { Complex40 elem[64];} cpx64_40;
typedef struct ubit32_80_s { uBit80_t elem[32]; } ubit32_80_t;
typedef struct sbit32_80_s { sBit80_t elem[32]; } sbit32_80_t;



typedef struct vec64_64_t { Int64 elem[64]; } vec64_64;
typedef struct vec128_32_t { Int32 elem[128]; } vec128_32;
typedef struct vec256_16_t { Int16 elem[256]; } vec256_16;
typedef struct vec512_8_t { Int8 elem[512]; } vec512_8;


typedef struct cpx256_16_t { Complex16 elem[256]; } cpx256_16;
typedef struct cpx128_32_t { Complex32 elem[128]; } cpx128_32;


typedef struct vec258_16_t { Int16 elem[258]; } vec258_16;
typedef struct vec129_32_t { Int32 elem[129]; } vec129_32;


typedef struct vec256_32_t { Int32 elem[256]; } vec256_32;

  typedef int voffset_t;




  typedef int vbase32_t;
  typedef int vbase_t;


typedef struct VCOM_ST_t {
    unsigned int ovf;
    unsigned int sbf[8][(2*(1024/32))];
} VCOM_ST;
# 36 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_debug.h" 1
# 37 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 49 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 1
# 10 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 1
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/generic.h" 1
# 29 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/crun_support.h" 1
# 30 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 1
# 25 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/attributes_volcano.h" 1
# 26 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 2
# 31 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 1
# 27 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h" 1
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin.h" 1








# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h" 1
# 12 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_cancel)))
OP_mc_cancel(unsigned int A, unsigned int E);
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_complete)))
OP_mc_complete(unsigned int E);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_complete_and_cancel)))
OP_mc_complete_and_cancel(unsigned int E);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_get_state)))
OP_mc_get_state(unsigned int A, unsigned int E);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_init)))
OP_mc_init(unsigned int A, unsigned int E);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_init_local_idc)))
OP_mc_init_local_idc(unsigned int A, unsigned int E);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_invalidate)))
OP_mc_invalidate(unsigned int E);
# 88 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_reset)))
OP_mc_reset(unsigned int E);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_mc_set_rate)))
OP_mc_set_rate(unsigned int A, unsigned int E);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_abssat)))
OP_s_abssat(int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_add)))
OP_s_add(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_add_i)))
OP_s_add_i(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_and)))
OP_s_and(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_and_i)))
OP_s_and_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_bfi)))
OP_s_bfi(int A, int B, int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_eq)))
OP_s_eq(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_eq_i)))
OP_s_eq_i(unsigned int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_eq_sel)))
OP_s_eq_sel(int A, int B, int C, int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ge_sel)))
OP_s_ge_sel(int A, int B, int C, int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_gt_sel)))
OP_s_gt_sel(int A, int B, int C, int D);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_imm)))
OP_s_imm(int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_imm_u)))
OP_s_imm_u(unsigned int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_immh)))
OP_s_immh(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_inv)))
OP_s_inv(unsigned int A);
# 276 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_16)))
OP_s_ldo_16(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_16_i)))
OP_s_ldo_16_i(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_16s)))
OP_s_ldo_16s(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_16s_i)))
OP_s_ldo_16s_i(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_32)))
OP_s_ldo_32(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_32_i)))
OP_s_ldo_32_i(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_8)))
OP_s_ldo_8(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_8_i)))
OP_s_ldo_8_i(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_8s)))
OP_s_ldo_8s(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ldo_8s_i)))
OP_s_ldo_8s_i(int A, int B);
# 416 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_le)))
OP_s_le(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_le_i)))
OP_s_le_i(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_le_sel)))
OP_s_le_sel(int A, int B, int C, int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_le_u)))
OP_s_le_u(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_le_u_i)))
OP_s_le_u_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lred)))
OP_s_lred(unsigned int A, unsigned int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lt)))
OP_s_lt(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lt_i)))
OP_s_lt_i(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lt_sel)))
OP_s_lt_sel(int A, int B, int C, int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lt_u)))
OP_s_lt_u(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_lt_u_i)))
OP_s_lt_u_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_max)))
OP_s_max(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_max_i)))
OP_s_max_i(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_max_u)))
OP_s_max_u(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_max_u_i)))
OP_s_max_u_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_min)))
OP_s_min(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_min_i)))
OP_s_min_i(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_min_u)))
OP_s_min_u(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_min_u_i)))
OP_s_min_u_i(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_modadd)))
OP_s_modadd(unsigned int ua, int sb, unsigned int uc);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_modadd_i)))
OP_s_modadd_i(unsigned int ua, int sb, unsigned int uc);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_moddec)))
OP_s_moddec(unsigned int ua, unsigned int uc);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_modinc)))
OP_s_modinc(unsigned int ua, unsigned int uc);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_mul)))
OP_s_mul(int A, int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_mul_i)))
OP_s_mul_i(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_mul_u)))
OP_s_mul_u(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_mul_u_i)))
OP_s_mul_u_i(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_mux)))
OP_s_mux(unsigned int A, unsigned int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ne_sel)))
OP_s_ne_sel(int A, int B, int C, int D);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_neg)))
OP_s_neg(unsigned int A);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_neq)))
OP_s_neq(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_neq_i)))
OP_s_neq_i(unsigned int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_or)))
OP_s_or(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_or_i)))
OP_s_or_i(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_pass)))
OP_s_pass(unsigned int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_pass_1)))
OP_s_pass_1(unsigned int A);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_se_16)))
OP_s_se_16(unsigned int A);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_se_8)))
OP_s_se_8(unsigned int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shl)))
OP_s_shl(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shl_i)))
OP_s_shl_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shra)))
OP_s_shra(int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shra_i)))
OP_s_shra_i(int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shrl)))
OP_s_shrl(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_shrl_i)))
OP_s_shrl_i(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sl16or)))
OP_s_sl16or(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_16)))
OP_s_stau_16(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_16_i)))
OP_s_stau_16_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_32)))
OP_s_stau_32(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_32_i)))
OP_s_stau_32_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_32x2)))
OP_s_stau_32x2(int A, int B, unsigned int C, unsigned int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_8)))
OP_s_stau_8(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stau_8_i)))
OP_s_stau_8_i(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_16)))
OP_s_sto_16(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_16_i)))
OP_s_sto_16_i(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_32)))
OP_s_sto_32(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_32_i)))
OP_s_sto_32_i(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_8)))
OP_s_sto_8(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sto_8_i)))
OP_s_sto_8_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_16)))
OP_s_stoi_16(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_16_i)))
OP_s_stoi_16_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_32)))
OP_s_stoi_32(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_32_i)))
OP_s_stoi_32_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_32x2)))
OP_s_stoi_32x2(int A, int B, unsigned int C, unsigned int D);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_8)))
OP_s_stoi_8(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stoi_8_i)))
OP_s_stoi_8_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stomi_32)))
OP_s_stomi_32(int A, int B, int L, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_stomi_32x2)))
OP_s_stomi_32x2(int A, int B, int L, unsigned int C, unsigned int D);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sub)))
OP_s_sub(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sub_i)))
OP_s_sub_i(unsigned int A, unsigned int B);
# 972 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xldo_32)))
OP_s_xldo_32(int A, int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xldo_32_i)))
OP_s_xldo_32_i(int A, int B);
# 996 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xor)))
OP_s_xor(unsigned int A, unsigned int B);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xor_i)))
OP_s_xor_i(unsigned int A, unsigned int B);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xstau_32)))
OP_s_xstau_32(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xsto_32)))
OP_s_xsto_32(int A, int B, unsigned int C);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xsto_32_i)))
OP_s_xsto_32_i(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xstoi_32)))
OP_s_xstoi_32(int A, int B, unsigned int C);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_xstoi_32_i)))
OP_s_xstoi_32_i(int A, int B, unsigned int C);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ze_16)))
OP_s_ze_16(unsigned int A);





static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_ze_8)))
OP_s_ze_8(unsigned int A);





static __inline__ __spacked128x8
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_std_pass_v0)))
OP_std_pass_v0(__spacked128x8 A);





static __inline__ __spacked128x8
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_std_pass_v1)))
OP_std_pass_v1(__spacked128x8 A);





static __inline__ __spacked128x8
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_acc_read)))
OP_v_acc_read(unsigned int ctrl0, __spacked128x20 win0);





static __inline__ __spacked128x20
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_acc_write)))
OP_v_acc_write(unsigned int ctrl0, __spacked128x8 vin0, __spacked128x20 win0);
# 1164 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ __spacked32x32
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_ld_1024)))
OP_v_ld_1024(unsigned int base_addr);
# 1176 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ __spacked32x32
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_ldo_1024)))
OP_v_ldo_1024(unsigned int base_addr, int offset_in);





static __inline__ __spacked32x32
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_ldo_1024_i)))
OP_v_ldo_1024_i(unsigned int base_addr, int offset_in);
# 1268 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ __spacked128x8
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_mux)))
OP_v_mux(__spacked128x8 A, __spacked128x8 B, unsigned int C);





static __inline__ __spacked128x8
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_pass)))
OP_v_pass(__spacked128x8 A);
# 1292 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_st_1024)))
OP_v_st_1024(unsigned int base_addr, __spacked128x8 vin0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_sthoi_2048)))
OP_v_sthoi_2048(unsigned int base_addr, int offset_in, unsigned int hdr, __spacked128x8 vin0, __spacked128x8 vin1);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_sto_1024)))
OP_v_sto_1024(unsigned int base_addr, int offset_in, __spacked128x8 vin0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_sto_1024_i)))
OP_v_sto_1024_i(unsigned int base_addr, int offset_in, __spacked128x8 vin0);
# 1332 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_stoi_1024)))
OP_v_stoi_1024(unsigned int base_addr, int offset_in, __spacked128x8 vin0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_stoi_1024_circ)))
OP_v_stoi_1024_circ(unsigned int base_addr, int offset_in, unsigned int limit, unsigned int rewind, __spacked128x8 vin0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_stoi_1024_i)))
OP_v_stoi_1024_i(unsigned int base_addr, int offset_in, __spacked128x8 vin0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_stoi_2048)))
OP_v_stoi_2048(unsigned int base_addr, int offset_in, __spacked128x8 vin0, __spacked128x8 vin1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_stoi_2048_circ)))
OP_v_stoi_2048_circ(unsigned int base_addr, int offset_in, unsigned int limit, unsigned int rewind, __spacked128x8 vin0, __spacked128x8 vin1);
# 1392 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ unsigned int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_vcom_tbl_write)))
OP_v_vcom_tbl_write(unsigned int in0, __spacked128x8 vin0, __spacked128x8 vin1);
# 1408 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_vec_addr_st_1024)))
OP_v_vec_addr_st_1024(unsigned int base_addr, unsigned int odd_row, __spacked128x8 vin0, __spacked128x8 vaddr_in);
# 1420 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin__ve32.h"
static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_1024)))
OP_v_xstau_1024(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_1024_i)))
OP_v_xstau_1024_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_1024x2)))
OP_v_xstau_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_32)))
OP_v_xstau_32(int A, int B, unsigned int D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_32_i)))
OP_v_xstau_32_i(int A, int B, unsigned int D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_32x2)))
OP_v_xstau_32x2(int A, int B, unsigned int D0, unsigned int D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_512)))
OP_v_xstau_512(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_512_i)))
OP_v_xstau_512_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_h_512)))
OP_v_xstau_h_512(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstau_h_512_i)))
OP_v_xstau_h_512_i(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_1024)))
OP_v_xsto_1024(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_1024_i)))
OP_v_xsto_1024_i(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_1024x2)))
OP_v_xsto_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_32)))
OP_v_xsto_32(int A, int B, unsigned int D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_32_i)))
OP_v_xsto_32_i(int A, int B, unsigned int D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_32x2)))
OP_v_xsto_32x2(int A, int B, unsigned int D0, unsigned int D1);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_512)))
OP_v_xsto_512(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_512_i)))
OP_v_xsto_512_i(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_h_512)))
OP_v_xsto_h_512(int A, int B, __spacked128x8 D0);





static __inline__ void
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xsto_h_512_i)))
OP_v_xsto_h_512_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_1024)))
OP_v_xstoi_1024(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_1024_i)))
OP_v_xstoi_1024_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_1024x2)))
OP_v_xstoi_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_32)))
OP_v_xstoi_32(int A, int B, unsigned int D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_32_i)))
OP_v_xstoi_32_i(int A, int B, unsigned int D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_32x2)))
OP_v_xstoi_32x2(int A, int B, unsigned int D0, unsigned int D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_512)))
OP_v_xstoi_512(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_512_i)))
OP_v_xstoi_512_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_h_512)))
OP_v_xstoi_h_512(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstoi_h_512_i)))
OP_v_xstoi_h_512_i(int A, int B, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_1024)))
OP_v_xstomi_1024(int A, int B, int L, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_1024x2)))
OP_v_xstomi_1024x2(int A, int B, int L, __spacked128x8 D0, __spacked128x8 D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_32)))
OP_v_xstomi_32(int A, int B, int L, unsigned int D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_32x2)))
OP_v_xstomi_32x2(int A, int B, int L, unsigned int D0, unsigned int D1);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_512)))
OP_v_xstomi_512(int A, int B, int L, __spacked128x8 D0);





static __inline__ int
__attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_v_xstomi_h_512)))
OP_v_xstomi_h_512(int A, int B, int L, __spacked128x8 D0);




static __inline__ void __attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_sleep)))
OP_s_sleep(void);






static __inline__ void __attribute__((__always_inline__, __nodebug__, clang_builtin_alias(__builtin_hive_OP_s_idle)))
OP_s_idle(void);
# 10 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/hiveintrin.h" 2
# 2 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h" 2
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 2
# 32 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/config.h" 1
# 33 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 11 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 2

# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/sdk/include/iss/performance_counters.h" 1
# 49 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/sdk/include/iss/performance_counters.h"
static inline unsigned int OP_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_hive_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))));



  return clc_l;
}

static inline unsigned int OP_exe_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_hive_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))));



  return exc_l;
}

static inline unsigned int OP_slp_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_hive_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))));



  return slc_l;
}
# 13 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 2
# 50 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_types.h" 1
# 27 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_types.h"
typedef __int2560 wvector_t;
typedef __int1024 uwvector_t;
# 51 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_macros.h" 1
# 249 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_macros.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_B_CLONE(int IP0, int IP1, int IP3, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
    unsigned int OP0, OP1;
    __int1024 VIP2 __attribute__((uninit)), VIP3 __attribute__((uninit));
    __int1024 VOP1;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; vec2i32 __prvdmyi __attribute__((uninit)), __prvdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (OP0 = __builtin_hive_OP_v_alu_2((unsigned int) (IP0), (unsigned int) (IP1), (unsigned int) (0), (unsigned int) (IP3), (unsigned int) (0), (unsigned int) (0), (int) (__pccdmyi), (__upacked2x32) (__prvdmyi), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8) (VIP2), (__spacked128x8) (VIP3), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&OP1), (int *) (&__pccdmyo), (__upacked2x32 *) (&__prvdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((hivemem(3))) *) (&VOP1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 52 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_ldst_macros.h" 1
# 53 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2





# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h" 1
# 35 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h" 1
# 53 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_A(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&dmyout), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 76 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_B(unsigned int in0, __int1024 vin0, __int1024 vin1, unsigned int *out0, unsigned int *out1)
{
    unsigned int dmyin __attribute__((uninit));
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (*out0 = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&*out1), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 99 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_C(unsigned int in0, unsigned int in1, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (in1), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&dmyout), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 120 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_D(unsigned int in0, __int1024 vin0, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&dmyout), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 140 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_E(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&dmyout), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 161 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_F(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int in1 = 0;
    unsigned int dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_alu_1((unsigned int) (in0), (unsigned int) (in1), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (unsigned int *) (&dmyout), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };
}
# 182 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_A(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit));
   __int1024 dmyvin __attribute__((uninit)), dmyvout;
   __int2560 dmywin __attribute__((uninit)), dmywout;

   { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (dmywin), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&dmywout)) __attribute__((on("Any")))); };
}
# 204 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_B(unsigned int in0, __int1024 vin0, __int1024 vin1, __int2560 win0, __int2560 *wout0)
{
    unsigned int dmyin __attribute__((uninit));
   __int1024 dmyvin __attribute__((uninit)), dmyvout;

   { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (win0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&*wout0)) __attribute__((on("Any")))); };
}
# 227 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_C(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit));
   __int1024 dmyvin __attribute__((uninit)), dmyvout;
   __int2560 dmywin __attribute__((uninit)), dmywout;

   { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (1), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (dmywin), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&dmywout)) __attribute__((on("Any")))); };
}
# 251 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_D(unsigned int in0, __int2560 win0, __int1024 *vout0)
{
    unsigned int cln0 = 0;
    unsigned int dmyin __attribute__((uninit));
    __int1024 dmyvin __attribute__((uninit)), dmyvout;
    __int2560 dmywout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (cln0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (win0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&dmywout)) __attribute__((on("Any")))); };
}
# 279 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_E(unsigned int in0, __int1024 vin0, __int2560 win0, __int1024 *vout0)
{
    unsigned int cln0 = 0;
    unsigned int dmyin __attribute__((uninit));
   __int1024 dmyvin __attribute__((uninit)), dmyvout;
   __int2560 dmywout;

   { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (cln0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (win0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&dmywout)) __attribute__((on("Any")))); };
}
# 302 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_F(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int cln0 = 0;
    unsigned int dmyin __attribute__((uninit));
   __int1024 dmyvin __attribute__((uninit)), dmyvout;
   __int2560 dmywin __attribute__((uninit)), dmywout;

   { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (__pccdmyo = __builtin_hive_OP_v_mul_1((unsigned int) (in0), (unsigned int) (cln0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (__spacked128x20) (dmywin), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo), (__spacked128x20 *) (&dmywout)) __attribute__((on("Any")))); };
}
# 36 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h" 2
# 59 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_mul.h" 1
# 60 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h" 1
# 27 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/vcom_fmt_c.h" 1
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h" 2
# 114 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MW_INTERLEAVE_32(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x2u << 28) | (1 << 19) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 165 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_16(__int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x2u << 28)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 244 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MW_DEINTERLEAVE_32(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x3u << 28) | (1 << 19) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 295 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_DEINTERLEAVE_16(__int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x3u << 28)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 364 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MS_ROTATE(unsigned int in0, unsigned int in1, __int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x1u << 28) | (0x1u << 3)), (unsigned int) (in1), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 409 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_SET_32(unsigned int in0, unsigned int in1, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
     __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x5u << 28) | (0x1u << 3)), (unsigned int) (in1), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 453 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_GET_32(unsigned int in0, __int1024 vin0, unsigned int *out0)
{
    unsigned int dmyin __attribute__((uninit));
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (*out0 = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x4u << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 492 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_CLONE_32(unsigned int in0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x7u << 28)), (unsigned int) (in0), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 550 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_PARALLEL_EXTRACT(unsigned int in0, __int1024 vin0, unsigned int *out0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit));
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (*out0 = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x8u << 28)), (unsigned int) (in0), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 598 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_VEC_CLONE_32(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xAu << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 665 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_BY_N_1X64(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xBu << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 736 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_BY_N_2X32(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0, __int1024 *vout1)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit));

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xCu << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout1), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 786 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_COMP_REVERSE(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xDu << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 837 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_COMP_SWAP(unsigned int in0, __int1024 vin0, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xEu << 28) | (0x1u << 3)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); } ;




}
# 888 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ROTATE_MERGE(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0xFu << 28) | (0x1u << 3) | (1 << 27)), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (in0), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 933 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_fmt.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MASK_MUX(unsigned int in0, __int1024 vin0, __int1024 vin1, __int1024 *vout0)
{
    unsigned int dmyin __attribute__((uninit)), dmyout;
    __int1024 dmyvin __attribute__((uninit)), dmyvout;

    { unsigned int __pccdmyi __attribute__((uninit)), __pccdmyo; __int1024 __pkrdmyi __attribute__((uninit)), __pkrdmyo; (dmyout = __builtin_hive_OP_v_fmt_1((unsigned int) ((0 << 0) | (0x6u << 28)), (unsigned int) (in0), (unsigned int) (dmyin), (unsigned int) (dmyin), (unsigned int) (dmyin), (int) (__pccdmyi), (__spacked128x8) (vin0), (__spacked128x8) (dmyvin), (__spacked128x8) (vin1), (__spacked128x8) (dmyvin), (__spacked128x8) (__pkrdmyi), (int *) (&__pccdmyo), (__spacked128x8 __attribute__((hivemem(3))) *) (&*vout0), (__spacked128x8 __attribute__((hivemem(3))) *) (&dmyvout), (__spacked128x8 __attribute__((hivemem(3))) *) (&__pkrdmyo)) __attribute__((on("Any")))); };




}
# 61 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 34 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 1
# 30 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 1
# 31 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 1
# 27 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h"
# 1 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h" 1
# 28 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 2
# 32 "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p6/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 35 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c" 2
# 1 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/defines.h" 1
# 36 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c" 2
# 50 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c"
vec32i32 __attribute__((address(0x0))) vbuffer_0[64];
vec32i32 __attribute__((address(0x2000))) vbuffer_1[64];
vec32i32 __attribute__((address(0x4000))) vbuffer_2[64];
vec32i32 __attribute__((address(0x6000))) vbuffer_3[64];
vec32i32 __attribute__((address(0x8000))) vbuffer_4[64];
vec32i32 __attribute__((address(0xa000))) vbuffer_5[64];
vec32i32 __attribute__((address(0xc000))) vbuffer_6[64];
vec32i32 __attribute__((address(0xe000))) vbuffer_7[64];


volatile unsigned int __attribute__((address(0x0))) g_dest_buffer0_base;
volatile unsigned int __attribute__((address(0x4))) g_dest_buffer1_base;
volatile unsigned int __attribute__((address(0x8))) g_dest_buffer2_base;
volatile unsigned int __attribute__((address(0xc))) g_dest_buffer3_base;
volatile unsigned int __attribute__((address(0x10))) g_dest_buffer4_base;
volatile unsigned int __attribute__((address(0x14))) g_dest_buffer5_base;
volatile unsigned int __attribute__((address(0x18))) g_dest_buffer6_base;
volatile unsigned int __attribute__((address(0x1C))) g_dest_buffer7_base;

volatile int __attribute__((address(0x20))) g_host_indicator;
volatile int __attribute__((address(0x24))) g_vex_exit;
volatile int __attribute__((address((0x28)))) g_timer_debug;
volatile int __attribute__((address(0x2c))) g_debug;
volatile int __attribute__((address(0x30))) g_timeout_cycles;
# 89 "/nfs/site/disks/xne_00001/workspace/hw/achennar/ABC/ABC_18A_0p6_1_04_03_24/tests/jesd/0p6_16G/TX_8s/vex_fw/vex_jesd_tx.c"
inline void init_timer(int cycles)
{

    (OP_s_xsto_32(0, 3, 3) __attribute__((on("Any"))));

    (OP_s_xsto_32(0, 4, cycles) __attribute__((on("Any"))));

    (OP_s_xsto_32(0, 6, 0x1) __attribute__((on("Any"))));

    (OP_s_xsto_32(0, 7, 0x4000 + (0x28)) __attribute__((on("Any"))));

    (OP_s_xsto_32(0, 8, 0xdeadbeef) __attribute__((on("Any"))));
}







void jesd_tx() __attribute__((hive_entry))
{
    int i, j;
    int iter_max = 64/2;
    int num_vec_per_stream = 2;

    g_host_indicator = 0;
    g_vex_exit = 0;

    OP___printstring("jesd_tx : start \n");
    init_timer(g_timeout_cycles);

    while (g_host_indicator == 0)
    {

    }

    (OP_s_xsto_32(0, 9, 1) __attribute__((on("Any"))));

    while(g_vex_exit == 0)
    {
        for(i = 0; (i < iter_max); i++)
        {






      for(j = 0; j < num_vec_per_stream; j++)
      {
       (OP_v_xsto_1024_i(g_dest_buffer0_base, 0x0, vbuffer_0[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer1_base, 0x0, vbuffer_1[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer2_base, 0x0, vbuffer_2[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer3_base, 0x0, vbuffer_3[(i * 2) + j]) __attribute__((on("Any"))));

       (OP_v_xsto_1024_i(g_dest_buffer4_base, 0x0, vbuffer_4[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer5_base, 0x0, vbuffer_5[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer6_base, 0x0, vbuffer_6[(i * 2) + j]) __attribute__((on("Any"))));
       (OP_v_xsto_1024_i(g_dest_buffer7_base, 0x0, vbuffer_7[(i * 2) + j]) __attribute__((on("Any"))));

         }


            while (g_timer_debug != 0xdeadbeef)
            {
            }
            g_timer_debug = 0xdead;
            g_debug++;
        }


    }

    (OP_s_xsto_32(0, 9, 2) __attribute__((on("Any"))));

}
