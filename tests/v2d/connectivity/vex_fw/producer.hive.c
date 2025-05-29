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
 * @file    producer.hive.c
 * @brief   Vex FW code to send the data through SDF.
 * @details 1. VEX will be sending the specified blocks of data on SDF.
**/

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <common_macros.h>
#include "ve32_appl_target.h"

#include "cir_buf.hive.h"
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
int producer_max_count;

vec32i32 AT(0) vbuffer_in[128];
unsigned int g_dest_buffer_base; //
unsigned int g_dest_ptr_address;
volatile int ALIGNED(128) producer_sm_gate[16]; // read pointer @ producer core  -> consumer core will write here
unsigned int g_num_vecs_in;
volatile int g_tbs_in_blk;
volatile int g_scalar_val;


vec32i32 vstate;
void process_block_int()
{
    V_CLONE_32(0, vstate);
}

void  producer_prog() ENTRY
{
    unsigned int wa = g_dest_ptr_address;//(unsigned int)&write_pointer1;
    int wp=0;
    int count;
    int lc;
    int max_count;
    int sm_ch = PRODUCER_SM_BUF_ID;
    int offset = 0;

    semaphore_gate_init();
    /*-------------------------------------------------------------------------*/
    /* Initialize producer             .                                       */
    /* g_tbs_in_blk :token buffer size for buffer1                               */
    /* producer_token_per_request: tokens processed per request and ready      */
    /* IS_PROD : the channel is configured for producer                        */
    /* 0 intial value for local pointer @ producer                             */
    /* SM_BUF_ID  - index of Semaphore used                                    */
    /*-------------------------------------------------------------------------*/
    circ_buff_init( IS_PROD, g_tbs_in_blk, PRODUCER_TOKEN_PER_REQUEST, 0, sm_ch);

    process_block_int();

    max_count = producer_max_count;
    count = 0;
    lc = 1; //loop condition

    while( count < max_count )//loop untill there are blocks to send
    {
        int is_space_avl;
        int idx;
        //request space in the buffer
        mc_request( Any, lc, sm_ch, is_space_avl, idx)  SYNC(buffer_read);

        //kernel processing of the block( date write to other core memory)
        //Process and write data if there is enough space in buffer(located in consumer core).

        OP___printstring("producer core: Iteration:\n");
        vec32i32 vin2;
        V_CLONE_32(0, vin2);

        //process_block(idx) ;
        //for (int i =0; i < NUM_VEC_IN_BLK; i++)
        for (int i =0; i < g_num_vecs_in; i++)
        {
            vec32i32 vin1, vout;
            vin1 = vbuffer_in[i];
            V_ADD_32(vin1, vin2, vout);
            v_xstomi_1024(Any, g_dest_buffer_base, offset, g_tbs_in_blk * g_num_vecs_in, vout, offset) SYNC_WITH(buffer_read);
        }

        //inform the consumer the block is ready
        mc_complete( Any, sm_ch, wp);
#if DEBUG
        OP___dump(4404, offset) SYNC_WITH(buffer_read);
        OP___dump(4402,wp);
        OP___dump(4403,wa);
#endif
        v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write);//send write pointer to the consumer core
        count++;
#if DEBUG
        OP___dump(4401,count);
#endif
    }

    OP___printstring( "\n" );
    OP___printstring( "------------producer core:END------------\n" );
}

