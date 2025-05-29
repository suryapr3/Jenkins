#include <common_macros.h>
#include "ve32_appl_target.h"

#include "dmem_write.hive.h"
#include "defines.h"


uInt32 pattern;
uInt32 gscalar[VEX_DMEM_TEST_SIZE];


void  dmem_write_prog() ENTRY
{
  for( int lc = 0; lc < VEX_DMEM_SIZE_WORDS - 1; lc++)
  {
    gscalar[lc] = pattern;
  }

  //OP___dump(__LINE__,lc);
  OP___printstring( "\n" );
  OP___printstring( "------------dmem_write core:END------------\n" );
}

