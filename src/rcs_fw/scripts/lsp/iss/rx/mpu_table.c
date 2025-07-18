
// Generated by xt-genmpu.

#include <stdint.h>
#include <xtensa/hal.h>

#if defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
#include <assert.h>
#endif

#if defined (__cplusplus)
extern "C"
#endif
const struct xthal_MPU_entry
__xt_mpu_init_table[] __attribute__((section(".ResetHandler.text"))) = {
  XTHAL_MPU_ENTRY(0x00000000, 1, XTHAL_AR_RXrx, XTHAL_MEM_WRITEBACK), // srom
  XTHAL_MPU_ENTRY(0x00020000, 1, XTHAL_AR_NONE, XTHAL_MEM_DEVICE), // unused
  XTHAL_MPU_ENTRY(0x10000000, 1, XTHAL_AR_RWXrwx, XTHAL_MEM_NON_CACHEABLE), // iram0
  XTHAL_MPU_ENTRY(0x10020000, 1, XTHAL_AR_RWrw, XTHAL_MEM_NON_CACHEABLE), // dram0
  XTHAL_MPU_ENTRY(0x10040000, 1, XTHAL_AR_NONE, XTHAL_MEM_DEVICE), // unused
  XTHAL_MPU_ENTRY(0x10080000, 1, XTHAL_AR_RWXrwx, XTHAL_MEM_WRITEBACK), // sram
  XTHAL_MPU_ENTRY(0x10100000, 1, XTHAL_AR_NONE, XTHAL_MEM_DEVICE), // unused
};

#if defined (__cplusplus)
extern "C"
#endif
const uint32_t __xt_mpu_init_table_size __attribute__((section(".ResetHandler.text"))) = 7;

#if defined (__cplusplus)
extern "C"
#endif
const uint32_t __xt_mpu_init_cacheadrdis __attribute__((section(".ResetHandler.text"))) = 0x000000fe;

#if defined (__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
static_assert(sizeof(__xt_mpu_init_table)/sizeof(__xt_mpu_init_table[0]) == 7, "Incorrect MPU table size");
#endif
