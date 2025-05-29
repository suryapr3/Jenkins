
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
/**************************************************************************************
 * @file  reset_common.c
****************************************************************************************/
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
#include "reset_common.h"

/*****************************************************************************************
 * Function        : register_read_write_access
 * Brief           : function to read and write the module registers before the reset
 *******************************************************************************************/
void register_read_write_access()
{
    uint32_t read_data;

    LOG_INFO("RCS GPREG Registers\n");
    read_data = read_reg_18a(RCS_GPREG_RCS_CFG_ADR, "RCS_GPREG_register");
    write_reg_18a(RCS_GPREG_RCS_CFG_ADR, 0xA5A5A5A5, RCS_GPREG_RCS_CFG_WR_MASK, "RCS_GPREG_register");
    read_data = read_reg_18a(RCS_GPREG_RCS_CFG_ADR, "RCS_GPREG_register");

    LOG_INFO("RCS DMAC Registers\n");
    read_data = read_reg_18a(RCS_DMAC_CFGREG_ADR, "RCS_DMAC_register");
    write_reg_18a(RCS_DMAC_CFGREG_ADR, 0xA5A5A5A5, RCS_DMAC_CFGREG_WR_MASK, "RCS_DMAC_register");
    read_data = read_reg_18a(RCS_DMAC_CFGREG_ADR, "RCS_DMAC_register");

    LOG_INFO("DLINK SCRATCH Registers\n");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_SCRATCH_ADR, "DLINK_register");
    write_reg_18a(DLNK_HUB_APB_HUB_SCRATCH_ADR, 0xA5A5A5A5, DLNK_HUB_APB_HUB_SCRATCH_WR_MASK, "DLINK_register");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_SCRATCH_ADR, "DLINK_register");

    LOG_INFO("DLINK FSM WR SEQ Registers\n");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_ADR, "DLINK_register");
    write_reg_18a(DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_ADR, 0xA5A5A5A5, DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_WR_MASK, "DLINK_register");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_ADR, "DLINK_register");

    LOG_INFO("V2D BFN CSR Registers\n");
    read_data = read_reg_18a((V2D0_BFN_CSR_BASE) + (BFN_CSR_BFN_SCRATCH_OFFSET), "bfn_csr_register");
    write_reg_18a(V2D0_BFN_CSR_BASE+BFN_CSR_BFN_SCRATCH_OFFSET, 0xA5A5A5A5, BFN_CSR_BFN_SCRATCH_WR_MASK, "bfn_csr_register");
    read_data = read_reg_18a(V2D0_BFN_CSR_BASE+BFN_CSR_BFN_SCRATCH_OFFSET, "bfn_csr_register");

    LOG_INFO("VHA CFG Registers\n");
    read_data = read_reg_18a((VHA0_ANT0_BASE) + (VHA_ANT_CFG_OFFSET), "VHA_ANT register");
    write_reg_18a(VHA0_ANT0_BASE+VHA_ANT_CFG_OFFSET, 0xA5A5A5A5, VHA_ANT_SCRATCH_WR_MASK, "VHA_ANT_register");
    read_data = read_reg_18a(VHA0_ANT0_BASE+VHA_ANT_CFG_OFFSET, "VHA_ANT register");

    LOG_INFO("SYSCON EVC_AGC Registers\n");
    read_data = read_reg_18a(EVC_AGC_EVC0_INTF_CFG_ADR, "EVCAGC_register");
    write_reg_18a(EVC_AGC_EVC0_INTF_CFG_ADR, 0xA5A5A5A5, EVC_AGC_EVC0_INTF_CFG_WR_MASK, "EVCAGC_register");
    read_data = read_reg_18a(EVC_AGC_EVC0_INTF_CFG_ADR, "EVCAGC_register");

    LOG_INFO("SYSCON SPICSR Registers\n");
    read_data = read_reg_18a(SYS_CTRL_SPICSR_ADR, "SPICSR");
    write_reg_18a(SYS_CTRL_SPICSR_ADR, 0x000000FF, SYS_CTRL_SPICSR_WR_MASK, "SPICSR_register");
    read_data = read_reg_18a(SYS_CTRL_SPICSR_ADR, "SPICSR");

    LOG_INFO("SYSCON SCRATCHBOTTOM Registers\n");
    read_data = read_reg_18a(SYS_CTRL_SCRATCHBOTTOM_ADR, "SYSCTRL_SCRATCH_register");
    write_reg_18a(SYS_CTRL_SCRATCHBOTTOM_ADR, 0x0000A5A5, SYS_CTRL_SCRATCHBOTTOM_WR_MASK, "SYSCTRL_SCRATCH_register");
    read_data = read_reg_18a(SYS_CTRL_SCRATCHBOTTOM_ADR, "SYSCTRL_SCRATCH_register");

    LOG_INFO("DRF SCRATCH Registers\n");
    read_data = read_reg_18a((HUB_DRF0_APB_BASE) + (HUB_DRF_APB_HUB_SCRATCH_OFFSET), "DRF0_register");
    write_reg_18a(HUB_DRF0_APB_BASE+HUB_DRF_APB_HUB_SCRATCH_OFFSET, 0xA5A5A5A5, HUB_DRF_APB_HUB_SCRATCH_WR_MASK, "DRF0_register");
    read_data = read_reg_18a(HUB_DRF0_APB_BASE+HUB_DRF_APB_HUB_SCRATCH_OFFSET, "DRF0_register");

    LOG_INFO("DRF CLK_EN Registers\n");
    read_data = read_reg_18a((HUB_DRF1_APB_BASE) + (HUB_DRF_APB_HUB_CLK_EN_OFFSET), "DRF1_register");
    write_reg_18a(HUB_DRF1_APB_BASE+HUB_DRF_APB_HUB_CLK_EN_OFFSET, 0xA5A5A5A5, HUB_DRF_APB_HUB_CLK_EN_WR_MASK, "DRF1_register");
    read_data = read_reg_18a(HUB_DRF1_APB_BASE+HUB_DRF_APB_HUB_CLK_EN_OFFSET, "DRF1_register");

    LOG_INFO("DTS Registers\n");
    read_data = read_reg_18a(DTS_MON_EN_ADR, "DTS_register");
    write_reg_18a(DTS_MON_EN_ADR, 0xA5A5A5A5, DTS_MON_EN_WR_MASK, "DTS_register");
    read_data = read_reg_18a(DTS_MON_EN_ADR, "DTS_register");
}

