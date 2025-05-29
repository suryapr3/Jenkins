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
#ifndef COMPUTE_SOP_LUT_H
#define COMPUTE_SOP_LUT_H
#include "math.h"
#include "stdint.h"
#define X4_2B_CYCLE_MODE                                    4
#define SOP_INPUT_SAMPLE_SIZE                               4
#define SAR_LUT_INPUT_SIZE                                  5
#define NUM_COMPARATOR                                      3
#define MODE                                                X4_2B_CYCLE_MODE
#define NUM_SOP_LUT_WEIGHTS                                 ((SOP_INPUT_SAMPLE_SIZE) * NUM_COMPARATOR)
#define NUM_COMBINATIONS                                    (1 << NUM_SOP_LUT_WEIGHTS)
#define COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL (1 << (NUM_COMPARATOR))
#define COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_TOTAL      ((SOP_INPUT_SAMPLE_SIZE)) * (COMPARATOR_WEIGHT_COMBINATION_TABLE_SIZE_INDIVIDUAL)
#define SAR_LUT_SIZE                                        (1 << (SAR_LUT_INPUT_SIZE))
#define SAR_LUT_INPUT_BIT_START                             20
#define SAR_LUT_INPUT_NUM_BITS                              12
extern void compute_sop_lut (void);
#if UNIT
extern float_t adc_input[];
extern uint32_t adc_output[];
#endif
#endif
