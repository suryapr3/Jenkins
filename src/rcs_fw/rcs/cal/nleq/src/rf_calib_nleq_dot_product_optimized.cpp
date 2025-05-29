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
 * @file    rf_calib_nleq_dot_product_optimized.cpp
 * @brief   Implementation of hand coded optimized version of dot product of vectors.
 * @details The implementation covers the dot product of one vector with 4, 2 and 1 other vectors
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include <xtensa/config/core-isa.h>
#include <xtensa/config/system.h>
#include <xtensa/tie/xt_bben.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implement the dot product of one vector with another vector
 * @param [in]      p_input_1: Pointer to the first vector
 * @param [in]      p_input_2: Pointer to the second vector
 * @param [out]     P_output:  Pointer to the float where the result will be stored
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_dot_product_1_opt (const float *__restrict p_input_1, const float *__restrict p_input_2, int size, float *__restrict p_output)
{
    int j;
    xb_vecN_2xf32 vx_0, vx_1;
    xb_vecN_2xf32 vAccum_0;
    xtfloat out;
    xtfloat *p_out = (xtfloat *)p_output;
    xb_vecN_2xf32 *__restrict ptr_xv_0 = (xb_vecN_2xf32 *)p_input_1;
    xb_vecN_2xf32 *__restrict ptr_xv_1 = (xb_vecN_2xf32 *)p_input_2;
    BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
    BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
    vAccum_0 = BBE_MULN_2XF32 (vx_0, vx_1);
    for (j = 0; j < size - 4; j = j + 4)
    {
        BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
        BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
        BBE_MULAN_2XF32 (vAccum_0, vx_0, vx_1);
    }
    out = xtfloat_loadi (p_out, 0);
    vx_0 = BBE_MOVN_2XF32_FROMF32 (out);
    vx_1 = BBE_ADDN_2XF32 (vx_0, vAccum_0);
    out = BBE_RADDN_2XF32 (vx_1);
    xtfloat_storei (out, p_out, 0);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implement the dot product of one vector with 4 other vectors
 * @param [in]      p_input_1: Pointer to the first vector
 * @param [in]      p_input_2: Pointer to the second vector
 * @param [out]     P_output:  Pointer to the float where the result will be stored
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_dot_product_4_opt (const float *__restrict p_input_base, const float *__restrict p_input_start, int size,
                                 float *__restrict p_output)
{
    int j;
    xb_vecN_2xf32 vx_0, vx_1, vx_2, vx_3, vx_4;
    xb_vecN_2xf32 vAccum_0, vAccum_1, vAccum_2, vAccum_3;
    xb_vecN_2xf32 out;
    xb_vecN_2xf32 *p_out = (xb_vecN_2xf32 *)p_output;
    xb_vecN_2xf32 *p_out_pre = p_out;
    xtfloat temp;
    xb_vecNx16 temp1;
    xb_vecNx16 temp2;
    xb_vecNx16 temp3;
    xb_vecNx16 temp4;
    xb_vecN_4x64 temp_v64;
    valign va_out;

    xb_vecN_2xf32 *__restrict ptr_xv_0 = (xb_vecN_2xf32 *)p_input_base;
    xb_vecN_2xf32 *__restrict ptr_xv_1 = (xb_vecN_2xf32 *)p_input_start;
    xb_vecN_2xf32 *__restrict ptr_xv_2 = (xb_vecN_2xf32 *)(p_input_start + size);
    xb_vecN_2xf32 *__restrict ptr_xv_3 = (xb_vecN_2xf32 *)(p_input_start + size * 2);
    xb_vecN_2xf32 *__restrict ptr_xv_4 = (xb_vecN_2xf32 *)(p_input_start + size * 3);
    BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
    BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
    BBE_LVN_2XF32_IP (vx_2, ptr_xv_2, 16);
    BBE_LVN_2XF32_IP (vx_3, ptr_xv_3, 16);
    BBE_LVN_2XF32_IP (vx_4, ptr_xv_4, 16);
    vAccum_0 = BBE_MULN_2XF32 (vx_0, vx_1);
    vAccum_1 = BBE_MULN_2XF32 (vx_0, vx_2);
    vAccum_2 = BBE_MULN_2XF32 (vx_0, vx_3);
    vAccum_3 = BBE_MULN_2XF32 (vx_0, vx_4);
    for (j = 0; j < size - 4; j = j + 4)
    {
        BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
        BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
        BBE_LVN_2XF32_IP (vx_2, ptr_xv_2, 16);
        BBE_LVN_2XF32_IP (vx_3, ptr_xv_3, 16);
        BBE_LVN_2XF32_IP (vx_4, ptr_xv_4, 16);
        BBE_MULAN_2XF32 (vAccum_0, vx_0, vx_1);
        BBE_MULAN_2XF32 (vAccum_1, vx_0, vx_2);
        BBE_MULAN_2XF32 (vAccum_2, vx_0, vx_3);
        BBE_MULAN_2XF32 (vAccum_3, vx_0, vx_4);
    }

    temp = BBE_RADDN_2XF32 (vAccum_0);
    vAccum_0 = BBE_MOVN_2XF32_FROMF32 (temp);
    temp = BBE_RADDN_2XF32 (vAccum_1);
    vAccum_1 = BBE_MOVN_2XF32_FROMF32 (temp);
    temp = BBE_RADDN_2XF32 (vAccum_2);
    vAccum_2 = BBE_MOVN_2XF32_FROMF32 (temp);
    temp = BBE_RADDN_2XF32 (vAccum_3);
    vAccum_3 = BBE_MOVN_2XF32_FROMF32 (temp);
    BBE_DSELN_2XF32I (vx_1, vx_0, vAccum_1, vAccum_0, 2);
    BBE_DSELN_2XF32I (vx_1, vx_2, vAccum_3, vAccum_2, 2);
    BBE_DSELN_2XF32I (vx_1, vx_3, vx_2, vx_0, 6);
    va_out = BBE_LAN_2XF32_PP (p_out);
    BBE_LAN_2XF32_IP (vx_4, va_out, p_out);
    vx_0 = BBE_ADDN_2XF32 (vx_3, vx_4);
    va_out = BBE_ZALIGN ();
    p_out = p_out_pre;
    BBE_SAN_2XF32_IP (vx_0, va_out, p_out);
    BBE_SAN_2XF32POS_FP (va_out, p_out);
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implement the dot product of one vector with 2 other vectors
 * @param [in]      p_input_1: Pointer to the first vector
 * @param [in]      p_input_2: Pointer to the second vector
 * @param [out]     P_output:  Pointer to the float where the result will be stored
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
void rf_calib_dot_product_2_opt (const float *__restrict p_input_1, const float *__restrict p_input_2, int size, float *__restrict p_output)
{
    int j;
    xb_vecN_2xf32 vx_0, vx_1, vx_2;
    xb_vecN_2xf32 vAccum_0, vAccum_1;
    xtfloat out;
    xtfloat *p_out = (xtfloat *)p_output;
    xb_vecN_2xf32 *__restrict ptr_xv_0 = (xb_vecN_2xf32 *)p_input_1;
    xb_vecN_2xf32 *__restrict ptr_xv_1 = (xb_vecN_2xf32 *)p_input_2;
    xb_vecN_2xf32 *__restrict ptr_xv_2 = (xb_vecN_2xf32 *)(p_input_2 + size);
    BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
    BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
    BBE_LVN_2XF32_IP (vx_2, ptr_xv_2, 16);
    vAccum_0 = BBE_MULN_2XF32 (vx_0, vx_1);
    vAccum_1 = BBE_MULN_2XF32 (vx_0, vx_2);
    for (j = 0; j < size - 4; j = j + 4)
    {
        BBE_LVN_2XF32_IP (vx_0, ptr_xv_0, 16);
        BBE_LVN_2XF32_IP (vx_1, ptr_xv_1, 16);
        BBE_LVN_2XF32_IP (vx_2, ptr_xv_2, 16);
        BBE_MULAN_2XF32 (vAccum_0, vx_0, vx_1);
        BBE_MULAN_2XF32 (vAccum_1, vx_0, vx_2);
    }
    out = xtfloat_loadi (p_out, 0);
    vx_0 = BBE_MOVN_2XF32_FROMF32 (out);
    vx_1 = BBE_ADDN_2XF32 (vx_0, vAccum_0);
    out = BBE_RADDN_2XF32 (vx_1);
    xtfloat_storeip (out, p_out, 4);
    out = xtfloat_loadi (p_out, 0);
    vx_0 = BBE_MOVN_2XF32_FROMF32 (out);
    vx_1 = BBE_ADDN_2XF32 (vx_0, vAccum_1);
    out = BBE_RADDN_2XF32 (vx_1);
    xtfloat_storei (out, p_out, 0);
}
