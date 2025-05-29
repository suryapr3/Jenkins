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
#ifndef PRESIL_COMMON_ASSERT_H
#define PRESIL_COMMON_ASSERT_H

#include <stdbool.h>
#include <stdint.h>

#define STRINGIZE(x)  STRINGIZE2 (x)
#define STRINGIZE2(x) #x

#define VP_PRINT_ERROR(...) com_assert_stub_printf (__VA_ARGS__);

#define ASSERTION_ERROR(text, ...) VP_PRINT_ERROR (text, ##__VA_ARGS__);

#define RT_ASSERT(expr)                         \
    {                                           \
        if (!(expr))                            \
        {                                       \
            ASSERTION_ERROR (STRINGIZE (expr)); \
        }                                       \
    } //! ASSERT check that expression evaluates to true.

// ASSERT_HERE regardless of expression.
#define RT_ASSERT_HERE() ASSERTION_ERROR ("ASSERTED_HERE");

// ASSERT_POINTER check if pointer != NULL.
#define RT_ASSERT_POINTER(p)                             \
    {                                                    \
        if ((p) == 0)                                    \
        {                                                \
            ASSERTION_ERROR ("pointer " #p " is NULL!"); \
        }                                                \
    }

// ASSERT_NOT_EQUAL check if not equal.
#define RT_ASSERT_NOT_EQUAL(a, b)                                \
    {                                                            \
        if ((a) == (b))                                          \
        {                                                        \
            ASSERTION_ERROR ("Values are EQUAL! (n = %d)", (a)); \
        }                                                        \
    }

// ASSERT_EQUAL check if equal.
#define RT_ASSERT_EQUAL(a, b)                                               \
    {                                                                       \
        if ((a) != (b))                                                     \
        {                                                                   \
            ASSERTION_ERROR ("Values are NOT EQUAL! (%d != %d)", (a), (b)); \
        }                                                                   \
    }

// ASSERT_IN_RANGE check if in range.
#define RT_ASSERT_IN_RANGE(val, range_low, range_high)                                                              \
    {                                                                                                               \
        if (!(((val) >= (range_low)) && ((val) <= (range_high))))                                                   \
        {                                                                                                           \
            ASSERTION_ERROR (#val "=%d is NOT IN RANGE! (low=%d, high=%d)", (int)(val), (range_low), (range_high)); \
        }                                                                                                           \
    }

void com_assert_stub_printf (char const *const p_str, ...);
#endif
