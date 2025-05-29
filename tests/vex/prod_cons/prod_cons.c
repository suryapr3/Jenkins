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

#include "producer.hive.h"
#include "producer_prog.map.h"
#include "consumer.hive.h"
#include "consumer_prog.map.h"

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

#define MAX_BLK_COUNT  80 //Has to be multiple of both producer and consumer blks per request
#define NUM_VEC_IN_BLK  3

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
//#define NUMBER_OF_VECTORS 2
#define NUM_OF_ELEMENTS_PER_VEC 32

#define STRM2CIO_2_VMEM  0
#define STRM2CIO_2_DMEM  0x18000 /* vmem of size 64kb starts from 0. dmem starts at the end of vmem physically */

#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))

// Data type to hold table for NOC data
typedef struct noc_tbl_s {
    unsigned  address;
    unsigned  value;
    unsigned  core;
    char      *name;
} noc_tbl_t;



void static relese_reset_abc_noc()
{
    write_reg_18a(CAR_NOC_CLK_GATE_ADR, 0, 0xFFFFFFFF, "CAR_NOC_CLK_GATE");
    write_reg_18a(CAR_NOC_SOFT_RST_ADR, 0, 0xFFFFFFFF, "CAR_NOC_CLK_GATE");
}

int static configure_noc(void *srp, int source_vex_id, int dest_vex_id)
{
    int i;
    int rv = 0;
    
    // Table with default NOC table to VE init
    noc_tbl_t noc_tbl[] = {
    //VE00->VE01 initialization

    //VE00 cio2strm
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET /* 0x8010 */ ,0x00000001, source_vex_id , "FIFO_STATUS_CTL"},//FIFO_STATUS_CTL
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET /* 0x8020 */ ,0x00000001, source_vex_id, "WORD_CNT_CTL" },//WORD_CNT_CTL
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET /* 0x8060 */ ,0x00000001, source_vex_id, "RANGE_EN" },//RANGE_EN -all ranges enabled

    //Range1 -default set to Zero
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET /* 0x8080 */ ,0x00000000, source_vex_id, "MEM_ADDR_LOW[0]" },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET /* 0x80C0 */ ,0x0001FFFF, source_vex_id, "MEM_ADDR_HIGH[0]" },//MEM_ADDR_HIGH[0]
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET /* 0x8100 */ ,0x00000000, source_vex_id, "MEM_OFFSET[0]" },//MEM_OFFSET[0]- is in words
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET /* 0x8140 */ ,dest_vex_id, source_vex_id, "STRM_DEST[0]" },//STRM_DEST[0] - mapped to VE01

    //Load the pointer copy address for the SDFGates
        { VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET /* 0xdc */ ,HIVE_ADDR_producer_prog_producer_sm_gate, source_vex_id, "lm_bpca_bp_dmem" },//lm_bpca_bp_dmem - mapped to VE00

        //destination cell
    //VE01 strm2cio
        { VE32_TILE_STRM2CIO_OFFSET + STRM2CIO_FIFO_STAT_CTL_OFFSET /* 0xc010 */ ,0x00000001, dest_vex_id, "FIFO_STATUS_CTL" },//FIFO_STATUS_CTL
        { VE32_TILE_STRM2CIO_OFFSET + STRM2CIO_WORD_CNT_CTL_OFFSET /* 0xc020 */ ,0x00000001, dest_vex_id, "WORD_CNT_CTL" },//WORD_CNT_CTL

    //VE01->VE00 initialization

    //VE01 cio2strm
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_FIFO_STAT_CTL_OFFSET /* 0x8010 */ ,0x00000001, dest_vex_id, "FIFO_STATUS_CTL" },//FIFO_STATUS_CTL
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_WORD_CNT_CTL_OFFSET /* 0x8020 */ ,0x00000001, dest_vex_id, "WORD_CNT_CTL" },//WORD_CNT_CTL
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_RANGE_EN_OFFSET /* 0x8060 */ ,0x00000001, dest_vex_id, "RANGE_EN" },//RANGE_EN -all ranges enabled

    //Range1 -default set to Zero
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_LOW0_OFFSET /* 0x8080 */ ,0x00000000, dest_vex_id, "MEM_ADDR_LOW[0]" },//MEM_ADDR_LOW[0] - [31-17] destination ID,[16-0] bits local address as seen from STRM2CIO
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_ADDR_HIGH0_OFFSET /* 0x80C0 */ ,0x0001FFFF, dest_vex_id, "MEM_ADDR_HIGH[0]" },//MEM_ADDR_HIGH[0]
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_MEM_OFFSET0_OFFSET /* 0x8100 */ ,0x00000000, dest_vex_id, "MEM_OFFSET[0]" },//MEM_OFFSET[0]- is in words
        { VE32_TILE_CIO2STRM_OFFSET + CIO2STRM_STRM_DEST0_OFFSET /* 0x8140 */ ,source_vex_id, dest_vex_id, "STRM_DEST[0]" },//STRM_DEST[0] - mapped to VE00
        
    //Load the pointer copy address for the SDFGates
        { VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_OFFSET /* 0xdc */ ,HIVE_ADDR_consumer_prog_consumer_sm_gate, dest_vex_id , "lm_bpca_bp_dmem"},//lm_bpca_bp_dmem - mapped to VE01

    };

    for(i = 0; i < ARRAY_SIZE(noc_tbl); i++)
    {

        if (rv = write_reg_18a(VE32_CELL_BASE(noc_tbl[i].core) + noc_tbl[i].address, noc_tbl[i].value, \
                0xFFFFFFFF, noc_tbl[i].name))
            return rv;
    }
    return rv;
}

