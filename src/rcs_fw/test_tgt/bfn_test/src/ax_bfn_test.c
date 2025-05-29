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
#include "com_timing.h"
#include "com_event.h"
#include "rcs_timer_gpreg.h"
#include "timerx8.h"
#include "com_shared_memory.h"
#include "bfn_test.h"
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


uint32_t const SIZE = 32;
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t dram_buff[128]  __attribute__((section(".dram0.data")));

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
#define BFN_COM_ISYNC_CLEAR        0x00000000
#define BFN_COM_ISYNC_TRIG         0x00000080
#define BFN_COM_ISYNC_LOAD         0x00000100
#define BFN_COM_ISYNC_READ         0x00000000
#define BFN_COM_ISYNC_VAL_DEF      0x00000000
#define BFN_COM_ISYNC_VAL_INC      0x00000010
#define BFN_COM_ISYNC_VAL_DEC      0x00000020
#define BFN_COM_ISYNC_VAL_CMD      0x00000030
#define BFN_COM_ISYNC_CMD_INC_LCNT 0x00000000
#define BFN_COM_ISYNC_CMD_INIT     0x00000002
#define BFN_COM_ISYNC_CMD_PRESET   0x00000001
#define BFN_COM_ISYNC_CMD_INC      0x00000003
#define BFN_COM_ISYNC_CMD_INC_PRE  0x00000003
#define BFN_COM_ISYNC_CMD_ADJ      0x00000005
#define BFN_COM_ISYNC_CMD_CAP      0x00000007
#define BFN_COM_ISYNC_CMD          (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_CMD)   // 0x000000B0
#define BFN_COM_SYNC_PRESET        (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_PRESET) // 0x000000B1
#define BFN_COM_SYNC_INIT          (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_INIT)   // 0x000000B2
#define BFN_COM_SYNC_INC           (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_INC)  // 0x000000B3
#define BFN_COM_SYNC_CAP           (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_CAP)    // 0x000000B7
//#define BFN_COM_SYNC_INC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_INC)   // 0x00000090
#define BFN_COM_SYNC_DEC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_DEC)   // 0x000000A0
#define BFN_1PPS_SYSREF_EN         0x50000    
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
	xthal_enable_interrupts();
	uint32_t waitCnt = 0;
	
	if (!com_shared_mem_wait_for_ready ())
    {
        // Update RSM flag for handshake with host code
		rsm_ax_shared_flag=0xDEADBEEF;
		waitCnt++;
    }
    rsm_ax_shared_flag=0xC000C0C0;
    
    bfn_start();
    
    // trigger host for bfn_start test results check
    rsm_ax_shared_flag = 0xC000C001;
    
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D001);
    
    // run the test      
    bfn_testPresetCmd();
    // trigger host for bfn_testPresetCmd test results check
    rsm_ax_shared_flag = 0xC000C002;

	   
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D002);
	
	// run the test
    bfn_testIncCmd(); // Not working!
    // trigger host for bfn_testResetCmd test results check
    rsm_ax_shared_flag = 0xC000C003;
   
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D003);
	
	// run the test
	bfn_testCaptureCmd();
    // trigger host for bfn_testCaptureCmd test results check
    rsm_ax_shared_flag = 0xC000C004;
    
    
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D004);
 	
	// run the test
    bfn_testSyncLoad();
    // trigger host for bfn_testSyncLoad test results check
    rsm_ax_shared_flag = 0xC000C005;
  
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D005);
	
	// run the test
    bfn_testSyncRead();
	// trigger host for bfn_testSyncRead test results check
    rsm_ax_shared_flag = 0xC000C006;
#if 0    
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D006);
	
	// run the test
    bfn_timerSingleShot();
	// trigger host for bfn_testSyncLoad test results check
    rsm_ax_shared_flag = 0xC000C007;
	
	// handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D007);
	
	// run the test
    bfn_timerContinuous();
	// trigger host for bfn_testSyncLoad test results check
    rsm_ax_shared_flag = 0xC000C008;
    
