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
    MEM_CAP0_ANALOG_PLL_BASE, MEM_CAP1_ANALOG_PLL_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG0_CSR_CLKMUX_OFFSET, \
                                    PLL_LOCAL_PLLREG0_CSR_CLKMUX_DEFAULT, \
                                    PLL_LOCAL_PLLREG0_CSR_CLKMUX_RD_MASK, "PLL_LOCAL_PLLREG0_CSR_CLKMUX_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG1_CSR_GENERAL_OFFSET, \
                                    PLL_LOCAL_PLLREG1_CSR_GENERAL_DEFAULT, \
                                    PLL_LOCAL_PLLREG1_CSR_GENERAL_RD_MASK, "PLL_LOCAL_PLLREG1_CSR_GENERAL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG2_CSR_SYS_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG2_CSR_SYS_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG2_CSR_SYS_CTRL_RD_MASK, "PLL_LOCAL_PLLREG2_CSR_SYS_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG3_CSR_FLB_OFFSET, \
                                    PLL_LOCAL_PLLREG3_CSR_FLB_DEFAULT, \
                                    PLL_LOCAL_PLLREG3_CSR_FLB_RD_MASK, "PLL_LOCAL_PLLREG3_CSR_FLB_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG4_CSR_DCO1_OFFSET, \
                                    PLL_LOCAL_PLLREG4_CSR_DCO1_DEFAULT, \
                                    PLL_LOCAL_PLLREG4_CSR_DCO1_RD_MASK, "PLL_LOCAL_PLLREG4_CSR_DCO1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG5_CSR_DCO2_OFFSET, \
                                    PLL_LOCAL_PLLREG5_CSR_DCO2_DEFAULT, \
                                    PLL_LOCAL_PLLREG5_CSR_DCO2_RD_MASK, "PLL_LOCAL_PLLREG5_CSR_DCO2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG6_CSR_LDO1_OFFSET, \
                                    PLL_LOCAL_PLLREG6_CSR_LDO1_DEFAULT, \
                                    PLL_LOCAL_PLLREG6_CSR_LDO1_RD_MASK, "PLL_LOCAL_PLLREG6_CSR_LDO1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG7_CSR_LDO2_OFFSET, \
                                    PLL_LOCAL_PLLREG7_CSR_LDO2_DEFAULT, \
                                    PLL_LOCAL_PLLREG7_CSR_LDO2_RD_MASK, "PLL_LOCAL_PLLREG7_CSR_LDO2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG8_CSR_TDC_OFFSET, \
                                    PLL_LOCAL_PLLREG8_CSR_TDC_DEFAULT, \
                                    PLL_LOCAL_PLLREG8_CSR_TDC_RD_MASK, "PLL_LOCAL_PLLREG8_CSR_TDC_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG9_CSR_START_OFFSET, \
                                    PLL_LOCAL_PLLREG9_CSR_START_DEFAULT, \
                                    PLL_LOCAL_PLLREG9_CSR_START_RD_MASK, "PLL_LOCAL_PLLREG9_CSR_START_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG10_CSR_CTRL_FLOWS_OFFSET, \
                                    PLL_LOCAL_PLLREG10_CSR_CTRL_FLOWS_DEFAULT, \
                                    PLL_LOCAL_PLLREG10_CSR_CTRL_FLOWS_RD_MASK, "PLL_LOCAL_PLLREG10_CSR_CTRL_FLOWS_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG11_CSR_CAL_OFFSET, \
                                    PLL_LOCAL_PLLREG11_CSR_CAL_DEFAULT, \
                                    PLL_LOCAL_PLLREG11_CSR_CAL_RD_MASK, "PLL_LOCAL_PLLREG11_CSR_CAL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG12_CSR_OPR1_OFFSET, \
                                    PLL_LOCAL_PLLREG12_CSR_OPR1_DEFAULT, \
                                    PLL_LOCAL_PLLREG12_CSR_OPR1_RD_MASK, "PLL_LOCAL_PLLREG12_CSR_OPR1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG13_CSR_OPR2_OFFSET, \
                                    PLL_LOCAL_PLLREG13_CSR_OPR2_DEFAULT, \
                                    PLL_LOCAL_PLLREG13_CSR_OPR2_RD_MASK, "PLL_LOCAL_PLLREG13_CSR_OPR2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG14_CSR_OPR3_OFFSET, \
                                    PLL_LOCAL_PLLREG14_CSR_OPR3_DEFAULT, \
                                    PLL_LOCAL_PLLREG14_CSR_OPR3_RD_MASK, "PLL_LOCAL_PLLREG14_CSR_OPR3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG15_CSR_STICKY_OFFSET, \
                                    PLL_LOCAL_PLLREG15_CSR_STICKY_DEFAULT, \
                                    PLL_LOCAL_PLLREG15_CSR_STICKY_RD_MASK, "PLL_LOCAL_PLLREG15_CSR_STICKY_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG16_CSR_AFS_FLOW_OFFSET, \
                                    PLL_LOCAL_PLLREG16_CSR_AFS_FLOW_DEFAULT, \
                                    PLL_LOCAL_PLLREG16_CSR_AFS_FLOW_RD_MASK, "PLL_LOCAL_PLLREG16_CSR_AFS_FLOW_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG17_CSR_AFS_OFFSET, \
                                    PLL_LOCAL_PLLREG17_CSR_AFS_DEFAULT, \
                                    PLL_LOCAL_PLLREG17_CSR_AFS_RD_MASK, "PLL_LOCAL_PLLREG17_CSR_AFS_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG18_CSR_AFS_OVRD_OFFSET, \
                                    PLL_LOCAL_PLLREG18_CSR_AFS_OVRD_DEFAULT, \
                                    PLL_LOCAL_PLLREG18_CSR_AFS_OVRD_RD_MASK, "PLL_LOCAL_PLLREG18_CSR_AFS_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG19_CSR_AFS_OVERWRITE_OFFSET, \
                                    PLL_LOCAL_PLLREG19_CSR_AFS_OVERWRITE_DEFAULT, \
                                    PLL_LOCAL_PLLREG19_CSR_AFS_OVERWRITE_RD_MASK, "PLL_LOCAL_PLLREG19_CSR_AFS_OVERWRITE_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG20_CSR_SEM_GENERAL_OFFSET, \
                                    PLL_LOCAL_PLLREG20_CSR_SEM_GENERAL_DEFAULT, \
                                    PLL_LOCAL_PLLREG20_CSR_SEM_GENERAL_RD_MASK, "PLL_LOCAL_PLLREG20_CSR_SEM_GENERAL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG21_CSR_MEM_OFFSET, \
                                    PLL_LOCAL_PLLREG21_CSR_MEM_DEFAULT, \
                                    PLL_LOCAL_PLLREG21_CSR_MEM_RD_MASK, "PLL_LOCAL_PLLREG21_CSR_MEM_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG22_CSR_MEM_ADDR_OFFSET, \
                                    PLL_LOCAL_PLLREG22_CSR_MEM_ADDR_DEFAULT, \
                                    PLL_LOCAL_PLLREG22_CSR_MEM_ADDR_RD_MASK, "PLL_LOCAL_PLLREG22_CSR_MEM_ADDR_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG23_CSR_MEM_DATA_OFFSET, \
                                    PLL_LOCAL_PLLREG23_CSR_MEM_DATA_DEFAULT, \
                                    PLL_LOCAL_PLLREG23_CSR_MEM_DATA_RD_MASK, "PLL_LOCAL_PLLREG23_CSR_MEM_DATA_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG24_CSR_PE_GEAR_OFFSET, \
                                    PLL_LOCAL_PLLREG24_CSR_PE_GEAR_DEFAULT, \
                                    PLL_LOCAL_PLLREG24_CSR_PE_GEAR_RD_MASK, "PLL_LOCAL_PLLREG24_CSR_PE_GEAR_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG25_CSR_PE_INIT_OFFSET, \
                                    PLL_LOCAL_PLLREG25_CSR_PE_INIT_DEFAULT, \
                                    PLL_LOCAL_PLLREG25_CSR_PE_INIT_RD_MASK, "PLL_LOCAL_PLLREG25_CSR_PE_INIT_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG26_CSR_DPD_OFFSET, \
                                    PLL_LOCAL_PLLREG26_CSR_DPD_DEFAULT, \
                                    PLL_LOCAL_PLLREG26_CSR_DPD_RD_MASK, "PLL_LOCAL_PLLREG26_CSR_DPD_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG27_CSR_DPD_OVERWRITE_OFFSET, \
                                    PLL_LOCAL_PLLREG27_CSR_DPD_OVERWRITE_DEFAULT, \
                                    PLL_LOCAL_PLLREG27_CSR_DPD_OVERWRITE_RD_MASK, "PLL_LOCAL_PLLREG27_CSR_DPD_OVERWRITE_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG28_CSR_LOCKDET_OFFSET, \
                                    PLL_LOCAL_PLLREG28_CSR_LOCKDET_DEFAULT, \
                                    PLL_LOCAL_PLLREG28_CSR_LOCKDET_RD_MASK, "PLL_LOCAL_PLLREG28_CSR_LOCKDET_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG29_CSR_LOCKDET_EXT_LOCK_OFFSET, \
                                    PLL_LOCAL_PLLREG29_CSR_LOCKDET_EXT_LOCK_DEFAULT, \
                                    PLL_LOCAL_PLLREG29_CSR_LOCKDET_EXT_LOCK_RD_MASK, "PLL_LOCAL_PLLREG29_CSR_LOCKDET_EXT_LOCK_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG30_CSR_JUMPDET_OFFSET, \
                                    PLL_LOCAL_PLLREG30_CSR_JUMPDET_DEFAULT, \
                                    PLL_LOCAL_PLLREG30_CSR_JUMPDET_RD_MASK, "PLL_LOCAL_PLLREG30_CSR_JUMPDET_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG31_CSR_DLF_OFFSET, \
                                    PLL_LOCAL_PLLREG31_CSR_DLF_DEFAULT, \
                                    PLL_LOCAL_PLLREG31_CSR_DLF_RD_MASK, "PLL_LOCAL_PLLREG31_CSR_DLF_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG32_CSR_DLF2_OFFSET, \
                                    PLL_LOCAL_PLLREG32_CSR_DLF2_DEFAULT, \
                                    PLL_LOCAL_PLLREG32_CSR_DLF2_RD_MASK, "PLL_LOCAL_PLLREG32_CSR_DLF2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG33_CSR_DLF_OVERWRITE_OFFSET, \
                                    PLL_LOCAL_PLLREG33_CSR_DLF_OVERWRITE_DEFAULT, \
                                    PLL_LOCAL_PLLREG33_CSR_DLF_OVERWRITE_RD_MASK, "PLL_LOCAL_PLLREG33_CSR_DLF_OVERWRITE_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG34_CSR_MLFPE_OFFSET, \
                                    PLL_LOCAL_PLLREG34_CSR_MLFPE_DEFAULT, \
                                    PLL_LOCAL_PLLREG34_CSR_MLFPE_RD_MASK, "PLL_LOCAL_PLLREG34_CSR_MLFPE_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG35_CSR_RDTC_OFFSET, \
                                    PLL_LOCAL_PLLREG35_CSR_RDTC_DEFAULT, \
                                    PLL_LOCAL_PLLREG35_CSR_RDTC_RD_MASK, "PLL_LOCAL_PLLREG35_CSR_RDTC_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG36_CSR_RDTC_OVRD_OFFSET, \
                                    PLL_LOCAL_PLLREG36_CSR_RDTC_OVRD_DEFAULT, \
                                    PLL_LOCAL_PLLREG36_CSR_RDTC_OVRD_RD_MASK, "PLL_LOCAL_PLLREG36_CSR_RDTC_OVRD_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG37_CSR_ASC1_OFFSET, \
                                    PLL_LOCAL_PLLREG37_CSR_ASC1_DEFAULT, \
                                    PLL_LOCAL_PLLREG37_CSR_ASC1_RD_MASK, "PLL_LOCAL_PLLREG37_CSR_ASC1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG38_CSR_ASC1_SPUR_OFFSET, \
                                    PLL_LOCAL_PLLREG38_CSR_ASC1_SPUR_DEFAULT, \
                                    PLL_LOCAL_PLLREG38_CSR_ASC1_SPUR_RD_MASK, "PLL_LOCAL_PLLREG38_CSR_ASC1_SPUR_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG39_CSR_ASC2_OFFSET, \
                                    PLL_LOCAL_PLLREG39_CSR_ASC2_DEFAULT, \
                                    PLL_LOCAL_PLLREG39_CSR_ASC2_RD_MASK, "PLL_LOCAL_PLLREG39_CSR_ASC2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG40_CSR_ASC2_SPUR_OFFSET, \
                                    PLL_LOCAL_PLLREG40_CSR_ASC2_SPUR_DEFAULT, \
                                    PLL_LOCAL_PLLREG40_CSR_ASC2_SPUR_RD_MASK, "PLL_LOCAL_PLLREG40_CSR_ASC2_SPUR_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG41_CSR_ASC3_OFFSET, \
                                    PLL_LOCAL_PLLREG41_CSR_ASC3_DEFAULT, \
                                    PLL_LOCAL_PLLREG41_CSR_ASC3_RD_MASK, "PLL_LOCAL_PLLREG41_CSR_ASC3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG42_CSR_ASC3_SPUR_OFFSET, \
                                    PLL_LOCAL_PLLREG42_CSR_ASC3_SPUR_DEFAULT, \
                                    PLL_LOCAL_PLLREG42_CSR_ASC3_SPUR_RD_MASK, "PLL_LOCAL_PLLREG42_CSR_ASC3_SPUR_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG43_CSR_ANA_CNT_OFFSET, \
                                    PLL_LOCAL_PLLREG43_CSR_ANA_CNT_DEFAULT, \
                                    PLL_LOCAL_PLLREG43_CSR_ANA_CNT_RD_MASK, "PLL_LOCAL_PLLREG43_CSR_ANA_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG44_CSR_DBGM_OFFSET, \
                                    PLL_LOCAL_PLLREG44_CSR_DBGM_DEFAULT, \
                                    PLL_LOCAL_PLLREG44_CSR_DBGM_RD_MASK, "PLL_LOCAL_PLLREG44_CSR_DBGM_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG45_CSR_ANALOG_OFFSET, \
                                    PLL_LOCAL_PLLREG45_CSR_ANALOG_DEFAULT, \
                                    PLL_LOCAL_PLLREG45_CSR_ANALOG_RD_MASK, "PLL_LOCAL_PLLREG45_CSR_ANALOG_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG46_CSR_STAT1_OFFSET, \
                                    PLL_LOCAL_PLLREG46_CSR_STAT1_DEFAULT, \
                                    PLL_LOCAL_PLLREG46_CSR_STAT1_RD_MASK, "PLL_LOCAL_PLLREG46_CSR_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG47_CSR_STAT2_OFFSET, \
                                    PLL_LOCAL_PLLREG47_CSR_STAT2_DEFAULT, \
                                    PLL_LOCAL_PLLREG47_CSR_STAT2_RD_MASK, "PLL_LOCAL_PLLREG47_CSR_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG48_CSR_STAT3_OFFSET, \
                                    PLL_LOCAL_PLLREG48_CSR_STAT3_DEFAULT, \
                                    PLL_LOCAL_PLLREG48_CSR_STAT3_RD_MASK, "PLL_LOCAL_PLLREG48_CSR_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG49_CSR_STAT4_OFFSET, \
                                    PLL_LOCAL_PLLREG49_CSR_STAT4_DEFAULT, \
                                    PLL_LOCAL_PLLREG49_CSR_STAT4_RD_MASK, "PLL_LOCAL_PLLREG49_CSR_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG50_CSR_START_UP_SEQ_OFFSET, \
                                    PLL_LOCAL_PLLREG50_CSR_START_UP_SEQ_DEFAULT, \
                                    PLL_LOCAL_PLLREG50_CSR_START_UP_SEQ_RD_MASK, "PLL_LOCAL_PLLREG50_CSR_START_UP_SEQ_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG51_CSR_SEQ_OFFSET, \
                                    PLL_LOCAL_PLLREG51_CSR_SEQ_DEFAULT, \
                                    PLL_LOCAL_PLLREG51_CSR_SEQ_RD_MASK, "PLL_LOCAL_PLLREG51_CSR_SEQ_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG52_CSR_SEQ_ON_CFG_OFFSET, \
                                    PLL_LOCAL_PLLREG52_CSR_SEQ_ON_CFG_DEFAULT, \
                                    PLL_LOCAL_PLLREG52_CSR_SEQ_ON_CFG_RD_MASK, "PLL_LOCAL_PLLREG52_CSR_SEQ_ON_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG53_CSR_SEQ_OFF_CFG_OFFSET, \
                                    PLL_LOCAL_PLLREG53_CSR_SEQ_OFF_CFG_DEFAULT, \
                                    PLL_LOCAL_PLLREG53_CSR_SEQ_OFF_CFG_RD_MASK, "PLL_LOCAL_PLLREG53_CSR_SEQ_OFF_CFG_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG54_CSR_MEMORY_CTRL1_OFFSET, \
                                    PLL_LOCAL_PLLREG54_CSR_MEMORY_CTRL1_DEFAULT, \
                                    PLL_LOCAL_PLLREG54_CSR_MEMORY_CTRL1_RD_MASK, "PLL_LOCAL_PLLREG54_CSR_MEMORY_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG55_CSR_MEMORY_CTRL2_OFFSET, \
                                    PLL_LOCAL_PLLREG55_CSR_MEMORY_CTRL2_DEFAULT, \
                                    PLL_LOCAL_PLLREG55_CSR_MEMORY_CTRL2_RD_MASK, "PLL_LOCAL_PLLREG55_CSR_MEMORY_CTRL2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG56_CSR_VBAND_DIV_BIAS_OFFSET, \
                                    PLL_LOCAL_PLLREG56_CSR_VBAND_DIV_BIAS_DEFAULT, \
                                    PLL_LOCAL_PLLREG56_CSR_VBAND_DIV_BIAS_RD_MASK, "PLL_LOCAL_PLLREG56_CSR_VBAND_DIV_BIAS_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG57_CSR_VBAND_OFFSET, \
                                    PLL_LOCAL_PLLREG57_CSR_VBAND_DEFAULT, \
                                    PLL_LOCAL_PLLREG57_CSR_VBAND_RD_MASK, "PLL_LOCAL_PLLREG57_CSR_VBAND_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG58_CSR_TDC_CLK_GATING_OFFSET, \
                                    PLL_LOCAL_PLLREG58_CSR_TDC_CLK_GATING_DEFAULT, \
                                    PLL_LOCAL_PLLREG58_CSR_TDC_CLK_GATING_RD_MASK, "PLL_LOCAL_PLLREG58_CSR_TDC_CLK_GATING_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG59_CSR_PNC_OFFSET, \
                                    PLL_LOCAL_PLLREG59_CSR_PNC_DEFAULT, \
                                    PLL_LOCAL_PLLREG59_CSR_PNC_RD_MASK, "PLL_LOCAL_PLLREG59_CSR_PNC_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG60_CSR_AE_OFFSET, \
                                    PLL_LOCAL_PLLREG60_CSR_AE_DEFAULT, \
                                    PLL_LOCAL_PLLREG60_CSR_AE_RD_MASK, "PLL_LOCAL_PLLREG60_CSR_AE_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG61_CSR_LDO_PDOS_OFFSET, \
                                    PLL_LOCAL_PLLREG61_CSR_LDO_PDOS_DEFAULT, \
                                    PLL_LOCAL_PLLREG61_CSR_LDO_PDOS_RD_MASK, "PLL_LOCAL_PLLREG61_CSR_LDO_PDOS_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG62_CSR_BIST_STAT_OFFSET, \
                                    PLL_LOCAL_PLLREG62_CSR_BIST_STAT_DEFAULT, \
                                    PLL_LOCAL_PLLREG62_CSR_BIST_STAT_RD_MASK, "PLL_LOCAL_PLLREG62_CSR_BIST_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG63_CSR_LDO3_OFFSET, \
                                    PLL_LOCAL_PLLREG63_CSR_LDO3_DEFAULT, \
                                    PLL_LOCAL_PLLREG63_CSR_LDO3_RD_MASK, "PLL_LOCAL_PLLREG63_CSR_LDO3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG64_CSR_CTRL1_OFFSET, \
                                    PLL_LOCAL_PLLREG64_CSR_CTRL1_DEFAULT, \
                                    PLL_LOCAL_PLLREG64_CSR_CTRL1_RD_MASK, "PLL_LOCAL_PLLREG64_CSR_CTRL1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG65_CSR_DCOTC1_OFFSET, \
                                    PLL_LOCAL_PLLREG65_CSR_DCOTC1_DEFAULT, \
                                    PLL_LOCAL_PLLREG65_CSR_DCOTC1_RD_MASK, "PLL_LOCAL_PLLREG65_CSR_DCOTC1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG66_CSR_DCOTC2_OFFSET, \
                                    PLL_LOCAL_PLLREG66_CSR_DCOTC2_DEFAULT, \
                                    PLL_LOCAL_PLLREG66_CSR_DCOTC2_RD_MASK, "PLL_LOCAL_PLLREG66_CSR_DCOTC2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG67_CSR_DCOTC3_OFFSET, \
                                    PLL_LOCAL_PLLREG67_CSR_DCOTC3_DEFAULT, \
                                    PLL_LOCAL_PLLREG67_CSR_DCOTC3_RD_MASK, "PLL_LOCAL_PLLREG67_CSR_DCOTC3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG68_CSR_DCOTC4_OFFSET, \
                                    PLL_LOCAL_PLLREG68_CSR_DCOTC4_DEFAULT, \
                                    PLL_LOCAL_PLLREG68_CSR_DCOTC4_RD_MASK, "PLL_LOCAL_PLLREG68_CSR_DCOTC4_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG69_CSR_PHLOCK1_OFFSET, \
                                    PLL_LOCAL_PLLREG69_CSR_PHLOCK1_DEFAULT, \
                                    PLL_LOCAL_PLLREG69_CSR_PHLOCK1_RD_MASK, "PLL_LOCAL_PLLREG69_CSR_PHLOCK1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG70_CSR_PHLOCK2_OFFSET, \
                                    PLL_LOCAL_PLLREG70_CSR_PHLOCK2_DEFAULT, \
                                    PLL_LOCAL_PLLREG70_CSR_PHLOCK2_RD_MASK, "PLL_LOCAL_PLLREG70_CSR_PHLOCK2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG71_CSR_PHLOCK3_OFFSET, \
                                    PLL_LOCAL_PLLREG71_CSR_PHLOCK3_DEFAULT, \
                                    PLL_LOCAL_PLLREG71_CSR_PHLOCK3_RD_MASK, "PLL_LOCAL_PLLREG71_CSR_PHLOCK3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG72_CSR_PHLOCK4_OFFSET, \
                                    PLL_LOCAL_PLLREG72_CSR_PHLOCK4_DEFAULT, \
                                    PLL_LOCAL_PLLREG72_CSR_PHLOCK4_RD_MASK, "PLL_LOCAL_PLLREG72_CSR_PHLOCK4_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG73_CSR_PHLOCK5_OFFSET, \
                                    PLL_LOCAL_PLLREG73_CSR_PHLOCK5_DEFAULT, \
                                    PLL_LOCAL_PLLREG73_CSR_PHLOCK5_RD_MASK, "PLL_LOCAL_PLLREG73_CSR_PHLOCK5_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG74_CSR_PHLOCK6_OFFSET, \
                                    PLL_LOCAL_PLLREG74_CSR_PHLOCK6_DEFAULT, \
                                    PLL_LOCAL_PLLREG74_CSR_PHLOCK6_RD_MASK, "PLL_LOCAL_PLLREG74_CSR_PHLOCK6_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG75_CSR_STAT1_OFFSET, \
                                    PLL_LOCAL_PLLREG75_CSR_STAT1_DEFAULT, \
                                    PLL_LOCAL_PLLREG75_CSR_STAT1_RD_MASK, "PLL_LOCAL_PLLREG75_CSR_STAT1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG76_CSR_STAT2_OFFSET, \
                                    PLL_LOCAL_PLLREG76_CSR_STAT2_DEFAULT, \
                                    PLL_LOCAL_PLLREG76_CSR_STAT2_RD_MASK, "PLL_LOCAL_PLLREG76_CSR_STAT2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG77_CSR_STAT3_OFFSET, \
                                    PLL_LOCAL_PLLREG77_CSR_STAT3_DEFAULT, \
                                    PLL_LOCAL_PLLREG77_CSR_STAT3_RD_MASK, "PLL_LOCAL_PLLREG77_CSR_STAT3_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG78_CSR_FLB1_OFFSET, \
                                    PLL_LOCAL_PLLREG78_CSR_FLB1_DEFAULT, \
                                    PLL_LOCAL_PLLREG78_CSR_FLB1_RD_MASK, "PLL_LOCAL_PLLREG78_CSR_FLB1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG79_CSR_FLB2_OFFSET, \
                                    PLL_LOCAL_PLLREG79_CSR_FLB2_DEFAULT, \
                                    PLL_LOCAL_PLLREG79_CSR_FLB2_RD_MASK, "PLL_LOCAL_PLLREG79_CSR_FLB2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG80_CSR_DLFX1_OFFSET, \
                                    PLL_LOCAL_PLLREG80_CSR_DLFX1_DEFAULT, \
                                    PLL_LOCAL_PLLREG80_CSR_DLFX1_RD_MASK, "PLL_LOCAL_PLLREG80_CSR_DLFX1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG81_CSR_STAT4_OFFSET, \
                                    PLL_LOCAL_PLLREG81_CSR_STAT4_DEFAULT, \
                                    PLL_LOCAL_PLLREG81_CSR_STAT4_RD_MASK, "PLL_LOCAL_PLLREG81_CSR_STAT4_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG82_CSR_STAT5_OFFSET, \
                                    PLL_LOCAL_PLLREG82_CSR_STAT5_DEFAULT, \
                                    PLL_LOCAL_PLLREG82_CSR_STAT5_RD_MASK, "PLL_LOCAL_PLLREG82_CSR_STAT5_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG83_CSR_STAT6_OFFSET, \
                                    PLL_LOCAL_PLLREG83_CSR_STAT6_DEFAULT, \
                                    PLL_LOCAL_PLLREG83_CSR_STAT6_RD_MASK, "PLL_LOCAL_PLLREG83_CSR_STAT6_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG84_CSR_STAT7_OFFSET, \
                                    PLL_LOCAL_PLLREG84_CSR_STAT7_DEFAULT, \
                                    PLL_LOCAL_PLLREG84_CSR_STAT7_RD_MASK, "PLL_LOCAL_PLLREG84_CSR_STAT7_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG85_CSR_STAT8_OFFSET, \
                                    PLL_LOCAL_PLLREG85_CSR_STAT8_DEFAULT, \
                                    PLL_LOCAL_PLLREG85_CSR_STAT8_RD_MASK, "PLL_LOCAL_PLLREG85_CSR_STAT8_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG86_CSR_STAT9_OFFSET, \
                                    PLL_LOCAL_PLLREG86_CSR_STAT9_DEFAULT, \
                                    PLL_LOCAL_PLLREG86_CSR_STAT9_RD_MASK, "PLL_LOCAL_PLLREG86_CSR_STAT9_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG87_CSR_STAT10_OFFSET, \
                                    PLL_LOCAL_PLLREG87_CSR_STAT10_DEFAULT, \
                                    PLL_LOCAL_PLLREG87_CSR_STAT10_RD_MASK, "PLL_LOCAL_PLLREG87_CSR_STAT10_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG88_CSR_SFTDC_OFFSET, \
                                    PLL_LOCAL_PLLREG88_CSR_SFTDC_DEFAULT, \
                                    PLL_LOCAL_PLLREG88_CSR_SFTDC_RD_MASK, "PLL_LOCAL_PLLREG88_CSR_SFTDC_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG89_CSR_DCG_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG89_CSR_DCG_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG89_CSR_DCG_CTRL_RD_MASK, "PLL_LOCAL_PLLREG89_CSR_DCG_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG90_CSR_DCO_LDO1_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG90_CSR_DCO_LDO1_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG90_CSR_DCO_LDO1_CTRL_RD_MASK, "PLL_LOCAL_PLLREG90_CSR_DCO_LDO1_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG91_CSR_DCO_LDO2_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG91_CSR_DCO_LDO2_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG91_CSR_DCO_LDO2_CTRL_RD_MASK, "PLL_LOCAL_PLLREG91_CSR_DCO_LDO2_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG92_CSR_TDC_LDO1_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG92_CSR_TDC_LDO1_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG92_CSR_TDC_LDO1_CTRL_RD_MASK, "PLL_LOCAL_PLLREG92_CSR_TDC_LDO1_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG93_CSR_TDC_LDO2_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG93_CSR_TDC_LDO2_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG93_CSR_TDC_LDO2_CTRL_RD_MASK, "PLL_LOCAL_PLLREG93_CSR_TDC_LDO2_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG94_CSR_DPLL_DIG_LDO_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG94_CSR_DPLL_DIG_LDO_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG94_CSR_DPLL_DIG_LDO_CTRL_RD_MASK, "PLL_LOCAL_PLLREG94_CSR_DPLL_DIG_LDO_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG95_CSR_BIAS_VREF_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG95_CSR_BIAS_VREF_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG95_CSR_BIAS_VREF_CTRL_RD_MASK, "PLL_LOCAL_PLLREG95_CSR_BIAS_VREF_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG96_CSR_LOPA_CLKREF_CTRL_OFFSET, \
                                    PLL_LOCAL_PLLREG96_CSR_LOPA_CLKREF_CTRL_DEFAULT, \
                                    PLL_LOCAL_PLLREG96_CSR_LOPA_CLKREF_CTRL_RD_MASK, "PLL_LOCAL_PLLREG96_CSR_LOPA_CLKREF_CTRL_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG97_CSR_PLL_CLKDIST_CONF0_OFFSET, \
                                    PLL_LOCAL_PLLREG97_CSR_PLL_CLKDIST_CONF0_DEFAULT, \
                                    PLL_LOCAL_PLLREG97_CSR_PLL_CLKDIST_CONF0_RD_MASK, "PLL_LOCAL_PLLREG97_CSR_PLL_CLKDIST_CONF0_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG98_CSR_PLL_CLKDIST_CONF1_OFFSET, \
                                    PLL_LOCAL_PLLREG98_CSR_PLL_CLKDIST_CONF1_DEFAULT, \
                                    PLL_LOCAL_PLLREG98_CSR_PLL_CLKDIST_CONF1_RD_MASK, "PLL_LOCAL_PLLREG98_CSR_PLL_CLKDIST_CONF1_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG99_CSR_PLL_CLKDIST_CONF2_OFFSET, \
                                    PLL_LOCAL_PLLREG99_CSR_PLL_CLKDIST_CONF2_DEFAULT, \
                                    PLL_LOCAL_PLLREG99_CSR_PLL_CLKDIST_CONF2_RD_MASK, "PLL_LOCAL_PLLREG99_CSR_PLL_CLKDIST_CONF2_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG100_CSR_PLL_CLKJESDANA_CONF0_OFFSET, \
                                    PLL_LOCAL_PLLREG100_CSR_PLL_CLKJESDANA_CONF0_DEFAULT, \
                                    PLL_LOCAL_PLLREG100_CSR_PLL_CLKJESDANA_CONF0_RD_MASK, "PLL_LOCAL_PLLREG100_CSR_PLL_CLKJESDANA_CONF0_OFFSET");

        read_reg_expect_18a(base_address[i]+PLL_LOCAL_PLLREG1023_APB_BRDG_STAT_OFFSET, \
                                    PLL_LOCAL_PLLREG1023_APB_BRDG_STAT_DEFAULT, \
                                    PLL_LOCAL_PLLREG1023_APB_BRDG_STAT_RD_MASK, "PLL_LOCAL_PLLREG1023_APB_BRDG_STAT_OFFSET");

    }

}
