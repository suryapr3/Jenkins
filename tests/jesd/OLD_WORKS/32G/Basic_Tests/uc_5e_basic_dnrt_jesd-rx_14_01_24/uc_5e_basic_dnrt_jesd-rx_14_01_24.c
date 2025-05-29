
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
* @file    vex_jesd_dnrt.c
* @brief   HOST Configuration code for sending the data from VEX to JESD and receving it back.
* @details 1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
and receving it back to VEX for all the Sample Rates
2. Evaluate the result written by VEX for the test case evaluation.
* @TC Description:
1. 32K samples (1K vectors) for given data rate will be streamed to JESD from
configured VEX core.
2. With JESD NSIP loop back enabled the data looped back at sample interface
was expected to reach the other VEX core where comparison will be performed.
4. VEX core on which comparison algo was running will update the comparison result for
every vector comparison and once the total 1K vector comparison was done HOST will
read the result.
5. Host will be waiting on a memory location where VEX will update the number of vectors
it was processed.
6. The supported Sample rates are
0.25IQ, 0.5IQ, 1IQ, 2IQ, 4IQ, 8IQ, 4R, 8R, 16R
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

#include "nsip_hbi.h"
#include "ve32_tile_strm2cio.h"
#include "ve32_tile_cio2strm.h"
#include "ve32_cell.h"
#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"

#include<time.h> 

//test

uint16_t core_number;
uint16_t i,j,k;


/***********************************************
* LOCAL/PRIVATE MACROS AND DEFINES            *
***********************************************/

//#define printf LOG_PRINT

#define NUM_TOTAL_VEC_PER_STREAM 64

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define NUM_OF_ELEMENTS_PER_VEC 32

#define APB_OFFSET_GEN(apb_num) (apb_num * 0x20000)

#define FIFO_CONTROL_VALUE 0x00000184
#define CREDIT_CS_VALUE 0x3
#define MISC_CTRL_VALUE 0x0
#define CSR_INT_VALUE 0xFFFFFFFF

void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// JESD CMN CSR reg
// JESD CMN CSR reg
//For 16G usecases JESD CMN CSR reg == 0x6 //UC-5C;UC-2B;UC-2C;UC-3A;UC-3B;UC-3D;UC-7C;

//For 32G usecases JESD CMN CSR reg == 0x1 //UC-5E
static int program_cmn_csr_registers()
	{
		int i=0;
		uint32_t base_address_cmn[] = {JESDABC_M0_CMN_CSR_BASE,  JESDABC_M1_CMN_CSR_BASE,  JESDABC_M2_CMN_CSR_BASE,  JESDABC_M3_CMN_CSR_BASE};
		printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
		//for(i=0; i<sizeof(base_address_cmn) / sizeof(base_address_cmn[0]); i++)
		for(i=0; i<1; i++)
		{ 		
				write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_TX_IP_CLK_CTRL_OFFSET");
				write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_DEFAULT, 0x00000001, 0x00000001, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_RD_MASK, JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_WR_MASK, "JESDABC_CMN_CSR_MEM_RX_IP_CLK_CTRL_OFFSET");
		}
	}

