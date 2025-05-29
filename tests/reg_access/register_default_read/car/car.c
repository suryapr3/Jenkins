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
    VEXA_CAR_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
		 LOG_PRINT("i is %d", i);
         if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){

                continue;
         }
            else
            {
        read_reg_expect_18a(base_address[i]+CAR_CLK_DIS0_OFFSET, \
                                    CAR_CLK_DIS0_DEFAULT, \
                                    CAR_CLK_DIS0_RD_MASK, "CAR_CLK_DIS0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_CLK_DIS1_OFFSET, \
                                    CAR_CLK_DIS1_DEFAULT, \
                                    CAR_CLK_DIS1_RD_MASK, "CAR_CLK_DIS1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_SOFT_RST0_OFFSET, \
                                    CAR_SOFT_RST0_DEFAULT, \
                                    CAR_SOFT_RST0_RD_MASK, "CAR_SOFT_RST0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_SOFT_RST1_OFFSET, \
                                    CAR_SOFT_RST1_DEFAULT, \
                                    CAR_SOFT_RST1_RD_MASK, "CAR_SOFT_RST1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HALT0_OFFSET, \
                                    CAR_HALT0_DEFAULT, \
                                    CAR_HALT0_RD_MASK, "CAR_HALT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HALT1_OFFSET, \
                                    CAR_HALT1_DEFAULT, \
                                    CAR_HALT1_RD_MASK, "CAR_HALT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_PD0_OFFSET, \
                                    CAR_PD0_DEFAULT, \
                                    CAR_PD0_RD_MASK, "CAR_PD0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_PD1_OFFSET, \
                                    CAR_PD1_DEFAULT, \
                                    CAR_PD1_RD_MASK, "CAR_PD1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_ROW_DIS_OFFSET, \
                                    CAR_ROW_DIS_DEFAULT, \
                                    CAR_ROW_DIS_RD_MASK, "CAR_ROW_DIS_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT0_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT1_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT2_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT3_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT4_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT5_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT5_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT6_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT6_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT7_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT7_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT8_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT8_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_HIGH_INT_STAT9_OFFSET, \
                                    CAR_HIGH_INT_STAT_DEFAULT, \
                                    CAR_HIGH_INT_STAT_RD_MASK, "CAR_HIGH_INT_STAT9_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+CAR_VEX_RST_RELEASE0_OFFSET, \
                                    CAR_VEX_RST_RELEASE0_DEFAULT, \
                                    CAR_VEX_RST_RELEASE0_RD_MASK, "CAR_VEX_RST_RELEASE0_OFFSET");

//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+CAR_VEX_RST_RELEASE1_OFFSET, \
                                    CAR_VEX_RST_RELEASE1_DEFAULT, \
                                    CAR_VEX_RST_RELEASE1_RD_MASK, "CAR_VEX_RST_RELEASE1_OFFSET");

