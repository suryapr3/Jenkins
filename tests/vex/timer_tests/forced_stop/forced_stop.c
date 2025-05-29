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

#include "vex_timer.map.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define MEM_SIZE  (8)

int rcsHaltsoftReset(void);
//int rsm_flag_addr[] = {0x3ffec,0x3FFF4, 0x3FFF0, 0x3FFF8,0x3FFFc};

//char *rcsFilePath[] = { "./rcs/tx_hw.elf", "./rcs/rx_hw.elf", "./rcs/cal_hw.elf" };
//int test_pattern_rsm[] = {0x22222222, 0x33334444, 0x77778888,0xbbbbcccc};
//int test_pattern_dcode[] = {0x11111111, 0x11112222,0x55556666, 0x9999aaaa};
int rsm_offset[] = {0x210000, 0x218000, 0x220000,0x230000};
int dcode_offset[] = {0xE4030, 0x124030,0x164030, 0x1C4030};
int rsm_flag_addr[] = {0x23ffec,0x23FFF4, 0x23FFF0, 0x23FFF8,0x23FFFc};
int rsm_flag[] = {0x8844, 0x7788, 0x8877,0xABCD,0x0};
int rsm_com_flag[] = {0x1234, 0x5678, 0x6543};


int main(int timer_id)
{
    //srp_st_t srp_st = SRP_ST_SUCCESS;
    int rv = 0;
    int lc,i;
    int j=1,k=0;
    int Val_out=0;
    
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;    
    
    
    unsigned timer_var,valr = 0;
    unsigned data_index, data_stop_index = 0;
    unsigned rsm_data1,rsm_data2,rsm_data3,rsm_data4,rsm_data5 =0;
    unsigned diff,timer_stop_diff,Diff_value = 0;
    unsigned data[40][8];
    unsigned actual_calculated_val,expected_rsm_val;
    
    unsigned random_timer_dut_cycles = 0;
    unsigned MIN_TIMER_DUT_CYCLES=0x100;
    unsigned MAX_TIMER_DUT_CYCLES=0x200;
    
    char srpReadCommand[50];
    //int rsm_offset[] = {0x30000, 0x24030, 0x44000};
    
    int valid_vex_id_list[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 34, 36,38};
    //int valid_vex_id_list[] = {0, 1, 2, 3};
    
    int vexCoreId =valid_vex_id_list[sizeof(valid_vex_id_list) / sizeof(valid_vex_id_list[0]) - 1];
    int num_of_ids = sizeof(valid_vex_id_list) / sizeof(valid_vex_id_list[0]);
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    
    int offsetVal[] = {HIVE_ADDR_vex_timer_g_timer_dut_cycles,HIVE_ADDR_vex_timer_g_timer_dut_id
    };
    unsigned Val_kargs[] = {random_timer_dut_cycles,timer_id 
                            //  1,     2,     3,     0
                            //  1,     0,     2,     3
    };
    
    
    print("Host: main starts!\n");    
    init();    

  
    for(i=0 ; i < num_of_ids; ++i)
    {
        vexCoreId = valid_vex_id_list[i];
        rv=0;
       
        
        vex_mem_clear(vexCoreId, srp);
        print("Host: start vex %d program load\n", vexCoreId);
      
        vex_loader(vexCoreId, "vex_fw/sim_m64/vex_timer.fw");
          
    
        random_timer_dut_cycles= MIN_TIMER_DUT_CYCLES + (vexCoreId % (MAX_TIMER_DUT_CYCLES - MIN_TIMER_DUT_CYCLES + 5));
      
        Val_kargs[0] =random_timer_dut_cycles; 
        
        print("Host: vex %d program load - done !!\n", vexCoreId);

        for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
        {
            write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "gscalar");
        }
    
    }

    print("Host: vex %d program start\n", vexCoreId);
   
   // data_stop_index = num_of_ids * 3;
    
    for(i=0 ; i < num_of_ids; ++i)
    {
        vexCoreId = valid_vex_id_list[i];
        rv=0;
        
        vex_start(vexCoreId, 0);
        //srp_config(dev_id, srp, &srp_cfg, &srp_hdl);
        
        print("Host: vex %d program start - done\n", vexCoreId);
        print("Host: timer %d program start \n", timer_id);
     }   
    
       
    print("Host: RCS starts!\n");        
    
#if 1
    print("calling rcsHaltsoftReset\n");
    rcsHaltsoftReset();
#else
    print("calling srpReset\n");
    system("srpReset -W");
    sleep(1);
