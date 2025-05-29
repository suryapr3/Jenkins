/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
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
*********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"
#include "common_functions.h"
#include "srp_block_ids.h"

#define write_data0 0xA5A5A5A5
#define write_data1 0x5a5a5a5a


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    uint32_t error = 0;
    uint32_t write_status = 0;
    uint32_t write_iteration;
    uint32_t write_data;
    uint32_t expected_data;
    int i;
    init();

    uint32_t base_address[] = {
    SYSCON_EVC_AGC_BASE
    };


    for (write_iteration = 0;write_iteration < 1; write_iteration++)
    {
        if (write_iteration == 0 )
        {
            write_data = write_data0;
        }
        else
        {
            write_data = write_data1;
        }

        expected_data = write_data;


        for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
        {
            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_INTF_CFG_OFFSET, \
                                    EVC_AGC_EVC0_INTF_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_INTF_CFG_RD_MASK, EVC_AGC_EVC0_INTF_CFG_WR_MASK, \
                                    "EVC_AGC_EVC0_INTF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_CAL_CFG_OFFSET, \
                                    EVC_AGC_EVC0_CAL_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_CAL_CFG_RD_MASK, EVC_AGC_EVC0_CAL_CFG_WR_MASK, \
                                    "EVC_AGC_EVC0_CAL_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_CAL_RSLT_OFFSET, \
                                    EVC_AGC_EVC0_CAL_RSLT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_CAL_RSLT_RD_MASK, EVC_AGC_EVC0_CAL_RSLT_WR_MASK, \
                                    "EVC_AGC_EVC0_CAL_RSLT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_SAFE_VAL_L_OFFSET, \
                                    EVC_AGC_EVC0_SAFE_VAL_L_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_SAFE_VAL_L_RD_MASK, EVC_AGC_EVC0_SAFE_VAL_L_WR_MASK, \
                                    "EVC_AGC_EVC0_SAFE_VAL_L_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_SAFE_VAL_H_OFFSET, \
                                    EVC_AGC_EVC0_SAFE_VAL_H_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_SAFE_VAL_H_RD_MASK, EVC_AGC_EVC0_SAFE_VAL_H_WR_MASK, \
                                    "EVC_AGC_EVC0_SAFE_VAL_H_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_BM_LUT_L_OFFSET, \
                                    EVC_AGC_EVC0_BM_LUT_L_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_BM_LUT_L_RD_MASK, EVC_AGC_EVC0_BM_LUT_L_WR_MASK, \
                                    "EVC_AGC_EVC0_BM_LUT_L_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_BM_LUT_H_OFFSET, \
                                    EVC_AGC_EVC0_BM_LUT_H_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_BM_LUT_H_RD_MASK, EVC_AGC_EVC0_BM_LUT_H_WR_MASK, \
                                    "EVC_AGC_EVC0_BM_LUT_H_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT0_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT0_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT0_RD_MASK, EVC_AGC_EVC0_MODE_LUT0_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT0_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT1_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT1_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT1_RD_MASK, EVC_AGC_EVC0_MODE_LUT1_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT1_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT2_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT2_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT2_RD_MASK, EVC_AGC_EVC0_MODE_LUT2_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT2_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT3_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT3_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT3_RD_MASK, EVC_AGC_EVC0_MODE_LUT3_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT3_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT4_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT4_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT4_RD_MASK, EVC_AGC_EVC0_MODE_LUT4_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT4_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_LUT5_OFFSET, \
                                    EVC_AGC_EVC0_MODE_LUT5_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_LUT5_RD_MASK, EVC_AGC_EVC0_MODE_LUT5_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_LUT5_OFFSET");//

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_MODE_ACC_OFFSET, \
                                    EVC_AGC_EVC0_MODE_ACC_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_MODE_ACC_RD_MASK, EVC_AGC_EVC0_MODE_ACC_WR_MASK, \
                                    "EVC_AGC_EVC0_MODE_ACC_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_STAT_OFFSET, \
                                    EVC_AGC_EVC0_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_STAT_RD_MASK, EVC_AGC_EVC0_STAT_WR_MASK, \
                                    "EVC_AGC_EVC0_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_PERR_CNT_OFFSET, \
                                    EVC_AGC_EVC0_PERR_CNT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_PERR_CNT_RD_MASK, EVC_AGC_EVC0_PERR_CNT_WR_MASK, \
                                    "EVC_AGC_EVC0_PERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_SERR_CNT_OFFSET, \
                                    EVC_AGC_EVC0_SERR_CNT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_SERR_CNT_RD_MASK, EVC_AGC_EVC0_SERR_CNT_WR_MASK, \
                                    "EVC_AGC_EVC0_SERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_ERR_STAT_OFFSET, \
                                    EVC_AGC_EVC0_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_ERR_STAT_RD_MASK, EVC_AGC_EVC0_ERR_STAT_WR_MASK, \
                                    "EVC_AGC_EVC0_ERR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_ECC_CTRL_OFFSET, \
                                    EVC_AGC_EVC0_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_ECC_CTRL_RD_MASK, EVC_AGC_EVC0_ECC_CTRL_WR_MASK, \
                                    "EVC_AGC_EVC0_ECC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC0_ECC_STAT_OFFSET, \
                                    EVC_AGC_EVC0_ECC_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC0_ECC_STAT_RD_MASK, EVC_AGC_EVC0_ECC_STAT_WR_MASK, \
                                    "EVC_AGC_EVC0_ECC_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_INTF_CFG_OFFSET, \
                                    EVC_AGC_EVC1_INTF_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_INTF_CFG_RD_MASK, EVC_AGC_EVC1_INTF_CFG_WR_MASK, \
                                    "EVC_AGC_EVC1_INTF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_CAL_CFG_OFFSET, \
                                    EVC_AGC_EVC1_CAL_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_CAL_CFG_RD_MASK, EVC_AGC_EVC1_CAL_CFG_WR_MASK, \
                                    "EVC_AGC_EVC1_CAL_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_CAL_RSLT_OFFSET, \
                                    EVC_AGC_EVC1_CAL_RSLT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_CAL_RSLT_RD_MASK, EVC_AGC_EVC1_CAL_RSLT_WR_MASK, \
                                    "EVC_AGC_EVC1_CAL_RSLT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_SAFE_VAL_L_OFFSET, \
                                    EVC_AGC_EVC1_SAFE_VAL_L_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_SAFE_VAL_L_RD_MASK, EVC_AGC_EVC1_SAFE_VAL_L_WR_MASK, \
                                    "EVC_AGC_EVC1_SAFE_VAL_L_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_SAFE_VAL_H_OFFSET, \
                                    EVC_AGC_EVC1_SAFE_VAL_H_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_SAFE_VAL_H_RD_MASK, EVC_AGC_EVC1_SAFE_VAL_H_WR_MASK, \
                                    "EVC_AGC_EVC1_SAFE_VAL_H_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_BM_LUT_L_OFFSET, \
                                    EVC_AGC_EVC1_BM_LUT_L_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_BM_LUT_L_RD_MASK, EVC_AGC_EVC1_BM_LUT_L_WR_MASK, \
                                    "EVC_AGC_EVC1_BM_LUT_L_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_BM_LUT_H_OFFSET, \
                                    EVC_AGC_EVC1_BM_LUT_H_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_BM_LUT_H_RD_MASK, EVC_AGC_EVC1_BM_LUT_H_WR_MASK, \
                                    "EVC_AGC_EVC1_BM_LUT_H_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT0_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT0_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT0_RD_MASK, EVC_AGC_EVC1_MODE_LUT0_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT0_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT1_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT1_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT1_RD_MASK, EVC_AGC_EVC1_MODE_LUT1_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT1_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT2_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT2_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT2_RD_MASK, EVC_AGC_EVC1_MODE_LUT2_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT2_OFFSET");//

           // write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT3_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT3_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT3_RD_MASK, EVC_AGC_EVC1_MODE_LUT3_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT3_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT4_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT4_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT4_RD_MASK, EVC_AGC_EVC1_MODE_LUT4_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT4_OFFSET");//

            //write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_LUT5_OFFSET, \
                                    EVC_AGC_EVC1_MODE_LUT5_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_LUT5_RD_MASK, EVC_AGC_EVC1_MODE_LUT5_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_LUT5_OFFSET");//

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_MODE_ACC_OFFSET, \
                                    EVC_AGC_EVC1_MODE_ACC_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_MODE_ACC_RD_MASK, EVC_AGC_EVC1_MODE_ACC_WR_MASK, \
                                    "EVC_AGC_EVC1_MODE_ACC_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_STAT_OFFSET, \
                                    EVC_AGC_EVC1_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_STAT_RD_MASK, EVC_AGC_EVC1_STAT_WR_MASK, \
                                    "EVC_AGC_EVC1_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_PERR_CNT_OFFSET, \
                                    EVC_AGC_EVC1_PERR_CNT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_PERR_CNT_RD_MASK, EVC_AGC_EVC1_PERR_CNT_WR_MASK, \
                                    "EVC_AGC_EVC1_PERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_SERR_CNT_OFFSET, \
                                    EVC_AGC_EVC1_SERR_CNT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_SERR_CNT_RD_MASK, EVC_AGC_EVC1_SERR_CNT_WR_MASK, \
                                    "EVC_AGC_EVC1_SERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_ERR_STAT_OFFSET, \
                                    EVC_AGC_EVC1_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_ERR_STAT_RD_MASK, EVC_AGC_EVC1_ERR_STAT_WR_MASK, \
                                    "EVC_AGC_EVC1_ERR_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_ECC_CTRL_OFFSET, \
                                    EVC_AGC_EVC1_ECC_CTRL_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_ECC_CTRL_RD_MASK, EVC_AGC_EVC1_ECC_CTRL_WR_MASK, \
                                    "EVC_AGC_EVC1_ECC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EVC1_ECC_STAT_OFFSET, \
                                    EVC_AGC_EVC1_ECC_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EVC1_ECC_STAT_RD_MASK, EVC_AGC_EVC1_ECC_STAT_WR_MASK, \
                                    "EVC_AGC_EVC1_ECC_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CFG_OFFSET, \
                                    EVC_AGC_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CFG_RD_MASK, EVC_AGC_CFG_WR_MASK, \
                                    "EVC_AGC_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_3B5_CFG_OFFSET, \
                                    EVC_AGC_3B5_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_3B5_CFG_RD_MASK, EVC_AGC_3B5_CFG_WR_MASK, \
                                    "EVC_AGC_3B5_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_3B5_OFFSET, \
                                    EVC_AGC_3B5_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_3B5_RD_MASK, EVC_AGC_3B5_WR_MASK, \
                                    "EVC_AGC_3B5_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GRP_LUT_OFFSET, \
                                    EVC_AGC_GRP_LUT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GRP_LUT_RD_MASK, EVC_AGC_GRP_LUT_WR_MASK, \
                                    "EVC_AGC_GRP_LUT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_LOG2PHY0_OFFSET, \
                                    EVC_AGC_LOG2PHY0_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_LOG2PHY0_RD_MASK, EVC_AGC_LOG2PHY0_WR_MASK, \
                                    "EVC_AGC_LOG2PHY0_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_LOG2PHY1_OFFSET, \
                                    EVC_AGC_LOG2PHY1_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_LOG2PHY1_RD_MASK, EVC_AGC_LOG2PHY1_WR_MASK, \
                                    "EVC_AGC_LOG2PHY1_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_STAT_OFFSET, \
                                    EVC_AGC_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_STAT_RD_MASK, EVC_AGC_STAT_WR_MASK, \
                                    "EVC_AGC_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_PERR_CNT_OFFSET, \
                                    EVC_AGC_PERR_CNT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_PERR_CNT_RD_MASK, EVC_AGC_PERR_CNT_WR_MASK, \
                                    "EVC_AGC_PERR_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_EN_MUX_OFFSET, \
                                    EVC_AGC_EN_MUX_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_EN_MUX_RD_MASK, EVC_AGC_EN_MUX_WR_MASK, \
                                    "EVC_AGC_EN_MUX_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_OUT_MUX_OFFSET, \
                                    EVC_AGC_OUT_MUX_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_OUT_MUX_RD_MASK, EVC_AGC_OUT_MUX_WR_MASK, \
                                    "EVC_AGC_OUT_MUX_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_OUT_MASK_OFFSET, \
                                    EVC_AGC_OUT_MASK_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_OUT_MASK_RD_MASK, EVC_AGC_OUT_MASK_WR_MASK, \
                                    "EVC_AGC_OUT_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_FGC_SEL_OFFSET, \
                                    EVC_AGC_FGC_SEL_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_FGC_SEL_RD_MASK, EVC_AGC_FGC_SEL_WR_MASK, \
                                    "EVC_AGC_FGC_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_RX_AC_GAIN_OFFSET, \
                                    EVC_AGC_RX_AC_GAIN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_RX_AC_GAIN_RD_MASK, EVC_AGC_RX_AC_GAIN_WR_MASK, \
                                    "EVC_AGC_RX_AC_GAIN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_RX_SLOW_GAIN_OFFSET, \
                                    EVC_AGC_RX_SLOW_GAIN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_RX_SLOW_GAIN_RD_MASK, EVC_AGC_RX_SLOW_GAIN_WR_MASK, \
                                    "EVC_AGC_RX_SLOW_GAIN_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_OUT_STAT_L_OFFSET, \
                                    EVC_AGC_OUT_STAT_L_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_OUT_STAT_L_RD_MASK, EVC_AGC_OUT_STAT_L_WR_MASK, \
                                    "EVC_AGC_OUT_STAT_L_OFFSET");//

            write_read_expect_18a(base_address[i]+EVC_AGC_OUT_STAT_H_OFFSET, \
                                    EVC_AGC_OUT_STAT_H_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_OUT_STAT_H_RD_MASK, EVC_AGC_OUT_STAT_H_WR_MASK, \
                                    "EVC_AGC_OUT_STAT_H_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_MON_INT_STAT_OFFSET, \
                                    EVC_AGC_MON_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_MON_INT_STAT_RD_MASK, EVC_AGC_MON_INT_STAT_WR_MASK, \
                                    "EVC_AGC_MON_INT_STAT_OFFSET");

            //write_read_expect_18a(base_address[i]+EVC_AGC_BRDG_STAT_OFFSET, \
                                    EVC_AGC_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BRDG_STAT_RD_MASK, EVC_AGC_BRDG_STAT_WR_MASK, \
                                    "EVC_AGC_BRDG_STAT_OFFSET");//

            write_read_expect_18a(base_address[i]+EVC_AGC_BUS_ERR_INT_STAT_OFFSET, \
                                    EVC_AGC_BUS_ERR_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BUS_ERR_INT_STAT_RD_MASK, EVC_AGC_BUS_ERR_INT_STAT_WR_MASK, \
                                    "EVC_AGC_BUS_ERR_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_BUS_ERR_HI_EN_OFFSET, \
                                    EVC_AGC_BUS_ERR_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BUS_ERR_HI_EN_RD_MASK, EVC_AGC_BUS_ERR_HI_EN_WR_MASK, \
                                    "EVC_AGC_BUS_ERR_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_BUS_ERR_LO_EN_OFFSET, \
                                    EVC_AGC_BUS_ERR_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BUS_ERR_LO_EN_RD_MASK, EVC_AGC_BUS_ERR_LO_EN_WR_MASK, \
                                    "EVC_AGC_BUS_ERR_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_BUS_ERR_CLR_OFFSET, \
                                    EVC_AGC_BUS_ERR_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BUS_ERR_CLR_RD_MASK, EVC_AGC_BUS_ERR_CLR_WR_MASK, \
                                    "EVC_AGC_BUS_ERR_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_BUS_ERR_FORCE_OFFSET, \
                                    EVC_AGC_BUS_ERR_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_BUS_ERR_FORCE_RD_MASK, EVC_AGC_BUS_ERR_FORCE_WR_MASK, \
                                    "EVC_AGC_BUS_ERR_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_RISE_INT_STAT_OFFSET, \
                                    EVC_AGC_TX_RX_RISE_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_RISE_INT_STAT_RD_MASK, EVC_AGC_TX_RX_RISE_INT_STAT_WR_MASK, \
                                    "EVC_AGC_TX_RX_RISE_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_RISE_HI_EN_OFFSET, \
                                    EVC_AGC_TX_RX_RISE_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_RISE_HI_EN_RD_MASK, EVC_AGC_TX_RX_RISE_HI_EN_WR_MASK, \
                                    "EVC_AGC_TX_RX_RISE_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_RISE_LO_EN_OFFSET, \
                                    EVC_AGC_TX_RX_RISE_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_RISE_LO_EN_RD_MASK, EVC_AGC_TX_RX_RISE_LO_EN_WR_MASK, \
                                    "EVC_AGC_TX_RX_RISE_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_RISE_CLR_OFFSET, \
                                    EVC_AGC_TX_RX_RISE_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_RISE_CLR_RD_MASK, EVC_AGC_TX_RX_RISE_CLR_WR_MASK, \
                                    "EVC_AGC_TX_RX_RISE_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_RISE_FORCE_OFFSET, \
                                    EVC_AGC_TX_RX_RISE_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_RISE_FORCE_RD_MASK, EVC_AGC_TX_RX_RISE_FORCE_WR_MASK, \
                                    "EVC_AGC_TX_RX_RISE_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_FALL_INT_STAT_OFFSET, \
                                    EVC_AGC_TX_RX_FALL_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_FALL_INT_STAT_RD_MASK, EVC_AGC_TX_RX_FALL_INT_STAT_WR_MASK, \
                                    "EVC_AGC_TX_RX_FALL_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_FALL_HI_EN_OFFSET, \
                                    EVC_AGC_TX_RX_FALL_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_FALL_HI_EN_RD_MASK, EVC_AGC_TX_RX_FALL_HI_EN_WR_MASK, \
                                    "EVC_AGC_TX_RX_FALL_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_FALL_LO_EN_OFFSET, \
                                    EVC_AGC_TX_RX_FALL_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_FALL_LO_EN_RD_MASK, EVC_AGC_TX_RX_FALL_LO_EN_WR_MASK, \
                                    "EVC_AGC_TX_RX_FALL_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_FALL_CLR_OFFSET, \
                                    EVC_AGC_TX_RX_FALL_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_FALL_CLR_RD_MASK, EVC_AGC_TX_RX_FALL_CLR_WR_MASK, \
                                    "EVC_AGC_TX_RX_FALL_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_TX_RX_FALL_FORCE_OFFSET, \
                                    EVC_AGC_TX_RX_FALL_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_TX_RX_FALL_FORCE_RD_MASK, EVC_AGC_TX_RX_FALL_FORCE_WR_MASK, \
                                    "EVC_AGC_TX_RX_FALL_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_RISE_INT_STAT_OFFSET, \
                                    EVC_AGC_CTL_RISE_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_RISE_INT_STAT_RD_MASK, EVC_AGC_CTL_RISE_INT_STAT_WR_MASK, \
                                    "EVC_AGC_CTL_RISE_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_RISE_HI_EN_OFFSET, \
                                    EVC_AGC_CTL_RISE_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_RISE_HI_EN_RD_MASK, EVC_AGC_CTL_RISE_HI_EN_WR_MASK, \
                                    "EVC_AGC_CTL_RISE_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_RISE_LO_EN_OFFSET, \
                                    EVC_AGC_CTL_RISE_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_RISE_LO_EN_RD_MASK, EVC_AGC_CTL_RISE_LO_EN_WR_MASK, \
                                    "EVC_AGC_CTL_RISE_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_RISE_CLR_OFFSET, \
                                    EVC_AGC_CTL_RISE_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_RISE_CLR_RD_MASK, EVC_AGC_CTL_RISE_CLR_WR_MASK, \
                                    "EVC_AGC_CTL_RISE_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_RISE_FORCE_OFFSET, \
                                    EVC_AGC_CTL_RISE_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_RISE_FORCE_RD_MASK, EVC_AGC_CTL_RISE_FORCE_WR_MASK, \
                                    "EVC_AGC_CTL_RISE_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_FALL_INT_STAT_OFFSET, \
                                    EVC_AGC_CTL_FALL_INT_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_FALL_INT_STAT_RD_MASK, EVC_AGC_CTL_FALL_INT_STAT_WR_MASK, \
                                    "EVC_AGC_CTL_FALL_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_FALL_HI_EN_OFFSET, \
                                    EVC_AGC_CTL_FALL_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_FALL_HI_EN_RD_MASK, EVC_AGC_CTL_FALL_HI_EN_WR_MASK, \
                                    "EVC_AGC_CTL_FALL_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_FALL_LO_EN_OFFSET, \
                                    EVC_AGC_CTL_FALL_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_FALL_LO_EN_RD_MASK, EVC_AGC_CTL_FALL_LO_EN_WR_MASK, \
                                    "EVC_AGC_CTL_FALL_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_FALL_CLR_OFFSET, \
                                    EVC_AGC_CTL_FALL_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_FALL_CLR_RD_MASK, EVC_AGC_CTL_FALL_CLR_WR_MASK, \
                                    "EVC_AGC_CTL_FALL_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_CTL_FALL_FORCE_OFFSET, \
                                    EVC_AGC_CTL_FALL_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_CTL_FALL_FORCE_RD_MASK, EVC_AGC_CTL_FALL_FORCE_WR_MASK, \
                                    "EVC_AGC_CTL_FALL_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_CFG_OFFSET, \
                                    EVC_AGC_GPIO_CFG_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_CFG_RD_MASK, EVC_AGC_GPIO_CFG_WR_MASK, \
                                    "EVC_AGC_GPIO_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_CURR_IN_OFFSET, \
                                    EVC_AGC_GPIO_CURR_IN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_CURR_IN_RD_MASK, EVC_AGC_GPIO_CURR_IN_WR_MASK, \
                                    "EVC_AGC_GPIO_CURR_IN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_SET_VAL_OFFSET, \
                                    EVC_AGC_GPIO_SET_VAL_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_SET_VAL_RD_MASK, EVC_AGC_GPIO_SET_VAL_WR_MASK, \
                                    "EVC_AGC_GPIO_SET_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DR_7_0_OFFSET, \
                                    EVC_AGC_GPIO_DR_7_0_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DR_7_0_RD_MASK, EVC_AGC_GPIO_DR_7_0_WR_MASK, \
                                    "EVC_AGC_GPIO_DR_7_0_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DR_11_8_OFFSET, \
                                    EVC_AGC_GPIO_DR_11_8_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DR_11_8_RD_MASK, EVC_AGC_GPIO_DR_11_8_WR_MASK, \
                                    "EVC_AGC_GPIO_DR_11_8_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_LPR_OFFSET, \
                                    EVC_AGC_GPIO_LPR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_LPR_RD_MASK, EVC_AGC_GPIO_LPR_WR_MASK, \
                                    "EVC_AGC_GPIO_LPR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_PDE_OFFSET, \
                                    EVC_AGC_GPIO_PDE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_PDE_RD_MASK, EVC_AGC_GPIO_PDE_WR_MASK, \
                                    "EVC_AGC_GPIO_PDE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_PUE_OFFSET, \
                                    EVC_AGC_GPIO_PUE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_PUE_RD_MASK, EVC_AGC_GPIO_PUE_WR_MASK, \
                                    "EVC_AGC_GPIO_PUE_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DELTA_STAT_OFFSET, \
                                    EVC_AGC_GPIO_DELTA_STAT_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DELTA_STAT_RD_MASK, EVC_AGC_GPIO_DELTA_STAT_WR_MASK, \
                                    "EVC_AGC_GPIO_DELTA_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DELTA_HI_EN_OFFSET, \
                                    EVC_AGC_GPIO_DELTA_HI_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DELTA_HI_EN_RD_MASK, EVC_AGC_GPIO_DELTA_HI_EN_WR_MASK, \
                                    "EVC_AGC_GPIO_DELTA_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DELTA_LO_EN_OFFSET, \
                                    EVC_AGC_GPIO_DELTA_LO_EN_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DELTA_LO_EN_RD_MASK, EVC_AGC_GPIO_DELTA_LO_EN_WR_MASK, \
                                    "EVC_AGC_GPIO_DELTA_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DELTA_CLR_OFFSET, \
                                    EVC_AGC_GPIO_DELTA_CLR_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DELTA_CLR_RD_MASK, EVC_AGC_GPIO_DELTA_CLR_WR_MASK, \
                                    "EVC_AGC_GPIO_DELTA_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+EVC_AGC_GPIO_DELTA_FORCE_OFFSET, \
                                    EVC_AGC_GPIO_DELTA_FORCE_DEFAULT, write_data, expected_data, \
                                    EVC_AGC_GPIO_DELTA_FORCE_RD_MASK, EVC_AGC_GPIO_DELTA_FORCE_WR_MASK, \
                                    "EVC_AGC_GPIO_DELTA_FORCE_OFFSET");

        }

    }

}
