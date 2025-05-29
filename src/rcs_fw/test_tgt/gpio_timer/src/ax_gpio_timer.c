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

#include "gpio_timer.h"

#include "com_bfn.h"
#include "com_timing.h"
#include "com_event.h"
#include "com_isr.h"
#include "rcs_timer_gpreg.h"
#include "timerx8.h"
#include "com_shared_memory.h"
#include "rcs_timestamp.h"
#include "timer_gpio.h"
#include "nsip_hbi.h"
#include "strm2cio.h"
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
#define BFN_COM_ISYNC_CMD_RESET    0x00000003
#define BFN_COM_ISYNC_CMD_INC_PRE  0x00000003
#define BFN_COM_ISYNC_CMD_ADJ      0x00000005
#define BFN_COM_ISYNC_CMD_CAP      0x00000007
#define BFN_COM_ISYNC_CMD          (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_CMD)   // 0x000000B0
#define BFN_COM_SYNC_PRESET        (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_PRESET) // 0x000000B1
#define BFN_COM_SYNC_INIT          (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_INIT)   // 0x000000B2
#define BFN_COM_SYNC_RESET         (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_RESET)  // 0x000000B3
#define BFN_COM_SYNC_CAP           (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_CAP)    // 0x000000B7
#define BFN_COM_SYNC_INC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_INC)   // 0x00000090
#define BFN_COM_SYNC_DEC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_DEC)   // 0x000000A0
#define BFN_1PPS_SYSREF_EN         0x50000

#define TIMER_TEST_ITER			   20
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
	xthal_enable_interrupts();
	uint32_t waitCnt, loopCnt, loopPassCnt = 0;
	
	if (!com_shared_mem_wait_for_ready ())
    {
        waitCnt++;
    }
    rsm_ax_shared_flag=0xC000C0C0;
    
    gpio_out_test();
    
    // trigger host for gpio_out_test test results check
    rsm_ax_shared_flag = 0xC000C001;

    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D001);

    
    // run the test      
    gpio_in_test();
   
    // trigger host for gpio_in_test test results check
    rsm_ax_shared_flag = 0xC000C002;
   
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D002);
	
	// run the test
    timerOneshotGrp0Tim0Test(); 
    // trigger host for timerOneshotGrp0Tim0Test test results check
    rsm_ax_shared_flag = 0xC000C003;
#if 1  
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D003);
	
	// run the test
    timerOneshotGrp0Tim1Test();
    // trigger host for timerOneshotGrp0Tim0Testresults check
    rsm_ax_shared_flag = 0xC000C004;
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D004);
	
	// run the test
    timerOneshotGrp1Tim0Test();
    // trigger host for timerOneshotGrp1Tim0Test results check
    rsm_ax_shared_flag = 0xC000C005;
  
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D005);
	
	// run the test
    timerOneshotGrp1Tim1Test();
	// trigger host for timerOneshotGrp1Tim0Test results check
    rsm_ax_shared_flag = 0xC000C006;
  
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D006);
	
	// run the test
    timerContGrp0Tim0Test();
	// trigger host for timerContGrp0Tim0Test results check
    rsm_ax_shared_flag = 0xC000C007;
 
	// handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D007);
	
	// run the test
    timerContGrp0Tim1Test();
	// trigger host for timerContGrp0Tim1Test results check
    rsm_ax_shared_flag = 0xC000C008;
    
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D008);
	
	// run the test
    timerContGrp1Tim0Test();
	// trigger host for timerContGrp1Tim0Test results check
    rsm_ax_shared_flag = 0xC000C009;
	
	// handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D009);
	
	// run the test
    timerContGrp1Tim1Test();
	// trigger host for timerContGrp1Tim1Test results check
    rsm_ax_shared_flag = 0xC000C00A;
   
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D00A);
	
	// run the test
    gpioTimeStampTestSingle();
	// trigger host for timerContGrp1Tim1Test results check
    rsm_ax_shared_flag = 0xC000C00B;
#endif    
#if 1 
	dram_buff[2] = 0;
    // handshake with host for starting next test
    waitCnt = 0;
    do
    {
		waitCnt++;
		
	} while(rsm_com_shared_flag != 0xC000D00A);
	
	// run the test
    gpioTimeStampTestSingle();
	// trigger host for timerContGrp1Tim1Test results check
    rsm_ax_shared_flag = 0xC000C00B;
 
    
#endif
    
    return (0);
}

