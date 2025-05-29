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
    DLNK_JESD0_PHY_PMA0_CMNPLLB_BASE, DLNK_JESD1_PHY_PMA0_CMNPLLB_BASE, DLNK_JESD2_PHY_PMA0_CMNPLLB_BASE, DLNK_JESD3_PHY_PMA0_CMNPLLB_BASE
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
            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CAR_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_CAR_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CAR_CFG_RD_MASK, PMA_CMNPLLB_MSG_CAR_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CAR_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CAR_CFG_RO_OFFSET, \
                                    PMA_CMNPLLB_MSG_CAR_CFG_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CAR_CFG_RO_RD_MASK, PMA_CMNPLLB_MSG_CAR_CFG_RO_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CAR_CFG_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_0_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_1_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_2_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_3_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_3_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_3_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_4_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_4_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_4_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_5_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_5_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_5_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_5_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_6_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_6_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_6_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_6_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCH_PAD_7_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_7_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCH_PAD_7_RD_MASK, PMA_CMNPLLB_MSG_SCRATCH_PAD_7_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCH_PAD_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FORCE_PUP_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_FORCE_PUP_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FORCE_PUP_CTRL_RD_MASK, PMA_CMNPLLB_MSG_FORCE_PUP_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FORCE_PUP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_PWR_MNG_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_PWR_MNG_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_PWR_MNG_CTRL_RD_MASK, PMA_CMNPLLB_MSG_PWR_MNG_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_PWR_MNG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_PWR_MNG_STAT_OFFSET, \
                                    PMA_CMNPLLB_MSG_PWR_MNG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_PWR_MNG_STAT_RD_MASK, PMA_CMNPLLB_MSG_PWR_MNG_STAT_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_PWR_MNG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CFG_RD_MASK, PMA_CMNPLLB_MSG_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CFG_RO_OFFSET, \
                                    PMA_CMNPLLB_MSG_CFG_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CFG_RO_RD_MASK, PMA_CMNPLLB_MSG_CFG_RO_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CFG_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_0_RD_MASK, PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_1_RD_MASK, PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_POSTDIVCLK_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_0_RD_MASK, PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_1_RD_MASK, PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_2_RD_MASK, PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CMNPLL_DIVRATE_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_CALMASTER_PSTATE_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_CALMASTER_PSTATE_CFG_RD_MASK, PMA_CMNPLLB_MSG_FSM_CALMASTER_PSTATE_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_CALMASTER_QUAD_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_CALMASTER_QUAD_CFG_RD_MASK, PMA_CMNPLLB_MSG_FSM_CALMASTER_QUAD_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_2_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_3_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_3_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_3_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_4_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_4_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_4_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_5_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_5_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_5_RD_MASK, PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_5_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_RATEWIDTH_CFG_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_CTRL_RD_MASK, PMA_CMNPLLB_MSG_RPU_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_LUT_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_RPU_LUT_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_LUT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_LUT_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_RPU_LUT_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_LUT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_LUT_CFG_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_2_RD_MASK, PMA_CMNPLLB_MSG_RPU_LUT_CFG_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_LUT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_LUT_CFG_3_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_3_RD_MASK, PMA_CMNPLLB_MSG_RPU_LUT_CFG_3_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_LUT_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_LUT_CFG_4_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_LUT_CFG_4_RD_MASK, PMA_CMNPLLB_MSG_RPU_LUT_CFG_4_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_LUT_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVENT_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVENT_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVENT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVENT_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVENT_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVENT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVENT_CFG_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_2_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVENT_CFG_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVENT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RPU_EVENT_CFG_4_OFFSET, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RPU_EVENT_CFG_4_RD_MASK, PMA_CMNPLLB_MSG_RPU_EVENT_CFG_4_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RPU_EVENT_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_STAT_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_STAT_0_RD_MASK, PMA_CMNPLLB_MSG_STAT_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_STAT_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_STAT_1_RD_MASK, PMA_CMNPLLB_MSG_STAT_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_STAT_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_STAT_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_STAT_2_RD_MASK, PMA_CMNPLLB_MSG_STAT_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_STAT_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RO_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RO_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RO_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_CTRL_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_RD_MASK, PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_PLLSTARTUP_TIMER_CFG_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_PLL_STAT_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_PLL_STAT_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RD_MASK, PMA_CMNPLLB_MSG_PLL_STAT_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_PLL_STAT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RO_OFFSET, \
                                    PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RO_RD_MASK, PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RO_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_PLL_STAT_CTRL_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CTRL_OUT_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_CTRL_OUT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CTRL_OUT_0_RD_MASK, PMA_CMNPLLB_MSG_CTRL_OUT_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CTRL_OUT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RD_MASK, PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RO_OFFSET, \
                                    PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RO_RD_MASK, PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RO_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_FSM_CTRL_OVRD_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_DCCRST_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_DCCRST_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_DCCRST_CTRL_RD_MASK, PMA_CMNPLLB_MSG_DCCRST_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_DCCRST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_STAGGER_TIME_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_STAGGER_TIME_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_STAGGER_TIME_CFG_RD_MASK, PMA_CMNPLLB_MSG_STAGGER_TIME_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_STAGGER_TIME_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_OBSVR_OFFSET, \
                                    PMA_CMNPLLB_MSG_OBSVR_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_OBSVR_RD_MASK, PMA_CMNPLLB_MSG_OBSVR_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_OBSVR_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_OUTPUT_PIN_OVRD_OFFSET, \
                                    PMA_CMNPLLB_MSG_OUTPUT_PIN_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_OUTPUT_PIN_OVRD_RD_MASK, PMA_CMNPLLB_MSG_OUTPUT_PIN_OVRD_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_OUTPUT_PIN_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_OUTPUT_PIN_PREOVRD_OFFSET, \
                                    PMA_CMNPLLB_MSG_OUTPUT_PIN_PREOVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_OUTPUT_PIN_PREOVRD_RD_MASK, PMA_CMNPLLB_MSG_OUTPUT_PIN_PREOVRD_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_OUTPUT_PIN_PREOVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_BRKPT_CTRL_OFFSET, \
                                    PMA_CMNPLLB_MSG_BRKPT_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_BRKPT_CTRL_RD_MASK, PMA_CMNPLLB_MSG_BRKPT_CTRL_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_BRKPT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_BRKPT_STAT_OFFSET, \
                                    PMA_CMNPLLB_MSG_BRKPT_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_BRKPT_STAT_RD_MASK, PMA_CMNPLLB_MSG_BRKPT_STAT_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_BRKPT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_BRKPT_CLR_OFFSET, \
                                    PMA_CMNPLLB_MSG_BRKPT_CLR_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_BRKPT_CLR_RD_MASK, PMA_CMNPLLB_MSG_BRKPT_CLR_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_BRKPT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_CFG_OFFSET, \
                                    PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_CFG_RD_MASK, PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_CFG_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_STAT_OFFSET, \
                                    PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_STAT_RD_MASK, PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_STAT_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CFGLOADER_APB2STRB_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_LOCKTIME_OFFSET, \
                                    PMA_CMNPLLB_MSG_LOCKTIME_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_LOCKTIME_RD_MASK, PMA_CMNPLLB_MSG_LOCKTIME_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_LOCKTIME_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCHY_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCHY_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCHY_0_RD_MASK, PMA_CMNPLLB_MSG_SCRATCHY_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCHY_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_SCRATCHY_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_SCRATCHY_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_SCRATCHY_1_RD_MASK, PMA_CMNPLLB_MSG_SCRATCHY_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_SCRATCHY_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CKM_CTRL_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_0_RD_MASK, PMA_CMNPLLB_MSG_CKM_CTRL_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CKM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CKM_CTRL_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_1_RD_MASK, PMA_CMNPLLB_MSG_CKM_CTRL_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CKM_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CKM_CTRL_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CKM_CTRL_2_RD_MASK, PMA_CMNPLLB_MSG_CKM_CTRL_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CKM_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_CKM_STAT_OFFSET, \
                                    PMA_CMNPLLB_MSG_CKM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_CKM_STAT_RD_MASK, PMA_CMNPLLB_MSG_CKM_STAT_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_CKM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_WRAPPER_RW_SPARE_OFFSET, \
                                    PMA_CMNPLLB_MSG_WRAPPER_RW_SPARE_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_WRAPPER_RW_SPARE_RD_MASK, PMA_CMNPLLB_MSG_WRAPPER_RW_SPARE_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_WRAPPER_RW_SPARE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_WRAPPER_RO_SPARE_OFFSET, \
                                    PMA_CMNPLLB_MSG_WRAPPER_RO_SPARE_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_WRAPPER_RO_SPARE_RD_MASK, PMA_CMNPLLB_MSG_WRAPPER_RO_SPARE_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_WRAPPER_RO_SPARE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RW_SPARE_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_0_RD_MASK, PMA_CMNPLLB_MSG_RW_SPARE_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RW_SPARE_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_1_RD_MASK, PMA_CMNPLLB_MSG_RW_SPARE_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RW_SPARE_2_OFFSET, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_2_RD_MASK, PMA_CMNPLLB_MSG_RW_SPARE_2_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RW_SPARE_3_OFFSET, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RW_SPARE_3_RD_MASK, PMA_CMNPLLB_MSG_RW_SPARE_3_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RO_SPARE_0_OFFSET, \
                                    PMA_CMNPLLB_MSG_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RO_SPARE_0_RD_MASK, PMA_CMNPLLB_MSG_RO_SPARE_0_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMNPLLB_MSG_RO_SPARE_1_OFFSET, \
                                    PMA_CMNPLLB_MSG_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMNPLLB_MSG_RO_SPARE_1_RD_MASK, PMA_CMNPLLB_MSG_RO_SPARE_1_WR_MASK, \
                                    "PMA_CMNPLLB_MSG_RO_SPARE_1_OFFSET");

        }

    }

}