#endif
    
    memset(&rcs_params, 0, sizeof(rcs_params));
    
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../../src/rcs_fw/out/bin/rcs_vex_timer_control/ax_hw.elf"; // core0
     
    print("calling srp_rcs_config...\n");
    
    rcs_config(&rcs_params);

    sleep (1);
    
    // start core0
    
    rcs_rcp_start( SRP_RCS_RCP_CTRL_AX);
    
    sleep(1);
    do{
        
        read_mem_18a(rsm_flag_addr[rcsCoreId],1,&Val_out,"RSM_FLAG");
        #if 0
        if ((rv = srp_dev_block_read32(srp,
             SRP_BLOCK_RCS_RSM, /*BlockVal,*/
             0, /*IndexVal*/
             rsm_flag_addr[0],
                  &Val_out,
                    0x1,
                    flags)))
            return rv;
        #endif
        
        sleep(1);
        print("loop\n");
           
        } while (Val_out != 0x8844);
    

    for (int i = 0; i < num_of_ids; i++) 
    {
        for (int j = 0; j < MEM_SIZE; j++) 
        {
            
            read_mem_18a(rsm_offset[0] +(j*4) + (i*4*MEM_SIZE),1,&data[i][j],"RSM_OFFSET");
            #if 0
            
            if ((rv = srp_dev_block_read32(srp,
                SRP_BLOCK_RCS_RSM, /*BlockVal,*/
                0, /*IndexVal*/
                rsm_offset[0] +(j*4) + (i*4*MEM_SIZE),
                &data[i][j],
                1,
                flags)))
             
                return rv;
            #endif
            print("%x", data[i][j]);
        }    
            
     }   
 
    
    for(i=0 ; i < num_of_ids; ++i)
    {
        vexCoreId = valid_vex_id_list[i];
        
        int timer_var=0;
        
        random_timer_dut_cycles= MIN_TIMER_DUT_CYCLES + (vexCoreId % (MAX_TIMER_DUT_CYCLES - MIN_TIMER_DUT_CYCLES + 5));
        Val_kargs[0] =random_timer_dut_cycles;
        
        read_mem_18a( vex_dmem_base_addr +HIVE_ADDR_vex_timer_g_timer_start, 1, &timer_var, "timer_var");
        #if 0
        if ((rv = srp_dev_block_read32(srp,
            0x63, 
            vexCoreId, 
                    dmemOffset + HIVE_ADDR_vex_timer_g_timer_start,
                    &timer_var,
                    1,
                    flags)))
        
           return rv;
        #endif
           
         //check for timer start criteria
        if(abs(random_timer_dut_cycles - timer_var) <= 60)
        {
            print("TIMER CYCLES=[0x%08x], Timer Start=[0x%08x]\n", random_timer_dut_cycles, timer_var);
           
        } 
        else 
        {
            print("ERROR: TIMER CYCLES =[0x%08x] ,  Timer Start= [0x%08x]\n", random_timer_dut_cycles, timer_var);
            rv=-1;
        }    
    
        
        //Timer values from RCS 
        
        rsm_data1 = data[i][0];
        rsm_data2 = data[i][1];
        rsm_data3 = data[i][2];
        rsm_data4 = data[i][3];
        rsm_data5 = data[i][4];
             
        print(" %x , %x, %x, %x, %x \n", rsm_data1, rsm_data2, rsm_data3, rsm_data4, rsm_data5 ); 
    
        diff= rsm_data2-rsm_data1;
        timer_stop_diff= rsm_data5-rsm_data4;
       
        actual_calculated_val= (diff * (20- j) * 3) + ((k* 2)) +diff;
   
        expected_rsm_val= rsm_data4- rsm_data3;
        
        Diff_value=abs(actual_calculated_val-expected_rsm_val);
        
        j++;
        k++;
        
        
        //check 1 for timer stop criteria
        if(Diff_value<=1000)
        {
            print("SUCCESS:Difference between timer values before and after when timer is stopped : %d,Vex id:%d\n",Diff_value,vexCoreId);
        }
        else
        {
            print("ERROR : Difference between timer values before and after when timer is stopped : %d,Vex id :%d\n",Diff_value,vexCoreId);
            rv = -1;
        }
        
        
        
        //check 2 for timer stop criteria
        if(timer_stop_diff==0)
        {
            print("Diff bw timer values after stopping : %d,Vex id:%d\n",timer_stop_diff,vexCoreId);
        }
        else
        {
            print("ERROR : Diff bw timer values after stopping: %d,Vex id:%d\n",timer_stop_diff,vexCoreId);
            rv = -1;
        }
        
        print("Timer stop = %x, \n", rsm_data4 );
        print("\n");
    
}
    if(rv == 0)
    {
        print("Host:------ SUCCESS ------\n\n");
    }
    else
    {
        print("Host:------ FAILURE ------\n\n");
    }


    /*srp_return:
    if (srp_st != SRP_ST_SUCCESS) {
        srp_status_print("error", srp_st);
    }*/
    return rv;
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




    





    
