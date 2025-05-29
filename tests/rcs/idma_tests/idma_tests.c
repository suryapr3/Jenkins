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



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define DCODE_MEM_COMPARE_SIZE 0x70
#define DCODE_MEM_COMPARE_SIZE_CAL 0x300

#define REG_SIZE 4

#define MEM_COMPARE_SIZE  8

int rcsHaltResetLoad(void *srp, void *rcs_hdl);
int pollRsmFlagRcs(void *srp,uint8_t core_id);
int idma_test_1d_poll_dcode_to_dcode(void *srp,uint8_t core_id);
int idma_test_1d_poll_dcode_to_rsm(void *srp,uint8_t core_id);
int idma_test_1d_poll_rsm_to_dcode(void *srp,uint8_t core_id);
int idma_test_desc_1d_dcode_to_rsm(void *srp,uint8_t core_id);
int idma_test_desc_1d_dcode_to_dcode(void *srp,uint8_t core_id);
int idma_broadcast_dcode_to_dcode(void *srp,uint8_t core_id);
int idma_broadcast_dcode_to_rsm(void *srp,uint8_t core_id);
int idma_broadcast_rsm_to_dcode(void *srp,uint8_t core_id);
int idma_broadcast_dcode_to_dcode_src_pitch(void *srp,uint8_t core_id);
int idma_broadcast_dcode_to_rsm_src_pitch(void *srp,uint8_t core_id);
int idma_broadcast_rsm_to_dcode_src_pitch(void *srp,uint8_t core_id);
int idma_test_desc_2d_dcode_to_dcode(void *srp,uint8_t core_id);
int idma_test_desc_2d_dcode_to_rsm(void *srp,uint8_t core_id);
int idma_test_desc_1d_rsm_to_dcode(void *srp,uint8_t core_id);
int idma_test_desc_2d_rsm_to_dcode(void *srp,uint8_t core_id);

int test_pattern[] ={0x55555555,0xAAAAAAAA,0x5A5A5A5A,0x55558888};
char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
int test_pattern_rsm[] = {0x11223344, 0x44332211, 0x55667788};
int test_pattern_dcode[] = {0x12345678, 0xaa55aa55, 0xaaaa5555};
int rsm_offset[] = {0x10000,0x18000,0x20000,0x28000};
int dcode_offset[] = {0x28530, 0x282a0,0x283a0,0x47e10};
int dcode_offset_2d[] = {0x29130, 0x28ea0,0x28fa0,0x48610};
//int rsm_flag_addr[] = {0x3FFF0, 0x3FFF4, 0x3FFF8,0x3FFFc,0x3FFe0};
int rsm_flag_addr[] = {0x3ffec,0x3FFF4, 0x3FFF0, 0x3FFF8,0x3FFFc,0x3FFe8};
int rsm_offset_2d[] = {0x10c00,0x18c00,0x20c00,0x28800};
int rsm_flag[] = {0x8844,0x7788, 0x6644, 0x8877,0x0};
int dcode_flag[]={0x2c144,0x2beb0,0x2bfb4,0x4a610};
uint32_t block_size[]={0x2c148,0x2beb4,0x2bfb8,0x4a614};

int flags = 0;

