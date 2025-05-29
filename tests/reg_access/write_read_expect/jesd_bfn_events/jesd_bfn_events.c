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
    DLNK_JESD0_BFN_EVENTS_BASE, DLNK_JESD1_BFN_EVENTS_BASE, DLNK_JESD2_BFN_EVENTS_BASE, DLNK_JESD3_BFN_EVENTS_BASE
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
            write_read_expect_18a(base_address[i]+JESD_BFNE_SCRATCH_OFFSET, \
                                    JESD_BFNE_SCRATCH_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_SCRATCH_RD_MASK, JESD_BFNE_SCRATCH_WR_MASK, \
                                    "JESD_BFNE_SCRATCH_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_BFNE_APB_BRDG_STAT_OFFSET, \
                                    JESD_BFNE_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_APB_BRDG_STAT_RD_MASK, JESD_BFNE_APB_BRDG_STAT_WR_MASK, \
                                    "JESD_BFNE_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_CTRL_OFFSET, \
                                    JESD_BFNE_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_CTRL_RD_MASK, JESD_BFNE_ISYNC_CTRL_WR_MASK, \
                                    "JESD_BFNE_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_LCNT_INC_OFFSET, \
                                    JESD_BFNE_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_LCNT_INC_RD_MASK, JESD_BFNE_ISYNC_LCNT_INC_WR_MASK, \
                                    "JESD_BFNE_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_TEN_MS_CNT_OFFSET, \
                                    JESD_BFNE_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_TEN_MS_CNT_RD_MASK, JESD_BFNE_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "JESD_BFNE_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_INC_PRE_OFFSET, \
                                    JESD_BFNE_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_INC_PRE_RD_MASK, JESD_BFNE_ISYNC_INC_PRE_WR_MASK, \
                                    "JESD_BFNE_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_CNT_ADJ_OFFSET, \
                                    JESD_BFNE_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_CNT_ADJ_RD_MASK, JESD_BFNE_ISYNC_CNT_ADJ_WR_MASK, \
                                    "JESD_BFNE_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    JESD_BFNE_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_BFN_CNT_SYNC_RD_MASK, JESD_BFNE_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "JESD_BFNE_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_ISYNC_BFN_CNT_OFFSET, \
                                    JESD_BFNE_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_ISYNC_BFN_CNT_RD_MASK, JESD_BFNE_ISYNC_BFN_CNT_WR_MASK, \
                                    "JESD_BFNE_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG0_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG1_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG2_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG3_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG4_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG5_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG6_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_CFG7_OFFSET, \
                                    JESD_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_CFG_RD_MASK, JESD_BFNE_CFG_WR_MASK, \
                                    "JESD_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR0_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR1_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR2_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR3_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR4_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR5_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR6_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_INCR7_OFFSET, \
                                    JESD_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_INCR_RD_MASK, JESD_BFNE_INCR_WR_MASK, \
                                    "JESD_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START0_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START1_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START2_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START3_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START4_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START5_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START6_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_START7_OFFSET, \
                                    JESD_BFNE_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_START_RD_MASK, JESD_BFNE_START_WR_MASK, \
                                    "JESD_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT0_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT1_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT2_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT3_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT4_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT5_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT6_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_STAT7_OFFSET, \
                                    JESD_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_STAT_RD_MASK, JESD_BFNE_STAT_WR_MASK, \
                                    "JESD_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_EVENT_VLD_OFFSET, \
                                    JESD_BFNE_BFN_CAP_EVENT_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_EVENT_VLD_RD_MASK, JESD_BFNE_BFN_CAP_EVENT_VLD_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_EVENT_VLD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_FIRST_SMPL_RCVD_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_FIRST_SMPL_RCVD_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_FIRST_SMPL_RCVD_RD_MASK, JESD_BFNE_BFN_CAP_RX_FIRST_SMPL_RCVD_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_FIRST_SMPL_RCVD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_STARTED_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_STARTED_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_STARTED_RD_MASK, JESD_BFNE_BFN_CAP_RX_STARTED_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_STARTED_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_SYSREF_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_SYSREF_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_SYSREF_RD_MASK, JESD_BFNE_BFN_CAP_RX_SYSREF_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_SYSREF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_BFN_SYNC_POINT_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_BFN_SYNC_POINT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_BFN_SYNC_POINT_RD_MASK, JESD_BFNE_BFN_CAP_RX_BFN_SYNC_POINT_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_BFN_SYNC_POINT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_ALARM_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_ALARM_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_ALARM_RD_MASK, JESD_BFNE_BFN_CAP_RX_ALARM_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_ALARM_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_HIGH_INTR_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_HIGH_INTR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_HIGH_INTR_RD_MASK, JESD_BFNE_BFN_CAP_RX_HIGH_INTR_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_HIGH_INTR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_RX_LOW_INTR_OFFSET, \
                                    JESD_BFNE_BFN_CAP_RX_LOW_INTR_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_RX_LOW_INTR_RD_MASK, JESD_BFNE_BFN_CAP_RX_LOW_INTR_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_RX_LOW_INTR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_TX_START_TRIG0_OFFSET, \
                                    JESD_BFNE_BFN_CAP_TX_START_TRIG0_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_TX_START_TRIG0_RD_MASK, JESD_BFNE_BFN_CAP_TX_START_TRIG0_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_TX_START_TRIG0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_TX_START_TRIG1_OFFSET, \
                                    JESD_BFNE_BFN_CAP_TX_START_TRIG1_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_TX_START_TRIG1_RD_MASK, JESD_BFNE_BFN_CAP_TX_START_TRIG1_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_TX_START_TRIG1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_TX_TSB_BUF_LVL_FILL_OFFSET, \
                                    JESD_BFNE_BFN_CAP_TX_TSB_BUF_LVL_FILL_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_TX_TSB_BUF_LVL_FILL_RD_MASK, JESD_BFNE_BFN_CAP_TX_TSB_BUF_LVL_FILL_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_TX_TSB_BUF_LVL_FILL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_TX_SYSREF_OFFSET, \
                                    JESD_BFNE_BFN_CAP_TX_SYSREF_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_TX_SYSREF_RD_MASK, JESD_BFNE_BFN_CAP_TX_SYSREF_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_TX_SYSREF_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_TX_BFN_SYNC_POINT_OFFSET, \
                                    JESD_BFNE_BFN_CAP_TX_BFN_SYNC_POINT_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_TX_BFN_SYNC_POINT_RD_MASK, JESD_BFNE_BFN_CAP_TX_BFN_SYNC_POINT_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_TX_BFN_SYNC_POINT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_CAP_ANT_RX_START_OFFSET, \
                                    JESD_BFNE_BFN_CAP_ANT_RX_START_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_CAP_ANT_RX_START_RD_MASK, JESD_BFNE_BFN_CAP_ANT_RX_START_WR_MASK, \
                                    "JESD_BFNE_BFN_CAP_ANT_RX_START_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_RX_SP_MON_CAP_VLD_OFFSET, \
                                    JESD_BFNE_BFN_RX_SP_MON_CAP_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_RX_SP_MON_CAP_VLD_RD_MASK, JESD_BFNE_BFN_RX_SP_MON_CAP_VLD_WR_MASK, \
                                    "JESD_BFNE_BFN_RX_SP_MON_CAP_VLD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_BFNE_BFN_TX_SP_MON_CAP_VLD_OFFSET, \
                                    JESD_BFNE_BFN_TX_SP_MON_CAP_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_BFNE_BFN_TX_SP_MON_CAP_VLD_RD_MASK, JESD_BFNE_BFN_TX_SP_MON_CAP_VLD_WR_MASK, \
                                    "JESD_BFNE_BFN_TX_SP_MON_CAP_VLD_OFFSET");

        }

    }

}
