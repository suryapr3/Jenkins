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
    int i,j;
    init();

    uint32_t base_address1[] = {
     FB_ANT0_RXM0_BASE,  FB_ANT0_RXM1_BASE,  FB_ANT1_RXM0_BASE,  FB_ANT1_RXM1_BASE};

     uint32_t base_address2[] = {
     TRX_ANT0_RXM0_BASE, TRX_ANT0_RXM1_BASE,  TRX_ANT1_RXM0_BASE,  TRX_ANT1_RXM1_BASE,  TRX_ANT2_RXM0_BASE,  TRX_ANT2_RXM1_BASE,
     TRX_ANT3_RXM0_BASE,  TRX_ANT3_RXM1_BASE,  TRX_ANT4_RXM0_BASE,  TRX_ANT4_RXM1_BASE,  TRX_ANT5_RXM0_BASE,
     TRX_ANT5_RXM1_BASE,  TRX_ANT6_RXM0_BASE,  TRX_ANT6_RXM1_BASE,  TRX_ANT7_RXM0_BASE,  TRX_ANT7_RXM1_BASE
    };

    uint32_t* base_addresses[] = {base_address1,base_address2};

    int size[] = {sizeof(base_address1)/(sizeof(base_address1[0])*2), sizeof(base_address2)/(sizeof(base_address2[0])*2)};

    for(i=0; i<sizeof(base_addresses) / sizeof(base_addresses[0]); i++)
    {
        for(j=0; j<size[i]; j++)
        {
            read_reg_expect_18a(base_addresses[i][j]+RXM_SCRATCH_OFFSET, \
                                        RXM_SCRATCH_DEFAULT, \
                                        RXM_SCRATCH_RD_MASK, "RXM_SCRATCH_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_PTI_OFFSET, \
                                        RXM_PTI_DEFAULT, \
                                        RXM_PTI_RD_MASK, "RXM_PTI_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_PEAK_INTERVAL_1_OFFSET, \
                                        RXM_PEAK_INTERVAL_1_DEFAULT, \
                                        RXM_PEAK_INTERVAL_1_RD_MASK, "RXM_PEAK_INTERVAL_1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_APWR_INTERVAL_1_OFFSET, \
                                        RXM_APWR_INTERVAL_1_DEFAULT, \
                                        RXM_APWR_INTERVAL_1_RD_MASK, "RXM_APWR_INTERVAL_1_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_SEL_PS_SRC_OFFSET, \
                                        RXM_SEL_PS_SRC_DEFAULT, \
                                        RXM_SEL_PS_SRC_RD_MASK, "RXM_SEL_PS_SRC_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_EN_OFFSET, \
                                        RXM_EN_DEFAULT, \
                                        RXM_EN_RD_MASK, "RXM_EN_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_PVAL_MEAS_OUT_OFFSET, \
                                        RXM_PVAL_MEAS_OUT_DEFAULT, \
                                        RXM_PVAL_MEAS_OUT_RD_MASK, "RXM_PVAL_MEAS_OUT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_APWR_MEAS_OUT_OFFSET, \
                                        RXM_APWR_MEAS_OUT_DEFAULT, \
                                        RXM_APWR_MEAS_OUT_RD_MASK, "RXM_APWR_MEAS_OUT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_PTI_ALARM_CNT_OFFSET, \
                                        RXM_PTI_ALARM_CNT_DEFAULT, \
                                        RXM_PTI_ALARM_CNT_RD_MASK, "RXM_PTI_ALARM_CNT_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_PEAK_DBG_OFFSET, \
                                        RXM_PEAK_DBG_DEFAULT, \
                                        RXM_PEAK_DBG_RD_MASK, "RXM_PEAK_DBG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_APWR_DBG_OFFSET, \
                                        RXM_APWR_DBG_DEFAULT, \
                                        RXM_APWR_DBG_RD_MASK, "RXM_APWR_DBG_OFFSET");

            read_reg_expect_18a(base_addresses[i][j]+RXM_APB_BRDG_STAT_OFFSET, \
                                        RXM_APB_BRDG_STAT_DEFAULT, \
                                        RXM_APB_BRDG_STAT_RD_MASK, "RXM_APB_BRDG_STAT_OFFSET");
        }

    }

}
