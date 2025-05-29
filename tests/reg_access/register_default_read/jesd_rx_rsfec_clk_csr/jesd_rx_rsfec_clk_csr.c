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
    DLNK_JESD0_RX_RSFEC_CLK_CSR_BASE, DLNK_JESD1_RX_RSFEC_CLK_CSR_BASE, DLNK_JESD2_RX_RSFEC_CLK_CSR_BASE, DLNK_JESD3_RX_RSFEC_CLK_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_SCRATCH_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_SCRATCH_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_SCRATCH_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_SCRATCH_OFFSET");

//        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_APB_BRDG_STAT_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_APB_BRDG_STAT_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_APB_BRDG_STAT_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_STS_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_STS_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_STS_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_HIGH_EN_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_HIGH_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_HIGH_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_LOW_EN_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_LOW_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_LOW_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ALM_EN_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ALM_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ALM_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ALM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CLR_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CLR_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CLR_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_FRC_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_FRC_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_FRC_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN2_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN3_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_EN3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR2_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR3_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_CLR3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_THRSH1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_NUM1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_WNDW_TIMER1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX2_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX3_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_IDX3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA0_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA1_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA2_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA3_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_WNDW_ERR_CNT_RDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_CFG_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_CFG_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_CFG_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_FRC_OFFSET, \
                                    JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_FRC_DEFAULT, \
                                    JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_FRC_RD_MASK, "JESD_RX_RSFEC_CLK_CSR_FECDLY_BUF_ECC_ERR_FRC_OFFSET");

    }

}
