#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"

int main(int argc, char **argv)
{
uint32_t read_value;
extern void * srp;
uint16_t i=0,j=0;
uint32_t error = 0;
uint32_t buffer[MEM_ACCESS_SIZE/4];
uint32_t instance_no = 0;
init();

/* reading RCS_CORE_CALIB_SIZE memory */
for (j=0;j < RCS_CORE_CALIB_SIZE/MEM_ACCESS_SIZE;j++) {
   LOG_PRINT("INFO: j is %d \n",j);
   read_mem_18a(RCS_CORE_CALIB_START + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"RCS_CORE_CALIB");
   for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","RCS_CORE_CALIB",instance_no,i*4,buffer[i]);
   }
}
return 0;
}



