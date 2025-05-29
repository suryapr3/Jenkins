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
#ifndef DITHER_CAL_H
#define DITHER_CAL_H
#include "math.h"
#include "stdint.h"
extern void compute_dither_coeff ();
#define NUM_DITHER_COEFFS 6
#if UNIT
extern uint32_t adc_output_dither_cal[];
#if USE_ANALOG_SIMULATION_OUTPUT
#define ASC_DITHER_CAL_NUM_SAMPLES_UNIT_TEST 2048
#else
#define ASC_DITHER_CAL_NUM_SAMPLES_UNIT_TEST 16384
#endif
#endif
#endif
