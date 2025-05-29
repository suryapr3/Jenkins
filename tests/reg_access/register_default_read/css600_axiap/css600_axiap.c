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
    SYSCON_CS_SOC_AXIAP_APB4_SLAVE_0_MM_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR4_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR4_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR4_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR5_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR5_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR5_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR6_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR6_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR6_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR7_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR7_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR7_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR8_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR8_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR8_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR8_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR9_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR9_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR9_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR9_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR10_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR10_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR10_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR10_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR11_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR11_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR11_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR11_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR12_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR12_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR12_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR12_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR13_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR13_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR13_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR13_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR14_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR14_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR14_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR14_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR15_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR15_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR15_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR15_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR16_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR16_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR16_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR16_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR17_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR17_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR17_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR17_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR18_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR18_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR18_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR18_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR19_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR19_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR19_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR19_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR20_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR20_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR20_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR20_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR21_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR21_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR21_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR21_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR22_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR22_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR22_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR22_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR23_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR23_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR23_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR23_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR24_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR24_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR24_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR24_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR25_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR25_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR25_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR25_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR26_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR26_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR26_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR26_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR27_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR27_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR27_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR27_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR28_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR28_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR28_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR28_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR29_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR29_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR29_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR29_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR30_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR30_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR30_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR30_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR31_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR31_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR31_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR31_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR32_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR32_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR32_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR32_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR33_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR33_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR33_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR33_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR34_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR34_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR34_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR34_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR35_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR35_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR35_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR35_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR36_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR36_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR36_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR36_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR37_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR37_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR37_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR37_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR38_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR38_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR38_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR38_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR39_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR39_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR39_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR39_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR40_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR40_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR40_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR40_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR41_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR41_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR41_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR41_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR42_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR42_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR42_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR42_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR43_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR43_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR43_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR43_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR44_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR44_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR44_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR44_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR45_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR45_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR45_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR45_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR46_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR46_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR46_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR46_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR47_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR47_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR47_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR47_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR48_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR48_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR48_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR48_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR49_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR49_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR49_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR49_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR50_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR50_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR50_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR50_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR51_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR51_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR51_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR51_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR52_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR52_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR52_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR52_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR53_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR53_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR53_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR53_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR54_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR54_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR54_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR54_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR55_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR55_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR55_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR55_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR56_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR56_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR56_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR56_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR57_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR57_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR57_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR57_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR58_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR58_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR58_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR58_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR59_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR59_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR59_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR59_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR60_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR60_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR60_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR60_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR61_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR61_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR61_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR61_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR62_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR62_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR62_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR62_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR63_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR63_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR63_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR63_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR64_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR64_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR64_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR64_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR65_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR65_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR65_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR65_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR66_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR66_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR66_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR66_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR67_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR67_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR67_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR67_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR68_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR68_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR68_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR68_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR69_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR69_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR69_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR69_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR70_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR70_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR70_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR70_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR71_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR71_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR71_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR71_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR72_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR72_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR72_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR72_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR73_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR73_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR73_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR73_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR74_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR74_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR74_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR74_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR75_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR75_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR75_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR75_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR76_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR76_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR76_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR76_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR77_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR77_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR77_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR77_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR78_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR78_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR78_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR78_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR79_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR79_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR79_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR79_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR80_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR80_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR80_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR80_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR81_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR81_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR81_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR81_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR82_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR82_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR82_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR82_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR83_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR83_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR83_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR83_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR84_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR84_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR84_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR84_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR85_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR85_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR85_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR85_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR86_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR86_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR86_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR86_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR87_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR87_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR87_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR87_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR88_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR88_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR88_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR88_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR89_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR89_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR89_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR89_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR90_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR90_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR90_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR90_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR91_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR91_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR91_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR91_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR92_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR92_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR92_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR92_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR93_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR93_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR93_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR93_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR94_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR94_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR94_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR94_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR95_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR95_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR95_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR95_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR96_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR96_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR96_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR96_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR97_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR97_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR97_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR97_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR98_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR98_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR98_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR98_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR99_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR99_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR99_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR99_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR100_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR100_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR100_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR100_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR101_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR101_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR101_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR101_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR102_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR102_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR102_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR102_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR103_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR103_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR103_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR103_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR104_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR104_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR104_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR104_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR105_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR105_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR105_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR105_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR106_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR106_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR106_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR106_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR107_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR107_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR107_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR107_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR108_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR108_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR108_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR108_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR109_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR109_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR109_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR109_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR110_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR110_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR110_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR110_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR111_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR111_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR111_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR111_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR112_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR112_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR112_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR112_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR113_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR113_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR113_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR113_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR114_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR114_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR114_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR114_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR115_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR115_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR115_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR115_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR116_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR116_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR116_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR116_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR117_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR117_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR117_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR117_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR118_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR118_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR118_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR118_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR119_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR119_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR119_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR119_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR120_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR120_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR120_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR120_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR121_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR121_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR121_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR121_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR122_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR122_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR122_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR122_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR123_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR123_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR123_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR123_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR124_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR124_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR124_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR124_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR125_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR125_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR125_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR125_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR126_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR126_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR126_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR126_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR127_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR127_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR127_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR127_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR128_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR128_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR128_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR128_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR129_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR129_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR129_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR129_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR130_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR130_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR130_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR130_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR131_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR131_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR131_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR131_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR132_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR132_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR132_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR132_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR133_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR133_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR133_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR133_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR134_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR134_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR134_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR134_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR135_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR135_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR135_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR135_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR136_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR136_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR136_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR136_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR137_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR137_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR137_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR137_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR138_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR138_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR138_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR138_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR139_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR139_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR139_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR139_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR140_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR140_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR140_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR140_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR141_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR141_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR141_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR141_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR142_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR142_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR142_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR142_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR143_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR143_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR143_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR143_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR144_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR144_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR144_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR144_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR145_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR145_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR145_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR145_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR146_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR146_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR146_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR146_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR147_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR147_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR147_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR147_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR148_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR148_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR148_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR148_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR149_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR149_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR149_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR149_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR150_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR150_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR150_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR150_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR151_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR151_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR151_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR151_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR152_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR152_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR152_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR152_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR153_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR153_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR153_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR153_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR154_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR154_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR154_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR154_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR155_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR155_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR155_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR155_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR156_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR156_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR156_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR156_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR157_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR157_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR157_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR157_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR158_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR158_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR158_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR158_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR159_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR159_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR159_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR159_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR160_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR160_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR160_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR160_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR161_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR161_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR161_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR161_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR162_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR162_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR162_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR162_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR163_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR163_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR163_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR163_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR164_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR164_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR164_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR164_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR165_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR165_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR165_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR165_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR166_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR166_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR166_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR166_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR167_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR167_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR167_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR167_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR168_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR168_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR168_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR168_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR169_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR169_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR169_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR169_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR170_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR170_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR170_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR170_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR171_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR171_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR171_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR171_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR172_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR172_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR172_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR172_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR173_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR173_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR173_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR173_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR174_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR174_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR174_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR174_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR175_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR175_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR175_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR175_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR176_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR176_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR176_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR176_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR177_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR177_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR177_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR177_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR178_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR178_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR178_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR178_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR179_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR179_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR179_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR179_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR180_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR180_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR180_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR180_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR181_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR181_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR181_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR181_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR182_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR182_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR182_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR182_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR183_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR183_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR183_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR183_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR184_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR184_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR184_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR184_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR185_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR185_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR185_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR185_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR186_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR186_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR186_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR186_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR187_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR187_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR187_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR187_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR188_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR188_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR188_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR188_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR189_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR189_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR189_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR189_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR190_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR190_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR190_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR190_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR191_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR191_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR191_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR191_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR192_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR192_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR192_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR192_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR193_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR193_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR193_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR193_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR194_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR194_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR194_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR194_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR195_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR195_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR195_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR195_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR196_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR196_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR196_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR196_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR197_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR197_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR197_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR197_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR198_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR198_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR198_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR198_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR199_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR199_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR199_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR199_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR200_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR200_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR200_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR200_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR201_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR201_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR201_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR201_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR202_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR202_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR202_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR202_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR203_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR203_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR203_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR203_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR204_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR204_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR204_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR204_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR205_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR205_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR205_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR205_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR206_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR206_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR206_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR206_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR207_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR207_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR207_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR207_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR208_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR208_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR208_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR208_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR209_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR209_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR209_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR209_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR210_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR210_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR210_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR210_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR211_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR211_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR211_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR211_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR212_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR212_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR212_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR212_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR213_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR213_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR213_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR213_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR214_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR214_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR214_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR214_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR215_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR215_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR215_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR215_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR216_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR216_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR216_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR216_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR217_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR217_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR217_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR217_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR218_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR218_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR218_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR218_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR219_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR219_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR219_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR219_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR220_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR220_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR220_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR220_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR221_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR221_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR221_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR221_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR222_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR222_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR222_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR222_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR223_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR223_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR223_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR223_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR224_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR224_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR224_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR224_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR225_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR225_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR225_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR225_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR226_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR226_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR226_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR226_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR227_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR227_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR227_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR227_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR228_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR228_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR228_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR228_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR229_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR229_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR229_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR229_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR230_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR230_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR230_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR230_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR231_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR231_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR231_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR231_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR232_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR232_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR232_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR232_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR233_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR233_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR233_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR233_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR234_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR234_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR234_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR234_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR235_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR235_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR235_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR235_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR236_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR236_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR236_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR236_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR237_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR237_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR237_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR237_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR238_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR238_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR238_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR238_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR239_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR239_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR239_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR239_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR240_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR240_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR240_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR240_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR241_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR241_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR241_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR241_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR242_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR242_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR242_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR242_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR243_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR243_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR243_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR243_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR244_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR244_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR244_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR244_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR245_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR245_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR245_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR245_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR246_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR246_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR246_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR246_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR247_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR247_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR247_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR247_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR248_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR248_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR248_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR248_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR249_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR249_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR249_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR249_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR250_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR250_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR250_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR250_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR251_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR251_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR251_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR251_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR252_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR252_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR252_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR252_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR253_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR253_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR253_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR253_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR254_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR254_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR254_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR254_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DAR255_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR255_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DAR255_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DAR255_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CSW_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CSW_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CSW_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CSW_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_TAR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_TAR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_TAR_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_TAR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DRW_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DRW_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DRW_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DRW_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_BD0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_BD0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_BD0_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_BD0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_BD1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_BD1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_BD1_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_BD1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_BD2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_BD2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_BD2_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_BD2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_BD3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_BD3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_BD3_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_BD3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_TRR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_TRR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_TRR_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_TRR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CFG1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CFG1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CFG1_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CFG_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CFG_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CFG_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_BASE_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_BASE_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_BASE_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_BASE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_IDR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_IDR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_IDR_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_IDR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_ITSTAT_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_ITSTAT_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_ITSTAT_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_ITSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_ITCTRL_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_ITCTRL_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_ITCTRL_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_ITCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CLAIMSET_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CLAIMSET_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CLAIMSET_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CLAIMSET_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CLAIMCLR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CLAIMCLR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CLAIMCLR_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CLAIMCLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_AUTHSTAT_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_AUTHSTAT_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_AUTHSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DEVARCH_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DEVARCH_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DEVARCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_DEVTYPE_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_DEVTYPE_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_DEVTYPE_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_DEVTYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR4_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR4_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR5_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR5_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR6_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR6_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR7_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR7_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_PIDR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_PIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_0_CIDR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_0_CIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR4_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR4_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR4_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR5_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR5_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR5_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR6_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR6_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR6_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR7_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR7_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR7_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR8_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR8_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR8_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR8_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR9_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR9_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR9_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR9_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR10_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR10_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR10_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR10_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR11_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR11_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR11_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR11_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR12_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR12_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR12_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR12_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR13_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR13_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR13_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR13_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR14_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR14_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR14_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR14_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR15_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR15_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR15_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR15_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR16_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR16_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR16_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR16_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR17_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR17_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR17_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR17_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR18_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR18_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR18_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR18_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR19_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR19_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR19_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR19_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR20_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR20_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR20_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR20_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR21_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR21_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR21_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR21_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR22_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR22_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR22_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR22_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR23_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR23_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR23_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR23_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR24_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR24_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR24_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR24_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR25_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR25_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR25_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR25_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR26_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR26_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR26_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR26_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR27_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR27_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR27_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR27_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR28_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR28_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR28_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR28_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR29_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR29_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR29_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR29_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR30_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR30_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR30_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR30_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR31_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR31_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR31_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR31_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR32_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR32_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR32_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR32_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR33_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR33_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR33_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR33_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR34_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR34_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR34_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR34_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR35_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR35_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR35_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR35_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR36_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR36_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR36_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR36_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR37_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR37_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR37_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR37_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR38_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR38_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR38_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR38_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR39_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR39_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR39_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR39_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR40_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR40_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR40_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR40_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR41_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR41_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR41_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR41_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR42_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR42_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR42_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR42_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR43_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR43_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR43_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR43_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR44_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR44_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR44_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR44_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR45_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR45_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR45_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR45_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR46_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR46_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR46_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR46_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR47_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR47_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR47_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR47_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR48_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR48_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR48_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR48_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR49_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR49_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR49_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR49_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR50_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR50_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR50_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR50_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR51_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR51_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR51_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR51_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR52_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR52_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR52_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR52_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR53_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR53_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR53_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR53_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR54_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR54_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR54_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR54_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR55_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR55_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR55_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR55_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR56_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR56_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR56_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR56_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR57_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR57_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR57_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR57_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR58_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR58_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR58_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR58_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR59_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR59_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR59_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR59_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR60_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR60_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR60_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR60_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR61_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR61_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR61_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR61_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR62_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR62_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR62_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR62_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR63_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR63_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR63_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR63_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR64_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR64_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR64_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR64_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR65_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR65_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR65_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR65_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR66_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR66_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR66_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR66_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR67_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR67_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR67_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR67_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR68_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR68_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR68_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR68_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR69_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR69_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR69_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR69_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR70_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR70_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR70_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR70_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR71_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR71_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR71_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR71_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR72_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR72_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR72_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR72_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR73_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR73_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR73_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR73_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR74_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR74_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR74_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR74_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR75_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR75_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR75_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR75_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR76_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR76_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR76_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR76_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR77_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR77_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR77_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR77_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR78_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR78_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR78_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR78_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR79_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR79_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR79_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR79_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR80_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR80_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR80_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR80_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR81_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR81_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR81_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR81_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR82_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR82_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR82_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR82_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR83_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR83_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR83_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR83_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR84_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR84_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR84_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR84_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR85_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR85_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR85_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR85_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR86_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR86_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR86_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR86_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR87_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR87_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR87_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR87_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR88_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR88_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR88_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR88_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR89_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR89_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR89_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR89_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR90_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR90_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR90_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR90_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR91_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR91_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR91_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR91_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR92_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR92_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR92_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR92_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR93_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR93_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR93_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR93_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR94_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR94_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR94_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR94_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR95_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR95_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR95_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR95_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR96_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR96_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR96_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR96_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR97_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR97_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR97_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR97_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR98_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR98_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR98_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR98_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR99_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR99_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR99_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR99_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR100_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR100_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR100_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR100_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR101_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR101_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR101_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR101_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR102_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR102_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR102_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR102_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR103_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR103_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR103_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR103_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR104_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR104_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR104_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR104_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR105_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR105_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR105_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR105_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR106_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR106_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR106_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR106_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR107_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR107_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR107_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR107_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR108_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR108_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR108_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR108_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR109_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR109_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR109_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR109_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR110_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR110_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR110_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR110_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR111_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR111_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR111_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR111_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR112_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR112_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR112_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR112_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR113_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR113_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR113_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR113_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR114_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR114_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR114_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR114_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR115_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR115_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR115_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR115_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR116_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR116_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR116_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR116_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR117_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR117_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR117_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR117_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR118_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR118_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR118_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR118_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR119_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR119_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR119_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR119_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR120_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR120_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR120_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR120_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR121_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR121_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR121_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR121_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR122_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR122_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR122_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR122_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR123_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR123_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR123_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR123_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR124_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR124_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR124_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR124_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR125_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR125_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR125_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR125_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR126_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR126_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR126_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR126_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR127_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR127_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR127_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR127_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR128_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR128_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR128_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR128_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR129_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR129_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR129_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR129_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR130_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR130_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR130_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR130_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR131_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR131_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR131_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR131_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR132_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR132_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR132_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR132_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR133_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR133_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR133_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR133_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR134_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR134_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR134_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR134_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR135_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR135_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR135_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR135_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR136_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR136_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR136_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR136_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR137_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR137_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR137_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR137_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR138_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR138_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR138_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR138_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR139_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR139_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR139_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR139_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR140_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR140_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR140_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR140_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR141_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR141_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR141_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR141_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR142_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR142_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR142_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR142_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR143_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR143_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR143_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR143_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR144_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR144_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR144_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR144_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR145_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR145_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR145_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR145_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR146_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR146_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR146_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR146_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR147_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR147_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR147_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR147_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR148_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR148_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR148_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR148_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR149_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR149_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR149_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR149_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR150_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR150_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR150_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR150_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR151_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR151_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR151_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR151_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR152_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR152_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR152_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR152_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR153_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR153_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR153_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR153_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR154_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR154_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR154_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR154_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR155_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR155_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR155_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR155_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR156_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR156_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR156_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR156_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR157_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR157_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR157_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR157_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR158_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR158_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR158_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR158_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR159_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR159_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR159_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR159_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR160_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR160_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR160_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR160_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR161_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR161_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR161_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR161_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR162_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR162_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR162_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR162_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR163_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR163_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR163_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR163_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR164_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR164_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR164_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR164_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR165_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR165_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR165_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR165_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR166_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR166_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR166_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR166_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR167_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR167_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR167_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR167_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR168_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR168_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR168_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR168_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR169_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR169_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR169_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR169_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR170_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR170_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR170_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR170_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR171_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR171_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR171_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR171_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR172_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR172_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR172_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR172_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR173_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR173_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR173_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR173_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR174_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR174_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR174_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR174_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR175_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR175_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR175_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR175_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR176_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR176_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR176_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR176_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR177_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR177_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR177_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR177_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR178_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR178_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR178_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR178_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR179_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR179_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR179_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR179_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR180_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR180_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR180_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR180_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR181_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR181_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR181_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR181_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR182_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR182_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR182_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR182_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR183_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR183_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR183_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR183_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR184_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR184_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR184_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR184_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR185_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR185_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR185_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR185_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR186_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR186_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR186_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR186_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR187_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR187_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR187_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR187_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR188_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR188_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR188_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR188_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR189_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR189_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR189_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR189_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR190_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR190_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR190_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR190_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR191_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR191_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR191_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR191_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR192_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR192_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR192_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR192_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR193_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR193_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR193_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR193_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR194_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR194_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR194_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR194_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR195_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR195_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR195_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR195_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR196_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR196_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR196_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR196_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR197_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR197_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR197_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR197_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR198_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR198_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR198_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR198_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR199_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR199_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR199_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR199_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR200_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR200_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR200_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR200_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR201_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR201_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR201_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR201_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR202_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR202_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR202_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR202_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR203_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR203_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR203_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR203_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR204_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR204_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR204_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR204_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR205_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR205_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR205_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR205_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR206_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR206_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR206_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR206_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR207_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR207_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR207_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR207_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR208_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR208_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR208_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR208_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR209_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR209_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR209_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR209_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR210_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR210_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR210_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR210_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR211_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR211_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR211_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR211_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR212_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR212_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR212_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR212_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR213_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR213_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR213_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR213_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR214_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR214_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR214_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR214_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR215_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR215_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR215_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR215_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR216_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR216_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR216_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR216_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR217_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR217_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR217_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR217_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR218_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR218_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR218_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR218_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR219_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR219_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR219_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR219_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR220_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR220_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR220_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR220_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR221_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR221_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR221_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR221_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR222_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR222_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR222_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR222_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR223_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR223_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR223_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR223_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR224_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR224_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR224_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR224_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR225_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR225_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR225_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR225_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR226_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR226_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR226_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR226_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR227_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR227_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR227_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR227_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR228_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR228_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR228_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR228_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR229_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR229_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR229_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR229_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR230_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR230_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR230_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR230_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR231_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR231_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR231_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR231_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR232_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR232_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR232_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR232_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR233_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR233_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR233_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR233_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR234_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR234_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR234_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR234_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR235_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR235_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR235_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR235_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR236_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR236_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR236_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR236_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR237_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR237_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR237_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR237_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR238_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR238_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR238_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR238_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR239_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR239_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR239_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR239_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR240_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR240_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR240_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR240_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR241_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR241_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR241_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR241_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR242_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR242_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR242_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR242_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR243_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR243_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR243_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR243_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR244_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR244_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR244_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR244_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR245_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR245_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR245_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR245_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR246_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR246_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR246_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR246_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR247_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR247_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR247_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR247_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR248_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR248_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR248_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR248_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR249_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR249_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR249_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR249_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR250_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR250_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR250_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR250_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR251_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR251_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR251_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR251_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR252_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR252_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR252_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR252_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR253_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR253_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR253_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR253_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR254_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR254_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR254_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR254_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DAR255_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR255_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DAR255_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DAR255_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CSW_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CSW_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CSW_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CSW_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_TAR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_TAR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_TAR_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_TAR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DRW_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DRW_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DRW_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DRW_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_BD0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_BD0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_BD0_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_BD0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_BD1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_BD1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_BD1_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_BD1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_BD2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_BD2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_BD2_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_BD2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_BD3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_BD3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_BD3_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_BD3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_TRR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_TRR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_TRR_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_TRR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CFG1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CFG1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CFG1_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CFG1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CFG_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CFG_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CFG_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_BASE_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_BASE_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_BASE_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_BASE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_IDR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_IDR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_IDR_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_IDR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_ITSTAT_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_ITSTAT_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_ITSTAT_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_ITSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_ITCTRL_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_ITCTRL_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_ITCTRL_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_ITCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CLAIMSET_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CLAIMSET_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CLAIMSET_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CLAIMSET_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CLAIMCLR_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CLAIMCLR_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CLAIMCLR_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CLAIMCLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_AUTHSTAT_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_AUTHSTAT_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_AUTHSTAT_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_AUTHSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DEVARCH_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DEVARCH_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DEVARCH_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DEVARCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_DEVTYPE_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_DEVTYPE_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_DEVTYPE_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_DEVTYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR4_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR4_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR4_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR5_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR5_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR5_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR6_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR6_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR6_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR7_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR7_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR7_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_PIDR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_PIDR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_PIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CIDR0_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR0_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR0_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CIDR1_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR1_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR1_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CIDR2_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR2_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR2_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_AXIAP_ADDRBLK_1_CIDR3_OFFSET, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR3_DEFAULT, \
                                    CSS600_AXIAP_ADDRBLK_1_CIDR3_RD_MASK, "CSS600_AXIAP_ADDRBLK_1_CIDR3_OFFSET");

    }

}
