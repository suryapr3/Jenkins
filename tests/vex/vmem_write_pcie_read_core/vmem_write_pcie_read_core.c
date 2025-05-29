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
#include "common_functions.h"
#include "all_comps.h"

#include "vmem_read.hive.h"
#include "vmem_read_prog.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define DMEM_OFFSET (0x4000)
#define VMEM_OFFSET (0x28000)

int
main(int vexCoreId, unsigned test_pattern)
//main(int argc, const char * argv[])
{
    int rv = 0;
    int lc;
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexCoreId * vex_vmem_offset);
    
    int offsetVal[1] = {HIVE_ADDR_vmem_read_prog_pattern
    };
    unsigned Val_kargs[1] = {test_pattern
    };

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    init();

    print("Host: start vex %d program load\n", vexCoreId);
    vex_loader(vexCoreId, "vex_fw/sim_m64/vmem_read_prog.fw");
    
    print("Host: vex %d program load - done !!\n", vexCoreId);
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
    {
        write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "gscalar"); 
    }
    
    
    // write the test_pattern into vex vmem
    for (lc = 0; lc < VEX_NUM_VEC * 32; lc++)
    {
        write_mem_18a(vex_vmem_base_addr + HIVE_ADDR_vmem_read_prog_gvector + (lc * 4), 1, &test_pattern, "gvector");    
    }

    print("Host: vex %d program start\n", vexCoreId);
    
    vex_start(vexCoreId, 0);

    print("Host: vex %d program start - done\n", vexCoreId);
    sleep(1);

    //Load and compare vector output from cell to host
    print("Host:comparing result with reference test pattern (0x%x) -- vector \n",test_pattern);

    for (lc = 0; lc < VEX_NUM_VEC * 32; lc++)
    {
        unsigned data;
        
        read_mem_18a( vex_vmem_base_addr + HIVE_ADDR_vmem_read_prog_gvector + (lc * 4), 1, &data, "gvector");
    
        if(data != 0)
        {
            print("ERROR:expected data[0x%08x], actual data[0x%08x], address[0x%08x]\n", 0, data, (lc * 4) );
            rv =-1;
        }   
    }


    if(rv==0)
    {
        print("Host:------ SUCCESS ------\n");
    }
    else
    {
        print("Host:------ FAILURE ------\n");
    }

    LOG_PRINT("INFO:logger ending !\n");
    return rv;
}
