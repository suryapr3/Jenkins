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



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

const unsigned nsip_base_array[] = {
RCS_CRUX_NSIP_HBI_BASE,

DLNK_JESD0_NSIP_HBI_CSR_BASE,
DLNK_JESD1_NSIP_HBI_CSR_BASE,
//DLNK_JESDABC2_NSIP_HBI_CSR_BASE,
//DLNK_JESDABC3_NSIP_HBI_CSR_BASE,

V2D0_AV2D_APB_0_NSIP_HBI_0_BASE,
V2D0_AV2D_APB_0_NSIP_HBI_1_BASE,
V2D0_AV2D_APB_1_NSIP_HBI_0_BASE,
V2D0_AV2D_APB_1_NSIP_HBI_1_BASE,
V2D1_AV2D_APB_0_NSIP_HBI_0_BASE,
V2D1_AV2D_APB_0_NSIP_HBI_1_BASE,
V2D1_AV2D_APB_1_NSIP_HBI_0_BASE,
V2D1_AV2D_APB_1_NSIP_HBI_1_BASE,
V2D2_AV2D_APB_0_NSIP_HBI_0_BASE,
V2D2_AV2D_APB_0_NSIP_HBI_1_BASE,
V2D2_AV2D_APB_1_NSIP_HBI_0_BASE,
V2D2_AV2D_APB_1_NSIP_HBI_1_BASE,
V2D3_AV2D_APB_0_NSIP_HBI_0_BASE,
V2D3_AV2D_APB_0_NSIP_HBI_1_BASE,
V2D3_AV2D_APB_1_NSIP_HBI_0_BASE,
V2D3_AV2D_APB_1_NSIP_HBI_1_BASE,
//V2D4_AV2D_APB_0_NSIP_HBI_0_BASE,
//V2D4_AV2D_APB_0_NSIP_HBI_1_BASE,
//V2D4_AV2D_APB_1_NSIP_HBI_0_BASE,
//V2D4_AV2D_APB_1_NSIP_HBI_1_BASE,
//V2D5_AV2D_APB_0_NSIP_HBI_0_BASE,
//V2D5_AV2D_APB_0_NSIP_HBI_1_BASE,
//V2D5_AV2D_APB_1_NSIP_HBI_0_BASE,
//V2D5_AV2D_APB_1_NSIP_HBI_1_BASE,
//V2D6_AV2D_APB_0_NSIP_HBI_0_BASE,
//V2D6_AV2D_APB_0_NSIP_HBI_1_BASE,
//V2D6_AV2D_APB_1_NSIP_HBI_0_BASE,
//V2D6_AV2D_APB_1_NSIP_HBI_1_BASE,
//V2D7_AV2D_APB_0_NSIP_HBI_0_BASE,
//V2D7_AV2D_APB_0_NSIP_HBI_1_BASE,
//V2D7_AV2D_APB_1_NSIP_HBI_0_BASE,
//V2D7_AV2D_APB_1_NSIP_HBI_1_BASE,

VHA0_ANT0_NSIP_HBI_CSR_BASE,
VHA0_ANT1_NSIP_HBI_CSR_BASE,
VHA1_ANT0_NSIP_HBI_CSR_BASE,
VHA1_ANT1_NSIP_HBI_CSR_BASE,
VHA2_ANT0_NSIP_HBI_CSR_BASE,
VHA2_ANT1_NSIP_HBI_CSR_BASE,
VHA3_ANT0_NSIP_HBI_CSR_BASE,
VHA3_ANT1_NSIP_HBI_CSR_BASE,
//VHA4_ANT0_NSIP_HBI_CSR_BASE,
//VHA4_ANT1_NSIP_HBI_CSR_BASE,
//VHA5_ANT0_NSIP_HBI_CSR_BASE,
//VHA5_ANT1_NSIP_HBI_CSR_BASE,
//VHA6_ANT0_NSIP_HBI_CSR_BASE,
//VHA6_ANT1_NSIP_HBI_CSR_BASE,
//VHA7_ANT0_NSIP_HBI_CSR_BASE,
//VHA7_ANT1_NSIP_HBI_CSR_BASE,

//MEM_FB0_NSIP_HBI_0_BASE,
//MEM_FB0_NSIP_HBI_1_BASE,
//MEM_FB1_NSIP_HBI_0_BASE,
//MEM_FB1_NSIP_HBI_1_BASE,
};

int rsm_buffer[] = {0x220000, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};
// may change once new functions are added, check .map file
int dcode_buffer[] = {0xE4030, 0xE4040, 0xE4050, 0xE4060}; 

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
        read_mem_18a(rsm_buffer[0], 1, &rdWrVal, "rsm_buffer");
        //system("srpRead 0x220000");
        
    } while(rdWrVal != 0xABCD);
}

static void test_interrupt_with_mask(unsigned int nsip_base, int bIntHigh)
{
    int i;

    int num_interrupts = 20;
    
    for(i = 0; i < num_interrupts; i++)
    {    
        // pre check status, masked status, car_high_int_status
        read_reg_expect_18a(NSIP_HBI_INTR_INT_STAT_ADR(nsip_base), 0, 0xFFFFFFFF, "INT_STATUS");
        
        //enable interrupt
        if (bIntHigh)
        {
            write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(nsip_base), 1 << i, 0xFFFFFFFF, "INT_HIGH_EN");
        }
        else
        {
            write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(nsip_base), 1 << i, 0xFFFFFFFF, "INT_LOW_EN");
        }
        
        //force interrupt
        write_reg_18a(NSIP_HBI_INTR_INT_FORCE_ADR(nsip_base), 1 << i, 0xFFFFFFFF, "INT_FORCE");
        
        // check status, masked status
        read_reg_expect_18a(NSIP_HBI_INTR_INT_STAT_ADR(nsip_base), 1 << i, 0xFFFFFFFF, "INT_STATUS");

        
        //check rcs interrupt status
        //wait_rcs_end();
        //read_reg_expect_18a(dcode_buffer[0], 0x9876, 0xFFFFFFFF, "dcode_buffer[0]");
        //read_reg_expect_18a(vex_car_high_int_status_addr, (1 & bMaskEnabled) << expected_bit_pos, 0xFFFFFFFF, "car_high_int_status");
        
        // clear interrupt status
        write_reg_18a(NSIP_HBI_INTR_INT_CLR_ADR(nsip_base), 1 << i, 0xFFFFFFFF, "INT_CLEAR");
    }
}

int
main(void)
{
    int rv = 0;
    int lc,i;
    
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcsCoreId = SRP_RCS_RCP_CTRL_TX;

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    // halt and soft reset all cores
    rcsHaltsoftReset();
    
    // fill in the .elf files
    memset(&rcs_params, 0, sizeof(rcs_params));
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../../../src/rcs_fw/out/bin/vex_interrupt/ax_hw.elf"; // core0
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "./rcs/rx_hw.elf"; // core1
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "./rcs/tx_hw.elf";
    //rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "./rcs/cal_hw.elf";
    
    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);

    write_reg_18a(dcode_buffer[0] + 4, 0, 0xFFFFFFFF, "vexCoreId");
    write_reg_18a(dcode_buffer[0] + 8, 0, 0xFFFFFFFF, "vexHighLow");
        
    // start core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    
    //test_interrupt_with_mask(nsip_base_array[0], 1);
    
#if 1
    for (i = 0; i < ARRAY_SIZE(nsip_base_array); i++)
    {
        test_interrupt_with_mask(nsip_base_array[i], 0);
        test_interrupt_with_mask(nsip_base_array[i], 1);
    }
#endif
    return rv;
}
