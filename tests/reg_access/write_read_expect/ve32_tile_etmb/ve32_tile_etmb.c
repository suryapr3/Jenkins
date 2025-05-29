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
    VEXABCCS0_ETMB_VE32_TILE_BASE, VEXABCCS1_ETMB_VE32_TILE_BASE, VEXABCCS2_ETMB_VE32_TILE_BASE, VEXABCCS3_ETMB_VE32_TILE_BASE, VEXABCCS4_ETMB_VE32_TILE_BASE,
    VEXABCCS5_ETMB_VE32_TILE_BASE, VEXABCCS6_ETMB_VE32_TILE_BASE, VEXABCCS7_ETMB_VE32_TILE_BASE, VEXABCCS8_ETMB_VE32_TILE_BASE, VEXABCCS9_ETMB_VE32_TILE_BASE,
    VEXABCCS10_ETMB_VE32_TILE_BASE, VEXABCCS11_ETMB_VE32_TILE_BASE, VEXABCCS12_ETMB_VE32_TILE_BASE, VEXABCCS13_ETMB_VE32_TILE_BASE, VEXABCCS14_ETMB_VE32_TILE_BASE,
    VEXABCCS15_ETMB_VE32_TILE_BASE, VEXABCCS16_ETMB_VE32_TILE_BASE, VEXABCCS17_ETMB_VE32_TILE_BASE, VEXABCCS18_ETMB_VE32_TILE_BASE, VEXABCCS19_ETMB_VE32_TILE_BASE,
    VEXABCCS20_ETMB_VE32_TILE_BASE, VEXABCCS21_ETMB_VE32_TILE_BASE, VEXABCCS22_ETMB_VE32_TILE_BASE, VEXABCCS23_ETMB_VE32_TILE_BASE, VEXABCCS24_ETMB_VE32_TILE_BASE,
    VEXABCCS25_ETMB_VE32_TILE_BASE, VEXABCCS26_ETMB_VE32_TILE_BASE, VEXABCCS27_ETMB_VE32_TILE_BASE, VEXABCCS28_ETMB_VE32_TILE_BASE, VEXABCCS29_ETMB_VE32_TILE_BASE,
    VEXABCCS30_ETMB_VE32_TILE_BASE, VEXABCCS31_ETMB_VE32_TILE_BASE, VEXABCCS32_ETMB_VE32_TILE_BASE, VEXABCCS33_ETMB_VE32_TILE_BASE, VEXABCCS34_ETMB_VE32_TILE_BASE,
    VEXABCCS35_ETMB_VE32_TILE_BASE, VEXABCCS36_ETMB_VE32_TILE_BASE, VEXABCCS37_ETMB_VE32_TILE_BASE, VEXABCCS38_ETMB_VE32_TILE_BASE, VEXABCCS39_ETMB_VE32_TILE_BASE
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
			LOG_PRINT("i is %d", i);
            if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
                continue;
			}
            else
            {
            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPRGCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCPRGCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPRGCTLR_RD_MASK, VE32_TILE_ETMB_TRCPRGCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPRGCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPROCSELR_OFFSET, \
                                    VE32_TILE_ETMB_TRCPROCSELR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPROCSELR_RD_MASK, VE32_TILE_ETMB_TRCPROCSELR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPROCSELR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSTATR_OFFSET, \
                                    VE32_TILE_ETMB_TRCSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSTATR_RD_MASK, VE32_TILE_ETMB_TRCSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCONFIGR_OFFSET, \
                                    VE32_TILE_ETMB_TRCCONFIGR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCONFIGR_RD_MASK, VE32_TILE_ETMB_TRCCONFIGR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCONFIGR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCAUXCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCAUXCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCAUXCTLR_RD_MASK, VE32_TILE_ETMB_TRCAUXCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCAUXCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCEVENTCTL0R_OFFSET, \
                                    VE32_TILE_ETMB_TRCEVENTCTL0R_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCEVENTCTL0R_RD_MASK, VE32_TILE_ETMB_TRCEVENTCTL0R_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCEVENTCTL0R_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCEVENTCTL1R_OFFSET, \
                                    VE32_TILE_ETMB_TRCEVENTCTL1R_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCEVENTCTL1R_RD_MASK, VE32_TILE_ETMB_TRCEVENTCTL1R_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCEVENTCTL1R_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSTALLCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCSTALLCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSTALLCTLR_RD_MASK, VE32_TILE_ETMB_TRCSTALLCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSTALLCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCTSCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCTSCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCTSCTLR_RD_MASK, VE32_TILE_ETMB_TRCTSCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCTSCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSYNCPR_OFFSET, \
                                    VE32_TILE_ETMB_TRCSYNCPR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSYNCPR_RD_MASK, VE32_TILE_ETMB_TRCSYNCPR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSYNCPR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCCCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCCCCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCCCTLR_RD_MASK, VE32_TILE_ETMB_TRCCCCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCCCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCBBCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCBBCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCBBCTLR_RD_MASK, VE32_TILE_ETMB_TRCBBCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCBBCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCTRACEIDR_OFFSET, \
                                    VE32_TILE_ETMB_TRCTRACEIDR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCTRACEIDR_RD_MASK, VE32_TILE_ETMB_TRCTRACEIDR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCTRACEIDR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCQCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCQCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCQCTLR_RD_MASK, VE32_TILE_ETMB_TRCQCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCQCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVICTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVICTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVICTLR_RD_MASK, VE32_TILE_ETMB_TRCVICTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVICTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVIIECTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVIIECTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVIIECTLR_RD_MASK, VE32_TILE_ETMB_TRCVIIECTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVIIECTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVISSCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVISSCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVISSCTLR_RD_MASK, VE32_TILE_ETMB_TRCVISSCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVISSCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVIPESSCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVIPESSCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVIPESSCTLR_RD_MASK, VE32_TILE_ETMB_TRCVIPESSCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVIPESSCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVDCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVDCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVDCTLR_RD_MASK, VE32_TILE_ETMB_TRCVDCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVDCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVDSACCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVDSACCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVDSACCTLR_RD_MASK, VE32_TILE_ETMB_TRCVDSACCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVDSACCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCVDARCCTLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCVDARCCTLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCVDARCCTLR_RD_MASK, VE32_TILE_ETMB_TRCVDARCCTLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCVDARCCTLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSEQEVR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCSEQEVR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSEQEVR0_RD_MASK, VE32_TILE_ETMB_TRCSEQEVR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSEQEVR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSEQEVR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCSEQEVR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSEQEVR1_RD_MASK, VE32_TILE_ETMB_TRCSEQEVR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSEQEVR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSEQEVR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCSEQEVR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSEQEVR2_RD_MASK, VE32_TILE_ETMB_TRCSEQEVR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSEQEVR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSEQRSTEVR_OFFSET, \
                                    VE32_TILE_ETMB_TRCSEQRSTEVR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSEQRSTEVR_RD_MASK, VE32_TILE_ETMB_TRCSEQRSTEVR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSEQRSTEVR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCSEQSTR_OFFSET, \
                                    VE32_TILE_ETMB_TRCSEQSTR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCSEQSTR_RD_MASK, VE32_TILE_ETMB_TRCSEQSTR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCSEQSTR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCEXTINSELR_OFFSET, \
                                    VE32_TILE_ETMB_TRCEXTINSELR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCEXTINSELR_RD_MASK, VE32_TILE_ETMB_TRCEXTINSELR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCEXTINSELR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCNTRLDVR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCNTRLDVR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCNTRLDVR0_RD_MASK, VE32_TILE_ETMB_TRCCNTRLDVR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCNTRLDVR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCNTCTLR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCNTCTLR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCNTCTLR0_RD_MASK, VE32_TILE_ETMB_TRCCNTCTLR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCNTCTLR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCNTVR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCNTVR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCNTVR0_RD_MASK, VE32_TILE_ETMB_TRCCNTVR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCNTVR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR8_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR8_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR8_RD_MASK, VE32_TILE_ETMB_TRCIDR8_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR8_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR9_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR9_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR9_RD_MASK, VE32_TILE_ETMB_TRCIDR9_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR9_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR10_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR10_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR10_RD_MASK, VE32_TILE_ETMB_TRCIDR10_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR10_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR11_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR11_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR11_RD_MASK, VE32_TILE_ETMB_TRCIDR11_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR11_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR12_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR12_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR12_RD_MASK, VE32_TILE_ETMB_TRCIDR12_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR12_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR13_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR13_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR13_RD_MASK, VE32_TILE_ETMB_TRCIDR13_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR13_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC0_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC0_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC1_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC1_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC2_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC2_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC3_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC3_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC4_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC4_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC5_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC5_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC6_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC6_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIMSPEC7_OFFSET, \
                                    VE32_TILE_ETMB_TRCIMSPEC7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIMSPEC7_RD_MASK, VE32_TILE_ETMB_TRCIMSPEC7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIMSPEC7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR0_RD_MASK, VE32_TILE_ETMB_TRCIDR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR1_RD_MASK, VE32_TILE_ETMB_TRCIDR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR2_RD_MASK, VE32_TILE_ETMB_TRCIDR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR3_RD_MASK, VE32_TILE_ETMB_TRCIDR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR4_RD_MASK, VE32_TILE_ETMB_TRCIDR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR5_RD_MASK, VE32_TILE_ETMB_TRCIDR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR6_RD_MASK, VE32_TILE_ETMB_TRCIDR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCIDR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCIDR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCIDR7_RD_MASK, VE32_TILE_ETMB_TRCIDR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCIDR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR2_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR3_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR4_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR5_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR6_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR7_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR8_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR8_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR8_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR8_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR8_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR9_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR9_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR9_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR9_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR9_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR10_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR10_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR10_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR10_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR10_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCRSCTLR11_OFFSET, \
                                    VE32_TILE_ETMB_TRCRSCTLR11_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCRSCTLR11_RD_MASK, VE32_TILE_ETMB_TRCRSCTLR11_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCRSCTLR11_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCOSLSR_OFFSET, \
                                    VE32_TILE_ETMB_TRCOSLSR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCOSLSR_RD_MASK, VE32_TILE_ETMB_TRCOSLSR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCOSLSR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPDCR_OFFSET, \
                                    VE32_TILE_ETMB_TRCPDCR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPDCR_RD_MASK, VE32_TILE_ETMB_TRCPDCR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPDCR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPDSR_OFFSET, \
                                    VE32_TILE_ETMB_TRCPDSR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPDSR_RD_MASK, VE32_TILE_ETMB_TRCPDSR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPDSR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR0_RD_MASK, VE32_TILE_ETMB_TRCACVR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR1_RD_MASK, VE32_TILE_ETMB_TRCACVR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR2_RD_MASK, VE32_TILE_ETMB_TRCACVR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR3_RD_MASK, VE32_TILE_ETMB_TRCACVR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR4_RD_MASK, VE32_TILE_ETMB_TRCACVR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR5_RD_MASK, VE32_TILE_ETMB_TRCACVR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR6_RD_MASK, VE32_TILE_ETMB_TRCACVR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACVR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCACVR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACVR7_RD_MASK, VE32_TILE_ETMB_TRCACVR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACVR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR0_RD_MASK, VE32_TILE_ETMB_TRCACATR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR1_RD_MASK, VE32_TILE_ETMB_TRCACATR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR2_RD_MASK, VE32_TILE_ETMB_TRCACATR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR3_RD_MASK, VE32_TILE_ETMB_TRCACATR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR4_RD_MASK, VE32_TILE_ETMB_TRCACATR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR5_RD_MASK, VE32_TILE_ETMB_TRCACATR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR6_RD_MASK, VE32_TILE_ETMB_TRCACATR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCACATR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCACATR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCACATR7_RD_MASK, VE32_TILE_ETMB_TRCACATR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCACATR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR0_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR1_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR2_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR3_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR4_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR5_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR6_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCVR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCVR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCVR7_RD_MASK, VE32_TILE_ETMB_TRCCIDCVR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCVR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCCTLR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCCTLR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCCTLR0_RD_MASK, VE32_TILE_ETMB_TRCCIDCCTLR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCCTLR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDCCTLR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDCCTLR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDCCTLR1_RD_MASK, VE32_TILE_ETMB_TRCCIDCCTLR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDCCTLR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCITCTRL_OFFSET, \
                                    VE32_TILE_ETMB_TRCITCTRL_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCITCTRL_RD_MASK, VE32_TILE_ETMB_TRCITCTRL_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCITCTRL_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCLAIMSET_OFFSET, \
                                    VE32_TILE_ETMB_TRCCLAIMSET_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCLAIMSET_RD_MASK, VE32_TILE_ETMB_TRCCLAIMSET_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCLAIMSET_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCLAIMCLR_OFFSET, \
                                    VE32_TILE_ETMB_TRCCLAIMCLR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCLAIMCLR_RD_MASK, VE32_TILE_ETMB_TRCCLAIMCLR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCLAIMCLR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVAFF0_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVAFF0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVAFF0_RD_MASK, VE32_TILE_ETMB_TRCDEVAFF0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVAFF0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVAFF1_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVAFF1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVAFF1_RD_MASK, VE32_TILE_ETMB_TRCDEVAFF1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVAFF1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCLAR_OFFSET, \
                                    VE32_TILE_ETMB_TRCLAR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCLAR_RD_MASK, VE32_TILE_ETMB_TRCLAR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCLAR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCLSR_OFFSET, \
                                    VE32_TILE_ETMB_TRCLSR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCLSR_RD_MASK, VE32_TILE_ETMB_TRCLSR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCLSR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCAUTHSTAT_OFFSET, \
                                    VE32_TILE_ETMB_TRCAUTHSTAT_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCAUTHSTAT_RD_MASK, VE32_TILE_ETMB_TRCAUTHSTAT_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCAUTHSTAT_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVARCH_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVARCH_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVARCH_RD_MASK, VE32_TILE_ETMB_TRCDEVARCH_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVARCH_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVRES0_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVRES0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVRES0_RD_MASK, VE32_TILE_ETMB_TRCDEVRES0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVRES0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVRES1_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVRES1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVRES1_RD_MASK, VE32_TILE_ETMB_TRCDEVRES1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVRES1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVID_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVID_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVID_RD_MASK, VE32_TILE_ETMB_TRCDEVID_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVID_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCDEVTYPE_OFFSET, \
                                    VE32_TILE_ETMB_TRCDEVTYPE_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCDEVTYPE_RD_MASK, VE32_TILE_ETMB_TRCDEVTYPE_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCDEVTYPE_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR4_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR4_RD_MASK, VE32_TILE_ETMB_TRCPIDR4_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR5_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR5_RD_MASK, VE32_TILE_ETMB_TRCPIDR5_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR6_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR6_RD_MASK, VE32_TILE_ETMB_TRCPIDR6_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR7_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR7_RD_MASK, VE32_TILE_ETMB_TRCPIDR7_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR0_RD_MASK, VE32_TILE_ETMB_TRCPIDR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR1_RD_MASK, VE32_TILE_ETMB_TRCPIDR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR2_RD_MASK, VE32_TILE_ETMB_TRCPIDR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCPIDR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCPIDR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCPIDR3_RD_MASK, VE32_TILE_ETMB_TRCPIDR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCPIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDR0_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDR0_RD_MASK, VE32_TILE_ETMB_TRCCIDR0_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDR1_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDR1_RD_MASK, VE32_TILE_ETMB_TRCCIDR1_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDR2_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDR2_RD_MASK, VE32_TILE_ETMB_TRCCIDR2_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCIDR3_OFFSET, \
                                    VE32_TILE_ETMB_TRCCIDR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCIDR3_RD_MASK, VE32_TILE_ETMB_TRCCIDR3_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCIDR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGCMDR_OFFSET, \
                                    VE32_TILE_ETMB_DBGCMDR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGCMDR_RD_MASK, VE32_TILE_ETMB_DBGCMDR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGCMDR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGBPIACSELR_OFFSET, \
                                    VE32_TILE_ETMB_DBGBPIACSELR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGBPIACSELR_RD_MASK, VE32_TILE_ETMB_DBGBPIACSELR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGBPIACSELR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGBPHITSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DBGBPHITSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGBPHITSTATR_RD_MASK, VE32_TILE_ETMB_DBGBPHITSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGBPHITSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGWPDACSELR_OFFSET, \
                                    VE32_TILE_ETMB_DBGWPDACSELR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGWPDACSELR_RD_MASK, VE32_TILE_ETMB_DBGWPDACSELR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGWPDACSELR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGWPDACRSELR_OFFSET, \
                                    VE32_TILE_ETMB_DBGWPDACRSELR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGWPDACRSELR_RD_MASK, VE32_TILE_ETMB_DBGWPDACRSELR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGWPDACRSELR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGWPHITSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DBGWPHITSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGWPHITSTATR_RD_MASK, VE32_TILE_ETMB_DBGWPHITSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGWPHITSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGCPSTOPENR_OFFSET, \
                                    VE32_TILE_ETMB_DBGCPSTOPENR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGCPSTOPENR_RD_MASK, VE32_TILE_ETMB_DBGCPSTOPENR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGCPSTOPENR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGCPSTARTENR_OFFSET, \
                                    VE32_TILE_ETMB_DBGCPSTARTENR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGCPSTARTENR_RD_MASK, VE32_TILE_ETMB_DBGCPSTARTENR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGCPSTARTENR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGCPHITSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DBGCPHITSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGCPHITSTATR_RD_MASK, VE32_TILE_ETMB_DBGCPHITSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGCPHITSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGPROCSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DBGPROCSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGPROCSTATR_RD_MASK, VE32_TILE_ETMB_DBGPROCSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGPROCSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGPROCPCR_OFFSET, \
                                    VE32_TILE_ETMB_DBGPROCPCR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGPROCPCR_RD_MASK, VE32_TILE_ETMB_DBGPROCPCR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGPROCPCR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGCTRLSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DBGCTRLSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGCTRLSTATR_RD_MASK, VE32_TILE_ETMB_DBGCTRLSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGCTRLSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGOBSENR_OFFSET, \
                                    VE32_TILE_ETMB_DBGOBSENR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGOBSENR_RD_MASK, VE32_TILE_ETMB_DBGOBSENR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGOBSENR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGPLCMDR_OFFSET, \
                                    VE32_TILE_ETMB_DBGPLCMDR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGPLCMDR_RD_MASK, VE32_TILE_ETMB_DBGPLCMDR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGPLCMDR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGPLADDRR_OFFSET, \
                                    VE32_TILE_ETMB_DBGPLADDRR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGPLADDRR_RD_MASK, VE32_TILE_ETMB_DBGPLADDRR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGPLADDRR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGSPRDATAR_OFFSET, \
                                    VE32_TILE_ETMB_DBGSPRDATAR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGSPRDATAR_RD_MASK, VE32_TILE_ETMB_DBGSPRDATAR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGSPRDATAR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DBGSPRVALIDR_OFFSET, \
                                    VE32_TILE_ETMB_DBGSPRVALIDR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DBGSPRVALIDR_RD_MASK, VE32_TILE_ETMB_DBGSPRVALIDR_WR_MASK, \
                                    "VE32_TILE_ETMB_DBGSPRVALIDR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_TRCCFGR_OFFSET, \
                                    VE32_TILE_ETMB_TRCCFGR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_TRCCFGR_RD_MASK, VE32_TILE_ETMB_TRCCFGR_WR_MASK, \
                                    "VE32_TILE_ETMB_TRCCFGR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACRNGSTATR_OFFSET, \
                                    VE32_TILE_ETMB_IACRNGSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACRNGSTATR_RD_MASK, VE32_TILE_ETMB_IACRNGSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_IACRNGSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_RESERVED_IAC_OFFSET, \
                                    VE32_TILE_ETMB_RESERVED_IAC_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_RESERVED_IAC_RD_MASK, VE32_TILE_ETMB_RESERVED_IAC_WR_MASK, \
                                    "VE32_TILE_ETMB_RESERVED_IAC_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACHITSTATR_OFFSET, \
                                    VE32_TILE_ETMB_IACHITSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACHITSTATR_RD_MASK, VE32_TILE_ETMB_IACHITSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_IACHITSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACRNGSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DACRNGSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACRNGSTATR_RD_MASK, VE32_TILE_ETMB_DACRNGSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DACRNGSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_RESERVED_DAC_OFFSET, \
                                    VE32_TILE_ETMB_RESERVED_DAC_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_RESERVED_DAC_RD_MASK, VE32_TILE_ETMB_RESERVED_DAC_WR_MASK, \
                                    "VE32_TILE_ETMB_RESERVED_DAC_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACHITSTATR_OFFSET, \
                                    VE32_TILE_ETMB_DACHITSTATR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACHITSTATR_RD_MASK, VE32_TILE_ETMB_DACHITSTATR_WR_MASK, \
                                    "VE32_TILE_ETMB_DACHITSTATR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_PARAMSR_OFFSET, \
                                    VE32_TILE_ETMB_PARAMSR_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_PARAMSR_RD_MASK, VE32_TILE_ETMB_PARAMSR_WR_MASK, \
                                    "VE32_TILE_ETMB_PARAMSR_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR0_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR0_RD_MASK, VE32_TILE_ETMB_IACVALR0_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR1_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR1_RD_MASK, VE32_TILE_ETMB_IACVALR1_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR2_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR2_RD_MASK, VE32_TILE_ETMB_IACVALR2_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR3_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR3_RD_MASK, VE32_TILE_ETMB_IACVALR3_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR4_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR4_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR4_RD_MASK, VE32_TILE_ETMB_IACVALR4_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR4_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR5_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR5_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR5_RD_MASK, VE32_TILE_ETMB_IACVALR5_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR5_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR6_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR6_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR6_RD_MASK, VE32_TILE_ETMB_IACVALR6_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR6_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_IACVALR7_OFFSET, \
                                    VE32_TILE_ETMB_IACVALR7_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_IACVALR7_RD_MASK, VE32_TILE_ETMB_IACVALR7_WR_MASK, \
                                    "VE32_TILE_ETMB_IACVALR7_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACCFGR0_OFFSET, \
                                    VE32_TILE_ETMB_DACCFGR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACCFGR0_RD_MASK, VE32_TILE_ETMB_DACCFGR0_WR_MASK, \
                                    "VE32_TILE_ETMB_DACCFGR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACCFGR1_OFFSET, \
                                    VE32_TILE_ETMB_DACCFGR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACCFGR1_RD_MASK, VE32_TILE_ETMB_DACCFGR1_WR_MASK, \
                                    "VE32_TILE_ETMB_DACCFGR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACCFGR2_OFFSET, \
                                    VE32_TILE_ETMB_DACCFGR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACCFGR2_RD_MASK, VE32_TILE_ETMB_DACCFGR2_WR_MASK, \
                                    "VE32_TILE_ETMB_DACCFGR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACCFGR3_OFFSET, \
                                    VE32_TILE_ETMB_DACCFGR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACCFGR3_RD_MASK, VE32_TILE_ETMB_DACCFGR3_WR_MASK, \
                                    "VE32_TILE_ETMB_DACCFGR3_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACVALR0_OFFSET, \
                                    VE32_TILE_ETMB_DACVALR0_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACVALR0_RD_MASK, VE32_TILE_ETMB_DACVALR0_WR_MASK, \
                                    "VE32_TILE_ETMB_DACVALR0_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACVALR1_OFFSET, \
                                    VE32_TILE_ETMB_DACVALR1_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACVALR1_RD_MASK, VE32_TILE_ETMB_DACVALR1_WR_MASK, \
                                    "VE32_TILE_ETMB_DACVALR1_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACVALR2_OFFSET, \
                                    VE32_TILE_ETMB_DACVALR2_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACVALR2_RD_MASK, VE32_TILE_ETMB_DACVALR2_WR_MASK, \
                                    "VE32_TILE_ETMB_DACVALR2_OFFSET");

            write_read_expect_18a(base_address[i]+VE32_TILE_ETMB_DACVALR3_OFFSET, \
                                    VE32_TILE_ETMB_DACVALR3_DEFAULT, write_data, expected_data, \
                                    VE32_TILE_ETMB_DACVALR3_RD_MASK, VE32_TILE_ETMB_DACVALR3_WR_MASK, \
                                    "VE32_TILE_ETMB_DACVALR3_OFFSET");

        }

    }

}
}
