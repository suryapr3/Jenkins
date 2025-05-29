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
    DLNK_JESD0_PHY_UC_TOP_BASE, DLNK_JESD1_PHY_UC_TOP_BASE, DLNK_JESD2_PHY_UC_TOP_BASE, DLNK_JESD3_PHY_UC_TOP_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_REVISION_OFFSET, \
                                    UC_TOP_MSG_UC_REVISION_DEFAULT, \
                                    UC_TOP_MSG_UC_REVISION_RD_MASK, "UC_TOP_MSG_UC_REVISION_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_JTAG_VER_OFFSET, \
                                    UC_TOP_MSG_UC_JTAG_VER_DEFAULT, \
                                    UC_TOP_MSG_UC_JTAG_VER_RD_MASK, "UC_TOP_MSG_UC_JTAG_VER_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_CAR_CLK_CTRL_OFFSET, \
                                    UC_TOP_MSG_CAR_CLK_CTRL_DEFAULT, \
                                    UC_TOP_MSG_CAR_CLK_CTRL_RD_MASK, "UC_TOP_MSG_CAR_CLK_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_CAR_RST_CTRL_OFFSET, \
                                    UC_TOP_MSG_CAR_RST_CTRL_DEFAULT, \
                                    UC_TOP_MSG_CAR_RST_CTRL_RD_MASK, "UC_TOP_MSG_CAR_RST_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RATE_LIMIT_LANE_0_OFFSET, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_0_DEFAULT, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_0_RD_MASK, "UC_TOP_MSG_UC_RATE_LIMIT_LANE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RATE_LIMIT_LANE_1_OFFSET, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_1_DEFAULT, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_1_RD_MASK, "UC_TOP_MSG_UC_RATE_LIMIT_LANE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RATE_LIMIT_LANE_2_OFFSET, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_2_DEFAULT, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_2_RD_MASK, "UC_TOP_MSG_UC_RATE_LIMIT_LANE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RATE_LIMIT_LANE_3_OFFSET, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_3_DEFAULT, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_3_RD_MASK, "UC_TOP_MSG_UC_RATE_LIMIT_LANE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RATE_LIMIT_LANE_4_OFFSET, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_4_DEFAULT, \
                                    UC_TOP_MSG_UC_RATE_LIMIT_LANE_4_RD_MASK, "UC_TOP_MSG_UC_RATE_LIMIT_LANE_4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_REF_CLK_FREQ_0_OFFSET, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_0_DEFAULT, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_0_RD_MASK, "UC_TOP_MSG_UC_REF_CLK_FREQ_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_REF_CLK_FREQ_1_OFFSET, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_1_DEFAULT, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_1_RD_MASK, "UC_TOP_MSG_UC_REF_CLK_FREQ_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_REF_CLK_FREQ_2_OFFSET, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_2_DEFAULT, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_2_RD_MASK, "UC_TOP_MSG_UC_REF_CLK_FREQ_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_REF_CLK_FREQ_3_OFFSET, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_3_DEFAULT, \
                                    UC_TOP_MSG_UC_REF_CLK_FREQ_3_RD_MASK, "UC_TOP_MSG_UC_REF_CLK_FREQ_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_FUSE_0_OFFSET, \
                                    UC_TOP_MSG_UC_FUSE_0_DEFAULT, \
                                    UC_TOP_MSG_UC_FUSE_0_RD_MASK, "UC_TOP_MSG_UC_FUSE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_FUSE_1_OFFSET, \
                                    UC_TOP_MSG_UC_FUSE_1_DEFAULT, \
                                    UC_TOP_MSG_UC_FUSE_1_RD_MASK, "UC_TOP_MSG_UC_FUSE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_FUSE_2_OFFSET, \
                                    UC_TOP_MSG_UC_FUSE_2_DEFAULT, \
                                    UC_TOP_MSG_UC_FUSE_2_RD_MASK, "UC_TOP_MSG_UC_FUSE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_FUSE_3_OFFSET, \
                                    UC_TOP_MSG_UC_FUSE_3_DEFAULT, \
                                    UC_TOP_MSG_UC_FUSE_3_RD_MASK, "UC_TOP_MSG_UC_FUSE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_PRODUCT_SKU_OFFSET, \
                                    UC_TOP_MSG_UC_PRODUCT_SKU_DEFAULT, \
                                    UC_TOP_MSG_UC_PRODUCT_SKU_RD_MASK, "UC_TOP_MSG_UC_PRODUCT_SKU_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FABRIC_CTRL_OFFSET, \
                                    UC_TOP_MSG_FABRIC_CTRL_DEFAULT, \
                                    UC_TOP_MSG_FABRIC_CTRL_RD_MASK, "UC_TOP_MSG_FABRIC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL0_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL0_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL0_RD_MASK, "UC_TOP_MSG_MEM_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL1_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL1_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL1_RD_MASK, "UC_TOP_MSG_MEM_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL2_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL2_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL2_RD_MASK, "UC_TOP_MSG_MEM_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL3_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL3_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL3_RD_MASK, "UC_TOP_MSG_MEM_CTRL3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL4_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL4_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL4_RD_MASK, "UC_TOP_MSG_MEM_CTRL4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL5_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL5_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL5_RD_MASK, "UC_TOP_MSG_MEM_CTRL5_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL6_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL6_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL6_RD_MASK, "UC_TOP_MSG_MEM_CTRL6_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL7_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL7_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL7_RD_MASK, "UC_TOP_MSG_MEM_CTRL7_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL8_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL8_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL8_RD_MASK, "UC_TOP_MSG_MEM_CTRL8_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL9_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL9_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL9_RD_MASK, "UC_TOP_MSG_MEM_CTRL9_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_MEM_CTRL10_OFFSET, \
                                    UC_TOP_MSG_MEM_CTRL10_DEFAULT, \
                                    UC_TOP_MSG_MEM_CTRL10_RD_MASK, "UC_TOP_MSG_MEM_CTRL10_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_PMA_RST_REQ_OFFSET, \
                                    UC_TOP_MSG_PMA_RST_REQ_DEFAULT, \
                                    UC_TOP_MSG_PMA_RST_REQ_RD_MASK, "UC_TOP_MSG_PMA_RST_REQ_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_0_CTL0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_0_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_0_CTL1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_0_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_0_CTL2_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL2_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_0_CTL2_RD_MASK, "UC_TOP_MSG_ICU_IRQ_0_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_0_STAT0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_0_STAT0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_0_STAT0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_0_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_0_STAT1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_0_STAT1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_0_STAT1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_0_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_4_CTL0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_4_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_4_CTL1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_4_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_4_CTL2_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL2_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_4_CTL2_RD_MASK, "UC_TOP_MSG_ICU_IRQ_4_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_4_STAT0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_4_STAT0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_4_STAT0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_4_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_4_STAT1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_4_STAT1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_4_STAT1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_4_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_10_CTL0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_10_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_10_CTL1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_10_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_10_CTL2_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL2_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_10_CTL2_RD_MASK, "UC_TOP_MSG_ICU_IRQ_10_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_10_STAT0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_10_STAT0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_10_STAT0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_10_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_10_STAT1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_10_STAT1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_10_STAT1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_10_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_16_CTL0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_16_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_16_CTL1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_16_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_16_CTL2_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL2_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_16_CTL2_RD_MASK, "UC_TOP_MSG_ICU_IRQ_16_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_16_STAT0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_16_STAT0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_16_STAT0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_16_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_16_STAT1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_16_STAT1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_16_STAT1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_16_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_17_CTL0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_17_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_17_CTL1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_17_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_17_CTL2_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL2_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_17_CTL2_RD_MASK, "UC_TOP_MSG_ICU_IRQ_17_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_17_STAT0_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_17_STAT0_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_17_STAT0_RD_MASK, "UC_TOP_MSG_ICU_IRQ_17_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_17_STAT1_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_17_STAT1_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_17_STAT1_RD_MASK, "UC_TOP_MSG_ICU_IRQ_17_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_ICU_IRQ_RAW_STAT_OFFSET, \
                                    UC_TOP_MSG_ICU_IRQ_RAW_STAT_DEFAULT, \
                                    UC_TOP_MSG_ICU_IRQ_RAW_STAT_RD_MASK, "UC_TOP_MSG_ICU_IRQ_RAW_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_0_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_0_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_0_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_1_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_1_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_1_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_2_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_2_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_2_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_3_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_3_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_3_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_4_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_4_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_4_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_5_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_5_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_5_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_5_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_6_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_6_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_6_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_6_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_STAT_RSLT_7_OFFSET, \
                                    UC_TOP_MSG_FW_STAT_RSLT_7_DEFAULT, \
                                    UC_TOP_MSG_FW_STAT_RSLT_7_RD_MASK, "UC_TOP_MSG_FW_STAT_RSLT_7_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_0_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_0_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_0_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_1_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_1_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_1_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_2_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_2_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_2_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_3_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_3_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_3_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_4_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_4_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_4_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_5_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_5_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_5_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_5_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_6_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_6_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_6_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_6_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_MACRO_TRIG_CTRL_7_OFFSET, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_7_DEFAULT, \
                                    UC_TOP_MSG_FW_MACRO_TRIG_CTRL_7_RD_MASK, "UC_TOP_MSG_FW_MACRO_TRIG_CTRL_7_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_TEMP_SENSE_OFFSET, \
                                    UC_TOP_MSG_TEMP_SENSE_DEFAULT, \
                                    UC_TOP_MSG_TEMP_SENSE_RD_MASK, "UC_TOP_MSG_TEMP_SENSE_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_AUTONEG_0_OFFSET, \
                                    UC_TOP_MSG_AUTONEG_0_DEFAULT, \
                                    UC_TOP_MSG_AUTONEG_0_RD_MASK, "UC_TOP_MSG_AUTONEG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_AUTONEG_1_OFFSET, \
                                    UC_TOP_MSG_AUTONEG_1_DEFAULT, \
                                    UC_TOP_MSG_AUTONEG_1_RD_MASK, "UC_TOP_MSG_AUTONEG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_VER_0_OFFSET, \
                                    UC_TOP_MSG_FW_VER_0_DEFAULT, \
                                    UC_TOP_MSG_FW_VER_0_RD_MASK, "UC_TOP_MSG_FW_VER_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_VER_1_OFFSET, \
                                    UC_TOP_MSG_FW_VER_1_DEFAULT, \
                                    UC_TOP_MSG_FW_VER_1_RD_MASK, "UC_TOP_MSG_FW_VER_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_VER_2_OFFSET, \
                                    UC_TOP_MSG_FW_VER_2_DEFAULT, \
                                    UC_TOP_MSG_FW_VER_2_RD_MASK, "UC_TOP_MSG_FW_VER_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_VER_3_OFFSET, \
                                    UC_TOP_MSG_FW_VER_3_DEFAULT, \
                                    UC_TOP_MSG_FW_VER_3_RD_MASK, "UC_TOP_MSG_FW_VER_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_TIMEBASE_OFFSET, \
                                    UC_TOP_MSG_FW_TIMEBASE_DEFAULT, \
                                    UC_TOP_MSG_FW_TIMEBASE_RD_MASK, "UC_TOP_MSG_FW_TIMEBASE_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_RATE_LIMIT_LANE_0_OFFSET, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_0_DEFAULT, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_0_RD_MASK, "UC_TOP_MSG_FW_RATE_LIMIT_LANE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_RATE_LIMIT_LANE_1_OFFSET, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_1_DEFAULT, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_1_RD_MASK, "UC_TOP_MSG_FW_RATE_LIMIT_LANE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_RATE_LIMIT_LANE_2_OFFSET, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_2_DEFAULT, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_2_RD_MASK, "UC_TOP_MSG_FW_RATE_LIMIT_LANE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_RATE_LIMIT_LANE_3_OFFSET, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_3_DEFAULT, \
                                    UC_TOP_MSG_FW_RATE_LIMIT_LANE_3_RD_MASK, "UC_TOP_MSG_FW_RATE_LIMIT_LANE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_REF_CLK_FREQ_0_OFFSET, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_0_DEFAULT, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_0_RD_MASK, "UC_TOP_MSG_FW_REF_CLK_FREQ_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_REF_CLK_FREQ_1_OFFSET, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_1_DEFAULT, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_1_RD_MASK, "UC_TOP_MSG_FW_REF_CLK_FREQ_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_REF_CLK_FREQ_2_OFFSET, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_2_DEFAULT, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_2_RD_MASK, "UC_TOP_MSG_FW_REF_CLK_FREQ_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_REF_CLK_FREQ_3_OFFSET, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_3_DEFAULT, \
                                    UC_TOP_MSG_FW_REF_CLK_FREQ_3_RD_MASK, "UC_TOP_MSG_FW_REF_CLK_FREQ_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_FUSE_0_OFFSET, \
                                    UC_TOP_MSG_FW_FUSE_0_DEFAULT, \
                                    UC_TOP_MSG_FW_FUSE_0_RD_MASK, "UC_TOP_MSG_FW_FUSE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_FUSE_1_OFFSET, \
                                    UC_TOP_MSG_FW_FUSE_1_DEFAULT, \
                                    UC_TOP_MSG_FW_FUSE_1_RD_MASK, "UC_TOP_MSG_FW_FUSE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_FUSE_2_OFFSET, \
                                    UC_TOP_MSG_FW_FUSE_2_DEFAULT, \
                                    UC_TOP_MSG_FW_FUSE_2_RD_MASK, "UC_TOP_MSG_FW_FUSE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_FUSE_3_OFFSET, \
                                    UC_TOP_MSG_FW_FUSE_3_DEFAULT, \
                                    UC_TOP_MSG_FW_FUSE_3_RD_MASK, "UC_TOP_MSG_FW_FUSE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_CORE_STAT_0_OFFSET, \
                                    UC_TOP_MSG_FW_CORE_STAT_0_DEFAULT, \
                                    UC_TOP_MSG_FW_CORE_STAT_0_RD_MASK, "UC_TOP_MSG_FW_CORE_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_CORE_STAT_1_OFFSET, \
                                    UC_TOP_MSG_FW_CORE_STAT_1_DEFAULT, \
                                    UC_TOP_MSG_FW_CORE_STAT_1_RD_MASK, "UC_TOP_MSG_FW_CORE_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_CORE_STAT_2_OFFSET, \
                                    UC_TOP_MSG_FW_CORE_STAT_2_DEFAULT, \
                                    UC_TOP_MSG_FW_CORE_STAT_2_RD_MASK, "UC_TOP_MSG_FW_CORE_STAT_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_0_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_0_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_0_RD_MASK, "UC_TOP_MSG_FW_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_1_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_1_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_1_RD_MASK, "UC_TOP_MSG_FW_SPARE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_2_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_2_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_2_RD_MASK, "UC_TOP_MSG_FW_SPARE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_3_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_3_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_3_RD_MASK, "UC_TOP_MSG_FW_SPARE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_4_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_4_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_4_RD_MASK, "UC_TOP_MSG_FW_SPARE_4_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_5_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_5_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_5_RD_MASK, "UC_TOP_MSG_FW_SPARE_5_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_6_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_6_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_6_RD_MASK, "UC_TOP_MSG_FW_SPARE_6_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_FW_SPARE_7_OFFSET, \
                                    UC_TOP_MSG_FW_SPARE_7_DEFAULT, \
                                    UC_TOP_MSG_FW_SPARE_7_RD_MASK, "UC_TOP_MSG_FW_SPARE_7_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_SPARE_PORT_OVRD_CTRL_OFFSET, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_CTRL_DEFAULT, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_CTRL_RD_MASK, "UC_TOP_MSG_SPARE_PORT_OVRD_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_SPARE_PORT_OVRD_0_OFFSET, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_0_DEFAULT, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_0_RD_MASK, "UC_TOP_MSG_SPARE_PORT_OVRD_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_SPARE_PORT_OVRD_1_OFFSET, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_1_DEFAULT, \
                                    UC_TOP_MSG_SPARE_PORT_OVRD_1_RD_MASK, "UC_TOP_MSG_SPARE_PORT_OVRD_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_SPARE_PORT_PREOVRD_0_OFFSET, \
                                    UC_TOP_MSG_SPARE_PORT_PREOVRD_0_DEFAULT, \
                                    UC_TOP_MSG_SPARE_PORT_PREOVRD_0_RD_MASK, "UC_TOP_MSG_SPARE_PORT_PREOVRD_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_SPARE_PORT_PREOVRD_1_OFFSET, \
                                    UC_TOP_MSG_SPARE_PORT_PREOVRD_1_DEFAULT, \
                                    UC_TOP_MSG_SPARE_PORT_PREOVRD_1_RD_MASK, "UC_TOP_MSG_SPARE_PORT_PREOVRD_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_TESTBUS_CFG_0_OFFSET, \
                                    UC_TOP_MSG_UC_TESTBUS_CFG_0_DEFAULT, \
                                    UC_TOP_MSG_UC_TESTBUS_CFG_0_RD_MASK, "UC_TOP_MSG_UC_TESTBUS_CFG_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_TESTBUS_CFG_1_OFFSET, \
                                    UC_TOP_MSG_UC_TESTBUS_CFG_1_DEFAULT, \
                                    UC_TOP_MSG_UC_TESTBUS_CFG_1_RD_MASK, "UC_TOP_MSG_UC_TESTBUS_CFG_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_TESTBUS_STAT_0_OFFSET, \
                                    UC_TOP_MSG_UC_TESTBUS_STAT_0_DEFAULT, \
                                    UC_TOP_MSG_UC_TESTBUS_STAT_0_RD_MASK, "UC_TOP_MSG_UC_TESTBUS_STAT_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_TESTBUS_STAT_1_OFFSET, \
                                    UC_TOP_MSG_UC_TESTBUS_STAT_1_DEFAULT, \
                                    UC_TOP_MSG_UC_TESTBUS_STAT_1_RD_MASK, "UC_TOP_MSG_UC_TESTBUS_STAT_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_APB_CTRL_OFFSET, \
                                    UC_TOP_MSG_APB_CTRL_DEFAULT, \
                                    UC_TOP_MSG_APB_CTRL_RD_MASK, "UC_TOP_MSG_APB_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_APB_STAT_OFFSET, \
                                    UC_TOP_MSG_APB_STAT_DEFAULT, \
                                    UC_TOP_MSG_APB_STAT_RD_MASK, "UC_TOP_MSG_APB_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_APB_MASK_STAT_PRELIM_OFFSET, \
                                    UC_TOP_MSG_APB_MASK_STAT_PRELIM_DEFAULT, \
                                    UC_TOP_MSG_APB_MASK_STAT_PRELIM_RD_MASK, "UC_TOP_MSG_APB_MASK_STAT_PRELIM_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_APB_MASK_STAT_FINAL_OFFSET, \
                                    UC_TOP_MSG_APB_MASK_STAT_FINAL_DEFAULT, \
                                    UC_TOP_MSG_APB_MASK_STAT_FINAL_RD_MASK, "UC_TOP_MSG_APB_MASK_STAT_FINAL_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_CPU_PROBE_ADDR_OFFSET, \
                                    UC_TOP_MSG_UC_CPU_PROBE_ADDR_DEFAULT, \
                                    UC_TOP_MSG_UC_CPU_PROBE_ADDR_RD_MASK, "UC_TOP_MSG_UC_CPU_PROBE_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_CPU_PROBE_OUT_OFFSET, \
                                    UC_TOP_MSG_UC_CPU_PROBE_OUT_DEFAULT, \
                                    UC_TOP_MSG_UC_CPU_PROBE_OUT_RD_MASK, "UC_TOP_MSG_UC_CPU_PROBE_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RW_SPARE_0_OFFSET, \
                                    UC_TOP_MSG_UC_RW_SPARE_0_DEFAULT, \
                                    UC_TOP_MSG_UC_RW_SPARE_0_RD_MASK, "UC_TOP_MSG_UC_RW_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RW_SPARE_1_OFFSET, \
                                    UC_TOP_MSG_UC_RW_SPARE_1_DEFAULT, \
                                    UC_TOP_MSG_UC_RW_SPARE_1_RD_MASK, "UC_TOP_MSG_UC_RW_SPARE_1_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RW_SPARE_2_OFFSET, \
                                    UC_TOP_MSG_UC_RW_SPARE_2_DEFAULT, \
                                    UC_TOP_MSG_UC_RW_SPARE_2_RD_MASK, "UC_TOP_MSG_UC_RW_SPARE_2_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RW_SPARE_3_OFFSET, \
                                    UC_TOP_MSG_UC_RW_SPARE_3_DEFAULT, \
                                    UC_TOP_MSG_UC_RW_SPARE_3_RD_MASK, "UC_TOP_MSG_UC_RW_SPARE_3_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RO_SPARE_0_OFFSET, \
                                    UC_TOP_MSG_UC_RO_SPARE_0_DEFAULT, \
                                    UC_TOP_MSG_UC_RO_SPARE_0_RD_MASK, "UC_TOP_MSG_UC_RO_SPARE_0_OFFSET");

        read_reg_expect_18a(base_address[i]+UC_TOP_MSG_UC_RO_SPARE_1_OFFSET, \
                                    UC_TOP_MSG_UC_RO_SPARE_1_DEFAULT, \
                                    UC_TOP_MSG_UC_RO_SPARE_1_RD_MASK, "UC_TOP_MSG_UC_RO_SPARE_1_OFFSET");

    }

}
