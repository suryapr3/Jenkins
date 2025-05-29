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
#include <srp_vex.h>
#include <srp_rcs.h>
//#include <srp_dev_uapi.h>
//#include <srpCliCommon.h>
#include <srp_block_ids.h>

#include "logger.h"

#include "cli.h"
#include "init.h"

#include "all_comps.h"
//#include "producer.hive.h"
#include "vex2rcs_prog.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request
#define NUM_VEC_IN_BLK  3
#define DCODE_MEM_COMPARE_SIZE 96

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000 /* vmem of size 64kb starts from 0. dmem starts at the end of vmem physically */

#define VMEM_OFFSET (0x28000)


#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

volatile unsigned long int* rcs_soft_reset = (unsigned long int*)0x26c02c ;
volatile unsigned long int* rcs_config_reg = (unsigned long int*)0x26c004 ;

int rcsHaltResetLoad(void *srp, void *rcs_hdl);
int pollRsmFlagRcs0(void *srp);
int pollRsmFlagRcs1(void *srp);
int pollRsmFlagRcs2(void *srp);

char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };

int rsm_offset[] = {0x10000, 0x20000, 0x30000};
int dcode_offset[] = {0x24030,0x24030, 0x24030, 0x44000};
int rsm_flag_addr[] = {0x3ffec,0x3FFF4, 0x3FFF0, 0x3FFF8,0x3FFFc,0x3FFe8};

int flags = 0;
// Data type to hold table for NOC data
typedef struct noc_tbl_s {
	unsigned  address;
	unsigned  value;
	unsigned  core;
} noc_tbl_t;



