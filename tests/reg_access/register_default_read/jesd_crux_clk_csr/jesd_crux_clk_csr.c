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
    DLNK_JESD0_CRUX_CLK_CSR_BASE, DLNK_JESD1_CRUX_CLK_CSR_BASE, DLNK_JESD2_CRUX_CLK_CSR_BASE, DLNK_JESD3_CRUX_CLK_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_SCRATCH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_SCRATCH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_SCRATCH_RD_MASK, "JESD_CRUX_CLK_CSR_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_APB_BRDG_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_APB_BRDG_STAT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_APB_BRDG_STAT_RD_MASK, "JESD_CRUX_CLK_CSR_APB_BRDG_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_RX_MEM_STRM_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_TOP_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_VNSH_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_TIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_SRC_START_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_FILL_LVL_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_DATA_CAP_FRZ_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_OVRFLW_STICKY_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_UNDERFLW_STICKY_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_INDIR_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_RD_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_WR_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_WR_DATA15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RSB_RD_DATA_RD_MASK, "JESD_CRUX_CLK_CSR_RSB_RD_DATA15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_MEM_TBL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_MEM_TBL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_WR_PTR_TBL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_RD_PTR_TBL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_MEM_STS15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL16_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL17_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL18_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL19_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL20_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL21_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL22_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL23_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL24_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL24_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL25_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL25_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL26_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL26_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL27_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL27_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL28_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL28_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL29_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL29_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL30_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL30_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL31_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_MANTISSA_CTL31_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_RX_DECOMP_EXP_CTL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_VMLGA_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_VMLGA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_VMLGA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_VMLGA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_VNSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_VNSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_VNSH_RD_MASK, "JESD_CRUX_CLK_CSR_TX_VNSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TOP_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TOP_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TOP_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TOP_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_NUM_VALID_STR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_TRIG_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_BUF_FILL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_BUF_OVERFLOW_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_APB_MEM_WADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_FULL_WATER_MARK_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_FULL_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_RD_MASK, "JESD_CRUX_CLK_CSR_TX_ECC_GEN_DIS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_TSB_CAP_MODE_CLR_WRPTR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL16_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL16_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL17_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL17_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL18_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL18_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL19_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL19_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL20_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL20_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL21_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL21_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL22_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL22_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL23_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL23_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL24_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL24_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL25_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL25_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL26_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL26_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL27_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL27_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL28_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL28_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL29_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL29_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL30_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL30_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL31_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_BITFORMAT_CTL31_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_ADDR15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_SIZE15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_MEM_WPTR15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA_RD_MASK, "JESD_CRUX_CLK_CSR_TX_MEM_APB_WDATA15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_TSB_RD_TRIG_LVL15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_NSIP_HALT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_RD_MASK, "JESD_CRUX_CLK_CSR_NSIP_HALT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_LPBK_CTL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_LPBK_CTL_RD_MASK, "JESD_CRUX_CLK_CSR_LPBK_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_OFFSET, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_RD_MASK, "JESD_CRUX_CLK_CSR_NSIP_HALT_DONE_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_WNDW_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MEA_TIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MIN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_DATARATE_MAX_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_WNDW_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_PEAK_MAX_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MEA_TIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_STALL_MAX_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_CRUX_PEAK_STALL_MAX_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_RCV_FLIT_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_WNDW_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_ERR_THRSH_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MEA_TIMER_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MIN_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_CRUX_DATARATE_MAX_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CAP_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_STS_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_SIG_MON_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_SIG_SEL_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_DBG_CAP_VLD_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ALM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_CMN_ERR_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_STS_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_INTR_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_INTR_ONLY_ERR_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_NSIP_ALRM_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_RSB_ECC_ERR_FRC_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_IDX_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_CNT_RDATA_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_RX_STRM_SENT_FLIT_CNT15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT2_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT3_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT4_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT4_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT5_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT5_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT6_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT6_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT7_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT7_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT8_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT8_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT9_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT9_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT10_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT10_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT11_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT11_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT12_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT12_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT13_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT13_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT14_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT14_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT15_OFFSET, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT_RD_MASK, "JESD_CRUX_CLK_CSR_TX_STRM_RCV_FLIT_CNT15_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_THRSH1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_NUM1_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER0_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER0_OFFSET");

        read_reg_expect_18a(base_address[i]+JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER1_OFFSET, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_DEFAULT, \
                                    JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER_RD_MASK, "JESD_CRUX_CLK_CSR_CRUX_CLK_WNDW_ERR_WNDW_TIMER1_OFFSET");

    }

}
