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
#include "trx_sys_csr.h"



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000
#define DMEM_OFFSET (0x4000)

#define VEX_BASE(vex_num)       ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

int rsm_buffer[] = {0x220000, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};

static void rcsHaltsoftReset(void)
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
        read_mem_18a(rsm_buffer[0] +0x10, 1, &rdWrVal, "rsm_buffer");
        //system("srpRead 0x220000");  
    } while(rdWrVal != 0xABCD);
}

static void test_interrupt_with_mask(int vexId, int bMaskEnabled, int tx_map_bmask)
{
    int vex_car_high_int_status_addr = VEXA_CAR_BASE + CAR_HIGH_INT_STAT0_OFFSET + 4*(vexId/4);
    int expected_bit_pos = CAR_HIGH_INT_STAT_VEX_WDT0_INT_STAT_BF_OFF + 8*(vexId%4);
    
    unsigned int vex_wdt_int_status;
    unsigned int vex_wdt_int_masked_stat;
    unsigned int vex_wdt_int_enable;
    unsigned int vex_wdt_int_force;
    unsigned int vex_wdt_int_clear;
    unsigned int vex_wdt_int_bitmask_pos;
    unsigned int tx_alarm_en;
    unsigned int tx_alarm_bitmask_pos;
    unsigned int tx_alarm_map;
    unsigned int tx_alarm_map_addr;
    unsigned int trx_sys_csr_base;
	
    if (vexId < 32)
    {
        vex_wdt_int_status = CAR_VEX_WDT_INT_STAT0_ADR;
        vex_wdt_int_masked_stat = CAR_VEX_WDT_INT_MASKED_STAT0_ADR;
        vex_wdt_int_enable = CAR_VEX_WDT_INT_EN0_ADR;
        vex_wdt_int_force  = CAR_VEX_WDT_INT_FORCE0_ADR;
        vex_wdt_int_clear = CAR_VEX_WDT_INT_CLR0_ADR;
        vex_wdt_int_bitmask_pos = vexId;
        tx_alarm_en = CAR_TX_ALARM_EN0_ADR;
        tx_alarm_bitmask_pos = vexId;
           
    }
    else
    {
        vex_wdt_int_status = CAR_VEX_WDT_INT_STAT1_ADR;
        vex_wdt_int_masked_stat = CAR_VEX_WDT_INT_MASKED_STAT1_ADR;
        vex_wdt_int_enable = CAR_VEX_WDT_INT_EN1_ADR;
        vex_wdt_int_force  = CAR_VEX_WDT_INT_FORCE1_ADR;
        vex_wdt_int_clear = CAR_VEX_WDT_INT_CLR1_ADR;
        vex_wdt_int_bitmask_pos = vexId - 32;
        tx_alarm_en = CAR_TX_ALARM_EN1_ADR;
        tx_alarm_bitmask_pos = vexId-32;
        
    }
    
    int index = vexId%8;
    tx_alarm_map = tx_map_bmask << (4 * index);
    if (tx_map_bmask == 0x0)
    {
        trx_sys_csr_base =TRX_SYS0_CSR_BASE ;
    }
    else if(tx_map_bmask == 0x1)
    {
        trx_sys_csr_base =TRX_SYS2_CSR_BASE ;
    }
	
    tx_alarm_map_addr = VEXA_CAR_BASE + CAR_TX_ALARM_MAP0_OFFSET + 4*(vexId/8);
	
    // enable tx alarm
    write_reg_18a(tx_alarm_en, 1 << tx_alarm_bitmask_pos, 0xFFFFFFFF, "tx_alarm_en");
    // enable tx alarm map
    write_reg_18a(tx_alarm_map_addr, tx_alarm_map, 0xFFFFFFFF, "tx_alarm_map"); 
    
    // pre check status, masked status, car_high_int_status
    read_reg_expect_18a(vex_wdt_int_masked_stat, 0, 0xFFFFFFFF, "vex_wdt_int_masked_stat");
    read_reg_expect_18a(vex_car_high_int_status_addr, 0, 0xFFFFFFFF, "car_high_int_status");

    // enable interrupt
    write_reg_18a(vex_wdt_int_enable, (1 & bMaskEnabled) << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_enable");
    
    // force interrupt
    write_reg_18a(vex_wdt_int_force, 1 << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_force");
 
    // check status, masked status
    read_reg_expect_18a(vex_wdt_int_status, 1 << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_status");
    read_reg_expect_18a(vex_wdt_int_masked_stat, (1 & bMaskEnabled) << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_masked_stat");
    
    // check car int high register
    read_reg_expect_18a(vex_car_high_int_status_addr, (1 & bMaskEnabled) << expected_bit_pos, 0xFFFFFFFF, "car_high_int_status");
	
    if (bMaskEnabled)
    {
        //wait_rcs_end();
        read_reg_expect_18a(rsm_buffer[0], 0x9876, 0xFFFFFFFF, "rsm_buffer[0]");
        // check tx alarm from vex array in Digrf trx_sys
        // check sticky register
        read_reg_expect_18a(trx_sys_csr_base+ TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys sticky for");
        // check status register
        read_reg_expect_18a(trx_sys_csr_base + TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys status");
        // clear interrupt status
        write_reg_18a(vex_wdt_int_clear, 1 << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_clear");
        // check sticky register
        read_reg_expect_18a(trx_sys_csr_base+ TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys sticky");
        // check status register
        read_reg_expect_18a(trx_sys_csr_base+ TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET,0x0,0xFFFFFFFF ,"Digrf trx_sys status");
    }
    else
    {
        read_reg_expect_18a(rsm_buffer[0], 0x0, 0xFFFFFFFF, "rsm_buffer[0]");
    }
       
    // clear interrupt status
    write_reg_18a(vex_wdt_int_clear, 1 << vex_wdt_int_bitmask_pos, 0xFFFFFFFF, "vex_wdt_int_clear");
}

int
main(int vexCoreId)
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
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = "../../../../src/rcs_fw/out/bin/vex_interrupt/ax_hw.elf"; // core0
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "../../../../src/rcs_fw/out/bin/vex_interrupt/rx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "../../../../src/rcs_fw/out/bin/vex_interrupt/tx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "../../../../src/rcs_fw/out/bin/vex_interrupt/cal_hw.elf";
    
    print("calling srp_rcs_config...\n");

    rcs_config(&rcs_params);
    
    write_reg_18a(rsm_buffer[0] + 4, vexCoreId, 0xFFFFFFFF, "vexCoreId");
    write_reg_18a(rsm_buffer[0] + 8, 1, 0xFFFFFFFF, "vexHighLow");
    
    print("Host: Testing wdt interrupt on vex %d!\n", vexCoreId);  
   
    // start core0
    for (rcsCoreId = SRP_RCS_RCP_CTRL_AX; rcsCoreId < SRP_RCS_RCP_MAX; rcsCoreId++)
    {
        rcs_rcp_start(rcsCoreId); 
        
        test_interrupt_with_mask(vexCoreId, 0, 0x0);
        test_interrupt_with_mask(vexCoreId, 0, 0x1);
        test_interrupt_with_mask(vexCoreId, 1, 0x0);
        test_interrupt_with_mask(vexCoreId, 1, 0x1);
        
    }
    
    return rv;
}
