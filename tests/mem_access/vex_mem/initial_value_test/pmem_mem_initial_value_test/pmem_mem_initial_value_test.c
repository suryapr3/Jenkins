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
#include "common_functions.h"

int main(int argc, char **argv)
{
uint32_t read_value;
extern void * srp;
uint16_t i=0,j=0;
uint32_t error = 0;
uint32_t buffer[MEM_ACCESS_SIZE/4];
uint32_t instance_no = 0;
init();
LOG_PRINT("The VEX_PMEM_OFFSET: 0x%x", VEX_PMEM_OFFSET);
/* reading VEX_PMEM memory */
for(instance_no = 0 ; instance_no < 40; instance_no++) {

	//HSED hangs for 39
    if((instance_no > 15  && instance_no < 32)||instance_no == 33 ||  instance_no == 35 || instance_no==37||instance_no==39)
	   continue;

else{
   LOG_PRINT("INFO: instance_no is %d \n",instance_no);
   for(j=0;j < VEX_PMEM_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(VEX_PMEM_START +(instance_no * VEX_PMEM_OFFSET) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"VEX_PMEM");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
           if(buffer[i] != 0x0)
               LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","VEX_PMEM",instance_no,i*4,buffer[i]);
           }
       }    
}	   
}
return 0;
}



