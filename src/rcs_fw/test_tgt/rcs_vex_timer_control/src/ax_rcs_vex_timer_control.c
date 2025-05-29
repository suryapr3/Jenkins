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

#include "tx_boot_test.h"
#include "com_event.h"
#include "rcs_gpreg.h"
#include "com_shared_memory.h"

#define NUM_VEX_CORES 20
#define VEX_CORE_OFFSET 0x40000
#define VEX0_TIMER_TMDVALR_BASE 0x02803004

volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));



uint32_t const SIZE = 16;
uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t write_dram[SIZE]  __attribute__((section(".dram0.data")));
volatile unsigned long int* car_timer0= (unsigned long int*) 0x024080a0;
volatile unsigned long int* car_timer1= (unsigned long int*) 0x024080a4;

volatile unsigned long int* timer_tmdvalr[NUM_VEX_CORES];


void initialize_timer_addresses() {
    uintptr_t base_address = VEX0_TIMER_TMDVALR_BASE;
    
    for (int i = 0; i < 16; i++) {
        
        timer_tmdvalr[i] = (volatile unsigned long int*)(base_address + i * VEX_CORE_OFFSET);
    }
    timer_tmdvalr[16] = (volatile unsigned long int*)0x03003004; // vex32
    timer_tmdvalr[17] = (volatile unsigned long int*)0x03083004; // vex34
    timer_tmdvalr[18] = (volatile unsigned long int*)0x03103004; // vex36
    timer_tmdvalr[19] = (volatile unsigned long int*)0x03183004; // vex38
}

//volatile uint32_t rsm_buf[NUM_VEX_CORES][8] __attribute__((section(".sram.reserved")));
volatile uint32_t rsm_buf[40][8] __attribute__((section(".sram.reserved")));
uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value,data2=0;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/




int main(int argc, char **argv)
{
   
    int index=0;  
	xthal_enable_interrupts();
	if (!com_shared_mem_wait_for_ready ())
    {
        // Update RSM flag for handshake with host code
		rsm_tx_shared_flag=0xDEADBEEF;
    }
    
    
    
    initialize_timer_addresses();

    *car_timer0 = 0xFFFFFFFF;
    *car_timer1 = 0xFF;
    
	while(*timer_tmdvalr[0] < 0xFFFF)
	{
	}
		
    for (int i = 0; i < NUM_VEX_CORES; i++)
    
    {   
		
        rsm_buf[i][0] = *timer_tmdvalr[i];
		rsm_buf[i][1] = *timer_tmdvalr[i];
		rsm_buf[i][2] = *timer_tmdvalr[i];

    }
    *car_timer0 = 0x0;
    *car_timer1 = 0x0;
    
    for (int i = 0; i < NUM_VEX_CORES; i++)
    
    {

		rsm_buf[i][3] = *timer_tmdvalr[i];
		rsm_buf[i][4] = *timer_tmdvalr[i];

    }

    
    rsm_ax_shared_flag= 0x8844;
				
    return (0);
}





