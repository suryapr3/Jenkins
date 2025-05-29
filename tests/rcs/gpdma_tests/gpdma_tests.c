/**************************************************************************
 ** INTEL CONFIDENTIAL
 ** Copyright 2008 - 2022 Intel Corporation All Rights Reserved.
 **
 ** The source code contained or described herein and all documents related to 
 ** the source code ("Material") are owned by Intel Corporation or its 
 ** suppliers or licensors. Title to the Material remains with 
 ** Intel Corporation or its suppliers and licensors. 
 ** The Material contains trade secrets and proprietary and confidential
 ** information of Intel or its suppliers and licensors. The Material is 
 ** protected by worldwide copyright and trade secret laws and treaty 
 ** provisions. No part of the Material may be used, copied, reproduced, 
 ** modified, published, uploaded, posted, transmitted, distributed, or 
 ** disclosed in any way without Intel's prior express written permission.
 **
 ** No license under any patent, copyright, trade secret or other 
 ** intellectual property right is granted to or conferred upon you by 
 ** disclosure or delivery of the Materials, either expressly, by implication, 
 ** inducement, estoppel or otherwise. Any license under such intellectual 
 ** property rights must be express and approved by Intel in writing.
 *************************************************************************/


#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_rcs.h>
#include <srp_dev_uapi.h>
#include <srpCliCommon.h>
#include <srp_block_ids.h>
#include <srp_vex.h>
#include "ve32_cell.h"
#include "ve32_tile_ctrl.h"
//#include "ve32_tile_cio2strm.h"
//#include "ve32_tile_strm2cio.h"
#include "car.h"
#include "logger.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"
//#include "producer.hive.h"
//#include "vex2rcs_prog.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define VMEM_COMPARE_SIZE  16


#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request
#define NUM_VEC_IN_BLK  3

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000 /* vmem of size 64kb starts from 0. dmem starts at the end of vmem physically */
#define MEM_COMPARE_SIZE  8

#define VMEM_OFFSET (0x30000)

#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_VE32_TILE_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_VE32_TILE_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define RSM_MEM_COMPARE_SIZE 0x100

int Rcs2Vex(int vexSrcCoreId,void *srp);
int rcsHaltResetLoad(void *srp, void *rcs_hdl);
int pollRsmFlagRcs(void *srp);
int gpdma_test_rsm_to_rsm(void *srp,uint8_t core_id);
int gpdma_test_rcs_to_vex(void *srp,uint8_t core_id);

int test_pattern[] ={0xA0A00000,0xB0B00000,0xC0C00000,0xD0D00000,0xE0E00000};
char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
int test_pattern_rsm[] = {0x11223344, 0x44332211, 0x55667788};
int test_pattern_dcode[] = {0x12345678, 0xaa55aa55, 0xaaaa5555};
int rsm_offset[] = {0x12900,0x1c900,0x26900,0x30900};
int dcode_offset[] = {0x26c60, 0x26c00,0x45c60};
int dcode_offset_2d[] = {0x28c60, 0x28c00,0x47060};
int rsm_flag_addr[] = {0x3ffec,0x3FFF4, 0x3FFF0, 0x3FFF8,0x3FFFc};
int rsm_offset_2d[] = {0x10200, 0x1cab0,0x26960};
int rsm_flag[] = {0x5588, 0x4488, 0x8877,0x7788,0};

int flags = 0;
// Data type to hold table for NOC data
typedef struct noc_tbl_s {
	unsigned  address;
	unsigned  value;
	unsigned  core;
} noc_tbl_t;
unsigned int  test_pattern_vmem[] = {0x33334444, 0x55556666};
unsigned int  test_pattern_vmem_rx[] = {0x33334444, 0x11112222};
unsigned int  test_pattern_vmem_cal[]= {0x33334444, 0x11112222};
/*unsigned int test_pattern_vmem[] = {	0x33334444, 0x11112222, 0x44445555, 0x22223333, 
  0x55556666, 0x33334444, 0x66667777, 0x44445555, 
  0x77778888, 0x55556666, 0x88889999, 0x66667777, 
  0x9999AAAA, 0x77778888, 0xAAAABBBB, 0x88889999 };

  unsigned int  test_pattern_vmem_rx[] = {	0x11111111, 0x11111111, 0x22222222, 0x22222222,
  0x33333333, 0x33333333, 0x44444444, 0x44444444,
  0x55555555, 0x55555555, 0x66666666, 0x66666666,
  0x77777777, 0x77777777, 0x88888888, 0x88888888};

  unsigned int  test_pattern_vmem_cal[] = {	0x11111111, 0x22222222, 0x22222222, 0x33333333,
  0x33333333, 0x44444444, 0x44444444, 0x55555555,
  0x55555555, 0x66666666, 0x66666666, 0x77777777,
  0x77777777, 0x88888888, 0x88888888, 0x99999999};*/

