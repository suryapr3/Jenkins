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
#if (1) // single shot

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

volatile int AT(128) consumer_sm_gate[MAX_STREAM_COUNT]; // write pointer @ consumer core -> producer core will write here

volatile int AT(0xc) g_rx_debug;

volatile int AT(0x10) g_rx_num_blocks;
volatile int AT(0x14) g_rx_tbs_in_blk;
volatile int AT(0x18) g_rx_num_vecs_in;
volatile int AT(0x1c) g_rx_stream_count;
// HOST OUTPUTS
volatile int AT(0x30) g_vec_processed_total;
volatile int AT(0x34) g_block_processed_total;
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

    int tbs_in_block = g_rx_tbs_in_blk;
    int stream_count = g_rx_stream_count;
    int blocks_count = 0;
    unsigned int is_data_ready, idx, ptr, iter_max;
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
    for (int s_id = 0; s_id < stream_count; s_id++)
        circ_buff_init(IS_CONS, g_rx_tbs_in_blk, CONSUMER_TOKEN_PER_REQUEST, 0, sm_ch_id[s_id]);
    g_rx_debug = 0xbc;

    iter_max = g_rx_num_vecs_in; // per stream

    g_rx_debug = g_rx_debug << 4;
    g_block_processed_total = 0;
    g_vec_processed_total = 0;
    // while (blocks_count < (2))
    while (blocks_count < (g_rx_num_blocks))
    {
        g_rx_debug = g_rx_debug << 4| 1;
        blocks_count++;

        // check token for each stream and take a backup of each stream's block
        for (int s_id = 0; s_id < stream_count; s_id++) // loop per stream
        {
            mc_request(Any, 1, sm_ch_id[s_id], is_data_ready, idx) SYNC(buffer_read);
            // g_rx_debug = g_rx_debug << 8 | (s_id * iter_max * tbs_in_block);
        }
        g_rx_debug = g_rx_debug << 4 | 2;

        for (int s_id = 0; s_id < stream_count; s_id++) // loop per stream
        {

#if (1)
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii = 0 // will let compiler to chose optimal piplining factor.
//  #pragma hive pipeline ii=2
//  #pragma hive pipeline ii=3
// #pragma hive force_unroll = 4 //thought: use this for stream loop not vector, vector offset update has dependency on previous one
#endif
#endif
#endif
            for (int i = 0; i < iter_max; i++) // loop per vector
            {
                // vout_copy[(s_id * iter_max) + i] = vbuffer_out[(s_id * iter_max * tbs_in_block) + i];
                vout_copy[(s_id * iter_max) + i] = vbuffer_out[(s_id * iter_max * tbs_in_block) + i];
                g_vec_processed_total++;
            }

        }
        g_rx_debug = g_rx_debug << 4| 3;

        for (int s_id = 0; s_id < stream_count; s_id++) // loop per stream
        {
            mc_complete(Any, sm_ch_id[s_id], ptr);
        }
        g_rx_debug = g_rx_debug << 4 | 4;


    }

} // vex_jesd_rx() ends
// end of single shot
#else //in vex comparison
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
vec32i32 AT(RX_SRC_BUFFER_OFFSET) vbuffer[VEX_SRC_BUF_SIZE_IN_VECTORS];        // pattern
vec32i32 AT(RX_DEST_BUFFER_OFFSET) vbuffer_out[VEX_DEST_BUF_SIZE_IN_VECTORS]; // recived stream address

vec32i32 AT(RX_DEBUG_BUFFER_OFFSET) vout_copy[2][DEBUG_BLOCK_DUMP_SIZE_IN_VECTORS];
// vec32i32 AT(RX_DEBUG_BUFFER_OFFSET) vout_copy[2][8];

volatile int AT(128) consumer_sm_gate[MAX_STREAM_COUNT]; // write pointer @ consumer core -> producer core will write here

volatile unsigned int AT(0x4) g_rx_dest_ptr_address;
volatile int AT(0xc) g_rx_debug;

