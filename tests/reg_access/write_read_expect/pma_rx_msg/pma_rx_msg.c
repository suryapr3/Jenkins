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
    DLNK_JESD0_PHY_PMA0_RX_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RX_Q0_BASE, DLNK_JESD0_PHY_PMA0_RX_Q1_BASE, DLNK_JESD0_PHY_PMA0_RX_Q2_BASE, DLNK_JESD0_PHY_PMA0_RX_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RX_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RX_Q0_BASE, DLNK_JESD1_PHY_PMA0_RX_Q1_BASE, DLNK_JESD1_PHY_PMA0_RX_Q2_BASE, DLNK_JESD1_PHY_PMA0_RX_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RX_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RX_Q0_BASE, DLNK_JESD2_PHY_PMA0_RX_Q1_BASE, DLNK_JESD2_PHY_PMA0_RX_Q2_BASE, DLNK_JESD2_PHY_PMA0_RX_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RX_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RX_Q0_BASE, DLNK_JESD3_PHY_PMA0_RX_Q1_BASE, DLNK_JESD3_PHY_PMA0_RX_Q2_BASE, DLNK_JESD3_PHY_PMA0_RX_Q3_BASE
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
            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CAR_CFG_OFFSET, \
                                    PMA_RX_MGS_CAR_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CAR_CFG_RD_MASK, PMA_RX_MGS_CAR_CFG_WR_MASK, \
                                    "PMA_RX_MGS_CAR_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CAR_CFG_RO_OFFSET, \
                                    PMA_RX_MGS_CAR_CFG_RO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CAR_CFG_RO_RD_MASK, PMA_RX_MGS_CAR_CFG_RO_WR_MASK, \
                                    "PMA_RX_MGS_CAR_CFG_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_0_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_0_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_0_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_1_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_1_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_1_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_2_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_2_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_2_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_3_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_3_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_3_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_4_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_4_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_4_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_5_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_5_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_5_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_6_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_6_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_6_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCH_PAD_7_OFFSET, \
                                    PMA_RX_MGS_SCRATCH_PAD_7_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCH_PAD_7_RD_MASK, PMA_RX_MGS_SCRATCH_PAD_7_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCH_PAD_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_0_RD_MASK, PMA_RX_MGS_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_1_RD_MASK, PMA_RX_MGS_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_RO_OFFSET, \
                                    PMA_RX_MGS_CTRL_RO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_RO_RD_MASK, PMA_RX_MGS_CTRL_RO_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_CFG_OFFSET, \
                                    PMA_RX_MSG_FSM_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_CFG_RD_MASK, PMA_RX_MSG_FSM_CFG_WR_MASK, \
                                    "PMA_RX_MSG_FSM_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MEM_CTRL_OFFSET, \
                                    PMA_RX_MGS_MEM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MEM_CTRL_RD_MASK, PMA_RX_MGS_MEM_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_MEM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MEM_REQ_CTRL_OFFSET, \
                                    PMA_RX_MGS_MEM_REQ_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MEM_REQ_CTRL_RD_MASK, PMA_RX_MGS_MEM_REQ_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_MEM_REQ_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_PLL_SEL_CFG_OFFSET, \
                                    PMA_RX_MGS_PLL_SEL_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_PLL_SEL_CFG_RD_MASK, PMA_RX_MGS_PLL_SEL_CFG_WR_MASK, \
                                    "PMA_RX_MGS_PLL_SEL_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_0_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_1_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_1_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_2_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_2_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_3_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_3_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_4_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_4_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_4_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_5_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_5_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_5_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_6_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_6_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_6_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_7_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_7_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_7_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_8_OFFSET, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_8_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_8_RD_MASK, PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_8_WR_MASK, \
                                    "PMA_RX_MSG_DCO_POSTDIVCLK_CTRL_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_PWR_MNG_CTRL_OFFSET, \
                                    PMA_RX_MGS_PWR_MNG_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_PWR_MNG_CTRL_RD_MASK, PMA_RX_MGS_PWR_MNG_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_PWR_MNG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_PWR_MNG_STAT_OFFSET, \
                                    PMA_RX_MGS_PWR_MNG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_PWR_MNG_STAT_RD_MASK, PMA_RX_MGS_PWR_MNG_STAT_WR_MASK, \
                                    "PMA_RX_MGS_PWR_MNG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALDUTY_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_CALDUTY_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALDUTY_CTRL_0_RD_MASK, PMA_RX_MGS_CALDUTY_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_CALDUTY_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALDUTY_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_CALDUTY_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALDUTY_CTRL_1_RD_MASK, PMA_RX_MGS_CALDUTY_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_CALDUTY_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALFSM_CTRL_OFFSET, \
                                    PMA_RX_MGS_CALFSM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALFSM_CTRL_RD_MASK, PMA_RX_MGS_CALFSM_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_CALFSM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_STAT_0_OFFSET, \
                                    PMA_RX_MGS_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_STAT_0_RD_MASK, PMA_RX_MGS_STAT_0_WR_MASK, \
                                    "PMA_RX_MGS_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_STAT_1_OFFSET, \
                                    PMA_RX_MGS_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_STAT_1_RD_MASK, PMA_RX_MGS_STAT_1_WR_MASK, \
                                    "PMA_RX_MGS_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_STAT_2_OFFSET, \
                                    PMA_RX_MGS_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_STAT_2_RD_MASK, PMA_RX_MGS_STAT_2_WR_MASK, \
                                    "PMA_RX_MGS_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_PCS_PCIE_CTRL_OFFSET, \
                                    PMA_RX_MSG_PCS_PCIE_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_PCS_PCIE_CTRL_RD_MASK, PMA_RX_MSG_PCS_PCIE_CTRL_WR_MASK, \
                                    "PMA_RX_MSG_PCS_PCIE_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_PCS_PCIE_CTRL_RO_OFFSET, \
                                    PMA_RX_MSG_PCS_PCIE_CTRL_RO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_PCS_PCIE_CTRL_RO_RD_MASK, PMA_RX_MSG_PCS_PCIE_CTRL_RO_WR_MASK, \
                                    "PMA_RX_MSG_PCS_PCIE_CTRL_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_0_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_0_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_0_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_1_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_1_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_1_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_2_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_2_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_2_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_3_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_3_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_3_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_4_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_4_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_4_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_RATEWIDTH_CFG_5_OFFSET, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_RATEWIDTH_CFG_5_RD_MASK, PMA_RX_MSG_FSM_RATEWIDTH_CFG_5_WR_MASK, \
                                    "PMA_RX_MSG_FSM_RATEWIDTH_CFG_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET, \
                                    PMA_RX_MSG_FSM_CALMASTER_PSTATE_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_CALMASTER_PSTATE_CFG_RD_MASK, PMA_RX_MSG_FSM_CALMASTER_PSTATE_CFG_WR_MASK, \
                                    "PMA_RX_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET, \
                                    PMA_RX_MSG_FSM_CALMASTER_QUAD_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_FSM_CALMASTER_QUAD_CFG_RD_MASK, PMA_RX_MSG_FSM_CALMASTER_QUAD_CFG_WR_MASK, \
                                    "PMA_RX_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALAVG_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_CALAVG_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALAVG_CTRL_0_RD_MASK, PMA_RX_MGS_CALAVG_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_CALAVG_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALAVG_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_CALAVG_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALAVG_CTRL_1_RD_MASK, PMA_RX_MGS_CALAVG_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_CALAVG_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALAVG_CTRL_2_OFFSET, \
                                    PMA_RX_MGS_CALAVG_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALAVG_CTRL_2_RD_MASK, PMA_RX_MGS_CALAVG_CTRL_2_WR_MASK, \
                                    "PMA_RX_MGS_CALAVG_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CAL_STAT_OFFSET, \
                                    PMA_RX_MGS_CAL_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CAL_STAT_RD_MASK, PMA_RX_MGS_CAL_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CAL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CALAVG_STAT_OFFSET, \
                                    PMA_RX_MGS_CALAVG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CALAVG_STAT_RD_MASK, PMA_RX_MGS_CALAVG_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CALAVG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_CTRL_OFFSET, \
                                    PMA_RX_MSG_RPU_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_CTRL_RD_MASK, PMA_RX_MSG_RPU_CTRL_WR_MASK, \
                                    "PMA_RX_MSG_RPU_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_LUT_CFG_0_OFFSET, \
                                    PMA_RX_MSG_RPU_LUT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_LUT_CFG_0_RD_MASK, PMA_RX_MSG_RPU_LUT_CFG_0_WR_MASK, \
                                    "PMA_RX_MSG_RPU_LUT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_LUT_CFG_1_OFFSET, \
                                    PMA_RX_MSG_RPU_LUT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_LUT_CFG_1_RD_MASK, PMA_RX_MSG_RPU_LUT_CFG_1_WR_MASK, \
                                    "PMA_RX_MSG_RPU_LUT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_LUT_CFG_2_OFFSET, \
                                    PMA_RX_MSG_RPU_LUT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_LUT_CFG_2_RD_MASK, PMA_RX_MSG_RPU_LUT_CFG_2_WR_MASK, \
                                    "PMA_RX_MSG_RPU_LUT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_LUT_CFG_3_OFFSET, \
                                    PMA_RX_MSG_RPU_LUT_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_LUT_CFG_3_RD_MASK, PMA_RX_MSG_RPU_LUT_CFG_3_WR_MASK, \
                                    "PMA_RX_MSG_RPU_LUT_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_LUT_CFG_4_OFFSET, \
                                    PMA_RX_MSG_RPU_LUT_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_LUT_CFG_4_RD_MASK, PMA_RX_MSG_RPU_LUT_CFG_4_WR_MASK, \
                                    "PMA_RX_MSG_RPU_LUT_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_0_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_0_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_1_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_1_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_2_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_2_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_2_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_3_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_3_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_3_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_4_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_4_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_4_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_5_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_5_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_5_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVUP_DELAY_CFG_6_OFFSET, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVUP_DELAY_CFG_6_RD_MASK, PMA_RX_MSG_RPU_EVUP_DELAY_CFG_6_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVUP_DELAY_CFG_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_0_RD_MASK, PMA_RX_MSG_RPU_EVDN_DELAY_CFG_0_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_1_RD_MASK, PMA_RX_MSG_RPU_EVDN_DELAY_CFG_1_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVDN_DELAY_CFG_2_OFFSET, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_2_RD_MASK, PMA_RX_MSG_RPU_EVDN_DELAY_CFG_2_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVDN_DELAY_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVDN_DELAY_CFG_3_OFFSET, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_3_RD_MASK, PMA_RX_MSG_RPU_EVDN_DELAY_CFG_3_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVDN_DELAY_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_RPU_EVDN_DELAY_CFG_4_OFFSET, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_RPU_EVDN_DELAY_CFG_4_RD_MASK, PMA_RX_MSG_RPU_EVDN_DELAY_CFG_4_WR_MASK, \
                                    "PMA_RX_MSG_RPU_EVDN_DELAY_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_0_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_0_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_0_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_1_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_1_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_1_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_2_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_2_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_2_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_3_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_3_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_3_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_4_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_4_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_4_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_5_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_5_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_5_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_6_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_6_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_6_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_7_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_7_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_7_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_7_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_8_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_8_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_8_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_8_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_9_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_9_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_9_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_9_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_10_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_10_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_10_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_10_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_11_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_11_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_11_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_11_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_12_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_12_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_12_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_12_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_13_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_13_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_13_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_13_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_14_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_14_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_14_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_14_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_15_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_15_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_15_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_15_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_16_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_16_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_16_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_16_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_16_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_17_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_17_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_17_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_17_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_17_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_18_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_18_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_18_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_18_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_18_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RPU_EVENT_CFG_19_OFFSET, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_19_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RPU_EVENT_CFG_19_RD_MASK, PMA_RX_MGS_RPU_EVENT_CFG_19_WR_MASK, \
                                    "PMA_RX_MGS_RPU_EVENT_CFG_19_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_0_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_1_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_1_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_1_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_2_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_2_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_2_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_3_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_3_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_3_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_4_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_4_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_4_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_5_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_5_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_5_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_6_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_6_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_6_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_7_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_7_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_7_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_7_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_CTRL_RO_OFFSET, \
                                    PMA_RX_MSG_SIGDET_CTRL_RO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_CTRL_RO_RD_MASK, PMA_RX_MSG_SIGDET_CTRL_RO_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_CTRL_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_SIGDET_STAT_OFFSET, \
                                    PMA_RX_MSG_SIGDET_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_SIGDET_STAT_RD_MASK, PMA_RX_MSG_SIGDET_STAT_WR_MASK, \
                                    "PMA_RX_MSG_SIGDET_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_LFPS_DET_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_LFPS_DET_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_LFPS_DET_CTRL_0_RD_MASK, PMA_RX_MGS_LFPS_DET_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_LFPS_DET_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_LFPS_DET_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_LFPS_DET_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_LFPS_DET_CTRL_1_RD_MASK, PMA_RX_MGS_LFPS_DET_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_LFPS_DET_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CTRL_0_RD_MASK, PMA_RX_MGS_SQLCH_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CTRL_1_RD_MASK, PMA_RX_MGS_SQLCH_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CTRL_2_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CTRL_2_RD_MASK, PMA_RX_MGS_SQLCH_CTRL_2_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CTRL_3_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CTRL_3_RD_MASK, PMA_RX_MGS_SQLCH_CTRL_3_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CTRL_4_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CTRL_4_RD_MASK, PMA_RX_MGS_SQLCH_CTRL_4_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_STAT_OFFSET, \
                                    PMA_RX_MGS_SQLCH_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_STAT_RD_MASK, PMA_RX_MGS_SQLCH_STAT_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCHOSCMEAS_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_0_RD_MASK, PMA_RX_MGS_SQLCHOSCMEAS_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_SQLCHOSCMEAS_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCHOSCMEAS_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_1_RD_MASK, PMA_RX_MGS_SQLCHOSCMEAS_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_SQLCHOSCMEAS_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCHOSCMEAS_CTRL_2_OFFSET, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_2_RD_MASK, PMA_RX_MGS_SQLCHOSCMEAS_CTRL_2_WR_MASK, \
                                    "PMA_RX_MGS_SQLCHOSCMEAS_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCHOSCMEAS_CTRL_3_OFFSET, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCHOSCMEAS_CTRL_3_RD_MASK, PMA_RX_MGS_SQLCHOSCMEAS_CTRL_3_WR_MASK, \
                                    "PMA_RX_MGS_SQLCHOSCMEAS_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CALFSM_CTRL_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CALFSM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CALFSM_CTRL_RD_MASK, PMA_RX_MGS_SQLCH_CALFSM_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CALFSM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CALFSM_STAT_0_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_0_RD_MASK, PMA_RX_MGS_SQLCH_CALFSM_STAT_0_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CALFSM_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CALFSM_STAT_1_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_1_RD_MASK, PMA_RX_MGS_SQLCH_CALFSM_STAT_1_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CALFSM_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SQLCH_CALFSM_STAT_2_OFFSET, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SQLCH_CALFSM_STAT_2_RD_MASK, PMA_RX_MGS_SQLCH_CALFSM_STAT_2_WR_MASK, \
                                    "PMA_RX_MGS_SQLCH_CALFSM_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_OVRD_OFFSET, \
                                    PMA_RX_MGS_CTRL_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_OVRD_RD_MASK, PMA_RX_MGS_CTRL_OVRD_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_OVRD_RO_OFFSET, \
                                    PMA_RX_MGS_CTRL_OVRD_RO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_OVRD_RO_RD_MASK, PMA_RX_MGS_CTRL_OVRD_RO_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_OVRD_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CTRL_OUT_OFFSET, \
                                    PMA_RX_MGS_CTRL_OUT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CTRL_OUT_RD_MASK, PMA_RX_MGS_CTRL_OUT_WR_MASK, \
                                    "PMA_RX_MGS_CTRL_OUT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MARGIN_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_MARGIN_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MARGIN_CTRL_0_RD_MASK, PMA_RX_MGS_MARGIN_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_MARGIN_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MARGIN_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_MARGIN_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MARGIN_CTRL_1_RD_MASK, PMA_RX_MGS_MARGIN_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_MARGIN_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MARGIN_CTRL_2_OFFSET, \
                                    PMA_RX_MGS_MARGIN_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MARGIN_CTRL_2_RD_MASK, PMA_RX_MGS_MARGIN_CTRL_2_WR_MASK, \
                                    "PMA_RX_MGS_MARGIN_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MARGIN_STAT_OFFSET, \
                                    PMA_RX_MGS_MARGIN_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MARGIN_STAT_RD_MASK, PMA_RX_MGS_MARGIN_STAT_WR_MASK, \
                                    "PMA_RX_MGS_MARGIN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_INPUT_PIN_OVRD_OFFSET, \
                                    PMA_RX_MGS_INPUT_PIN_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_INPUT_PIN_OVRD_RD_MASK, PMA_RX_MGS_INPUT_PIN_OVRD_WR_MASK, \
                                    "PMA_RX_MGS_INPUT_PIN_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_INPUT_PIN_PREOVRD_OFFSET, \
                                    PMA_RX_MGS_INPUT_PIN_PREOVRD_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_INPUT_PIN_PREOVRD_RD_MASK, PMA_RX_MGS_INPUT_PIN_PREOVRD_WR_MASK, \
                                    "PMA_RX_MGS_INPUT_PIN_PREOVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OUTPUT_PIN_OVRD_0_OFFSET, \
                                    PMA_RX_MGS_OUTPUT_PIN_OVRD_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OUTPUT_PIN_OVRD_0_RD_MASK, PMA_RX_MGS_OUTPUT_PIN_OVRD_0_WR_MASK, \
                                    "PMA_RX_MGS_OUTPUT_PIN_OVRD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OUTPUT_PIN_OVRD_1_OFFSET, \
                                    PMA_RX_MGS_OUTPUT_PIN_OVRD_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OUTPUT_PIN_OVRD_1_RD_MASK, PMA_RX_MGS_OUTPUT_PIN_OVRD_1_WR_MASK, \
                                    "PMA_RX_MGS_OUTPUT_PIN_OVRD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OUTPUT_PIN_PREOVRD_0_OFFSET, \
                                    PMA_RX_MGS_OUTPUT_PIN_PREOVRD_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OUTPUT_PIN_PREOVRD_0_RD_MASK, PMA_RX_MGS_OUTPUT_PIN_PREOVRD_0_WR_MASK, \
                                    "PMA_RX_MGS_OUTPUT_PIN_PREOVRD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OUTPUT_PIN_PREOVRD_1_OFFSET, \
                                    PMA_RX_MGS_OUTPUT_PIN_PREOVRD_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OUTPUT_PIN_PREOVRD_1_RD_MASK, PMA_RX_MGS_OUTPUT_PIN_PREOVRD_1_WR_MASK, \
                                    "PMA_RX_MGS_OUTPUT_PIN_PREOVRD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_BRKPT_CTRL_OFFSET, \
                                    PMA_RX_MGS_BRKPT_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_BRKPT_CTRL_RD_MASK, PMA_RX_MGS_BRKPT_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_BRKPT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_BRKPT_STAT_OFFSET, \
                                    PMA_RX_MGS_BRKPT_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_BRKPT_STAT_RD_MASK, PMA_RX_MGS_BRKPT_STAT_WR_MASK, \
                                    "PMA_RX_MGS_BRKPT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_BRKPT_CLR_OFFSET, \
                                    PMA_RX_MGS_BRKPT_CLR_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_BRKPT_CLR_RD_MASK, PMA_RX_MGS_BRKPT_CLR_WR_MASK, \
                                    "PMA_RX_MGS_BRKPT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_STAT_OFFSET, \
                                    PMA_RX_MSG_DCO_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_STAT_RD_MASK, PMA_RX_MSG_DCO_STAT_WR_MASK, \
                                    "PMA_RX_MSG_DCO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_ANA_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_ANA_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_ANA_RD_MASK, PMA_RX_MSG_DCO_CTRL_ANA_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_ANA_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_DIG_MUXD0_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD0_RD_MASK, PMA_RX_MSG_DCO_CTRL_DIG_MUXD0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_DIG_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_DIG_MUXD1_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD1_RD_MASK, PMA_RX_MSG_DCO_CTRL_DIG_MUXD1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_DIG_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_DIG_MUXD2_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD2_RD_MASK, PMA_RX_MSG_DCO_CTRL_DIG_MUXD2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_DIG_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_DIG_MUXD3_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD3_RD_MASK, PMA_RX_MSG_DCO_CTRL_DIG_MUXD3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_DIG_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_CTRL_DIG_MUXD4_OFFSET, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_CTRL_DIG_MUXD4_RD_MASK, PMA_RX_MSG_DCO_CTRL_DIG_MUXD4_WR_MASK, \
                                    "PMA_RX_MSG_DCO_CTRL_DIG_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD0_RD_MASK, PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD1_RD_MASK, PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD2_RD_MASK, PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD3_RD_MASK, PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD4_RD_MASK, PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_CTRL_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_PKSEN_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_PKSEN_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_PKSEN_STAT_RD_MASK, PMA_RX_MGS_CDR_PKSEN_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_PKSEN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_SWING_CTRL_MUXD0_OFFSET, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD0_RD_MASK, PMA_RX_MSG_DCO_SWING_CTRL_MUXD0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_SWING_CTRL_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_SWING_CTRL_MUXD1_OFFSET, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD1_RD_MASK, PMA_RX_MSG_DCO_SWING_CTRL_MUXD1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_SWING_CTRL_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_SWING_CTRL_MUXD2_OFFSET, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD2_RD_MASK, PMA_RX_MSG_DCO_SWING_CTRL_MUXD2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_SWING_CTRL_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_SWING_CTRL_MUXD3_OFFSET, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD3_RD_MASK, PMA_RX_MSG_DCO_SWING_CTRL_MUXD3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_SWING_CTRL_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_SWING_CTRL_MUXD4_OFFSET, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_SWING_CTRL_MUXD4_RD_MASK, PMA_RX_MSG_DCO_SWING_CTRL_MUXD4_WR_MASK, \
                                    "PMA_RX_MSG_DCO_SWING_CTRL_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_0_RD_MASK, PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_1_OFFSET, \
                                    PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_1_RD_MASK, PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_BANGBANG_PD_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_BAUD_PD_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_0_RD_MASK, PMA_RX_MSG_DCO_BAUD_PD_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_BAUD_PD_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_BAUD_PD_CTRL_1_OFFSET, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_1_RD_MASK, PMA_RX_MSG_DCO_BAUD_PD_CTRL_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_BAUD_PD_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_BAUD_PD_CTRL_2_OFFSET, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_BAUD_PD_CTRL_2_RD_MASK, PMA_RX_MSG_DCO_BAUD_PD_CTRL_2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_BAUD_PD_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_LOCK_TFER_CTRL_OFFSET, \
                                    PMA_RX_MSG_DCO_LOCK_TFER_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_LOCK_TFER_CTRL_RD_MASK, PMA_RX_MSG_DCO_LOCK_TFER_CTRL_WR_MASK, \
                                    "PMA_RX_MSG_DCO_LOCK_TFER_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OPTCLFASTLOCK_CTRL_OFFSET, \
                                    PMA_RX_MSG_DCO_OPTCLFASTLOCK_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OPTCLFASTLOCK_CTRL_RD_MASK, PMA_RX_MSG_DCO_OPTCLFASTLOCK_CTRL_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OPTCLFASTLOCK_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OPTCLFASTLOCK_STAT_OFFSET, \
                                    PMA_RX_MSG_DCO_OPTCLFASTLOCK_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OPTCLFASTLOCK_STAT_RD_MASK, PMA_RX_MSG_DCO_OPTCLFASTLOCK_STAT_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OPTCLFASTLOCK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_ETH_PMD_STAT_0_OFFSET, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_0_RD_MASK, PMA_RX_MSG_DCO_ETH_PMD_STAT_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_ETH_PMD_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_ETH_PMD_STAT_1_OFFSET, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_1_RD_MASK, PMA_RX_MSG_DCO_ETH_PMD_STAT_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_ETH_PMD_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_ETH_PMD_STAT_2_OFFSET, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_2_RD_MASK, PMA_RX_MSG_DCO_ETH_PMD_STAT_2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_ETH_PMD_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_ETH_PMD_STAT_3_OFFSET, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_ETH_PMD_STAT_3_RD_MASK, PMA_RX_MSG_DCO_ETH_PMD_STAT_3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_ETH_PMD_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_0_RD_MASK, PMA_RX_MSG_DCO_OVRD_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_CTRL_1_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_1_RD_MASK, PMA_RX_MSG_DCO_OVRD_CTRL_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_CTRL_2_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_2_RD_MASK, PMA_RX_MSG_DCO_OVRD_CTRL_2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_CTRL_3_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_3_RD_MASK, PMA_RX_MSG_DCO_OVRD_CTRL_3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_CTRL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_CTRL_4_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_CTRL_4_RD_MASK, PMA_RX_MSG_DCO_OVRD_CTRL_4_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_CTRL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_PHDT_OVRD_CTRL_0_OFFSET, \
                                    PMA_RX_MSG_PHDT_OVRD_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_PHDT_OVRD_CTRL_0_RD_MASK, PMA_RX_MSG_PHDT_OVRD_CTRL_0_WR_MASK, \
                                    "PMA_RX_MSG_PHDT_OVRD_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_STAT_0_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_0_RD_MASK, PMA_RX_MSG_DCO_OVRD_STAT_0_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_STAT_1_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_1_RD_MASK, PMA_RX_MSG_DCO_OVRD_STAT_1_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_STAT_2_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_2_RD_MASK, PMA_RX_MSG_DCO_OVRD_STAT_2_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_STAT_3_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_3_RD_MASK, PMA_RX_MSG_DCO_OVRD_STAT_3_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_DCO_OVRD_STAT_4_OFFSET, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_DCO_OVRD_STAT_4_RD_MASK, PMA_RX_MSG_DCO_OVRD_STAT_4_WR_MASK, \
                                    "PMA_RX_MSG_DCO_OVRD_STAT_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_PHDT_OVRD_STAT_0_OFFSET, \
                                    PMA_RX_MSG_PHDT_OVRD_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_PHDT_OVRD_STAT_0_RD_MASK, PMA_RX_MSG_PHDT_OVRD_STAT_0_WR_MASK, \
                                    "PMA_RX_MSG_PHDT_OVRD_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_ADC_SPARE_OFFSET, \
                                    PMA_RX_MGS_ADC_SPARE_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_ADC_SPARE_RD_MASK, PMA_RX_MGS_ADC_SPARE_WR_MASK, \
                                    "PMA_RX_MGS_ADC_SPARE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CKM_CTRL_0_OFFSET, \
                                    PMA_RX_MGS_CKM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CKM_CTRL_0_RD_MASK, PMA_RX_MGS_CKM_CTRL_0_WR_MASK, \
                                    "PMA_RX_MGS_CKM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CKM_CTRL_1_OFFSET, \
                                    PMA_RX_MGS_CKM_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CKM_CTRL_1_RD_MASK, PMA_RX_MGS_CKM_CTRL_1_WR_MASK, \
                                    "PMA_RX_MGS_CKM_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CKM_CTRL_2_OFFSET, \
                                    PMA_RX_MGS_CKM_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CKM_CTRL_2_RD_MASK, PMA_RX_MGS_CKM_CTRL_2_WR_MASK, \
                                    "PMA_RX_MGS_CKM_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CKM_STAT_OFFSET, \
                                    PMA_RX_MGS_CKM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CKM_STAT_RD_MASK, PMA_RX_MGS_CKM_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CKM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_CFG_0_OFFSET, \
                                    PMA_RX_MSG_BIST_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_CFG_0_RD_MASK, PMA_RX_MSG_BIST_CFG_0_WR_MASK, \
                                    "PMA_RX_MSG_BIST_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_CFG_1_OFFSET, \
                                    PMA_RX_MSG_BIST_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_CFG_1_RD_MASK, PMA_RX_MSG_BIST_CFG_1_WR_MASK, \
                                    "PMA_RX_MSG_BIST_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_SEED_OFFSET, \
                                    PMA_RX_MSG_BIST_SEED_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_SEED_RD_MASK, PMA_RX_MSG_BIST_SEED_WR_MASK, \
                                    "PMA_RX_MSG_BIST_SEED_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF00_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF00_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF00_RD_MASK, PMA_RX_MSG_BIST_UDP_VF00_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF00_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF01_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF01_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF01_RD_MASK, PMA_RX_MSG_BIST_UDP_VF01_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF01_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF02_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF02_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF02_RD_MASK, PMA_RX_MSG_BIST_UDP_VF02_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF02_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF03_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF03_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF03_RD_MASK, PMA_RX_MSG_BIST_UDP_VF03_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF03_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF04_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF04_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF04_RD_MASK, PMA_RX_MSG_BIST_UDP_VF04_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF04_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF05_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF05_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF05_RD_MASK, PMA_RX_MSG_BIST_UDP_VF05_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF05_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF06_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF06_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF06_RD_MASK, PMA_RX_MSG_BIST_UDP_VF06_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF06_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF07_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF07_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF07_RD_MASK, PMA_RX_MSG_BIST_UDP_VF07_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF07_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF08_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF08_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF08_RD_MASK, PMA_RX_MSG_BIST_UDP_VF08_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF08_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_UDP_VF09_OFFSET, \
                                    PMA_RX_MSG_BIST_UDP_VF09_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_UDP_VF09_RD_MASK, PMA_RX_MSG_BIST_UDP_VF09_WR_MASK, \
                                    "PMA_RX_MSG_BIST_UDP_VF09_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_ERRCNT_STAT_0_OFFSET, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_0_RD_MASK, PMA_RX_MSG_BIST_ERRCNT_STAT_0_WR_MASK, \
                                    "PMA_RX_MSG_BIST_ERRCNT_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_ERRCNT_STAT_1_OFFSET, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_1_RD_MASK, PMA_RX_MSG_BIST_ERRCNT_STAT_1_WR_MASK, \
                                    "PMA_RX_MSG_BIST_ERRCNT_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_ERRCNT_STAT_2_OFFSET, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_2_RD_MASK, PMA_RX_MSG_BIST_ERRCNT_STAT_2_WR_MASK, \
                                    "PMA_RX_MSG_BIST_ERRCNT_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_ERRCNT_STAT_3_OFFSET, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_ERRCNT_STAT_3_RD_MASK, PMA_RX_MSG_BIST_ERRCNT_STAT_3_WR_MASK, \
                                    "PMA_RX_MSG_BIST_ERRCNT_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_STAT_DATACHKCNT_OFFSET, \
                                    PMA_RX_MSG_BIST_STAT_DATACHKCNT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_STAT_DATACHKCNT_RD_MASK, PMA_RX_MSG_BIST_STAT_DATACHKCNT_WR_MASK, \
                                    "PMA_RX_MSG_BIST_STAT_DATACHKCNT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_0_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_0_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_0_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_1_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_1_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_1_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_2_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_2_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_2_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_3_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_3_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_3_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_4_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_4_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_4_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_5_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_5_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_5_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_6_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_6_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_6_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_6_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_7_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_7_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_7_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_7_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_8_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_8_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_8_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_8_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_9_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_9_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_9_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_9_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_10_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_10_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_10_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_10_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_11_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_11_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_11_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_11_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_12_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_12_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_12_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_12_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_13_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_13_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_13_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_13_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_14_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_14_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_14_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_14_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_BIST_DATA_STAT_15_OFFSET, \
                                    PMA_RX_MSG_BIST_DATA_STAT_15_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_BIST_DATA_STAT_15_RD_MASK, PMA_RX_MSG_BIST_DATA_STAT_15_WR_MASK, \
                                    "PMA_RX_MSG_BIST_DATA_STAT_15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_AFFE_COEFF_SET_STAT_0_OFFSET, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_STAT_0_RD_MASK, PMA_RX_MGS_AFFE_COEFF_SET_STAT_0_WR_MASK, \
                                    "PMA_RX_MGS_AFFE_COEFF_SET_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_AFFE_COEFF_SET_STAT_1_OFFSET, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_STAT_1_RD_MASK, PMA_RX_MGS_AFFE_COEFF_SET_STAT_1_WR_MASK, \
                                    "PMA_RX_MGS_AFFE_COEFF_SET_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_AFFE_COEFF_SET_OVRD_0_OFFSET, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_OVRD_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_OVRD_0_RD_MASK, PMA_RX_MGS_AFFE_COEFF_SET_OVRD_0_WR_MASK, \
                                    "PMA_RX_MGS_AFFE_COEFF_SET_OVRD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_AFFE_COEFF_SET_OVRD_1_OFFSET, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_OVRD_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_AFFE_COEFF_SET_OVRD_1_RD_MASK, PMA_RX_MGS_AFFE_COEFF_SET_OVRD_1_WR_MASK, \
                                    "PMA_RX_MGS_AFFE_COEFF_SET_OVRD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_STAT_0_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_STAT_0_RD_MASK, PMA_RX_MGS_OPS_IF_STAT_0_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_STAT_1_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_STAT_1_RD_MASK, PMA_RX_MGS_OPS_IF_STAT_1_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_STAT_2_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_STAT_2_RD_MASK, PMA_RX_MGS_OPS_IF_STAT_2_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_OVRD_0_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_OVRD_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_OVRD_0_RD_MASK, PMA_RX_MGS_OPS_IF_OVRD_0_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_OVRD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_OVRD_1_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_OVRD_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_OVRD_1_RD_MASK, PMA_RX_MGS_OPS_IF_OVRD_1_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_OVRD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_OPS_IF_OVRD_2_OFFSET, \
                                    PMA_RX_MGS_OPS_IF_OVRD_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_OPS_IF_OVRD_2_RD_MASK, PMA_RX_MGS_OPS_IF_OVRD_2_WR_MASK, \
                                    "PMA_RX_MGS_OPS_IF_OVRD_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCHY_0_OFFSET, \
                                    PMA_RX_MGS_SCRATCHY_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCHY_0_RD_MASK, PMA_RX_MGS_SCRATCHY_0_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCHY_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_SCRATCHY_1_OFFSET, \
                                    PMA_RX_MGS_SCRATCHY_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_SCRATCHY_1_RD_MASK, PMA_RX_MGS_SCRATCHY_1_WR_MASK, \
                                    "PMA_RX_MGS_SCRATCHY_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_GENERAL_CTRL_OFFSET, \
                                    PMA_RX_MGS_CDR_GENERAL_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_GENERAL_CTRL_RD_MASK, PMA_RX_MGS_CDR_GENERAL_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_CDR_GENERAL_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_DIV0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_DIV0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_DIV0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_DIV0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_DIV0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRAC_LOCK1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD0_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD1_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD2_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD3_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD4_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_CTRL_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LOCKFSM_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_LOCKFSM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LOCKFSM_STAT_RD_MASK, PMA_RX_MGS_CDR_LOCKFSM_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LOCKFSM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TAP_OVRD_OFFSET, \
                                    PMA_RX_MGS_CDR_TAP_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TAP_OVRD_RD_MASK, PMA_RX_MGS_CDR_TAP_OVRD_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TAP_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX_DCO_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD0_RD_MASK, PMA_RX_MGS_CDR_DFX_DCO_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX_DCO_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX_DCO_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD1_RD_MASK, PMA_RX_MGS_CDR_DFX_DCO_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX_DCO_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX_DCO_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD2_RD_MASK, PMA_RX_MGS_CDR_DFX_DCO_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX_DCO_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX_DCO_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD3_RD_MASK, PMA_RX_MGS_CDR_DFX_DCO_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX_DCO_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX_DCO_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX_DCO_MUXD4_RD_MASK, PMA_RX_MGS_CDR_DFX_DCO_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX_DCO_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_RD_MASK, PMA_RX_MGS_CDR_DIV1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_DIV1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_DIV1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_DIV1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_DIV1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DIV1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DIV1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_DIV1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DIV1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CNTR_BIST_SETTINGS_OFFSET, \
                                    PMA_RX_MGS_CDR_CNTR_BIST_SETTINGS_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CNTR_BIST_SETTINGS_RD_MASK, PMA_RX_MGS_CDR_CNTR_BIST_SETTINGS_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CNTR_BIST_SETTINGS_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_CALIB0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_CALIB0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_CALIB0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_CALIB0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_CALIB0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_CALIB1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_CALIB1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_CALIB1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_CALIB1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_CALIB1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB2_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD0_RD_MASK, PMA_RX_MGS_CDR_CALIB2_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB2_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB2_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD1_RD_MASK, PMA_RX_MGS_CDR_CALIB2_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB2_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB2_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD2_RD_MASK, PMA_RX_MGS_CDR_CALIB2_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB2_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB2_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD3_RD_MASK, PMA_RX_MGS_CDR_CALIB2_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB2_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB2_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB2_MUXD4_RD_MASK, PMA_RX_MGS_CDR_CALIB2_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB2_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB3_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD0_RD_MASK, PMA_RX_MGS_CDR_CALIB3_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB3_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB3_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD1_RD_MASK, PMA_RX_MGS_CDR_CALIB3_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB3_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB3_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD2_RD_MASK, PMA_RX_MGS_CDR_CALIB3_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB3_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB3_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD3_RD_MASK, PMA_RX_MGS_CDR_CALIB3_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB3_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB3_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB3_MUXD4_RD_MASK, PMA_RX_MGS_CDR_CALIB3_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB3_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD0_RD_MASK, PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD1_RD_MASK, PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD2_RD_MASK, PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD3_RD_MASK, PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD4_RD_MASK, PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TEMP_TRACKING_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD0_RD_MASK, PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD1_RD_MASK, PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD2_RD_MASK, PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD3_RD_MASK, PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD4_RD_MASK, PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MAIN_FSM_CTRL_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL2_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD0_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL2_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL2_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL2_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD1_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL2_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL2_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL2_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD2_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL2_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL2_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL2_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD3_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL2_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL2_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL2_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL2_MUXD4_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL2_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL2_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL3_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD0_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL3_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL3_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL3_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD1_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL3_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL3_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL3_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD2_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL3_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL3_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL3_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD3_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL3_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL3_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ANA_CTRL3_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ANA_CTRL3_MUXD4_RD_MASK, PMA_RX_MGS_CDR_ANA_CTRL3_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ANA_CTRL3_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_DFX0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_DFX0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_DFX0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_DFX0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_DFX0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_DFX1_OFFSET, \
                                    PMA_RX_MGS_CDR_DFX1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_DFX1_RD_MASK, PMA_RX_MGS_CDR_DFX1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_DFX1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_LDO0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_LDO0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_LDO0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_LDO0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_LDO0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_LDO1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_LDO1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_LDO1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_LDO1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_LDO1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO2_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD0_RD_MASK, PMA_RX_MGS_CDR_LDO2_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO2_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO2_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD1_RD_MASK, PMA_RX_MGS_CDR_LDO2_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO2_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO2_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD2_RD_MASK, PMA_RX_MGS_CDR_LDO2_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO2_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO2_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD3_RD_MASK, PMA_RX_MGS_CDR_LDO2_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO2_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO2_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO2_MUXD4_RD_MASK, PMA_RX_MGS_CDR_LDO2_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO2_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_LDO_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_LDO_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_LDO_STAT_RD_MASK, PMA_RX_MGS_CDR_LDO_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_LDO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ADL0_OFFSET, \
                                    PMA_RX_MGS_CDR_ADL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ADL0_RD_MASK, PMA_RX_MGS_CDR_ADL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ADL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_ADL1_OFFSET, \
                                    PMA_RX_MGS_CDR_ADL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_ADL1_RD_MASK, PMA_RX_MGS_CDR_ADL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_ADL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC0_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD0_RD_MASK, PMA_RX_MGS_CDR_KVCC0_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC0_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC0_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD1_RD_MASK, PMA_RX_MGS_CDR_KVCC0_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC0_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC0_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD2_RD_MASK, PMA_RX_MGS_CDR_KVCC0_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC0_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC0_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD3_RD_MASK, PMA_RX_MGS_CDR_KVCC0_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC0_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC0_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC0_MUXD4_RD_MASK, PMA_RX_MGS_CDR_KVCC0_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC0_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC1_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD0_RD_MASK, PMA_RX_MGS_CDR_KVCC1_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC1_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC1_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD1_RD_MASK, PMA_RX_MGS_CDR_KVCC1_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC1_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC1_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD2_RD_MASK, PMA_RX_MGS_CDR_KVCC1_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC1_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC1_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD3_RD_MASK, PMA_RX_MGS_CDR_KVCC1_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC1_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC1_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC1_MUXD4_RD_MASK, PMA_RX_MGS_CDR_KVCC1_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC1_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC2_MUXD0_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD0_RD_MASK, PMA_RX_MGS_CDR_KVCC2_MUXD0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC2_MUXD0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC2_MUXD1_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD1_RD_MASK, PMA_RX_MGS_CDR_KVCC2_MUXD1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC2_MUXD1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC2_MUXD2_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD2_RD_MASK, PMA_RX_MGS_CDR_KVCC2_MUXD2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC2_MUXD2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC2_MUXD3_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD3_RD_MASK, PMA_RX_MGS_CDR_KVCC2_MUXD3_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC2_MUXD3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC2_MUXD4_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC2_MUXD4_RD_MASK, PMA_RX_MGS_CDR_KVCC2_MUXD4_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC2_MUXD4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_CTRL0_RD_MASK, PMA_RX_MGS_CDR_UXPPM_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_CTRL1_RD_MASK, PMA_RX_MGS_CDR_UXPPM_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_WATCHDOG_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_WATCHDOG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_WATCHDOG_RD_MASK, PMA_RX_MGS_CDR_UXPPM_WATCHDOG_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_WATCHDOG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BRKPPM_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CDR_BRKPPM_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BRKPPM_CTRL0_RD_MASK, PMA_RX_MGS_CDR_BRKPPM_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BRKPPM_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BRKPPM_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CDR_BRKPPM_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BRKPPM_CTRL1_RD_MASK, PMA_RX_MGS_CDR_BRKPPM_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BRKPPM_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL0_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL1_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_CTRL2_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_CTRL2_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_CTRL2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL0_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL1_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_HI_GAIN_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL0_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL1_RD_MASK, PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_PROP_LO_GAIN_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_QPD_ACCUM_MASK_HI_OFFSET, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_MASK_HI_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_MASK_HI_RD_MASK, PMA_RX_MGS_CDR_QPD_ACCUM_MASK_HI_WR_MASK, \
                                    "PMA_RX_MGS_CDR_QPD_ACCUM_MASK_HI_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_QPD_ACCUM_MASK_LO_OFFSET, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_MASK_LO_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_MASK_LO_RD_MASK, PMA_RX_MGS_CDR_QPD_ACCUM_MASK_LO_WR_MASK, \
                                    "PMA_RX_MGS_CDR_QPD_ACCUM_MASK_LO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_QPD_ACCUM_CTRL_OFFSET, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_CTRL_RD_MASK, PMA_RX_MGS_CDR_QPD_ACCUM_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_CDR_QPD_ACCUM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BBPD_ACCUM_MASK_OFFSET, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_MASK_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_MASK_RD_MASK, PMA_RX_MGS_CDR_BBPD_ACCUM_MASK_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BBPD_ACCUM_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BBPD_ACCUM_CTRL_OFFSET, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_CTRL_RD_MASK, PMA_RX_MGS_CDR_BBPD_ACCUM_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BBPD_ACCUM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_RW_SPARE0_OFFSET, \
                                    PMA_RX_MGS_CDR_RW_SPARE0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_RW_SPARE0_RD_MASK, PMA_RX_MGS_CDR_RW_SPARE0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_RW_SPARE0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FINE_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_FINE_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FINE_STAT_RD_MASK, PMA_RX_MGS_CDR_FINE_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FINE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BRKPPM_STAT0_OFFSET, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT0_RD_MASK, PMA_RX_MGS_CDR_BRKPPM_STAT0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BRKPPM_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BRKPPM_STAT1_OFFSET, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT1_RD_MASK, PMA_RX_MGS_CDR_BRKPPM_STAT1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BRKPPM_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BRKPPM_STAT2_OFFSET, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BRKPPM_STAT2_RD_MASK, PMA_RX_MGS_CDR_BRKPPM_STAT2_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BRKPPM_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_STAT_RD_MASK, PMA_RX_MGS_CDR_UXPPM_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_TEST_0_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_TEST_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_TEST_0_RD_MASK, PMA_RX_MGS_CDR_UXPPM_TEST_0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_TEST_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_UXPPM_TEST_1_OFFSET, \
                                    PMA_RX_MGS_CDR_UXPPM_TEST_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_UXPPM_TEST_1_RD_MASK, PMA_RX_MGS_CDR_UXPPM_TEST_1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_UXPPM_TEST_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CALIB_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_CALIB_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CALIB_STAT_RD_MASK, PMA_RX_MGS_CDR_CALIB_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CALIB_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MEAS_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_MEAS_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MEAS_STAT_RD_MASK, PMA_RX_MGS_CDR_MEAS_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MEAS_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_TIME2LOCK_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_TIME2LOCK_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_TIME2LOCK_STAT_RD_MASK, PMA_RX_MGS_CDR_TIME2LOCK_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_TIME2LOCK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FRACDIV_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_FRACDIV_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FRACDIV_STAT_RD_MASK, PMA_RX_MGS_CDR_FRACDIV_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FRACDIV_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MISC0_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_MISC0_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MISC0_STAT_RD_MASK, PMA_RX_MGS_CDR_MISC0_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MISC0_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MISC1_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_MISC1_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MISC1_STAT_RD_MASK, PMA_RX_MGS_CDR_MISC1_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MISC1_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CSELFINE_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_CSELFINE_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CSELFINE_STAT_RD_MASK, PMA_RX_MGS_CDR_CSELFINE_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CSELFINE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_REFGEN_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_REFGEN_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_REFGEN_STAT_RD_MASK, PMA_RX_MGS_CDR_REFGEN_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_REFGEN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_MISC3_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_MISC3_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_MISC3_STAT_RD_MASK, PMA_RX_MGS_CDR_MISC3_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_MISC3_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC_STAT_0_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC_STAT_0_RD_MASK, PMA_RX_MGS_CDR_KVCC_STAT_0_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_KVCC_STAT_1_OFFSET, \
                                    PMA_RX_MGS_CDR_KVCC_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_KVCC_STAT_1_RD_MASK, PMA_RX_MGS_CDR_KVCC_STAT_1_WR_MASK, \
                                    "PMA_RX_MGS_CDR_KVCC_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_FEEDFWRDGAIN_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_FEEDFWRDGAIN_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_FEEDFWRDGAIN_STAT_RD_MASK, PMA_RX_MGS_CDR_FEEDFWRDGAIN_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_FEEDFWRDGAIN_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CAP_CTRL_OFFSET, \
                                    PMA_RX_MGS_CDR_CAP_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CAP_CTRL_RD_MASK, PMA_RX_MGS_CDR_CAP_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CAP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_VOTE_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_VOTE_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_VOTE_STAT_RD_MASK, PMA_RX_MGS_CDR_VOTE_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_VOTE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_CODE_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_CODE_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_CODE_STAT_RD_MASK, PMA_RX_MGS_CDR_CODE_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_CODE_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_RO_SPARE_ANA2DIG_OFFSET, \
                                    PMA_RX_MGS_CDR_RO_SPARE_ANA2DIG_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_RO_SPARE_ANA2DIG_RD_MASK, PMA_RX_MGS_CDR_RO_SPARE_ANA2DIG_WR_MASK, \
                                    "PMA_RX_MGS_CDR_RO_SPARE_ANA2DIG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_L2R_LOCKTIME_OFFSET, \
                                    PMA_RX_MGS_CDR_L2R_LOCKTIME_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_L2R_LOCKTIME_RD_MASK, PMA_RX_MGS_CDR_L2R_LOCKTIME_WR_MASK, \
                                    "PMA_RX_MGS_CDR_L2R_LOCKTIME_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_L2D_LOCKTIME_OFFSET, \
                                    PMA_RX_MGS_CDR_L2D_LOCKTIME_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_L2D_LOCKTIME_RD_MASK, PMA_RX_MGS_CDR_L2D_LOCKTIME_WR_MASK, \
                                    "PMA_RX_MGS_CDR_L2D_LOCKTIME_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_QPD_ACCUM_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_QPD_ACCUM_STAT_RD_MASK, PMA_RX_MGS_CDR_QPD_ACCUM_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_QPD_ACCUM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_BBPD_ACCUM_STAT_OFFSET, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_BBPD_ACCUM_STAT_RD_MASK, PMA_RX_MGS_CDR_BBPD_ACCUM_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CDR_BBPD_ACCUM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CDR_RO_SPARE_OFFSET, \
                                    PMA_RX_MGS_CDR_RO_SPARE_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CDR_RO_SPARE_RD_MASK, PMA_RX_MGS_CDR_RO_SPARE_WR_MASK, \
                                    "PMA_RX_MGS_CDR_RO_SPARE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_CFG0_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_CFG0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_CFG0_RD_MASK, PMA_RX_MGS_MODE_SEL_CFG0_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_CFG1_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_CFG1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_CFG1_RD_MASK, PMA_RX_MGS_MODE_SEL_CFG1_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_CFG2_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_CFG2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_CFG2_RD_MASK, PMA_RX_MGS_MODE_SEL_CFG2_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_CFG3_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_CFG3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_CFG3_RD_MASK, PMA_RX_MGS_MODE_SEL_CFG3_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_CFG4_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_CFG4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_CFG4_RD_MASK, PMA_RX_MGS_MODE_SEL_CFG4_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_STAT0_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_STAT0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_STAT0_RD_MASK, PMA_RX_MGS_MODE_SEL_STAT0_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_STAT1_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_STAT1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_STAT1_RD_MASK, PMA_RX_MGS_MODE_SEL_STAT1_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_MODE_SEL_STAT2_OFFSET, \
                                    PMA_RX_MGS_MODE_SEL_STAT2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_MODE_SEL_STAT2_RD_MASK, PMA_RX_MGS_MODE_SEL_STAT2_WR_MASK, \
                                    "PMA_RX_MGS_MODE_SEL_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_ADCSKEWDET_CALASSIST_CTRL_OFFSET, \
                                    PMA_RX_MGS_ADCSKEWDET_CALASSIST_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_ADCSKEWDET_CALASSIST_CTRL_RD_MASK, PMA_RX_MGS_ADCSKEWDET_CALASSIST_CTRL_WR_MASK, \
                                    "PMA_RX_MGS_ADCSKEWDET_CALASSIST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_ADCSKEWDET_CALASSIST_STAT_OFFSET, \
                                    PMA_RX_MGS_ADCSKEWDET_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_ADCSKEWDET_CALASSIST_STAT_RD_MASK, PMA_RX_MGS_ADCSKEWDET_CALASSIST_STAT_WR_MASK, \
                                    "PMA_RX_MGS_ADCSKEWDET_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_CTRL_OFFSET, \
                                    PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_CTRL_RD_MASK, PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_CTRL_WR_MASK, \
                                    "PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_STAT_OFFSET, \
                                    PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_STAT_RD_MASK, PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_STAT_WR_MASK, \
                                    "PMA_RX_MSG_LANE_CHARGEPUMP_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL0_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL0_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL0_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL1_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL1_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL1_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL2_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL2_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL2_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL3_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL3_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL3_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL4_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL4_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL4_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL4_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_CTRL5_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL5_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_CTRL5_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_CTRL5_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_CTRL5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_CMPOUT_CALASSIST_STAT_OFFSET, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_CMPOUT_CALASSIST_STAT_RD_MASK, PMA_RX_MGS_CMPOUT_CALASSIST_STAT_WR_MASK, \
                                    "PMA_RX_MGS_CMPOUT_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RW_SPARE_0_OFFSET, \
                                    PMA_RX_MGS_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RW_SPARE_0_RD_MASK, PMA_RX_MGS_RW_SPARE_0_WR_MASK, \
                                    "PMA_RX_MGS_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RW_SPARE_1_OFFSET, \
                                    PMA_RX_MGS_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RW_SPARE_1_RD_MASK, PMA_RX_MGS_RW_SPARE_1_WR_MASK, \
                                    "PMA_RX_MGS_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RW_SPARE_2_OFFSET, \
                                    PMA_RX_MGS_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RW_SPARE_2_RD_MASK, PMA_RX_MGS_RW_SPARE_2_WR_MASK, \
                                    "PMA_RX_MGS_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RW_SPARE_3_OFFSET, \
                                    PMA_RX_MGS_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RW_SPARE_3_RD_MASK, PMA_RX_MGS_RW_SPARE_3_WR_MASK, \
                                    "PMA_RX_MGS_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RO_SPARE_0_OFFSET, \
                                    PMA_RX_MGS_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RO_SPARE_0_RD_MASK, PMA_RX_MGS_RO_SPARE_0_WR_MASK, \
                                    "PMA_RX_MGS_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_RX_MGS_RO_SPARE_1_OFFSET, \
                                    PMA_RX_MGS_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_RX_MGS_RO_SPARE_1_RD_MASK, PMA_RX_MGS_RO_SPARE_1_WR_MASK, \
                                    "PMA_RX_MGS_RO_SPARE_1_OFFSET");

        }

    }

}
