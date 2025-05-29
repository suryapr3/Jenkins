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
#ifndef SLICECAL_H
#define SLICECAL_H
#include "stdint.h"   // IWYU pragma: keep
#include "asc_wrap.h" // IWYU pragma: keep
extern void slicecal (void);
#define NUM_MAJORITY_VOTE_LUT_BITS 6
#if UNIT
#define NUM_ADC_IN_ONE_QUAD   1 // To reduce the unit test run time
#define NUM_SLICES_IN_ONE_ADC 1 // To reduce the unit test run time
#else
#define NUM_ADC_IN_ONE_QUAD   5                   // 4 Regular and 1 Feed back
#define NUM_SLICES_IN_ONE_ADC ASC_SLICE_W_ARR_SZ0 // 16 regular and 1 observation
#endif
#endif
