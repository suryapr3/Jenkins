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
    DLNK_HUB_BASE
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
            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_SCRATCH_OFFSET, \
                                    DLNK_HUB_APB_HUB_SCRATCH_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_SCRATCH_RD_MASK, DLNK_HUB_APB_HUB_SCRATCH_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_VER_OFFSET, \
                                    DLNK_HUB_APB_HUB_VER_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_VER_RD_MASK, DLNK_HUB_APB_HUB_VER_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_VER_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_OFFSET, \
                                    DLNK_HUB_APB_HUB_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_RD_MASK, DLNK_HUB_APB_HUB_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_STAT_OFFSET, \
                                    DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_STAT_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_STAT_RD_MASK, DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_STAT_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_OFFSET, \
                                    DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_RD_MASK, DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_FSM_DBG_WR_SEQ_SM_OFFSET, \
                                    DLNK_HUB_APB_HUB_FSM_DBG_WR_SEQ_SM_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_FSM_DBG_WR_SEQ_SM_RD_MASK, DLNK_HUB_APB_HUB_FSM_DBG_WR_SEQ_SM_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_FSM_DBG_WR_SEQ_SM_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_DRF_TX_ALARM_SEL_OFFSET, \
                                    DLNK_HUB_APB_HUB_DRF_TX_ALARM_SEL_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_DRF_TX_ALARM_SEL_RD_MASK, DLNK_HUB_APB_HUB_DRF_TX_ALARM_SEL_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_DRF_TX_ALARM_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_EVC_TX_RX_EN_MASK_N_OFFSET, \
                                    DLNK_HUB_APB_HUB_EVC_TX_RX_EN_MASK_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_EVC_TX_RX_EN_MASK_N_RD_MASK, DLNK_HUB_APB_HUB_EVC_TX_RX_EN_MASK_N_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_EVC_TX_RX_EN_MASK_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_EVC_FB_EN_RX_STARTED_MASK_N_OFFSET, \
                                    DLNK_HUB_APB_HUB_EVC_FB_EN_RX_STARTED_MASK_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_EVC_FB_EN_RX_STARTED_MASK_N_RD_MASK, DLNK_HUB_APB_HUB_EVC_FB_EN_RX_STARTED_MASK_N_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_EVC_FB_EN_RX_STARTED_MASK_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_HUB_DRF_RX_FB_STARTED_EN_MASK_N_OFFSET, \
                                    DLNK_HUB_APB_HUB_DRF_RX_FB_STARTED_EN_MASK_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_HUB_DRF_RX_FB_STARTED_EN_MASK_N_RD_MASK, DLNK_HUB_APB_HUB_DRF_RX_FB_STARTED_EN_MASK_N_WR_MASK, \
                                    "DLNK_HUB_APB_HUB_DRF_RX_FB_STARTED_EN_MASK_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_0_OFFSET, \
                                    DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_0_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_0_RD_MASK, DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_0_WR_MASK, \
                                    "DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_1_OFFSET, \
                                    DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_1_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_1_RD_MASK, DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_1_WR_MASK, \
                                    "DLNK_HUB_APB_LDO_BGR_LDO_MISC_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_LDO_BGR_SW_RST_OFFSET, \
                                    DLNK_HUB_APB_LDO_BGR_SW_RST_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_LDO_BGR_SW_RST_RD_MASK, DLNK_HUB_APB_LDO_BGR_SW_RST_WR_MASK, \
                                    "DLNK_HUB_APB_LDO_BGR_SW_RST_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_PCIE_MEM_DIS_OFFSET, \
                                    DLNK_HUB_APB_PCIE_MEM_DIS_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_PCIE_MEM_DIS_RD_MASK, DLNK_HUB_APB_PCIE_MEM_DIS_WR_MASK, \
                                    "DLNK_HUB_APB_PCIE_MEM_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_PCIE_CLK_EN_OFFSET, \
                                    DLNK_HUB_APB_PCIE_CLK_EN_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_PCIE_CLK_EN_RD_MASK, DLNK_HUB_APB_PCIE_CLK_EN_WR_MASK, \
                                    "DLNK_HUB_APB_PCIE_CLK_EN_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_OFFSET, \
                                    DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_WR_MASK, \
                                    "DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_PCIE_SW_RST_N_OFFSET, \
                                    DLNK_HUB_APB_PCIE_SW_RST_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_PCIE_SW_RST_N_RD_MASK, DLNK_HUB_APB_PCIE_SW_RST_N_WR_MASK, \
                                    "DLNK_HUB_APB_PCIE_SW_RST_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP0_JESD_MEM_DIS_OFFSET, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_RD_MASK, DLNK_HUB_APB_JESD_MEM_DIS_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP0_JESD_MEM_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP0_JESD_CLK_EN_OFFSET, \
                                    DLNK_HUB_APB_JESD_CLK_EN_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_CLK_EN_RD_MASK, DLNK_HUB_APB_JESD_CLK_EN_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP0_JESD_CLK_EN_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP0_JESD_GLITCH_SUPPRESS_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP0_JESD_GLITCH_SUPPRESS_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP0_JESD_SW_RST_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_RD_MASK, DLNK_HUB_APB_JESD_SW_RST_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP0_JESD_SW_RST_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP1_JESD_MEM_DIS_OFFSET, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_RD_MASK, DLNK_HUB_APB_JESD_MEM_DIS_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP1_JESD_MEM_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP1_JESD_CLK_EN_OFFSET, \
                                    DLNK_HUB_APB_JESD_CLK_EN_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_CLK_EN_RD_MASK, DLNK_HUB_APB_JESD_CLK_EN_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP1_JESD_CLK_EN_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP1_JESD_GLITCH_SUPPRESS_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP1_JESD_GLITCH_SUPPRESS_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP1_JESD_SW_RST_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_RD_MASK, DLNK_HUB_APB_JESD_SW_RST_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP1_JESD_SW_RST_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP2_JESD_MEM_DIS_OFFSET, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_RD_MASK, DLNK_HUB_APB_JESD_MEM_DIS_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP2_JESD_MEM_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP2_JESD_CLK_EN_OFFSET, \
                                    DLNK_HUB_APB_JESD_CLK_EN_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_CLK_EN_RD_MASK, DLNK_HUB_APB_JESD_CLK_EN_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP2_JESD_CLK_EN_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP2_JESD_GLITCH_SUPPRESS_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP2_JESD_GLITCH_SUPPRESS_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP2_JESD_SW_RST_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_RD_MASK, DLNK_HUB_APB_JESD_SW_RST_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP2_JESD_SW_RST_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP3_JESD_MEM_DIS_OFFSET, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_MEM_DIS_RD_MASK, DLNK_HUB_APB_JESD_MEM_DIS_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP3_JESD_MEM_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP3_JESD_CLK_EN_OFFSET, \
                                    DLNK_HUB_APB_JESD_CLK_EN_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_CLK_EN_RD_MASK, DLNK_HUB_APB_JESD_CLK_EN_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP3_JESD_CLK_EN_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP3_JESD_GLITCH_SUPPRESS_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP3_JESD_GLITCH_SUPPRESS_N_OFFSET");

            write_read_expect_18a(base_address[i]+DLNK_HUB_APB_JESD_MAP3_JESD_SW_RST_N_OFFSET, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT, write_data, expected_data, \
                                    DLNK_HUB_APB_JESD_SW_RST_N_RD_MASK, DLNK_HUB_APB_JESD_SW_RST_N_WR_MASK, \
                                    "DLNK_HUB_APB_JESD_MAP3_JESD_SW_RST_N_OFFSET");

        }

    }

}