#endif    
    return (0);
}
uint32_t bfn_start()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
	
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
     
    com_timing_wait_ns (20000); //20us   
    // read BFN live count register   
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (40000); //40us
    
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (640000); //640us
    
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[9] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (1280000); //1280us
    
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    return 0;
	
}
uint32_t bfn_testLcnt()
{
	// change the LCNT val and check
	
	return 0;
}

uint32_t bfn_testTenmsCnt()
{
	// change the TEN_MS_CNT val and check
	
	return 0;
}

uint32_t bfn_testUpperCntAdjReg()
{
	 //  When the upper BFN counter equals this value, 
	 // the Upper BFN counter is incremented by the value in TIMER_INC_PRE register.
	 
	 return 0;
}

uint32_t bfn_testSyncLoad()
{
	// INC_PRE_REG0 will be loaded into BFN counter when sync pulse occurs
	
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 10;
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 10000; // 10000 BFN counts
	
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // init command, timer will start
    
    com_timing_wait_ns (20000); // wait 20000 cycles -1G clock
    // read live counter
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    
    // trigger load
    RCS_TIMER_GPREG->ICTRL.value |= BFN_COM_ISYNC_LOAD;
    // send timesync
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
    
    // read live BFN count
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // BFN count during sync/sysref pulse
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
    
    com_timing_wait_ns (30000); // wait 30000 cycles -1G clock
    
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // toggle load
    RCS_TIMER_GPREG->ICTRL.value &= (!BFN_COM_ISYNC_LOAD);
    INTRINSIC_NOP; // HSD
    RCS_TIMER_GPREG->ICTRL.value |= BFN_COM_ISYNC_LOAD;
    // send timesync
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
    
    com_timing_wait_ns (100000); // wait 100000 cycles -1G clock
    
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // toggle load
    RCS_TIMER_GPREG->ICTRL.value &= (!BFN_COM_ISYNC_LOAD);
    INTRINSIC_NOP; // HSD
    RCS_TIMER_GPREG->ICTRL.value |= BFN_COM_ISYNC_LOAD;
    // send timesync
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
	dram_buff[9] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
    
    com_timing_wait_ns (200000); // wait 200000 cycles -1G clock
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // toggle load
    RCS_TIMER_GPREG->ICTRL.value &= (!BFN_COM_ISYNC_LOAD);
    INTRINSIC_NOP; // HSD
    RCS_TIMER_GPREG->ICTRL.value |= BFN_COM_ISYNC_LOAD;
    // send timesync
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
    
    return 0;
    
}

uint32_t bfn_testSyncRead()
{
	// Read BFN counter when sync pulse occurs
	
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 10;
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 10000; // 10000 BFN counts
	
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // init command, timer will start
    
    com_timing_wait_ns (20000); // wait 20000 cycles -1G clock
    // read live counter
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // send timesync to read BFN, load_read=0 in ICNTL
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
    INTRINSIC_BARRIER;
        
    // read BFN_CNT_VAL1_REG0
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_CNT_VAL1_REG0.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
    
    com_timing_wait_ns (20000); // wait 20000 cycles -1G clock
    // read live counter
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // send timesync to read BFN, load_read=0 in ICNTL
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value |= BFN_1PPS_SYSREF_EN;
    INTRINSIC_BARRIER;
        
    // read BFN_CNT_VAL1_REG0
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_CNT_VAL1_REG0.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_CNT_LO.value;
   
    return 0;
	
}

uint32_t bfn_testCaptureCmd()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 10;
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 10;
	
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // init command
    com_timing_wait_ns (10000); // 10us
    // capture BFN
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP;
    // proper capture value available after 18NOP : HSD
    INTRINSIC_BARRIER;
    
    // read capture register   
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    
    // read live count register
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;  
  
    com_timing_wait_ns (20000); // 10+20us
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // capture command
    INTRINSIC_BARRIER;
    // read capture register 
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    // read live count register 
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (40000); //30+40us
    
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // capture command
    INTRINSIC_BARRIER;
    
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[9] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (60000); //70+60us
    
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // capture command
    INTRINSIC_BARRIER;
    
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_CNT_VAL2_REG0.value;
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    return 0;
}

