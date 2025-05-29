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


#include "dcode_core_wr_pcie_rd.h"
#include "com_event.h"




volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));

#define DRAM_MEM_SIZE 0x1000

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
uint32_t pattern = 0x5A5A5A5A;

uint32_t write_dram[DRAM_MEM_SIZE]  __attribute__((section(".dram0.data")));

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
int main(int argc, char **argv)
{
	xthal_enable_interrupts();
	dcode_tests();
	// update RSM flag for handshake with host code
	rsm_cal_shared_flag = 0x5566;
    return (0);
}
int8_t dcode_tests()
{

	dcode_wr_core_rd_pcie_tests(pattern);

    return 0;
}


int8_t dcode_wr_core_rd_pcie_tests(int32_t pattern)
{
	int32_t dataCnt = 0;

	for (dataCnt = 0; dataCnt < DRAM_MEM_SIZE; dataCnt++)
	{
		write_dram[dataCnt] = pattern;
	}

	return 0;
}













