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
#include <srp_vex.h>
#include "logger.h"
#include "srp_block_ids.h"
#include "all_comps.h"
#include "common_functions.h"



#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000
#define DMEM_OFFSET (0x4000)

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

static void generate_error_usecase(int vexId, int cio2strm_base)
{
    vex_loader(vexId, "vex_fw/sim_m64/vex2any_prog.fw");
    
    write_reg_18a(CIO2STRM_RANGE_EN_ADR(cio2strm_base), 0x3, 0xFFFFFFFF, "cio2strm_range_en");
    write_reg_18a(CIO2STRM_CREDIT_CNT_ADR(cio2strm_base), 0x4, 0xFFFFFFFF, "cio2strm_range_en");
    
    write_reg_18a(CIO2STRM_FIFO_STAT_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "cio2strm_range_en");
    write_reg_18a(CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "cio2strm_range_en");
    
    write_reg_18a(CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "cio2strm_range_en");
    write_reg_18a(CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "cio2strm_range_en");
    write_reg_18a(CIO2STRM_MEM_ADDR_LOW1_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "cio2strm_range_en");
    write_reg_18a(CIO2STRM_MEM_ADDR_HIGH1_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "cio2strm_range_en");

    vex_start(vexId, 0);
    vex_wait(vexId);
}

static void test_interrupt_with_mask(int vexId, int bMaskEnabled)
{
    int cio2strm_base = VE32_CELL_BASE(vexId) + VE32_TILE_CIO2STRM_OFFSET;
    int strm2cio_base = VE32_CELL_BASE(vexId) + VE32_TILE_STRM2CIO_OFFSET;
    int i = CIO2STRM_INT_EN_RANGE_ERR_INT_EN_BF_OFF;

    int num_interrupts = i;
    int vex_car_high_int_status_addr = VEXA_CAR_BASE + CAR_HIGH_INT_STAT0_OFFSET + 4*(vexId/4);
    int expected_bit_pos = CAR_HIGH_INT_STAT_C2S_ERR0_INT_STAT_BF_OFF + 8*(vexId%4);
    
    //for(i = 0; i < num_interrupts; i++)
    {    
        // pre check status, masked status, car_high_int_status
        read_reg_expect_18a(CIO2STRM_INT_STAT_ADR(cio2strm_base), 0, 0xFFFFFFFF, "cio2strm_int_status");
        read_reg_expect_18a(CIO2STRM_INT_MASKED_STAT_ADR(cio2strm_base), 0, 0xFFFFFFFF, "cio2strm_int_masked_stat");
        read_reg_expect_18a(vex_car_high_int_status_addr, 0, 0xFFFFFFFF, "car_high_int_status");
    
        //enable interrupt
        write_reg_18a(CIO2STRM_INT_EN_ADR(cio2strm_base), (1 & bMaskEnabled) << i, 0xFFFFFFFF, "cio2strm_int_enable");
        
        //force interrupt
        generate_error_usecase(vexId, cio2strm_base);
        //write_reg_18a(CIO2STRM_INT_FORCE_ADR(cio2strm_base), 1 << i, 0xFFFFFFFF, "cio2strm_int_force");
        
        // check status, masked status
        read_reg_expect_18a(CIO2STRM_INT_STAT_ADR(cio2strm_base), 1 << i, 0xFFFFFFFF, "cio2strm_int_status");
        read_reg_expect_18a(CIO2STRM_INT_MASKED_STAT_ADR(cio2strm_base), (1 & bMaskEnabled) << i, 0xFFFFFFFF, "cio2strm_int_masked_stat");
        
        //check car int high register
        read_reg_expect_18a(vex_car_high_int_status_addr, (1 & bMaskEnabled) << expected_bit_pos, 0xFFFFFFFF, "car_high_int_status");
        
        // clear interrupt status
        write_reg_18a(CIO2STRM_INT_CLR_ADR(cio2strm_base), 1 << i, 0xFFFFFFFF, "cio2strm_int_clear");
    }
}

int
main(int vexCoreId)
{
    int rv = 0;
    
    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");

    init();

    print("Host: Testing strm2cio interrupt on vex %d!\n", vexCoreId);
    test_interrupt_with_mask(vexCoreId, 0);
    test_interrupt_with_mask(vexCoreId, 1);

    return rv;
}
