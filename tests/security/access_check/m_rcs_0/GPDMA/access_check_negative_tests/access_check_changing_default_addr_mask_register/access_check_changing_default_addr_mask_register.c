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
#define RSM_SKIP_TARGETS1_ADDR    ( 0x0023fff0 )
#define RSM_SKIP_TARGETS2_ADDR    ( 0x0023fff4 )
#define RSM_PATTERN_ADDR          ( 0x0023fff8 )
#define HANDSHAKE_MOVEON          ( 0x12345678 )

// External variables
extern char g_compile_time[];
extern target_list_type_t g_noc_targets[64];
extern noc_type_t g_noc_bridges;

int main(int argc, const char* argv[])
{
    int dev_id = 0;
    int rcs_core;
    srp_st_t srp_st = SRP_ST_SUCCESS;
    uint32_t pattern;

    init();
    enable_drf0_memories();
    LOG_PRINT("\nINFO: Logger beginning\n");
    LOG_PRINT("Test: Negative test: access_check_changing_default_addr_mask_register\n");
    LOG_PRINT("      %s\n", g_compile_time);
    LOG_PRINT("      BUILD_DIR: %s\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        LOG_PRINT("Exiting test..!\n");
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
    if((rcs_core < RCS_CORE_AX) || (rcs_core > RCS_CORE_TX))
    {
        LOG_PRINT("ERROR: COREID can take only values 0 or 1 or 2\nExiting...!\n");
        return FAILURE;
    }

    srp_rcs_rcp_t rcs_core_id;

    if(rcs_core == RCS_CORE_AX)
    {
        rcs_core_id = SRP_RCS_RCP_CTRL_AX;
        rcs_params.rcs_cfg[rcs_core_id].img_file = "./rcs_fw/ax_rcs_fw.elf";
    } else if(rcs_core == RCS_CORE_RX)
    {
        rcs_core_id = SRP_RCS_RCP_CTRL_RX;
        rcs_params.rcs_cfg[rcs_core_id].img_file = "./rcs_fw/rx_rcs_fw.elf";
    } else if(rcs_core == RCS_CORE_TX)
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

    // waiting for the RCS CORE to update an RSM_HANDSHAKE_ADDR as a means for handshaking
    int cnt = 0;
    volatile uint32_t handshake;
    LOG_PRINT("HOST: Waiting for the RCS CORE-%d to update RSM_HANDSHAKE_ADDR (0x%x) to indicate that it has STARTED\n",
               rcs_core, RSM_HANDSHAKE_ADDR);
    do
    {
        handshake = read_reg_18a(RSM_HANDSHAKE_ADDR, "RSM_HANDSHAKE_ADDR");
    } while((handshake != RCS_CORE_STARTED) && (cnt++ < 65536));

    if(cnt > 65536)
    {
        LOG_PRINT("ERROR: Waited for %d cycles, but RCS CORE-%d is not updating RSM_HANDSHAKE_ADDR (0x%x)\n",
                  (cnt - 1), rcs_core, RSM_HANDSHAKE_ADDR);
        LOG_PRINT("INFO: [%x] = %x\n", RSM_HANDSHAKE_ADDR, handshake);
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }

    LOG_PRINT("INFO: [%x] = %x -> %s\n", RSM_HANDSHAKE_ADDR, handshake, "RCS_CORE_STARTED");


    uint64_t skip_targets;
    uint64_t skip_targets1, skip_targets2;

    skip_targets1 = (1 << HUB)              |              // Not available on FRIO, so disabling it.
                    (0 << JESD_0)           |
                    (0 << JESD_1)           |
                    (1 << JESD_2)           |              // Not available on FRIO, so disabling it.
                    (1 << JESD_3)           |              // Not available on FRIO, so disabling it.
                    (1 << PCIE)             |              // Not available on FRIO, so disabling it.
                    (1 << PCIE_CFG)         |              // Not available on FRIO, so disabling it.
                    (1 << PCIE_DBI)         |              // Not available on FRIO, so disabling it.
                    (0 << DRF_0_ANT_0)      |
                    (0 << DRF_0_ANT_1)      |
                    (0 << DRF_0_FB_ANT)     |
                    (0 << DRF_0_FB_SYS)     |
                    (0 << DRF_0_MEM)        |
                    (0 << DRF_0_MEM_FB)     |
                    (0 << DRF_0_TRXANT_0)   |
                    (0 << DRF_0_TRXANT_1)   |
                    (0 << DRF_0_TRXANT_2)   |
                    (0 << DRF_0_TRXANT_3)   |
                    (0 << DRF_0_TRXSYS_0)   |
                    (0 << DRF_0_TRXSYS_1)   |
                    (0 << DRF_0_TRXSYS_2)   |
                    (0 << DRF_0_TRXSYS_3)   |
                    (1 << DRF_1_ANT_0)      |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_ANT_1)      |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_FB_ANT)     |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_FB_SYS)     |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_MEM)        |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_MEM_FB)     |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_TRXANT_0)   |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_TRXANT_1)   |              // Not available on FRIO, so disabling it.
                    (1 << DRF_1_TRXANT_2)   |              // Not available on FRIO, so disabling it.
                    (1ULL << DRF_1_TRXANT_3);              // Not available on FRIO, so disabling it.

    skip_targets2 = (1 << (DRF_1_TRXSYS_0 - 32)) |         // Not available on FRIO, so disabling it.
                    (1 << (DRF_1_TRXSYS_1 - 32)) |         // Not available on FRIO, so disabling it.
                    (1 << (DRF_1_TRXSYS_2 - 32)) |         // Not available on FRIO, so disabling it.
                    (1 << (DRF_1_TRXSYS_3 - 32)) |         // Not available on FRIO, so disabling it.
                    (1 << (VEX_SFC_RBM - 32))    |         // Corrupting this would disable further access of RCS core into RBM registers,
                                                           //  so skip it
                    (1 << (RCS_0 - 32))          |         // RCS target regsiter cannot be modified, so disabling it.
                    (1 << (RCS_1 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (RCS_CS - 32))         |         // RCS CS registers Not available on FRIO, so disabling it.
                    (0 << (SYSCON_MAIN - 32))    |
                    (0 << (V2D_0 - 32))          |
                    (0 << (V2D_1 - 32))          |
                    (0 << (V2D_2 - 32))          |
                    (0 << (V2D_3 - 32))          |
                    (1 << (V2D_4 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_5 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_6 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_7 - 32))          |         // Not available on FRIO, so disabling it.
                    (0 << (VEX_0 - 32))          |
                    (1 << (VEX_1 - 32))          |         // VEX_16 Not available on FRIO, so disabling it.
                    (0 << (VEX_2 - 32))          |
                    (0 << (VEX_CAR - 32))        |
                    (1 << (VEX_DBG_0 - 32))      |         // CS registers Not available on FRIO, so disabling it.
                    (1 << (VEX_DBG_1 - 32))      |         // CS registers Not available on FRIO, so disabling it.
                    (1 << (VEX_DBG_2 - 32))      |         // CS registers Not available on FRIO, so disabling it.
                    (0 << (VHA_0 - 32))          |
                    (0 << (VHA_1 - 32))          |
                    (0 << (VHA_2 - 32))          |
                    (0 << (VHA_3 - 32))          |
                    (1 << (VHA_4 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_5 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_6 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_7 - 32));                   // Not available on FRIO, so disabling it.

    write_reg_18a(RSM_SKIP_TARGETS1_ADDR, skip_targets1, 0xffffffff, "RSM_SKIP_TARGETS1_ADDR");
    write_reg_18a(RSM_SKIP_TARGETS2_ADDR, skip_targets2, 0xffffffff, "RSM_SKIP_TARGETS2_ADDR");
    skip_targets = (skip_targets2 << 32) | skip_targets1;
    LOG_PRINT("INFO: Skip_targets = %x_%x\n", (skip_targets >> 32), skip_targets);

    target_list_type_t* target;
    uint32_t num_targets = 0;
    int i;
    uint32_t act_val, exp_val, result;
    uint32_t reg_num, wr_pattern;
    uint32_t wr_addr, rd_addr, rd_mask, wr_mask;
    target_type_t target_num;
    exp_val = pattern;
    uint32_t rsm_buf_addr;

    for(i = 0; i < 64; i++)
    {
        if(!(skip_targets & (1ULL << i))) num_targets++;
    }
    LOG_PRINT("INFO: Number of targets selected = %d\n", num_targets);
    if(num_targets == 0)
    {
        LOG_PRINT("ERROR: No targets selected. Exiting the test..!\n");
        return FAILURE;
    }

    char* msg = "INFO";

    // Writing a pattern to the target's address space from host
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
        {
            if(!(skip_targets & (1ULL << target_num)))
            {
                target = &(g_noc_targets[target_num]);
                LOG_PRINT("\nINFO: TARGET: %s\n", target->name);

                                                           // we where taking end address  of each target  adrress
                for(reg_num = 1; reg_num < ARRAY_SIZE(target->regs); reg_num++)
                {
                    wr_addr = (target->regs[reg_num].base_addr + target->regs[reg_num].offset);
                    wr_mask = target->regs[reg_num].wr_mask;
                    rd_mask = target->regs[reg_num].rd_mask;
                    if((target_num == DRF_0_MEM_FB) || (target_num == DRF_1_MEM_FB))
                    {
                    // DRF_MEM_FB writes require atleast 16 words(512 bits) to go through.
                    // so do 15 additional writes here
                        for(i = 1; i <= 15; i++)
                        {
                            write_reg_18a((rd_addr + (i * 4)), pattern, wr_mask, target->name);
                        }
                    }
                    write_reg_18a(wr_addr, pattern, wr_mask, target->name);
                    act_val = read_reg_18a(wr_addr, target->name);
                    LOG_PRINT("%s: addr = %x, act_val = %x, exp_val = %x, wr_mask = %x\n", msg,
                              wr_addr, act_val, exp_val, wr_mask);
                }
            }
        }

    // Host sends a signal to the RCS
    write_reg_18a(RSM_HANDSHAKE_ADDR, HANDSHAKE_MOVEON, 0xffffffff, "RSM_HANDSHAKE_ADDR");

    // Host waits for RCS to send a signal that it has corrupted the base address of RBM regsiters.
    LOG_PRINT("INFO: Waiting for the RCS CORE to finish execution\n\n");
    if(poll_rsm_flag(srp, RSM_HANDSHAKE_ADDR, RCS_CORE_FINISHED) < 0)
    {
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }
    LOG_PRINT("INFO: Received execution FINISHED handshake from the RCS CORE\n");

    // Negative test, the access should fail and result in 0xffffffff
    uint32_t err_cnt = 0;
    exp_val = 0xdeadbeef;                                  // the default pattern in the rsm_buf
    rsm_buf_addr = RSM_BUF_ADDR;
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(!(skip_targets & (1ULL << target_num)))
        {
            target = &(g_noc_targets[target_num]);
            LOG_PRINT("\nINFO: TARGET: %s\n", target->name);
                                                           // we where taking end address  of each target
            for(reg_num = 1; reg_num < ARRAY_SIZE(target->regs); reg_num++)
            {
                rd_addr = rsm_buf_addr;
                wr_mask = target->regs[reg_num].wr_mask;
                act_val = read_reg_18a(rd_addr, "RSM_BUF_ADDR");
                result = read_reg_expect_18a(rd_addr, exp_val, wr_mask, "RSM_BUF_ADDR");
                msg = "INFO";
                if(result)
                {
                    msg = "ERROR";
                    err_cnt++;
                }
                LOG_PRINT("%s: addr = %x, act_val = %x, exp_val = %x, wr_mask = %x\n", msg,
                          (target->regs[reg_num].base_addr + target->regs[reg_num].offset), act_val, exp_val, wr_mask);

                rsm_buf_addr += 4;
            }

        }
    }

    LOG_PRINT("\nINFO: Error count = %d\n", err_cnt);

    char* output = "PASS";
    if(err_cnt > 0) output = "FAIL";
    LOG_PRINT("\n      Test Result = %s\n", output);

srp_return:

    LOG_PRINT("\nEnd of the test execution..!\n");

    return SUCCESS;

}


