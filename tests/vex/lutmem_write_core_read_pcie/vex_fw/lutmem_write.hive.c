#include <common_macros.h>
#include "ve32_appl_target.h"

#include "lutmem_write.hive.h"
#include "defines.h"


uInt32 pattern;
vec32i32 vecA;
vec32i32 vecB; 	

void  lutmem_write_prog() ENTRY
{
    uInt32 idxR = 0;
    for( int lc = 0; lc < LUTMEM_VEC_NUM ; lc++)
    {
        V_CLONE_32(pattern, vecA);
        V_CLONE_32(pattern, vecB);
				  
        V_VCOM_TBL_WRITE(idxR, vecA, vecB, idxR);
        idxR++;	  
    }

    //OP___dump(__LINE__,lc);
    OP___printstring( "\n" );
    OP___printstring( "------------lutmem_write core:END------------\n" );
}
