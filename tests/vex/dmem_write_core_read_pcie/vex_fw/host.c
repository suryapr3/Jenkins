#include <abc_vex40_system.h>
#include "host.h"
#include <stdlib.h>
#include "utilities.h"

//#define HIVE_MULTIPLE_PROGRAMS

#include "dmem_write.hive.h"

#include "defines.h"
#include "master_to_slave_hrt.h"

#define CELL0 abc_vex40_vex_0_0_ve32

#include "dmem_write_prog.map.h"


int hrt_main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  int i;

  int output_scalar;
  int exit_status = 0;
  unsigned int test_pattern = 0xAAAAAAAA;

  // Load program in cell program memory
  hrt_cell_load_program(CELL0, "dmem_write_prog");

  // load the scalars
  hrt_scalar_store(CELL0, uint, dmem_write_prog_pattern, test_pattern);

  // Run program
  hrt_cell_start_function(CELL0, dmem_write_prog_dmem_write_prog);

  //Wait for the program finish
  hrt_cell_wait(CELL0);

  //Load and compare vector output from cell to host
  for(i=0;i<VEX_DMEM_TEST_SIZE;i++)
  {
    output_scalar = hrt_indexed_load(CELL0, int, dmem_write_prog_gscalar, i);
    printf("test_pattern[%d]: ox%08x [ox%08x]\n", i, output_scalar,test_pattern);

    if((output_scalar) != (test_pattern))
    {
        printf("ERROR:test_pattern[%d]: ox%08x [ox%08x] (diff = %d)\n", i, output_scalar,test_pattern, (output_scalar - test_pattern) );
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
