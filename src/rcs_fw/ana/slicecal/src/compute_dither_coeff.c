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
 * @file    compute_dither_coeff.c
 * @brief   Implementation of dither calibration
 * @details Compute dither coefficients by binning and averaging
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "dithercal.h"
#include "math.h"
#include "ana_common.h"
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
static void slicecal_compute_d1 ();
static void slicecal_fold_acc_and_compute_d1_d4 (uint32_t folding_size, uint32_t dither_idx);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void slicecal_compute_d1 ()
{
    extern float *p_dither_acc;
    extern float *p_dither_cal_valid_flag;
    extern float dither_coeff[];
    float sum = 0;
    float count = 0;
    uint32_t num_valid_bins = 1 << (NUM_DITHER_COEFFS - 1);

    for (uint32_t j = 0; j < num_valid_bins / 2; ++j)
    {
        float flag = p_dither_cal_valid_flag[j] * p_dither_cal_valid_flag[j + num_valid_bins / 2];
        sum += (p_dither_acc[j] - p_dither_acc[j + num_valid_bins / 2]) * flag;
        count += flag;
    }
    if (count)
    {
        dither_coeff[1] = sum / count;
    }
    return;
}
static void slicecal_fold_acc_and_compute_d1_d4 (uint32_t folding_size, uint32_t dither_idx)
{
    extern float *p_dither_acc;
    extern float *p_dither_cal_valid_flag;
    extern float dither_coeff[];
    float valid_count = 0;
    float sum = 0;
    float count = 0;
    uint32_t idx_offset = folding_size;
    for (uint32_t i = 0; i < folding_size; ++i)
    {
        p_dither_acc[i] = (p_dither_acc[i] - dither_coeff[dither_idx]) * p_dither_cal_valid_flag[i];
        p_dither_acc[i + idx_offset] = (p_dither_acc[i + idx_offset]) * p_dither_cal_valid_flag[i + idx_offset];
        valid_count = p_dither_cal_valid_flag[i] + p_dither_cal_valid_flag[i + idx_offset];
        if (valid_count)
        {
            p_dither_cal_valid_flag[i] = 1.0;
            p_dither_acc[i] = (p_dither_acc[i] + p_dither_acc[i + idx_offset]) / valid_count;
        }
    }
    for (uint32_t j = 0; j < folding_size / 2; ++j)
    {
        float flag = p_dither_cal_valid_flag[j] * p_dither_cal_valid_flag[j + folding_size / 2];
        sum += (p_dither_acc[j] - p_dither_acc[j + folding_size / 2]) * flag;
        count += flag;
    }
    if (count)
    {
        dither_coeff[dither_idx + 1] = sum / count;
    }
    return;
}
void compute_dither_coeff ()
{
    extern float dither_coeff[];
    extern float *p_combinations;
    extern float sar_lut[];
    extern float *p_dither_acc;
    extern uint32_t *p_dither_acc_cnt;
    extern float_t *p_dither_cal_valid_flag;
    extern uint32_t *p_majority_vote_lut;
    extern T_ANA_EXT_INFO ana_ext_info;
    uint32_t adc_output;
    uint32_t idx;
    float_t adc_out_cal;
    uint32_t num_bins = 1 << NUM_DITHER_COEFFS;

#if UNIT
    uint32_t *p_adc_output = adc_output_dither_cal;
#else
// TODO: obtain the number of samples from the populated structure
#endif
    for (uint32_t i = 0; i < num_bins; ++i)
    {
        p_dither_acc[i] = 0;
        p_dither_cal_valid_flag[i] = 0;
    }
    for (uint32_t i = 0; i < num_bins; ++i)
    {
        p_dither_acc[i] = 0.0;
        p_dither_acc_cnt[i] = 0;
        p_dither_cal_valid_flag[i] = 0.0;
    }

    for (uint32_t i = 0; i < NUM_STEPS_IN_INPUT; ++i)
    {
        for (uint32_t j = 0; j < ana_ext_info.dither_offset_cal_sg_info[0].num_points; ++j)
        {
#if UNIT
            adc_output = p_adc_output[j];
#else
            adc_output = GET_ADC_OUT_SAMPLE (0x1000);
#endif
            // SETUP_PROFILE
            // START_PROFILE
            idx = ACI_CAL_GET_BITS (adc_output, 8, 3) << 2;
            idx += p_majority_vote_lut[ACI_CAL_GET_BITS (adc_output, 5, 6)];
            adc_out_cal = p_combinations[ACI_CAL_GET_BITS (adc_output, 20, 12)] - sar_lut[idx];
            idx = ACI_CAL_GET_BITS (adc_output, 26, 6);
            p_dither_acc[idx] += adc_out_cal;
            p_dither_acc_cnt[idx] += 1;
            // END_PROFILE
            // STORE_PROFILE (dither_sample_processing)
        }
#if UNIT
        p_adc_output += ana_ext_info.dither_offset_cal_sg_info[0].num_points;
#endif
    }
    for (uint32_t i = 0; i < num_bins; ++i)
    {
        if (p_dither_acc_cnt[i])
        {
            p_dither_acc[i] /= p_dither_acc_cnt[i];
            p_dither_cal_valid_flag[i] = 1.0;
        }
    }
    slicecal_compute_d1 ();
    slicecal_fold_acc_and_compute_d1_d4 (16, 1);
    slicecal_fold_acc_and_compute_d1_d4 (8, 2);
    slicecal_fold_acc_and_compute_d1_d4 (4, 3);
    slicecal_fold_acc_and_compute_d1_d4 (2, 4);
    for (uint32_t i = 1; i < NUM_DITHER_COEFFS; ++i) { dither_coeff[i] /= 2.0; }
    dither_coeff[0] = 0.0;
}
