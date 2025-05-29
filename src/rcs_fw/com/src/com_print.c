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

/**
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <xtensa/simcall.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"

#if (CPU_AX)
#include "ax_static_data_table.h"
#elif (CPU_RX)
#include "rx_static_data_table.h"
#elif (CPU_TX)
#include "tx_static_data_table.h"
#elif (CPU_CAL)
#include "rf_calib_static_data_table.h"
#endif

#if (CPU_ANA)
#define ANA_TRACE_BASE (0xbddd6f00)
#else
#include "com_static_data_table.h"
#endif

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TRACE_ADDRESS   (0x00)
#define ARG1_ADDRESS    (0x04)
#define ARG2_ADDRESS    (0x08)
#define ARG3_ADDRESS    (0x0C)
#define ARG4_ADDRESS    (0x10)
#define ARG5_ADDRESS    (0x14)
#define MSG_END_ADDRESS (0x18)
#define TEST_ADDRESS    (0x3C)
#define TEST_PASS       (0x0000000d)
#define TEST_FAIL       (0x00000002)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static uint32_t g_com_print_level = FW_INFO;
static uint32_t g_trace_base = 0x00000000;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

INTRINSIC_ALWAYS_INLINE static void HWW (uint32_t offset, uint32_t value)
{
    if (!g_trace_base)
    {
#if (CPU_ANA)
        g_trace_base = ANA_TRACE_BASE;
#else
        int const env_idx = get_tf (com_fw_config_lut, 0, fw_env);
#if (CPU_AX)
        g_trace_base = get_tf (ax_print_config_lut, env_idx, print_monitor_base_address);
#elif (CPU_RX)
        g_trace_base = get_tf (rx_print_config_lut, env_idx, print_monitor_base_address);
#elif (CPU_TX)
        g_trace_base = get_tf (tx_print_config_lut, env_idx, print_monitor_base_address);
#elif (CPU_CAL)
        g_trace_base = get_tf (cal_print_config_lut, env_idx, print_monitor_base_address);
#endif // not CPU_ANA
#endif // CPU_ANA
    }
    *(uint32_t *)(g_trace_base + offset) = value;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
void com_set_print_level (uint32_t level)
{
    g_com_print_level = level;

#if PRINT_CUSTOM_SIMCALL
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a8 __asm__("a8") = level;

    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a8));
#endif
}

uint32_t com_get_print_level ()
{
    return g_com_print_level;
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief          Trace Pass or fail
 * @return          none
 * todo: Include check for Pass/Fail
 ---------------------------------------------------------------------------------------------------------------------*/
void com_test_FW (bool state)
{
    if (state)
    {
        HWW (TEST_ADDRESS, TEST_PASS);
    }
    else
    {
        HWW (TEST_ADDRESS, TEST_FAIL);
    }
}

#if PRINT_C_PRINTF

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Error trace message from a specified code location.
 * @param [in]      file: File from which the message was printed.
 * @param [in]      line: Line number from which the message was printed.
 * @param [in]      str:  Format of the string to print.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_print_FW_ERR (char const *const p_file, char const *p_str, ...)
{
    printf ("FW_ERROR: %s  ", p_file);
    va_list args;
    va_start (args, p_str);
    vprintf (p_str, args);
    va_end (args);
    printf ("\n");
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Warning trace message from a specified code location.
 * @param [in]      file: File from which the message was printed.
 * @param [in]      line: Line number from which the message was printed.
 * @param [in]      str:  Format of the string to print.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_print_FW_WARN (char const *const p_file, char const *p_str, ...)
{
    if (g_com_print_level >= FW_WARN)
    {
        printf ("FW_WARNING: %s  ", p_file);
        va_list args;
        va_start (args, p_str);
        vprintf (p_str, args);
        va_end (args);
        printf ("\n");
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Note trace message from a specified code location.
 * @param [in]      file: File from which the message was printed.
 * @param [in]      line: Line number from which the message was printed.
 * @param [in]      str:  Format of the string to print.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_print_FW_NOTE (char const *const p_file, char const *p_str, ...)
{
    if (g_com_print_level >= FW_NOTE)
    {
        printf ("FW_NOTICE: %s  ", p_file);
        va_list args;
        va_start (args, p_str);
        vprintf (p_str, args);
        va_end (args);
        printf ("\n");
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Info trace message from a specified code location.
 * @param [in]      file: File from which the message was printed.
 * @param [in]      line: Line number from which the message was printed.
 * @param [in]      str:  Format of the string to print.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_print_FW_INFO (char const *const p_file, char const *p_str, ...)
{
    if (g_com_print_level >= FW_INFO)
    {
        printf ("FW_INFO: %s  ", p_file);
        va_list args;
        va_start (args, p_str);
        vprintf (p_str, args);
        va_end (args);
        printf ("\n");
    }
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Debug trace message from a specified code location.
 * @param [in]      file: File from which the message was printed.
 * @param [in]      line: Line number from which the message was printed.
 * @param [in]      str:  Format of the string to print.
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void com_print_FW_DEBUG (char const *const p_file, char const *p_str, ...)
{
    if (g_com_print_level >= FW_DEBUG)
    {
        printf ("FW_DEBUG: %s  ", p_file);
        va_list args;
        va_start (args, p_str);
        vprintf (p_str, args);
        va_end (args);
        printf ("\n");
    }
}

#elif PRINT_CUSTOM_SIMCALL

void com_vp_sys_exit (const int code)
{
    register int32_t a2 __asm__("a2") = SYS_exit;
    register int32_t a3 __asm__("a3") = U32 (code);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3));
}

void com_print_vp_arg0 (const char *const p_str)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a8));
}

void com_print_vp_arg1 (const char *const p_str, const int32_t arg1)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a3 __asm__("a3") = arg1;
    // The first of the 6 arguments is passed as the last argument to the simcall.
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3), "a"(a8));
}

