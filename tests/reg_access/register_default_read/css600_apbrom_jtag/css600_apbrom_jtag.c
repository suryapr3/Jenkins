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
    SYSCON_CS_SOC_APBROM_APB4_SLAVE_0_MM_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY8_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY9_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY10_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY11_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY12_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY13_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY14_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY15_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY16_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY17_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY18_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY19_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY20_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY21_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY22_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY23_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY24_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY25_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY26_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY27_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY28_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY29_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY30_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY31_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY32_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY33_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY34_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY35_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY36_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY37_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY38_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY39_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY40_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY41_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY42_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY43_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY44_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY45_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY46_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY47_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY48_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY49_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY50_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY51_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY52_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY53_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY54_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY55_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY56_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY57_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY58_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY59_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY60_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY61_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY62_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY63_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY64_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY65_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY66_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY67_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY68_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY69_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY70_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY71_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY72_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY73_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY74_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY75_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY76_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY77_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY78_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY79_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY80_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY81_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY82_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY83_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY84_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY85_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY86_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY87_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY88_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY89_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY90_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY91_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY92_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY93_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY94_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY95_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY96_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY97_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY98_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY99_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY100_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY101_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY102_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY103_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY104_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY105_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY106_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY107_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY108_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY109_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY110_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY111_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY112_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY113_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY114_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY115_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY116_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY117_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY118_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY119_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY120_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY121_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY122_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY123_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY124_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY125_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY126_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY127_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY128_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY129_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY130_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY131_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY132_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY133_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY134_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY135_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY136_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY137_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY138_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY139_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY140_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY141_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY142_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY143_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY144_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY145_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY146_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY147_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY148_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY149_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY150_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY151_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY152_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY153_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY154_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY155_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY156_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY157_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY158_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY159_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY160_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY161_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY162_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY163_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY164_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY165_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY166_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY167_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY168_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY169_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY170_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY171_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY172_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY173_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY174_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY175_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY176_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY177_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY178_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY179_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY180_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY181_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY182_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY183_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY184_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY185_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY186_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY187_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY188_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY189_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY190_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY191_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY192_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY193_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY194_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY195_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY196_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY197_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY198_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY199_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY200_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY201_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY202_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY203_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY204_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY205_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY206_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY207_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY208_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY209_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY210_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY211_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY212_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY213_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY214_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY215_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY216_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY217_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY218_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY219_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY220_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY221_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY222_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY223_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY224_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY225_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY226_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY227_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY228_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY229_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY230_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY231_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY232_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY233_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY234_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY235_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY236_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY237_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY238_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY239_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY240_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY241_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY242_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY243_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY244_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY245_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY246_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY247_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY248_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY249_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY250_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY251_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY252_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY253_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY254_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY255_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY256_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY257_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY258_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY259_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY260_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY261_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY262_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY263_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY264_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY265_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY266_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY267_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY268_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY269_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY270_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY271_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY272_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY273_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY274_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY275_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY276_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY277_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY278_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY279_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY280_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY281_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY282_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY283_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY284_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY285_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY286_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY287_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY288_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY289_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY290_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY291_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY292_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY293_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY294_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY295_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY296_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY297_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY298_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY299_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY300_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY301_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY302_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY303_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY304_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY305_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY306_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY307_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY308_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY309_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY310_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY311_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY312_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY313_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY314_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY315_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY316_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY317_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY318_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY319_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY320_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY321_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY322_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY323_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY324_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY325_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY326_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY327_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY328_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY329_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY330_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY331_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY332_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY333_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY334_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY335_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY336_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY337_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY338_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY339_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY340_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY341_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY342_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY343_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY344_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY345_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY346_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY347_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY348_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY349_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY350_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY351_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY352_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY353_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY354_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY355_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY356_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY357_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY358_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY359_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY360_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY361_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY362_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY363_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY364_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY365_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY366_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY367_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY368_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY369_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY370_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY371_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY372_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY373_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY374_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY375_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY376_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY377_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY378_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY379_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY380_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY381_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY382_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY383_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY384_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY385_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY386_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY387_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY388_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY389_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY390_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY391_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY392_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY393_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY394_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY395_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY396_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY397_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY398_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY399_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY400_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY401_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY402_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY403_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY404_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY405_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY406_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY407_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY408_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY409_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY410_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY411_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY412_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY413_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY414_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY415_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY416_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY417_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY418_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY419_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY420_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY421_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY422_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY423_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY424_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY425_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY426_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY427_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY428_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY429_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY430_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY431_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY432_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY433_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY434_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY435_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY436_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY437_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY438_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY439_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY440_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY441_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY442_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY443_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY444_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY445_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY446_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY447_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY448_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY449_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY450_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY451_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY452_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY453_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY454_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY455_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY456_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY457_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY458_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY459_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY460_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY461_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY462_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY463_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY464_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY465_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY466_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY467_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY468_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY469_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY470_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY471_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY472_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY473_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY474_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY475_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY476_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY477_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY478_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY479_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY480_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY481_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY482_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY483_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY484_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY485_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY486_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY487_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY488_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY489_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY490_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY491_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY492_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY493_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY494_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY495_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY496_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY497_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY498_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY499_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY500_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY501_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY502_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY503_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY504_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY505_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY506_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY507_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY508_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY509_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY510_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_ROMENTRY511_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_AUTHSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_DEVARCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_DEVID_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_PIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_DEFAULT, \
                                    CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_RD_MASK, "CSS600_APBROM_JTAG_ADDRBLK_0_CIDR3_OFFSET");

    }

}
