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
 * @file    dnrt_jesd_vex_loopback.c
 * @brief   HOST Configuration code for sending the data from JESD to VEX and receving it back at DNRT.
 * @details 1. Configuration of VEX, JESD and Common Module for sending data from JESD to VEX
 and sending it back to JESD for all the Sample Rates
 2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 1. 32K samples (1K vectors) for given data rate will be streamed from JESD from
 to VEX core.
 2. With VEX core loop back enabled the data looped back at sample interface
 was expected to reach the JESD and DNRT where comparison will be performed.
 3. The supported Sample rates are
 0.25IQ, 0.5IQ, 1IQ, 2IQ, 4IQ, 8IQ, 4R, 8R, 16R
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
#include "defines.h"

#include<time.h> 

#include "copy_kernal.map.h"
//#include "vha2vex_p5_8iq.map.h"


/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

//#define printf LOG_PRINT

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define VE32_TILE_CIO2STRM_OFFSET (VEXABC0_C2S_VE32_TILE_CIO2STRM_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0x8000 */
#define VE32_TILE_STRM2CIO_OFFSET (VEXABC0_S2C_VE32_TILE_STRM2CIO_BASE - VEXABC0_SC_VE32_CELL_BASE) /* 0xC000 */

#define NUMBER_OF_VECTORS_INPUT        ( 128 )   // Corresponds to 1 block of data for 8GSPS
#define NUM_OF_ELEMENTS_PER_VEC        (  32 )
#define VEX_MAX_BUF_SIZE               ( 256 )   // in vectors and it should be power of 2

#define VEX_BASE(vex_num)              ( VEXABC0_SC_VE32_CELL_BASE + (vex_num * 0x40000) )


#define DMEM_OFFSET 0x4000

extern int configure_jesd(uint32_t testcase);

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

typedef enum {
    JESD_SYS_RATE_IQ_P125 = 0,
    JESD_SYS_RATE_IQ_P25,
    JESD_SYS_RATE_IQ_P5,
    JESD_SYS_RATE_IQ_1,
    JESD_SYS_RATE_IQ_2,
    JESD_SYS_RATE_IQ_4,
    JESD_SYS_RATE_IQ_8,
} jesd_sys_rate_t;


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/* Vectors per block for the given sample rate which was defined as per order in sys_rate_t enum*/
const int g_vectors_per_block[2][6] =
{
     {2/*p125 gsps*/, 4/*p25*/, 8/*p5*/, 16/*1*/, 32/*2*/, 64/*4*/},
     {3/*p187*/, 6/*p375*/, 12/*75*/, 24/*1.5*/, 48/*3*/, 96/*6*/}
};
const uint32_t g_max_blocks = 1;


static register_config_tbl_t g_register_sequence_config_tbl[] = {
#include "register_sequence.h"
};

/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      tx_vex, rx_vex, vha_num, ant_num, in_rate and out_rate
 * @return          status
 */

static int register_configure(uint32_t rx_vex)
{
    int i, rv = 0;

    for(i = 0; i < ARRAY_SIZE(g_register_sequence_config_tbl); i++)
    {
        if(rv = write_reg_18a(g_register_sequence_config_tbl[i].addr,
                              g_register_sequence_config_tbl[i].value,
                              0xFFFFFFFF,
                              g_register_sequence_config_tbl[i].name))
            return rv;
    }

    print("INFO: Vex & HWA register configuration completed\n");

    return rv;
}

static void delay(unsigned int milliseconds){

    clock_t start = clock();

    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}



static void enable_sysref()
{
    //enable sysref
    system("frioPciWrite -F s5a3 -P 0x20000 0x02");
    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
}

static int init_test(uint32_t rx_vex)
{
    int rv = 0;
    
    configure_jesd(43);

    //init(); // Initialize the srp

    // Let's take the modules out of RESET
    print("HOST: Doing sub-system RESET cycle\n");

    //subsys_reset_cycle();
    //vex_reset_cycle();

    //crux_reset_cycle();

    print("HOST: all reset done\n");

    //sleep(2);


    
    return rv;
}


int configure_receiver(uint32_t rx_vex, jesd_sys_rate_t in_rate, jesd_sys_rate_t out_rate, uint32_t dl_clk)
{
    int cnt, lc, i, j, k;
    int rv = 0, flags = 0;
    int dmem_offset = 0x4000;
    unsigned val_out[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    FILE *fptr;
    
    int vex_rx_offset_val[] = {HIVE_ADDR_copy_kernal_g_num_vecs_in,
                               HIVE_ADDR_copy_kernal_g_num_blocks,
                               HIVE_ADDR_copy_kernal_g_tbs_in_blk,
                               HIVE_ADDR_copy_kernal_g_dest_ptr_address, HIVE_ADDR_copy_kernal_g_dest_ptr_address + (1 *4),
                               HIVE_ADDR_copy_kernal_g_dest_ptr_address + (2 *4), HIVE_ADDR_copy_kernal_g_dest_ptr_address + (3 *4),
                               HIVE_ADDR_copy_kernal_g_dest_ptr_address + (4 *4), HIVE_ADDR_copy_kernal_g_dest_ptr_address + (5 *4),
                               HIVE_ADDR_copy_kernal_g_dest_ptr_address + (6 *4), HIVE_ADDR_copy_kernal_g_dest_ptr_address + (7 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (CONSUMER_SM_BUF_ID *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (1 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (2 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (3 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (4 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (5 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (6 *4),
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (7 *4)};
    unsigned vex_rx_val_kargs[] = {NUMBER_OF_VECTORS_INPUT, 1, 64,
                               0      , 0x20000,
                               0x40000, 0x60000,
                               0x80000, 0xA0000,
                               0xC0000, 0xE0000,
                               0, 0, 
                               0, 0, 
                               0, 0, 
                               0, 0};
    
    unsigned int vex_dmem_offset = VEXABC1_DMEM_VE32_BP_CFG_BASE - VEXABC0_DMEM_VE32_BP_CFG_BASE;
    unsigned int rec_vex_dmem_base_addr = VEXABC0_DMEM_VE32_BP_CFG_BASE + (rx_vex * vex_dmem_offset);


    vex_rx_val_kargs[0] = g_vectors_per_block[dl_clk][out_rate];
    vex_rx_val_kargs[1] = g_max_blocks;
    vex_rx_val_kargs[2] = VEX_MAX_BUF_SIZE / g_vectors_per_block[dl_clk][out_rate];

    // SDF init
    if(rv = write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(VEX_BASE(rx_vex)),
                          HIVE_ADDR_copy_kernal_consumer_sm_gate,
                          VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                          "BPCA_BP_DMEM"))
        return rv;

    // to clear the VEX memories before running a test
    vex_mem_clear(rx_vex, srp);

    if(out_rate < JESD_SYS_RATE_IQ_P5)
    {
        if((rv = vex_loader(rx_vex,
                                "vex_fw/sim_m64/copy_kernal.fw")))
            return rv;
        print("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/copy_kernal.fw", rx_vex);
    }
    else
    {
        /*if((rv = srp_vex_loader(g_vex_hdl,
                                rx_vex,
                                "vha_vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
            return rv;*/
        print("ERROR: load right vex fw", rx_vex);
    }
    
    
    for(lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        write_mem_18a( rec_vex_dmem_base_addr + vex_rx_offset_val[lc], 1, &vex_rx_val_kargs[lc], "Val_kargs");
    }
    print("HOST: Loaded host params to vex core %d\n", rx_vex);

    return rv;    
}


int test_start(uint32_t rx_vex)
{
    int rv = 0;

    // Make sure the order is preserved (Start Rx vex first and then Tx vex)
    vex_start(rx_vex, 0);
    print("HOST: Started vex core %d (Rx VEX)\n", rx_vex);

    //enable_sysref();

    print("HOST: End of the Test execution....!\n");
    
    return rv;
}

int main ()
{
    int rx_vex = 0;
    int in_rate = JESD_SYS_RATE_IQ_P25;
    int out_rate = JESD_SYS_RATE_IQ_P25;
    
    LOG_PRINT("INFO:logger begining !\n");

    init_test(rx_vex);
    register_configure(rx_vex);

    configure_receiver(rx_vex, in_rate, out_rate, 0);
    //configure_jesd_block();

    test_start(rx_vex);
    
    return 0;
}


