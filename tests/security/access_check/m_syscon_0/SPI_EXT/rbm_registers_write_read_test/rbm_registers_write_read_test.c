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

#include "access_check_common_definitions.h"
#include "access_check_common_noc_definitions.h"

// External variables
extern char g_compile_time[];
extern noc_type_t g_noc_bridges;

int main(int argc, const char * argv[])
{
    srp_st_t srp_st = SRP_ST_SUCCESS;
    uint32_t pattern;

    init();
    system ("srpBusSelect -s spi");                        // Enabling SPI EXT

    LOG_PRINT("\nINFO: Logger beginning\n");
    LOG_PRINT("Test: rbm registers write read test\n");
    LOG_PRINT("      %s\n", g_compile_time);
    LOG_PRINT("      BUILD_DIR: %s\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    pattern = (uint32_t)argv[0];
    LOG_PRINT("INFO: argv[0] = PATTERN = 0x%x\n", pattern);
    int reg_num;
    uint32_t rd_addr, num_slaves_connected;
    uint32_t act_val, def_val, exp_val, rd_mask, result, wr_mask;
    exp_val = pattern;
    volatile uint32_t* wr_rd_addr_ptr;

    uint32_t skip_master_bridge = 0x00;

    skip_master_bridge = (0 << M_RCS_0)       |
                         (0 << M_RCS_1)       |
                         (0 << M_PCIE)        |
                         (0 << M_CS_DBG)      |
                         (0 << M_SYSCON_1)    |
                         (0 << M_SYSCON_0)    |
                         (0 << M_DRF0_MEM_FB) |
                         (0 << M_DRF1_MEM_FB);

    LOG_PRINT("\nINFO: skip_master_bridge = %x\n", skip_master_bridge);

    char* msg = "INFO";

    num_slaves_connected = 62;                             // M_RCS_0
    if(!(skip_master_bridge & (1 << M_RCS_0)))
    {
        m_rcs_0_type_t* m_rcs_0 = &(g_noc_bridges.m_rcs_0);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_rcs_0->name, m_rcs_0->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_rcs_0->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_rcs_0->base_addr + m_rcs_0->regs[reg_num].offset);

            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it
            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_rcs_0->regs[reg_num].wr_mask;
            rd_mask = m_rcs_0->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_rcs_0->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_rcs_0->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_rcs_0->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_rcs_0->regs[reg_num].offset, act_val, exp_val, wr_mask, m_rcs_0->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 62;                             // M_RCS_1
    if(!(skip_master_bridge & (1 << M_RCS_1)))
    {
        m_rcs_1_type_t* m_rcs_1 = &(g_noc_bridges.m_rcs_1);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_rcs_1->name, m_rcs_1->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_rcs_1->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_rcs_1->base_addr + m_rcs_1->regs[reg_num].offset);
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                 continue;                                 // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_rcs_1->regs[reg_num].wr_mask;
            rd_mask = m_rcs_1->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_rcs_1->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_rcs_1->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_rcs_1->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_rcs_1->regs[reg_num].offset, act_val, exp_val, wr_mask, m_rcs_1->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 63;                             // M_PCIE
    if(!(skip_master_bridge & (1 << M_PCIE)))
    {
        m_pcie_type_t* m_pcie = &(g_noc_bridges.m_pcie);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_pcie->name, m_pcie->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_pcie->regs); reg_num++)
        {

            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_pcie->base_addr + m_pcie->regs[reg_num].offset);

            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
              (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_pcie->regs[reg_num].wr_mask;
            rd_mask = m_pcie->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_pcie->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_pcie->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_pcie->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_pcie->regs[reg_num].offset, act_val, exp_val, wr_mask, m_pcie->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 4;                              // M_CS_DBG
    if(!(skip_master_bridge & (1 << M_CS_DBG)))
    {
        m_cs_dbg_type_t* m_cs_dbg = &(g_noc_bridges.m_cs_dbg);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_cs_dbg->name, m_cs_dbg->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_cs_dbg->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_cs_dbg->base_addr + m_cs_dbg->regs[reg_num].offset);
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_cs_dbg->regs[reg_num].wr_mask;
            rd_mask = m_cs_dbg->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_cs_dbg->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_cs_dbg->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_cs_dbg->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_cs_dbg->regs[reg_num].offset, act_val, exp_val, wr_mask, m_cs_dbg->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 63;                             // M_SYSCON_1
    if(!(skip_master_bridge & (1 << M_SYSCON_1)))
    {
        m_syscon_1_type_t* m_syscon_1 = &(g_noc_bridges.m_syscon_1);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_syscon_1->name, m_syscon_1->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_syscon_1->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_syscon_1->base_addr + m_syscon_1->regs[reg_num].offset);
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_syscon_1->regs[reg_num].wr_mask;
            rd_mask = m_syscon_1->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_syscon_1->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_syscon_1->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_syscon_1->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_syscon_1->regs[reg_num].offset, act_val, exp_val, wr_mask, m_syscon_1->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 64;                             // M_SYSCON_0
    if(!(skip_master_bridge & (1 << M_SYSCON_0)))
    {
        m_syscon_0_type_t* m_syscon_0 = &(g_noc_bridges.m_syscon_0);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_syscon_0->name, m_syscon_0->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_syscon_0->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_syscon_0->base_addr + m_syscon_0->regs[reg_num].offset);

            if(((uint32_t)wr_rd_addr_ptr == 0x00d586c0)| ((uint32_t)wr_rd_addr_ptr == 0x00d586f0))
            {
                // VEX_SFC_S_RBM & RCS_S_RCS_0
                // Writing any value except the default value to these registers causes access denial to RCS/RBM memory space.
                //  So, skip it.
                reg_num = reg_num + 2;
                continue;
            }

            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it
            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_syscon_0->regs[reg_num].wr_mask;
            rd_mask = m_syscon_0->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_syscon_0->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_syscon_0->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_syscon_0->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_syscon_0->regs[reg_num].offset, act_val, exp_val, wr_mask, m_syscon_0->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 62;                             // M_DRF0_MEM_FB
    if(!(skip_master_bridge & (1 << M_DRF0_MEM_FB)))
    {
        m_drf0_mem_fb_type_t* m_drf0_mem_fb = &(g_noc_bridges.m_drf0_mem_fb);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_drf0_mem_fb->name, m_drf0_mem_fb->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_drf0_mem_fb->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_drf0_mem_fb->base_addr + m_drf0_mem_fb->regs[reg_num].offset);
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_drf0_mem_fb->regs[reg_num].wr_mask;
            rd_mask = m_drf0_mem_fb->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_drf0_mem_fb->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_drf0_mem_fb->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_drf0_mem_fb->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_drf0_mem_fb->regs[reg_num].offset, act_val, exp_val, wr_mask, m_drf0_mem_fb->regs[reg_num].reg_name);
        }
    }

    num_slaves_connected = 62;                             // M_DRF1_MEM_FB
    if(!(skip_master_bridge & (1 << M_DRF1_MEM_FB)))
    {
        m_drf1_mem_fb_type_t* m_drf1_mem_fb = &(g_noc_bridges.m_drf1_mem_fb);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", m_drf1_mem_fb->name, m_drf1_mem_fb->base_addr);

        for(reg_num = 0; reg_num < ARRAY_SIZE(m_drf1_mem_fb->regs); reg_num++)
        {
            if((reg_num < (num_slaves_connected * 3)) && (((reg_num + 1) % 3 ) == 0))
                continue;                                  // Every 3rd register is a relocation register which are RO, so skip it

            wr_rd_addr_ptr = (volatile uint32_t*)(m_drf1_mem_fb->base_addr + m_drf1_mem_fb->regs[reg_num].offset);
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = m_drf1_mem_fb->regs[reg_num].wr_mask;
            rd_mask = m_drf1_mem_fb->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, m_drf1_mem_fb->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, m_drf1_mem_fb->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, m_drf1_mem_fb->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_drf1_mem_fb->regs[reg_num].offset, act_val, exp_val, wr_mask, m_drf1_mem_fb->regs[reg_num].reg_name);
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

    uint64_t skip_slave_bridge = 0x0000000000000000;
    skip_slave_bridge = (skip_slave_bridge2 << 32 ) | skip_slave_bridge1;
    LOG_PRINT("\nINFO: skip_slave_bridge = %x_%x\n", (skip_slave_bridge >> 32), skip_slave_bridge);

    bridge_type_t bridge_num;
    s_bridge_type_t* s_bridge;
    uint32_t max_regs;
    for(bridge_num = S_JESD0; bridge_num < ARRAY_SIZE(g_noc_bridges.s_bridges); bridge_num++)
    {
        if(!(skip_slave_bridge & (1ULL << bridge_num)))
        {
            s_bridge = &(g_noc_bridges.s_bridges[bridge_num]);
            LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", s_bridge->name, s_bridge->base_addr);
            max_regs = ARRAY_SIZE(s_bridge->regs);
            for(reg_num = 0; reg_num < max_regs; reg_num++)
            {
                wr_rd_addr_ptr = (volatile uint32_t*)(s_bridge->base_addr + s_bridge->regs[reg_num].offset);
                if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf10))
                    continue;                              // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

                rd_addr = (uint32_t)wr_rd_addr_ptr;
                wr_mask = s_bridge->regs[reg_num].wr_mask;
                rd_mask = s_bridge->regs[reg_num].rd_mask;
                write_reg_18a(rd_addr, pattern, wr_mask, s_bridge->regs[reg_num].reg_name);
                result = read_reg_expect_18a(rd_addr, pattern, wr_mask, s_bridge->regs[reg_num].reg_name);
                act_val = read_reg_18a(rd_addr, s_bridge->regs[reg_num].reg_name);
                msg = "INFO";
                if(result) msg = "ERROR";
                LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                          (s_bridge->regs[reg_num].offset), act_val, exp_val, wr_mask, s_bridge->regs[reg_num].reg_name);
            }
        }
    }

    if(!(skip_slave_bridge & (1ULL << bridge_num)))
    {
        s_bridge_rbm_type_t* s_bridge_rbm = &(g_noc_bridges.s_bridge_rbm);
        LOG_PRINT("\nINFO: BRIDGE: %s, base_addr: 0x%x\n", s_bridge_rbm->name, s_bridge_rbm->base_addr);
        max_regs = ARRAY_SIZE(s_bridge_rbm->regs);
        for(reg_num = 0; reg_num < max_regs; reg_num++)
        {
            wr_rd_addr_ptr = (volatile uint32_t*)(s_bridge_rbm->base_addr + s_bridge_rbm->regs[reg_num].offset);
            if(((uint32_t)wr_rd_addr_ptr & 0xfff) == 0x60)
                continue;                                  // (offset 0x60) -> error inject register is 'V', so skip it

            rd_addr = (uint32_t)wr_rd_addr_ptr;
            wr_mask = s_bridge_rbm->regs[reg_num].wr_mask;
            rd_mask = s_bridge_rbm->regs[reg_num].rd_mask;
            write_reg_18a(rd_addr, pattern, wr_mask, s_bridge_rbm->regs[reg_num].reg_name);
            result = read_reg_expect_18a(rd_addr, pattern, wr_mask, s_bridge_rbm->regs[reg_num].reg_name);
            act_val = read_reg_18a(rd_addr, s_bridge_rbm->regs[reg_num].reg_name);
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      (s_bridge_rbm->regs[reg_num].offset), act_val, exp_val, wr_mask, s_bridge_rbm->regs[reg_num].reg_name);
        }
        }
srp_return:

    srp_status_print("main return value: ", srp_st);

    LOG_PRINT("\nHOST: End of test execution\n");
}


