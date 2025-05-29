#include <common_macros.h>
#include "ve32_appl_target.h"

#include "defines.h"
#include "vex2rcs.hive.h"
#include "cir_buf.hive.h"

#if 1

vec32i32 vinput[3];

void  vex2rcs_prog() ENTRY
{
  for(int i = 0; i < 3; i++)
	v_xsto_1024_i(Any, 0x0, 0x0, vinput[i]);

  OP___printstring( "\n" );
  OP___printstring( "------------vex2rcs core:END------------\n" );
}

#else
int producer_max_count ;

unsigned int buffer_va; //base address of buffer
unsigned int buffer_wa; //
//unsigned int delay_count;
volatile int ALIGNED(128) producer_sm_gate[16];      // read pointer @ producer core  -> consumer core will write here
int producer_token_per_request;


vec32i32 vstate;
void process_block_int()
{
  V_CLONE_32(0, vstate);
}
void process_block(unsigned int buffer_va, int token_per_request, int blk_idx)
{
  int i, j;
  int idx=0;
  vec32i32 MEM(simd0_xvmem) *base_buffer = ( vec32i32 MEM(simd0_xvmem) * )(buffer_va);
  idx = (blk_idx*NUM_VEC_IN_BLK);
  for(j=0;j<(token_per_request*NUM_VEC_IN_BLK);j++)
  {
    //creating data - sequence of numbers
    vec32i32 va, v_one;

    V_CLONE_32(1, v_one);
    V_ADD_32(v_one, vstate, va);
    
    /*for(i = 0; i < delay_count; i++)
    {
		V_ADD_32(v_one, va, va);
	}*/

    vstate = va;
    OP___dump(9990,va);
    (base_buffer[idx] = va) SYNC_WITH(buffer_read) SYNC_WITH(buffer_write);
    idx++;
    idx = (idx == TBS_IN_VEC) ? 0: idx;
  }
}

void  vex2rcs_prog() ENTRY
{
  unsigned int wa = buffer_wa;//(unsigned int)&write_pointer1;
  int wp=0;
  int count;
  int lc;
  int max_count;
  int sm_ch = PRODUCER_SM_BUF_ID;

  semaphore_gate_init();
  /*-------------------------------------------------------------------------*/
  /* Initialize producer             .                                       */
  /* TBS_IN_BLK :token buffer size for buffer1                               */
  /* producer_token_per_request: tokens processed per request and ready      */
  /* IS_PROD : the channel is configured for producer                        */
  /* 0 intial value for local pointer @ producer                             */
  /* SM_BUF_ID  - index of Semaphore used                                    */
  /*-------------------------------------------------------------------------*/
  circ_buff_init( IS_PROD, TBS_IN_BLK, producer_token_per_request, 0, sm_ch);

  process_block_int();

  max_count = producer_max_count;
  count = 0;
  lc = 1; //loop condition

  while( lc )//loop untill there are blocks to send
  {
    int is_space_avl;
    int idx;
    //request space in the buffer
    mc_request( Any, lc, sm_ch, is_space_avl, idx)  SYNC(buffer_read);

    //kernel processing of the block( date write to other core memory)
    //Process and write data if there is enough space in buffer(located in consumer core).
    count = count + producer_token_per_request;
    lc = (count < max_count);

    OP___printstring("producer core: Iteration:");
    OP___dump(4401,count);
    process_block(buffer_va, producer_token_per_request, idx) ;

    //inform the consumer the block is ready
    mc_complete( Any, sm_ch, wp);
    v_xsto_32(Any, wa, 0, wp) SYNC(buffer_write);//send write pointer to the consumer core
    
  }

  OP___dump(__LINE__,count);
  OP___printstring( "\n" );
  OP___printstring( "------------producer core:END------------\n" );
}
#endif
