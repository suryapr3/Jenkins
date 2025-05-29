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
    VEXARRAYCS16_00_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_01_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_0_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_0_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_1_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE,
    VEXARRAYCS8_1_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_2_FUNNEL2TO1_64BIT0_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_2_FUNNEL2TO1_64BIT1_APB4_SLAVE_0_MM_BASE, VEXARRAYCS8_3_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_10_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE,
    VEXARRAYCS16_11_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_20_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE, VEXARRAYCS16_21_FUNNEL2TO1_64BIT_APB4_SLAVE_0_MM_BASE
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
            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_FUNNELCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PRIORITYCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBDATA0_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBDATA0_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBDATA0_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBDATA0_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBDATA0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR3_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR3_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR3_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR3_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR2_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR2_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR2_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR2_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR1_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR1_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR1_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR1_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR0_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR0_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR0_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR0_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITATBCTR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITCTRL_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITCTRL_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITCTRL_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITCTRL_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_ITCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMSET_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMSET_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMSET_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMSET_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMSET_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMCLR_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMCLR_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMCLR_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMCLR_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CLAIMCLR_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF0_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF0_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF0_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF0_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF1_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF1_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF1_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF1_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVAFF1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_AUTHSTAT_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_AUTHSTAT_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_AUTHSTAT_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_AUTHSTAT_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_AUTHSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVARCH_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVARCH_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVARCH_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVARCH_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVARCH_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID2_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID2_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID2_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID2_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID1_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID1_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID1_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID1_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVID_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVTYPE_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVTYPE_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVTYPE_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVTYPE_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_DEVTYPE_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR4_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR4_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR4_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR4_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR4_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR5_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR5_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR5_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR5_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR5_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR6_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR6_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR6_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR6_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR6_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR7_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR7_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR7_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR7_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR7_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR0_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR0_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR0_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR1_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR1_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR1_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR2_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR2_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR2_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR3_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR3_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR3_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_PIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR0_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR0_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR0_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR0_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR1_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR1_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR1_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR1_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR2_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR2_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR2_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR2_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR3_OFFSET, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR3_DEFAULT, write_data, expected_data, \
                                    CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR3_RD_MASK, CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR3_WR_MASK, \
                                    "CSS600_ATBFUNNEL_2TO1_64BIT_ADDRBLK_0_CIDR3_OFFSET");

        }

    }

}
