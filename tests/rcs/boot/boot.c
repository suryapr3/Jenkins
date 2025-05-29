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
#include "cli.h"
#include "logger.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MEM_COMPARE_SIZE  8
#define REG_SIZE 4

int rcsHaltsoftReset(void);
//int pollRsmFlagRcs(void *srp);

char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
int test_pattern_rsm[] = {0x22222222, 0x33334444, 0x77778888,0xbbbbcccc};
int test_pattern_dcode[] = {0x11111111, 0x11112222,0x55556666, 0x9999aaaa};
int rsm_offset[] = {0x210000, 0x218000, 0x220000,0x230000};
int dcode_offset[] = {0xE4030, 0x124030,0x164030, 0x1C4030};
int rsm_flag_addr[] = {0x23ffec,0x23FFF4, 0x23FFF0, 0x23FFF8,0x23FFFc};
int rsm_flag[] = {0x8844, 0x7788, 0x8877,0xABCD,0x0};
int rsm_com_flag[] = {0x1234, 0x5678, 0x6543};
int flags = 0;
int pollRsmFlagRcs(void *srp,uint8_t core_id);


int main(int argc, const char * argv[])
{
	
	uint32_t rv;
	uint32_t errCnt=0;
	uint32_t dev_id = 0;	
	uint32_t dataCnt=0;
	uint32_t rcs_ctrl = 0; 	
	uint32_t Val_out[MEM_COMPARE_SIZE] =  {0};
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
	
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/boot_test/ax_hw.elf"; // core0
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/boot_test/rx_hw.elf"; // core1
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/boot_test/tx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/boot_test/cal_hw.elf";
    
	print("calling srp_rcs_config...\n");
    
    rcs_config(&rcs_params);
    
    print("after calling srp_rcs_config...\n");
	
	sleep (1);
		
    // start core0
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);
    rcs_rcp_start( SRP_RCS_RCP_CALIB); 
	
	
# if 1
    // read the data from rsm
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId <4; rcsCoreId++)
    {
		
		// poll till core execution is done
		pollRsmFlagRcs(srp,rcsCoreId);
		//clear rsm  flag		
		//write_mem_18a(rsm_flag_addr[rcsCoreId],1,rsm_flag[4],"RSM_FLAG_ADDRESS");		
		//Load and compare vector output from cell to host	
		// read the data from rsm
		read_mem_18a(rsm_offset[rcsCoreId],MEM_COMPARE_SIZE,Val_out,"RSM_OFFESET");	
        for(dataCnt = 0; dataCnt <MEM_COMPARE_SIZE; dataCnt++)
        {
		
			if((Val_out[dataCnt]) != (test_pattern_rsm[rcsCoreId]))
			{
				printf("ERROR RSM: CORE :%x test_pattern[%d]: ox%08x [ox%08x] \n",rcsCoreId,0, Val_out[dataCnt],test_pattern_rsm[rcsCoreId] );
				errCnt++;
			}
        }
        // read the data from dcode
		read_mem_18a(dcode_offset[rcsCoreId],MEM_COMPARE_SIZE,Val_out,"DCODE_OFFSET");
        for(dataCnt = 0; dataCnt <MEM_COMPARE_SIZE; dataCnt++)
        {
		
			if((Val_out[dataCnt]) != (test_pattern_dcode[rcsCoreId]))
			{
				printf("ERROR DCODE: CORE :%x test_pattern[%d]: ox%08x [ox%08x] \n",rcsCoreId,0, Val_out[dataCnt],test_pattern_dcode[rcsCoreId] );
				errCnt++;
			}
        }
 
	
    }

    if(errCnt==0)
    {
        printf("Host:------ All RCS core boot test passed ------\n");
    }
    else
    {
    	printf("Host:------ RCS core boot test FAILED!!! ------\n");
    }
    
	LOG_PRINT("INFO:logger ending !\n");
	return errCnt;
	printf("end\n");
	
#endif	
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

int pollRsmFlagRcs(void *srp,uint8_t rcsCoreId)
{
	//int Val_out = 0;
	int rv,sleepCnt=0;
	volatile uint32_t Val_out[MEM_COMPARE_SIZE] =  {0};
	// wait for core0 to complete the task
	// poll for the RSM location
#if 1
	if(rcsCoreId==0)
	{
		do
		{

			readMem(rsm_flag_addr[rcsCoreId],REG_SIZE,&Val_out);	
			//read_mem_18a(rsm_flag_addr[rcsCoreId],REG_SIZE,Val_out,"rsm_flag_addr");					
			sleep(1);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE0 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
			//printf("loop1val:%x, rsm_flag_addr[rcsCoreId] :%x\n",Val_out[0],rsm_flag_addr[rcsCoreId]);
		} while (Val_out[0] != 0x1234);
	}
    if(rcsCoreId==1)
	{
		// wait for core1 to complete the task
		// poll for the RSM location
		do
		{
			readMem(rsm_flag_addr[rcsCoreId],REG_SIZE,Val_out);
			//read_mem_18a(rsm_flag_addr[rcsCoreId],REG_SIZE,Val_out,"rsm_flag_addr");
			//system("srpRead 0x23fff4");
			sleep(1);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE1 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
			//printf("loop2val:%x, rsm_flag_addr[rcsCoreId] :%x\n",Val_out[0],rsm_flag_addr[rcsCoreId]);
		} while (Val_out[0]!= 0x5678);
	}	
	
	if(rcsCoreId==2)
	{
		// wait for core1 to complete the task
		// poll for the RSM location
		do
		{
			readMem(rsm_flag_addr[rcsCoreId],REG_SIZE,&Val_out);
			//read_mem_18a(rsm_flag_addr[rcsCoreId],REG_SIZE,Val_out,"rsm_flag_addr");	
			sleep(1);
			//printf("loop3val:%x\n",Val_out[0]);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE2 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
		} while (Val_out[0] != 0x1234);
	}	
#endif
#if 1
	if(rcsCoreId==3)
	{
		// wait for core2 to complete the task
		// poll for the RSM location
		do
		{
			readMem(rsm_flag_addr[rcsCoreId],REG_SIZE,&Val_out);
			//read_mem_18a(rsm_flag_addr[rcsCoreId],REG_SIZE,Val_out,"rsm_flag_addr");	
			sleep(2);
			//printf("loop4val:%x\n",Val_out[0]);
			sleepCnt++;
			if(sleepCnt > 15)
			{
				print("Host:------ ERROR: RCS LX7 CORE3 DIDNT FINISH EXECUTION!!! ------\n");
				return;
			}
		} while (Val_out[0] != 0xABCD);	
}
#endif 
}		