int static relese_reset_abc_noc(void *srp)
{
	int i;
	int rv = 0;
	int flags = 0;

	noc_tbl_t noc_config[] = {

		{ CAR_MEM_NOC_CLOCK_GATE_OFFSET /* 0x94 */ , 0, 0 /* not used */ },// abc_noc_clock_gate
		{ CAR_MEM_NOC_SOFT_RESET_OFFSET /* 0x98 */ , 0, 0 /* not used */ },// abc_noc_soft_reset
	};

	for(i = 0; i < ARRAY_SIZE(noc_config); i++)
	{
		rv = srp_dev_block_write32(srp, SRP_BLOCK_VEX_CFG_CTRL, 0, noc_config[i].address,
				&noc_config[i].value,
				1,
				flags);
	}
	return rv;
}
#if 0
int static configure_noc(void *srp, int source_vex_id)
{
	int i;
	int rv = 0;
	int flags = 0;

	// Table with default NOC table to VE init
	noc_tbl_t noc_tbl[] = {
		//VE00->VE01 initialization

		//VE00 cio2strm
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_OFFSET /* 0x8010 */ ,0x00000001, source_vex_id },//FIFO_STATUS_CTL
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_OFFSET /* 0x8020 */ ,0x00000001, source_vex_id },//WORD_CNT_CTL
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_RANGE_EN_OFFSET /* 0x8060 */ ,0x00000001, source_vex_id },//RANGE_EN -all ranges enabled

		//Range1 -default set to Zero
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_OFFSET /* 0x8080 */ ,0x00000000, source_vex_id },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_OFFSET /* 0x80C0 */ ,0x0001FFFF, source_vex_id },//MEM_ADDR_HIGH[0]
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_OFFSET /* 0x8100 */ ,0x00000000, source_vex_id },//MEM_OFFSET[0]- is in words
		{ VE32_TILE_CIO2STRM_OFFSET + VE32_TILE_CIO2STRM_MEM_CIO2STRM_STRM_DEST0_OFFSET /* 0x8140 */ ,116, source_vex_id },//STRM_DEST[0] - mapped to VE01


		//Load the pointer copy address for the SDFGates
		//{ VE32_CELL_MEM_LM_BPCA_BP_DMEM_OFFSET /* 0xdc */ ,HIVE_ADDR_consumer_prog_consumer_sm_gate, dest_vex_id },//lm_bpca_bp_dmem - mapped to VE01

		//VE00 strm2cio
		//{ 0x8010,0x00000001, source_vex_id },//FIFO_STATUS_CTL
		//{ 0x8020,0x00000001, source_vex_id },//WORD_CNT_CTL
		//{ 0x8010,0x00000001, source_vex_id },//FIFO_STATUS_CTL
		//{ 0x8020,0x00000001, source_vex_id },//WORD_CNT_CTL
	};

	for(i = 0; i < ARRAY_SIZE(noc_tbl); i++)
	{
		rv = srp_dev_block_write32(srp,
				SRP_BLOCK_VEX_CORE /*BlockVal*/,
				noc_tbl[i].core/*IndexVal+1*/,
				noc_tbl[i].address,
				&noc_tbl[i].value,
				1,
				flags);
		if (rv)
		{
			print("\n Vijay rv = %d \n", rv);
		}
	}
	return rv;
}

#endif

int main(int argc, const char * argv[])
{
	int rv;
	int errCnt=0,i;
	int dev_id = 0;

	int dataCnt=0;
	int rcs_ctrl = 0; 

	unsigned Val_out[MEM_COMPARE_SIZE] =  {0};
	unsigned data_tx=0;

	srp_hdl_t srp_hdl = NULL;
	srp_dev_config_t srp_cfg = { 0 };

	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;


	print("Host: main starts!\n");
	init();
	v2d_clk_enable(0xFF, 0xFF);
	srp_dev_config(dev_id, srp, &srp_cfg, &srp_hdl);

	// halt and soft reset all cores
	rcsHaltsoftReset();

	// poll for memory init done

	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/gpdma_test/ax_hw.elf"; // core0
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/gpdma_test/rx_hw.elf"; // core1
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/gpdma_test/tx_hw.elf";
	rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/gpdma_test/cal_hw.elf";

	print("calling srp_rcs_config...\n");

	srp_rcs_config(srp_hdl, &rcs_params);

	sleep (1);

	// start core0
	srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_AX);  
	srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_RX);
	srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_TX);
	srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CALIB); 

	for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId < 4; rcsCoreId++)
	{	


		for ( i = 0; i < 1; i++)
		{
			gpdma_test_rsm_to_rsm(srp,rcsCoreId);



		}

	}



}

