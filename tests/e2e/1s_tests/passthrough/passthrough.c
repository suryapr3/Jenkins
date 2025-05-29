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
 * @file    vex_jesd_dnrt.c
 * @brief   HOST Configuration code for sending the data from VEX to JESD and receving it back.
 * @details 1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
 and receving it back to VEX for all the Sample Rates
 2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 1. 32K samples (1K vectors) for given data rate will be streamed to JESD from
 configured VEX core.
 2. With JESD NSIP loop back enabled the data looped back at sample interface
 was expected to reach the other VEX core where comparison will be performed.
 4. VEX core on which comparison algo was running will update the comparison result for
 every vector comparison and once the total 1K vector comparison was done HOST will
 read the result.
 5. Host will be waiting on a memory location where VEX will update the number of vectors
 it was processed.
 6. The supported Sample rates are
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
#include "vha_common_definitions.h"

#include "srp_block_ids.h"
#include "cli.h"
#include "init.h"
#include "all_comps.h"
#include "common_functions.h"

#include "common_utils.h"
#include "defines.h"

#include<time.h> 

#include "vex_producer.map.h"
#include "vha2vex_p25iq.map.h"
#include "vha2vex_p5_8iq.map.h"
#include "vex2vha.map.h"
#include "copy_kernal.map.h"

#include "e2e_common_definitions.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
extern int configure_jesd(uint32_t testcase);

#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)

//#define printf LOG_PRINT

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

#define LOAD_IP_FROM_FILE
#define INPUT_FILE_PATH "./vha_matlab_wrappers/input_samples/upconversion/single_band_upconversion_p125.txt"

/* V2D config  check vijay */

#define V2D_NSIP_HBI_0_OFFSET (V2D0_AV2D_APB_0_NSIP_HBI_0_BASE - V2D0_PDPD_0_BASE)
#define V2D_NSIP_HBI_1_OFFSET (V2D0_AV2D_APB_0_NSIP_HBI_1_BASE - V2D0_PDPD_0_BASE)
#define V2D_CSR_OFFSET (V2D0_AV2D_APB_0_CSR_BASE - V2D0_PDPD_0_BASE)
#define V2D_BFN_OFFSET (V2D0_BFN_CSR_BASE - V2D0_PDPD_0_BASE)
#define PDPD_BASE_ADDR(v2d_num, apb_num) ((V2D0_PDPD_0_BASE + ((v2d_num) * (V2D1_PDPD_0_BASE - V2D0_PDPD_0_BASE))) + APB_OFFSET_GEN(apb_num))
#define VE32_CELL_BASE(vex_num) (VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE)))

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
int g_num_blocks_v2d_buffer = 3;

/* The value should be number of blocks required for 32K samples i.e 1024 vectors defined as per order in sys_rate_t enum */
const uint32_t g_max_blocks_vha[] = {1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000};

const char *g_input_file[] = {
    "./vha_matlab_wrappers/input_samples/upconversion/single_band_upconversion_p125.txt",
    "./vha_matlab_wrappers/input_samples/upconversion/single_band_upconversion_p25.txt",
    "./vha_matlab_wrappers/input_samples/upconversion/single_band_upconversion_p5.txt",
    "./vha_matlab_wrappers/input_samples/upconversion/single_band_upconversion_1.txt",
};

