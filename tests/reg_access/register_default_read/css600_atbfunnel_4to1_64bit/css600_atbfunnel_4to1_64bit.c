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
    VEXARRAYCS16_00_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_01_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_10_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_11_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_20_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE,
    VEXARRAYCS16_21_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_30_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_31_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE, RCS_CS_FUNNEL4TO1_64BIT_APB4_SLAVE_0_MM_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_FUNNELCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_FUNNELCTRL_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_FUNNELCTRL_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_FUNNELCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBDATA0_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBDATA0_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBDATA0_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR3_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR3_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR3_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR2_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR2_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR2_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR1_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR1_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR1_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR0_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR0_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR0_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITATBCTR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITCTRL_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITCTRL_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_ITCTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMSET_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMSET_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMSET_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMSET_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMCLR_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMCLR_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMCLR_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CLAIMCLR_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF0_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF0_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF0_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF1_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF1_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF1_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVAFF1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_AUTHSTAT_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_AUTHSTAT_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_AUTHSTAT_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVARCH_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVARCH_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVARCH_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID2_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID2_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID2_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID1_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID1_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID1_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVID_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVTYPE_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVTYPE_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVTYPE_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_DEVTYPE_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR4_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR4_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR5_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR5_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR6_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR6_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR7_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR7_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR0_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR0_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR1_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR1_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR2_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR2_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR3_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR3_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_PIDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR0_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR0_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR1_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR1_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR2_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR2_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR3_DEFAULT, \
                                    CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR3_RD_MASK, "CSS600_ATBFUNNEL_4TO1_64BIT_ADDRBLK_0_CIDR3_OFFSET");

    }

}