// JESD RX reg
static int program_rx_ip_registers()
	{
		int i=0; 
		uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
		printf("JESD RX IP CONFIG : program_rx_ip_registers \n");
		//for(i=0; i<sizeof(base_address_rx) / sizeof(base_address_rx[0]); i++)
		for(i=0; i<1; i++)
		{ 
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SUBCLASS_OFFSET, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SUBCLASS_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SUBCLASS_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET, JESD_XIP_204C_RX_MEM_RX_FEC_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_FEC_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_FEC_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_FEC_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CRC3_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CRC3_EN_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_OFFSET, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_BIT_ORDER_OFFSET");
			
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_E_OFFSET, JESD_XIP_204C_RX_MEM_RX_E_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_E_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_E_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_E_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CF_OFFSET, JESD_XIP_204C_RX_MEM_RX_CF_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CF_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_HD_OFFSET, JESD_XIP_204C_RX_MEM_RX_HD_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_HD_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_HD_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_HD_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CMD_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CMD_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CMD_EN_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_OFFSET, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CLK_RATIO_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_S_OFFSET, JESD_XIP_204C_RX_MEM_RX_S_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_S_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_S_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_S_OFFSET");
			
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_DEFAULT, 0x00000100, 0x00000100, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SONIF_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SONIF_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_N_OFFSET, JESD_XIP_204C_RX_MEM_RX_N_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_N_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_N_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_N_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_NTOTAL_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_NTOTAL_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CS_OFFSET, JESD_XIP_204C_RX_MEM_RX_CS_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CS_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CS_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CS_OFFSET");
			
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET, JESD_XIP_204C_RX_MEM_RX_SCR_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_SCR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_SCR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_SCR_OFFSET");
			
			printf("JESD RX path - UC 5E 32G -LMFS -2-16-16-1 - IQ bandwidth -\n");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000001, 0x00000001, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
			write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000009, 0x00000009, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
	
		}
	} 

