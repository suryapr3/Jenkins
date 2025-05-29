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
    RCS_CRUX_INTF_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+CRUX_INTF_WDATA0_R_OFFSET, \
                                    CRUX_INTF_WDATA0_R_DEFAULT, \
                                    CRUX_INTF_WDATA0_R_RD_MASK, "CRUX_INTF_WDATA0_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_WDATA1_R_OFFSET, \
                                    CRUX_INTF_WDATA1_R_DEFAULT, \
                                    CRUX_INTF_WDATA1_R_RD_MASK, "CRUX_INTF_WDATA1_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_WDATA2_R_OFFSET, \
                                    CRUX_INTF_WDATA2_R_DEFAULT, \
                                    CRUX_INTF_WDATA2_R_RD_MASK, "CRUX_INTF_WDATA2_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_WDATA3_R_OFFSET, \
                                    CRUX_INTF_WDATA3_R_DEFAULT, \
                                    CRUX_INTF_WDATA3_R_RD_MASK, "CRUX_INTF_WDATA3_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_WROUTING_DATA_R_OFFSET, \
                                    CRUX_INTF_WROUTING_DATA_R_DEFAULT, \
                                    CRUX_INTF_WROUTING_DATA_R_RD_MASK, "CRUX_INTF_WROUTING_DATA_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_TX_PUSH_OFFSET, \
                                    CRUX_INTF_TX_PUSH_DEFAULT, \
                                    CRUX_INTF_TX_PUSH_RD_MASK, "CRUX_INTF_TX_PUSH_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_TX_FIFO_WM_OFFSET, \
                                    CRUX_INTF_TX_FIFO_WM_DEFAULT, \
                                    CRUX_INTF_TX_FIFO_WM_RD_MASK, "CRUX_INTF_TX_FIFO_WM_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_MASKS_OFFSET, \
                                    CRUX_INTF_MASKS_DEFAULT, \
                                    CRUX_INTF_MASKS_RD_MASK, "CRUX_INTF_MASKS_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_FIFO_SW_RST_OFFSET, \
                                    CRUX_INTF_FIFO_SW_RST_DEFAULT, \
                                    CRUX_INTF_FIFO_SW_RST_RD_MASK, "CRUX_INTF_FIFO_SW_RST_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+CRUX_INTF_RX_POP_OFFSET, \
                                    CRUX_INTF_RX_POP_DEFAULT, \
                                    CRUX_INTF_RX_POP_RD_MASK, "CRUX_INTF_RX_POP_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_RDATA0_R_OFFSET, \
                                    CRUX_INTF_RDATA0_R_DEFAULT, \
                                    CRUX_INTF_RDATA0_R_RD_MASK, "CRUX_INTF_RDATA0_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_RDATA1_R_OFFSET, \
                                    CRUX_INTF_RDATA1_R_DEFAULT, \
                                    CRUX_INTF_RDATA1_R_RD_MASK, "CRUX_INTF_RDATA1_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_RDATA2_R_OFFSET, \
                                    CRUX_INTF_RDATA2_R_DEFAULT, \
                                    CRUX_INTF_RDATA2_R_RD_MASK, "CRUX_INTF_RDATA2_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_RDATA3_R_OFFSET, \
                                    CRUX_INTF_RDATA3_R_DEFAULT, \
                                    CRUX_INTF_RDATA3_R_RD_MASK, "CRUX_INTF_RDATA3_R_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+CRUX_INTF_RROUTING_DATA_R_OFFSET, \
                                    CRUX_INTF_RROUTING_DATA_R_DEFAULT, \
                                    CRUX_INTF_RROUTING_DATA_R_RD_MASK, "CRUX_INTF_RROUTING_DATA_R_OFFSET");

        read_reg_expect_18a(base_address[i]+CRUX_INTF_FIFO_STAT_OFFSET, \
                                    CRUX_INTF_FIFO_STAT_DEFAULT, \
                                    CRUX_INTF_FIFO_STAT_RD_MASK, "CRUX_INTF_FIFO_STAT_OFFSET");

    }

}
