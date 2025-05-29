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

#include "logger.h"
#include "init.h"
#include "all_comps.h"

int rcsHaltResetLoad(void *srp, void *rcs_hdl);


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define RSM_MEM_COMPARE_SIZE  4
#define RSM_MEM_COMPARE_SIZE_CAL 0x10
#define REG_SIZE 4

#define MEM_COMPARE_SIZE  8

//char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
int pollRsmFlagRcs(void *srp,uint8_t core_id);
int test_pattern[] ={0x55555555,0xAAAAAAAA, 0x55555555,0xA5A5A5A5};
int rsm_offset[] = {0x210000, 0x218000, 0x220000,0x228000};
int rsm_flag_addr[] = {0x23ffec,0x23FFF4, 0x23FFF0, 0x23FFF8,0x23FFFc};
int rsm_flag[] = {0x8844, 0x7788,0x8844,0x8877};
int com_flag[] = {0x1122, 0x2233, 0x4433,0x6633};
int flags = 0;
int Val_out[] = {0};	

int main(int argc, const char * argv[])
{
	uint32_t rv;
	uint32_t errCnt=0,sleepCnt=0;
	uint32_t dev_id = 0;	
	uint32_t dataCnt=0;
	uint32_t rcs_ctrl = 0; 	
	uint32_t Val_out[MEM_COMPARE_SIZE] =  {0},buffer[RSM_MEM_COMPARE_SIZE]={0};
	uint32_t data_tx=0;	
		
	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;    
	print("Host: main starts!\n");	
	init();	
	print("calling srp_config!\n");	
	// halt and soft reset all cores
	rcsHaltsoftReset();
	
	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
	
	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/rsm_pcie_wr_core_rd/ax_hw.elf"; // core0
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/rsm_pcie_wr_core_rd/rx_hw.elf"; // core1
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/rsm_pcie_wr_core_rd/tx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/rsm_pcie_wr_core_rd/cal_hw.elf";
    
	print("calling srp_rcs_config...\n");
    
    rcs_config(&rcs_params);
    
    print("after calling srp_rcs_config...\n");
	
	sleep (1);
		
    // start core0
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);
    rcs_rcp_start( SRP_RCS_RCP_CALIB);  
       // write the data to dram Tx,Rx
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId <4; rcsCoreId++)
    {
		
		//Load and compare vector output from cell to host
		fill_buffer(buffer,RSM_MEM_COMPARE_SIZE,test_pattern[rcsCoreId]);	   		   
		write_mem_18a(rsm_offset[rcsCoreId],RSM_MEM_COMPARE_SIZE,buffer,"RSM_OFFESET");	
		//write_mem_18a(dcode_offset[rcsCoreId],DCODE_MEM_COMPARE_SIZE,test_pattern[rcsCoreId],"DCODE_OFFESET");	
		//write_mem_18a(dcode_offset[rcsCoreId],DCODE_MEM_COMPARE_SIZE,test_pattern[rcsCoreId],"DCODE_OFFESET");	
		//write_mem_18a(dcode_offset[rcsCoreId],DCODE_MEM_COMPARE_SIZE_CAL,test_pattern[rcsCoreId],"DCODE_OFFESET");   
		//write rsm flag core0
		fill_buffer(buffer,1,rsm_flag[rcsCoreId]);	
		write_mem_18a(rsm_flag_addr[rcsCoreId],1,buffer,"RSM_FLAG_WRITE");	
		sleep(2);
		//read rsm flag wriiten by rcs core
		do
		{
			readMem(rsm_flag_addr[4],REG_SIZE,&Val_out);
			//read_mem_18a(rsm_flag_addr[4],REG_SIZE,Val_out,"RSM_FLAG_READ");
			printf("Val_out%x\n",Val_out[0]);
			sleepCnt++;
			if(sleepCnt > 15)
				{
					print("Host:------ ERROR: RCS LX7 CORE%x FAILED TO READ ------\n",rcsCoreId);
					return;
				}
		}while(Val_out[0]!=com_flag[rcsCoreId]);
				
		if(Val_out[0]==com_flag[rcsCoreId])
		{
			print("Host:------ CORE %x DCODE write from PCIe Read  PASS ------\n",rcsCoreId);
		}
		else
		{
			print("Host:------ CORE %x DCODE write from PCIe Read FAILED!!! ------\n",rcsCoreId);
		}	
    }
	LOG_PRINT("INFO:logger ending !\n");
	return errCnt;
}
#if 0


    // write the data to RSM
    for (rcsCoreId = SRP_RCS_RCP_CTRL_TX; rcsCoreId < 3; rcsCoreId++)
    {
		
	

		// read the data
		for (dataCnt = 0; dataCnt <RSM_MEM_COMPARE_SIZE; dataCnt++)
		{
			unsigned data_tx,data_rx;
			//Load and compare vector output from cell to host
					
			/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
				   srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
				   srp_uint32_t *data, srp_size_t size);*/
			// above is not working, check with Gary Mcgee 	   
			
			if ((rv = srp_dev_block_write32(srp,
				SRP_BLOCK_RCS_RSM, /*BlockVal,*/
				0, /*IndexVal*/
						rsm_offset[rcsCoreId] + (dataCnt *4),
						&test_pattern[rcsCoreId],
						1,
						flags)))
			return rv;
			
			
		}
		 //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[rcsCoreId],
					&rsm_flag[rcsCoreId],
					0x1,
					flags)))
		return rv;
	sleep(1);

	//read rsm flag wriiten by core0
	if ((rv = srp_dev_block_read32(srp,
		SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		0, /*IndexVal*/
				rsm_flag_addr[3],
				&Val_out,
				0x1,
				flags)))
	return rv;			
	if(Val_out[0]==com_flag[rcsCoreId])
    {
        print("Host:------ RSM write from PCIe Read from core0 PASS ------\n");
    }
    else
    {
    	print("Host:------ RSM write from PCIe Read from core0 FAILED!!! ------\n");
    }
    // clear rsm host flag written by core 0 
     if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[3],
					&rsm_flag[3],
					0x1,
					flags)))
		return rv;
	// update rsm flag to indicate to rcs that host read is complete
     if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[rcsCoreId],
					&rsm_flag[rcsCoreId],
					0x1,
					flags)))
		return rv;
	pollRsmFlagRcs(srp,rcsCoreId);
	}
 
   
  
	LOG_PRINT("INFO:logger ending !\n");
	return errCnt;
}
#endif
int rcsHaltsoftReset(void)
{
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
int pollRsmFlagRcs(void *srp,uint8_t core_id)
{
	int Val_out = 0;
	int rv;
	// wait for core0 to complete the task
	// poll for the RSM location
		#if 1
	if(core_id==0)
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
		sleep(2);
	printf("loop\n");
	} while (Val_out != 0x8844);
	}

	
	if(core_id==1)
	{
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
		printf("loop2\n");
			
		sleep(1);
	} while (Val_out != 0x7788);
	}	
		#endif
#if 1
	if(core_id==2)
	{
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
		printf("loop3\n");
	} while (Val_out != 0x8877);	
}
#endif 


}		
		

