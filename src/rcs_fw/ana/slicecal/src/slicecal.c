/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2023 Intel Corporation
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
 * @file    slicecal.c
 * @brief   slicecal implementation
 * @details main driver for slicecal
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_heap.h"
#include "dithercal.h"
#include "offset_cal.h"
#include "stdint.h"
#include "compute_sop_lut.h"
#include "compute_w0_w11.h"
#include "slicecal.h"
#include <string.h>
#include <xtensa/core-macros.h>
#include "com_print.h"
#include "asc_wrap.h"
#include "ana_common.h"
#include <xtensa/tie/xt_FP.h>
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 **********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static asc_quad_ant_t asc_quad_ant;
#if UNIT
extern asc_wrap_t asc_wrap[];
#endif
static float_t pow_2[33] = {1,         2,         4,         8,          16,         32,        64,       128,      256,
                            512,       1024,      2048,      4096,       8192,       16384,     32768,    65536,    131072,
                            262144,    524288,    1048576,   2097152,    4194304,    8388608,   16777216, 33554432, 67108864,
                            134217728, 268435456, 536870912, 1073741824, 2147483648, 4294967296};
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
float *p_acc;
uint32_t *p_cnt;
uint32_t *p_wgt_cal_lut;
float *p_valid_flag;
float *p_wgt_combination;
float *p_combinations;
float_t sar_lut[SAR_LUT_SIZE];
float_t w0_w11[NUM_WEIGHTS];
float_t dither_coeff[NUM_DITHER_COEFFS];
float_t offset_coeff;
float *p_Rn_running_sum;
uint32_t *p_Rn_running_idx;
float *p_dither_acc;
uint32_t *p_dither_acc_cnt;
float *p_dither_cal_valid_flag;
uint32_t *p_majority_vote_lut;
float *p_dither_lut;
T_ANA_EXT_INFO ana_ext_info __attribute__ ((section (".ana_ext_info_section")));
// T_ANA_DEBUG ana_debug[ANA_DEBUG_SIZE] __attribute__ ((section (".ana_debug_section")));
// T_ANA_PROFILE ana_profile __attribute__ ((section (".ana_profile_section")));
// T_ASC_SLICE_WGT_SAR_LUT_CAL_SG_INFO wgt_sar_lut_cal_sg_info[2][8] __attribute__ ((section (".ana_tables_from_rx_core")));
// T_ASC_SLICE_DITHER_OFFSET_CAL_SG_INFO dither_offset_cal_sg_info[2] __attribute__ ((section (".ana_tables_from_rx_core")));
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void populate_wgt_cal_lut (uint32_t *p_lut);
static void construct_wgt_combination ();
static uint32_t scale_float (float_t value, bool is_signed, uint32_t word_length, uint32_t fract_length);
static void init_asc_wrap ();
static void compute_linear_combination ();
static void compute_maj_vote_lut (uint32_t *p_majority_vote_lut);
/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static uint32_t scale_float (float_t value, bool is_signed, uint32_t word_length, uint32_t fract_length)
{
    uint32_t overflow_mask;
    uint32_t positive_sat_value_for_false_is_signed;
    uint32_t negative_sat_value;
    int32_t overflow_check_value;
    uint32_t output_mask;
    if (!is_signed && (value < 0))
    {
        return 0;
    }
    if (word_length == 32)
    {
        overflow_mask = 0x80000000;
        negative_sat_value = 0x80000000;
        positive_sat_value_for_false_is_signed = ~0;
        output_mask = ~0;
    }
    else
    {
        is_signed == true ? (overflow_mask = ~0 << (word_length - 1)) : (overflow_mask = (~0 << word_length));
        positive_sat_value_for_false_is_signed = (1 << word_length) - 1;
        negative_sat_value = 1 << (word_length - 1);
        output_mask = ~(~0 << word_length);
    }
    float_t temp = XT_MUL_S (value, pow_2[fract_length]);
    uint32_t scaled_output = XT_ROUND_S (temp, 0);
    overflow_check_value = scaled_output & overflow_mask;
    if (overflow_check_value == 0 || overflow_check_value == overflow_mask)
    {
        return scaled_output & output_mask;
    }
    else if (overflow_check_value > 0 && is_signed)
    {
        return (negative_sat_value - 1);
    }
    else if (overflow_check_value < 0 && is_signed)
    {
        return (negative_sat_value);
    }
    else if (overflow_check_value > 0 && !is_signed)
    {
        return (positive_sat_value_for_false_is_signed);
    }
    else
    {
        return 0;
    }
}

static void init_asc_wrap ()
{
    uint32_t prid = xthal_get_prid ();
#if UNIT
    memset (asc_wrap, 0, sizeof (asc_wrap_t) * NUM_ADC_IN_ONE_QUAD);
    switch (prid)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i) { asc_quad_ant.ant[i] = &asc_wrap[i]; }
            break;
        default: FW_PRINT (FW_INFO, " This CPU ID is wrong"); break;
    }
