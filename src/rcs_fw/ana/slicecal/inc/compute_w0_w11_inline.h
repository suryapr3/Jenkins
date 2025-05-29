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
#ifndef COMPUTE_W0_W11_INLINE_H
#define COMPUTE_W0_W11_INLINE_H
#include "math.h"
#include "stdint.h"
#include "compute_w0_w11.h"
#include "ana_common.h"

void __attribute__ ((always_inline)) static COMPUTE_DAC_COEFF_KERNEL (float_t center, float_t range, uint32_t input_bp_start, uint32_t input_num_bits, uint32_t sum_input_bp_start, uint32_t threshold_1,uint32_t threshold_2,uint32_t threshold_3,uint32_t threshold_4,uint32_t* p_unit_test_input, float_t* p_weights)
{
    uint32_t input;
    uint32_t temp;
    uint32_t temp_add;
    uint32_t acc[NUM_VARIABLES_IN_EQUATION];
    float_t comp_mean_dac1;
    float_t v_center_adj_dac1[NUM_VARIABLES_IN_EQUATION];
    for (uint32_t i = 0; i < NUM_VARIABLES_IN_EQUATION; ++i) { acc[i] = 0; }
    for (uint32_t i = 0; i < NUM_SAMPLES_W0_W11; ++i)
    {

#if (UNIT)
        input = p_unit_test_input[i];
#else
        input = GET_ADC_OUT_SAMPLE (0x1000);
#endif
        temp = ACI_CAL_GET_BITS (input, input_bp_start,input_num_bits);
        temp_add = ACI_CAL_GET_BITS (input, sum_input_bp_start, 1);
        if (temp > threshold_1)
        {
            ++acc[0];
            ++acc[1];
            ++acc[2];
            ++acc[3];
        }
        else if (temp == threshold_1)
        {
            acc[0] += temp_add;
            ++acc[1];
            ++acc[2];
            ++acc[3];
        }
        else if (temp > threshold_2)
        {
            ++acc[1];
            ++acc[2];
            ++acc[3];
        }
        else if (temp == threshold_2)
        {
            acc[1] += temp_add;
            ++acc[2];
            ++acc[3];
        }
        else if (temp > threshold_3)
        {
            ++acc[2];
            ++acc[3];
        }
        else if (temp == threshold_3)
        {
            acc[2] += temp_add;
            ++acc[3];
        }
        else if (temp > threshold_4)
        {
            ++acc[3];
        }
        else if (temp == threshold_4)
        {
            acc[3] += temp_add;
        }
    }
    for (uint32_t j = 0; j < NUM_VARIABLES_IN_EQUATION; ++j)
    {
        comp_mean_dac1 = 2.0 * (1.0 - (float_t)acc[j] / NUM_SAMPLES_W0_W11) - 1.0;
        v_center_adj_dac1[j] = center + comp_mean_dac1 * range / 2.0;
    }
    p_weights[0] = 0.5 * v_center_adj_dac1[0] - 0.5 * v_center_adj_dac1[1];
    p_weights[1] = 0.5 * v_center_adj_dac1[1] - 0.5 * v_center_adj_dac1[2];
    p_weights[2] = 0.5 * v_center_adj_dac1[2] - 0.5 * v_center_adj_dac1[3];
    p_weights[3] = 0.5 * v_center_adj_dac1[0] + 0.5 * v_center_adj_dac1[3];
    return;
}
#endif