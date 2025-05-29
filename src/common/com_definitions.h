/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/
#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

#include <stdbool.h>
#include <stdint.h>

enum cpu_id_t
{
    E_CPUID_TX0,
    E_CPUID_RX0,
    E_CPUID_CAL0,
    E_CPUID_NUM_CPUID
};
/*
#if CPU_TX
#define RCS_CPU E_CPUID_TX0
#elif CPU_RX
#define RCS_CPU E_CPUID_RX0
#elif CPU_CAL
#define RCS_CPU E_CPUID_CAL0
#elif CPU_ANA
#undef RCS_CPU
#else
#error RCS_CPU undefined.
#endif
*/
#define INTRINSIC_ALWAYS_INLINE __attribute__ ((always_inline))
#define INTRINSIC_NEVER_INLINE  __attribute__ ((noinline))
#define INTRINSIC_NOP           __asm__ volatile("nop")
#define INTRINSIC_BARRIER       __asm__ volatile("memw" : : : "memory")
#define INTRINSIC_RSYNC         __asm__ volatile("rsync" : : : "memory")
#define INTRINSIC_WAIT_FOR_IRQ  __asm__ volatile("waiti 0")

#define U8(a)  ((uint8_t)  (a))
#define S8(a)  ((int8_t)   (a))
#define U16(a) ((uint16_t) (a))
#define S16(a) ((int16_t)  (a))
#define U32(a) ((uint32_t) (a))
#define S32(a) ((int32_t)  (a))
#define U64(a) ((uint64_t) (a))
#define S64(a) ((int64_t)  (a))

#define U8_P(a)  ((uint8_t *)  (a))
#define S8_P(a)  ((int8_t *)   (a))
#define U16_P(a) ((uint16_t *) (a))
#define S16_P(a) ((int16_t *)  (a))
#define U32_P(a) ((uint32_t *) (a))
#define S32_P(a) ((int32_t *)  (a))
#define U64_P(a) ((uint64_t *) (a))
#define S64_P(a) ((int64_t *)  (a))

#ifdef __SIZEOF_INT128__
typedef unsigned __int128 uint128_t;
typedef __int128 int128_t;

#define U32_TO_U128(val_a, val_b, val_c, val_d) \
    (((uint128_t)val_a << 96) | ((uint128_t)val_b << 64) | ((uint128_t)val_c << 32) | ((uint128_t)val_d))
#define U64_TO_U128(val_a, val_b) (((uint128_t)val_a << 64) | (val_b))
#define U128LW64(val_a)           ((uint64_t)val_a)
#define U128UP64(val_a)           ((uint64_t) (val_a >> 64))
#endif // __SIZEOF_INT128__

#define STRINGIZE(x)  STRINGIZE2 (x)
#define STRINGIZE2(x) #x

#define ATOMIC_SCOPE_OPEN \
    {                     \
        uint32_t __interrupt__level__;
#define ATOMIC_SCOPE_CLOSE }

#define ATOMIC_SCOPED_BEGIN __asm__ volatile("rsil %0, 0xF" : "=a"(__interrupt__level__)::"memory");

#define ATOMIC_SCOPED_END                        \
    __asm__ volatile("wsr.ps %0 \n\t"            \
                     "esync"                     \
                     :                           \
                     : "a"(__interrupt__level__) \
                     : "memory");

/** Begin of an atomic section. */
#define ATOMIC_BEGIN  \
    ATOMIC_SCOPE_OPEN \
    ATOMIC_SCOPED_BEGIN

/** End of an atomic section. */
#define ATOMIC_END    \
    ATOMIC_SCOPED_END \
    ATOMIC_SCOPE_CLOSE

#define UNUSED_ARGUMENT(a) ((void)(a))

#endif // COMMON_DEFINITIONS_H