void com_print_vp_arg2 (const char *const p_str, const int32_t arg1, const int32_t arg2)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a3 __asm__("a3") = arg1;
    register int32_t a4 __asm__("a4") = arg2;
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3), "a"(a4), "a"(a8));
}

void com_print_vp_arg3 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a3 __asm__("a3") = arg1;
    register int32_t a4 __asm__("a4") = arg2;
    register int32_t a5 __asm__("a5") = arg3;
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3), "a"(a4), "a"(a5), "a"(a8));
}

void com_print_vp_arg4 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3, const int32_t arg4)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a3 __asm__("a3") = arg1;
    register int32_t a4 __asm__("a4") = arg2;
    register int32_t a5 __asm__("a5") = arg3;
    register int32_t a6 __asm__("a6") = arg4;
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3), "a"(a4), "a"(a5), "a"(a6), "a"(a8));
}

void com_print_vp_arg5 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3, const int32_t arg4,
                        const int32_t arg5)
{
    register int32_t a2 __asm__("a2") = SYS_user_simcall;
    register int32_t a3 __asm__("a3") = arg1;
    register int32_t a4 __asm__("a4") = arg2;
    register int32_t a5 __asm__("a5") = arg3;
    register int32_t a6 __asm__("a6") = arg4;
    register int32_t a7 __asm__("a7") = arg5;
    register int32_t a8 __asm__("a8") = U32 (p_str);
    register int32_t ret_val __asm__("a2");
    register int32_t ret_err __asm__("a3");
    __asm__ volatile("simcall" : "=a"(ret_val), "=a"(ret_err) : "a"(a2), "a"(a3), "a"(a4), "a"(a5), "a"(a6), "a"(a7), "a"(a8));
}

#elif PRINT_CUSTOM_DEBUGCALL
#include "rcs_gpreg.h"
static int com_print_index = 0;

void com_print_rtl_arg0 (const char *const p_str)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

void com_print_rtl_arg1 (const char *const p_str, const int32_t arg1)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (ARG1_ADDRESS, arg1);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

void com_print_rtl_arg2 (const char *const p_str, const int32_t arg1, const int32_t arg2)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (ARG1_ADDRESS, arg1);
        HWW (ARG2_ADDRESS, arg2);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

void com_print_rtl_arg3 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (ARG1_ADDRESS, arg1);
        HWW (ARG2_ADDRESS, arg2);
        HWW (ARG3_ADDRESS, arg3);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

void com_print_rtl_arg4 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3, const int32_t arg4)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (ARG1_ADDRESS, arg1);
        HWW (ARG2_ADDRESS, arg2);
        HWW (ARG3_ADDRESS, arg3);
        HWW (ARG4_ADDRESS, arg4);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

void com_print_rtl_arg5 (const char *const p_str, const int32_t arg1, const int32_t arg2, const int32_t arg3, const int32_t arg4,
                         const int32_t arg5)
{
    uint32_t const level = U32 (p_str) >> 29;
    if (g_com_print_level >= level)
    {
        HWW (TRACE_ADDRESS, U32 (p_str) & CUSTOM_PRINT_ADDR_MASK);
        HWW (ARG1_ADDRESS, arg1);
        HWW (ARG2_ADDRESS, arg2);
        HWW (ARG3_ADDRESS, arg3);
        HWW (ARG4_ADDRESS, arg4);
        HWW (ARG5_ADDRESS, arg5);
        HWW (MSG_END_ADDRESS, com_print_index++);
    }
}

#endif
