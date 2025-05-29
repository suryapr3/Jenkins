#include <abc_vex40_system.h>
#include "host.h"
#include <stdlib.h>
#include "utilities.h"
#define HIVE_MULTIPLE_PROGRAMS
#include "defines.h"
#include "master_to_slave_hrt.h"

#define CELL0 abc_vex40_vex_0_0_ve32
#define CELL1 abc_vex40_vex_0_1_ve32
#define CELL2 abc_vex40_vex_0_2_ve32
#define CELL3 abc_vex40_vex_0_3_ve32 

#include "producer_consumer.hive.h"
#include "producer_consumer_prog.map.h"

#define MAX_BLK_COUNT  50 //Has to be multiple of both producer and consumer blks per request

#define BASE_VE00_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_cio2strm_sl_cfg
#define BASE_VE00_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_strm2cio_sl_cfg

#define BASE_VE01_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_strm2cio_sl_cfg
#define BASE_VE01_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_cio2strm_sl_cfg

#define BASE_VE02_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_2_strm2cio_sl_cfg
#define BASE_VE02_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_2_cio2strm_sl_cfg

#define BASE_VE03_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_3_strm2cio_sl_cfg
#define BASE_VE03_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_3_cio2strm_sl_cfg

#define STRM2CIO_2_VMEM  0         //_hrt_master_to_slave_address_abc_vex40_vex_0_0_strm2cio_mt_to_abc_vex40_vex_0_0_ve32_sl_vip
                                   //same for all strm2cio's _hrt_master_to_slave_address_abc_vex40_vex_"X_X"_strm2cio_mt_to_abc_vex40_vex_"X_X"_ve32_sl_vip
#define STRM2CIO_2_DMEM  0x18000   //_hrt_master_to_slave_address_abc_vex40_vex_0_0_strm2cio_mt_to_abc_vex40_vex_0_0_ve32_sl_ip_dmem
                                   //same for all strm2cio's _hrt_master_to_slave_address_abc_vex40_vex_"X_X"_strm2cio_mt_to_abc_vex40_vex_"X_X"_ve32_sl_ip_dmem

// Data type to hold table for NOC data
typedef struct address_value_pair_s {
    hive_sim_address  address;
    uint32_t          value;
} address_value_pair_t;