int main(int argc, const char * argv[])
{

    int rv;
    int errCnt=0;
    int dev_id = 0;	
    int dataCnt=0;
    int rcs_ctrl = 0; 	
    unsigned Val_out[MEM_COMPARE_SIZE] =  {0};
    unsigned data_tx=0;	

    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;    
    print("Host: main starts!\n");	
    init();	
    print("calling srp_config!\n");	
    // halt and soft reset all cores
    rcsHaltsoftReset();

    // fill in the .elf files
    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/idma_test/ax_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/idma_test/rx_hw.elf"; // core1
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/idma_test/tx_hw.elf";
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../src/rcs_fw/out/bin/idma_test/cal_hw.elf";

    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);

    print("after calling srp_rcs_config...\n");

    sleep (1);

    // start core0
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_RX);
    rcs_rcp_start( SRP_RCS_RCP_CTRL_TX);
    //rcs_rcp_start( SRP_RCS_RCP_CALIB); 


    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId<3; rcsCoreId++)
    {
	for(dataCnt=0;dataCnt<1;dataCnt++)
	{

	    print("iteration no:%d\n",dataCnt);
	    idma_broadcast_dcode_to_dcode(srp,rcsCoreId);
	    idma_broadcast_dcode_to_rsm(srp,rcsCoreId);
	    idma_broadcast_rsm_to_dcode(srp,rcsCoreId);
	    idma_broadcast_dcode_to_dcode_src_pitch(srp,rcsCoreId);
	    idma_broadcast_rsm_to_dcode_src_pitch(srp,rcsCoreId);
	    idma_broadcast_dcode_to_rsm_src_pitch(srp,rcsCoreId);
	    idma_test_desc_1d_dcode_to_dcode(srp,rcsCoreId);
	    idma_test_desc_1d_dcode_to_rsm(srp,rcsCoreId);
	    idma_test_desc_1d_rsm_to_dcode(srp,rcsCoreId);
	    idma_test_desc_2d_dcode_to_dcode(srp,rcsCoreId);
	    idma_test_desc_2d_rsm_to_dcode(srp,rcsCoreId);
	    idma_test_desc_2d_dcode_to_rsm(srp,rcsCoreId);
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
			    rsm_flag_addr[core_id],
			    &Val_out,
			    0x1,
			    flags)))
		return rv;
	    sleep(1);
	    //printf("loop1\n");
	} while (Val_out != 0x1234);
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
			    rsm_flag_addr[core_id],
			    &Val_out,
			    0x1,
			    flags)))
		return rv;
	    sleep(1);
	} while (Val_out != 0x5678);
    }	

    if(core_id==2)
    {
	// wait for core1 to complete the task
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
	} while (Val_out != 0x1234);
    }	
#endif
#if 1
    if(core_id==3)
    {
	// wait for core2 to complete the task
	// poll for the RSM location
	do
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			    0, /*IndexVal*/
			    rsm_flag_addr[3],
			    &Val_out,
			    0x1,
			    flags)))
		return rv;
	    sleep(1);
	    //printf("loop2\n");
	} while (Val_out != 0xabcd);	
    }
#endif 
}		

int idma_test_1d_poll_dcode_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id);
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;
    sleep(1);
    printf("out\n");
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;
	//printf("ERROR:test_pattern tx %x  , data %x address %x \n",0x88885555, data_tx, dcode_offset[core_id] + (dataCnt*4) );
	if(data_tx != 0x88885555)
	{
	    //printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",0x88885555, data_tx, dcode_offset[core_id] + (dataCnt*4) );
	    errCnt++;
	}

    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA 1Dpoll DCODE to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA 1Dpoll DCODE to DCODE  FAILED ------\n",core_id);
    }
    //write rsm flag core0
#if 1
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
#endif
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_test_1d_poll_rsm_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id);
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;
    sleep(1);
    //sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;

	if(data_tx != 0xA5A5A5A5)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",0xA5A5A5A5, data_tx, dcode_offset[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA 1Dpoll RSM to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA 1Dpoll RSM to DCODE  FAILED ------\n",core_id);
    }
    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}

int idma_test_desc_1d_dcode_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
    // Read num_bytes from RCS
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))


	    return rv;


#if 1
	printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x85858585, data_tx, dcode_offset[core_id]+dataCnt,blk_size,num_bytes);
	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			    core_id, /*IndexVal*/
			    dcode_offset[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;
	    //printf("blk_size%x\n",blk_size);
	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x85858585, data_tx, dcode_offset[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0x85858585)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0x85858585, data_tx, dcode_offset[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}


	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;





#endif
	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA desc test DCODE to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA desc test DCODE to DCODE  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm tx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;

}
int idma_test_desc_1d_dcode_to_rsm(void *srp,uint8_t core_id)
{

    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
#if 1
    //write rsm tx/rx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
#endif    
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))

	    return rv;

	//printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x58585858, data_tx, rsm_offset[core_id]+dataCnt,blk_size,num_bytes);

	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			    0, /*IndexVal*/
			    rsm_offset[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;
	    //printf("blk_size%x\n",blk_size);
	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x58585858, data_tx, rsm_offset[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0x58585858)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0x58585858, data_tx, rsm_offset[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}

	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;

	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA desc test DCODE to RSM  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA desc test DCODE to RSM  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm tx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;

}
int idma_test_desc_1d_rsm_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
    // Read num_bytes from RCS
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))


	    return rv;
