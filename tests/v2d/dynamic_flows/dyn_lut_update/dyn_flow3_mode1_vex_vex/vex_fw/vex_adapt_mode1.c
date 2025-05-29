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
 * @file    vex_gbuffer_mode1_tx.c
 * @brief   Vex FW code to update the PDPD LUT at regular intervals.
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>
#include "defines.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(TX_G_BUFFER_BASE) v_gbuffer[VMEM_IN_VEC];
volatile int AT(0x4) g_host_cycle_count;
volatile int AT(0x8) g_vectors_g_buf;
volatile int AT(0xc) g_dpd_coeff_base;
volatile int AT(0x10) g_vex_indicator;
volatile int AT(0x14) g_host_indicator;
volatile int AT(0x18) g_lut_update_block_duration;
volatile int AT(0x1c) g_cnt;
volatile int AT(0x20) g_max_lut_update;
volatile int AT(0x24) g_ld_offset;
volatile int AT(TIMER_DEBUG_LOCATION) g_timer_debug;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function Initialzing the timer with required number
 *                  of clock cycles in continuous watchdog mode
 * @param [in]      num of cycles
 * @return          none
 */
inline void init_timer(int cycles)
{
    // set reg_timer_tmdcfgr0, continuous watchdog
    s_xsto_32(Any, 0, TIMER_TMDCFGR0, TMD_CONTINUOUS_WATCHDOG);
    // set reg_timer_tmdinitr0, set the timeout val
    s_xsto_32(Any, 0, TIMER_TMDINITR0, cycles);
    // set reg_timer_tmdwdnotr0, enable notif
    s_xsto_32(Any, 0, TIMER_TMDWDNOTR0, 0x1);
    // set reg_timer_tmdwdaddrr0, 0x4000 is mapped to DRAM start
    s_xsto_32(Any, 0, TIMER_TMDWDADDRR0, 0x4000 + TIMER_DEBUG_LOCATION);
    // set reg_timer_tmdwddatar0, data will be written to above address
    s_xsto_32(Any, 0, TIMER_TMDWDDATAR0, 0xdeadbeef);
}

/**
 * @brief           Function sending pre defined blocks of data to HOST
 * @param [in]      none
 * @return          none
 */
void v2d_adapt_mode1() ENTRY
{
    int i = 0, ld_offset = 0, offset = 0;
    int limit = 0, rewind = 0;

    g_vex_indicator = 0x0;
    g_ld_offset = 0;

    limit =  ((BYTES_PER_VEC) << 20) | ((VMEM_IN_VEC * BYTES_PER_VEC) - (BYTES_PER_VEC));
    rewind = (VMEM_IN_VEC * BYTES_PER_VEC) - (BYTES_PER_VEC);

    //while (g_max_lut_update > g_cnt)
    while (g_host_indicator != 3)
    {
        offset = 0;

        while (g_vex_indicator == g_cnt * g_lut_update_block_duration)
        {

            ld_offset = g_ld_offset;
            /* 241 Flits should be updated in 2164 clock cycles*
             * 60 batches x 32(gap) cycles + 60 batches of 4 flit writes + 1 flit write*/
#ifdef VOLCANO
#pragma hive pipeline ii=36
//#pragma hive force_unroll=4
#endif
            for (i = 0; (i < g_vectors_g_buf / 2); i++)
            {
                vec32i32 v_dpd_coeff0 UNINIT, v_dpd_coeff1 UNINIT;

                v_ldoi_1024_circ(Any, v_gbuffer, ld_offset, limit, rewind, v_dpd_coeff0, ld_offset) SYNC(buffer_read);
                v_ldoi_1024_circ(Any, v_gbuffer, ld_offset, limit, rewind, v_dpd_coeff1, ld_offset) SYNC_WITH(buffer_read);
#if DEBUG
                OP___dump(__LINE__, v_dpd_coeff);
                OP___printstring("\n");
                OP___dump(__LINE__, i);
#endif
                v_xstomi_1024x2(Any, g_dpd_coeff_base, offset, 511, v_dpd_coeff0, v_dpd_coeff1, offset) NO_ALIAS SYNC_WITH(buffer_read);
            }

            /* for writing the 241st entry of G buffer*/
            vec32i32 v_passthru UNINIT;
            /*Reading the 1024 bits so that the next read will be a 1024 bit aligned boundary*/
            v_ldoi_1024(Any, v_gbuffer, ld_offset, v_passthru, ld_offset) NO_ALIAS SYNC_WITH(buffer_read);
            offset = offset * 2;    // is required because s_offset is in 1024 bits but in the next instruction we are using 512 bit transfer
            v_xsto_512(Any, g_dpd_coeff_base, offset, v_passthru) NO_ALIAS SYNC_WITH(buffer_read);

            g_cnt = g_cnt + 1;
            g_host_indicator = 1;
            g_ld_offset = ld_offset;
        }
    }
    g_host_indicator = 0xDEAD;

}

