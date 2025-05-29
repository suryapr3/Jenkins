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
    DLNK_JESD0_PHY_PMA0_TXPLL_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_TXPLL_Q0_BASE, DLNK_JESD0_PHY_PMA0_TXPLL_Q1_BASE, DLNK_JESD0_PHY_PMA0_TXPLL_Q2_BASE, DLNK_JESD0_PHY_PMA0_TXPLL_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_TXPLL_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_TXPLL_Q0_BASE, DLNK_JESD1_PHY_PMA0_TXPLL_Q1_BASE, DLNK_JESD1_PHY_PMA0_TXPLL_Q2_BASE, DLNK_JESD1_PHY_PMA0_TXPLL_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_TXPLL_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_TXPLL_Q0_BASE, DLNK_JESD2_PHY_PMA0_TXPLL_Q1_BASE, DLNK_JESD2_PHY_PMA0_TXPLL_Q2_BASE, DLNK_JESD2_PHY_PMA0_TXPLL_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_TXPLL_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_TXPLL_Q0_BASE, DLNK_JESD3_PHY_PMA0_TXPLL_Q1_BASE, DLNK_JESD3_PHY_PMA0_TXPLL_Q2_BASE, DLNK_JESD3_PHY_PMA0_TXPLL_Q3_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CAR_CFG_OFFSET, \
                                    PMA_TXPLL_MGS_CAR_CFG_DEFAULT, \
                                    PMA_TXPLL_MGS_CAR_CFG_RD_MASK, "PMA_TXPLL_MGS_CAR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CAR_CFG_RO_OFFSET, \
                                    PMA_TXPLL_MGS_CAR_CFG_RO_DEFAULT, \
                                    PMA_TXPLL_MGS_CAR_CFG_RO_RD_MASK, "PMA_TXPLL_MGS_CAR_CFG_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_0_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_0_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_0_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_1_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_1_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_1_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_2_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_2_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_2_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_3_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_3_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_3_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_4_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_4_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_4_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_5_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_5_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_5_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_6_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_6_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_6_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_6_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCH_PAD_7_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_7_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCH_PAD_7_RD_MASK, "PMA_TXPLL_MGS_SCRATCH_PAD_7_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_FORCE_PUP_CTRL_OFFSET, \
                                    PMA_TXPLL_MGS_FORCE_PUP_CTRL_DEFAULT, \
                                    PMA_TXPLL_MGS_FORCE_PUP_CTRL_RD_MASK, "PMA_TXPLL_MGS_FORCE_PUP_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_PWR_MNG_CTRL_OFFSET, \
                                    PMA_TXPLL_MGS_PWR_MNG_CTRL_DEFAULT, \
                                    PMA_TXPLL_MGS_PWR_MNG_CTRL_RD_MASK, "PMA_TXPLL_MGS_PWR_MNG_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_PWR_MNG_STAT_OFFSET, \
                                    PMA_TXPLL_MGS_PWR_MNG_STAT_DEFAULT, \
                                    PMA_TXPLL_MGS_PWR_MNG_STAT_RD_MASK, "PMA_TXPLL_MGS_PWR_MNG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CFG_OFFSET, \
                                    PMA_TXPLL_MGS_CFG_DEFAULT, \
                                    PMA_TXPLL_MGS_CFG_RD_MASK, "PMA_TXPLL_MGS_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CFG_RO_OFFSET, \
                                    PMA_TXPLL_MGS_CFG_RO_DEFAULT, \
                                    PMA_TXPLL_MGS_CFG_RO_RD_MASK, "PMA_TXPLL_MGS_CFG_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_POSTDIVCLK_CTRL_0_OFFSET, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_0_DEFAULT, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_0_RD_MASK, "PMA_TXPLL_MGS_POSTDIVCLK_CTRL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_POSTDIVCLK_CTRL_1_OFFSET, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_1_DEFAULT, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_1_RD_MASK, "PMA_TXPLL_MGS_POSTDIVCLK_CTRL_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_POSTDIVCLK_CTRL_2_OFFSET, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_2_DEFAULT, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_2_RD_MASK, "PMA_TXPLL_MGS_POSTDIVCLK_CTRL_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_POSTDIVCLK_CTRL_3_OFFSET, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_3_DEFAULT, \
                                    PMA_TXPLL_MGS_POSTDIVCLK_CTRL_3_RD_MASK, "PMA_TXPLL_MGS_POSTDIVCLK_CTRL_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_0_OFFSET, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_0_DEFAULT, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_0_RD_MASK, "PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_1_OFFSET, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_1_DEFAULT, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_1_RD_MASK, "PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_2_OFFSET, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_2_DEFAULT, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_2_RD_MASK, "PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_3_OFFSET, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_3_DEFAULT, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_3_RD_MASK, "PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_4_OFFSET, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_4_DEFAULT, \
                                    PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_4_RD_MASK, "PMA_TXPLL_MGS_TXPLL_DIVRATE_CTRL_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_CALMASTER_PSTATE_CFG_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_CALMASTER_PSTATE_CFG_RD_MASK, "PMA_TXPLL_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_CALMASTER_QUAD_CFG_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_CALMASTER_QUAD_CFG_RD_MASK, "PMA_TXPLL_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_0_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_1_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_2_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_2_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_2_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_3_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_3_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_3_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_4_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_4_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_4_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_5_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_5_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_5_RD_MASK, "PMA_TXPLL_MSG_FSM_RATEWIDTH_CFG_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RATEWIDTH_CASCADE_CFG_OFFSET, \
                                    PMA_TXPLL_MGS_RATEWIDTH_CASCADE_CFG_DEFAULT, \
                                    PMA_TXPLL_MGS_RATEWIDTH_CASCADE_CFG_RD_MASK, "PMA_TXPLL_MGS_RATEWIDTH_CASCADE_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_CTRL_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_CTRL_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_CTRL_RD_MASK, "PMA_TXPLL_MSG_RPU_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_LUT_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_0_RD_MASK, "PMA_TXPLL_MSG_RPU_LUT_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_LUT_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_1_RD_MASK, "PMA_TXPLL_MSG_RPU_LUT_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_LUT_CFG_2_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_2_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_2_RD_MASK, "PMA_TXPLL_MSG_RPU_LUT_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_LUT_CFG_3_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_3_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_3_RD_MASK, "PMA_TXPLL_MSG_RPU_LUT_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_LUT_CFG_4_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_4_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_LUT_CFG_4_RD_MASK, "PMA_TXPLL_MSG_RPU_LUT_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_0_RD_MASK, "PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_1_RD_MASK, "PMA_TXPLL_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_0_RD_MASK, "PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_1_RD_MASK, "PMA_TXPLL_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RPU_EVENT_CFG_0_OFFSET, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_0_RD_MASK, "PMA_TXPLL_MGS_RPU_EVENT_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RPU_EVENT_CFG_1_OFFSET, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_1_RD_MASK, "PMA_TXPLL_MGS_RPU_EVENT_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RPU_EVENT_CFG_2_OFFSET, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_2_DEFAULT, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_2_RD_MASK, "PMA_TXPLL_MGS_RPU_EVENT_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RPU_EVENT_CFG_3_OFFSET, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_3_DEFAULT, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_3_RD_MASK, "PMA_TXPLL_MGS_RPU_EVENT_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RPU_EVENT_CFG_4_OFFSET, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_4_DEFAULT, \
                                    PMA_TXPLL_MGS_RPU_EVENT_CFG_4_RD_MASK, "PMA_TXPLL_MGS_RPU_EVENT_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_STAT_0_OFFSET, \
                                    PMA_TXPLL_MGS_STAT_0_DEFAULT, \
                                    PMA_TXPLL_MGS_STAT_0_RD_MASK, "PMA_TXPLL_MGS_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_STAT_1_OFFSET, \
                                    PMA_TXPLL_MGS_STAT_1_DEFAULT, \
                                    PMA_TXPLL_MGS_STAT_1_RD_MASK, "PMA_TXPLL_MGS_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_STAT_2_OFFSET, \
                                    PMA_TXPLL_MGS_STAT_2_DEFAULT, \
                                    PMA_TXPLL_MGS_STAT_2_RD_MASK, "PMA_TXPLL_MGS_STAT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_RO_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_RO_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_RO_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_CTRL_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_RD_MASK, "PMA_TXPLL_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_PLL_STAT_CTRL_OFFSET, \
                                    PMA_TXPLL_MGS_PLL_STAT_CTRL_DEFAULT, \
                                    PMA_TXPLL_MGS_PLL_STAT_CTRL_RD_MASK, "PMA_TXPLL_MGS_PLL_STAT_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_PLL_STAT_CTRL_RO_OFFSET, \
                                    PMA_TXPLL_MGS_PLL_STAT_CTRL_RO_DEFAULT, \
                                    PMA_TXPLL_MGS_PLL_STAT_CTRL_RO_RD_MASK, "PMA_TXPLL_MGS_PLL_STAT_CTRL_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CTRL_OUT_0_OFFSET, \
                                    PMA_TXPLL_MGS_CTRL_OUT_0_DEFAULT, \
                                    PMA_TXPLL_MGS_CTRL_OUT_0_RD_MASK, "PMA_TXPLL_MGS_CTRL_OUT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_CTRL_OVRD_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_CTRL_OVRD_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_CTRL_OVRD_RD_MASK, "PMA_TXPLL_MSG_FSM_CTRL_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_FSM_CTRL_OVRD_RO_OFFSET, \
                                    PMA_TXPLL_MSG_FSM_CTRL_OVRD_RO_DEFAULT, \
                                    PMA_TXPLL_MSG_FSM_CTRL_OVRD_RO_RD_MASK, "PMA_TXPLL_MSG_FSM_CTRL_OVRD_RO_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_DCCRST_CTRL_OFFSET, \
                                    PMA_TXPLL_MGS_DCCRST_CTRL_DEFAULT, \
                                    PMA_TXPLL_MGS_DCCRST_CTRL_RD_MASK, "PMA_TXPLL_MGS_DCCRST_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_STAGGER_TIME_CFG_OFFSET, \
                                    PMA_TXPLL_MGS_STAGGER_TIME_CFG_DEFAULT, \
                                    PMA_TXPLL_MGS_STAGGER_TIME_CFG_RD_MASK, "PMA_TXPLL_MGS_STAGGER_TIME_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_OBSVR_OFFSET, \
                                    PMA_TXPLL_MGS_OBSVR_DEFAULT, \
                                    PMA_TXPLL_MGS_OBSVR_RD_MASK, "PMA_TXPLL_MGS_OBSVR_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_OUTPUT_PIN_OVRD_OFFSET, \
                                    PMA_TXPLL_MGS_OUTPUT_PIN_OVRD_DEFAULT, \
                                    PMA_TXPLL_MGS_OUTPUT_PIN_OVRD_RD_MASK, "PMA_TXPLL_MGS_OUTPUT_PIN_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_OUTPUT_PIN_PREOVRD_OFFSET, \
                                    PMA_TXPLL_MGS_OUTPUT_PIN_PREOVRD_DEFAULT, \
                                    PMA_TXPLL_MGS_OUTPUT_PIN_PREOVRD_RD_MASK, "PMA_TXPLL_MGS_OUTPUT_PIN_PREOVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_BRKPT_CTRL_OFFSET, \
                                    PMA_TXPLL_MGS_BRKPT_CTRL_DEFAULT, \
                                    PMA_TXPLL_MGS_BRKPT_CTRL_RD_MASK, "PMA_TXPLL_MGS_BRKPT_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_BRKPT_STAT_OFFSET, \
                                    PMA_TXPLL_MGS_BRKPT_STAT_DEFAULT, \
                                    PMA_TXPLL_MGS_BRKPT_STAT_RD_MASK, "PMA_TXPLL_MGS_BRKPT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_BRKPT_CLR_OFFSET, \
                                    PMA_TXPLL_MGS_BRKPT_CLR_DEFAULT, \
                                    PMA_TXPLL_MGS_BRKPT_CLR_RD_MASK, "PMA_TXPLL_MGS_BRKPT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CKM_CTRL_0_OFFSET, \
                                    PMA_TXPLL_MGS_CKM_CTRL_0_DEFAULT, \
                                    PMA_TXPLL_MGS_CKM_CTRL_0_RD_MASK, "PMA_TXPLL_MGS_CKM_CTRL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CKM_CTRL_1_OFFSET, \
                                    PMA_TXPLL_MGS_CKM_CTRL_1_DEFAULT, \
                                    PMA_TXPLL_MGS_CKM_CTRL_1_RD_MASK, "PMA_TXPLL_MGS_CKM_CTRL_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CKM_CTRL_2_OFFSET, \
                                    PMA_TXPLL_MGS_CKM_CTRL_2_DEFAULT, \
                                    PMA_TXPLL_MGS_CKM_CTRL_2_RD_MASK, "PMA_TXPLL_MGS_CKM_CTRL_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CKM_STAT_OFFSET, \
                                    PMA_TXPLL_MGS_CKM_STAT_DEFAULT, \
                                    PMA_TXPLL_MGS_CKM_STAT_RD_MASK, "PMA_TXPLL_MGS_CKM_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CFGLOADER_APB2STRB_CFG_OFFSET, \
                                    PMA_TXPLL_MGS_CFGLOADER_APB2STRB_CFG_DEFAULT, \
                                    PMA_TXPLL_MGS_CFGLOADER_APB2STRB_CFG_RD_MASK, "PMA_TXPLL_MGS_CFGLOADER_APB2STRB_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_CFGLOADER_APB2STRB_STAT_OFFSET, \
                                    PMA_TXPLL_MGS_CFGLOADER_APB2STRB_STAT_DEFAULT, \
                                    PMA_TXPLL_MGS_CFGLOADER_APB2STRB_STAT_RD_MASK, "PMA_TXPLL_MGS_CFGLOADER_APB2STRB_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_LOCKTIME_OFFSET, \
                                    PMA_TXPLL_MGS_LOCKTIME_DEFAULT, \
                                    PMA_TXPLL_MGS_LOCKTIME_RD_MASK, "PMA_TXPLL_MGS_LOCKTIME_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCHY_0_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCHY_0_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCHY_0_RD_MASK, "PMA_TXPLL_MGS_SCRATCHY_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_SCRATCHY_1_OFFSET, \
                                    PMA_TXPLL_MGS_SCRATCHY_1_DEFAULT, \
                                    PMA_TXPLL_MGS_SCRATCHY_1_RD_MASK, "PMA_TXPLL_MGS_SCRATCHY_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_TESTBUS_CFG_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_CFG_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_CFG_0_RD_MASK, "PMA_TXPLL_MSG_LANE_TESTBUS_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_TESTBUS_CFG_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_CFG_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_CFG_1_RD_MASK, "PMA_TXPLL_MSG_LANE_TESTBUS_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_TESTBUS_STAT_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_STAT_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_STAT_0_RD_MASK, "PMA_TXPLL_MSG_LANE_TESTBUS_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_TESTBUS_STAT_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_STAT_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_TESTBUS_STAT_1_RD_MASK, "PMA_TXPLL_MSG_LANE_TESTBUS_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_CTRL_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_CTRL_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_CTRL_RD_MASK, "PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_RD_MASK, "PMA_TXPLL_MSG_LANE_SPARE_PORT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_SPARE_PORT_PREOVRD_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_PREOVRD_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_SPARE_PORT_PREOVRD_RD_MASK, "PMA_TXPLL_MSG_LANE_SPARE_PORT_PREOVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_FORCE_EVENT_CTRL_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_FORCE_EVENT_CTRL_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_FORCE_EVENT_CTRL_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_FORCE_EVENT_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_0_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_1_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_EN_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_0_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_1_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_MASK_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_0_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_1_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_CLR_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_0_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_1_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_RAW_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_0_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_0_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_0_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_1_OFFSET, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_1_DEFAULT, \
                                    PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_1_RD_MASK, "PMA_TXPLL_MSG_LANE_ICU_IRQ_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_WRAPPER_RW_SPARE_OFFSET, \
                                    PMA_TXPLL_MGS_WRAPPER_RW_SPARE_DEFAULT, \
                                    PMA_TXPLL_MGS_WRAPPER_RW_SPARE_RD_MASK, "PMA_TXPLL_MGS_WRAPPER_RW_SPARE_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_WRAPPER_RO_SPARE_OFFSET, \
                                    PMA_TXPLL_MGS_WRAPPER_RO_SPARE_DEFAULT, \
                                    PMA_TXPLL_MGS_WRAPPER_RO_SPARE_RD_MASK, "PMA_TXPLL_MGS_WRAPPER_RO_SPARE_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RW_SPARE_0_OFFSET, \
                                    PMA_TXPLL_MGS_RW_SPARE_0_DEFAULT, \
                                    PMA_TXPLL_MGS_RW_SPARE_0_RD_MASK, "PMA_TXPLL_MGS_RW_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RW_SPARE_1_OFFSET, \
                                    PMA_TXPLL_MGS_RW_SPARE_1_DEFAULT, \
                                    PMA_TXPLL_MGS_RW_SPARE_1_RD_MASK, "PMA_TXPLL_MGS_RW_SPARE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RW_SPARE_2_OFFSET, \
                                    PMA_TXPLL_MGS_RW_SPARE_2_DEFAULT, \
                                    PMA_TXPLL_MGS_RW_SPARE_2_RD_MASK, "PMA_TXPLL_MGS_RW_SPARE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RW_SPARE_3_OFFSET, \
                                    PMA_TXPLL_MGS_RW_SPARE_3_DEFAULT, \
                                    PMA_TXPLL_MGS_RW_SPARE_3_RD_MASK, "PMA_TXPLL_MGS_RW_SPARE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RO_SPARE_0_OFFSET, \
                                    PMA_TXPLL_MGS_RO_SPARE_0_DEFAULT, \
                                    PMA_TXPLL_MGS_RO_SPARE_0_RD_MASK, "PMA_TXPLL_MGS_RO_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PMA_TXPLL_MGS_RO_SPARE_1_OFFSET, \
                                    PMA_TXPLL_MGS_RO_SPARE_1_DEFAULT, \
                                    PMA_TXPLL_MGS_RO_SPARE_1_RD_MASK, "PMA_TXPLL_MGS_RO_SPARE_1_OFFSET");

    }

}
