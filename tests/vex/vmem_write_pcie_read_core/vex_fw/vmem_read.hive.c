#include <common_macros.h>
#include "ve32_appl_target.h"

#include "vmem_read.hive.h"
#include "defines.h"


uInt32 pattern;
vec32i32 gvector[VEX_NUM_VEC];


void  vmem_read_prog() ENTRY
{
  vec32i32 patternVector;

  V_CLONE_32(pattern, patternVector);

  for( int lc = 0; lc < VEX_NUM_VEC; lc++)
  {
    V_SUB_32(gvector[lc], patternVector, gvector[lc]);
  }

  //OP___dump(__LINE__,lc);
  OP___printstring( "\n" );
  OP___printstring( "------------vmem_write core:END------------\n" );
}
