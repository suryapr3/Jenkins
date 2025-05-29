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
    DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE
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
            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_SCRATCH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_SCRATCH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_SCRATCH_RD_MASK, JESD_CRUX_CLK_CSR_SCRATCH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_SCRATCH_OFFSET");

//            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_APB_BRDG_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_APB_BRDG_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_APB_BRDG_STAT_RD_MASK, JESD_CRUX_CLK_CSR_APB_BRDG_STAT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_APB_BRDG_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_RD_MASK, JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_RD_MASK, JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_RD_MASK, JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_WR_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, JESD_CRUX_CLK_CSR_RSB_RD_DATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL16_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL17_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL18_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL19_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL20_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL21_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL22_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL23_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL23_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL24_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL24_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL25_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL25_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL26_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL26_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL27_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL27_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL28_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL28_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL29_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL29_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL30_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL30_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL31_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL31_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_VMLGA_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_VMLGA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_VMLGA_RD_MASK, JESD_CRUX_CLK_CSR_TX_VMLGA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_VMLGA_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_VNSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_VNSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_VNSH_RD_MASK, JESD_CRUX_CLK_CSR_TX_VNSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_VNSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TOP_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TOP_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TOP_RD_MASK, JESD_CRUX_CLK_CSR_TX_TOP_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TOP_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_RD_MASK, JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CFG_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_RD_MASK, JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL16_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL16_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL17_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL17_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL18_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL18_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL19_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL19_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL20_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL20_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL21_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL21_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL22_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL22_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL23_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL23_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL24_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL24_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL25_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL25_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL26_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL26_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL27_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL27_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL28_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL28_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL29_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL29_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL30_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL30_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL31_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL31_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_NSIP_HALT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_RD_MASK, JESD_CRUX_CLK_CSR_NSIP_HALT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_NSIP_HALT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_LPBK_CTL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_LPBK_CTL_RD_MASK, JESD_CRUX_CLK_CSR_LPBK_CTL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_OFFSET, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_RD_MASK, JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT2_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT3_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT4_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT5_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT6_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT7_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT8_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT9_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT10_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT11_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT12_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT13_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT14_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT15_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM1_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER0_OFFSET");

            write_read_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_DEFAULT, write_data, expected_data, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_RD_MASK, JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_WR_MASK, \
                                    "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER1_OFFSET");

        }

    }

}
