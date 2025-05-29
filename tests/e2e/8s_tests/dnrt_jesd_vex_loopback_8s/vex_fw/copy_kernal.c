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
#define NUM_STREAMS_SUPPORTED (8)
 

#define VEX_DEST_BUFFER_ADDR (0x0)


/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

vec32i32 AT(VEX_DEST_BUFFER_ADDR) vbuffer_out[NUM_STREAMS_SUPPORTED][VEX_DEST_BUF_SIZE];


volatile int ALIGNED(128) consumer_sm_gate[16]; // write pointer @ consumer core -> producer core will write here


volatile int AT(0x0C) g_num_vecs_in;
volatile int AT(0x10) g_num_blocks;
volatile int AT(0x14) g_tbs_in_blk;


volatile int AT(0x20) g_vec_processed;
unsigned int AT(0x24) g_cur_vec_pos;

volatile unsigned int AT(0x30) g_dest_ptr_address[NUM_STREAMS_SUPPORTED];


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
    int offset = 0;
    int ptr = 0;

    g_vec_processed = 0;
    g_cur_vec_pos = 0;

    semaphore_gate_init();
    /*-------------------------------------------------------------------------*/
    /* Initialize consumer(Buffer):                                            */
    /* g_tbs_in_blk :token buffer size for buffer                                */
    /* consumer_token_per_request : tokens processed per request and ready     */
    /* IS_CONS : the channel is configured as consumer                         */
    /* 0 intial value for local pointer @ consumer                             */
    /* sm_ch - index of Semaphore used                                         */
    /*-------------------------------------------------------------------------*/

    for (int sm_ch = 0; sm_ch < NUM_STREAMS_SUPPORTED; sm_ch++)
    {
        circ_buff_init( IS_CONS, g_tbs_in_blk, CONSUMER_TOKEN_PER_REQUEST, 0, sm_ch);
    }
    
    while(1)
    {

        unsigned int is_data_ready, idx;
        
        for (int sm_ch = 0; sm_ch < NUM_STREAMS_SUPPORTED; sm_ch++)
        {
            mc_request( Any, 1, sm_ch, is_data_ready, idx)  SYNC(buffer_read);
        }

        /* for 0.25IQ ii = 8 is needed due to prologue+epilogue is going beyond the
         * required number of iterations for all other rates ii=0 would work and it
         * will give a loop of 3 cycles with the prologue 7 and epilogue 0 cycles*/
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii=6
#endif
#endif
        for (int i = 0; i < g_num_vecs_in; i++, g_cur_vec_pos++)
        {
          for (int j = 0; j < NUM_STREAMS_SUPPORTED; j++)
          {
              v_xsto_1024_i(Any, g_dest_ptr_address[j], offset, vbuffer_out[j][g_cur_vec_pos]);
          }
          g_vec_processed++;
        }   // for (i = 0; i< g_num_vecs_in; i++) ends

        for (int sm_ch = 0; sm_ch < NUM_STREAMS_SUPPORTED; sm_ch++)
        {
            mc_complete( Any, sm_ch, ptr);
        }
        
        if (g_cur_vec_pos == VEX_DEST_BUF_SIZE)
        {
            g_cur_vec_pos = 0;
        }
        
    }   // while (1) ends
}
