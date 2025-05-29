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

#include "srp.h"                           // Should be the first file to include
#include "cli.h"
#include "init.h"
#include <stdio.h>
#include <stdbool.h>
//#include <srp_vex.h>
#include "logger.h"
//#include "srp_block_ids.h"
#include "all_comps.h"
#include "common_functions.h"
#include "noc.h"



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

const unsigned noc_base_array[] = {
VEXA_ABCNOC_JESD_0_P0_0X00000400_BASE,
VEXA_ABCNOC_JESD_0_P1_0X00000800_BASE,
//VEXA_ABCNOC_JESD_1_P0_0X00000C00_BASE,
//VEXA_ABCNOC_JESD_1_P1_0X00001000_BASE,

//VEXA_ABCNOC_RBC_0X00018800_BASE,
//VEXA_ABCNOC_RBC_RBM_0X00000000_BASE,

VEXA_ABCNOC_RCS_0_P0_0X00001400_BASE,

VEXA_ABCNOC_RXFB_0_P0_0X00001800_BASE,
VEXA_ABCNOC_RXFB_0_P1_0X00001C00_BASE,


//VEXA_ABCNOC_RXFB_1_P0_0X00002000_BASE,
//VEXA_ABCNOC_RXFB_1_P1_0X00002400_BASE,


VEXA_ABCNOC_V2D_0_P0_0X00002800_BASE,
VEXA_ABCNOC_V2D_0_P1_0X00002C00_BASE,
VEXA_ABCNOC_V2D_0_P2_0X00003000_BASE,
VEXA_ABCNOC_V2D_0_P3_0X00003400_BASE,
VEXA_ABCNOC_V2D_1_P0_0X00003800_BASE,
VEXA_ABCNOC_V2D_1_P1_0X00003C00_BASE,
VEXA_ABCNOC_V2D_1_P2_0X00004000_BASE,
VEXA_ABCNOC_V2D_1_P3_0X00004400_BASE,
VEXA_ABCNOC_V2D_2_P0_0X00004800_BASE,
VEXA_ABCNOC_V2D_2_P1_0X00004C00_BASE,
VEXA_ABCNOC_V2D_2_P2_0X00005000_BASE,
VEXA_ABCNOC_V2D_2_P3_0X00005400_BASE,
VEXA_ABCNOC_V2D_3_P0_0X00005800_BASE,
VEXA_ABCNOC_V2D_3_P1_0X00005C00_BASE,
VEXA_ABCNOC_V2D_3_P2_0X00006000_BASE,
VEXA_ABCNOC_V2D_3_P3_0X00006400_BASE,
/*VEXA_ABCNOC_V2D_4_P0_0X00006800_BASE,
VEXA_ABCNOC_V2D_4_P1_0X00006C00_BASE,
VEXA_ABCNOC_V2D_4_P2_0X00007000_BASE,
VEXA_ABCNOC_V2D_4_P3_0X00007400_BASE,
VEXA_ABCNOC_V2D_5_P0_0X00007800_BASE,
VEXA_ABCNOC_V2D_5_P1_0X00007C00_BASE,
VEXA_ABCNOC_V2D_5_P2_0X00008000_BASE,
VEXA_ABCNOC_V2D_5_P3_0X00008400_BASE,
VEXA_ABCNOC_V2D_6_P0_0X00008800_BASE,
VEXA_ABCNOC_V2D_6_P1_0X00008C00_BASE,
VEXA_ABCNOC_V2D_6_P2_0X00009000_BASE,
VEXA_ABCNOC_V2D_6_P3_0X00009400_BASE,
VEXA_ABCNOC_V2D_7_P0_0X00009800_BASE,
VEXA_ABCNOC_V2D_7_P1_0X00009C00_BASE,
VEXA_ABCNOC_V2D_7_P2_0X0000A000_BASE,
VEXA_ABCNOC_V2D_7_P3_0X0000A400_BASE,*/


VEXA_ABCNOC_VE_0_0_P0_0X0000A800_BASE,
VEXA_ABCNOC_VE_0_1_P0_0X0000AC00_BASE,
VEXA_ABCNOC_VE_0_2_P0_0X0000B000_BASE,
VEXA_ABCNOC_VE_0_3_P0_0X0000B400_BASE,
VEXA_ABCNOC_VE_0_4_P0_0X0000B800_BASE,
VEXA_ABCNOC_VE_0_5_P0_0X0000BC00_BASE,
VEXA_ABCNOC_VE_0_6_P0_0X0000C000_BASE,
VEXA_ABCNOC_VE_0_7_P0_0X0000C400_BASE,
VEXA_ABCNOC_VE_1_0_P0_0X0000C800_BASE,
VEXA_ABCNOC_VE_1_1_P0_0X0000CC00_BASE,
VEXA_ABCNOC_VE_1_2_P0_0X0000D000_BASE,
VEXA_ABCNOC_VE_1_3_P0_0X0000D400_BASE,
VEXA_ABCNOC_VE_1_4_P0_0X0000D800_BASE,
VEXA_ABCNOC_VE_1_5_P0_0X0000DC00_BASE,
VEXA_ABCNOC_VE_1_6_P0_0X0000E000_BASE,
VEXA_ABCNOC_VE_1_7_P0_0X0000E400_BASE,
/*VEXA_ABCNOC_VE_2_0_P0_0X0000E800_BASE,
VEXA_ABCNOC_VE_2_1_P0_0X0000EC00_BASE,
VEXA_ABCNOC_VE_2_2_P0_0X0000F000_BASE,
VEXA_ABCNOC_VE_2_3_P0_0X0000F400_BASE,
VEXA_ABCNOC_VE_2_4_P0_0X0000F800_BASE,
VEXA_ABCNOC_VE_2_5_P0_0X0000FC00_BASE,
VEXA_ABCNOC_VE_2_6_P0_0X00010000_BASE,
VEXA_ABCNOC_VE_2_7_P0_0X00010400_BASE,
VEXA_ABCNOC_VE_3_0_P0_0X00010800_BASE,
VEXA_ABCNOC_VE_3_1_P0_0X00010C00_BASE,
VEXA_ABCNOC_VE_3_2_P0_0X00011000_BASE,
VEXA_ABCNOC_VE_3_3_P0_0X00011400_BASE,
VEXA_ABCNOC_VE_3_4_P0_0X00011800_BASE,
VEXA_ABCNOC_VE_3_5_P0_0X00011C00_BASE,
VEXA_ABCNOC_VE_3_6_P0_0X00012000_BASE,
VEXA_ABCNOC_VE_3_7_P0_0X00012400_BASE,*/


VEXA_ABCNOC_VE_4_0_P0_0X00012800_BASE,
//VEXA_ABCNOC_VE_4_1_P0_0X00012C00_BASE,
VEXA_ABCNOC_VE_4_2_P0_0X00013000_BASE,
//VEXA_ABCNOC_VE_4_3_P0_0X00013400_BASE,
VEXA_ABCNOC_VE_4_4_P0_0X00013800_BASE,
//VEXA_ABCNOC_VE_4_5_P0_0X00013C00_BASE,
VEXA_ABCNOC_VE_4_6_P0_0X00014000_BASE,
//VEXA_ABCNOC_VE_4_7_P0_0X00014400_BASE,

VEXA_ABCNOC_VHA_0_P0_0X00014800_BASE,
VEXA_ABCNOC_VHA_0_P1_0X00014C00_BASE,
VEXA_ABCNOC_VHA_1_P0_0X00015000_BASE,
VEXA_ABCNOC_VHA_1_P1_0X00015400_BASE,
VEXA_ABCNOC_VHA_2_P0_0X00015800_BASE,
VEXA_ABCNOC_VHA_2_P1_0X00015C00_BASE,
VEXA_ABCNOC_VHA_3_P0_0X00016000_BASE,
VEXA_ABCNOC_VHA_3_P1_0X00016400_BASE,

/*VEXA_ABCNOC_VHA_4_P0_0X00016800_BASE,
VEXA_ABCNOC_VHA_4_P1_0X00016C00_BASE,
VEXA_ABCNOC_VHA_5_P0_0X00017000_BASE,
VEXA_ABCNOC_VHA_5_P1_0X00017400_BASE,
VEXA_ABCNOC_VHA_6_P0_0X00017800_BASE,
VEXA_ABCNOC_VHA_6_P1_0X00017C00_BASE,
VEXA_ABCNOC_VHA_7_P0_0X00018000_BASE,
VEXA_ABCNOC_VHA_7_P1_0X00018400_BASE,
*/
};

