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
uint32_t data0=0xa5a5a5a5;
uint32_t data1=0x5a5a5a5a;
uint32_t buffer[MEM_ACCESS_SIZE/4];
uint32_t instance_no = 0;
init();

/* reading RCS_CORE_CALIB_SIZE memory */
for (j=0;j < RCS_CORE_CALIB_SIZE/MEM_ACCESS_SIZE;j++) {
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data0);
                write_read_mem_expect_18a(RCS_CORE_CALIB_START + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"RCS_CORE_CALIB");
		fill_buffer(buffer,MEM_ACCESS_SIZE/4,data1);
                write_read_mem_expect_18a(RCS_CORE_CALIB_START + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"RCS_CORE_CALIB");
	        fill_random_buffer(buffer,MEM_ACCESS_SIZE/4);
                write_read_mem_expect_18a(RCS_CORE_CALIB_START + j*MEM_ACCESS_SIZE,MEM_ACCESS_SIZE/4,buffer,"RCS_CORE_CALIB");
}

return 0;
}
