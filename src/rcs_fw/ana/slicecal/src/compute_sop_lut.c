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
 * @file    compute_sop_lut.c
 * @brief   Implementation of Sum Of Products LUT
 * @details sop LUT is constructed using the computed weights
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "compute_sop_lut.h"
#include "math.h"
#include "stdint.h"
#include "ana_common.h"
// #include "com_print.h"
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
extern uint32_t sample_size_adc_in[];
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

void compute_sop_lut ()
{
    extern float sar_lut[];
    extern float *p_combinations;
    extern float_t *p_Rn_running_sum;
    extern uint32_t *p_Rn_running_idx;
    extern uint32_t *p_majority_vote_lut;
    uint32_t adc_out;
    float_t adc_in;
    float_t Rn;
    float_t sop_output;
    uint32_t sar_correction_tbl_idx;
    float_t sop_running_sum;
    uint32_t sop_running_count;
    float_t sop_average;
    extern T_ANA_EXT_INFO ana_ext_info;

    for (uint32_t i = 0; i < SAR_LUT_SIZE; ++i)
    {
        p_Rn_running_sum[i] = 0.0;
        p_Rn_running_idx[i] = 0;
    }
    //     T_ASC_SLICE_WGT_SAR_LUT_CAL_SG_INFO sg_info;
    // #if UNIT
    //     sg_info.unit_test.p_adc_in = adc_input;
    //     sg_info.unit_test.p_adc_out = adc_output;

    // #endif
    for (uint32_t k = 0; k < NUM_STEPS_IN_INPUT; ++k)
    {
        for (uint32_t i = 0; i < ana_ext_info.wgt_sar_lut_cal_sg_info[1][k].num_points; ++i)
        {
#if (UNIT)
            adc_out = ana_ext_info.wgt_sar_lut_cal_sg_info[1][k].unit_test.p_adc_out[i];
            adc_in = ana_ext_info.wgt_sar_lut_cal_sg_info[1][k].unit_test.p_adc_in[i];
#else
            // FIXME:
            adc_out = GET_ADC_OUT_SAMPLE (0x1000);
            adc_in = 0.5;
#endif
            // SETUP_PROFILE
            // START_PROFILE
            if (ACI_CAL_GET_BITS (adc_out, SAR_LUT_INPUT_BIT_START, SAR_LUT_INPUT_NUM_BITS) == 0
                || ACI_CAL_GET_BITS (adc_out, SAR_LUT_INPUT_BIT_START, SAR_LUT_INPUT_NUM_BITS) == 0xFFF)
            {
                // END_PROFILE
                continue;
            }
            sop_output = p_combinations[ACI_CAL_GET_BITS (adc_out, 20, 12)];
            Rn = sop_output - adc_in;

            sar_correction_tbl_idx = (ACI_CAL_GET_BITS (adc_out, 8, 3) << 2) + p_majority_vote_lut[ACI_CAL_GET_BITS (adc_out, 5, 6)];
            // FW_PRINT (FW_INFO, "adc_out = %x\n", adc_out);
            // FW_PRINT (FW_INFO, "i = %d\n", i);
            // FW_PRINT (FW_INFO, "sar_correction_tbl_idx = %d\n", sar_correction_tbl_idx);
            // FW_PRINT (FW_INFO, "sop_output = %f\n", sop_output);
            // FW_PRINT (FW_INFO, "tbl_idx = %d\n", tbl_idx);
            p_Rn_running_sum[sar_correction_tbl_idx] += Rn;
            p_Rn_running_idx[sar_correction_tbl_idx]++;
            // END_PROFILE
            // STORE_PROFILE (sop_lut_sample_processing)
            // FW_PRINT (FW_INFO, "p_Rn_running_sum[%d] = %f\n", sar_correction_tbl_idx, p_Rn_running_sum[sar_correction_tbl_idx]);
            // FW_PRINT (FW_INFO, "p_Rn_running_idx[%d] = %d\n", sar_correction_tbl_idx, p_Rn_running_idx[sar_correction_tbl_idx]);
        }
    }
    for (uint32_t i = 0; i < SAR_LUT_SIZE; ++i)
    {
        if (p_Rn_running_sum[i])
        {
            sar_lut[i] = p_Rn_running_sum[i] / p_Rn_running_idx[i];
        }
    }
    sop_running_sum = 0.0;
    sop_running_count = 0;
    for (uint32_t i = 0; i < SAR_LUT_SIZE; ++i)
    {
        if (sar_lut[i])
        {
            sop_running_sum += sar_lut[i];
            ++sop_running_count;
        }
    }
    if (sop_running_count)
    {
        sop_average = sop_running_sum / sop_running_count;
    }
    for (uint32_t i = 0; i < SAR_LUT_SIZE; ++i)
    {
        if (sar_lut[i])
        {
            sar_lut[i] -= sop_average;
        }
    }
}
