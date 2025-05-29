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
 * @file    presil_com_assert.c
 * @brief   wrappers for FW asserts
 * @details This file contains wrappers for RT_ASSERT() functions implemented
 *          in the FW to work in the pre-sil environment
 */

#include "presil_com_assert.h"
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
    void SVTask_write_warning (char const *str);
};

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief      wrapper for asserts
 * @param [in]  str and variable number of arguments
 * @return          none
 */

void com_assert_stub_printf (char const *const p_str, ...)
{
    va_list args;
    char str[1000];
    va_start (args, p_str);
    vsnprintf (str, sizeof (str), p_str, args);
    va_end (args);
    SVTask_write_warning (str);
}