uint32_t gpioTimeStampTestSingle()
{
	dram_buff[2] = 0x11;
	int i;

	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// CMD_MD_STREAM_EN, enable all 16 streams
	RCS_CRUX_NSIP_HBI->MD_CMD_STRM_EN.STREAM_EN = 0xFFFF;
	// CMD_MD_MESSAGE - should be filled by Timestamp module
	RCS_CRUX_NSIP_HBI->MD_CMD_MSG.MESSAGE = 0x1234;
	// CMD_MD_CONTROL
	RCS_CRUX_NSIP_HBI->MD_CMD_CTRL.SEQUENCE_CNT = 0x0;
	RCS_CRUX_NSIP_HBI->MD_CMD_CTRL.MODE = 0x0;
	// PRL_SEQ_COUNT
	//RCS_CRUX_NSIP_HBI->SCNT_PRL_SEQ_COUNT.SEQUENCE_CNT = 0x0;
	// PRL_STREAM_EN
	RCS_CRUX_NSIP_HBI->SCNT_PRL_STRM_EN.STREAM_EN = 0x1; // is it needed?

    // Per entry

	for(i = 0; i< 16; i++)
	{
		// address
		RCS_CRUX_NSIP_HBI->H2B_ADDR_LKUP_TBL[i].BASE_BYTE_ADDRESS = 0x0; // VMEM
		RCS_CRUX_NSIP_HBI->H2B_MD_ADDR_LKUP_TBL[i].BASE_BYTE_ADDRESS = 0x18000; // MD in DMEM
		RCS_CRUX_NSIP_HBI->H2B_TK_ADDR_LKUP_TBL[i].TK_BYTE_ADDRESS = 0x18184; //TK in DMEM
		//route
		RCS_CRUX_NSIP_HBI->H2B_MD_ROUTE_LKUP_TBL[i].DEST_HOST_ID = i;
		RCS_CRUX_NSIP_HBI->H2B_TK_ROUTE_LKUP_TBL[i].DEST_HOST_ID = i;
		RCS_CRUX_NSIP_HBI->H2B_ROUTE_LKUP_TBL[i].DEST_HOST_ID = i;
			
		// H2B_MD_CONTROL_TBL[16]
		RCS_CRUX_NSIP_HBI->H2B_MD_CTRL_TBL[i].METADATA_EN = 0x1;
		RCS_CRUX_NSIP_HBI->H2B_MD_CTRL_TBL[i].DA_BLOCK_SIZE = 0x0;
		
		RCS_CRUX_NSIP_HBI->H2B_ADDR_LKUP_TBL[i].VALID = 0x1;
	}

	// Vex 0 Strm2Cio config
	VEXABC0_S2C_STRM2CIO->STRM2CIO_FIFO_STAT_CTL.FIFO_STATUS_ENABLE = 0x1;
	VEXABC0_S2C_STRM2CIO->STRM2CIO_WORD_CNT_CTL.WORD_CNT_ENABLE = 0x1;
	VEXABC0_S2C_STRM2CIO->STRM2CIO_INT_EN.value = 0xF;

	// Vex 0 Strm2Cio config
	VEXABC1_S2C_STRM2CIO->STRM2CIO_FIFO_STAT_CTL.FIFO_STATUS_ENABLE = 0x1;
	VEXABC1_S2C_STRM2CIO->STRM2CIO_WORD_CNT_CTL.WORD_CNT_ENABLE = 0x1;
	VEXABC1_S2C_STRM2CIO->STRM2CIO_INT_EN.value = 0xF;

	

	
	/*
	 * {NSIP_HBI_INTR_INT_HIGH_EN_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_HIGH_EN"},
{NSIP_HBI_INTR_INT_LOW_EN_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_LOW_EN"},


{NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x184, 0xFFFFFFFF, "H2B_FIFO_CONTROL"},
{NSIP_HBI_H2B_CREDIT_READY_CS_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x4, 0xFFFFFFFF, "H2B_CREDIT_READY_CS"},
{NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x3F, 0xFFFFFFFF, "H2B_BUF_SZ_HW_TBL0"},

{NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x18080, 0xFFFFFFFF, "H2B_TK_ADDR_LKUP_TBL0"},
{NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x18000, 0xFFFFFFFF, "H2B_MD_ADDR_LKUP_TBL0"},
{NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x80010000, 0xFFFFFFFF, "H2B_ADDR_LKUP_TBL0"},
{NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 68, 0xFFFFFFFF, "H2B_TK_ROUTE_LKUP_TBL0"},
{NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 68, 0xFFFFFFFF, "H2B_MD_ROUTE_LKUP_TBL0"},
{NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 68, 0xFFFFFFFF, "H2B_ROUTE_LKUP_TBL0"},
{NSIP_HBI_H2B_MD_CONTROL_TBL0_ADR(V2D0_AV2D_APB_0_NSIP_HBI_0_BASE), 0x40000007, 0xFFFFFFFF, "H2B_MD_CONTROL_TBL0"},

 */
	dram_buff[2] = 0x33;
	// grp0 gpio polarity
	RCS_TIMER_GRP0_GPIO->GPIO_POLARITY.value = 0x0;
	// grp1 gpio polarity
	RCS_TIMER_GRP1_GPIO->GPIO_POLARITY.value = 0x0;
	// grp0 gpio_inout, out
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	// grp1 gpio_inout, out
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	
	// GPIO[7:0] contribute to EC0:15
	for(i = 0; i<16; i++)
		RCS_TIMER_TIMESTAMP->EC_GPIO_SEL[i].EC_GPIO_SELECT = 0xFF;
	
	// GPIO_GRP0 to EC0
	RCS_TIMER_TIMESTAMP->EC_GRP_SEL.EC_GROUP_SELECT = 0;
	
	// Enable EC0:15
	RCS_TIMER_TIMESTAMP->EC_EN.EC_ENABLE = 0xFFFF;
	//RCS_TIMER_TIMESTAMP->EC_EN.EC_ENABLE = 0x1;
	
	dram_buff[2] = 0x44;
	
	// The WINDOW_START field can only be updated either before the 
	// timestamp has started or while the GLOBAL_DISABLE is set.
	RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.GLOBAL_DISABLE = 1;
	// GPIO states will be captured for 1 us duration (982 BFN counts)
	RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.DURATION = 982; // 1 us duration
	// Send Metadata only once
	RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.RESTART = 0;
	// Time of the first processing window specified in BFN time units
	RCS_TIMER_TIMESTAMP->WND_START.TS_WINDOW = 10000; //10000 ns
	// Global Enable
	RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.GLOBAL_DISABLE = 0;
	
	
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
	
	dram_buff[2] = 0x55;
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0000;
	com_timing_wait_ns (10150);  // wait 10000 cycles for start of time stamp window
	
	dram_buff[2] = 0x66;
	// Toggle GRP0_GPIO[7:0] max 15 times
	// grp0 gpio_set_val_15_0
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0001;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0002;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0003;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0004;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0005;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0006;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0007;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0008;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0009;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000A;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000B;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000C;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000D;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000E;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF000F;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0010;
	com_timing_wait_ns (20);
	
	//RCS_CRUX_NSIP_HBI->H2B_ADDR_LKUP_TBL[i].VALID = 0x0;
	//for(i = 0; i<10; i++)
		//RCS_CRUX_NSIP_HBI->H2B_ADDR_LKUP_TBL[i].BASE_BYTE_ADDRESS = 0x80; // VMEM
	//RCS_CRUX_NSIP_HBI->H2B_ADDR_LKUP_TBL[i].VALID = 0x1;
	
#if 0
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0011;
	com_timing_wait_ns (20);
	
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0012;
	com_timing_wait_ns (20);
	
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0013;
	com_timing_wait_ns (20);

	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0014;
	com_timing_wait_ns (20);

	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0015;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0016;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0017;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0018;
	com_timing_wait_ns (20);

	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0019;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001A;
	com_timing_wait_ns (20);
		
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001B;
	com_timing_wait_ns (20);
	
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001C;
	com_timing_wait_ns (20);
// here 2nd packet goes	
	
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001D;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001E;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF001F;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0020;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0021;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0022;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0023;
	com_timing_wait_ns (20);
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF0024;
#endif	
	
	dram_buff[1] = 0x22;
	
	// Disable EC0
	RCS_TIMER_TIMESTAMP->EC_EN.EC_ENABLE = 0x0;
	RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.GLOBAL_DISABLE = 1;
	
	// Disable capture
	//RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.GLOBAL_DISABLE = 1;
	//RCS_TIMER_TIMESTAMP->TIMESTAMP_SETUP.RESTART = 1;
	
	
	
	return 0;
}

