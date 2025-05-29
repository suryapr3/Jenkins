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
    DLNK_JESD0_TX_CHAR_CLK_CSR_BASE, DLNK_JESD1_TX_CHAR_CLK_CSR_BASE, DLNK_JESD2_TX_CHAR_CLK_CSR_BASE, DLNK_JESD3_TX_CHAR_CLK_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_SCRATCH_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_SCRATCH_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_SCRATCH_RD_MASK, "JESD_TX_CHAR_CLK_CSR_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_APB_BRDG_STAT_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_APB_BRDG_STAT_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_APB_BRDG_STAT_RD_MASK, "JESD_TX_CHAR_CLK_CSR_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_STS_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_STS_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_STS_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_HIGH_EN_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_HIGH_EN_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_HIGH_EN_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_LOW_EN_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_LOW_EN_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_LOW_EN_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ALM_EN_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ALM_EN_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ALM_EN_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ALM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_CLR_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_CLR_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_CLR_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_FRC_OFFSET, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_FRC_DEFAULT, \
                                    JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_FRC_RD_MASK, "JESD_TX_CHAR_CLK_CSR_TX_CHAR_CLK_IMM_ERR_FRC_OFFSET");

    }

}
