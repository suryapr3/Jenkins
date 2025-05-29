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
#include "logger.h"
#include "all_comps.h"
#include "common_functions.h"
#include "vex_timer.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define TIMER_TEST_TIMEOUT (0x200)
#define TIMER_PERF_START_TIMEOUT (0x100)
#define TIMER_PERF_STOP_TIMEOUT (0x280)
#define TIMER_PERF_SNAP_TIMEOUT (0x290)

#define TIMER_LOOP_CYCLES (16)

int
main(int vexCoreId, int timer_id)
{
    int rv = 0;
    int lc;
    char srpReadCommand[50];
    unsigned count_exe_lsbs_data = 0;
    unsigned expected_count_exe_lsbs_min = 0;
    unsigned expected_count_exe_lsbs_max = 0;
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    
    unsigned int cell_addr[40] = { VEXABC0_SC_VE32_CELL_BASE,VEXABC1_SC_VE32_CELL_BASE,VEXABC2_SC_VE32_CELL_BASE,VEXABC3_SC_VE32_CELL_BASE,
            VEXABC4_SC_VE32_CELL_BASE,VEXABC5_SC_VE32_CELL_BASE,VEXABC6_SC_VE32_CELL_BASE,VEXABC7_SC_VE32_CELL_BASE,VEXABC8_SC_VE32_CELL_BASE,
            VEXABC9_SC_VE32_CELL_BASE,VEXABC10_SC_VE32_CELL_BASE,VEXABC11_SC_VE32_CELL_BASE,VEXABC12_SC_VE32_CELL_BASE,VEXABC13_SC_VE32_CELL_BASE,
            VEXABC14_SC_VE32_CELL_BASE,VEXABC15_SC_VE32_CELL_BASE,VEXABC16_SC_VE32_CELL_BASE,VEXABC17_SC_VE32_CELL_BASE,VEXABC18_SC_VE32_CELL_BASE,
            VEXABC19_SC_VE32_CELL_BASE,VEXABC20_SC_VE32_CELL_BASE,VEXABC21_SC_VE32_CELL_BASE,VEXABC22_SC_VE32_CELL_BASE,VEXABC23_SC_VE32_CELL_BASE,
            VEXABC24_SC_VE32_CELL_BASE,VEXABC25_SC_VE32_CELL_BASE,VEXABC26_SC_VE32_CELL_BASE,VEXABC27_SC_VE32_CELL_BASE,VEXABC28_SC_VE32_CELL_BASE,
            VEXABC29_SC_VE32_CELL_BASE,VEXABC30_SC_VE32_CELL_BASE,VEXABC31_SC_VE32_CELL_BASE,VEXABC32_SC_VE32_CELL_BASE,VEXABC33_SC_VE32_CELL_BASE,
            VEXABC34_SC_VE32_CELL_BASE,VEXABC35_SC_VE32_CELL_BASE,VEXABC36_SC_VE32_CELL_BASE,VEXABC37_SC_VE32_CELL_BASE,VEXABC38_SC_VE32_CELL_BASE,
            VEXABC39_SC_VE32_CELL_BASE
        };


    int offsetVal[] = {HIVE_ADDR_vex_timer_g_timeout_dut_cycles, HIVE_ADDR_vex_timer_g_timeout_perf_start_cycles,
        HIVE_ADDR_vex_timer_g_timeout_perf_stop_cycles, HIVE_ADDR_vex_timer_g_timeout_perf_snap_cycles,
        HIVE_ADDR_vex_timer_g_timer_dut_id, HIVE_ADDR_vex_timer_g_timer_perf_start_id,
        HIVE_ADDR_vex_timer_g_timer_perf_stop_id, HIVE_ADDR_vex_timer_g_timer_perf_snap_id
    };
    
    unsigned Val_kargs[] = {0x200,        0x100, 0x280, 0x290,
                            timer_id,    1,     2,     3  
                            //  1,     2,     3,     0
                            //  1,     0,     2,     3
    };
    
    Val_kargs[4+timer_id] = 0;

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();

    print("Host: start vex %d program load\n", vexCoreId);
    
    vex_loader(vexCoreId, "vex_fw/sim_m64/vex_timer.fw");
    
    print("Host: vex %d program load - done !!\n", vexCoreId);
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
    {
        write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "test_pattern");
    }


    print("Host: vex %d program start\n", vexCoreId);

    vex_start(vexCoreId, 0);

    print("Host: vex %d program start - done\n", vexCoreId);
    sleep(2);
    
    print("Host: timer %d program start \n", timer_id);
 
    count_exe_lsbs_data = read_reg_18a(cell_addr[vexCoreId]+ VE32_CELL_CNT_EXE_LSBS_OFFSET, "count_exe_lsbs_data");
 
    expected_count_exe_lsbs_min = (TIMER_TEST_TIMEOUT - TIMER_PERF_START_TIMEOUT) + TIMER_LOOP_CYCLES + 8;
    expected_count_exe_lsbs_max = expected_count_exe_lsbs_min + TIMER_LOOP_CYCLES;

    if(count_exe_lsbs_data < expected_count_exe_lsbs_min || count_exe_lsbs_data >= expected_count_exe_lsbs_max )
    {
        print("ERROR:actual[0x%08x], min[0x%08x], max[0x%08x]\n", count_exe_lsbs_data, expected_count_exe_lsbs_min, expected_count_exe_lsbs_max);
        rv =-1;
    }
    
    print("%d count_exe_lsbs_data\n", count_exe_lsbs_data);

    

    if(rv==0)
    {
        print("Host:------ SUCCESS ------\n");
    }
    else
    {
        print("Host:------ FAILURE ------\n");
    }
 
    LOG_PRINT("INFO:logger ending !\n");

    sprintf(srpReadCommand, "srpRead 0x63.%d.0x3000 44", vexCoreId);
    system(srpReadCommand);
    return rv;
}

    

    
