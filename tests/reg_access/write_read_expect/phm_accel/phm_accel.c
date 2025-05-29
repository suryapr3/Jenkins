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
    RCS_PHM0_ACCEL0_BASE, RCS_PHM0_ACCEL1_BASE, RCS_PHM0_ACCEL2_BASE, RCS_PHM0_ACCEL3_BASE, RCS_PHM0_ACCEL4_BASE,
    RCS_PHM0_ACCEL5_BASE, RCS_PHM0_ACCEL6_BASE, RCS_PHM0_ACCEL7_BASE, RCS_PHM0_ACCEL8_BASE, RCS_PHM0_ACCEL9_BASE,
    RCS_PHM1_ACCEL0_BASE, RCS_PHM1_ACCEL1_BASE, RCS_PHM1_ACCEL2_BASE, RCS_PHM1_ACCEL3_BASE, RCS_PHM1_ACCEL4_BASE,
    RCS_PHM1_ACCEL5_BASE, RCS_PHM1_ACCEL6_BASE, RCS_PHM1_ACCEL7_BASE, RCS_PHM1_ACCEL8_BASE, RCS_PHM1_ACCEL9_BASE
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
            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD0_OFFSET, \
                                    PHM_ACCEL_TSHOLD_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_RD_MASK, PHM_ACCEL_TSHOLD_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD1_OFFSET, \
                                    PHM_ACCEL_TSHOLD_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_RD_MASK, PHM_ACCEL_TSHOLD_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD1_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD2_OFFSET, \
                                    PHM_ACCEL_TSHOLD_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_RD_MASK, PHM_ACCEL_TSHOLD_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD2_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD3_OFFSET, \
                                    PHM_ACCEL_TSHOLD_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_RD_MASK, PHM_ACCEL_TSHOLD_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD3_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD_CNT0_OFFSET, \
                                    PHM_ACCEL_TSHOLD_CNT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_CNT_RD_MASK, PHM_ACCEL_TSHOLD_CNT_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD_CNT0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD_CNT1_OFFSET, \
                                    PHM_ACCEL_TSHOLD_CNT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_CNT_RD_MASK, PHM_ACCEL_TSHOLD_CNT_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD_CNT1_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD_CNT2_OFFSET, \
                                    PHM_ACCEL_TSHOLD_CNT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_CNT_RD_MASK, PHM_ACCEL_TSHOLD_CNT_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD_CNT2_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_TSHOLD_CNT3_OFFSET, \
                                    PHM_ACCEL_TSHOLD_CNT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_TSHOLD_CNT_RD_MASK, PHM_ACCEL_TSHOLD_CNT_WR_MASK, \
                                    "PHM_ACCEL_TSHOLD_CNT3_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_RSLT0_OFFSET, \
                                    PHM_ACCEL_RSLT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_RSLT_RD_MASK, PHM_ACCEL_RSLT_WR_MASK, \
                                    "PHM_ACCEL_RSLT0_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_RSLT1_OFFSET, \
                                    PHM_ACCEL_RSLT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_RSLT_RD_MASK, PHM_ACCEL_RSLT_WR_MASK, \
                                    "PHM_ACCEL_RSLT1_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_RSLT2_OFFSET, \
                                    PHM_ACCEL_RSLT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_RSLT_RD_MASK, PHM_ACCEL_RSLT_WR_MASK, \
                                    "PHM_ACCEL_RSLT2_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_RSLT3_OFFSET, \
                                    PHM_ACCEL_RSLT_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_RSLT_RD_MASK, PHM_ACCEL_RSLT_WR_MASK, \
                                    "PHM_ACCEL_RSLT3_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_SETUP_OFFSET, \
                                    PHM_ACCEL_SETUP_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_SETUP_RD_MASK, PHM_ACCEL_SETUP_WR_MASK, \
                                    "PHM_ACCEL_SETUP_OFFSET");

            write_read_expect_18a(base_address[i]+PHM_ACCEL_PHM_RD_FIFO_CFG_OFFSET, \
                                    PHM_ACCEL_PHM_RD_FIFO_CFG_DEFAULT, write_data, expected_data, \
                                    PHM_ACCEL_PHM_RD_FIFO_CFG_RD_MASK, PHM_ACCEL_PHM_RD_FIFO_CFG_WR_MASK, \
                                    "PHM_ACCEL_PHM_RD_FIFO_CFG_OFFSET");

        }

    }

}
