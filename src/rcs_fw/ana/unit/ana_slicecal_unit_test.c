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
 * @file        ana_slicecal_unit_test.c
 * @brief       Unit test for slice calibration
 * @details
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "compute_w0_w11.h"
#include "dithercal.h"
#include "slicecal.h"
#include "stdint.h"
#include "com_print.h"
#include <xtensa/core-macros.h>
#include "ana_common.h"
#include "math.h"
#include "compute_sop_lut.h"
#include "com_heap.h"
#include "offset_cal.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static uint8_t ana_Heap[ANA_HEAP_SIZE] __attribute__ ((section (".dram0_calib_heap")));
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
uint32_t csr_base;
uint32_t ant_cpu_base; // todo: Seema double check
asc_wrap_t asc_wrap[NUM_ADC_IN_ONE_QUAD] __attribute__ ((section (".hwc_slice_cal_output_global"))) = {0};
extern T_ASC_SLICE_WGT_SAR_LUT_CAL_SG_INFO wgt_sar_lut_cal_sg_info[][8];
extern T_ASC_SLICE_DITHER_OFFSET_CAL_SG_INFO dither_offset_cal_sg_info[];
extern float_t adc_input[];
extern uint32_t adc_output[];
extern uint32_t sample_size_adc_in[];

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static bool validate_w0_w11 ();
static bool validate_dither_coeff ();
static bool validate_offset_coeff ();
static bool validate_sar_lut ();
static void init_tbale_from_rx ();
/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
static bool validate_w0_w11 ()
{
    extern uint32_t expected_w0_w11[][NUM_SLICES_IN_ONE_ADC][ASC_SLICE_W_TOTAL - 6];
    for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i)
    {
        for (uint32_t j = 0; j < NUM_SLICES_IN_ONE_ADC; ++j)
        {
            for (uint32_t k = 0; k < ASC_SLICE_W_TOTAL - 6; ++k)
            {
                if (asc_wrap[i].SLICE[j].W[k].value != expected_w0_w11[i][j][k])
                {
                    return (false);
                }
            }
        }
    }
    return (true);
}
static bool validate_dither_coeff ()
{
    extern uint32_t expected_dither_coeff[][NUM_SLICES_IN_ONE_ADC][NUM_DITHER_COEFFS];
    for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i)
    {
        for (uint32_t j = 0; j < NUM_SLICES_IN_ONE_ADC; ++j)
        {
            for (uint32_t k = 0; k < NUM_DITHER_COEFFS; ++k)
            {
                if (asc_wrap[i].SLICE[j].W[ASC_SLICE_W_TOTAL - 6 + k].value != expected_dither_coeff[i][j][k])
                {
                    return (false);
                }
            }
        }
    }
    return (true);
}
static bool validate_offset_coeff ()
{
    extern uint32_t expected_offset_coeff[][NUM_SLICES_IN_ONE_ADC][NUM_OFFSET_COEFFS];
    for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i)
    {
        for (uint32_t j = 0; j < NUM_SLICES_IN_ONE_ADC; ++j)
        {
            for (uint32_t k = 0; k < 1; ++k)
            {
                if (asc_wrap[i].SLICE[j].C.value != expected_offset_coeff[i][j][k])
                {
                    return (false);
                }
            }
        }
    }
    return (true);
}
static bool validate_sar_lut ()
{
    extern uint32_t expected_sar_lut[][NUM_SLICES_IN_ONE_ADC][SAR_LUT_SIZE];
    for (uint32_t i = 0; i < NUM_ADC_IN_ONE_QUAD; ++i)
    {
        for (uint32_t j = 0; j < NUM_SLICES_IN_ONE_ADC; ++j)
        {
            for (uint32_t k = 0; k < SAR_LUT_SIZE; ++k)
            {
                if (asc_wrap[i].SLICE[j].W_LUT[k].value != expected_sar_lut[i][j][k])
                {
                    return (false);
                }
            }
        }
    }
    return (true);
}
static void init_tbale_from_rx ()
{
    float_t *temp_in = adc_input;
    uint32_t *temp_out = adc_output;
    extern T_ANA_EXT_INFO ana_ext_info;
    // weight calculation sg information
    for (uint32_t i = 0; i < NUM_STEPS_IN_INPUT; ++i)
    {
        ana_ext_info.wgt_sar_lut_cal_sg_info[0][i].unit_test.p_adc_in = temp_in;
        ana_ext_info.wgt_sar_lut_cal_sg_info[0][i].unit_test.p_adc_out = temp_out;
        ana_ext_info.wgt_sar_lut_cal_sg_info[0][i].num_points = sample_size_adc_in[i];
        temp_in += sample_size_adc_in[i];
        temp_out += sample_size_adc_in[i];
    }
    // sar lut calculation sg information
    temp_in = adc_input;
    temp_out = adc_output;
    for (uint32_t i = 0; i < NUM_STEPS_IN_INPUT; ++i)
    {
        ana_ext_info.wgt_sar_lut_cal_sg_info[1][i].unit_test.p_adc_in = temp_in;
        ana_ext_info.wgt_sar_lut_cal_sg_info[1][i].unit_test.p_adc_out = temp_out;
        ana_ext_info.wgt_sar_lut_cal_sg_info[1][i].num_points = sample_size_adc_in[i];
        temp_in += sample_size_adc_in[i];
        temp_out += sample_size_adc_in[i];
    }
    // Dither calculation sg information
    ana_ext_info.dither_offset_cal_sg_info[0].num_points = ASC_DITHER_CAL_NUM_SAMPLES_UNIT_TEST / NUM_STEPS_IN_INPUT;
    // Offset calculation sg information
    ana_ext_info.dither_offset_cal_sg_info[1].num_points = ASC_OFFSET_CAL_NUM_SAMPLES_UNIT_TEST / NUM_STEPS_IN_INPUT;
    return;
}
int main (void)
{
    extern T_ANA_EXT_INFO ana_ext_info;
    SETUP_PROFILE
    com_heap_create (ana_Heap, ANA_HEAP_SIZE);
    uint32_t prid = xthal_get_prid ();
    switch (prid)
    {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        default: FW_PRINT (FW_INFO, " This CPU ID is wrong"); break;
    }
    init_tbale_from_rx ();
    START_PROFILE
    slicecal ();
    END_PROFILE
    STORE_PROFILE (slice_cal)
    if (!validate_w0_w11 ())
    {
        FW_PRINT (FW_ERR, "Weights computed does not match expected");
    }
    else
    {
        FW_PRINT (FW_INFO, "Weights computation successful!");
    }
    if (!validate_sar_lut ())
    {
        FW_PRINT (FW_ERR, "SAR LUT computed does not match expected");
    }
    else
    {
        FW_PRINT (FW_INFO, "SAR LUT computation successful!");
    }
    if (!validate_dither_coeff ())
    {
        FW_PRINT (FW_ERR, "Dither coeffs. computed does not match expected");
    }
    else
    {
        FW_PRINT (FW_INFO, "Dither coeffs. computation successful!");
    }
    if (!validate_offset_coeff ())
    {
        FW_PRINT (FW_ERR, "Offset coeff. computed does not match expected");
    }
    else
    {
        FW_PRINT (FW_INFO, "Offset coeff. computation successful!");
    }
}
