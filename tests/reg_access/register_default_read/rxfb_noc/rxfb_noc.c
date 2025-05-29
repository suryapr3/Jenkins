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

    uint32_t base_address[] = {VEXA_ABCNOC_RXFB_0_P0_0X00001800_BASE, VEXA_ABCNOC_RXFB_0_P1_0X00001C00_BASE,VEXA_ABCNOC_RXFB_1_P0_0X00002000_BASE,
    VEXA_ABCNOC_RXFB_1_P1_0X00002400_BASE};

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        if(i==0)
        {
            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P0_116_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==1)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_0_P1_117_21_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==2)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P0_119_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

        else if(i==3)
        {

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_STRTX_BRDG_ID_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_CTRL_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_STAT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_TX_ERR_INJECT_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

            read_reg_expect_18a(base_address[i]+NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT,  \
                                    NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, \
                                    "NOC_BRDG_RXFB_1_P1_120_51_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
        }

    }

}
