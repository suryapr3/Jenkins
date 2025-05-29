/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
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
 * @file    bfn_test.h
 * @brief   Trigger the delayed start of for the Ch0 of given quad along with start the corresponding vex cores.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#include "com_definitions.h"
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
uint32_t bfn_start();
uint32_t bfn_test_preset_cmd();
void bfn_test_capture_cmd();
uint32_t get_v2d_bfn_cnt();
void v2d_bfn_capture();
void bfn_positive_adjustment_cmd();
void bfn_negative_adjustment_cmd();
void restore_default();
void bfn_sync_adj_cmd();
