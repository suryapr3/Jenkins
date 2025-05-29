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

#include "consumer.hive.h"
#include "consumer_prog.map.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MEM_COMPARE_SIZE  128
#define TIMER_TEST_ITER   20

#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x18000 /* vmem of size 64kb starts from 0. dmem starts at the end of vmem physically */

#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))

// Data type to hold table for NOC data
typedef struct noc_tbl_s {
    unsigned  address;
    unsigned  value;
    unsigned  core;
    char      *name;
} noc_tbl_t;

int rcsHaltsoftReset(void);

int rsm_buffer[] = {0x23FFEC, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};
// may change once new functions are added, check .map file
int dcode_buffer[] = {0xE4030, 0xE4040, 0xE4050, 0xE4060}; 

int flags = 0;

static int frioPciReadVal(int address)
{
    char buf[20], data[20], temp[20];
    char cmd_buf[50];
    FILE *fptr;
    int nCnt, reg_value;
    
 
	sprintf(cmd_buf, "/p/frio/tools/frioPciRead -F s6a1 -P 0x%x", address);
	//system(cmd_buf);
	
    fptr = popen(cmd_buf, "r");
    // copy the string out from frioPciRead
    for(nCnt = 0; (fgets(buf, sizeof(buf), fptr)) != NULL; nCnt++)
    {
        if(1 == nCnt) strcpy(temp, buf);
    }
    pclose(fptr);
    
    // skip first three characters
    for(nCnt = 3; temp[nCnt] != '\0'; nCnt++)                        
    {
        data[nCnt - 3] = temp[nCnt];
    }
    data[nCnt -3 - 2] = '\0';
    
    // convert string to hex int
    reg_value = (int)strtol(data, NULL, 16); 

    return reg_value;
}


int static configure_noc(int dest_vex_id)
{
    int i;
    int rv = 0;
    
    // Table with default NOC table to VE init
    noc_tbl_t noc_tbl[] = {

        //destination cell
    //VE01 strm2cio
        { VE32_TILE_STRM2CIO_OFFSET + STRM2CIO_FIFO_STAT_CTL_OFFSET /* 0xc010 */ ,0x00000001, dest_vex_id, "FIFO_STATUS_CTL" },//FIFO_STATUS_CTL
        { VE32_TILE_STRM2CIO_OFFSET + STRM2CIO_WORD_CNT_CTL_OFFSET /* 0xc020 */ ,0x00000001, dest_vex_id, "WORD_CNT_CTL" },//WORD_CNT_CTL

    //Load the pointer copy address for the SDFGates
        { VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET /* 0xdc */ ,HIVE_ADDR_consumer_prog_consumer_sm_gate, dest_vex_id , "lm_bpca_bp_dmem"},//lm_bpca_bp_dmem - mapped to VE01

    };

    for(i = 0; i < ARRAY_SIZE(noc_tbl); i++)
    {

        if (rv = write_reg_18a(VE32_CELL_BASE(noc_tbl[i].core) + noc_tbl[i].address, noc_tbl[i].value, \
                0xFFFFFFFF, noc_tbl[i].name))
            return rv;
    }
    return rv;
}

