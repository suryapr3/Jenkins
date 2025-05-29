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


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    int i;
    init();

    uint32_t base_address[] = {
    DLNK_JESD0_RX_GLUE_BASE, DLNK_JESD1_RX_GLUE_BASE, DLNK_JESD2_RX_GLUE_BASE, DLNK_JESD3_RX_GLUE_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SCRATCH_OFFSET, \
                                    JESD_RX_GLUE_SCRATCH_DEFAULT, \
                                    JESD_RX_GLUE_SCRATCH_RD_MASK, "JESD_RX_GLUE_SCRATCH_OFFSET");

//        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_APB_BRDG_STAT_OFFSET, \
                                    JESD_RX_GLUE_APB_BRDG_STAT_DEFAULT, \
                                    JESD_RX_GLUE_APB_BRDG_STAT_RD_MASK, "JESD_RX_GLUE_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SONI_OFFSET, \
                                    JESD_RX_GLUE_SONI_DEFAULT, \
                                    JESD_RX_GLUE_SONI_RD_MASK, "JESD_RX_GLUE_SONI_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_GATE_SEL_DEFAULT, \
                                    JESD_RX_GLUE_DATAPATH_GATE_SEL_RD_MASK, "JESD_RX_GLUE_DATAPATH_GATE_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_SW_EN_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_SW_EN_DEFAULT, \
                                    JESD_RX_GLUE_DATAPATH_SW_EN_RD_MASK, "JESD_RX_GLUE_DATAPATH_SW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_OFFSET, \
                                    JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_DEFAULT, \
                                    JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_RD_MASK, "JESD_RX_GLUE_DATAPATH_INIT_CYC_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_DP_START_SYNC_DLY_OFFSET, \
                                    JESD_RX_GLUE_DP_START_SYNC_DLY_DEFAULT, \
                                    JESD_RX_GLUE_DP_START_SYNC_DLY_RD_MASK, "JESD_RX_GLUE_DP_START_SYNC_DLY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_DL_EN_EVENT_DLY_OFFSET, \
                                    JESD_RX_GLUE_DL_EN_EVENT_DLY_DEFAULT, \
                                    JESD_RX_GLUE_DL_EN_EVENT_DLY_RD_MASK, "JESD_RX_GLUE_DL_EN_EVENT_DLY_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_ZERO_INS_EN_OFFSET, \
                                    JESD_RX_GLUE_ZERO_INS_EN_DEFAULT, \
                                    JESD_RX_GLUE_ZERO_INS_EN_RD_MASK, "JESD_RX_GLUE_ZERO_INS_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_START_SYNC_BYP_OFFSET, \
                                    JESD_RX_GLUE_START_SYNC_BYP_DEFAULT, \
                                    JESD_RX_GLUE_START_SYNC_BYP_RD_MASK, "JESD_RX_GLUE_START_SYNC_BYP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_OFFSET, \
                                    JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_DEFAULT, \
                                    JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_RD_MASK, "JESD_RX_GLUE_CONV_SMPL_INTRLV_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_CFG_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_CFG_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_CFG_RD_MASK, "JESD_RX_GLUE_SMPL_VLD_MON_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_RD_MASK, "JESD_RX_GLUE_SMPL_VLD_MON_PERIOD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_OFFSET, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_RD_MASK, "JESD_RX_GLUE_SMPL_VLD_MON_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_EN_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_STS_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_STS_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_STS_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_CLR_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_CLR_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_STS_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_STS_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_STS_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ALM_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ALM_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_ALM_EN_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_ALM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_CLR_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_CLR_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_ERR_FRC_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_FRC_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_ERR_FRC_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_ERR_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA0_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA1_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA2_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA3_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA4_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA5_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA6_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA7_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA8_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA9_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA10_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA11_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA12_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA13_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA14_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA15_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA16_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA17_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA18_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA19_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA20_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA21_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA22_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA23_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA24_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA24_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA25_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA25_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA26_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA26_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA27_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA27_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA28_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA28_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA29_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA29_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA30_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA30_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA31_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA31_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA32_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA32_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA33_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA33_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA34_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA34_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA35_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA35_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA36_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA36_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA37_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA37_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA38_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA38_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA39_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA39_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA40_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA40_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA41_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA41_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA42_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA42_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA43_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA43_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA44_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA44_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA45_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA45_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA46_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA46_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA47_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA47_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA48_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA48_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA49_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA49_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA50_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA50_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA51_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA51_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA52_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA52_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA53_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA53_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA54_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA54_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA55_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA55_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA56_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA56_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA57_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA57_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA58_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA58_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA59_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA59_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA60_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA60_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA61_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA61_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA62_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA62_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA63_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA63_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA64_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA64_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA65_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA65_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA66_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA66_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA67_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA67_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA68_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA68_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA69_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA69_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA70_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA70_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA71_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA71_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA72_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA72_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA73_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA73_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA74_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA74_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA75_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA75_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA76_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA76_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA77_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA77_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA78_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA78_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA79_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA79_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA80_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA80_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA81_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA81_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA82_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA82_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA83_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA83_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA84_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA84_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA85_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA85_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA86_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA86_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA87_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA87_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA88_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA88_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA89_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA89_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA90_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA90_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA91_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA91_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA92_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA92_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA93_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA93_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA94_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA94_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA95_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA95_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA96_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA96_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA97_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA97_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA98_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA98_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA99_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA99_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA100_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA100_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA101_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA101_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA102_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA102_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA103_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA103_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA104_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA104_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA105_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA105_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA106_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA106_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA107_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA107_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA108_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA108_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA109_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA109_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA110_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA110_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA111_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA111_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA112_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA112_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA113_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA113_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA114_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA114_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA115_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA115_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA116_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA116_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA117_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA117_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA118_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA118_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA119_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA119_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA120_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA120_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA121_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA121_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA122_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA122_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA123_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA123_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA124_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA124_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA125_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA125_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA126_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA126_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_INTF_CAP_DATA127_OFFSET, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_INTF_CAP_DATA_RD_MASK, "JESD_RX_GLUE_SMPL_INTF_CAP_DATA127_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_SIG_MON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_SIG_MON_CAP_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_SIG_MON_STS_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_SIG_MON_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_DBG_SIG_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_OFFSET, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_DEFAULT, \
                                    JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_RD_MASK, "JESD_RX_GLUE_SMPL_CLK_DBG_CAP_VLD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_GLUE_SP_MON_CAP_VLD_OFFSET, \
                                    JESD_RX_GLUE_SP_MON_CAP_VLD_DEFAULT, \
                                    JESD_RX_GLUE_SP_MON_CAP_VLD_RD_MASK, "JESD_RX_GLUE_SP_MON_CAP_VLD_OFFSET");

    }

}