// JESD enable reg
static int program_enable_registers()
	{
		
		//18A
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
	
static void configure_jesd_block()
	{
		uint32_t tx_gb_empty_reg = 0;
		uint32_t tx_gb_full_reg = 0;
		uint32_t rx_gb_empty_reg = 0;
		uint32_t rx_gb_full_reg = 0;

		// function calls - Reg seq usecase
		program_rx_ip_registers();
		program_cmn_csr_registers();
		//program_rx_glue_registers();


		printf("Giving delay of 10 milli seconds \n");
		delay(10);
		program_enable_registers();

		int i,j=0;
		uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
		uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
		
		
		for(i=0; i<1; i++)
		{
			tx_gb_empty_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
			tx_gb_full_reg = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
		}
		for(j=0; j<1; j++)
		{
			rx_gb_empty_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
			rx_gb_full_reg = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
		}

		printf(" Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", tx_gb_empty_reg);
		printf(" Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", tx_gb_full_reg);
		printf(" Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", rx_gb_empty_reg);
		printf(" Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", rx_gb_full_reg);

		//program_enable_registers();
	}


int
main(int argc, const char *argv[])
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

	delay(500);
	system("frioPciWrite -F s5a1 -P 0x20000 0x14");
	system("frioPciWrite -F s5b1 -P 0x20000 0x14");
	printf("CLK Done\n");
	delay(500);
	
	init(); // Initialize the srp
	printf("RST Done\n");
	sleep(2);

	LOG_PRINT("INFO: logger beginning\n");
	
	configure_jesd_block();

	delay(1000);
	//===========================================================================
	//enable sysref for 32G usecases
	system("frioPciWrite -F s5a3 -P 0x20000 0x06"); //IP
	//system("frioPciWrite -F s5a3 -P 0x20000 0x04"); //Serial
	//system("frioPciWrite -F s5a3 -P 0x20000 0x05"); //Parallel
	system("frioPciWrite -F s5a1 -P 0x20000 0x94");
	system("frioPciWrite -F s5b1 -P 0x20000 0x94");
	printf("SYSREF Done\n");
	delay(1000);


	uint32_t read_value;
	extern void * srp;
	uint32_t error = 0;
	uint32_t write_status = 0;
	uint32_t dev_id =0;
	uint32_t dev_flags = 0;

	uint32_t value24 = 0;
	uint32_t value25 = 0;
	uint32_t value26 = 0;
	uint32_t value27 = 0;
    uint32_t value28 = 0;
	uint32_t value29 = 0;
	uint32_t value30 = 0;
	uint32_t value31 = 0;
	uint32_t value32 = 0;
	uint32_t value33 = 0;
    uint32_t value34 = 0;
	uint32_t value35 = 0;
	uint32_t value36 = 0;
	uint32_t value37 = 0;
	uint32_t value38 = 0;
	uint32_t value39 = 0;
	uint32_t value40 = 0;
	uint32_t value41 = 0;
	uint32_t value42 = 0;
	uint32_t value43 = 0;
	uint32_t value44 = 0;
	uint32_t value45 = 0;
	uint32_t stream0_buffer = 0;
	uint32_t stream1_buffer = 0;
	uint32_t stream2_buffer = 0;
	uint32_t stream3_buffer = 0;
	uint32_t stream4_buffer = 0;
	uint32_t stream5_buffer = 0;
	uint32_t stream6_buffer = 0;
	uint32_t stream7_buffer = 0;
	uint32_t stream8_buffer = 0;
	uint32_t stream9_buffer = 0;
	uint32_t stream10_buffer = 0;
	uint32_t stream11_buffer = 0;
	uint32_t stream12_buffer = 0;
	uint32_t stream13_buffer = 0;
	uint32_t stream14_buffer = 0;
	uint32_t stream15_buffer = 0;
	
	uint32_t value   = 0;
	uint32_t value1   = 0;
	uint32_t value2  = 0;
	uint32_t value3  = 0;
	uint32_t value4  = 0;
	uint32_t value5  = 0;
	uint32_t value6  = 0;
	uint32_t value7  = 0;
	uint32_t value8  = 0;
	uint32_t value9  = 0;
	uint32_t value10 = 0;
	uint32_t value11 = 0;
	uint32_t value12 = 0;
	uint32_t value13 = 0;
	uint32_t value14 = 0;
	uint32_t value15 = 0;
	uint32_t value16 = 0;
	uint32_t value17 = 0;
	uint32_t value18 = 0;
	uint32_t value19 = 0;
	uint32_t value20 = 0;
	uint32_t value21 = 0;
	uint32_t value22 = 0;
	uint32_t value23 = 0;
	

	uint32_t curr_value  = 0;
	uint32_t curr_value1  = 0;
	uint32_t curr_value2  = 0;
	uint32_t curr_value3  = 0;
	uint32_t curr_value4  = 0;
	uint32_t curr_value5  = 0;
	uint32_t curr_value6  = 0;
	uint32_t curr_value7  = 0;
	uint32_t curr_value8  = 0;
	uint32_t curr_value9  = 0;
	uint32_t curr_value10 = 0;
	uint32_t curr_value11 = 0;
	uint32_t curr_value12 = 0;
	uint32_t curr_value13 = 0;
	uint32_t curr_value14 = 0;
	uint32_t curr_value15 = 0;
	uint32_t curr_value16 = 0;
	uint32_t curr_value17 = 0;
	uint32_t curr_value18 = 0;
	uint32_t curr_value19 = 0;
	uint32_t curr_value20 = 0;
	uint32_t curr_value21 = 0;
	uint32_t curr_value22 = 0;
	uint32_t curr_value23 = 0;
	uint32_t curr_value24 = 0;
	uint32_t curr_value25 = 0;
	uint32_t curr_value26 = 0;
	uint32_t curr_value27 = 0;

	uint32_t prev_value   = 0;
	uint32_t prev_value1  = 0;
	uint32_t prev_value2  = 0;
	uint32_t prev_value3  = 0;
	uint32_t prev_value4  = 0;
	uint32_t prev_value5  = 0;
	uint32_t prev_value6  = 0;
	uint32_t prev_value7  = 0;
	uint32_t prev_value8  = 0;
	uint32_t prev_value9  = 0;
	uint32_t prev_value10 = 0;
	uint32_t prev_value11 = 0;
	uint32_t prev_value12 = 0;
	uint32_t prev_value13 = 0;
	uint32_t prev_value14 = 0;
	uint32_t prev_value15 = 0;
	uint32_t prev_value16 = 0;
	uint32_t prev_value17 = 0;
	uint32_t prev_value18 = 0;
	uint32_t prev_value19 = 0;
	uint32_t prev_value20 = 0;
	uint32_t prev_value21 = 0;
	uint32_t prev_value22 = 0;
	uint32_t prev_value23 = 0;
	uint32_t prev_value24 = 0;
	uint32_t prev_value25 = 0;
	uint32_t prev_value26 = 0;
	uint32_t prev_value27 = 0;

	uint32_t print  = 0;
	uint32_t print1  = 0;
	uint32_t print2  = 0;
	uint32_t print3  = 0;
	uint32_t print4  = 0;
	uint32_t print5  = 0;
	uint32_t print6  = 0;
	uint32_t print7  = 0;
	uint32_t print8  = 0;
	uint32_t print9  = 0;
	uint32_t print10 = 0;
	uint32_t print11 = 0;
	uint32_t print12 = 0;
	uint32_t print13 = 0;
	uint32_t print14 = 0;
	uint32_t print15 = 0;
	uint32_t print16 = 0;
	uint32_t print17 = 0;
	uint32_t print18 = 0;
	uint32_t print19 = 0;
	uint32_t print20 = 0;
	uint32_t print21 = 0;
	uint32_t print22 = 0;
	uint32_t print23 = 0;
	uint32_t print24 = 0;
	uint32_t print25 = 0;
	uint32_t print26 = 0;
	uint32_t print27 = 0;
	uint32_t count = 0;
	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};

	srp_dev_open(dev_id, dev_flags, &srp);
	