int rcsHaltsoftReset(void)
{
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	unsigned rcs_ctrl = 0;
	int rv;

	rcs_gpreg_rcs_config_reg_t  rcs_config_reg = {.value = RCS_GPREG_RCS_CONFIG_DEFAULT};
	rcs_gpreg_core0_control_reg_t core0_control_reg = {.value = RCS_GPREG_CORE0_CONTROL_DEFAULT};
	rcs_gpreg_core1_control_reg_t core1_control_reg = {.value = RCS_GPREG_CORE1_CONTROL_DEFAULT};
	rcs_gpreg_core2_control_reg_t core2_control_reg = {.value = RCS_GPREG_CORE2_CONTROL_DEFAULT};
	rcs_gpreg_core3_control_reg_t core3_control_reg = {.value = RCS_GPREG_CORE3_CONTROL_DEFAULT};
	rcs_gpreg_soft_reset_reg_t soft_reset_reg = {.value = RCS_GPREG_SOFT_RESET_DEFAULT};

	// halt core0/1/2/3 
	write_reg_18a(RCS_GPREG_CORE0_CONTROL_ADR, RCS_GPREG_CORE0_CONTROL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE1_CONTROL_ADR, RCS_GPREG_CORE1_CONTROL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE1_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE2_CONTROL_ADR, RCS_GPREG_CORE2_CONTROL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE2_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE3_CONTROL_ADR, RCS_GPREG_CORE3_CONTROL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE3_CONTROL_ADR");

	// enable soft reset 
	rcs_config_reg.RESERVED = 0xFA;
	write_reg_18a(RCS_GPREG_RCS_CONFIG_ADR, rcs_config_reg.value,0xFFFFFFFF, "RCS_GPREG_RCS_CONFIG_ADR");

	// soft reset all cores
	soft_reset_reg.CORE0_CPU_SFT_RST = 0x1;
	soft_reset_reg.CORE1_CPU_SFT_RST = 0x1;
	soft_reset_reg.CORE2_CPU_SFT_RST = 0x1;
	soft_reset_reg.CORE3_CPU_SFT_RST = 0x1;
	write_reg_18a(RCS_GPREG_SOFT_RESET_ADR, soft_reset_reg.value,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

	sleep(1);

	// remove soft reset of all cores
	write_reg_18a(RCS_GPREG_SOFT_RESET_ADR, RCS_GPREG_SOFT_RESET_DEFAULT,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

	sleep(1);

}
int pollRsmFlagRcs(void *srp)
{
	int Val_out = 0;
	int rv;
	// wait for core0 to complete the task
	// poll for the RSM location
	do
	{
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[0],
						&Val_out,
						0x1,
						flags)))
			return rv;
		sleep(1);
	} while (Val_out != 0x1234);
#if 1
	// wait for core1 to complete the task
	// poll for the RSM location
	do
	{
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[1],
						&Val_out,
						0x1,
						flags)))
			return rv;
		sleep(1);
	} while (Val_out != 0x5678);

	// wait for core2 to complete the task
	// poll for the RSM location
	do
	{
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[2],
						&Val_out,
						0x1,
						flags)))
			return rv;
		sleep(1);
	} while (Val_out != 0xABCD);	
#endif 
}		
int gpdma_test_rsm_to_rsm(void *srp,uint8_t core_id)
{
	int rv;

	int errCnt=0;
	int dataCnt=0;
	int Val_out=0,Eal_out=0,Dal_out=0;
	int Cnt=0,i=0;
	int rcs_ctrl = 1,rsm_reset = 0x300,rsm_reset_rel=0x0; 

	//while(i<0x20d0)
	while(i<0xd8)
	{
#if 1
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[core_id],
							&Val_out,
							0x1,
							flags)))
				return rv;
			//printf("Val_out:%x ,rsm_flag[core_id] %x\n",Val_out,rsm_flag[core_id]);
			sleep(1);
		} while ((Val_out != rsm_flag[core_id]));
		//clear rsm_tx_flag
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[core_id],
						&rsm_flag[4],
						0x1,
						flags)))
			return rv;
		/*if (Val_out==0x8855)
		  Cnt=1;
		  else
		  Cnt=1;*/
		//printf("loop%d\n",i);
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x118,
						&Val_out,
						1,
						flags)))
			return rv;



		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x11c,
						&Dal_out,
						1,
						flags)))
			return rv;
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x110,
						&Eal_out,
						1,
						flags)))
			return rv;

		//	printf("count %d,reg :%x,%x ,block:%x\n",i,Val_out ,Dal_out,Eal_out);


