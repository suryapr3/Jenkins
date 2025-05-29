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
#include "vex_core.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000
#define DMEM_OFFSET (0x4000)

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

int rsm_buffer[] = {0x220000, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};


typedef enum e_core_low_interrupt_type_
{
    e_core_low_interrupt_type_false_start,
    e_core_low_interrupt_type_sleep,
    e_core_low_interrupt_type_idle,
    e_core_low_interrupt_type_count
}e_core_low_interrupt_type;

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

static void generate_usecase(int vexId, e_core_low_interrupt_type interruptType)
{
	unsigned int vex_cell_offset = VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE;
    unsigned int vex_cell_base_addr = VEXABC0_SC_VE32_CELL_BASE + (vexId * vex_cell_offset);

	unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexId * vex_dmem_offset);

    unsigned int error_clear[] = {};
    unsigned int error_mask[] = {VE32_CELL_CTRL_IRQMSK_FALSE_START_BF_MSK, VE32_CELL_CTRL_IRQMSK_SLEEP_BF_MSK, VE32_CELL_CTRL_IRQMSK_IDLE_BF_MSK};
    unsigned int irq_mask[] = {VE32_CELL_SEQUENCER_IRQ_STTR_IRQ_FALSE_START_BF_MSK, VE32_CELL_SEQUENCER_IRQ_STTR_IRQ_SLEEP_BF_MSK, VE32_CELL_SEQUENCER_IRQ_STTR_IRQ_IDLE_BF_MSK};
    int intType = (int)interruptType;
    
    unsigned int core_control_reg = read_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, "cell_ctrl");
    
    print("generate_usecase entry %d\n", intType);
    
    switch(interruptType)
    {
		// core would be already running, try to start again for error
		case e_core_low_interrupt_type_false_start:
			//set mask
			write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_mask[intType],0xFFFFFFFF, "cell_ctrl");
			
			//trigger error
			//vex_start(vexId, 0);
			write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_mask[intType] | VE32_CELL_CTRL_START_BF_MSK,0xFFFFFFFF, "cell_ctrl");
			
			read_reg_expect_18a(vex_cell_base_addr + VE32_CELL_SEQUENCER_IRQ_STTR_OFFSET, irq_mask[intType], 0xFFFFFFFF, "sequencer_irq");
			
			break;
		case e_core_low_interrupt_type_sleep:
			//set mask
			write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_mask[intType],0xFFFFFFFF, "cell_ctrl");
			
			// core is in loop, pull it out of loop so it will enter sleep !
			write_reg_18a( vex_dmem_base_addr + HIVE_ADDR_vex_core_g_wait_in_loop, 0, 0xFFFFFFFF, "g_wait_in_loop");
			
			read_reg_expect_18a(vex_cell_base_addr + VE32_CELL_SEQUENCER_IRQ_STTR_OFFSET, irq_mask[intType], 0xFFFFFFFF, "sequencer_irq");
			
			break;
		case e_core_low_interrupt_type_idle:
			//set mask
			write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_mask[intType],0xFFFFFFFF, "cell_ctrl");
			
			// core is sleeping, start it so it runs to end and goes idle
			write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_mask[intType] | VE32_CELL_CTRL_START_BF_MSK | VE32_CELL_CTRL_RUN_BF_MSK,0xFFFFFFFF, "cell_ctrl");

			read_reg_expect_18a(vex_cell_base_addr + VE32_CELL_SEQUENCER_IRQ_STTR_OFFSET, irq_mask[intType], 0xFFFFFFFF, "sequencer_irq");
			break;
		default:
			break;
	}
}

static void clear_usecase(int vexId, e_core_low_interrupt_type interruptType)
{
	unsigned int vex_cell_offset = VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE;
    unsigned int vex_cell_base_addr = VEXABC0_SC_VE32_CELL_BASE + (vexId * vex_cell_offset);
    
    unsigned int error_clear[] = {VE32_CELL_CTRL_IRQCLR_FALSE_START_BF_MSK, VE32_CELL_CTRL_IRQCLR_SLEEP_BF_MSK, VE32_CELL_CTRL_IRQCLR_IDLE_BF_MSK};
    int intType = (int)interruptType;
    
    unsigned int core_control_reg = read_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, "cell_ctrl");
    write_reg_18a(vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, core_control_reg | error_clear[intType],0xFFFFFFFF, "cell_ctrl");		
}

