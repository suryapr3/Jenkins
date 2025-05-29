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
 * @brief   This test is to validate write/read access to target registers.
 * @details There are 64 targets out of which 29 targets are available.
 */

/***********************************************
 * HEADERS     *
 ***********************************************/
#include "access_check_common_rcs_definitions.h"
#include "access_check_common_noc_rcs_definitions.h"

/***********************************************
 * DEFINES (consts, vars)      *
 ***********************************************/
#define RSM_SIZE                   ( 1000 )
#define RCS_STARTED                ( 0xc001babe )
#define RCS_FINISHED               ( 0xdeaddead )
#define HANDSHAKE_MOVEON           ( 0x12345678 )

extern target_list_type_t g_noc_targets[64];

volatile uint32_t g_rsm_buf[RSM_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t g_rsm_handshake __attribute__((section(".sram.ax.flag")));
volatile uint32_t g_skip_targets1 __attribute__((section(".sram.tx.flag")));
volatile uint32_t g_skip_targets2 __attribute__((section(".sram.rx.flag")));
volatile uint32_t g_rsm_pattern __attribute__((section(".sram.cal.flag")));
volatile uint32_t g_rsm_buf_temp[16] __attribute__((section(".sram.reserved")));

int main()
{
    xthal_enable_interrupts();

    uint32_t wait_cnt = 0;
    if (!com_shared_mem_wait_for_ready ())
    {
        wait_cnt++;
    }

    for (int i = 0; i < RSM_SIZE; i++)
        g_rsm_buf[i] = 0xdeadbeef;                         // Pre-fill rsm_buf with a known pattern

    uint32_t skip_targets1, skip_targets2;

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
                    (1 << (RCS_0 - 32))          |         // Not accessible for M_RCS_0
                    (1 << (RCS_1 - 32))          |         // Not accessible for M_RCS_0
                    (1 << (RCS_CS - 32))         |         // RCS registers Not available on FRIO, so disabling it.
                    (0 << (SYSCON_MAIN - 32))    |
                    (0 << (VEX_SFC_RBM - 32))    |
                    (0 << (V2D_0 - 32))          |
                    (0 << (V2D_1 - 32))          |
                    (0 << (V2D_2 - 32))          |
                    (0 << (V2D_3 - 32))          |
                    (1 << (V2D_4 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_5 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_6 - 32))          |         // Not available on FRIO, so disabling it.
                    (1 << (V2D_7 - 32))          |         // Not available on FRIO, so disabling it.
                    (0 << (VEX_0 - 32))          |
                    (1 << (VEX_1 - 32))          |         // VEX_16 Not vavailable on FRIO, so disabling it.
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

    g_skip_targets1 = skip_targets1;                       // Will be shared with the HOST driver
    g_skip_targets2 = skip_targets2;                       // Will be shared with the HOST driver

    g_rsm_handshake = RCS_STARTED;
    while(g_rsm_handshake != HANDSHAKE_MOVEON);            // Waiting for the handshake from HOST

    uint32_t rsm_buf_index;
    target_list_type_t* target;
    uint32_t reg_num, wr_pattern;
    volatile uint32_t* wr_rd_addr_ptr;
    uint32_t skip_targets;
    skip_targets = skip_targets1;
    rsm_buf_index = 0;
    wr_pattern = g_rsm_pattern;                            // HOST updates this location as the argument from python script
    int i;
    target_type_t target_num;
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(target_num > 31)
            skip_targets = skip_targets2;

        if(!(skip_targets & (1 << target_num)))
        {
            target = &(g_noc_targets[target_num]);

            for(reg_num = 0; reg_num < ARRAY_SIZE(target->regs); reg_num++)
            {
                wr_rd_addr_ptr = (volatile uint32_t*)(target->regs[reg_num].base_addr + target->regs[reg_num].offset);
                // Writing by GPDMA to register
                   gpdma_test_LLI(0, wr_rd_addr_ptr, (uint32_t)(&g_rsm_pattern));

                if((target_num == DRF_0_MEM_FB) || (target_num == DRF_1_MEM_FB))
                {
                    // DRF_MEM_FB writes require atleast 16 words(512 bits) to go through.
                    // so do 15 additional writes here
                    for(i = 1; i <= 15; i++)
                    {
                        g_rsm_buf_temp[i] = wr_pattern;    // Filling the buffer with pattern
                    }
                    // Writing by GPDMA to memory address
                    gpdma_test_LLI(15, wr_rd_addr_ptr, (uint32_t)(g_rsm_buf_temp));
                }
                // Reading by GPDMA
                gpdma_test_LLI(0, (uint32_t)(g_rsm_buf + rsm_buf_index), wr_rd_addr_ptr);
                rsm_buf_index++;
				
            }
            }
        }

    g_rsm_handshake = RCS_FINISHED;

    return 0;
}


