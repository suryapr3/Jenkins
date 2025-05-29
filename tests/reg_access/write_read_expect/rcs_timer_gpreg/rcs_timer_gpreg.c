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
    RCS_TIMER_GPREG_BASE
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
            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_MUX_15_8_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_15_8_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_15_8_RD_MASK, RCS_TIMER_GPREG_SSP_CS_MUX_15_8_WR_MASK, \
                                    "RCS_TIMER_GPREG_SSP_CS_MUX_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_RD_MASK, RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_WR_MASK, \
                                    "RCS_TIMER_GPREG_SSP_CS_MUX_7_0_R_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_RD_MASK, RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_WR_MASK, \
                                    "RCS_TIMER_GPREG_SSP_CS_GPIO_MUX_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_OFFSET, \
                                    RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_RD_MASK, RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMER_GPREG_SSP_DMA_TRIG_GPIO_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_OFFSET, \
                                    RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_RD_MASK, RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_WR_MASK, \
                                    "RCS_TIMER_GPREG_CORE_DMA_TRIG_GPIO_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_LCNT_INC_OFFSET, \
                                    RCS_TIMER_GPREG_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_LCNT_INC_RD_MASK, RCS_TIMER_GPREG_LCNT_INC_WR_MASK, \
                                    "RCS_TIMER_GPREG_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_TEN_MS_CNT_OFFSET, \
                                    RCS_TIMER_GPREG_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_TEN_MS_CNT_RD_MASK, RCS_TIMER_GPREG_TEN_MS_CNT_WR_MASK, \
                                    "RCS_TIMER_GPREG_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_INC_PRE_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_INC_PRE_REG0_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_INC_PRE_REG0_RD_MASK, RCS_TIMER_GPREG_INC_PRE_REG0_WR_MASK, \
                                    "RCS_TIMER_GPREG_INC_PRE_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_INC_PRE_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_INC_PRE_REG1_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_INC_PRE_REG1_RD_MASK, RCS_TIMER_GPREG_INC_PRE_REG1_WR_MASK, \
                                    "RCS_TIMER_GPREG_INC_PRE_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_CNT_ADJ_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG0_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG0_RD_MASK, RCS_TIMER_GPREG_CNT_ADJ_REG0_WR_MASK, \
                                    "RCS_TIMER_GPREG_CNT_ADJ_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_CNT_ADJ_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG1_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_CNT_ADJ_REG1_RD_MASK, RCS_TIMER_GPREG_CNT_ADJ_REG1_WR_MASK, \
                                    "RCS_TIMER_GPREG_CNT_ADJ_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_CFG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG1_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG1_RD_MASK, RCS_TIMER_GPREG_BFN_CAPT_CFG1_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CAPT_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_CFG2_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG2_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CAPT_CFG2_RD_MASK, RCS_TIMER_GPREG_BFN_CAPT_CFG2_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CAPT_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_RD_MASK, RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CAPT_INT_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_RD_MASK, RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_TIME_CAPT_STAT_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_ICTRL_OFFSET, \
                                    RCS_TIMER_GPREG_ICTRL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_ICTRL_RD_MASK, RCS_TIMER_GPREG_ICTRL_WR_MASK, \
                                    "RCS_TIMER_GPREG_ICTRL_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_OFFSET, \
                                    RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_RD_MASK, RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_WR_MASK, \
                                    "RCS_TIMER_GPREG_OPPS_VAL_TIMESYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_LO_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_LO_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_LO_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_LO_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_LO_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_HI_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_HI_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_HI_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_HI_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_HI_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_RD_MASK, RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_LIVE_CNT_LO_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_RD_MASK, RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_LIVE_CNT_HI_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_VAL1_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_VAL1_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_VAL2_REG0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_OFFSET, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_RD_MASK, RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_WR_MASK, \
                                    "RCS_TIMER_GPREG_BFN_CNT_VAL2_REG1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL2_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_TX_EN_BFN_CAP_VAL3_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL2_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_EN_BFN_CAP_VAL3_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL0_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL0_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL1_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL1_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL2_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL2_OFFSET");

            write_read_expect_18a(base_address[i]+RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL3_OFFSET, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_DEFAULT, write_data, expected_data, \
                                    RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_RD_MASK, RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL_WR_MASK, \
                                    "RCS_TIMER_GPREG_RX_FB_BFN_CAP_VAL3_OFFSET");

        }

    }

}