#endif
		for (dataCnt = 0; dataCnt < RSM_MEM_COMPARE_SIZE; dataCnt++)
		{
			uint32_t data_tx=0,data_rx=0;

			//Read rsm destination location from RCS
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_offset[core_id] + (dataCnt *4),
							&data_tx,
							1,
							flags)))
				return rv;
			if(data_tx != (test_pattern[core_id]|dataCnt))
			{
				if ((rv = srp_dev_block_read32(srp,
								SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
								0, /*IndexVal*/
								0x118,
								&Val_out,
								1,
								flags)))
					return rv;

				print("ERROR:reg_ctrl :%x ,test_pattern tx %x  , data %x , address %x \n",Val_out,test_pattern[core_id]|dataCnt, data_tx, rsm_offset[core_id] + (dataCnt*4) );
				errCnt++;

			}

		}			

		//if (core_id==2)
		//while(1);
		//write rsm flag core0

		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[4],
						&rsm_flag[core_id],
						1,
						flags)))
			return rv;
		i++;
	}
	if(errCnt==0)
	{
		print("Host:------ CORE %x: GPDMA TEST RSM TO RSM PASSED ,test_pattern: %x------\n",core_id,test_pattern[core_id]);
	}
	else
	{
		print("Host:------ CORE %x: GPDMA TEST RSM TO RSM  FAILED ------\n",core_id);
	}
}
//return errCnt;
//	}

int gpdma_test_rcs_to_vex(void *srp,uint8_t core_id)
{
	int rv;

	int errCnt=0;
	int dataCnt=0;
	int Val_out=0,reg_val,Eal_out=0,Dal_out=0;
	int Cnt=0,i=0,j=0,k=0,vex_offset=0x40000;
	int rcs_ctrl = 1,rsm_reset = 0x3000,rsm_reset_rel=0x0,destVexId=0; 
	// while(i<0x4000)
	while(i<0xd8)
	{
#if 1
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[core_id],
							&Val_out,
							0x1,
							flags)))
				return rv;
			sleep(1);
		} while ((Val_out != rsm_flag[core_id]));
		//clear rsm_tx_flag
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[core_id],
						&rsm_flag[4],
						0x1,
						flags)))
			return rv;

		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x118,
						&Val_out,
						1,
						flags)))
			return rv;



		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x11c,
						&Dal_out,
						1,
						flags)))
			return rv;
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
						0, /*IndexVal*/
						0x110,
						&Eal_out,
						1,
						flags)))
			return rv;

		//	print("count %d,reg :%x,%x ,block:%x\n",i,Val_out ,Dal_out,Eal_out);


#endif
		k=0;
		for (destVexId = 0; destVexId< 16; destVexId++)
		{

			for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
			{
				// read the data from VMEM
				if ((rv = srp_dev_block_read32(srp,
								SRP_BLOCK_VEX_CORE, /*BlockVal,*/
								destVexId, /*IndexVal*/
								(0x30000  + (dataCnt*4) ),
								&Val_out,
								1,
								flags)))
					return rv;
				//read the data from DMEM
				if ((rv = srp_dev_block_read32(srp,
								SRP_BLOCK_VEX_CORE, /*BlockVal,*/
								destVexId, /*IndexVal*/
								(0x28000 + (dataCnt*4) ),
								&Val_out,
								1,
								flags)))

					return rv;
				// read the data from PMEM
				if ((rv = srp_dev_block_read32(srp,
								SRP_BLOCK_VEX_CORE, /*BlockVal,*/
								destVexId, /*IndexVal*/
								(0x8000  + (dataCnt*4) ),
								&Val_out,
								1,
								flags)))

					return rv;

				if(((Val_out) != (test_pattern[core_id]|dataCnt))&&((Eal_out) != (test_pattern[core_id]|dataCnt))&&((Dal_out) != (test_pattern[core_id]|dataCnt)))
				{

					if ((rv = srp_dev_block_read32(srp,
									SRP_BLOCK_RCS_DMAC, /*BlockVal,*/
									0, /*IndexVal*/
									0x218,
									&reg_val,
									1,
									flags)))
						return rv;
					print("ERROR:reg_ctrl: %xtest_pattern[%d]: 0x%08x [0x%08x]  address :%x \n",reg_val,dataCnt, Val_out,(test_pattern[core_id]|dataCnt) ,0x30000  + (dataCnt*4));
					errCnt++;
				}


			}	
			k=k+1;

			// printf("k :%d\n",k);
		}		

		// printf("i :%d\n",i);
		//write rsm flag core0

		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[4],
						&rsm_flag[core_id],
						1,
						flags)))
			return rv;

		//printf("write tx flag\n");
		i++;
	}
	if(errCnt==0)
	{
		print("Host:------ CORE %x: GPDMA TEST RCS TO VEX AXI PASSED ,test_pattern: %x------\n",core_id,test_pattern[Cnt]);
	}
	else
	{
		print("Host:------ CORE %x: GPDMA TEST RCS TO VEX AXI FAILED ------\n",core_id);
	}
}
//return errCnt;
//	}