/*****************************************************************************************
 * Function        : register_access_for_default_value_after_reset
 * Brief           : function to read the module registers for the default value after the reset
 *******************************************************************************************/
void register_access_for_default_value_after_reset()
{
    uint32_t read_data;

    LOG_INFO("RCS GPREG Registers\n");
    read_data = read_reg_18a(RCS_GPREG_RCS_CFG_ADR, "RCS_GPREG_register");
    if(read_data == RCS_GPREG_RCS_CFG_DEFAULT)
    {
        LOG_PRINT("The RCS GPREG Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The RCS GPREG Registers have not gone through the reset\n");
    }

    LOG_INFO("RCS DMAC Registers\n");
    read_data = read_reg_18a(RCS_DMAC_CFGREG_ADR, "RCS_DMAC_register");
    if(read_data == RCS_DMAC_CFGREG_DEFAULT)
    {
        LOG_PRINT("The RCS DMAC Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The RCS DMAC Registers have not gone through the reset\n");
    }

    LOG_INFO("DLINK SCRATCH Registers\n");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_SCRATCH_ADR, "DLINK_register");
    if(read_data == DLNK_HUB_APB_HUB_SCRATCH_DEFAULT)
    {
        LOG_PRINT("The DLINK SCRATCH Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The DLINK SCRATCH Registers have not gone through the reset\n");
    }

    LOG_INFO("DLINK FSM WR SEQ Registers\n");
    read_data = read_reg_18a(DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_ADR, "DLINK_register");
    if(read_data == DLNK_HUB_APB_HUB_FSM_WR_SEQ_SM_CTRL_DEFAULT)
    {
        LOG_PRINT("The DLINK FSM SEQ Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The DLINK FSM SEQ Registers have not gone through the reset\n");
    }

    LOG_INFO("V2D BFN CSR Registers\n");
    read_data = read_reg_18a((V2D0_BFN_CSR_BASE) + (BFN_CSR_BFN_SCRATCH_OFFSET), "bfn_csr_register");
    if(read_data == BFN_CSR_BFN_SCRATCH_DEFAULT)
    {
        LOG_PRINT("The V2D BFN CSR Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The V2D BFN CSR Registers have not gone through the reset\n");
    }

    LOG_INFO("VHA CFG Registers\n");
    read_data = read_reg_18a((VHA0_ANT0_BASE) + (VHA_ANT_CFG_OFFSET), "VHA_ANT register");
    if(read_data == VHA_ANT_CFG_DEFAULT)
    {
        LOG_PRINT("The VHA_ANT Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The VHA_ANT Registers have not gone through the reset\n");
    }

    LOG_INFO("SYSCON EVC_AGC Registers\n");
    read_data = read_reg_18a(EVC_AGC_EVC0_INTF_CFG_ADR, "EVCAGC_register");
    if(read_data == EVC_AGC_EVC0_INTF_CFG_DEFAULT)
    {
        LOG_PRINT("The SYSCON EVC_AGC Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The SYSCON EVC_AGC Registers have not gone through the reset\n");
    }

    LOG_INFO("SYSCON SPICSR Registers\n");
    read_data = read_reg_18a(SYS_CTRL_SPICSR_ADR, "SPICSR");
    if(read_data == SYS_CTRL_SPICSR_DEFAULT)
    {
        LOG_PRINT("The SYSCON SPICSR Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The SYSCON SPICSR Registers have not gone through the reset\n");
    }

    LOG_INFO("SYSCON SCRATCHBOTTOM Registers\n");
    read_data = read_reg_18a(SYS_CTRL_SCRATCHBOTTOM_ADR, "SYSCTRL_SCRATCH_register");
    if(read_data == SYS_CTRL_SCRATCHBOTTOM_DEFAULT)
    {
        LOG_PRINT("The SYSCON SYS_CTRL Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The SYSCON SYS_CTRL Registers have not gone through the reset\n");
    }

    LOG_INFO("DRF SCRATCH Registers\n");
    read_data = read_reg_18a((HUB_DRF0_APB_BASE) + (HUB_DRF_APB_HUB_SCRATCH_OFFSET), "DRF0_register");
    if(read_data == HUB_DRF_APB_HUB_SCRATCH_DEFAULT)
    {
        LOG_PRINT("The DRF SCRATCH Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The DRF SCRATCH Registers have not gone through the reset\n");
    }

    LOG_INFO("DRF CLK_EN Registers\n");
    read_data = read_reg_18a((HUB_DRF1_APB_BASE) + (HUB_DRF_APB_HUB_CLK_EN_OFFSET), "DRF1_register");
    if(read_data == HUB_DRF_APB_HUB_CLK_EN_DEFAULT)
    {
        LOG_PRINT("The DRF CLK_EN Register has gone through the reset with the default value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The DRF CLK_EN Registers have not gone through the reset\n");
    }

    LOG_INFO("DTS Registers\n");
    read_data = read_reg_18a(DTS_MON_EN_ADR, "DTS_register");
    if(read_data != DTS_MON_EN_DEFAULT)
    {
        LOG_PRINT("The DTS Register has NOT gone through the Cold reset as expected with the default value %xs\n", read_data);
    }
    else
    {
        LOG_ERROR("The DTS Registers have gone through the cold reset\n");
    }
}