int rsm_buffer[] = {0x220000, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};


static void rcsHaltsoftReset(void)
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
    
    // remove soft reset core0
    write_reg_18a(RCS_GPREG_CORE0_CTRL_ADR, RCS_GPREG_CORE0_CTRL_DEFAULT,0xFFFFFFFF, "RCS_GPREG_CORE0_CONTROL_ADR");
    // remove soft reset of cores 1/2/3
    write_reg_18a(RCS_GPREG_SOFT_RST_ADR, RCS_GPREG_SOFT_RST_DEFAULT,0xFFFFFFFF, "RCS_GPREG_SOFT_RESET_ADR");
 
}

static void wait_rcs_end(void)
{
    unsigned int rdWrVal;
    do
    {
        read_mem_18a(rsm_buffer[0] + 0x10, 1, &rdWrVal, "rsm_buffer");
        //system("srpRead 0x220000");
        
    } while(rdWrVal != 0xABCD);
}

static void test_interrupt_with_mask(unsigned int noc_base, srp_rcs_rcp_t rcsCoreId)
{
    int i;

    int num_interrupts = 13; //18; // last 5 are disabled
    int status_offset = 0x58; //bridge_rbc_rbm_63_30_rbm_error_status_strg_value
    int clear_offset = 0x60; //bridge_rbc_rbm_63_30_rbm_error_status_value
    int error_inject_offset = 0x88; //bridge_rbc_rbm_63_30_rbm_error_inject_value
    
    
    for(i = 0; i < num_interrupts; i++)
    {
        if (i == 3) // E3 is unused
            continue;

        // start core0
        rcs_rcp_start(rcsCoreId);

        // pre check status, masked status, car_high_int_status
        read_reg_expect_18a(status_offset + noc_base, 0, 0xFFFFFFFF, "INT_STATUS");

        //force interrupt
        write_reg_18a(error_inject_offset + noc_base, 1 << i, 0xFFFFFFFF, "INT_FORCE");
        
        // check status, masked status
        read_reg_expect_18a(status_offset + noc_base, 1 << i, 0xFFFFFFFF, "INT_STATUS");


        //check rcs interrupt status
        wait_rcs_end();
        read_reg_expect_18a(rsm_buffer[0], 0x9876, 0xFFFFFFFF, "rsm_buffer[0]");
        //read_reg_expect_18a(vex_car_high_int_status_addr, (1 & bMaskEnabled) << expected_bit_pos, 0xFFFFFFFF, "car_high_int_status");
        
        // clear interrupt status
        write_reg_18a(clear_offset + noc_base, ~(1 << i), 0xFFFFFFFF, "INT_CLEAR");
        
        // post check status, masked status, car_high_int_status
        read_reg_expect_18a(status_offset + noc_base, 0, 0xFFFFFFFF, "INT_STATUS");
    }
}