uint32_t gpio_out_test()
{
	// grp0 gpio polarity
	RCS_TIMER_GRP0_GPIO->GPIO_POLARITY.value = 0x0;
	// grp1 gpio polarity
	RCS_TIMER_GRP1_GPIO->GPIO_POLARITY.value = 0x0;
	// grp0 gpio_inout, out
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	// grp1 gpio_inout, out
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	// grp0 gpio_set_val_15_0
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFFa5a5;
	// grp0 gpio_set_val_31_16
	RCS_TIMER_GRP0_GPIO->GPIO_SET_VAL_31_16.value = 0xFFFFa5a5;
	// grp1 gpio_set_val_15_0
	RCS_TIMER_GRP1_GPIO->GPIO_SET_VAL_15_0.value = 0xFFFF5a5a;
	// grp1 gpio_set_val_31_16
	RCS_TIMER_GRP1_GPIO->GPIO_SET_VAL_31_16.value = 0xFFFF5a5a;
	
	return 0;
	
}

uint32_t gpio_out_mask_test()
{
	// grp0 gpio polarity
	RCS_TIMER_GRP0_GPIO->GPIO_POLARITY.value = 0xFFFFFFFF;
	// grp1 gpio polarity
	
	// grp0 gpio_inout, out
	
	// grp1 gpio_inout, out
	
	// grp0 gpio_set_val_15_0
	
	// grp0 gpio_set_val_31_16
	
	// grp0 gpio_set_val_15_0
	
	// grp0 gpio_set_val_31_16
	
	return 0;
	
}