#else
    switch (prid)
    {
        case 0:
            asc_quad_ant.ant[0] = (asc_wrap_t *)ANT0_ASC0_BASE;
            asc_quad_ant.ant[1] = (asc_wrap_t *)ANT0_ASC1_BASE;
            asc_quad_ant.ant[2] = (asc_wrap_t *)ANT0_ASC2_BASE;
            asc_quad_ant.ant[3] = (asc_wrap_t *)ANT0_ASC3_BASE;
            asc_quad_ant.ant[4] = (asc_wrap_t *)ANT0_ASC_FB_BASE;
            break;
        case 1:
            asc_quad_ant.ant[0] = (asc_wrap_t *)ANT1_ASC0_BASE;
            asc_quad_ant.ant[1] = (asc_wrap_t *)ANT1_ASC1_BASE;
            asc_quad_ant.ant[2] = (asc_wrap_t *)ANT1_ASC2_BASE;
            asc_quad_ant.ant[3] = (asc_wrap_t *)ANT1_ASC3_BASE;
            asc_quad_ant.ant[4] = (asc_wrap_t *)ANT1_ASC_FB_BASE;
        case 2:
            asc_quad_ant.ant[0] = (asc_wrap_t *)ANT2_ASC0_BASE;
            asc_quad_ant.ant[1] = (asc_wrap_t *)ANT2_ASC1_BASE;
            asc_quad_ant.ant[2] = (asc_wrap_t *)ANT2_ASC2_BASE;
            asc_quad_ant.ant[3] = (asc_wrap_t *)ANT2_ASC3_BASE;
            asc_quad_ant.ant[4] = (asc_wrap_t *)ANT2_ASC_FB_BASE;
        case 3:
            asc_quad_ant.ant[0] = (asc_wrap_t *)ANT3_ASC0_BASE;
            asc_quad_ant.ant[1] = (asc_wrap_t *)ANT3_ASC1_BASE;
            asc_quad_ant.ant[2] = (asc_wrap_t *)ANT3_ASC2_BASE;
            asc_quad_ant.ant[3] = (asc_wrap_t *)ANT3_ASC3_BASE;
            asc_quad_ant.ant[4] = (asc_wrap_t *)ANT3_ASC_FB_BASE;
        default: FW_PRINT (FW_INFO, " This CPU ID is wrong"); break;
    }
#endif
    return;
}
static void populate_wgt_cal_lut (uint32_t *p_lut)
{
    uint16_t val;
    uint32_t i;
    uint32_t j;
    for (i = 0, j = 0; i < WEIGHT_CAL_BINARY_RANGE; i += 16, ++j)
    {
        val = ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS, 1) << 3;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 1, 1) << 3;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 2, 1) << 5;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 3, 1) << 5;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 4, 1) << 5;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 5, 1) << 7;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 6, 1) << 7;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 7, 1) << 7;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 8, 1) << 9;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 9, 1) << 9;
        val += ACI_CAL_GET_BITS (i, WEIGHT_CAL_BINARY_WEIGHT_BITS + 10, 1) << 9;
        p_lut[j] = val;
    }
    return;
}
static void construct_wgt_combination ()
{
    uint32_t start_wgt_idx = 0;
    uint32_t start_combination_idx = 0;
    for (uint32_t i = 0; i < MODE; ++i)
    {
        p_wgt_combination[start_combination_idx] = w0_w11[start_wgt_idx] + w0_w11[start_wgt_idx + 1] + w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 4] = -w0_w11[start_wgt_idx] + w0_w11[start_wgt_idx + 1] + w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 2] = w0_w11[start_wgt_idx] - w0_w11[start_wgt_idx + 1] + w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 6] = -w0_w11[start_wgt_idx] - w0_w11[start_wgt_idx + 1] + w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 1] = w0_w11[start_wgt_idx] + w0_w11[start_wgt_idx + 1] - w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 5] = -w0_w11[start_wgt_idx] + w0_w11[start_wgt_idx + 1] - w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 3] = w0_w11[start_wgt_idx] - w0_w11[start_wgt_idx + 1] - w0_w11[start_wgt_idx + 2];
        p_wgt_combination[start_combination_idx + 7] = -w0_w11[start_wgt_idx] - w0_w11[start_wgt_idx + 1] - w0_w11[start_wgt_idx + 2];
        start_wgt_idx += NUM_COMPARATOR;
        start_combination_idx += COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL;
    }
}
static void compute_linear_combination ()
{
    construct_wgt_combination ();
    for (uint32_t i = 0; i < NUM_COMBINATIONS; ++i)
    {
        float_t temp = 0.0;
        uint32_t tbl_idx = 0;
        uint32_t start_bit_position = 11;
        tbl_idx = ACI_CAL_GET_BITS (i, start_bit_position, NUM_COMPARATOR);
        temp += p_wgt_combination[tbl_idx];
        tbl_idx = ACI_CAL_GET_BITS (i, start_bit_position - NUM_COMPARATOR, NUM_COMPARATOR);
        temp += p_wgt_combination[tbl_idx + COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL];
        tbl_idx = ACI_CAL_GET_BITS (i, start_bit_position - 2 * NUM_COMPARATOR, NUM_COMPARATOR);
        temp += p_wgt_combination[tbl_idx + 2 * COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL];
        tbl_idx = ACI_CAL_GET_BITS (i, start_bit_position - 3 * NUM_COMPARATOR, NUM_COMPARATOR);
        temp += p_wgt_combination[tbl_idx + 3 * COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL];
        p_combinations[i] = temp;
    }
    return;
}
static void compute_maj_vote_lut (uint32_t *p_majority_vote_lut)
{
    uint32_t maj_vote[1 << NUM_COMPARATOR] = {0, 0, 0, 1, 0, 1, 1, 1};
    for (uint32_t i = 0; i < 1 << NUM_MAJORITY_VOTE_LUT_BITS; ++i)
    {
        p_majority_vote_lut[i] = (maj_vote[ACI_CAL_GET_BITS (i, 5, 3)] << 1) + maj_vote[ACI_CAL_GET_BITS (i, 2, 3)];
    }
}

