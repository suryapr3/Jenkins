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
    SYSCON_CTRL_BASE
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
            //write_read_expect_18a(base_address[i]+SYS_CTRL_SCRATCHBOTTOM_OFFSET, \
                                    SYS_CTRL_SCRATCHBOTTOM_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SCRATCHBOTTOM_RD_MASK, SYS_CTRL_SCRATCHBOTTOM_WR_MASK, \
                                    "SYS_CTRL_SCRATCHBOTTOM_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_VER_OFFSET, \
                                    SYS_CTRL_VER_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_VER_RD_MASK, SYS_CTRL_VER_WR_MASK, \
                                    "SYS_CTRL_VER_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SYS_CTRL_OFFSET, \
                                    SYS_CTRL_SYS_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SYS_CTRL_RD_MASK, SYS_CTRL_SYS_CTRL_WR_MASK, \
                                    "SYS_CTRL_SYS_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SYS_STAT_OFFSET, \
                                    SYS_CTRL_SYS_STAT_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SYS_STAT_RD_MASK, SYS_CTRL_SYS_STAT_WR_MASK, \
                                    "SYS_CTRL_SYS_STAT_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_RST_CTRL_OFFSET, \
                                    SYS_CTRL_RST_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_RST_CTRL_RD_MASK, SYS_CTRL_RST_CTRL_WR_MASK, \
                                    "SYS_CTRL_RST_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_GPIO_CTRL_OFFSET, \
                                    SYS_CTRL_GPIO_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_GPIO_CTRL_RD_MASK, SYS_CTRL_GPIO_CTRL_WR_MASK, \
                                    "SYS_CTRL_GPIO_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SPICSR_OFFSET, \
                                    SYS_CTRL_SPICSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SPICSR_RD_MASK, SYS_CTRL_SPICSR_WR_MASK, \
                                    "SYS_CTRL_SPICSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_RST_SOURCE_OFFSET, \
                                    SYS_CTRL_RST_SOURCE_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_RST_SOURCE_RD_MASK, SYS_CTRL_RST_SOURCE_WR_MASK, \
                                    "SYS_CTRL_RST_SOURCE_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_CSTS_SNAPSHOT_H_OFFSET, \
                                    SYS_CTRL_CSTS_SNAPSHOT_H_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_CSTS_SNAPSHOT_H_RD_MASK, SYS_CTRL_CSTS_SNAPSHOT_H_WR_MASK, \
                                    "SYS_CTRL_CSTS_SNAPSHOT_H_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_CSTS_SNAPSHOT_L_OFFSET, \
                                    SYS_CTRL_CSTS_SNAPSHOT_L_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_CSTS_SNAPSHOT_L_RD_MASK, SYS_CTRL_CSTS_SNAPSHOT_L_WR_MASK, \
                                    "SYS_CTRL_CSTS_SNAPSHOT_L_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_VADFSMSR_OFFSET, \
                                    SYS_CTRL_VADFSMSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_VADFSMSR_RD_MASK, SYS_CTRL_VADFSMSR_WR_MASK, \
                                    "SYS_CTRL_VADFSMSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_FDISTOV_CSR_OFFSET, \
                                    SYS_CTRL_FDISTOV_CSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_FDISTOV_CSR_RD_MASK, SYS_CTRL_FDISTOV_CSR_WR_MASK, \
                                    "SYS_CTRL_FDISTOV_CSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP0_WDOG_CSR_OFFSET, \
                                    SYS_CTRL_WDOG_CSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_CSR_RD_MASK, SYS_CTRL_WDOG_CSR_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP0_WDOG_CSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP0_WDOG_IVAL_OFFSET, \
                                    SYS_CTRL_WDOG_IVAL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_IVAL_RD_MASK, SYS_CTRL_WDOG_IVAL_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP0_WDOG_IVAL_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP0_WDOG_KA_OFFSET, \
                                    SYS_CTRL_WDOG_KA_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_KA_RD_MASK, SYS_CTRL_WDOG_KA_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP0_WDOG_KA_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP1_WDOG_CSR_OFFSET, \
                                    SYS_CTRL_WDOG_CSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_CSR_RD_MASK, SYS_CTRL_WDOG_CSR_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP1_WDOG_CSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP1_WDOG_IVAL_OFFSET, \
                                    SYS_CTRL_WDOG_IVAL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_IVAL_RD_MASK, SYS_CTRL_WDOG_IVAL_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP1_WDOG_IVAL_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_WDOG_MAP1_WDOG_KA_OFFSET, \
                                    SYS_CTRL_WDOG_KA_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_WDOG_KA_RD_MASK, SYS_CTRL_WDOG_KA_WR_MASK, \
                                    "SYS_CTRL_WDOG_MAP1_WDOG_KA_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_CTRL_STAT_OFFSET, \
                                    SYS_CTRL_SBB_CTRL_STAT_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_CTRL_STAT_RD_MASK, SYS_CTRL_SBB_CTRL_STAT_WR_MASK, \
                                    "SYS_CTRL_SBB_CTRL_STAT_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_CTRL_OFFSET, \
                                    SYS_CTRL_SBB_MEM_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_CTRL_RD_MASK, SYS_CTRL_SBB_MEM_CTRL_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_CTRL0_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL0_RD_MASK, SYS_CTRL_SBB_MEM_ECC_CTRL0_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_CTRL0_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_CTRL1_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL1_RD_MASK, SYS_CTRL_SBB_MEM_ECC_CTRL1_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_CTRL1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_CTRL2_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL2_RD_MASK, SYS_CTRL_SBB_MEM_ECC_CTRL2_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_CTRL2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_CTRL3_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL3_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_CTRL3_RD_MASK, SYS_CTRL_SBB_MEM_ECC_CTRL3_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_CTRL3_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_STAT0_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_STAT0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_STAT0_RD_MASK, SYS_CTRL_SBB_MEM_ECC_STAT0_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_STAT0_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_STAT1_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_STAT1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_STAT1_RD_MASK, SYS_CTRL_SBB_MEM_ECC_STAT1_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_STAT1_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_ERR_CNTER0_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_ERR_CNTER0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_ERR_CNTER0_RD_MASK, SYS_CTRL_SBB_MEM_ECC_ERR_CNTER0_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_ERR_CNTER0_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ECC_ERR_CNTER1_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ECC_ERR_CNTER1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ECC_ERR_CNTER1_RD_MASK, SYS_CTRL_SBB_MEM_ECC_ERR_CNTER1_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ECC_ERR_CNTER1_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_MEM_ERR_INFORMATION_OFFSET, \
                                    SYS_CTRL_SBB_MEM_ERR_INFORMATION_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_MEM_ERR_INFORMATION_RD_MASK, SYS_CTRL_SBB_MEM_ERR_INFORMATION_WR_MASK, \
                                    "SYS_CTRL_SBB_MEM_ERR_INFORMATION_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_SBB_TRNG_RAND_OFFSET, \
                                    SYS_CTRL_SBB_TRNG_RAND_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SBB_TRNG_RAND_RD_MASK, SYS_CTRL_SBB_TRNG_RAND_WR_MASK, \
                                    "SYS_CTRL_SBB_TRNG_RAND_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_INTR0_CSR_INTRSTAT0_OFFSET, \
                                    SYS_CTRL_INTR0_CSR_INTRSTAT0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR0_CSR_INTRSTAT0_RD_MASK, SYS_CTRL_INTR0_CSR_INTRSTAT0_WR_MASK, \
                                    "SYS_CTRL_INTR0_CSR_INTRSTAT0_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR0_CSR_INTRENHIGH0_OFFSET, \
                                    SYS_CTRL_INTR0_CSR_INTRENHIGH0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR0_CSR_INTRENHIGH0_RD_MASK, SYS_CTRL_INTR0_CSR_INTRENHIGH0_WR_MASK, \
                                    "SYS_CTRL_INTR0_CSR_INTRENHIGH0_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR0_CSR_INTRENLOW0_OFFSET, \
                                    SYS_CTRL_INTR0_CSR_INTRENLOW0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR0_CSR_INTRENLOW0_RD_MASK, SYS_CTRL_INTR0_CSR_INTRENLOW0_WR_MASK, \
                                    "SYS_CTRL_INTR0_CSR_INTRENLOW0_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR0_CSR_INTRCLR0_OFFSET, \
                                    SYS_CTRL_INTR0_CSR_INTRCLR0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR0_CSR_INTRCLR0_RD_MASK, SYS_CTRL_INTR0_CSR_INTRCLR0_WR_MASK, \
                                    "SYS_CTRL_INTR0_CSR_INTRCLR0_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR0_CSR_INTRFORCE0_OFFSET, \
                                    SYS_CTRL_INTR0_CSR_INTRFORCE0_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR0_CSR_INTRFORCE0_RD_MASK, SYS_CTRL_INTR0_CSR_INTRFORCE0_WR_MASK, \
                                    "SYS_CTRL_INTR0_CSR_INTRFORCE0_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_INTR1_CSR_INTRSTAT1_OFFSET, \
                                    SYS_CTRL_INTR1_CSR_INTRSTAT1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR1_CSR_INTRSTAT1_RD_MASK, SYS_CTRL_INTR1_CSR_INTRSTAT1_WR_MASK, \
                                    "SYS_CTRL_INTR1_CSR_INTRSTAT1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR1_CSR_INTRENHIGH1_OFFSET, \
                                    SYS_CTRL_INTR1_CSR_INTRENHIGH1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR1_CSR_INTRENHIGH1_RD_MASK, SYS_CTRL_INTR1_CSR_INTRENHIGH1_WR_MASK, \
                                    "SYS_CTRL_INTR1_CSR_INTRENHIGH1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR1_CSR_INTRENLOW1_OFFSET, \
                                    SYS_CTRL_INTR1_CSR_INTRENLOW1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR1_CSR_INTRENLOW1_RD_MASK, SYS_CTRL_INTR1_CSR_INTRENLOW1_WR_MASK, \
                                    "SYS_CTRL_INTR1_CSR_INTRENLOW1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR1_CSR_INTRCLR1_OFFSET, \
                                    SYS_CTRL_INTR1_CSR_INTRCLR1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR1_CSR_INTRCLR1_RD_MASK, SYS_CTRL_INTR1_CSR_INTRCLR1_WR_MASK, \
                                    "SYS_CTRL_INTR1_CSR_INTRCLR1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR1_CSR_INTRFORCE1_OFFSET, \
                                    SYS_CTRL_INTR1_CSR_INTRFORCE1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR1_CSR_INTRFORCE1_RD_MASK, SYS_CTRL_INTR1_CSR_INTRFORCE1_WR_MASK, \
                                    "SYS_CTRL_INTR1_CSR_INTRFORCE1_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_INTR2_CSR_INTRSTAT2_OFFSET, \
                                    SYS_CTRL_INTR2_CSR_INTRSTAT2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR2_CSR_INTRSTAT2_RD_MASK, SYS_CTRL_INTR2_CSR_INTRSTAT2_WR_MASK, \
                                    "SYS_CTRL_INTR2_CSR_INTRSTAT2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR2_CSR_INTRENHIGH2_OFFSET, \
                                    SYS_CTRL_INTR2_CSR_INTRENHIGH2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR2_CSR_INTRENHIGH2_RD_MASK, SYS_CTRL_INTR2_CSR_INTRENHIGH2_WR_MASK, \
                                    "SYS_CTRL_INTR2_CSR_INTRENHIGH2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR2_CSR_INTRENLOW2_OFFSET, \
                                    SYS_CTRL_INTR2_CSR_INTRENLOW2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR2_CSR_INTRENLOW2_RD_MASK, SYS_CTRL_INTR2_CSR_INTRENLOW2_WR_MASK, \
                                    "SYS_CTRL_INTR2_CSR_INTRENLOW2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR2_CSR_INTRCLR2_OFFSET, \
                                    SYS_CTRL_INTR2_CSR_INTRCLR2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR2_CSR_INTRCLR2_RD_MASK, SYS_CTRL_INTR2_CSR_INTRCLR2_WR_MASK, \
                                    "SYS_CTRL_INTR2_CSR_INTRCLR2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_INTR2_CSR_INTRFORCE2_OFFSET, \
                                    SYS_CTRL_INTR2_CSR_INTRFORCE2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_INTR2_CSR_INTRFORCE2_RD_MASK, SYS_CTRL_INTR2_CSR_INTRFORCE2_WR_MASK, \
                                    "SYS_CTRL_INTR2_CSR_INTRFORCE2_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_TXALARM_CSR_TXALARMSTAT_OFFSET, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMSTAT_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMSTAT_RD_MASK, SYS_CTRL_TXALARM_CSR_TXALARMSTAT_WR_MASK, \
                                    "SYS_CTRL_TXALARM_CSR_TXALARMSTAT_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_TXALARM_CSR_TXALARMEN_OFFSET, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMEN_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMEN_RD_MASK, SYS_CTRL_TXALARM_CSR_TXALARMEN_WR_MASK, \
                                    "SYS_CTRL_TXALARM_CSR_TXALARMEN_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_TXALARM_CSR_TXALARMCLR_OFFSET, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMCLR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMCLR_RD_MASK, SYS_CTRL_TXALARM_CSR_TXALARMCLR_WR_MASK, \
                                    "SYS_CTRL_TXALARM_CSR_TXALARMCLR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_TXALARM_CSR_TXALARMFORCE_OFFSET, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMFORCE_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_TXALARM_CSR_TXALARMFORCE_RD_MASK, SYS_CTRL_TXALARM_CSR_TXALARMFORCE_WR_MASK, \
                                    "SYS_CTRL_TXALARM_CSR_TXALARMFORCE_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_HW_LOCK_STAT_OFFSET, \
                                    SYS_CTRL_DFX_HW_LOCK_STAT_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_HW_LOCK_STAT_RD_MASK, SYS_CTRL_DFX_HW_LOCK_STAT_WR_MASK, \
                                    "SYS_CTRL_DFX_HW_LOCK_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BOOTDBG_STAT_OFFSET, \
                                    SYS_CTRL_DFX_BOOTDBG_STAT_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BOOTDBG_STAT_RD_MASK, SYS_CTRL_DFX_BOOTDBG_STAT_WR_MASK, \
                                    "SYS_CTRL_DFX_BOOTDBG_STAT_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BOOTDBG_CTRL_OFFSET, \
                                    SYS_CTRL_DFX_BOOTDBG_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BOOTDBG_CTRL_RD_MASK, SYS_CTRL_DFX_BOOTDBG_CTRL_WR_MASK, \
                                    "SYS_CTRL_DFX_BOOTDBG_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BOOTDBG_RSTOVRD_OFFSET, \
                                    SYS_CTRL_DFX_BOOTDBG_RSTOVRD_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BOOTDBG_RSTOVRD_RD_MASK, SYS_CTRL_DFX_BOOTDBG_RSTOVRD_WR_MASK, \
                                    "SYS_CTRL_DFX_BOOTDBG_RSTOVRD_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BOOTDBG_RSTVAL_OFFSET, \
                                    SYS_CTRL_DFX_BOOTDBG_RSTVAL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BOOTDBG_RSTVAL_RD_MASK, SYS_CTRL_DFX_BOOTDBG_RSTVAL_WR_MASK, \
                                    "SYS_CTRL_DFX_BOOTDBG_RSTVAL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_GPIOEAST_CTRL_OFFSET, \
                                    SYS_CTRL_DFX_GPIOEAST_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_GPIOEAST_CTRL_RD_MASK, SYS_CTRL_DFX_GPIOEAST_CTRL_WR_MASK, \
                                    "SYS_CTRL_DFX_GPIOEAST_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_DBGMUX_CTRL_OFFSET, \
                                    SYS_CTRL_DFX_DBGMUX_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_DBGMUX_CTRL_RD_MASK, SYS_CTRL_DFX_DBGMUX_CTRL_WR_MASK, \
                                    "SYS_CTRL_DFX_DBGMUX_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_MEM_TRIM_OVRD1_OFFSET, \
                                    SYS_CTRL_DFX_MEM_TRIM_OVRD1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_MEM_TRIM_OVRD1_RD_MASK, SYS_CTRL_DFX_MEM_TRIM_OVRD1_WR_MASK, \
                                    "SYS_CTRL_DFX_MEM_TRIM_OVRD1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_MEM_TRIM_OVRD2_OFFSET, \
                                    SYS_CTRL_DFX_MEM_TRIM_OVRD2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_MEM_TRIM_OVRD2_RD_MASK, SYS_CTRL_DFX_MEM_TRIM_OVRD2_WR_MASK, \
                                    "SYS_CTRL_DFX_MEM_TRIM_OVRD2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_LB_TRIM_OVRD1_OFFSET, \
                                    SYS_CTRL_DFX_LB_TRIM_OVRD1_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_LB_TRIM_OVRD1_RD_MASK, SYS_CTRL_DFX_LB_TRIM_OVRD1_WR_MASK, \
                                    "SYS_CTRL_DFX_LB_TRIM_OVRD1_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_LB_TRIM_OVRD2_OFFSET, \
                                    SYS_CTRL_DFX_LB_TRIM_OVRD2_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_LB_TRIM_OVRD2_RD_MASK, SYS_CTRL_DFX_LB_TRIM_OVRD2_WR_MASK, \
                                    "SYS_CTRL_DFX_LB_TRIM_OVRD2_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_FSLDO_STATOVRD_OFFSET, \
                                    SYS_CTRL_DFX_FSLDO_STATOVRD_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_FSLDO_STATOVRD_RD_MASK, SYS_CTRL_DFX_FSLDO_STATOVRD_WR_MASK, \
                                    "SYS_CTRL_DFX_FSLDO_STATOVRD_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BSLDO_STATOVRD_OFFSET, \
                                    SYS_CTRL_DFX_BSLDO_STATOVRD_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BSLDO_STATOVRD_RD_MASK, SYS_CTRL_DFX_BSLDO_STATOVRD_WR_MASK, \
                                    "SYS_CTRL_DFX_BSLDO_STATOVRD_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_FSLDO_CTRL_OFFSET, \
                                    SYS_CTRL_DFX_FSLDO_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_FSLDO_CTRL_RD_MASK, SYS_CTRL_DFX_FSLDO_CTRL_WR_MASK, \
                                    "SYS_CTRL_DFX_FSLDO_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BSLDO_CTRL_OFFSET, \
                                    SYS_CTRL_DFX_BSLDO_CTRL_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BSLDO_CTRL_RD_MASK, SYS_CTRL_DFX_BSLDO_CTRL_WR_MASK, \
                                    "SYS_CTRL_DFX_BSLDO_CTRL_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_SBGRLDO_CSR_OFFSET, \
                                    SYS_CTRL_DFX_SBGRLDO_CSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_SBGRLDO_CSR_RD_MASK, SYS_CTRL_DFX_SBGRLDO_CSR_WR_MASK, \
                                    "SYS_CTRL_DFX_SBGRLDO_CSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_BISR_CSR_OFFSET, \
                                    SYS_CTRL_DFX_BISR_CSR_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_BISR_CSR_RD_MASK, SYS_CTRL_DFX_BISR_CSR_WR_MASK, \
                                    "SYS_CTRL_DFX_BISR_CSR_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_DFX_DBGMSGCMD_OFFSET, \
                                    SYS_CTRL_DFX_DBGMSGCMD_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_DFX_DBGMSGCMD_RD_MASK, SYS_CTRL_DFX_DBGMSGCMD_WR_MASK, \
                                    "SYS_CTRL_DFX_DBGMSGCMD_OFFSET");

            //write_read_expect_18a(base_address[i]+SYS_CTRL_SCRATCHTOP_OFFSET, \
                                    SYS_CTRL_SCRATCHTOP_DEFAULT, write_data, expected_data, \
                                    SYS_CTRL_SCRATCHTOP_RD_MASK, SYS_CTRL_SCRATCHTOP_WR_MASK, \
                                    "SYS_CTRL_SCRATCHTOP_OFFSET");

        }

    }

}