uint32_t gpio_in_test()
{
	// grp0/1 gpio_curr_in
	dram_buff[0] = RCS_TIMER_GRP0_GPIO->GPIO_CURR_IN.value;
    dram_buff[1] = RCS_TIMER_GRP1_GPIO->GPIO_CURR_IN.value;
		
	return 0;
	
}

uint32_t timerOneshotGrp0Tim0Test()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 10us
	RCS_TIMER_GRP0_TMR0->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP0_TMR0->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP0_TMR0->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP0_TMR0->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP0_TMR0->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP0_TMR0->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP0_TMR0->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP0_TMR0->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP0_TMR0->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP0_TMR0->T0_GPIO_VAL.value = 0x321; // HSD16023770293
	RCS_TIMER_GRP0_TMR0->T1_GPIO_VAL.value = 0x20;
	RCS_TIMER_GRP0_TMR0->T2_GPIO_VAL.value = 0x300;
	RCS_TIMER_GRP0_TMR0->T3_GPIO_VAL.value = 0x4000;
	RCS_TIMER_GRP0_TMR0->T4_GPIO_VAL.value = 0x50000;
	RCS_TIMER_GRP0_TMR0->T5_GPIO_VAL.value = 0x600000;
	RCS_TIMER_GRP0_TMR0->T6_GPIO_VAL.value = 0x7000000;
	RCS_TIMER_GRP0_TMR0->T7_GPIO_VAL.value = 0x80000000;
	
	// clear int flag
	write_rsm[1] = 0x0;
	dram_buff[10] = 0x0; 
	// register irq handler
	com_isr_event (e_RCS_TIMER_INT0_IRQ, timer0_irq_handler, (void *)0);
    //com_isr_event (e_RCS_TIMER_INT0_DIRECT_IRQ, timer0_irq_handler, (void *)0);

	// enable interrupt
	com_isr_interrupt_enable (e_RCS_TIMER_INT0_IRQ);
	//com_isr_interrupt_enable (e_RCS_TIMER_INT0_DIRECT_IRQ);
	
	
	// timer_cfg, oneshot, enable interrupt
	RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x5;
	RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x5;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
	
	// wait till timer expiry - all timer status bit is set
	do
    {
		dram_buff[0] = RCS_TIMER_GRP0_TMR0->STAT.value;
		
	} while(dram_buff[0] != 0xFF);
	
		
	// check GPIO values in host code and clear timer status
	// Read timer_cfg to clear status
	dram_buff[1] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[2] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[3] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[4] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[5] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[6] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[7] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[8] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
	
	// Read timer status to verify its cleared
	dram_buff[9] = RCS_TIMER_GRP0_TMR0->STAT.value;
		
	return 0;
	
}

uint32_t timerOneshotGrp0Tim1Test()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 10us
	RCS_TIMER_GRP0_TMR1->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP0_TMR1->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP0_TMR1->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP0_TMR1->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP0_TMR1->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP0_TMR1->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP0_TMR1->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP0_TMR1->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP0_TMR1->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP0_TMR1->T0_GPIO_VAL.value = 0x8; // HSD16023770293
	RCS_TIMER_GRP0_TMR1->T1_GPIO_VAL.value = 0x70;
	RCS_TIMER_GRP0_TMR1->T2_GPIO_VAL.value = 0x600;
	RCS_TIMER_GRP0_TMR1->T3_GPIO_VAL.value = 0x5000;
	RCS_TIMER_GRP0_TMR1->T4_GPIO_VAL.value = 0x40000;
	RCS_TIMER_GRP0_TMR1->T5_GPIO_VAL.value = 0x300000;
	RCS_TIMER_GRP0_TMR1->T6_GPIO_VAL.value = 0x2000000;
	RCS_TIMER_GRP0_TMR1->T7_GPIO_VAL.value = 0x10000000;
	
	// timer_cfg, oneshot, enable
	RCS_TIMER_GRP0_TMR1->T0_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T1_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T2_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T3_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T4_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T5_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T6_CFG.value = 0x1;
	RCS_TIMER_GRP0_TMR1->T7_CFG.value = 0x1;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
	
	// wait till timer expiry - all timer status bit is set
	do
    {
		dram_buff[0] = RCS_TIMER_GRP0_TMR1->STAT.value;
		
	} while(dram_buff[0] != 0xFF);
	
		
	// check GPIO values in host code and clear timer status
	// Read timer_cfg to clear status
	dram_buff[1] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
	dram_buff[2] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
	dram_buff[3] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
	dram_buff[4] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
	dram_buff[5] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
	dram_buff[6] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
	dram_buff[7] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
	dram_buff[8] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
	
	// Read timer status to verify its cleared
	dram_buff[9] = RCS_TIMER_GRP0_TMR1->STAT.value;
		
	return 0;
	
}

