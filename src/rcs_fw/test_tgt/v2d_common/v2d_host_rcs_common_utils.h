#ifndef _HOST_RCS_COMMON_H_
#define _HOST_RCS_COMMON_H_
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
 * @file    v2d_host_rcs_common_utils.h
 * @brief   Header file contains common entities between HOST and RCS.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

typedef struct v2d_rcs_host_param
{
    int quad_instance;
    int drf_clock;
    int pdpd_rate;
    int match_value;
    int ant0_cycles;
    int ant1_cycles;
    int ant2_cycles;
    int ant3_cycles;
    int skip_cycles;
    int capture_blocks;
    int num_captures;
    int add_factor;
    int num_antennas;
    int configured_channel[4];
}v2d_rcs_host_param_t;

#define RCS_COMPLETE            (0xC000C0C0)
#define HOST_TEST_COMPLETE      (0xD000D0D0)
#define RCS_INTERRUPT_DONE      (0xabababab)
#define HOST_VALIDATION_DONE    (0xbabababa)
#define RCS_READY               (0xC000C0C1)
#define RCS_GPDMA_TFR_DONE      (0xacacacac)

#endif