//	int i,j=0;
	//uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};
	//uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};
    uint32_t base_address_rx_glue[] = {JESDABC_M0_RX_GLUE_BASE,  JESDABC_M1_RX_GLUE_BASE,  JESDABC_M2_RX_GLUE_BASE,  JESDABC_M3_RX_GLUE_BASE};
	uint32_t base_address_cmn[] = {JESDABC_M0_CMN_CSR_BASE,  JESDABC_M1_CMN_CSR_BASE,  JESDABC_M2_CMN_CSR_BASE,  JESDABC_M3_CMN_CSR_BASE};

	
	for(i=0; i<1; i++)
	{
		value24 = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		value25 = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}
	for(j=0; j<1; j++)
	{
		value26 = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		value27 = read_reg_18a(base_address_rx[j] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}
	
	printf("\n\n");
	printf("Before jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", value24);
	printf("Before jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", value25);
	printf("Before jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", value26);
	printf("Before jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", value27);

	delay(2000);
	while(1)
	{

	value28  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");

	value32  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");

	value36  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");

	value37  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");

	printf("Present value of SH lock of Link0 is 0x%x \n",value28);
	printf("Present value of EMB lock of Link0 is 0x%x \n",value32);
	printf("Present value of SH lock loss of Link0 is 0x%x \n",value36);
	printf("Present value of EMB lock loss of Link0 is 0x%x \n",value37);
	
	i=0;
	j=0;
	for(i=0; i<1; i++)
	{
		value   = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE0_OFFSET, "ICOUNTER_REPORT_LANE0");
		value1  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE1_OFFSET, "ICOUNTER_REPORT_LANE1");
		value2  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE2_OFFSET, "ICOUNTER_REPORT_LANE2");
		value3  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE3_OFFSET, "ICOUNTER_REPORT_LANE3");
		value4  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE4_OFFSET, "ICOUNTER_REPORT_LANE4");
		value5  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE5_OFFSET, "ICOUNTER_REPORT_LANE5");
		value6  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE6_OFFSET, "ICOUNTER_REPORT_LANE6");
		value7  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE7_OFFSET, "ICOUNTER_REPORT_LANE7");
		value8  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE8_OFFSET, "ICOUNTER_REPORT_LANE8");
		value9  = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE9_OFFSET, "ICOUNTER_REPORT_LANE9");
		value10 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE10_OFFSET, "ICOUNTER_REPORT_LANE10");
		value11 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE11_OFFSET, "ICOUNTER_REPORT_LANE11");
		value12 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE12_OFFSET, "ICOUNTER_REPORT_LANE12");
		value13 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE13_OFFSET, "ICOUNTER_REPORT_LANE13");
		value14 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE14_OFFSET, "ICOUNTER_REPORT_LANE14");
		value15 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE15_OFFSET, "ICOUNTER_REPORT_LANE15");
		value16 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE16_OFFSET, "ICOUNTER_REPORT_LANE16");
		value17 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE17_OFFSET, "ICOUNTER_REPORT_LANE17");
		value18 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE18_OFFSET, "ICOUNTER_REPORT_LANE18");
		value19 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE19_OFFSET, "ICOUNTER_REPORT_LANE19");
		value20 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE20_OFFSET, "ICOUNTER_REPORT_LANE20");
		value21 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE21_OFFSET, "ICOUNTER_REPORT_LANE21");
		value22 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE22_OFFSET, "ICOUNTER_REPORT_LANE22");
		value23 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE23_OFFSET, "ICOUNTER_REPORT_LANE23");
		value26 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_RX_GB_EMPTY_REG");
		value27 = read_reg_18a(base_address_rx[i] + JESD_XIP_204C_RX_MEM_RX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_RX_GB_FULL_REG");
	}
	int j=0;
	for(j=0; j<1; j++)
	{
		value24 = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_TX_GB_EMPTY_REG");
		value25 = read_reg_18a(base_address_tx[j] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_TX_GB_FULL_REG");
	}
	if( count == 0 )
	{
		printf("\n");
		printf("\n");
	
		printf("\n");
		printf("\n");
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE0  is 0x%x \n",  value);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE1  is 0x%x \n",  value1);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE2  is 0x%x \n",  value2);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE3  is 0x%x \n",  value3);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE4  is 0x%x \n",  value4);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE5  is 0x%x \n",  value5);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE6  is 0x%x \n",  value6);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE7  is 0x%x \n",  value7);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE8  is 0x%x \n",  value8);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE9  is 0x%x \n",  value9);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE10 is 0x%x \n", value10);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE11 is 0x%x \n", value11);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE12 is 0x%x \n", value12);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE13 is 0x%x \n", value13);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE14 is 0x%x \n", value14);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE15 is 0x%x \n", value15);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE16 is 0x%x \n", value16);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE17 is 0x%x \n", value17);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE18 is 0x%x \n", value18);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE19 is 0x%x \n", value19);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE20 is 0x%x \n", value20);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE21 is 0x%x \n", value21);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE22 is 0x%x \n", value22);
		printf(" After Jesd enable value for ICOUNTER_REPORT_LANE23 is 0x%x \n", value23);
		printf(" After Jesd enable value for JL_N_TX_GB_EMPTY_REG --------is 0x%x \n", value24);
		printf(" After Jesd enable value for JL_N_TX_GB_FULL_REG ---------is 0x%x \n", value25);
		printf(" After Jesd enable value for JL_N_RX_GB_EMPTY_REG --------is 0x%x \n", value26);
		printf(" After Jesd enable value for JL_N_RX_GB_FULL_REG ---------is 0x%x \n", value27);
    }
			if(value)
			{
				curr_value = value;
				if(prev_value != curr_value)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE0 are 0x%x, 0x%x\n", prev_value, curr_value);
					print = 1;
					prev_value = curr_value;
				}
			}
			
			if(value1)
			{
				curr_value1 = value1;
				if(prev_value1 != curr_value1)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE1 are 0x%x, 0x%x\n", prev_value1, curr_value1);
					print1 = 1;
					prev_value1 = curr_value1;
				}
			}

			if(value2)
			{
				curr_value2 = value2;
				if(prev_value2 != curr_value2)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE2 are 0x%x, 0x%x\n", prev_value2, curr_value2);
					print2 = 1;
					prev_value2 = curr_value2;
				}
			}

			if(value3)
			{
				curr_value3 = value3;
				if(prev_value3 != curr_value3)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE3 are 0x%x, 0x%x\n", prev_value3, curr_value3);
					print3 = 1;
					prev_value3 = curr_value3;
				}
			}

			if(value4)
			{
				curr_value4 = value4;
				if(prev_value4 != curr_value4)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE4 are 0x%x, 0x%x\n", prev_value4, curr_value4);
					print4 = 1;
					prev_value4 = curr_value4;
				}
			}

			if(value5)
			{
				curr_value5 = value5;
				if(prev_value5 != curr_value5)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE5 are 0x%x, 0x%x\n", prev_value5, curr_value5);
					print5 = 1;
					prev_value5 = curr_value5;
				}
			}

			if(value6)
			{
				curr_value6 = value6;
				if(prev_value6 != curr_value6)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE6 are 0x%x, 0x%x\n", prev_value6, curr_value6);
					print6 = 1;
					prev_value6 = curr_value6;
				}
			}

			if(value7)
			{
				curr_value7 = value7;
				if(prev_value7 != curr_value7)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE7 are 0x%x, 0x%x\n", prev_value7, curr_value7);
					print7 = 1;
					prev_value7 = curr_value7;
				}
			}

			if(value8)
			{
				curr_value8 = value8;
				if(prev_value8 != curr_value8)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE8 are 0x%x, 0x%x\n", prev_value8, curr_value8);
					print8 = 1;
					prev_value8 = curr_value8;
				}
			}
			
			if(value9)
			{
				curr_value9 = value9;
				if(prev_value9 != curr_value9)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE9 are 0x%x, 0x%x\n", prev_value9, curr_value9);
					print9 = 1;
					prev_value9 = curr_value9;
				}
			}

			if(value10)
			{
				curr_value10 = value10;
				if(prev_value10 != curr_value10)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE10 are 0x%x, 0x%x\n", prev_value10, curr_value10);
					print10 = 1;
					prev_value10 = curr_value10;
				}
			}

			if(value11)
			{
				curr_value11 = value11;
				if(prev_value11 != curr_value11)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE11 are 0x%x, 0x%x\n", prev_value11, curr_value11);
					print11 = 1;
					prev_value11 = curr_value11;
				}
			}

			if(value12)
			{
				curr_value12 = value12;
				if(prev_value12 != curr_value12)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE12 are 0x%x, 0x%x\n", prev_value12, curr_value12);
					print12 = 1;
					prev_value12 = curr_value12;
				}
			}

			if(value13)
			{
				curr_value13 = value13;
				if(prev_value13 != curr_value13)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE13 are 0x%x, 0x%x\n", prev_value13, curr_value13);
					print13 = 1;
					prev_value13 = curr_value13;
				}
			}

			if(value14)
			{
				curr_value14 = value14;
				if(prev_value14 != curr_value14)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE14 are 0x%x, 0x%x\n", prev_value14, curr_value14);
					print14 = 1;
					prev_value14 = curr_value14;
				}
			}

			if(value15)
			{
				curr_value15 = value15;
				if(prev_value15 != curr_value15)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE15 are 0x%x, 0x%x\n", prev_value15, curr_value15);
					print15 = 1;
					prev_value15 = curr_value15;
				}
			}

			if(value16)
			{
				curr_value16 = value16;
				if(prev_value16 != curr_value16)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE16 are 0x%x, 0x%x\n", prev_value16, curr_value16);
					print16 = 1;
					prev_value16 = curr_value16;
				}
			}
			
			if(value17)
			{
				curr_value17 = value17;
				if(prev_value17 != curr_value17)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE17 are 0x%x, 0x%x\n", prev_value17, curr_value17);
					print17 = 1;
					prev_value17 = curr_value17;
				}
			}
			
			if(value18)
			{
				curr_value18 = value18;
				if(prev_value18 != curr_value18)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE18 are 0x%x, 0x%x\n", prev_value18, curr_value18);
					print18 = 1;
					prev_value18 = curr_value18;
				}
			}

			if(value19)
			{
				curr_value19 = value19;
				if(prev_value19 != curr_value19)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE19 are 0x%x, 0x%x\n", prev_value19, curr_value19);
					print19 = 1;
					prev_value19 = curr_value19;
				}
			}

			if(value20)
			{
				curr_value20 = value20;
				if(prev_value20 != curr_value20)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE20 are 0x%x, 0x%x\n", prev_value20, curr_value20);
					print20 = 1;
					prev_value20 = curr_value20;
				}
			}

			if(value21)
			{
				curr_value21 = value21;
				if(prev_value21 != curr_value21)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE21 are 0x%x, 0x%x\n", prev_value21, curr_value21);
					print21 = 1;
					prev_value21 = curr_value21;
				}
			}

			if(value22)
			{
				curr_value22 = value22;
				if(prev_value22 != curr_value22)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE22 are 0x%x, 0x%x\n", prev_value22, curr_value22);
					print22 = 1;
					prev_value22 = curr_value22;
				}
			}

			if(value23)
			{
				curr_value23 = value23;
				if(prev_value23 != curr_value23)
				{
				printf(" \nprevious and current value for ICOUNTER_REPORT_LANE23 are 0x%x, 0x%x\n", prev_value23, curr_value23);
					print23 = 1;
					prev_value23 = curr_value23;
				}
			}

			if(value24)
			{
				curr_value24 = value24;
				if(prev_value24 != curr_value24)
				{
				printf(" \nprevious and current value for JL_N_TX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_value24, curr_value24);
					print24 = 1;
					prev_value24 = curr_value24;
				}
			}

			if(value25)
			{
				curr_value25 = value25;
				if(prev_value25 != curr_value25)
				{
				printf(" \nprevious and current value for JL_N_TX_GB_FULL_REG are 0x%x, 0x%x\n", prev_value25, curr_value25);
					print25 = 1;
					prev_value25 = curr_value25;
				}
			}
			
			if(value26)
			{
				curr_value26 = value26;
				if(prev_value26 != curr_value26)
				{
				printf(" \nprevious and current value for JL_N_RX_GB_EMPTY_REG are 0x%x, 0x%x\n", prev_value26, curr_value26);
					print26 = 1;
					prev_value26 = curr_value26;
				}
			}
			
			if(value27)
			{
				curr_value27 = value27;
				if(prev_value27 != curr_value27)
				{
				printf(" \nprevious and current value for JL_N_RX_GB_FULL_REG are 0x%x, 0x%x\n", prev_value27, curr_value27);
					print27 = 1;
					prev_value27 = curr_value27;
				}
			}
					
			if((print == 1) || (print1 == 1) || (print2 == 1) || (print3 == 1) || (print4 == 1) || (print5 == 1) || (print6 == 1) || (print7 == 1) || (print8 == 1) || (print9 == 1) || (print10 == 1) || (print11 == 1) || (print12 == 1) || (print13 == 1) || (print14 == 1) || (print15 == 1) || (print16 == 1) || (print17 == 1) || (print18 == 1) || (print19 == 1) || (print20 == 1) || (print21 == 1) || (print22 == 1) || (print23 == 1) || (print24 == 1) || (print25 == 1) || (print26 == 1) || (print27 == 1))
			{
				printf("\n\n");
				printf("\n");
				printf("\n\n");
				print   = 0;
				print1  = 0;
				print2  = 0;
				print3  = 0;
				print4  = 0;
				print5  = 0;
				print6  = 0;
				print7  = 0;
				print8  = 0;
				print9  = 0;
				print10 = 0;
				print11 = 0;
				print12 = 0;
				print13 = 0;
				print14 = 0;
				print15 = 0;
				print16 = 0;
				print17 = 0;
				print18 = 0;
				print19 = 0;
				print20 = 0;
				print21 = 0;
				print22 = 0;
				print23 = 0;
				print24 = 0;
				print25 = 0;
				print26 = 0;
				print27 = 0;
				count   = 1;
			}

			else
			{
				if((count % 3000) == 0)
				printf(" no change in errors and no change in fifo empty or full at both rx and tx \n");
			}

			
			//if((count % 1000) == 0)
			//	printf("########count is %d \n",count);
			//delay(10000);
			delay(1000);
			count = count + 1;
	}
	
return rv;


}   // main ends


