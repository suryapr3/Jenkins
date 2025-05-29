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
    TRX_SYS0_TXSR0_BASE, TRX_SYS0_TXSR1_BASE, TRX_SYS1_TXSR0_BASE, TRX_SYS1_TXSR1_BASE, TRX_SYS2_TXSR0_BASE,
    TRX_SYS2_TXSR1_BASE, TRX_SYS3_TXSR0_BASE, TRX_SYS3_TXSR1_BASE, TRX_SYS4_TXSR0_BASE, TRX_SYS4_TXSR1_BASE,
    TRX_SYS5_TXSR0_BASE, TRX_SYS5_TXSR1_BASE, TRX_SYS6_TXSR0_BASE, TRX_SYS6_TXSR1_BASE, TRX_SYS7_TXSR0_BASE,
    TRX_SYS7_TXSR1_BASE
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
            write_read_expect_18a(base_address[i]+TXSR_SCRATCH_OFFSET, \
                                    TXSR_SCRATCH_DEFAULT, write_data, expected_data, \
                                    TXSR_SCRATCH_RD_MASK, TXSR_SCRATCH_WR_MASK, \
                                    "TXSR_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_TRIG_TSHOLD_OFFSET, \
                                    TXSR_SLEW_TRIG_TSHOLD_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_TRIG_TSHOLD_RD_MASK, TXSR_SLEW_TRIG_TSHOLD_WR_MASK, \
                                    "TXSR_SLEW_TRIG_TSHOLD_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_ALARM_CNTR_OFFSET, \
                                    TXSR_SLEW_ALARM_CNTR_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_ALARM_CNTR_RD_MASK, TXSR_SLEW_ALARM_CNTR_WR_MASK, \
                                    "TXSR_SLEW_ALARM_CNTR_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_ALARM_MASK_OFFSET, \
                                    TXSR_SLEW_ALARM_MASK_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_ALARM_MASK_RD_MASK, TXSR_SLEW_ALARM_MASK_WR_MASK, \
                                    "TXSR_SLEW_ALARM_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_TIMER_CNT_OFFSET, \
                                    TXSR_SLEW_TIMER_CNT_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_TIMER_CNT_RD_MASK, TXSR_SLEW_TIMER_CNT_WR_MASK, \
                                    "TXSR_SLEW_TIMER_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_PRE_NORMAL_TIMER_CNT_OFFSET, \
                                    TXSR_PRE_NORMAL_TIMER_CNT_DEFAULT, write_data, expected_data, \
                                    TXSR_PRE_NORMAL_TIMER_CNT_RD_MASK, TXSR_PRE_NORMAL_TIMER_CNT_WR_MASK, \
                                    "TXSR_PRE_NORMAL_TIMER_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_TMR_CFG_OFFSET, \
                                    TXSR_TMR_CFG_DEFAULT, write_data, expected_data, \
                                    TXSR_TMR_CFG_RD_MASK, TXSR_TMR_CFG_WR_MASK, \
                                    "TXSR_TMR_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_TMR_ERR_OFFSET, \
                                    TXSR_TMR_ERR_DEFAULT, write_data, expected_data, \
                                    TXSR_TMR_ERR_RD_MASK, TXSR_TMR_ERR_WR_MASK, \
                                    "TXSR_TMR_ERR_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_INT_STAT_OFFSET, \
                                    TXSR_INT_STAT_DEFAULT, write_data, expected_data, \
                                    TXSR_INT_STAT_RD_MASK, TXSR_INT_STAT_WR_MASK, \
                                    "TXSR_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_INT_HIGH_EN_OFFSET, \
                                    TXSR_INT_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    TXSR_INT_HIGH_EN_RD_MASK, TXSR_INT_HIGH_EN_WR_MASK, \
                                    "TXSR_INT_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_INT_LOW_EN_OFFSET, \
                                    TXSR_INT_LOW_EN_DEFAULT, write_data, expected_data, \
                                    TXSR_INT_LOW_EN_RD_MASK, TXSR_INT_LOW_EN_WR_MASK, \
                                    "TXSR_INT_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_INT_CLR_OFFSET, \
                                    TXSR_INT_CLR_DEFAULT, write_data, expected_data, \
                                    TXSR_INT_CLR_RD_MASK, TXSR_INT_CLR_WR_MASK, \
                                    "TXSR_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_INT_FORCE_OFFSET, \
                                    TXSR_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    TXSR_INT_FORCE_RD_MASK, TXSR_INT_FORCE_WR_MASK, \
                                    "TXSR_INT_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_ALARM_FORCE_OFFSET, \
                                    TXSR_SLEW_ALARM_FORCE_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_ALARM_FORCE_RD_MASK, TXSR_SLEW_ALARM_FORCE_WR_MASK, \
                                    "TXSR_SLEW_ALARM_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_SLEW_ALARM_STAT_OFFSET, \
                                    TXSR_SLEW_ALARM_STAT_DEFAULT, write_data, expected_data, \
                                    TXSR_SLEW_ALARM_STAT_RD_MASK, TXSR_SLEW_ALARM_STAT_WR_MASK, \
                                    "TXSR_SLEW_ALARM_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TXSR_APB_BRDG_STAT_OFFSET, \
                                    TXSR_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    TXSR_APB_BRDG_STAT_RD_MASK, TXSR_APB_BRDG_STAT_WR_MASK, \
                                    "TXSR_APB_BRDG_STAT_OFFSET");

        }

    }

}
