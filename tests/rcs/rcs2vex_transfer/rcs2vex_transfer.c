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
#include "cio2strm.h"
#include "strm2cio.h"
#include "car.h"
#include "logger.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define VMEM_COMPARE_SIZE  16

int rcsHaltResetLoad(void *srp, void *rcs_hdl);
int pollRsmFlagRcs0(void *srp);
int pollRsmFlagRcs1(void *srp);
int pollRsmFlagRcs2(void *srp);

char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };

unsigned int test_pattern_vmem[] = {	0x33334444, 0x11112222, 0x44445555, 0x22223333, 
    0x55556666, 0x33334444, 0x66667777, 0x44445555, 
    0x77778888, 0x55556666, 0x88889999, 0x66667777, 
    0x9999AAAA, 0x77778888, 0xAAAABBBB, 0x88889999 };


unsigned int  test_pattern_vmem_rx[] = {	0x11111111, 0x11111111, 0x22222222, 0x22222222,
    0x33333333, 0x33333333, 0x44444444, 0x44444444,
    0x55555555, 0x55555555, 0x66666666, 0x66666666,
    0x77777777, 0x77777777, 0x88888888, 0x88888888};

unsigned int  test_pattern_vmem_tx[] = {	0x22222222, 0x22222222, 0x11111111, 0x11111111,
    0x44444444, 0x44444444, 0x33333333, 0x33333333,
    0x55555555, 0x55555555, 0x66666666, 0x66666666,
    0x77777777, 0x77777777, 0x88888888, 0x88888888};

unsigned int  test_pattern_vmem_cal[] = {	0x11111111, 0x22222222, 0x22222222, 0x33333333,
    0x33333333, 0x44444444, 0x44444444, 0x55555555,
    0x55555555, 0x66666666, 0x66666666, 0x77777777,
    0x77777777, 0x88888888, 0x88888888, 0x99999999};																				

int test_pattern_dcode[] = {0x12345678, 0xaa55aa55, 0xaaaa5555};
int rsm_offset[] = {0x10000,0x218000, 0x220000, 0x30000};
int dcode_offset[] = {0x24000, 0x24000, 0x44000};
int rsm_flag_addr[] = {0x3ffec,0x3FFF4, 0x3FFF0, 0x3FFF8,0x3FFFc,0x3FFe8};
int flags = 0;

int main(int destVexId)
{

    //destVexId=0;
    int rv;
    int errCnt=0,i;
    int dev_id = 0;

    int dataCnt=0;
    int rcs_ctrl = 0; 

    int Val_out=0;
    unsigned data_tx=0;

    srp_hdl_t srp_hdl = NULL;

    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;

    init();	
    print("calling srp_config!\n");	
    // halt and soft reset all cores
    rcsHaltsoftReset();

    // fill in the .elf files
    memset(&rcs_params, 0, sizeof(rcs_params));

    // poll for memory init done

    // fill in the .elf files
    memset(&rcs_params, 0, sizeof(rcs_params));
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/rcs2vex_transfer/ax_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/rcs2vex_transfer/rx_hw.elf"; // core1
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/rcs2vex_transfer/tx_hw.elf";
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/rcs2vex_transfer/cal_hw.elf";

    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);

    print("after calling srp_rcs_config...\n");

    sleep (1);

    // release abc noc from reset    
    // srpWrite 0x62.0.0x94 0x0
    // srpWrite 0x62.0.0x98 0x0
    rcs_ctrl = 0; 
#if 1
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
		    0, /*IndexVal*/
		    0x94,
		    &rcs_ctrl,
		    1,
		    flags)))
	return rv;
    print("after calling srp_rcs_config1...\n");
    rcs_ctrl = 0; 
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_VEX_CFG_CTRL, /*BlockVal,*/
		    0, /*IndexVal*/
		    0x98,
		    &rcs_ctrl,
		    1,
		    flags)))
	return rv;


    print("release abc noc from reset done\n");
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

    //print("program dest vex core id done\n");
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
    print("enable strm2cio of vex 0 done1 \n");
    rcs_ctrl = 1; 
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_VEX_CORE, /*BlockVal,*/
		    destVexId, /*IndexVal*/
		    0xC020,
		    &rcs_ctrl,
		    1,
		    flags)))
	return rv;
    print("enable strm2cio of vex 0 done2 \n");
    // start core0

    // start core0
    //srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_AX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);


    // poll till core0 execution is done
    pollRsmFlagRcs0(srp);

    //print("core0 execution is done \n");

    sleep(2);
    // wait till transfer is done - check for push data bit to clear 

    // read the data from VMEM
    for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
    {
	// read the data from VMEM
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_VEX_CORE, /*BlockVal,*/
			destVexId, /*IndexVal*/
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

	if((Val_out) != (test_pattern_vmem[dataCnt]))
	{
	    print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem[dataCnt] );
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
#if 1
    //if(destVexId==1)
    //while(1);  
    // Clear the VMEM after the test for the next iteration
    Val_out = 0;
    for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
    {
	// read the data from VMEM
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_VEX_CORE, /*BlockVal,*/
			destVexId, /*IndexVal*/
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

    }
#endif

#if 1
    // Trigger core1 execution RSM shared flags
    //srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_RX);	
    rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);



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
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

	if((Val_out) != (test_pattern_vmem_rx[dataCnt]))
	{
	    print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem_rx[dataCnt] );
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
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

    }
#endif

#if 1
    // Trigger core2 execution RSM shared flags
    //srp_rcs_rcp_start(srp_hdl, SRP_RCS_RCP_CTRL_TX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);



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
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

	if((Val_out) != (test_pattern_vmem_tx[dataCnt]))
	{
	    print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_vmem_tx[dataCnt] );
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
#endif 
#endif
    printf("end\n");

    // Clear the VMEM after the test for the next iteration
    Val_out = 0;
#if 0
    for (dataCnt = 0; dataCnt < VMEM_COMPARE_SIZE; dataCnt++)
    {
	// read the data from VMEM
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_VEX_CORE, /*BlockVal,*/
			destVexId, /*IndexVal*/
			0x28000 + (dataCnt*4),
			&Val_out,
			1,
			flags)))
	    return rv;

    }
#endif
    printf("end\n");
    return errCnt;
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
			rsm_flag_addr[0], // AX core flag for handshake with host
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
			rsm_flag_addr[2], // rx core flag for handshake with host
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

