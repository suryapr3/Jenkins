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

uint32_t const SIZE = 32;
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));

volatile int flitCount = 0;

//volatile uint32_t rsm_txdata[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t dram_txdata[SIZE]  __attribute__((section(".dram0.data")));


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
	xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();

	// wait for memory zeroise

	// clear all flags
	rsm_ax_shared_flag=0;
	rsm_tx_shared_flag = 0;
	rsm_rx_shared_flag = 0;
	rsm_cal_shared_flag = 0;
	rsm_com_shared_flag = 0;

	// run tests
	vex2tx_transfer_test();

	// Trigger RX core to read 1K from crux registers
	rsm_rx_shared_flag = 0xC1C1; // enable this line for all cores and remove below line
	rsm_ax_shared_flag = 1;
	rsm_com_shared_flag = 0xC0C1C2; // temp hack for tx test , move to rx
	// host will verify data once rx and cal done reading crux data
	rsm_ax_shared_flag = 11;
    return (0);
}

uint32_t vex2tx_transfer_test()
{
	int waitCnt;
	

	crux_intf_rdata0_r_reg_t crux_rdata0;
	crux_intf_rdata1_r_reg_t crux_rdata1;
	crux_intf_rdata2_r_reg_t crux_rdata2;
	crux_intf_rdata3_r_reg_t crux_rdata3;

	nsip_hbi_b2h_csr_flit_cnt_reg_t b2h_flit_count_reg;
	crux_intf_rx_pop_reg_t crux_rx_pop;
	
	rsm_ax_shared_flag = 3;
	
	//return 0;

	// wait for flit count to be non zero
	// i.e VEX has written data to B2H interface
	do
	{
		b2h_flit_count_reg = *(NSIP_HBI_B2H_CSR_FLIT_CNT_REG(RCS_CRUX_NSIP_HBI_BASE));
		//rsm_tx_shared_flag = *(( uint32_t*) 0x274014);
		flitCount = b2h_flit_count_reg.FLIT_COUNT;
		waitCnt++;
		if(waitCnt > 1000)
		{
			rsm_com_shared_flag = 0xDEADC000; // VEX didnt write data, host to check and print error
			return 0;
		}
	} while (flitCount!= 0x6); // wait till VEX writes 6 FLITS*/
	//while(1);
	rsm_ax_shared_flag = 4;
	// pop the data - 1024 bits for tx core
	// 512 bits per pop
	// POP bit is read only in 18A, read the register
	// crux_rx_pop.POP = 0x1;
	
	//*CRUX_INTF_CRUX_RX_POP_REG = crux_rx_pop;
#if 1
	// wait
	// there is no way to know when the POP has been completed,
	//POP needs to load 4, 128 bit registers, so obviously this may take some time
	// raise a HSD
	for(waitCnt = 0; waitCnt< 0xFF; waitCnt++)
	{
		rsm_ax_shared_flag = waitCnt;
	}
#endif
	crux_rx_pop =  *CRUX_INTF_RX_POP_REG;
	rsm_ax_shared_flag = crux_rx_pop.POP; // else above line may get optimised by the compiler?
	for(waitCnt = 0; waitCnt< 0xFFF; waitCnt++)
	{
		rsm_ax_shared_flag = waitCnt;
	}
	//while(1);
	rsm_ax_shared_flag = 5;
	// read CRUX_INTF_CRUX_RDATA0_R_ADR
	crux_rdata0 = *CRUX_INTF_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_RDATA3_R_REG;

	// copy CRUX register contents to DRAM
	dram_txdata[0] = crux_rdata0.DATA0;
	dram_txdata[1] = crux_rdata0.DATA1;
	dram_txdata[2] = crux_rdata0.DATA2;
	dram_txdata[3] = crux_rdata0.DATA3;

	dram_txdata[4] = crux_rdata1.DATA0;
	dram_txdata[5] = crux_rdata1.DATA1;
	dram_txdata[6] = crux_rdata1.DATA2;
	dram_txdata[7] = crux_rdata1.DATA3;

	dram_txdata[8] = crux_rdata2.DATA0;
	dram_txdata[9] = crux_rdata2.DATA1;
	dram_txdata[10] = crux_rdata2.DATA2;
	dram_txdata[11] = crux_rdata2.DATA3;

	dram_txdata[12] = crux_rdata3.DATA0;
	dram_txdata[13] = crux_rdata3.DATA1;
	dram_txdata[14] = crux_rdata3.DATA2;
	dram_txdata[15] = crux_rdata3.DATA3;

	// next pop, 512 bits per pop
	//crux_rx_pop.POP = 0x1;
	//*CRUX_INTF_CRUX_RX_POP_REG = crux_rx_pop;
	crux_rx_pop =  *CRUX_INTF_RX_POP_REG;
	rsm_tx_shared_flag = crux_rx_pop.POP;

#if 1
	// wait
	for(waitCnt = 0; waitCnt< 0xFF; waitCnt++)
	{
		rsm_ax_shared_flag = waitCnt;
	}
#endif
	// read CRUX_INTF_CRUX_RDATA0_R_ADR
	crux_rdata0 = *CRUX_INTF_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_RDATA3_R_REG;

	// copy CRUX register contents to DRAM
	dram_txdata[16] = crux_rdata0.DATA0;
	dram_txdata[17] = crux_rdata0.DATA1;
	dram_txdata[18] = crux_rdata0.DATA2;
	dram_txdata[19] = crux_rdata0.DATA3;

	dram_txdata[20] = crux_rdata1.DATA0;
	dram_txdata[21] = crux_rdata1.DATA1;
	dram_txdata[22] = crux_rdata1.DATA2;
	dram_txdata[23] = crux_rdata1.DATA3;

	dram_txdata[24] = crux_rdata2.DATA0;
	dram_txdata[25] = crux_rdata2.DATA1;
	dram_txdata[26] = crux_rdata2.DATA2;
	dram_txdata[27] = crux_rdata2.DATA3;

	dram_txdata[28] = crux_rdata3.DATA0;
	dram_txdata[29] = crux_rdata3.DATA1;
	dram_txdata[30] = crux_rdata3.DATA2;
	dram_txdata[31] = crux_rdata3.DATA3;
	return 0;
}



