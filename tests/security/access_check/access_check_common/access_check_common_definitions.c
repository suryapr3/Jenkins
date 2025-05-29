/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
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
 *
 *********************************************************************************************/

/*
 * @file     This file contains functions and declarations that are applicable for all the NOC tests.
 * **/
#include <stdio.h>
#include "access_check_common_definitions.h"

int rcs_halt_soft_reset(void)
{
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
    unsigned rcs_ctrl = 0;
    int rv;

    rcs_gpreg_rcs_cfg_reg_t  rcs_config_reg = {.value = RCS_GPREG_RCS_CFG_DEFAULT};
    rcs_gpreg_core0_ctrl_reg_t core0_control_reg = {.value = RCS_GPREG_CORE0_CTRL_DEFAULT};
    rcs_gpreg_core1_ctrl_reg_t core1_control_reg = {.value = RCS_GPREG_CORE1_CTRL_DEFAULT};
    rcs_gpreg_core2_ctrl_reg_t core2_control_reg = {.value = RCS_GPREG_CORE2_CTRL_DEFAULT};
    rcs_gpreg_core3_ctrl_reg_t core3_control_reg = {.value = RCS_GPREG_CORE3_CTRL_DEFAULT};
    rcs_gpreg_soft_rst_reg_t soft_reset_reg = {.value = RCS_GPREG_SOFT_RST_DEFAULT};

    // halt core0/1/2/3
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_CORE0_CTRL_ADR");
    write_reg_18a(RCS_GPREG_CORE1_CTRL_ADR, RCS_GPREG_CORE1_CTRL_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_CORE1_CTRL_ADR");
    write_reg_18a(RCS_GPREG_CORE2_CTRL_ADR, RCS_GPREG_CORE2_CTRL_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_CORE2_CTRL_ADR");
    write_reg_18a(RCS_GPREG_CORE3_CTRL_ADR, RCS_GPREG_CORE3_CTRL_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_CORE3_CTRL_ADR");

    // enable soft reset
    rcs_config_reg.SOFT_RST_LOCK = 0xFA;
    write_reg_18a(RCS_GPREG_RCS_CFG_ADR, rcs_config_reg.value, 0xFFFFFFFF, "RCS_GPREG_RCS_CONFIG_ADR");

    // soft reset core0
    core0_control_reg.SOFT_RESET_CORE0 = 0x1;
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, soft_reset_reg.value, 0xFFFFFFFF, "RCS_GPREG_CORE0_CTRL_ADR");
    //soft reset core 1/2/3
    soft_reset_reg.CORE1_CPU_SFT_RST = 0x1;
    soft_reset_reg.CORE2_CPU_SFT_RST = 0x1;
    soft_reset_reg.CORE3_CPU_SFT_RST = 0x1;
    write_reg_18a(RCS_GPREG_SOFT_RST_ADR, soft_reset_reg.value, 0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

    sleep(1);

    // remove soft reset core0
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_CORE0_CTRL_ADR");
    // remove soft reset of cores 1/2/3
    write_reg_18a(RCS_GPREG_SOFT_RST_ADR, RCS_GPREG_SOFT_RST_DEFAULT, 0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

    sleep(1);
}

/**
 * function         poll_rsm_flag()
 * @brief           Function for polling the RSM flag.
 * @param [in]      srp, address, message
 */
int poll_rsm_flag(void* srp, uint32_t addr, uint32_t message)
{
    volatile uint32_t val, flags;
    int cnt, rv;

    cnt = 0;
    do
    {
        val = (volatile uint32_t)read_reg_18a(addr, "RSM_HANDSHAKE_ADDR");
        usleep(1);
        if(cnt++ > (64 * 512))
        {
            LOG_PRINT("ERROR: Waited for %d cycles, but RSM_FLAG is not getting updated by the RCS\n", cnt);
            LOG_PRINT("ERROR: RSM_FLAG = %x, but expected = %x\n", val, message);
            return FAILURE;
        }
    } while(val != message);

    return 0;

}

/**
 * function         enable_drf0_memories()
 * @brief           Function for setting power down and enable bit for drf0 capture, mem_fb and fb_ant0 memory
 */

void enable_drf0_memories()
{
    uint32_t val;

    // Disabling Capture memory's power down control
    write_reg_18a(MEM_CAP0_BASE + MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET, 0x0, MEM_CAP_WRAP_PWR_DOWN_CTRL_PWR_DOWN_BF_MSK,
                  "MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET");
    val = read_reg_18a(MEM_CAP0_BASE + MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET, "MEM_CAP_WRAP_PWR_DOWN_CTRL_OFFSET");

    // Enabling Feedback memory
    write_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_EN_OFFSET, 0x1, MEM_FB_EN_WR_MASK, "MEM_FB_EN_OFFSET");
    val = read_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_EN_OFFSET, "MEM_FB_EN_OFFSET");

    // Disabling Feedback memory's power down control
    write_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_PWR_DOWN_CTRL_OFFSET, 0x0, MEM_FB_PWR_DOWN_CTRL_WR_MASK,
                  "MEM_FB_PWR_DOWN_CTRL_OFFSET");
    val = read_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_PWR_DOWN_CTRL_OFFSET, "MEM_FB_PWR_DOWN_CTRL_OFFSET");

    // Enabling CMEM CFG0 memory
    write_reg_18a(FB_ANT0_CMEM_CFG0_BASE + CMEM_CFG_OFFSET, 0x1, CMEM_CFG_WR_MASK, "CMEM_CFG0_OFFSET");
    val = read_reg_18a(FB_ANT0_CMEM_CFG0_BASE + CMEM_CFG_OFFSET, "CMEM_CFG0_OFFSET");

    // Enabling CMEM CFG1 memory
    write_reg_18a(FB_ANT0_CMEM_CFG1_BASE + CMEM_CFG_OFFSET, 0x1, CMEM_CFG_WR_MASK, "CMEM_CFG1_OFFSET");
    val = read_reg_18a(FB_ANT0_CMEM_CFG1_BASE + CMEM_CFG_OFFSET, "CMEM_CFG1_OFFSET");

    // Power down control register for: descriptor memory and four DMA FIFO memories
    write_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET, 0x0, MEM_FB_PWR_DOWN_CTRL_CHAIN_WR_MASK,
                  "MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET");
    val = read_reg_18a(MEM_FB0_CFG_BASE + MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET, "MEM_FB_PWR_DOWN_CTRL_CHAIN_OFFSET");

    // Enabling fb DMAC0 DW_axi_dmac Common Register Space Interrupt Enable Register
    write_reg_18a(MEM_FB0_DMAC_0_BASE + MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_OFFSET, 0xffffffff,
                  MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_WR_MASK, "MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_OFFSET");
    val = read_reg_18a(MEM_FB0_DMAC_0_BASE + MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_OFFSET,
                       "MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_OFFSET");

    // Enabling fb DMAC0 DW_axi_dmac Channel Interrupt Status Register
    write_reg_18a(MEM_FB0_DMAC_0_BASE + MEM_FB_DMAC_CH1_INTSTAT_ENREG_OFFSET, 0xffffffff,
                  MEM_FB_DMAC_CH1_INTSTAT_ENREG_WR_MASK, "MEM_FB_DMAC_CH1_INTSTAT_ENREG_OFFSET");
    val = read_reg_18a(MEM_FB0_DMAC_0_BASE + MEM_FB_DMAC_CH1_INTSTAT_ENREG_OFFSET, "MEM_FB_DMAC_CH1_INTSTAT_ENREG_OFFSET");
}

