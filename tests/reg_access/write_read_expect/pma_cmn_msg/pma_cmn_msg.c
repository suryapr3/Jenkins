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
    DLNK_JESD0_PHY_PMA0_CMN_BASE, DLNK_JESD1_PHY_PMA0_CMN_BASE, DLNK_JESD2_PHY_PMA0_CMN_BASE, DLNK_JESD3_PHY_PMA0_CMN_BASE
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
            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_REVISION_OFFSET, \
                                    PMA_CMN_MSG_PMA_REVISION_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_REVISION_RD_MASK, PMA_CMN_MSG_PMA_REVISION_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_REVISION_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_JTAG_VER_OFFSET, \
                                    PMA_CMN_MSG_PMA_JTAG_VER_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_JTAG_VER_RD_MASK, PMA_CMN_MSG_PMA_JTAG_VER_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_JTAG_VER_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_0_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_0_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_0_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_1_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_1_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_1_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_2_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_2_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_2_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_3_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_3_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_3_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_4_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_4_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_4_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_5_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_5_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_5_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_5_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_5_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_6_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_6_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_6_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_6_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_6_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_7_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_7_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_7_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_7_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_7_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_8_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_8_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_8_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_8_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_8_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_9_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_9_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_9_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_9_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_9_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_10_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_10_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_10_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_10_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_10_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_11_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_11_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_11_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_11_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_11_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_12_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_12_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_12_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_12_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_12_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_13_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_13_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_13_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_13_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_13_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_14_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_14_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_14_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_14_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_14_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_SCRATCH_PAD_15_OFFSET, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_15_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_SCRATCH_PAD_15_RD_MASK, PMA_CMN_MSG_PMA_SCRATCH_PAD_15_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_SCRATCH_PAD_15_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_PMU_IRANGE_OFFSET, \
                                    PMA_CMN_MSG_PMA_PMU_IRANGE_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_PMU_IRANGE_RD_MASK, PMA_CMN_MSG_PMA_PMU_IRANGE_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_PMU_IRANGE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_PMU_VFORCE_OFFSET, \
                                    PMA_CMN_MSG_PMA_PMU_VFORCE_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_PMU_VFORCE_RD_MASK, PMA_CMN_MSG_PMA_PMU_VFORCE_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_PMU_VFORCE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_DIE_TEMP_OFFSET, \
                                    PMA_CMN_MSG_PMA_DIE_TEMP_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_DIE_TEMP_RD_MASK, PMA_CMN_MSG_PMA_DIE_TEMP_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_DIE_TEMP_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_PMA_CMN_FUSE_SPARE_OFFSET, \
                                    PMA_CMN_MSG_PMA_CMN_FUSE_SPARE_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_PMA_CMN_FUSE_SPARE_RD_MASK, PMA_CMN_MSG_PMA_CMN_FUSE_SPARE_WR_MASK, \
                                    "PMA_CMN_MSG_PMA_CMN_FUSE_SPARE_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CAR_CFG_OFFSET, \
                                    PMA_CMN_MSG_CMN_CAR_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CAR_CFG_RD_MASK, PMA_CMN_MSG_CMN_CAR_CFG_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CAR_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CAR_CFG_RO_OFFSET, \
                                    PMA_CMN_MSG_CMN_CAR_CFG_RO_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CAR_CFG_RO_RD_MASK, PMA_CMN_MSG_CMN_CAR_CFG_RO_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CAR_CFG_RO_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_FORCE_PUP_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_FORCE_PUP_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_FORCE_PUP_CTRL_RD_MASK, PMA_CMN_MSG_CMN_FORCE_PUP_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_FORCE_PUP_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_PWR_MNG_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_PWR_MNG_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_PWR_MNG_CTRL_RD_MASK, PMA_CMN_MSG_CMN_PWR_MNG_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_PWR_MNG_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_PWR_MNG_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_PWR_MNG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_PWR_MNG_STAT_RD_MASK, PMA_CMN_MSG_CMN_PWR_MNG_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_PWR_MNG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_FSM_MAINFSM_CTRL_OFFSET, \
                                    PMA_CMN_MSG_FSM_MAINFSM_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_FSM_MAINFSM_CTRL_RD_MASK, PMA_CMN_MSG_FSM_MAINFSM_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_FSM_MAINFSM_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_FSM_STAT_0_OFFSET, \
                                    PMA_CMN_MSG_FSM_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_FSM_STAT_0_RD_MASK, PMA_CMN_MSG_FSM_STAT_0_WR_MASK, \
                                    "PMA_CMN_MSG_FSM_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_FSM_STAT_1_OFFSET, \
                                    PMA_CMN_MSG_FSM_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_FSM_STAT_1_RD_MASK, PMA_CMN_MSG_FSM_STAT_1_WR_MASK, \
                                    "PMA_CMN_MSG_FSM_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET, \
                                    PMA_CMN_MSG_FSM_CALMASTER_PSTATE_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_FSM_CALMASTER_PSTATE_CFG_RD_MASK, PMA_CMN_MSG_FSM_CALMASTER_PSTATE_CFG_WR_MASK, \
                                    "PMA_CMN_MSG_FSM_CALMASTER_PSTATE_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET, \
                                    PMA_CMN_MSG_FSM_CALMASTER_QUAD_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_FSM_CALMASTER_QUAD_CFG_RD_MASK, PMA_CMN_MSG_FSM_CALMASTER_QUAD_CFG_WR_MASK, \
                                    "PMA_CMN_MSG_FSM_CALMASTER_QUAD_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_CTRL_OFFSET, \
                                    PMA_CMN_MSG_RPU_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_CTRL_RD_MASK, PMA_CMN_MSG_RPU_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_LUT_CFG_0_OFFSET, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_0_RD_MASK, PMA_CMN_MSG_RPU_LUT_CFG_0_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_LUT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_LUT_CFG_1_OFFSET, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_1_RD_MASK, PMA_CMN_MSG_RPU_LUT_CFG_1_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_LUT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_LUT_CFG_2_OFFSET, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_2_RD_MASK, PMA_CMN_MSG_RPU_LUT_CFG_2_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_LUT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_LUT_CFG_3_OFFSET, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_3_RD_MASK, PMA_CMN_MSG_RPU_LUT_CFG_3_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_LUT_CFG_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_LUT_CFG_4_OFFSET, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_4_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_LUT_CFG_4_RD_MASK, PMA_CMN_MSG_RPU_LUT_CFG_4_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_LUT_CFG_4_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET, \
                                    PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_0_RD_MASK, PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_0_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET, \
                                    PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_1_RD_MASK, PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_1_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_EVUP_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET, \
                                    PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_0_RD_MASK, PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_0_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET, \
                                    PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_1_RD_MASK, PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_1_WR_MASK, \
                                    "PMA_CMN_MSG_RPU_EVDN_DELAY_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RPU_EVENT_CFG_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_0_RD_MASK, PMA_CMN_MSG_CMN_RPU_EVENT_CFG_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RPU_EVENT_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RPU_EVENT_CFG_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_1_RD_MASK, PMA_CMN_MSG_CMN_RPU_EVENT_CFG_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RPU_EVENT_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RPU_EVENT_CFG_2_OFFSET, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RPU_EVENT_CFG_2_RD_MASK, PMA_CMN_MSG_CMN_RPU_EVENT_CFG_2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RPU_EVENT_CFG_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CALAVG_CTRL_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_0_RD_MASK, PMA_CMN_MSG_CMN_CALAVG_CTRL_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CALAVG_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CALAVG_CTRL_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_1_RD_MASK, PMA_CMN_MSG_CMN_CALAVG_CTRL_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CALAVG_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CALAVG_CTRL_2_OFFSET, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CALAVG_CTRL_2_RD_MASK, PMA_CMN_MSG_CMN_CALAVG_CTRL_2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CALAVG_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CALAVG_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_CALAVG_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CALAVG_STAT_RD_MASK, PMA_CMN_MSG_CMN_CALAVG_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CALAVG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_BRKPT_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_BRKPT_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_BRKPT_CTRL_RD_MASK, PMA_CMN_MSG_CMN_BRKPT_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_BRKPT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_BRKPT_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_BRKPT_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_BRKPT_STAT_RD_MASK, PMA_CMN_MSG_CMN_BRKPT_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_BRKPT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_BRKPT_CLR_OFFSET, \
                                    PMA_CMN_MSG_CMN_BRKPT_CLR_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_BRKPT_CLR_RD_MASK, PMA_CMN_MSG_CMN_BRKPT_CLR_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_BRKPT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_REF_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_REF_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_REF_CTRL_RD_MASK, PMA_CMN_MSG_CMN_REF_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_REF_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_REF_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_REF_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_REF_STAT_RD_MASK, PMA_CMN_MSG_CMN_REF_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_REF_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_OUTPUT_PIN_OVRD_OFFSET, \
                                    PMA_CMN_MSG_CMN_OUTPUT_PIN_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_OUTPUT_PIN_OVRD_RD_MASK, PMA_CMN_MSG_CMN_OUTPUT_PIN_OVRD_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_OUTPUT_PIN_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_OUTPUT_PIN_PREOVRD_OFFSET, \
                                    PMA_CMN_MSG_CMN_OUTPUT_PIN_PREOVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_OUTPUT_PIN_PREOVRD_RD_MASK, PMA_CMN_MSG_CMN_OUTPUT_PIN_PREOVRD_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_OUTPUT_PIN_PREOVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_APB_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_APB_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_APB_CTRL_RD_MASK, PMA_CMN_MSG_CMN_APB_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_APB_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_APB_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_APB_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_APB_STAT_RD_MASK, PMA_CMN_MSG_CMN_APB_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_APB_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_APB_MASK_STAT_PRELIM_OFFSET, \
                                    PMA_CMN_MSG_CMN_APB_MASK_STAT_PRELIM_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_APB_MASK_STAT_PRELIM_RD_MASK, PMA_CMN_MSG_CMN_APB_MASK_STAT_PRELIM_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_APB_MASK_STAT_PRELIM_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_APB_MASK_STAT_FINAL_OFFSET, \
                                    PMA_CMN_MSG_CMN_APB_MASK_STAT_FINAL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_APB_MASK_STAT_FINAL_RD_MASK, PMA_CMN_MSG_CMN_APB_MASK_STAT_FINAL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_APB_MASK_STAT_FINAL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_TESTBUS_CFG_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_TESTBUS_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SCRATCHY_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_0_RD_MASK, PMA_CMN_MSG_CMN_SCRATCHY_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SCRATCHY_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SCRATCHY_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_1_RD_MASK, PMA_CMN_MSG_CMN_SCRATCHY_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SCRATCHY_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SCRATCHY_2_OFFSET, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SCRATCHY_2_RD_MASK, PMA_CMN_MSG_CMN_SCRATCHY_2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SCRATCHY_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CKM_CTRL_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_0_RD_MASK, PMA_CMN_MSG_CMN_CKM_CTRL_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CKM_CTRL_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CKM_CTRL_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_1_RD_MASK, PMA_CMN_MSG_CMN_CKM_CTRL_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CKM_CTRL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CKM_CTRL_2_OFFSET, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CKM_CTRL_2_RD_MASK, PMA_CMN_MSG_CMN_CKM_CTRL_2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CKM_CTRL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CKM_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_CKM_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CKM_STAT_RD_MASK, PMA_CMN_MSG_CMN_CKM_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CKM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_BTI_CLK_CFG_OFFSET, \
                                    PMA_CMN_MSG_BTI_CLK_CFG_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_BTI_CLK_CFG_RD_MASK, PMA_CMN_MSG_BTI_CLK_CFG_WR_MASK, \
                                    "PMA_CMN_MSG_BTI_CLK_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL0_OFFSET, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL0_RD_MASK, PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL1_OFFSET, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL1_RD_MASK, PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL2_OFFSET, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL2_RD_MASK, PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_STAT_RD_MASK, PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CMPOUT_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_CTRL_RD_MASK, PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_STAT_OFFSET, \
                                    PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_STAT_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_STAT_RD_MASK, PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_STAT_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_CHARGEPUMP_CALASSIST_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_CTRL_RD_MASK, PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_OFFSET, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_RD_MASK, PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SPARE_PORT_OVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SPARE_PORT_PREOVRD_OFFSET, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_PREOVRD_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SPARE_PORT_PREOVRD_RD_MASK, PMA_CMN_MSG_CMN_SPARE_PORT_PREOVRD_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SPARE_PORT_PREOVRD_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_FORCE_EVENT_CTRL_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_FORCE_EVENT_CTRL_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_FORCE_EVENT_CTRL_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_FORCE_EVENT_CTRL_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_FORCE_EVENT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_EN_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_MASK_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_CLR_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_RAW_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_0_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_1_RD_MASK, PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_SYNTH_ICU_IRQ_STAT_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RW_SPARE_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_0_RD_MASK, PMA_CMN_MSG_CMN_RW_SPARE_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RW_SPARE_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_1_RD_MASK, PMA_CMN_MSG_CMN_RW_SPARE_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RW_SPARE_2_OFFSET, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_2_RD_MASK, PMA_CMN_MSG_CMN_RW_SPARE_2_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RW_SPARE_3_OFFSET, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RW_SPARE_3_RD_MASK, PMA_CMN_MSG_CMN_RW_SPARE_3_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RO_SPARE_0_OFFSET, \
                                    PMA_CMN_MSG_CMN_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RO_SPARE_0_RD_MASK, PMA_CMN_MSG_CMN_RO_SPARE_0_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PMA_CMN_MSG_CMN_RO_SPARE_1_OFFSET, \
                                    PMA_CMN_MSG_CMN_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PMA_CMN_MSG_CMN_RO_SPARE_1_RD_MASK, PMA_CMN_MSG_CMN_RO_SPARE_1_WR_MASK, \
                                    "PMA_CMN_MSG_CMN_RO_SPARE_1_OFFSET");

        }

    }

}
