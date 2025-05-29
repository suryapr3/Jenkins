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
    DLNK_PCIE_TOP_GPREG_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_SCRATCH0_OFFSET, \
                                    PCIE_TOP_GPREG_SCRATCH0_DEFAULT, \
                                    PCIE_TOP_GPREG_SCRATCH0_RD_MASK, "PCIE_TOP_GPREG_SCRATCH0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_SCRATCH1_OFFSET, \
                                    PCIE_TOP_GPREG_SCRATCH1_DEFAULT, \
                                    PCIE_TOP_GPREG_SCRATCH1_RD_MASK, "PCIE_TOP_GPREG_SCRATCH1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_CTL_0_OFFSET, \
                                    PCIE_TOP_GPREG_CTL_0_DEFAULT, \
                                    PCIE_TOP_GPREG_CTL_0_RD_MASK, "PCIE_TOP_GPREG_CTL_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_CTL_1_S_OFFSET, \
                                    PCIE_TOP_GPREG_CTL_1_S_DEFAULT, \
                                    PCIE_TOP_GPREG_CTL_1_S_RD_MASK, "PCIE_TOP_GPREG_CTL_1_S_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_CTL_RWM_0_S_OFFSET, \
                                    PCIE_TOP_GPREG_CTL_RWM_0_S_DEFAULT, \
                                    PCIE_TOP_GPREG_CTL_RWM_0_S_RD_MASK, "PCIE_TOP_GPREG_CTL_RWM_0_S_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_0_OFFSET, \
                                    PCIE_TOP_GPREG_RO_0_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_0_RD_MASK, "PCIE_TOP_GPREG_RO_0_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_1_OFFSET, \
                                    PCIE_TOP_GPREG_RO_1_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_1_RD_MASK, "PCIE_TOP_GPREG_RO_1_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_2_OFFSET, \
                                    PCIE_TOP_GPREG_RO_2_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_2_RD_MASK, "PCIE_TOP_GPREG_RO_2_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_3_OFFSET, \
                                    PCIE_TOP_GPREG_RO_3_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_3_RD_MASK, "PCIE_TOP_GPREG_RO_3_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_4_OFFSET, \
                                    PCIE_TOP_GPREG_RO_4_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_4_RD_MASK, "PCIE_TOP_GPREG_RO_4_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_RO_5_OFFSET, \
                                    PCIE_TOP_GPREG_RO_5_DEFAULT, \
                                    PCIE_TOP_GPREG_RO_5_RD_MASK, "PCIE_TOP_GPREG_RO_5_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_INTR0_STAT_OFFSET, \
                                    PCIE_TOP_GPREG_INTR0_STAT_DEFAULT, \
                                    PCIE_TOP_GPREG_INTR0_STAT_RD_MASK, "PCIE_TOP_GPREG_INTR0_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_INTR0_HIGH_EN_OFFSET, \
                                    PCIE_TOP_GPREG_INTR0_HIGH_EN_DEFAULT, \
                                    PCIE_TOP_GPREG_INTR0_HIGH_EN_RD_MASK, "PCIE_TOP_GPREG_INTR0_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_INTR0_LOW_EN_OFFSET, \
                                    PCIE_TOP_GPREG_INTR0_LOW_EN_DEFAULT, \
                                    PCIE_TOP_GPREG_INTR0_LOW_EN_RD_MASK, "PCIE_TOP_GPREG_INTR0_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_INTR0_CLR_OFFSET, \
                                    PCIE_TOP_GPREG_INTR0_CLR_DEFAULT, \
                                    PCIE_TOP_GPREG_INTR0_CLR_RD_MASK, "PCIE_TOP_GPREG_INTR0_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+PCIE_TOP_GPREG_INTR0_FORCE_OFFSET, \
                                    PCIE_TOP_GPREG_INTR0_FORCE_DEFAULT, \
                                    PCIE_TOP_GPREG_INTR0_FORCE_RD_MASK, "PCIE_TOP_GPREG_INTR0_FORCE_OFFSET");

    }

}
