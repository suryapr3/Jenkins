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
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.h
 */


/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <abc_vex_system.h>
#include <stdlib.h>
#include "utilities.h"
#include "v2d_underrun_B.map.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define HIVE_MULTIPLE_PROGRAMS

#define VE00 abc_vex_vex_0_0_ve32
#define VE01 abc_vex_vex_0_1_ve32

#define BASE_VE00_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex_vex_0_0_cio2strm_sl_cfg
#define BASE_VE01_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex_vex_0_1_strm2cio_sl_cfg

#define BASE_VE01_CIO2STRM  _hrt_master_to_slave_address_host_op0_to_abc_vex_vex_0_1_cio2strm_sl_cfg
#define BASE_VE00_STRM2CIO  _hrt_master_to_slave_address_host_op0_to_abc_vex_vex_0_0_strm2cio_sl_cfg


#define NUMBER_OF_VECTORS_IN 128 // Corresponds to 1 block of data for 8GSPS
#define NUMBER_OF_VECTORS_OUT 128 // Corresponds to 1 blocks of data for 8GSPS
#define NUM_OF_ELEMENTS_PER_VEC 32

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
//VE00->VE01 initialization
//VE00 cio2strm
    { BASE_VE00_CIO2STRM + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE00_CIO2STRM + 0x020,0x00000001 },//WORD_CNT_CTL
    { BASE_VE00_CIO2STRM + 0x060,0x00000003 },//RANGE_EN -one bit for a range enable - 2 sets enabled below

//Range1
    { BASE_VE00_CIO2STRM + 0x080,0x00000000 },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
    { BASE_VE00_CIO2STRM + 0x0C0,0x0001FFFF },//MEM_ADDR_HIGH[0]
    { BASE_VE00_CIO2STRM + 0x100,0x00000000 },//MEM_OFFSET[0]- is in words
    { BASE_VE00_CIO2STRM + 0x140,0x00000001 },//STRM_DEST[0] - mapped to VE01

//VE01 strm2cio
    { BASE_VE01_STRM2CIO + 0x010,0x00000001 },//FIFO_STATUS_CTL
    { BASE_VE01_STRM2CIO + 0x020,0x00000001 },//WORD_CNT_CTL

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
    int add_const = 10;
    int num_vec_input = NUMBER_OF_VECTORS_IN;
    int num_vec_output = NUMBER_OF_VECTORS_OUT;
    int dest_addr = 0x4000;
    int num_blocks = num_vec_output/num_vec_input;

    // Load program in cell program memory
    hrt_cell_load_program(VE00, "v2d_underrun_B");

    hrt_scalar_store(VE00, uint, v2d_underrun_B_g_scalar_val, add_const);
    hrt_scalar_store(VE00, uint, v2d_underrun_B_g_num_vecs_in, num_vec_input);
    hrt_scalar_store(VE00, uint, v2d_underrun_B_g_dest_buffer_base, dest_addr);
    for (i = 0; i < num_vec_input; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            hrt_indexed_store(VE00, int, v2d_underrun_B_vbuffer, i * NUM_OF_ELEMENTS_PER_VEC + j,
                              (((i * NUM_OF_ELEMENTS_PER_VEC + j) << 16) |(i * NUM_OF_ELEMENTS_PER_VEC + j)));
        }
    }
    //Initialize cio2strm and strm2cio of involved cores in data transfer used in this test
    for (idx = 0; idx < sizeof(noc_tbl) / sizeof(noc_tbl_t); idx++)
    {
        _hrt_master_port_store(noc_tbl[idx].address,
                              &noc_tbl[idx].value,
                              sizeof(uint32_t));
    }

    // Run program
    hrt_cell_start_function(VE00, v2d_underrun_B_underrun_B);

    //Wait for the program finish
    hrt_cell_wait(VE00);

    //Load outputs from cell to host
    for (i = 0; i < num_vec_output; i++)
    {
        if ((0 != i) && (0 == (i % num_vec_input)))
        {
            add_const++;
        }

        printf("host:VE00 output- %d vec elem:", i);
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            int ref_elem = ((((i % num_vec_input) * NUM_OF_ELEMENTS_PER_VEC + j) << 16) |((i % num_vec_input) * NUM_OF_ELEMENTS_PER_VEC + j))
                           + add_const ;
            int cell_elem = hrt_indexed_load(VE01, int, v2d_underrun_B_vbuffer_out, i * NUM_OF_ELEMENTS_PER_VEC + j);
            printf("%d,", cell_elem);
            if(cell_elem != ref_elem)
            {
                printf("host:VE00-vec:[j=%d, i=%d elem idx = %d] cell_elem = 0x%08x [0x%08x], add_const : 0x%08x\n",
                       j,i, i * NUM_OF_ELEMENTS_PER_VEC + j, cell_elem, ref_elem, add_const);
                exit_status =1;
            }
        }
        printf("\n");
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
