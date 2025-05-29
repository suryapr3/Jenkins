#include <common_macros.h>
#include "ve32_appl_target.h"

#include "defines.h"
#include "consumer.hive.h"
#include "cir_buf.hive.h"

int consumer_max_count;
unsigned int buffer_ra;
volatile int ALIGNED(128) AT(0x180) consumer_sm_gate[16];// write pointer @ consumer core -> producer core will write here
int consumer_token_per_request;
int AT(0x40) count; 

vec32i32 AT(0x0) gTimeStampData;
vec32i32 AT(0x100) gTimeStampDataCopy[10];


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
  circ_buff_init( IS_CONS, 1, 1, 0, sm_ch);


  count = 0;
  int max_count = 5;
  lc = (count < max_count); //loop condition

  while( lc )
  {
    int is_data_ready;
    int idx;
    //check for data buffer
    mc_request( Any, lc, sm_ch, is_data_ready, idx)  SYNC(buffer_read);
    (gTimeStampDataCopy[count++] = gTimeStampData) SYNC_WITH(buffer_read) SYNC_WITH(buffer_write);

    lc = (count < max_count);

    mc_complete( Any, sm_ch, rp);
    v_xsto_32(Any, ra, 0, rp) SYNC(buffer_write);
  }

  OP___dump(__LINE__,count);
  OP___printstring( "\n" );
  OP___printstring( "------------consumer core:END------------\n" );
}
