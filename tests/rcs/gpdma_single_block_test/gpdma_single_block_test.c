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
//#include <srp_dev_uapi.h>
//#include <srpCliCommon.h>
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
int gpdma_test_rsm_to_DIGRF_capture_mem(void *srp,uint8_t core_id);


int test_pattern[] ={0xA0A00000,0xB0B00000,0xC0C00000,0xD0D00000,0xE0E00000};
char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
int test_pattern_rsm[] = {0x11223344, 0x44332211, 0x55667788};
int test_pattern_dcode[] = {0x12345678, 0xaa55aa55, 0xaaaa5555};
int rsm_offset[] = {0x11000,0x11000,0x11000,0x11000};
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
#if 0
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
	uint32_t rv;
	uint32_t errCnt=0;
	uint32_t dev_id = 0;	
	uint32_t dataCnt=0;
	uint32_t rcs_ctrl = 0; 	
	uint32_t Val_out[MEM_COMPARE_SIZE] =  {0};
	uint32_t data_tx=0,i;	

	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;    
	print("Host: main starts!\n");	
	init();	
	print("calling srp_config!\n");	
	// halt and soft reset all cores
	rcsHaltsoftReset();

	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));

	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/gpdma_single_block_test/ax_hw.elf"; // core0
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/gpdma_single_block_test/rx_hw.elf"; // core1
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/gpdma_single_block_test/tx_hw.elf";
	rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/gpdma_single_block_test/cal_hw.elf";

	print("calling srp_rcs_config...\n");

	rcs_config(&rcs_params);

	print("after calling srp_rcs_config...\n");

	sleep (1);

	// start core0
	rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
	rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);
	rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);
	rcs_rcp_start( SRP_RCS_RCP_CALIB); 
	for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId <4; rcsCoreId++)
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

	rcs_gpreg_rcs_cfg_reg_t  rcs_config_reg = {.value = RCS_GPREG_RCS_CFG_DEFAULT};
	rcs_gpreg_core0_ctrl_reg_t core0_control_reg = {.value = RCS_GPREG_CORE0_CTRL_DEFAULT};
	rcs_gpreg_core1_ctrl_reg_t core1_control_reg = {.value = RCS_GPREG_CORE1_CTRL_DEFAULT};
	rcs_gpreg_core2_ctrl_reg_t core2_control_reg = {.value = RCS_GPREG_CORE2_CTRL_DEFAULT};
	rcs_gpreg_core3_ctrl_reg_t core3_control_reg = {.value = RCS_GPREG_CORE3_CTRL_DEFAULT};
	rcs_gpreg_soft_rst_reg_t soft_reset_reg = {.value = RCS_GPREG_SOFT_RST_DEFAULT};

	// halt core0/1/2/3 
	write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE1_CTRL_ADR, RCS_GPREG_CORE1_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE1_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE2_CTRL_ADR, RCS_GPREG_CORE2_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE2_CONTROL_ADR");
	write_reg_18a(RCS_GPREG_CORE3_CTRL_ADR, RCS_GPREG_CORE3_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE3_CONTROL_ADR");

	// enable soft reset 
	rcs_config_reg.SOFT_RST_LOCK = 0xFA;
	write_reg_18a(RCS_GPREG_RCS_CFG_ADR, rcs_config_reg.value,0xFFFFFFFF, "RCS_GPREG_RCS_CONFIG_ADR");

	// soft reset core0
	core0_control_reg.SOFT_RESET_CORE0 = 0x1;
	write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, soft_reset_reg.value,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
	//soft reset core 1/2/3
	soft_reset_reg.CORE1_CPU_SFT_RST = 0x1;
	soft_reset_reg.CORE2_CPU_SFT_RST = 0x1;
	soft_reset_reg.CORE3_CPU_SFT_RST = 0x1;
	write_reg_18a(RCS_GPREG_SOFT_RST_ADR, soft_reset_reg.value,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

	sleep(1);

	// remove soft reset core0
	write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
	// remove soft reset of cores 1/2/3
	write_reg_18a(RCS_GPREG_SOFT_RST_ADR, RCS_GPREG_SOFT_RST_DEFAULT,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");

	sleep(1);


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
#endif
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

		printf("count %d,reg :%x,%x ,block:%x\n",i,Val_out ,Dal_out,Eal_out);


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

