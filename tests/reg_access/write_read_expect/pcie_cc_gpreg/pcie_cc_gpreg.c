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
    DLNK_PCIE_CC_GPREG_BASE
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


        for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
        {
            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_SCRATCH0_OFFSET, \
                                    PCIE_CC_GPREG_SCRATCH0_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_SCRATCH0_RD_MASK, PCIE_CC_GPREG_SCRATCH0_WR_MASK, \
                                    "PCIE_CC_GPREG_SCRATCH0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_SCRATCH1_OFFSET, \
                                    PCIE_CC_GPREG_SCRATCH1_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_SCRATCH1_RD_MASK, PCIE_CC_GPREG_SCRATCH1_WR_MASK, \
                                    "PCIE_CC_GPREG_SCRATCH1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_BRDG_OFFSET, \
                                    PCIE_CC_GPREG_BRDG_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_BRDG_RD_MASK, PCIE_CC_GPREG_BRDG_WR_MASK, \
                                    "PCIE_CC_GPREG_BRDG_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_0_S_OFFSET, \
                                    PCIE_CC_GPREG_CTL_0_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_0_S_RD_MASK, PCIE_CC_GPREG_CTL_0_S_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_0_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_1_OFFSET, \
                                    PCIE_CC_GPREG_CTL_1_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_1_RD_MASK, PCIE_CC_GPREG_CTL_1_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_2_OFFSET, \
                                    PCIE_CC_GPREG_CTL_2_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_2_RD_MASK, PCIE_CC_GPREG_CTL_2_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_3_OFFSET, \
                                    PCIE_CC_GPREG_CTL_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_3_RD_MASK, PCIE_CC_GPREG_CTL_3_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_4_OFFSET, \
                                    PCIE_CC_GPREG_CTL_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_4_RD_MASK, PCIE_CC_GPREG_CTL_4_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_5_OFFSET, \
                                    PCIE_CC_GPREG_CTL_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_5_RD_MASK, PCIE_CC_GPREG_CTL_5_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_6_S_OFFSET, \
                                    PCIE_CC_GPREG_CTL_6_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_6_S_RD_MASK, PCIE_CC_GPREG_CTL_6_S_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_6_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_7_OFFSET, \
                                    PCIE_CC_GPREG_CTL_7_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_7_RD_MASK, PCIE_CC_GPREG_CTL_7_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_CTL_8_OFFSET, \
                                    PCIE_CC_GPREG_CTL_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_CTL_8_RD_MASK, PCIE_CC_GPREG_CTL_8_WR_MASK, \
                                    "PCIE_CC_GPREG_CTL_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_FORCE_TYPE_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_FORCE_TYPE_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_FORCE_TYPE_S_RD_MASK, PCIE_CC_GPREG_ECC_FORCE_TYPE_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_FORCE_TYPE_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_FORCE_ERR_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_FORCE_ERR_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_FORCE_ERR_S_RD_MASK, PCIE_CC_GPREG_ECC_FORCE_ERR_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_FORCE_ERR_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_ERR_CLR_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_ERR_CLR_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_ERR_CLR_S_RD_MASK, PCIE_CC_GPREG_ECC_ERR_CLR_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_ERR_CLR_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_CNT_CLR_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_CNT_CLR_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_CNT_CLR_S_RD_MASK, PCIE_CC_GPREG_ECC_CNT_CLR_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_CNT_CLR_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_CHK_DIS_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_CHK_DIS_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_CHK_DIS_S_RD_MASK, PCIE_CC_GPREG_ECC_CHK_DIS_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_CHK_DIS_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_GEN_DIS_S_OFFSET, \
                                    PCIE_CC_GPREG_ECC_GEN_DIS_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_GEN_DIS_S_RD_MASK, PCIE_CC_GPREG_ECC_GEN_DIS_S_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_GEN_DIS_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S0_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S1_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S1_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S2_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S2_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S3_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S4_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S5_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S6_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S7_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S7_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S8_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S9_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S9_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S10_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S11_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S12_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S13_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S14_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S14_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S15_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S15_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S16_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S16_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S17_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S18_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S19_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S20_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S20_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_SW_SHDW_S21_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_SW_SHDW_S_RD_MASK, PCIE_CC_GPREG_WIRE_SW_SHDW_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_SW_SHDW_S21_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_0_OFFSET, \
                                    PCIE_CC_GPREG_RO_0_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_0_RD_MASK, PCIE_CC_GPREG_RO_0_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_0_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_3_OFFSET, \
                                    PCIE_CC_GPREG_RO_3_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_3_RD_MASK, PCIE_CC_GPREG_RO_3_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_3_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_4_OFFSET, \
                                    PCIE_CC_GPREG_RO_4_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_4_RD_MASK, PCIE_CC_GPREG_RO_4_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_4_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_5_OFFSET, \
                                    PCIE_CC_GPREG_RO_5_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_5_RD_MASK, PCIE_CC_GPREG_RO_5_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_5_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_6_OFFSET, \
                                    PCIE_CC_GPREG_RO_6_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_6_RD_MASK, PCIE_CC_GPREG_RO_6_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_6_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_8_OFFSET, \
                                    PCIE_CC_GPREG_RO_8_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_8_RD_MASK, PCIE_CC_GPREG_RO_8_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_8_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_10_OFFSET, \
                                    PCIE_CC_GPREG_RO_10_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_10_RD_MASK, PCIE_CC_GPREG_RO_10_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_10_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_11_OFFSET, \
                                    PCIE_CC_GPREG_RO_11_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_11_RD_MASK, PCIE_CC_GPREG_RO_11_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_11_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_12_OFFSET, \
                                    PCIE_CC_GPREG_RO_12_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_12_RD_MASK, PCIE_CC_GPREG_RO_12_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_12_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_13_OFFSET, \
                                    PCIE_CC_GPREG_RO_13_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_13_RD_MASK, PCIE_CC_GPREG_RO_13_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_13_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_17_OFFSET, \
                                    PCIE_CC_GPREG_RO_17_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_17_RD_MASK, PCIE_CC_GPREG_RO_17_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_17_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_18_OFFSET, \
                                    PCIE_CC_GPREG_RO_18_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_18_RD_MASK, PCIE_CC_GPREG_RO_18_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_18_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_19_OFFSET, \
                                    PCIE_CC_GPREG_RO_19_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_19_RD_MASK, PCIE_CC_GPREG_RO_19_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_19_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_RO_20_OFFSET, \
                                    PCIE_CC_GPREG_RO_20_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_RO_20_RD_MASK, PCIE_CC_GPREG_RO_20_WR_MASK, \
                                    "PCIE_CC_GPREG_RO_20_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_00_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_00_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_00_S_RD_MASK, PCIE_CC_GPREG_DOE_00_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_00_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_01_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_01_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_01_S_RD_MASK, PCIE_CC_GPREG_DOE_01_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_01_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_02_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_02_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_02_S_RD_MASK, PCIE_CC_GPREG_DOE_02_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_02_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_03_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_03_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_03_S_RD_MASK, PCIE_CC_GPREG_DOE_03_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_03_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_04_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_04_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_04_S_RD_MASK, PCIE_CC_GPREG_DOE_04_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_04_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_05_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_05_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_05_S_RD_MASK, PCIE_CC_GPREG_DOE_05_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_05_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_06_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_06_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_06_S_RD_MASK, PCIE_CC_GPREG_DOE_06_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_06_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_07_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_07_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_07_S_RD_MASK, PCIE_CC_GPREG_DOE_07_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_07_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_08_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_08_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_08_S_RD_MASK, PCIE_CC_GPREG_DOE_08_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_08_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_09_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_09_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_09_S_RD_MASK, PCIE_CC_GPREG_DOE_09_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_09_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_10_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_10_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_10_S_RD_MASK, PCIE_CC_GPREG_DOE_10_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_10_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_11_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_11_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_11_S_RD_MASK, PCIE_CC_GPREG_DOE_11_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_11_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_12_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_12_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_12_S_RD_MASK, PCIE_CC_GPREG_DOE_12_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_12_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_13_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_13_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_13_S_RD_MASK, PCIE_CC_GPREG_DOE_13_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_13_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_14_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_14_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_14_S_RD_MASK, PCIE_CC_GPREG_DOE_14_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_14_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_15_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_15_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_15_S_RD_MASK, PCIE_CC_GPREG_DOE_15_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_15_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_16_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_16_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_16_S_RD_MASK, PCIE_CC_GPREG_DOE_16_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_16_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_17_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_17_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_17_S_RD_MASK, PCIE_CC_GPREG_DOE_17_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_17_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_18_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_18_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_18_S_RD_MASK, PCIE_CC_GPREG_DOE_18_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_18_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_19_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_19_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_19_S_RD_MASK, PCIE_CC_GPREG_DOE_19_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_19_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_INTR_STAT_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_INTR_STAT_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_INTR_STAT_S_RD_MASK, PCIE_CC_GPREG_DOE_INTR_STAT_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_INTR_STAT_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_INTR_HIGH_EN_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_INTR_HIGH_EN_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_INTR_HIGH_EN_S_RD_MASK, PCIE_CC_GPREG_DOE_INTR_HIGH_EN_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_INTR_HIGH_EN_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_INTR_LOW_EN_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_INTR_LOW_EN_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_INTR_LOW_EN_S_RD_MASK, PCIE_CC_GPREG_DOE_INTR_LOW_EN_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_INTR_LOW_EN_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_INTR_CLR_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_INTR_CLR_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_INTR_CLR_S_RD_MASK, PCIE_CC_GPREG_DOE_INTR_CLR_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_INTR_CLR_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_DOE_INTR_FORCE_S_OFFSET, \
                                    PCIE_CC_GPREG_DOE_INTR_FORCE_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_DOE_INTR_FORCE_S_RD_MASK, PCIE_CC_GPREG_DOE_INTR_FORCE_S_WR_MASK, \
                                    "PCIE_CC_GPREG_DOE_INTR_FORCE_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_WIRE_S_OFFSET, \
                                    PCIE_CC_GPREG_WIRE_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_WIRE_S_RD_MASK, PCIE_CC_GPREG_WIRE_S_WR_MASK, \
                                    "PCIE_CC_GPREG_WIRE_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_LTSSM_S_OFFSET, \
                                    PCIE_CC_GPREG_LTSSM_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_LTSSM_S_RD_MASK, PCIE_CC_GPREG_LTSSM_S_WR_MASK, \
                                    "PCIE_CC_GPREG_LTSSM_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_RD_MASK, PCIE_CC_GPREG_ECC_SBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_DBE_OFFSET, \
                                    PCIE_CC_GPREG_ECC_DBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_DBE_RD_MASK, PCIE_CC_GPREG_ECC_DBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_DBE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_CNT_OVFL_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_CNT_OVFL_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_CNT_OVFL_RD_MASK, PCIE_CC_GPREG_ECC_SBE_CNT_OVFL_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_CNT_OVFL_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_CNT_00_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_RD_MASK, PCIE_CC_GPREG_ECC_SBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_CNT_00_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_CNT_01_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_RD_MASK, PCIE_CC_GPREG_ECC_SBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_CNT_01_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_CNT_02_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_RD_MASK, PCIE_CC_GPREG_ECC_SBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_CNT_02_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_ECC_SBE_CNT_03_OFFSET, \
                                    PCIE_CC_GPREG_ECC_SBE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_ECC_SBE_RD_MASK, PCIE_CC_GPREG_ECC_SBE_WR_MASK, \
                                    "PCIE_CC_GPREG_ECC_SBE_CNT_03_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR0_STAT_OFFSET, \
                                    PCIE_CC_GPREG_INTR0_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR0_STAT_RD_MASK, PCIE_CC_GPREG_INTR0_STAT_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR0_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR0_HIGH_EN_OFFSET, \
                                    PCIE_CC_GPREG_INTR0_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR0_HIGH_EN_RD_MASK, PCIE_CC_GPREG_INTR0_HIGH_EN_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR0_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR0_LOW_EN_OFFSET, \
                                    PCIE_CC_GPREG_INTR0_LOW_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR0_LOW_EN_RD_MASK, PCIE_CC_GPREG_INTR0_LOW_EN_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR0_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR0_CLR_OFFSET, \
                                    PCIE_CC_GPREG_INTR0_CLR_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR0_CLR_RD_MASK, PCIE_CC_GPREG_INTR0_CLR_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR0_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR0_FORCE_OFFSET, \
                                    PCIE_CC_GPREG_INTR0_FORCE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR0_FORCE_RD_MASK, PCIE_CC_GPREG_INTR0_FORCE_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR0_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR1_STAT_OFFSET, \
                                    PCIE_CC_GPREG_INTR1_STAT_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR1_STAT_RD_MASK, PCIE_CC_GPREG_INTR1_STAT_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR1_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR1_HIGH_EN_OFFSET, \
                                    PCIE_CC_GPREG_INTR1_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR1_HIGH_EN_RD_MASK, PCIE_CC_GPREG_INTR1_HIGH_EN_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR1_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR1_LOW_EN_OFFSET, \
                                    PCIE_CC_GPREG_INTR1_LOW_EN_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR1_LOW_EN_RD_MASK, PCIE_CC_GPREG_INTR1_LOW_EN_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR1_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR1_CLR_OFFSET, \
                                    PCIE_CC_GPREG_INTR1_CLR_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR1_CLR_RD_MASK, PCIE_CC_GPREG_INTR1_CLR_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR1_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR1_FORCE_OFFSET, \
                                    PCIE_CC_GPREG_INTR1_FORCE_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR1_FORCE_RD_MASK, PCIE_CC_GPREG_INTR1_FORCE_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR1_FORCE_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR2_STAT_S_OFFSET, \
                                    PCIE_CC_GPREG_INTR2_STAT_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR2_STAT_S_RD_MASK, PCIE_CC_GPREG_INTR2_STAT_S_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR2_STAT_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR2_HIGH_EN_S_OFFSET, \
                                    PCIE_CC_GPREG_INTR2_HIGH_EN_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR2_HIGH_EN_S_RD_MASK, PCIE_CC_GPREG_INTR2_HIGH_EN_S_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR2_HIGH_EN_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR2_LOW_EN_S_OFFSET, \
                                    PCIE_CC_GPREG_INTR2_LOW_EN_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR2_LOW_EN_S_RD_MASK, PCIE_CC_GPREG_INTR2_LOW_EN_S_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR2_LOW_EN_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR2_CLR_S_OFFSET, \
                                    PCIE_CC_GPREG_INTR2_CLR_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR2_CLR_S_RD_MASK, PCIE_CC_GPREG_INTR2_CLR_S_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR2_CLR_S_OFFSET");

            write_read_expect_18a(base_address[i]+PCIE_CC_GPREG_INTR2_FORCE_S_OFFSET, \
                                    PCIE_CC_GPREG_INTR2_FORCE_S_DEFAULT, write_data, expected_data, \
                                    PCIE_CC_GPREG_INTR2_FORCE_S_RD_MASK, PCIE_CC_GPREG_INTR2_FORCE_S_WR_MASK, \
                                    "PCIE_CC_GPREG_INTR2_FORCE_S_OFFSET");

        }

    }

}
