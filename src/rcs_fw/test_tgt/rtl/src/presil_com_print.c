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

/**
 * @file    presil_com_print.c
 * @brief   wrappers for FW prints
 * @details This file contains wrappers for FW_PRINT() functions implemented
 *          in the FW to work in the pre-sil environment
 */

#include "rtl_api.h"
#include "stdarg.h"
#include "stdio.h"

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief      Functions imported from DPI export - need to be declared here with the same footprint
 *             See src/val/env/abc_soc/abc_soc_fw_funcs.sv, namespace egc_verif_fw_utils {
 * @param [in] str
 * @return          none
 */

extern "C"
{
    void SVTask_write_fatal (char const *str);
    void SVTask_write_error (char const *str);
    void SVTask_write_warning (char const *str);
    void SVTask_write_info (char const *str);
};

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief       stub for FW_PRINT (FW_ERR, ...);
 * @param [in] fmt and variable number of arguments
 * @return          none
 */

void com_stub_print_FW_ERR (char const *const fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_error (str);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief       stub for FW_PRINT (FW_WARN, ...);
 * @param [in] fmt and variable number of arguments
 * @return          none
 */

void com_stub_print_FW_WARN (char const *const fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_warning (str);
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief       stub for FW_PRINT (FW_NOTE, ...);
 * @param [in] fmt and variable number of arguments
 * @return          none
 */

void com_stub_print_FW_NOTE (char const *const fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_info (str);
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief       stub for FW_PRINT (FW_INFO, ...);
 * @param [in] fmt and variable number of arguments
 * @return          none
 */

void com_stub_print_FW_INFO (char const *const fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_info (str);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief       stub for FW_PRINT (FW_DEBUG, ...);
 * @param [in] fmt and variable number of arguments
 * @return          none
 */

void com_stub_print_FW_DEBUG (char const *const fmt, ...)
{
    va_list args;
    char str[1000];
    va_start (args, fmt);
    vsnprintf (str, sizeof (str), fmt, args);
    va_end (args);
    SVTask_write_info (str);
}
