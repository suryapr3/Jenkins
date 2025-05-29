/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/
/**
 * @file    host.c
 * @brief   HRT host configuration file for sending data from one Vex to another Vex.
 * @details 1. VEX00 sends the data (3 blocks) to VEX02.
            2. VEX02 (producer core) will send the data (MAX block) to VEX01.
            3. VEX01 which is waiting on the SDF will receive the data and do the comparision..
            4. Host will read the result written by VEX and evaluate the test.
 * @todo    Write documentation for source file sample_source.h
 */


/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <abc_vex40_system.h>
#include <stdlib.h>
#include "utilities.h"
#include "v2d_flow7_tx.map.h"
#include "producer_prog.map.h"
#include "v2d_flow7_rx.map.h"
#include "defines.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS

#define VE00 abc_vex40_vex_0_0_ve32
#define VE01 abc_vex40_vex_0_1_ve32
#define VE02 abc_vex40_vex_0_2_ve32

#define BASE_VE00_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_cio2strm_sl_cfg
#define BASE_VE01_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_cio2strm_sl_cfg
#define BASE_VE02_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_2_cio2strm_sl_cfg

#define BASE_VE00_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_0_strm2cio_sl_cfg
#define BASE_VE01_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_1_strm2cio_sl_cfg
#define BASE_VE02_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex40_vex_0_2_strm2cio_sl_cfg

#define NUMBER_OF_VECTORS_IN 8 // Corresponds to 1 block of data for 0.25IQGSPS
#define NUMBER_OF_VECTORS_OUT 512 // Corresponds to 3 blocks of data for 8GSPS
#define NUM_OF_ELEMENTS_PER_VEC 32

#if VEX_HOST_DEBUG
#define MAX_BLOCKS 500
#else
#define MAX_BLOCKS  2
#endif

