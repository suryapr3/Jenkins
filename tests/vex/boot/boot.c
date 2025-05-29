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

#include "common_functions.h"
#include "all_comps.h"

#include "boot_prog.map.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request
#define NUM_VEC_IN_BLK  3

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x10000

//extern srp_hdl_t vex_srp_hdl;

int
main(int vexCoreId, unsigned test_pattern)
//main(int argc, const char * argv[])
{
    int rv = 0;
    int lc;

    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);

    int offsetVal[] = {HIVE_ADDR_boot_prog_pattern, HIVE_ADDR_boot_prog_gscalar
    };
    
    unsigned Val_kargs[] = {test_pattern, 0
    };

    unsigned Val_out =  0;

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    
    print("Host: start vex %d program load\n", vexCoreId);
    vex_loader(vexCoreId, "vex_fw/sim_m64/boot_prog.fw");

    print("Host: vex %d program load - done !!\n", vexCoreId);
    
    
    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++)
    {
        write_mem_18a( vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "gscalar");
    }

    print("Host: vex %d program start\n", vexCoreId);

    vex_start(vexCoreId, 0);

    print("Host: vex %d program start - done\n", vexCoreId);
    vex_wait(vexCoreId);

    //Load and compare vector output from cell to host
    print("Host:comparing result with reference test pattern (0x%x) -- vector \n",test_pattern);

    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_boot_prog_gscalar, 1, &Val_out, "gscalar");

    if((Val_out) != (test_pattern))
    {
        printf("ERROR:test_pattern[%d]: ox%08x [ox%08x] (diff = %d)\n", 0, Val_out,test_pattern, (Val_out - test_pattern) );
        rv =1;
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