volatile int AT(0x10) g_rx_num_blocks;
volatile int AT(0x14) g_rx_tbs_in_blk;
volatile int AT(0x18) g_rx_num_vecs_in;
volatile int AT(0x1c) g_rx_stream_count;

volatile int AT(0x20) g_rx_processed_block_count;
volatile int AT(0x24) g_rx_passed_block_count;
volatile int AT(0x28) g_rx_processed_vector_count;
volatile int AT(0x2C) g_rx_passed_vector_count;

volatile int AT(0x30) g_rx_compare_result;
volatile int AT(0x34) g_scalar_comp_result;
volatile int AT(0x38) g_next_dest_offset;
volatile int AT(0x3c) g_next_src_offset;

volatile int AT(0x40) g_rx_debug_scalar_value_dest_index_0;
volatile int AT(0x44) g_rx_debug_scalar_value_src_index_0;
volatile int AT(0x48) g_rx_debug_scalar_offset;
volatile int AT(0x4C) g_next_src_offset_1;

volatile int AT(0x50) g_sample_shift_dest_to_src;
volatile int AT(0x54) g_scalar_value_src_index_x;
volatile int AT(0x58) g_is_shift_vector_aligned;
volatile int AT(0x5c) g_vector_shift_dest_to_src;

volatile int AT(0x60) g_rx_debug_scalar_value_dest_index_00;
volatile int AT(0x64) g_rx_debug_scalar_value_src_index_00;
volatile int AT(0x68) g_shift_rewind_src_value;
volatile int AT(0x6C) g_compare_offset_temp;

volatile int AT(0x70) g_rx_debug_failed_dest_buffer_sample_0;
volatile int AT(0x74) g_rx_debug_failed_src_vector_x_sample_0;
volatile int AT(0x78) g_rx_debug_failed_src_vector_x1_sample_0;

#if DEBUG
volatile int AT(0x3C) g_host_debug;
volatile int AT(0x40) g_host_debug1;
volatile int AT(0x44) g_fail_cnt;
#endif

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
#if (1) // Idea0.2.2  => Idea0.2 + V_ROTATE_32(in0, vin0, vin1, vout0, vout1)
// status: under progress
// Idea0.2!! calculate the shift from 0th index expected pattern ( read only least 16bit) and use as offset for next src buffer v_ldoi_1024_circ cmd.
// use this shift to capture the exact vector at the offset; which should exactly match with the destination
// Note! shift has to be vector aligned
// note! Idea0.2 would only work for sequential 16bit incremental pattern // or with some predefined step(with some tweak)
// note!(extension to Idea0.1 not related to 0.2)  we can also compare only very first element for exact match and use that with Idea0.1( with only checking constant diff b/w src and dest vector).
// prob with Ex: Lets say dest.vector[0].element[0] is matched at src.vector[6].element[30] is matched and therefore the sample onwards, but since it is not vector aligned, normal comparison will fail.
//  Sol: we will combine and rotate src.vector[6] and src.vector[7] to right by '128-30'. this will make src.vector[6].element[30] move to src.vector[7].element[0] and hence will become vector aligned and then it can be compared with dest.vector[0].element[0] successfully
// if matching sample is not vector aligned in src.vector[7]; it(/) will return offset to src.vector[6]; hence +1 to exaclty point to vector where starting matched element found in after rotate
// for this we have to calculate vector shift along with sample shift within vector if any

