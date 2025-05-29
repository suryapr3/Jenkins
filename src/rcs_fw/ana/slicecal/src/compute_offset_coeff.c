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
 * @file    compute_offset_coeff.c
 * @brief   Implementation of offset coeff computation
 * @details Compute offset coeff  binning and averaging
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "offset_cal.h"
#include "math.h"
#include "ana_common.h"
#include "dithercal.h"
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
static void compute_dither_lut (float *p_dither_coeffs, float *p_dither_lut);
/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static void compute_dither_lut (float *p_dither_coeffs, float *p_dither_lut)
{
    float map[2] = {1.0, -1.0};
    float sum;
    for (uint32_t i = 0; i < (1 << NUM_DITHER_COEFFS); ++i)
    {
        sum = 0.0;
        sum += map[ACI_CAL_GET_BITS (i, 0, 1)] * p_dither_coeffs[5];
        sum += map[ACI_CAL_GET_BITS (i, 1, 1)] * p_dither_coeffs[4];
        sum += map[ACI_CAL_GET_BITS (i, 2, 1)] * p_dither_coeffs[3];
        sum += map[ACI_CAL_GET_BITS (i, 3, 1)] * p_dither_coeffs[2];
        sum += map[ACI_CAL_GET_BITS (i, 4, 1)] * p_dither_coeffs[1];
        sum += map[ACI_CAL_GET_BITS (i, 5, 1)] * p_dither_coeffs[0];
        p_dither_lut[i] = sum;
    }
    return;
}
void compute_offset_coeff ()
{
    extern float *p_combinations;
    extern float dither_coeff[];
    extern float sar_lut[];
    extern float offset_coeff;
    extern uint32_t *p_majority_vote_lut;
    uint32_t num_samples = 0;
    uint32_t adc_output;
    uint32_t idx;
    extern float *p_dither_lut;
    extern T_ANA_EXT_INFO ana_ext_info;

#if UNIT
    extern uint32_t sample_size_adc_output_dither_offset_cal[];
    uint32_t *p_adc_output = adc_output_dither_cal;
#else
// TODO: obtain the number of samples from the populated structure
#endif
    float offset_acc = 0;
    compute_dither_lut (dither_coeff, p_dither_lut);

    for (uint32_t i = 0; i < NUM_STEPS_IN_INPUT; ++i)
    {
        for (uint32_t j = 0; j < ana_ext_info.dither_offset_cal_sg_info[1].num_points; ++j)
        {
#if UNIT
            adc_output = p_adc_output[j];
#else
            adc_output = GET_ADC_OUT_SAMPLE (0x1000);
#endif
            // SETUP_PROFILE
            // START_PROFILE
            ++num_samples;
            idx = ACI_CAL_GET_BITS (adc_output, 8, 3) << 2;
            idx += p_majority_vote_lut[ACI_CAL_GET_BITS (adc_output, 5, 6)];
            float sar_lut_out = sar_lut[idx];
            uint32_t idx = ACI_CAL_GET_BITS (adc_output, 26, 6);
            float dither_lut_out = p_dither_lut[idx];
            float wgt_output = p_combinations[ACI_CAL_GET_BITS (adc_output, 20, 12)];
            offset_acc += wgt_output - sar_lut_out - dither_lut_out;
            // END_PROFILE
            // STORE_PROFILE (offset_sample_processing)
        }
#if UNIT
        p_adc_output += ana_ext_info.dither_offset_cal_sg_info[1].num_points;
#endif
    }
    offset_coeff = offset_acc / num_samples;
    return;
}
