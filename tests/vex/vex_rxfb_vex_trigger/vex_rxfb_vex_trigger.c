/*********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/
/**
 * @file    rxfb_vex_connectivity.c
 * @brief   HOST Configuration code for sending the data from VEX to RXFB and receving it back.
 * @details 1. Configuration of VEX, RXFB and Common Module for sending data from VEX to RXFB
 and receving it back to VEX for all the Sample Rates
 2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 1. 256 samples (8 vectors) for given data rate will be streamed to RXFB from
 configured VEX core.
 2. With RXFB NSIP loop back enabled the data looped back at sample interface
 was expected to reach the other VEX core where comparison will be performed.
 4. VEX core on which comparison algo was running will update the comparison result for
 every vector comparison and once the total 8 vector comparison was done HOST will
 read the result.
 5. Host will be waiting on a memory location where VEX will update the number of vectors
 it was processed.
 */

/*********************************************************************************************
 * LOCAL INCLUDE STATEMENTS                    *
 *********************************************************************************************/
#define HIVE_MULTIPLE_PROGRAMS
#include "srp.h"
#include <stdio.h>
#include <stdbool.h>
#include <srp_vex.h>
#include "logger.h"


#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"

#include<time.h> 

#include "vex_producer.map.h"


/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

//#define printf LOG_PRINT

#define NUM_TOTAL_VEC_PER_STREAM 64

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define NUMBER_OF_VECTORS_INPUT        ( 8 )
#define NUM_OF_ELEMENTS_PER_VEC        (  32 )

#define VMEM_OP_BUFF_OFFSET               ( 0x8000 )

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))
#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

#define MSB_PATTERN 7
#define SCRATCH_PATTERN 0x56785678

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef struct register_config_tbl_s {
    uint32_t addr;
    uint32_t value;
    uint32_t mask;
    char *name;
} register_config_tbl_t;

// Data type to hold table for NOC data
typedef struct noc_tbl_s {
    unsigned  address;
    unsigned  value;
    unsigned  core;
} noc_tbl_t;

typedef union
{
    struct
    {
    uint32_t sar_lsb;
    uint32_t sar_msb;
    uint32_t dar_lsb;
    uint32_t dar_msb;
    uint32_t block_ts;
    uint32_t res14;
    uint32_t llp_lsb;
    uint32_t llp_msb;
    mem_fb_dmac_ch1_ctl_reg_t ctl;
    uint32_t wb_lsb;
    uint32_t wb_msb;
    uint32_t llp_stat_lsb;
    uint32_t llp_stat_msb;
    uint32_t res38;
    uint32_t res3c;
    };
    uint32_t value[16];
} drf_dma_desc_t;


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
register_config_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};


static int g_rxfb_nsip_base_addr[2][2] = {{MEM_FB0_NSIP_HBI_0_BASE, MEM_FB0_NSIP_HBI_1_BASE}, {MEM_FB1_NSIP_HBI_0_BASE, MEM_FB1_NSIP_HBI_1_BASE}};

static uint32_t g_mem_fb_dmac_base_array[2][2] = {{MEM_FB0_DMAC_0_BASE, MEM_FB1_DMAC_0_BASE},
                                      {MEM_FB0_DMAC_1_BASE, MEM_FB1_DMAC_1_BASE}};

static unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};

mem_fb_dmac_ch1_ctl_reg_t dmac_ctl_reg = {
    .SRC_TR_WIDTH = 1,
    .DST_TR_WIDTH = 1,
    .SHADOWREG_OR_LLI_VALID = 1,
    .SRC_MSIZE = 2,
    .DST_MSIZE = 2,
    .DINC = 1,
    .ARLEN_EN = 1,
    .ARLEN = 0x5,
    .AWLEN_EN = 1,
    .AWLEN = 0x3,
    .IOC_BLKTFR=1,
    .DST_STAT_EN=1,
    .SRC_STAT_EN=1,
    .NONPOSTED_LASTWRITE_EN=0,
}; 

mem_fb_dmac_ch1_cfg_reg_t dmac_cfg_reg = {.SRC_MULTBLK_TYPE = 3,
    .DST_MULTBLK_TYPE = 3,
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,
    .HS_SEL_SRC = 0,
    .HS_SEL_DST = 1,
    .SRC_HWHS_POL = 0,
    .DST_HWHS_POL = 0,
    .SRC_PER = 1,
    .DST_PER = 1,
    .CH_PRIOR = 0x7,
    .LOCK_CH = 0,
    .LOCK_CH_L = 1,
    .SRC_OSR_LMT = 0xF,
    .DST_OSR_LMT = 0x6
};
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/



