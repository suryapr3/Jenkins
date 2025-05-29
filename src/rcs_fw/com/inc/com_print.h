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
#ifndef COMMON_PRINT_H
#define COMMON_PRINT_H

#include "com_definitions.h"
#include <stdbool.h>
#include <stdint.h>
enum
{
    FW_ERR = 0,
    FW_WARN = 1,
    FW_NOTE = 2,
    FW_INFO = 3,
    FW_DEBUG = 4,
};
#ifdef __cplusplus
extern "C" {
#endif
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Set the trace level for logging
 * @param [in]      level: Trace level to display
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_set_print_level (uint32_t level);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Get the trace level for logging
 * @param [in]      none
 * @return          Trace level being displayed
 * -------------------------------------------------------------------------------------------------------------------*/
uint32_t com_get_print_level (void);

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief          Trace Pass or fail
 * @return          none
 ---------------------------------------------------------------------------------------------------------------------*/
void com_test_FW (bool state);

#if PRINT_C_PRINTF

#define MACRO_DISPATCHER(func, severity) func##severity
#define FW_PRINT(sev, ...)                                                                                   \
    do {                                                                                                     \
        MACRO_DISPATCHER (com_print_, sev) (STRINGIZE(__FILENAME__) ":" STRINGIZE(__LINE__), __VA_ARGS__); \
    } while (0)

#define FW_ERR_(fmt, ...) FW_PRINT (FW_ERR, fmt, ...)

// void com_print_FW_ERR (char const *const p_file, uint32_t line, char const *p_str, ...);
// void com_print_FW_WARN (char const *const p_file, uint32_t line, char const *p_str, ...);
// void com_print_FW_NOTE (char const *const p_file, uint32_t line, char const *p_str, ...);
// void com_print_FW_INFO (char const *const p_file, uint32_t line, char const *p_str, ...);
// void com_print_FW_DEBUG (char const *const p_file, uint32_t line, char const *p_str, ...);
void com_print_FW_ERR (char const *const p_file, char const *p_str, ...);
void com_print_FW_WARN (char const *const p_file, char const *p_str, ...);
void com_print_FW_NOTE (char const *const p_file, char const *p_str, ...);
void com_print_FW_INFO (char const *const p_file, char const *p_str, ...);
void com_print_FW_DEBUG (char const *const p_file, char const *p_str, ...);
#elif PRINT_CUSTOM_SIMCALL

#define VA_NUM_ARGS(...)                                                                                                                 \
    VA_NUM_ARGS_IMPL (, ##__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, \
                      7, 6, 5, 4, 3, 2, 1, 0)
#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, \
                         _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...)                                                          \
    N

#define macro_dispatcher(func, ...)     macro_dispatcher_ (func, VA_NUM_ARGS (__VA_ARGS__))
#define macro_dispatcher_(func, nargs)  macro_dispatcher__ (func, nargs)
#define macro_dispatcher__(func, nargs) func##nargs

#define CONST_VAR_NAME__(a) debug_str_##a
#define CONST_VAR_NAME_(a)  CONST_VAR_NAME__ (a)
#define CONST_VAR_NAME(a)   CONST_VAR_NAME_ (a)

#define CUSTOM_PRINT_ADDR_MASK (0x1FFFFFFF)
#define CREATE_CONST_STRING(fmt, counter)                                                      \
    static const char __attribute__ ((section (".dram0.rodata"))) CONST_VAR_NAME (counter)[] = \
        (STRINGIZE (__FILENAME__) ":" STRINGIZE (__LINE__) ": " fmt)

#define COMBINE_PTR_WITH_LOGLEVEL(str, log_level) (const char *const) ((uintptr_t (&str) & CUSTOM_PRINT_ADDR_MASK) | ((log_level) << 29))