#if 0
int Rcs2Vex(int vexSrcCoreId,void *srp)
{

	int rv,i=0;
	int errCnt= 0,core_id=0;
	int dev_id = 0;
	void *rcs_hdl;
	srp_rcs_config_t rcs_params;
	srp_rcs_t srp_rcs_hdl;
	int dataCnt=0;
	int rcs_ctrl = 0; 
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	unsigned Val_out,destVexId=0;
	while(i<20)
	{
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[0],
							&Val_out,
							0x1,
							flags)))
				return rv;
			sleep(1);
		} while ((Val_out != 0x8855));

		//clear rsm_tx_flag
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[core_id],
						&rsm_flag[3],
						0x1,
						flags)))
			return rv;

		// read the data from VMEM
		for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
		{
			// read the data from VMEM

			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_VEX_CORE, /*BlockVal,*/
							destVexId, /*IndexVal*/
							0x30000 + (dataCnt*4),
							&Val_out,
							1,
							flags)))
				return rv;
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] adress %x\n", dataCnt, Val_out,0x88882222,0x30000 + (dataCnt*4) );
			if((Val_out)!= 0x88882222)
			{
				print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] adress %x\n", dataCnt, Val_out,0x88882222,0x30000 + (dataCnt*4) );
				errCnt++;
			}

		}


		if(errCnt==0)
		{
			print("Host:------ RCS core0 to VEX%d CRUX transfer Pass ------\n", destVexId);
		}
		else
		{
			print("Host:------ RCS core0 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
		}



		//write rsm flag core0

		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_RCS_RSM, /*BlockVal,*/
						0, /*IndexVal*/
						rsm_flag_addr[3],
						&rsm_flag[0],
						1,
						flags)))
			return rv;
		i++;	

		return errCnt;
	}

}
#endif
#if 1
int Rcs2Vex(int vexSrcCoreId,void *srp)
{

	int rv;
	int dev_id = 0;
	int flags = 0;
	void  *vex_hdl, *rcs_hdl;
	int errCnt1= 0,errCnt2= 0,errCnt3= 0 ;
	srp_vex_config_t vex_params;
	srp_vex_t srp_vex_hdl;
	srp_rcs_config_t rcs_params;
	srp_hdl_t srp_rcs_hdl;
	int dataCnt = 0, errCnt = 0;
	int sleepCnt;
	int rcs_ctrl = 0,destVexId=0; 
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	unsigned Val_out;
	int lc,i;

	int number_blocks = MAX_BLK_COUNT;
	int number_vec = (number_blocks * NUM_VEC_IN_BLK);
	unsigned int testPattern[96]; // 3kb data



	print("Host: main startssss!\n");
#if 0
	memset(&rcs_params, 0, sizeof(rcs_params));
	memset(&srp_rcs_hdl, 0, sizeof(srp_rcs_hdl));

	rcs_hdl = &srp_rcs_hdl;

	/* open the device */
	srp_dev_open(dev_id, flags, &srp);
	if ((rv = srp_rcs_config(srp, &rcs_hdl, &rcs_params)))
		return rv;

	rcsHaltResetLoad(srp, rcs_hdl);*/
		print("Host: main startssss!\n");
#endif
	// release abc noc from reset    
	// srpWrite 0x62.0.0x94 0x0
	// srpWrite 0x62.0.0x98 0x0
	rcs_ctrl = 0; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
					0, /*IndexVal*/
					0x94,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	rcs_ctrl = 0; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
					0, /*IndexVal*/
					0x98,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	// program dest vex core id into write_rsm of RCS. RCS uses this as dest id to program routing data.
	// for tx & cal fw, variable write_rsm found at addr 0x210000
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					0x10000,
					&destVexId,
					1,
					flags)))
		return rv;

	// enable strm2cio of vex 0
	// srpWrite 0x63.0.0xc010 0x1
	// srpWrite 0x63.0.0xc020 0x1
	rcs_ctrl = 1; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CORE, /*BlockVal,*/
					destVexId, /*IndexVal*/
					0x2010,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	rcs_ctrl = 1; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CORE, /*BlockVal,*/
					destVexId, /*IndexVal*/
					0x2020,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	// start core0
	//srp_rcs_rcp_start(rcs_hdl, SRP_RCS_RCP_0); // not working, check with Gary!
	rcs_ctrl = 0; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
					0, /*IndexVal*/
					0x8,
					&rcs_ctrl,
					1,
					flags)))
		return rv;
	while(1);
