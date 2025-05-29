# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 543 "<built-in>" 3
# 1 "<command line>" 1
# 12 "<command line>"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipupseudo.h" 1



# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/iputypes.h" 1




typedef char __int8;
typedef short __int16;
typedef int __int32;

typedef char __sint8;
typedef short __sint16;
typedef int __sint32;

typedef unsigned char __uint8;
typedef unsigned short __uint16;
typedef unsigned int __uint32;


# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_custom_types.h" 1



# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_macroutils.h" 1
# 5 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_custom_types.h" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/custom_types_ve32.h" 1






typedef unsigned int __upacked32x1;

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

typedef __int20 __packed128x20 __attribute__((ext_vector_type(128)));
typedef __int20 __spacked128x20 __attribute__((ext_vector_type(128)));
typedef unsigned __int20 __upacked128x20 __attribute__((ext_vector_type(128)));

typedef __int20 vec128i20 __attribute__((ext_vector_type(128)));
typedef __int20 vec128si20 __attribute__((ext_vector_type(128)));
typedef unsigned __int20 vec128ui20 __attribute__((ext_vector_type(128)));

typedef __spacked128x20 __int2560;
typedef __spacked128x20 __sint2560;
typedef __upacked128x20 __uint2560;
# 7 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_custom_types.h" 2
# 18 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/iputypes.h" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_memory_types.h" 1





# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/memory_types_ve32.h" 1
# 7 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_memory_types.h" 2
# 20 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/iputypes.h" 2
# 5 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipupseudo.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_pseudoop_defs.h" 1
# 13 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_pseudoop_defs.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/pseudoop_defs__ve32.inc" 1





void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __spacked32x32 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __spacked32x32 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __upacked32x32 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __upacked32x32 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __spacked32x32 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __upacked32x32 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __spacked32x32 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __upacked32x32 __b, int __c, int __d, int __e);



void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __spacked128x8 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __spacked128x8 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __upacked128x8 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __upacked128x8 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __spacked128x8 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __upacked128x8 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __spacked128x8 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __upacked128x8 __b, int __c, int __d, int __e);



void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __spacked128x20 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __spacked128x20 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, __upacked128x20 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, __upacked128x20 __b);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __spacked128x20 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(int __a, __upacked128x20 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __spacked128x20 __b, int __c, int __d, int __e);

void __attribute__((__nodebug__, overloadable))
OP___dump_fmt(void* __a, __upacked128x20 __b, int __c, int __d, int __e);

enum stateId_t {
    bp_s2_tsu_MulticoreFuState1Type = 0x20101,
    bp_s2_tsu_MulticoreFuState2Type = 0x20102,
    simd0_vcom0_vcom_VcomFuStatePccType = 0x5020b,
    simd0_vcom0_vcom_VcomFuStatePkrType = 0x5020f,
    simd0_vcom0_vcom_VcomFuStateLutType = 0x50210,
    simd0_vcom0_vcom_VcomFuStateSbfType = 0x5020e,
    simd0_vcom0_vcom_VcomFuStatePrvType = 0x5020c,
    simd0_vcom0_vcom_VcomFuStateMlcType = 0x5020d,
};

void __attribute__((__nodebug__))
OP___dump_state(unsigned __a);
# 14 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipu_pseudoop_defs.h" 2
# 6 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipupseudo.h" 2


void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, int __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, int __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, unsigned int __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, unsigned int __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, unsigned long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, unsigned long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, long long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, long long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, unsigned long long __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, unsigned long long __b);




void __attribute__((__nodebug__, overloadable))
OP___dump(int __a, const void* __b);

void __attribute__((__nodebug__, overloadable))
OP___dump(void* __a, const void* __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, unsigned __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, unsigned __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, int __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, int __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, unsigned long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, unsigned long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, long long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, long long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, unsigned long long __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, unsigned long long __b);




void __attribute__((__nodebug__, overloadable))
OP___udump(int __a, const void* __b);

void __attribute__((__nodebug__, overloadable))
OP___udump(void* __a, const void* __b);

void __attribute__((__nodebug__))
OP___printdec(int __a);

void __attribute__((__nodebug__))
OP___printhex(int __a);

void __attribute__((__nodebug__))
OP___printchar(int __a);

void __attribute__((__nodebug__))
OP___printstring(char* __a);

void __attribute__((__nodebug__))
OP___vcd_update(char* __a, int __b);