void jesd_rx() ENTRY
{
    g_rx_compare_result = 0; // 0xFFFFFFFF;
    g_rx_processed_block_count = 0;
    g_next_dest_offset = 0;
    g_next_src_offset = 0;
    g_next_src_offset_1 = 0;
    int sm_ch = CONSUMER_SM_BUF_ID;
    int vex_dest_buffer = RX_DEST_BUFFER_OFFSET;
    // int *p_vex_dest_buffer = (int *)RX_DEST_BUFFER_OFFSET;
    int vex_src_buffer = RX_SRC_BUFFER_OFFSET;
    int compare_offset = 0x0;       // has to be vector aligned (ie 128byte/1024-bit aligned)
    int compare_offset_temp = 0x0;  // has to be vector aligned (ie 128byte/1024-bit aligned)
    int src_compare_offset = 0x0;   // has to be vector aligned (ie 128byte/1024-bit aligned)
    int src_compare_offset_1 = 0x0; // has to be vector aligned (ie 128byte/1024-bit aligned)
    int vec_processed = 0;
    int tbs_in_block = g_rx_tbs_in_blk;
    int limit = 0, rewind = 0;
    int limit_src = 0, rewind_src = 0;
    int scalar_value_src_index_0 = 0;
    int scalar_value_src_index_00 = 0;
    int scalar_value_src_index_x = 0;
    int scalar_value_dest_index_0 = 0;
    int scalar_value_dest_index_00 = 0;
    int failed_src_vector_x_sample_0 = 0;
    int failed_src_vector_x1_sample_0 = 0;
    int failed_dest_buffer_sample_0 = 0;
    int scalar_offset_dest_to_src_index_0 = 0;
    int sample_shift_dest_to_src = 0;
    int vector_shift_dest_to_src = 0;
    int byte_shift_dest_to_src = 0;
    int sample_shift_offset_in_vector = 0;
    int shift_rewind_src_offset = 0;
    int shift_rewind_src_value = 0;
    int offset_diff_with_direction = 0;
    const int count_bit_per_vector_mask = ((1 << g_rx_num_vecs_in) - 1); // ex for 16 vector, it should be 0xFFFF
    int pass_count_bit_per_vector_in_block = 0;
    int passed_vector_count_in_block = 0;
    int passed_vector_count_overall = 0;
    int passed_block_count = 0; // all vector of this block are passed
    int blockToggle = 0;

    // int vec_compare_fail_count[16] = {0}; // per stream; for max 16 stream
    // int vec_compare_pass_count[16] = {0}; // per stream; for max 16 stream

    int blocks_count = 0, result = 0xFFFFFFFF, scalar_comp_result = 0;
    int capture_time = 1;
    unsigned int is_data_ready, idx, ptr, iter_max;
    vec32i32 vin2 UNINIT;
    vec32i32 vin UNINIT, vout_0 UNINIT, vout UNINIT, vadd UNINIT;
    vec32i32 vin_0 UNINIT, vin_1 UNINIT, vin_rout_0 UNINIT, vin_rout_1 UNINIT;
    int sout0 = 0, sout1 = 0;

#if DEBUG
    g_host_debug1 = 0;
    g_host_debug = 0;
    g_fail_cnt = 0;
#endif
    limit = ((BYTES_PER_VEC) << 20) | ((tbs_in_block * g_rx_num_vecs_in * BYTES_PER_VEC) - (BYTES_PER_VEC));
    // limit =  ((128) << 20)        | ((2            * 16            * 128          ) - (128          ));
    // ==> 134,217,728 (0x800 0000) | 3968 (0xF80) = 134,221,696 ( 0x800 0F80)

    rewind = (tbs_in_block * g_rx_num_vecs_in * BYTES_PER_VEC) - (BYTES_PER_VEC);
    //    rewind = (2      * 16            * 128          ) - (128          ); // = 3968 (0xF80)
    //              ( 2     *8              *128)            -(128)            ;//=1920

    // why  limit and rewind 1 vector lesser

    // lata 5/6
    /*
    limit_src = ((BYTES_PER_VEC) << 20) | (2048 - 128); // why 128 less  // size of input pattern is 2048 Bytes
    rewind_src = (2048 - 128);                          // why 128 less  // size of input pattern is 2048 Bytes
     */

    //   limit_src = ((BYTES_PER_VEC) << 20) | (1024 - 128); // why 128 less  // size of input pattern is 1024 Bytes
    //   rewind_src = (1024 - 128);                          // why 128 less  // size of input pattern is 1024 Bytes

    //   limit_src = ((BYTES_PER_VEC) << 20) | (512 - 128); // why 128 less  // size of input pattern is 512 Bytes
    //   rewind_src = (512 - 128);                          // why 128 less  // size of input pattern is 512 Bytes

    limit_src = (((BYTES_PER_VEC) << 20) | ((g_rx_num_vecs_in * BYTES_PER_VEC) - BYTES_PER_VEC)); // why 128 less  // size of input pattern is 1024 Bytes
    rewind_src = ((g_rx_num_vecs_in * BYTES_PER_VEC) - BYTES_PER_VEC);                            // why 128 less  // size of input pattern is 1024 Bytes

    // limit_src =  ((BYTES_PER_VEC) << 20) | (2048); // why 128 less  // size of input pattern is 2048 Bytes
    // rewind_src = (2048); // why 128 less  // size of input pattern is 2048 Bytes

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
    circ_buff_init(IS_CONS, g_rx_tbs_in_blk, CONSUMER_TOKEN_PER_REQUEST, 0, sm_ch);
    g_rx_debug = 0xbc;
#if DEBUG
    OP___dump(__LINE__, g_rx_stream_count);
    OP___dump(__LINE__, g_rx_num_vecs_in);
#endif

    iter_max = g_rx_num_vecs_in;

    s_xsto_32(Any, 0, 4, 0); // clearing timer ?

#if (1) // start first vector handling

    /*First vector has to be ignored from comparision; only to compute the diff*/
    {
        mc_request(Any, 1, sm_ch, is_data_ready, idx);
        // v_ldoi_1024_circ(Any, vex_dest_buffer ,compare_offset, limit, rewind, vtemp, compare_offset);

        // v_ldoi_1024_circ(Any, vex_dest_buffer, compare_offset, limit_src, rewind_src, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
        // v_ldoi_1024_circ(Any, vex_src_buffer, src_compare_offset, limit_src, rewind_src, vin, src_compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
        v_ld_1024(Any, vex_dest_buffer, vout) NO_ALIAS SYNC_WITH(buffer_read); // syntax: v_ld_1024 (<FU>, base_addr, vout0);
        v_ld_1024(Any, vex_src_buffer, vin) NO_ALIAS SYNC_WITH(buffer_read);   // syntax: v_ld_1024 (<FU>, base_addr, vout0);

#if (1)
        V_GET_32(0, vin, scalar_value_src_index_0);
        V_GET_32(0, vout, scalar_value_dest_index_0);

        // now calc pattern shift
        s_sub(Any, scalar_value_dest_index_0, scalar_value_src_index_0, scalar_offset_dest_to_src_index_0); // unit is word (32 bit) sample,

        // Idea0.2!! calculate the shift from 0th index expected pattern ( read only least 16bit) and use as offset for next src buffer v_ldoi_1024_circ cmd.
        // use this shift to capture the exact vector at the offset; which should exactly match with the destination
        // Note! shift has to be vector aligned
        // note! Idea0.2 would only work for sequential 16bit incremental pattern // or with some predefined step(with some tweak)
        // note!(extension to Idea0.1 not related to 0.2)  we can also compare only very first element for exact match and use that with Idea0.1( with only checking constant diff b/w src and dest vector).

        s_shrl(Any, scalar_offset_dest_to_src_index_0, 16, sample_shift_dest_to_src); // logical right shift of 16bits ( both converter (16 bit) data will have same shift)

        // find the scalar value at shift indexed of source buffer. ( value at this index should be exactly same as scalar value of 0th index from destination buffer )
        vector_shift_dest_to_src = (sample_shift_dest_to_src / SAMPLES_PER_VEC);
        sample_shift_offset_in_vector = (sample_shift_dest_to_src % SAMPLES_PER_VEC);
        g_is_shift_vector_aligned = !sample_shift_offset_in_vector;
        // if (sample_shift_offset_in_vector) // to keep the pipeline value intact we do the rotate always, so this condition is irrelevant
        {
            // vector_shift_dest_to_src += 1; // Idealy if matching sample is not vector aligned in src.vector[7]; it(/) will return offset to src.vector[6]; hence +1 to exaclty point to vector where starting matched element found in after rotate but // to keep the pipeline value intact we do the rotate always, in case of aligned it rotates 32 elements so this condition is irrelevant
        }

        v_ldo_1024(Any, vex_src_buffer, (vector_shift_dest_to_src * BYTES_PER_VEC), vin2) NO_ALIAS SYNC_WITH(buffer_read); // syntax: v_ldo_1024 (<FU>, base_addr, offset_in, vout0);

        V_GET_32(sample_shift_offset_in_vector, vin2, scalar_value_src_index_x); // for case when incoming is not vector aligned
        // V_GET_32(0, vin2, scalar_value_src_index_x); // confirmed with PV: it is not gauranteed to be vector aligned in all case
        //  check if it matched as expected
        s_eq(Any, scalar_value_src_index_x, scalar_value_dest_index_0, scalar_comp_result); // syntax: s_eq (<FU>, in0, in1, out0);
#endif

        mc_complete(Any, sm_ch, ptr);
        // iter_max++; // use s_modinc (<FU>, in0, in1, out0); for increments
        // vec_processed++;
        // count = count + 1;
        // compare_offset = 0; // g_rx_num_vecs_in * BYTES_PER_VEC;
        // // src_compare_offset = g_rx_num_vecs_in * BYTES_PER_VEC; // recompute with the shift calculated as per Idea0.2
        // src_compare_offset = (vector_shift_dest_to_src * BYTES_PER_VEC); // sample_shift_dest_to_src* + (g_rx_num_vecs_in * BYTES_PER_VEC);
        // // src_compare_offset_1 = src_compare_offset + BYTES_PER_VEC;       // pointing to next vector in same buffer in rollover manner
        // src_compare_offset_1 = ((vector_shift_dest_to_src + 1) % g_rx_num_vecs_in) * BYTES_PER_VEC; // pointing to next vector in same buffer in rollover manner

#if VEX_HOST_DEBUG
        OP___printstring("vex_flow1: at mc_complete done:\n");
        v_xsto_32(Any, g_rx_dest_ptr_address, 0, ptr) SYNC(buffer_write); // This statement is not required for HOST to VEX communication
#endif
    }
#endif // end first vecor handling
    g_rx_debug = g_rx_debug << 4;

    // while (blocks_count < (2))
    while (blocks_count < (g_rx_num_blocks))
    {
        g_rx_debug = g_rx_debug << 4;
        blocks_count++;
        pass_count_bit_per_vector_in_block = 0; // clearing // temporary
        passed_vector_count_in_block = 0;
        // compare_offset = 0; // g_rx_num_vecs_in * BYTES_PER_VEC; //commented to // pp support
        // src_compare_offset = g_rx_num_vecs_in * BYTES_PER_VEC; // recompute with the shift calculated as per Idea0.2
        src_compare_offset = (vector_shift_dest_to_src * BYTES_PER_VEC); // sample_shift_dest_to_src* + (g_rx_num_vecs_in * BYTES_PER_VEC);
        // src_compare_offset_1 = src_compare_offset + BYTES_PER_VEC;       // pointing to next vector in same buffer in rollover manner
        src_compare_offset_1 = ((vector_shift_dest_to_src + 1) % g_rx_num_vecs_in) * BYTES_PER_VEC; // pointing to next vector in same buffer in rollover manner

        mc_request(Any, 1, sm_ch, is_data_ready, idx) SYNC(buffer_read);
        g_rx_debug = g_rx_debug << 4;

        if (capture_time)
        {
            // start the timer
            s_xsto_32(Any, 0, 9, 0x1);
        }

        // compare_offset_temp = compare_offset;
        // // debug temp starts
        // v_ldoi_1024_circ(Any, vex_dest_buffer, compare_offset, limit, rewind, vout_0, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
        // // compare_offset = 0;
        // compare_offset = compare_offset_temp;
        // vout_o_copy[i] = vout_0;
        //  debug temp ends to remove
        // g_next_dest_offset = compare_offset;
        // g_next_src_offset = src_compare_offset;
        // g_next_src_offset_1 = src_compare_offset_1;
#if !DEBUG
#ifdef VOLCANO
#pragma hive pipeline ii = 6 // will let compiler to chose optimal piplining factor.
//  #pragma hive pipeline ii=2
//  #pragma hive pipeline ii=3
// #pragma hive force_unroll = 4 //thought: use this for stream loop not vector, vector offset update has dependency on previous one
#endif
#endif

        for (int i = 0; i < iter_max; i++)
        // for (int i = 0; i < 1; i++)
        {
            result = 0xFFFFFFFF; // resetting for next vector// just for debugging to have distinct result instead of accumulating and sticky result affecting next vector comparison result;

            // v_ldoi_1024_circ(Any, vex_dest_buffer, compare_offset, limit_src, rewind_src, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
#if (1)
            v_ldoi_1024_circ(Any, vex_dest_buffer, compare_offset, limit, rewind, vout, compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
            v_ldoi_1024_circ(Any, vex_src_buffer, src_compare_offset, limit_src, rewind_src, vin_0, src_compare_offset) NO_ALIAS SYNC_WITH(buffer_read);
            v_ldoi_1024_circ(Any, vex_src_buffer, src_compare_offset_1, limit_src, rewind_src, vin_1, src_compare_offset_1) NO_ALIAS SYNC_WITH(buffer_read);
#else
            v_ldoi_1024_circ(Any, vex_dest_buffer, g_next_dest_offset, limit, rewind, vout, g_next_dest_offset) NO_ALIAS SYNC_WITH(buffer_read);
            v_ldoi_1024_circ(Any, vex_src_buffer, g_next_src_offset, limit_src, rewind_src, vin_0, g_next_src_offset) NO_ALIAS SYNC_WITH(buffer_read);
            v_ldoi_1024_circ(Any, vex_src_buffer, g_next_src_offset_1, limit_src, rewind_src, vin_1, g_next_src_offset_1) NO_ALIAS SYNC_WITH(buffer_read);
#endif
            // vout_copy[i] = vout;

            // Ex: Lets say dest.vector[0].element[0] is matched at src.vector[6].element[30] is matched and therefore the sample onwards, but since it is not vector aligned, normal comparison will fail.
            //  Sol: we will combine and rotate src.vector[6] and src.vector[7] to right by '32(SAMPLES_PER_VEC)-30'. this will make src.vector[6].element[30] move to src.vector[7].element[0] and hence will become vector aligned and then it can be compared with dest.vector[0].element[0] successfully
            //  did not find left rotate
#if (1)
            V_ROTATE_32((SAMPLES_PER_VEC - sample_shift_offset_in_vector), vin_0, vin_1, vin_rout_0, vin_rout_1); // vin_rout_1 should contain vector aligned sample matched
            // just for testing remove it// to check if it being synchronized after first circ
            V_GET_32(0, vin_rout_1, scalar_value_src_index_00);
            V_GET_32(0, vout, scalar_value_dest_index_00);
            g_rx_debug = 0xcd;

            // add the calculated differnce / word to ref_pattern to make it as input streamed word order
            // V_ADD_32(vin, vin2, vadd); // should be required as per Idea0.2

            // Bit value of 1 in output indicates corresponding vector elements are equal
            V_EQ_32(vin_rout_1, vout, sout0, sout1);
#endif
            result = result & (sout0)SYNC_WITH(buffer_write);
            // result = (result & (sout0));                                                 // NO_ALIAS SYNC_WITH(buffer_read);
            // pass_count_bit_per_vector_in_block |= ((result == 0xFFFFFFFF) ? (1 << i) : 0); // max 32 vector per block
            // pass_count_bit_per_vector_in_block |=  (result == 0xFFFFFFFF) ? (1<<i) : (1<<(16+i)); // max 32 vector per block
            passed_vector_count_in_block += ((result == 0xFFFFFFFF) ? 1 : 0);
            vec_processed++;

        } // for (i = 0; i< num_vecs; i++) ends

        if (capture_time)
        {
            // stop the timer
            s_xsto_32(Any, 0, 9, 0x2);
            capture_time = 0;
        }

#if VEX_HOST_DEBUG
        OP___printstring("vex_flow1: at mc_complete done:\n");
        v_xsto_32(Any, g_rx_dest_ptr_address, 0, ptr) SYNC(buffer_write); // This statement is not required for HOST to VEX communication
#endif
        // blocks_count++;
        // passed_block_count += ((pass_count_bit_per_vector_in_block & count_bit_per_vector_mask) == count_bit_per_vector_mask) ? 1 : 0;
        passed_block_count += ((passed_vector_count_in_block == g_rx_num_vecs_in) ? 1 : 0);
        passed_vector_count_overall += passed_vector_count_in_block;
        // g_rx_debug = pass_count_bit_per_vector_in_block; //(pass_count_bit_per_vector_in_block & count_bit_per_vector_mask);
#if DEBUG
        OP___dump(__LINE__, count);
#endif
        iter_max = g_rx_num_vecs_in; // resetting iter_max to. ( setting at end due to different handling of very first vector)
#if 1

        for (int i = 0; i < iter_max; i++)
        {
            // vout_copy[blockToggle][i] = vbuffer_out[i];

            // vout_copy[blockToggle][i] = vbuffer_out[(compare_offset_temp/BYTES_PER_VEC)+i];
            vout_copy[blockToggle][i] = vbuffer_out[(blockToggle * iter_max) + i];
        }
        g_rx_debug = g_rx_debug << 4 | blockToggle;
        blockToggle = !blockToggle;

        mc_complete(Any, sm_ch, ptr);

        if (0xffffffff != result)
        {
            // V_GET_32(0, vout_0, failed_dest_buffer_sample_0);
            V_GET_32(0, vin_0, failed_src_vector_x_sample_0);
            V_GET_32(0, vin_1, failed_src_vector_x1_sample_0);
            // V_GET_32(0, vout, scalar_value_dest_index_00_fail);
            // failed_dest_buffer_sample_0 = p_vex_dest_buffer[0];
            g_next_dest_offset = compare_offset;
            g_next_src_offset = src_compare_offset;
            g_next_src_offset_1 = src_compare_offset_1;
            // for (int i = 0; i < iter_max; i++)
            //     vout_copy[i] = vbuffer_out[i];
            // g_rx_debug = blockToggle;
            // g_rx_debug = g_rx_debug << 4;
            break;
        }

#endif
    }
    // g_rx_debug = g_rx_debug << 8 | 0xef;
    g_rx_processed_block_count = blocks_count;
    g_rx_passed_block_count = passed_block_count;
    g_rx_processed_vector_count = vec_processed;
    g_rx_passed_vector_count = passed_vector_count_overall;
    g_scalar_comp_result = scalar_comp_result;
    g_rx_debug_scalar_offset = scalar_offset_dest_to_src_index_0;
    g_rx_debug_scalar_value_src_index_0 = scalar_value_src_index_0;
    g_rx_debug_scalar_value_dest_index_0 = scalar_value_dest_index_0;
    g_rx_debug_scalar_value_src_index_00 = scalar_value_src_index_00;
    g_rx_debug_scalar_value_dest_index_00 = scalar_value_dest_index_00;
    g_rx_debug_failed_src_vector_x_sample_0 = failed_src_vector_x_sample_0;
    g_rx_debug_failed_src_vector_x1_sample_0 = failed_src_vector_x1_sample_0;
    g_rx_debug_failed_dest_buffer_sample_0 = scalar_value_dest_index_00; // failed_dest_buffer_sample_0;
    g_sample_shift_dest_to_src = sample_shift_dest_to_src;
    g_vector_shift_dest_to_src = vector_shift_dest_to_src;
    g_rx_compare_result = result;
    g_compare_offset_temp = compare_offset_temp;
    g_scalar_value_src_index_x = scalar_value_src_index_x;
    g_shift_rewind_src_value = passed_vector_count_in_block; // pass_count_bit_per_vector_in_block; // shift_rewind_src_value; // temp debug to be removed
    // g_is_shift_vector_aligned = pass_count_bit_per_vector_in_block; // temp debug to be removed
#if DEBUG
    OP___printstring("\n");
    OP___printstring("------------core:END------------\n");
#endif
} // vex_jesd_rx() ends

#endif //#if (1) // Idea0.2.2  => Idea0.2 + V_ROTATE_32(in0, vin0, vin1, vout0, vout1)

//end of in_vex_comparison
#endif //

