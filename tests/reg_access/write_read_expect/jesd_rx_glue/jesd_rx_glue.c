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
    DLNK_JESD0_RX_GLUE_BASE, DLNK_JESD1_RX_GLUE_BASE, DLNK_JESD2_RX_GLUE_BASE, DLNK_JESD3_RX_GLUE_BASE
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


        for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
        {							

              									
            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SCRATCH_OFFSET, \
                                    JESD_RX_GLUE_SCRATCH_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SCRATCH_RD_MASK, JESD_RX_GLUE_SCRATCH_WR_MASK, \
                                    "JESD_RX_GLUE_SCRATCH_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_APB_BRDG_STAT_OFFSET, \
                                    JESD_RX_GLUE_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_APB_BRDG_STAT_RD_MASK, JESD_RX_GLUE_APB_BRDG_STAT_WR_MASK, \
                                    "JESD_RX_GLUE_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SONI_OFFSET, \
                                    JESD_RX_GLUE_SONI_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SONI_RD_MASK, JESD_RX_GLUE_SONI_WR_MASK, \
                                    "JESD_RX_GLUE_SONI_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_GATE_SEL_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_DATAPATH_GATE_SEL_RD_MASK, JESD_RX_GLUE_DATAPATH_GATE_SEL_WR_MASK, \
                                    "JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_SW_EN_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_SW_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_DATAPATH_SW_EN_RD_MASK, JESD_RX_GLUE_DATAPATH_SW_EN_WR_MASK, \
                                    "JESD_RX_GLUE_DATAPATH_SW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_RD_MASK, JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_WR_MASK, \
                                    "JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_DP_START_SYNC_DLY_OFFSET, \
                                    JESD_RX_GLUE_DP_START_SYNC_DLY_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_DP_START_SYNC_DLY_RD_MASK, JESD_RX_GLUE_DP_START_SYNC_DLY_WR_MASK, \
                                    "JESD_RX_GLUE_DP_START_SYNC_DLY_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_DL_EN_EVENT_DLY_OFFSET, \
                                    JESD_RX_GLUE_DL_EN_EVENT_DLY_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_DL_EN_EVENT_DLY_RD_MASK, JESD_RX_GLUE_DL_EN_EVENT_DLY_WR_MASK, \
                                    "JESD_RX_GLUE_DL_EN_EVENT_DLY_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_ZERO_INS_EN_OFFSET, \
                                    JESD_RX_GLUE_ZERO_INS_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_ZERO_INS_EN_RD_MASK, JESD_RX_GLUE_ZERO_INS_EN_WR_MASK, \
                                    "JESD_RX_GLUE_ZERO_INS_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_START_SYNC_BYP_OFFSET, \
                                    JESD_RX_GLUE_START_SYNC_BYP_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_START_SYNC_BYP_RD_MASK, JESD_RX_GLUE_START_SYNC_BYP_WR_MASK, \
                                    "JESD_RX_GLUE_START_SYNC_BYP_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_OFFSET, \
                                    JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_RD_MASK, JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_WR_MASK, \
                                    "JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_CFG_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_CFG_RD_MASK, JESD_RX_GLUE_SMPL_VLD_MON_CFG_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_VLD_MON_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_RD_MASK, JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_RD_MASK, JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_EN_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_STS_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_STS_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_STS_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_STS_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_CLR_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_CLR_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_STS_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_STS_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_STS_RD_MASK, JESD_RX_GLUE_SMPL_CLK_ERR_STS_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_ERR_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_RD_MASK, JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_RD_MASK, JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ALM_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ALM_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_ALM_EN_RD_MASK, JESD_RX_GLUE_SMPL_CLK_ALM_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_ALM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_CLR_RD_MASK, JESD_RX_GLUE_SMPL_CLK_ERR_CLR_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_ERR_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_FRC_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_FRC_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_FRC_RD_MASK, JESD_RX_GLUE_SMPL_CLK_ERR_FRC_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_ERR_FRC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA0_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA1_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA2_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA3_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA4_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA5_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA6_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA7_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA8_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA9_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA10_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA11_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA12_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA13_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA14_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA15_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA16_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA17_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA18_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA19_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA20_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA21_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA22_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA23_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA23_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA24_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA24_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA25_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA25_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA26_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA26_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA27_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA27_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA28_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA28_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA29_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA29_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA30_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA30_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA31_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA31_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA32_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA32_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA33_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA33_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA34_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA34_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA35_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA35_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA36_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA36_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA37_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA37_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA38_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA38_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA39_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA39_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA40_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA40_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA41_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA41_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA42_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA42_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA43_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA43_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA44_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA44_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA45_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA45_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA46_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA46_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA47_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA47_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA48_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA48_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA49_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA49_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA50_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA50_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA51_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA51_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA52_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA52_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA53_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA53_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA54_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA54_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA55_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA55_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA56_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA56_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA57_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA57_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA58_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA58_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA59_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA59_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA60_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA60_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA61_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA61_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA62_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA62_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA63_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA63_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA64_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA64_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA65_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA65_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA66_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA66_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA67_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA67_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA68_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA68_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA69_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA69_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA70_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA70_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA71_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA71_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA72_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA72_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA73_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA73_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA74_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA74_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA75_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA75_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA76_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA76_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA77_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA77_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA78_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA78_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA79_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA79_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA80_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA80_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA81_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA81_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA82_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA82_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA83_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA83_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA84_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA84_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA85_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA85_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA86_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA86_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA87_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA87_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA88_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA88_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA89_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA89_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA90_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA90_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA91_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA91_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA92_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA92_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA93_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA93_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA94_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA94_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA95_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA95_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA96_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA96_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA97_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA97_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA98_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA98_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA99_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA99_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA100_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA100_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA101_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA101_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA102_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA102_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA103_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA103_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA104_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA104_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA105_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA105_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA106_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA106_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA107_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA107_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA108_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA108_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA109_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA109_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA110_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA110_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA111_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA111_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA112_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA112_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA113_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA113_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA114_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA114_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA115_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA115_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA116_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA116_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA117_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA117_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA118_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA118_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA119_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA119_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA120_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA120_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA121_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA121_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA122_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA122_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA123_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA123_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA124_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA124_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA125_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA125_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA126_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA126_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA127_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, JESD_RX_GLUE_SMPL_INTF_CAP_DATA_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_INTF_CAP_DATA127_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_RD_MASK, JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_RD_MASK, JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_RD_MASK, JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_RD_MASK, JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_RD_MASK, JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_RD_MASK, JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_WR_MASK, \
                                    "JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_RX_GLUE_SP_MON_CAP_VLD_OFFSET, \
                                    JESD_RX_GLUE_SP_MON_CAP_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_RX_GLUE_SP_MON_CAP_VLD_RD_MASK, JESD_RX_GLUE_SP_MON_CAP_VLD_WR_MASK, \
                                    "JESD_RX_GLUE_SP_MON_CAP_VLD_OFFSET");

        }

    }

}
