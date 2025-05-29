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
    VEXA_ABCNOC_VE_0_0_P0_0X0000A800_BASE, VEXA_ABCNOC_VE_0_1_P0_0X0000AC00_BASE,
    VEXA_ABCNOC_VE_0_2_P0_0X0000B000_BASE, VEXA_ABCNOC_VE_0_3_P0_0X0000B400_BASE, VEXA_ABCNOC_VE_0_4_P0_0X0000B800_BASE, VEXA_ABCNOC_VE_0_5_P0_0X0000BC00_BASE, VEXA_ABCNOC_VE_0_6_P0_0X0000C000_BASE,
    VEXA_ABCNOC_VE_0_7_P0_0X0000C400_BASE, VEXA_ABCNOC_VE_1_0_P0_0X0000C800_BASE, VEXA_ABCNOC_VE_1_1_P0_0X0000CC00_BASE, VEXA_ABCNOC_VE_1_2_P0_0X0000D000_BASE, VEXA_ABCNOC_VE_1_3_P0_0X0000D400_BASE,
    VEXA_ABCNOC_VE_1_4_P0_0X0000D800_BASE, VEXA_ABCNOC_VE_1_5_P0_0X0000DC00_BASE, VEXA_ABCNOC_VE_1_6_P0_0X0000E000_BASE, VEXA_ABCNOC_VE_1_7_P0_0X0000E400_BASE, VEXA_ABCNOC_VE_2_0_P0_0X0000E800_BASE,
    VEXA_ABCNOC_VE_2_1_P0_0X0000EC00_BASE, VEXA_ABCNOC_VE_2_2_P0_0X0000F000_BASE, VEXA_ABCNOC_VE_2_3_P0_0X0000F400_BASE, VEXA_ABCNOC_VE_2_4_P0_0X0000F800_BASE, VEXA_ABCNOC_VE_2_5_P0_0X0000FC00_BASE,
    VEXA_ABCNOC_VE_2_6_P0_0X00010000_BASE, VEXA_ABCNOC_VE_2_7_P0_0X00010400_BASE, VEXA_ABCNOC_VE_3_0_P0_0X00010800_BASE, VEXA_ABCNOC_VE_3_1_P0_0X00010C00_BASE, VEXA_ABCNOC_VE_3_2_P0_0X00011000_BASE,
    VEXA_ABCNOC_VE_3_3_P0_0X00011400_BASE, VEXA_ABCNOC_VE_3_4_P0_0X00011800_BASE, VEXA_ABCNOC_VE_3_5_P0_0X00011C00_BASE, VEXA_ABCNOC_VE_3_6_P0_0X00012000_BASE, VEXA_ABCNOC_VE_3_7_P0_0X00012400_BASE,
    VEXA_ABCNOC_VE_4_0_P0_0X00012800_BASE, VEXA_ABCNOC_VE_4_1_P0_0X00012C00_BASE, VEXA_ABCNOC_VE_4_2_P0_0X00013000_BASE, VEXA_ABCNOC_VE_4_3_P0_0X00013400_BASE, VEXA_ABCNOC_VE_4_4_P0_0X00013800_BASE,
    VEXA_ABCNOC_VE_4_5_P0_0X00013C00_BASE, VEXA_ABCNOC_VE_4_6_P0_0X00014000_BASE, VEXA_ABCNOC_VE_4_7_P0_0X00014400_BASE
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
            LOG_PRINT("i is %d:", i);
            if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
                continue;
            }
            else
            {
                if(i==0)
                {
                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_P0_0_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==1)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_1_P0_1_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==2)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_2_P0_2_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==3)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_3_P0_3_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==4)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_4_P0_4_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==5)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_5_P0_5_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==6)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_6_P0_6_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==7)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_0_7_P0_7_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==8)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_0_P0_8_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==9)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_P0_9_22_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==10)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_2_P0_10_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==11)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_3_P0_11_24_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }


                else if(i==12)
                {
                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_4_P0_12_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==13)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_5_P0_13_26_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }
                
                else if(i==14)
                {
                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register
#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_6_P0_14_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==15)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register
#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_1_7_P0_15_28_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==16)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register
#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_0_P0_16_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==17)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_TX_ERR_STAT_VAL_OFFSET");
#if 0
                //RW(V) Register

#endif

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_1_P0_17_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==18)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_P0_18_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==19)
                {
                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_3_P0_19_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==20)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_4_P0_20_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==21)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_5_P0_21_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==22)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_6_P0_22_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==23)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_2_7_P0_23_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==24)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_0_P0_24_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==25)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_1_P0_25_52_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==26)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_2_P0_26_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==27)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_P0_27_54_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==28)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_4_P0_28_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==29)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_5_P0_29_56_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==30)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_6_P0_30_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==31)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_3_7_P0_31_58_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==32)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_0_P0_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==33)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_1_P0_33_32_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==34)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_2_P0_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==35)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_3_P0_35_34_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==36)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_P0_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==37)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_5_P0_37_36_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==38)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_6_P0_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

                else if(i==39)
                {

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_STRTX_BRDG_ID_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_AB_DEST_DEC_ERR_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_CTRL_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_QOS_WEIGHT_0_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_STRG_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_TX_ERR_STAT_VAL_OFFSET");


                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_VC_B2H_CREDIT_CNTER_VAL_OFFSET");

                write_read_expect_18a(base_address[i]+NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_DEFAULT, write_data, expected_data, \
                                        NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_RD_MASK, NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_WR_MASK, \
                                        "NOC_BRDG_VE_4_7_P0_39_38_NOC_RX_A_SHARED_B2H_CREDIT_CNTER_VAL_OFFSET");
                }

             }

        }

    }
}
