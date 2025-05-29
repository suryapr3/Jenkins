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

#include "common_functions.h"

#include "strm2cio.h"
#include "cio2strm.h"
#include "car.h"
#include "ve32_cell.h"
#include "all_comps.h"

#include "producer_consumer.hive.h"
#include "producer_consumer_prog.map.h"
#include "defines.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x18000 /* vmem of size 64kb starts from 0. dmem starts at the end of vmem physically */

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

// Data type to hold table for NOC data
typedef struct noc_tbl_s {
    unsigned  address;
    unsigned  value;
    unsigned  core;
    char      *name;
} noc_tbl_t;



//release reset noc

void static configure_noc(int source_vex_id, int past_vex_id, int dest_vex_id)
{
    int cio2strm_base = VE32_CELL_BASE(source_vex_id) + VE32_TILE_CIO2STRM_OFFSET;
    int strm2cio_base = VE32_CELL_BASE(source_vex_id) + VE32_TILE_STRM2CIO_OFFSET;
    int cell_base = VE32_CELL_BASE(source_vex_id);

    //source_vex_id cio2strm
    write_reg_18a(CIO2STRM_FIFO_STAT_CTL_ADR(cio2strm_base), 1, 0xFFFFFFFF, "cio2strm_fifo_status_ctl");
    write_reg_18a(CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base), 1, 0xFFFFFFFF, "cio2strm_word_cnt_ctl");
    write_reg_18a(CIO2STRM_RANGE_EN_ADR(cio2strm_base), 3, 0xFFFFFFFF, "cio2strm_range_en");

    //range 0
    //source_vex_id->past_vex_id
    write_reg_18a(CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base), 0x00000000, 0xFFFFFFFF, "cio2strm_mem_addr_low[0]");
    write_reg_18a(CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base), 0x0001FFFF, 0xFFFFFFFF, "cio2strm_mem_addr_high[0]");
    write_reg_18a(CIO2STRM_MEM_OFFSET0_ADR(cio2strm_base), 0x00000000, 0xFFFFFFFF, "cio2strm_mem_offset[0]");
    write_reg_18a(CIO2STRM_STRM_DEST0_ADR(cio2strm_base), past_vex_id, 0xFFFFFFFF, "cio2strm_strm_dest[0]");

    //range 1
    //source_vex_id->dest_vex_id
    write_reg_18a(CIO2STRM_MEM_ADDR_LOW1_ADR(cio2strm_base), 0x10000000, 0xFFFFFFFF, "cio2strm_mem_addr_low[1]");
    write_reg_18a(CIO2STRM_MEM_ADDR_HIGH1_ADR(cio2strm_base), 0x1001FFFF, 0xFFFFFFFF, "cio2strm_mem_addr_high[1]");
    write_reg_18a(CIO2STRM_MEM_OFFSET1_ADR(cio2strm_base), 0x00000000, 0xFFFFFFFF, "cio2strm_mem_offset[1]");
    write_reg_18a(CIO2STRM_STRM_DEST1_ADR(cio2strm_base), dest_vex_id, 0xFFFFFFFF, "cio2strm_strm_dest[1]");

    //soruce_vex_id strm2cio
    write_reg_18a(CIO2STRM_FIFO_STAT_CTL_ADR(strm2cio_base), 1, 0xFFFFFFFF, "strm2cio_fifo_status_ctl");
    write_reg_18a(CIO2STRM_WORD_CNT_CTL_ADR(strm2cio_base), 1, 0xFFFFFFFF, "strm2cio_word_cnt_ctl");

    write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(cell_base), HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate,0xFFFFFFFF, "lm_bpca_bp_dmem");

}

int
main()
{
    int rv = 0;
    int lc,i;
    
    int vexId;
    int valid_vex_cores[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 34, 36, 38};
    //int valid_vex_cores[] = {0, 1, 2, 3};

    int number_blocks = MAX_BLK_COUNT;
    int number_vec = (number_blocks * NUM_VEC_IN_BLK);
    

    
    int vex_result;
    int num_vex_core_count = ARRAY_SIZE(valid_vex_cores);

    int offsetVal[] = {HIVE_ADDR_producer_consumer_prog_first_vex_vex,
            HIVE_ADDR_producer_consumer_prog_first_cm_vex,
            HIVE_ADDR_producer_consumer_prog_last_vex_cm,
            HIVE_ADDR_producer_consumer_prog_producer_consumer_max_count,
            HIVE_ADDR_producer_consumer_prog_producer_consumer_token_per_request,

            HIVE_ADDR_producer_consumer_prog_buffer_ra,
            HIVE_ADDR_producer_consumer_prog_buffer_wa,
            HIVE_ADDR_producer_consumer_prog_buffer_va,

    };
    unsigned Val_kargs[] = {1,
            0,
            0,
            number_blocks,
            1,

            (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (PROD_SM_BUF_ID*4) + 0x00000000),
            (STRM2CIO_2_DMEM + HIVE_ADDR_producer_consumer_prog_producer_consumer_sm_gate + (CONS_SM_BUF_ID*4) + 0x10000000),
            (STRM2CIO_2_VMEM + HIVE_ADDR_producer_consumer_prog_buffer + 0x10000000),
    };

    unsigned Val_out[NUM_VEC_IN_BLK][NUM_OF_ELEMENTS_PER_VEC] =  {0};

    LOG_PRINT("INFO:logger begining !\n");

    init();

   /* if ((rv = relese_reset_abc_noc(srp)))
        return rv;*/

    for(i = 0; i < num_vex_core_count; i++)
    {
        int vexId= valid_vex_cores[i];
        unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
        unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexId * vex_dmem_offset);
        unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
        unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexId * vex_vmem_offset);
        
        print("Host: start vex program load for core(%d)\n", valid_vex_cores[i]);
        vex_mem_clear(valid_vex_cores[i], NULL);
        configure_noc(valid_vex_cores[i], valid_vex_cores[(i-1+num_vex_core_count)%num_vex_core_count], valid_vex_cores[(i+1+num_vex_core_count)%num_vex_core_count]);

        if ((rv = vex_loader(vexId, "sim/sim_m64/producer_consumer_prog.fw")))
            return rv;

        for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++) {
            
            write_mem_18a(vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "gscalar");    //doubt
        }
        Val_kargs[0] = 0;
        
        
    }
    print("Host: vex program load - done !!\n");
    
    for(i = 0; i < num_vex_core_count; i++)
    {
        vex_start(valid_vex_cores[i], 0);
    }
    print("Host: vex program start - done\n");

    vex_wait(valid_vex_cores[0]);
    
    
    int vexId1 = valid_vex_cores[0];
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexId1 * vex_dmem_offset);
        
    read_mem_18a( vex_dmem_base_addr + HIVE_ADDR_producer_consumer_prog_VEX_RESULT, 1, &vex_result, "vex_result");   

    //Load and compare output from cell to host
    print("final vex result [%d]\n",  vex_result);

    if(vex_result != TEST_PASS)
    {
        printf("ERROR: expected vex result = 3\n");
        rv = -1;
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
