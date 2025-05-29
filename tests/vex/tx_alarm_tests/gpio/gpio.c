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

#define VEX_BASE(vex_num)       ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))


static void test_interrupt_with_mask(int vexId, int tx_map_bmask)
{
    
    int gpio_reg_en = VEXABC0_GP_VE32_TILE_CTRL_BASE + (0x40000*vexId);
    
    unsigned int tx_alarm_en;
    unsigned int tx_alarm_map;
    unsigned int tx_alarm_map_addr;
    unsigned int tx_alarm_bitmask_pos;
    unsigned int gpio_alarm_en;
    unsigned int gpio_alarm_bitmask_pos;
    unsigned int trx_sys_csr_base;
	
    if (vexId < 32)
    {
        tx_alarm_en = CAR_TX_ALARM_EN0_ADR;
        tx_alarm_bitmask_pos = vexId;
        gpio_alarm_en = CAR_GPIO_TX_ALM_EN0_ADR ;
        gpio_alarm_bitmask_pos = vexId;
         
    }
    else
    {
        tx_alarm_en = CAR_TX_ALARM_EN1_ADR;
        tx_alarm_bitmask_pos = vexId-32;
        gpio_alarm_en = CAR_GPIO_TX_ALM_EN1_ADR ;
        gpio_alarm_bitmask_pos = vexId-32;
        
    }
    if (tx_map_bmask == 0x0)
    {
        trx_sys_csr_base =TRX_SYS0_CSR_BASE ;
    }
    else if(tx_map_bmask == 0x1)
    {
        trx_sys_csr_base =TRX_SYS2_CSR_BASE ;
    }
    int index = vexId%8;
    tx_alarm_map = tx_map_bmask << (4 * index);
    tx_alarm_map_addr = VEXA_CAR_BASE + CAR_TX_ALARM_MAP0_OFFSET + 4*(vexId/8);
    
    // enable tx alarm
    write_reg_18a(tx_alarm_en, 1 << tx_alarm_bitmask_pos, 0xFFFFFFFF, "tx_alarm_en");
    
    // enable tx alarm map
    write_reg_18a(tx_alarm_map_addr, tx_alarm_map, 0xFFFFFFFF, "tx_alarm_map");   
     
    // enable gpio alarm
    write_reg_18a(gpio_alarm_en, 1 << gpio_alarm_bitmask_pos, 0xFFFFFFFF, "gpio_alarm_en");
    
    //enable gpio
    write_reg_18a(gpio_reg_en, 0x1, 0xFFFFFFFF, "gpio_alarm_en");
    
    // Check tx alarm from vex array in Digrf trx_sys
    // check sticky register
    read_reg_expect_18a(trx_sys_csr_base + TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys sticky");
    // check status register
    read_reg_expect_18a(trx_sys_csr_base + TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys status");
    // clear gpio
    write_reg_18a(gpio_reg_en, 0, 0xFFFFFFFF, "gpio_stat_clear");
    // check sticky register
    read_reg_expect_18a(trx_sys_csr_base + TRX_SYS_CSR_TX_ALARM0_STICKY_OFFSET,0x43,0xFFFFFFFF ,"Digrf trx_sys sticky");
    // check status register
    read_reg_expect_18a(trx_sys_csr_base+ TRX_SYS_CSR_TX_ALARM0_STAT_OFFSET,0x0,0xFFFFFFFF ,"Digrf trx_sys status"); //0x43

}


int
main(int vexCoreId)
{
    int rv = 0;
    int lc,i;
   
    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    print("Host: Testing gpio on vex %d!\n", vexCoreId);
         
    test_interrupt_with_mask(vexCoreId,  0x0);
    test_interrupt_with_mask(vexCoreId,  0x1);
	
    return rv;
}

