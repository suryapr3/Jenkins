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
#include "lutmem_write.hive.h"
#include "lutmem_write_prog.map.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

int
main(int vexCoreId, unsigned test_pattern)
//main(int argc, const char * argv[])
{
    int rv = 0;
    
    int lc,i;
    unsigned data=0;
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    unsigned int vex_lutmem_offset = VEXABC1_LUTMEM_VE32_SIMD0_BASE - VEXABC0_LUTMEM_VE32_SIMD0_BASE;
    unsigned int vex_lutmem_base_addr = VEXABC0_LUTMEM_VE32_SIMD0_BASE + (vexCoreId * vex_lutmem_offset);

    int offsetVal[1] = {HIVE_ADDR_lutmem_write_prog_pattern 
    };
    unsigned Val_kargs[2] = {test_pattern 
    };

    unsigned Val_out[NUM_OF_ELEMENTS_PER_VEC] =  {0};
    
    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();

    print("Host: start vex %d program load\n", vexCoreId);
    vex_loader(vexCoreId, "vex_fw/sim_m64/lutmem_write_prog.fw");
    
    print("Host: vex %d program load - done !!\n", vexCoreId);
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
    {
        write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "gscalar[lc]");
    }

    print("Host: vex %d program start\n", vexCoreId);
  
    vex_start(vexCoreId, 0);
   
    
    print("Host: vex %d program start - done\n", vexCoreId);
    vex_wait(vexCoreId);

    //Load and compare vector output from cell to host
    print("Host:comparing result with reference test pattern (0x%x) -- vector \n",test_pattern);
    
    
    for (lc = 0; lc < LUTMEM_VEC_NUM *2 ; lc++)
    {
        for(i=0;i<32;i++)
        {
            read_mem_18a(vex_lutmem_base_addr + (lc * NUM_OF_ELEMENTS_PER_VEC * sizeof(unsigned))+(i * sizeof(int)), 1, &Val_out[i] , "Val_out");
            if(Val_out[i] != test_pattern)
            {
                print("ERROR:vecsum[%d]: ox%08x [ox%08x] (diff = %d)\n", i, Val_out[i],test_pattern, (Val_out[i] - test_pattern));
                rv =-1;
            }
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
