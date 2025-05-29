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
    TRX_ANT0_TXM0_BASE, TRX_ANT0_TXM1_BASE, TRX_ANT1_TXM0_BASE, TRX_ANT1_TXM1_BASE, TRX_ANT2_TXM0_BASE,
    TRX_ANT2_TXM1_BASE, TRX_ANT3_TXM0_BASE, TRX_ANT3_TXM1_BASE, TRX_ANT4_TXM0_BASE, TRX_ANT4_TXM1_BASE,
    TRX_ANT5_TXM0_BASE, TRX_ANT5_TXM1_BASE, TRX_ANT6_TXM0_BASE, TRX_ANT6_TXM1_BASE, TRX_ANT7_TXM0_BASE,
    TRX_ANT7_TXM1_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+TXM_SCRATCH_OFFSET, \
                                    TXM_SCRATCH_DEFAULT, \
                                    TXM_SCRATCH_RD_MASK, "TXM_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_PEAK_VAL_INTERVAL_OFFSET, \
                                    TXM_PEAK_VAL_INTERVAL_DEFAULT, \
                                    TXM_PEAK_VAL_INTERVAL_RD_MASK, "TXM_PEAK_VAL_INTERVAL_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_PEAK_VAL_LIMIT_OFFSET, \
                                    TXM_PEAK_VAL_LIMIT_DEFAULT, \
                                    TXM_PEAK_VAL_LIMIT_RD_MASK, "TXM_PEAK_VAL_LIMIT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_EN_OFFSET, \
                                    TXM_EN_DEFAULT, \
                                    TXM_EN_RD_MASK, "TXM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_PEAK_VAL_MEAS_OUT_OFFSET, \
                                    TXM_PEAK_VAL_MEAS_OUT_DEFAULT, \
                                    TXM_PEAK_VAL_MEAS_OUT_RD_MASK, "TXM_PEAK_VAL_MEAS_OUT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_PEAK_VAL_ALARM_CNT_OFFSET, \
                                    TXM_PEAK_VAL_ALARM_CNT_DEFAULT, \
                                    TXM_PEAK_VAL_ALARM_CNT_RD_MASK, "TXM_PEAK_VAL_ALARM_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_CLR_OFFSET, \
                                    TXM_GLOBAL_PEAK_CLR_DEFAULT, \
                                    TXM_GLOBAL_PEAK_CLR_RD_MASK, "TXM_GLOBAL_PEAK_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_VAL_MEAS_OFFSET, \
                                    TXM_GLOBAL_PEAK_VAL_MEAS_DEFAULT, \
                                    TXM_GLOBAL_PEAK_VAL_MEAS_RD_MASK, "TXM_GLOBAL_PEAK_VAL_MEAS_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_GLOBAL_PEAK_BFN_CNT_OFFSET, \
                                    TXM_GLOBAL_PEAK_BFN_CNT_DEFAULT, \
                                    TXM_GLOBAL_PEAK_BFN_CNT_RD_MASK, "TXM_GLOBAL_PEAK_BFN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_PEAK_DBG_OFFSET, \
                                    TXM_PEAK_DBG_DEFAULT, \
                                    TXM_PEAK_DBG_RD_MASK, "TXM_PEAK_DBG_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_INT_STAT_OFFSET, \
                                    TXM_INT_STAT_DEFAULT, \
                                    TXM_INT_STAT_RD_MASK, "TXM_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_INT_HI_EN_OFFSET, \
                                    TXM_INT_HI_EN_DEFAULT, \
                                    TXM_INT_HI_EN_RD_MASK, "TXM_INT_HI_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_INT_LO_EN_OFFSET, \
                                    TXM_INT_LO_EN_DEFAULT, \
                                    TXM_INT_LO_EN_RD_MASK, "TXM_INT_LO_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_INT_CLR_OFFSET, \
                                    TXM_INT_CLR_DEFAULT, \
                                    TXM_INT_CLR_RD_MASK, "TXM_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_INT_FORCE_OFFSET, \
                                    TXM_INT_FORCE_DEFAULT, \
                                    TXM_INT_FORCE_RD_MASK, "TXM_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+TXM_APB_BRDG_STAT_OFFSET, \
                                    TXM_APB_BRDG_STAT_DEFAULT, \
                                    TXM_APB_BRDG_STAT_RD_MASK, "TXM_APB_BRDG_STAT_OFFSET");

    }

}