uint32_t bfn_testPresetCmd()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER;
	//INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	//INTRINSIC_NOP;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 0;
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 0;
	// init command, load config regs to internal regs, start bfn
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; 
    
    com_timing_wait_ns (10000); //10us 
      
    // Read live counter
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // preset command
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET;
    INTRINSIC_BARRIER;
    
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (20000); //20us
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // preset command
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 10;
    // load the register
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; 
    INTRINSIC_BARRIER;
    
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (40000); //40us
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[9] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // preset command
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 20;
    // load the register
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; 
    INTRINSIC_BARRIER;
    
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
      
    com_timing_wait_ns (60000); //60us
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // preset command
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 30;
    // load the register
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; 
    INTRINSIC_BARRIER;
    
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
	
	return 0;
	} 

uint32_t bfn_testIncCmd()
{
	
	// Iter1: soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 10000; 
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 10000;
	// init command, load config regs to internal regs, start bfn
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; 
    
    //com_timing_wait_ns (1000); //10us 
      
    // Read live counter
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // INC command
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INC;
    INTRINSIC_BARRIER;
    
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // Iter2: soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 20000; 
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 20000;
	// init command, load config regs to internal regs, start bfn
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; 
   
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // INC command
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INC;
    INTRINSIC_BARRIER;
    
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // Iter3: soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 30000; 
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 30000;
	// init command, load config regs to internal regs, start bfn
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; 
   
    
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[9] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // INC command
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INC; 
    INTRINSIC_BARRIER;
    
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    // Iter3: soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	RCS_TIMER_GPREG->INC_PRE_REG1.value = 40000; 
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 40000;
	// init command, load config regs to internal regs, start bfn
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; 
   
      
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // INC command
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INC; 
    INTRINSIC_BARRIER;
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
	
	return 0;
}



	
uint32_t bfn_testfreeRun() // HSD 16023407226
{
	//resetBfn();
    // PRE_REG0/1 will be loaded with default values
    //com_bfn_init(); // check why 1pps_timesync_ctrl regi is not written, w/o sysrefen, bfn wont start!
    //com_bfn_sync(0,0); // bfn_sync_time_high = 0, bfn_sync_time_low = 0
#if 1   
    dram_buff[0] = 0x1122;
    RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	//INTRINSIC_NOP;
    INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
	
	RCS_TIMER_GPREG->ICTRL.value = 0;
    //RCS_TIMER_GPREG->TEN_MS_CNT.value = 0x112233;
    RCS_TIMER_GPREG->INC_PRE_REG1.value = 10;
    RCS_TIMER_GPREG->INC_PRE_REG0.value = 20000;
    //RCS_TIMER_GPREG->ICTRL.value = 0x32; // load the values into internal regs
    INTRINSIC_NOP;
    //RCS_TIMER_GPREG->ICTRL.value = 0;
    RCS_TIMER_GPREG->ICTRL.value = 0x1B2; // initialise,load_read = 1
    //RCS_TIMER_GPREG->ICTRL.value = 0xB1; // preset,load_read = 1, is load read valid needed with preset command?
    //RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value = 0x30031;
    RCS_TIMER_GPREG->OPPS_VAL_TIMESYNC_CTRL.value = 0x70031;
    //RCS_TIMER_GPREG->ICTRL.value = 0x1B2; // load_read = 1
    
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    com_timing_wait_ns (20000); //20us
    
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
#endif
#if 0    
    //reset and run BFN
    resetBfn();
    com_bfn_init(); 
    presetBfnCounter (10, 20000);
    // preset values not working with below function
    com_bfn_sync(10, 20000); // 1pps_timesync_ctrl reg.sysrefen, bfn start!
    
    com_timing_wait_ns (20000); //20us
    
    // read BFN live counter
    dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[2] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[3] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    resetBfn();
    com_bfn_init(); 
    com_bfn_sync(0, 0); // 1pps_timesync_ctrl reg.sysrefen, bfn start!
    com_timing_wait_ns (40000); //40us
    
    // read BFN live counter
    dram_buff[4] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[5] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[6] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[7] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    resetBfn();
    com_bfn_init(); 
    com_bfn_sync(0, 0); // 1pps_timesync_ctrl reg.sysrefen, bfn start!
    com_timing_wait_ns (640000); //640us
    
    // read BFN live counter
    dram_buff[8] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[9] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[10] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[11] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    
    resetBfn();
    com_bfn_init(); 
    com_bfn_sync(0, 0); // 1pps_timesync_ctrl reg.sysrefen, bfn start!
    com_timing_wait_ns (1280000); // 1.28ms
    
    // read BFN live counter
    dram_buff[12] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[13] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[14] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    dram_buff[15] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
#endif    
    // presetBfnCounter(0x55667788, 0x11223344);
    //com_bfn_main_reset_time(0x55667788, 0x11223344);
    //captureBfnCounter(0); // dram_offset = 8
    //captureBfnCounter(8); // dram_offset = 8
    //captureBfnCounter(16); // dram_offset = 8
   
    //captureBfnCounter(0); // dram_offset = 8
    // will preset/reset operations work when the BFN is running?
	return 0;
	
}