int
main(int vexSrcCoreId, int vexDstCoreId)
{
    int rv;
    int lc,i;

    int number_blocks = MAX_BLK_COUNT;
    int number_vec = (number_blocks * NUM_VEC_IN_BLK);

    int dmemOffset = 0x4000;

    int offsetVal[5] = {HIVE_ADDR_producer_prog_producer_max_count,
            HIVE_ADDR_producer_prog_buffer_wa,
            HIVE_ADDR_producer_prog_buffer_va,
            HIVE_ADDR_producer_prog_producer_token_per_request,
            HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)
    };
    unsigned Val_kargs[5] = {number_blocks,
            (STRM2CIO_2_DMEM + HIVE_ADDR_consumer_prog_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)),
            (STRM2CIO_2_VMEM + HIVE_ADDR_consumer_prog_buffer),
            2,
            0
    };

    int offsetVal_2[4] = {HIVE_ADDR_consumer_prog_consumer_max_count,
            HIVE_ADDR_consumer_prog_buffer_ra,
            HIVE_ADDR_consumer_prog_consumer_token_per_request,
            HIVE_ADDR_consumer_prog_consumer_sm_gate + (CONSUMER_SM_BUF_ID*4)
    };
    unsigned Val_kargs_2[4] = {number_blocks,
            (STRM2CIO_2_DMEM + HIVE_ADDR_producer_prog_producer_sm_gate + (PRODUCER_SM_BUF_ID*4)),
            5,
            0
    };

    unsigned Val_out[NUM_VEC_IN_BLK][NUM_OF_ELEMENTS_PER_VEC] =  {0};

    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int src_vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexSrcCoreId * vex_dmem_offset);
    unsigned int dst_vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexDstCoreId * vex_dmem_offset);
    
    
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int dst_vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexDstCoreId * vex_vmem_offset);

    LOG_PRINT("INFO:logger begining !\n");
    
    init();
    
    vex_mem_clear(vexSrcCoreId, NULL);
    vex_mem_clear(vexDstCoreId, NULL);

    if ((rv = configure_noc(srp, vexSrcCoreId, vexDstCoreId)))
        return rv;
            
    print("Host: start vex program load for cores (%d, %d)\n", vexSrcCoreId, vexDstCoreId);
    vex_loader(vexSrcCoreId, "vex_fw/sim_m64/producer_prog.fw");
    vex_loader(vexDstCoreId, "vex_fw/sim_m64/consumer_prog.fw");

    print("Host: vex program load - done !!\n");

    for (lc = 0; lc < ARRAY_SIZE(offsetVal); lc++) {
        write_mem_18a( src_vex_dmem_base_addr + offsetVal[lc], 1, &Val_kargs[lc], "Val_kargs");
    }

    for (lc = 0; lc < ARRAY_SIZE(offsetVal_2); lc++) {
        write_mem_18a( dst_vex_dmem_base_addr + offsetVal_2[lc], 1, &Val_kargs_2[lc], "Val_kargs_2");
    }

    relese_reset_abc_noc();


    print("Host: vex program start\n");
    vex_start(vexSrcCoreId, 0);
    vex_start(vexDstCoreId, 0);
    
    print("Host: vex program start - done\n");
    vex_wait(vexSrcCoreId);
    vex_wait(vexDstCoreId);

    //Load and compare vector output from cell to host
    print("Host:comparing result with reference -- vector \n");

    for(i=0;i<32;i++)
    {
      int ref_sum;
      //sum of 1...n numbers = (n * (n+1))/2)
      int n = number_vec;
      ref_sum = ((n*(n+1))/2);
      
      read_mem_18a( dst_vex_vmem_base_addr + HIVE_ADDR_consumer_prog_gvecsum + (i*sizeof(int)), 1, &Val_out[0][i], "Val_out");

      print("vecsum[%d]: ox%08x [ox%08x]\n", i, Val_out[0][i],ref_sum);

      if(((short)Val_out[0][i]) != ((short)ref_sum))
      {
          print("ERROR:vecsum[%d]: ox%08x [ox%08x] (diff = %d)\n", i, Val_out[0][i],ref_sum, (Val_out[0][i] - ref_sum) );
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
