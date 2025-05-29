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



uint32_t const SIZE = 32;
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.rx.rw")));
volatile uint64_t __attribute__ ((section (".sram.rx.rw"))) crux_source_buffer[512];
volatile uint32_t __attribute__ ((section (".sram.rx.rw"))) x_source_buffer[1024]; // 2k samples.
volatile uint32_t __attribute__ ((section (".sram.rx.rw"))) x_dest_buffer[1024];   // 2k samples.
volatile  gpdma_desc_t __attribute__ ((section (".sram.rx.rw"))) descr_buffer[100];
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_host_shared_flag __attribute__((section(".sram.host.flag")));
volatile uint32_t dram_txdata[SIZE]  __attribute__((section(".dram0.data")));
volatile uint32_t* x_source_buffer_dmem = (uint32_t*)0x2804000; 
volatile uint32_t* x_source_buffer_pmem = (uint32_t*)0x2808000; 
volatile uint32_t* x_source_buffer_vmem = (uint32_t*)0x02828000;
volatile uint128_t* crux_wdata = (uint32_t*)0x00278000 ;
volatile uint32_t status_var[10];


uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
unsigned int g_test_val = 0;



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
	if (desc_idx == 2)
		desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
	desc.llp_lsb = (uint32_t)&descr_buffer[desc_idx + 1];
	memcpy (&descr_buffer[desc_idx], &desc, sizeof (gpdma_desc_t));

}
#endif
#if 0
void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size )
{
	gpdma_desc_t desc;
	memset ((void *)&desc, 0, sizeof (gpdma_desc_t));
	desc.sar_lsb = src_addr;
	desc.dar_lsb = dst_addr;
	desc.block_ts = block_size;
	desc.ctl = dmac_ch1_ctl_reg;
	desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
	memcpy (&descr_buffer, &desc, sizeof (gpdma_desc_t));
}
#endif
int main(int argc, char **argv)
{	
	xthal_enable_interrupts();
	com_shared_mem_wait_for_ready ();
	do
	{	
		if(rsm_rx_shared_flag==0x1234)
			break;
		com_timing_wait_ns(10000);   

	}while(rsm_rx_shared_flag!=0x1234);
	gpdma_combinations_test();
	//gpdma_test();
	rsm_tx_shared_flag=0x1234;
	//gpdma_test_rcs2vex_crux(0);
	//gpdma_rcs_to_vex_mem();
	//rcs2vex_transfer_test();
	//vex2tx_transfer_test();
	//gpdma_test(0,3,512,1,1,3,3);
	return (0);
}
#if 1
int gpdma_test_shadow_mode(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
{

	for (int dataCnt = 0; dataCnt <1024; dataCnt++)
	{
		x_source_buffer[dataCnt] = 0xB0B00000|dataCnt; 
	}

	//config source/destination width,source/destination  msize , multiblock type for channel 1
	dmac_ch1_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch1_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch1_ctl_reg.DST_MSIZE=dst_msize; 
	dmac_ch1_cfg_reg.SRC_MULTBLK_TYPE=0;
	dmac_ch1_cfg_reg.DST_MULTBLK_TYPE=2;

	//config source/destination width,source/destination  msize , multiblock type for channel 2
	dmac_ch2_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch2_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch2_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch2_ctl_reg.DST_MSIZE=dst_msize;
	dmac_ch2_cfg_reg.SRC_MULTBLK_TYPE=multiblock_type;
	dmac_ch2_cfg_reg.DST_MULTBLK_TYPE=multiblock_type;

	//clear destination buffer
	memset (x_dest_buffer,0, 1024);

	//gpdma_set_descr (0, (uint32_t)x_dest_buffer, ((uint32_t)x_source_buffer),block_size);
	RCS_DMAC_CFGREG_REG->value = 1;

	// Channel configuration.
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	/*src_adrss=0x211900;
	 *dst_adrss=0x230000;
	 *ch1_block_ts=0x1f;*/
	// Descr address.
	rcs_dmac_ch1_sar_reg_t sar_reg={.value =(uint32_t)x_source_buffer};
	*RCS_DMAC_CH1_SAR_REG=sar_reg;   
	rcs_dmac_ch1_dar_reg_t dar_reg={.value = (uint32_t)x_dest_buffer};
	*RCS_DMAC_CH1_DAR_REG=dar_reg;
	rcs_dmac_ch1_block_ts_reg_t block_ts_reg={.value = (uint32_t)block_size};
	*RCS_DMAC_CH1_BLOCK_TS_REG=block_ts_reg;

	// Descr address.
	rcs_dmac_ch2_sar_reg_t sar_reg2={.value =(uint32_t)x_source_buffer};
	*RCS_DMAC_CH2_SAR_REG=sar_reg2;   
	rcs_dmac_ch2_dar_reg_t dar_reg2={.value = (uint32_t)x_dest_buffer};
	*RCS_DMAC_CH2_DAR_REG=dar_reg2;
	rcs_dmac_ch2_block_ts_reg_t block_ts_reg2={.value = (uint32_t)block_size};
	*RCS_DMAC_CH2_BLOCK_TS_REG=block_ts_reg2;

	dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID =1;
	dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_LAST =0;

	dmac_ch2_ctl_reg.SHADOWREG_OR_LLI_VALID =1;
	dmac_ch2_ctl_reg.SHADOWREG_OR_LLI_LAST =0;

	// Channel configuration.
	//*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	*RCS_DMAC_CH1_CTL_REG = (rcs_dmac_ch1_ctl_reg_t) dmac_ch1_ctl_reg.value;
	*RCS_DMAC_CH2_CTL_REG = (rcs_dmac_ch2_ctl_reg_t) dmac_ch2_ctl_reg.value;

	// Descr address.
	//rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
	//*RCS_DMAC_CH1_LLP_REG = llp_reg;
	// Channel 1 enabl
	/*  rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
	    chen_reg.CH1_EN = 1;
	    chen_reg.CH1_EN_WE = 1;
	 *RCS_DMAC_CHENREG_REG = chen_reg;
	 if(dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID ==0)
	 {
	 dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID =1;
	 dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_LAST =1;
	 }
	 *RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;
	// Channel 1 enabl
	rcs_dmac_chenreg_reg_t chen_reg1 = {.value = 0};
	chen_reg.CH1_EN = 1;
	chen_reg.CH1_EN_WE = 1;
	 *RCS_DMAC_CHENREG_REG = chen_reg1;*/

#if 1
	if(dmac_channel==0)
	{ 
		// Channel 1 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH1_EN = 1;
		chen_reg.CH1_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg; 
		//Wait till the transfer is done
		/*rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);	       
		  while ((rcs_dmac_ch1_intstatus_reg.value & 0x1)!=0x1)
		  {
		  com_timing_wait_ns(100);
		  rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
		  rsm_rx_shared_flag=rcs_dmac_ch1_intstatus_reg.value;
		  }
		//clear INTSTATUS REG   
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		 *RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;*/
	}
	else
	{
		// Channel 2 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH2_EN = 1;
		chen_reg.CH2_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg;		
		//Wait till the transfer is done
		/*rcs_dmac_ch2_intstatus_reg_t rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);	       
		  while ((rcs_dmac_ch2_intstatus_reg.value & 0x1)!=0x1)
		  {
		  com_timing_wait_ns(100);
		  rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);
		  }
		//clear INTSTATUS REG
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		 *RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;*/

	}
	if(dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID ==0||dmac_ch2_ctl_reg.SHADOWREG_OR_LLI_VALID ==0)
	{
		dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID =1;
		dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_LAST =1;
		dmac_ch2_ctl_reg.SHADOWREG_OR_LLI_VALID =1;
		dmac_ch2_ctl_reg.SHADOWREG_OR_LLI_LAST =1;
	}
	*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;
	*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;

	if(dmac_channel==0)
	{ 
		// Channel 1 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH1_EN = 1;
		chen_reg.CH1_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg; 
		//Wait till the transfer is done
		rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);	       
		while ((rcs_dmac_ch1_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
			rsm_rx_shared_flag=rcs_dmac_ch1_intstatus_reg.value;
		}
		//clear INTSTATUS REG   
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;
	}
	else
	{
		// Channel 2 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH2_EN = 1;
		chen_reg.CH2_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg;		
		//Wait till the transfer is done
		rcs_dmac_ch2_intstatus_reg_t rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);	       
		while ((rcs_dmac_ch2_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);
		}
		//clear INTSTATUS REG
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;

	}

#endif   

	rsm_rx_shared_flag=0x4488;
	while(rsm_com_shared_flag!=0x4488); //host will update flag to 0x4488 after read
	rsm_com_shared_flag=0x0;
	//while(1);
	//dmac reset
	rcs_config_reg=0xFA000000;	
	*rsm_soft_reset=0x800;
	com_timing_wait_ns(100);
	*rsm_soft_reset=0x0;
	com_timing_wait_ns(100);



}
#endif
#if 1
int gpdma_test_LLI(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
{

	//data fill to source buffer
	for (int dataCnt = 0; dataCnt <1024; dataCnt++)
	{
		x_source_buffer[dataCnt] = 0xB0B00000|dataCnt; 
	}
	//config source/destination width,source/destination  msize , multiblock type for channel 1
	dmac_ch1_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch1_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch1_ctl_reg.DST_MSIZE=dst_msize; 


	//config source/destination width,source/destination  msize , multiblock type for channel 2
	dmac_ch2_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch2_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch2_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch2_ctl_reg.DST_MSIZE=dst_msize;

	//clear destination buffer
	memset (x_dest_buffer,0, 1024);


	//fill descriptor
	gpdma_set_descr (0, (uint32_t)x_dest_buffer, ((uint32_t)x_source_buffer),block_size);
	//gpdma_set_descr (0, (uint32_t)0x03814000, ((uint32_t)x_source_buffer),block_size);



	RCS_DMAC_CFGREG_REG->value = 1;

	// Channel configurationfor channel 1
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;

	// Channel configuration for channel 2
	*RCS_DMAC_CH2_CFG_REG = dmac_ch2_cfg_reg;
	*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;

	// Descr address.
	rcs_dmac_ch1_llp_reg_t llp_reg_ch1 = {.value = (uint64_t)descr_buffer};
	*RCS_DMAC_CH1_LLP_REG = llp_reg_ch1;

	// Descr address.
	rcs_dmac_ch2_llp_reg_t llp_reg_ch2 = {.value = (uint64_t)descr_buffer};
	*RCS_DMAC_CH2_LLP_REG = llp_reg_ch2;


	if(dmac_channel==0)
	{ 
		// Channel 1 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH1_EN = 1;
		chen_reg.CH1_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg; 
		//Wait till the transfer is done
		rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);	       
		while ((rcs_dmac_ch1_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
			rsm_rx_shared_flag=rcs_dmac_ch1_intstatus_reg.value;
		}
		//clear INTSTATUS REG   
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;
	}
	else
	{
		// Channel 2 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH2_EN = 1;
		chen_reg.CH2_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg;		
		//Wait till the transfer is done
		rcs_dmac_ch2_intstatus_reg_t rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);	       
		while ((rcs_dmac_ch2_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);
		}
		//clear INTSTATUS REG
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;

	}




	rsm_rx_shared_flag=0x4488;
	while(rsm_com_shared_flag!=0x4488); //host will update flag to 0x4488 after read
	rsm_com_shared_flag=0x0;
	//dmac reset
	rcs_config_reg=0xFA000000;	
	*rsm_soft_reset=0x800;
	com_timing_wait_ns(100);
	*rsm_soft_reset=0x0;
	com_timing_wait_ns(100);

	//while(1);

}
#endif
#if 1
int gpdma_test_single_block(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
{

	for (int dataCnt = 0; dataCnt <1024; dataCnt++)
	{
		x_source_buffer[dataCnt] = 0xB0B00000|dataCnt; 
	}

	//config source/destination width,source/destination  msize , multiblock type for channel 1
	dmac_ch1_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch1_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch1_ctl_reg.DST_MSIZE=dst_msize; 
	dmac_ch1_cfg_reg.SRC_MULTBLK_TYPE=multiblock_type;
	dmac_ch1_cfg_reg.DST_MULTBLK_TYPE=multiblock_type;

	//config source/destination width,source/destination  msize , multiblock type for channel 2
	dmac_ch2_ctl_reg.SRC_TR_WIDTH=src_tr_width;
	dmac_ch2_ctl_reg.DST_TR_WIDTH=dst_tr_width;
	dmac_ch2_ctl_reg.SRC_MSIZE=src_msize;
	dmac_ch2_ctl_reg.DST_MSIZE=dst_msize;
	dmac_ch2_cfg_reg.SRC_MULTBLK_TYPE=multiblock_type;
	dmac_ch2_cfg_reg.DST_MULTBLK_TYPE=multiblock_type;

	//clear destination buffer
	memset (x_dest_buffer,0, 1024);

	gpdma_set_descr (0, (uint32_t)x_dest_buffer, ((uint32_t)x_source_buffer),block_size);
	RCS_DMAC_CFGREG_REG->value = 1;


	dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_VALID =0;
	dmac_ch1_ctl_reg.SHADOWREG_OR_LLI_LAST =0;

	// Channel configuration.
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;


	// Descr address.
	rcs_dmac_ch1_sar_reg_t sar_reg={.value =(uint32_t)x_source_buffer};
	*RCS_DMAC_CH1_SAR_REG=sar_reg;   
	rcs_dmac_ch1_dar_reg_t dar_reg={.value = (uint32_t)x_dest_buffer};
	*RCS_DMAC_CH1_DAR_REG=dar_reg;
	rcs_dmac_ch1_block_ts_reg_t block_ts_reg={.value = (uint32_t)block_size};
	*RCS_DMAC_CH1_BLOCK_TS_REG=block_ts_reg;

	// Channel configuration.
	*RCS_DMAC_CH2_CFG_REG = dmac_ch2_cfg_reg;
	*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;


	// Descr address.
	rcs_dmac_ch2_sar_reg_t sar_reg2={.value =(uint32_t)x_source_buffer};
	*RCS_DMAC_CH2_SAR_REG=sar_reg2;   
	rcs_dmac_ch2_dar_reg_t dar_reg2={.value = (uint32_t)x_dest_buffer};
	*RCS_DMAC_CH2_DAR_REG=dar_reg2;
	rcs_dmac_ch2_block_ts_reg_t block_ts_reg2={.value = (uint32_t)block_size};
	*RCS_DMAC_CH2_BLOCK_TS_REG=block_ts_reg2;


	if(dmac_channel==0)
	{ 
		// Channel 1 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH1_EN = 1;
		chen_reg.CH1_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg; 
		//Wait till the transfer is done
		rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);	       
		while ((rcs_dmac_ch1_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
			rsm_rx_shared_flag=rcs_dmac_ch1_intstatus_reg.value;
		}
		//clear INTSTATUS REG   
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;
	}
	else
	{
		// Channel 2 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH2_EN = 1;
		chen_reg.CH2_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg;		
		//Wait till the transfer is done
		rcs_dmac_ch2_intstatus_reg_t rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);	       
		while ((rcs_dmac_ch2_intstatus_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);
		}
		//clear INTSTATUS REG
		rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
		*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;

	}

}
#endif
#if 0
int gpdma_test()
{
#if 1  
	int block_size =0x4,d=0,mem_offset=0x40000; 
	for (int dataCnt = 0; dataCnt<1024; dataCnt++)
	{
		x_source_buffer[dataCnt]=0xB0B00000|dataCnt;	
	}

	dmac_ch1_ctl_reg.SRC_TR_WIDTH=4;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=4;
	dmac_ch1_ctl_reg.SRC_MSIZE=1;
	dmac_ch1_ctl_reg.DST_MSIZE=1;
	gpdma_set_descr (0, (uint32_t*)x_dest_buffer, ((uint32_t)x_source_buffer),0x4);
	gpdma_set_descr (1, (uint32_t*)x_dest_buffer+0x4, ((uint32_t)x_source_buffer),0x8);
	gpdma_set_descr (2, (uint32_t*)x_dest_buffer+0x10, ((uint32_t)x_source_buffer),0x10);

	/*gpdma_set_descr (0, (uint32_t*)0x2804000, ((uint32_t)x_source_buffer),block_size);
	  gpdma_set_descr (1, (uint32_t*)0x2808000, ((uint32_t)x_source_buffer),block_size);
	  gpdma_set_descr (2, (uint32_t*)0x2828000, ((uint32_t)x_source_buffer),block_size);*/


	RCS_DMAC_CFGREG_REG->value = 1;

	// Channel configuration.
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
	*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;

	// Descr address.
	rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
	*RCS_DMAC_CH1_LLP_REG = llp_reg;
	//*gpdma_ctl_reg=0x46200;


	// Channel 1 enabl
	rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
	chen_reg.CH1_EN = 1;
	chen_reg.CH1_EN_WE = 1;
	*RCS_DMAC_CHENREG_REG = chen_reg;

	// Channel configuration.
	//*RCS_DMAC_CH2_CFG_REG = dmac_ch2_cfg_reg;
	//*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;


	// Descr address.
	//rcs_dmac_ch2_llp_reg_t llp_reg2 = {.value = (uint64_t)descr_buffer};
	//*RCS_DMAC_CH2_LLP_REG = llp_reg2;

	//rcs_dmac_chenreg_reg_t chen_reg2 = {.value =0}; 
	//chen_reg2.CH2_EN = 1;
	//chen_reg2.CH2_EN_WE = 1;
	//*RCS_DMAC_CHENREG_REG = chen_reg2;


	do
	{	
		if((*gpdma_status_reg & 0x1 )==1)
			break;

	}while((*gpdma_status_reg & 0x1 )!=0x1); 
	*gpdma_intclear_reg=0x3;

	rsm_rx_shared_flag=0x4488;
	while(rsm_com_shared_flag!=0x4488); //host will update flag to 0x4488 after read
	rsm_com_shared_flag=0x0;
	//rsm reset
	rcs_config_reg=0xFA000000;
	for(int i=0;i<1000;i++);	
	*rsm_soft_reset=0x800;
	for(int i=0;i<1000;i++);
	*rsm_soft_reset=0x0;
	for(int i=0;i<1000;i++);

#endif
}
#endif
typedef enum{
	mem2mem,
	mem2per,
	per2mem,
	per2per
}TransferType;
typedef enum{
	contiguous,
	reload,
	shadowRegiser,
	LLI
}MultiblockType;	
typedef enum{
	ch1,
	ch2
}Dmac_Channel;	

