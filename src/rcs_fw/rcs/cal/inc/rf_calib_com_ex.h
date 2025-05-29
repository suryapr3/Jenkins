/*
 * Copyright (c) 2022 by Cadence Design Systems, Inc.  ALL RIGHTS RESERVED.
 * These coded instructions, statements, and computer programs are the
 * copyrighted works and confidential proprietary information of
 * Cadence Design Systems Inc.  They may be adapted and modified by bona fide
 * purchasers for internal use, but neither the original nor any adapted
 * or modified version may be disclosed or distributed to third parties
 * in any manner, medium, or form, in whole or in part, without the prior
 * written consent of Cadence Design Systems Inc.  This software and its
 * derivatives are to be executed solely on products incorporating a Cadence
 * Design Systems processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef RF_CALIB_COM_EX_H
#define RF_CALIB_COM_EX_H
#include "com_eigen.h"
#include <complex.h>
#include <xtensa/config/core-isa.h>
#include <xtensa/config/system.h>
#include <xtensa/tie/xt_bben.h>
#define SIMD_N_X_2 (SIMD_N * 2)

/* Macros for 8-bit memory alignment attributes */
#define ALIGN_SIMD  __attribute__ ((aligned (2 * XCHAL_BBEN_SIMD_WIDTH)))
#define ALIGN_2SIMD __attribute__ ((aligned (4 * XCHAL_BBEN_SIMD_WIDTH)))
#define ALIGN64     __attribute__ ((aligned (64)))
#define ALIGN32     __attribute__ ((aligned (32)))
#define ALIGN16     __attribute__ ((aligned (16)))

/* Macros for memory placement attributes */
#if defined(XSHAL_RAM_AVAIL_VSIZE)
#define PLACE_IN_SRAM __attribute__ ((section (".sram.data")))
#else
#define PLACE_IN_SRAM
#endif

#if !defined(NO_MEM_MODEL)
#if defined(XCHAL_DATARAM0_SIZE)
#define PLACE_IN_DRAM0 __attribute__ ((section (".dram0.data")))
#else
#define PLACE_IN_DRAM0 PLACE_IN_SRAM
#endif
#if defined(XCHAL_DATARAM1_SIZE)
#define PLACE_IN_DRAM1 __attribute__ ((section (".dram1.data")))
#else
#define PLACE_IN_DRAM1 PLACE_IN_DRAM0
#endif
#if defined(XCHAL_INSTRAM0_SIZE)
#define PLACE_IN_IRAM0 __attribute__ ((section (".iram0.text")))
#else
#define PLACE_IN_IRAM0
#endif
#else
#define PLACE_IN_DRAM0 PLACE_IN_SRAM
#define PLACE_IN_DRAM1 PLACE_IN_SRAM
#endif

/* log2(BBE_SIMD_WIDTH) */
#if XCHAL_BBEN_SIMD_WIDTH == 4
#define LOG2_SIMD_WIDTH 2
#define LOG2_SIMD_N     2
#elif XCHAL_BBEN_SIMD_WIDTH == 8
#define LOG2_SIMD_WIDTH 3
#define LOG2_SIMD_N     3
#elif XCHAL_BBEN_SIMD_WIDTH == 16
#define LOG2_SIMD_WIDTH 4
#define LOG2_SIMD_N     4
#elif XCHAL_BBEN_SIMD_WIDTH == 32
#define LOG2_SIMD_WIDTH 5
#define LOG2_SIMD_N     5
#elif XCHAL_BBEN_SIMD_WIDTH == 64
#define LOG2_SIMD_WIDTH 6
#define LOG2_SIMD_N     6
#endif

#define LOG2_SIMD_N_4 (LOG2_SIMD_N - 2)
#define LOG2_SIMD_N_2 (LOG2_SIMD_N - 1)
#define LOG2_SIMD_2N  (LOG2_SIMD_N + 1)
#define LOG2_SIMD_4N  (LOG2_SIMD_N + 2)

//#define restrict __restrict
#define NASSERT(x)                            \
    {                                         \
        (void)__builtin_expect ((x) != 0, 1); \
    }

#define INLINE __attribute__ ((always_inline)) static

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/*DP isa macro for KP1 */
#if XCHAL_BBEN_SIMD_WIDTH == 8

#if !defined(xb_vecN_8xcf64)
#define xb_vecN_8xcf64 xb_vecN_4xf64
#endif

#if !defined(BBE_LVN_8XCF64_XP)
#define BBE_LVN_8XCF64_XP BBE_LVN_4XF64_XP
#endif

#if !defined(BBE_LVN_8XCF64_IP)
#define BBE_LVN_8XCF64_IP BBE_LVN_4XF64_IP
#endif

#if !defined(BBE_SVN_8XCF64_XP)
#define BBE_SVN_8XCF64_XP BBE_SVN_4XF64_XP
#endif

#if !defined(BBE_SVN_8XCF64_IP)
#define BBE_SVN_8XCF64_IP BBE_SVN_4XF64_IP
#endif

#if !defined(BBE_LSRN_8XCF64_IP)
#define BBE_LSRN_8XCF64_IP(_a, _b, _c)                  \
    {                                                   \
        BBE_LVN_4XF64_IP (_a, (xb_vecN_4xf64 *)_b, _c); \
    }
#endif

#if !defined(BBE_MULN_8XCF64)

#define BBE_MULN_8XCF64(_b, _c)                 \
    ({                                          \
        xb_vecN_4xf64 _a, acc0, acc1;           \
        acc0 = BBE_MULMN_4XF64 (_b, _c, 0, 4);  \
        acc1 = BBE_MULMN_4XF64 (_b, _c, 1, 11); \
        _a = BBE_ADDN_4XF64 (acc0, acc1);       \
        _a;                                     \
    })

#endif // BBE_MULN_8XCF64
#if !defined(BBE_MULAN_8XCF64)

#define BBE_MULAN_8XCF64(_a, _b, _c)           \
    {                                          \
        BBE_MULMASN_4XF64 (_a, _b, _c, 0, 4);  \
        BBE_MULMASN_4XF64 (_a, _b, _c, 1, 11); \
    }

#endif // BBE_MULAN_8XCF64

#if !defined(BBE_MULJN_8XCF64)

#define BBE_MULJN_8XCF64(_b, _c)                \
    ({                                          \
        xb_vecN_4xf64 _a, acc0, acc1;           \
        acc0 = BBE_MULMN_4XF64 (_b, _c, 2, 4);  \
        acc1 = BBE_MULMN_4XF64 (_b, _c, 0, 11); \
        _a = BBE_ADDN_4XF64 (acc0, acc1);       \
        _a;                                     \
    })

#endif // BBE_MULJN_8XCF64

#if !defined(BBE_MULJAN_8XCF64)

#define BBE_MULJAN_8XCF64(_a, _b, _c)          \
    {                                          \
        BBE_MULMASN_4XF64 (_a, _b, _c, 2, 4);  \
        BBE_MULMASN_4XF64 (_a, _b, _c, 0, 11); \
    }

#endif // BBE_MULJAN_8XCF64

#if !defined(BBE_CONJN_8XCF64)
#define BBE_CONJN_8XCF64 BBE_CONJN_4XF64
#endif

#endif
#endif // RF_CALIB_COM_EX_H