int main(int argc, const char * argv[])
{
	
	int rv;
	int errCnt=0;
	int dev_id = 0;
	
	int dataCnt=0;
	int rcs_ctrl = 0; 
	int lc = 0;
	
	FILE *fp;
	char val[128];
	
	unsigned rdWrVal[MEM_COMPARE_SIZE] =  {0};
	unsigned data_tx=0;
	
		
	srp_rcs_config_t rcs_params;
	srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;
	
	int vexId;
	
	int consumerVexId = 0;
	
	int offsetVal_2[3] = {
            HIVE_ADDR_consumer_prog_consumer_token_per_request,
            HIVE_ADDR_consumer_prog_consumer_sm_gate,
            HIVE_ADDR_consumer_prog_consumer_max_count
    };
    unsigned Val_kargs_2[3] = {
            1,
            0,
            5
    };
    
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int dst_vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (consumerVexId * vex_vmem_offset);
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;    
    unsigned int dst_vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (consumerVexId * vex_dmem_offset);
    
    uint32_t vmem_base_addr[40] = {
        VEXABC0_VMEM_VE32_SIMD0_BASE, VEXABC1_VMEM_VE32_SIMD0_BASE, VEXABC2_VMEM_VE32_SIMD0_BASE, VEXABC3_VMEM_VE32_SIMD0_BASE,
        VEXABC4_VMEM_VE32_SIMD0_BASE, VEXABC5_VMEM_VE32_SIMD0_BASE ,VEXABC6_VMEM_VE32_SIMD0_BASE ,VEXABC7_VMEM_VE32_SIMD0_BASE,
        VEXABC8_VMEM_VE32_SIMD0_BASE , VEXABC9_VMEM_VE32_SIMD0_BASE, VEXABC10_VMEM_VE32_SIMD0_BASE , VEXABC11_VMEM_VE32_SIMD0_BASE ,
        VEXABC12_VMEM_VE32_SIMD0_BASE , VEXABC13_VMEM_VE32_SIMD0_BASE ,VEXABC14_VMEM_VE32_SIMD0_BASE ,VEXABC15_VMEM_VE32_SIMD0_BASE  ,
        VEXABC16_VMEM_VE32_SIMD0_BASE ,VEXABC17_VMEM_VE32_SIMD0_BASE ,VEXABC18_VMEM_VE32_SIMD0_BASE , VEXABC19_VMEM_VE32_SIMD0_BASE ,
        VEXABC20_VMEM_VE32_SIMD0_BASE , VEXABC21_VMEM_VE32_SIMD0_BASE  , VEXABC22_VMEM_VE32_SIMD0_BASE , VEXABC23_VMEM_VE32_SIMD0_BASE ,
        VEXABC24_VMEM_VE32_SIMD0_BASE  , VEXABC25_VMEM_VE32_SIMD0_BASE , VEXABC26_VMEM_VE32_SIMD0_BASE , VEXABC27_VMEM_VE32_SIMD0_BASE ,
        VEXABC28_VMEM_VE32_SIMD0_BASE , VEXABC29_VMEM_VE32_SIMD0_BASE ,VEXABC30_VMEM_VE32_SIMD0_BASE ,VEXABC31_VMEM_VE32_SIMD0_BASE ,
        VEXABC32_VMEM_VE32_SIMD0_BASE , VEXABC33_VMEM_VE32_SIMD0_BASE , VEXABC34_VMEM_VE32_SIMD0_BASE , VEXABC35_VMEM_VE32_SIMD0_BASE,
        VEXABC36_VMEM_VE32_SIMD0_BASE , VEXABC37_VMEM_VE32_SIMD0_BASE ,VEXABC38_VMEM_VE32_SIMD0_BASE , VEXABC39_VMEM_VE32_SIMD0_BASE

        };

    uint32_t dmem_base_addr[40] = {VEXABC0_DMEM_VE32_BP_CFG_BASE,VEXABC1_DMEM_VE32_BP_CFG_BASE,VEXABC2_DMEM_VE32_BP_CFG_BASE,
        VEXABC3_DMEM_VE32_BP_CFG_BASE,VEXABC4_DMEM_VE32_BP_CFG_BASE,VEXABC5_DMEM_VE32_BP_CFG_BASE,VEXABC6_DMEM_VE32_BP_CFG_BASE,
        VEXABC7_DMEM_VE32_BP_CFG_BASE,VEXABC8_DMEM_VE32_BP_CFG_BASE,VEXABC9_DMEM_VE32_BP_CFG_BASE,VEXABC10_DMEM_VE32_BP_CFG_BASE,
        VEXABC11_DMEM_VE32_BP_CFG_BASE,VEXABC12_DMEM_VE32_BP_CFG_BASE,VEXABC13_DMEM_VE32_BP_CFG_BASE,VEXABC14_DMEM_VE32_BP_CFG_BASE,
        VEXABC15_DMEM_VE32_BP_CFG_BASE,VEXABC16_DMEM_VE32_BP_CFG_BASE,VEXABC17_DMEM_VE32_BP_CFG_BASE,VEXABC18_DMEM_VE32_BP_CFG_BASE,
        VEXABC19_DMEM_VE32_BP_CFG_BASE,VEXABC20_DMEM_VE32_BP_CFG_BASE,VEXABC21_DMEM_VE32_BP_CFG_BASE,VEXABC22_DMEM_VE32_BP_CFG_BASE,
        VEXABC23_DMEM_VE32_BP_CFG_BASE,VEXABC24_DMEM_VE32_BP_CFG_BASE,VEXABC25_DMEM_VE32_BP_CFG_BASE,VEXABC26_DMEM_VE32_BP_CFG_BASE,
        VEXABC27_DMEM_VE32_BP_CFG_BASE,VEXABC28_DMEM_VE32_BP_CFG_BASE,VEXABC29_DMEM_VE32_BP_CFG_BASE,VEXABC30_DMEM_VE32_BP_CFG_BASE,
        VEXABC31_DMEM_VE32_BP_CFG_BASE,VEXABC32_DMEM_VE32_BP_CFG_BASE,VEXABC33_DMEM_VE32_BP_CFG_BASE,VEXABC34_DMEM_VE32_BP_CFG_BASE,
        VEXABC35_DMEM_VE32_BP_CFG_BASE,VEXABC36_DMEM_VE32_BP_CFG_BASE,VEXABC37_DMEM_VE32_BP_CFG_BASE,VEXABC38_DMEM_VE32_BP_CFG_BASE,
        VEXABC39_DMEM_VE32_BP_CFG_BASE

    };
#if 0    
    uint32_t timeStampData[16] = {
	0x0001000f, 0x0002001d, 0x00030043, 0x00040069, 
	0x0005008f, 0x000600b5, 0x000700db, 0x00080101, 
	0x00090127, 0x000a014d, 0x000b0173, 0x000c0199, 
	0x000d01bf, 0x000e01e5, 0x000f020b, 0x00100231
	};
#endif	
	uint32_t timeStampData[16] = {
	 0x0000160f, 0x00010105, 0x0002012b, 0x00030151, 
     0x00040177, 0x0005019d, 0x000601c3, 0x000701e9, 
     0x0008020f, 0x00090235, 0x000a025b, 0x000b0281, 
     0x000c02a7, 0x000d02cd, 0x000e02f3, 0x000f0319
	};

	print("Host: main starts!\n");
	init();

	//return 0;

	// halt and soft reset all cores
	rcsHaltsoftReset();
	
	
	// clear first 32 vmem location for VEX[0:15]
    for( vexId = 0; vexId < 16; vexId++)
	{
		vex_mem_clear(vexId, NULL);
    }
    
	
	// poll for memory init done
	
	// fill in the .elf files
	memset(&rcs_params, 0, sizeof(rcs_params));
	rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/gpio_timer/ax_hw.elf"; // core0
	//rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "./rcs/rx_hw.elf"; // core1
	//rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "./rcs/tx_hw.elf";
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "./rcs/cal_hw.elf";
    
	print("calling srp_rcs_config...\n");
	

    rcs_config(&rcs_params);
    
#if 1
    configure_noc(consumerVexId);
    vex_loader(consumerVexId, "vex_fw/sim_m64/consumer_prog.fw");
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal_2); lc++) {
        write_mem_18a( dst_vex_dmem_base_addr + offsetVal_2[lc], 1, &Val_kargs_2[lc], "Val_kargs_2");
    }
    vex_start(consumerVexId, 0);
