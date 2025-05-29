#include <common_macros.h>
#include "ve32_appl_target.h"

#include "defines.h"
#include "producer_consumer.hive.h"
#include "cir_buf.hive.h"

vec32i32 buffer[TBS_IN_VEC];
volatile int ALIGNED(128) AT(0x100) producer_consumer_sm_gate[16];// write pointer @ consumer core -> producer core will write here
unsigned int AT(0x140) buffer_ra;
unsigned int AT(0x144) buffer_va;
unsigned int AT(0x148) buffer_wa;
int AT(0x14C) producer_consumer_max_count;
int AT(0x150) producer_consumer_token_per_request;

int AT(0x154) first_vex_vex;
int AT(0x158) first_cm_vex;
int AT(0x15C) last_vex_cm;

int AT(0x160) VEX_RESULT;
unsigned int AT(0x164) blk_seq_cnt;

vec32i32 v_producer[NUM_VEC_IN_BLK];
vec32i32 vstate;
void p_process_block_int()
{
  V_CLONE_32(0, vstate);
}

// The first VEX producer processing which generates test data
inline void p_process_block(unsigned int buffer_va, int token_per_request, int blk_idx)
{
  int j;
  int idx=0;
  vec32i32 vone;
  V_CLONE_32(1, vone);
  vec32i32 MEM(simd0_xvmem) *base_buffer = ( vec32i32 MEM(simd0_xvmem) * )(buffer_va);
  idx = (blk_idx*NUM_VEC_IN_BLK);
  for(j=0;j<(token_per_request*NUM_VEC_IN_BLK);j++)
  {
    //creating data - sequence of numbers
    vec32i32 v1;
    V_ADD_32(vstate, vone, v1);
    vstate = v1;
    v_producer[j] = v1;
    (base_buffer[idx] = v1) SYNC_WITH(buffer_read) SYNC_WITH(buffer_write);
    idx++;
    idx = (idx == TBS_IN_VEC) ? 0: idx;
  }
}

int gsum_tot;
vec32i32 gvecsum;
void c_process_block_int()
{
  V_CLONE_32(0, gvecsum);
  gsum_tot = 0;
}

// The first VEX consumer processing for loopback data
inline int c_process_block(int token_per_request, int blk_idx)
{
  int loc_sum;
  vec32i32 loc_vsum;
  int idx;
  int j;
  int result = 0;
  int vex_result;
  uint32 out0, dmyouts;
  idx = (blk_idx*NUM_VEC_IN_BLK);
  loc_sum = gsum_tot;
  loc_vsum = gvecsum;
  for(j=0;j<(token_per_request*NUM_VEC_IN_BLK);j++)
  {
    //calculate sum in each element lane
    vec32i32 v1;
    (v1 = buffer[idx]) SYNC_WITH(buffer_read) SYNC_WITH(buffer_write);
    idx++;
    idx = (idx == TBS_IN_VEC) ? 0: idx;
    V_ADD_SAT_32(v1,loc_vsum, loc_vsum);
    loc_sum++;
    V_EQ_32(v_producer[j], v1, out0, dmyouts);
    result += (out0 == 0xFFFFFFFF);
  }
  gsum_tot = loc_sum;
  gvecsum = loc_vsum;
  vex_result = (result == NUM_VEC_IN_BLK) ? TEST_PASS : TEST_FAIL;

  return vex_result;
}

// VEX processing for FIFO mode ( pass thru test data )
inline void p_c_process_block(int token_per_request, int in_blk_idx, int out_blk_idx)
{
  int in_idx, out_idx;
  int j;
  in_idx = (in_blk_idx*NUM_VEC_IN_BLK);

  vec32i32 MEM(simd0_xvmem) *dst_base_buffer = ( vec32i32 MEM(simd0_xvmem) * )(buffer_va);
  out_idx = (out_blk_idx*NUM_VEC_IN_BLK);
  for(j=0;j<(token_per_request*NUM_VEC_IN_BLK);j++)
  {
    vec32i32 v1;
    (v1 = buffer[in_idx]) SYNC_WITH(buffer_read);
    in_idx++;
    in_idx = (in_idx == TBS_IN_VEC) ? 0: in_idx;

    (dst_base_buffer[out_idx] = v1) SYNC(cm_data_order) SYNC_WITH(buffer_write);
    out_idx++;
    out_idx = (out_idx == TBS_IN_VEC) ? 0: out_idx;
  }
}


