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
 * @file    vex_jesd_connectivity.c
 * @brief   HOST Configuration code for sending the data from VEX to JESD and receving it back.
 * @details 1. Configuration of VEX, JESD and Common Module for sending data from VEX to JESD
 and receving it back to VEX for all the Sample Rates
 2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 1. 256 samples (8 vectors) for given data rate will be streamed to JESD from
 configured VEX core.
 2. With JESD NSIP loop back enabled the data looped back at sample interface
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


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
register_config_tbl_t g_vex_noc_config[] = {
    {0x94, 0, 0, "NOC_CLK_GATE"},
    {0x98, 0, 0, "NOC_SOFT_RESET"}
};

void *g_vex_hdl;
srp_vex_config_t g_vex_params;
srp_vex_t g_srp_vex_hdl;

static int g_jesd_nsip_base_addr[4] = {DLNK_JESDABC0_NSIP_HBI_CSR_BASE, DLNK_JESDABC1_NSIP_HBI_CSR_BASE, DLNK_JESDABC2_NSIP_HBI_CSR_BASE, DLNK_JESDABC3_NSIP_HBI_CSR_BASE};
    
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/



/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/

static void fpga_clk_and_sysref_period()
{
    system("frioPciWrite -F s5a1 -P 0x20000 0x10");
    system("frioPciWrite -F s5b1 -P 0x20000 0x10");
    system("frioPciWrite -F s5a1 -P 0x20004 0x1900190");
    system("frioPciWrite -F s5b1 -P 0x20004 0x1900190");

    //enable jesd_ip path or serial or parallel lpbk
    system("frioPciWrite -F s5a3 -P 0x20000 0x02"); //IP
    //system("frioPciWrite -F s5a3 -P 0x20000 0x0"); //Serial
    //system("frioPciWrite -F s5a3 -P 0x20000 0x01"); //Parallel
}

static void fpga_provided_sysref()
{
   //enable sysref
    system("frioPciWrite -F s5a1 -P 0x20000 0x90");
    system("frioPciWrite -F s5b1 -P 0x20000 0x90");
}