#endif
	
	sleep (1);
	//return 0;	
    // start core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX); 
    
    //return 0;
    
    // wait for handshake from gpio_out_test() 
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C001);
	
	rdWrVal[0] = frioPciReadVal(0x20014);
	rdWrVal[1] = frioPciReadVal(0x2001C);
	if(rdWrVal[0] == 0xa5a5a5a5 && rdWrVal[1] == 0xa5a5a)
	{
		print("\n GPIO OUT test: PASS");
	} 
	else
	{
		print("\n GPIO OUT test: FAIL");
		errCnt++;
	}

	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");
	
	// grp0 gpio polarity
	write_reg_18a(TIMER_GPIO_POLARITY_REG(RCS_TIMER_GRP0_GPIO_BASE), 0x0, 0xFFFFFFFF, "TIMER_GPIO_POLARITY_REG");
	
	// grp1 gpio polarity
	write_reg_18a(TIMER_GPIO_POLARITY_REG(RCS_TIMER_GRP1_GPIO_BASE), 0x0, 0xFFFFFFFF, "TIMER_GPIO_POLARITY_REG");
	
	// grp0 gpio_inout, in
	write_reg_18a(TIMER_GPIO_INOUT_REG(RCS_TIMER_GRP0_GPIO_BASE), 0x0, 0xFFFFFFFF, "TIMER_GPIO_INOUT_REG");
	
	// grp1 gpio_inout, in
	write_reg_18a(TIMER_GPIO_INOUT_REG(RCS_TIMER_GRP1_GPIO_BASE), 0x0, 0xFFFFFFFF, "TIMER_GPIO_INOUT_REG");
	
	
	// drive grp0/1 
	system("/p/frio/tools/frioPciWrite -F s6a1 -P 0x20010 0xaaaa5555");
    system("/p/frio/tools/frioPciWrite -F s6a1 -P 0x20018 0x5555aaaa");
   
    // trigger next test gpio_in_test()
    rdWrVal[0] = 0xC000D001;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from gpio_in_test()
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C002);

	// check results of gpio_in_test
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[0], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+4, 1, &rdWrVal[1], "DCODE_BUFFER");
	
	if( rdWrVal[0] == 0xaaaa5555 && rdWrVal[1] == 0x5aaaa)
	{
		print("\n GPIO IN test: PASS");
		print("\n");
	}
	else
	{
		print("	\n GPIO IN test: FAIL");
		print("\n"); 
		errCnt++;
	}
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");
 
    // trigger next test timerOneshotGrp0Tim0Test
    rdWrVal[0] = 0xC000D002;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from timerOneshotGrp0Tim0Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C003);

	
	print("\n timerOneshotGrp0Tim0Test: HSD16023770293");
	print("\n");
	
	// check results of timerOneshotGrp0Tim0Test
	// rd grp0 GPIO
	rdWrVal[0] = frioPciReadVal(0x20014);
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[1], "DCODE_BUFFER"); // status
	read_mem_18a(dcode_buffer[2]+8, 1, &rdWrVal[2], "DCODE_BUFFER"); // isr flag
	read_mem_18a(dcode_buffer[0]+36, 1, &rdWrVal[3], "DCODE_BUFFER"); // timer_cfg
	
	
	if( rdWrVal[0] == 0x87654321 && rdWrVal[1] == 0xFF && rdWrVal[2] == 0xF0E0D0C0 && rdWrVal[3] == 0x0)
	{
		print("\n timerOneshotGrp0Tim0Test: PASS");
		print("\n");
	}
	else
	{
		print("	\n timerOneshotGrp0Tim0Test: FAIL");
		print("\n"); 
		errCnt++;
	}