uint32_t timerOneshotGrp1Tim0Test()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 10us
	RCS_TIMER_GRP1_TMR0->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP1_TMR0->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP1_TMR0->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP1_TMR0->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP1_TMR0->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP1_TMR0->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP1_TMR0->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP1_TMR0->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP1_TMR0->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP1_TMR0->T0_GPIO_VAL.value = 0xa; // HSD16023770293
	RCS_TIMER_GRP1_TMR0->T1_GPIO_VAL.value = 0x50;
	RCS_TIMER_GRP1_TMR0->T2_GPIO_VAL.value = 0xa00;
	RCS_TIMER_GRP1_TMR0->T3_GPIO_VAL.value = 0x5000;
	RCS_TIMER_GRP1_TMR0->T4_GPIO_VAL.value = 0xa0000;
	RCS_TIMER_GRP1_TMR0->T5_GPIO_VAL.value = 0x500000;
	RCS_TIMER_GRP1_TMR0->T6_GPIO_VAL.value = 0xa000000;
	RCS_TIMER_GRP1_TMR0->T7_GPIO_VAL.value = 0x50000000;
	
	// timer_cfg, oneshot, enable
	RCS_TIMER_GRP1_TMR0->T0_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T1_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T2_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T3_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T4_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T5_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T6_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR0->T7_CFG.value = 0x1;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
	
	// wait till timer expiry - all timer status bit is set
	do
    {
		dram_buff[0] = RCS_TIMER_GRP1_TMR0->STAT.value;
		
	} while(dram_buff[0] != 0xFF);
	
		
	// check GPIO values in host code and clear timer status
	// Read timer_cfg to clear status
	dram_buff[1] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
	dram_buff[2] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
	dram_buff[3] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
	dram_buff[4] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
	dram_buff[5] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
	dram_buff[6] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
	dram_buff[7] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
	dram_buff[8] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
	
	// Read timer status to verify its cleared
	dram_buff[9] = RCS_TIMER_GRP1_TMR0->STAT.value;
		
	return 0;
	
}

uint32_t timerOneshotGrp1Tim1Test()
{
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 10us
	RCS_TIMER_GRP1_TMR1->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP1_TMR1->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP1_TMR1->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP1_TMR1->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP1_TMR1->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP1_TMR1->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP1_TMR1->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP1_TMR1->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP1_TMR1->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP1_TMR1->T0_GPIO_VAL.value = 0x5; // HSD16023770293
	RCS_TIMER_GRP1_TMR1->T1_GPIO_VAL.value = 0xa0;
	RCS_TIMER_GRP1_TMR1->T2_GPIO_VAL.value = 0x500;
	RCS_TIMER_GRP1_TMR1->T3_GPIO_VAL.value = 0xa000;
	RCS_TIMER_GRP1_TMR1->T4_GPIO_VAL.value = 0x50000;
	RCS_TIMER_GRP1_TMR1->T5_GPIO_VAL.value = 0xa00000;
	RCS_TIMER_GRP1_TMR1->T6_GPIO_VAL.value = 0x5000000;
	RCS_TIMER_GRP1_TMR1->T7_GPIO_VAL.value = 0xa0000000;
	
	// timer_cfg, oneshot, enable
	RCS_TIMER_GRP1_TMR1->T0_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T1_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T2_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T3_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T4_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T5_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T6_CFG.value = 0x1;
	RCS_TIMER_GRP1_TMR1->T7_CFG.value = 0x1;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
	
	// wait till timer expiry - all timer status bit is set
	do
    {
		dram_buff[0] = RCS_TIMER_GRP1_TMR1->STAT.value;
		
	} while(dram_buff[0] != 0xFF);
	
		
	// check GPIO values in host code and clear timer status
	// Read timer_cfg to clear status
	dram_buff[1] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
	dram_buff[2] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
	dram_buff[3] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
	dram_buff[4] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
	dram_buff[5] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
	dram_buff[6] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
	dram_buff[7] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
	dram_buff[8] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
	
	// Read timer status to verify its cleared
	dram_buff[9] = RCS_TIMER_GRP1_TMR1->STAT.value;
		
	return 0;
	
}

