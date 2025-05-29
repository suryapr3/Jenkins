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
 * @file    vha2vex_p25iq.c
 * @brief   Vex FW code to validate VHA DL path.
 * @details 1. VEX will be waiting on SDF to receive the data from HOST VHA..
            2. VEX will do the comparison with the generated REF output and stores the result.
            3. Once all the blocks were received the result will be stored to a predefined location
               for the host to read to declare the test result..
            4. This code is specific to sample rate 0.25IQGSPS
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>
#include "cir_buf.hive.h"
#include "defines.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TIMER_NOTIF_LOCATION (0x28)

/* register offsets */
#define TIMER_TMDCFGR0      3
#define TIMER_TMDINITR0     4
#define TIMER_TMDWDNOTR0    6
#define TIMER_TMDWDADDRR0   7
#define TIMER_TMDWDDATAR0   8
#define TIMER_TMDCMDR0  9
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

vec32i32 AT(0x4000) vbuffer_out[VEX_DEST_BUF_SIZE];
vec32i32 AT(0xd000) vbuffer_copy[8];


volatile int ALIGNED(128) consumer_sm_gate[16]; // write pointer @ consumer core -> producer core will write here
volatile unsigned int AT(0x04) g_dest_ptr_address;

volatile int AT(0x0C) g_num_vecs_in;
volatile int AT(0x10) g_num_blocks;
volatile int AT(0x14) g_tbs_in_blk;


volatile int AT(0x20) g_vec_processed;

volatile int AT(TIMER_NOTIF_LOCATION) g_timer_debug;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function comparing the blocks received from HOST
 * @param [in]      none
 * @return          none
 */
void copy_kernal() ENTRY
{
    int sm_ch = CONSUMER_SM_BUF_ID;
    int vex_dest_buffer = 0x4000;
    int offset = 0;
    int compare_offset = 0x0;
    unsigned int iter_max = g_num_vecs_in;

    g_vec_processed = 0;

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
    
    while(1)
    {

        unsigned int is_data_ready, idx, ptr;
        

        mc_request( Any, 1, sm_ch, is_data_ready, idx)  SYNC(buffer_read);

        /* for 0.25IQ ii = 8 is needed due to prologue+epilogue is going beyond the
         * required number of iterations for all other rates ii=0 would work and it
         * will give a loop of 3 cycles with the prologue 7 and epilogue 0 cycles*/
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii=6
#endif
#endif
        for (int i = 0; i < iter_max; i++)
        {
          vec32i32 vout UNINIT;

          v_ldoi_1024_circ(Any, vex_dest_buffer , compare_offset, LD_CTL1, LD_CTL2, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
          v_xsto_1024_i(Any, g_dest_ptr_address, offset, vout);

          v_xsto_1024_i(Any, 0x20000, offset, vout);
          v_xsto_1024_i(Any, 0x40000, offset, vout);
          v_xsto_1024_i(Any, 0x60000, offset, vout);
          
          v_xsto_1024_i(Any, 0x80000, offset, vout);
          v_xsto_1024_i(Any, 0xA0000, offset, vout);
          v_xsto_1024_i(Any, 0xC0000, offset, vout);
          v_xsto_1024_i(Any, 0xE0000, offset, vout);
#if DEBUG
          if(0 == g_vec_processed)
          {
              (vbuffer_copy[i] = vout) SYNC_WITH(buffer_read);
          }
#endif
          g_vec_processed++;
          

        }   // for (i = 0; i< num_vecs; i++) ends
        mc_complete( Any, sm_ch, ptr);
    }   // while (1) ends
}