/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      tx_vex, rx_vex, rxfb_num
 * @return          status
 */

static int test_configure(int vexId, int rxfb_num, int nsipId)
{
    int i = 0, rv;
    
    static int rxfb_host_ids[2][2] = {{116, 117}, {119, 120}};
    int rxfb_nsip_hbi_base = g_rxfb_nsip_base_addr[rxfb_num][nsipId];

    int cio2strm_base = VE32_CELL_BASE(vexId) + VE32_TILE_CIO2STRM_OFFSET;
    int strm2cio_base = VE32_CELL_BASE(vexId) + VE32_TILE_STRM2CIO_OFFSET;
    
    register_config_tbl_t ve_cio2strm_config_tbl[] = {
        {CIO2STRM_INT_EN_ADR(cio2strm_base), 0x3F, 0xFFFFFFFF, "CIO2STRM_INT_ENABLE"},
        {CIO2STRM_FIFO_STAT_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "CIO2STRM_FIFO_STATUS_CTL"},
        {CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "CIO2STRM_WORD_CNT_CTL"},
        {CIO2STRM_RANGE_EN_ADR(cio2strm_base), 0x00000001, 0xFFFFFFFF, "CIO2STRM_RANGE_EN"},
        {CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "CIO2STRM_MEM_ADDR_LOW0"},
        {CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base), 0x3fffffff, 0xFFFFFFFF, "CIO2STRM_MEM_ADDR_HIGH0"},

        {CIO2STRM_MEM_OFFSET0_ADR(cio2strm_base), 0x00000000, 0xFFFFFFFF, "CIO2STRM_MEM_OFFSET0"},
        {CIO2STRM_STRM_DEST0_ADR(cio2strm_base), rxfb_host_ids[rxfb_num][nsipId], 0xFFFFFFFF, "CIO2STRM_STRM_DEST0"}
    };

    register_config_tbl_t ve_strm2cio_config_tbl[] = {
        {STRM2CIO_INT_EN_ADR(strm2cio_base), 0xF, 0xFFFFFFFF, "STRM2CIO_INT_ENABLE"},
        {STRM2CIO_FIFO_STAT_CTL_ADR(strm2cio_base), 0x1, 0xFFFFFFFF, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
        {STRM2CIO_WORD_CNT_CTL_ADR(strm2cio_base), 0x1, 0xFFFFFFFF, "STRM2CIO_MEM_WORD_CNT_CTL"},
    };

    register_config_tbl_t rxfb_port_nsip_hbi_config_tbl[] = {
        {NSIP_HBI_INTR_INT_HIGH_EN_ADR(rxfb_nsip_hbi_base), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_HIGH_EN"},
        {NSIP_HBI_INTR_INT_LOW_EN_ADR(rxfb_nsip_hbi_base), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_LOW_EN"},
       
        {NSIP_HBI_H2B_FF_FIFO_CTRL_ADR(rxfb_nsip_hbi_base), 0x184, 0xFFFFFFFF, "H2B_FIFO_CONTROL"},
        {NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(rxfb_nsip_hbi_base), 0x8, 0xFFFFFFFF, "H2B_BUF_SZ_HW_TBL0"},

        {NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), 0x18080, 0xFFFFFFFF, "H2B_TK_ADDR_LKUP_TBL0"},
        {NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), 0x18100, 0xFFFFFFFF, "H2B_MD_ADDR_LKUP_TBL0"},
        {NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), 0x80000000 | VMEM_OP_BUFF_OFFSET, 0xFFFFFFFF, "H2B_ADDR_LKUP_TBL0"},
        
        {NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_TK_ROUTE_LKUP_TBL0"},
        {NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_MD_ROUTE_LKUP_TBL0"},
        {NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(rxfb_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_ROUTE_LKUP_TBL0"},
        
        {NSIP_HBI_H2B_MD_CTRL_TBL0_ADR(rxfb_nsip_hbi_base), 0x4000000F, 0xFFFFFFFF, "H2B_MD_CONTROL_TBL0"},

        {NSIP_HBI_B2H_FF_FIFO_CTRL_ADR(rxfb_nsip_hbi_base), 0x184, 0xFFFFFFFF, "B2H_FIFO_CONTROL"},
        {NSIP_HBI_B2H_CSR_ADDR_TBL0_ADR(rxfb_nsip_hbi_base), 0x80000000, 0xFFFFFFFF, "B2H_ADDR_MAP_TBL0"},
        {NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_ADR(rxfb_nsip_hbi_base), 0x1, 0xFFFFFFFF, "B2H_ADDR_MASK_TBL0"},
    };
    

    printf("INFO: RXFB%d configuration completed\n", rxfb_num);

    for(i = 0; i < ARRAY_SIZE(rxfb_port_nsip_hbi_config_tbl); i++)
    {
        if(rv = write_reg_18a(rxfb_port_nsip_hbi_config_tbl[i].addr,
                              rxfb_port_nsip_hbi_config_tbl[i].value,
                              0xFFFFFFFF,
                              rxfb_port_nsip_hbi_config_tbl[i].name))
            return rv;
    }

    print("INFO: CM configuration completed\n");

    for(i = 0; i < ARRAY_SIZE(ve_cio2strm_config_tbl); i++)
    {
        if(rv = write_reg_18a(ve_cio2strm_config_tbl[i].addr,
                              ve_cio2strm_config_tbl[i].value,
                              0xFFFFFFFF,
                              ve_cio2strm_config_tbl[i].name))
            return rv;
    }

    print("INFO: CIO2STRM configuration completed\n");

    for(i = 0; i < ARRAY_SIZE(ve_strm2cio_config_tbl); i++)
    {
        if(rv = write_reg_18a(ve_strm2cio_config_tbl[i].addr,
                              ve_strm2cio_config_tbl[i].value,
                              0xFFFFFFFF,
                              ve_strm2cio_config_tbl[i].name))
            return rv;
    }
    print("INFO: STRM2CIO configuration completed\n");

    return rv;
}

static void enable_drf_memories(uint32_t rxfbId, uint32_t dmaId, uint32_t chId)
{
    int mem_fb_cfg_base[2] = {MEM_FB0_CFG_BASE, MEM_FB1_CFG_BASE};
    int mem_fb_dmac_base = g_mem_fb_dmac_base_array[dmaId][rxfbId];

    write_reg_18a(MEM_FB_EN_ADR(mem_fb_cfg_base[rxfbId]), 0x1, 0xf, "MEM_FB_EN");
    write_reg_18a(MEM_FB_PWR_DOWN_CTRL_ADR(mem_fb_cfg_base[rxfbId]), 0x0, 0x7f, "MEM_FB_PWR_DOWN_CTRL");
    write_reg_18a(MEM_FB_PWR_DOWN_CTRL_CHAIN_ADR(mem_fb_cfg_base[rxfbId]), 0x0, 0x1, "MEM_FB_PWR_DOWN_CTRL_CHAIN");
    
    write_reg_18a(MEM_FB_DMAC_CMNREG_INTSTAT_ENREG_ADR(mem_fb_dmac_base), 0xffffffff, 0xffffffff, "MEM_FB_DMAC_CMNREG_INTSTAT_ENREG");

    if (chId == 0)
    {
        write_reg_18a(MEM_FB_DMAC_CH1_INTSTAT_ENREG_ADR(mem_fb_dmac_base), 0xffffffff, 0xffffffff, "MEM_FB_DMAC_CH1_INTSTAT_ENREG");
    }
    else if (chId == 1)
    {
        write_reg_18a(MEM_FB_DMAC_CH2_INTSTAT_ENREG_ADR(mem_fb_dmac_base), 0xffffffff, 0xffffffff, "MEM_FB_DMAC_CH2_INTSTAT_ENREG");
    }
}

/**
 * function         drf_dma_set_descr()
 * @brief           Sets up a DRF DMA transfer descriptor. This function initializes and sets up a DRF DMA
 *                  (General Purpose Direct Memory Access transfer descriptor with the given parameters.
 *                  It zeroes out the descriptor structure,sets the source and destination addresses,
 *                  block transfer size, and control register value. It also marks the descriptor as the
 *                  last in a linked list and copies the descriptor settings to the descriptor buffer.
 * @param [in]      desc_idx, dst_addr, src_addr, block_size
 */

static void drf_dma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr, uint32_t block_size, int rxfbId)
{
    unsigned int mem_fb_desc_base[2] = {MEM_FB0_DESC_BASE, MEM_FB1_DESC_BASE};
    // The below  line declares a variable desc of type gpdma_desc_t,
    // which is presumably a structure that holds the details of a DMA transfer descriptor.
    drf_dma_desc_t desc;
    // The below line initializes the desc structure to zero.
    // It ensures that all fields in the descriptor are set to zero before setting specific fields.
    memset ((void *)&desc, 0, sizeof (drf_dma_desc_t));
    // The below  line sets the source address (least significant bits) in the descriptor to the value provided by src_addr
    desc.sar_lsb = src_addr;
    // The below  line sets the destination address (least significant bits) in the descriptor to the value provided by dst_addr
    desc.dar_lsb = dst_addr;
    // This  below line sets the block transfer size in the descriptor to the value provided by block_size.
    desc.block_ts = block_size;
    // This line sets the control register value in the descriptor to a value dmac_ctl_reg
    desc.ctl = dmac_ctl_reg;
    // This line sets a specific field within the control register,
    // this descriptor is the last in a linked list or that it should use shadow registers
    // while 1 indicates that the shadow register contents are valid
    //if (desc_idx == 2)
    desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    
    //desc.llp_lsb = (uint32_t)&descr_buffer[desc_idx + 1];
    // This line copies the contents of the desc structure into another memory location, presumably a buffer called descr_buffer.
    // This buffer might be an array or a memory-mapped register that the DMA controller uses to read the descriptor settings.
    
    for(int i=0; i<16; i++)
    {
        write_reg_18a(mem_fb_desc_base[rxfbId] + (i * 4), desc.value[i], 0xFFFFFFFF, "MEM_FB0_DESC");
    }
}


static void configure_dma(int rxfbId, int dmaId, int chId, int nsipId)
{
    uint32_t dest_addr, src_addr, block_size;
    uint32_t mem_fb_dmac_base = g_mem_fb_dmac_base_array[dmaId][rxfbId];

    block_size = 0xF;
    dest_addr = 0x108000;
    src_addr = 0; 

    if (nsipId == 1)
        dest_addr = 0x10A000;

    // set desc
    drf_dma_set_descr(0, dest_addr, src_addr, block_size, rxfbId);

    // enable dmac0
    write_reg_18a(MEM_FB_DMAC_CFGREG_ADR(mem_fb_dmac_base), 1, 0x1, "MEM_FB_DMAC_CFGREG");

    if (chId == 0)
    {
        // Channel 1 configuration.
        write_reg64_18a(MEM_FB_DMAC_CH1_CFG_ADR(mem_fb_dmac_base), dmac_cfg_reg.value, MEM_FB_DMAC_CH1_CFG_WR_MASK, "MEM_FB_DMAC_CH1_CFG");
        write_reg64_18a(MEM_FB_DMAC_CH1_CTL_ADR(mem_fb_dmac_base), dmac_ctl_reg.value, MEM_FB_DMAC_CH1_CTL_WR_MASK, "MEM_FB_DMAC_CH1_CTL");

        // Descr address.
        mem_fb_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)0x110000};//0x04510000};
        write_reg64_18a(MEM_FB_DMAC_CH1_LLP_ADR(mem_fb_dmac_base), llp_reg.value, MEM_FB_DMAC_CH1_LLP_WR_MASK, "MEM_FB_DMAC_CH1_LLP");

    }
    else if (chId == 1)
    {
        // Channel 2 configuration.
        write_reg64_18a(MEM_FB_DMAC_CH2_CFG_ADR(mem_fb_dmac_base), dmac_cfg_reg.value, MEM_FB_DMAC_CH2_CFG_WR_MASK, "MEM_FB_DMAC_CH2_CFG");
        write_reg64_18a(MEM_FB_DMAC_CH2_CTL_ADR(mem_fb_dmac_base), dmac_ctl_reg.value, MEM_FB_DMAC_CH2_CTL_WR_MASK, "MEM_FB_DMAC_CH2_CTL");

        // Descr address.
        mem_fb_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)0x110000};//0x04510000};
        write_reg64_18a(MEM_FB_DMAC_CH2_LLP_ADR(mem_fb_dmac_base), llp_reg.value, MEM_FB_DMAC_CH2_LLP_WR_MASK, "MEM_FB_DMAC_CH2_LLP");

    }
}


