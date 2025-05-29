#include <common_macros.h>
#include "ve32_appl_target.h"

#include "defines.h"
#include "vex2any.hive.h"
#include "cir_buf.hive.h"

vec32i32 vinput[3];

void  vex2any_prog() ENTRY
{
  for(int i = 0; i < 3; i++)
    v_xsto_1024_i(Any, 0x0, 0x0, vinput[i]);

  OP___printstring( "\n" );
  OP___printstring( "------------vex2any core:END------------\n" );
}
