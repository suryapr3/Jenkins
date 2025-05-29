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
 * @brief   This is a negative test to validate read access
 *          we change the addr mask register  of the m_drf_0 port
 *          that gives access to target address space. Then
 *          we read back each targets.
 */

/***********************************************
 * HEADERS     *
 ***********************************************/
#include "access_check_common_rcs_definitions.h"
#include "access_check_common_noc_rcs_definitions.h"
/***********************************************
 * DEFINES (consts, vars)      *
 ***********************************************/
#define RSM_SIZE                      ( 1000 )
#define RCS_STARTED                   ( 0xc001babe )
#define RCS_FINISHED                  ( 0xdeaddead )
#define HANDSHAKE_MOVEON              ( 0x12345678 )

extern target_list_type_t g_noc_targets[64];
extern noc_type_t g_noc_bridges;

volatile uint32_t g_rsm_buf[RSM_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t g_rsm_handshake __attribute__((section(".sram.ax.flag")));
volatile uint32_t g_skip_targets1 __attribute__((section(".sram.tx.flag")));
volatile uint32_t g_skip_targets2 __attribute__((section(".sram.rx.flag")));


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

    g_rsm_handshake = RCS_STARTED;                         // 0xc001babe
    while(g_rsm_handshake != HANDSHAKE_MOVEON);            // 0x12345678

    skip_targets1 = g_skip_targets1;                       // Shared by the HOST driver
    skip_targets2 = g_skip_targets2;                       // Shared by the HOST driver

    target_type_t target_num;
    target_list_type_t* target;
    m_drf0_mem_fb_type_t* m_drf0_mem_fb = &(g_noc_bridges.m_drf0_mem_fb);
    volatile uint32_t* addr_mask_ptr;
    uint32_t reg_num;
    uint32_t rsm_buf_index = 0;
    uint32_t offset_adj = 0;
    uint64_t skip_targets;
    skip_targets = skip_targets1;
    uint64_t m_drf0_mem_fb_unconnected_targets = (1ULL << DRF_0_MEM_FB) | (1ULL << VEX_SFC_RBM);
    uint32_t rd_addr;
    // Now modify the RBM addr mask register to deny access to targets
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(m_drf0_mem_fb_unconnected_targets & (1ULL << target_num))
        {
            offset_adj++;
            continue;
        }

        if(target_num > 31) skip_targets = skip_targets2;

        if(!(skip_targets & (1 << target_num)))
        {
            addr_mask_ptr = (volatile uint32_t*)(m_drf0_mem_fb->base_addr +
                            m_drf0_mem_fb->regs[((target_num - offset_adj) * 3) + 1].offset);
            *addr_mask_ptr = 0xfffff002;
            // corrupt the address mask register so that the address range of each target reduces.

            target = &(g_noc_targets[target_num]);

            for(reg_num = 1; reg_num < ARRAY_SIZE(target->regs); reg_num++)
            {
               rd_addr = (target->regs[reg_num].base_addr + target->regs[reg_num].offset);
               // Let DRF DMA try to access the address whose access is denied, and then copy to RSM memory.
               // This call is expected to fail and hence the content of the RSM should remain the same.
               drf_dma_negative_test_LLI(0, (uint32_t)(g_rsm_buf + rsm_buf_index), (uint32_t)rd_addr);
            }
            rsm_buf_index++;
        }
    }
    g_rsm_handshake = RCS_FINISHED;

    return 0;
}


