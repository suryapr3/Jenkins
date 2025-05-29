#include <abc_vex40_system.h>
#include "host.h"
#include <stdlib.h>
#include "utilities.h"

//#define HIVE_MULTIPLE_PROGRAMS

#include "lutmem_read.hive.h"

#include "defines.h"
#include "master_to_slave_hrt.h"

#define CELL0 abc_vex40_vex_0_0_ve32

#include "lutmem_read_prog.map.h"


#if 0

int hrt_main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  int i;

  //int output_scalar;
  int output_vector;
  int exit_status = 0;
  unsigned int test_pattern = 0xAAAAAAAA;

  // Load program in cell program memory
  hrt_cell_load_program(CELL0, "lutmem_read_prog");

  // load the scalars
  hrt_scalar_store(CELL0, uint, lutmem_read_prog_pattern, test_pattern);
  
  // write the test_pattern into vex dmem
 
  for(i = 0; i < (LUTMEM_VEC_NUM * 2); i++)

  {
    hrt_indexed_store(CELL0, int, lutmem_read_prog_vecA, i, test_pattern);
  }
  // Run program
  hrt_cell_start_function(CELL0, lutmem_read_prog_lutmem_read_prog);

  //Wait for the program finish
  hrt_cell_wait(CELL0);

  //Load and compare vector output from cell to host
  

  for(i = 0;i < (LUTMEM_VEC_NUM * 2); i++)

  {
    output_vector = hrt_indexed_load(CELL0, int, lutmem_read_prog_pattern, i);
    printf("test_pattern[%d]: ox%08x [ox%08x]\n", i, output_vector,0x0);

    if((output_vector) != (0x0))
    {
        printf("ERROR:test_pattern[%d]: ox%08x [ox%08x] (diff = %d)\n", i, output_vector,0x0, (output_vector - 0x0) );
        exit_status =1;
    }
  }

  if(exit_status ==0)
  {
     printf("host:----------------SUCCESS----------------\n");
  }
  else
  {
    printf("host:****************FAILURE****************\n");
  }
  return TB_FINISH(exit_status ? -1 : 0);  // Mandatory testbench finish routine - will return its argument as exit code
}

#endif

