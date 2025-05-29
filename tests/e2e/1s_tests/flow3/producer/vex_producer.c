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
 * @file    vex_jesd_tx.c
 * @brief   Vex FW code to validate VEX -> JESD -> DNRT rx.
 * @details 1. VEX will wait on the host indication.
 *          2. After the host indication was received for every 2048 cycles 2 number of
 *             vectors will be sent to CM (JESD 0/1) per stream of total 8 streams forever kill host exits app
 *             via modifying g_vex_exit to non zero value ...
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

#define TIMER_NOTIF_LOCATION (0x28)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(0x0)    vbuffer[NUM_MAX_STREAMS_SUPPORT][NUM_TOTAL_VEC_PER_STREAM];
//vec32i32 AT(0x0)    vbuffer[NUM_TOTAL_VEC_PER_STREAM*8];

/*vec32i32 AT(0x2000) vbuffer_1[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0x4000) vbuffer_2[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0x6000) vbuffer_3[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0x8000) vbuffer_4[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0xa000) vbuffer_5[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0xc000) vbuffer_6[NUM_TOTAL_VEC_PER_STREAM];
vec32i32 AT(0xe000) vbuffer_7[NUM_TOTAL_VEC_PER_STREAM];*/


volatile unsigned int AT(0x0) g_dest_buffer_addr[NUM_MAX_STREAMS_SUPPORT];
/*volatile unsigned int AT(0x4) g_dest_buffer1_base;
volatile unsigned int AT(0x8) g_dest_buffer2_base;
volatile unsigned int AT(0xc) g_dest_buffer3_base;
volatile unsigned int AT(0x10) g_dest_buffer4_base;
volatile unsigned int AT(0x14) g_dest_buffer5_base;
volatile unsigned int AT(0x18) g_dest_buffer6_base;
volatile unsigned int AT(0x1C) g_dest_buffer7_base;*/

volatile int AT(0x20) g_num_vec_to_transfer;
volatile int AT(0x24) g_run_forever;
volatile int AT(TIMER_NOTIF_LOCATION) g_timer_debug;
volatile int AT(0x2c) g_debug;
volatile int AT(0x30) g_timeout_cycles;

// 64 should be divisible by vec_per_stream. allowed inputs = 1, 2, 4, 8, 16, 32
volatile int AT(0x40) g_num_vec_per_stream; // mentions how many vectors of data to be streamed per stream in one timeout cycle. 1 = 1kb per stream
volatile int AT(0x44) g_num_streams;


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
    s_xsto_32(Any, 0, TIMER_TMDWDADDRR0, 0x4000 + TIMER_NOTIF_LOCATION);
    // set reg_timer_tmdwddatar0, data will be written to above address
    s_xsto_32(Any, 0, TIMER_TMDWDDATAR0, 0xdeadbeef);
}


/**
 * @brief           Function sending pre defined blocks of data to JESD
 * @param [in]      none
 * @return          none
 */
void vex_producer() ENTRY
{
    int vec_id, stream_id;
    int offset = 0;

    OP___printstring("jesd_tx : start \n");
    init_timer(g_timeout_cycles);

    s_xsto_32(Any, 0, TIMER_TMDCMDR0, TMD_COMMAND_START);           // start the timer

    do
    {
        for(vec_id = 0; (vec_id < g_num_vec_to_transfer); vec_id++)
        {
			for (stream_id = 0; stream_id < g_num_streams; stream_id++)
			{
				//v_xsto_1024(Any, g_dest_buffer_addr[stream_id], vec_id, vbuffer[stream_id][vec_id]);

				v_xstomi_1024(Any, g_dest_buffer_addr[stream_id], offset, 1023, vbuffer[stream_id][vec_id], offset);
				//v_xstomi_1024(Any, dest_address, offset, 1023, vout, offset);
			}
        }   // for(i = 0; i < iter_max; i++) ends
        
		// This flag will be set by Timer once the configured clockds were elapsed
		while (g_timer_debug != 0xdeadbeef)
		{
		}
		g_timer_debug = 0xdead;
		g_debug++;
    } while(g_run_forever == 1);

    s_xsto_32(Any, 0, TIMER_TMDCMDR0, TMD_COMMAND_STOP);           // stop the timer

} // jesd_tx() ends