int static release_reset_abc_noc(void *srp)
{
	int i;
	int rv = 0;
	int flags = 0;
	
	noc_tbl_t noc_config[] = {

        { CAR_NOC_CLK_GATE_OFFSET /* 0x94 */ , 0, 0 /* not used */ },// abc_noc_clock_gate
        { CAR_NOC_SOFT_RST_OFFSET /* 0x98 */ , 0, 0 /* not used */ },// abc_noc_soft_reset
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
	
	printf("VE32_TILE_CIO2STRM_OFFSET = 0x%x \n", VE32_TILE_CIO2STRM_OFFSET);
	
	// Table with default NOC table to VE init
	noc_tbl_t noc_tbl[] = {
	//VE00->VE01 initialization

	//VE00 cio2strm
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET /* 0x8010 */ ,0x00000001, source_vex_id },//FIFO_STATUS_CTL
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET /* 0x8020 */ ,0x00000001, source_vex_id },//WORD_CNT_CTL
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET /* 0x8060 */ ,0x00000001, source_vex_id },//RANGE_EN -all ranges enabled

	//Range1 -default set to Zero
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET /* 0x8080 */ ,0x00000000, source_vex_id },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET /* 0x80C0 */ ,0x0001FFFF, source_vex_id },//MEM_ADDR_HIGH[0]
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET /* 0x8100 */ ,0x00000000, source_vex_id },//MEM_OFFSET[0]- is in words
		{ VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET /* 0x8140 */ ,118, source_vex_id },//STRM_DEST[0] - mapped to VE01


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
			print("\n NOC table  rv = %d \n", rv);
		}
	}
	return rv;
}
srp_st_t
check_status(void *dev_hdl)
{
	srp_st_t srp_st = SRP_ST_SUCCESS;
	int i;
	srp_uint32_t v32[8];

	SRP_CALL(srp_dev_block_read32(dev_hdl,
			SRP_BLOCK_RCS_GPREG_RCS,
			0,
			0x0,
			v32,
			8,
			0));

	printf("RCS GPREGG:\n");
	printf(" 0x%08x 0x%08x 0x%08x 0x%08x\n", v32[0], v32[1], v32[2], v32[3]);
	printf(" 0x%08x 0x%08x 0x%08x 0x%08x\n", v32[4], v32[5], v32[6], v32[7]);



srp_return:
	return srp_st;
}
int
main(int vexSrcCoreId)
{
	
	srp_st_t srp_st = SRP_ST_SUCCESS;
	//destVexId=0;
	int rv;
	int errCnt=0;
	int dev_id = 0;

	int dataCnt=0;
	int rcs_ctrl = 0; 

	int Val_out=0,sleepCnt =0;

	srp_config_t srp_cfg = { 0 };

	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;
	
	int flags = 0;
	void *vex_hdl, *rcs_hdl;
	srp_vex_config_t vex_params;
	//srp_vex_t srp_vex_hdl;
	int lc,i;

	unsigned data_tx=0;

	srp_hdl_t srp_hdl = NULL;
	
	
	int number_blocks = MAX_BLK_COUNT;
    int number_vec = (number_blocks * NUM_VEC_IN_BLK);
    unsigned int testPattern[96]; // 3kb data


	print("Host: main starts!\n");
	init();
	print("after init main starts!\n");
	


	
	// init the test pattern
	for(dataCnt = 0; dataCnt < 96; dataCnt++)
	{
		testPattern[dataCnt] = vexSrcCoreId + dataCnt;
	}

	memset(&vex_params, 0, sizeof(vex_params));
	//memset(&srp_vex_hdl, 0, sizeof(srp_vex_hdl));


    print("Host: start vex program load for cores (%d)\n", vexSrcCoreId);
	//if ((rv = srp_vex_loader(srp_hdl, vexSrcCoreId, "vex/sim_m64/vex2rcs_prog.fw")))
		//return rv;
    if ((rv = vex_loader(vexSrcCoreId, "vex/sim_m64/vex2rcs_prog.fw")))
        return rv;	
	
    print("Host: vex program load - done !!\n");
    
    if ((rv = configure_noc(srp, vexSrcCoreId)))
	return rv;
	/*resetting the VEC NOC*/
    if (rv = release_reset_abc_noc(srp))
    {
        printf("ERROR: reset_abc failed\n");
        return rv;
    }


	// write the test_pattern into vex vmem
	for (lc = 0; lc <  96; lc++)
    {
		if ((rv = srp_dev_block_write32(srp,
				0x63, /*BlockVal,*/
				vexSrcCoreId, /*IndexVal*/
						VMEM_OFFSET + HIVE_ADDR_vex2rcs_prog_vinput + (lc * 4),
						&testPattern[lc],
						1,
						flags)))
			return rv;	
    }
    
    // write B2H CREDIT CS register
    write_reg_18a(NSIP_HBI_B2H_CSR_CREDIT_CS_ADR(RCS_CRUX_NSIP_HBI_BASE),
                              0x8,
                              0xFFFFFFFF,
                              "B2H_CREDIT_CS");
	write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(RCS_CRUX_NSIP_HBI_BASE),
							  0xFFFFF,
							  0xFFFFFFFF,
							  "CM_0_INT_HIGH_EN");          
	write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(RCS_CRUX_NSIP_HBI_BASE),
							  0xFFFFF,
							  0xFFFFFFFF,
							  "CM_0_INT_LOW_EN");           
		

    print("Host: vex program start\n");
    vex_start(vexSrcCoreId, 0);
 	//while(1);
 	 print("Host: srp vex start done\n");
 	// while(1);

	// halt and soft reset all cores
	print("calling rcsHaltsoftReset\n");
	rcsHaltsoftReset();

	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));

	// poll for memory init done

	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/vex2rcs_transfer/ax_hw.elf"; // core0
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/vex2rcs_transfer/rx_hw.elf"; // core1
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/vex2rcs_transfer/tx_hw.elf";
	//rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/rcs2vex_transfer/cal_hw.elf";

	print("calling srp_rcs_config...\n");
    
    rcs_config(&rcs_params);
    
    print("after calling srp_rcs_config...\n");
    
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);
    //rcs_rcp_start( SRP_RCS_RCP_CTRL_CAL);
    
	// wait for all RCS cores to finish execution
	do
	{
		if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[4], // com flag for handshake with host
					&Val_out,
					0x1,
					flags)))
		return rv;
		printf("Val_out:%x  sleepCnt%d \n",Val_out,sleepCnt);
		sleep(1);
		sleepCnt++;
		if(sleepCnt > 15)
		{
			print("Host:------ ERROR: RCS Cores DIDNT FINISH EXECUTION!!! ------\n");
			return;
		}
		
	} while (Val_out != 0xC0C1C2);	
	// Read and compare data from RCS cores
	for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE; dataCnt++)
    {
		unsigned data_dram;
		if(dataCnt < 32) // Read and compare data from RCS tx core 
		{
			if ((rv = srp_dev_block_read32(srp,
				SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
				0, /*IndexVal*/
				dcode_offset[0] + (dataCnt *4),
				&data_dram,
				1,
				flags)))
			return rv;
			
			//print("ERROR:test_pattern RCS core0 0x%x  , data 0x%x address 0x%x \n",(vexSrcCoreId + dataCnt), data_dram, 0x24030 + (dataCnt*4) );
			if(data_dram != (vexSrcCoreId + dataCnt))
			{
				printf("ERROR:test_pattern RCS core0 0x%x  , data 0x%x address 0x%x \n",(vexSrcCoreId + dataCnt), data_dram, 0x24030 + (dataCnt*4) );
				errCnt++;
			}
			
		}
		

		// Read and compare data from RCS rx core
		else if ((dataCnt >= 32)  && (dataCnt < 64))
		{
			unsigned rx_dcode_offset;
			
			rx_dcode_offset = dcode_offset[1] + ( (dataCnt - 32) *4);
			//printf("\n rx_dcode_offset = 0x%x", rx_dcode_offset);
			
			if ((rv = srp_dev_block_read32(srp,
				SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
				1, /*IndexVal*/
				rx_dcode_offset,
				&data_dram,
				1,
				flags)))
			return rv;
			
			//print("\ntest_pattern RCS core1 0x%x  , data 0x%x address 0x%x \n",(vexSrcCoreId + dataCnt), data_dram, rx_dcode_offset );
			
			if(data_dram != (vexSrcCoreId + dataCnt))
			{
				printf("ERROR:test_pattern RCS core1 0x%x  , data 0x%x address 0x%x \n",(vexSrcCoreId + dataCnt), data_dram, rx_dcode_offset );
				errCnt++;
			}
		}
#if 1			
		else // Read and compare data from RCS cal core  
		{
			unsigned tx_dcode_offset;
			
			tx_dcode_offset = dcode_offset[2] + ( (dataCnt - 64) *4);
			//printf("\n cal_dcode_offset = 0x%x", cal_dcode_offset);
			
			if ((rv = srp_dev_block_read32(srp,
				SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
				2, /*IndexVal*/
				tx_dcode_offset,
				&data_dram,
				1,
				flags)))
			return rv;
			
			if(data_dram != (vexSrcCoreId + dataCnt))
			{
				printf("ERROR:test_pattern RCS core2 0x%x  , data 0x%x address 0x%x \n",(vexSrcCoreId + dataCnt), data_dram, tx_dcode_offset );
				errCnt++;
			}
		} 
#endif			   
    }
    
    // check fifo status to make sure fifo is empty
    int fifo_status=readReg(0x26c02c);
    printf("fifo_status %x\n",fifo_status);
	

    if(errCnt==0)
    {
        print("Host:------ VEX%d to RCS CRUX TRANSFER PASS ------\n", vexSrcCoreId);
    }
    else
    {
    	print("Host:------ VEX%d to RCS CRUX TRANSFER FAILURE!!! ------\n", vexSrcCoreId);
    }	
	//crux soft reset
	//writeReg(0x0026c02c,0x20000,0xFFFFFFFF);
	//*rcs_config_reg=0xFA000000;
	//*rcs_soft_reset=0x20000;
	sleep(1);
	//writeReg(0x0026c02c,0x0,0x0);
	//*rcs_soft_reset=0x0;

	LOG_PRINT("INFO:logger ending !\n");
	
	srp_return:
	if (srp_st != SRP_ST_SUCCESS) {
		srp_status_print("error", srp_st);
	}
	//while(1);
	return rv;
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