#if 0
	// poll till core0 execution is done
	pollRsmFlagRcs0(srp);
	print("Host: main startssss!\n");
	while(1);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

		if((Val_out) != (test_pattern_vmem[dataCnt]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem[dataCnt] );
			//errCnt1++;
		}


	}


	if(errCnt1==0)
	{
		print("Host:------ RCS core0 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core0 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}

	// Trigger core1 execution RSM shared flags
	Val_out = 0xC1C1;
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					rsm_flag_addr[3],
					&Val_out,
					0x1,
					flags)))
		return rv;


	// poll till core1 execution is done
	pollRsmFlagRcs1(srp);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

		if((Val_out) != (test_pattern_vmem_rx[dataCnt]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem_rx[dataCnt] );
			//errCnt2++;
		}


	}

	if(errCnt2==0)
	{
		print("Host:------ RCS core1 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core1 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}

	// Trigger core2 execution RSM shared flags
	Val_out = 0xC2C2;
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					rsm_flag_addr[3],
					&Val_out,
					0x1,
					flags)))
		return rv;


	// poll till core1 execution is done
	pollRsmFlagRcs2(srp);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

		if((Val_out) != (test_pattern_vmem_cal[dataCnt]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem_cal[dataCnt] );
			//errCnt3++;
		}


	}

	if(errCnt3==0)
	{
		print("Host:------ RCS core2 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core2 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}


	//return errCnt1+errCnt2+errCnt3;
#endif
}
#endif
#if 0
int vex2Rcs(int vexSrcCoreId)
{
	int rv;
	int dev_id = 0;
	int flags = 0;
	void *srp, *vex_hdl;
	srp_vex_config_t vex_params;
	srp_vex_t srp_vex_hdl;
	int lc,i;

	int number_blocks = MAX_BLK_COUNT;
	int number_vec = (number_blocks * NUM_VEC_IN_BLK);

	unsigned int testPattern[32] = {0x00000000, 0x11111111, 0x22222222, 0x33333333,
		0x44444444, 0x55555555, 0x66666666, 0x77777777,
		0x88888888, 0x99999999, 0xAAAAAAAA, 0xBBBBBBBB,
		0xCCCCCCCC, 0xDDDDDDDD, 0xEEEEEEEE, 0xFFFFFFFF,
		0x00001111, 0x22223333, 0x44445555, 0x66667777,
		0x88889999, 0xAAAABBBB, 0xCCCCDDDD, 0xEEEEFFFF,
		0x11110000, 0x33332222, 0x55554444, 0x77776666,
		0x99998888, 0xBBBBAAAA, 0xDDDDCCCC, 0xFFFFEEEE};

	int dmemOffset = 0x4000;

	/*int offsetVal[5] = {HIVE_ADDR_producer_prog_producer_max_count,
	  HIVE_ADDR_producer_prog_buffer_wa,
	  HIVE_ADDR_producer_prog_buffer_va,
	  HIVE_ADDR_producer_prog_producer_token_per_request,
	  HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)
	  };
	  unsigned Val_kargs[5] = {number_blocks,
	  (STRM2CIO_2_DMEM + HIVE_ADDR_consumer_prog_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)),
	  (STRM2CIO_2_VMEM + HIVE_ADDR_consumer_prog_buffer),
	  2,
	  0
	  };*/

	/*int offsetVal_2[4] = {HIVE_ADDR_consumer_prog_consumer_max_count,
	  HIVE_ADDR_consumer_prog_buffer_ra,
	  HIVE_ADDR_consumer_prog_consumer_token_per_request,
	  HIVE_ADDR_consumer_prog_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)
	  };
	  unsigned Val_kargs_2[4] = {number_blocks,
	  (STRM2CIO_2_DMEM + HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)),
	  5,
	  0
	  };*/

	unsigned Val_out[NUM_VEC_IN_BLK][NUM_OF_ELEMENTS_PER_VEC] =  {0};

	LOG_PRINT("INFO:logger begining !\n");

	memset(&vex_params, 0, sizeof(vex_params));
	memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));

	vex_hdl = &srp_vex_hdl;

	/* open the device */
	srp_dev_open(dev_id, flags, &srp);
	if ((rv = srp_vex_config(srp, &vex_hdl, &vex_params)))
		return rv;

	print("Host: start vex program load for cores (%d)\n", vexSrcCoreId);
	if ((rv = srp_vex_loader(vex_hdl, vexSrcCoreId, "../vex/sim_m64/vex2rcs_prog.fw")))
		return rv;


	print("Host: vex program load - done !!\n");
