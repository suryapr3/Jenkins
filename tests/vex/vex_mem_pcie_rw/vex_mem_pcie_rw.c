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

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)


#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request
#define NUM_VEC_IN_BLK  3

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#define NUM_OF_ELEMENTS_PER_VEC 32


#define PMEM_SIZE (64*1024) // bytes
#define PMEM_OFFSET (0x20000)

#define VMEM_SIZE (64*1024) // bytes
#define VMEM_OFFSET (0x30000)

#define DMEM_SIZE (16*1024) // bytes
#define DMEM_OFFSET (0x4000)

#define TEST_BLOCK_SIZE (1024)


int test_pmem(int vexCoreId, unsigned test_pattern)
{
    int rv;
    int lc;
    int i;
    
    unsigned int vex_pmem_offset = VEXABC1_PMEM_VE32_BP_CFG_BASE - VEXABC0_PMEM_VE32_BP_CFG_BASE;
    unsigned int vex_pmem_base_addr = VEXABC0_PMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_pmem_offset);

    print("Host: testing pmem, core id %d!\n", vexCoreId);
    
    for (lc = 0; lc < PMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for (i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            write_mem_18a(vex_pmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &test_pattern, "test_pattern");
        }
    }
    
    for (lc = 0; lc < PMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for(i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            unsigned data;
            
            // vex instruction width is in power of 2, 512 bits (8 words)
            // but vex internal instruction width is only 384 bits (6 words)
            // remaining two words are reserved. (for every 8 words, 6 are programmable and 2 are not)
    
            if( (i % 16)/4 == 3 )
                continue;
            
            read_mem_18a(vex_pmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &data, "data");
            
            if(data != test_pattern)
            {
                print("ERROR:expected data[0x%08x], actual data[0x%08x], address[0x%08x]\n", test_pattern, data, (lc * TEST_BLOCK_SIZE) + (i * 4) );
                rv =-1;
            }
        }
        print("PMEM %dkb tested\n", lc+1);
    }
    return rv;
}

int test_dmem(int vexCoreId, unsigned test_pattern)
{
    int rv;
    int lc,i;
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexCoreId * vex_dmem_offset);
    
    print("Host: testing dmem, core id %d!\n", vexCoreId);
    
    for (lc = 0; lc < DMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for (i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            write_mem_18a( vex_dmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &test_pattern, "test_pattern");
            
        }
    }
    
    for (lc = 0; lc < DMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for(i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            unsigned data;
            
            read_mem_18a( vex_dmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &data, "data");

            if(data != test_pattern)
            {
                print("ERROR:expected data[0x%08x], actual data[0x%08x], address[0x%08x]\n", test_pattern, data, (lc * TEST_BLOCK_SIZE) + (i * 4) );
                rv =-1;
            }
        }
        print("DMEM %dkb tested\n", lc+1);
    }
    return rv;
}

int test_vmem(int vexCoreId, unsigned test_pattern)
{
    int rv = 0;
    
    int lc,i;
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexCoreId * vex_vmem_offset);

    print("Host: testing vmem, core id %d!\n", vexCoreId);
    
    for (lc = 0; lc < VMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for (i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            write_mem_18a( vex_vmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &test_pattern, "test_pattern");    
        }
    }
    
    for (lc = 0; lc < VMEM_SIZE/TEST_BLOCK_SIZE; lc++)
    {
        for(i = 0; i < TEST_BLOCK_SIZE/sizeof(unsigned); i++)
        {
            unsigned data;
            
            read_mem_18a( vex_vmem_base_addr + (i * 4) + (lc * TEST_BLOCK_SIZE), 1, &data, "data");
            if(data != test_pattern)
            {
                print("ERROR:expected data[0x%08x], actual data[0x%08x], address[0x%08x]\n", test_pattern, data, (lc * TEST_BLOCK_SIZE) + (i * 4) );
                rv =-1;
            }
        }
        print("VMEM %dkb tested\n", lc+1);
    }
    return rv;
}

int
main(int vexCoreId, unsigned test_pattern)
//main(int argc, const char * argv[])
{
    int rv = 0;

    print("Host: main starts!\n");
    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    
    rv = test_dmem(vexCoreId, test_pattern);
    rv += test_vmem(vexCoreId, test_pattern);
    rv += test_pmem(vexCoreId, test_pattern);

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
