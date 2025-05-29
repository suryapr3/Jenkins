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
    RCS_TIMER_GPREG_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_MUX_15_8_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_15_8_DEFAULT, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_15_8_RD_MASK, "RCS_TIMER_GPREG_SSP_CS_MUX_15_8_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_DEFAULT, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_RD_MASK, "RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_DEFAULT, \
                                    RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_RD_MASK, "RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_DEFAULT, \
                                    RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_RD_MASK, "RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_OFFSET, \
                                    RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_DEFAULT, \
                                    RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_RD_MASK, "RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_LCNT_INC_OFFSET, \
                                    RCS_TIMER_GPREG_LCNT_INC_DEFAULT, \
                                    RCS_TIMER_GPREG_LCNT_INC_RD_MASK, "RCS_TIMER_GPREG_LCNT_INC_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_TEN_MS_CNT_OFFSET, \
                                    RCS_TIMER_GPREG_TEN_MS_CNT_DEFAULT, \
                                    RCS_TIMER_GPREG_TEN_MS_CNT_RD_MASK, "RCS_TIMER_GPREG_TEN_MS_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_INC_PRE_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_INC_PRE_REG0_DEFAULT, \
                                    RCS_TIMER_GPREG_INC_PRE_REG0_RD_MASK, "RCS_TIMER_GPREG_INC_PRE_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_INC_PRE_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_INC_PRE_REG1_DEFAULT, \
                                    RCS_TIMER_GPREG_INC_PRE_REG1_RD_MASK, "RCS_TIMER_GPREG_INC_PRE_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_CNT_ADJ_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG0_DEFAULT, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG0_RD_MASK, "RCS_TIMER_GPREG_CNT_ADJ_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_CNT_ADJ_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG1_DEFAULT, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG1_RD_MASK, "RCS_TIMER_GPREG_CNT_ADJ_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_CFG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG1_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG1_RD_MASK, "RCS_TIMER_GPREG_BFN_CAPT_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_CFG2_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG2_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG2_RD_MASK, "RCS_TIMER_GPREG_BFN_CAPT_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_RD_MASK, "RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_RD_MASK, "RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_ICTRL_OFFSET, \
                                    RCS_TIMER_GPREG_ICTRL_DEFAULT, \
                                    RCS_TIMER_GPREG_ICTRL_RD_MASK, "RCS_TIMER_GPREG_ICTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_OFFSET, \
                                    RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_DEFAULT, \
                                    RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_RD_MASK, "RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_LO_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_LO_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_LO_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_LO_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_HI_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_HI_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_HI_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_HI_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_RD_MASK, "RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_RD_MASK, "RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_DEFAULT, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_RD_MASK, "RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL3_OFFSET");

    }

}
