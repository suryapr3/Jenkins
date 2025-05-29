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
    VEXA_CAR_BASE
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
		  LOG_PRINT("i is %d", i);
        if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
            continue;
        }
        else
        {
            write_read_expect_18a(base_address[i]+CAR_CLK_DIS0_OFFSET, \
                                    CAR_CLK_DIS0_DEFAULT, write_data, expected_data, \
                                    CAR_CLK_DIS0_RD_MASK, CAR_CLK_DIS0_WR_MASK, \
                                    "CAR_CLK_DIS0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_CLK_DIS1_OFFSET, \
                                    CAR_CLK_DIS1_DEFAULT, write_data, expected_data, \
                                    CAR_CLK_DIS1_RD_MASK, CAR_CLK_DIS1_WR_MASK, \
                                    "CAR_CLK_DIS1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_SOFT_RST0_OFFSET, \
                                    CAR_SOFT_RST0_DEFAULT, write_data, expected_data, \
                                    CAR_SOFT_RST0_RD_MASK, CAR_SOFT_RST0_WR_MASK, \
                                    "CAR_SOFT_RST0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_SOFT_RST1_OFFSET, \
                                    CAR_SOFT_RST1_DEFAULT, write_data, expected_data, \
                                    CAR_SOFT_RST1_RD_MASK, CAR_SOFT_RST1_WR_MASK, \
                                    "CAR_SOFT_RST1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HALT0_OFFSET, \
                                    CAR_HALT0_DEFAULT, write_data, expected_data, \
                                    CAR_HALT0_RD_MASK, CAR_HALT0_WR_MASK, \
                                    "CAR_HALT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HALT1_OFFSET, \
                                    CAR_HALT1_DEFAULT, write_data, expected_data, \
                                    CAR_HALT1_RD_MASK, CAR_HALT1_WR_MASK, \
                                    "CAR_HALT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_PD0_OFFSET, \
                                    CAR_PD0_DEFAULT, write_data, expected_data, \
                                    CAR_PD0_RD_MASK, CAR_PD0_WR_MASK, \
                                    "CAR_PD0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_PD1_OFFSET, \
                                    CAR_PD1_DEFAULT, write_data, expected_data, \
                                    CAR_PD1_RD_MASK, CAR_PD1_WR_MASK, \
                                    "CAR_PD1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_ROW_DIS_OFFSET, \
                                    CAR_ROW_DIS_DEFAULT, write_data, expected_data, \
                                    CAR_ROW_DIS_RD_MASK, CAR_ROW_DIS_WR_MASK, \
                                    "CAR_ROW_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT0_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT1_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT2_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT3_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT4_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT5_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT6_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT7_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT8_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT8_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_HIGH_INT_STAT9_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, write_data, expected_data, \
                                    CAR_HIGH_INT_STAT_RD_MASK, CAR_HIGH_INT_STAT_WR_MASK, \
                                    "CAR_HIGH_INT_STAT9_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_RST_RELEASE0_OFFSET, \
                                    CAR_VEX_RST_RELEASE0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_RST_RELEASE0_RD_MASK, CAR_VEX_RST_RELEASE0_WR_MASK, \
                                    "CAR_VEX_RST_RELEASE0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_RST_RELEASE1_OFFSET, \
                                    CAR_VEX_RST_RELEASE1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_RST_RELEASE1_RD_MASK, CAR_VEX_RST_RELEASE1_WR_MASK, \
                                    "CAR_VEX_RST_RELEASE1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_NOC_RST_RELEASE_OFFSET, \
                                    CAR_NOC_RST_RELEASE_DEFAULT, write_data, expected_data, \
                                    CAR_NOC_RST_RELEASE_RD_MASK, CAR_NOC_RST_RELEASE_WR_MASK, \
                                    "CAR_NOC_RST_RELEASE_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_NOC_CLK_GATE_OFFSET, \
                                    CAR_NOC_CLK_GATE_DEFAULT, write_data, expected_data, \
                                    CAR_NOC_CLK_GATE_RD_MASK, CAR_NOC_CLK_GATE_WR_MASK, \
                                    "CAR_NOC_CLK_GATE_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_NOC_SOFT_RST_OFFSET, \
                                    CAR_NOC_SOFT_RST_DEFAULT, write_data, expected_data, \
                                    CAR_NOC_SOFT_RST_RD_MASK, CAR_NOC_SOFT_RST_WR_MASK, \
                                    "CAR_NOC_SOFT_RST_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TIMER_START0_OFFSET, \
                                    CAR_TIMER_START0_DEFAULT, write_data, expected_data, \
                                    CAR_TIMER_START0_RD_MASK, CAR_TIMER_START0_WR_MASK, \
                                    "CAR_TIMER_START0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TIMER_START1_OFFSET, \
                                    CAR_TIMER_START1_DEFAULT, write_data, expected_data, \
                                    CAR_TIMER_START1_RD_MASK, CAR_TIMER_START1_WR_MASK, \
                                    "CAR_TIMER_START1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_SEL0_OFFSET, \
                                    CAR_VEX_WDT_SEL0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_SEL0_RD_MASK, CAR_VEX_WDT_SEL0_WR_MASK, \
                                    "CAR_VEX_WDT_SEL0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_SEL1_OFFSET, \
                                    CAR_VEX_WDT_SEL1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_SEL1_RD_MASK, CAR_VEX_WDT_SEL1_WR_MASK, \
                                    "CAR_VEX_WDT_SEL1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_INT_SEL_OFFSET, \
                                    CAR_VEX_INT_SEL_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_INT_SEL_RD_MASK, CAR_VEX_INT_SEL_WR_MASK, \
                                    "CAR_VEX_INT_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_STAT0_OFFSET, \
                                    CAR_VEX_HIGH_INT_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_STAT0_RD_MASK, CAR_VEX_HIGH_INT_STAT0_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_EN0_OFFSET, \
                                    CAR_VEX_HIGH_INT_EN0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_EN0_RD_MASK, CAR_VEX_HIGH_INT_EN0_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_CLR0_OFFSET, \
                                    CAR_VEX_HIGH_INT_CLR0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_CLR0_RD_MASK, CAR_VEX_HIGH_INT_CLR0_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_CLR0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_FORCE0_OFFSET, \
                                    CAR_VEX_HIGH_INT_FORCE0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_FORCE0_RD_MASK, CAR_VEX_HIGH_INT_FORCE0_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_FORCE0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT0_RD_MASK, CAR_VEX_HIGH_INT_MASKED_STAT0_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_MASKED_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_STAT1_OFFSET, \
                                    CAR_VEX_HIGH_INT_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_STAT1_RD_MASK, CAR_VEX_HIGH_INT_STAT1_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_EN1_OFFSET, \
                                    CAR_VEX_HIGH_INT_EN1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_EN1_RD_MASK, CAR_VEX_HIGH_INT_EN1_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_CLR1_OFFSET, \
                                    CAR_VEX_HIGH_INT_CLR1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_CLR1_RD_MASK, CAR_VEX_HIGH_INT_CLR1_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_CLR1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_FORCE1_OFFSET, \
                                    CAR_VEX_HIGH_INT_FORCE1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_FORCE1_RD_MASK, CAR_VEX_HIGH_INT_FORCE1_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_FORCE1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT1_RD_MASK, CAR_VEX_HIGH_INT_MASKED_STAT1_WR_MASK, \
                                    "CAR_VEX_HIGH_INT_MASKED_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_STAT0_OFFSET, \
                                    CAR_VEX_WDT_INT_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_STAT0_RD_MASK, CAR_VEX_WDT_INT_STAT0_WR_MASK, \
                                    "CAR_VEX_WDT_INT_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_EN0_OFFSET, \
                                    CAR_VEX_WDT_INT_EN0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_EN0_RD_MASK, CAR_VEX_WDT_INT_EN0_WR_MASK, \
                                    "CAR_VEX_WDT_INT_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_CLR0_OFFSET, \
                                    CAR_VEX_WDT_INT_CLR0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_CLR0_RD_MASK, CAR_VEX_WDT_INT_CLR0_WR_MASK, \
                                    "CAR_VEX_WDT_INT_CLR0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_FORCE0_OFFSET, \
                                    CAR_VEX_WDT_INT_FORCE0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_FORCE0_RD_MASK, CAR_VEX_WDT_INT_FORCE0_WR_MASK, \
                                    "CAR_VEX_WDT_INT_FORCE0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_WDT_INT_MASKED_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_MASKED_STAT0_RD_MASK, CAR_VEX_WDT_INT_MASKED_STAT0_WR_MASK, \
                                    "CAR_VEX_WDT_INT_MASKED_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_STAT1_OFFSET, \
                                    CAR_VEX_WDT_INT_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_STAT1_RD_MASK, CAR_VEX_WDT_INT_STAT1_WR_MASK, \
                                    "CAR_VEX_WDT_INT_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_EN1_OFFSET, \
                                    CAR_VEX_WDT_INT_EN1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_EN1_RD_MASK, CAR_VEX_WDT_INT_EN1_WR_MASK, \
                                    "CAR_VEX_WDT_INT_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_CLR1_OFFSET, \
                                    CAR_VEX_WDT_INT_CLR1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_CLR1_RD_MASK, CAR_VEX_WDT_INT_CLR1_WR_MASK, \
                                    "CAR_VEX_WDT_INT_CLR1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_FORCE1_OFFSET, \
                                    CAR_VEX_WDT_INT_FORCE1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_FORCE1_RD_MASK, CAR_VEX_WDT_INT_FORCE1_WR_MASK, \
                                    "CAR_VEX_WDT_INT_FORCE1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_WDT_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_WDT_INT_MASKED_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_WDT_INT_MASKED_STAT1_RD_MASK, CAR_VEX_WDT_INT_MASKED_STAT1_WR_MASK, \
                                    "CAR_VEX_WDT_INT_MASKED_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_STAT0_OFFSET, \
                                    CAR_VEX_LOW_INT_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_STAT0_RD_MASK, CAR_VEX_LOW_INT_STAT0_WR_MASK, \
                                    "CAR_VEX_LOW_INT_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_EN0_OFFSET, \
                                    CAR_VEX_LOW_INT_EN0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_EN0_RD_MASK, CAR_VEX_LOW_INT_EN0_WR_MASK, \
                                    "CAR_VEX_LOW_INT_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_CLR0_OFFSET, \
                                    CAR_VEX_LOW_INT_CLR0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_CLR0_RD_MASK, CAR_VEX_LOW_INT_CLR0_WR_MASK, \
                                    "CAR_VEX_LOW_INT_CLR0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_FORCE0_OFFSET, \
                                    CAR_VEX_LOW_INT_FORCE0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_FORCE0_RD_MASK, CAR_VEX_LOW_INT_FORCE0_WR_MASK, \
                                    "CAR_VEX_LOW_INT_FORCE0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_LOW_INT_MASKED_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_MASKED_STAT0_RD_MASK, CAR_VEX_LOW_INT_MASKED_STAT0_WR_MASK, \
                                    "CAR_VEX_LOW_INT_MASKED_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_STAT1_OFFSET, \
                                    CAR_VEX_LOW_INT_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_STAT1_RD_MASK, CAR_VEX_LOW_INT_STAT1_WR_MASK, \
                                    "CAR_VEX_LOW_INT_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_EN1_OFFSET, \
                                    CAR_VEX_LOW_INT_EN1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_EN1_RD_MASK, CAR_VEX_LOW_INT_EN1_WR_MASK, \
                                    "CAR_VEX_LOW_INT_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_CLR1_OFFSET, \
                                    CAR_VEX_LOW_INT_CLR1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_CLR1_RD_MASK, CAR_VEX_LOW_INT_CLR1_WR_MASK, \
                                    "CAR_VEX_LOW_INT_CLR1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_FORCE1_OFFSET, \
                                    CAR_VEX_LOW_INT_FORCE1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_FORCE1_RD_MASK, CAR_VEX_LOW_INT_FORCE1_WR_MASK, \
                                    "CAR_VEX_LOW_INT_FORCE1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_VEX_LOW_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_LOW_INT_MASKED_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_VEX_LOW_INT_MASKED_STAT1_RD_MASK, CAR_VEX_LOW_INT_MASKED_STAT1_WR_MASK, \
                                    "CAR_VEX_LOW_INT_MASKED_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_EN0_OFFSET, \
                                    CAR_TX_ALARM_EN0_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_EN0_RD_MASK, CAR_TX_ALARM_EN0_WR_MASK, \
                                    "CAR_TX_ALARM_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_EN1_OFFSET, \
                                    CAR_TX_ALARM_EN1_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_EN1_RD_MASK, CAR_TX_ALARM_EN1_WR_MASK, \
                                    "CAR_TX_ALARM_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_MAP0_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_RD_MASK, CAR_TX_ALARM_WR_MASK, \
                                    "CAR_TX_ALARM_MAP0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_MAP1_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_RD_MASK, CAR_TX_ALARM_WR_MASK, \
                                    "CAR_TX_ALARM_MAP1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_MAP2_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_RD_MASK, CAR_TX_ALARM_WR_MASK, \
                                    "CAR_TX_ALARM_MAP2_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_MAP3_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_RD_MASK, CAR_TX_ALARM_WR_MASK, \
                                    "CAR_TX_ALARM_MAP3_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_TX_ALARM_MAP4_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, write_data, expected_data, \
                                    CAR_TX_ALARM_RD_MASK, CAR_TX_ALARM_WR_MASK, \
                                    "CAR_TX_ALARM_MAP4_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_GPIO_TX_ALM_EN0_OFFSET, \
                                    CAR_GPIO_TX_ALM_EN0_DEFAULT, write_data, expected_data, \
                                    CAR_GPIO_TX_ALM_EN0_RD_MASK, CAR_GPIO_TX_ALM_EN0_WR_MASK, \
                                    "CAR_GPIO_TX_ALM_EN0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_GPIO_TX_ALM_EN1_OFFSET, \
                                    CAR_GPIO_TX_ALM_EN1_DEFAULT, write_data, expected_data, \
                                    CAR_GPIO_TX_ALM_EN1_RD_MASK, CAR_GPIO_TX_ALM_EN1_WR_MASK, \
                                    "CAR_GPIO_TX_ALM_EN1_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_GPIO_STAT0_OFFSET, \
                                    CAR_GPIO_STAT0_DEFAULT, write_data, expected_data, \
                                    CAR_GPIO_STAT0_RD_MASK, CAR_GPIO_STAT0_WR_MASK, \
                                    "CAR_GPIO_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+CAR_GPIO_STAT1_OFFSET, \
                                    CAR_GPIO_STAT1_DEFAULT, write_data, expected_data, \
                                    CAR_GPIO_STAT1_RD_MASK, CAR_GPIO_STAT1_WR_MASK, \
                                    "CAR_GPIO_STAT1_OFFSET");

        }

    }
}
}