const char *g_output_ref_file[] = {
    // For the inputs at p125 Gsps
    "./vha_matlab_wrappers/output_samples/upconversion/p125/single_band_upconversion_p125.txt",        // without any upconversion
    "./vha_matlab_wrappers/output_samples/upconversion/p125/single_band_upconversion_p25.txt",         // W1 only
    "./vha_matlab_wrappers/output_samples/upconversion/p125/single_band_upconversion_p5.txt",          // W1+W2
    "./vha_matlab_wrappers/output_samples/upconversion/p125/single_band_upconversion_1.txt",           // W1+W2+W3
    "./vha_matlab_wrappers/output_samples/upconversion/p125/single_band_upconversion_2.txt",           // W1+W2+W3+W4

    // For the inputs at p25 Gsps
    "./vha_matlab_wrappers/output_samples/upconversion/p25/single_band_upconversion_p25.txt",          // without any upconversion
    "./vha_matlab_wrappers/output_samples/upconversion/p25/single_band_upconversion_p5.txt",           // W1 only
    "./vha_matlab_wrappers/output_samples/upconversion/p25/single_band_upconversion_1.txt",            // W1+W2
    "./vha_matlab_wrappers/output_samples/upconversion/p25/single_band_upconversion_2.txt",            // W1+W2+W3
    "./vha_matlab_wrappers/output_samples/upconversion/p25/single_band_upconversion_4.txt",            // W1+W2+W3+W4

    // For the inputs at p5 Gsps
    "./vha_matlab_wrappers/output_samples/upconversion/p5/single_band_upconversion_p5.txt",           // without any upconversion
    "./vha_matlab_wrappers/output_samples/upconversion/p5/single_band_upconversion_1.txt",            // W1 only
    "./vha_matlab_wrappers/output_samples/upconversion/p5/single_band_upconversion_2.txt",            // W1+W2
    "./vha_matlab_wrappers/output_samples/upconversion/p5/single_band_upconversion_4.txt",            // W1+W2+W3
    NULL,

    // For the inputs at 1 Gsps
    "./vha_matlab_wrappers/output_samples/upconversion/1g/single_band_upconversion_1.txt",            // without any upconversion
    "./vha_matlab_wrappers/output_samples/upconversion/1g/single_band_upconversion_2.txt",            // W1 only
    "./vha_matlab_wrappers/output_samples/upconversion/1g/single_band_upconversion_4.txt",            // W1+W2
    NULL,
    NULL
};


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

// External variables
extern char g_compile_time[];

extern int g_vha_ve_list[][NUM_VE_PER_VHA];
extern const uint32_t vha_host_id[8][2];
//extern const char *sys_rate_str[2][6];
extern const char *vha_dl_clk[2];
extern const char *duc_mode_str[2];
//extern const int g_vectors_per_block[2][6];
extern const uint32_t g_max_blocks;
//extern g_md_control_tbl[2][6];

static register_config_tbl_t g_register_sequence_config_tbl[] = {
#include "register_sequence.h"
};


#define vha_ant_dl_cfg_pos    ( 3 )                                   // register at this offset will get overwritten with in_rate and out_rates


/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/

/*
 * function  : test_show_regs()
 * @breif    : this function is a wrapper to dump out vex and vha registers
 *
 * */