void resetBfn(void)
{
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	//INTRINSIC_NOP;
    INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;

}
void startBfn(void)
{
	
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
	RCS_TIMER_GPREG->ICTRL.TIMER_CMD = 0x2; // INIT
	RCS_TIMER_GPREG->ICTRL.ISYNC_TRIGGER = 0x1;
	RCS_TIMER_GPREG->ICTRL.LOAD_READ = 0x1;
	INTRINSIC_BARRIER; // todo: Need this?
	// RCS_TIMER_GPREG->ICTRL.value = 0x00000000;
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

uint32_t bfn_timerSingleShot()
{
    // soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
   
    // grp0, timer0 trigger
    RCS_TIMER_GRP0_TMR0->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR0->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp0, timer0 cfg, oneshot, enable
    RCS_TIMER_GRP0_TMR0->T0_CFG.ENABLE = 0x1;
    RCS_TIMER_GRP0_TMR0->T1_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T2_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T3_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T4_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T5_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T6_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR0->T7_CFG.ENABLE = 0x1;
#if 1    
    // grp0, timer1 trigger
    RCS_TIMER_GRP0_TMR1->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp0, timer1 cfg, oneshot, enable
    RCS_TIMER_GRP0_TMR1->T0_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T1_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T2_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T3_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T4_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T5_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T6_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP0_TMR1->T7_CFG.ENABLE = 0x1;
		
    // grp1, timer0 trigger
    RCS_TIMER_GRP1_TMR0->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp1, timer0 cfg, oneshot, enable
    RCS_TIMER_GRP1_TMR0->T0_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T1_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T2_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T3_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T4_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T5_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T6_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR0->T7_CFG.ENABLE = 0x1;
    
    // grp1, timer1 trigger
    RCS_TIMER_GRP1_TMR1->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp1, timer1 cfg, oneshot, enable
    RCS_TIMER_GRP1_TMR1->T0_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T1_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T2_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T3_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T4_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T5_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T6_CFG.ENABLE = 0x1;
	RCS_TIMER_GRP1_TMR1->T7_CFG.ENABLE = 0x1;
#endif	
	// Read all timer status registers to make sure its 0
	dram_buff[0] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[1] = RCS_TIMER_GRP0_TMR1->STAT.value;
	dram_buff[2] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[3] = RCS_TIMER_GRP1_TMR1->STAT.value;
	
	// start BFN
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
     
    com_timing_wait_ns (15000); // 15us
	//dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
    // Read all timer status registers to make sure its 1
    dram_buff[4] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[5] = RCS_TIMER_GRP0_TMR1->STAT.value;
	dram_buff[6] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[7] = RCS_TIMER_GRP1_TMR1->STAT.value;
#if 1    
    // Clear all timer status by reading cfg register
    dram_buff[8]  = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[9]  = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[10] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[11] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[12] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[13] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[14] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[15] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
									
	dram_buff[16] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
	dram_buff[17] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
	dram_buff[18] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
	dram_buff[19] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
	dram_buff[20] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
	dram_buff[21] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
	dram_buff[22] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
	dram_buff[23] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
									
	dram_buff[24] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
	dram_buff[25] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
	dram_buff[26] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
	dram_buff[27] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
	dram_buff[28] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
	dram_buff[29] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
	dram_buff[30] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
	dram_buff[31] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
	
	dram_buff[32] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
	dram_buff[33] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
	dram_buff[34] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
	dram_buff[35] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
	dram_buff[36] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
	dram_buff[37] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
	dram_buff[38] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
	dram_buff[39] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
    
    // Read and confirm status reg is 0
    dram_buff[40] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[41] = RCS_TIMER_GRP0_TMR1->STAT.value;
	dram_buff[42] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[43] = RCS_TIMER_GRP1_TMR1->STAT.value;
    
    // read and confirm expired bit is cleared in cfg register    
    dram_buff[44] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[45] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[46] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[47] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[48] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[49] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[50] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[51] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
									
	dram_buff[52] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
	dram_buff[53] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
	dram_buff[54] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
	dram_buff[55] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
	dram_buff[56] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
	dram_buff[57] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
	dram_buff[58] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
	dram_buff[59] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
									
	dram_buff[60] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
	dram_buff[61] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
	dram_buff[62] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
	dram_buff[63] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
	dram_buff[64] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
	dram_buff[65] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
	dram_buff[66] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
	dram_buff[67] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
	
	dram_buff[68] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
	dram_buff[69] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
	dram_buff[70] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
	dram_buff[71] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
	dram_buff[72] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
	dram_buff[73] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
	dram_buff[74] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
	dram_buff[75] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
#endif
	return 0;
}

uint32_t bfn_timerContinuous()
{
	uint32_t cntIter = 0, errCnt = 0 ;
    
    // soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_NOP; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_NOP;
   
    // grp0, timer0 trigger
    RCS_TIMER_GRP0_TMR0->T0_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T1_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T2_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T3_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T4_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T5_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T6_TRIG.LOWER_COUNT = 5000; //5us
    RCS_TIMER_GRP0_TMR0->T7_TRIG.LOWER_COUNT = 5000; //5us
    
    // grp0 , timer0 interval
    RCS_TIMER_GRP0_TMR0->T0_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T1_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T2_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T3_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T4_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T5_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T6_INTERVAL.value = 5000;
    RCS_TIMER_GRP0_TMR0->T7_INTERVAL.value = 5000;
    
    // grp0, timer0 cfg, continuous, enable
    RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x3;
    RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x3;
#if 0    
    // grp0, timer1 trigger
    RCS_TIMER_GRP0_TMR1->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP0_TMR1->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp0, timer1 cfg, oneshot, enable
    RCS_TIMER_GRP0_TMR1->T0_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T1_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T2_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T3_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T4_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T5_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T6_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T7_CFG.value = 0x1;
		
    // grp1, timer0 trigger
    RCS_TIMER_GRP1_TMR0->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR0->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp1, timer0 cfg, oneshot, enable
    RCS_TIMER_GRP1_TMR0->T0_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T1_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T2_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T3_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T4_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T5_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T6_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T7_CFG.value = 0x1;
    
    // grp1, timer1 trigger
    RCS_TIMER_GRP1_TMR1->T0_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T1_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T2_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T3_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T4_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T5_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T6_TRIG.LOWER_COUNT = 10000; //10us
    RCS_TIMER_GRP1_TMR1->T7_TRIG.LOWER_COUNT = 10000; //10us
    
    // grp1, timer1 cfg, oneshot, enable
    RCS_TIMER_GRP1_TMR1->T0_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T1_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T2_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T3_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T4_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T5_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T6_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T7_CFG.value = 0x1;
#endif	
	// Read all timer status registers to make sure its 0
	dram_buff[0] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[1] = RCS_TIMER_GRP0_TMR1->STAT.value;
	dram_buff[2] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[3] = RCS_TIMER_GRP1_TMR1->STAT.value;
	
	// start BFN
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
     
    //com_timing_wait_ns (5000); // 12us
	dram_buff[0] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
	
	for(cntIter = 0; cntIter < 1;)
	{
		// Read all timer status registers to make sure its 1
		// wait till all timer status registers is 0xFF
#if 1
		do
		{
			dram_buff[4] = RCS_TIMER_GRP0_TMR0->STAT.value;
			errCnt++;
			if (errCnt > 0xFFFFF)
			{
				dram_buff[0] = 0xDEADBEEF;
				return 0;
			}
			
		} while (dram_buff[4] != 0xFF);
#endif		
		//dram_buff[4] = RCS_TIMER_GRP0_TMR0->STAT.value;
		if(dram_buff[4] == 0xFF) // all timer status bits set
		{
			// clear the status by reading cfg register
			dram_buff[8]  = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
			dram_buff[9]  = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
			dram_buff[10] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
			dram_buff[11] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
			dram_buff[12] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
			dram_buff[13] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
			dram_buff[14] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
			dram_buff[15] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
		}
		else
		{
			dram_buff[1] = 0xDEADBEEF;
			return 0;
			
		}
		errCnt = 0;
		// make sure status is 0
		do
		{
			dram_buff[4] = RCS_TIMER_GRP0_TMR0->STAT.value;
			errCnt++;
			if (errCnt > 0xFFFFF)
			{
				dram_buff[0] = 0xDEADBEEF;
				return 0;
			}
			
		} while (dram_buff[4] != 0x0);
		
		cntIter++;
		// wait for next timeout
		//com_timing_wait_ns (5000); // 12us
		
	}
	dram_buff[1] = RCS_TIMER_GPREG-> BFN_LIVE_CNT_LO.value;
	dram_buff[2] = cntIter;
    
	dram_buff[5] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[6] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[7] = RCS_TIMER_GRP1_TMR1->STAT.value;
#if 0    
    // Clear all timer status by reading cfg register
    dram_buff[8]  = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[9]  = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[10] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[11] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[12] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[13] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[14] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[15] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
									
	dram_buff[16] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
	dram_buff[17] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
	dram_buff[18] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
	dram_buff[19] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
	dram_buff[20] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
	dram_buff[21] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
	dram_buff[22] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
	dram_buff[23] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
									
	dram_buff[24] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
	dram_buff[25] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
	dram_buff[26] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
	dram_buff[27] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
	dram_buff[28] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
	dram_buff[29] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
	dram_buff[30] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
	dram_buff[31] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
	
	dram_buff[32] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
	dram_buff[33] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
	dram_buff[34] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
	dram_buff[35] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
	dram_buff[36] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
	dram_buff[37] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
	dram_buff[38] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
	dram_buff[39] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
    
    // Read and confirm status reg is 0
    dram_buff[40] = RCS_TIMER_GRP0_TMR0->STAT.value;
	dram_buff[41] = RCS_TIMER_GRP0_TMR1->STAT.value;
	dram_buff[42] = RCS_TIMER_GRP1_TMR0->STAT.value;
	dram_buff[43] = RCS_TIMER_GRP1_TMR1->STAT.value;
    
    // read and confirm expired bit is cleared in cfg register    
    dram_buff[44] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[45] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[46] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[47] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[48] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[49] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[50] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[51] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
									
	dram_buff[52] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
	dram_buff[53] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
	dram_buff[54] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
	dram_buff[55] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
	dram_buff[56] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
	dram_buff[57] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
	dram_buff[58] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
	dram_buff[59] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
									
	dram_buff[60] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
	dram_buff[61] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
	dram_buff[62] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
	dram_buff[63] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
	dram_buff[64] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
	dram_buff[65] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
	dram_buff[66] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
	dram_buff[67] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
	
	dram_buff[68] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
	dram_buff[69] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
	dram_buff[70] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
	dram_buff[71] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
	dram_buff[72] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
	dram_buff[73] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
	dram_buff[74] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
	dram_buff[75] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
#endif
	return 0;
}