int init_test(int vexId, int rxfbId, int dmaId, int chId)
{
    int rv = 0;

    init(); // Initialize the srp

    print("HOST: all reset done\n");
    
    enable_drf_memories(rxfbId, dmaId, chId);

    // to clear the VEX memories before running a test
    vex_mem_clear(vexId, NULL);
    
    return rv;
}

int configure_producer(int vexIdx, int rxfb_num, int nsip_id)
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int dmem_offset = 0x4000;
    int host_flag = 1;
    int rxfb_nsip_hbi_base = g_rxfb_nsip_base_addr[rxfb_num][nsip_id];
    int strm2cio_base = VE32_CELL_BASE(vexIdx) + VE32_TILE_STRM2CIO_OFFSET;
    int strm2cio_word_count = 0;
    int error_count = 0, cnt = 0;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;
    unsigned int mem_fb_sram_base[2] = {MEM_FB0_SRAM_BASE, MEM_FB1_SRAM_BASE};

    unsigned stream_id[8]= {MSB_PATTERN, 9, 10, 11, 12, 13, 14, 15}; // Accepctble range 0 to 15
    unsigned val_op[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
/*            0x24       0x4        g_vex_exit
            0x20       0x4        g_host_indicator
            0x44       0x4        g_num_streams
            0x0        0x20       g_dest_buffer_base
            0x30       0x4        g_timeout_cycles
            0x28       0x4        g_timer_debug
            0x40       0x4        g_num_vec_per_stream
            0x2C       0x4        g_debug
            */

    unsigned vex_args_tbl[]={    0,            0x10000000,
                                0x20000000,    0x30000000,
                                0x40000000,    0x50000000,
                                0x60000000, 0x70000000,
                                1,            512,
                                NUMBER_OF_VECTORS_INPUT,            NUMBER_OF_VECTORS_INPUT,
                                0, 0x101016c0,
                                0x10101000, SCRATCH_PATTERN}; /* Vijay, change it to run forever */
                                                  
    unsigned vex_args_addr[] = {HIVE_ADDR_vex_producer_g_dest_buffer_addr, HIVE_ADDR_vex_producer_g_dest_buffer_addr + (1*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (2*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (3*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (4*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (5*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (6*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (7*4),
        HIVE_ADDR_vex_producer_g_num_streams, HIVE_ADDR_vex_producer_g_timeout_cycles,
        HIVE_ADDR_vex_producer_g_num_vec_per_stream, HIVE_ADDR_vex_producer_g_num_vec_to_transfer,
        HIVE_ADDR_vex_producer_g_run_forever, HIVE_ADDR_vex_producer_g_rxfb_dma0_ch0_llp_addr,
        HIVE_ADDR_vex_producer_g_rxfb_scratch_addr, HIVE_ADDR_vex_producer_g_rxfb_scratch_data};
        
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (vexIdx * vex_dmem_offset);
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexIdx * vex_vmem_offset);
    
    if ((rv = vex_loader(vexIdx, "producer/sim_m64/vex_producer.fw")))
        return rv;

    print("vex%d being configured as producer core",vexIdx);

    for (lc = 0; lc < ARRAY_SIZE(vex_args_tbl); lc++)
    {
        write_mem_18a(vex_dmem_base_addr + vex_args_addr[lc], 1, &vex_args_tbl[lc], "gscalar");
    }

    /* Input Vector Generation VEX_1*/

    for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
            val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
            val_inp[i][j] = val_inp[i][j] | (stream_id[vexIdx%8] << 28 | stream_id[vexIdx%8] << 12);
        }
        write_mem_18a(vex_vmem_base_addr + (i*NUM_OF_ELEMENTS_PER_VEC*sizeof(int)), (NUM_OF_ELEMENTS_PER_VEC), val_inp[i], "val_inp");
        
    }

    return rv;
}   // main ends


static void wait_dma_finish(int rxfbId, int dmaId, int chId)
{
    uint32_t mem_fb_dmac_base = g_mem_fb_dmac_base_array[dmaId][rxfbId];
    volatile uint32_t mem_fb_dmac_ch1_intstat_reg;

    if (chId == 0)
    {
        // Wait till the transfer is done
        mem_fb_dmac_ch1_intstat_reg = read_reg_18a(MEM_FB_DMAC_CH1_INTSTAT_ADR(mem_fb_dmac_base), "MEM_FB_DMAC_CH1_INTSTAT");

        // The function enters a while loop that continuously checks the DMA channel interrupt status register RCS_DMAC_CH1_INTSTATUS_REG.
        // Until the transfer complete bit (bit 0) is set, indicating that the DMA transfer has finished.
        while (0 == (mem_fb_dmac_ch1_intstat_reg & 0x1))
        {
            mem_fb_dmac_ch1_intstat_reg = read_reg_18a(MEM_FB_DMAC_CH1_INTSTAT_ADR(mem_fb_dmac_base), "MEM_FB_DMAC_CH1_INTSTAT");
        }
    }
    else if (chId == 1)
    {
        // Wait till the transfer is done
        mem_fb_dmac_ch1_intstat_reg = read_reg_18a(MEM_FB_DMAC_CH2_INTSTAT_ADR(mem_fb_dmac_base), "MEM_FB_DMAC_CH2_INTSTAT");

        // The function enters a while loop that continuously checks the DMA channel interrupt status register RCS_DMAC_CH1_INTSTATUS_REG.
        // Until the transfer complete bit (bit 0) is set, indicating that the DMA transfer has finished.
        while (0 == (mem_fb_dmac_ch1_intstat_reg & 0x1))
        {
            mem_fb_dmac_ch1_intstat_reg = read_reg_18a(MEM_FB_DMAC_CH2_INTSTAT_ADR(mem_fb_dmac_base), "MEM_FB_DMAC_CH2_INTSTAT");
        }
    }
}

static void start_transfer_data(int vexId, int rxfbId, int dmaId, int chId)
{
    unsigned int vex_vmem_offset = VEXABC1_VMEM_VE32_SIMD0_BASE - VEXABC0_VMEM_VE32_SIMD0_BASE;
    unsigned int vex_vmem_base_addr = VEXABC0_VMEM_VE32_SIMD0_BASE + (vexId * vex_vmem_offset);
    int i, j;
    unsigned val_op[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    int mem_fb_cfg_base[2] = {MEM_FB0_CFG_BASE, MEM_FB1_CFG_BASE};
    int mem_fb_sram_base[2] = {MEM_FB0_SRAM_BASE, MEM_FB1_SRAM_BASE};
    int mem_fb_dmac_base = g_mem_fb_dmac_base_array[dmaId][rxfbId];
    unsigned vex_trigger[16] = {0x00110000, 0, (1<<chId) << 8 | 1<<chId, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0};


    write_mem_18a(vex_vmem_base_addr + HIVE_ADDR_vex_producer_vDmaReqData, 16, &vex_trigger[0], "vex_trigger");
    write_reg_18a(MEM_FB_VEX_DMA_SEL_HALT_ADR(mem_fb_cfg_base[rxfbId]), 1 << chId, 0xF, "MEM_FB_VEX_DMA_SEL_HALT");

    vex_start(vexId, 0);
    vex_wait(vexId);
    wait_dma_finish(rxfbId, dmaId, chId);

    read_reg_expect_18a(MEM_FB_SCRATCH_ADR(mem_fb_cfg_base[rxfbId]), SCRATCH_PATTERN, 0xFFFFFFFF, "SCRATCH");

    for (i = 0; i < NUMBER_OF_VECTORS_INPUT; i++)
    {
        read_mem_18a(mem_fb_sram_base[rxfbId] + (i*NUM_OF_ELEMENTS_PER_VEC*sizeof(int)), (NUM_OF_ELEMENTS_PER_VEC), &val_op[i], "val_op");
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            if (val_op[i][j] != val_inp[i][j])
            {
                print("ERROR: Mem_FB : data mismatch, vec %d, index %d expected[0x%8x], received[0x%8x]\n", i, j, val_inp[i][j], val_op[i][j]);
            }
        }
    }
 
    for (i = 0; i < NUMBER_OF_VECTORS_INPUT; i++)
    {
        read_mem_18a(vex_vmem_base_addr + VMEM_OP_BUFF_OFFSET + (i*NUM_OF_ELEMENTS_PER_VEC*sizeof(int)), (NUM_OF_ELEMENTS_PER_VEC), &val_op[i], "check_transfer_data");
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            if (val_op[i][j] != val_inp[i][j])
            {
                print("ERROR: VMEM :data mismatch, vec %d, index %d expected[0x%8x], received[0x%8x]\n", i, j, val_inp[i][j], val_op[i][j]);
            }
        }
    }
}


int main (int vexId, int rxfbId, int dmaId, int chId, int nsipId)
{
    print("testing connectivity between vex%d, rxfb%d, dmac%d, ch%d, nsib_hbi_%d \n",vexId, rxfbId, dmaId, chId, nsipId);

    init_test(vexId, rxfbId, dmaId, chId);

    test_configure(vexId, rxfbId, nsipId);
    
    configure_producer(vexId, rxfbId, nsipId);
    
    configure_dma(rxfbId, dmaId, chId, nsipId);
    
    start_transfer_data(vexId, rxfbId, dmaId, chId);
    
    print("HOST: End of the Test execution....!\n");
    return 0;
}
