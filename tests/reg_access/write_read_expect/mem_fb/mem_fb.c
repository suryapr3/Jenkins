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
    MEM_FB0_CFG_BASE, MEM_FB1_CFG_BASE
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
            write_read_expect_18a(base_address[i]+MEM_FB_SCRATCH_OFFSET, \
                                    MEM_FB_SCRATCH_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SCRATCH_RD_MASK, MEM_FB_SCRATCH_WR_MASK, \
                                    "MEM_FB_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SOFT_RST_OFFSET, \
                                    MEM_FB_SOFT_RST_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SOFT_RST_RD_MASK, MEM_FB_SOFT_RST_WR_MASK, \
                                    "MEM_FB_SOFT_RST_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_EN_OFFSET, \
                                    MEM_FB_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_EN_RD_MASK, MEM_FB_EN_WR_MASK, \
                                    "MEM_FB_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_LL_CORRUPT_OFFSET, \
                                    MEM_FB_LL_CORRUPT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_LL_CORRUPT_RD_MASK, MEM_FB_LL_CORRUPT_WR_MASK, \
                                    "MEM_FB_LL_CORRUPT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_PWR_DOWN_CTRL_OFFSET, \
                                    MEM_FB_PWR_DOWN_CTRL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_PWR_DOWN_CTRL_RD_MASK, MEM_FB_PWR_DOWN_CTRL_WR_MASK, \
                                    "MEM_FB_PWR_DOWN_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET, \
                                    MEM_FB_PWR_DOWN_CTRL_CHAIN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_PWR_DOWN_CTRL_CHAIN_RD_MASK, MEM_FB_PWR_DOWN_CTRL_CHAIN_WR_MASK, \
                                    "MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_HOLD_REQ_OFFSET, \
                                    MEM_FB_DMAC_HOLD_REQ_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_HOLD_REQ_RD_MASK, MEM_FB_DMAC_HOLD_REQ_WR_MASK, \
                                    "MEM_FB_DMAC_HOLD_REQ_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_HOLD_ACK_OFFSET, \
                                    MEM_FB_DMAC_HOLD_ACK_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_HOLD_ACK_RD_MASK, MEM_FB_DMAC_HOLD_ACK_WR_MASK, \
                                    "MEM_FB_DMAC_HOLD_ACK_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_LA_DBG_SEL_OFFSET, \
                                    MEM_FB_LA_DBG_SEL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_LA_DBG_SEL_RD_MASK, MEM_FB_LA_DBG_SEL_WR_MASK, \
                                    "MEM_FB_LA_DBG_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_DBG_CHAN_SEL_OFFSET, \
                                    MEM_FB_DMAC_DBG_CHAN_SEL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_DBG_CHAN_SEL_RD_MASK, MEM_FB_DMAC_DBG_CHAN_SEL_WR_MASK, \
                                    "MEM_FB_DMAC_DBG_CHAN_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_DMA0_DBG_OFFSET, \
                                    MEM_FB_DMAC_DMA0_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_DMA0_DBG_RD_MASK, MEM_FB_DMAC_DMA0_DBG_WR_MASK, \
                                    "MEM_FB_DMAC_DMA0_DBG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_DMA1_DBG_OFFSET, \
                                    MEM_FB_DMAC_DMA1_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_DMA1_DBG_RD_MASK, MEM_FB_DMAC_DMA1_DBG_WR_MASK, \
                                    "MEM_FB_DMAC_DMA1_DBG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC0_CH_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC0_CH_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC0_CH_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC0_CH_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC0_CH_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC1_CH_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC1_CH_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC1_CH_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC1_CH_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC1_CH_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC0_DST_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC0_DST_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC0_DST_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC0_DST_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC0_DST_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC1_DST_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC1_DST_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC1_DST_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC1_DST_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC1_DST_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC0_SRC_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC0_SRC_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC0_SRC_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC0_SRC_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC0_SRC_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC1_SRC_TFR_DONE_CNT_OFFSET, \
                                    MEM_FB_DMAC1_SRC_TFR_DONE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC1_SRC_TFR_DONE_CNT_RD_MASK, MEM_FB_DMAC1_SRC_TFR_DONE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC1_SRC_TFR_DONE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_TDD_STALL_OFFSET, \
                                    MEM_FB_TDD_STALL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_TDD_STALL_RD_MASK, MEM_FB_TDD_STALL_WR_MASK, \
                                    "MEM_FB_TDD_STALL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC0_CH0_PAUSE_CNT_OFFSET, \
                                    MEM_FB_DMAC0_CH0_PAUSE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC0_CH0_PAUSE_CNT_RD_MASK, MEM_FB_DMAC0_CH0_PAUSE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC0_CH0_PAUSE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC1_CH0_PAUSE_CNT_OFFSET, \
                                    MEM_FB_DMAC1_CH0_PAUSE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC1_CH0_PAUSE_CNT_RD_MASK, MEM_FB_DMAC1_CH0_PAUSE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC1_CH0_PAUSE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC0_CH1_PAUSE_CNT_OFFSET, \
                                    MEM_FB_DMAC0_CH1_PAUSE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC0_CH1_PAUSE_CNT_RD_MASK, MEM_FB_DMAC0_CH1_PAUSE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC0_CH1_PAUSE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMAC1_CH1_PAUSE_CNT_OFFSET, \
                                    MEM_FB_DMAC1_CH1_PAUSE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC1_CH1_PAUSE_CNT_RD_MASK, MEM_FB_DMAC1_CH1_PAUSE_CNT_WR_MASK, \
                                    "MEM_FB_DMAC1_CH1_PAUSE_CNT_OFFSET");

//            write_read_expect_18a(base_address[i]+MEM_FB_DMAC_LL_INVALID_OFFSET, \
                                    MEM_FB_DMAC_LL_INVALID_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMAC_LL_INVALID_RD_MASK, MEM_FB_DMAC_LL_INVALID_WR_MASK, \
                                    "MEM_FB_DMAC_LL_INVALID_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_NSIP_CM0_PKT_LEN_OFFSET, \
                                    MEM_FB_NSIP_CM0_PKT_LEN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_NSIP_CM0_PKT_LEN_RD_MASK, MEM_FB_NSIP_CM0_PKT_LEN_WR_MASK, \
                                    "MEM_FB_NSIP_CM0_PKT_LEN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_NSIP_CM1_PKT_LEN_OFFSET, \
                                    MEM_FB_NSIP_CM1_PKT_LEN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_NSIP_CM1_PKT_LEN_RD_MASK, MEM_FB_NSIP_CM1_PKT_LEN_WR_MASK, \
                                    "MEM_FB_NSIP_CM1_PKT_LEN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_NSIP_CM_HALT_CFG_OFFSET, \
                                    MEM_FB_NSIP_CM_HALT_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_NSIP_CM_HALT_CFG_RD_MASK, MEM_FB_NSIP_CM_HALT_CFG_WR_MASK, \
                                    "MEM_FB_NSIP_CM_HALT_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_NSIP_CM_HALT_STAT_OFFSET, \
                                    MEM_FB_NSIP_CM_HALT_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_NSIP_CM_HALT_STAT_RD_MASK, MEM_FB_NSIP_CM_HALT_STAT_WR_MASK, \
                                    "MEM_FB_NSIP_CM_HALT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_NSIP_CM_STATE_DBG_OFFSET, \
                                    MEM_FB_NSIP_CM_STATE_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_NSIP_CM_STATE_DBG_RD_MASK, MEM_FB_NSIP_CM_STATE_DBG_WR_MASK, \
                                    "MEM_FB_NSIP_CM_STATE_DBG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_HI_AGG_STAT_OFFSET, \
                                    MEM_FB_INT_HI_AGG_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_HI_AGG_STAT_RD_MASK, MEM_FB_INT_HI_AGG_STAT_WR_MASK, \
                                    "MEM_FB_INT_HI_AGG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_LO_AGG_STAT_OFFSET, \
                                    MEM_FB_INT_LO_AGG_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_LO_AGG_STAT_RD_MASK, MEM_FB_INT_LO_AGG_STAT_WR_MASK, \
                                    "MEM_FB_INT_LO_AGG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_FB_STAT_OFFSET, \
                                    MEM_FB_INT_FB_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_FB_STAT_RD_MASK, MEM_FB_INT_FB_STAT_WR_MASK, \
                                    "MEM_FB_INT_FB_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_FB_HIGH_EN_OFFSET, \
                                    MEM_FB_INT_FB_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_FB_HIGH_EN_RD_MASK, MEM_FB_INT_FB_HIGH_EN_WR_MASK, \
                                    "MEM_FB_INT_FB_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_FB_LOW_EN_OFFSET, \
                                    MEM_FB_INT_FB_LOW_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_FB_LOW_EN_RD_MASK, MEM_FB_INT_FB_LOW_EN_WR_MASK, \
                                    "MEM_FB_INT_FB_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_FB_CLR_OFFSET, \
                                    MEM_FB_INT_FB_CLR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_FB_CLR_RD_MASK, MEM_FB_INT_FB_CLR_WR_MASK, \
                                    "MEM_FB_INT_FB_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_FB_FORCE_OFFSET, \
                                    MEM_FB_INT_FB_FORCE_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_FB_FORCE_RD_MASK, MEM_FB_INT_FB_FORCE_WR_MASK, \
                                    "MEM_FB_INT_FB_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_CRUX_STAT_OFFSET, \
                                    MEM_FB_INT_CRUX_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_CRUX_STAT_RD_MASK, MEM_FB_INT_CRUX_STAT_WR_MASK, \
                                    "MEM_FB_INT_CRUX_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_CRUX_HIGH_EN_OFFSET, \
                                    MEM_FB_INT_CRUX_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_CRUX_HIGH_EN_RD_MASK, MEM_FB_INT_CRUX_HIGH_EN_WR_MASK, \
                                    "MEM_FB_INT_CRUX_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_CRUX_LOW_EN_OFFSET, \
                                    MEM_FB_INT_CRUX_LOW_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_CRUX_LOW_EN_RD_MASK, MEM_FB_INT_CRUX_LOW_EN_WR_MASK, \
                                    "MEM_FB_INT_CRUX_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_CRUX_CLR_OFFSET, \
                                    MEM_FB_INT_CRUX_CLR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_CRUX_CLR_RD_MASK, MEM_FB_INT_CRUX_CLR_WR_MASK, \
                                    "MEM_FB_INT_CRUX_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_INT_CRUX_FORCE_OFFSET, \
                                    MEM_FB_INT_CRUX_FORCE_DEFAULT, write_data, expected_data, \
                                    MEM_FB_INT_CRUX_FORCE_RD_MASK, MEM_FB_INT_CRUX_FORCE_WR_MASK, \
                                    "MEM_FB_INT_CRUX_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_INFO0_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_INFO_RD_MASK, MEM_FB_AXI_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_INFO0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_CTL0_OFFSET, \
                                    MEM_FB_AXI_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_CTL_RD_MASK, MEM_FB_AXI_ECC_CTL_WR_MASK, \
                                    "MEM_FB_AXI_ECC_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_STAT0_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_STAT_RD_MASK, MEM_FB_AXI_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_INFO1_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_INFO_RD_MASK, MEM_FB_AXI_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_INFO1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_CTL1_OFFSET, \
                                    MEM_FB_AXI_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_CTL_RD_MASK, MEM_FB_AXI_ECC_CTL_WR_MASK, \
                                    "MEM_FB_AXI_ECC_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_STAT1_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_STAT_RD_MASK, MEM_FB_AXI_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_INFO2_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_INFO_RD_MASK, MEM_FB_AXI_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_INFO2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_CTL2_OFFSET, \
                                    MEM_FB_AXI_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_CTL_RD_MASK, MEM_FB_AXI_ECC_CTL_WR_MASK, \
                                    "MEM_FB_AXI_ECC_CTL2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_AXI_ECC_ERR_STAT2_OFFSET, \
                                    MEM_FB_AXI_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_AXI_ECC_ERR_STAT_RD_MASK, MEM_FB_AXI_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_AXI_ECC_ERR_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_MEM_PTR_PORT0_OFFSET, \
                                    MEM_FB_MEM_PTR_PORT0_DEFAULT, write_data, expected_data, \
                                    MEM_FB_MEM_PTR_PORT0_RD_MASK, MEM_FB_MEM_PTR_PORT0_WR_MASK, \
                                    "MEM_FB_MEM_PTR_PORT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_MEM_PTR_PORT1_OFFSET, \
                                    MEM_FB_MEM_PTR_PORT1_DEFAULT, write_data, expected_data, \
                                    MEM_FB_MEM_PTR_PORT1_RD_MASK, MEM_FB_MEM_PTR_PORT1_WR_MASK, \
                                    "MEM_FB_MEM_PTR_PORT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_MEM_PTR_PORT2_OFFSET, \
                                    MEM_FB_MEM_PTR_PORT2_DEFAULT, write_data, expected_data, \
                                    MEM_FB_MEM_PTR_PORT2_RD_MASK, MEM_FB_MEM_PTR_PORT2_WR_MASK, \
                                    "MEM_FB_MEM_PTR_PORT2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_MEM_PTR_PORT3_OFFSET, \
                                    MEM_FB_MEM_PTR_PORT3_DEFAULT, write_data, expected_data, \
                                    MEM_FB_MEM_PTR_PORT3_RD_MASK, MEM_FB_MEM_PTR_PORT3_WR_MASK, \
                                    "MEM_FB_MEM_PTR_PORT3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SAMPLE_CNT0_OFFSET, \
                                    MEM_FB_SAMPLE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SAMPLE_CNT_RD_MASK, MEM_FB_SAMPLE_CNT_WR_MASK, \
                                    "MEM_FB_SAMPLE_CNT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SAMPLE_CNT1_OFFSET, \
                                    MEM_FB_SAMPLE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SAMPLE_CNT_RD_MASK, MEM_FB_SAMPLE_CNT_WR_MASK, \
                                    "MEM_FB_SAMPLE_CNT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SAMPLE_CNT2_OFFSET, \
                                    MEM_FB_SAMPLE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SAMPLE_CNT_RD_MASK, MEM_FB_SAMPLE_CNT_WR_MASK, \
                                    "MEM_FB_SAMPLE_CNT2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SAMPLE_CNT3_OFFSET, \
                                    MEM_FB_SAMPLE_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SAMPLE_CNT_RD_MASK, MEM_FB_SAMPLE_CNT_WR_MASK, \
                                    "MEM_FB_SAMPLE_CNT3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ANT_INTF_STAT_OFFSET, \
                                    MEM_FB_ANT_INTF_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ANT_INTF_STAT_RD_MASK, MEM_FB_ANT_INTF_STAT_WR_MASK, \
                                    "MEM_FB_ANT_INTF_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR0_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR0_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR1_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR1_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR2_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR2_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR3_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR3_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR4_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR4_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR5_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR5_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR6_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR6_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR7_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR7_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR8_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR8_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR8_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR9_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR9_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR9_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR10_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR10_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR10_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR11_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR11_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR11_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR12_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR12_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR12_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR13_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR13_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR13_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR14_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR14_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR14_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR15_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR15_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR15_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR16_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR16_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR16_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR17_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR17_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR17_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR17_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR18_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR18_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR18_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR18_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR19_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR19_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR19_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR19_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR20_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR20_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR20_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR20_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR21_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR21_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR21_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR21_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR22_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR22_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR22_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR22_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR23_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR23_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR23_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR23_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR24_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR24_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR24_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR24_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR25_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR25_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR25_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR25_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR26_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR26_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR26_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR26_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR27_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR27_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR27_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR27_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR28_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR28_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR28_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR28_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR29_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR29_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR29_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR29_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR30_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR30_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR30_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR30_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_END_PTR31_OFFSET, \
                                    MEM_FB_SECTOR_END_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_END_PTR_RD_MASK, MEM_FB_SECTOR_END_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_END_PTR31_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_SECTOR_NEXT_PTR31_OFFSET, \
                                    MEM_FB_SECTOR_NEXT_PTR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_SECTOR_NEXT_PTR_RD_MASK, MEM_FB_SECTOR_NEXT_PTR_WR_MASK, \
                                    "MEM_FB_SECTOR_NEXT_PTR31_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFN_STATE_DBG0_OFFSET, \
                                    MEM_FB_BFN_STATE_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFN_STATE_DBG_RD_MASK, MEM_FB_BFN_STATE_DBG_WR_MASK, \
                                    "MEM_FB_BFN_STATE_DBG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFN_STATE_DBG1_OFFSET, \
                                    MEM_FB_BFN_STATE_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFN_STATE_DBG_RD_MASK, MEM_FB_BFN_STATE_DBG_WR_MASK, \
                                    "MEM_FB_BFN_STATE_DBG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_CTRL_OFFSET, \
                                    MEM_FB_ISYNC_CTRL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_CTRL_RD_MASK, MEM_FB_ISYNC_CTRL_WR_MASK, \
                                    "MEM_FB_ISYNC_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_LCNT_INC_OFFSET, \
                                    MEM_FB_ISYNC_LCNT_INC_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_LCNT_INC_RD_MASK, MEM_FB_ISYNC_LCNT_INC_WR_MASK, \
                                    "MEM_FB_ISYNC_LCNT_INC_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_TEN_MS_CNT_OFFSET, \
                                    MEM_FB_ISYNC_TEN_MS_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_TEN_MS_CNT_RD_MASK, MEM_FB_ISYNC_TEN_MS_CNT_WR_MASK, \
                                    "MEM_FB_ISYNC_TEN_MS_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_INC_PRE_OFFSET, \
                                    MEM_FB_ISYNC_INC_PRE_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_INC_PRE_RD_MASK, MEM_FB_ISYNC_INC_PRE_WR_MASK, \
                                    "MEM_FB_ISYNC_INC_PRE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_CNT_ADJ_OFFSET, \
                                    MEM_FB_ISYNC_CNT_ADJ_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_CNT_ADJ_RD_MASK, MEM_FB_ISYNC_CNT_ADJ_WR_MASK, \
                                    "MEM_FB_ISYNC_CNT_ADJ_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    MEM_FB_ISYNC_BFN_CNT_SYNC_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_BFN_CNT_SYNC_RD_MASK, MEM_FB_ISYNC_BFN_CNT_SYNC_WR_MASK, \
                                    "MEM_FB_ISYNC_BFN_CNT_SYNC_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_ISYNC_BFN_CNT_OFFSET, \
                                    MEM_FB_ISYNC_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_ISYNC_BFN_CNT_RD_MASK, MEM_FB_ISYNC_BFN_CNT_WR_MASK, \
                                    "MEM_FB_ISYNC_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG0_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG1_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG2_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG3_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG4_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG5_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG6_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_CFG7_OFFSET, \
                                    MEM_FB_BFNE_CFG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_CFG_RD_MASK, MEM_FB_BFNE_CFG_WR_MASK, \
                                    "MEM_FB_BFNE_CFG7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR0_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR1_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR2_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR3_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR4_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR5_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR6_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_INCR7_OFFSET, \
                                    MEM_FB_BFNE_INCR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_INCR_RD_MASK, MEM_FB_BFNE_INCR_WR_MASK, \
                                    "MEM_FB_BFNE_INCR7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START0_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START1_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START2_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START3_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START4_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START5_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START6_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_START7_OFFSET, \
                                    MEM_FB_BFNE_START_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_START_RD_MASK, MEM_FB_BFNE_START_WR_MASK, \
                                    "MEM_FB_BFNE_START7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT0_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT1_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT2_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT2_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT3_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT3_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT4_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT4_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT5_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT5_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT6_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT6_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_BFNE_STAT7_OFFSET, \
                                    MEM_FB_BFNE_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_BFNE_STAT_RD_MASK, MEM_FB_BFNE_STAT_WR_MASK, \
                                    "MEM_FB_BFNE_STAT7_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_ERR_INFO0_OFFSET, \
                                    MEM_FB_DESC_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_ERR_INFO_RD_MASK, MEM_FB_DESC_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DESC_ECC_ERR_INFO0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_CTL0_OFFSET, \
                                    MEM_FB_DESC_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_CTL_RD_MASK, MEM_FB_DESC_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DESC_ECC_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_ERR_STAT0_OFFSET, \
                                    MEM_FB_DESC_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_ERR_STAT_RD_MASK, MEM_FB_DESC_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DESC_ECC_ERR_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_ERR_INFO1_OFFSET, \
                                    MEM_FB_DESC_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_ERR_INFO_RD_MASK, MEM_FB_DESC_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DESC_ECC_ERR_INFO1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_CTL1_OFFSET, \
                                    MEM_FB_DESC_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_CTL_RD_MASK, MEM_FB_DESC_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DESC_ECC_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DESC_ECC_ERR_STAT1_OFFSET, \
                                    MEM_FB_DESC_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DESC_ECC_ERR_STAT_RD_MASK, MEM_FB_DESC_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DESC_ECC_ERR_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_ERR_INFO0_OFFSET, \
                                    MEM_FB_DMA0_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_ERR_INFO_RD_MASK, MEM_FB_DMA0_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_ERR_INFO0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_CTL0_OFFSET, \
                                    MEM_FB_DMA0_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_CTL_RD_MASK, MEM_FB_DMA0_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_ERR_STAT0_OFFSET, \
                                    MEM_FB_DMA0_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_ERR_STAT_RD_MASK, MEM_FB_DMA0_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_ERR_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_ERR_INFO1_OFFSET, \
                                    MEM_FB_DMA0_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_ERR_INFO_RD_MASK, MEM_FB_DMA0_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_ERR_INFO1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_CTL1_OFFSET, \
                                    MEM_FB_DMA0_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_CTL_RD_MASK, MEM_FB_DMA0_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA0_ECC_ERR_STAT1_OFFSET, \
                                    MEM_FB_DMA0_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA0_ECC_ERR_STAT_RD_MASK, MEM_FB_DMA0_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DMA0_ECC_ERR_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_ERR_INFO0_OFFSET, \
                                    MEM_FB_DMA1_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_ERR_INFO_RD_MASK, MEM_FB_DMA1_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_ERR_INFO0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_CTL0_OFFSET, \
                                    MEM_FB_DMA1_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_CTL_RD_MASK, MEM_FB_DMA1_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_ERR_STAT0_OFFSET, \
                                    MEM_FB_DMA1_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_ERR_STAT_RD_MASK, MEM_FB_DMA1_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_ERR_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_ERR_INFO1_OFFSET, \
                                    MEM_FB_DMA1_ECC_ERR_INFO_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_ERR_INFO_RD_MASK, MEM_FB_DMA1_ECC_ERR_INFO_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_ERR_INFO1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_CTL1_OFFSET, \
                                    MEM_FB_DMA1_ECC_CTL_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_CTL_RD_MASK, MEM_FB_DMA1_ECC_CTL_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA1_ECC_ERR_STAT1_OFFSET, \
                                    MEM_FB_DMA1_ECC_ERR_STAT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA1_ECC_ERR_STAT_RD_MASK, MEM_FB_DMA1_ECC_ERR_STAT_WR_MASK, \
                                    "MEM_FB_DMA1_ECC_ERR_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA_DP_INIT_OFFSET, \
                                    MEM_FB_DMA_DP_INIT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA_DP_INIT_RD_MASK, MEM_FB_DMA_DP_INIT_WR_MASK, \
                                    "MEM_FB_DMA_DP_INIT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_DMA_DP_INIT_DONE_OFFSET, \
                                    MEM_FB_DMA_DP_INIT_DONE_DEFAULT, write_data, expected_data, \
                                    MEM_FB_DMA_DP_INIT_DONE_RD_MASK, MEM_FB_DMA_DP_INIT_DONE_WR_MASK, \
                                    "MEM_FB_DMA_DP_INIT_DONE_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA_SEL_HALT_OFFSET, \
                                    MEM_FB_VEX_DMA_SEL_HALT_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA_SEL_HALT_RD_MASK, MEM_FB_VEX_DMA_SEL_HALT_WR_MASK, \
                                    "MEM_FB_VEX_DMA_SEL_HALT_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_MEM_START_ADDR_OFFSET, \
                                    MEM_FB_VEX_MEM_START_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_MEM_START_ADDR_RD_MASK, MEM_FB_VEX_MEM_START_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_MEM_START_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_MEM_END_ADDR_OFFSET, \
                                    MEM_FB_VEX_MEM_END_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_MEM_END_ADDR_RD_MASK, MEM_FB_VEX_MEM_END_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_MEM_END_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DESC_START_ADDR_OFFSET, \
                                    MEM_FB_VEX_DESC_START_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DESC_START_ADDR_RD_MASK, MEM_FB_VEX_DESC_START_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_DESC_START_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DESC_END_ADDR_OFFSET, \
                                    MEM_FB_VEX_DESC_END_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DESC_END_ADDR_RD_MASK, MEM_FB_VEX_DESC_END_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_DESC_END_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_START_ADDR_OFFSET, \
                                    MEM_FB_VEX_START_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_START_ADDR_RD_MASK, MEM_FB_VEX_START_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_START_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_END_ADDR_OFFSET, \
                                    MEM_FB_VEX_END_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_END_ADDR_RD_MASK, MEM_FB_VEX_END_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_END_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_ADDR_MASK_OFFSET, \
                                    MEM_FB_VEX_ADDR_MASK_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_ADDR_MASK_RD_MASK, MEM_FB_VEX_ADDR_MASK_WR_MASK, \
                                    "MEM_FB_VEX_ADDR_MASK_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_CM0_BAD_ADDR_OFFSET, \
                                    MEM_FB_VEX_CM0_BAD_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_CM0_BAD_ADDR_RD_MASK, MEM_FB_VEX_CM0_BAD_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_CM0_BAD_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_CM1_BAD_ADDR_OFFSET, \
                                    MEM_FB_VEX_CM1_BAD_ADDR_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_CM1_BAD_ADDR_RD_MASK, MEM_FB_VEX_CM1_BAD_ADDR_WR_MASK, \
                                    "MEM_FB_VEX_CM1_BAD_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_CM0_DROP_IDX_OFFSET, \
                                    MEM_FB_VEX_CM0_DROP_IDX_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_CM0_DROP_IDX_RD_MASK, MEM_FB_VEX_CM0_DROP_IDX_WR_MASK, \
                                    "MEM_FB_VEX_CM0_DROP_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_CM1_DROP_IDX_OFFSET, \
                                    MEM_FB_VEX_CM1_DROP_IDX_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_CM1_DROP_IDX_RD_MASK, MEM_FB_VEX_CM1_DROP_IDX_WR_MASK, \
                                    "MEM_FB_VEX_CM1_DROP_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_TIMER_OFFSET, \
                                    MEM_FB_VEX_TIMER_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_TIMER_RD_MASK, MEM_FB_VEX_TIMER_WR_MASK, \
                                    "MEM_FB_VEX_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DBG_OFFSET, \
                                    MEM_FB_VEX_DBG_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DBG_RD_MASK, MEM_FB_VEX_DBG_WR_MASK, \
                                    "MEM_FB_VEX_DBG_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA0_CH0_LLP_OFFSET, \
                                    MEM_FB_VEX_DMA0_CH0_LLP_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA0_CH0_LLP_RD_MASK, MEM_FB_VEX_DMA0_CH0_LLP_WR_MASK, \
                                    "MEM_FB_VEX_DMA0_CH0_LLP_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA0_CH1_LLP_OFFSET, \
                                    MEM_FB_VEX_DMA0_CH1_LLP_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA0_CH1_LLP_RD_MASK, MEM_FB_VEX_DMA0_CH1_LLP_WR_MASK, \
                                    "MEM_FB_VEX_DMA0_CH1_LLP_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA1_CH0_LLP_OFFSET, \
                                    MEM_FB_VEX_DMA1_CH0_LLP_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA1_CH0_LLP_RD_MASK, MEM_FB_VEX_DMA1_CH0_LLP_WR_MASK, \
                                    "MEM_FB_VEX_DMA1_CH0_LLP_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA1_CH1_LLP_OFFSET, \
                                    MEM_FB_VEX_DMA1_CH1_LLP_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA1_CH1_LLP_RD_MASK, MEM_FB_VEX_DMA1_CH1_LLP_WR_MASK, \
                                    "MEM_FB_VEX_DMA1_CH1_LLP_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA0_CH01_EN_OFFSET, \
                                    MEM_FB_VEX_DMA0_CH01_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA0_CH01_EN_RD_MASK, MEM_FB_VEX_DMA0_CH01_EN_WR_MASK, \
                                    "MEM_FB_VEX_DMA0_CH01_EN_OFFSET");

            write_read_expect_18a(base_address[i]+MEM_FB_VEX_DMA1_CH01_EN_OFFSET, \
                                    MEM_FB_VEX_DMA1_CH01_EN_DEFAULT, write_data, expected_data, \
                                    MEM_FB_VEX_DMA1_CH01_EN_RD_MASK, MEM_FB_VEX_DMA1_CH01_EN_WR_MASK, \
                                    "MEM_FB_VEX_DMA1_CH01_EN_OFFSET");

        }

    }

}