#if 1
	// printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x85858585, data_tx, dcode_offset[core_id]+dataCnt,blk_size,num_bytes);
	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			    core_id, /*IndexVal*/
			    dcode_offset[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;
	    //printf("blk_size%x\n",blk_size);
	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x85858585, data_tx, dcode_offset[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0xA5A5A5A5)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0xA5A5A5A5, data_tx, dcode_offset[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}

	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;

#endif
	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA desc test RSM to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA desc test RSM to DCODE  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm tx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;
}
int idma_test_desc_2d_dcode_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
    //write rsm tx/rx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    // Read num_bytes from RCS
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))


	    return rv;

#if 1


	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			    core_id, /*IndexVal*/
			    dcode_offset_2d[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;

	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x5D5D5D5D, data_tx, dcode_offset_2d[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0x5D5D5D5D)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0x5D5D5D5D, data_tx, dcode_offset_2d[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}

	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;

#endif
	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: 2D IDMA desc test DCODE to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: 2D IDMA desc test DCODE to DCODE  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm host flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;
}

int idma_test_desc_2d_dcode_to_rsm(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
    //write rsm tx/rx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    // Read num_bytes from RCS
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))


	    return rv;


#if 1

	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			    0, /*IndexVal*/
			    rsm_offset_2d[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;

	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0x5C5C5C5C, data_tx, rsm_offset_2d[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0x5C5C5C5C)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0x5C5C5C5C, data_tx, rsm_offset_2d[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}

	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;

#endif
	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: 2D IDMA desc test DCODE to RSM  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: 2D IDMA desc test DCODE to RSM  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm host flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;
}
int idma_test_desc_2d_rsm_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0,i=0,dataCnt=0,j,count=0;
    int Val_out[]={0};
    int blk_size=0,num_bytes=0;
    unsigned int data_tx=0,data_rx=0;
    //write rsm tx/rx flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    // Read num_bytes from RCS
    while(num_bytes<2048)
    {
	//printf("running%x\n",num_bytes);
	// poll till core execution is done
	pollRsmFlagRcs(srp,core_id);
	//clear tx/rx flag
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[core_id],
			&rsm_flag[4],
			0x1,
			flags)))
	    return rv;

	// read num_bytes from rcs
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_flag[core_id],
			&num_bytes,
			0x1,
			flags)))
	    return rv;
	//printf("coreid%x\n",core_id);
	// Read blk_size from RCS
	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			block_size[core_id],
			&blk_size,
			0x1,
			flags)))


	    return rv;

#if 1

	for (dataCnt=0;dataCnt<blk_size;dataCnt+=4)
	{
	    if ((rv = srp_dev_block_read32(srp,
			    SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			    core_id, /*IndexVal*/
			    dcode_offset_2d[core_id] +(dataCnt),
			    &data_tx,
			    1,
			    flags)))
		return rv;

	    //printf(":test_pattern tx %x  , data %x address  %x blk_size=%xnum_bytes =%x  \n",0xB5B5B5B5, data_tx, dcode_offset_2d[core_id]+dataCnt,blk_size,num_bytes);
	    if(data_tx != 0xB5B5B5B5)
	    {
		//printf("ERROR:test_pattern %x  , address %x \n",test_pattern[0],0x24000 + (lc*4) );
		printf("ERROR:test_pattern tx %x  , data %x address  %x \n dataCnt=%x",0xB5B5B5B5, data_tx, dcode_offset_2d[core_id]+dataCnt);
		errCnt++;
	    }
	    //printf("num_bytes:%x ,blksize %x",num_bytes,blk_size);

	}

	//write rsm host flag core0
	if ((rv = srp_dev_block_write32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_flag_addr[4],
			&rsm_flag[core_id],
			0x1,
			flags)))
	    return rv;