#if 1
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test timerOneshotGrp0Tim1Test
    rdWrVal[0] = 0xC000D003;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
    // wait for handshake from timerOneshotGrp0Tim1Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C004);
	
	print("\n timerOneshotGrp0Tim1Test: HSD16023770293");
	print("\n");
	
	// check results of timerOneshotGrp0Tim1Test
	// rd grp0 GPIO
	rdWrVal[0] = frioPciReadVal(0x20014);
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+32, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+36, 1, &rdWrVal[3], "DCODE_BUFFER");
	
	
	if( rdWrVal[0] == 0x12345678 && rdWrVal[1] == 0xFF && rdWrVal[2] == 0x8 && rdWrVal[3] == 0x0)
	{
		print("\n timerOneshotGrp0Tim1Test: PASS");
		print("\n");
	}
	else
	{
		print("	\n timerOneshotGrp0Tim1Test: FAIL");
		print("\n"); 
		errCnt++;
	}

	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test timerOneshotGrp1Tim0Test
    rdWrVal[0] = 0xC000D004;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	// wait for handshake from timerOneshotGrp1Tim0Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C005);
	
	print("\n timerOneshotGrp1Tim0Test: HSD16023770293");
	print("\n");
	
	// check results of timerOneshotGrp1Tim0Test
	// rd grp1 GPIO
	rdWrVal[0] = frioPciReadVal(0x2001C);
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+32, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+36, 1, &rdWrVal[3], "DCODE_BUFFER");
	
	
	if( rdWrVal[0] == 0xa5a5a && rdWrVal[1] == 0xFF && rdWrVal[2] == 0x8 && rdWrVal[3] == 0x0)
	{
		print("\n timerOneshotGrp1Tim0Test: PASS");
		print("\n");
	}
	else
	{
		print("	\n timerOneshotGrp1Tim0Test: FAIL");
		print("\n"); 
		errCnt++;
	}
	
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 32, &rdWrVal[0], "DCODE_BUFFER");

    // trigger next test timerOneshotGrp1Tim1Test
    rdWrVal[0] = 0xC000D005;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	// wait for handshake from timerOneshotGrp1Tim1Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C006);
	
	print("\n timerOneshotGrp1Tim1Test: HSD16023770293");
	print("\n");
	
	// check results of timerOneshotGrp1Tim1Test
	// rd grp1 GPIO
	rdWrVal[0] = frioPciReadVal(0x2001C);
	read_mem_18a(dcode_buffer[0], 1, &rdWrVal[1], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+32, 1, &rdWrVal[2], "DCODE_BUFFER");
	read_mem_18a(dcode_buffer[0]+36, 1, &rdWrVal[3], "DCODE_BUFFER");
	
	
	if( rdWrVal[0] == 0x5a5a5 && rdWrVal[1] == 0xFF && rdWrVal[2] == 0x8 && rdWrVal[3] == 0x0)
	{
		print("\n timerOneshotGrp1Tim1Test: PASS");
		print("\n");
	}
	else
	{
		print("	\n timerOneshotGrp1Tim1Test: FAIL");
		print("\n"); 
		errCnt++;
	}
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 128, &rdWrVal[0], "DCODE_BUFFER");


	
    // trigger next test timerContGrp0Tim0Test
	rdWrVal[0] = 0xC000D006;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from timerContGrp0Tim0Test test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C007);

	// check results of timerContGrp0Tim0Test test
	read_mem_18a(dcode_buffer[0], 2, &rdWrVal[0], "DCODE_BUFFER");
	
	if(rdWrVal[1] == TIMER_TEST_ITER) // needs to match with TIMER_TEST_ITER in RCS code
	{
		print("\n Group0 Timer0 continuous test passed for %d iterations", rdWrVal[1] );
		print("\n");
	}
	else
	{
		print("	\n Group0 Timer0 continuous test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 128, &rdWrVal[0], "DCODE_BUFFER");
	
    // trigger next test timerContGrp0Tim1Test
	rdWrVal[0] = 0xC000D007;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from timerContGrp0Tim1Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C008);

	print("\n timerContGrp0Tim1Test test:");
	printf("\n");
	
	// check results of timerContGrp0Tim1Test test
	read_mem_18a(dcode_buffer[0], 8, &rdWrVal[0], "DCODE_BUFFER");
	
	if(rdWrVal[2] == TIMER_TEST_ITER) // needs to match with TIMER_TEST_ITER in RCS code
	{
		print("\n Group0 Timer1 continuous test passed for %d iterations", rdWrVal[2] );
		print("\n");
	}
	else
	{
		print("	\n Group0 Timer01continuous test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	
	// clear DRAM results buffer
	//rdWrVal[0] = 0;
	//write_mem_18a(dcode_buffer[0], 128, &rdWrVal[0], "DCODE_BUFFER");
	
	// trigger next test timerContGrp1Tim0Test
	rdWrVal[0] = 0xC000D008;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from timerContGrp1Tim0Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C009);

	print("\n timerContGrp1Tim0Test test:");
	printf("\n");
	
	// check results of timerContGrp1Tim0Test test
	read_mem_18a(dcode_buffer[0], 8, &rdWrVal[0], "DCODE_BUFFER");
	
	if(rdWrVal[3] == TIMER_TEST_ITER) // needs to match with TIMER_TEST_ITER in RCS code
	{
		print("\n Group1 Timer0 continuous test passed for %d iterations", rdWrVal[3] );
		print("\n");
	}
	else
	{
		print("	\n Group1 Timer0 continuous test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
	
	
	// clear DRAM results buffer
	//rdWrVal[0] = 0;
	//write_mem_18a(dcode_buffer[0], 128, &rdWrVal[0], "DCODE_BUFFER");
	
	// trigger next test timerContGrp1Tim1Test
	rdWrVal[0] = 0xC000D009;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");

	// wait for handshake from timerContGrp1Tim1Test
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C00A);

	print("\n timerContGrp1Tim1Test test:");
	printf("\n");
	
	// check results of timerContGrp1Tim1Test test
	read_mem_18a(dcode_buffer[0], 8, &rdWrVal[0], "DCODE_BUFFER");
	
	if(rdWrVal[4] == TIMER_TEST_ITER) // needs to match with TIMER_TEST_ITER in RCS code
	{
		print("\n Group1 Timer1 continuous test passed for %d iterations", rdWrVal[4] );
		print("\n");
	}
	else
	{
		print("	\n Group1 Timer1 continuous test: FAIL!!!");
		print("\n"); 
		errCnt++;
	}
#endif	

#if 1	
	// trigger next test gpioTimeStampTestSingle
	rdWrVal[0] = 0xC000D00A;
	write_mem_18a(rsm_buffer[4], 1, &rdWrVal[0], "rsm_com_shared_flag");
	print("\n gpioTimeStampTestSingle test start:");

	// wait for handshake from gpioTimeStampTest
    do
    {
		read_mem_18a(rsm_buffer[0], 1, &rdWrVal[0], "SRAM_AX_FLAG");
		
	} while(rdWrVal[0] != 0xC000C00B);

	print("\n gpioTimeStampTestSingle read VEX[0:15] VMEM and verify:");
	printf("\n");
	
	sleep(2);
	
	for(vexId = 0; vexId < 16; vexId++)
	{
		errCnt += read_mem_expect_18a(vmem_base_addr[vexId], 16, timeStampData, "VMEM");
	}
	print("\n errCnt = %d", errCnt);
	printf("\n");
	// clear DRAM results buffer
	rdWrVal[0] = 0;
	write_mem_18a(dcode_buffer[0], 128, &rdWrVal[0], "DCODE_BUFFER");
	
#endif	
	
	if(errCnt)
	{
		print("\n GPIO Timer Tests FAILED!!!");
		print("\n");
	}
	else
	{
		print("\n All GPIO Timer Tests PASS");
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

