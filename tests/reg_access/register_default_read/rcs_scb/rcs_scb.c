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
    RCS_SCB_BASE
    };

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_REMAP_OFFSET, \
                                    RCS_SCB_PERIPH_REMAP_DEFAULT, \
                                    RCS_SCB_PERIPH_REMAP_RD_MASK, "RCS_SCB_PERIPH_REMAP_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_RSM_0_SECURITY_OFFSET, \
                                    RCS_SCB_S_RSM_0_SECURITY_DEFAULT, \
                                    RCS_SCB_S_RSM_0_SECURITY_RD_MASK, "RCS_SCB_S_RSM_0_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_RSM_1_SECURITY_OFFSET, \
                                    RCS_SCB_S_RSM_1_SECURITY_DEFAULT, \
                                    RCS_SCB_S_RSM_1_SECURITY_RD_MASK, "RCS_SCB_S_RSM_1_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_VEX_STRM_SECURITY_OFFSET, \
                                    RCS_SCB_S_VEX_STRM_SECURITY_DEFAULT, \
                                    RCS_SCB_S_VEX_STRM_SECURITY_RD_MASK, "RCS_SCB_S_VEX_STRM_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ORION_KP1_SECURITY_OFFSET, \
                                    RCS_SCB_S_ORION_KP1_SECURITY_DEFAULT, \
                                    RCS_SCB_S_ORION_KP1_SECURITY_RD_MASK, "RCS_SCB_S_ORION_KP1_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ORION_MAIN_SECURITY_OFFSET, \
                                    RCS_SCB_S_ORION_MAIN_SECURITY_DEFAULT, \
                                    RCS_SCB_S_ORION_MAIN_SECURITY_RD_MASK, "RCS_SCB_S_ORION_MAIN_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_0_SECURITY_OFFSET, \
                                    RCS_SCB_S_CORE_0_SECURITY_DEFAULT, \
                                    RCS_SCB_S_CORE_0_SECURITY_RD_MASK, "RCS_SCB_S_CORE_0_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_1_SECURITY_OFFSET, \
                                    RCS_SCB_S_CORE_1_SECURITY_DEFAULT, \
                                    RCS_SCB_S_CORE_1_SECURITY_RD_MASK, "RCS_SCB_S_CORE_1_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_3_SECURITY_OFFSET, \
                                    RCS_SCB_S_CORE_3_SECURITY_DEFAULT, \
                                    RCS_SCB_S_CORE_3_SECURITY_RD_MASK, "RCS_SCB_S_CORE_3_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ROM_SECURITY_OFFSET, \
                                    RCS_SCB_S_ROM_SECURITY_DEFAULT, \
                                    RCS_SCB_S_ROM_SECURITY_RD_MASK, "RCS_SCB_S_ROM_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_PHM_SECURITY_OFFSET, \
                                    RCS_SCB_S_PHM_SECURITY_DEFAULT, \
                                    RCS_SCB_S_PHM_SECURITY_RD_MASK, "RCS_SCB_S_PHM_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_PHM1_SECURITY_OFFSET, \
                                    RCS_SCB_S_PHM_SECURITY_DEFAULT, \
                                    RCS_SCB_S_PHM_SECURITY_RD_MASK, "RCS_SCB_S_PHM1_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_2_SECURITY_OFFSET, \
                                    RCS_SCB_S_CORE_2_SECURITY_DEFAULT, \
                                    RCS_SCB_S_CORE_2_SECURITY_RD_MASK, "RCS_SCB_S_CORE_2_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_BFN_GRP_SECURITY_OFFSET, \
                                    RCS_SCB_APB_BFN_GRP_SECURITY_DEFAULT, \
                                    RCS_SCB_APB_BFN_GRP_SECURITY_RD_MASK, "RCS_SCB_APB_BFN_GRP_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_RCS_GRP_SECURITY_OFFSET, \
                                    RCS_SCB_APB_RCS_GRP_SECURITY_DEFAULT, \
                                    RCS_SCB_APB_RCS_GRP_SECURITY_RD_MASK, "RCS_SCB_APB_RCS_GRP_SECURITY_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_AXI2SER_NONSECURE_ACCESS_31_0_OFFSET, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_31_0_DEFAULT, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_31_0_RD_MASK, "RCS_SCB_AXI2SER_NONSECURE_ACCESS_31_0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_AXI2SER_NONSECURE_ACCESS_63_32_OFFSET, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_63_32_DEFAULT, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_63_32_RD_MASK, "RCS_SCB_AXI2SER_NONSECURE_ACCESS_63_32_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_AXI2SER_NONSECURE_ACCESS_95_64_OFFSET, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_95_64_DEFAULT, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_95_64_RD_MASK, "RCS_SCB_AXI2SER_NONSECURE_ACCESS_95_64_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_AXI2SER_NONSECURE_ACCESS_127_96_OFFSET, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_127_96_DEFAULT, \
                                    RCS_SCB_AXI2SER_NONSECURE_ACCESS_127_96_RD_MASK, "RCS_SCB_AXI2SER_NONSECURE_ACCESS_127_96_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_SECURE_BOOT_CFG_LOCK_OFFSET, \
                                    RCS_SCB_SECURE_BOOT_CFG_LOCK_DEFAULT, \
                                    RCS_SCB_SECURE_BOOT_CFG_LOCK_RD_MASK, "RCS_SCB_SECURE_BOOT_CFG_LOCK_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID4_OFFSET, \
                                    RCS_SCB_PERIPH_ID4_DEFAULT, \
                                    RCS_SCB_PERIPH_ID4_RD_MASK, "RCS_SCB_PERIPH_ID4_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID5_OFFSET, \
                                    RCS_SCB_PERIPH_ID5_DEFAULT, \
                                    RCS_SCB_PERIPH_ID5_RD_MASK, "RCS_SCB_PERIPH_ID5_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID6_OFFSET, \
                                    RCS_SCB_PERIPH_ID6_DEFAULT, \
                                    RCS_SCB_PERIPH_ID6_RD_MASK, "RCS_SCB_PERIPH_ID6_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID7_OFFSET, \
                                    RCS_SCB_PERIPH_ID7_DEFAULT, \
                                    RCS_SCB_PERIPH_ID7_RD_MASK, "RCS_SCB_PERIPH_ID7_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID0_OFFSET, \
                                    RCS_SCB_PERIPH_ID0_DEFAULT, \
                                    RCS_SCB_PERIPH_ID0_RD_MASK, "RCS_SCB_PERIPH_ID0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID1_OFFSET, \
                                    RCS_SCB_PERIPH_ID1_DEFAULT, \
                                    RCS_SCB_PERIPH_ID1_RD_MASK, "RCS_SCB_PERIPH_ID1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID2_OFFSET, \
                                    RCS_SCB_PERIPH_ID2_DEFAULT, \
                                    RCS_SCB_PERIPH_ID2_RD_MASK, "RCS_SCB_PERIPH_ID2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_PERIPH_ID3_OFFSET, \
                                    RCS_SCB_PERIPH_ID3_DEFAULT, \
                                    RCS_SCB_PERIPH_ID3_RD_MASK, "RCS_SCB_PERIPH_ID3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_COMP_ID0_OFFSET, \
                                    RCS_SCB_COMP_ID0_DEFAULT, \
                                    RCS_SCB_COMP_ID0_RD_MASK, "RCS_SCB_COMP_ID0_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_COMP_ID1_OFFSET, \
                                    RCS_SCB_COMP_ID1_DEFAULT, \
                                    RCS_SCB_COMP_ID1_RD_MASK, "RCS_SCB_COMP_ID1_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_COMP_ID2_OFFSET, \
                                    RCS_SCB_COMP_ID2_DEFAULT, \
                                    RCS_SCB_COMP_ID2_RD_MASK, "RCS_SCB_COMP_ID2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_COMP_ID3_OFFSET, \
                                    RCS_SCB_COMP_ID3_DEFAULT, \
                                    RCS_SCB_COMP_ID3_RD_MASK, "RCS_SCB_COMP_ID3_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_RSM_0_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_RSM_0_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_RSM_0_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_RSM_0_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_RSM_1_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_RSM_1_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_RSM_1_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_RSM_1_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_VEX_STRM_IB_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_VEX_STRM_IB_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_VEX_STRM_IB_FN_MOD2_OFFSET, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD2_DEFAULT, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD2_RD_MASK, "RCS_SCB_S_VEX_STRM_IB_FN_MOD2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_VEX_STRM_IB_FN_MOD_OFFSET, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD_DEFAULT, \
                                    RCS_SCB_S_VEX_STRM_IB_FN_MOD_RD_MASK, "RCS_SCB_S_VEX_STRM_IB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ORION_KP1_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_ORION_KP1_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_ORION_KP1_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_ORION_KP1_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ORION_MAIN_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_ORION_MAIN_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_ORION_MAIN_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_ORION_MAIN_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_0_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_CORE_0_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_CORE_0_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_CORE_0_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_1_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_CORE_1_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_CORE_1_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_CORE_1_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_3_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_CORE_3_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_CORE_3_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_CORE_3_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_ROM_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_ROM_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_ROM_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_ROM_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_PHM_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_PHM_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_PHM_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_PHM_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_PHM1_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_PHM_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_PHM_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_PHM1_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_S_CORE_2_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_S_CORE_2_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_S_CORE_2_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_S_CORE_2_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_BFN_GRP_IB_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_APB_BFN_GRP_IB_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_APB_BFN_GRP_IB_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_APB_BFN_GRP_IB_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_BFN_GRP_IB_FN_MOD2_OFFSET, \
                                    RCS_SCB_APB_BFN_GRP_IB_FN_MOD2_DEFAULT, \
                                    RCS_SCB_APB_BFN_GRP_IB_FN_MOD2_RD_MASK, "RCS_SCB_APB_BFN_GRP_IB_FN_MOD2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_RCS_GRP_IB_FN_MOD_ISS_BM_OFFSET, \
                                    RCS_SCB_APB_RCS_GRP_IB_FN_MOD_ISS_BM_DEFAULT, \
                                    RCS_SCB_APB_RCS_GRP_IB_FN_MOD_ISS_BM_RD_MASK, "RCS_SCB_APB_RCS_GRP_IB_FN_MOD_ISS_BM_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_APB_RCS_GRP_IB_FN_MOD2_OFFSET, \
                                    RCS_SCB_APB_RCS_GRP_IB_FN_MOD2_DEFAULT, \
                                    RCS_SCB_APB_RCS_GRP_IB_FN_MOD2_RD_MASK, "RCS_SCB_APB_RCS_GRP_IB_FN_MOD2_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMAC_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_DMAC_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_DMAC_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_DMAC_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMAC_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_DMAC_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_DMAC_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_DMAC_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_ORION_RSM_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_ORION_RSM_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_ORION_RSM_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_ORION_RSM_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_ORION_RSM_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_ORION_RSM_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_ORION_RSM_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_ORION_RSM_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_SSPDMA_0_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_SSPDMA_0_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_SSPDMA_0_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_SSPDMA_0_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_SSPDMA_0_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_SSPDMA_0_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_SSPDMA_0_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_SSPDMA_0_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_0_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_CORE_0_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_CORE_0_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_CORE_0_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_0_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_CORE_0_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_CORE_0_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_CORE_0_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_1_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_CORE_1_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_CORE_1_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_CORE_1_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_1_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_CORE_1_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_CORE_1_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_CORE_1_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_3_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_CORE_3_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_CORE_3_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_CORE_3_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_3_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_CORE_3_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_CORE_3_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_CORE_3_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_ORION_MAIN_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_ORION_MAIN_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_ORION_MAIN_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_ORION_MAIN_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_ORION_MAIN_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_ORION_MAIN_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_ORION_MAIN_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_ORION_MAIN_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_0_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_0_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_0_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_DMA_CORE_0_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_0_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_0_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_0_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_DMA_CORE_0_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_1_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_1_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_1_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_DMA_CORE_1_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_1_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_1_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_1_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_DMA_CORE_1_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_3_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_3_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_3_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_DMA_CORE_3_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_3_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_3_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_3_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_DMA_CORE_3_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_2_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_CORE_2_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_CORE_2_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_CORE_2_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_CORE_2_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_CORE_2_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_CORE_2_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_CORE_2_ASIB_AXPROT_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_2_ASIB_FN_MOD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_2_ASIB_FN_MOD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_2_ASIB_FN_MOD_RD_MASK, "RCS_SCB_M_DMA_CORE_2_ASIB_FN_MOD_OFFSET");

        read_reg_expect_18a(base_address[i]+RCS_SCB_M_DMA_CORE_2_ASIB_AXPROT_OVRD_OFFSET, \
                                    RCS_SCB_M_DMA_CORE_2_ASIB_AXPROT_OVRD_DEFAULT, \
                                    RCS_SCB_M_DMA_CORE_2_ASIB_AXPROT_OVRD_RD_MASK, "RCS_SCB_M_DMA_CORE_2_ASIB_AXPROT_OVRD_OFFSET");

    }

}
