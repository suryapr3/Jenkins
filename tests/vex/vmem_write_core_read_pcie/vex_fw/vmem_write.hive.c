#include <common_macros.h>
#include "ve32_appl_target.h"

#include "vmem_write.hive.h"
#include "defines.h"

unsigned int pattern; //base address of buffer


vec32i32 gvector[VEX_NUM_VEC];


void  vmem_write_prog() ENTRY
{
  for( int lc = 0; lc < VEX_NUM_VEC; lc++)
  {
    V_CLONE_32(pattern, gvector[lc]);
  }

  //OP___dump(__LINE__,lc);
  OP___printstring( "\n" );
  OP___printstring( "------------vmem_write core:END------------\n" );
}