void timer0_irq_handler (void *arg)
{
    UNUSED (arg);
    com_isr_interrupt_disable(e_RCS_TIMER_INT0_IRQ);
    //com_isr_interrupt_disable(e_RCS_TIMER_INT0_DIRECT_IRQ);
    
    // Read timer_cfg to clear status
	dram_buff[1] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
	dram_buff[2] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
	dram_buff[3] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
	dram_buff[4] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
	dram_buff[5] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
	dram_buff[6] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
	dram_buff[7] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
	dram_buff[8] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
	
	// Read timer status to verify its cleared
	dram_buff[9] = RCS_TIMER_GRP0_TMR0->STAT.value;
	
	// disable timer and interrupts
	RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x0;
	
	// int flag
	write_rsm[1] = 0xC0D0E0F0;
	dram_buff[10] = 0xF0E0D0C0; 
		
		
}


uint32_t timerContGrp0Tim0Test()
{
	uint32_t loopCnt, loopPassCnt=0;
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// Read timer status reg, if nonzero, read timer_cfg to clear it
	write_rsm[0] = RCS_TIMER_GRP0_TMR0->STAT.value;
	if(write_rsm[0] != 0)
	{
		// Disable timers
		// timer_cfg, disable
		RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x0;
		RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x0;
		
		// read config to clear status
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
	}
	
	
	
	// All timer trigger, after 1ms
	RCS_TIMER_GRP0_TMR0->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T7_TRIG.value = 0x2710;
	
	// Timer interval register
	RCS_TIMER_GRP0_TMR0->T0_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T1_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T2_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T3_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T4_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T5_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T6_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR0->T7_INTERVAL.value = 0x2710;
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP0_TMR0->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP0_TMR0->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP0_TMR0->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP0_TMR0->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP0_TMR0->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP0_TMR0->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP0_TMR0->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP0_TMR0->T7_GPIO_MASK.value = 0xF0000000;
	
	RCS_TIMER_GRP0_TMR0->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP0_TMR0->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP0_TMR0->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP0_TMR0->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP0_TMR0->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP0_TMR0->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP0_TMR0->T6_GPIO_MASK.value = 0xFF000000;
	RCS_TIMER_GRP0_TMR0->T7_GPIO_MASK.value = 0xFF000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP0_TMR0->T0_GPIO_VAL.value = 0x0; 
	RCS_TIMER_GRP0_TMR0->T1_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T2_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T3_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T4_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T5_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T6_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T7_GPIO_VAL.value = 0x0;
	
	// timer_cfg, cont, enable
	RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x3;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;
#if 1
	for( loopCnt = 0; loopCnt < TIMER_TEST_ITER; loopCnt++)
	{
		// wait till timer expiry - all timer status bit is set
		do
		{
			write_rsm[0] = RCS_TIMER_GRP0_TMR0->STAT.value;
			
			
		} while(write_rsm[0] != 0xFF);
		
		
		
		// verify whether GPIO is toggled
		dram_buff[0] = RCS_TIMER_GRP0_GPIO->GPIO_CURR_OUT.value;
		// GPIO will be 0x0 for the even values of loopCnt
		if(loopCnt % 2 == 0 && dram_buff[0] == 0x0)
		{
			loopPassCnt++;
			dram_buff[2] = 0xC001 + loopPassCnt;
		}
		else if(dram_buff[0] == 0xFFFFFFFF)
		{
			loopPassCnt++;
			dram_buff[3] = 0xC002 + loopPassCnt;
		}
		
		//dram_buff[1] =  loopPassCnt;// shouldnt this be moved out of the loop?
		
		// Toggle GPIO - may have to use rdWrVal since regs are not volatile
		RCS_TIMER_GRP0_TMR0->T0_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T0_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T1_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T1_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T2_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T2_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T3_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T3_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T4_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T4_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T5_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T5_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T6_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T6_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR0->T7_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR0->T7_GPIO_VAL.value);
		
		//dram_buff[4 + loopCnt] =  RCS_TIMER_GRP0_GPIO->GPIO_CURR_OUT.value;
	
		// read config to clear status
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T0_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T1_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T2_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T3_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T4_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T5_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T6_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR0->T7_CFG.value;
		
	}
	
	dram_buff[1] =  loopPassCnt;
	//dram_buff[4] =  0x45454545;
		
	// timer_cfg, disable
	RCS_TIMER_GRP0_TMR0->T0_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T1_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T2_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T3_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T4_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T5_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T6_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR0->T7_CFG.value = 0x0;
	
	//dram_buff[5] =  0x56565656;
	
