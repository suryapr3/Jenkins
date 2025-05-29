#include <abc_vex40_system.h>
#include "host.h"
#include <stdlib.h>
#include "utilities.h"
#define HIVE_MULTIPLE_PROGRAMS
#include "defines.h"
#include "master_to_slave_hrt.h"

#define CELL0 abc_vex40_vex_0_0_ve32
#define CELL1 abc_vex40_vex_0_1_ve32

#include "producer.hive.h"
#include "consumer.hive.h"

#include "producer_prog.map.h"
#include "consumer_prog.map.h"

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request

#define BASE_VE00_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_cio2strm_sl_cfg
#define BASE_VE01_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_strm2cio_sl_cfg

#define BASE_VE01_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_cio2strm_sl_cfg
#define BASE_VE00_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_strm2cio_sl_cfg

#define STRM2CIO_2_VMEM  _hrt_master_to_slave_address_abc_vex40_vex_0_0_strm2cio_mt_to_abc_vex40_vex_0_0_ve32_sl_vip
                                   //same for all strm2cio's _hrt_master_to_slave_address_abc_vex40_vex_"X_X"_strm2cio_mt_to_abc_vex40_vex_"X_X"_ve32_sl_vip
#define STRM2CIO_2_DMEM  _hrt_master_to_slave_address_abc_vex40_vex_0_0_strm2cio_mt_to_abc_vex40_vex_0_0_ve32_sl_ip_dmem
                                   //same for all strm2cio's _hrt_master_to_slave_address_abc_vex40_vex_"X_X"_strm2cio_mt_to_abc_vex40_vex_"X_X"_ve32_sl_ip_dmem

#define BASE_CAR _hrt_master_to_slave_address_host_op0_to_abc_vex40_car_sl

#define CAR_ABC_CLOCK_DISABLE0 0x000
#define CAR_ABC_CLOCK_DISABLE1 0x004
#define CAR_ABC_SOFT_RESET0    0x008
#define CAR_ABC_SOFT_RESET1    0x00c
#define CAR_ABC_NOC_CLOCK_GATE 0x094
#define CAR_ABC_NOC_SOFT_RESET 0x098

// Data type to hold table for NOC data
typedef struct address_value_pair_s {
    hive_sim_address  address;
    uint32_t          value;
} address_value_pair_t;