#if 0
	for (lc = 0; lc < ARRAY_SIZE(10); lc++) {
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						vexSrcCoreId, /*IndexVal*/
						dmemOffset + offsetVal[lc],
						&Val_kargs[lc],
						1,
						flags)))
			return rv;
	}

	for (lc = 0; lc < ARRAY_SIZE(offsetVal_2); lc++) {
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE /*BlockVal*/,
						vexDstCoreId/*IndexVal+1*/,
						dmemOffset + offsetVal_2[lc],
						&Val_kargs_2[lc],
						1,
						flags)))
			return rv;
	}
#endif
	if ((rv = configure_noc(srp, vexSrcCoreId)))
		return rv;

	if ((rv = relese_reset_abc_noc(srp)))
		return rv;

	// write the test_pattern into vex vmem
	for (lc = 0; lc <  32; lc++)
	{
		if ((rv = srp_dev_block_write32(srp,
						0x63, /*BlockVal,*/
						vexSrcCoreId, /*IndexVal*/
						VMEM_OFFSET  + (lc * 4),
						&testPattern[lc],
						1,
						flags)))
			return rv;	
	}

	print("Host: vex program start\n");
	srp_vex_start(vex_hdl, vexSrcCoreId, 0);

	//srp_cell_wait ?? - Issue - cell_wait kind of api nedded - applying sleep(2) temporary hack to check output

	sleep(2);
#if 0
	if ((rv = srp_vex_memid_load(vex_hdl,
					vexDstCoreId,
					SRP_VEX_VMEM,
					HIVE_ADDR_consumer_prog_gvecsum,/*local_addr*/
					Val_out[0],
					sizeof(Val_out))))
		return rv;

	//Load and compare vector output from cell to host
	print("Host:comparing result with reference -- vector \n");

	for(i=0;i<32;i++)
	{
		int ref_sum;
		//sum of 1...n numbers = (n * (n+1))/2)
		int n = number_vec;
		ref_sum = ((n*(n+1))/2);

		print("vecsum[%d]: ox%08x [ox%08x]\n", i, Val_out[0][i],ref_sum);

		if(((short)Val_out[0][i]) != ((short)ref_sum))
		{
			print("ERROR:vecsum[%d]: ox%08x [ox%08x] (diff = %d)\n", i, Val_out[0][i],ref_sum, (Val_out[0][i] - ref_sum) );
			rv =-1;
		}
	}

	if(rv==0)
	{
		print("Host:------ SUCCESS ------\n");
	}
	else
	{
		print("Host:------ FAILURE ------\n");
	}

	LOG_PRINT("INFO:logger ending !\n");
	return rv;
