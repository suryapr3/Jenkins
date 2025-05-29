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
    VEXA_ABCNOC_JESD_0_P0_0X00000400_BASE, VEXA_ABCNOC_JESD_0_P1_0X00000800_BASE, VEXA_ABCNOC_JESD_1_P0_0X00000C00_BASE, VEXA_ABCNOC_JESD_1_P1_0X00001000_BASE, VEXA_ABCNOC_RBC_0X00018800_BASE,
    VEXA_ABCNOC_RBC_RBM_0X00000000_BASE, VEXA_ABCNOC_RCS_0_P0_0X00001400_BASE, VEXA_ABCNOC_RXFB_0_P0_0X00001800_BASE, VEXA_ABCNOC_RXFB_0_P1_0X00001C00_BASE, VEXA_ABCNOC_RXFB_1_P0_0X00002000_BASE,
    VEXA_ABCNOC_RXFB_1_P1_0X00002400_BASE, VEXA_ABCNOC_V2D_0_P0_0X00002800_BASE, VEXA_ABCNOC_V2D_0_P1_0X00002C00_BASE, VEXA_ABCNOC_V2D_0_P2_0X00003000_BASE, VEXA_ABCNOC_V2D_0_P3_0X00003400_BASE,
    VEXA_ABCNOC_V2D_1_P0_0X00003800_BASE, VEXA_ABCNOC_V2D_1_P1_0X00003C00_BASE, VEXA_ABCNOC_V2D_1_P2_0X00004000_BASE, VEXA_ABCNOC_V2D_1_P3_0X00004400_BASE, VEXA_ABCNOC_V2D_2_P0_0X00004800_BASE,
    VEXA_ABCNOC_V2D_2_P1_0X00004C00_BASE, VEXA_ABCNOC_V2D_2_P2_0X00005000_BASE, VEXA_ABCNOC_V2D_2_P3_0X00005400_BASE, VEXA_ABCNOC_V2D_3_P0_0X00005800_BASE, VEXA_ABCNOC_V2D_3_P1_0X00005C00_BASE,
    VEXA_ABCNOC_V2D_3_P2_0X00006000_BASE, VEXA_ABCNOC_V2D_3_P3_0X00006400_BASE, VEXA_ABCNOC_V2D_4_P0_0X00006800_BASE, VEXA_ABCNOC_V2D_4_P1_0X00006C00_BASE, VEXA_ABCNOC_V2D_4_P2_0X00007000_BASE,
    VEXA_ABCNOC_V2D_4_P3_0X00007400_BASE, VEXA_ABCNOC_V2D_5_P0_0X00007800_BASE, VEXA_ABCNOC_V2D_5_P1_0X00007C00_BASE, VEXA_ABCNOC_V2D_5_P2_0X00008000_BASE, VEXA_ABCNOC_V2D_5_P3_0X00008400_BASE,
    VEXA_ABCNOC_V2D_6_P0_0X00008800_BASE, VEXA_ABCNOC_V2D_6_P1_0X00008C00_BASE, VEXA_ABCNOC_V2D_6_P2_0X00009000_BASE, VEXA_ABCNOC_V2D_6_P3_0X00009400_BASE, VEXA_ABCNOC_V2D_7_P0_0X00009800_BASE,
    VEXA_ABCNOC_V2D_7_P1_0X00009C00_BASE, VEXA_ABCNOC_V2D_7_P2_0X0000A000_BASE, VEXA_ABCNOC_V2D_7_P3_0X0000A400_BASE, VEXA_ABCNOC_VE_0_0_P0_0X0000A800_BASE, VEXA_ABCNOC_VE_0_1_P0_0X0000AC00_BASE,
    VEXA_ABCNOC_VE_0_2_P0_0X0000B000_BASE, VEXA_ABCNOC_VE_0_3_P0_0X0000B400_BASE, VEXA_ABCNOC_VE_0_4_P0_0X0000B800_BASE, VEXA_ABCNOC_VE_0_5_P0_0X0000BC00_BASE, VEXA_ABCNOC_VE_0_6_P0_0X0000C000_BASE,
    VEXA_ABCNOC_VE_0_7_P0_0X0000C400_BASE, VEXA_ABCNOC_VE_1_0_P0_0X0000C800_BASE, VEXA_ABCNOC_VE_1_1_P0_0X0000CC00_BASE, VEXA_ABCNOC_VE_1_2_P0_0X0000D000_BASE, VEXA_ABCNOC_VE_1_3_P0_0X0000D400_BASE,
    VEXA_ABCNOC_VE_1_4_P0_0X0000D800_BASE, VEXA_ABCNOC_VE_1_5_P0_0X0000DC00_BASE, VEXA_ABCNOC_VE_1_6_P0_0X0000E000_BASE, VEXA_ABCNOC_VE_1_7_P0_0X0000E400_BASE, VEXA_ABCNOC_VE_2_0_P0_0X0000E800_BASE,
    VEXA_ABCNOC_VE_2_1_P0_0X0000EC00_BASE, VEXA_ABCNOC_VE_2_2_P0_0X0000F000_BASE, VEXA_ABCNOC_VE_2_3_P0_0X0000F400_BASE, VEXA_ABCNOC_VE_2_4_P0_0X0000F800_BASE, VEXA_ABCNOC_VE_2_5_P0_0X0000FC00_BASE,
    VEXA_ABCNOC_VE_2_6_P0_0X00010000_BASE, VEXA_ABCNOC_VE_2_7_P0_0X00010400_BASE, VEXA_ABCNOC_VE_3_0_P0_0X00010800_BASE, VEXA_ABCNOC_VE_3_1_P0_0X00010C00_BASE, VEXA_ABCNOC_VE_3_2_P0_0X00011000_BASE,
    VEXA_ABCNOC_VE_3_3_P0_0X00011400_BASE, VEXA_ABCNOC_VE_3_4_P0_0X00011800_BASE, VEXA_ABCNOC_VE_3_5_P0_0X00011C00_BASE, VEXA_ABCNOC_VE_3_6_P0_0X00012000_BASE, VEXA_ABCNOC_VE_3_7_P0_0X00012400_BASE,
    VEXA_ABCNOC_VE_4_0_P0_0X00012800_BASE, VEXA_ABCNOC_VE_4_1_P0_0X00012C00_BASE, VEXA_ABCNOC_VE_4_2_P0_0X00013000_BASE, VEXA_ABCNOC_VE_4_3_P0_0X00013400_BASE, VEXA_ABCNOC_VE_4_4_P0_0X00013800_BASE,
    VEXA_ABCNOC_VE_4_5_P0_0X00013C00_BASE, VEXA_ABCNOC_VE_4_6_P0_0X00014000_BASE, VEXA_ABCNOC_VE_4_7_P0_0X00014400_BASE, VEXA_ABCNOC_VHA_0_P0_0X00014800_BASE, VEXA_ABCNOC_VHA_0_P1_0X00014C00_BASE,
    VEXA_ABCNOC_VHA_1_P0_0X00015000_BASE, VEXA_ABCNOC_VHA_1_P1_0X00015400_BASE, VEXA_ABCNOC_VHA_2_P0_0X00015800_BASE, VEXA_ABCNOC_VHA_2_P1_0X00015C00_BASE, VEXA_ABCNOC_VHA_3_P0_0X00016000_BASE,
    VEXA_ABCNOC_VHA_3_P1_0X00016400_BASE, VEXA_ABCNOC_VHA_4_P0_0X00016800_BASE, VEXA_ABCNOC_VHA_4_P1_0X00016C00_BASE, VEXA_ABCNOC_VHA_5_P0_0X00017000_BASE, VEXA_ABCNOC_VHA_5_P1_0X00017400_BASE,
    VEXA_ABCNOC_VHA_6_P0_0X00017800_BASE, VEXA_ABCNOC_VHA_6_P1_0X00017C00_BASE, VEXA_ABCNOC_VHA_7_P0_0X00018000_BASE, VEXA_ABCNOC_VHA_7_P1_0X00018400_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_CLK_GATING_OVRD_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_CLK_GATING_OVRD_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_CLK_GATING_OVRD_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_CLK_GATING_OVRD_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_ERR_MASK_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_MASK_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_MASK_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_ERR_MASK_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RBC_RBM_63_30_RBM_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RBC_RBM_63_30_RBM_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RBC_RBM_63_30_RBM_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_0_P0_64_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_0_P1_65_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_1_P0_66_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_JESD_1_P1_67_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RCS_0_P0_118_11_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P0_94_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P1_95_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P2_96_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_4_P3_97_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P0_100_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P1_101_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P2_102_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_5_P3_103_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P0_106_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P1_107_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P2_108_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_6_P3_109_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P0_112_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P1_113_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P2_114_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_V2D_7_P3_115_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_0_P0_68_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_0_P1_69_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_1_P0_74_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_1_P1_75_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_2_P0_80_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_2_P1_81_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_3_P0_86_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_3_P1_87_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_4_P0_92_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_4_P1_93_62_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_5_P0_98_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_5_P1_99_64_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_6_P0_104_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_6_P1_105_66_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_7_P0_110_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_STRTX_BRDG_ID_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_STRTX_BRDG_ID_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_STRTX_BRDG_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_CTRL_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_CTRL_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_CTRL_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_STAT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_INJECT_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_INJECT_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_TX_ERR_INJECT_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, \
                                    NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, "NOC_BRDG_VHA_7_P1_111_68_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_AGENT_RBC_CLK_GATING_OVRD_VAL_OFFSET, \
                                    NOC_AGENT_RBC_CLK_GATING_OVRD_VAL_DEFAULT, \
                                    NOC_AGENT_RBC_CLK_GATING_OVRD_VAL_RD_MASK, "NOC_AGENT_RBC_CLK_GATING_OVRD_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_AGENT_RBC_DBG_RBM_ID_VAL_OFFSET, \
                                    NOC_AGENT_RBC_DBG_RBM_ID_VAL_DEFAULT, \
                                    NOC_AGENT_RBC_DBG_RBM_ID_VAL_RD_MASK, "NOC_AGENT_RBC_DBG_RBM_ID_VAL_OFFSET");

        read_reg_expect_18a(base_address[i]+NOC_AGENT_RBC_DBG_PENDING_TRANSACTIONS_VAL_OFFSET, \
                                    NOC_AGENT_RBC_DBG_PENDING_TRANSACTIONS_VAL_DEFAULT, \
                                    NOC_AGENT_RBC_DBG_PENDING_TRANSACTIONS_VAL_RD_MASK, "NOC_AGENT_RBC_DBG_PENDING_TRANSACTIONS_VAL_OFFSET");

    }

}
