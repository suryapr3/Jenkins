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
 * @file    flow7_common_utils.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D and receving it back.
 * @details 1. Host utilitis for flow7.
 * @todo    Write documentation for source file sample_source.h
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "flow7_common_utils.h"


/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id ,lut_mode and center coeff value
 * @return          none
 */
int flow7_configure_pdpd(int v2d_num, int apb_num, lut_mode_t lut_mode, int center_value)
{
    int rv = 0;

    printf("INFO: PDPD configuration Started");

    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, center_value))
    {
        printf("PDPD post_C_center config failed\n");
        return rv;
    }

    if (rv = pdpd_extra_static_reg_config(v2d_num, apb_num, 10))
    {
        printf("PDPD post_C_center config failed\n");
        return rv;
    }

    printf("INFO: PDPD configuration Completed");
    return rv;
}
