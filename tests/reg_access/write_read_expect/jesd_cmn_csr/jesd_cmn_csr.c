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
    DLNK_JESD0_CMN_CSR_BASE, DLNK_JESD1_CMN_CSR_BASE, DLNK_JESD2_CMN_CSR_BASE, DLNK_JESD3_CMN_CSR_BASE 
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
        
            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_SCRATCH_OFFSET, \
                                    JESD_CMN_CSR_SCRATCH_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_SCRATCH_RD_MASK, JESD_CMN_CSR_SCRATCH_WR_MASK, \
                                    "JESD_CMN_CSR_SCRATCH_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_APB_BRDG_STAT_OFFSET, \
                                    JESD_CMN_CSR_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_APB_BRDG_STAT_RD_MASK, JESD_CMN_CSR_APB_BRDG_STAT_WR_MASK, \
                                    "JESD_CMN_CSR_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_JESD_MODE_OFFSET, \
                                    JESD_CMN_CSR_TX_JESD_MODE_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_JESD_MODE_RD_MASK, JESD_CMN_CSR_TX_JESD_MODE_WR_MASK, \
                                    "JESD_CMN_CSR_TX_JESD_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_DATA_DLY_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_CNT_EN_RD_MASK, JESD_CMN_CSR_TX_SYSREF_DATA_DLY_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_DATA_DLY_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_IP_CLK_CTRL_OFFSET, \
                                    JESD_CMN_CSR_TX_IP_CLK_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_IP_CLK_CTRL_RD_MASK, JESD_CMN_CSR_TX_IP_CLK_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_TX_IP_CLK_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_TSAD_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_TSAD_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_TX_SYSREF_TSAD_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_TSAD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYNC_POINT_CTRL_OFFSET, \
                                    JESD_CMN_CSR_TX_SYNC_POINT_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_TX_SYNC_POINT_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYNC_POINT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_IP_SYSREF_CFG_OFFSET, \
                                    JESD_CMN_CSR_TX_IP_SYSREF_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_IP_SYSREF_CFG_RD_MASK, JESD_CMN_CSR_TX_IP_SYSREF_CFG_WR_MASK, \
                                    "JESD_CMN_CSR_TX_IP_SYSREF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_RD_MASK, JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_CLK_1P5G_DIV_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_CLK_GEN_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_CLK_GEN_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_TX_CLK_GEN_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_CLK_GEN_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_IP_SYSREF_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_IP_SYSREF_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_IP_SYSREF_EN_RD_MASK, JESD_CMN_CSR_TX_IP_SYSREF_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_IP_SYSREF_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYNC_POINT_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_FRAC_CLK_GEN_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_OFFSET, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_RD_MASK, JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_WR_MASK, \
                                    "JESD_CMN_CSR_TX_FRAC_CLK_PERIOD_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_OFFSET, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_RD_MASK, JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_WR_MASK, \
                                    "JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P1_OFFSET, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P1_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P1_RD_MASK, JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P1_WR_MASK, \
                                    "JESD_CMN_CSR_TX_FRAC_CLK_GATE_CTL_P1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_BFN_SYSREF_SEL_OFFSET, \
                                    JESD_CMN_CSR_TX_BFN_SYSREF_SEL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_BFN_SYSREF_SEL_RD_MASK, JESD_CMN_CSR_TX_BFN_SYSREF_SEL_WR_MASK, \
                                    "JESD_CMN_CSR_TX_BFN_SYSREF_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_OFFSET, \
                                    JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_WR_MASK, \
                                    "JESD_CMN_CSR_TX_BFN_SYSREF_TSAD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_OFFSET, \
                                    JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_BFN_SYNC_POINT_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_INT_CNT_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_INT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_INT_CNT_RD_MASK, JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_INT_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_INT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_FRAC_CNT_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_FRAC_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_FRAC_CNT_RD_MASK, JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_FRAC_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1G_FRAC_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_INT_CNT_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_INT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_INT_CNT_RD_MASK, JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_INT_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_INT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_OFFSET, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_RD_MASK, JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_JESD_MODE_OFFSET, \
                                    JESD_CMN_CSR_RX_JESD_MODE_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_JESD_MODE_RD_MASK, JESD_CMN_CSR_RX_JESD_MODE_WR_MASK, \
                                    "JESD_CMN_CSR_RX_JESD_MODE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_DATA_DLY_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_SYSREF_DATA_DLY_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_DATA_DLY_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_IP_CLK_CTRL_OFFSET, \
                                    JESD_CMN_CSR_RX_IP_CLK_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_IP_CLK_CTRL_RD_MASK, JESD_CMN_CSR_RX_IP_CLK_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_RX_IP_CLK_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_TSAD_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_TSAD_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_RX_SYSREF_TSAD_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_TSAD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYNC_POINT_CTRL_OFFSET, \
                                    JESD_CMN_CSR_RX_SYNC_POINT_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_RX_SYNC_POINT_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYNC_POINT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_IP_SYSREF_CFG_OFFSET, \
                                    JESD_CMN_CSR_RX_IP_SYSREF_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_IP_SYSREF_CFG_RD_MASK, JESD_CMN_CSR_RX_IP_SYSREF_CFG_WR_MASK, \
                                    "JESD_CMN_CSR_RX_IP_SYSREF_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_RD_MASK, JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_CLK_1P5G_DIV_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_CLK_GEN_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_CLK_GEN_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_RX_CLK_GEN_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_CLK_GEN_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_IP_SYSREF_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_IP_SYSREF_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_IP_SYSREF_EN_RD_MASK, JESD_CMN_CSR_RX_IP_SYSREF_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_IP_SYSREF_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYNC_POINT_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_RD_MASK, JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_FRAC_CLK_GEN_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_FRAC_CLK_PERIOD_CTL_OFFSET, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_PERIOD_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_PERIOD_CTL_RD_MASK, JESD_CMN_CSR_RX_FRAC_CLK_PERIOD_CTL_WR_MASK, \
                                    "JESD_CMN_CSR_RX_FRAC_CLK_PERIOD_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_OFFSET, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_RD_MASK, JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_WR_MASK, \
                                    "JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P1_OFFSET, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P1_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P1_RD_MASK, JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P1_WR_MASK, \
                                    "JESD_CMN_CSR_RX_FRAC_CLK_GATE_CTL_P1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_BFN_SYSREF_SEL_OFFSET, \
                                    JESD_CMN_CSR_RX_BFN_SYSREF_SEL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_BFN_SYSREF_SEL_RD_MASK, JESD_CMN_CSR_RX_BFN_SYSREF_SEL_WR_MASK, \
                                    "JESD_CMN_CSR_RX_BFN_SYSREF_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_OFFSET, \
                                    JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_RD_MASK, JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_WR_MASK, \
                                    "JESD_CMN_CSR_RX_BFN_SYSREF_TSAD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_OFFSET, \
                                    JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_RD_MASK, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_WR_MASK, \
                                    "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CTRL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_RD_MASK, JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_BFN_SYNC_POINT_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_INT_CNT_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_INT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_INT_CNT_RD_MASK, JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_INT_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_INT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_FRAC_CNT_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_FRAC_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_FRAC_CNT_RD_MASK, JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_FRAC_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1G_FRAC_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_INT_CNT_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_INT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_INT_CNT_RD_MASK, JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_INT_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_INT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_OFFSET, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_RD_MASK, JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SYSREF_DATA_DLY_1P5G_FRAC_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SP_MON_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_SP_MON_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SP_MON_EN_RD_MASK, JESD_CMN_CSR_RX_SP_MON_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SP_MON_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SP_MON_CAP_EN_OFFSET, \
                                    JESD_CMN_CSR_RX_SP_MON_CAP_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SP_MON_CAP_EN_RD_MASK, JESD_CMN_CSR_RX_SP_MON_CAP_EN_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SP_MON_CAP_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SP_MON_STS_CLR_OFFSET, \
                                    JESD_CMN_CSR_RX_SP_MON_STS_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SP_MON_STS_CLR_RD_MASK, JESD_CMN_CSR_RX_SP_MON_STS_CLR_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SP_MON_STS_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_SP_MON_CFG_OFFSET, \
                                    JESD_CMN_CSR_RX_SP_MON_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_RX_SP_MON_CFG_RD_MASK, JESD_CMN_CSR_RX_SP_MON_CFG_WR_MASK, \
                                    "JESD_CMN_CSR_RX_SP_MON_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SP_MON_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_SP_MON_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SP_MON_EN_RD_MASK, JESD_CMN_CSR_TX_SP_MON_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SP_MON_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SP_MON_CAP_EN_OFFSET, \
                                    JESD_CMN_CSR_TX_SP_MON_CAP_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SP_MON_CAP_EN_RD_MASK, JESD_CMN_CSR_TX_SP_MON_CAP_EN_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SP_MON_CAP_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SP_MON_STS_CLR_OFFSET, \
                                    JESD_CMN_CSR_TX_SP_MON_STS_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SP_MON_STS_CLR_RD_MASK, JESD_CMN_CSR_TX_SP_MON_STS_CLR_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SP_MON_STS_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_SP_MON_CFG_OFFSET, \
                                    JESD_CMN_CSR_TX_SP_MON_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_TX_SP_MON_CFG_RD_MASK, JESD_CMN_CSR_TX_SP_MON_CFG_WR_MASK, \
                                    "JESD_CMN_CSR_TX_SP_MON_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_UL_DL_EN_CFG_OFFSET, \
                                    JESD_CMN_CSR_UL_DL_EN_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_UL_DL_EN_CFG_RD_MASK, JESD_CMN_CSR_UL_DL_EN_CFG_WR_MASK, \
                                    "JESD_CMN_CSR_UL_DL_EN_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CMN_CSR_CLK_OBS_CNT_EN_OFFSET, \
                                    JESD_CMN_CSR_CLK_OBS_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CMN_CSR_CLK_OBS_CNT_EN_RD_MASK, JESD_CMN_CSR_CLK_OBS_CNT_EN_WR_MASK, \
                                    "JESD_CMN_CSR_CLK_OBS_CNT_EN_OFFSET");
									
			


           
        }

    }

			

        
