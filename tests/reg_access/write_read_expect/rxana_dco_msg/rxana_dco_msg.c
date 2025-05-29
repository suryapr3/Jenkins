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
    DLNK_JESD0_PHY_PMA0_RXANA_DCO_GLOBAL_BASE, DLNK_JESD0_PHY_PMA0_RXANA_DCO_Q0_BASE, DLNK_JESD0_PHY_PMA0_RXANA_DCO_Q1_BASE, DLNK_JESD0_PHY_PMA0_RXANA_DCO_Q2_BASE, DLNK_JESD0_PHY_PMA0_RXANA_DCO_Q3_BASE,
    DLNK_JESD1_PHY_PMA0_RXANA_DCO_GLOBAL_BASE, DLNK_JESD1_PHY_PMA0_RXANA_DCO_Q0_BASE, DLNK_JESD1_PHY_PMA0_RXANA_DCO_Q1_BASE, DLNK_JESD1_PHY_PMA0_RXANA_DCO_Q2_BASE, DLNK_JESD1_PHY_PMA0_RXANA_DCO_Q3_BASE,
    DLNK_JESD2_PHY_PMA0_RXANA_DCO_GLOBAL_BASE, DLNK_JESD2_PHY_PMA0_RXANA_DCO_Q0_BASE, DLNK_JESD2_PHY_PMA0_RXANA_DCO_Q1_BASE, DLNK_JESD2_PHY_PMA0_RXANA_DCO_Q2_BASE, DLNK_JESD2_PHY_PMA0_RXANA_DCO_Q3_BASE,
    DLNK_JESD3_PHY_PMA0_RXANA_DCO_GLOBAL_BASE, DLNK_JESD3_PHY_PMA0_RXANA_DCO_Q0_BASE, DLNK_JESD3_PHY_PMA0_RXANA_DCO_Q1_BASE, DLNK_JESD3_PHY_PMA0_RXANA_DCO_Q2_BASE, DLNK_JESD3_PHY_PMA0_RXANA_DCO_Q3_BASE
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
            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCO_CTRL0_OFFSET, \
                                    RXANA_DCO_MSG_RXDCO_CTRL0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCO_CTRL0_RD_MASK, RXANA_DCO_MSG_RXDCO_CTRL0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCO_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCODIV_CTRL0_OFFSET, \
                                    RXANA_DCO_MSG_RXDCODIV_CTRL0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCODIV_CTRL0_RD_MASK, RXANA_DCO_MSG_RXDCODIV_CTRL0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCODIV_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCODIV_CTRL1_OFFSET, \
                                    RXANA_DCO_MSG_RXDCODIV_CTRL1_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCODIV_CTRL1_RD_MASK, RXANA_DCO_MSG_RXDCODIV_CTRL1_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCODIV_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCO_DFX0_OFFSET, \
                                    RXANA_DCO_MSG_RXDCO_DFX0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCO_DFX0_RD_MASK, RXANA_DCO_MSG_RXDCO_DFX0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCO_DFX0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCO_LDO0_OFFSET, \
                                    RXANA_DCO_MSG_RXDCO_LDO0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCO_LDO0_RD_MASK, RXANA_DCO_MSG_RXDCO_LDO0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCO_LDO0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXDCO_PFD0_OFFSET, \
                                    RXANA_DCO_MSG_RXDCO_PFD0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXDCO_PFD0_RD_MASK, RXANA_DCO_MSG_RXDCO_PFD0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXDCO_PFD0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_CTRL0_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL0_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_CTRL0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_CTRL0_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_CTRL1_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL1_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL1_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_CTRL1_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_CTRL1_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_CTRL2_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL2_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL2_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_CTRL2_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_CTRL2_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_CTRL3_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL3_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL3_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_CTRL3_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_CTRL4_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL4_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_CTRL4_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_CTRL4_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_CTRL4_OFFSET");

            write_read_expect_18a(base_address[i]+RXANA_DCO_MSG_RXADCCLKGEN_SPARE0_OFFSET, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_SPARE0_DEFAULT, write_data, expected_data, \
                                    RXANA_DCO_MSG_RXADCCLKGEN_SPARE0_RD_MASK, RXANA_DCO_MSG_RXADCCLKGEN_SPARE0_WR_MASK, \
                                    "RXANA_DCO_MSG_RXADCCLKGEN_SPARE0_OFFSET");

        }

    }

}
