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
 * @file    vex2vha.c
 * @brief   Vex FW code to stream vectors from VEX vector memory to VHA downlink fifo
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
vec32i32 AT(0) vbuffer[128];
vec32i32 AT(0x4000) vbuffer_out[384];
volatile int g_scalar_val;
volatile int g_num_vecs_in;
volatile int AT(0x00) g_timer_debug;
volatile unsigned int AT(0x4) g_dest_buffer_base;
volatile int AT(0x08) g_num_blocks;
volatile int AT(0x0C) g_host_debug;
volatile int AT(0x10) g_host_indicator;
volatile int AT(0x14) g_vex_clk;
volatile int AT(0x20) g_stop_me;
volatile int AT(0x24) g_version;

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

inline void init_vex_timer(int cycles)
{
    // set reg_timer_tmdcfgr0, continuous watchdog
    s_xsto_32(Any, 0, 3, 0x3);

    // set reg_timer_tmdinitr0, set the timeout val
    s_xsto_32(Any, 0, 4, cycles);

    // set reg_timer_tmdwdnotr0, enable notification
    s_xsto_32(Any, 0, 6, 0x1);

    // set reg_timer_tmdwdaddrr0, 0x4000 is mapped to DRAM start
    s_xsto_32(Any, 0, 7, 0x4000);

    // set reg_timer_tmdwddatar0, data will be written to the above address
    s_xsto_32(Any, 0, 8, 0xdeadbeef);

}


/**
 * @brief           Function sending pre defined blocks of data to HOST (VHA)
 * @param [in]      none
 * @return          none
 */
void vex2vha () ENTRY
{
    int i, j, offset =0;
    int dest_address = g_dest_buffer_base;
    int iter_max = g_num_vecs_in;
    unsigned int timer_count;
    g_host_indicator = 0;
    g_stop_me = 1;
    g_version = 0x25062024;

#if DEBUG
    OP___dump(__LINE__, g_scalar_val);
    OP___dump(__LINE__, g_num_vecs_in);
    OP___dump(__LINE__, g_num_blocks);
#endif

    timer_count = (512 - 1);                     // if the VEX is working at 1GHz
    if(g_vex_clk)
        timer_count = (768 - 1);                 // for VEX working at 1.5GHz
    g_host_debug = timer_count;
    init_vex_timer(timer_count);
    s_xsto_32(Any, 0, 9, 0x1);                   // start the timer
#if 1
    while(g_stop_me) {
#endif
    for (j = 0; j < g_num_blocks; j++)
    {
        vec32i32 vin2;
        V_CLONE_32(g_scalar_val, vin2);
#ifdef VOLCANO
#pragma hive pipeline ii=4
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

            v_xstomi_1024(Any, dest_address, offset, 1023, vout, offset);
        }
        while (g_timer_debug != 0xdeadbeef)
        {
            // do nothing and wait for the timer event to occur
        }
        g_timer_debug = 0xdead;
    }
#if 1
       }                                         // end of stop_me loop
#endif

    s_xsto_32(Any, 0, 9, 0x2);                   // stop the timer
}
