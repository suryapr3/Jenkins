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
    uint32_t error = 0;
    int i;
    init();

    uint32_t base_address[] = {
    VEXA_ABCNOC_V2D_0_P0_0X00002800_BASE, VEXA_ABCNOC_V2D_0_P1_0X00002C00_BASE, VEXA_ABCNOC_V2D_0_P2_0X00003000_BASE, VEXA_ABCNOC_V2D_0_P3_0X00003400_BASE,
    VEXA_ABCNOC_V2D_1_P0_0X00003800_BASE, VEXA_ABCNOC_V2D_1_P1_0X00003C00_BASE, VEXA_ABCNOC_V2D_1_P2_0X00004000_BASE, VEXA_ABCNOC_V2D_1_P3_0X00004400_BASE, VEXA_ABCNOC_V2D_2_P0_0X00004800_BASE,
    VEXA_ABCNOC_V2D_2_P1_0X00004C00_BASE, VEXA_ABCNOC_V2D_2_P2_0X00005000_BASE, VEXA_ABCNOC_V2D_2_P3_0X00005400_BASE, VEXA_ABCNOC_V2D_3_P0_0X00005800_BASE, VEXA_ABCNOC_V2D_3_P1_0X00005C00_BASE,
    VEXA_ABCNOC_V2D_3_P2_0X00006000_BASE, VEXA_ABCNOC_V2D_3_P3_0X00006400_BASE   };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        if(i==0)
        {
            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P0_70_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==1)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P1_71_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==2)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P2_72_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==3)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_0_P3_73_12_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==4)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P0_76_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==5)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P1_77_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");

        }

        else if(i==6)
        {
            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P2_78_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==7)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_1_P3_79_14_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==8)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P0_82_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==9)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P1_83_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==10)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P2_84_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==11)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_2_P3_85_16_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==12)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P0_88_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==13)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P1_89_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==14)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P2_90_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==15)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_V2D_3_P3_91_18_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

    }

}