#endif
	//printf("blk_size = %x dataCnt=%x\n",blk_size,dataCnt);
	//blk_size*=2;
	//printf("blk_size = %x \n",blk_size);

    }

    if(errCnt==0)
    {
	print("Host:------ CORE %x: 2D IDMA desc test RSM to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: 2D IDMA desc test RSM to DCODE  FAILED ------\n",core_id);
    }


    LOG_PRINT("INFO:logger ending !\n");
    //write rsm host flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    return errCnt;
}

int idma_broadcast_dcode_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};
    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id);
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;   
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset_2d[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;

	if(data_tx != dataCnt)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, dcode_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST DCODE to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST DCODE to DCODE  FAILED ------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_broadcast_rsm_to_dcode(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id);
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;   
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset_2d[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;


	if(data_tx != dataCnt)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, dcode_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST RSM to  DCODE PASSED------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST RSM to   DCODE FAILED------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_broadcast_dcode_to_rsm(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id); 
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;  
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_offset_2d[core_id]+ (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;

	if(data_tx != dataCnt)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, rsm_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST DCODE to  RSM PASSED------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST DCODE to  RSM FAILED------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_broadcast_dcode_to_dcode_src_pitch(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id); 
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;  
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset_2d[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;

	if(data_tx != dataCnt)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, dcode_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH DCODE to DCODE  PASSED ------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH DCODE to DCODE  FAILED ------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_broadcast_rsm_to_dcode_src_pitch(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id); 
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;  
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_CORE_CTRL, /*BlockVal,*/
			core_id, /*IndexVal*/
			dcode_offset_2d[core_id] + (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;


	if(data_tx != dataCnt)
	{

	    print("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, dcode_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH RSM to  DCODE PASSED------\n",core_id);
    }
    else
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH RSM to   DCODE FAILED------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
int idma_broadcast_dcode_to_rsm_src_pitch(void *srp,uint8_t core_id)
{
    int rv;
    int errCnt=0;
    int dataCnt=0;
    int Val_out[]={0};

    // poll till core execution is done
    pollRsmFlagRcs(srp,core_id);
    //clear rsm flag
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[core_id],
		    &rsm_flag[4],
		    0x1,
		    flags)))
	return rv;   
    sleep(1);
    for (dataCnt = 0; dataCnt < DCODE_MEM_COMPARE_SIZE/4; dataCnt++)
    {
	unsigned data_tx=0,data_rx=0;
	//Load and compare vector output from cell to host

	/*int srp_rcs_rcp_memid_load(void *rcs_hdl, srp_ccp_core_t core_id,
	  srp_rcs_rcp_mem_t mem_id, srp_uint32_t local_addr,
	  srp_uint32_t *data, srp_size_t size);*/
	// above is not working, check with Gary Mcgee 	   

	if ((rv = srp_dev_block_read32(srp,
			SRP_BLOCK_RCS_RSM, /*BlockVal,*/
			0, /*IndexVal*/
			rsm_offset_2d[core_id]+ (dataCnt *4),
			&data_tx,
			1,
			flags)))
	    return rv;

	if(data_tx != dataCnt)
	{

	    printf("ERROR:test_pattern tx %x  , data %x address %x \n",dataCnt, data_tx, rsm_offset_2d[core_id] + (dataCnt*4) );
	    errCnt++;
	}
    }				
    if(errCnt==0)
    {
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH DCODE to  RSM PASSED------\n",core_id);
    }
    else
    { 
	print("Host:------ CORE %x: IDMA BROADCAST TEST SRC PITCH DCODE to  RSM FAILED------\n",core_id);
    }

    //write rsm flag core0
    if ((rv = srp_dev_block_write32(srp,
		    SRP_BLOCK_RCS_RSM, /*BlockVal,*/
		    0, /*IndexVal*/
		    rsm_flag_addr[4],
		    &rsm_flag[core_id],
		    0x1,
		    flags)))
	return rv;
    LOG_PRINT("INFO:logger ending !\n");
    return errCnt;
}
