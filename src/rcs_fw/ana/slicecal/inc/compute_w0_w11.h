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
#ifndef COMPUTE_W0_W11_H
#define COMPUTE_W0_W11_H
#include "math.h"
#include "stdint.h"

#define NUM_WEIGHTS                         12
#define ASC_SLICE_SOP_LUT_NUM_FRACTION_BITS 16
#define WEIGHT_CAL_LUT_BITS                 11
#define WEIGHT_CAL_BINARY_WEIGHT_BITS       4
#define WEIGHT_CAL_TOTAL_BITS               (WEIGHT_CAL_LUT_BITS) + (WEIGHT_CAL_BINARY_WEIGHT_BITS)
#define WEIGHT_CAL_BINARY_RANGE             (1 << (WEIGHT_CAL_TOTAL_BITS))
#define WEIGHT_CAL_NUM_BINS                 2048
extern void compute_w0_w11 (void);
#if UNIT
extern float_t adc_input[];
extern uint32_t adc_output[];
#if USE_ANALOG_SIMULATION_OUTPUT
#define NUM_SAMPLES_W0_W11 (2541)
#else
#define NUM_SAMPLES_W0_W11 (16384)
#endif
#endif
#endif