void __attribute__((__nodebug__))
OP___schedule();

int __attribute__((__nodebug__))
OP___cycles();

void __attribute__((__nodebug__))
OP___listing_on();

void __attribute__((__nodebug__))
OP___listing_off();

void __attribute__((__nodebug__))
OP___warnings_on();

void __attribute__((__nodebug__))
OP___warnings_off();

void __attribute__((__nodebug__, deprecated))
OP___csim_assert(int __a);

void __attribute__((__nodebug__))
OP___assert(int __a);

void __attribute__((__nodebug__))
OP___pragma(char* __a);
# 13 "<command line>" 2
# 1 "<built-in>" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c" 2
# 32 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/common_macros.h" 1
# 32 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 1
# 33 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/hrt/include/ve32_params.h" 1
# 34 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 1
# 28 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_alu_c.h" 1
# 29 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_unfied_op_c.h" 1
# 30 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_lut_c.h" 1
# 31 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2


# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_c.h" 1
# 34 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_fmt_c.h" 1
# 36 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_consts.h" 2
# 35 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h" 1
# 29 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/common_types.h" 1
# 33 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/common_types.h"
typedef char Int8;
typedef short Int16;
typedef int Int32;
typedef long long Int64;





typedef unsigned char uInt8;
typedef unsigned short uInt16;
typedef unsigned int uInt32;
typedef unsigned long long uInt64;





typedef struct { Int64 L40, H40; } Int80;
# 60 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/common_types.h"
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
# 30 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_common_types.h" 2



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
    unsigned int lut[16][(2*(1024/32))];
    unsigned int pkr[4*(1024/32)];
    unsigned int ovf;
    unsigned int mlc[1];
    unsigned int sbf[8][(2*(1024/32))];
    unsigned int prv[2];
    unsigned int pcc[4];
} VCOM_ST;
# 36 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_debug.h" 1
# 37 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 49 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 1
# 10 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 1
# 28 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/generic.h" 1
# 29 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/crun_support.h" 1
# 30 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 1
# 25 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/attributes_volcano.h" 1
# 26 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 2
# 31 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 1
# 27 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/customops.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h" 1
# 11 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin.h" 1








# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h" 1
# 10 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_cancel(unsigned int A, unsigned int E)
{
  return __builtin_ipu_OP_mc_cancel((unsigned int) (A), (unsigned int) (E));
}
# 28 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_mc_complete(unsigned int E)
{
  return __builtin_ipu_OP_mc_complete((unsigned int) (E));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_mc_complete_and_cancel(unsigned int E)
{
  return __builtin_ipu_OP_mc_complete_and_cancel((unsigned int) (E));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_mc_get_state(unsigned int A, unsigned int E)
{
  return __builtin_ipu_OP_mc_get_state((unsigned int) (A), (unsigned int) (E));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_init(unsigned int A, unsigned int E)
{
  return __builtin_ipu_OP_mc_init((unsigned int) (A), (unsigned int) (E));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_init_local_idc(unsigned int A, unsigned int E)
{
  return __builtin_ipu_OP_mc_init_local_idc((unsigned int) (A), (unsigned int) (E));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_invalidate(unsigned int E)
{
  return __builtin_ipu_OP_mc_invalidate((unsigned int) (E));
}
# 100 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_reset(unsigned int E)
{
  return __builtin_ipu_OP_mc_reset((unsigned int) (E));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_mc_set_rate(unsigned int A, unsigned int E)
{
  return __builtin_ipu_OP_mc_set_rate((unsigned int) (A), (unsigned int) (E));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_abssat(int A)
{
  return __builtin_ipu_OP_s_abssat((int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_add(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_add((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_add_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_add_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_and(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_and((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_and_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_and_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_bfi(int A, int B, int C)
{
  return __builtin_ipu_OP_s_bfi((int) (A), (int) (B), (int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_eq(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_eq((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_eq_i(unsigned int A, int B)
{
  return __builtin_ipu_OP_s_eq_i((unsigned int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_eq_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_eq_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ge_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_ge_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_gt_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_gt_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_imm(int A)
{
  return __builtin_ipu_OP_s_imm((int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_imm_u(unsigned int A)
{
  return __builtin_ipu_OP_s_imm_u((unsigned int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_immh(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_immh((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_inv(unsigned int A)
{
  return __builtin_ipu_OP_s_inv((unsigned int) (A));
}
# 322 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_16(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_16((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_16_i(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_16_i((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_16s(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_16s((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_16s_i(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_16s_i((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_32(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_32((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_32_i(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_32_i((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_8(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_8((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_8_i(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_8_i((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_8s(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_8s((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ldo_8s_i(int A, int B)
{
  return __builtin_ipu_OP_s_ldo_8s_i((int) (A), (int) (B));
}
# 482 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_le(int A, int B)
{
  return __builtin_ipu_OP_s_le((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_le_i(int A, int B)
{
  return __builtin_ipu_OP_s_le_i((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_le_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_le_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_le_u(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_le_u((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_le_u_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_le_u_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lred(unsigned int A, unsigned int B, unsigned int C)
{
  return __builtin_ipu_OP_s_lred((unsigned int) (A), (unsigned int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lt(int A, int B)
{
  return __builtin_ipu_OP_s_lt((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lt_i(int A, int B)
{
  return __builtin_ipu_OP_s_lt_i((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lt_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_lt_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lt_u(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_lt_u((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_lt_u_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_lt_u_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_max(int A, int B)
{
  return __builtin_ipu_OP_s_max((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_max_i(int A, int B)
{
  return __builtin_ipu_OP_s_max_i((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_max_u(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_max_u((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_max_u_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_max_u_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_min(int A, int B)
{
  return __builtin_ipu_OP_s_min((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_min_i(int A, int B)
{
  return __builtin_ipu_OP_s_min_i((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_min_u(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_min_u((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_min_u_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_min_u_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_modadd(unsigned int ua, int sb, unsigned int uc)
{
  return __builtin_ipu_OP_s_modadd((unsigned int) (ua), (int) (sb), (unsigned int) (uc));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_modadd_i(unsigned int ua, int sb, unsigned int uc)
{
  return __builtin_ipu_OP_s_modadd_i((unsigned int) (ua), (int) (sb), (unsigned int) (uc));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_moddec(unsigned int ua, unsigned int uc)
{
  return __builtin_ipu_OP_s_moddec((unsigned int) (ua), (unsigned int) (uc));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_modinc(unsigned int ua, unsigned int uc)
{
  return __builtin_ipu_OP_s_modinc((unsigned int) (ua), (unsigned int) (uc));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_mul(int A, int B)
{
  return __builtin_ipu_OP_s_mul((int) (A), (int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_mul_i(int A, int B)
{
  return __builtin_ipu_OP_s_mul_i((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_mul_u(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_mul_u((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_mul_u_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_mul_u_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_mux(unsigned int A, unsigned int B, unsigned int C)
{
  return __builtin_ipu_OP_s_mux((unsigned int) (A), (unsigned int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_ne_sel(int A, int B, int C, int D)
{
  return __builtin_ipu_OP_s_ne_sel((int) (A), (int) (B), (int) (C), (int) (D));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_neg(unsigned int A)
{
  return __builtin_ipu_OP_s_neg((unsigned int) (A));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_neq(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_neq((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_neq_i(unsigned int A, int B)
{
  return __builtin_ipu_OP_s_neq_i((unsigned int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_or(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_or((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_or_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_or_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_pass(unsigned int A)
{
  return __builtin_ipu_OP_s_pass((unsigned int) (A));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_se_16(unsigned int A)
{
  return __builtin_ipu_OP_s_se_16((unsigned int) (A));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_se_8(unsigned int A)
{
  return __builtin_ipu_OP_s_se_8((unsigned int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_shl(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shl((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_shl_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shl_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_shra(int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shra((int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_shra_i(int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shra_i((int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_shrl(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shrl((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_shrl_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_shrl_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_sl16or(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_sl16or((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_16(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_16((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_16_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_16_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_32_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_32_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_32x2(int A, int B, unsigned int C, unsigned int D)
{
  return __builtin_ipu_OP_s_stau_32x2((int) (A), (int) (B), (unsigned int) (C), (unsigned int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_8(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_8((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stau_8_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stau_8_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_16(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_16((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_16_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_16_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_32_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_32_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_8(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_8((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sto_8_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_sto_8_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_16(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_16((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_16_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_16_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_32_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_32_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_32x2(int A, int B, unsigned int C, unsigned int D)
{
  return __builtin_ipu_OP_s_stoi_32x2((int) (A), (int) (B), (unsigned int) (C), (unsigned int) (D));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_8(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_8((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stoi_8_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_stoi_8_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stomi_32(int A, int B, int L, unsigned int C)
{
  return __builtin_ipu_OP_s_stomi_32((int) (A), (int) (B), (int) (L), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_stomi_32x2(int A, int B, int L, unsigned int C, unsigned int D)
{
  return __builtin_ipu_OP_s_stomi_32x2((int) (A), (int) (B), (int) (L), (unsigned int) (C), (unsigned int) (D));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_sub(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_sub((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_sub_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_sub_i((unsigned int) (A), (unsigned int) (B));
}
# 1166 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_xldo_32(int A, int B)
{
  return __builtin_ipu_OP_s_xldo_32((int) (A), (int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_xldo_32_i(int A, int B)
{
  return __builtin_ipu_OP_s_xldo_32_i((int) (A), (int) (B));
}
# 1194 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_xor(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_xor((unsigned int) (A), (unsigned int) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_xor_i(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_s_xor_i((unsigned int) (A), (unsigned int) (B));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_xstau_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_xstau_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_xsto_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_xsto_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_xsto_32_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_xsto_32_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_xstoi_32(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_xstoi_32((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_s_xstoi_32_i(int A, int B, unsigned int C)
{
  return __builtin_ipu_OP_s_xstoi_32_i((int) (A), (int) (B), (unsigned int) (C));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ze_16(unsigned int A)
{
  return __builtin_ipu_OP_s_ze_16((unsigned int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_s_ze_8(unsigned int A)
{
  return __builtin_ipu_OP_s_ze_8((unsigned int) (A));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_std_pass_v0(__spacked128x8 A)
{
  return __builtin_ipu_OP_std_pass_v0((__spacked128x8) (A));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_std_pass_v1(__spacked128x8 A)
{
  return __builtin_ipu_OP_std_pass_v1((__spacked128x8) (A));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_v_acc_read(unsigned int A, __spacked128x20 B)
{
  return __builtin_ipu_OP_v_acc_read((unsigned int) (A), (__spacked128x20) (B));
}





static __inline__ __spacked128x20 __attribute__((__always_inline__, __nodebug__))
OP_v_acc_write(unsigned int A, __spacked128x8 B, __spacked128x20 C)
{
  return __builtin_ipu_OP_v_acc_write((unsigned int) (A), (__spacked128x8) (B), (__spacked128x20) (C));
}
# 1368 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ __spacked32x32 __attribute__((__always_inline__, __nodebug__))
OP_v_ld_1024(unsigned int A)
{
  return __builtin_ipu_OP_v_ld_1024((unsigned int) (A));
}
# 1382 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ __spacked32x32 __attribute__((__always_inline__, __nodebug__))
OP_v_ldo_1024(unsigned int A, int B)
{
  return __builtin_ipu_OP_v_ldo_1024((unsigned int) (A), (int) (B));
}





static __inline__ __spacked32x32 __attribute__((__always_inline__, __nodebug__))
OP_v_ldo_1024_i(unsigned int A, int B)
{
  return __builtin_ipu_OP_v_ldo_1024_i((unsigned int) (A), (int) (B));
}
# 1446 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_v_mux(__spacked128x8 A, __spacked128x8 B, unsigned int C)
{
  return __builtin_ipu_OP_v_mux((__spacked128x8) (A), (__spacked128x8) (B), (unsigned int) (C));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_v_pass(__spacked128x8 A)
{
  return __builtin_ipu_OP_v_pass((__spacked128x8) (A));
}
# 1470 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_st_1024(unsigned int A, __spacked128x8 B)
{
  return __builtin_ipu_OP_v_st_1024((unsigned int) (A), (__spacked128x8) (B));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_sthoi_2048(unsigned int A, unsigned int B, unsigned int C, __spacked128x8 D, __spacked128x8 E)
{
  return __builtin_ipu_OP_v_sthoi_2048((unsigned int) (A), (unsigned int) (B), (unsigned int) (C), (__spacked128x8) (D), (__spacked128x8) (E));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_sto_1024(unsigned int A, int B, __spacked128x8 C)
{
  return __builtin_ipu_OP_v_sto_1024((unsigned int) (A), (int) (B), (__spacked128x8) (C));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_sto_1024_i(unsigned int A, int B, __spacked128x8 C)
{
  return __builtin_ipu_OP_v_sto_1024_i((unsigned int) (A), (int) (B), (__spacked128x8) (C));
}
# 1518 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_stoi_1024(unsigned int A, int B, __spacked128x8 C)
{
  return __builtin_ipu_OP_v_stoi_1024((unsigned int) (A), (int) (B), (__spacked128x8) (C));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_stoi_1024_circ(unsigned int A, unsigned int B, unsigned int C, unsigned int D, __spacked128x8 E)
{
  return __builtin_ipu_OP_v_stoi_1024_circ((unsigned int) (A), (unsigned int) (B), (unsigned int) (C), (unsigned int) (D), (__spacked128x8) (E));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_stoi_1024_i(unsigned int A, int B, __spacked128x8 C)
{
  return __builtin_ipu_OP_v_stoi_1024_i((unsigned int) (A), (int) (B), (__spacked128x8) (C));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_stoi_2048(unsigned int A, unsigned int B, __spacked128x8 C, __spacked128x8 D)
{
  return __builtin_ipu_OP_v_stoi_2048((unsigned int) (A), (unsigned int) (B), (__spacked128x8) (C), (__spacked128x8) (D));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_stoi_2048_circ(unsigned int A, unsigned int B, unsigned int C, unsigned int D, __spacked128x8 E, __spacked128x8 F)
{
  return __builtin_ipu_OP_v_stoi_2048_circ((unsigned int) (A), (unsigned int) (B), (unsigned int) (C), (unsigned int) (D), (__spacked128x8) (E), (__spacked128x8) (F));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_vcom_mlc_rw(unsigned int A)
{
  return __builtin_ipu_OP_v_vcom_mlc_rw((unsigned int) (A));
}





static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_vcom_pcc_rw(unsigned int A, unsigned int B)
{
  return __builtin_ipu_OP_v_vcom_pcc_rw((unsigned int) (A), (unsigned int) (B));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_v_vcom_pkr_rw(unsigned int A, __spacked128x8 B)
{
  return __builtin_ipu_OP_v_vcom_pkr_rw((unsigned int) (A), (__spacked128x8) (B));
}
# 1610 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ unsigned int __attribute__((__always_inline__, __nodebug__))
OP_v_vcom_tbl_write(unsigned int A, __spacked128x8 B, __spacked128x8 C)
{
  return __builtin_ipu_OP_v_vcom_tbl_write((unsigned int) (A), (__spacked128x8) (B), (__spacked128x8) (C));
}
# 1624 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin__ve32.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_vec_addr_st_1024(unsigned int A, unsigned int B, __spacked128x8 C, __spacked128x8 D)
{
  return __builtin_ipu_OP_v_vec_addr_st_1024((unsigned int) (A), (unsigned int) (B), (__spacked128x8) (C), (__spacked128x8) (D));
}





static __inline__ __spacked128x8 __attribute__((__always_inline__, __nodebug__))
OP_v_xbar_cmpr_sel(unsigned int A, unsigned int B, unsigned int C, unsigned int D, __spacked128x8 E, __spacked128x8 F)
{
  return __builtin_ipu_OP_v_xbar_cmpr_sel((unsigned int) (A), (unsigned int) (B), (unsigned int) (C), (unsigned int) (D), (__spacked128x8) (E), (__spacked128x8) (F));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_1024(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xstau_1024((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_1024_i(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xstau_1024_i((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1)
{
  return __builtin_ipu_OP_v_xstau_1024x2((int) (A), (int) (B), (__spacked128x8) (D0), (__spacked128x8) (D1));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_32(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xstau_32((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_32_i(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xstau_32_i((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstau_32x2(int A, int B, unsigned int D0, unsigned int D1)
{
  return __builtin_ipu_OP_v_xstau_32x2((int) (A), (int) (B), (unsigned int) (D0), (unsigned int) (D1));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_1024(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xsto_1024((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_1024_i(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xsto_1024_i((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1)
{
  return __builtin_ipu_OP_v_xsto_1024x2((int) (A), (int) (B), (__spacked128x8) (D0), (__spacked128x8) (D1));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_32(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xsto_32((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_32_i(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xsto_32_i((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_v_xsto_32x2(int A, int B, unsigned int D0, unsigned int D1)
{
  return __builtin_ipu_OP_v_xsto_32x2((int) (A), (int) (B), (unsigned int) (D0), (unsigned int) (D1));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_1024(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xstoi_1024((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_1024_i(int A, int B, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xstoi_1024_i((int) (A), (int) (B), (__spacked128x8) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_1024x2(int A, int B, __spacked128x8 D0, __spacked128x8 D1)
{
  return __builtin_ipu_OP_v_xstoi_1024x2((int) (A), (int) (B), (__spacked128x8) (D0), (__spacked128x8) (D1));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_32(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xstoi_32((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_32_i(int A, int B, unsigned int D0)
{
  return __builtin_ipu_OP_v_xstoi_32_i((int) (A), (int) (B), (unsigned int) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstoi_32x2(int A, int B, unsigned int D0, unsigned int D1)
{
  return __builtin_ipu_OP_v_xstoi_32x2((int) (A), (int) (B), (unsigned int) (D0), (unsigned int) (D1));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstomi_1024(int A, int B, int L, __spacked128x8 D0)
{
  return __builtin_ipu_OP_v_xstomi_1024((int) (A), (int) (B), (int) (L), (__spacked128x8) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstomi_1024x2(int A, int B, int L, __spacked128x8 D0, __spacked128x8 D1)
{
  return __builtin_ipu_OP_v_xstomi_1024x2((int) (A), (int) (B), (int) (L), (__spacked128x8) (D0), (__spacked128x8) (D1));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstomi_32(int A, int B, int L, unsigned int D0)
{
  return __builtin_ipu_OP_v_xstomi_32((int) (A), (int) (B), (int) (L), (unsigned int) (D0));
}





static __inline__ int __attribute__((__always_inline__, __nodebug__))
OP_v_xstomi_32x2(int A, int B, int L, unsigned int D0, unsigned int D1)
{
  return __builtin_ipu_OP_v_xstomi_32x2((int) (A), (int) (B), (int) (L), (unsigned int) (D0), (unsigned int) (D1));
}




static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_sleep(void) {
  __builtin_ipu_OP_s_sleep();
}



static __inline__ void __attribute__((__always_inline__, __nodebug__))
OP_s_idle(void) {
  __builtin_ipu_OP_s_idle();
}
# 10 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/ipuintrin.h" 2
# 12 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano/hive/customops_volcano.h" 2
# 28 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 2
# 32 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/config.h" 1
# 33 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 11 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss/performance_counters.h" 1
# 49 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss/performance_counters.h"
static inline unsigned int OP_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_ipu_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))) );



  return clc_l;
}

static inline unsigned int OP_exe_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_ipu_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))) );



  return exc_l;
}

static inline unsigned int OP_slp_cycles() {
  unsigned int exc_h, exc_l, slc_h, slc_l, clc_h, clc_l;

  (exc_h = __builtin_ipu_OP_getallc((unsigned int *) (&exc_l), (unsigned int *) (&slc_h), (unsigned int *) (&slc_l), (unsigned int *) (&clc_h), (unsigned int *) (&clc_l)) __attribute__((on("Any"))) );



  return slc_l;
}
# 13 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_core_api.h" 2
# 50 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_types.h" 1
# 26 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_types.h"
typedef __int2560 wvector_t;
typedef __int1024 uwvector_t;
# 51 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_macros.h" 1
# 193 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_macros.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_B_CLONE(int IP0, int IP1, int IP3, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
    unsigned int OP0, OP1;
    __int1024 VIP2 __attribute__((uninit)), VIP3 __attribute__((uninit));
    __int1024 VOP1;

    (OP0 = __builtin_ipu_OP_v_alu_2((unsigned int) (IP0), (unsigned int) (IP1), (unsigned int) (0), (unsigned int) (IP3), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8) (VIP2), (__spacked128x8) (VIP3), (unsigned int *) (&OP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 52 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_hivecc_ldst_macros.h" 1
# 53 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2





# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h" 1
# 35 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h" 1
# 53 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_A(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
    unsigned int OP0, OP1;
    __int1024 VOP1;

    (OP0 = __builtin_ipu_OP_v_alu_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8) (VIP1), (unsigned int *) (&OP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 76 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_B(int IP0, __int1024 VIP0, __int1024 VIP1, unsigned int *OP0, unsigned int *OP1)
{
    __int1024 VOP0, VOP1;

    (*OP0 = __builtin_ipu_OP_v_alu_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8) (VIP1), (unsigned int *) (&*OP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 97 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_C(int IP0, int IP1, __int1024 VIP0, __int1024 *VOP0)
{
    unsigned int OP0, OP1;
    __int1024 VOP1;

    (OP0 = __builtin_ipu_OP_v_alu_1((unsigned int) (IP0), (unsigned int) (IP1), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (unsigned int *) (&OP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 118 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ALU_1_D(int IP0, __int1024 VIP0, __int1024 *VOP0, __int1024 *VOP1)
{
    unsigned int OP0, OP1;

    (OP0 = __builtin_ipu_OP_v_alu_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (unsigned int *) (&OP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 138 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_A(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP1;
   __int2560 WIP0 __attribute__((uninit));
   __int2560 WOP0;

   (*VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIP1), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&WOP0)) __attribute__((on("Any"))) );
}
# 161 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_B(int IP0, __int1024 VIP0, __int1024 VIP1, __int2560 WIP0, __int2560 *WOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP0, VOP1;

   (VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIP1), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&*WOP0)) __attribute__((on("Any"))) );
}
# 184 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_C(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP1;
   __int2560 WIP0 __attribute__((uninit));
   __int2560 WOP0;

   (*VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0), (unsigned int) (1), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&WOP0)) __attribute__((on("Any"))) );

}
# 210 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_D(int IP0, __int2560 WIP0, __int1024 *VOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP1;
   __int2560 WOP0;

   (*VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&WOP0)) __attribute__((on("Any"))) );
}
# 237 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_E(int IP0, __int1024 VIP0, __int2560 WIP0, __int1024 *VOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP1;
   __int2560 WOP0;

   (*VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0), (unsigned int) (0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIP0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&WOP0)) __attribute__((on("Any"))) );
}
# 259 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MUL_1_F(int IP0, __int1024 VIP0, __int1024 *VOP0)
{
   __int1024 VIPDMY __attribute__((uninit));
   __int1024 VOP1;
   __int2560 WIP0 __attribute__((uninit));
   __int2560 WOP0;

   (*VOP0 = __builtin_ipu_OP_v_mul_1((unsigned int) (IP0 | (2 << 0)), (unsigned int) (0), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x8) (VIPDMY), (__spacked128x20) (WIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1), (__spacked128x20 *) (&WOP0)) __attribute__((on("Any"))) );
}
# 36 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_alu.h" 2
# 59 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_mul.h" 1
# 60 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h" 1
# 27 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/vcom_fmt_c.h" 1
# 28 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h" 2
# 125 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MW_INTERLEAVE_32(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (2 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 170 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_16(__int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (2 << 27), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 243 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MW_DEINTERLEAVE_32(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (3 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 288 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_DEINTERLEAVE_16(__int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (3 << 27), (unsigned int) (0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 351 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MS_ROTATE(int IP0, int IP1, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (1 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (IP1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 390 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_SET_32(int IP0, int IP1, __int1024 VIP0, __int1024 *VOP0)
{
    int OP0;__int1024 VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (5 << 27), (unsigned int) (IP0), (unsigned int) (IP1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) ) __attribute__((ignore_all_state));

}
# 429 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_GET_32(int IP0, __int1024 VIP0, int *OP0)
{
    __int1024 VOP0, VOP1;
    (*OP0 = __builtin_ipu_OP_v_format((unsigned int) (4 << 27), (unsigned int) (IP0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) ) __attribute__((ignore_all_state));

}
# 464 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_CLONE_32(int IP0, __int1024 *VOP0)
{
    int OP0; __int1024 VIP0 __attribute__((uninit)), VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (7 << 27), (unsigned int) (IP0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) ) __attribute__((ignore_all_state));
}
# 529 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_PARALLEL_EXTRACT(int IP0, int IP1, __int1024 VIP0, int *OP0, __int1024 *VOP0)
{
    __int1024 VIP1 __attribute__((uninit)), VOP1;
    (*OP0 = __builtin_ipu_OP_v_format((unsigned int) (8 << 27), (unsigned int) (IP0 & 0x1f), (unsigned int) (IP1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 608 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_VEC_CLONE_MW(int IP0, int IP1, __int1024 VIP0, __int1024 *VOP0)
{
    int OP0; __int1024 VIP1 __attribute__((uninit)), VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (10 << 27), (unsigned int) (IP0), (unsigned int) (IP1), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );

}
# 671 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_BY_N_1X64(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (11 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 736 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INTERLEAVE_BY_N_2X32(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (12 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 780 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_COMP_REVERSE(int IP0, __int1024 VIP0, __int1024 *VOP0)
{
    int OP0; __int1024 VIP1 __attribute__((uninit)), VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (13 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 825 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_COMP_SWAP(int IP0, __int1024 VIP0, __int1024 *VOP0)
{
    int OP0; __int1024 VIP1 __attribute__((uninit)), VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (14 << 27), (unsigned int) (IP0 & 0x7), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 873 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_ROTATE_MERGE(int IP0, __int1024 VIP0, __int1024 VIP1, int *OP0, __int1024 *VOP0)
{
    __int1024 VOP1;
    (*OP0 = __builtin_ipu_OP_v_format((unsigned int) (15 << 27), (unsigned int) (IP0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );

}
# 913 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INSERT_ROTATE(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (16 << 27), (unsigned int) (IP0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 951 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_INT_INSERT_ROTATE(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0, __int1024 *VOP1)
{
    int OP0;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (17 << 27), (unsigned int) (IP0), (unsigned int) (0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1)) __attribute__((on("Any"))) );
}
# 1106 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_MASK_MUX(int IP0, __int1024 VIP0, __int1024 VIP1, __int1024 *VOP0)
{
    int OP0; __int1024 VOP1;
    (OP0 = __builtin_ipu_OP_v_format((unsigned int) (6 << 27), (unsigned int) (0), (unsigned int) (IP0), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0), (__spacked128x8 __attribute__((ipumem(3))) *) (&VOP1)) __attribute__((on("Any"))) );
}
# 1191 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_macros_derived_format.h"
static __inline__ void __attribute__((__always_inline__, __nodebug__))
inl_V_PEX_MERGE(int IP0, int IP1, __int1024 VIP0, __int1024 VIP1, int *OP0, __int1024 *VOP0, __int1024 *VOP1)
{
    (*OP0 = __builtin_ipu_OP_v_format((unsigned int) (9 << 27), (unsigned int) (IP1), (unsigned int) (IP0|2), (__spacked128x8) (VIP0), (__spacked128x8) (VIP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP1), (__spacked128x8 __attribute__((ipumem(3))) *) (&*VOP0)) __attribute__((on("Any"))) );


}
# 61 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include/ve32_appl_target.h" 2
# 33 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 1
# 30 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h"
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/attributes.h" 1
# 31 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/customops.h" 1
# 32 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/hive/support.h" 2
# 34 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c" 2

# 1 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/defines.h" 1
# 35 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c" 2
# 50 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c"
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
# 88 "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c"
inline void init_timer(int cycles)
{

    (OP_s_xsto_32(0, 3, 3) __attribute__((on("Any"))) );

    (OP_s_xsto_32(0, 4, cycles) __attribute__((on("Any"))) );

    (OP_s_xsto_32(0, 6, 0x1) __attribute__((on("Any"))) );

    (OP_s_xsto_32(0, 7, 0x4000 + (0x28)) __attribute__((on("Any"))) );

    (OP_s_xsto_32(0, 8, 0xdeadbeef) __attribute__((on("Any"))) );
}







void jesd_tx() __attribute__((ipu_entry))
{
    int i, j;
    int iter_max = 64/2;
    int num_vec_per_stream = 2;

    g_host_indicator = 0;
    g_vex_exit = 0;

    OP___printstring("jesd_tx : start \n");
    init_timer(2048);

    while (g_host_indicator == 0)
    {

    }

    (OP_s_xsto_32(0, 9, 1) __attribute__((on("Any"))) );

    while(g_vex_exit == 0)
    {
        for(i = 0; (i < iter_max); i++)
        {
      for(j = 0; j < num_vec_per_stream; j++)
      {
       (OP_v_xsto_1024_i(g_dest_buffer0_base, 0x0, vbuffer_0[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer1_base, 0x0, vbuffer_1[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer2_base, 0x0, vbuffer_2[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer3_base, 0x0, vbuffer_3[(i * 2) + j]) __attribute__((on("Any"))) );

       (OP_v_xsto_1024_i(g_dest_buffer4_base, 0x0, vbuffer_4[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer5_base, 0x0, vbuffer_5[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer6_base, 0x0, vbuffer_6[(i * 2) + j]) __attribute__((on("Any"))) );
       (OP_v_xsto_1024_i(g_dest_buffer7_base, 0x0, vbuffer_7[(i * 2) + j]) __attribute__((on("Any"))) );

         }


            while (g_timer_debug != 0xdeadbeef)
            {
            }
            g_timer_debug = 0xdead;
            g_debug++;
        }


    }

    (OP_s_xsto_32(0, 9, 2) __attribute__((on("Any"))) );

}
