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

/*DRF_CMEM */
for(instance_no = 0 ; instance_no < 3; instance_no++) {
	
	if(instance_no==1)
		continue;
	
	else{
	LOG_PRINT("The instance_no is %d", instance_no);
   for (j=0;j < DRF_CMEM_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(DRF_CMEM_START + (instance_no * DRF_CMEM_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_CMEM");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","DRF_CMEM",instance_no,i*4,buffer[i]);
       }
   }
}
}

/* DRF_SRAM */

for(instance_no = 0 ; instance_no < 1; instance_no++) {
	LOG_PRINT("The instance_no is %d", instance_no);
   for (j=0;j < DRF_SRAM_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(DRF_SRAM_START + (instance_no * DRF_SRAM_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_SRAM");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","DRF_SRAM",instance_no,i*4,buffer[i]);
       }
   }
}

/*DRF_SRAM_CAP*/

for(instance_no = 0 ; instance_no < 1; instance_no++) {
	LOG_PRINT("The instance_no is %d", instance_no);
   for (j=0;j < DRF_SRAM_CAP_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(DRF_SRAM_CAP_START + (instance_no * DRF_SRAM_CAP_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_SRAM_CAP");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","DRF_SRAM_CAP_MEM",instance_no,i*4,buffer[i]);
       }
   }
}


/*DRF_ADC_CPU*/
for(instance_no = 0 ; instance_no < 1; instance_no++) {
	LOG_PRINT("The instance_no is %d", instance_no);
   for (j=0;j < DRF_ADC_CPU_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(DRF_ADC_CPU_START + (instance_no * DRF_ADC_CPU_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_ADC_CPU");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","DRF_ADC_CPU_MEM",instance_no,i*4,buffer[i]);
       }
   }
}


/*DRF_DESC*/

for(instance_no = 0 ; instance_no < 1; instance_no++) {
	LOG_PRINT("The instance_no is %d", instance_no);
   for (j=0;j < DRF_DESC_SIZE/MEM_ACCESS_SIZE;j++) {
       LOG_PRINT("INFO: j is %d \n",j);
       read_mem_18a(DRF_DESC_START + (instance_no * DRF_DESC_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_DESC");
       for(i=0;i<MEM_ACCESS_SIZE/4;i++){
       if(buffer[i] != 0x0)
           LOG_PRINT("ERROR: data read from %s memory instance %d offset 0x%x  is 0x%x","DRF_DESC_MEM",instance_no,i*4,buffer[i]);
       }
   }
}


return 0;
}






