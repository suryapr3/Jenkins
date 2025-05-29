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

// Macros
#define RCS_CORE_STARTED          ( 0xc001babe )
#define RCS_CORE_FINISHED         ( 0xdeaddead )
#define RSM_BUF_ADDR              ( 0x00230000 )
#define RSM_HANDSHAKE_ADDR        ( 0x0023ffec )
#define RSM_SKIP_MASTER_BRDG_ADDR ( 0x00232ee0 )
#define RSM_SKIP_SLAVE_BRDG1_ADDR ( 0x00232ee4 )
#define RSM_SKIP_SLAVE_BRDG2_ADDR ( 0x00232ee8 )
#define RSM_PATTERN_ADDR          ( 0x0023fff8 )
#define HANDSHAKE_MOVEON          ( 0x12345678 )

// External variables
extern char g_compile_time[];
extern noc_type_t g_noc_bridges;

int main(int argc, const char * argv[])
{
    int dev_id = 0;
    int rcs_core;
    srp_st_t srp_st = SRP_ST_SUCCESS;
    uint32_t pattern;

    init();
    jump_to_ram();
    LOG_PRINT("\nINFO: Logger beginning\n");
    LOG_PRINT("Test: rbm registers write read test\n");
    LOG_PRINT("      %s\n", g_compile_time);
    LOG_PRINT("      BUILD_DIR: %s\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    // setting the configuration -->halt,reset,remove all reset
    rcs_halt_soft_reset();
    // sets RCS configuration parameters
    srp_rcs_config_t rcs_params;
    // sets rcs_params to 0
    memset(&rcs_params, 0, sizeof(rcs_params));
    rcs_core = (int)argv[0];
    pattern = (uint32_t)argv[1];
    LOG_PRINT("INFO: argv[0] = COREID = %d\n", rcs_core);
    LOG_PRINT("INFO: argv[1] = PATTERN = 0x%x\n", pattern);

    if ((rcs_core < RCS_CORE_AX) || (rcs_core > RCS_CORE_TX))
    {
        LOG_PRINT("ERROR: COREID can take only values 0 or 1 or 2\nExiting...!\n");
        return FAILURE;
    }

    srp_rcs_rcp_t rcs_core_id;

    if (rcs_core == RCS_CORE_AX)
    {
        rcs_core_id = SRP_RCS_RCP_CTRL_AX;
        rcs_params.rcs_cfg[rcs_core_id].img_file = "./rcs_fw/ax_rcs_fw.elf";
    } else if (rcs_core == RCS_CORE_RX)
    {
        rcs_core_id = SRP_RCS_RCP_CTRL_RX;
        rcs_params.rcs_cfg[rcs_core_id].img_file = "./rcs_fw/rx_rcs_fw.elf";
    } else if (rcs_core == RCS_CORE_TX)
    {
        rcs_core_id = SRP_RCS_RCP_CTRL_TX;
        rcs_params.rcs_cfg[rcs_core_id].img_file = "./rcs_fw/tx_rcs_fw.elf";
    }

    // sets up all the RCS cores with the given configuration
    rcs_config(&rcs_params);
    LOG_PRINT("HOST: Downloaded the elf %s to CORE-%d\n", rcs_params.rcs_cfg[rcs_core_id].img_file, rcs_core);

    // starting the core
    LOG_PRINT("HOST: Starting RCS CORE-%d\n", rcs_core);
    rcs_rcp_start(rcs_core_id);

    int reg_num;
    uint32_t rsm_buf_addr, rd_addr, num_slaves_connected;
    uint32_t act_val, exp_val, rd_mask, result, wr_mask;
    exp_val = pattern;
    volatile uint32_t handshake;
    int srpstatus = 0;
    int i;
    volatile uint32_t* wr_rd_addr_ptr;

    // write the pattern to the memory so that the RCS will write that to the targets while running
    int rv;
    LOG_PRINT("INFO: Writing pattern-0x%x to the RSM memory (0x%x)\n", pattern, RSM_PATTERN_ADDR);
    if(rv = write_reg_18a(RSM_PATTERN_ADDR, pattern, 0xffffffff, "PATTERN"))
    {
        LOG_PRINT("ERROR: Writing pattern-0x%x to the RSM memory (0x%x) failed with return status-0x%x\n", pattern, RSM_PATTERN_ADDR, rv);
        return FAILURE;
    }
    // waiting for the RCS CORE to update an RSM_HANDSHAKE_ADDR as a means for handshaking
    int cnt = 0;
    LOG_PRINT("HOST: Waiting for the RCS CORE-%d to update an RSM_HANDSHAKE_ADDR (0x%x)\n", rcs_core, RSM_HANDSHAKE_ADDR);
    while ((handshake != RCS_CORE_FINISHED) && (cnt++ < 65536))
    {
        handshake = read_reg_18a(RSM_HANDSHAKE_ADDR, "RSM_HANDSHAKE_ADDR");
    }
    if(cnt > 65536)
    {
        LOG_PRINT("ERROR: Waited for %d cycles, but RCS CORE-%d is not updating RSM_HANDSHAKE_ADDR (0x%x)\n       Exiting..!\n",
                  (cnt - 1), rcs_core, RSM_HANDSHAKE_ADDR);
        LOG_PRINT("INFO: [%x] = %x\n", RSM_HANDSHAKE_ADDR, handshake);
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }
    LOG_PRINT("INFO: Checking the results of accessing RBM registers\n");

    uint32_t skip_master_bridge = 0x00;
    skip_master_bridge = read_reg_18a(RSM_SKIP_MASTER_BRDG_ADDR, "RSM_SKIP_MASTER_BRDG_ADDR");
    LOG_PRINT("\nINFO: skip_master_bridge = %x\n", skip_master_bridge);

    char* msg = "INFO";
    rsm_buf_addr = RSM_BUF_ADDR;

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

            if((uint32_t)wr_rd_addr_ptr == 0x00d306c0)     // VEX_SFC_S_RBM
            {
                // Writing any value except the default value to this register disable access to the rbm register space.
                //  So, skip it.
                reg_num = reg_num + 2;
                continue;
            }

            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it
            rd_addr = rsm_buf_addr;
            wr_mask = m_rcs_0->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_rcs_0->regs[reg_num].offset, act_val, exp_val, wr_mask, m_rcs_0->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = rsm_buf_addr;
            wr_mask = m_rcs_1->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_rcs_1->regs[reg_num].offset, act_val, exp_val, wr_mask, m_rcs_1->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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
            if((uint32_t)wr_rd_addr_ptr == 0x00c086c0)     // RCS_S_RCS_0
            {
                // Writing any value except the default value to this register causes access denial to RCS memory space.
                //  So, skip it.
                reg_num = reg_num + 2;
                continue;
            }
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
              (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = rsm_buf_addr;
            wr_mask = m_pcie->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_pcie->regs[reg_num].offset, act_val, exp_val, wr_mask, m_pcie->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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

            rd_addr = rsm_buf_addr;
            wr_mask = m_cs_dbg->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_cs_dbg->regs[reg_num].offset, act_val, exp_val, wr_mask, m_cs_dbg->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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

            rd_addr = rsm_buf_addr;
            wr_mask = m_syscon_1->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_syscon_1->regs[reg_num].offset, act_val, exp_val, wr_mask, m_syscon_1->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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
            if((((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xe20) || (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf20) ||
               (((uint32_t)wr_rd_addr_ptr & 0xfff) == 0xf40))
                continue;                                  // (offset 0xe20) -> error inject register is 'V', so skip it
                                                           // (offset 0xf20, 0xf40) -> event counter registers, so skip it

            rd_addr = rsm_buf_addr;
            wr_mask = m_syscon_0->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_syscon_0->regs[reg_num].offset, act_val, exp_val, wr_mask, m_syscon_0->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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

            rd_addr = rsm_buf_addr;
            wr_mask = m_drf0_mem_fb->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_drf0_mem_fb->regs[reg_num].offset, act_val, exp_val, wr_mask, m_drf0_mem_fb->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
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

            rd_addr = rsm_buf_addr;
            wr_mask = m_drf1_mem_fb->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      m_drf1_mem_fb->regs[reg_num].offset, act_val, exp_val, wr_mask, m_drf1_mem_fb->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
        }
    }
    uint64_t skip_slave_bridge1, skip_slave_bridge2;
    uint64_t skip_slave_bridge = 0x0000000000000000;
    skip_slave_bridge1 = read_reg_18a(RSM_SKIP_SLAVE_BRDG1_ADDR, "RSM_SKIP_SLAVE_BRDG1_ADDR");
    skip_slave_bridge2 = read_reg_18a(RSM_SKIP_SLAVE_BRDG2_ADDR, "RSM_SKIP_SLAVE_BRDG2_ADDR");
    skip_slave_bridge= (skip_slave_bridge2 << 32 ) | skip_slave_bridge1 ;
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

                rd_addr = rsm_buf_addr;
                wr_mask = s_bridge->regs[reg_num].wr_mask;
                act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
                result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
                msg = "INFO";
                if(result) msg = "ERROR";
                LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                          (s_bridge->regs[reg_num].offset), act_val, exp_val, wr_mask, s_bridge->regs[reg_num].reg_name);
                rsm_buf_addr += 0x4;
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

            rd_addr = rsm_buf_addr;
            wr_mask = s_bridge_rbm->regs[reg_num].wr_mask;
            act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
            result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
            msg = "INFO";
            if(result) msg = "ERROR";
            LOG_PRINT("%s: offset = %x, act_val = %x, exp_val = %x, wr_mask = %x, reg_name = %s\n", msg,
                      (s_bridge_rbm->regs[reg_num].offset), act_val, exp_val, wr_mask, s_bridge_rbm->regs[reg_num].reg_name);
            rsm_buf_addr += 0x4;
        }
        }
srp_return:

    srp_status_print("main return value: ", srp_st);

    LOG_PRINT("\nHOST: End of test execution\n");
}