static void test_interrupt_with_mask(int vexId, int bMaskEnabled)
{
    int vex_car_high_int_status_addr = VEXA_CAR_BASE + CAR_HIGH_INT_STAT0_OFFSET + 4*(vexId/4);
    //int expected_bit_pos = CAR_MEM_CAR_HIGH_INT_STATUS_VEX_LOW0_INT_STAT_BF_OFF + 8*(vexId%4);
    
    unsigned int vex_low_int_status;
    unsigned int vex_low_int_masked_stat;
    unsigned int vex_low_int_enable;
    unsigned int vex_low_int_force;
    unsigned int vex_low_int_clear;
    unsigned int vex_low_int_bitmask_pos;
    e_core_low_interrupt_type intType; 
    
    vex_start(vexId, 0);

    if (vexId < 32)
    {
        vex_low_int_status = CAR_VEX_LOW_INT_STAT0_ADR;
        vex_low_int_masked_stat = CAR_VEX_LOW_INT_MASKED_STAT0_ADR;
        vex_low_int_enable = CAR_VEX_LOW_INT_EN0_ADR;
        vex_low_int_force  = CAR_VEX_LOW_INT_FORCE0_ADR;
        vex_low_int_clear = CAR_VEX_LOW_INT_CLR0_ADR;
        vex_low_int_bitmask_pos = vexId;
    }
    else
    {
        vex_low_int_status = CAR_VEX_LOW_INT_STAT1_ADR;
        vex_low_int_masked_stat = CAR_VEX_LOW_INT_MASKED_STAT1_ADR;
        vex_low_int_enable = CAR_VEX_LOW_INT_EN1_ADR;
        vex_low_int_force  = CAR_VEX_LOW_INT_FORCE1_ADR;
        vex_low_int_clear = CAR_VEX_LOW_INT_CLR1_ADR;
        vex_low_int_bitmask_pos = vexId - 32;
    }

	for (intType = e_core_low_interrupt_type_false_start; intType < e_core_low_interrupt_type_count; intType++)
	{
		print("test_interrupt_with_mask entry %d\n", intType);
		
		// pre check status, masked status, car_high_int_status
		read_reg_expect_18a(vex_low_int_status, 0, 0xFFFFFFFF, "vex_low_int_status");
		read_reg_expect_18a(vex_low_int_masked_stat, 0, 0xFFFFFFFF, "vex_low_int_masked_stat");
		read_reg_expect_18a(vex_car_high_int_status_addr, 0, 0xFFFFFFFF, "car_high_int_status");

		//enable interrupt
		write_reg_18a(vex_low_int_enable, (1 & bMaskEnabled) << vex_low_int_bitmask_pos, 0xFFFFFFFF, "vex_low_int_enable");

		//force interrupt
		//write_reg_18a(vex_low_int_force, 1 << vex_low_int_bitmask_pos, 0xFFFFFFFF, "vex_low_int_force");
		generate_usecase(vexId, intType);

		// check status, masked status
		read_reg_expect_18a(vex_low_int_status, 1 << vex_low_int_bitmask_pos, 0xFFFFFFFF, "vex_low_int_status");
		read_reg_expect_18a(vex_low_int_masked_stat, (1 & bMaskEnabled) << vex_low_int_bitmask_pos, 0xFFFFFFFF, "vex_low_int_masked_stat");

		//check car int high register
		read_reg_expect_18a(vex_car_high_int_status_addr, 0, 0xFFFFFFFF, "car_high_int_status");
		if (bMaskEnabled)
		{
			//wait_rcs_end();
			read_reg_expect_18a(rsm_buffer[0], 0x9876, 0xFFFFFFFF, "rsm_buffer[0]");
		}
		else
		{
			read_reg_expect_18a(rsm_buffer[0], 0x0, 0xFFFFFFFF, "rsm_buffer[0]");
		}

		// clear interrupt status
		clear_usecase(vexId, intType);
		write_reg_18a(vex_low_int_clear, 1 << vex_low_int_bitmask_pos, 0xFFFFFFFF, "vex_low_int_clear");

    }
}


static void configure_vex(int vexCoreId)
{
	unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    int lc = 0;

    int offsetVal[] = {HIVE_ADDR_vex_core_g_wait_in_loop};
    unsigned Val_kargs[] = {1};
    
    vex_loader(vexCoreId, "vex_fw/sim_m64/vex_core.fw");
    
    print("Host: vex %d program load - done !!\n", vexCoreId);
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
    {
        write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "vex_args");
    }

    print("Host: vex %d program start\n", vexCoreId);
}

int
main(int vexCoreId)
{
    int rv =0;
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
    configure_vex(vexCoreId);
    
    write_reg_18a(rsm_buffer[0] + 4, vexCoreId, 0xFFFFFFFF, "vexCoreId");
    write_reg_18a(rsm_buffer[0] + 8, 0, 0xFFFFFFFF, "vexHighLow");
        
    // start core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX); 
    print("Host: Testing vex_low interrupt on vex %d!\n", vexCoreId);
    test_interrupt_with_mask(vexCoreId, 0);
    
    configure_vex(vexCoreId);
    test_interrupt_with_mask(vexCoreId, 1);

    return rv;
}