void  producer_consumer_prog() ENTRY
{
  unsigned int ra = buffer_ra;//(unsigned int)&read_pointer;
  unsigned int wa = buffer_wa;//(unsigned int)&write_pointer1;
  int wp = 0;
  int rp = 0;
  int count;
  int lc;
  int c_sm_ch = CONS_SM_BUF_ID;
  int p_sm_ch = PROD_SM_BUF_ID;
  unsigned int block_sequence_count = 0;

  semaphore_gate_init();
  /*-------------------------------------------------------------------------*/
  /* Initialize consumer(Buffer):                                            */
  /* TBS_IN_BLK :token buffer size for buffer                                */
  /* consumer_token_per_request : tokens processed per request and ready     */
  /* IS_CONS : the channel is configured as consumer                         */
  /* 0 intial value for local pointer @ consumer                             */
  /* sm_ch - index of Semaphore used                                         */
  /*-------------------------------------------------------------------------*/
  circ_buff_init( IS_CONS, TBS_IN_BLK, producer_consumer_token_per_request, 0, c_sm_ch);
  circ_buff_init( IS_PROD, TBS_IN_BLK, producer_consumer_token_per_request, 0, p_sm_ch);

  //kernel related initialization
  p_process_block_int();
  c_process_block_int();

  count = 0;
  int max_count = producer_consumer_max_count;
  lc = (max_count == RUN_FOREVER) ? 1 : (count < max_count); //loop condition

  if(first_cm_vex == 1) // CM to first VEX data transfer. No need to send read pointer to CM
  {
    while( lc )
    {
      int is_data_ready;
      int c_idx, p_idx;
      //check for data buffer
      mc_request( Any, lc, c_sm_ch, is_data_ready, c_idx)  SYNC(buffer_read);
      mc_request( Any, lc, p_sm_ch, is_data_ready, p_idx)  SYNC(buffer_write);

      //kernel processing
      count = count + producer_consumer_token_per_request;
      lc = (max_count == RUN_FOREVER) ? 1 : (count < max_count);

      OP___printstring("          producer_consumer core: Iteration:");
      OP___dump(8801,count);
      p_c_process_block( producer_consumer_token_per_request , c_idx, p_idx);

      //keep a count of number of blocks processed so far
      blk_seq_cnt = block_sequence_count++;

      // inform the producer the block is read and free to refill.
      mc_complete( Any, c_sm_ch, rp);
//      v_xsto_32(Any, ra, 0, rp) SYNC(buffer_read); // No need to send rp to CM

      // inform the consumer the block is written and ready to be read
      mc_complete( Any, p_sm_ch, wp);
      v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write);
    }
  }
  else if(first_vex_vex == 1) // First vex for vex chain loopback test. Full SDF protocol.
  {                           // First vex generates data and also checks loopback result
    while( lc )
    {

     // Running test for a new block ( VEX_RESULT is checked for per block basis ).
     VEX_RESULT = TEST_RUNNING;

     { // First vex core producer code. Generate test data.
      int is_space_avl;
      int p_idx;
      //request space in the buffer
      mc_request( Any, lc, p_sm_ch, is_space_avl, p_idx)  SYNC(buffer_read);

      //kernel processing of the block( date write to other core memory)
      //Process and write data if there is enough space in buffer(located in consumer core).
//    count = count + producer_consumer_token_per_request;
//    lc = (count < max_count);

      OP___printstring("producer core: Iteration:");
      OP___dump(4401,count);
      p_process_block(buffer_va, producer_consumer_token_per_request, p_idx) ;

      //keep a count of number of blocks processed so far
//    blk_seq_cnt = block_sequence_count++;

      //inform the consumer the block is ready
      mc_complete( Any, p_sm_ch, wp);
      v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write);//send write pointer to the consumer core
     }

     { // First vex core consumer code. Receive loopback test data and check.
      int is_data_ready;
      int c_idx;
      int vex_result;

      //check for data buffer
      mc_request( Any, lc, c_sm_ch, is_data_ready, c_idx)  SYNC(buffer_read) SYNC(buffer_write);

      //kernel processing
      count = count + producer_consumer_token_per_request;
      lc = (max_count == RUN_FOREVER) ? 1 : (count < max_count);

      OP___printstring("     consumer core: Iteration:");
      OP___dump(6601,count);
      vex_result = c_process_block(producer_consumer_token_per_request , c_idx);

      //keep a count of number of blocks processed so far
      blk_seq_cnt = block_sequence_count++;

      // inform the producer the block is read and free to refill.
      //ie..transfer the pointer to producer core if the block is read
      mc_complete( Any, c_sm_ch, rp);
      v_xsto_32(Any, ra, 0, rp) SYNC(buffer_write);

      VEX_RESULT = vex_result;

      if(vex_result == TEST_FAIL)
      {
        lc = 0; // Stop the loop if the test fail for this block
        OP___printstring("Test failed at block # "); OP___printdec(count-producer_consumer_token_per_request); OP___printstring("\n");
      }
     }
    } // end of while(lc)
  }
  else if(last_vex_cm == 1) // Last VEX to CM. No pointer exchange with CM
  {
    int p_idx = 0;

    while( lc )
    {
      int is_data_ready;
      int c_idx;
      //check for data buffer
      mc_request( Any, lc, c_sm_ch, is_data_ready, c_idx)  SYNC(buffer_read);
//      mc_request( Any, lc, p_sm_ch, is_data_ready, p_idx)  SYNC(buffer_write); // CM not sending rp back.

      //kernel processing
      count = count + producer_consumer_token_per_request;
      lc = (max_count == RUN_FOREVER) ? 1 : (count < max_count);

      OP___printstring("          producer_consumer core: Iteration:");
      OP___dump(8802,count);
      p_c_process_block( producer_consumer_token_per_request , c_idx, p_idx);

      // Increment p_idx every token with modulo TBS_IN_BLK
      s_modadd(Any, p_idx, producer_consumer_token_per_request, TBS_IN_BLK, p_idx);

      //keep a count of number of blocks processed so far
      blk_seq_cnt = block_sequence_count++;

      // inform the producer the block is read and free to refill.
      mc_complete( Any, c_sm_ch, rp);
      v_xsto_32(Any, ra, 0, rp) SYNC(buffer_read);

      // inform the consumer the block is written and ready to be read
//      mc_complete( Any, p_sm_ch, wp); // VEX producer mc_request, mc_complete not needed for CM consumer
//      v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write); // No need to send wp to CM
    }
  }
  else // VEX cores in FIFO( data pass thru ). Full SDF protocol
  {
    while( lc )
    {
      int is_data_ready;
      int c_idx, p_idx;
      //check for data buffer
      mc_request( Any, lc, c_sm_ch, is_data_ready, c_idx)  SYNC(buffer_read);
      mc_request( Any, lc, p_sm_ch, is_data_ready, p_idx)  SYNC(buffer_write);

      //kernel processing
      count = count + producer_consumer_token_per_request;
      lc = (max_count == RUN_FOREVER) ? 1 : (count < max_count);

      OP___printstring("          producer_consumer core: Iteration:");
      OP___dump(8001,count);
      p_c_process_block( producer_consumer_token_per_request , c_idx, p_idx);

      //keep a count of number of blocks processed so far
      blk_seq_cnt = block_sequence_count++;

      // inform the producer the block is read and free to refill.
      mc_complete( Any, c_sm_ch, rp);
      v_xsto_32(Any, ra, 0, rp) SYNC(buffer_read);

      // inform the consumer the block is written and ready to be read
      mc_complete( Any, p_sm_ch, wp);
      v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write);
    }
  }

  OP___dump(__LINE__,count);
  OP___printstring( "\n" );
  OP___printstring( "------------producer_consumer core:END------------\n" );
}
