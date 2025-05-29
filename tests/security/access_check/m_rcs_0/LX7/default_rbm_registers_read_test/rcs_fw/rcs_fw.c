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

/**
 * @file    rcs_fw.c
 * @brief   This test is to validate read access to all RBM registers.
 * @details This test is trying to access all the available RBM registers
 *          of all master bridges and slave bridges.
 */

/***********************************************
 * HEADERS     *
 ***********************************************/
#include "access_check_common_rcs_definitions.h"
#include "access_check_common_noc_rcs_definitions.h"
/***********************************************
 * DEFINES (consts, vars)      *
 ***********************************************/
#define RSM_BUF_SIZE          ( 3000 )
#define RCS_STARTED           ( 0xc001babe )
#define RCS_FINISHED          ( 0xdeaddead )

extern noc_type_t g_noc_bridges;
volatile uint32_t g_rsm_buf[RSM_BUF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t g_rsm_handshake __attribute__((section(".sram.ax.flag")));
volatile uint32_t g_skip_master_bridge __attribute__((section(".sram.reserved")));
volatile uint32_t g_skip_slave_bridge1 __attribute__((section(".sram.reserved")));
volatile uint32_t g_skip_slave_bridge2 __attribute__((section(".sram.reserved")));


int main()
{
    xthal_enable_interrupts();

    uint32_t wait_cnt = 0;
    if (!com_shared_mem_wait_for_ready ())
    {
        wait_cnt++;
    }

    g_rsm_handshake = RCS_STARTED;

    for (int i = 0; i < RSM_BUF_SIZE; i++)
        g_rsm_buf[i] = 0xdeadbeef;                         // Pre-fill g_rsm_buf with a known pattern

    uint32_t reg_num, index;
    volatile uint32_t* rd_addr_ptr;
    uint32_t skip_master_bridge = 0x00;

    skip_master_bridge = (0 << M_RCS_0)       |
                         (0 << M_RCS_1)       |
                         (0 << M_PCIE)        |
                         (0 << M_CS_DBG)      |
                         (0 << M_SYSCON_1)    |
                         (0 << M_SYSCON_0)    |
                         (0 << M_DRF0_MEM_FB) |
                         (0 << M_DRF1_MEM_FB);

    g_skip_master_bridge = skip_master_bridge;             // Will be shared with the HOST driver

    index = 0;
    if(!(skip_master_bridge & (1 << M_RCS_0)))
    {
        m_rcs_0_type_t* m_rcs_0 = &(g_noc_bridges.m_rcs_0);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_rcs_0->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_rcs_0->base_addr + m_rcs_0->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_RCS_1)))
    {
        m_rcs_1_type_t* m_rcs_1 = &(g_noc_bridges.m_rcs_1);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_rcs_1->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_rcs_1->base_addr + m_rcs_1->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_PCIE)))
    {
        m_pcie_type_t* m_pcie = &(g_noc_bridges.m_pcie);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_pcie->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_pcie->base_addr + m_pcie->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_CS_DBG)))
    {
        m_cs_dbg_type_t* m_cs_dbg = &(g_noc_bridges.m_cs_dbg);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_cs_dbg->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_cs_dbg->base_addr + m_cs_dbg->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_SYSCON_1)))
    {
        m_syscon_1_type_t* m_syscon_1 = &(g_noc_bridges.m_syscon_1);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_syscon_1->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_syscon_1->base_addr + m_syscon_1->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_SYSCON_0)))
    {
        m_syscon_0_type_t* m_syscon_0 = &(g_noc_bridges.m_syscon_0);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_syscon_0->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_syscon_0->base_addr + m_syscon_0->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_DRF0_MEM_FB)))
    {
        m_drf0_mem_fb_type_t* m_drf0_mem_fb = &(g_noc_bridges.m_drf0_mem_fb);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_drf0_mem_fb->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_drf0_mem_fb->base_addr + m_drf0_mem_fb->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    if(!(skip_master_bridge & (1 << M_DRF1_MEM_FB)))
    {
        m_drf1_mem_fb_type_t* m_drf1_mem_fb = &(g_noc_bridges.m_drf1_mem_fb);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_drf1_mem_fb->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(m_drf1_mem_fb->base_addr + m_drf1_mem_fb->regs[reg_num].offset);

            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    uint32_t skip_slave_bridge1, skip_slave_bridge2;
    skip_slave_bridge1 = (0 << S_JESD0)           |
                         (0 << S_JESD1)           |
                         (0 << S_JESD2)           |
                         (0 << S_JESD3)           |
                         (0 << S_DRF0_FB_ANT)     |
                         (0 << S_DRF0_FB_SYS)     |
                         (0 << S_DRF0_TRXANT0)    |
                         (0 << S_DRF0_ANT0)       |
                         (0 << S_DRF0_TRXSYS0)    |
                         (0 << S_DRF0_TRXANT1)    |
                         (0 << S_DRF0_ANT1)       |
                         (0 << S_DRF0_TRXSYS1)    |
                         (0 << S_DRF0_TRXANT2)    |
                         (0 << S_DRF0_TRXSYS2)    |
                         (0 << S_DRF0_TRXANT3)    |
                         (0 << S_DRF0_TRXSYS3)    |
                         (0 << S_DRF0_MEM)        |
                         (0 << S_DRF0_MEM_FB)     |
                         (1 << S_DRF1_FB_ANT)     |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_FB_SYS)     |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXANT0)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_ANT0)       |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXSYS0)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXANT1)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_ANT1)       |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXSYS1)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXANT2)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXSYS2)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXANT3)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_TRXSYS3)    |        // Not available on FRIO, so disabling it.
                         (1 << S_DRF1_MEM)        |        // Not available on FRIO, so disabling it.
                         (1ULL << S_DRF1_MEM_FB);          // Not available on FRIO, so disabling it.

    skip_slave_bridge2 = (0 << (S_SYSCON_MAIN - 32))  |
                         (0 << (S_PCIE - 32))         |
                         (0 << (S_PCIE_DBI - 32))     |
                         //(1 << (S_PCIE_CFG - 32))   |    // Not available in RBM register html
                         (0 << (S_VEX_CAR - 32))      |
                         (0 << (S_VEX0 - 32))         |
                         (0 << (S_VEX1 - 32))         |
                         (0 << (S_VEX2 - 32))         |
                         //(1 << (S_VEX_DBG0 - 32))   |    // Not available in RBM register html
                         //(1 << (S_VEX_DBG1 - 32))   |    // Not available in RBM register html
                         //(1 << (S_VEX_DBG2 - 32))   |    // Not available in RBM register html
                         (0 << (S_VHA0 - 32))         |
                         (0 << (S_VHA1 - 32))         |
                         (0 << (S_VHA2 - 32))         |
                         (0 << (S_VHA3 - 32))         |
                         (1 << (S_VHA4 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_VHA5 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_VHA6 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_VHA7 - 32))         |    // Not available on FRIO, so disabling it.
                         (0 << (S_V2D0 - 32))         |
                         (0 << (S_V2D1 - 32))         |
                         (0 << (S_V2D2 - 32))         |
                         (0 << (S_V2D3 - 32))         |
                         (1 << (S_V2D4 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_V2D5 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_V2D6 - 32))         |    // Not available on FRIO, so disabling it.
                         (1 << (S_V2D7 - 32))         |    // Not available on FRIO, so disabling it.
                         //(1 << (S_HUB - 32))        |    // Not available in RBM register html
                         (0 << (S_RCS0 - 32))         |
                         (0 << (S_RCS1 - 32))         |
                         //(1 << (S_RCS_CS - 32);          // Not available in RBM register html
                         (0ULL << (S_VEX_SFC_RBM - 32));

    g_skip_slave_bridge1 = skip_slave_bridge1;
    g_skip_slave_bridge2 = skip_slave_bridge2;
    bridge_type_t bridge_num;
    s_bridge_type_t* s_bridge;
    uint32_t skip_slave_bridge = skip_slave_bridge1;
    for(bridge_num = S_JESD0; bridge_num < ARRAY_SIZE(g_noc_bridges.s_bridges); bridge_num++)
    {
        if(bridge_num > S_DRF1_MEM_FB)
            skip_slave_bridge = skip_slave_bridge2;
        if(!(skip_slave_bridge & (1 << bridge_num)))
        {
            s_bridge = &(g_noc_bridges.s_bridges[bridge_num]);

            for(reg_num = 0; reg_num < ARRAY_SIZE(s_bridge->regs); reg_num++)
            {
                rd_addr_ptr = (volatile uint32_t*)(s_bridge->base_addr + s_bridge->regs[reg_num].offset);
                g_rsm_buf[index++] = *rd_addr_ptr;         // Core reading from register address
            }
        }
    }
    if(!(skip_slave_bridge & (1 << bridge_num)))
    {
        s_bridge_rbm_type_t* s_bridge_rbm = &(g_noc_bridges.s_bridge_rbm);

        for(reg_num = 0; reg_num < ARRAY_SIZE(s_bridge_rbm->regs); reg_num++)
        {
            rd_addr_ptr = (volatile uint32_t*)(s_bridge_rbm->base_addr + s_bridge_rbm->regs[reg_num].offset);
            g_rsm_buf[index++] = *rd_addr_ptr;             // Core reading from register address
        }
    }

    g_rsm_handshake = RCS_FINISHED;

    return 0;
}


