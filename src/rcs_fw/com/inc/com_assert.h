/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/
#ifndef COMMON_ASSERT_H
#define COMMON_ASSERT_H

#include "com_print.h"

// Compile time assert
#define COMPILE_ASSERT(expr) static int compile_assertion[(expr) ? 1 : -1]

// Runtime assert
#if (COVERITY_EN)

#define require RT_ASSERT
#define ensure  RT_ASSERT

extern void __coverity_panic__ (void);
// check that expression evaluates to true
#define RT_ASSERT(expr)            \
    {                              \
        if (!(expr))               \
            __coverity_panic__ (); \
    }

// assert without checking.
#define RT_ASSERT_HERE() __coverity_panic__ ();

// check if pointer != NULL.
#define RT_ASSERT_POINTER(p)       \
    {                              \
        if ((p) == NULL)           \
            __coverity_panic__ (); \
    }

// check if not equal.
#define RT_ASSERT_NOT_EQUAL(a, b)  \
    {                              \
        if ((a) == (b))            \
            __coverity_panic__ (); \
    }

// check if equal.
#define RT_ASSERT_EQUAL(a, b)      \
    {                              \
        if ((a) != (b))            \
            __coverity_panic__ (); \
    }

// check if in range
#define RT_ASSERT_IN_RANGE(val, low, high, name) \
    {                                            \
        if (((val) < (low)) || ((val) > (high))) \
            __coverity_panic__ ();               \
    }

#define RT_ASSERT_EX(expr, ...) RT_ASSERT (expr)
#define RT_ASSERT_HERE_EX(...)  RT_ASSERT_HERE ()

#elif (FW_ASSERT_EN) // FW assert

#define VP_PRINT_ERROR(...)  FW_PRINT(FW_ERR, __VA_ARGS__)

#if (UNIT)

extern uint32_t g_assertion_counter;
#define ASSERTION_ERROR(text, ...)        \
    VP_PRINT_ERROR ("ASSERTION ERROR: " text, ##__VA_ARGS__); \
    g_assertion_counter++;

#else // NOT UNIT

#define ASSERTION_ERROR(text, ...)        \
    VP_PRINT_ERROR ("ASSERTION ERROR: " text, ##__VA_ARGS__);

#endif // UNIT

#define require    RT_ASSERT
#define ensure     RT_ASSERT
#define require_ex RT_ASSERT_EX
#define ensure_ex  RT_ASSERT_EX

// ASSERT check that expression evaluates to true
#define RT_ASSERT(expr)                         \
    {                                           \
        if (!(expr))                            \
        {                                       \
            ASSERTION_ERROR (STRINGIZE (expr)); \
        }                                       \
    }

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

// ASSERT check with custom message
#define RT_ASSERT_EX(expr, ...)            \
    {                                      \
        if (!(expr))                       \
        {                                  \
            ASSERTION_ERROR (__VA_ARGS__); \
        }                                  \
    }

// ASSERT_HERE with custom message
#define RT_ASSERT_HERE_EX(...) ASSERTION_ERROR (__VA_ARGS__);

#else // Production code => do nothing

#define require(expr) // ASSERT for contract programming precondition
#define ensure(expr)  // ASSERT for contract programming postcondition

#define RT_ASSERT(expr)                                // ASSERT check that expression evaluates to true.
#define RT_ASSERT_HERE()                               // ASSERT regardless of expression.
#define RT_ASSERT_POINTER(p)                           // ASSERT_POINTER check if pointer != NULL.
#define RT_ASSERT_NOT_EQUAL(a, b)                      // ASSERT_NOT_EQUAL check if not equal.
#define RT_ASSERT_EQUAL(a, b)                          // ASSERT_EQUAL check if equal.
#define RT_ASSERT_IN_RANGE(val, range_low, range_high) // ASSERT_IN_RANGE check if in range.
#define RT_ASSERT_EX(expr, ...)                        // ASSERT check that expression evaluates to true.
#define RT_ASSERT_HERE_EX(...)                         // ASSERT regardless of expression.

#endif // COVERITY_ASSERT_EN

#endif // COMMON_ASSERT_H