/*****************************************************************************************
 * Function        : sw_cold_reset
 * Brief           : function to initiate the software cold reset
 *******************************************************************************************/
void sw_cold_reset()
{
    uint32_t read_data;

    LOG_INFO("To Read and clear all the previous Resets\n");
    read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");
    write_reg_18a(SYS_CTRL_RST_SOURCE_ADR, 0x000001FF, SYS_CTRL_RST_SOURCE_WR_MASK, "SYS_CTRL_RST_SOURCE");
    read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");

    LOG_INFO("enabling and asserting the cold reset\n");
    read_reg_18a(SYS_CTRL_SYS_CTRL_ADR,"SYS_CTRL_SYS_CTRL");
    //SYS_CTRL[31:30] = 2, SYS_CTRL[29]= 1;
    write_reg_18a(SYS_CTRL_SYS_CTRL_ADR, 0xa0000000, SYS_CTRL_SYS_CTRL_WR_MASK, "SYS_CTRL_SYS_CTRL_OFFSET");

    LOG_INFO("reenabling the pcie after the reset\n");
    system ("srpBusSelect -s spi");
    read_reg_18a(SYS_CTRL_RST_CTRL_ADR, "SYS_CTRL_RST_CTRL");
    write_reg_18a(SYS_CTRL_RST_CTRL_ADR, 0x0007ffff, SYS_CTRL_RST_CTRL_WR_MASK, "SYS_CTRL_RST_CTRL");
    write_reg_18a(DLNK_HUB_APB_PCIE_GLITCH_SUPPRESS_N_ADR, 0x00000001, 0x1, "PCIE_GLITCH_SUPPRESS");
    system ("srpBusSelect -s pci");

    LOG_INFO("To deassert the system out of software cold reset\n");
    write_reg_18a(SYS_CTRL_RST_CTRL_ADR, 0x0007ffff, SYS_CTRL_RST_CTRL_WR_MASK, "SYS_CTRL_RST_CTRL");

    LOG_INFO("To verify whether the previous reset is cold reset\n");
    read_data = read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");
    if(read_data == 0x4)
    {
        LOG_PRINT("The sw cold reset sequence is triggered with the RST_SOURCE value %x\n", read_data);
    }
    else
    {
        LOG_ERROR("The sw cold reset sequence is not triggered\n");
    }
}

