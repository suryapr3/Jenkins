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
#include "coresight_common.h"


// Macros
#define RCS_CORE_STARTED          ( 0xc001babe )
#define RCS_CORE_FINISHED         ( 0xdeaddead )
#define RCS_CORE_NEXT             ( 0x11111111 )
#define RCS_CORE_SKIP_ADDR        ( 0x00001357 )
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
    // To enable coresight in 0p8b R0.1
    system("frioPciWrite -F s6b3 -P 0x20000 0x20200009");
    enable_drf0_memories();
    LOG_PRINT("\nINFO: Logger beginning\n");
    LOG_PRINT("Test:Negative test: Access_check_changing_default_base_addr_register\n");
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

    // waiting for the RCS CORE to update an RSM_HANDSHAKE_ADDR as a means for handshaking
    int cnt = 0;
    volatile uint32_t handshake;
    LOG_PRINT("HOST: Waiting for the RCS CORE-%d to update RSM_HANDSHAKE_ADDR (0x%x) to indicate that it has STARTED\n",
               rcs_core, RSM_HANDSHAKE_ADDR);
    do
    {
        handshake = read_reg_18a(RSM_HANDSHAKE_ADDR, "RSM_HANDSHAKE_ADDR");
    } while ((handshake != RCS_CORE_STARTED) && (cnt++ < 65536));
    if(cnt > 65536)
    {
        LOG_PRINT("ERROR: Waited for %d cycles, but RCS CORE-%d is not updating RSM_HANDSHAKE_ADDR (0x%x)\n",
                  (cnt - 1), rcs_core, RSM_HANDSHAKE_ADDR);
        LOG_PRINT("INFO: [%x] = %x\n", RSM_HANDSHAKE_ADDR, handshake);
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }

    // write the pattern to the memory so that the RCS will write that to the targets while running
    int rv;
    LOG_PRINT("INFO: Writing pattern-0x%x to the RSM memory (0x%x)\n", pattern, RSM_PATTERN_ADDR);
    if(rv = write_reg_18a(RSM_PATTERN_ADDR, pattern, 0xffffffff, "PATTERN"))
    {
        LOG_PRINT("ERROR: Writing pattern-0x%x to the RSM memory (0x%x) failed with return status-0x%x\n", pattern, RSM_PATTERN_ADDR, rv);
        return FAILURE;
    }

    uint64_t skip_targets;
    uint64_t skip_targets1, skip_targets2;

    skip_targets1 = (1 << HUB)              |              // Not available on FRIO, so disabling it.
                    (1 << JESD_0)           |              // Disabling as per the design excel sheet.
                    (1 << JESD_1)           |              // Disabling as per the design excel sheet.
                    (1 << JESD_2)           |              // Not available on FRIO, so disabling it.
                    (1 << JESD_3)           |              // Not available on FRIO, so disabling it.
                    (1 << PCIE)             |              // Not available on FRIO, so disabling it.
                    (1 << PCIE_CFG)         |              // Not available on FRIO, so disabling it.
                    (1 << PCIE_DBI)         |              // Not available on FRIO, so disabling it.
                    (1 << DRF_0_ANT_0)      |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_ANT_1)      |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_FB_ANT)     |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_FB_SYS)     |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_MEM)        |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_MEM_FB)     |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXANT_0)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXANT_1)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXANT_2)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXANT_3)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXSYS_0)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXSYS_1)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXSYS_2)   |              // Disabling as per the design excel sheet.
                    (1 << DRF_0_TRXSYS_3)   |              // Disabling as per the design excel sheet.
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
                    (1 << (DRF_1_TRXSYS_3 - 32)) |         // Disabling as per the design excel sheet
                    (1 << (VEX_SFC_RBM - 32))    |         // Disabling as per the design excel sheet
                    (1 << (RCS_0 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (RCS_1 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (RCS_CS - 32))         |         // Header file not available, HSD#16025070209
                    (1 << (SYSCON_MAIN - 32))    |         // Disabling as per the design excel sheet
                    (1 << (V2D_0 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (V2D_1 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (V2D_2 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (V2D_3 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (V2D_4 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_5 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_6 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_7 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VEX_0 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VEX_1 - 32))          |         // Disabling as per the design excel sheet.
                    (1 << (VEX_2 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VEX_CAR - 32))        |         // Disabling as per the design excel sheet
                    (0 << (VEX_DBG_0 - 32))      |
                    (1 << (VEX_DBG_1 - 32))      |         // Not available on FRIO, so disabling it.
                    (0 << (VEX_DBG_2 - 32))      |
                    (1 << (VHA_0 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VHA_1 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VHA_2 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VHA_3 - 32))          |         // Disabling as per the design excel sheet
                    (1 << (VHA_4 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_5 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_6 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (VHA_7 - 32));                   // Not available on FRIO, so disabling it.

    skip_targets = (skip_targets2 << 32) | skip_targets1;
    LOG_PRINT("INFO: Skip_targets = %x_%x\n", (skip_targets >> 32), skip_targets);
    LOG_PRINT("INFO: Writing skip_targets1-0x%x to the RSM memory (0x%x)\n",skip_targets1, RSM_SKIP_TARGETS1_ADDR, rv);
    if(rv = write_reg_18a(RSM_SKIP_TARGETS1_ADDR, skip_targets1, 0xffffffff, "RSM_SKIP_TARGET1_ADDR"))
    {
        LOG_PRINT("ERROR: Writing skip_targets1-0x%x to the RSM memory (0x%x) failed with return status-0x%x\n", skip_targets1,
                  RSM_SKIP_TARGETS1_ADDR, rv);
        return FAILURE;
    }

    LOG_PRINT("INFO: Writing skip_targets2-0x%x to the RSM memory (0x%x)\n",skip_targets2, RSM_SKIP_TARGETS2_ADDR, rv);
    if(rv = write_reg_18a(RSM_SKIP_TARGETS2_ADDR, skip_targets2, 0xffffffff, "RSM_SKIP_TARGET2_ADDR"))
    {
        LOG_PRINT("ERROR: Writing skip_targets2-0x%x to the RSM memory (0x%x) failed with return status-0x%x\n", skip_targets2,
                  RSM_SKIP_TARGETS2_ADDR, rv);
        return FAILURE;
    }
    // RCS will wait for HOST to write the skip_addr to the RCS memory location
    if(rv = write_reg_18a(RSM_HANDSHAKE_ADDR, RCS_CORE_SKIP_ADDR, 0xffffffff, "SKIP_TARGETS"))
    {
        LOG_PRINT("ERROR: Writing skip_addr-0x%x to the RSM memory (0x%x) failed with return status-0x%x\n", RCS_CORE_SKIP_ADDR,
                  RSM_PATTERN_ADDR, rv);
        return FAILURE;
    }

    uint32_t num_targets = 0;
    target_list_type_t* target;
    int i;

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

    LOG_PRINT("INFO: Waiting for the RCS CORE to finish changing the security bit\n");
    if(poll_rsm_flag(srp, RSM_HANDSHAKE_ADDR, RCS_CORE_NEXT) < 0)
    {
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }
    LOG_PRINT("INFO: Received execution NEXT handshake from the RCS CORE\n");

    uint32_t err_cnt = 0;
    uint32_t rd_addr, wr_mask, act_val, exp_val, result, reg_num;
    exp_val = pattern;
    char* msg = "INFO";
    LOG_PRINT("INFO: Now checking the results of access to the targets\n");

    int j;
    target_type_t target_num;

    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(!(skip_targets & (1ULL << target_num)))
        {
            target = &(g_noc_targets[target_num]);
            LOG_PRINT("\nINFO: TARGET: %s\n", target->name);

            for(reg_num = 0; reg_num < ARRAY_SIZE(target->regs); reg_num++)
            {
                rd_addr = target->regs[reg_num].base_addr + target->regs[reg_num].offset;
                wr_mask = target->regs[reg_num].wr_mask;
                write_m_cs_dbg_18a(rd_addr, pattern, NON_SECURE, target->name);
                act_val = read_m_cs_dbg_18a(rd_addr, NON_SECURE, target->name);

                result = 0;
                if((act_val & wr_mask) != (exp_val & wr_mask))
                    result = -1;
                msg = "INFO";
                if(result)
                {
                  msg = "ERROR";
                  err_cnt++;
                }
                LOG_PRINT("%s: addr = %x, act_val = %x, exp_val = %x, wr_mask = %x\n", msg,
                          (target->regs[reg_num].base_addr + target->regs[reg_num].offset), act_val, exp_val, wr_mask);
            }

        }
    }
    // Host sends a signal to the RCS that targets has been written with pattern
    write_reg_18a(RSM_HANDSHAKE_ADDR, HANDSHAKE_MOVEON, 0xffffffff, "RSM_HANDSHAKE_ADDR");

    // Host waits for RCS to send a signal that it has corrupted the security bit of RBM regsiters.
    LOG_PRINT("INFO: Waiting for the RCS CORE to finish execution\n");
    if(poll_rsm_flag(srp, RSM_HANDSHAKE_ADDR, RCS_CORE_FINISHED) < 0)
    {
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }
    LOG_PRINT("INFO: Received execution FINISHED handshake from the RCS CORE\n");

    // Host will access the target registers
    // Negative test, the access should fail and result in 0xffffffff
    exp_val = 0xffffffff;
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(!(skip_targets & (1ULL << target_num)))
        {
            target = &(g_noc_targets[target_num]);
            LOG_PRINT("\nINFO: TARGET: %s\n", target->name);

            for(reg_num = 0; reg_num < ARRAY_SIZE(target->regs); reg_num++)
            {
                rd_addr = (target->regs[reg_num].base_addr + target->regs[reg_num].offset);
                wr_mask = target->regs[reg_num].wr_mask;
                act_val = read_m_cs_dbg_18a(rd_addr, NON_SECURE, target->name);

                result = 0;
                if((act_val & wr_mask) != (exp_val & wr_mask))
                    result = -1;
                msg = "INFO";
                if(result)
                {
                  msg = "ERROR";
                  err_cnt++;
                }
                LOG_PRINT("%s: addr = %x, act_val = %x, exp_val = %x, wr_mask = %x\n", msg,
                          (target->regs[reg_num].base_addr + target->regs[reg_num].offset), act_val, exp_val, wr_mask);

            }
        }
    }

    LOG_PRINT("Error count = %d\n", err_cnt);
    char* output = "PASS";
    if(err_cnt > 0) output = "FAIL";
    LOG_PRINT("\n      Test Result = %s\n", output);

srp_return:

    LOG_PRINT("\nEnd of the test execution..!\n");
    return SUCCESS;
}




