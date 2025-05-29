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
#include <stdlib.h>
#include <stdbool.h>
#include <srp_rcs.h>

#include <srp_block_ids.h>

#include "logger.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"
#include "cli.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MEM_COMPARE_SIZE  32

int rcsHaltsoftReset(void);

int rsm_buffer[] = {0x23FFEC, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};
// may change once new functions are added, check .map file
int dcode_buffer[] = {0xE4030, 0xE4040, 0xE4050, 0xE4060}; 

int flags = 0;

int main(int argc, const char * argv[])
{
	
	int rv;
	int errCnt=0;
	int dev_id = 0;
	
	int dataVal = 0, dataCnt = 0;
	int rcs_ctrl = 0; 
	
	unsigned rdWrVal[MEM_COMPARE_SIZE] =  {0};
	unsigned data_tx=0;
	
		
	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	
     
	print("Host: main starts!\n");
	init();

		
	// halt and soft reset all cores
	rcsHaltsoftReset();
	
	// poll for memory init done
	
	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/bfn_test/ax_hw.elf"; // core0
	//rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "./rcs/rx_hw.elf"; // core1
	//rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "./rcs/tx_hw.elf";
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "./rcs/cal_hw.elf";
    
	print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);
	
	sleep (1);
		
    // start core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX); 
    
    // wait for handshake from ax - bfn_start() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C001);
	
	// check results of bfn_start test
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1], 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[2], 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[3], 1, &rdWrVal[3], "DCODE_BUFFER");
	
	print("\n BFN start test: HSD 16023407069");
	print("\n BFN live counter after 20us  = %d", rdWrVal[0]);
	print("\n BFN live counter after 60us  = %d", rdWrVal[1]);
	print("\n BFN live counter after 700us = %d", rdWrVal[2]);
	print("\n BFN live counter after 1.98ms = %d", rdWrVal[3]);
	print("\n");	
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test bfn_testPresetCmd
    rdWrVal[0] = 0xC000D001;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from ax - bfn_testPresetCmd() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C002);
	
	print("\n BFN preset command test: HSD 16023470640");
	print("\n");
	dataVal = 0;
	// check results of bfn_testPresetCmd test
	read_mem_18a((dcode_buffer[0]+8), 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a((dcode_buffer[1]+8), 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a((dcode_buffer[2]+8), 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a((dcode_buffer[3]+8), 1, &rdWrVal[3], "DCODE_BUFFER");
		
	if( rdWrVal[0] == 40 && rdWrVal[1] == 50 && rdWrVal[2] == 60 && \
	    rdWrVal[3] == 70 )
	{
		print("\n BFN counter INC_PRE reg val = 10, BFN preset to %d, %d, %d, %d", \
		        rdWrVal[0], rdWrVal[1], rdWrVal[2], rdWrVal[3]);
		print("\n BFN preset command test: PASS");
		print("\n");
	}
	else
	{
		print("\n BFN counter INC_PRE reg val = 10, BFN preset to %d", dataVal);
		print("	\n BFN preset command test: FAIL");
		print("\n"); 
		errCnt++;
	}
	
	sleep (1);
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test bfn_testIncCmd
    rdWrVal[0] = 0xC000D002;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	

	// wait for handshake from ax - bfn_testIncCmd() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C003);
	
	print("\n BFN INC command test:");
	print("\n");
	
	// check results of bfn_testIncCmd test
	read_mem_18a(dcode_buffer[0]+8, 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1]+8, 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[2]+8, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[3]+8, 1, &rdWrVal[3], "DCODE_BUFFER");
	
	if( ((rdWrVal[0] % 10000) < 150) && ((rdWrVal[1] % 20000) < 150) && \
	    ((rdWrVal[2] % 30000) < 150) && ((rdWrVal[3] % 40000) < 150) )
	{
		print("\n BFN counter incremented to %d, %d, %d, %d", rdWrVal[0], \
		      rdWrVal[1],rdWrVal[2],rdWrVal[3]);
		print("\n BFN INC command test: PASS");
		print("\n");
	}
	else
	{
		print("\n BFN counter incremented to %d, %d, %d, %d", (rdWrVal[0] % 10000), \
		      rdWrVal[1],rdWrVal[2],rdWrVal[3]);
		print("	\n BFN INC command test: FAIL");
		print("\n"); 
		errCnt++;
	}

	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test bfn_testCaptureCmd
    rdWrVal[0] = 0xC000D003;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
    // wait for handshake from ax - bfn_testCaptureCmd() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C004);
	
	print("\n BFN Capture command test: HSD 16023470985");
	print("\n");
	
	// check results of bfn_testCaptureCmd test
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1], 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[2], 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[3], 1, &rdWrVal[3], "DCODE_BUFFER");
	
	rdWrVal[0] = abs(10000 - rdWrVal[0]);
	rdWrVal[1] = abs(30000 - rdWrVal[1]);
	rdWrVal[2] = abs(70000 - rdWrVal[2]);
	rdWrVal[3] = abs(130000 - rdWrVal[3]);
	print("\nrdWrVal[3] is %d, %d, %d, %d", rdWrVal[0],rdWrVal[1],rdWrVal[2],rdWrVal[3]);
	
	if( rdWrVal[0] < 200 && rdWrVal[1] < 300 && \
	     rdWrVal[2] < 700 && rdWrVal[3] < 1500  )
	{
		print("\n BFN captured values diff at 10us is %d", rdWrVal[0]);
		print("\n BFN captured values diff at 30us is %d", rdWrVal[1]);
		print("\n BFN captured values diff at 70us is %d", rdWrVal[2]);
		print("\n BFN captured values diff at 130us is %d", rdWrVal[3]);
		print("\n BFN Capture command test: PASS");
		print("\n");
	}
	else
	{
		print("\n BFN captured values diff at 10us is %d", rdWrVal[0]);
		print("\n BFN captured values diff at 30us is %d", rdWrVal[1]);
		print("\n BFN captured values diff at 70us is %d", rdWrVal[2]);
		print("\n BFN captured values diff at 130us is %d", rdWrVal[3]);
		
		print("	\n BFN Capture command test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test bfn_testSyncLoad
    rdWrVal[0] = 0xC000D004;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	// wait for handshake from ax - bfn_testSyncLoad() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C005);
	
	print("\n BFN sysref Load test: HSD 16023471909");
	print("\n");
	
	// check results of bfn_testSyncLoad test
	read_mem_18a(dcode_buffer[0]+4, 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1]+4, 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[2]+4, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[3]+4, 1, &rdWrVal[3], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+12, 1, &rdWrVal[4], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1]+12, 1, &rdWrVal[5], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[2]+12, 1, &rdWrVal[6], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[3]+12, 1, &rdWrVal[7], "DCODE_BUFFER");
	
	if( rdWrVal[0] == 10018 && rdWrVal[1] == 10018 && rdWrVal[2] == 10018 && \
	    rdWrVal[3] == 10018 )
	{
		print("\n BFN sysref load at %d, BFN counter after load %d", rdWrVal[4],rdWrVal[0]);
		print("\n BFN sysref load at %d, BFN counter after load %d", rdWrVal[5],rdWrVal[1]);
		print("\n BFN sysref load at %d, BFN counter after load %d", rdWrVal[6],rdWrVal[2]);
		print("\n BFN sysref load at %d, BFN counter after load %d", rdWrVal[7],rdWrVal[3]);
		print("\n BFN sysref load test: PASS");
		print("\n");
	}
	else
	{
		print("	\n BFN sysref loadtest: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test bfn_testSyncRead
    rdWrVal[0] = 0xC000D005;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	// wait for handshake from ax - bfn_testSyncRead() test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C006);
	
	print("\n BFN sysref Read test: HSD 16023472082");
	print("\n");
	// check results of bfn_testSyncLoad test
	read_mem_18a(dcode_buffer[0]+8, 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+12, 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1]+8, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[1]+12, 1, &rdWrVal[3], "DCODE_BUFFER");
	
	if( (rdWrVal[0] == rdWrVal[1]) && (rdWrVal[2] == rdWrVal[3]) )
	{
		print("\n BFN sysref read at %d, BFN counter %d", rdWrVal[1],rdWrVal[0]);
		print("\n BFN sysref load at %d, BFN counter %d", rdWrVal[3],rdWrVal[2]);
		
		print("\n BFN sysref Read test: PASS");
		print("\n");
	}
	else
	{
		print("	\n BFN sysref Read test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");
	
	// signal AX core for next test execution

	if(errCnt)
	{
		print("\n BFN Tests FAILED!!!");
		print("\n");
	}
	else
	{
		print("\n BFN Tests PASS");
		print("\n");
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