// Table with NOC table to VE init
static address_value_pair_t noc_tbl[] = {
// Crux-reset
    { BASE_CAR+CAR_ABC_NOC_CLOCK_GATE, 0x00000001 },
    { BASE_CAR+CAR_ABC_NOC_SOFT_RESET, 0x00000001 },
    { BASE_CAR+CAR_ABC_NOC_CLOCK_GATE, 0x00000000 },
    { BASE_CAR+CAR_ABC_NOC_SOFT_RESET, 0x00000000 },
// Vex core reset
// clock disable move 1 to 0 and softreset from 0 to 1
    { BASE_CAR+CAR_ABC_CLOCK_DISABLE0,0xFFFFFFFF },//vex cores reset Vex37-Vex00
    { BASE_CAR+CAR_ABC_CLOCK_DISABLE1,      0xFF },//vex cores reset Vex47-Vex40
    { BASE_CAR+CAR_ABC_SOFT_RESET0,   0x00000000 },//vex cores reset Vex37-Vex00
    { BASE_CAR+CAR_ABC_SOFT_RESET1,         0x00 },//vex cores reset Vex47-Vex40

    { BASE_CAR+CAR_ABC_CLOCK_DISABLE0,0x00000000 },//vex cores reset Vex37-Vex00
    { BASE_CAR+CAR_ABC_CLOCK_DISABLE1,      0x00 },//vex cores reset Vex47-Vex40
    { BASE_CAR+CAR_ABC_SOFT_RESET0,   0xFFFFFFFF },//vex cores reset Vex37-Vex00
    { BASE_CAR+CAR_ABC_SOFT_RESET1,         0xFF },//vex cores reset Vex47-Vex40

//VE00->VE01 initialization
//VE00 cio2strm
    { BASE_VE00_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE00_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE00_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE00_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE00_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE00_CIO2STRM+0x140,0x00000001 },//STRM_DEST[0] - mapped to VE01

//VE01 strm2cio
    { BASE_VE01_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL

//VE01->VE00 initialization
//VE01 cio2strm
    { BASE_VE01_CIO2STRM+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_CIO2STRM+0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE01_CIO2STRM+0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE01_CIO2STRM+0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE01_CIO2STRM+0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE01_CIO2STRM+0x100,0x00000000 },//MEM_OFFSET[0]- is in bytes
    { BASE_VE01_CIO2STRM+0x140,0x00000000 },//STRM_DEST[0] - mapped to VE00

//VE00 strm2cio
    { BASE_VE00_STRM2CIO+0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_STRM2CIO+0x020,0x00000001 },//WORD_CNT_CTL
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

  //Initialize cio2strm and strm2cio of involved cores in data transfer used in this test
  // also programs the car-device for power-up/out-of-reset of the vexes
  for (idx=0; idx < sizeof(noc_tbl)/sizeof(address_value_pair_t); idx++)
  {
    _hrt_master_port_store( noc_tbl[idx].address,
                            &noc_tbl[idx].value,
                            sizeof(uint32_t));
  }

  // Initialize system (includes memories of the vex core for ecc reasons!)
  hrt_system_init();

  // Load the pointer copy address for the SDFGates
  hrtx_memid_set_sdfgate_bpca(CELL0, ve32_bp_dmem, HIVE_ADDR_producer_prog_producer_sm_gate);
  hrtx_memid_set_sdfgate_bpca(CELL1, ve32_bp_dmem, HIVE_ADDR_consumer_prog_consumer_sm_gate);

  // Load program in cell program memory
  hrt_cell_load_program(CELL0, "producer_prog");
  hrt_cell_load_program(CELL1, "consumer_prog");

  //producer knows how many numbers of blocks to process at init time.
  //consumer core receives the last block to process as part of token exchange message.
  hrt_scalar_store(CELL0, int, producer_prog_producer_max_count, number_blocks);
  hrt_scalar_store(CELL1, int, consumer_prog_consumer_max_count, number_blocks);

  //Share base address of buffers and address of read/write pointers
  hrt_scalar_store(CELL0, uint, producer_prog_buffer_wa, (STRM2CIO_2_DMEM + HIVE_ADDR_consumer_prog_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)));
  hrt_scalar_store(CELL0, uint, producer_prog_buffer_va, (STRM2CIO_2_VMEM + HIVE_ADDR_consumer_prog_buffer));

  hrt_scalar_store(CELL1, uint, consumer_prog_buffer_ra, (STRM2CIO_2_DMEM + HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)));

  //number of blocks processsed per request
  //if producer and consumer have  different token_per_request, then total blocks processed should  be multiple of both.
  hrt_scalar_store(CELL0, uint, producer_prog_producer_token_per_request, 2);
  hrt_scalar_store(CELL1, uint, consumer_prog_consumer_token_per_request, 5);

  //init values of external pointers
  hrt_indexed_store(CELL0, int, producer_prog_producer_sm_gate, PRODUCER_SM_BUF_ID, 0);
  hrt_indexed_store(CELL1, int, consumer_prog_consumer_sm_gate, CONSUMER_SM_BUF_ID, 0);

  // Run program
  hrt_cell_start_function(CELL0, producer_prog_producer_prog);
  hrt_cell_start_function(CELL1, consumer_prog_consumer_prog);

  //Wait for the program finish
  hrt_cell_wait(CELL0);
  hrt_cell_wait(CELL1);

  //Load scalar output from cell to host
  cell_sum = hrt_scalar_load(CELL1, int, consumer_prog_gsum_tot);
  printf("cell_sum =0x%08x [0x%08x]\n", cell_sum, number_vec);

  //Load and compare vector output from cell to host
  for(i=0;i<32;i++)
  {
    int ref_sum;
    //sum of 1...n numbers = (n * (n+1))/2)
    int n = number_vec;
    ref_sum = ((n*(n+1))/2);
    output_vec[i] = hrt_indexed_load(CELL1, int, consumer_prog_gvecsum,i);
    printf("vecsum[%d]: ox%08x [ox%08x]\n", i, output_vec[i],ref_sum);

    if(((short)output_vec[i]) != ((short)ref_sum))
    {
        printf("ERROR:vecsum[%d]: ox%08x [ox%08x] (diff = %d)\n", i, output_vec[i],ref_sum, (output_vec[i] - ref_sum) );
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
