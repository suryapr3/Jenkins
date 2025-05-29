#include <common_macros.h>
#include "ve32_appl_target.h"

#include "dmem_read.hive.h"
#include "defines.h"


uInt32 pattern;
uInt32 gscalar[VEX_DMEM_TEST_SIZE];


void  dmem_read_prog() ENTRY
{
  for( int lc = 0; lc < VEX_DMEM_SIZE_WORDS - 1; lc++)
  {
    if( gscalar[lc] == pattern )
    {
      gscalar[lc] = 0;
    }
  }

  //OP___dump(__LINE__,lc);
  OP___printstring( "\n" );
  OP___printstring( "------------dmem_read core:END------------\n" );
}