#define _printf_args0(p_str)                         com_print_vp_arg0 (p_str)
#define _printf_args1(p_str, arg1)                   com_print_vp_arg1 (p_str, S32 (arg1))
#define _printf_args2(p_str, arg1, arg2)             com_print_vp_arg2 (p_str, S32 (arg1), S32 (arg2))
#define _printf_args3(p_str, arg1, arg2, arg3)       com_print_vp_arg3 (p_str, S32 (arg1), S32 (arg2), S32 (arg3))
#define _printf_args4(p_str, arg1, arg2, arg3, arg4) com_print_vp_arg4 (p_str, S32 (arg1), S32 (arg2), S32 (arg3), S32 (arg4))
#define _printf_args5(p_str, arg1, arg2, arg3, arg4, arg5) \
    com_print_vp_arg5 (p_str, S32 (arg1), S32 (arg2), S32 (arg3), S32 (arg4), S32 (arg5))

#define _print(lvl, ...)                  _printf_args (lvl, __VA_ARGS__)
#define _printf_args(log_level, fmt, ...) _printf_args_ (log_level, fmt, __COUNTER__, ##__VA_ARGS__)
#define _printf_args_(log_level, fmt, counter, ...)                                                                                    \
    do {                                                                                                                               \
        CREATE_CONST_STRING (fmt, counter);                                                                                            \
        macro_dispatcher (_printf_args, __VA_ARGS__) (COMBINE_PTR_WITH_LOGLEVEL (CONST_VAR_NAME (counter), log_level), ##__VA_ARGS__); \
    } while (0)

void INTRINSIC_ALWAYS_INLINE com_print_vp_arg0 (const char *const p_str);
void INTRINSIC_ALWAYS_INLINE com_print_vp_arg1 (const char *const p_str, const int32_t arg1);
void INTRINSIC_ALWAYS_INLINE com_print_vp_arg2 (const char *const p_str, const int32_t arg1, const int32_t arg2);
void INTRINSIC_ALWAYS_INLINE com_print_vp_arg3 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3);
void INTRINSIC_ALWAYS_INLINE com_print_vp_arg4 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3,
                                                const int32_t arg4);
void INTRINSIC_ALWAYS_INLINE com_print_vp_arg5 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3,
                                                const int32_t arg4, const int32_t arg5);
#ifdef FW_DEBUG_DISABLE
#define FW_DEBUG_(...)
#else
#define FW_DEBUG_(fmt, ...) _print (FW_DEBUG, fmt, ##__VA_ARGS__)
#endif
#ifdef FW_NOTE_DISABLE
#define FW_NOTE_(...)
#else
#define FW_NOTE_(fmt, ...) _print (FW_NOTE, fmt, ##__VA_ARGS__)
#endif
#define FW_WARN_(fmt, ...)      _print (FW_WARNING, fmt, ##__VA_ARGS__)
#define FW_ERR_(fmt, ...)       _print (FW_ERR, fmt, ##__VA_ARGS__)
#define FW_PRINT(lvl, fmt, ...) _print (lvl, fmt, ##__VA_ARGS__)

/* ---------------------------------------------------------------------------------------------------------------------
 * RTL PRINT
 * ---------------------------------------------------------------------------------------------------------------------*/
#elif PRINT_CUSTOM_DEBUGCALL

#define VA_NUM_ARGS(...)                                                                                                                 \
    VA_NUM_ARGS_IMPL (, ##__VA_ARGS__, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, \
                      7, 6, 5, 4, 3, 2, 1, 0)
#define VA_NUM_ARGS_IMPL(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, \
                         _24, _25, _26, _27, _28, _29, _30, _31, _32, N, ...)                                                          \
    N

#define macro_dispatcher(func, ...)     macro_dispatcher_ (func, VA_NUM_ARGS (__VA_ARGS__))
#define macro_dispatcher_(func, nargs)  macro_dispatcher__ (func, nargs)
#define macro_dispatcher__(func, nargs) func##nargs

