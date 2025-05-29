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
    TRX_SYS0_TXCPM0_BASE, TRX_SYS0_TXCPM1_BASE, TRX_SYS1_TXCPM0_BASE, TRX_SYS1_TXCPM1_BASE, TRX_SYS2_TXCPM0_BASE,
    TRX_SYS2_TXCPM1_BASE, TRX_SYS3_TXCPM0_BASE, TRX_SYS3_TXCPM1_BASE, TRX_SYS4_TXCPM0_BASE, TRX_SYS4_TXCPM1_BASE,
    TRX_SYS5_TXCPM0_BASE, TRX_SYS5_TXCPM1_BASE, TRX_SYS6_TXCPM0_BASE, TRX_SYS6_TXCPM1_BASE, TRX_SYS7_TXCPM0_BASE,
    TRX_SYS7_TXCPM1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TXCPM_SCRATCH_OFFSET, \
                                    TXCPM_SCRATCH_DEFAULT, \
                                    TXCPM_SCRATCH_RD_MASK, "TXCPM_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_LNR_ATTACK_TSHOLD_OFFSET, \
                                    TXCPM_LNR_ATTACK_TSHOLD_DEFAULT, \
                                    TXCPM_LNR_ATTACK_TSHOLD_RD_MASK, "TXCPM_LNR_ATTACK_TSHOLD_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_LNR_RELEASE_TSHOLD_OFFSET, \
                                    TXCPM_LNR_RELEASE_TSHOLD_DEFAULT, \
                                    TXCPM_LNR_RELEASE_TSHOLD_RD_MASK, "TXCPM_LNR_RELEASE_TSHOLD_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_DLINK_MHI_OFFSET, \
                                    TXCPM_DLINK_MHI_DEFAULT, \
                                    TXCPM_DLINK_MHI_RD_MASK, "TXCPM_DLINK_MHI_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_SEL_WND_SIZE_OFFSET, \
                                    TXCPM_SEL_WND_SIZE_DEFAULT, \
                                    TXCPM_SEL_WND_SIZE_RD_MASK, "TXCPM_SEL_WND_SIZE_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_SEL_MEAS_OUTPUT_OFFSET, \
                                    TXCPM_SEL_MEAS_OUTPUT_DEFAULT, \
                                    TXCPM_SEL_MEAS_OUTPUT_RD_MASK, "TXCPM_SEL_MEAS_OUTPUT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_ERR_TRIG_TIMER_CNT_OFFSET, \
                                    TXCPM_ERR_TRIG_TIMER_CNT_DEFAULT, \
                                    TXCPM_ERR_TRIG_TIMER_CNT_RD_MASK, "TXCPM_ERR_TRIG_TIMER_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_PRE_NORMAL_TIMER_CNT_OFFSET, \
                                    TXCPM_PRE_NORMAL_TIMER_CNT_DEFAULT, \
                                    TXCPM_PRE_NORMAL_TIMER_CNT_RD_MASK, "TXCPM_PRE_NORMAL_TIMER_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_ALARM_MASK_OFFSET, \
                                    TXCPM_ALARM_MASK_DEFAULT, \
                                    TXCPM_ALARM_MASK_RD_MASK, "TXCPM_ALARM_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_ALARM_FORCE_OFFSET, \
                                    TXCPM_ALARM_FORCE_DEFAULT, \
                                    TXCPM_ALARM_FORCE_RD_MASK, "TXCPM_ALARM_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_EN_MEAS_OFFSET, \
                                    TXCPM_EN_MEAS_DEFAULT, \
                                    TXCPM_EN_MEAS_RD_MASK, "TXCPM_EN_MEAS_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_PIQ_MEAS_TRIP_VAL_OFFSET, \
                                    TXCPM_PIQ_MEAS_TRIP_VAL_DEFAULT, \
                                    TXCPM_PIQ_MEAS_TRIP_VAL_RD_MASK, "TXCPM_PIQ_MEAS_TRIP_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_DBG_ALARM_STAT_OFFSET, \
                                    TXCPM_DBG_ALARM_STAT_DEFAULT, \
                                    TXCPM_DBG_ALARM_STAT_RD_MASK, "TXCPM_DBG_ALARM_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_DBG_TOTAL_WND_PWR_OFFSET, \
                                    TXCPM_DBG_TOTAL_WND_PWR_DEFAULT, \
                                    TXCPM_DBG_TOTAL_WND_PWR_RD_MASK, "TXCPM_DBG_TOTAL_WND_PWR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_DBG_PEAK_WND_PWR_OFFSET, \
                                    TXCPM_DBG_PEAK_WND_PWR_DEFAULT, \
                                    TXCPM_DBG_PEAK_WND_PWR_RD_MASK, "TXCPM_DBG_PEAK_WND_PWR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_ALARM_CNTER_OFFSET, \
                                    TXCPM_ALARM_CNTER_DEFAULT, \
                                    TXCPM_ALARM_CNTER_RD_MASK, "TXCPM_ALARM_CNTER_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_TXE_DELAY_OFFSET, \
                                    TXCPM_TXE_DELAY_DEFAULT, \
                                    TXCPM_TXE_DELAY_RD_MASK, "TXCPM_TXE_DELAY_OFFSET");

        read_reg_expect_18a(base_address[i]+TXCPM_APB_BRDG_STAT_OFFSET, \
                                    TXCPM_APB_BRDG_STAT_DEFAULT, \
                                    TXCPM_APB_BRDG_STAT_RD_MASK, "TXCPM_APB_BRDG_STAT_OFFSET");

    }

}