void slicecal (void)
{
    SETUP_PROFILE
    init_asc_wrap ();
    p_dither_lut = (float *)com_calloc (1 << NUM_DITHER_COEFFS, sizeof (float_t));
    p_wgt_combination = (float *)com_calloc (COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_TOTAL, sizeof (float));
    p_combinations = (float *)com_calloc (NUM_COMBINATIONS, sizeof (float));
    p_wgt_cal_lut = (uint32_t *)com_calloc (1 << WEIGHT_CAL_LUT_BITS, sizeof (uint32_t));
    p_acc = (float *)com_calloc (WEIGHT_CAL_NUM_BINS, sizeof (float));
    p_cnt = (uint32_t *)com_calloc (WEIGHT_CAL_NUM_BINS, sizeof (uint32_t));
    p_valid_flag = (float *)com_calloc (WEIGHT_CAL_NUM_BINS, sizeof (float));
    p_Rn_running_sum = (float *)com_calloc (SAR_LUT_SIZE, sizeof (float));
    p_Rn_running_idx = (uint32_t *)com_calloc (SAR_LUT_SIZE, sizeof (uint32_t));
    p_dither_acc = (float *)com_calloc (1 << NUM_DITHER_COEFFS, sizeof (float_t));
    p_dither_acc_cnt = (uint32_t *)com_calloc (1 << NUM_DITHER_COEFFS, sizeof (uint32_t));
    p_dither_cal_valid_flag = (float *)com_calloc (1 << NUM_DITHER_COEFFS, sizeof (float));
    p_majority_vote_lut = (uint32_t *)com_calloc (1 << NUM_MAJORITY_VOTE_LUT_BITS, sizeof (uint32_t));
    populate_wgt_cal_lut (p_wgt_cal_lut);
    compute_maj_vote_lut (p_majority_vote_lut);
    for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i)
    {
        for (uint32_t j = 0; j < NUM_SLICES_IN_ONE_ADC; ++j)
        {

            START_PROFILE
            compute_w0_w11 ();
            END_PROFILE
            STORE_PROFILE (w0_w11)
            compute_linear_combination ();
            START_PROFILE
            compute_sop_lut ();
            END_PROFILE
            STORE_PROFILE (sop_lut)
            START_PROFILE
            compute_dither_coeff ();
            END_PROFILE
            STORE_PROFILE (dither)
            START_PROFILE
            compute_offset_coeff ();
            END_PROFILE
            STORE_PROFILE (offset)
            for (uint32_t k = 0; k < ASC_SLICE_W_TOTAL - 6; ++k)
            {
                asc_quad_ant.ant[i]->SLICE[j].W[k].value = scale_float (w0_w11[k], false, 17, 16);
            }
            for (uint32_t k = 0; k < SAR_LUT_SIZE; ++k)
            {
                asc_quad_ant.ant[i]->SLICE[j].W_LUT[k].value = scale_float (sar_lut[k], true, 10, 16);
            }
            for (uint32_t k = 0; k < NUM_DITHER_COEFFS; ++k)
            {
                asc_quad_ant.ant[i]->SLICE[j].W[ASC_SLICE_W_TOTAL - 6 + k].value = scale_float (dither_coeff[k], false, 17, 16);
            }
            asc_quad_ant.ant[i]->SLICE[j].C.value = scale_float (offset_coeff, true, 17, 16);
        }
        com_free (p_majority_vote_lut);
        com_free (p_dither_cal_valid_flag);
        com_free (p_dither_acc_cnt);
        com_free (p_dither_acc);
        com_free (p_Rn_running_idx);
        com_free (p_Rn_running_sum);
        com_free (p_valid_flag);
        com_free (p_cnt);
        com_free (p_acc);
        com_free (p_wgt_cal_lut);
        com_free (p_combinations);
        com_free (p_wgt_combination);
        com_free (p_dither_lut);
    }
}
