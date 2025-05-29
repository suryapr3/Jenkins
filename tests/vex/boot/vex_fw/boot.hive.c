#include <common_macros.h>
#include "ve32_appl_target.h"


uInt32 pattern;
uInt32 gscalar;


void  boot_prog() ENTRY
{
  gscalar = pattern;

  //OP___dump(__LINE__,lc);
  OP___printstring( "\n" );
  OP___printstring( "------------boot_prog core:END------------\n" );
}

