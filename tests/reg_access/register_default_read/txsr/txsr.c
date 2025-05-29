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
    TRX_SYS0_TXSR0_BASE, TRX_SYS0_TXSR1_BASE, TRX_SYS1_TXSR0_BASE, TRX_SYS1_TXSR1_BASE, TRX_SYS2_TXSR0_BASE,
    TRX_SYS2_TXSR1_BASE, TRX_SYS3_TXSR0_BASE, TRX_SYS3_TXSR1_BASE, TRX_SYS4_TXSR0_BASE, TRX_SYS4_TXSR1_BASE,
    TRX_SYS5_TXSR0_BASE, TRX_SYS5_TXSR1_BASE, TRX_SYS6_TXSR0_BASE, TRX_SYS6_TXSR1_BASE, TRX_SYS7_TXSR0_BASE,
    TRX_SYS7_TXSR1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TXSR_SCRATCH_OFFSET, \
                                    TXSR_SCRATCH_DEFAULT, \
                                    TXSR_SCRATCH_RD_MASK, "TXSR_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_TRIG_TSHOLD_OFFSET, \
                                    TXSR_SLEW_TRIG_TSHOLD_DEFAULT, \
                                    TXSR_SLEW_TRIG_TSHOLD_RD_MASK, "TXSR_SLEW_TRIG_TSHOLD_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_ALARM_CNTR_OFFSET, \
                                    TXSR_SLEW_ALARM_CNTR_DEFAULT, \
                                    TXSR_SLEW_ALARM_CNTR_RD_MASK, "TXSR_SLEW_ALARM_CNTR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_ALARM_MASK_OFFSET, \
                                    TXSR_SLEW_ALARM_MASK_DEFAULT, \
                                    TXSR_SLEW_ALARM_MASK_RD_MASK, "TXSR_SLEW_ALARM_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_TIMER_CNT_OFFSET, \
                                    TXSR_SLEW_TIMER_CNT_DEFAULT, \
                                    TXSR_SLEW_TIMER_CNT_RD_MASK, "TXSR_SLEW_TIMER_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_PRE_NORMAL_TIMER_CNT_OFFSET, \
                                    TXSR_PRE_NORMAL_TIMER_CNT_DEFAULT, \
                                    TXSR_PRE_NORMAL_TIMER_CNT_RD_MASK, "TXSR_PRE_NORMAL_TIMER_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_TMR_CFG_OFFSET, \
                                    TXSR_TMR_CFG_DEFAULT, \
                                    TXSR_TMR_CFG_RD_MASK, "TXSR_TMR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_TMR_ERR_OFFSET, \
                                    TXSR_TMR_ERR_DEFAULT, \
                                    TXSR_TMR_ERR_RD_MASK, "TXSR_TMR_ERR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_INT_STAT_OFFSET, \
                                    TXSR_INT_STAT_DEFAULT, \
                                    TXSR_INT_STAT_RD_MASK, "TXSR_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_INT_HIGH_EN_OFFSET, \
                                    TXSR_INT_HIGH_EN_DEFAULT, \
                                    TXSR_INT_HIGH_EN_RD_MASK, "TXSR_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_INT_LOW_EN_OFFSET, \
                                    TXSR_INT_LOW_EN_DEFAULT, \
                                    TXSR_INT_LOW_EN_RD_MASK, "TXSR_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_INT_CLR_OFFSET, \
                                    TXSR_INT_CLR_DEFAULT, \
                                    TXSR_INT_CLR_RD_MASK, "TXSR_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_INT_FORCE_OFFSET, \
                                    TXSR_INT_FORCE_DEFAULT, \
                                    TXSR_INT_FORCE_RD_MASK, "TXSR_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_ALARM_FORCE_OFFSET, \
                                    TXSR_SLEW_ALARM_FORCE_DEFAULT, \
                                    TXSR_SLEW_ALARM_FORCE_RD_MASK, "TXSR_SLEW_ALARM_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_SLEW_ALARM_STAT_OFFSET, \
                                    TXSR_SLEW_ALARM_STAT_DEFAULT, \
                                    TXSR_SLEW_ALARM_STAT_RD_MASK, "TXSR_SLEW_ALARM_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXSR_APB_BRDG_STAT_OFFSET, \
                                    TXSR_APB_BRDG_STAT_DEFAULT, \
                                    TXSR_APB_BRDG_STAT_RD_MASK, "TXSR_APB_BRDG_STAT_OFFSET");

    }

}