static void delay(unsigned int milliseconds){

    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      tx_vex, rx_vex, jesd_num
 * @return          status
 */

static int test_configure(uint32_t vexId, uint32_t jesd_num)
{
    int i = 0, rv;
    
    static int jesd_host_ids[4] = {0x40, 0x41, 0x42, 0x43};
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_num];
    int cio2strm_base = VE32_CELL_BASE(vexId) + VE32_TILE_CIO2STRM_OFFSET;
    int strm2cio_base = VE32_CELL_BASE(vexId) + VE32_TILE_STRM2CIO_OFFSET;
    
    register_config_tbl_t ve_cio2strm_config_tbl[] = {
        {CIO2STRM_MEM_CIO2STRM_INT_ENABLE_ADR(cio2strm_base), 0x3F, 0xFFFFFFFF, "CIO2STRM_INT_ENABLE"},
        {CIO2STRM_MEM_CIO2STRM_FIFO_STATUS_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "CIO2STRM_FIFO_STATUS_CTL"},
        {CIO2STRM_MEM_CIO2STRM_WORD_CNT_CTL_ADR(cio2strm_base), 0x1, 0xFFFFFFFF, "CIO2STRM_WORD_CNT_CTL"},
        {CIO2STRM_MEM_CIO2STRM_RANGE_EN_ADR(cio2strm_base), 0x00000001, 0xFFFFFFFF, "CIO2STRM_RANGE_EN"},
        {CIO2STRM_MEM_CIO2STRM_MEM_ADDR_LOW0_ADR(cio2strm_base), 0x0, 0xFFFFFFFF, "CIO2STRM_MEM_ADDR_LOW0"},
        {CIO2STRM_MEM_CIO2STRM_MEM_ADDR_HIGH0_ADR(cio2strm_base), 0x3ffffff, 0xFFFFFFFF, "CIO2STRM_MEM_ADDR_HIGH0"},
        {CIO2STRM_MEM_CIO2STRM_MEM_OFFSET0_ADR(cio2strm_base), 0x00000000, 0xFFFFFFFF, "CIO2STRM_MEM_OFFSET0"},
        {CIO2STRM_MEM_CIO2STRM_STRM_DEST0_ADR(cio2strm_base), jesd_host_ids[jesd_num], 0xFFFFFFFF, "CIO2STRM_STRM_DEST0"}
    };

    register_config_tbl_t ve_strm2cio_config_tbl[] = {
        {STRM2CIO_MEM_STRM2CIO_INT_ENABLE_ADR(strm2cio_base), 0xF, 0xFFFFFFFF, "STRM2CIO_INT_ENABLE"},
        {STRM2CIO_MEM_STRM2CIO_FIFO_STATUS_CTL_ADR(strm2cio_base), 0x1, 0xFFFFFFFF, "STRM2CIO_MEM_FIFO_STATUS_CTL"},
        {STRM2CIO_MEM_STRM2CIO_WORD_CNT_CTL_ADR(strm2cio_base), 0x1, 0xFFFFFFFF, "STRM2CIO_MEM_WORD_CNT_CTL"},
    };

    register_config_tbl_t jesd_port_nsip_hbi_config_tbl[] = {
        {NSIP_HBI_INTR_INT_HIGH_EN_ADR(jesd_nsip_hbi_base), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_HIGH_EN"},
        {NSIP_HBI_INTR_INT_LOW_EN_ADR(jesd_nsip_hbi_base), 0xFFFFF, 0xFFFFFFFF, "CM_0_INT_LOW_EN"},
        {NSIP_HBI_H2B_FF_H2B_FIFO_CONTROL_ADR(jesd_nsip_hbi_base), 0x184, 0xFFFFFFFF, "H2B_FIFO_CONTROL"},
        {NSIP_HBI_H2B_CREDIT_READY_CS_ADR(jesd_nsip_hbi_base), 0x4, 0xFFFFFFFF, "H2B_CREDIT_READY_CS"},
        {NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(jesd_nsip_hbi_base), 0x1, 0xFFFFFFFF, "H2B_BUF_SZ_HW_TBL0"},
        {NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base), 0x10080, 0xFFFFFFFF, "H2B_TK_ADDR_LKUP_TBL0"},
        {NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base), 0x10000, 0xFFFFFFFF, "H2B_MD_ADDR_LKUP_TBL0"},
        {NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(jesd_nsip_hbi_base), 0x80000000 | VMEM_OP_BUFF_OFFSET, 0xFFFFFFFF, "H2B_ADDR_LKUP_TBL0"},
        {NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_TK_ROUTE_LKUP_TBL0"},
        {NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_MD_ROUTE_LKUP_TBL0"},
        {NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(jesd_nsip_hbi_base), vexId, 0xFFFFFFFF, "H2B_ROUTE_LKUP_TBL0"},
        {NSIP_HBI_H2B_MD_CONTROL_TBL0_ADR(jesd_nsip_hbi_base), 7, 0xFFFFFFFF, "H2B_MD_CONTROL_TBL0"},
        {NSIP_HBI_B2H_FF_B2H_FIFO_CONTROL_ADR(jesd_nsip_hbi_base), 0x184, 0xFFFFFFFF, "B2H_FIFO_CONTROL"},
        {NSIP_HBI_B2H_CSR_B2H_CREDIT_CS_ADR(jesd_nsip_hbi_base), 0x8, 0xFFFFFFFF, "B2H_CREDIT_CS"},
        {NSIP_HBI_B2H_CSR_B2H_ADDR_TBL0_ADR(jesd_nsip_hbi_base), 0x80000000, 0xFFFFFFFF, "B2H_ADDR_MAP_TBL0"},
        {NSIP_HBI_B2H_CSR_B2H_ADDR_MASK_TBL0_ADR(jesd_nsip_hbi_base), 0x1FFFF, 0xFFFFFFFF, "B2H_ADDR_MASK_TBL0"},
    };
    
    
    int jesd_cmn_csr_base_addr[4] = {DLNK_JESDABC0_CRUX_CLK_CSR_BASE,  DLNK_JESDABC1_CRUX_CLK_CSR_BASE,  DLNK_JESDABC2_CRUX_CLK_CSR_BASE,  DLNK_JESDABC3_CRUX_CLK_CSR_BASE};

    write_reg_18a(JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL_ADR(jesd_cmn_csr_base_addr[jesd_num]), 1, 0xFFFFFFFF, "JESDABC_CRUX_CLK_CSR_MEM_LPBK_CTL");
    
    printf("INFO: JESD%d configuration completed\n", jesd_num);

    for(i = 0; i < ARRAY_SIZE(jesd_port_nsip_hbi_config_tbl); i++)
    {
        if(rv = write_reg_18a(jesd_port_nsip_hbi_config_tbl[i].addr,
                              jesd_port_nsip_hbi_config_tbl[i].value,
                              0xFFFFFFFF,
                              jesd_port_nsip_hbi_config_tbl[i].name))
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


int init_test(uint32_t vexId, uint32_t jesdId)
{
    int rv = 0;

    fpga_clk_and_sysref_period();
    delay(100);

    init(); // Initialize the srp
    delay(1000);
    jesd_reset(1 << jesdId,0);
    delay(1000);
    fpga_provided_sysref();
    delay(100);
    
    memset(&g_vex_params, 0, sizeof(g_vex_params));
    memset(&g_srp_vex_hdl, 0, sizeof(g_srp_vex_hdl));
    
    g_vex_hdl = &g_srp_vex_hdl;

    if ((rv = srp_vex_config(srp, &g_vex_hdl, &g_vex_params)))
        return rv;

    // Let's take the modules out of RESET
    print("HOST: Doing sub-system RESET cycle\n");

    subsys_reset_cycle();
    vex_reset_cycle();
    crux_reset_cycle();
    sleep(2);

    print("HOST: all reset done\n");

    // to clear the VEX memories before running a test
    vex_mem_clear(vexId, srp);
    
    return rv;
}

int configure_producer(int vexIdx, uint32_t jesd_num)
{
    int rv = 0;
    int flags = 0;
    int lc, i, j;
    int dmem_offset = 0x4000;
    int host_flag = 1;
    int jesd_nsip_hbi_base = g_jesd_nsip_base_addr[jesd_num];
    int strm2cio_base = VE32_CELL_BASE(vexIdx) + VE32_TILE_STRM2CIO_OFFSET;
    int strm2cio_word_count = 0;
    int error_count = 0, cnt = 0;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0;

    unsigned stream_id[8]= {8, 9, 10, 11, 12, 13, 14, 15}; // Accepctble range 0 to 15
    unsigned val_inp[NUM_TOTAL_VEC_PER_STREAM][NUM_OF_ELEMENTS_PER_VEC] = {0};
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
                                0}; /* Vijay, change it to run forever */

                                                                
    unsigned vex_args_addr[] = {HIVE_ADDR_vex_producer_g_dest_buffer_addr, HIVE_ADDR_vex_producer_g_dest_buffer_addr + (1*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (2*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (3*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (4*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (5*4),
        HIVE_ADDR_vex_producer_g_dest_buffer_addr + (6*4), HIVE_ADDR_vex_producer_g_dest_buffer_addr + (7*4),
        HIVE_ADDR_vex_producer_g_num_streams, HIVE_ADDR_vex_producer_g_timeout_cycles,
        HIVE_ADDR_vex_producer_g_num_vec_per_stream, HIVE_ADDR_vex_producer_g_num_vec_to_transfer,
        HIVE_ADDR_vex_producer_g_run_forever};
    
    if ((rv = srp_vex_loader(g_vex_hdl, vexIdx, "producer/sim_m64/vex_producer.fw")))
        return rv;

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

    /* Input Vector Generation VEX_1*/

    for (i = 0; i < NUM_TOTAL_VEC_PER_STREAM; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            val_inp[i][j] = (((((i * 2 * NUM_OF_ELEMENTS_PER_VEC) + (j * 2)) + 1) << 16) |((i * 2* NUM_OF_ELEMENTS_PER_VEC) + (j *2)));
            val_inp[i][j] = val_inp[i][j] & 0x0FFF0FFF;
            val_inp[i][j] = val_inp[i][j] | (stream_id[vexIdx%8] << 28 | stream_id[vexIdx%8] << 12);
        }
    }


    if ((rv = srp_vex_memid_store(g_vex_hdl,
                    vexIdx,
                    SRP_VEX_VMEM,
                    0,/*local_addr*/
                    val_inp[0],
                    (NUM_TOTAL_VEC_PER_STREAM * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
        return rv;

    // Try reading some input and output samples so programmed from the VEX vector memories
    print_registers(VEX_BASE(vexIdx) + VEX_VMEM_OFFSET, 16, "Tx VEX Input samples");

    srp_vex_start(g_vex_hdl, vexIdx, 0); // vijay

    cnt = 0;
    while(1)
    {
        b2h_flit_cnt += read_reg_18a(NSIP_HBI_B2H_CSR_B2H_FLIT_COUNT_ADR(jesd_nsip_hbi_base),
                                     "B2H_FLIT_COUNT");
        if(b2h_flit_cnt >= (NUMBER_OF_VECTORS_INPUT * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but b2h_flit_cnt is NOT reaching %d\n", cnt, (1 * NUMBER_OF_VECTORS_INPUT * 2));
            break;
        }
    }
    printf("HOST: B2H_FLIT_CNT = %d\n", b2h_flit_cnt);

    printf("HOST: Waiting for the JESD H2B flit count to be atleast %d\n", (1 * NUMBER_OF_VECTORS_INPUT * 2));
    cnt = 0;
    while(1)
    {
        h2b_flit_cnt += read_reg_18a(NSIP_HBI_H2B_FLIT_COUNT_ADR(jesd_nsip_hbi_base),
                                     "H2B_FLIT_COUNT");
        if(h2b_flit_cnt >= (1 * NUMBER_OF_VECTORS_INPUT * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but h2b_flit_cnt is NOT reaching %d\n", cnt, (1 * NUMBER_OF_VECTORS_INPUT * 2));
            break;
        }
    }
    printf("HOST: H2B_FLIT_CNT = %d\n", h2b_flit_cnt);

    printf("HOST: Waiting for the Rx VEX to receive and compare %d vectors\n", (1 * NUMBER_OF_VECTORS_INPUT));
    cnt = 0;
    while(1)
    {
        strm2cio_word_count = read_reg_18a(STRM2CIO_MEM_STRM2CIO_WORD_CNT_ADR(strm2cio_base),
                                     "S2C_WORD_CNT");
        if(strm2cio_word_count >= (1 * NUMBER_OF_VECTORS_INPUT * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but S2C_WORD_CNT is NOT reaching %d\n", cnt, (1 * NUMBER_OF_VECTORS_INPUT * 2));
            break;
        }
    }
    
    if ((rv = srp_vex_memid_load(g_vex_hdl,
                vexIdx,
                SRP_VEX_VMEM,
                VMEM_OP_BUFF_OFFSET,
                val_op[0],
                (NUMBER_OF_VECTORS_INPUT * NUM_OF_ELEMENTS_PER_VEC * sizeof(int)))))
    return rv;
    
    for (i = 0; i < NUMBER_OF_VECTORS_INPUT; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            if (val_op[i][j] != val_inp[i][j])
            {
                printf("ERROR: data mismatch, vec %d, index %d expected[0x%8x], received[0x%8x]\n", i, j, val_inp[i][j], val_op[i][j]);
                error_count++;
            }
        }
    }
    
    char *test_status = "SUCCESS";
    if(error_count) test_status = "FAILURE";

    print("HOST: Comparison result :  %s\n      Processed vectors : 0x%x\n", test_status, NUMBER_OF_VECTORS_INPUT);

    if(error_count)
    {
        print("ERROR: input and output samples didn't match\n");
        rv = -1;
    }

    if(0 == rv)
    {
        print("Test:------ PASSED ------!\n");
    } else
    {
        print("Test:------ FAILED -----!\n");
    }

    print("HOST: End of the Test execution....!\n");
    return rv;
}   // main ends


int main (int vexId, int jesdId)
{
    print("testing connectivity between vex%d & jesd_m%d \n",vexId, jesdId);

    init_test(vexId, jesdId);


    test_configure(vexId, jesdId);
    configure_producer(vexId, jesdId);
    
    return 0;
}