#endif	
	return 0;
	
}
uint32_t timerContGrp1Tim0Test()
{
	uint32_t loopCnt, loopPassCnt=0;
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 1ms
	RCS_TIMER_GRP1_TMR0->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	RCS_TIMER_GRP1_TMR0->T0_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T1_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T2_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T3_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T4_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T5_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T6_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR0->T7_INTERVAL.value = 0x2710;
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP1_TMR0->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP1_TMR0->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP1_TMR0->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP1_TMR0->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP1_TMR0->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP1_TMR0->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP1_TMR0->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP1_TMR0->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP1_TMR0->T0_GPIO_VAL.value = 0x0; // HSD16023770293
	RCS_TIMER_GRP1_TMR0->T1_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T2_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T3_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T4_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T5_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T6_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T7_GPIO_VAL.value = 0x0;
	
	// timer_cfg, cont, enable
	RCS_TIMER_GRP1_TMR0->T0_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T1_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T2_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T3_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T4_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T5_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T6_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR0->T7_CFG.value = 0x3;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;

	for( loopCnt = 0; loopCnt < TIMER_TEST_ITER; loopCnt++)
	{
		// wait till timer expiry - all timer status bit is set
		do
		{
			write_rsm[0] = RCS_TIMER_GRP1_TMR0->STAT.value;
			
		} while(write_rsm[0] != 0xFF);
		
		// verify whether GPIO is toggled
		dram_buff[0] = RCS_TIMER_GRP1_GPIO->GPIO_CURR_OUT.value;
		if(loopCnt % 2 == 0 && dram_buff[0] == 0x0)
		{
				loopPassCnt++;
			
		}
		else if(dram_buff[0] == 0xFFFFFFFF)
		{
			loopPassCnt++;
		}
		
		dram_buff[3] =  loopPassCnt;
		
		// Toggle GPIO - may have to use rdWrVal since regs are not volatile
		RCS_TIMER_GRP1_TMR0->T0_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T0_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T1_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T1_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T2_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T2_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T3_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T3_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T4_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T4_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T5_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T5_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T6_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T6_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR0->T7_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR0->T7_GPIO_VAL.value);
	
		// read config to clear status
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T0_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T1_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T2_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T3_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T4_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T5_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T6_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR0->T7_CFG.value;
		
	}
	// timer_cfg, disable
	RCS_TIMER_GRP1_TMR0->T0_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T1_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T2_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T3_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T4_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T5_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T6_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR0->T7_CFG.value = 0x0;
			
	return 0;
	
}
uint32_t timerContGrp0Tim1Test()
{
	uint32_t loopCnt, loopPassCnt=0;
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 1ms
	RCS_TIMER_GRP0_TMR1->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	RCS_TIMER_GRP0_TMR1->T0_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T1_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T2_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T3_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T4_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T5_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T6_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP0_TMR1->T7_INTERVAL.value = 0x2710;
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP0_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP0_TMR1->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP0_TMR1->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP0_TMR1->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP0_TMR1->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP0_TMR1->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP0_TMR1->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP0_TMR1->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP0_TMR1->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP0_TMR1->T0_GPIO_VAL.value = 0x0; // HSD16023770293
	RCS_TIMER_GRP0_TMR1->T1_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T2_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T3_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T4_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T5_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T6_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T7_GPIO_VAL.value = 0x0;
	
	// timer_cfg, cont, enable
	RCS_TIMER_GRP0_TMR1->T0_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T1_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T2_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T3_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T4_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T5_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T6_CFG.value = 0x3;
	RCS_TIMER_GRP0_TMR1->T7_CFG.value = 0x3;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;

	for( loopCnt = 0; loopCnt < TIMER_TEST_ITER; loopCnt++)
	{
		// wait till timer expiry - all timer status bit is set
		do
		{
			write_rsm[0] = RCS_TIMER_GRP0_TMR1->STAT.value;
			
		} while(write_rsm[0] != 0xFF);
		
		// verify whether GPIO is toggled
		dram_buff[0] = RCS_TIMER_GRP0_GPIO->GPIO_CURR_OUT.value;
		if(loopCnt % 2 == 0 && dram_buff[0] == 0x0)
		{
				loopPassCnt++;
			
		}
		else if(dram_buff[0] == 0xFFFFFFFF)
		{
			loopPassCnt++;
		}
		
		dram_buff[2] =  loopPassCnt;
		
		// Toggle GPIO - may have to use rdWrVal since regs are not volatile
		RCS_TIMER_GRP0_TMR1->T0_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T0_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T1_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T1_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T2_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T2_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T3_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T3_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T4_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T4_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T5_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T5_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T6_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T6_GPIO_VAL.value);
		RCS_TIMER_GRP0_TMR1->T7_GPIO_VAL.value = ~(RCS_TIMER_GRP0_TMR1->T7_GPIO_VAL.value);
	
		// read config to clear status
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T0_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T1_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T2_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T3_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T4_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T5_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T6_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP0_TMR1->T7_CFG.value;
		
	}
	// timer_cfg, disable
	RCS_TIMER_GRP0_TMR1->T0_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T1_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T2_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T3_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T4_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T5_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T6_CFG.value = 0x0;
	RCS_TIMER_GRP0_TMR1->T7_CFG.value = 0x0;
			
	return 0;
	
}
uint32_t timerContGrp1Tim1Test()
{
	uint32_t loopCnt, loopPassCnt=0;
	// soft reset BFN
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x1;
	INTRINSIC_BARRIER; // HSD 16023407069 
	RCS_TIMER_GPREG->ICTRL.SOFT_RESET = 0x0;
	INTRINSIC_BARRIER;
	
	// All timer trigger, after 1ms
	RCS_TIMER_GRP1_TMR1->T0_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T1_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T2_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T3_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T4_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T5_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T6_TRIG.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T7_TRIG.value = 0x2710;
	
	// Timer interval register - no need to program in oneshot mode
	RCS_TIMER_GRP1_TMR1->T0_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T1_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T2_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T3_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T4_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T5_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T6_INTERVAL.value = 0x2710;
	RCS_TIMER_GRP1_TMR1->T7_INTERVAL.value = 0x2710;
	
	// GPIO grp0_inout, OUT
	RCS_TIMER_GRP1_GPIO->GPIO_INOUT.value = 0xFFFFFFFF;
	
	// GPIO set mask for timers
	RCS_TIMER_GRP1_TMR1->T0_GPIO_MASK.value = 0xF;
	RCS_TIMER_GRP1_TMR1->T1_GPIO_MASK.value = 0xF0;
	RCS_TIMER_GRP1_TMR1->T2_GPIO_MASK.value = 0xF00;
	RCS_TIMER_GRP1_TMR1->T3_GPIO_MASK.value = 0xF000;
	RCS_TIMER_GRP1_TMR1->T4_GPIO_MASK.value = 0xF0000;
	RCS_TIMER_GRP1_TMR1->T5_GPIO_MASK.value = 0xF00000;
	RCS_TIMER_GRP1_TMR1->T6_GPIO_MASK.value = 0xF000000;
	RCS_TIMER_GRP1_TMR1->T7_GPIO_MASK.value = 0xF0000000;
	
	// GPIO_val for timer: The value to which the GPIO will be set
	RCS_TIMER_GRP1_TMR1->T0_GPIO_VAL.value = 0x0; // HSD16023770293
	RCS_TIMER_GRP1_TMR1->T1_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T2_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T3_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T4_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T5_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T6_GPIO_VAL.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T7_GPIO_VAL.value = 0x0;
	
	// timer_cfg, cont, enable
	RCS_TIMER_GRP1_TMR1->T0_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T1_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T2_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T3_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T4_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T5_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T6_CFG.value = 0x3;
	RCS_TIMER_GRP1_TMR1->T7_CFG.value = 0x3;
	
	// ICNTRL -  trigger ISYNC, BFN should start
	// isync_trigger=1, ISYNC = 3 = timer_cmd , timer_cmd = 2 = init
	RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT;

	for( loopCnt = 0; loopCnt < TIMER_TEST_ITER; loopCnt++)
	{
		// wait till timer expiry - all timer status bit is set
		do
		{
			write_rsm[0] = RCS_TIMER_GRP1_TMR1->STAT.value;
			
		} while(write_rsm[0] != 0xFF);
		
		// verify whether GPIO is toggled
		dram_buff[0] = RCS_TIMER_GRP1_GPIO->GPIO_CURR_OUT.value;
		if(loopCnt % 2 == 0 && dram_buff[0] == 0x0)
		{
				loopPassCnt++;
			
		}
		else if(dram_buff[0] == 0xFFFFFFFF)
		{
			loopPassCnt++;
		}
		
		dram_buff[4] =  loopPassCnt;
		
		// Toggle GPIO - may have to use rdWrVal since regs are not volatile
		RCS_TIMER_GRP1_TMR1->T0_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T0_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T1_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T1_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T2_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T2_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T3_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T3_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T4_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T4_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T5_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T5_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T6_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T6_GPIO_VAL.value);
		RCS_TIMER_GRP1_TMR1->T7_GPIO_VAL.value = ~(RCS_TIMER_GRP1_TMR1->T7_GPIO_VAL.value);
	
		// read config to clear status
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T0_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T1_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T2_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T3_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T4_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T5_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T6_CFG.value;
		write_rsm[0] = RCS_TIMER_GRP1_TMR1->T7_CFG.value;
		
	}
	
	// timer_cfg, disable
	RCS_TIMER_GRP1_TMR1->T0_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T1_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T2_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T3_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T4_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T5_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T6_CFG.value = 0x0;
	RCS_TIMER_GRP1_TMR1->T7_CFG.value = 0x0;
		
	return 0;
	
}




