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
 * @file    vex_jesd_rx.c
 * @brief   Vex FW code to validate Jesd Rx Path.
 * @details 1. VEX will be waiting on SDF to receive the data from HOST.
            2. VEX will do the comparison with the generated REF output and stores the result.
            3. Once all the blocks were received the result will be stored to a predefined location
               for the host to read..
            4. This code is specific to sample rates 0.5IQGSPS to 8IQ GSPS and 3R GSPS to 16R GSPS
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"
#include <hive/support.h>
#include "cir_buf.hive.h"
#include "defines.h"

#if (1) // loopback
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(RX_SRC_BUFFER_OFFSET) vbuffer[VEX_SRC_BUF_SIZE_IN_VECTORS];       // pattern
vec32i32 AT(RX_DEST_BUFFER_OFFSET) vbuffer_out[VEX_DEST_BUF_SIZE_IN_VECTORS]; // recived stream address

vec32i32 AT(RX_DEBUG_BUFFER_OFFSET) vout_copy[JESD_MAX_SAMPLE_SIZE_VECTORS];
// vec32i32 AT(RX_DEBUG_BUFFER_OFFSET) vout_copy[2][8];
// RX-HOST INPUTS
volatile int AT(0xc) g_rx_debug;
volatile int AT(0x10) g_rx_num_blocks;
volatile int AT(0x14) g_rx_tbs_in_blk;
volatile int AT(0x18) g_rx_num_vecs_in;
volatile int AT(0x1c) g_rx_stream_count;
volatile int AT(0x20) g_timeout_cycles;
// HOST OUTPUTS
volatile int AT(0x30) g_vec_processed_total;
volatile int AT(0x34) g_block_processed_total;
// TX-HOST INPUTS
// destination addresses
volatile unsigned int AT(0x40) g_tx_dest_address[MAX_STREAM_COUNT];

// TOKENS
volatile int AT(0x80) consumer_sm_gate[MAX_STREAM_COUNT]; // write pointer @ consumer core -> producer core will write here

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

void jesd_rx() ENTRY
{

    // int sm_ch = CONSUMER_SM_BUF_ID;
    int sm_ch_id[MAX_STREAM_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}; // semaphare channel id for each stream
    int stream_count = g_rx_stream_count;
    int offset = 0;
    int ptr = 0;


    // moved this div to host
    //int vec_count_per_stream = (g_rx_num_vecs_in / g_rx_stream_count) * g_rx_tbs_in_blk;

    //int vec_count_per_stream = g_rx_num_vecs_in;
	int vec_count_per_stream = g_rx_num_vecs_in * g_rx_tbs_in_blk;

    g_rx_debug = 0xaa;

    semaphore_gate_init();
    /*-------------------------------------------------------------------------*/
    /* Initialize consumer(Buffer):                                            */
    /* g_rx_tbs_in_blk :token buffer size for buffer                                */
    /* consumer_token_per_request : tokens processed per request and ready     */
    /* IS_CONS : the channel is configured as consumer                         */
    /* 0 intial value for local pointer @ consumer                             */
    /* sm_ch - index of Semaphore used                                         */
    /*-------------------------------------------------------------------------*/

    g_rx_debug = 0xab;
    for (int strm_id = 0; strm_id < MAX_STREAM_COUNT; strm_id++)
    {
        circ_buff_init(IS_CONS, g_rx_tbs_in_blk, CONSUMER_TOKEN_PER_REQUEST, 0, sm_ch_id[strm_id]);
    }
    g_rx_debug = 0xbc;

    // iter_max = g_rx_num_vecs_in; // per stream

    g_rx_debug = g_rx_debug << 4;
    g_block_processed_total = 0;
    g_vec_processed_total = 0;

    // while (blocks_count < (2))
    // while (blocks_count < (g_rx_num_blocks))
    int ping_pong = 0;
    while (1)
    {
        unsigned int is_data_ready, idx;

        g_rx_debug = g_rx_debug << 4;
        // check token for each stream and take a backup of each stream's block
        for (int strm_id = 0; strm_id < stream_count; strm_id++) // loop per stream
        {
            mc_request(Any, 1, sm_ch_id[strm_id], is_data_ready, idx) SYNC(buffer_read);
        }
        // g_rx_debug = g_rx_debug << 8 | (strm_id * iter_max * tbs_in_block);
        g_rx_debug = g_rx_debug << 4 | 2;

#if (0)
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii = 0 // will let compiler to chose optimal piplining factor.
//  #pragma hive pipeline ii=2
//  #pragma hive pipeline ii=3
// #pragma hive force_unroll = 4 //thought: use this for stream loop not vector, vector offset update has dependency on previous one
#endif
#endif
#endif
        for (int vec_id = 0; vec_id < vec_count_per_stream; vec_id++) // loop per vector
        {
            for (int strm_id = 0; strm_id < stream_count; strm_id++) // loop per stream
            {
                // v_xsto_1024_i(Any, g_tx_dest_address[strm_id], offset, vbuffer_out[strm_id][vec_id]);
                // v_xsto_1024_i(Any, g_tx_dest_address[strm_id], offset, vbuffer_out[strm_id * vec_count_per_stream + vec_id]);
                v_xsto_1024_i(Any, g_tx_dest_address[strm_id], offset, vbuffer_out[strm_id * vec_count_per_stream * (ping_pong+1) + vec_id]);
                // v_xsto_1024_i(Any, g_tx_dest_address[strm_id], offset, *(vbuffer_out + (strm_id * vec_count_per_stream *(ping_pong+1) + vec_id)));
            }
            g_vec_processed_total++;
        }
        g_rx_debug = g_rx_debug << 4| 3;

        for (int strm_id = 0; strm_id < stream_count; strm_id++) // loop per stream
        {
            mc_complete(Any, sm_ch_id[strm_id], ptr);
        }

        g_block_processed_total++;        
        g_rx_debug = g_rx_debug << 4 | 4;

    }
    ping_pong = !ping_pong;
} // vex_jesd_rx() ends
// end of loopback code
#endif 
