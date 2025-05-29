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
    V2D0_AV2D_APB_0_CSR_BASE, V2D0_AV2D_APB_1_CSR_BASE, V2D1_AV2D_APB_0_CSR_BASE, V2D1_AV2D_APB_1_CSR_BASE, V2D2_AV2D_APB_0_CSR_BASE,
    V2D2_AV2D_APB_1_CSR_BASE, V2D3_AV2D_APB_0_CSR_BASE, V2D3_AV2D_APB_1_CSR_BASE, V2D4_AV2D_APB_0_CSR_BASE, V2D4_AV2D_APB_1_CSR_BASE,
    V2D5_AV2D_APB_0_CSR_BASE, V2D5_AV2D_APB_1_CSR_BASE, V2D6_AV2D_APB_0_CSR_BASE, V2D6_AV2D_APB_1_CSR_BASE, V2D7_AV2D_APB_0_CSR_BASE,
    V2D7_AV2D_APB_1_CSR_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+AV2D_CSR_AV2D_SCRATCH_OFFSET, \
                                    AV2D_CSR_AV2D_SCRATCH_DEFAULT, \
                                    AV2D_CSR_AV2D_SCRATCH_RD_MASK, "AV2D_CSR_AV2D_SCRATCH_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_APB_BRI_STAT_OFFSET, \
                                    AV2D_CSR_APB_BRI_STAT_DEFAULT, \
                                    AV2D_CSR_APB_BRI_STAT_RD_MASK, "AV2D_CSR_APB_BRI_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_GNRL_CSR_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_GNRL_CSR_RD_MASK, "AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET");
//Commenting this register as per discussion with emulation validation owner of this IP, and ensured the registers are getting exercise in their test case
//        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_SIF_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_SIF_CTRL_RD_MASK, "AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_SIF_SMPL_CNT_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_SIF_SMPL_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_SIF_SMPL_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_SIF_SMPL_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_BUF_STAT_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_BUF_STAT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_BUF_STAT_RD_MASK, "AV2D_CSR_TX_CSR_TX_BUF_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PTR_BOUND1_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PTR_BOUND1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PTR_BOUND2_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PTR_BOUND2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PTR_BOUND3_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PTR_BOUND3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND1_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND2_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND3_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_STRM_CNT1_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_STRM_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_STRM_CNT2_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_STRM_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_STRM_CNT3_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_STRM_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_STRM_CNT1_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_STRM_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_STRM_CNT2_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_STRM_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_CSR_TX_PD_STRM_CNT3_OFFSET, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_TX_CSR_TX_PD_STRM_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_GNRL_CSR_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_GNRL_CSR_RD_MASK, "AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PACKET_SZ_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PACKET_SZ_RD_MASK, "AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT0_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT1_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_IN_SMPL_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_STRM_CNT1_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_STRM_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_STRM_CNT2_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_STRM_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_STRM_CNT3_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_STRM_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PD_STRM_CNT0_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_PD_STRM_CNT0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PD_STRM_CNT1_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_PD_STRM_CNT1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PD_STRM_CNT2_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_PD_STRM_CNT2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PD_STRM_CNT3_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_PD_STRM_CNT3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_RX_CSR_RX_PD_STRM_CNT4_OFFSET, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT, \
                                    AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_RD_MASK, "AV2D_CSR_RX_CSR_RX_PD_STRM_CNT4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_PIF_CTRL_OFFSET, \
                                    AV2D_CSR_PIF_CTRL_DEFAULT, \
                                    AV2D_CSR_PIF_CTRL_RD_MASK, "AV2D_CSR_PIF_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START0_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START1_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START2_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START3_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_START3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO0_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO1_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO2_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO3_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO4_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO5_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO6_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO7_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_BUF_WM_HILO7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                                    AV2D_CSR_TX_BUF_WM_TX_START_WM_DEFAULT, \
                                    AV2D_CSR_TX_BUF_WM_TX_START_WM_RD_MASK, "AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_INT_CSR_INT_STAT_OFFSET, \
                                    AV2D_CSR_INT_CSR_INT_STAT_DEFAULT, \
                                    AV2D_CSR_INT_CSR_INT_STAT_RD_MASK, "AV2D_CSR_INT_CSR_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, \
                                    AV2D_CSR_INT_CSR_INT_HIGH_EN_DEFAULT, \
                                    AV2D_CSR_INT_CSR_INT_HIGH_EN_RD_MASK, "AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, \
                                    AV2D_CSR_INT_CSR_INT_LOW_EN_DEFAULT, \
                                    AV2D_CSR_INT_CSR_INT_LOW_EN_RD_MASK, "AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_INT_CSR_INT_CLR_OFFSET, \
                                    AV2D_CSR_INT_CSR_INT_CLR_DEFAULT, \
                                    AV2D_CSR_INT_CSR_INT_CLR_RD_MASK, "AV2D_CSR_INT_CSR_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_INT_CSR_INT_FORCE_OFFSET, \
                                    AV2D_CSR_INT_CSR_INT_FORCE_DEFAULT, \
                                    AV2D_CSR_INT_CSR_INT_FORCE_RD_MASK, "AV2D_CSR_INT_CSR_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R0_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R0_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R0_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R1_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R1_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R1_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R2_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R2_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R2_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R3_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R3_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R3_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R4_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R4_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R4_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R5_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R5_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R5_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R6_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R6_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R6_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_SMON_CSR_SMON_R7_OFFSET, \
                                    AV2D_CSR_SMON_CSR_SMON_R7_DEFAULT, \
                                    AV2D_CSR_SMON_CSR_SMON_R7_RD_MASK, "AV2D_CSR_SMON_CSR_SMON_R7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO0_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO1_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO2_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO3_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO4_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO5_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO6_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO7_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_INFO7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL0_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL1_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL2_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL3_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL4_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL5_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL6_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL7_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_CTRL7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_STAT_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_STAT_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_STAT_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR0_TX_BUF_ECC_ERR_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO0_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO1_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO2_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO3_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO4_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO5_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO6_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO7_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_INFO_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_INFO7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL0_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL0_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL1_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL2_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL3_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL3_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL4_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL4_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL5_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL5_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL6_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL6_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL7_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_CTRL_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_CTRL7_OFFSET");

        read_reg_expect_18a(base_address[i]+AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_STAT_OFFSET, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_STAT_DEFAULT, \
                                    AV2D_CSR_TX_BUF_ECC_CSR_TX_BUF_ECC_ERR_STAT_RD_MASK, "AV2D_CSR_TX_BUF_ECC_CSR1_TX_BUF_ECC_ERR_STAT_OFFSET");

    }

}