// Table with NOC table to VE init
static address_value_pair_t noc_tbl[] = {
//VE00->VE03, VE00->VE01 initialization
//VE00 cio2strm
    { BASE_VE00_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE00_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE00_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-28] destination ID,[27-2] bits local address as seen from STRM2CIO in words
    { BASE_VE00_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE00_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE00_CIO2STRM+0x140,0x00000003 },//STRM_DEST[0] - mapped to VE03

//Range2
    { BASE_VE00_CIO2STRM+0x080+1*4,0x10000000 },//MEM_ADDR_LOW[1] - first nibble to differentiative the destination
    { BASE_VE00_CIO2STRM+0x0C0+1*4,0x1001FFFF },//MEM_ADDR_HIGH[1]
    { BASE_VE00_CIO2STRM+0x100+1*4,0x00000000 },//MEM_OFFSET[1]- is in bytes
    { BASE_VE00_CIO2STRM+0x140+1*4,0x00000001 },//STRM_DEST[1] - mapped to VE01

//VE00 strm2cio
    { BASE_VE00_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL


//VE01->VE00, VE01->VE02 initialization
//VE01 cio2strm
    { BASE_VE01_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE01_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE01_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-28] destination ID,[27-2] bits local address as seen from STRM2CIO in words
    { BASE_VE01_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE01_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE01_CIO2STRM+0x140,0x00000000 },//STRM_DEST[0] - mapped to VE00

//Range2
    { BASE_VE01_CIO2STRM+0x080+1*4,0x10000000 },//MEM_ADDR_LOW[1] - first nibble to differentiative the destination
    { BASE_VE01_CIO2STRM+0x0C0+1*4,0x1001FFFF },//MEM_ADDR_HIGH[1]
    { BASE_VE01_CIO2STRM+0x100+1*4,0x00000000 },//MEM_OFFSET[1]- is in bytes
    { BASE_VE01_CIO2STRM+0x140+1*4,0x00000002 },//STRM_DEST[1] - mapped to VE02

//VE01 strm2cio
    { BASE_VE01_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL
    

//VE02->VE01, VE02->VE03 initialization
//VE02 cio2strm
    { BASE_VE02_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE02_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE02_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE02_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-28] destination ID,[27-2] bits local address as seen from STRM2CIO in words
    { BASE_VE02_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE02_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE02_CIO2STRM+0x140,0x00000001 },//STRM_DEST[0] - mapped to VE01

//Range2
    { BASE_VE02_CIO2STRM+0x080+1*4,0x10000000 },//MEM_ADDR_LOW[1] - first nibble to differentiative the destination
    { BASE_VE02_CIO2STRM+0x0C0+1*4,0x1001FFFF },//MEM_ADDR_HIGH[1]
    { BASE_VE02_CIO2STRM+0x100+1*4,0x00000000 },//MEM_OFFSET[1]- is in bytes
    { BASE_VE02_CIO2STRM+0x140+1*4,0x00000003 },//STRM_DEST[1] - mapped to VE03

//VE02 strm2cio
    { BASE_VE02_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE02_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL


//VE03: VE03->VE02, VE03->VE00 initialization
//VE03 cio2strm
    { BASE_VE03_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE03_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE03_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE03_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-28] destination ID,[27-2] bits local address as seen from STRM2CIO in words
    { BASE_VE03_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE03_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE03_CIO2STRM+0x140,0x00000002 },//STRM_DEST[0] - mapped to VE02

//Range2
    { BASE_VE03_CIO2STRM+0x080+1*4,0x10000000 },//MEM_ADDR_LOW[1] - first nibble to differentiative the destination
    { BASE_VE03_CIO2STRM+0x0C0+1*4,0x1001FFFF },//MEM_ADDR_HIGH[1]
    { BASE_VE03_CIO2STRM+0x100+1*4,0x00000000 },//MEM_OFFSET[1]- is in bytes
    { BASE_VE03_CIO2STRM+0x140+1*4,0x00000000 },//STRM_DEST[1] - mapped to VE00

//VE03 strm2cio
    { BASE_VE03_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE03_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL
};

int hrt_main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  int i, idx;

  int output_vec[32];
  int number_blocks = MAX_BLK_COUNT;
  int number_vec = (number_blocks * NUM_VEC_IN_BLK);
  int exit_status = 0;
  int cell_sum;
  int vex_result;

  // Initialize system
  hrt_system_init();

  // Load the pointer copy address for the SDFGates
  hrtx_memid_set_bpca(CELL0, ve32_bp_dmem, HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate);
  hrtx_memid_set_bpca(CELL1, ve32_bp_dmem, HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate);
  hrtx_memid_set_bpca(CELL2, ve32_bp_dmem, HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate);
  hrtx_memid_set_bpca(CELL3, ve32_bp_dmem, HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate);

  // Load program in cell program memory
  hrt_cell_load_program(CELL0, "producer_consumer_prog");
  hrt_cell_load_program(CELL1, "producer_consumer_prog");
  hrt_cell_load_program(CELL2, "producer_consumer_prog");
  hrt_cell_load_program(CELL3, "producer_consumer_prog");

  // For VEX0->VEX1->VEX2->VEX3 with VEX3 loopback to VEX0
  // Note: there is no default flag value. Need to set/clear the flags on all cores
  // Set CELL0 as the first core to generate the test data 
  hrt_scalar_store(CELL0, int, producer_consumer_prog_first_vex_vex, 1);
  hrt_scalar_store(CELL1, int, producer_consumer_prog_first_vex_vex, 0);
  hrt_scalar_store(CELL2, int, producer_consumer_prog_first_vex_vex, 0);
  hrt_scalar_store(CELL3, int, producer_consumer_prog_first_vex_vex, 0);
  // Clear first_cm_vex flag on all cores
  hrt_scalar_store(CELL0, int, producer_consumer_prog_first_cm_vex, 0);
  hrt_scalar_store(CELL1, int, producer_consumer_prog_first_cm_vex, 0);
  hrt_scalar_store(CELL2, int, producer_consumer_prog_first_cm_vex, 0);
  hrt_scalar_store(CELL3, int, producer_consumer_prog_first_cm_vex, 0);
  // Clear last_vex_cm flag on all cores
  hrt_scalar_store(CELL0, int, producer_consumer_prog_last_vex_cm, 0);
  hrt_scalar_store(CELL1, int, producer_consumer_prog_last_vex_cm, 0);
  hrt_scalar_store(CELL2, int, producer_consumer_prog_last_vex_cm, 0);
  hrt_scalar_store(CELL3, int, producer_consumer_prog_last_vex_cm, 0);

  // For CM->VEX0->VEX1->VEX2->VEX3->CM testing, set the flags as follow
  // Note: there is no default flag value. Need to set/clear the flags on all cores
  // Clear first_vex_vex flag on all cores
//  hrt_scalar_store(CELL0, int, producer_consumer_prog_first_vex_vex, 0);
//  hrt_scalar_store(CELL1, int, producer_consumer_prog_first_vex_vex, 0);
//  hrt_scalar_store(CELL2, int, producer_consumer_prog_first_vex_vex, 0);
//  hrt_scalar_store(CELL3, int, producer_consumer_prog_first_vex_vex, 0);
  // Set first_cm_vex flag  on CELL0(the first vex core)
//  hrt_scalar_store(CELL0, int, producer_consumer_prog_first_cm_vex, 1);
//  hrt_scalar_store(CELL1, int, producer_consumer_prog_first_cm_vex, 0);
//  hrt_scalar_store(CELL2, int, producer_consumer_prog_first_cm_vex, 0);
//  hrt_scalar_store(CELL3, int, producer_consumer_prog_first_cm_vex, 0);
  // Set last_vex_cm flag on CELL3(the last vex core)
//  hrt_scalar_store(CELL0, int, producer_consumer_prog_last_vex_cm, 0);
//  hrt_scalar_store(CELL1, int, producer_consumer_prog_last_vex_cm, 0);
//  hrt_scalar_store(CELL2, int, producer_consumer_prog_last_vex_cm, 0);
//  hrt_scalar_store(CELL3, int, producer_consumer_prog_last_vex_cm, 1);

  // Set the number of blocks for the test
  // To run it forever, set producer_consumer_max_count = 0 on all cores
  hrt_scalar_store(CELL0, int, producer_consumer_prog_producer_consumer_max_count, number_blocks);
  hrt_scalar_store(CELL1, int, producer_consumer_prog_producer_consumer_max_count, number_blocks);
  hrt_scalar_store(CELL2, int, producer_consumer_prog_producer_consumer_max_count, number_blocks);
  hrt_scalar_store(CELL3, int, producer_consumer_prog_producer_consumer_max_count, number_blocks);

  //Share base address of buffers and address of read/write pointers
  hrt_scalar_store(CELL0, uint, producer_consumer_prog_buffer_ra, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (PROD_SM_BUF_ID*4) + 0x00000000));
  hrt_scalar_store(CELL0, uint, producer_consumer_prog_buffer_wa, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (CONS_SM_BUF_ID*4) + 0x10000000));
  hrt_scalar_store(CELL0, uint, producer_consumer_prog_buffer_va, (STRM2CIO_2_VMEM + HIVE_ADDR_producer_consumer_prog_buffer + 0x10000000));

  hrt_scalar_store(CELL1, uint, producer_consumer_prog_buffer_ra, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (PROD_SM_BUF_ID*4) + 0x00000000));
  hrt_scalar_store(CELL1, uint, producer_consumer_prog_buffer_wa, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (CONS_SM_BUF_ID*4)+ 0x10000000));
  hrt_scalar_store(CELL1, uint, producer_consumer_prog_buffer_va, (STRM2CIO_2_VMEM + HIVE_ADDR_producer_consumer_prog_buffer + 0x10000000));
  
  hrt_scalar_store(CELL2, uint, producer_consumer_prog_buffer_ra, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (PROD_SM_BUF_ID*4) + 0x00000000));
  hrt_scalar_store(CELL2, uint, producer_consumer_prog_buffer_wa, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (CONS_SM_BUF_ID*4) + 0x10000000));
  hrt_scalar_store(CELL2, uint, producer_consumer_prog_buffer_va, (STRM2CIO_2_VMEM + HIVE_ADDR_producer_consumer_prog_buffer + 0x10000000));

  hrt_scalar_store(CELL3, uint, producer_consumer_prog_buffer_ra, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (PROD_SM_BUF_ID*4) + 0x00000000));
  hrt_scalar_store(CELL3, uint, producer_consumer_prog_buffer_wa, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (CONS_SM_BUF_ID*4) + 0x10000000));
  hrt_scalar_store(CELL3, uint, producer_consumer_prog_buffer_va, (STRM2CIO_2_VMEM + HIVE_ADDR_producer_consumer_prog_buffer + 0x10000000));

  // number of blocks processsed per request
  // if producer and consumer have  different token_per_request, then total blocks processed should  be multiple of both.
  hrt_scalar_store(CELL0, uint, producer_consumer_prog_producer_consumer_token_per_request, 1);
  hrt_scalar_store(CELL1, uint, producer_consumer_prog_producer_consumer_token_per_request, 1);
  hrt_scalar_store(CELL2, uint, producer_consumer_prog_producer_consumer_token_per_request, 1);
  hrt_scalar_store(CELL3, uint, producer_consumer_prog_producer_consumer_token_per_request, 1);

  //Initialize cio2strm and strm2cio of involved cores in data transfer used in this test
  for (idx=0; idx < sizeof(noc_tbl)/sizeof(address_value_pair_t); idx++)
  {
    _hrt_master_port_store( noc_tbl[idx].address,
                            &noc_tbl[idx].value,
                            sizeof(uint32_t));
  }

  vex_result = hrt_scalar_load(CELL0, int, producer_consumer_prog_VEX_RESULT);
  printf("Initial vex result [%d]\n",  vex_result);

  // Run program
  hrt_cell_start_function(CELL0, producer_consumer_prog_producer_consumer_prog);
  hrt_cell_start_function(CELL1, producer_consumer_prog_producer_consumer_prog);
  hrt_cell_start_function(CELL2, producer_consumer_prog_producer_consumer_prog);
  hrt_cell_start_function(CELL3, producer_consumer_prog_producer_consumer_prog);

  //Wait for the program finish
  //hrt_cell_wait(CELL0); // Cell0 will be the last one to finish since it is also the final consumer
  hrt_cell_wait(CELL1);
  vex_result = hrt_scalar_load(CELL0, int, producer_consumer_prog_VEX_RESULT);
  printf("Running vex result [%d]\n",  vex_result);
  hrt_cell_wait(CELL2);
  hrt_cell_wait(CELL3);
  hrt_cell_wait(CELL0);

  //Load scalar output from cell to host
  cell_sum = hrt_scalar_load(CELL0, int, producer_consumer_prog_gsum_tot);
  printf("cell_sum =0x%08x [0x%08x]\n", cell_sum, number_vec);
#if 0
  //Load and compare vector output from cell to host
  for(i=0;i<32;i++)
  {
    int ref_sum;
    //sum of 1...n numbers = (n * (n+1))/2)
    int n = number_vec;
    ref_sum = ((n*(n+1))/2);
    output_vec[i] = hrt_indexed_load(CELL0, int, producer_consumer_prog_gvecsum,i);
    printf("vecsum[%d]: ox%08x [ox%08x]\n", i, output_vec[i],ref_sum);

    if(((short)output_vec[i]) != ((short)ref_sum))
    {
        printf("ERROR:vecsum[%d]: ox%08x [ox%08x] (diff = %d)\n", i, output_vec[i],ref_sum, (output_vec[i] - ref_sum) );
        exit_status =1;
    }
  }
#endif
  vex_result = hrt_scalar_load(CELL0, int, producer_consumer_prog_VEX_RESULT);
  printf("final vex result [%d]\n",  vex_result);

  if(vex_result != TEST_PASS)
  {
     printf("ERROR: expected vex result = 3\n");
     exit_status = 1;
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
