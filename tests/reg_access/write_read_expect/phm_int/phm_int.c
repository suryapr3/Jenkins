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
    RCS_PHM0_INT_BASE, RCS_PHM1_INT_BASE
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
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case			
//            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_STAT_7_0_OFFSET, \
                                    PHM_INT_EDGE_IRQ_STAT_7_0_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_STAT_7_0_RD_MASK, PHM_INT_EDGE_IRQ_STAT_7_0_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_STAT_7_0_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_STAT_15_8_OFFSET, \
                                    PHM_INT_EDGE_IRQ_STAT_15_8_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_STAT_15_8_RD_MASK, PHM_INT_EDGE_IRQ_STAT_15_8_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_STAT_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_MASK_7_0_OFFSET, \
                                    PHM_INT_EDGE_IRQ_MASK_7_0_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_MASK_7_0_RD_MASK, PHM_INT_EDGE_IRQ_MASK_7_0_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_MASK_7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_MASK_15_8_OFFSET, \
                                    PHM_INT_EDGE_IRQ_MASK_15_8_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_MASK_15_8_RD_MASK, PHM_INT_EDGE_IRQ_MASK_15_8_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_MASK_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_INV_7_0_OFFSET, \
                                    PHM_INT_EDGE_IRQ_INV_7_0_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_INV_7_0_RD_MASK, PHM_INT_EDGE_IRQ_INV_7_0_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_INV_7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_INV_15_8_OFFSET, \
                                    PHM_INT_EDGE_IRQ_INV_15_8_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_INV_15_8_RD_MASK, PHM_INT_EDGE_IRQ_INV_15_8_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_INV_15_8_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_NOMASK_7_0_OFFSET, \
                                    PHM_INT_EDGE_IRQ_NOMASK_7_0_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_NOMASK_7_0_RD_MASK, PHM_INT_EDGE_IRQ_NOMASK_7_0_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_NOMASK_7_0_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_NOMASK_15_8_OFFSET, \
                                    PHM_INT_EDGE_IRQ_NOMASK_15_8_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_NOMASK_15_8_RD_MASK, PHM_INT_EDGE_IRQ_NOMASK_15_8_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_NOMASK_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_RAW_7_0_OFFSET, \
                                    PHM_INT_EDGE_IRQ_RAW_7_0_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_RAW_7_0_RD_MASK, PHM_INT_EDGE_IRQ_RAW_7_0_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_RAW_7_0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_EDGE_IRQ_RAW_15_8_OFFSET, \
                                    PHM_INT_EDGE_IRQ_RAW_15_8_DEFAULT, write_data, expected_data, \
                                    PHM_INT_EDGE_IRQ_RAW_15_8_RD_MASK, PHM_INT_EDGE_IRQ_RAW_15_8_WR_MASK, \
                                    "PHM_INT_EDGE_IRQ_RAW_15_8_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_PHM_RD_FIFO_STAT_OFFSET, \
                                    PHM_INT_PHM_RD_FIFO_STAT_DEFAULT, write_data, expected_data, \
                                    PHM_INT_PHM_RD_FIFO_STAT_RD_MASK, PHM_INT_PHM_RD_FIFO_STAT_WR_MASK, \
                                    "PHM_INT_PHM_RD_FIFO_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_INT_PHM_RD_FIFO_INT_EN_OFFSET, \
                                    PHM_INT_PHM_RD_FIFO_INT_EN_DEFAULT, write_data, expected_data, \
                                    PHM_INT_PHM_RD_FIFO_INT_EN_RD_MASK, PHM_INT_PHM_RD_FIFO_INT_EN_WR_MASK, \
                                    "PHM_INT_PHM_RD_FIFO_INT_EN_OFFSET");

        }

    }

}
