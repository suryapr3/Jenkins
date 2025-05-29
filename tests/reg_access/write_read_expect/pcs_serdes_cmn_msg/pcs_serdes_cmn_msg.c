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
    DLNK_JESD0_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD1_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD2_PHY_PCS_SERDES_CMN_BASE, DLNK_JESD3_PHY_PCS_SERDES_CMN_BASE
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
            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_REVISION_OFFSET, \
                                    PCS_SERDES_CMN_MSG_REVISION_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_REVISION_RD_MASK, PCS_SERDES_CMN_MSG_REVISION_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_REVISION_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_JTAG_VER_OFFSET, \
                                    PCS_SERDES_CMN_MSG_JTAG_VER_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_JTAG_VER_RD_MASK, PCS_SERDES_CMN_MSG_JTAG_VER_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_JTAG_VER_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_RD_MASK, PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_SCRATCH_PAD_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_RD_MASK, PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_SCRATCH_PAD_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_0_RD_MASK, PCS_SERDES_CMN_MSG_RW_SPARE_0_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RW_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_1_RD_MASK, PCS_SERDES_CMN_MSG_RW_SPARE_1_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RW_SPARE_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_2_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_2_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_2_RD_MASK, PCS_SERDES_CMN_MSG_RW_SPARE_2_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RW_SPARE_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RW_SPARE_3_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_3_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RW_SPARE_3_RD_MASK, PCS_SERDES_CMN_MSG_RW_SPARE_3_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RW_SPARE_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RO_SPARE_0_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_0_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_0_RD_MASK, PCS_SERDES_CMN_MSG_RO_SPARE_0_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RO_SPARE_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCS_SERDES_CMN_MSG_RO_SPARE_1_OFFSET, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_1_DEFAULT, write_data, expected_data, \
                                    PCS_SERDES_CMN_MSG_RO_SPARE_1_RD_MASK, PCS_SERDES_CMN_MSG_RO_SPARE_1_WR_MASK, \
                                    "PCS_SERDES_CMN_MSG_RO_SPARE_1_OFFSET");

        }

    }

}
