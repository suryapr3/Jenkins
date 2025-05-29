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
* @file    tsb_preload_dsm_0p5_14_12_23.c
* @brief   Code for TSB data source mode - preloading data
* @details 1. Configuration of JESD TX glue - filling TSB buffers with data 
2. TX_TSB_TRIG_EN_REG -> Trig0 , trig 1 
* @TC Description:
1. 
*/

/*********************************************************************************************
* LOCAL INCLUDE STATEMENTS                    *
*********************************************************************************************/
#include "srp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include <stdbool.h>
#include "logger.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include<time.h> 
#include "srpCliCommon.h"
#include "common_macro.h"
#include<time.h> 
//#include "jesd.h"
// later need to port the function declaration to jesd.h
// return value void/int  - paramaterization to be explored

void delay(unsigned int mseconds);


int main(int argc, char **argv)
{
	printf("Hello from Main\n");
	uint32_t read_value;
	extern void * srp;
	uint32_t error = 0;
	uint32_t write_status = 0;
	uint32_t dev_id =0;
    uint32_t dev_flags = 0;
	uint32_t count = 0;
	
	//Data source mode TSB - preload TSB and en trigger
	printf("Giving delay of 10 milli seconds \n");
	delay(10);
	/* open the core, first function to call before initiating any read/write */
	srp_dev_open(dev_id, dev_flags, &srp);
	
	uint32_t base_address_tx_glue[] = {JESDABC_M0_TX_GLUE_BASE,  JESDABC_M1_TX_GLUE_BASE,  JESDABC_M2_TX_GLUE_BASE,  JESDABC_M3_TX_GLUE_BASE};
	// preload TSB
	int m=0; 
	
	for(m=0; m<1; m++)	
	{ 	
		int flit_count = 0;
		for(flit_count=0; flit_count < 63; flit_count++)
		{
			int wr_addr = 0x0;
			wr_addr = flit_count | 0x100;
			printf("%x\n",flit_count);
			printf("%x\n",wr_addr);
			
			// 4kb -> 4096 bytes= 4096*8 = 32,768 bits
			// every flit count 16 registers*32 bits = 512 bits =1 flit
			// 32,768 bits / 512 bits = 64 flits -> flit count 0-63
			
			// 64kb -> 65,536 bytes= 65,536*8 = 524,288 bits
			// every flit count 16 registers*32 bits = 512 bits =1 flit
			// 524,288 bits / 512 bits = 64 flits -> flit count 0-63
				
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_DEFAULT, 0x0, 0x0, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET");
			
			//DBG_MEM_WRITE_ADDR :6; [4:0] ->00 0000
			//DBG_WR_BUFFER_SEL : 16; [23:8] -> indicates the buffers selected to be written in data source mode multiple buffers can be selected to written at once , eg 16'b0000_0000_0000_0001
			// wr_addr -> b' 0001 0000 0000 -> 0x100
			
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_DEFAULT, wr_addr, wr_addr, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_ADDR_OFFSET");
			
			// 16 registers *32 bit = 512 bit data 
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA0_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5,0xa5a5a5a5,JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA0_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA1_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA1_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA2_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA2_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA3_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA3_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA4_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA4_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA5_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA5_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA6_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA6_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA7_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA7_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA8_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA8_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA9_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA9_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA10_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA10_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA11_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA11_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA12_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA12_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA13_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA13_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA14_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA14_OFFSET");
			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA15_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_DEFAULT, 0xa5a5a5a5, 0xa5a5a5a5, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_DATA15_OFFSET");

			write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_DEFAULT, 0x1, 0x1, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET");
		}
		write_read_expect_18a(base_address_tx_glue[m]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_DEFAULT, 0x0, 0x0, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MEM_WR_LOAD_OFFSET");
	}	
	
	/* int p=0;
	for(p=0; p<1; p++)
	{ 		
		//TSB ->changing to 0x80000fff -> fff trig fill level size -4kb, not triggering on half full (2kb), trigger en
		// new value of 0x80000fff, after checking with mahesh, 14/12/23
		write_read_expect_18a(base_address_tx_glue[p]+JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x80000fff, 0x80000fff, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET");
	} */
}

void delay(unsigned int milliseconds)
{

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

