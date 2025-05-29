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
    MEM_CAP0_CFG_BASE, MEM_CAP1_CFG_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG8_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG9_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG10_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG11_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG12_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG13_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG14_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG15_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_CFG16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_CFG_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_CFG_RD_MASK, "MEM_CAP_CFG_BFNE_CFG16_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR8_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR9_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR10_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR11_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR12_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR13_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR14_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR15_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_INCR16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_INCR_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_INCR_RD_MASK, "MEM_CAP_CFG_BFNE_INCR16_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START8_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START9_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START10_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START11_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START12_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START13_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START14_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START15_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_START16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_START_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_START_RD_MASK, "MEM_CAP_CFG_BFNE_START16_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT0_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT1_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT2_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT3_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT4_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT5_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT6_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT7_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT8_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT8_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT9_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT9_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT10_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT10_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT11_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT11_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT12_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT12_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT13_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT13_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT14_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT14_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT15_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT15_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFNE_STAT16_OFFSET, \
                                    MEM_CAP_CFG_BFNE_STAT_DEFAULT, \
                                    MEM_CAP_CFG_BFNE_STAT_RD_MASK, "MEM_CAP_CFG_BFNE_STAT16_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_TX_FIFO_START_DELAY_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_RX_FIFO_START_DELAY_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG0_OFFSET, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG1_OFFSET, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_DEFAULT, \
                                    MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG_RD_MASK, "MEM_CAP_CFG_RXFB_FIFO_START_DELAY_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_JESD_IN0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_RD_MASK, "MEM_CAP_CFG_BFN_CAP_TX_JESD_IN0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_JESD_IN1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_TX_JESD_IN_RD_MASK, "MEM_CAP_CFG_BFN_CAP_TX_JESD_IN1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_TX_OUT0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_TX_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_TX_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_TX_OUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RX_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_RX_OUT0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RX_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_RX_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_RX_OUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RXFB_OUT0_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_RXFB_OUT0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_BFN_CAP_RXFB_OUT1_OFFSET, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_DEFAULT, \
                                    MEM_CAP_CFG_BFN_CAP_RXFB_OUT_RD_MASK, "MEM_CAP_CFG_BFN_CAP_RXFB_OUT1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_CTRL_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_CTRL_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_CTRL_RD_MASK, "MEM_CAP_CFG_ISYNC_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_LCNT_INC_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_LCNT_INC_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_LCNT_INC_RD_MASK, "MEM_CAP_CFG_ISYNC_LCNT_INC_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_TEN_MS_CNT_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_TEN_MS_CNT_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_TEN_MS_CNT_RD_MASK, "MEM_CAP_CFG_ISYNC_TEN_MS_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_INC_PRE_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_INC_PRE_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_INC_PRE_RD_MASK, "MEM_CAP_CFG_ISYNC_INC_PRE_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_CNT_ADJ_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_CNT_ADJ_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_CNT_ADJ_RD_MASK, "MEM_CAP_CFG_ISYNC_CNT_ADJ_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_RD_MASK, "MEM_CAP_CFG_ISYNC_BFN_CNT_SYNC_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_ISYNC_BFN_CNT_OFFSET, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_DEFAULT, \
                                    MEM_CAP_CFG_ISYNC_BFN_CNT_RD_MASK, "MEM_CAP_CFG_ISYNC_BFN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_TX_RATE_OFFSET, \
                                    MEM_CAP_CFG_TX_RATE_DEFAULT, \
                                    MEM_CAP_CFG_TX_RATE_RD_MASK, "MEM_CAP_CFG_TX_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_RX_RATE_OFFSET, \
                                    MEM_CAP_CFG_RX_RATE_DEFAULT, \
                                    MEM_CAP_CFG_RX_RATE_RD_MASK, "MEM_CAP_CFG_RX_RATE_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_PLL_CTL_OFFSET, \
                                    MEM_CAP_CFG_PLL_CTL_DEFAULT, \
                                    MEM_CAP_CFG_PLL_CTL_RD_MASK, "MEM_CAP_CFG_PLL_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_AC_NCO_CFG_OFFSET, \
                                    MEM_CAP_CFG_AC_NCO_CFG_DEFAULT, \
                                    MEM_CAP_CFG_AC_NCO_CFG_RD_MASK, "MEM_CAP_CFG_AC_NCO_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_DP_INIT_OFFSET, \
                                    MEM_CAP_CFG_DP_INIT_DEFAULT, \
                                    MEM_CAP_CFG_DP_INIT_RD_MASK, "MEM_CAP_CFG_DP_INIT_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R0_OFFSET, \
                                    MEM_CAP_CFG_SMON_R0_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R0_RD_MASK, "MEM_CAP_CFG_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R1_OFFSET, \
                                    MEM_CAP_CFG_SMON_R1_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R1_RD_MASK, "MEM_CAP_CFG_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R2_OFFSET, \
                                    MEM_CAP_CFG_SMON_R2_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R2_RD_MASK, "MEM_CAP_CFG_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R3_OFFSET, \
                                    MEM_CAP_CFG_SMON_R3_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R3_RD_MASK, "MEM_CAP_CFG_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R4_OFFSET, \
                                    MEM_CAP_CFG_SMON_R4_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R4_RD_MASK, "MEM_CAP_CFG_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R5_OFFSET, \
                                    MEM_CAP_CFG_SMON_R5_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R5_RD_MASK, "MEM_CAP_CFG_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R6_OFFSET, \
                                    MEM_CAP_CFG_SMON_R6_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R6_RD_MASK, "MEM_CAP_CFG_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_SMON_R7_OFFSET, \
                                    MEM_CAP_CFG_SMON_R7_DEFAULT, \
                                    MEM_CAP_CFG_SMON_R7_RD_MASK, "MEM_CAP_CFG_SMON_R7_OFFSET");

        read_reg_expect_18a(base_address[i]+MEM_CAP_CFG_APB_BRDG_STAT_OFFSET, \
                                    MEM_CAP_CFG_APB_BRDG_STAT_DEFAULT, \
                                    MEM_CAP_CFG_APB_BRDG_STAT_RD_MASK, "MEM_CAP_CFG_APB_BRDG_STAT_OFFSET");

    }

}