#endif
}
#endif
#if 0
int Rcs2Vex(int vexSrcCoreId,void *srp)
{

	int rv;
	int errCnt= 0;
	int dev_id = 0;
	void *rcs_hdl;
	srp_rcs_config_t rcs_params;
	srp_rcs_t srp_rcs_hdl;
	int dataCnt=0;
	int rcs_ctrl = 0; 
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	unsigned Val_out,destVexId=0;
	// release abc noc from reset    
	// srpWrite 0x62.0.0x94 0x0
	// srpWrite 0x62.0.0x98 0x0
	rcs_ctrl = 0; 

	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
					0, /*IndexVal*/
					0x94,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	rcs_ctrl = 0; 

	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
					0, /*IndexVal*/
					0x98,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	// program dest vex core id into write_rsm of RCS. RCS uses this as dest id to program routing data.
	// for tx & cal fw, variable write_rsm found at addr 0x210000
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					0x10000,
					&destVexId,
					1,
					flags)))
		return rv;

	// enable strm2cio of vex 0
	// srpWrite 0x63.0.0xc010 0x1
	// srpWrite 0x63.0.0xc020 0x1
	rcs_ctrl = 1; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CORE, /*BlockVal,*/
					destVexId, /*IndexVal*/
					0xC010,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	rcs_ctrl = 1; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_VEX_CORE, /*BlockVal,*/
					destVexId, /*IndexVal*/
					0xC020,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	// start core0
	//srp_rcs_rcp_start(rcs_hdl, SRP_RCS_RCP_CTRL_TX); // not working, check with Gary!
	rcs_ctrl = 0; 
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
					0, /*IndexVal*/
					0x8,
					&rcs_ctrl,
					1,
					flags)))
		return rv;

	// poll till core0 execution is done
	pollRsmFlagRcs0(srp);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

		if((Val_out) != (test_pattern_vmem[0])&&(Val_out) != (test_pattern_vmem[1]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] adress %x\n", dataCnt, Val_out,test_pattern_vmem[0],0x30000 + (dataCnt*4) );
			errCnt++;
		}

	}


	if(errCnt==0)
	{
		print("Host:------ RCS core0 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core0 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}

	// Trigger core1 execution RSM shared flags
	Val_out = 0xC1C1;
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					rsm_flag_addr[3],
					&Val_out,
					0x1,
					flags)))
		return rv;


	// poll till core1 execution is done
	pollRsmFlagRcs1(srp);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;


		if((Val_out) != (test_pattern_vmem[0])&&(Val_out) != (test_pattern_vmem[1]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] adress %x\n", dataCnt, Val_out,test_pattern_vmem[0],0x30000 + (dataCnt*4) );
			errCnt++;
		}


	}

	if(errCnt==0)
	{
		print("Host:------ RCS core1 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core1 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}

	// Trigger core2 execution RSM shared flags
	Val_out = 0xC2C2;
	if ((rv = srp_dev_block_write32(srp,
					SRP_BLOCK_RCS_RSM, /*BlockVal,*/
					0, /*IndexVal*/
					rsm_flag_addr[3],
					&Val_out,
					0x1,
					flags)))
		return rv;


	// poll till core1 execution is done
	pollRsmFlagRcs2(srp);

	sleep(2);
	// wait till transfer is done - check for push data bit to clear 
	// srpRead 0x1c.0.0x50 0x1

	// read the data from VMEM
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_read32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

		if((Val_out) != (test_pattern_vmem[0])&&(Val_out) != (test_pattern_vmem[1]))
		{
			print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] adress %x\n", dataCnt, Val_out,test_pattern_vmem[0],0x30000 + (dataCnt*4) );
			errCnt++;
		}


	}

	if(errCnt==0)
	{
		print("Host:------ RCS core2 to VEX%d CRUX transfer Pass ------\n", destVexId);
	}
	else
	{
		print("Host:------ RCS core2 to VEX%d CRUX transfer FAILED!!! ------\n", destVexId);
	}


	// Clear the VMEM after the test for the next iteration
	Val_out = 0;
	for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
	{
		// read the data from VMEM
		if ((rv = srp_dev_block_write32(srp,
						SRP_BLOCK_VEX_CORE, /*BlockVal,*/
						destVexId, /*IndexVal*/
						0x30000 + (dataCnt*4),
						&Val_out,
						1,
						flags)))
			return rv;

	}


	return errCnt;
#endif
	int pollRsmFlagRcs0(void *srp)
	{
		int Val_out = 0, sleepCnt = 1;
		int rv;
		// wait for core0 to complete the task
		// poll for the RSM location
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[0], // TX core flag for handshake with host
							&Val_out,
							0x1,
							flags)))
				return rv;
			sleep(1);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE0 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
		} while (Val_out != 0xD0C0);	
	}		

	int pollRsmFlagRcs1(void *srp)
	{
		int Val_out = 0, sleepCnt = 1;
		int rv;
		// wait for core0 to complete the task
		// poll for the RSM location
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[1], // rx core flag for handshake with host
							&Val_out,
							0x1,
							flags)))
				return rv;
			sleep(1);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE1 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
		} while (Val_out != 0xD0C1);	

	}

	int pollRsmFlagRcs2(void *srp)
	{
		int Val_out = 0, sleepCnt = 1;
		int rv;
		// wait for core0 to complete the task
		// poll for the RSM location
		do
		{
			if ((rv = srp_dev_block_read32(srp,
							SRP_BLOCK_RCS_RSM, /*BlockVal,*/
							0, /*IndexVal*/
							rsm_flag_addr[1], // rx core flag for handshake with host
							&Val_out,
							0x1,
							flags)))
				return rv;
			sleep(1);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE2 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
		} while (Val_out != 0xD0C2);	

	}		


