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
    RCS_TIMER_GRP0_TMR0_BASE, RCS_TIMER_GRP0_TMR1_BASE, RCS_TIMER_GRP1_TMR0_BASE, RCS_TIMER_GRP1_TMR1_BASE
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
            write_read_expect_18a(base_address[i]+TIMERX8_T0_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T0_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T0_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T0_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T0_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T0_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T0_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T0_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T0_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T0_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T1_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T1_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T1_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T1_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T1_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T1_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T1_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T1_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T1_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T1_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T2_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T2_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T2_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T2_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T2_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T2_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T2_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T2_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T2_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T2_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T3_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T3_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T3_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T3_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T3_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T3_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T3_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T3_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T3_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T3_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T4_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T4_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T4_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T4_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T4_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T4_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T4_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T4_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T4_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T4_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T5_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T5_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T5_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T5_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T5_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T5_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T5_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T5_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T5_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T5_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T6_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T6_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T6_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T6_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T6_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T6_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T6_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T6_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T6_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T6_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T7_TRIG_OFFSET, \
                                    TIMERX8_T_TRIG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_TRIG_RD_MASK, TIMERX8_T_TRIG_WR_MASK, \
                                    "TIMERX8_T7_TRIG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T7_INTERVAL_OFFSET, \
                                    TIMERX8_T_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_INTERVAL_RD_MASK, TIMERX8_T_INTERVAL_WR_MASK, \
                                    "TIMERX8_T7_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T7_GPIO_MASK_OFFSET, \
                                    TIMERX8_T_GPIO_MASK_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_MASK_RD_MASK, TIMERX8_T_GPIO_MASK_WR_MASK, \
                                    "TIMERX8_T7_GPIO_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T7_GPIO_VAL_OFFSET, \
                                    TIMERX8_T_GPIO_VAL_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_GPIO_VAL_RD_MASK, TIMERX8_T_GPIO_VAL_WR_MASK, \
                                    "TIMERX8_T7_GPIO_VAL_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_T7_CFG_OFFSET, \
                                    TIMERX8_T_CFG_DEFAULT, write_data, expected_data, \
                                    TIMERX8_T_CFG_RD_MASK, TIMERX8_T_CFG_WR_MASK, \
                                    "TIMERX8_T7_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+TIMERX8_STAT_OFFSET, \
                                    TIMERX8_STAT_DEFAULT, write_data, expected_data, \
                                    TIMERX8_STAT_RD_MASK, TIMERX8_STAT_WR_MASK, \
                                    "TIMERX8_STAT_OFFSET");

        }

    }

}
