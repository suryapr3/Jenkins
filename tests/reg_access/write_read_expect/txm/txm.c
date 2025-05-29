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
    TRX_ANT0_TXM0_BASE, TRX_ANT0_TXM1_BASE, TRX_ANT1_TXM0_BASE, TRX_ANT1_TXM1_BASE, TRX_ANT2_TXM0_BASE,
    TRX_ANT2_TXM1_BASE, TRX_ANT3_TXM0_BASE, TRX_ANT3_TXM1_BASE, TRX_ANT4_TXM0_BASE, TRX_ANT4_TXM1_BASE,
    TRX_ANT5_TXM0_BASE, TRX_ANT5_TXM1_BASE, TRX_ANT6_TXM0_BASE, TRX_ANT6_TXM1_BASE, TRX_ANT7_TXM0_BASE,
    TRX_ANT7_TXM1_BASE
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
			write_read_expect_18a(base_address[i]+TXM_EN_OFFSET, \
                                    TXM_EN_DEFAULT, write_data, expected_data, \
                                    0x1f, 0x1f, \
                                    "TXM_EN_OFFSET");
									
            write_read_expect_18a(base_address[i]+TXM_SCRATCH_OFFSET, \
                                    TXM_SCRATCH_DEFAULT, write_data, expected_data, \
                                    TXM_SCRATCH_RD_MASK, TXM_SCRATCH_WR_MASK, \
                                    "TXM_SCRATCH_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_PEAK_VAL_INTERVAL_OFFSET, \
                                    TXM_PEAK_VAL_INTERVAL_DEFAULT, write_data, expected_data, \
                                    TXM_PEAK_VAL_INTERVAL_RD_MASK, TXM_PEAK_VAL_INTERVAL_WR_MASK, \
                                    "TXM_PEAK_VAL_INTERVAL_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_PEAK_VAL_LIMIT_OFFSET, \
                                    TXM_PEAK_VAL_LIMIT_DEFAULT, write_data, expected_data, \
                                    TXM_PEAK_VAL_LIMIT_RD_MASK, TXM_PEAK_VAL_LIMIT_WR_MASK, \
                                    "TXM_PEAK_VAL_LIMIT_OFFSET");

          

            write_read_expect_18a(base_address[i]+TXM_PEAK_VAL_MEAS_OUT_OFFSET, \
                                    TXM_PEAK_VAL_MEAS_OUT_DEFAULT, write_data, expected_data, \
                                    TXM_PEAK_VAL_MEAS_OUT_RD_MASK, TXM_PEAK_VAL_MEAS_OUT_WR_MASK, \
                                    "TXM_PEAK_VAL_MEAS_OUT_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_PEAK_VAL_ALARM_CNT_OFFSET, \
                                    TXM_PEAK_VAL_ALARM_CNT_DEFAULT, write_data, expected_data, \
                                    TXM_PEAK_VAL_ALARM_CNT_RD_MASK, TXM_PEAK_VAL_ALARM_CNT_WR_MASK, \
                                    "TXM_PEAK_VAL_ALARM_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_CLR_OFFSET, \
                                    TXM_GLOBAL_PEAK_CLR_DEFAULT, write_data, expected_data, \
                                    TXM_GLOBAL_PEAK_CLR_RD_MASK, TXM_GLOBAL_PEAK_CLR_WR_MASK, \
                                    "TXM_GLOBAL_PEAK_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_VAL_MEAS_OFFSET, \
                                    TXM_GLOBAL_PEAK_VAL_MEAS_DEFAULT, write_data, expected_data, \
                                    TXM_GLOBAL_PEAK_VAL_MEAS_RD_MASK, TXM_GLOBAL_PEAK_VAL_MEAS_WR_MASK, \
                                    "TXM_GLOBAL_PEAK_VAL_MEAS_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_BFN_CNT_OFFSET, \
                                    TXM_GLOBAL_PEAK_BFN_CNT_DEFAULT, write_data, expected_data, \
                                    TXM_GLOBAL_PEAK_BFN_CNT_RD_MASK, TXM_GLOBAL_PEAK_BFN_CNT_WR_MASK, \
                                    "TXM_GLOBAL_PEAK_BFN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_PEAK_DBG_OFFSET, \
                                    TXM_PEAK_DBG_DEFAULT, write_data, expected_data, \
                                    TXM_PEAK_DBG_RD_MASK, TXM_PEAK_DBG_WR_MASK, \
                                    "TXM_PEAK_DBG_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_INT_STAT_OFFSET, \
                                    TXM_INT_STAT_DEFAULT, write_data, expected_data, \
                                    TXM_INT_STAT_RD_MASK, TXM_INT_STAT_WR_MASK, \
                                    "TXM_INT_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_INT_HI_EN_OFFSET, \
                                    TXM_INT_HI_EN_DEFAULT, write_data, expected_data, \
                                    TXM_INT_HI_EN_RD_MASK, TXM_INT_HI_EN_WR_MASK, \
                                    "TXM_INT_HI_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_INT_LO_EN_OFFSET, \
                                    TXM_INT_LO_EN_DEFAULT, write_data, expected_data, \
                                    TXM_INT_LO_EN_RD_MASK, TXM_INT_LO_EN_WR_MASK, \
                                    "TXM_INT_LO_EN_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_INT_CLR_OFFSET, \
                                    TXM_INT_CLR_DEFAULT, write_data, expected_data, \
                                    TXM_INT_CLR_RD_MASK, TXM_INT_CLR_WR_MASK, \
                                    "TXM_INT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+TXM_INT_FORCE_OFFSET, \
                                    TXM_INT_FORCE_DEFAULT, write_data, expected_data, \
                                    TXM_INT_FORCE_RD_MASK, TXM_INT_FORCE_WR_MASK, \
                                    "TXM_INT_FORCE_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//            write_read_expect_18a(base_address[i]+TXM_APB_BRDG_STAT_OFFSET, \
                                    TXM_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    TXM_APB_BRDG_STAT_RD_MASK, TXM_APB_BRDG_STAT_WR_MASK, \
                                    "TXM_APB_BRDG_STAT_OFFSET");

        }

    }

}