#define CONST_VAR_NAME__(a) debug_str_##a
#define CONST_VAR_NAME_(a)  CONST_VAR_NAME__ (a)
#define CONST_VAR_NAME(a)   CONST_VAR_NAME_ (a)

#define CUSTOM_PRINT_ADDR_MASK (0x1FFFFFFF)
#define CREATE_CONST_DEBUG_STRING(fmt, counter)                                                      \
    static const char __attribute__ ((section (".dram0.debug.rodata"))) CONST_VAR_NAME (counter)[] = \
        (STRINGIZE (__FILENAME__) ":" STRINGIZE (__LINE__) ":" fmt "   ")

#define COMBINE_PTR_WITH_LOGLEVEL(str, log_level) (const char *const) (((uintptr_t) (&str) & CUSTOM_PRINT_ADDR_MASK) | ((log_level) << 29))

#define _printf_rtl_args0(p_str)                         com_print_rtl_arg0 (p_str)
#define _printf_rtl_args1(p_str, arg1)                   com_print_rtl_arg1 (p_str, S32 (arg1))
#define _printf_rtl_args2(p_str, arg1, arg2)             com_print_rtl_arg2 (p_str, S32 (arg1), S32 (arg2))
#define _printf_rtl_args3(p_str, arg1, arg2, arg3)       com_print_rtl_arg3 (p_str, S32 (arg1), S32 (arg2), S32 (arg3))
#define _printf_rtl_args4(p_str, arg1, arg2, arg3, arg4) com_print_rtl_arg4 (p_str, S32 (arg1), S32 (arg2), S32 (arg3), S32 (arg4))
#define _printf_rtl_args5(p_str, arg1, arg2, arg3, arg4, arg5) \
    com_print_rtl_arg5 (p_str, S32 (arg1), S32 (arg2), S32 (arg3), S32 (arg4), S32 (arg5))

#define _print(lvl, ...)                  _printf_args (lvl, __VA_ARGS__)
#define _printf_args(log_level, fmt, ...) _printf_args_ (log_level, fmt, __COUNTER__, ##__VA_ARGS__)
#define _printf_args_(log_level, fmt, counter, ...)                                                                                        \
    do {                                                                                                                                   \
        CREATE_CONST_DEBUG_STRING (fmt, counter);                                                                                          \
        macro_dispatcher (_printf_rtl_args, __VA_ARGS__) (COMBINE_PTR_WITH_LOGLEVEL (CONST_VAR_NAME (counter), log_level), ##__VA_ARGS__); \
    } while (0)

void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg0 (const char *const p_str);
void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg1 (const char *const p_str, const int32_t arg1);
void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg2 (const char *const p_str, const int32_t arg1, const int32_t arg2);
void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg3 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3);
void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg4 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3,
                                                 const int32_t arg4);
void INTRINSIC_ALWAYS_INLINE com_print_rtl_arg5 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3,
                                                 const int32_t arg4, const int32_t arg5);

#ifdef FW_DEBUG_DISABLE
#define FW_DEBUG_(...)
#else
#define FW_DEBUG_(fmt, ...) _print (FW_DEBUG, fmt, ##__VA_ARGS__)
#endif
#ifdef FW_NOTE_DISABLE
#define FW_NOTE_(...)
#else
#define FW_NOTE_(fmt, ...) _print (FW_NOTE, fmt, ##__VA_ARGS__)
#endif
#ifdef FW_PRINT_DISABLE
#define FW_PRINT(lvl, fmt, ...) ;
#else
#define FW_PRINT(lvl, fmt, ...) _print (lvl, fmt, ##__VA_ARGS__)
#endif
#define FW_WARN_(fmt, ...)      _print (FW_WARNING, fmt, ##__VA_ARGS__)
#define FW_ERR_(fmt, ...)       _print (FW_ERR, fmt, ##__VA_ARGS__)

#else

#define FW_PRINT(sev, ...) ;
#define FW_ERR_(fmt, ...)  ;

#endif
#ifdef __cplusplus
}
#endif
#endif
