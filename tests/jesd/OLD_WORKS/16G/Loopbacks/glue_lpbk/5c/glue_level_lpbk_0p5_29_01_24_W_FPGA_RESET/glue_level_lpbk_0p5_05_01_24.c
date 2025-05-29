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
	* @file    glue_level_lpbk_0p5_05_01_24.c
	* @brief   Code for Glue level external loopback - JESD RX glue to JESD TX glue
	* @details 1. Configuration of JESD TX IP, JESD TX glue logic, JESD RX IP,JESD RX glue registers
	2.Configure loopback register 
	* @TC Description:
	1. Data is sent from DNRT Tx to JESD RX IP and received at JESD Rx glue
	2. Data is looped back from JESD Rx glue to JESD Tx glue
	3. From JESD TX IP the data is streamed and captured instantaneously at DNRT RX.
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
	#include <srp_vex.h>
	#include "srp_block_ids.h"
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
	int program_rx_ip_registers();
	int program_rx_glue_registers();
	int program_cmn_csr_registers();
	int program_enable_registers();
	//int program_bfn_registers();

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

	//Added by Aditya for SH & EMB lock, error checks on 8th Jan 2024
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
	uint32_t value28 = 0;
	uint32_t value32 = 0;
	uint32_t value36 = 0;
	uint32_t value37 = 0;
	uint32_t value80 = 0;
	uint32_t value81 = 0;
	uint32_t value82 = 0;
	uint32_t value83 = 0;
	uint32_t value84 = 0;
	uint32_t value85 = 0;
	uint32_t value86 = 0;
	uint32_t value87 = 0;
	uint32_t value88 = 0;
	delay(500);
	system("frioPciWrite -F s6b3 -P 0x20000 0xa");
	system("frioPciWrite -F s6b3 -P 0x20000 0xb");

	/* 	delay(5000);
	//enable clock
	system("frioPciWrite -F s5a1 -P 0x20000 0x10");
	system("frioPciWrite -F s5b1 -P 0x20000 0x10");
	delay(500);
	printf("CLOCK Enabled before starting DUT \n");
	*/
	// initialize DUT
	init();
	delay(100);
	//enable clock
	system("frioPciWrite -F s5a1 -P 0x20000 0x10");
	system("frioPciWrite -F s5b1 -P 0x20000 0x10");
	delay(500);
	printf("CLOCK Enabled before starting DUT \n");
	delay(500);
	//=======================================================
	//=======================================================
	//clear vex memory
	printf("\n########Starting to clear vex mem from 0-10\n\n");
	vex_mem_clear(0, srp);
	vex_mem_clear(1, srp);
	vex_mem_clear(2, srp);
	vex_mem_clear(3, srp);
	vex_mem_clear(4, srp);
	vex_mem_clear(5, srp);
	vex_mem_clear(6, srp);
	vex_mem_clear(7, srp);
	printf("\n########Done clearing vex mem from 0-7\n\n");
	//=======================================================
	delay(100);
	//=======================================================

	//function calls - glue level lpbk - config Tx IP,Rx ip,Rx glue,Tx Glue,cmn csr registers
	program_tx_ip_registers();
	program_rx_ip_registers();
	program_rx_glue_registers();
	program_cmn_csr_registers();
	program_tx_glue_registers();
	//program_bfn_registers();

	printf("Giving delay of 10 milli seconds \n");
	delay(10);

	//enable loopback - glue level - jesd rx glue to jesd tx glue - lpbk ctl - 0x2
	int i=0;
	uint32_t base_address_cmn[] = {JESDABC_M0_CMN_CSR_BASE,  JESDABC_M1_CMN_CSR_BASE,  JESDABC_M2_CMN_CSR_BASE,  JESDABC_M3_CMN_CSR_BASE};
	printf("JESD CMN CSR CONFIG : program_cmn_csr_registers \n");
	//for(i=0; i<sizeof(base_address_cmn) / sizeof(base_address_cmn[0]); i++)
	for(i=0; i<1; i++)
	{ 		
	write_read_expect_18a(base_address_cmn[i]+JESDABC_CMN_CSR_MEM_LPBK_CTL_OFFSET, JESDABC_CMN_CSR_MEM_LPBK_CTL_DEFAULT, 0x2, 0x2, JESDABC_CMN_CSR_MEM_LPBK_CTL_RD_MASK, JESDABC_CMN_CSR_MEM_LPBK_CTL_WR_MASK, "JESDABC_CMN_CSR_MEM_LPBK_CTL_OFFSET");
	}
	delay(10);

	/* open the core, first function to call before initiating any read/write */
	srp_dev_open(dev_id, dev_flags, &srp);

	int j=0;	

	uint32_t base_address_tx[] = {JESDABC_M0_XIP_204C_TX_BASE,  JESDABC_M1_XIP_204C_TX_BASE,  JESDABC_M2_XIP_204C_TX_BASE,  JESDABC_M3_XIP_204C_TX_BASE};

	uint32_t base_address_rx[] = {JESDABC_M0_XIP_204C_RX_BASE,  JESDABC_M1_XIP_204C_RX_BASE,  JESDABC_M2_XIP_204C_RX_BASE,  JESDABC_M3_XIP_204C_RX_BASE};


	for(j=0; j<1; j++)
	{
	tx_gb_empty_st = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_EMPTY_STATUS_OFFSET, "JL_N_tx_gb_empty_st_REG");
	tx_gb_full_st = read_reg_18a(base_address_tx[i] + JESD_XIP_204C_TX_MEM_TX_GEARBOX_FULL_STATUS_OFFSET, "JL_N_tx_gb_full_st_REG");
	}

	printf("\n\n");
	printf("Before jesd enable value for JL_N_tx_gb_empty_st_REG --------is 0x%x \n", tx_gb_empty_st);
	printf("Before jesd enable value for JL_N_tx_gb_full_st_REG ---------is 0x%x \n", tx_gb_full_st);

	// JESD IP en 
	program_enable_registers();

	int loop = 0;
	while(loop < 1)
	{
	//INT STATUS -if jesd 204c and rx cfg en  
	value81  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_MASK_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_MASK");
	value82  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_STATUS_OFFSET, "JESD_XIP_204C_RX_MEM_RX_CORE_INTERRUPT_STATUS");

	// test mode error -if jesd 204c and rx cfg en 
	value80  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE_OFFSET, "JESD_XIP_204C_RX_MEM_RX_TL_TEST_MODE");

	value28  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_STATUS");
	value32  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_STATUS");
	value36  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SH_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_SH_LOCK_LOSS_STATUS");
	value37  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_EMB_LOCK_LOSS_STATUS_OFFSET, "JESD_XIP_RX_MEM_JL_EMB_LOCK_LOSS_STATUS");
	//err_rpt_reg -if jesd 204c and rx cfg en 
	value83  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG0_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG0");
	value84  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG1_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG1");
	value85  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG2_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG2");
	value86  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG3_OFFSET, "JESD_XIP_204C_RX_MEM_RX_ERROR_REPORT_LANE_REG3");

	//lemc boundary phase TODO: can these be predicted?-if jesd 204c and rx cfg en 
	value87  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_LEMC_BOUNDARY_PHASE_OFFSET, "JESD_XIP_204C_RX_MEM_RX_LEMC_BOUNDARY_PHASE");

	//Sysref-  One shot sysref / periodic sysre -if jesd 204c and rx cfg en 
	value88  = read_reg_18a(base_address_rx[0] + JESD_XIP_204C_RX_MEM_RX_SYSREF_COUNTER_STATUS_OFFSET, "JESD_XIP_204C_RX_MEM_RX_SYSREF_COUNTER_STATUS");
	printf("Present value of RX_TL_TEST_MODE of Link0 is 0x%x \n",value80);
	printf("Present value of RX_CORE_INTERRUPT_MASK of Link0 is 0x%x \n",value81);
	printf("Present value of RX_CORE_INTERRUPT_STATUS of Link0 is 0x%x \n",value82);

	printf("\nPresent value of SH lock of Link0 is 0x%x \n",value28);
	printf("Present value of EMB lock of Link0 is 0x%x \n",value32);
	printf("Present value of SH lock loss of Link0 is 0x%x \n",value36);
	printf("Present value of EMB lock loss of Link0 is 0x%x \n",value37);

	printf("Present value of RX_ERROR_REPORT_LANE_REG0 of Link0 is 0x%x \n",value83);
	printf("Present value of RX_ERROR_REPORT_LANE_REG1 of Link0 is 0x%x \n",value84);
	printf("Present value of RX_ERROR_REPORT_LANE_REG2 of Link0 is 0x%x \n",value85);
	printf("Present value of RX_ERROR_REPORT_LANE_REG3 of Link0 is 0x%x \n",value86);
	printf("Present value of RX_LEMC_BOUNDARY_PHASE of Link0 is 0x%x \n",value87);
	printf("Present value of RX_SYSREF_COUNTER_STATUS of Link0 is 0x%x \n",value88);
	int m=0;
	for(m=0; m<1; m++)
	{
	value   = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE0_OFFSET, "ICOUNTER_REPORT_LANE0");
	value1  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE1_OFFSET, "ICOUNTER_REPORT_LANE1");
	value2  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE2_OFFSET, "ICOUNTER_REPORT_LANE2");
	value3  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE3_OFFSET, "ICOUNTER_REPORT_LANE3");
	value4  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE4_OFFSET, "ICOUNTER_REPORT_LANE4");
	value5  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE5_OFFSET, "ICOUNTER_REPORT_LANE5");
	value6  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE6_OFFSET, "ICOUNTER_REPORT_LANE6");
	value7  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE7_OFFSET, "ICOUNTER_REPORT_LANE7");
	value8  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE8_OFFSET, "ICOUNTER_REPORT_LANE8");
	value9  = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE9_OFFSET, "ICOUNTER_REPORT_LANE9");
	value10 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE10_OFFSET, "ICOUNTER_REPORT_LANE10");
	value11 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE11_OFFSET, "ICOUNTER_REPORT_LANE11");
	value12 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE12_OFFSET, "ICOUNTER_REPORT_LANE12");
	value13 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE13_OFFSET, "ICOUNTER_REPORT_LANE13");
	value14 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE14_OFFSET, "ICOUNTER_REPORT_LANE14");
	value15 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE15_OFFSET, "ICOUNTER_REPORT_LANE15");
	value16 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE16_OFFSET, "ICOUNTER_REPORT_LANE16");
	value17 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE17_OFFSET, "ICOUNTER_REPORT_LANE17");
	value18 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE18_OFFSET, "ICOUNTER_REPORT_LANE18");
	value19 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE19_OFFSET, "ICOUNTER_REPORT_LANE19");
	value20 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE20_OFFSET, "ICOUNTER_REPORT_LANE20");
	value21 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE21_OFFSET, "ICOUNTER_REPORT_LANE21");
	value22 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE22_OFFSET, "ICOUNTER_REPORT_LANE22");
	value23 = read_reg_18a(base_address_rx[m]  + JESD_XIP_204C_RX_MEM_RX_ICOUNTER_REPORT_LANE23_OFFSET, "ICOUNTER_REPORT_LANE23");
	}

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

	delay(1000);
	//enable sysref
	system("frioPciWrite -F s5a3 -P 0x20000 0x02");
	system("frioPciWrite -F s5a1 -P 0x20000 0x90");
	system("frioPciWrite -F s5b1 -P 0x20000 0x90");
	printf("SYSREF Done\n");
	}

	printf("\n");
	printf("\n");
	system("srpRead 0x63.2.0x30000 64");
	printf("\n");
	system("srpRead 0x63.3.0x30200 64");
	printf("\n");
	system("srpRead 0x63.4.0x30400 64");
	printf("\n");
	system("srpRead 0x63.5.0x30600 64");
	printf("\n");
	system("srpRead 0x63.6.0x30800 64");
	printf("\n");
	system("srpRead 0x63.7.0x31000 64");
	printf("\n");
	system("srpRead 0x63.8.0x31200 64");
	printf("\n");
	system("srpRead 0x63.9.0x31400 64");

	}

	void delay(unsigned int milliseconds)
	{

	clock_t start = clock();

	while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
	}

	// JESD RX IP reg
	int program_rx_ip_registers()
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
	write_read_expect_18a(base_address_rx[i]+JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_DEFAULT, 0x00000000, 0x00000000, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_CRC12_EN_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_CRC12_EN_OFFSET");
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

	printf("JESD RX path - UC 5B -LMFS -4-16-8-1 - IQ bandwidth \n");
	write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_L_OFFSET, JESD_XIP_204C_RX_MEM_RX_L_REG_DEFAULT, 0x00000003, 0x00000003, JESD_XIP_204C_RX_MEM_RX_L_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_L_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_L_OFFSET");
	write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_M_OFFSET, JESD_XIP_204C_RX_MEM_RX_M_REG_DEFAULT, 0x0000000f, 0x0000000f, JESD_XIP_204C_RX_MEM_RX_M_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_M_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_M_OFFSET");
	write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_F_OFFSET, JESD_XIP_204C_RX_MEM_RX_F_REG_DEFAULT, 0x00000007, 0x00000007, JESD_XIP_204C_RX_MEM_RX_F_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_F_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_F_OFFSET");

	write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_DEFAULT, 0x00000005, 0x00000005, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_EMB_ERR_OFFSET");
	write_read_expect_18a(JESDABC_M0_XIP_204C_RX_BASE+JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_DEFAULT, 0x00000005, 0x00000005, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_RD_MASK, JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_REG_WR_MASK, "JESD_XIP_204C_RX_MEM_RX_THRESH_SH_ERR_OFFSET");
	}
	}	

	// JESD RX glue reg
	int program_rx_glue_registers()
	{
	int i=0;
	uint32_t base_address_rx_glue[] = {JESDABC_M0_RX_GLUE_BASE,  JESDABC_M1_RX_GLUE_BASE,  JESDABC_M2_RX_GLUE_BASE,  JESDABC_M3_RX_GLUE_BASE};
	printf("JESD RX GLUE CONFIG : program_rx_glue_registers \n");
	//for(i=0; i<sizeof(base_address_rx_glue) / sizeof(base_address_rx_glue[0]); i++)
	for(i=0; i<1; i++)
	{ 
	//enabling for 8 streams, 5/1/24
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL0_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000040, 0x00000040, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL1_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000080, 0x00000080, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL2_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000000c0, 0x000000c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL3_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000100, 0x00000100, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL4_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000140, 0x00000140, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL5_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x00000180, 0x00000180, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL6_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_DEFAULT, 0x000001c0, 0x000001c0, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_WR_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_WR_MEM_TBL7_OFFSET");

	//enabling for 8 streams, 5/1/24
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000000, 0x00000000, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL0_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000240, 0x00000240, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL1_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000480, 0x00000480, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL2_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x000006c0, 0x000006c0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL3_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000900, 0x00000900, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL4_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000b40, 0x00000b40, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL5_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000d80, 0x00000d80, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL6_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_DEFAULT, 0x00000fc0, 0x00000fc0, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_RD_MASK, JESDABC_RX_GLUE_MEM_RD_MEM_TBL_WR_MASK, "JESDABC_RX_GLUE_MEM_RD_MEM_TBL7_OFFSET");


	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_DEFAULT, 0x00000001, 0x00000001, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_RD_MASK, JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_WR_MASK, "JESDABC_RX_GLUE_MEM_RX_GLUE_SONI_OFFSET");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STRM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STRM_CFG_DEFAULT, 0x000000e8, 0x000000e8, JESDABC_RX_GLUE_MEM_STRM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STRM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STRM_ID_EN");
	write_read_expect_18a(base_address_rx_glue[i]+JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET, JESDABC_RX_GLUE_MEM_STREAM_CFG_DEFAULT, 0x0000003f, 0x0000003f, JESDABC_RX_GLUE_MEM_STREAM_CFG_RD_MASK, JESDABC_RX_GLUE_MEM_STREAM_CFG_WR_MASK, "JESDABC_RX_GLUE_MEM_STREAM_CFG_OFFSET");
	}
	}

	// JESD TX IP reg
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
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR1_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00001000, 0x00001000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR1_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR2_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00002000, 0x00002000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR2_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR3_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00003000, 0x00003000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR3_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR4_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00004000, 0x00004000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR4_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR5_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00005000, 0x00005000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR5_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR6_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00006000, 0x00006000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR6_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR7_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_DEFAULT, 0x00007000, 0x00007000, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_ADDR7_OFFSET");

	//changing to 4kb per stream 0x00000fff
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE0_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE0_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE1_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE1_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE2_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE2_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE3_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE3_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE4_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE4_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE5_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE5_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE6_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE6_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE7_OFFSET, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_DEFAULT, 0x00000fff, 0x00000fff, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_ID_MEM_SIZE7_OFFSET");

	// 8 stream changing to 1 memory blocks =4kb - 8*4 =32kb -> 0x1
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_OFFSET, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_RD_MASK, JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_WR_MASK, "JESDABC_TX_GLUE_MEM_STRM_MEM_INST_CNT_OFFSET");

	// 8 stream using 8 buffers - 0x000000ff 
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_OFFSET, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_DEFAULT, 0x000000ff, 0x000000ff, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_RD_MASK, JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_NUM_BUFFER_SETS_USED_OFFSET");

	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_CONV_DP_CFG_OFFSET, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_DEFAULT, 0x00000030, 0x00000030, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_CONV_DP_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_CONV_DP_CFG_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_RD_CFG_OFFSET, JESDABC_TX_GLUE_MEM_RD_CFG_DEFAULT, 0x0000000f, 0x0000000f, JESDABC_TX_GLUE_MEM_RD_CFG_RD_MASK, JESDABC_TX_GLUE_MEM_RD_CFG_WR_MASK, "JESDABC_TX_GLUE_MEM_RD_CFG_OFFSET");

	// trig 0 - tsb level , trig1 - after trig 0 
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_DEFAULT, 0x00000120, 0x00000120, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_REG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_DATAPATH_EN_OFFSET");

	//Each stream 0x80000fff -> fff trig fill level size -4kb,not triggering on half full (2kb), trigger en 
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_DEFAULT, 0xc00007ff, 0xc00007ff, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_RD_MASK, JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_REG_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_TSB_TRIG_EN_OFFSET");

	// cfg update - twice ? 
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET");

	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_OFFSET, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_DEFAULT, 0x00000000, 0x00000000, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_RD_MASK, JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_WR_MASK, "JESDABC_TX_GLUE_MEM_PHM_FOVR_EN_OFFSET");
	write_read_expect_18a(base_address_tx_glue[i]+JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_DEFAULT, 0x00000001, 0x00000001, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_RD_MASK, JESDABC_TX_GLUE_MEM_TX_CFG_UPD_WR_MASK, "JESDABC_TX_GLUE_MEM_TX_CFG_UPD_OFFSET");
	}
	}

	/*
	// JESD BFN reg
	int program_bfn_registers()
	{
	printf("JESD BFN EVENT CONFIG : program_bfn_registers \n");
	for (core_number=0; core_number <= 1; core_number++)
	{
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_ISYNC_CTRL_OFFSET, core_number,JESD_JESDABC_BFN_EVENTS_ISYNC_CTRL,0x00000002,0x00000002,JESD_JESDABC_BFN_EVENTS_ISYNC_CTRL_RD_MASK,JESD_JESDABC_BFN_EVENTS_ISYNC_CTRL_WR_MASK,"JESD_JESDABC_BFN_EVENTS_ISYNC_CTRL");
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_ISYNC_TEN_MS_CNT_OFFSET, core_number,JESD_JESDABC_BFN_EVENTS_ISYNC_TEN_MS_CNT,0x00004000,0x00004000,JESD_JESDABC_BFN_EVENTS_ISYNC_TEN_MS_CNT_RD_MASK,JESD_JESDABC_BFN_EVENTS_ISYNC_TEN_MS_CNT_WR_MASK,"JESD_JESDABC_BFN_EVENTS_ISYNC_TEN_MS_CNT");

	for (i=0; i <= 7; i++)
	{
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_DEFAULT,0x0000000d,0x0000000d,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_CONFIG");
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_DEFAULT,0x00000400,0x00000400,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_INCR");
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_DEFAULT,0x00000400,0x00000400,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_START");

	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_DEFAULT,0x0000000d,0x0000000d,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_CONFIG_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_CONFIG");
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_DEFAULT,0x00000400,0x00000400,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_INCR_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_INCR");
	write_read_expect_18a(JESD_JESDBFN_EVENTS_BASE + JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START(i)_OFFSET, JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_DEFAULT,0x000004c8,0x000004c8,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_RD_MASK,JESDABC_BFN_EVENTS_MEM_BFN_EVENTS_BFNE_START_WR_MASK,"JESD_JESDABC_BFN_EVENTS_BFNE_START");
	}
	}
	}
	*/ 

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

