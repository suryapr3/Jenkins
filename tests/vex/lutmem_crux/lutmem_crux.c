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
#include "logger.h"
#include "cli.h"
#include "init.h"
#include "common_functions.h"
#include "all_comps.h"

#include <srp_block_ids.h>

#include "ve32_cell.h"
#include "ve32_tile_ctrl.h"
#include "cio2strm.h"
#include "strm2cio.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define MEM_SIZE  (8)
#define MEM_COMPARE_SIZE  1024
#define NUM_OF_ELEMENTS_PER_VEC 32

int rsm_offset[] = {0x210000, 0x218000, 0x220000, 0x30000}; //sram address 230000 if using sram reserved / 210000 if using normal ax sram 
int rsm_flag_addr[] = {0x23ffec,0x23FFF4, 0x23FFF0, 0x23FFF8,0x23FFFc};

int rcsHaltsoftReset(void);

//int pollRsmFlagRcs(void *srp , int rcsCoreId) ;

char *rcsFilePath[] = { "../../rcs/tx_hw.elf", "../../rcs/rx_hw.elf", "../../rcs/cal_hw.elf" };

unsigned int test_pattern_lutmem[SRP_RCS_RCP_MAX][16] = {
    // Pattern for SRP_RCS_RCP_CTRL_AX
    {0x33334444, 0x11112222, 0x44445555, 0x22223333, 
     0x55556666, 0x33334444, 0x66667777, 0x44445555, 
     0x77778888, 0x55556666, 0x88889999, 0x66667777, 
     0x9999AAAA, 0x77778888, 0xAAAABBBB, 0x88889999},
    // Pattern for SRP_RCS_RCP_CTRL_RX
    {0x11111111, 0x11111111, 0x22222222, 0x22222222,
     0x33333333, 0x33333333, 0x44444444, 0x44444444,
     0x55555555, 0x55555555, 0x66666666, 0x66666666,
     0x77777777, 0x77777777, 0x88888888, 0x88888888},
    // Pattern for SRP_RCS_RCP_CTRL_TX
    {0x22222222, 0x22222222, 0x11111111, 0x11111111,
     0x44444444, 0x44444444, 0x33333333, 0x33333333,
     0x55555555, 0x55555555, 0x66666666, 0x66666666,
     0x77777777, 0x77777777, 0x88888888, 0x88888888},
   
};


