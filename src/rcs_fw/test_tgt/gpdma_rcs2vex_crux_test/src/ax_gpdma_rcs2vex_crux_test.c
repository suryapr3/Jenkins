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


#include "com_event.h"
#include "rcs_gpreg.h"
#include "tx_tests.h"
#include "com_definitions.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "rcs_dmac.h"
#include "string.h"
#include "com_event.h"
#include "nsip_hbi.h"
#include "crux_intf.h"
#include "com_isr.h"
//#include "../inc/rcs2vex_transfer.h"
//#include "common_macro.h"



uint32_t const SIZE = 32;
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.ax.rw")));
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) crux_source_buffer[100];
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) x_source_buffer[1024]; // 2k samples.
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) x_dest_buffer[1024];   // 2k samples.
volatile  gpdma_desc_t __attribute__ ((section (".sram.ax.rw"))) descr_buffer[100];
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t dram_txdata[SIZE]  __attribute__((section(".dram0.data")));
volatile uint32_t* x_source_buffer_dmem = (uint32_t*)0x2804000; 
volatile uint32_t* x_source_buffer_pmem = (uint32_t*)0x2808000; 
volatile uint32_t* x_source_buffer_vmem = (uint32_t*)0x02828000;
volatile uint128_t* crux_wdata = (uint32_t*)0x00278000 ;
volatile uint32_t* dmac_ch1_int_en = (uint32_t*)0x00270190; 
//volatile uint32_t* dmac_ch1_int_en = (uint32_t*)0x00270048; 
volatile uint32_t* dmac_ch1_int_stat = (uint32_t*)0x00270180 ;
volatile uint32_t status_var[10];

void com_irq_handler (void *arg);
void interrupt_test();
uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
unsigned int g_test_val = 0;

uint32_t gpdma_test_rcs2vex_crux();


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/


#define GPDMA_CTL_LSB      ((4 << 8) | (4 << 11))  // 128-bit xfer.
#define GPDMA_CTL_MSB_LAST ((1 << 31) | (1 << 30)) // valid/Last descriptor.
#define GPDMA_CTL_MSB      (1 << 31)               // valid
#define GPDMA_BLOCK_TS     4096                     // 1024 * 128b = 4k samples.




/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
#if 1
void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size)
{

    gpdma_desc_t desc;
    memset ((void *)&desc, 0, sizeof (gpdma_desc_t));
    desc.sar_lsb = src_addr;
    desc.dar_lsb = dst_addr;
    desc.block_ts = block_size;
    desc.ctl = dmac_ch1_ctl_reg;
    if (desc_idx == 0)
	desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    desc.llp_lsb = (uint32_t)&descr_buffer[desc_idx + 1];
    memcpy (&descr_buffer[desc_idx], &desc, sizeof (gpdma_desc_t));

}
#endif
int main(int argc, char **argv)
{	
    xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();
    rsm_ax_shared_flag=0x0;
    gpdma_test_rcs2vex_crux();

    //start core 1
    rsm_rx_shared_flag=0x1234;
    return (0);
}

uint32_t gpdma_test_rcs2vex_crux()
{

    uint32_t Vex_id[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,32,34,36,38};
    uint32_t numVex_id =sizeof(Vex_id)/sizeof(Vex_id[0]);
    numVex_id=20;	
    for (int vex_core = 0; vex_core<numVex_id; vex_core++)	
    {					
	for (int dataCnt = 0; dataCnt<1024; dataCnt++)
	{
	    crux_source_buffer[dataCnt]=0xA0A00000|dataCnt;
	}
	dmac_ch1_ctl_reg.SRC_TR_WIDTH=2;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=2;
	dmac_ch1_ctl_reg.SRC_MSIZE=1;
	dmac_ch1_ctl_reg.DST_MSIZE=1;						
	gpdma_set_descr (0,(uint128_t)CRUX_INTF_WDATA0_R_REG,(uint64_t)crux_source_buffer,15);
	RCS_DMAC_CFGREG_REG->value = 1;

	// Channel configuration.
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;

	// Descr address.
	rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
	*RCS_DMAC_CH1_LLP_REG = llp_reg;

	// Channel 1 enabl
	rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
	chen_reg.CH1_EN = 1;
	chen_reg.CH1_EN_WE = 1;
	*RCS_DMAC_CHENREG_REG = chen_reg;   
	com_timing_wait_ns(1000);     

	// write crux data registers
	// routing data
	crux_intf_wrouting_data_r_reg_t crux_wrouting_reg = {.value = 0x0};
#if 1 // enable once 18A html is matching for the register:INTF_ID is removed
	crux_wrouting_reg.SOP = 0x1;
	crux_wrouting_reg.EOP = 0x1;
	crux_wrouting_reg.BYPASS = 0x1;

	//crux_wrouting_reg.HOST_ID = (uint16_t)write_rsm[0]; // Send to vex id programmed in write_rsm[0]
	crux_wrouting_reg.HOST_ID = Vex_id[vex_core];
	crux_wrouting_reg.ADDRESS = 0x0; // VMEM address in VEX0
	crux_wrouting_reg.FLIT_TYPE = 0x6; // 64 valid bytes in the streaming word
	*CRUX_INTF_WROUTING_DATA_R_REG = crux_wrouting_reg;
#endif
	//crux_wrouting_reg.value = 0x40000C6; // comment out once html matches
	*CRUX_INTF_WROUTING_DATA_R_REG = crux_wrouting_reg;

	// Configure RCS crux -> H2B_CREDIT_READY_CS - TBD from host
	nsip_hbi_h2b_credit_ready_cs_reg_t h2b_credit_ready_reg = {.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT};
	h2b_credit_ready_reg.MAX_CREDITS = 0x3;
	*(NSIP_HBI_H2B_CREDIT_READY_CS_REG(RCS_CRUX_NSIP_HBI_BASE)) = h2b_credit_ready_reg;
	// push the data
	crux_intf_tx_push_reg_t crux_tx_push = {.value = 0};
	crux_tx_push.PUSH = 0x1;
	*CRUX_INTF_TX_PUSH_REG = crux_tx_push;
    }
    //flag to let host start read
    rsm_ax_shared_flag=0x5588;
    //wait till host read
    while(rsm_com_shared_flag!=0x5588); 
    return 0;
}

