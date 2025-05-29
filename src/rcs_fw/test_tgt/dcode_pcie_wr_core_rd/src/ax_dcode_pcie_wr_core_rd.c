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



#include "tx_dcode_rwtest.h"
#include "com_event.h"
#include "rcs_gpreg.h"


volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


#define DRAM_MEM_SIZE 0x2000
uint32_t write_dram[DRAM_MEM_SIZE]  __attribute__((section(".dram0.data")));
//uint32_t *write_dram = (uint32_t *)0x10027030;

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
uint32_t pattern = 0x55555555,Cnt=0;


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
	xthal_enable_interrupts();
	com_shared_mem_wait_for_ready ();

	
	
#if 0
	rcs_gpreg_core1_control_reg_t rx_start_reg = {.value = RCS_GPREG_CORE1_CONTROL_DEFAULT};
	rx_start_reg.CORE_RUNSTALL = 0;
	*RCS_GPREG_CORE1_CONTROL_REG = rx_start_reg;
	rcs_gpreg_core2_control_reg_t cal_start_reg = {.value = RCS_GPREG_CORE2_CONTROL_DEFAULT};
	cal_start_reg.CORE_RUNSTALL = 0;
	*RCS_GPREG_CORE2_CONTROL_REG = cal_start_reg;
#endif
	dcode_tests();
	//while(1);
    return (0);
}

int8_t dcode_tests()
{

	dcode_rd_core_wr_pcie_tests(pattern);
    return 0;
}


int8_t dcode_rd_core_wr_pcie_tests(int32_t pattern)
{
	
	do
    {
        if(rsm_ax_shared_flag == 0x8844)
		break;
    }while(rsm_ax_shared_flag != 0x8844);
    //rsm_ax_shared_flag=*write_dram;
    //*write_dram=0x0;
#if 1    
    for (dataCnt = 0; dataCnt < DRAM_MEM_SIZE; dataCnt++)
	{
    	if (write_dram[dataCnt] != pattern)
		    errCnt++;
		    Cnt++;
		    rsm_ax_shared_flag=Cnt;
	}
    if (errCnt == 0)
	{
    	
    	rsm_com_shared_flag = 0x1122;
	}
	else
	{
		
		rsm_com_shared_flag = 0x2211;
    }
#endif    
}








