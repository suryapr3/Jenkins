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

#include "com_bfn.h"
#include "bfn_test.h"
#include "com_event.h"
#include "rcs_timer_gpreg.h"
#include "com_shared_memory.h"


volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


uint32_t const SIZE = 32;
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t dram_buff[SIZE]  __attribute__((section(".dram0.data")));

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
	xthal_enable_interrupts();
	if (!com_shared_mem_wait_for_ready ())
    {
        // Update RSM flag for handshake with host code
		rsm_tx_shared_flag=0xDEADBEEF;
    }
    rsm_tx_shared_flag=0xC002C1C1;
    
    bfn_start();
	// Update RSM flag for handshake with host code
	// rsm_tx_shared_flag=0x1234;
    // Wait till Read from host completes

	
    return (0);
}

uint32_t bfn_start()
{
	//resetBfn();
    // PRE_REG0/1 will be loaded with default values
    //com_bfn_init(); // check why 1pps_timesync_ctrl regi is not written, w/o sysrefen, bfn wont start!
    //com_bfn_sync(0,0); // bfn_sync_time_high = 0, bfn_sync_time_low = 0
    
    dram_buff[0] = 0x3344;
    RCS_TIMER_GPREG->TEN_MS_CNT.value = 0x112233;
    RCS_TIMER_GPREG->ICTRL.value = 0x32;
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value = 0x30031;
    RCS_TIMER_GPREG->ICTRL.value = 0xB2;
    dram_buff[1] = 0x4455;
    
#if 0  
    captureBfnCounter(0); // dram_offset = 0
    //resetBfn();
    //com_timing_wait_ns (20000);
    //com_bfn_init(); // check why 1pps_timesync_ctrl regi is not written, w/o sysrefen, bfn wont start!
    // presetBfnCounter(0x55667788, 0x11223344);
    //com_bfn_main_reset_time(0x55667788, 0x11223344);
    //captureBfnCounter(0); // dram_offset = 8
    captureBfnCounter(8); // dram_offset = 8
    captureBfnCounter(16); // dram_offset = 8
#endif    
    //captureBfnCounter(0); // dram_offset = 8
    // will preset/reset operations work when the BFN is running?
	return 0;
	
}

void resetBfn(void)
{
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;

}
void presetBfnCounter(uint32_t const bfn_time_high, uint32_t const bfn_time_low)
{
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;

	RCS_TIMER_GPREG->INC_PRE_REG0.value = bfn_time_low;
	RCS_TIMER_GPREG->INC_PRE_REG1.value = bfn_time_high;

	// not working, it has to be written after ICTRL?
	//RCS_TIMER_GPREG->REG_OPPS_VAL_TIMESYNC_CTRL.TS_CAPTURE = 0x1;

	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	//RCS_TIMER_GPREG->ICTRL.value = 0x000001B2;
	RCS_TIMER_GPREG->ICTRL.ISYNC_VALUE = 0x3;
	RCS_TIMER_GPREG->ICTRL.TIMER_CMD = 0x2;
	RCS_TIMER_GPREG->ICTRL.ISYNC_TRIGGER = 0x1;
	RCS_TIMER_GPREG->ICTRL.LOAD_READ = 0x1;
	INTRINSIC_BARRIER; // todo: Need this?
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	//RCS_TIMER_GPREG->REG_OPPS_VAL_TIMESYNC_CTRL.value |= 0x40000;
	RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.TS_CAPTURE = 0x1;
	//RCS_TIMER_GPREG->ICTRL.value = 0x1B2;

}

void resetBfnCounter(uint32_t const bfn_time_high, uint32_t const bfn_time_low)
{
	RCS_TIMER_GPREG->INC_PRE_REG0.value = bfn_time_low;
	RCS_TIMER_GPREG->INC_PRE_REG1.value = bfn_time_high;
}



void captureBfnCounter(uint32_t const dram_offset)
{
	volatile com_bfn_cnt_t bfn_time = {.value = 0};
	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	// save the BFN val to RSM
	dram_buff[dram_offset] = bfn_time.CNT_LOW.value;
	//dram_buff[1] = bfn_time.CNT_HIGH.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+1] = bfn_time.CNT_LOW.value;
	//dram_buff[3] = bfn_time.CNT_HIGH.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+2] = bfn_time.CNT_LOW.value;
	//dram_buff[5] = bfn_time.CNT_HIGH.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+3] = bfn_time.CNT_LOW.value;
	//dram_buff[7] = bfn_time.CNT_HIGH.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+4] = bfn_time.CNT_LOW.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+5] = bfn_time.CNT_LOW.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+6] = bfn_time.CNT_LOW.value;

	// capture BFN
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	RCS_TIMER_GPREG->ICTRL.value = 0x000000B7;
	INTRINSIC_BARRIER;
	RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
	bfn_time.CNT_LOW.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG0.value;
	bfn_time.CNT_HIGH.value = RCS_TIMER_GPREG->BFN_CNT_VAL2_REG1.value;

	dram_buff[dram_offset+7] = bfn_time.CNT_LOW.value;

}




