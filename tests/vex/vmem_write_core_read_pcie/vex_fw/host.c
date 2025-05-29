#include <abc_vex40_system.h>
#include "host.h"
#include <stdlib.h>
#include "utilities.h"

//#define HIVE_MULTIPLE_PROGRAMS

#include "vmem_write.hive.h"

#include "defines.h"
#include "master_to_slave_hrt.h"

#define CELL0 abc_vex40_vex_0_0_ve32

#include "vmem_write_prog.map.h"


int hrt_main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  int i, j, idx;

  int output_vec[32];
  int exit_status = 0;
  int cell_sum;
  unsigned int test_pattern = 0x55555555;

  // Load program in cell program memory
  hrt_cell_load_program(CELL0, "vmem_write_prog");

  // load the scalars
  hrt_scalar_store(CELL0, uint, vmem_write_prog_pattern, test_pattern);

  // Run program
  hrt_cell_start_function(CELL0, vmem_write_prog_vmem_write_prog);

  //Wait for the program finish
  hrt_cell_wait(CELL0);

  //Load and compare vector output from cell to host
  for(i=0;i<VEX_NUM_VEC;i++)
  {
    for(j=0;j<32;j++)
    {
      output_vec[j] = hrt_indexed_load(CELL0, int, vmem_write_prog_gvector, ((j) + i*32));
      printf("test_pattern[%d]: ox%08x [ox%08x]\n", ((j) + i*32), output_vec[j],test_pattern);

      if((output_vec[j]) != (test_pattern))
      {
          printf("ERROR:test_pattern[%d]: ox%08x [ox%08x] (diff = %d)\n", ((j) + i*32), output_vec[j],test_pattern, (output_vec[j] - test_pattern) );
          exit_status =1;
      }
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
