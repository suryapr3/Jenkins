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
 * @file    vex_flow1_tx_p25_4iq.c
 * @brief   Vex FW code to validate V2D Path A.
 * @details 1. VEX will send INITIAL_BLOCK_SIZE of data to CM and waiting on the host indication
 *             to send the remainng blocks.
 *          2. After the host indication was received for every 512 cycles g_num_vecs_in number of
 *             vectors will be sent to CM (V2D) till the required number of blocks were
 *             transmitted...
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
vec32i32 AT(INPUT_VMEM_LOCATION) vbuffer[VEX_IN_BUF_SIZE];
vec32i32 AT(OUTPUT_VMEM_LOCATION) vbuffer_out[VEX_DEST_BUF_SIZE];
volatile unsigned int AT(0x4) g_dest_buffer_base;
volatile int g_scalar_val;
volatile int g_num_vecs_in;
volatile int AT (0x8) g_num_blocks;
volatile int AT(0xC) g_host_debug;
volatile int AT(0x10) g_host_indicator;
volatile int AT(0x18) g_host_cycle_count;
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
void v2d_flow1_tx_p25_4iq() ENTRY
{
    int i, j = 0, offset =0;
    g_host_debug = 0;
    int dest_address = g_dest_buffer_base;
    int iter_max = g_num_vecs_in;
    g_host_indicator = 0;
#if DEBUG
    OP___dump(__LINE__, g_scalar_val);
    OP___dump(__LINE__, g_num_vecs_in);
    OP___dump(__LINE__, g_num_blocks);
#endif
    init_timer(g_host_cycle_count);
    //init_timer(512);
    s_xsto_32(Any, 0, TIMER_TMDCMDR0, TMD_COMMAND_START);           // start the timer

    /* This loop will generate the iter_max vectors in 512 cycles
     * Same loop is used for testing all rates by varying the iter_max value*/
    for (j = 0; j < g_num_blocks; j++)
    {
        vec32i32 vin2;
        //g_scalar_val = g_scalar_val + j;
        //(V_CLONE_32(g_scalar_val+j, vin2)) AFTER(L0,85);
        V_CLONE_32(g_scalar_val+j, vin2);

        /* for 0.25IQ to 4IQ ii = 4 is needed due to prologue+epilogue is going beyond the
         * required number of iterations. For 8IQ and 16R ii=2 would work and it
         * will give a loop of 2 cycles with the prologue 6 and epilogue 1 cycles*/
#ifdef VOLCANO
#pragma hive pipeline ii=4
//#pragma hive force_unroll=4
#endif
        for(i = 0; i < iter_max; i++)
        {
            vec32i32 vin1, vout;
            vin1= vbuffer[i];
#if DEBUG
            OP___dump(__LINE__, i);
            OP___dump(__LINE__, vin1);
#endif
            V_ADD_32(vin1, vin2, vout);

            //v_sto_1024(Any,vbuffer_base,i*128,vout);
            //v_xsto_1024(Any,vbuffer_base,i,vout);
            v_xstomi_1024(Any, dest_address, offset, LD_OFFSET_MAX, vout, offset);
        }   // for(i = 0; i < g_num_vecs_in; i++) ends
        // This flag will be set by Timer once the configured clockds were elapsed
        while (g_timer_debug != 0xdeadbeef)
        {
        }
        g_timer_debug = 0xdead;

    }   // for (j=0; j < g_num_blocks; j++) ends

    s_xsto_32(Any, 0, TIMER_TMDCMDR0, TMD_COMMAND_STOP);           // stop the timer
#if DEBUG
    OP___printstring("vex_flow1: 3 bloks sent:");
    OP___dump(__LINE__,0xFFFF);
#endif
} // v2d_flow1() ends



