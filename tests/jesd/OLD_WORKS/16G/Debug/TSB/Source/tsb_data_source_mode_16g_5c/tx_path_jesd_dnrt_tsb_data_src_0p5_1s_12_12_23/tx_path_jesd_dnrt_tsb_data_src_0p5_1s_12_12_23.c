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
* @file    tsb_dsm_config_0p5_12_12_23.c
* @brief   Config for TSB data source mode
* @details 1. Configuration of JESD TX glue , JESD TX IP for data source mode using TSB
2.Tx enable
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

int program_tx_ip_registers();
int program_tx_glue_registers();
int program_cmn_csr_registers();
int program_enable_registers();
int program_bfn_registers();

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

	uint32_t tx_gb_empty_st = 0;
	uint32_t tx_gb_full_st = 0;
	
	uint32_t curr_tx_gb_empty_st = 0;
	uint32_t curr_tx_gb_full_st = 0;
	
	uint32_t prev_tx_gb_empty_st = 0;
	uint32_t prev_tx_gb_full_st = 0;

	uint32_t flag_tx_gb_empty_st   = 0;
	uint32_t flag_tx_gb_full_st  = 0;
	
	uint32_t count = 0;
	
	// initialize DUT
	init();
	
	//function calls - Data source mode TSB - config Tx IP,Tx Glue, cmn csr registers
	program_tx_ip_registers();
	program_tx_glue_registers();
	program_cmn_csr_registers();
	program_bfn_registers();
	
	printf("Giving delay of 10 milli seconds \n");
	delay(10);
	
	//enable TSB data source mode - TX_DEBUG_MODE_SEL 0x1
	uint32_t base_address_tx_glue[] = {JESDABC_M0_TX_GLUE_BASE,  JESDABC_M1_TX_GLUE_BASE,  JESDABC_M2_TX_GLUE_BASE,  JESDABC_M3_TX_GLUE_BASE};
	int i=0;
	for(i=0; i<1; i++)	
	{ 
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DEBUG_MODE_SEL_OFFSET, JESDABC_TX_GLUE_MEM_TX_DEBUG_MODE_SEL_DEFAULT, 0x1, 0x1, JESDABC_TX_GLUE_MEM_TX_DEBUG_MODE_SEL_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DEBUG_MODE_SEL_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DEBUG_MODE_SEL_OFFSET");
	}
	delay(10);
	
	/* open the core, first function to call before initiating any read/write */
    srp_dev_open(dev_id, dev_flags, &srp);
	
	int j=0;
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	
	for(j=0; j<1; j++)
	{
		tx_gb_empty_st = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_tx_gb_empty_st_REG");
		tx_gb_full_st = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_tx_gb_full_st_REG");
	}

	printf("\n\n");
	printf("Before jesd enable value for JL_N_tx_gb_empty_st_REG --------is 0x%x \n", tx_gb_empty_st);
	printf("Before jesd enable value for JL_N_tx_gb_full_st_REG ---------is 0x%x \n", tx_gb_full_st);
	
	//for TSB data source mode, the sequence is configure jesd with TSB dsm mode, TX ip en, prefill TSB with data, trig en 
	// sysref en - capture in dnrt Rx 
	program_enable_registers();
	
    int loop = 0;
	while(loop < 1)
	{
		int k=0;
		for(k=0; k<1; k++)
		{
			tx_gb_empty_st = read_reg_18a(base_address_tx[k] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_tx_gb_empty_st_REG");
			tx_gb_full_st = read_reg_18a(base_address_tx[k] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_tx_gb_full_st_REG");
		}
		
		if( count == 0 )
		{
			printf("\n");
			printf("\n");
			printf(" After Jesd enable value for JL_N_tx_gb_empty_st_REG --------is 0x%x \n", tx_gb_empty_st);
			printf(" After Jesd enable value for JL_N_tx_gb_full_st_REG ---------is 0x%x \n", tx_gb_full_st);
		}

			
			if(tx_gb_empty_st)
			{
				curr_tx_gb_empty_st = tx_gb_empty_st;
				if(prev_tx_gb_empty_st != curr_tx_gb_empty_st)
				{
				printf(" \nprevious and current value for JL_N_tx_gb_empty_st_REG are 0x%x, 0x%x\n", prev_tx_gb_empty_st, curr_tx_gb_empty_st);
					flag_tx_gb_empty_st = 1;
					prev_tx_gb_empty_st = curr_tx_gb_empty_st;
				}
			}

			if(tx_gb_full_st)
			{
				curr_tx_gb_full_st = tx_gb_full_st;
				if(prev_tx_gb_full_st != curr_tx_gb_full_st)
				{
				printf(" \nprevious and current value for JL_N_tx_gb_full_st_REG are 0x%x, 0x%x\n", prev_tx_gb_full_st, curr_tx_gb_full_st);
					flag_tx_gb_full_st = 1;
					prev_tx_gb_full_st = curr_tx_gb_full_st;
				}
			}
			
			if((flag_tx_gb_empty_st == 1) || (flag_tx_gb_full_st == 1))
			{
				printf("\n\n");
				flag_tx_gb_empty_st   = 0;
				flag_tx_gb_full_st  = 0;
				count   = 1;
			}

			else
			{
				if((count % 3000) == 0)
				printf(" no change in errors and no change in fifo empty or full at both rx and tx \n");
			}

			
			//if((count % 1000) == 0)
			//	printf("########count is %d \n",count);
			delay(1000); 
			count = count + 1;
			loop = loop + 1;
	}
	
}

void delay(unsigned int milliseconds)
{

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// JESD TX reg
int program_tx_ip_registers()
{
	int i=0;
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	printf("JESD TX IP CONFIG : program_tx_ip_registers \n");
	//for(i=0; i<sizeof(base_address_tx) / sizeof(base_address_tx[0]); i++)
	for(i=0; i<1; i++)
	{ 
		// Common reg config for UC 
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SUBCLASS_OFFSET, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SUBCLASS_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SUBCLASS_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_FEC_OFFSET, JESD_XIP_204C_TX_MEM_TX_FEC_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_FEC_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_FEC_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_FEC_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CRC3_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CRC3_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CRC3_EN_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CRC12_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CRC12_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CRC12_EN_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_OFFSET, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_BIT_ORDER_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_E_OFFSET, JESD_XIP_204C_TX_MEM_TX_E_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_E_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_E_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_E_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CF_OFFSET, JESD_XIP_204C_TX_MEM_TX_CF_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CF_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_HD_OFFSET, JESD_XIP_204C_TX_MEM_TX_HD_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_HD_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_HD_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_HD_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CMD_EN_OFFSET, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CMD_EN_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CMD_EN_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CLK_RATIO_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_S_OFFSET, JESD_XIP_204C_TX_MEM_TX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_S_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_S_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_S_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SONIF_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SONIF_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_N_OFFSET, JESD_XIP_204C_TX_MEM_TX_N_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_N_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_N_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_N_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_NTOTAL_OFFSET, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_NTOTAL_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_NTOTAL_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_CS_OFFSET, JESD_XIP_204C_TX_MEM_TX_CS_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_CS_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_CS_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_CS_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_TEST_MODE_OFFSET");

		printf("JESD tx path - UC 5C -LMFS -4-16-8-1 \n");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SAMPLE_REQ_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_L_OFFSET, JESD_XIP_204C_TX_MEM_TX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_TX_MEM_TX_L_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_L_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_L_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_M_OFFSET, JESD_XIP_204C_TX_MEM_TX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_TX_MEM_TX_M_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_M_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_M_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_F_OFFSET, JESD_XIP_204C_TX_MEM_TX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_TX_MEM_TX_F_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_F_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_F_OFFSET");

		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_DEFAULT, 0x00000010, 0x00000010, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_TL_LATENCY_OFFSET");
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET, JESD_XIP_204C_TX_MEM_TX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_TX_MEM_TX_SCR_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_SCR_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_SCR_OFFSET");
	}
}

// JESD CMN CSR reg
int program_cmn_csr_registers()
{
	int i=0;
	uint32_t base_address_cmn[] = {JESDABC_M0_CMN_CSR_BASE,  JESDABC_M1_CMN_CSR_BASE,  JESDABC_M2_CMN_CSR_BASE,  JESDABC_M3_CMN_CSR_BASE};
	printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
	//for(i=0; i<sizeof(base_address_cmn) / sizeof(base_address_cmn[0]); i++)
	for(i=0; i<1; i++)
	{ 		
		write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
		write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000006, 0x00000006, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
	}
}

// JESD TX glue reg
int program_tx_glue_registers()
{
	int i=0;
	uint32_t base_address_tx_glue[] = {JESDABC_M0_TX_GLUE_BASE,  JESDABC_M1_TX_GLUE_BASE,  JESDABC_M2_TX_GLUE_BASE,  JESDABC_M3_TX_GLUE_BASE};
	printf("JESD TX GLUE CONFIG : program_tx_glue_registers \n");
	//for(i=0; i<sizeof(base_address_tx_glue) / sizeof(base_address_tx_glue[0]); i++)
	for(i=0; i<1; i++)	
	{ 		
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR0_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR0_OFFSET");
		/*
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR1_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR1_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR2_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR2_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR3_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR3_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR4_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR4_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR5_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR5_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR6_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR6_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR7_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR7_OFFSET");
		*/
		
		//changing to 4kb per stream 0x00000fff
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE0_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE0_OFFSET");
		/*
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE1_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE1_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE2_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE2_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE3_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE3_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE4_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE4_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE5_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE5_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE6_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE6_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE7_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE7_OFFSET");
		*/
		// 8 stream changing to 1 memory blocks =4kb - 16*4 =64kb -> 0x10
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_DEFAULT, 0x00000010, 0x00000010, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_OFFSET");
		
		// 8 stream using 1 buffers - 0x00000001
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_OFFSET, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_RD_MASK, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_OFFSET");
		
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_DEFAULT, 0x00000030, 0x00000030, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_CONV_DP_CFG_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_RD_CFG_OFFSET, JESDABC_TX_GLUE_MEM_RD_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_RD_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_RD_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_RD_CFG_OFFSET");

		// trig 0 - bfn trigger , trig1 - bfn trigger 
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_OFFSET");
	
		//Each stream 0x00000000 -> 000 trig fill level size ,not triggering on half full, trigger en -0 -Not using tsb trig en register for tsb dsm 
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET");

		// cfg update - twice ? 
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET");
		
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_OFFSET, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_RD_MASK, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_OFFSET");
		write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET");
	}
}

// JESD BFN reg
int program_bfn_registers()
{
	int i,j = 0;
	uint32_t base_address_bfn[] = {JESDABC_M0_BFN_EVENTS_BASE,  JESDABC_M1_BFN_EVENTS_BASE,  JESDABC_M2_BFN_EVENTS_BASE,  JESDABC_M3_BFN_EVENTS_BASE};
	printf("JESD BFN EVENT CONFIG : program_bfn_registers \n");
	//for(i=0; i<sizeof(base_address_tx) / sizeof(base_address_tx[0]); i++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_ISYNC_CTRL_OFFSET, JESDABC_MEM_JESDABC_ISYNC_CTRL_DEFAULT, 0x00000002, 0x00000002, JESDABC_MEM_JESDABC_ISYNC_CTRL_RD_MASK, JESDABC_MEM_JESDABC_ISYNC_CTRL_WR_MASK, "JESDABC_MEM_JESDABC_ISYNC_CTRL_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_ISYNC_TEN_MS_CNT_OFFSET, JESDABC_MEM_JESDABC_ISYNC_TEN_MS_CNT_DEFAULT, 0x00004000, 0x00004000, JESDABC_MEM_JESDABC_ISYNC_TEN_MS_CNT_RD_MASK, JESDABC_MEM_JESDABC_ISYNC_TEN_MS_CNT_WR_MASK, "JESDABC_MEM_JESDABC_ISYNC_TEN_MS_CNT_OFFSET");

		//for (i=0; i <= 7; i++)
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_CONFIG0_OFFSET, JESDABC_MEM_JESDABC_BFNE_CONFIG_DEFAULT, 0x0000000d, 0x0000000d, JESDABC_MEM_JESDABC_BFNE_CONFIG_RD_MASK, JESDABC_MEM_JESDABC_BFNE_CONFIG_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_CONFIG0_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_INCR0_OFFSET, JESDABC_MEM_JESDABC_BFNE_INCR_DEFAULT, 0x00000400, 0x00000400, JESDABC_MEM_JESDABC_BFNE_INCR_RD_MASK, JESDABC_MEM_JESDABC_BFNE_INCR_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_INCR0_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_START0_OFFSET, JESDABC_MEM_JESDABC_BFNE_START_DEFAULT, 0x00000400, 0x00000400, JESDABC_MEM_JESDABC_BFNE_START_RD_MASK, JESDABC_MEM_JESDABC_BFNE_START_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_START0_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_START0_OFFSET, JESDABC_MEM_JESDABC_BFNE_START_DEFAULT, 0x000004c8, 0x000004c8, JESDABC_MEM_JESDABC_BFNE_START_RD_MASK, JESDABC_MEM_JESDABC_BFNE_START_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_START0_OFFSET");

		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_CONFIG1_OFFSET, JESDABC_MEM_JESDABC_BFNE_CONFIG_DEFAULT, 0x0000000d, 0x0000000d, JESDABC_MEM_JESDABC_BFNE_CONFIG_RD_MASK, JESDABC_MEM_JESDABC_BFNE_CONFIG_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_CONFIG1_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_INCR1_OFFSET, JESDABC_MEM_JESDABC_BFNE_INCR_DEFAULT, 0x00000400, 0x00000400, JESDABC_MEM_JESDABC_BFNE_INCR_RD_MASK, JESDABC_MEM_JESDABC_BFNE_INCR_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_INCR1_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_START1_OFFSET, JESDABC_MEM_JESDABC_BFNE_START_DEFAULT, 0x00000400, 0x00000400, JESDABC_MEM_JESDABC_BFNE_START_RD_MASK, JESDABC_MEM_JESDABC_BFNE_START_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_START1_OFFSET");
		write_read_expect_18a(base_address_bfn[i]+JESDABC_MEM_JESDABC_BFNE_START1_OFFSET, JESDABC_MEM_JESDABC_BFNE_START_DEFAULT, 0x000004c8, 0x000004c8, JESDABC_MEM_JESDABC_BFNE_START_RD_MASK, JESDABC_MEM_JESDABC_BFNE_START_WR_MASK, "JESDABC_MEM_JESDABC_BFNE_START1_OFFSET");
	}
		
}


// JESD enable reg
int program_enable_registers()
{
	int i,j = 0;
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	printf("JESD ENABLE : program_enable_registers \n");
	//for(i=0; i<sizeof(base_address_tx) / sizeof(base_address_tx[0]); i++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_tx[i]+JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_TX_MEM_TX_ENABLEMODULE_OFFSET");
	}
	//for(j=0; i<sizeof(base_address_rx) / sizeof(base_address_rx[0]); j++)
	for(i=0; i<1; i++)
	{ 
		write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_DEFAULT, 0x1, 0x1, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_ENABLEMODULE_OFFSET");
	}
}

