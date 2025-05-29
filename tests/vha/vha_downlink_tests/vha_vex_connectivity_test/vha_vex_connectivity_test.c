/**********************************************************************************************
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
/*
 * @file    vha_vex_connectivity_test.c
 * @brief   HOST Configuration code for sending the data from VEX to VHA and receving it back.
 * @details 1. Configuration of VEX, VHA and Common Module for sending data from VEX to VHA
               and receving it back to VEX for all the Sample Rates
            2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 *          1. A certain number of IQ samples will be streamed from one VEX core to the VHA single
 *             band DL path.
 *          2. DUC filters are enabled as per the input and output rates passed down.
 *          3. VHA processed samples will be streamed back to another VEX core for data comparison.
            4. HOST will be waiting on a memory location where VEX will update the number of vectors
               it processed.
 */

#include "vha_common_definitions.h"
#include "vex2vha.map.h"
#include "vha2vex_p25iq.map.h"
#include "vha2vex_p5_8iq.map.h"

// Dumping registers are disabled by default.
//  Enable it with a compile time argument REGISTER_DUMP if required.
#if defined(REGISTER_DUMP)
#define CHECK_STATUS                   ( 1 )
#endif

// Pointers to the input IQ samples
const char* input_path_prefix = "./vha_matlab_wrappers/input_samples/upconversion/";
const char* g_input_file[2][4] = {
    {
    "single_band_upconversion_p125.txt",
    "single_band_upconversion_p25.txt",
    "single_band_upconversion_p5.txt",
    "single_band_upconversion_1.txt"
    },
    {
    "single_band_upconversion_p187.txt",
    "single_band_upconversion_p375.txt",
    "single_band_upconversion_p75.txt",
    "single_band_upconversion_1p5.txt"
    }
   };

// Pointers to the Matlab output reference IQ samples
const char* output_path_prefix = "./vha_matlab_wrappers/output_samples/upconversion/";
const char* g_output_ref_file[2][20] = {
    {
    // For the inputs at p125 Gsps
    "p125/single_band_upconversion_p125.txt",              // without any upconversion
    "p125/single_band_upconversion_p25.txt",               // W1 only
    "p125/single_band_upconversion_p5.txt",                // W1+W2
    "p125/single_band_upconversion_1.txt",                 // W1+W2+W3
    "p125/single_band_upconversion_2.txt",                 // W1+W2+W3+W4

    // For the inputs at p25 Gsps
    "p25/single_band_upconversion_p25.txt",                // without any upconversion
    "p25/single_band_upconversion_p5.txt",                 // W1 only
    "p25/single_band_upconversion_1.txt",                  // W1+W2
    "p25/single_band_upconversion_2.txt",                  // W1+W2+W3
    "p25/single_band_upconversion_4.txt",                  // W1+W2+W3+W4

    // For the inputs at p5 Gsps
    "p5/single_band_upconversion_p5.txt",                  // without any upconversion
    "p5/single_band_upconversion_1.txt",                   // W1 only
    "p5/single_band_upconversion_2.txt",                   // W1+W2
    "p5/single_band_upconversion_4.txt",                   // W1+W2+W3
    NULL,

    // For the inputs at 1 Gsps
    "1g/single_band_upconversion_1.txt",                   // without any upconversion
    "1g/single_band_upconversion_2.txt",                   // W1 only
    "1g/single_band_upconversion_4.txt",                   // W1+W2
    NULL,
    NULL
    },
    {
    // For the inputs at p187 Gsps
    "p187/single_band_upconversion_p187.txt",              // without any upconversion
    "p187/single_band_upconversion_p375.txt",              // W1 only
    "p187/single_band_upconversion_p75.txt",               // W1+W2
    "p187/single_band_upconversion_1p5.txt",               // W1+W2+W3
    "p187/single_band_upconversion_3.txt",                 // W1+W2+W3+W4

    // For the inputs at p375 Gsps
    "p375/single_band_upconversion_p375.txt",              // without any upconversion
    "p375/single_band_upconversion_p75.txt",               // W1 only
    "p375/single_band_upconversion_1p5.txt",               // W1+W2
    "p375/single_band_upconversion_3.txt",                 // W1+W2+W3
    "p375/single_band_upconversion_6.txt",                 // W1+W2+W3+W4

    // For the inputs at p75 Gsps
    "p75/single_band_upconversion_p75.txt",                // without any upconversion
    "p75/single_band_upconversion_1p5.txt",                // W1 only
    "p75/single_band_upconversion_3.txt",                  // W1+W2
    "p75/single_band_upconversion_6.txt",                  // W1+W2+W3
    NULL,

    // For the inputs at 1.5 Gsps
    "1p5/single_band_upconversion_1p5.txt",                // without any upconversion
    "1p5/single_band_upconversion_3.txt",                  // W1 only
    "1p5/single_band_upconversion_6.txt",                  // W1+W2
    NULL,
    NULL
    },
};

