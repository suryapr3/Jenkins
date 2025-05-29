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
extern target_list_type_t g_noc_targets[64];


int main(int argc, const char* argv[])
{
    srp_st_t srp_st = SRP_ST_SUCCESS;
    uint32_t pattern;

    init();
    enable_drf0_memories();

    LOG_PRINT("\nINFO: Logger beginning\n");
    LOG_PRINT("Test: TARGET write-read access test\n");
    LOG_PRINT("      %s\n", g_compile_time);
    LOG_PRINT("      BUILD_DIR: %s\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        LOG_PRINT("Exiting test..!\n");
        return FAILURE;
    }

    pattern = (uint32_t)argv[0];
    LOG_PRINT("INFO: argv[0] = PATTERN = 0x%x\n", pattern);

    target_list_type_t* target;
    uint64_t skip_targets;
    uint32_t num_targets = 0;
    int i;

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
                    (0 << (VEX_SFC_RBM - 32))    |
                    (0 << (RCS_0 - 32))          |
                    (1 << (RCS_1 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (RCS_CS - 32))         |         // RCS registers Not available on FRIO, so disabling it.
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

    skip_targets = (skip_targets2 << 32) | skip_targets1;
    LOG_PRINT("INFO: Skip_targets = %x_%x\n", (skip_targets >> 32), skip_targets);

    for(i = 0; i < 64; i++)
    {
        if(!(skip_targets & (1ULL << i))) num_targets++;
    }
    LOG_PRINT("INFO: Number of targets selected = %d\n", num_targets);
    if(skip_targets == 0)
    {
        LOG_PRINT("ERROR: No targets selected. Exiting the test..!\n");
        return FAILURE;
    }

    uint32_t err_cnt=0;
    uint32_t rd_addr, wr_mask, act_val, exp_val, result, reg_num, rd_mask;
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
                rd_mask = target->regs[reg_num].rd_mask;
                if((target_num == DRF_0_MEM_FB) || (target_num == DRF_1_MEM_FB))
                {
                    // DRF_MEM_FB writes require atleast 16 words(512 bits) to go through.
                    // so do 15 additional writes here
                    for(j = 1; j <= 15; j++)
                    {
                      write_reg_18a(rd_addr + j*4, pattern, wr_mask, target->name);
                    }
                }
                write_reg_18a(rd_addr, pattern, wr_mask, target->name);
                result = read_reg_expect_18a(rd_addr, pattern, wr_mask, target->name);
                act_val = read_reg_18a(rd_addr, target->name);
                msg = "INFO";
                if(result)
                {
                    msg = "ERROR";
                    err_cnt++;
                }
                LOG_PRINT("%s: addr = %x, act_val = %x, exp_val = %x, wr_mask = %x\n", msg,
                          rd_addr, act_val, exp_val, wr_mask);

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

