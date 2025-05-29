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
 * @file    compute_w0_w11.c
 * @brief   Implementation of weights w0..w11
 * @details Form the equations to solve the weights with 3 weights during each iteration
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "math.h"
#include "ana_common.h"
#include "compute_w0_w11.h"
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
extern uint32_t *p_cnt;
extern float_t *p_acc;
extern float_t *p_valid_flag;
extern float w0_w11[];
extern uint32_t *p_wgt_cal_lut;
extern uint32_t sample_size_adc_in[];

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void slicecal_compute_mean_and_valid_bins ();
static void slicecal_compute_w0_w2 ();
static void slicecal_fold_acc_and_compute_wgts (uint32_t folding_size, uint32_t wgt_idx);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void slicecal_compute_mean_and_valid_bins ()
{
    for (uint32_t i = 0; i < WEIGHT_CAL_NUM_BINS; ++i)
    {
        if (p_cnt[i])
        {
            p_acc[i] /= p_cnt[i];
            p_valid_flag[i] = 1.0;
        }
        else
        {
            p_valid_flag[i] = 0.0;
        }
    }
    return;
}
static void slicecal_compute_w0_w2 ()
{
    float sum = 0;
    float count = 0;
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t idx = i * (WEIGHT_CAL_NUM_BINS / 4);
        uint32_t idx1 = idx + WEIGHT_CAL_NUM_BINS / 4;
        for (uint32_t j = 0; j < WEIGHT_CAL_NUM_BINS / 4; ++j)
        {
            float flag = p_valid_flag[idx] * p_valid_flag[idx1];
            sum += (p_acc[idx] - p_acc[idx1]) * flag;
            count += flag;
            ++idx;
            ++idx1;
        }
        if (count)
        {
            w0_w11[i] = sum / count;
        }
        sum = 0;
        count = 0;
    }
    return;
}
static void slicecal_fold_acc_and_compute_wgts (uint32_t folding_size, uint32_t wgt_idx)
{
    float valid_count = 0;
    float sum = 0;
    float count = 0;
    uint32_t idx_offset = folding_size;
    for (uint32_t i = 0; i < folding_size; ++i)
    {
        p_acc[i] = (p_acc[i] - w0_w11[wgt_idx] - w0_w11[wgt_idx + 1] - w0_w11[wgt_idx + 2]) * p_valid_flag[i];
        p_acc[i + idx_offset] = (p_acc[i + idx_offset] - w0_w11[wgt_idx + 1] - w0_w11[wgt_idx + 2]) * p_valid_flag[i + idx_offset];
        p_acc[i + 2 * idx_offset] = (p_acc[i + 2 * idx_offset] - w0_w11[wgt_idx + 2]) * p_valid_flag[i + 2 * idx_offset];
        p_acc[i + 3 * idx_offset] = p_acc[i + 3 * idx_offset] * p_valid_flag[i + 3 * idx_offset];
        valid_count = p_valid_flag[i] + p_valid_flag[i + idx_offset] + p_valid_flag[i + 2 * idx_offset] + p_valid_flag[i + 3 * idx_offset];
        if (valid_count)
        {
            p_valid_flag[i] = 1.0;
            p_acc[i] = (p_acc[i] + p_acc[i + idx_offset] + p_acc[i + 2 * idx_offset] + p_acc[i + 3 * idx_offset]) / valid_count;
        }
    }
    for (uint32_t i = 0; i < 3; ++i)
    {
        uint32_t idx = i * (folding_size / 4);
        uint32_t idx1 = idx + (folding_size / 4);
        for (uint32_t j = 0; j < folding_size / 4; ++j)
        {
            float flag = p_valid_flag[idx] * p_valid_flag[idx1];
            sum += (p_acc[idx] - p_acc[idx1]) * flag;
            count += flag;
            ++idx;
            ++idx1;
        }
        if (count)
        {
            w0_w11[wgt_idx + 3 + i] = sum / count;
        }
        sum = 0;
        count = 0;
    }
    return;
}
static void slicecal_compute_bin_count_and_accumulate (T_ASC_SLICE_WGT_SAR_LUT_CAL_SG_INFO *p_sg_info)
{
    // extern float *p_acc;
    // extern uint32_t *p_cnt;
    //  extern uint32_t *p_wgt_cal_lut;
    for (uint32_t i = 0; i < p_sg_info->num_points; ++i)
    {
#if UNIT
        // SETUP_PROFILE
        // START_PROFILE
        uint32_t idx = ACI_CAL_GET_BITS (p_sg_info->unit_test.p_adc_out[i], 9, 4)
                       + (p_wgt_cal_lut[ACI_CAL_GET_BITS (p_sg_info->unit_test.p_adc_out[i], 20, 11)]);
        p_acc[idx] += p_sg_info->unit_test.p_adc_in[i];
        ++p_cnt[idx];
        // END_PROFILE
        // STORE_PROFILE (w0_w11_sample_processing)
#else
        // TODO: Set up the Bit Stream Generator sequencer programming
        uint32_t adc_out;
        float_t adc_in = 0.5;
        adc_out = GET_ADC_OUT_SAMPLE (0x1000);
        uint32_t idx = ACI_CAL_GET_BITS (adc_out, 9, 4) + (p_wgt_cal_lut[ACI_CAL_GET_BITS (adc_out, 20, 11)]);
        p_acc[idx] += adc_in;
        ++p_cnt[idx];
#endif
    }
    return;
}
void compute_w0_w11 ()
{
    extern T_ANA_EXT_INFO ana_ext_info;
#if UNIT
    // sg_info.unit_test.p_adc_in = adc_input;
    // sg_info.unit_test.p_adc_out = adc_output;
#endif
    for (uint32_t i = 0; i < WEIGHT_CAL_NUM_BINS; ++i)
    {
        p_acc[i] = 0;
        p_cnt[i] = 0;
    }

    for (uint32_t k = 0; k < NUM_STEPS_IN_INPUT; ++k)
    {
        slicecal_compute_bin_count_and_accumulate (&ana_ext_info.wgt_sar_lut_cal_sg_info[0][k]);
    }
    slicecal_compute_mean_and_valid_bins ();
    p_acc[0] = 0;
    p_valid_flag[0] = 0;
    p_acc[WEIGHT_CAL_NUM_BINS - 1] = 0;
    p_valid_flag[WEIGHT_CAL_NUM_BINS - 1] = 0;
    slicecal_compute_w0_w2 ();
    slicecal_fold_acc_and_compute_wgts (512, 0);
    slicecal_fold_acc_and_compute_wgts (128, 3);
    slicecal_fold_acc_and_compute_wgts (32, 6);
    for (uint32_t i = 0; i < NUM_WEIGHTS; ++i) { w0_w11[i] /= 2.0; }
}
