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
#include <stdint.h>
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
volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.cal.rw")));
volatile uint64_t __attribute__ ((section (".sram.ax.rw"))) crux_source_buffer[512];
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) x_source_buffer[1024]; // 2k samples.
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) x_dest_buffer[1024];   // 2k samples.
volatile  gpdma_desc_t __attribute__ ((section (".sram.ax.rw"))) descr_buffer[100];
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t dram_txdata[SIZE]  __attribute__((section(".dram0.data")));
volatile uint32_t* x_source_buffer_dmem = (uint32_t*)0x2804000; 
volatile uint32_t* x_source_buffer_pmem = (uint32_t*)0x2808000; 
volatile uint32_t* x_source_buffer_vmem = (uint32_t*)0x02828000;
volatile uint32_t* crux_wdata = (uint32_t*)0x00278000 ;
volatile uint32_t status_var[10];


uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
unsigned int g_test_val = 0;

void com_irq_handler (void *arg);
void interrupt_test();


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
    rsm_tx_shared_flag=0x1234;

}

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

	//gpdma_set_descr (0, (uint32_t)x_dest_buffer, ((uint32_t)x_source_buffer),block_size);
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
	rcs_dmac_ch1_blk_ts_reg_t block_ts_reg={.value = (uint32_t)block_size};
	*RCS_DMAC_CH1_BLK_TS_REG=block_ts_reg;

	// Channel configration.
	*RCS_DMAC_CH2_CFG_REG = dmac_ch2_cfg_reg;
	*RCS_DMAC_CH2_CTL_REG = dmac_ch2_ctl_reg;


	// destination and source adresss.
	rcs_dmac_ch2_sar_reg_t sar_reg2={.value =(uint32_t)x_source_buffer};
	*RCS_DMAC_CH2_SAR_REG=sar_reg2;   
	rcs_dmac_ch2_dar_reg_t dar_reg2={.value = (uint32_t)x_dest_buffer};
	*RCS_DMAC_CH2_DAR_REG=dar_reg2;
	rcs_dmac_ch2_blk_ts_reg_t block_ts_reg2={.value = (uint32_t)block_size};
	*RCS_DMAC_CH2_BLK_TS_REG=block_ts_reg2;

   
	if(dmac_channel==0)
	{ 
		// Channel 1 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH1_EN = 1;
		chen_reg.CH1_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg; 		
		
		//Wait till the transfer is done
		rcs_dmac_ch1_intstat_reg_t rcs_dmac_ch1_intstat_reg = *(RCS_DMAC_CH1_INTSTAT_REG);	       
		while ((rcs_dmac_ch1_intstat_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch1_intstat_reg = *(RCS_DMAC_CH1_INTSTAT_REG);
			//rsm_tx_shared_flag=rcs_dmac_ch1_intstat_reg.value;
		}
		//clear INTSTATUS REG   
		rcs_dmac_ch1_intclrreg_reg_t rcs_dmac_ch1_intclrreg_reg = {.value = 0};
	    *RCS_DMAC_CH1_INTCLRREG_REG = rcs_dmac_ch1_intclrreg_reg;
	}
	else
	{
		// Channel 2 enabl
		rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
		chen_reg.CH2_EN = 1;
		chen_reg.CH2_EN_WE = 1;
		*RCS_DMAC_CHENREG_REG = chen_reg;	
		//Wait till the transfer is done
		rcs_dmac_ch2_intstat_reg_t rcs_dmac_ch2_intstat_reg = *(RCS_DMAC_CH2_INTSTAT_REG);	       
		while ((rcs_dmac_ch2_intstat_reg.value & 0x1)!=0x1)
		{
			com_timing_wait_ns(100);
			rcs_dmac_ch2_intstat_reg = *(RCS_DMAC_CH2_INTSTAT_REG);
		}
		//clear INTSTATUS REG
		rcs_dmac_ch2_intclrreg_reg_t rcs_dmac_ch2_intclrreg_reg = {.value = 0};
		*RCS_DMAC_CH2_INTCLRREG_REG = rcs_dmac_ch2_intclrreg_reg;

	}
	rsm_rx_shared_flag=0x4488;
	while(rsm_com_shared_flag!=0x4488); //host will update flag to 0x5588 after read
	rsm_com_shared_flag=0x0;
	//dmac reset
	*rcs_config_reg=0xFA000000;	
	*rsm_soft_reset=0x800;
	com_timing_wait_ns(100);
	*rsm_soft_reset=0x0;
	com_timing_wait_ns(100);

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

								//gpdma_test_LLI(dmac_channel[i],0,multiblock_type[3],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
								gpdma_test_single_block(dmac_channel[i],0,multiblock_type[0],block_size[k],src_msize[m],dst_msize[n],src_tr_width[o],dst_tr_width[p]);
							}
						}

					}
				}
			}
		}
	}
#endif 	

}