#define STRM2CIO_0_DMEM 0x10000
#define STRM2CIO_0_VMEM 0x0
#define TBS_IN_BLK  2

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
// Data type to hold table for NOC data
typedef struct noc_tbl_s {
    hive_sim_address  address;
    uint32_t          value;
} noc_tbl_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
// Table with NOC table to VE init
static noc_tbl_t noc_tbl[] = {
//VE00->VE02 initialization
//VE00 cio2strm
    { BASE_VE00_CIO2STRM + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_CIO2STRM + 0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE00_CIO2STRM + 0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE00_CIO2STRM + 0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE00_CIO2STRM + 0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE00_CIO2STRM + 0x100,0x00000000 },//MEM_OFFSET[0]- is in words
    { BASE_VE00_CIO2STRM + 0x140,0x00000002 },//STRM_DEST[0] - mapped to VE02

//VE02 strm2cio
    { BASE_VE02_STRM2CIO + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE02_STRM2CIO + 0x020,0x00000001 },//WORD_CNT_CTL

//VE02->VE01 initialization
//VE02 cio2strm
    { BASE_VE02_CIO2STRM + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE02_CIO2STRM + 0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE02_CIO2STRM + 0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE02_CIO2STRM + 0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE02_CIO2STRM + 0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE02_CIO2STRM + 0x100,0x00000000 },//MEM_OFFSET[0]- is in words
    { BASE_VE02_CIO2STRM + 0x140,0x00000001 },//STRM_DEST[0] - mapped to VE01

//VE01 strm2cio
    { BASE_VE01_STRM2CIO + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_STRM2CIO + 0x020,0x00000001 },//WORD_CNT_CTL

//VE01->VE02 initialization
//VE01 cio2strm
    { BASE_VE01_CIO2STRM + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_CIO2STRM + 0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE01_CIO2STRM + 0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE01_CIO2STRM + 0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE01_CIO2STRM + 0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE01_CIO2STRM + 0x100,0x00000000 },//MEM_OFFSET[0]- is in words
    { BASE_VE01_CIO2STRM + 0x140,0x00000002 },//STRM_DEST[0] - mapped to VE02

};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int hrt_main(int argc, char **argv)
{
    int i, j, idx;
    int cell_val = 0;
    int exit_status = 0;
    int add_const = 0x0;
    int num_vec_input = NUMBER_OF_VECTORS_IN;
    int num_vec_output = NUMBER_OF_VECTORS_OUT;
    int dest_addr = 0x4000;
    int num_blocks = MAX_BLOCKS;
    //int host_num_vecs_block = 128;
    int host_num_vecs_block = 1;


    // Load program in cell program memory
    hrt_cell_load_program(VE00, "v2d_flow7_tx");
    hrt_cell_load_program(VE01, "v2d_flow7_rx");
    hrt_cell_load_program(VE02, "producer_prog");

    // Load the pointer copy address for the SDFGates
    hrtx_memid_set_bpca(VE01, ve32_bp_dmem, HIVE_ADDR_v2d_flow7_rx_consumer_sm_gate);
    hrtx_memid_set_bpca(VE02, ve32_bp_dmem, HIVE_ADDR_producer_prog_producer_sm_gate);

    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_scalar_val, add_const);
    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_num_vecs_in, num_vec_input);
    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_dest_buffer_base, 0x6000);
    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_num_blocks, 0);
    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_initial_block_size, 3);
    hrt_scalar_store(VE00, uint, v2d_flow7_tx_g_host_cycle_count, 511);

    hrt_scalar_store(VE01, uint, v2d_flow7_rx_g_scalar_val, add_const);
    hrt_scalar_store(VE01, uint, v2d_flow7_rx_g_num_vecs_in, num_vec_input);
    hrt_scalar_store(VE01, uint, v2d_flow7_rx_g_tbs_in_blk, TBS_IN_BLK);
    hrt_scalar_store(VE01, uint, v2d_flow7_rx_g_dest_ptr_address,
            (STRM2CIO_0_DMEM + HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)));
    hrt_scalar_store(VE01, uint, v2d_flow7_rx_g_num_blocks, num_blocks);

    hrt_scalar_store(VE02, uint, producer_prog_producer_max_count, num_blocks);
    hrt_scalar_store(VE02, uint, producer_prog_g_scalar_val, add_const);
    hrt_scalar_store(VE02, uint, producer_prog_g_num_vecs_in, num_vec_input);
    hrt_scalar_store(VE02, uint, producer_prog_g_tbs_in_blk, TBS_IN_BLK);
    hrt_scalar_store(VE02, uint, producer_prog_g_dest_ptr_address,
            (STRM2CIO_0_DMEM + HIVE_ADDR_v2d_flow7_rx_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)));
    hrt_scalar_store(VE02, uint, producer_prog_g_dest_buffer_base, (STRM2CIO_0_VMEM + HIVE_ADDR_v2d_flow7_rx_vbuffer_out));

    for(i = 0; i < num_vec_input; i++)
    {
        for(j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            hrt_indexed_store(VE02, int, producer_prog_vbuffer_in, i * NUM_OF_ELEMENTS_PER_VEC + j,
                              (((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + j)));
            hrt_indexed_store(VE01, int, v2d_flow7_rx_vbuffer, i * NUM_OF_ELEMENTS_PER_VEC + j,
                              (((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + j)));
            hrt_indexed_store(VE00, int, v2d_flow7_tx_vbuffer, i * NUM_OF_ELEMENTS_PER_VEC + j,
                              (((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + j)));
        }
    }

    //Initialize cio2strm and strm2cio of involved cores in data transfer used in this test
    for (idx=0; idx < sizeof(noc_tbl) / sizeof(noc_tbl_t); idx++)
    {
        _hrt_master_port_store(noc_tbl[idx].address,
                              &noc_tbl[idx].value,
                              sizeof(uint32_t));
    }

    // Run program
    hrt_cell_start_function(VE00, v2d_flow7_tx_v2d_flow7_tx);
    printf ("abc_flow1 is started \n");
    hrt_cell_start_function(VE01, v2d_flow7_rx_v2d_flow7_rx);
    printf ("abc_flow1_rx is started\n");

    hrt_cell_start_function(VE02, producer_prog_producer_prog);

    //Wait for the program finish
    hrt_cell_wait(VE01);

    //Load outputs from cell to host
    int vex_compare_result = hrt_scalar_load(VE01, int, v2d_flow7_rx_g_compare_result);
    if (vex_compare_result != 0xFFFFFFFF)
    {
        printf("vex comparision failed, value is %08X\n", vex_compare_result);
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
