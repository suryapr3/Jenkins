
/*********************************************************************************************
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
* @file    16g_5c_basic_access2_13_02_24.c
* @brief   jesd reset and enable register access
* @details enable jesd link as needed and hence enable register access.
*/

/*********************************************************************************************
* LOCAL INCLUDE STATEMENTS                    *
*********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"

//#include "nsip_hbi.h"
//#include "ve32_tile_strm2cio.h"
//#include "ve32_tile_cio2strm.h"
//#include "ve32_cell.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"
#include<time.h> 

#define NUM_TOTAL_VEC_PER_STREAM 64
#define NUM_OF_ELEMENTS_PER_VEC 32

/***********************************************
* LOCAL/PRIVATE MACROS AND DEFINES            *
***********************************************/

//#define printf LOG_PRINT


void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

	
static void configure_jesd_block()
{
	uint32_t tx_gb_empty_reg = 0;
	uint32_t tx_gb_full_reg = 0;
	uint32_t rx_gb_empty_reg = 0;
	uint32_t rx_gb_full_reg = 0;


	int i,j=0;
	uint32_t base_address_rx[] = {DLNK_JESDABC0_XIP_204C_RX_BASE,  DLNK_JESDABC1_XIP_204C_RX_BASE,  DLNK_JESDABC2_XIP_204C_RX_BASE,  DLNK_JESDABC3_XIP_204C_RX_BASE};
	uint32_t base_address_tx[] = {DLNK_JESDABC0_XIP_204C_TX_BASE,  DLNK_JESDABC1_XIP_204C_TX_BASE,  DLNK_JESDABC2_XIP_204C_TX_BASE,  DLNK_JESDABC3_XIP_204C_TX_BASE};
	
	for(i=1; i<2; i++)
	{
		tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}
	for(j=1; j<2; j++)
	{
		rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}

	printf(" After jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
	printf(" After jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
	printf(" After jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
	printf(" After jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);
}


int main(int argc, const char *argv[])
{
	int rv = 0;
	int flags = 0;
	int lc, i, j;
	volatile unsigned int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0, host_vec_processed = 0, host_blocks_processed = 0;
	int total_streams_0 = 8;
	int total_streams_1 = 16;
	int dmem_offset = 0x4000;

	unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
	unsigned int add_val[1];
	int rr=0;
	int k=0;
	
	delay(100);	
	system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xa");
    system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0xb");
	delay(100);
	init(); // Initialize the srp
	delay(1000);
	
	//pass the link instances to be enabled
	jesd_reset((JESD_INSTANCE_1), 0);
	delay(1000);
	
	configure_jesd_block();
	delay(1000);

	return rv;
}   // main ends