static void rrc_rbm_test_interrupt_with_mask(int noc_base, int bMaskEnabled, srp_rcs_rcp_t rcsCoreId)
{
    int i;

    int num_interrupts = 7;
    int status_offset = 0x30; //bridge_rbc_rbm_63_30_rbm_error_status_strg_value
    int clear_offset = 0x38; //bridge_rbc_rbm_63_30_rbm_error_status_value
    int mask_offset = 0x40; //bridge_rbc_rbm_63_30_rbm_error_mask_value
    int error_inject_offset = 0x60; //bridge_rbc_rbm_63_30_rbm_error_inject_value
    
    
    for(i = 0; i < num_interrupts; i++)
    {
        if (i == 1) // E1 is unused
            continue;
        
        // start core0
        rcs_rcp_start(rcsCoreId);
        
        // pre check status, masked status, car_high_int_status
        read_reg_expect_18a(status_offset + noc_base, 0, 0xFFFFFFFF, "INT_STATUS");
        
        //enable interrupt
        write_reg_18a(mask_offset + noc_base, ~((1 & bMaskEnabled) << i), 0xFFFFFFFF, "INT_MASK");
        
        //force interrupt
        write_reg_18a(error_inject_offset + noc_base, 1 << i, 0xFFFFFFFF, "INT_FORCE");
        
        // check status, masked status
        read_reg_expect_18a(status_offset + noc_base, 1 << i, 0xFFFFFFFF, "INT_STATUS");


        //check rcs interrupt status
        // Uncomment below once its figured out which interrupt to expect
        //wait_rcs_end();
        if (bMaskEnabled)
            read_reg_expect_18a(rsm_buffer[0], 0x9876, 0xFFFFFFFF, "rsm_buffer[0]");
        
        // clear interrupt status
        write_reg_18a(clear_offset + noc_base, ~(1 << i), 0xFFFFFFFF, "INT_CLEAR");
        
        // post check status, masked status, car_high_int_status
        read_reg_expect_18a(status_offset + noc_base, 0, 0xFFFFFFFF, "INT_STATUS");
    }
}

int
main(void)
{
    int rv = 0;
    int lc,i;
    
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_AX;

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    // halt and soft reset all cores
    rcsHaltsoftReset();
    
    // fill in the .elf files
    memset(&rcs_params, 0, sizeof(rcs_params));
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../../../src/rcs_fw/out/bin/vex_interrupt/ax_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../../../src/rcs_fw/out/bin/vex_interrupt/rx_hw.elf"; // core1
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../../../src/rcs_fw/out/bin/vex_interrupt/tx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../../../src/rcs_fw/out/bin/vex_interrupt/cal_hw.elf";
    
    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);

    print("after srp_rcs_config...\n");

   
    write_reg_18a(rsm_buffer[0] + 8, 2, 0xFFFFFFFF, "vex_irq"); /* e_VEX_CRUX_NOC_INTERRUPT */
    
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId < SRP_RCS_RCP_MAX; rcsCoreId++)
    {
        for (i = 0; i < ARRAY_SIZE(noc_base_array); i++)
        {
            test_interrupt_with_mask(noc_base_array[i], rcsCoreId);
        }
    }


    //write_reg_18a(rsm_buffer[0] + 8, 3, 0xFFFFFFFF, "vex_irq"); /* e_VEX_ORION_NOC_INTERRUPT */
    // start core0
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId < SRP_RCS_RCP_MAX; rcsCoreId++)
    {   
        rrc_rbm_test_interrupt_with_mask(VEXA_ABCNOC_RBC_RBM_0X00000000_BASE, 1, rcsCoreId);
        rrc_rbm_test_interrupt_with_mask(VEXA_ABCNOC_RBC_RBM_0X00000000_BASE, 0, rcsCoreId);
    }
    return rv;
}
