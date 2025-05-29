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
uint16_t i,j;
uint32_t error = 0;
uint32_t data0=0xa5a5a5a5;
uint32_t data1=0x5a5a5a5a;
uint32_t buffer[MEM_ACCESS_SIZE/4];
uint32_t instance_no = 0;
init();


write_reg_18a(MEM_FB0_CFG_BASE+MEM_FB_PWR_DOWN_CTRL_OFFSET, 0x0, MEM_FB_PWR_DOWN_CTRL_WR_MASK, "MEM_FB_PWR_DOWN_CTRL_OFFSET");
write_reg_18a(MEM_FB0_CFG_BASE+MEM_FB_EN_OFFSET, 0x1, MEM_FB_EN_WR_MASK, "MEM_FB_EN_OFFSET");
system("srpWrite 0x05028004 0x0");
system("srpWrite 0x05068004 0x0");

#if 1
/* DRF_SRAM_CMEM memory */
for(instance_no = 0 ; instance_no < 2; instance_no++) {
    
	for (j=0;j < DRF_CMEM_SIZE/MEM_ACCESS_SIZE;j++) {

		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_read_mem_expect_18a(DRF_CMEM_START + (instance_no * DRF_CMEM_OFFSET) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_CMEM");
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data1);                       
		write_read_mem_expect_18a(DRF_CMEM_START + (instance_no * DRF_CMEM_OFFSET) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_CMEM");
		fill_random_buffer(buffer,MEM_ACCESS_SIZE/4);                      
		write_read_mem_expect_18a(DRF_CMEM_START + (instance_no * DRF_CMEM_OFFSET) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_CMEM");
	}
}

#endif

#if 1
/*  DRF_SRAM_MEM memory */

for(instance_no = 0 ; instance_no < 1; instance_no++) {
	for (j=0;j < DRF_SRAM_SIZE/MEM_ACCESS_SIZE;j++) {
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_mem_18a(DRF_SRAM_START + (instance_no * DRF_SRAM_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_SRAM");
	}
	for (j=0;j < DRF_SRAM_SIZE/MEM_ACCESS_SIZE;j++) {

		read_mem_expect_18a(DRF_SRAM_START + (instance_no * DRF_SRAM_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_SRAM");
	}
}
#endif
#if 0

/* reading DRF_SRAM_CAP_MEM memory */

for(instance_no = 0 ; instance_no < 1; instance_no++) {
	for (j=0;j < DRF_SRAM_CAP_SIZE/MEM_ACCESS_SIZE;j++) {

		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_read_mem_expect_18a(DRF_SRAM_CAP_START + (instance_no * DRF_SRAM_CAP_SIZE) + j*MEM_ACCESS_SIZE,10,buffer,"DRF_SRAM_CAP");
	}
	for (j=0;j < DRF_SRAM_CAP_SIZE/MEM_ACCESS_SIZE;j++) {

		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		read_mem_expect_18a(DRF_SRAM_CAP_START + (instance_no * DRF_SRAM_CAP_SIZE) + j*MEM_ACCESS_SIZE,10,buffer,"DRF_SRAM_CAP");
	}
	
}
#endif
#if 1
/* reading DRF_ADC_CPU_MEM memory */
for(instance_no = 0 ; instance_no < 2; instance_no++) {
	for (j=0;j < DRF_ADC_CPU_SIZE/MEM_ACCESS_SIZE;j++) {

		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_read_mem_expect_18a(DRF_ADC_CPU_START + (instance_no * DRF_ADC_CPU_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_ADC_CPU");
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data1);
		write_read_mem_expect_18a(DRF_ADC_CPU_START + (instance_no * DRF_ADC_CPU_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_ADC_CPU");
		fill_random_buffer(buffer,MEM_ACCESS_SIZE/4);
		write_read_mem_expect_18a(DRF_ADC_CPU_START + (instance_no * DRF_ADC_CPU_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_ADC_CPU");
	}
}
#endif
#if 0
/* reading DRF_DESC MEM memory*/
for(instance_no = 0 ; instance_no < 1; instance_no++) {
	for (j=0;j < DRF_DESC_SIZE/MEM_ACCESS_SIZE;j++) {

		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
		write_read_mem_expect_18a(DRF_DESC_START + (instance_no * DRF_DESC_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_DESC");
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data1);
		write_read_mem_expect_18a(DRF_DESC_START + (instance_no * DRF_DESC_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_DESC");
		fill_random_buffer(buffer,MEM_ACCESS_SIZE/4);
		write_read_mem_expect_18a(DRF_DESC_START + (instance_no * DRF_DESC_SIZE) + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"DRF_DESC");
	}
}

#endif
return 0;
}