static int test_show_regs(
//    uint32_t tx_vex,
//    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num)
{
    vha_show_regs(vha_num, ant_num);                       // VHA registers
    //vex_cio2strm_show_regs(tx_vex);                        // CIO2STRM registers of tx_vex
    //vex_strm2cio_show_regs(rx_vex);                        // STRM2CIO registers of rx_vex
}

/*
 * function  : test_check_status()
 * @breif    : this function dumps out various VHA and VEX status registers
 *
 * */
static int test_check_status(
//    uint32_t tx_vex,
//    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num,
    int postrun)
{
    int rv, e_code;

    e_code = SUCCESS;
    rv = SUCCESS;
    if(rv = vha_check_status(vha_num, ant_num))
        e_code = 1;                                        // FAILURE code for VHA status wrong
    /*if(rv = vex_cio2strm_check_status(tx_vex))
        e_code |= 2;                                       // FAILURE code for CIO2STRM status wrong
    if(rv = vex_strm2cio_check_status(rx_vex))
        e_code |= 4;*/                                     // FAILURE code for STRM2CIO status wrong

    test_show_regs(vha_num, ant_num);

    return e_code;
}


static int init_test(uint32_t vha_num, uint32_t jesd_test_id)
{
    int rv = 0;

    configure_jesd(jesd_test_id);
 
    vha_init(vha_num);

    print("HOST: all reset done\n");

    sleep(2);
    
    return rv;
}

#if 0
int configure_producer(int vexIdx, vha_sys_rate_t in_rate, uint32_t dl_clk)
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int dmem_offset = 0x4000;
    int host_flag = 1;
        
    //unsigned stream_id[8]= {0, 1, 2, 3, 4, 5, 6, 7};
    unsigned stream_id[8]= {8, 9, 10, 11, 12, 13, 14, 15}; // Accepctble range 0 to 15
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
/*            0x24       0x4        g_vex_exit
            0x20       0x4        g_host_indicator
            0x44       0x4        g_num_streams
            0x0        0x20       g_dest_buffer_base
            0x30       0x4        g_timeout_cycles
            0x28       0x4        g_timer_debug
            0x40       0x4        g_num_vec_per_stream
            0x2C       0x4        g_debug
            */
#if 1
    unsigned vex_args_tbl[]={    0,            0x10000000,
                                0x20000000,    0x30000000,
                                0x40000000,    0x50000000,
                                0x60000000, 0x70000000,
                                1,            511,
                                g_vectors_per_block[dl_clk][in_rate],            g_vectors_per_block[dl_clk][in_rate],
                                1}; /* Vijay, change it to run forever */

                                                                
    unsigned vex_args_addr[] = {HIVE_ADDR_vex_producer_g_dest_buffer_addr, HIVE_ADDR_vex_producer_g_dest_buffer_addr + (1*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (2*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (3*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (4*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (5*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (6*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (7*4),
        HIVE_ADDR_vex_producer_g_num_streams, HIVE_ADDR_vex_producer_g_timeout_cycles,
        HIVE_ADDR_vex_producer_g_num_vec_per_stream, HIVE_ADDR_vex_producer_g_num_vec_to_transfer,
        HIVE_ADDR_vex_producer_g_run_forever};
    
    if ((rv = srp_vex_loader(g_vex_hdl, vexIdx, "producer/sim_m64/vex_producer.fw")))
        return rv;
#else
    unsigned vex_args_tbl[]={0, NUMBER_OF_VECTORS_INPUT, 0, 0}; /* Vijay, change it to run forever */
                                                  
    unsigned vex_args_addr[] = {HIVE_ADDR_vex2vha_g_scalar_val,
        HIVE_ADDR_vex2vha_g_num_vecs_in,
        HIVE_ADDR_vex2vha_g_dest_buffer_base,
        HIVE_ADDR_vex2vha_g_num_blocks};
    
    vex_args_tbl[3] = g_max_blocks;
    vex_args_tbl[1] = g_vectors_per_block[dl_clk][in_rate];
    
    if ((rv = srp_vex_loader(g_vex_hdl, vexIdx, "vha_vex_fw/sim_m64/vex2vha.fw")))
        return rv;
#endif
    print("vex%d being configured as producer core",vexIdx);

    for (lc = 0; lc < ARRAY_SIZE(vex_args_tbl); lc++)
    {
        if ((rv = srp_dev_block_write32(srp,
                        SRP_BLOCK_VEX_CORE,
                        vexIdx,
                        dmem_offset + vex_args_addr[lc],
                        &vex_args_tbl[lc],
                        1,
                        flags)))
            return rv;
    }


#ifdef LOAD_IP_FROM_FILE
    FILE *fptr;
    
    fptr = fopen(g_input_file[in_rate], "r");
    if(NULL == fptr)
    {
        LOG_PRINT("ERROR: Not able to open the input file\n");
        return -1;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_inp,
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_PRINT("ERROR: Insufficient input samples\n");
        return -1;
    }
    fclose(fptr);

    if((rv = srp_vex_memid_store(g_vex_hdl,
                                 vexIdx,
                                 SRP_VEX_VMEM,
                                 HIVE_ADDR_vex_producer_vbuffer,/*local_addr*/
                                 val_inp[0],
                                 (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;
    print("HOST: Initialized pattern into the vector memory of vex core %d\n", vexIdx);
#else
    /* Input Vector Generation VEX_1*/
    for (lc = 0; lc < 8 ; lc++)
    {
        for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
        {
            for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
            {
                val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
                val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
                val_inp[i][j] = val_inp[i][j] | (stream_id[lc] << 28 | stream_id[lc] << 12);
            }
        }

        if ((rv = srp_vex_memid_store(g_vex_hdl,
                        vexIdx,
                        SRP_VEX_VMEM,
                        lc*0x2000,/*local_addr*/
                        val_inp[0],
                        (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
            return rv;
    }
#endif //LOAD_IP_FROM_FILE

    //srp_vex_start(g_vex_hdl, vexIdx, 0); // vex_0 start

    print("producer core started\n");

    //system("srpRamTest -s 64KB -W 0x63.0.0x30000 0"); // Vijay: Just for testing, remove it
    return rv;
}   // main ends

int configure_receiver(uint32_t rx_vex, vha_sys_rate_t in_rate, vha_sys_rate_t out_rate, uint32_t dl_clk)
{
    int cnt, lc, i, j, k;
    int rv = 0, flags = 0;
    int dmem_offset = 0x4000;
    unsigned val_out[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    FILE *fptr;
    
    int vex_rx_offset_val[] = {HIVE_ADDR_vha2vex_p5_8iq_g_scalar_val,
                               HIVE_ADDR_vha2vex_p5_8iq_g_num_vecs_in,
                               HIVE_ADDR_vha2vex_p5_8iq_g_num_blocks,
                               HIVE_ADDR_vha2vex_p5_8iq_g_tbs_in_blk,
                               HIVE_ADDR_vha2vex_p5_8iq_g_dest_ptr_address};
    unsigned vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64, 0};
    
    vex_rx_val_kargs[2] = g_max_blocks;
    vex_rx_val_kargs[1] = g_vectors_per_block[dl_clk][out_rate];
    vex_rx_val_kargs[3] = VEX_MAX_BUF_SIZE / g_vectors_per_block[dl_clk][out_rate];
    
    if (rx_vex == 8)
    {
        vex_rx_val_kargs[4] = 0x10000;
    }
    
    vex_mem_clear(rx_vex, srp);
    

    if(out_rate < VHA_SYS_RATE_IQ_P5)
    {
        if((rv = srp_vex_loader(g_vex_hdl,
                                rx_vex,
                                "vha_vex_fw/sim_m64/vha2vex_p25iq.fw")))
            return rv;
        print("HOST: Loaded %s to vex core %d\n", "vha_vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex);
    }
    else
    {
        if((rv = srp_vex_loader(g_vex_hdl,
                                rx_vex,
                                "vha_vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
            return rv;
        print("HOST: Loaded %s to vex core %d\n", "vha_vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex);
    }
    
    
    for(lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if((rv = srp_dev_block_write32(srp,
                                        SRP_BLOCK_VEX_CORE,
                                        rx_vex,
                                        dmem_offset + vex_rx_offset_val[lc],
                                        &vex_rx_val_kargs[lc],
                                        1,
                                        flags)))
            return rv;
    }
    print("HOST: Loaded host params to vex core %d\n", rx_vex);
    
    fptr = fopen(g_output_ref_file[(in_rate*4)+out_rate], "r");
    if(NULL == fptr)
    {
        LOG_PRINT("ERROR: Not able to open the output file\n");
        return -1;
    }
    if(vector_read_hex_u32(fptr,
                           (int*) val_out,
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_PRINT("ERROR: Insufficient output samples\n");
        return -1;
    }
    fclose(fptr);
   if((rv = srp_vex_memid_store(g_vex_hdl,
                                rx_vex,
                                SRP_VEX_VMEM,
                                HIVE_ADDR_vha2vex_p5_8iq_vbuffer,/*local_addr*/
                                val_out[0],
                                (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;
    print("HOST: Initialized pattern into the vector memory of vex core %d\n", rx_vex);
    
    // SDF init
    if(rv = write_reg_18a(VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_ADR(VEX_BASE(rx_vex)),
                          HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate,
                          VE32_CELL_MEM_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                          "BPCA_BP_DMEM"))
        return rv;

    return rv;    

}

#endif

static int configure_vha(uint32_t vha_num, uint32_t ant_num, vha_sys_rate_t in_rate, vha_sys_rate_t out_rate, filter_mode_t mode, uint32_t dl_clk)
{
    int rv = 0;
    
    // print registers before starting any configurations
    print("HOST: Checking registers before doing any register configurations\n");
    if(rv = test_check_status(vha_num, ant_num, 0))
    {
        print("ERROR: One or many register statuses are NOT clean. Exiting test..!\n");
        return -1;
    }
    print("HOST: test configurations\n");
    if(rv = test_configure_vha_duc_ddc(vha_num, ant_num, in_rate, out_rate, mode, dl_clk))
    {
        print("ERROR: test_configure\n");
        return rv;
    }

    // print registers after the configurations are done
    print("HOST: Finished register configurations, now checking registers\n");
    if(rv = test_check_status(vha_num, ant_num, 0))
    {
        print("ERROR: One or many register statuses are NOT clean. Exiting test..!\n");
        return -1;
    }
    
    return rv;
}


int test_start(uint32_t vex_num)
{
    int rv = 0;

    if(0 == rv)
    {
        print("Test:------ PASSED ------!\n");
    } else
    {
        print("Test:------ FAILED -----!\n");
    }



    print("HOST: End of the Test execution....!\n");
	
	return rv;
}

static void configure_registers()
{
    int i;
    
    for(i = 0; i < ARRAY_SIZE(g_register_sequence_config_tbl); i++)
    {
        write_reg_18a(g_register_sequence_config_tbl[i].addr,
                              g_register_sequence_config_tbl[i].value,
                              0xFFFFFFFF,
                              g_register_sequence_config_tbl[i].name);
    }

}


static int configure_copy_kernal(uint32_t rx_vex, jesd_sys_rate_t in_rate, jesd_sys_rate_t out_rate, uint32_t dl_clk)
{
    int cnt, lc, i, j, k;
    int rv = 0, flags = 0;
    int dmem_offset = 0x4000;
    unsigned val_out[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    FILE *fptr;
    
    int vex_rx_offset_val[] = {HIVE_ADDR_copy_kernal_g_num_vecs_in,
                               HIVE_ADDR_copy_kernal_g_num_blocks,
                               HIVE_ADDR_copy_kernal_g_tbs_in_blk,
                               HIVE_ADDR_copy_kernal_g_dest_ptr_address,
                               HIVE_ADDR_copy_kernal_consumer_sm_gate + (CONSUMER_SM_BUF_ID *4)};
    unsigned vex_rx_val_kargs[] = {NUMBER_OF_VECTORS_INPUT, 1, 64, 0, 0};
    
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
    
    vex_start(rx_vex, 0);

    return rv;    
}

int main ()
{
	vha_node_config_t vha_node_config = {
	#include "vha_0_port_0_node_config.h"
	};
	
	v2d_node_config_t v2d_node_config = {
	#include "v2d_0_port_0_node_config.h"
	};
	
	uint32_t dl_clk = 0;
	uint32_t jesd_test_id = 43;

	init_test(vha_node_config.vha_num, jesd_test_id);
	print("hello\n");
	
	configure_registers();
	configure_vha(vha_node_config.vha_num, vha_node_config.ant_num, vha_node_config.in_rate, vha_node_config.out_rate, vha_node_config.mode, dl_clk);
	
	configure_v2d_flow1(v2d_node_config.v2d_num, v2d_node_config.apb_num, v2d_node_config.drf_clock, v2d_node_config.in_rate);

	
	configure_copy_kernal(0, vha_node_config.in_rate, vha_node_config.in_rate, 0);

	print("vijay starting test");
	//test_start(0);
	
	//srp_vex_start(g_vex_hdl, tx_vex, 0); // vex_0 start
	
	return 0;
}