//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+CAR_NOC_RST_RELEASE_OFFSET, \
                                    CAR_NOC_RST_RELEASE_DEFAULT, \
                                    CAR_NOC_RST_RELEASE_RD_MASK, "CAR_NOC_RST_RELEASE_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_NOC_CLK_GATE_OFFSET, \
                                    CAR_NOC_CLK_GATE_DEFAULT, \
                                    CAR_NOC_CLK_GATE_RD_MASK, "CAR_NOC_CLK_GATE_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_NOC_SOFT_RST_OFFSET, \
                                    CAR_NOC_SOFT_RST_DEFAULT, \
                                    CAR_NOC_SOFT_RST_RD_MASK, "CAR_NOC_SOFT_RST_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TIMER_START0_OFFSET, \
                                    CAR_TIMER_START0_DEFAULT, \
                                    CAR_TIMER_START0_RD_MASK, "CAR_TIMER_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TIMER_START1_OFFSET, \
                                    CAR_TIMER_START1_DEFAULT, \
                                    CAR_TIMER_START1_RD_MASK, "CAR_TIMER_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_SEL0_OFFSET, \
                                    CAR_VEX_WDT_SEL0_DEFAULT, \
                                    CAR_VEX_WDT_SEL0_RD_MASK, "CAR_VEX_WDT_SEL0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_SEL1_OFFSET, \
                                    CAR_VEX_WDT_SEL1_DEFAULT, \
                                    CAR_VEX_WDT_SEL1_RD_MASK, "CAR_VEX_WDT_SEL1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_INT_SEL_OFFSET, \
                                    CAR_VEX_INT_SEL_DEFAULT, \
                                    CAR_VEX_INT_SEL_RD_MASK, "CAR_VEX_INT_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_STAT0_OFFSET, \
                                    CAR_VEX_HIGH_INT_STAT0_DEFAULT, \
                                    CAR_VEX_HIGH_INT_STAT0_RD_MASK, "CAR_VEX_HIGH_INT_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_EN0_OFFSET, \
                                    CAR_VEX_HIGH_INT_EN0_DEFAULT, \
                                    CAR_VEX_HIGH_INT_EN0_RD_MASK, "CAR_VEX_HIGH_INT_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_CLR0_OFFSET, \
                                    CAR_VEX_HIGH_INT_CLR0_DEFAULT, \
                                    CAR_VEX_HIGH_INT_CLR0_RD_MASK, "CAR_VEX_HIGH_INT_CLR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_FORCE0_OFFSET, \
                                    CAR_VEX_HIGH_INT_FORCE0_DEFAULT, \
                                    CAR_VEX_HIGH_INT_FORCE0_RD_MASK, "CAR_VEX_HIGH_INT_FORCE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT0_DEFAULT, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT0_RD_MASK, "CAR_VEX_HIGH_INT_MASKED_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_STAT1_OFFSET, \
                                    CAR_VEX_HIGH_INT_STAT1_DEFAULT, \
                                    CAR_VEX_HIGH_INT_STAT1_RD_MASK, "CAR_VEX_HIGH_INT_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_EN1_OFFSET, \
                                    CAR_VEX_HIGH_INT_EN1_DEFAULT, \
                                    CAR_VEX_HIGH_INT_EN1_RD_MASK, "CAR_VEX_HIGH_INT_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_CLR1_OFFSET, \
                                    CAR_VEX_HIGH_INT_CLR1_DEFAULT, \
                                    CAR_VEX_HIGH_INT_CLR1_RD_MASK, "CAR_VEX_HIGH_INT_CLR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_FORCE1_OFFSET, \
                                    CAR_VEX_HIGH_INT_FORCE1_DEFAULT, \
                                    CAR_VEX_HIGH_INT_FORCE1_RD_MASK, "CAR_VEX_HIGH_INT_FORCE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_HIGH_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT1_DEFAULT, \
                                    CAR_VEX_HIGH_INT_MASKED_STAT1_RD_MASK, "CAR_VEX_HIGH_INT_MASKED_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_STAT0_OFFSET, \
                                    CAR_VEX_WDT_INT_STAT0_DEFAULT, \
                                    CAR_VEX_WDT_INT_STAT0_RD_MASK, "CAR_VEX_WDT_INT_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_EN0_OFFSET, \
                                    CAR_VEX_WDT_INT_EN0_DEFAULT, \
                                    CAR_VEX_WDT_INT_EN0_RD_MASK, "CAR_VEX_WDT_INT_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_CLR0_OFFSET, \
                                    CAR_VEX_WDT_INT_CLR0_DEFAULT, \
                                    CAR_VEX_WDT_INT_CLR0_RD_MASK, "CAR_VEX_WDT_INT_CLR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_FORCE0_OFFSET, \
                                    CAR_VEX_WDT_INT_FORCE0_DEFAULT, \
                                    CAR_VEX_WDT_INT_FORCE0_RD_MASK, "CAR_VEX_WDT_INT_FORCE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_WDT_INT_MASKED_STAT0_DEFAULT, \
                                    CAR_VEX_WDT_INT_MASKED_STAT0_RD_MASK, "CAR_VEX_WDT_INT_MASKED_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_STAT1_OFFSET, \
                                    CAR_VEX_WDT_INT_STAT1_DEFAULT, \
                                    CAR_VEX_WDT_INT_STAT1_RD_MASK, "CAR_VEX_WDT_INT_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_EN1_OFFSET, \
                                    CAR_VEX_WDT_INT_EN1_DEFAULT, \
                                    CAR_VEX_WDT_INT_EN1_RD_MASK, "CAR_VEX_WDT_INT_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_CLR1_OFFSET, \
                                    CAR_VEX_WDT_INT_CLR1_DEFAULT, \
                                    CAR_VEX_WDT_INT_CLR1_RD_MASK, "CAR_VEX_WDT_INT_CLR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_FORCE1_OFFSET, \
                                    CAR_VEX_WDT_INT_FORCE1_DEFAULT, \
                                    CAR_VEX_WDT_INT_FORCE1_RD_MASK, "CAR_VEX_WDT_INT_FORCE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_WDT_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_WDT_INT_MASKED_STAT1_DEFAULT, \
                                    CAR_VEX_WDT_INT_MASKED_STAT1_RD_MASK, "CAR_VEX_WDT_INT_MASKED_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_STAT0_OFFSET, \
                                    CAR_VEX_LOW_INT_STAT0_DEFAULT, \
                                    CAR_VEX_LOW_INT_STAT0_RD_MASK, "CAR_VEX_LOW_INT_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_EN0_OFFSET, \
                                    CAR_VEX_LOW_INT_EN0_DEFAULT, \
                                    CAR_VEX_LOW_INT_EN0_RD_MASK, "CAR_VEX_LOW_INT_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_CLR0_OFFSET, \
                                    CAR_VEX_LOW_INT_CLR0_DEFAULT, \
                                    CAR_VEX_LOW_INT_CLR0_RD_MASK, "CAR_VEX_LOW_INT_CLR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_FORCE0_OFFSET, \
                                    CAR_VEX_LOW_INT_FORCE0_DEFAULT, \
                                    CAR_VEX_LOW_INT_FORCE0_RD_MASK, "CAR_VEX_LOW_INT_FORCE0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_MASKED_STAT0_OFFSET, \
                                    CAR_VEX_LOW_INT_MASKED_STAT0_DEFAULT, \
                                    CAR_VEX_LOW_INT_MASKED_STAT0_RD_MASK, "CAR_VEX_LOW_INT_MASKED_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_STAT1_OFFSET, \
                                    CAR_VEX_LOW_INT_STAT1_DEFAULT, \
                                    CAR_VEX_LOW_INT_STAT1_RD_MASK, "CAR_VEX_LOW_INT_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_EN1_OFFSET, \
                                    CAR_VEX_LOW_INT_EN1_DEFAULT, \
                                    CAR_VEX_LOW_INT_EN1_RD_MASK, "CAR_VEX_LOW_INT_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_CLR1_OFFSET, \
                                    CAR_VEX_LOW_INT_CLR1_DEFAULT, \
                                    CAR_VEX_LOW_INT_CLR1_RD_MASK, "CAR_VEX_LOW_INT_CLR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_FORCE1_OFFSET, \
                                    CAR_VEX_LOW_INT_FORCE1_DEFAULT, \
                                    CAR_VEX_LOW_INT_FORCE1_RD_MASK, "CAR_VEX_LOW_INT_FORCE1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_VEX_LOW_INT_MASKED_STAT1_OFFSET, \
                                    CAR_VEX_LOW_INT_MASKED_STAT1_DEFAULT, \
                                    CAR_VEX_LOW_INT_MASKED_STAT1_RD_MASK, "CAR_VEX_LOW_INT_MASKED_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_EN0_OFFSET, \
                                    CAR_TX_ALARM_EN0_DEFAULT, \
                                    CAR_TX_ALARM_EN0_RD_MASK, "CAR_TX_ALARM_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_EN1_OFFSET, \
                                    CAR_TX_ALARM_EN1_DEFAULT, \
                                    CAR_TX_ALARM_EN1_RD_MASK, "CAR_TX_ALARM_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_MAP0_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, \
                                    CAR_TX_ALARM_RD_MASK, "CAR_TX_ALARM_MAP0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_MAP1_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, \
                                    CAR_TX_ALARM_RD_MASK, "CAR_TX_ALARM_MAP1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_MAP2_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, \
                                    CAR_TX_ALARM_RD_MASK, "CAR_TX_ALARM_MAP2_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_MAP3_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, \
                                    CAR_TX_ALARM_RD_MASK, "CAR_TX_ALARM_MAP3_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_TX_ALARM_MAP4_OFFSET, \
                                    CAR_TX_ALARM_DEFAULT, \
                                    CAR_TX_ALARM_RD_MASK, "CAR_TX_ALARM_MAP4_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_GPIO_TX_ALM_EN0_OFFSET, \
                                    CAR_GPIO_TX_ALM_EN0_DEFAULT, \
                                    CAR_GPIO_TX_ALM_EN0_RD_MASK, "CAR_GPIO_TX_ALM_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_GPIO_TX_ALM_EN1_OFFSET, \
                                    CAR_GPIO_TX_ALM_EN1_DEFAULT, \
                                    CAR_GPIO_TX_ALM_EN1_RD_MASK, "CAR_GPIO_TX_ALM_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_GPIO_STAT0_OFFSET, \
                                    CAR_GPIO_STAT0_DEFAULT, \
                                    CAR_GPIO_STAT0_RD_MASK, "CAR_GPIO_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+CAR_GPIO_STAT1_OFFSET, \
                                    CAR_GPIO_STAT1_DEFAULT, \
                                    CAR_GPIO_STAT1_RD_MASK, "CAR_GPIO_STAT1_OFFSET");

    }

}
}
