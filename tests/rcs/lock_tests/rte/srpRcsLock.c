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
#include <srp_core_uapi.h>
#include <srpCliCommon.h>
#include <srp_block_ids.h>

#include "logger.h"



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MEM_COMPARE_SIZE  16

int rcsHaltResetLoad(void *srp, void *rcs_hdl);
int pollRsmFlagRcs(void *srp);

char *rcsFilePath[] = { "../rcs/tx_hw.elf", "../rcs/rx_hw.elf", "../rcs/cal_hw.elf" };
int test_pattern_rsm[] = {0x11223344, 0x44332211, 0x55667788};
int test_pattern_dcode[] = {0x12345678, 0xaa55aa55, 0xaaaa5555};
int rsm_offset[] = {0x10000, 0x20000, 0x30000};
int dcode_offset[] = {0x24000, 0x24000, 0x44000};
int rsm_flag_addr[] = {0x3FFF0, 0x3FFF4, 0x3FFF8};
int flags = 0;

int main(int argc, const char * argv[])
{
	int rv;
	int errCnt=0;
	int dev_id = 0;
	void *srp, *rcs_hdl;
	srp_rcs_config_t rcs_params;
	srp_rcs_t srp_rcs_hdl;
	int dataCnt=0;
	int rcs_ctrl = 0; 
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_0;
	unsigned Val_out[MEM_COMPARE_SIZE] =  {0};
	
	
	print("Host: main starts!\n");
	
	memset(&rcs_params, 0, sizeof(rcs_params));
	memset(&srp_rcs_hdl, 0, sizeof(srp_rcs_hdl));

	rcs_hdl = &srp_rcs_hdl;

	/* open the device */
	srp_core_open(dev_id, flags, &srp);
	if ((rv = srp_rcs_config(srp, &rcs_hdl, rcs_params)))
		return rv;
		
	rcsHaltResetLoad(srp, rcs_hdl);
	
    // start core0
    //srp_rcs_rcp_start(rcs_hdl, SRP_RCS_RCP_0); // not working, check with Gary!
		
	if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0x8,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
 #if 0  
    // poll till core execution is done
    pollRsmFlagRcs(srp);
	

    // read the data from rsm
    for (rcsCoreId = SRP_RCS_RCP_0; rcsCoreId < SRP_RCS_RCP_MAX; rcsCoreId++)
    {
		//Load and compare vector output from cell to host
		
		// read the data from rsm
		if ((rv = srp_core_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_offset[rcsCoreId],
					&Val_out[0],
					MEM_COMPARE_SIZE,
					flags)))
		return rv;

        for(dataCnt = 0; dataCnt <MEM_COMPARE_SIZE; dataCnt++)
        {
		
			if((Val_out[dataCnt]) != (test_pattern_rsm[rcsCoreId]))
			{
				printf("ERROR:test_pattern[%d]: ox%08x [ox%08x] \n", 0, Val_out[dataCnt],test_pattern_rsm[rcsCoreId] );
				errCnt++;
			}
        }
        // read the data from dcode
        if ((rv = srp_core_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			rcsCoreId, /*IndexVal*/
					dcode_offset[rcsCoreId],
					&Val_out[0],
					MEM_COMPARE_SIZE,
					flags)))
		return rv;

        for(dataCnt = 0; dataCnt <MEM_COMPARE_SIZE; dataCnt++)
        {
		
			if((Val_out[dataCnt]) != (test_pattern_dcode[rcsCoreId]))
			{
				print("ERROR:test_pattern[%d]: ox%08x [ox%08x] \n", 0, Val_out[dataCnt],test_pattern_dcode[rcsCoreId] );
				errCnt++;
			}
        }
    }



    if(errCnt==0)
    {
        print("Host:------ All RCS core boot test passed ------\n");
    }
    else
    {
    	print("Host:------ RCS core boot test FAILED!!! ------\n");
    }
#endif    
    
	LOG_PRINT("INFO:logger ending !\n");
	return errCnt;
}

int rcsHaltResetLoad(void *srp, void *rcs_hdl)
{
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_0;
    unsigned rcs_ctrl = 0;
    int rv;
    
    // halt core0  
	rcs_ctrl=0x1;
	if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0x8,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
	// halt core1 
	rcs_ctrl=0x11;
	if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0xC,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
	// halt core2  
	rcs_ctrl=0x11;
	if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0x10,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
	// soft reset all cores
    rcs_ctrl=0xE00000;
     if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0x24,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
    sleep(1);
    // remove soft reset of all cores
    rcs_ctrl=0x0;
    sleep(1);
    if ((rv = srp_core_block_write32(srp,
	SRP_BLOCK_RCS_GPREG_RCS, /*BlockVal,*/
	0, /*IndexVal*/
			0x24,
			&rcs_ctrl,
			1,
			flags)))
	return rv;
    sleep(2);
	// load all cores
    for (rcsCoreId = SRP_RCS_RCP_0; rcsCoreId < SRP_RCS_RCP_MAX; rcsCoreId++)
    {
		print("Host: start rcs %d program load\n", rcsCoreId);
		if ((rv = srp_rcs_rcp_loader(rcs_hdl, rcsCoreId, rcsFilePath[rcsCoreId])))
			return rv;

		print("Host: rcs %d program load - done !!\n", rcsCoreId);

    }
}

int pollRsmFlagRcs(void *srp)
{
	int Val_out = 0;
	int rv;
	// wait for core0 to complete the task
	// poll for the RSM location
	do
	{
		if ((rv = srp_core_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[0],
					&Val_out,
					0x1,
					flags)))
		return rv;
		sleep(1);
	} while (Val_out != 0x1234);	
	
	// wait for core1 to complete the task
	// poll for the RSM location
	do
	{
		if ((rv = srp_core_block_read32(srp,
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
		if ((rv = srp_core_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
					rsm_flag_addr[2],
					&Val_out,
					0x1,
					flags)))
		return rv;
		sleep(1);
	} while (Val_out != 0xABCD);	
}		
