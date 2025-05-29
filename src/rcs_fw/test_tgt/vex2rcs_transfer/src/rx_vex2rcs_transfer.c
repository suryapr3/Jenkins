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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */



#include "../inc/vex2rcs_transfer.h"
#include "com_event.h"
#include "rcs_gpreg.h"
#include "crux_intf.h"
#include "nsip_hbi.h"



volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));

uint32_t const SIZE = 32;
uint32_t dram_rxdata[SIZE]  __attribute__((section(".dram0.data")));

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
int main(int argc, char **argv)
{
	int waitCnt = 0;
	xthal_enable_interrupts();

	// wait for handshake from tx core
	do
	{
		/*waitCnt++;
		if(waitCnt > 0xFFFFFFF)
		{
			rsm_com_shared_flag = 0xDEADC000; // core0 didnt finish, host to check and print error
			return 0;
		}*/
	} while (rsm_rx_shared_flag != 0xC1C1);
	rsm_rx_shared_flag=0;

	vex2rx_transfer_test();

	// update RSM flag for handshake with cal core
	rsm_tx_shared_flag = 0xC2C2;
	
	rsm_com_shared_flag = 0xC0C1C2; // temp hack for rx test, should be done in after cal test 

	// cal core will be triggered by host
	return (0);
}

uint32_t vex2rx_transfer_test()
{

	int waitCnt;

	crux_intf_rdata0_r_reg_t crux_rdata0;
	crux_intf_rdata1_r_reg_t crux_rdata1;
	crux_intf_rdata2_r_reg_t crux_rdata2;
	crux_intf_rdata3_r_reg_t crux_rdata3;

	crux_intf_rx_pop_reg_t crux_rx_pop;


	// pop the data - 1024 bits for tx core
	// 512 bits per pop
	crux_rx_pop =  *CRUX_INTF_RX_POP_REG;
	rsm_rx_shared_flag = crux_rx_pop.POP; // else above line may get optimised by the compiler?
#if 1
	// wait
	// there is no way to know when the POP has been completed,
	//POP needs to load 4, 128 bit registers, so obviously this may take some time
	// raise a HSD
	for(waitCnt = 0; waitCnt< 0xFF; waitCnt++)
	{
		rsm_com_shared_flag = waitCnt;
	}
#endif
	// read CRUX_INTF_CRUX_RDATA0_R_ADR
	crux_rdata0 = *CRUX_INTF_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_RDATA3_R_REG;

	// copy CRUX register contents to DRAM
	dram_rxdata[0] = crux_rdata0.DATA0;
	dram_rxdata[1] = crux_rdata0.DATA1;
	dram_rxdata[2] = crux_rdata0.DATA2;
	dram_rxdata[3] = crux_rdata0.DATA3;

	dram_rxdata[4] = crux_rdata1.DATA0;
	dram_rxdata[5] = crux_rdata1.DATA1;
	dram_rxdata[6] = crux_rdata1.DATA2;
	dram_rxdata[7] = crux_rdata1.DATA3;

	dram_rxdata[8] = crux_rdata2.DATA0;
	dram_rxdata[9] = crux_rdata2.DATA1;
	dram_rxdata[10] = crux_rdata2.DATA2;
	dram_rxdata[11] = crux_rdata2.DATA3;

	dram_rxdata[12] = crux_rdata3.DATA0;
	dram_rxdata[13] = crux_rdata3.DATA1;
	dram_rxdata[14] = crux_rdata3.DATA2;
	dram_rxdata[15] = crux_rdata3.DATA3;

	// next pop, 512 bits per pop
	crux_rx_pop =  *CRUX_INTF_RX_POP_REG;
	rsm_rx_shared_flag = crux_rx_pop.POP;
	
#if 1
	// wait
	for(waitCnt = 0; waitCnt< 0xFF; waitCnt++)
	{
		rsm_com_shared_flag = waitCnt;
	}
#endif
	// read CRUX_INTF_CRUX_RDATA0_R_ADR
	crux_rdata0 = *CRUX_INTF_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_RDATA3_R_REG;

	// copy CRUX register contents to DRAM
	dram_rxdata[16] = crux_rdata0.DATA0;
	dram_rxdata[17] = crux_rdata0.DATA1;
	dram_rxdata[18] = crux_rdata0.DATA2;
	dram_rxdata[19] = crux_rdata0.DATA3;

	dram_rxdata[20] = crux_rdata1.DATA0;
	dram_rxdata[21] = crux_rdata1.DATA1;
	dram_rxdata[22] = crux_rdata1.DATA2;
	dram_rxdata[23] = crux_rdata1.DATA3;

	dram_rxdata[24] = crux_rdata2.DATA0;
	dram_rxdata[25] = crux_rdata2.DATA1;
	dram_rxdata[26] = crux_rdata2.DATA2;
	dram_rxdata[27] = crux_rdata2.DATA3;

	dram_rxdata[28] = crux_rdata3.DATA0;
	dram_rxdata[29] = crux_rdata3.DATA1;
	dram_rxdata[30] = crux_rdata3.DATA2;
	dram_rxdata[31] = crux_rdata3.DATA3;

	return 0;
}
