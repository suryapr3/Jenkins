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
 * @brief   This is a negative test that validates access to target registers by changing the
 *          base address register's security bit for each target.
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
#define RCS_NEXT                      ( 0x11111111 )
#define RCS_SKIP_ADDR                 ( 0x00001357 )

extern target_list_type_t g_noc_targets[64];
extern noc_type_t g_noc_bridges;

volatile uint32_t g_rsm_buf[RSM_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t g_rsm_handshake __attribute__((section(".sram.ax.flag")));
volatile uint32_t g_skip_targets1 __attribute__((section(".sram.tx.flag")));
volatile uint32_t g_skip_targets2 __attribute__((section(".sram.rx.flag")));
volatile uint32_t g_rsm_pattern __attribute__((section(".sram.cal.flag")));

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

    g_rsm_handshake = RCS_STARTED;
    do
    {
        wait_cnt++;
    } while(g_rsm_handshake != RCS_SKIP_ADDR);             // Waiting for host to write skip_addr to RCS memory location

    skip_targets1 = g_skip_targets1;                       // Shared by the HOST driver
    skip_targets2 = g_skip_targets2;                       // Shared by the HOST driver

    target_type_t target_num;
    target_list_type_t* target;
    m_cs_dbg_type_t* m_cs_dbg = &(g_noc_bridges.m_cs_dbg);
    volatile uint32_t* base_addr_ptr;
    uint64_t skip_targets;
    uint32_t wr_pattern;
    uint32_t offset_adj = 0;
    skip_targets = skip_targets1;
    wr_pattern = g_rsm_pattern;                            // HOST updates this location as the argument from python

    uint64_t m_cs_dbg_connected_targets = ((1ULL << VEX_DBG_0) | (1ULL << VEX_DBG_1) | (1ULL << VEX_DBG_2) | (1ULL << RCS_CS));

    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(!(m_cs_dbg_connected_targets & (1ULL << target_num)))
        {
            offset_adj++;
            continue;
        }
        if(target_num > 31) skip_targets = skip_targets2;

        if(!(skip_targets & (1 << target_num)))
        {
            base_addr_ptr = (volatile uint32_t*)(m_cs_dbg->base_addr + m_cs_dbg->regs[(target_num - offset_adj) * 3].offset);
            // By default secure for all targets,
            //  Since m_cs_dbg is non-secure changing all targets to non-secure to allow access.
            *base_addr_ptr = ((*base_addr_ptr) | (1 << 1));
        }
    }

    g_rsm_handshake = RCS_NEXT;
    while(g_rsm_handshake != HANDSHAKE_MOVEON) ;           // Waiting for host to write the pattern to the target space

    skip_targets = skip_targets1;
    offset_adj = 0;
    for(target_num = HUB; target_num < ARRAY_SIZE(g_noc_targets); target_num++)
    {
        if(!(m_cs_dbg_connected_targets & (1ULL << target_num)))
        {
            offset_adj++;
            continue;
        }
        if(target_num > 31) skip_targets = skip_targets2;

        if(!(skip_targets & (1 << target_num)))
        {
            base_addr_ptr = (volatile uint32_t*)(m_cs_dbg->base_addr + m_cs_dbg->regs[((target_num - offset_adj) * 3)].offset);
            *base_addr_ptr = ((*base_addr_ptr) & ~(1 << 1));
            // corrupt the security bit so that access will be denied
        }

    }
    g_rsm_handshake = RCS_FINISHED;

    return 0;
}


