#include <common_macros.h>
#include "ve32_appl_target.h"

#include "defines.h"
#include "consumer.hive.h"
#include "cir_buf.hive.h"

int consumer_max_count;
vec32i32 buffer[TBS_IN_VEC];
unsigned int buffer_ra;
volatile int ALIGNED(128) consumer_sm_gate[16];// write pointer @ consumer core -> producer core will write here
int consumer_token_per_request;
int AT(0x40) count; 

volatile int AT(0x44) debug_counter; 

int gsum_tot;
vec32i32 gvecsum;
void process_block_int()
{
  V_CLONE_32(0, gvecsum);
  gsum_tot = 0;
}

void process_block(int token_per_request, int blk_idx)
{
  int loc_sum;
  vec32i32 loc_vsum;
  int idx;
  int j;
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
    V_ADD_SAT_16(v1,loc_vsum, loc_vsum);
    loc_sum++;
  }
  gsum_tot = loc_sum;
  gvecsum = loc_vsum;
}

void  consumer_prog() ENTRY
{
  unsigned int ra = buffer_ra;//(unsigned int)&read_pointer;
  //int count;
  int lc;
  int rp = 0;
  int sm_ch = CONSUMER_SM_BUF_ID;

  semaphore_gate_init();
  /*-------------------------------------------------------------------------*/
  /* Initialize consumer(Buffer):                                            */
  /* TBS_IN_BLK :token buffer size for buffer                                */
  /* consumer_token_per_request : tokens processed per request and ready     */
  /* IS_CONS : the channel is configured as consumer                         */
  /* 0 intial value for local pointer @ consumer                             */
  /* sm_ch - index of Semaphore used                                         */
  /*-------------------------------------------------------------------------*/
  circ_buff_init( IS_CONS, TBS_IN_BLK, consumer_token_per_request, 0, sm_ch);

  //kernel related initialization
  process_block_int();

  count = 0;
  debug_counter = 0;
  int max_count = consumer_max_count;
  lc = (count < max_count); //loop condition

  while( lc )
  {
    int is_data_ready;
    int idx;
    //check for data buffer
    mc_request( Any, lc, sm_ch, is_data_ready, idx)  SYNC(buffer_read);

    //kernel processing
    count = count + consumer_token_per_request;
    lc = (count < max_count);
    debug_counter = 1;

    OP___printstring("     consumer core: Iteration:");
    OP___dump(6601,count);
    debug_counter = 2;
    process_block(consumer_token_per_request , idx);
    debug_counter = 3;
    // inform the producer the block is read and free to refill.
    //ie..transfer the pointer to producer core if the block is filled
    debug_counter = 4;
    mc_complete( Any, sm_ch, rp);
    v_xsto_32(Any, ra, 0, rp) SYNC(buffer_write);
  }

  OP___dump(__LINE__,count);
  OP___printstring( "\n" );
  OP___printstring( "------------consumer core:END------------\n" );
}