/*****************************************************************************************
 * Function        : sw_warm_reset
 * Brief           : function to initiate the software warm reset
 *******************************************************************************************/
void sw_warm_reset()
{
    uint32_t read_data;

    LOG_INFO("To Read and clear all the previous Resets\n");
    read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");
    write_reg_18a(SYS_CTRL_RST_SOURCE_ADR, 0x000001FF, SYS_CTRL_RST_SOURCE_WR_MASK, "SYS_CTRL_RST_SOURCE");
    read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");

    LOG_INFO("enabling and asserting the warm reset\n");
    read_reg_18a(SYS_CTRL_SYS_CTRL_ADR,"SYS_CTRL_SYS_CTRL");
    //SYS_CTRL[31:30] = 1, SYS_CTRL[28]= 1;
    write_reg_18a(SYS_CTRL_SYS_CTRL_ADR, 0x50000000, SYS_CTRL_SYS_CTRL_WR_MASK, "SYS_CTRL_SYS_CTRL_OFFSET");

    LOG_INFO("reenabling the pcie after the reset\n");
    reenable_pcie_after_sys_reset();

    LOG_INFO("To deassert the system out of software warm reset from SW\n");
    write_reg_18a(SYS_CTRL_RST_CTRL_ADR, 0x0007ffff, SYS_CTRL_RST_CTRL_WR_MASK, "SYS_CTRL_RST_CTRL");

    LOG_INFO("To verify whether the previous reset is warm reset\n");
    read_data = read_reg_18a(SYS_CTRL_RST_SOURCE_ADR,"SYS_CTRL_RST_SOURCE");
    if(read_data == 0x8)
    {
        LOG_PRINT("The sw warm reset sequence is triggered with the RST_SOURCE value 0x%x\n", read_data);
    }
    else
    {
        LOG_ERROR("The sw warm reset sequence is not triggered\n");
    }
}