// Global declarations for the submodules getting used in this test
vha_dev_t vha_dev;
vha_dev_t* vha = &(vha_dev);

// External variables
extern char g_compile_time[];
extern int g_vha_ve_list[][NUM_VE_PER_VHA];
extern const uint32_t vha_host_id[8][2];
extern const char* sys_rate_str[2][6];
extern const char* vha_dl_clk[2];
extern const char* duc_mode_str[2];
extern const int g_vectors_per_block[2][6];
extern const uint32_t g_max_blocks;
extern const int g_md_control_tbl[2][6];

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int test_configure(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num,
    sys_rate_t in_rate,
    sys_rate_t out_rate,
    filter_mode_t mode,
    uint32_t dl_clk);

int test_configure_vha(
    uint32_t vha_num,
    uint32_t ant_num,
    uint32_t in_rate,
    uint32_t out_rate,
    filter_mode_t mode,
    uint32_t dl_clk,
    uint32_t dest_id);

int test_check_status(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num);

void test_show_regs(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num);

/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */

int main(
    int tx_vex,
    int rx_vex,
    int vha_num,
    int ant_num)
{
    FILE* fptr;
    char file_name[100];
    int rv = 0, val = 0, dev_id = 0, flags = 0;
    int tx_in_list, rx_in_list, vex_combo_good;
    int (*ve_list)[NUM_VE_PER_VHA];
    uint64_t base_addr;
    sys_rate_t in_rate, out_rate, min_in_rate, min_out_rate, max_in_rate, max_out_rate;
    filter_mode_t mode;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result = 0;
    volatile int host_vec_processed = 0, host_blocks_processed = 0;
    int cnt, lc, i, j, k;
    int vex_num, dl_clk;

    int offset_val[5] =
    {
        HIVE_ADDR_vex2vha_g_scalar_val,
        HIVE_ADDR_vex2vha_g_num_vecs_in,
        HIVE_ADDR_vex2vha_g_dest_buffer_base,
        HIVE_ADDR_vex2vha_g_num_blocks,
        HIVE_ADDR_vex2vha_g_vex_clk
    };
    unsigned val_kargs[5] = {0, NUMBER_OF_VECTORS_INPUT, 0, 0, 0};
    int vex_rx_offset_val[] =
    {
        HIVE_ADDR_vha2vex_p5_8iq_g_scalar_val,
        HIVE_ADDR_vha2vex_p5_8iq_g_num_vecs_in,
        HIVE_ADDR_vha2vex_p5_8iq_g_num_blocks,
        HIVE_ADDR_vha2vex_p5_8iq_g_tbs_in_blk
    };
    unsigned vex_rx_val_kargs[] = {0, NUMBER_OF_VECTORS_INPUT, 1, 64};
    unsigned val_inp[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned val_out[NUMBER_OF_VECTORS_INPUT][NUM_OF_ELEMENTS_PER_VEC] = {0};
    unsigned int add_val[1];

    init();                                                // Initialize the srp
    printf("\n");
    printf("Test: VHA-VEX connectivity test\n");
    printf("%s\n", g_compile_time);
    printf("BUILD_DIR: %s\n\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    mode = 0; in_rate = 0; out_rate = 0; dl_clk = 0;
    printf("INFO: Test arguments (VHA%d, ANT%d, VEX%d, VEX%d)\n", vha_num, ant_num, tx_vex, rx_vex);
    // Let's first do some sanity checks on the input arguments received
    if(vha_num > (NUM_VHA_INSTANCES - 1))
    {
        printf("ERROR: VHA number cannot be higher than 7, Exiting test..!\n");
        return FAILURE;
    }
    if((tx_vex > (NUM_VE_CORES - 1)) || (rx_vex > (NUM_VE_CORES - 1)))
    {
        printf("ERROR: VEX number cannot be higher than 39, Exiting test..!\n");
        return FAILURE;
    }

    if(is_vha_present(vha_num) < 0)                        // check is the VHA present on this build
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    vex_num = tx_vex;
    for(i = 0; i < 2; i++)
    {
        if(1 == i) vex_num = rx_vex;
        if(is_vex_present(vex_num) < 0)                    // check are the VEX's present on this build
        {
            printf("Exiting..!\n");
            return FAILURE;
        }
    }

    vex_combo_good = 0; tx_in_list = 0; rx_in_list = 0;
    ve_list = &g_vha_ve_list[(vha_num & 3)];               // VHA 0 & 4 share the same VEX cores, so is 1 & 5, 2 & 6 and 3 & 7

    for(i = 0; i < NUM_VE_PER_VHA; i++)
    {
        if(tx_vex == *((*ve_list) + i))
        {
            tx_in_list = 1;
        }
        if(rx_vex == *((*ve_list) + i))
        {
            rx_in_list = 1;
        }
        if(tx_in_list && rx_in_list)
        {
            break;
        }
    }

    if(tx_vex == rx_vex) printf("ERROR: Tx VEX and Rx VEX cannot be the same cores\n");
    if(!tx_in_list) printf("ERROR: Tx VEX (core %d) is NOT connected to VHA%d\n", tx_vex, vha_num);
    if(!rx_in_list) printf("ERROR: Rx VEX (core %d) is NOT connected to VHA%d\n", rx_vex, vha_num);
    if(!tx_in_list || !rx_in_list)
    {
        printf("Please find below the list of VEX cores connected to VHA%d\n   [ ", vha_num);
        for(i = 0; i < NUM_VE_PER_VHA; i++)
        {
            printf("%d ", *(*(ve_list) + i));
        }
        printf("]\n");
    }

    if((tx_in_list && rx_in_list) && (tx_vex != rx_vex))
    {
        vex_combo_good = 1;
    }
    if(!vex_combo_good)
    {
        printf("ERROR: Cannot run this test with these VHA-VEX combinations.\n");
        printf("Please make sure,\n"
               "    i. Tx VEX and Rx VEX are connected to VHA%d\n"
               "    ii. Tx VEX and Rx VEX are not the same cores\n", vha_num);
        printf("Exiting test..!\n");
        return FAILURE;
    }

    min_in_rate = SYS_RATE_IQ_P125;
    max_in_rate = SYS_RATE_IQ_1;
    min_out_rate = SYS_RATE_IQ_P125;
    max_out_rate = SYS_RATE_IQ_4;
    if(dl_clk)                                             // clk = 1.5GHz
    {
        min_in_rate = SYS_RATE_IQ_P187;
        max_in_rate = SYS_RATE_IQ_1P5;
        min_out_rate = SYS_RATE_IQ_P187;
        max_out_rate = SYS_RATE_IQ_6;
    }
    if(in_rate > max_in_rate)
    {
        printf("ERROR: DUC input rate cannot be higher than %s. Exiting test..!\n",
                sys_rate_str[dl_clk][max_in_rate]);
        return FAILURE;
    }

    if(in_rate < min_in_rate)
    {
        printf("ERROR: DUC input rate cannot be lesser than %s. Exiting test..!\n",
                sys_rate_str[dl_clk][min_in_rate]);
        return FAILURE;
    }

    if(out_rate > max_out_rate)
    {
        printf("ERROR: DUC output rate cannot be higher than %s. Exiting test..!\n",
                sys_rate_str[dl_clk][max_out_rate]);
        return FAILURE;
    }

    if(out_rate < min_out_rate)
    {
        printf("ERROR: DUC output rate cannot be lesser than %s. Exiting test..!\n",
                sys_rate_str[dl_clk][min_out_rate]);
        return FAILURE;
    }

    if(out_rate < in_rate)
    {
        printf("ERROR: DUC output rate cannot be lesser than the input rate. Exiting test..!\n");
        return FAILURE;
    }

    if(((in_rate == SYS_RATE_IQ_P125) && (out_rate > SYS_RATE_IQ_2)) ||
       ((in_rate == SYS_RATE_IQ_P187) && (out_rate > SYS_RATE_IQ_3)))
    {
        printf("ERROR: Only 4 DUC filter chains are available, so only upto an interpolation by 2^4 is possible.\n");
        printf("       Max out_rate for %s in_rate is %s. Exiting test..!\n", sys_rate_str[dl_clk][in_rate],
                sys_rate_str[dl_clk][4]);
        return FAILURE;
    }

    add_val[0] = val_kargs[0];

    val_kargs[1] = g_vectors_per_block[dl_clk][in_rate];
    val_kargs[3] = g_max_blocks;
    val_kargs[4] = dl_clk;

    vex_rx_val_kargs[1] = g_vectors_per_block[dl_clk][out_rate];
    vex_rx_val_kargs[2] = g_max_blocks;
    vex_rx_val_kargs[3] = VEX_MAX_BUF_SIZE / g_vectors_per_block[dl_clk][out_rate];

    if(rv = vha_init(vha_num))
    {
        printf("ERROR: Failed to do vha_init(), rv = %d\n", rv);
        return rv;
    }
#if CHECK_STATUS
    // print registers before starting any configurations
    printf("HOST: Checking registers before doing any register configurations\n");
    if(rv = test_check_status(tx_vex, rx_vex, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }
#endif

    if(rv = test_configure(tx_vex, rx_vex, vha_num, ant_num, in_rate, out_rate, mode, dl_clk))
    {
        printf("ERROR: Failed to do test_configure(), (rv = %d) Exiting test...!\n", rv);
        return FAILURE;
    }

#if CHECK_STATUS
    // print registers after the configurations are done
    printf("HOST: Finished register configurations, now checking registers\n");
    if(rv = test_check_status(tx_vex, rx_vex, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }
#endif

    // to clear the VEX memories before running a test
    vex_num = tx_vex;
    for(i = 0; i < 2; i++)
    {
        if(1 == i) vex_num = rx_vex;

        if(vex_mem_clear(vex_num, srp))
        {
             printf("ERROR: Failed to clear memories of VEX%d\n", vex_num);
             return FAILURE;
        }
        printf("HOST: Cleared memories of VEX%d\n", vex_num);
    }

    printf("HOST: Start vex program load...!\n");
    if((rv = vex_loader(tx_vex, "vex_fw/sim_m64/vex2vha.fw")))
    {
        LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vex2vha.fw", tx_vex);
        return rv;
    }
    printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vex2vha.fw", tx_vex);

    if(out_rate < SYS_RATE_IQ_P5)
    {
        if((rv = vex_loader(rx_vex, "vex_fw/sim_m64/vha2vex_p25iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex);
    }
    else
    {
        if((rv = vex_loader(rx_vex, "vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex);
    }
    printf("HOST: VEX program load - done\n");

    /* Loading the host parameters to VEX cores*/
    for(lc = 0; lc < ARRAY_SIZE(offset_val); lc++)
    {
        if(rv = write_reg_18a((VEX_BASE(tx_vex) + VEX_DMEM_OFFSET + offset_val[lc]), val_kargs[lc],
                              0xffffffff, "TX_VEX_PARAMS"))
            return rv;
    }
    printf("HOST: Loaded host params to vex core %d\n", tx_vex);

    for(lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if(rv = write_reg_18a((VEX_BASE(rx_vex) + VEX_DMEM_OFFSET + vex_rx_offset_val[lc]), vex_rx_val_kargs[lc],
                               0xffffffff, "RX_VEX_PARAMS"))
            return rv;
    }
    printf("HOST: Loaded host params to vex core %d\n", rx_vex);

    // We've a pointer to the input IQ samples, let's write that to the vector memory of the vex core 0
    strcpy(file_name, input_path_prefix);
    strcat(file_name, g_input_file[dl_clk][in_rate]);
    LOG_PRINT("HOST: Input sample file : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if(NULL == fptr)
    {
        LOG_PRINT("ERROR: Not able to open the input file\n");
        return FAILURE;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_inp,
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_PRINT("ERROR: Insufficient input samples\n");
        return FAILURE;
    }
    fclose(fptr);
    write_mem_18a((VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + HIVE_ADDR_vex2vha_vbuffer),
                  (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC),
                  val_inp[0], "TX_VEX_VMEM");
    printf("HOST: Initialized pattern into the vector memory of vex core %d\n", tx_vex);

    // We've a pointer to the output IQ samples, let's write that to the vector memory of the vex core 1
    strcpy(file_name, output_path_prefix);
    strcat(file_name, g_output_ref_file[dl_clk][(in_rate * 4) + out_rate]);
    LOG_PRINT("HOST: Output reference sample file : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if(NULL == fptr)
    {
        LOG_PRINT("ERROR: Not able to open the output file\n");
        return FAILURE;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_out,
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        LOG_PRINT("ERROR: Insufficient output samples\n");
        return FAILURE;
    }
    fclose(fptr);
    write_mem_18a((VEX_BASE(rx_vex) + VEX_VMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_vbuffer),
                  (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC),
                  val_out[0], "RX_VEX_VMEM");
    printf("HOST: Initialized pattern into the vector memory of vex core %d\n", rx_vex);

#if CHECK_STATUS
    // Dump out all the registers before starting the VEX to check all the status are clean
    printf("HOST: Checking registers before starting VEX cores\n");
    if(rv = test_check_status(tx_vex, rx_vex, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    // Try reading some input and output samples so programmed from the VEX vector memories
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET, 16, "Tx VEX Input samples");
    print_registers(VEX_BASE(rx_vex) + VEX_VMEM_OFFSET, 16, "Rx VEX Output ref samples");
#endif

    // Make sure the order is preserved (Start Rx vex first and then Tx vex)
    vex_start(rx_vex, 0/*start_addr*/);
    printf("HOST: Started vex core %d (Rx VEX)\n", rx_vex);

    vex_start(tx_vex, 0/*start_addr*/);
    printf("HOST: Started vex core %d (Tx VEX)\n", tx_vex);

    printf("HOST: Waiting for the VHA B2H flit count to be atleast %d\n", (g_vectors_per_block[dl_clk][in_rate] * 2));
    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_NSIP_OFFSET;
    cnt = 0;
    while(1)
    {
        b2h_flit_cnt += read_reg_18a(NSIP_HBI_B2H_CSR_FLIT_CNT_ADR(base_addr), "B2H_FLIT_COUNT");
        if(b2h_flit_cnt > (1 * g_vectors_per_block[dl_clk][in_rate] * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but b2h_flit_cnt is NOT reaching %d\n", cnt,
                   (1 * g_vectors_per_block[dl_clk][in_rate] * 2));
            break;
        }
    }
    printf("HOST: B2H_FLIT_CNT = %d\n", b2h_flit_cnt);

    printf("HOST: Waiting for the VHA H2B flit count to be atleast %d\n",
           (g_max_blocks * g_vectors_per_block[dl_clk][out_rate] * 2));
    cnt = 0;
    while(1)
    {
        h2b_flit_cnt += read_reg_18a(NSIP_HBI_H2B_FLIT_CNT_ADR(base_addr), "H2B_FLIT_COUNT");
        if(h2b_flit_cnt > (g_max_blocks * g_vectors_per_block[dl_clk][out_rate] * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but h2b_flit_cnt is NOT reaching %d\n", cnt,
                   (g_max_blocks * g_vectors_per_block[dl_clk][out_rate] * 2));
            break;
        }
    }
    printf("HOST: H2B_FLIT_CNT = %d\n", h2b_flit_cnt);

    printf("HOST: Waiting for the Rx VEX to receive and compare %d vectors\n",
           (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]));
    cnt = 0;
    while(1)
    {
       host_vec_processed = read_reg_18a((VEX_BASE(rx_vex) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_count1),
                                         "RX_VEX_HOST_VEC_PROCESSED");
       if(host_vec_processed >= (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]))
       {
          break;
       }
       cnt++;
       if(128 == cnt)
       {
           printf("ERROR: Waited for %d cycles, but host_vec_processed is NOT reaching %d\n", cnt,
                  (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]));
           break;
       }
    }

    printf("HOST: Reading the vector comparison results from the VEX core %d\n", rx_vex);
    host_result = read_reg_18a((VEX_BASE(rx_vex) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_compare_result),
                               "RX_VEX_HOST_RESULT");

    host_blocks_processed = read_reg_18a((VEX_BASE(rx_vex) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_add_val_out),
                                         "RX_VEX_HOST_RESULT");

    char* test_status = "SUCCESS";
    if((0xffffffff != host_result) || (!host_vec_processed)) test_status = "FAILURE";
    printf("HOST: Comparison result : 0x%x --> %s\n      Processed vectors : 0x%x\n", host_result, test_status,host_vec_processed);
    printf("      Processed blocks  : 0x%x\n", host_blocks_processed - add_val[0]);

    if(0xffffffff != host_result)
    {
        printf("ERROR: Output samples did not match with the Matlab reference output samples\n");
        rv = FAILURE;
    }
    if(0 == host_vec_processed)
    {
       printf("ERROR: Rx VEX did not process any samples\n");
       rv = FAILURE;
    }

#if CHECK_STATUS
    // Looking for any abnormal statuses post a test run
    printf("HOST: Checking registers after a test completion\n");
    if(test_check_status(tx_vex, rx_vex, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        rv = FAILURE;
    }
#endif
    if(SUCCESS == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    } else
    {
        printf("Test Result:------ FAIL -----!\n\n");
        printf("DEBUG INFO: Test failed for the input combination TXVEX=%d, RXVEX=%d, VHA=%d, ANT=%d, INRATE=%d, OUTRATE=%d, MODE=%d, "
               "DLCLK=%d\n\n", tx_vex, rx_vex, vha_num, ant_num, in_rate, out_rate, mode, dl_clk);
    }

#if DEBUG
    int num_samples;
    num_samples =(g_max_blocks * g_vectors_per_block[dl_clk][in_rate]) * NUM_OF_ELEMENTS_PER_VEC;
    printf("INFO: Number of input samples = %d\n", num_samples);
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + 0x0000, num_samples, "Tx VEX input samples");
    num_samples =(g_max_blocks * g_vectors_per_block[dl_clk][out_rate]) * NUM_OF_ELEMENTS_PER_VEC;
    printf("INFO: Number of output samples = %d\n", num_samples);
    print_registers(VEX_BASE(rx_vex) + VEX_VMEM_OFFSET + 0x0000, num_samples, "Rx VEX input samples");
    print_registers(VEX_BASE(rx_vex) + VEX_VMEM_OFFSET + 0xc000, num_samples, "Rx VEX Output ref samples copy");
    print_registers(VEX_BASE(rx_vex) + VEX_VMEM_OFFSET + 0xe000, num_samples, "Rx VEX Output samples");
#endif

    printf("HOST: End of the Test execution....!\n");

    return rv;

}

/**
 * function         test_configure()
 * @brief           Function configuring all the blocks required to run this test
 * @param [in]      tx_vex, rx_vex, vha_num, ant_num, in_rate, out_rate, mode, dl_clk
 * @return          status
 */

int test_configure(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num,
    sys_rate_t in_rate,
    sys_rate_t out_rate,
    filter_mode_t mode,
    uint32_t dl_clk)
{
    int rv;
    uint32_t dest_id;
    uint64_t vex_base_addr;

    rv = 0;
    // Configure VHA registers
    dest_id = rx_vex;                                      // VHA will stream to rx_vex
    if(rv = test_configure_vha(vha_num, ant_num, in_rate, out_rate, mode, dl_clk, dest_id))
    {
        printf("ERROR: Failed to configure VHA%d (rv = %d) Exiting test..!\n", vha_num, rv);
        return rv;
    }

    // Configure the CIO2STRM registers of tx_vex
    dest_id = vha_host_id[vha_num][ant_num];               // tx_vex will stream to vha
    if(rv = vex_cio2strm_configure(tx_vex, dest_id))
    {
        printf("ERROR: Failed to configure CIO2STRM of VEX%d (rv = %d) Exiting test..!\n", tx_vex, rv);
        return rv;
    }

    // Configure STRM2CIO registers of rx_vex
    if(rv = vex_strm2cio_configure(rx_vex))
    {
        printf("ERROR: Failed to configure STRM2CIO of VEX%d (rv = %d) Exiting test..!\n", rx_vex, rv);
        return rv;
    }

    // SDF init: An SDF gate should be initialized so that the receiving VEX will wait for a configured
    //  number of flits followed by a token flit to reach to it.
    vex_base_addr = VEX_BASE(rx_vex);
    if(rv = write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(vex_base_addr),
                          HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate,
                          VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                          "BPCA_BP_DMEM"))
        return rv;

    return rv;
}

/**
 * function         test_configure_vha()
 * @brief           Function configuring all the required VHA registers to run this test
 * @param [in]      vha_num, ant_num, in_rate, out_rate, mode, dl_clk
 * @return          status
 */

int test_configure_vha(
    uint32_t vha_num,
    uint32_t ant_num,
    uint32_t in_rate,
    uint32_t out_rate,
    filter_mode_t mode,
    uint32_t dl_clk,
    uint32_t dest_id)
{
    vha_antenna_t* vha_ant;
    vha_duc_t* duc0;
    vha_mod_t* mod;
    vha_ant_t* ant_reg;
    vha_t* vha_reg;
    nsip_hbi_t* cm;
    uint64_t vha_base_addr, vha_apb_base_addr, vha_reg_base_addr;
    uint64_t duc0_base_addr, mod_base_addr, ant_reg_base_addr, cm_base_addr;
    uint32_t value;
    int i, rv;

    rv = 0;
    vha_base_addr = VHA_BASE(vha_num);
    vha_apb_base_addr = vha_base_addr + VHA_APB_OFFSET(ant_num);
    if((vha_base_addr < 0x03c00000) || (vha_base_addr > 0x03ce0000))
    {
        printf("ERROR: Cannot configure VHA with base_addr = %x\n", vha_base_addr);
        return FAILURE;
    }
    // Let's first configure the VHA
    vha->base_addr = vha_base_addr;
    vha_ant = &(vha->ant[ant_num]);
    vha_ant->base_addr = vha_apb_base_addr;

    printf("INFO: vha_base_addr = 0x%x\n", vha_base_addr);
    // VHA_DUC block settings
    value = mode;                                          // bit0: 0-> auto, 1-> manual
    if(mode == MANUAL)
    {
        for(i = 1; ((i <= 4) && ((out_rate - (i - 1)) > in_rate)); i++)
        {
            value |= (1 << i);                             // bit[4:1] = stage_active
        }
    }
    duc0 = &(vha_ant->duc[0]);
    duc0_base_addr = vha_apb_base_addr + VHA_DUC_OFFSET(0);
    duc0->CFG.value = value;
    if(rv = write_reg_18a(VHA_DUC_CFG_ADR(duc0_base_addr),
                          duc0->CFG.value,
                          VHA_DUC_CFG_WR_MASK,
                          "VHA_DUC0_CONFIG"))
        return rv;

    // VHA_MOD block settings
    mod = &(vha_ant->mod);
    mod_base_addr = vha_apb_base_addr + VHA_MOD_OFFSET;
    mod->CFG.value = 0;                                    // active_bands = 0
    if(rv = write_reg_18a(VHA_MOD_CFG_ADR(mod_base_addr),
                          mod->CFG.value,
                          VHA_MOD_CFG_WR_MASK,
                          "VHA_MOD_CFG"))
        return rv;

    // VHA_ANT_REG block settings
    ant_reg = &(vha_ant->ant_reg);
    ant_reg_base_addr = vha_apb_base_addr + VHA_ANT_REG_OFFSET;
    value = g_vectors_per_block[dl_clk][in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_DL_IF_CFG[0].value = (4 << 8) | value;// cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_DL_CFG.value = (1 << 14) | (out_rate << 8) | (3 << 6) | in_rate;
                                                           // bit14: dl_of_enable band0,
                                                           // bit[10:8]: out_rate0,
                                                           // bit[7:6]: mod_bypass,
                                                           // bit[2:0]: in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    if(dl_clk & !out_rate)
    {
        ant_reg->VHA_ANT_CFG.value = 0x1;                  // Hack: if the out_rate is p187, then the
                                                           //  blk size (6flits) will not be the multiple
                                                           //  of 4, so make it to multiple of 2.
    }
    ant_reg->VHA_ANT_DL_OF_CFG[0].value = 0;               // no split
    ant_reg->VHA_ANT_ARB_CFG.value = 0;                    // mode = 0 = strict priority
    ant_reg->VHA_ANT_INT_HIGH_EN.value = 0x7ff;            // enable all the interrupts
    ant_reg->VHA_ANT_INT_LOW_EN.value = 0x7ff;             // enable all the interrupts
    if(rv = write_reg_18a(VHA_ANT_DL_IF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_IF_CFG[0].value,
                          VHA_ANT_DL_IF_CFG_WR_MASK,
                          "VHA_ANT_DL_IF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_CFG.value,
                          VHA_ANT_DL_CFG_WR_MASK,
                          "VHA_ANT_DL_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_CFG.value,
                          VHA_ANT_CFG_WR_MASK,
                          "VHA_ANT_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_OF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_OF_CFG[0].value,
                          VHA_ANT_DL_OF_CFG_WR_MASK,
                          "VHA_ANT_DL_OF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_ARB_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_ARB_CFG.value,
                          VHA_ANT_ARB_CFG_WR_MASK,
                          "VHA_ANT_ARB_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_HIGH_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_HIGH_EN.value,
                          VHA_ANT_INT_HIGH_EN_WR_MASK,
                          "VHA_ANT_INT_HIGH_EN"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_LOW_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_LOW_EN.value,
                          VHA_ANT_INT_LOW_EN_WR_MASK,
                          "VHA_ANT_INT_LOW_EN"))
        return rv;

    // VHA_ANT_CM settings
    cm = &(vha_ant->cm);
    cm_base_addr = vha_apb_base_addr + VHA_NSIP_OFFSET;
    cm->INTR_INT_HIGH_EN.value = ((1 << 20) - 1);          // enable all interrupts
    cm->INTR_INT_LOW_EN.value = ((1 << 20) - 1);           // enable all interrupts
    //  B2H registers
    cm->B2H_FF_FIFO_CTRL.value = NSIP_HBI_B2H_FF_FIFO_CTRL_DEFAULT;
    cm->B2H_CSR_CREDIT_CS.value = NSIP_HBI_B2H_CSR_CREDIT_CS_DEFAULT;
    cm->B2H_CSR_ADDR_TBL[0].value = 0x80000000;            // bit31: valid
                                                           // bit[27:0]: map_byte_addr
    cm->B2H_CSR_ADDR_MASK_TBL[0].value = 0x1ffff;          // mask
    //  H2B registers
    cm->H2B_FF_FIFO_CTRL.value = NSIP_HBI_H2B_FF_FIFO_CTRL_DEFAULT;
    cm->H2B_CREDIT_READY_CS.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT;
    cm->H2B_BUF_SZ_HW_TBL[0].value = 1;                    // dest_buf_size = (1 + 1) x da_block_size
    cm->H2B_MD_ADDR_LKUP_TBL[0].value = STRM2CIO_2_VEX_DMEM_OFFSET;
                                                           // metadata if enabled will get written to address 0x00 data memory
    cm->H2B_TK_ADDR_LKUP_TBL[0].value = STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate;
                                                           // token will be written to the address 0x80 in data memory of VEX
    cm->H2B_ADDR_LKUP_TBL[0].value = (1 << 31) | HIVE_ADDR_vha2vex_p5_8iq_vbuffer_out;
                                                           // data will be written to the address 0x4000 in vector memory
    cm->H2B_MD_CTRL_TBL[0].value = g_md_control_tbl[dl_clk][out_rate];
                                                           // bit[9:0]: da_block_size
    cm->H2B_TK_ROUTE_LKUP_TBL[0].value = dest_id;          // route the tokens to rx_vex
    cm->H2B_MD_ROUTE_LKUP_TBL[0].value = dest_id;          // route the metadata to rx_vex
    cm->H2B_ROUTE_LKUP_TBL[0].value = dest_id;             // route the data to rx_vex
    if(rv = write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(cm_base_addr),
                          cm->INTR_INT_HIGH_EN.value,
                          NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK,
                          "NSIP_HBI_INTR_INT_HIGH_EN"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(cm_base_addr),
                          cm->INTR_INT_LOW_EN.value,
                          NSIP_HBI_INTR_INT_LOW_EN_WR_MASK,
                          "NSIP_HBI_INTR_INT_LOW_EN"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_B2H_FF_FIFO_CTRL_ADR(cm_base_addr),
                          cm->B2H_FF_FIFO_CTRL.value,
                          NSIP_HBI_B2H_FF_FIFO_CTRL_WR_MASK,
                          "NSIP_HBI_B2H_FIFO_CONTROL"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_B2H_CSR_CREDIT_CS_ADR(cm_base_addr),
                          cm->B2H_CSR_CREDIT_CS.value,
                          NSIP_HBI_B2H_CSR_CREDIT_CS_WR_MASK,
                          "NSIP_HBI_B2H_CREDIT_CS"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_B2H_CSR_ADDR_TBL0_ADR(cm_base_addr),
                          cm->B2H_CSR_ADDR_TBL[0].value,
                          NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK,
                          "NSIP_HBI_B2H_ADDR_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_B2H_CSR_ADDR_MASK_TBL0_ADR(cm_base_addr),
                          cm->B2H_CSR_ADDR_MASK_TBL[0].value,
                          NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK,
                          "NSIP_HBI_B2H_ADDR_MASK_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_FF_FIFO_CTRL_ADR(cm_base_addr),
                          cm->H2B_FF_FIFO_CTRL.value,
                          NSIP_HBI_H2B_FF_FIFO_CTRL_WR_MASK,
                          "NSIP_HBI_H2B_FIFO_CONTROL"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_CREDIT_READY_CS_ADR(cm_base_addr),
                          cm->H2B_CREDIT_READY_CS.value,
                          NSIP_HBI_H2B_CREDIT_READY_CS_WR_MASK,
                          "NSIP_HBI_H2B_CREDIT_READY_CS"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_BUF_SZ_HW_TBL0_ADR(cm_base_addr),
                          cm->H2B_BUF_SZ_HW_TBL[0].value,
                          NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK,
                          "NSIP_HBI_H2B_BUF_SZ_HW_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_TK_ADDR_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_MD_ADDR_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_ADDR_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_ADDR_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_ADDR_LKUP_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_CTRL_TBL0_ADR(cm_base_addr),
                          cm->H2B_MD_CTRL_TBL[0].value,
                          NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_CTRL_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_TK_ROUTE_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_MD_ROUTE_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL0"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_ROUTE_LKUP_TBL0_ADR(cm_base_addr),
                          cm->H2B_ROUTE_LKUP_TBL[0].value,
                          NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_ROUTE_LKUP_TBL0"))
        return rv;

    // VHA_REG block settings
    vha_reg = &(vha->vha_reg);
    vha_reg_base_addr = vha_base_addr + VHA_REG_OFFSET;
    vha_reg->VHA_CFG.value = 0x3fc | dl_clk;
                                                           // bit[9:8]: crux_clock_enable,
                                                           // bit[3:2]: dl_clock_enable,
                                                           // bit0: dl_clock_select (0->983MHz, 1->1GHz)
    vha_reg->VHA_DL_IF_CFG.value = ((1 + (3 * ant_num)) << (ant_num * 8));
                                                           // bit[11:8]: dl_ant1_band0_af_gate,
                                                           // bit[3:0]: dl_ant0_band0_af_gate
    vha_reg->VHA_DL_CTL.value = (1 << (2 * ant_num));      // dl_ififo_enable ant0/1_band0
    if(rv = write_reg_18a(VHA_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_CFG.value,
                          VHA_CFG_WR_MASK,
                          "VHA_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_IF_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_IF_CFG.value,
                          VHA_DL_IF_CFG_WR_MASK,
                          "VHA_DL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_CTL_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_CTL.value,
                          VHA_DL_CTL_WR_MASK,
                          "VHA_DL_CTL"))
        return rv;

    printf("INFO: VHA%d configuration completed\n", vha_num);

    return rv;
}

/*
 * function    : test_check_status()
 * @brief      : this function checks various statuses of VHA and VEX streaming interfaces
 *
 */
int test_check_status(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num)
{
    int rv, e_code;

    e_code = SUCCESS;
    rv = SUCCESS;
    if(rv = vha_check_status(vha_num, ant_num))
        e_code = 1;                                        // FAILURE code for VHA status wrong
    if(rv = vex_cio2strm_check_status(tx_vex))
        e_code |= 2;                                       // FAILURE code for CIO2STRM status wrong
    if(rv = vex_strm2cio_check_status(rx_vex))
        e_code |= 4;                                       // FAILURE code for STRM2CIO status wrong

    test_show_regs(tx_vex, rx_vex, vha_num, ant_num);

    return e_code;
}

/*
 * function    : test_show_regs()
 * @brief      : this function all the registers of VHA and VEX streaming interfaces
 *
 */
void test_show_regs(
    uint32_t tx_vex,
    uint32_t rx_vex,
    uint32_t vha_num,
    uint32_t ant_num)
{
    vha_show_regs(vha_num, ant_num);                       // VHA registers
    vex_cio2strm_show_regs(tx_vex);                        // CIO2STRM registers of tx_vex
    vex_strm2cio_show_regs(rx_vex);                        // STRM2CIO registers of rx_vex
}

// End of file
