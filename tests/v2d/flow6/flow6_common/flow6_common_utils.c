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
 * @file    flow6_common_utils.c
 * @brief   common utilitis for Flow6 code base.
 * @todo    Write documentation for source file sample_source.h
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "flow6_common_utils.h"
#include "common_utils.h"

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id , test_config and post_c_center value
 * @return          none
 */
int flow6_configure_pdpd(int v2d_num, int apb_num, int test_config, int post_c_center_value)
{
    int rv = 0;
    int i_value = 0, q_value = 0, update_passthru = 0, center_value = post_c_center_value, update_c_lut = 0;
    pdpd_rate_t pdpd_out_rate;

    i_value = PASSTHRU_I_COEFF_UNITY_GAIN;
    q_value = PASSTHRU_Q_COEFF_UNITY_GAIN;
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, FLOW6_PASSTHRU_VALUE, pdpd_out_rate))
    {
        printf ("PDPD reg config failed\n");
        return rv;
    }
    if (rv = pdpd_ctrl_reg_config(v2d_num, apb_num, update_passthru, update_c_lut))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_reg_config(v2d_num, apb_num, i_value, q_value))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, center_value))
    {
        printf("PDPD post_C_center config failed\n");
        return rv;
    }

    printf("INFO: PDPD configuration Completed");
    return rv;
}