int main(int vexCoreId)
{
    int rv = 0;
    int lc,i;
    int j=1,k=0;
    int Val_out=0;
    int rcs_ctrl = 0,errCnt=0;
    int dataCnt=0,data_index=0;

    srp_hdl_t srp_hdl = NULL;
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;    

    unsigned int vex_lutmem_offset = VEXABC1_LUTMEM_VE32_SIMD0_BASE - VEXABC0_LUTMEM_VE32_SIMD0_BASE;
    unsigned int vex_lutmem_base_addr = VEXABC0_LUTMEM_VE32_SIMD0_BASE + (vexCoreId * vex_lutmem_offset);

    unsigned int s2c_offset = VEXABC1_S2C_STRM2CIO_BASE - VEXABC0_S2C_STRM2CIO_BASE ;
    unsigned int s2c_base_addr = VEXABC0_S2C_STRM2CIO_BASE + (vexCoreId*s2c_offset) ;

    print("Host: main starts!\n");    
    init();

    vex_mem_clear(vexCoreId, srp);

    print("Host: RCS starts!\n");  

#if 1
    // halt and soft reset all cores
    print("calling rcsHaltsoftReset\n");
    rcsHaltsoftReset();
#else
    print("calling srpReset\n");
    system("srpReset -W");
    sleep(1);
#endif

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../src/rcs_fw/out/bin/vex_lutmem_crux/ax_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../src/rcs_fw/out/bin/vex_lutmem_crux/rx_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../src/rcs_fw/out/bin/vex_lutmem_crux/tx_hw.elf"; // core0

    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);

    sleep (1);
    
    print("vexCoreId- %d\n",vexCoreId);

    // program dest vex core id into write_rsm of RCS. RCS uses this as dest id to program routing data.
    write_mem_18a(rsm_offset[0] ,1,&vexCoreId,"Dest Vex Id");  

    // enable strm2cio of vex 0
    // srpWrite 0x63.0.0x2010 0x1
    // srpWrite 0x63.0.0x2020 
    rcs_ctrl= 1;
    write_reg_18a(s2c_base_addr + STRM2CIO_FIFO_STAT_CTL_OFFSET ,rcs_ctrl,0xFFFFFFFF,"RCS_CTL_FLAG");   
    print("enable strm2cio of vex %d done1 \n",vexCoreId);
    rcs_ctrl = 1; 
    write_reg_18a(s2c_base_addr + STRM2CIO_WORD_CNT_CTL_OFFSET ,rcs_ctrl,0xFFFFFFFF,"RCS_CTL_FLAG");
    print("enable strm2cio of vex %d done2 \n",vexCoreId); 
    print("vexCoreId- %d\n",vexCoreId);


    // start rcs core
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId < 3; rcsCoreId++)
    {
        printf("rcs core id %d\n",rcsCoreId);
        rcs_rcp_start(rcsCoreId);

        // poll till core0 execution is done
        pollRsmFlagRcs(srp,rcsCoreId);

        // wait till transfer is done - check for push data bit to clear 
        sleep(2);

        // read the data from LUTMEM
        Val_out = 0;
        for (dataCnt = 0; dataCnt < MEM_COMPARE_SIZE; dataCnt++)
        {
            data_index = dataCnt % 16;
            read_mem_18a(vex_lutmem_base_addr + (dataCnt*4) , 1, &Val_out , "Val_out");
            //print("test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_lutmem[rcsCoreId][data_index] );
            if((Val_out) != (test_pattern_lutmem[rcsCoreId][data_index]))
            {
                print("ERROR:test_pattern[%d]: 0x%08x [0x%08x] \n", dataCnt, Val_out,test_pattern_lutmem[rcsCoreId][data_index]);
                errCnt++;
            }
        }
        
        if(errCnt==0)
        {
            print("Host:------ Lutmem Access to VEX %d via CRUX Pass for RCS Core %d ------\n", vexCoreId , rcsCoreId);
        }
        else
        {
            print("Host:------ Lutmem Access to VEX %d via CRUX FAILED for RCS Core %d!!! ------\n", vexCoreId , rcsCoreId);
        }
        Val_out = 0;
        for (dataCnt = 0; dataCnt < MEM_COMPARE_SIZE; dataCnt++)
        {
            // clear lutmem for next iteration
            write_mem_18a(vex_lutmem_base_addr + (dataCnt*4) , 1, &Val_out , "Val_out");
        }
    }  
}

int rcsHaltsoftReset(void)
{
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;
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


int pollRsmFlagRcs(void *srp , int rcsCoreId)
{
    int Val_out = 0, sleepCnt = 1;
    int rv;
    // wait for core0 to complete the task
    if (rcsCoreId== SRP_RCS_RCP_CTRL_AX)
    {
        do
        {
            read_mem_18a(rsm_flag_addr[0],1,&Val_out,"rsm_flag_addr");
            sleep(1);
            sleepCnt++;
            if(sleepCnt > 15)
            {
                print("Host:------ ERROR: RCS LX7 CORE0 DIDNT FINISH EXECUTION!!! ------\n");
                return rv;
            }
            //printf("loop1val:%x, rsm_flag_addr[rcsCoreId] :%x\n",Val_out,rsm_flag_addr[rcsCoreId]);
        } while (Val_out != 0xD0C0);
    }
    // wait for core1 to complete the task
    if (rcsCoreId== SRP_RCS_RCP_CTRL_RX)
    {
        do
        {	
            read_mem_18a(rsm_flag_addr[1],1,&Val_out,"rsm_flag_addr");
            sleep(1);
            sleepCnt++;
            if(sleepCnt > 15)
            {
                print("Host:------ ERROR: RCS LX7 CORE1 DIDNT FINISH EXECUTION!!! ------\n");
                return rv;
            }
        } while (Val_out != 0xD0C1);
    }
    // wait for core1 to complete the task
    if (rcsCoreId== SRP_RCS_RCP_CTRL_TX)
    {
        do
        {
            read_mem_18a(rsm_flag_addr[2],1,&Val_out,"rsm_flag_addr");
            sleep(1);
            sleepCnt++;
            if(sleepCnt > 15)
            {   
                print("Host:------ ERROR: RCS LX7 CORE2 DIDNT FINISH EXECUTION!!! ------\n");
                return rv;
            }
        } while (Val_out != 0xD0C2);	
    }	
}	
	