int gpdma_combinations_test()
{

	TransferType transfer_type[]={mem2mem,mem2per,per2mem,per2per};
	MultiblockType multiblock_type[]={contiguous,reload,shadowRegiser,LLI};
	Dmac_Channel dmac_channel[]={ch1,ch2};
	/*uint32_t block_size[]={512,1023};
	  uint32_t src_msize[]={0,1,2,3,4,5,6,7,8,9};
	  uint32_t dst_msize[]={0,1,2,3,4,5,6,7,8,9};
	  uint32_t src_tr_width[]={0,1,2,3,4,5,6};
	  uint32_t dst_tr_width[]={0,1,2,3,4,5,6};*/

	/*uint32_t block_size[]={512};
	  uint32_t src_msize[]={0,1,2};
	  uint32_t dst_msize[]={0,1,2};
	  uint32_t src_tr_width[]={0,1,2};
	  uint32_t dst_tr_width[]={0,1,2};*/



	/*uint32_t block_size[]={512,1023};
	  uint32_t src_msize[]={2,3,4,5,6,7,8,9};
	  uint32_t dst_msize[]={2,3,4,5,6,7,8,9};
	  uint32_t src_tr_width[]={2,3,4,5,6};
	  uint32_t dst_tr_width[]={2,3,4,5,6};*/

	uint32_t block_size[]={512,1023};
	uint32_t src_msize[]={2,3,4};
	uint32_t dst_msize[]={2,3,4};
	uint32_t src_tr_width[]={2,3,4};
	uint32_t dst_tr_width[]={2,3,4};

	uint32_t numTransferTypes=sizeof(transfer_type)/sizeof(transfer_type[0]);
	uint32_t numMultiblock_type=sizeof(transfer_type)/sizeof(transfer_type[0]);
	uint32_t numDmac_Channel =sizeof(dmac_channel)/sizeof(dmac_channel[0]);
	uint32_t numBlocksize=sizeof(block_size)/sizeof(block_size[0]);
	uint32_t numSrc_msize=sizeof(src_msize)/sizeof(src_msize[0]);
	uint32_t numDst_msize=sizeof(dst_msize)/sizeof(dst_msize[0]);
	uint32_t numSrc_tr_width=sizeof(dst_tr_width)/sizeof(dst_tr_width[0]);
	uint32_t numDst_tr_width=sizeof(dst_tr_width)/sizeof(dst_tr_width[0]);
	gpdma_vex_vmem_config();

#if 1
	for(uint32_t i=0;i<numDmac_Channel;i++)
	{ 
		for(uint32_t j=0;j<1/*numMultiblock_type*/;j++)
		{
			for(uint32_t k=0;k<numBlocksize;k++)
			{
				for(uint32_t m=0;m<numSrc_msize;m++)
				{
					for(uint32_t n=0;n<numDst_msize;n++)
					{
						for(uint32_t o=1;o<numSrc_tr_width;o++)
						{
							for(uint32_t p=0;p<numDst_tr_width;p++)
							{

								gpdma_test_LLI(dmac_channel[i],0,multiblock_type[3],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								//gpdma_test_single_block(dmac_channel[i],0,multiblock_type[0],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								//gpdma_test_shadow_mode(dmac_channel[i],0,multiblock_type[0],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								//gpdma_rcs2vex_axi_test(dmac_channel[i],0,multiblock_type[0],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								//gpdma_vex2rcs_crux_test(0,multiblock_type[3],block_size[1],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								cnt++;
								rsm_cal_shared_flag=cnt;
							}
						}

					}
				}
			}
		}
	}
#endif 	


}
int gpdma_rcs2vex_axi_test(int dmac_channel,int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
{
	uint32_t mem_offset=0x40000,d=0;
	dmac_channel=1;
	for (int dataCnt = 0; dataCnt<16; dataCnt++)
	{

		for (int dataCnt = 0; dataCnt<1024; dataCnt++)
		{
			x_source_buffer[dataCnt]=0xB0B00000|dataCnt;	
		}

		dmac_ch2_ctl_reg.SRC_TR_WIDTH=src_tr_width;
		dmac_ch2_ctl_reg.DST_TR_WIDTH=dst_tr_width;
		dmac_ch2_ctl_reg.SRC_MSIZE=src_msize;
		dmac_ch2_ctl_reg.DST_MSIZE=dst_msize;
		dmac_ch1_ctl_reg.SRC_TR_WIDTH=src_tr_width;
		dmac_ch1_ctl_reg.DST_TR_WIDTH=src_tr_width;
		dmac_ch1_ctl_reg.SRC_MSIZE=src_msize;
		dmac_ch1_ctl_reg.DST_MSIZE=src_msize;


		//clear destination buffer
		memset ((uint32_t)x_source_buffer_dmem +(mem_offset*d) ,0, 1024);
		memset ((uint32_t)x_source_buffer_vmem +(mem_offset*d),0, 1024);
		memset ((uint32_t)x_source_buffer_pmem +(mem_offset*d),0, 1024);

		//gpdma_set_descr (0, (uint32_t*)0x2808000, ((uint32_t)x_source_buffer),block_size);
		gpdma_set_descr (0, (uint32_t)x_source_buffer_dmem +(mem_offset*d) , (uint32_t)x_source_buffer,block_size);
		gpdma_set_descr (1, (uint32_t)x_source_buffer_vmem +(mem_offset*d) , (uint32_t)x_source_buffer,block_size);
		gpdma_set_descr (2,(uint32_t)x_source_buffer_pmem +(mem_offset*d) , (uint32_t)x_source_buffer,block_size);
		d=d+1;
		RCS_DMAC_CFGREG_REG->value = 1;

		// Channel configurationfor channel 1
		*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;
		*RCS_DMAC_CH1_CTL_REG = dmac_ch1_ctl_reg;

		// Channel configuration for channel 2
		*RCS_DMAC_CH2_CFG_REG = dmac_ch2_cfg_reg;
		*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;

		// Descr address.
		rcs_dmac_ch1_llp_reg_t llp_reg_ch1 = {.value = (uint64_t)descr_buffer};
		*RCS_DMAC_CH1_LLP_REG = llp_reg_ch1;

		// Descr address.
		rcs_dmac_ch2_llp_reg_t llp_reg_ch2 = {.value = (uint64_t)descr_buffer};
		*RCS_DMAC_CH2_LLP_REG = llp_reg_ch2;


		if(dmac_channel==0)
		{ 
			// Channel 1 enabl
			rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
			chen_reg.CH1_EN = 1;
			chen_reg.CH1_EN_WE = 1;
			*RCS_DMAC_CHENREG_REG = chen_reg; 
			//Wait till the transfer is done
			rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);	       
			while ((rcs_dmac_ch1_intstatus_reg.value & 0x1)!=0x1)
			{
				com_timing_wait_ns(100);
				rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
				rsm_rx_shared_flag=rcs_dmac_ch1_intstatus_reg.value;
			}
			//clear INTSTATUS REG   
			rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
			*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;
		}
		else
		{
			// Channel 2 enabl
			rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
			chen_reg.CH2_EN = 1;
			chen_reg.CH2_EN_WE = 1;
			*RCS_DMAC_CHENREG_REG = chen_reg;		
			//Wait till the transfer is done
			rcs_dmac_ch2_intstatus_reg_t rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);	       
			while ((rcs_dmac_ch2_intstatus_reg.value & 0x1)!=0x1)
			{
				com_timing_wait_ns(100);
				rcs_dmac_ch2_intstatus_reg = *(RCS_DMAC_CH2_INTSTATUS_REG);
			}
			//clear INTSTATUS REG
			rcs_dmac_ch1_intclearreg_reg_t rcs_dmac_ch1_intclearreg_reg = {.value = 0};
			*RCS_DMAC_CH1_INTCLEARREG_REG = rcs_dmac_ch1_intclearreg_reg;

		}


	}   

	rsm_rx_shared_flag=0x4488;
	while(rsm_com_shared_flag!=0x4488); //host will update flag to 0x4488 after read
	rsm_com_shared_flag=0x0;
	//dmac reset
	rcs_config_reg=0xFA000000;	
	*rsm_soft_reset=0x800;
	com_timing_wait_ns(100);
	*rsm_soft_reset=0x0;
	com_timing_wait_ns(100);

	//while(1);

}
#if 0
//uint32_t gpdma_rcs2vex_crux_test(int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
uint32_t gpdma_test_rcs2vex_crux(uint32_t vex_id)
{


	/*x_source_buffer[] = {	0x1111222233334444, 0x2222333344445555,
	  0x3333444455556666, 0x4444555566667777,
	  0x5555666677778888, 0x6666777788889999,
	  0x777788889999AAAA, 0x88889999AAAABBBB};*/
	//gpdma_vex_vmem_config();							
	for (int dataCnt = 0; dataCnt<1024; dataCnt++)
	{
		crux_source_buffer[dataCnt]=0x1111222233335555;
	}
	dmac_ch1_ctl_reg.SRC_TR_WIDTH=4;
	dmac_ch1_ctl_reg.DST_TR_WIDTH=4;
	dmac_ch1_ctl_reg.SRC_MSIZE=1;
	dmac_ch1_ctl_reg.DST_MSIZE=1;						
	gpdma_set_descr (0,(uint64_t)crux_wdata,(uint64_t)crux_source_buffer,1024);
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
	// write crux data registers
	crux_intf_crux_wdata0_r_reg_t crux_wdata0_reg = {.value = 0x0};
	crux_wdata0_reg.DATA = U64_TO_U128(crux_wdata[1], crux_wdata[0]);
	*CRUX_INTF_CRUX_WDATA0_R_REG = crux_wdata0_reg;
	//*((CRUX_INTF_CRUX_WDATA0_R_ADR)) = 0x5566778899aabbcc;
	//*((CRUX_INTF_CRUX_WDATA0_R_ADR) + (0xC)) = (uint64_t)0x55667788;


	crux_intf_crux_wdata1_r_reg_t crux_wdata1_reg = {.value = 0};
	crux_wdata1_reg.DATA = U64_TO_U128(crux_wdata[3], crux_wdata[2]);
	*CRUX_INTF_CRUX_WDATA1_R_REG = crux_wdata1_reg;

	crux_intf_crux_wdata2_r_reg_t crux_wdata2_reg = {.value = 0};
	crux_wdata2_reg.DATA = U64_TO_U128(crux_wdata[5], crux_wdata[4]);
	*CRUX_INTF_CRUX_WDATA2_R_REG = crux_wdata2_reg;

	crux_intf_crux_wdata3_r_reg_t crux_wdata3_reg = {.value = 0};
	crux_wdata3_reg.DATA = U64_TO_U128(crux_wdata[7], crux_wdata[6]);
	*CRUX_INTF_CRUX_WDATA3_R_REG = crux_wdata3_reg;

	// routing data
	crux_intf_crux_wrouting_data_r_reg_t crux_wrouting_reg = {.value = 0x0};
#if 1 // enable once 18A html is matching for the register:INTF_ID is removed
	crux_wrouting_reg.SOP = 0x1;
	crux_wrouting_reg.EOP = 0x1;
	crux_wrouting_reg.BYPASS = 0x1;

	//crux_wrouting_reg.HOST_ID = (uint16_t)write_rsm[0]; // Send to vex id programmed in write_rsm[0]
	crux_wrouting_reg.HOST_ID = 0x0;
	crux_wrouting_reg.ADDRESS = 0x0; // VMEM address in VEX0
	crux_wrouting_reg.FLIT_TYPE = 0x6; // 64 valid bytes in the streaming word
	//crux_wrouting_reg.value=0x4000C6;
	rsm_rx_shared_flag=crux_wrouting_reg.value;
	*CRUX_INTF_CRUX_WROUTING_DATA_R_REG = crux_wrouting_reg;
#endif
	//crux_wrouting_reg.value = 0x40000C6; // comment out once html matches
	*CRUX_INTF_CRUX_WROUTING_DATA_R_REG = crux_wrouting_reg;

	// Configure RCS crux -> H2B_CREDIT_READY_CS - TBD from host
	nsip_hbi_h2b_credit_ready_cs_reg_t h2b_credit_ready_reg = {.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT};
	h2b_credit_ready_reg.MAX_CREDITS = 0x3;
	*(NSIP_HBI_H2B_CREDIT_READY_CS_REG(RCS_CRUX_NSIP_HBI_BASE)) = h2b_credit_ready_reg;
	// push the data
	crux_intf_crux_tx_push_reg_t crux_tx_push = {.value = 0};
	crux_tx_push.PUSH = 0x1;
	*CRUX_INTF_CRUX_TX_PUSH_REG = crux_tx_push;
	return 0;
}
#endif
#if 1
uint32_t gpdma_vex2rcs_crux_test(int transfer_type,int multiblock_type,int block_size,int src_msize,int dst_msize,int src_tr_width,int dst_tr_width)
{
	int waitCnt;

	crux_intf_crux_rdata0_r_reg_t crux_rdata0;
	crux_intf_crux_rdata1_r_reg_t crux_rdata1;
	crux_intf_crux_rdata2_r_reg_t crux_rdata2;
	crux_intf_crux_rdata3_r_reg_t crux_rdata3;

	//nsip_hbi_b2h_flit_count_reg_t b2h_flit_count_reg;
	crux_intf_crux_rx_pop_reg_t crux_tx_pop;

	// wait for flit count to be non zero
	// i.e VEX has written data to B2H interface
#if 0
	do
	{
		b2h_flit_count_reg = *(NSIP_HBI_H2B_FLIT_COUNT_REG(CRUX_NSIP_HBI_BASE));
		waitCnt++;
		if(waitCnt > 0xFFFFFFF)
		{
			rsm_com_shared_flag = 0xDEADC000; // VEX didnt write data, host to check and print error
			return 0;
		}

	} while (b2h_flit_count_reg.FLIT_COUNT != 6); // wait till VEX writes 6 FLITS
#endif
	// pop the data - 1024 bits for tx core
	// 512 bits per pop
	crux_tx_pop.POP = 0x1;
	crux_tx_pop=*CRUX_INTF_CRUX_RX_POP_REG;
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
	crux_rdata0 = *CRUX_INTF_CRUX_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_CRUX_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_CRUX_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_CRUX_RDATA3_R_REG;

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
	crux_tx_pop.POP = 0x1;
	*CRUX_INTF_CRUX_RX_POP_REG = crux_tx_pop;
#if 1
	// wait
	for(waitCnt = 0; waitCnt< 0xFF; waitCnt++)
	{
		rsm_com_shared_flag = waitCnt;
	}
#endif
	// read CRUX_INTF_CRUX_RDATA0_R_ADR
	crux_rdata0 = *CRUX_INTF_CRUX_RDATA0_R_REG;
	crux_rdata1 = *CRUX_INTF_CRUX_RDATA1_R_REG;
	crux_rdata2 = *CRUX_INTF_CRUX_RDATA2_R_REG;
	crux_rdata3 = *CRUX_INTF_CRUX_RDATA3_R_REG;

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


	gpdma_set_descr (0, (uint32_t)x_dest_buffer,0x002780a0,512);
	RCS_DMAC_CFGREG_REG->value = 1;

	// Channel configuration.
	*RCS_DMAC_CH1_CFG_REG = dmac_ch1_cfg_reg;

	// Descr address.
	rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
	*RCS_DMAC_CH1_LLP_REG = llp_reg;

	// Channel 1 enabl
	rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
	chen_reg.CH1_EN = 1;
	chen_reg.CH1_EN_WE = 1;
	*RCS_DMAC_CHENREG_REG = chen_reg;
	rsm_cal_shared_flag=0x2222;

	return 0;
}
#endif

int gpdma_vex_vmem_config()
{
	*reg_strm2cio_fifo_status_ctl=0x1;
	*reg_strm2cio_word_cnt_ctl=0x1;

}



