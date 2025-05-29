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
#include "cir_buf.hive.h"

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
vec32i32 AT(0x0)    vbuffer_0[NUM_TOTAL_VEC_PER_STREAM];

vec32i32 AT(0xc000) vbuffer_7[NUM_TOTAL_VEC_PER_STREAM*2];


//vec32i32 AT(0) vbuffer[VEX_IN_BUF_SIZE];
vec32i32 AT(0x4000) vbuffer_out[VEX_DEST_BUF_SIZE];


volatile int ALIGNED(128) consumer_sm_gate[16]; // write pointer @ consumer core -> producer core will write here

volatile int AT(0xC) g_num_vecs_in;
volatile int AT(0x14) g_tbs_in_blk;


volatile int AT(0x24) g_vex_exit;
volatile int AT(TIMER_NOTIF_LOCATION) g_timer_debug;

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
void jesd_rx() ENTRY
{
    int iter_max = g_num_vecs_in;
    int sm_ch = CONSUMER_SM_BUF_ID;
    int vex_dest_buffer = 0x4000;
    int compare_offset = 0x0;

    g_vex_exit = 0;

    OP___printstring("jesd_tx : start \n");
    
    semaphore_gate_init();
    /*-------------------------------------------------------------------------*/
    /* Initialize consumer(Buffer):                                            */
    /* g_tbs_in_blk :token buffer size for buffer                                */
    /* consumer_token_per_request : tokens processed per request and ready     */
    /* IS_CONS : the channel is configured as consumer                         */
    /* 0 intial value for local pointer @ consumer                             */
    /* sm_ch - index of Semaphore used                                         */
    /*-------------------------------------------------------------------------*/

    circ_buff_init( IS_CONS, g_tbs_in_blk, CONSUMER_TOKEN_PER_REQUEST, 0, sm_ch);
    

    while(g_vex_exit == 0)
    {
		int index = 0;
		unsigned int is_data_ready, idx, ptr;
		
        mc_request( Any, 1, sm_ch, is_data_ready, idx)  SYNC(buffer_read);
        
        for (int i = 0; i < iter_max; i++)
        {
		  vec32i32 vout UNINIT;

          v_ldoi_1024_circ(Any, vex_dest_buffer , compare_offset, LD_CTL1, LD_CTL2, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
          
          vbuffer_7[index%(NUM_TOTAL_VEC_PER_STREAM*2)]= vout;

		}
		index++;
		mc_complete( Any, sm_ch, ptr);

    }
    
    //s_xsto_32(Any, 0, TIMER_TMDCMDR0, TMD_COMMAND_STOP);           // stop the timer

} // jesd_rx() ends



