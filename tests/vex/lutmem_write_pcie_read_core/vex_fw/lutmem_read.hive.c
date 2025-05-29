#include <common_macros.h>
#include "ve32_appl_target.h"

#include "lutmem_read.hive.h"
#include "defines.h"

// Define an array to store the vectors read from LUT memory
vec32i32 AT(0x0) arr[LUTMEM_VEC_NUM];

void  lutmem_read_prog() ENTRY
{
    uInt32 idxR = 0;
    for( int lc = 0; lc < LUTMEM_VEC_NUM/2; lc++)
    {
        V_VCOM_TBL_READ(idxR, idxR,arr[2*lc] ,arr[(2*lc)+1]);
        // Increment idxR by 2 
        idxR += 2;    
    }
	
    OP___printstring( "\n" );
    OP___printstring( "------------lutmem_read core:END------------\n" )		
}




