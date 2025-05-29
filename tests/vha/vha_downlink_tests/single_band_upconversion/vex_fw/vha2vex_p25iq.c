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

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(0x0000) vbuffer[VEX_IN_BUF_SIZE];
vec32i32 AT(0x4000) vbuffer_out[VEX_DEST_BUF_SIZE];
//vec32i32 AT(0xc000) vbuffer_out_copy[4];
#if DEBUG
vec32i32 AT(0xc000) vIpCopy[128];
#endif
volatile int AT(0x80) consumer_sm_gate[16]; // write pointer @ consumer core -> producer core will write here
volatile unsigned int AT(0x4) g_dest_ptr_address;
volatile int AT(0x08) g_scalar_val;
volatile int AT(0x0C) g_num_vecs_in;
volatile int AT(0x10) g_num_blocks;
volatile int AT(0x14) g_tbs_in_blk;
volatile int AT(0x24) g_version;
volatile int AT(0x30) g_count1;
volatile int AT(0x34) g_compare_result;
volatile int AT(0x38) g_add_val_out;
#if DEBUG
volatile int AT(0x3C) g_host_debug;
volatile int AT(0x40) g_host_debug1;
volatile int AT(0x44) g_fail_cnt;
#endif
//volatile int AT(0x60) g_dbg[8];
//volatile int AT(0x90) g_compare[64];

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
void vha2vex_p25iq() ENTRY
{
    int sm_ch = CONSUMER_SM_BUF_ID;
    int vex_dest_buffer = 0x4000;
    int compare_offset = 0x0;
    int vec_processed = 0;
    g_compare_result = 0xFFFFFFFF;
    g_add_val_out = g_scalar_val;
    g_version = 0x30112023;
#if DEBUG
    g_host_debug1 = 0;
    g_host_debug = 0;
    g_fail_cnt = 0;
#endif

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
#if DEBUG
    OP___dump(__LINE__, g_scalar_val);
    OP___dump(__LINE__, g_num_vecs_in);
#endif

    int count = 0, add_temp = 0, result = 0xFFFFFFFF;
    add_temp = g_add_val_out;

    while (count < (g_num_blocks))
    {

        unsigned int is_data_ready, idx, ptr, iter_max;
        vec32i32 vin2 UNINIT;
        iter_max = g_num_vecs_in;

        V_CLONE_32(add_temp, vin2);
        mc_request( Any, 1, sm_ch, is_data_ready, idx)  SYNC(buffer_read);

        /* for 0.25IQ ii = 8 is needed due to prologue+epilogue is going beyond the
         * required number of iterations for all other rates ii=0 would work and it
         * will give a loop of 3 cycles with the prologue 7 and epilogue 0 cycles*/
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii=8
#endif
#endif
        for (int i = 0; i < iter_max; i++)
        {
          vec32i32 vin UNINIT, vout UNINIT, vadd UNINIT;

          int sout0, sout1;
          (vin = vbuffer[i]) NO_ALIAS SYNC_WITH(buffer_read);
          V_ADD_32(vin, vin2, vadd);
          v_ldoi_1024_circ(Any, vex_dest_buffer , compare_offset, LD_CTL1, LD_CTL2, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
          //vout = vbuffer_out[g_count1%256];
          //Bit value of 1 in output indicates corresponding vector elements are equal
          V_EQ_32(vadd, vout, sout0, sout1) SYNC_WITH(buffer_read);
#if DEBUG
         (vIpCopy[i] = vadd) SYNC_WITH(buffer_read);
         (vIpCopy[i+64] = vout) SYNC_WITH(buffer_read);
#endif

#if DEBUG
          OP___dump(__LINE__, vadd);;
          OP___dump(__LINE__, vout);;
          OP___dump(__LINE__, sout0);
          OP___dump(9008, compare_offset);
#endif
          result = result & (sout0) SYNC_WITH(buffer_read);
#if DEBUG
          OP___dump(__LINE__, result);
          if(0 == count)
          {
//             (vbuffer_out_copy[i] = vout) SYNC_WITH(buffer_read); //vbuffer_out[count];
          }
#if 1
         if(0xffffffff != result)
         {
             g_fail_cnt += 1;
         }
         if ((0 == count) && (0 == i))
          {
                //V_GET_32(2,vout,g_host_debug);
                //V_GET_32(2,vadd,g_host_debug1);
                //V_GET_32(0,vout,g_dbg[0]);
                //V_GET_32(1,vout,g_dbg[1]);
                //V_GET_32(2,vout,g_dbg[2]);
                //V_GET_32(3,vout,g_dbg[3]);
          }
#endif
#endif
          vec_processed++;

	  //g_compare[i] = result;
        }   // for (i = 0; i< num_vecs; i++) ends
        add_temp ++;
        mc_complete( Any, sm_ch, ptr);

        count++;
#if DEBUG
        OP___dump(__LINE__,count);
#endif
    }   // while (count < g_num_blocks) ends
    g_add_val_out = add_temp;
    g_count1 = vec_processed;
    g_compare_result = result;
#if DEBUG
    OP___printstring( "\n" );
    OP___printstring( "------------core:END------------\n" );
#endif
}
