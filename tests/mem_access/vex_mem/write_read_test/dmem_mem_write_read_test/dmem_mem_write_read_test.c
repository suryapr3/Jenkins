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
uint32_t data0=0xa5a5a5a5;
uint32_t data1=0x5a5a5a5a;
uint32_t buffer[MEM_ACCESS_SIZE/4];
uint32_t instance_no = 0;
init();


error += subsys_reset_cycle();
error += vex_reset_cycle();

/* reading VEX_DMEM memory */
for(instance_no = 0 ; instance_no < 40; instance_no++) {
//HSED hangs for instance 39
    if((instance_no > 15  && instance_no < 32)||instance_no == 33 ||  instance_no == 35 || instance_no==37||instance_no==39)
	   continue;

   else{
	LOG_PRINT("INFO: j is %d \n",j);
	LOG_PRINT("Instance is: %d\n", instance_no);
	for(j=0;j < VEX_DMEM_SIZE/MEM_ACCESS_SIZE;j++) {
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_read_mem_expect_18a(VEX_DMEM_START + (VEX_DMEM_OFFSET * instance_no) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"VEX_DMEM");
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data1);
		write_read_mem_expect_18a(VEX_DMEM_START + (VEX_DMEM_OFFSET * instance_no) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"VEX_DMEM");
		fill_random_buffer(buffer,MEM_ACCESS_SIZE/4);
		write_read_mem_expect_18a(VEX_DMEM_START + (VEX_DMEM_OFFSET * instance_no) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"VEX_DMEM");
	}     
}
}
return 0;
}
