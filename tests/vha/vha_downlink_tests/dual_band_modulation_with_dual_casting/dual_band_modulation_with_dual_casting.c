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
 * @file    dual_band_modulation_with_dual_casting.c
 * @brief   HOST Configuration code for sending the data from VEX to VHA and receving it back.
 * @details 1. Configuration of VEX, VHA and Common Module for sending data from VEX to VHA
               and receving it back to VEX for all the Sample Rates
            2. Evaluate the result written by VEX for the test case evaluation.
 * @TC Description:
 *          1. A certain number of IQ samples will be streamed from a VEX core to the VHA dual
 *             band DL path. One VEX core will be streaming both Band0 and Band1 IQ samples.
 *          2. DUC filters are enabled as per the input and output rates passed down.
 *          3. VHA processed samples will be streamed back to two different VEXes via two different
 *             output FIFOs.
            4. HOST will be waiting on a memory location where VEXes will update the number of vectors
               it processed.
 */

#include "vha_common_definitions.h"
#include "vex2vha.map.h"
#include "vha2vex_p25iq.map.h"
#include "vha2vex_p5_8iq.map.h"

// Pointers to the input IQ samples
const char* input_path_prefix = "./vha_matlab_wrappers/input_samples/modulation/";
const char* g_input_file[2][4][2] = {
    {
     {"band0_dual_band_modulation_p125.txt", "band1_dual_band_modulation_p125.txt"},
     {"band0_dual_band_modulation_p25.txt", "band1_dual_band_modulation_p25.txt"},
     {"band0_dual_band_modulation_p5.txt", "band1_dual_band_modulation_p5.txt"},
     {"band0_dual_band_modulation_1.txt", "band1_dual_band_modulation_1.txt"},
    },
    {
     {"band0_dual_band_modulation_p187.txt", "band1_dual_band_modulation_p187.txt"},
     {"band0_dual_band_modulation_p375.txt", "band1_dual_band_modulation_p375.txt"},
     {"band0_dual_band_modulation_p75.txt", "band1_dual_band_modulation_p75.txt"},
     {"band0_dual_band_modulation_1p5.txt", "band1_dual_band_modulation_1p5.txt"},
    }
   };

// Pointers to the Matlab output reference IQ samples
const char* output_path_prefix = "./vha_matlab_wrappers/output_samples/modulation/";
const char* g_output_ref_file[2][12] = {
    {
    // For the inputs at p125 Gsps
    "p125/dual_band_modulation_1.txt",                     // W1+W2+W3
    "p125/dual_band_modulation_2.txt",                     // W1+W2+W3+W4
    NULL,

    // For the inputs at p25 Gsps
    "p25/dual_band_modulation_1.txt",                      // W1+W2
    "p25/dual_band_modulation_2.txt",                      // W1+W2+W3
    "p25/dual_band_modulation_4.txt",                      // W1+W2+W3+W4

    // For the inputs at p5 Gsps
    "p5/dual_band_modulation_1.txt",                       // W1 only
    "p5/dual_band_modulation_2.txt",                       // W1+W2
    "p5/dual_band_modulation_4.txt",                       // W1+W2+W3

    // For the inputs at 1 Gsps
    NULL,
    "1g/dual_band_modulation_2.txt",                       // W1 only
    "1g/dual_band_modulation_4.txt",                       // W1+W2
    },
    {
    // For the inputs at p187 Gsps
    "p187/dual_band_modulation_1p5.txt",                   // W1+W2+W3
    "p187/dual_band_modulation_3.txt",                     // W1+W2+W3+W4
    NULL,

    // For the inputs at p375 Gsps
    "p375/dual_band_modulation_1p5.txt",                   // W1+W2
    "p375/dual_band_modulation_3.txt",                     // W1+W2+W3
    "p375/dual_band_modulation_6.txt",                     // W1+W2+W3+W4

    // For the inputs at p75 Gsps
    "p75/dual_band_modulation_1p5.txt",                    // W1 only
    "p75/dual_band_modulation_3.txt",                      // W1+W2
    "p75/dual_band_modulation_6.txt",                      // W1+W2+W3

    // For the inputs at 1.5 Gsps
    NULL,
    "1p5/dual_band_modulation_3.txt",                      // W1 only
    "1p5/dual_band_modulation_6.txt",                      // W1+W2
    }
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
    uint32_t rx_vex0,
    uint32_t rx_vex1,
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
    uint32_t dest_id0,
    uint32_t dest_id1);

int test_check_status(
    uint32_t tx_vex,
    uint32_t rx_vex0,
    uint32_t rx_vex1,
    uint32_t vha_num,
    uint32_t ant_num);

void test_show_regs(
    uint32_t tx_vex,
    uint32_t rx_vex0,
    uint32_t rx_vex1,
    uint32_t vha_num,
    uint32_t ant_num);

/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */

int main(
    int argc,
    const char* argv[])
{
    FILE* fptr;
    char file_name[100];
    int rv = 0, val = 0, dev_id = 0, flags = 0;
    int tx_in_list, rx0_in_list, rx1_in_list, same_cores, vex_combo_good;
    int (*ve_list)[NUM_VE_PER_VHA];
    uint64_t base_addr;
    uint32_t tx_vex, rx_vex0, rx_vex1, vha_num, ant_num;
    sys_rate_t in_rate, out_rate, min_in_rate, min_out_rate, max_in_rate, max_out_rate;
    filter_mode_t mode;
    volatile int b2h_flit_cnt = 0, h2b_flit_cnt = 0, host_result0 = 0, host_result1 = 0;
    volatile int host_vec_processed0 = 0, host_blocks_processed0 = 0;
    volatile int host_vec_processed1 = 0, host_blocks_processed1 = 0;
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
    printf("Test: Dual band modulation with dual casting\n");
    printf("%s\n", g_compile_time);
    printf("BUILD_DIR: %s\n\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    printf("\n");

    tx_vex   = (int)argv[0];
    rx_vex0  = (int)argv[1];
    rx_vex1  = (int)argv[2];
    vha_num  = (int)argv[3];
    ant_num  = (int)argv[4];
    in_rate  = (int)argv[5];
    out_rate = (int)argv[6];
    mode     = (int)argv[7];
    dl_clk   = (int)argv[8];

    printf("INFO: File    : %s\n", __FILE__);
    printf("INFO: argc    : %d\n", argc);
    printf("INFO: argv[0] : %d = tx_vex   (VEX%d)\n", tx_vex, tx_vex);
    printf("INFO: argv[1] : %d = rx_vex0  (VEX%d)\n", rx_vex0, rx_vex0);
    printf("INFO: argv[2] : %d = rx_vex1  (VEX%d)\n", rx_vex1, rx_vex1);
    printf("INFO: argv[3] : %d = vha_num  (VHA%d)\n", vha_num, vha_num);
    printf("INFO: argv[4] : %d = ant_num  (ANTENNA%d)\n", ant_num, ant_num);
    printf("INFO: argv[5] : %d = in_rate  (%s)\n", in_rate, sys_rate_str[dl_clk][in_rate]);
    printf("INFO: argv[6] : %d = out_rate (%s)\n", out_rate, sys_rate_str[dl_clk][out_rate]);
    printf("INFO: argv[7] : %d = mode     (%s)\n", mode, duc_mode_str[mode]);
    printf("INFO: argv[8] : %d = dl_clk   (%s)\n", dl_clk, vha_dl_clk[dl_clk]);

    // Let's first do some sanity checks on the input arguments received
    if(vha_num > (NUM_VHA_INSTANCES - 1))
    {
        printf("ERROR: VHA number cannot be higher than 7, Exiting test..!\n");
        return FAILURE;
    }
    if((tx_vex > (NUM_VE_CORES - 1)) || (rx_vex0 > (NUM_VE_CORES - 1)) || (rx_vex1 > (NUM_VE_CORES - 1)))
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
    for(i = 0; i < 3; i++)
    {
        if(1 == i) vex_num = rx_vex0;
        if(2 == i) vex_num = rx_vex1;
        if(is_vex_present(vex_num) < 0)                    // check are the VEX's present on this build
        {
            printf("Exiting..!\n");
            return FAILURE;
        }
    }

    vex_combo_good = 0; tx_in_list = 0; rx0_in_list = 0; rx1_in_list = 0;
    ve_list = &g_vha_ve_list[(vha_num & 3)];               // VHA 0 & 4 share the same VEX cores, so is 1 & 5, 2 & 6 and 3 & 7

    for(i = 0; i < NUM_VE_PER_VHA; i++)
    {
        if((tx_vex == *((*ve_list) + i)) && (!tx_in_list))
        {
            tx_in_list = 1;
        }
        if((rx_vex0 == *((*ve_list) + i)) && (!rx0_in_list))
        {
            rx0_in_list = 1;
        }
        if((rx_vex1 == *((*ve_list) + i)) && (!rx1_in_list))
        {
            rx1_in_list = 1;
        }
        if(tx_in_list && rx0_in_list && rx1_in_list)
        {
            break;
        }
    }

    same_cores = 0;
    if((tx_vex == rx_vex0) || (tx_vex == rx_vex1) || (rx_vex0 == rx_vex1))
        same_cores = 1;
    if(same_cores) printf("ERROR: Cannot run this test with same cores\n");
    if(!tx_in_list) printf("ERROR: Tx VEX (core %d) is NOT connected to VHA%d\n", tx_vex, vha_num);
    if(!rx0_in_list) printf("ERROR: Rx VEX (core %d) is NOT connected to VHA%d\n", rx_vex0, vha_num);
    if(!rx1_in_list) printf("ERROR: Rx VEX (core %d) is NOT connected to VHA%d\n", rx_vex1, vha_num);
    if(!tx_in_list || !rx0_in_list || !rx1_in_list)
    {
        printf("Please find below the list of VEX cores connected to VHA%d\n   [ ", vha_num);
        for(i = 0; i < NUM_VE_PER_VHA; i++)
        {
            printf("%d ", *(*(ve_list) + i));
        }
        printf("]\n");
    }

    if((tx_in_list && rx0_in_list && rx1_in_list) && (!same_cores))
    {
        vex_combo_good = 1;
    }
    if(!vex_combo_good)
    {
        printf("ERROR: Cannot run this test with these VHA-VEX combinations.\n");
        printf("Please make sure,\n"
               "   i. Tx VEX and Rx VEX's are connected to VHA%d\n"
               "   ii. All the VEX cores are distinct and not the same cores\n", vha_num);
        printf("Exiting test..!\n");
        return FAILURE;
    }

    if((dl_clk != 0) && (dl_clk != 1))
    {
        printf("ERROR: dl_clk can take either 0 (983Mhz) or 1 (1.474MHz)\n");
        printf("Exiting test..!\n");
        return FAILURE;
    }
    min_in_rate = SYS_RATE_IQ_P125;
    max_in_rate = SYS_RATE_IQ_1;
    min_out_rate = SYS_RATE_IQ_1;
    max_out_rate = SYS_RATE_IQ_4;
    if(dl_clk)                                             // clk = 1.5GHz
    {
        min_in_rate = SYS_RATE_IQ_P187;
        max_in_rate = SYS_RATE_IQ_1P5;
        min_out_rate = SYS_RATE_IQ_1P5;
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
        printf("ERROR: MODULATOR output rate cannot be lesser than %s. Exiting test..!\n",
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

    // print registers before starting any configurations
    printf("HOST: Checking registers before doing any register configurations\n");
    if(rv = test_check_status(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    if(rv = test_configure(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num, in_rate, out_rate, mode, dl_clk))
    {
        printf("ERROR: Failed to do test_configure(), (rv = %d) Exiting test...!\n", rv);
        return FAILURE;
    }

    // print registers after the configurations are done
    printf("HOST: Finished register configurations, now checking registers\n");
    if(rv = test_check_status(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    // to clear the VEX memories before running a test
    vex_num = tx_vex;
    for(i = 0; i < 3; i++)
    {
        if(1 == i) vex_num = rx_vex0;
        else if(1 == i) vex_num = rx_vex1;

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
        if((rv = vex_loader(rx_vex0, "vex_fw/sim_m64/vha2vex_p25iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex0);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex0);

        if((rv = vex_loader(rx_vex1, "vex_fw/sim_m64/vha2vex_p25iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex1);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p25iq.fw", rx_vex1);
    } else
    {
        if((rv = vex_loader(rx_vex0, "vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex0);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex0);
        if((rv = vex_loader(rx_vex1, "vex_fw/sim_m64/vha2vex_p5_8iq.fw")))
        {
            LOG_ERROR("Failed to download progarm: %s to VEX%d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex1);
            return rv;
        }
        printf("HOST: Loaded %s to vex core %d\n", "vex_fw/sim_m64/vha2vex_p5_8iq.fw", rx_vex1);
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
        if(rv = write_reg_18a((VEX_BASE(rx_vex0) + VEX_DMEM_OFFSET + vex_rx_offset_val[lc]), vex_rx_val_kargs[lc],
                               0xffffffff, "RX_VEX_PARAMS"))
            return rv;
    }
    printf("HOST: Loaded host params to vex core %d\n", rx_vex0);

    for(lc = 0; lc < ARRAY_SIZE(vex_rx_offset_val); lc++)
    {
        if(rv = write_reg_18a((VEX_BASE(rx_vex1) + VEX_DMEM_OFFSET + vex_rx_offset_val[lc]), vex_rx_val_kargs[lc],
                               0xffffffff, "RX_VEX_PARAMS"))
            return rv;
    }
    printf("HOST: Loaded host params to vex core %d\n", rx_vex1);

    // We've a pointer to the input IQ samples, let's write that to the vector memory of the transmit VEX
    strcpy(file_name, input_path_prefix);
    strcat(file_name, g_input_file[dl_clk][in_rate][0]);   // Band0
    printf("HOST: Input sample file (Band0) : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if(NULL == fptr)
    {
        printf("ERROR: Not able to open the input file\n");
        return FAILURE;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_inp,
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient input samples\n");
        return FAILURE;
    }
    fclose(fptr);
    write_mem_18a((VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + HIVE_ADDR_vex2vha_vbuffer0),
                  (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC),
                  val_inp[0], "TX_VEX_VMEM");
    printf("HOST: Initialized pattern (Band0) into the vector memory of vex core %d\n", tx_vex);

    strcpy(file_name, input_path_prefix);
    strcat(file_name, g_input_file[dl_clk][in_rate][1]);   // Band1
    printf("HOST: Input sample file (Band1) : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if(NULL == fptr)
    {
        printf("ERROR: Not able to open the input file\n");
        return -1;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_inp,
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient input samples\n");
        return -1;
    }
    fclose(fptr);
    write_mem_18a((VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + HIVE_ADDR_vex2vha_vbuffer1),
                  (g_vectors_per_block[dl_clk][in_rate] * NUM_OF_ELEMENTS_PER_VEC),
                  val_inp[0], "TX_VEX_VMEM");
    printf("HOST: Initialized pattern (Band1) into the vector memory of vex core %d\n", tx_vex);

    // We've a pointer to the output IQ samples, let's write that to the vector memory of the receiving VEX
    strcpy(file_name, output_path_prefix);
    strcat(file_name, g_output_ref_file[dl_clk][(in_rate * 3) + (out_rate - 3)]);
    printf("HOST: Output reference sample file : %s\n", file_name);
    fptr = fopen(file_name, "r");
    if(NULL == fptr)
    {
        printf("ERROR: Not able to open the output file\n");
        return FAILURE;
    }
    if(vector_read_hex_u32(fptr,
                           (int*)val_out,
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC)) <
                           (g_vectors_per_block[dl_clk][out_rate] * NUM_OF_ELEMENTS_PER_VEC))
    {
        printf("ERROR: Insufficient output samples\n");
        return FAILURE;
    }
    fclose(fptr);
    write_mem_18a((VEX_BASE(rx_vex0) + VEX_VMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_vbuffer),
                  ((g_vectors_per_block[dl_clk][out_rate]) * NUM_OF_ELEMENTS_PER_VEC),
                  val_out[0], "RX_VEX_VMEM");
    printf("HOST: Initialized pattern into the vector memory of vex core %d\n", rx_vex0);

    write_mem_18a((VEX_BASE(rx_vex1) + VEX_VMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_vbuffer),
                  ((g_vectors_per_block[dl_clk][out_rate]) * NUM_OF_ELEMENTS_PER_VEC),
                  val_out[0], "RX_VEX_VMEM");
    printf("HOST: Initialized pattern into the vector memory of vex core %d\n", rx_vex1);

    // Dump out all the registers before starting the VEX to check all the status are clean
    printf("HOST: Checking registers before starting VEX cores\n");
    if(rv = test_check_status(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    // Try reading some data memory contents from both the VEXes
    print_registers(VEX_BASE(tx_vex) + VEX_DMEM_OFFSET, 24, "Tx VEX DMEM");
    print_registers(VEX_BASE(rx_vex0) + VEX_DMEM_OFFSET, 24, "Rx VEX DMEM");
    print_registers(VEX_BASE(rx_vex1) + VEX_DMEM_OFFSET, 24, "Rx VEX DMEM");

    // Try reading some input and output samples so programmed from the VEX vector memories
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET, 16, "Tx VEX Input samples");          // Band0 IQ samples
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + HIVE_ADDR_vex2vha_vbuffer1, 16, "Tx VEX Input samples");
                                                                                              // Band1 IQ samples
    print_registers(VEX_BASE(rx_vex0) + VEX_VMEM_OFFSET,  16, "Rx VEX0 Output ref samples");  // Band combined IQ samples
    print_registers(VEX_BASE(rx_vex1) + VEX_VMEM_OFFSET, 16, "Rx VEX1 Output ref samples");

    // Make sure the order is preserved (Start Rx vex first and then Tx vex)
    vex_start(rx_vex0, 0);
    printf("HOST: Started vex core %d (Rx VEX)\n", rx_vex0);
    vex_start(rx_vex1, 0);
    printf("HOST: Started vex core %d (Rx VEX)\n", rx_vex1);

    vex_start(tx_vex, 0);
    printf("HOST: Started vex core %d (Tx VEX)\n", tx_vex);

    printf("HOST: Waiting for the VHA B2H flit count to be atleast %d\n", (2 * (g_vectors_per_block[dl_clk][in_rate] * 2)));
                                                           // 2 times, because there are flits for 2 bands
    base_addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant_num) + VHA_NSIP_OFFSET;
    cnt = 0;
    while(1)
    {
        b2h_flit_cnt += read_reg_18a(NSIP_HBI_B2H_CSR_FLIT_CNT_ADR(base_addr), "B2H_FLIT_COUNT");
        if(b2h_flit_cnt > (2 * g_vectors_per_block[dl_clk][in_rate] * 2))
        {
            break;
        }
        cnt++;
        if(128 == cnt)
        {
            printf("ERROR: Waited for %d cycles, but b2h_flit_cnt is NOT reaching %d\n", cnt,
                   (2 * g_vectors_per_block[dl_clk][in_rate] * 2));
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
       host_vec_processed0 = read_reg_18a((VEX_BASE(rx_vex0) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_count1),
                                         "RX_VEX_HOST_VEC_PROCESSED");
       if(host_vec_processed0 >= (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]))
       {
          break;
       }
       cnt++;
       if(128 == cnt)
       {
           printf("ERROR: Waited for %d cycles, but VEX %d host_vec_processed is NOT reaching %d\n", cnt, rx_vex0,
                  (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]));
           break;
       }
    }

    cnt = 0;
    while(1)
    {
       host_vec_processed1 = read_reg_18a((VEX_BASE(rx_vex1) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_count1),
                                         "RX_VEX_HOST_VEC_PROCESSED");
       if(host_vec_processed1 >= (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]))
       {
          break;
       }
       cnt++;
       if(128 == cnt)
       {
           printf("ERROR: Waited for %d cycles, but VEX %d host_vec_processed is NOT reaching %d\n", cnt, rx_vex1,
                             (g_max_blocks * g_vectors_per_block[dl_clk][out_rate]));
           break;
       }
    }

    printf("HOST: Reading the vector comparison results from the VEX cores %d and %d\n", rx_vex0, rx_vex1);
    host_result0 = read_reg_18a((VEX_BASE(rx_vex0) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_compare_result),
                               "RX_VEX_HOST_RESULT");

    host_blocks_processed0 = read_reg_18a((VEX_BASE(rx_vex0) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_add_val_out),
                                         "RX_VEX_HOST_RESULT");
    host_result1 = read_reg_18a((VEX_BASE(rx_vex1) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_compare_result),
                               "RX_VEX_HOST_RESULT");

    host_blocks_processed1 = read_reg_18a((VEX_BASE(rx_vex1) + VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_g_add_val_out),
                                         "RX_VEX_HOST_RESULT");

    char* test_status0 = "SUCCESS";
    char* test_status1 = "SUCCESS";
    if((0xffffffff != host_result0) || (!host_vec_processed0)) test_status0 = "FAILURE";
    if((0xffffffff != host_result1) || (!host_vec_processed1)) test_status1 = "FAILURE";
    printf("HOST: Comparison result (VEX%d) : 0x%x --> %s\n      Processed vectors : %d\n", rx_vex0, host_result0, test_status0, host_vec_processed0);
    printf("      Processed blocks  : %d\n", host_blocks_processed0 - add_val[0]);

    if(0xffffffff != host_result0)
    {
        printf("ERROR: Output samples did not match with the Matlab reference output samples for the VEX%d\n", rx_vex0);
        rv = FAILURE;
    }
    if(0 == host_vec_processed0)
    {
       printf("     Rx VEX %d did not process any samples\n", rx_vex0);
       rv = FAILURE;
    }
    printf("HOST: Comparison result (VEX%d) : 0x%x --> %s\n      Processed vectors : %d\n", rx_vex1, host_result1, test_status1,host_vec_processed1);
    printf("      Processed blocks  : %d\n", host_blocks_processed1 - add_val[0]);

    if(0xffffffff != host_result1)
    {
        printf("ERROR: Output samples did not match with the Matlab reference output samples for the VEX%d\n", rx_vex1);
        rv = -1;
    }
    if(0 == host_vec_processed1)
    {
       printf("     Rx VEX %d did not process any samples\n", rx_vex1);
       rv = -1;
    }

    // Looking for any abnormal statuses post a test run
    printf("HOST: Checking registers after a test completion\n");
    if(test_check_status(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        rv = FAILURE;
    }

    if(SUCCESS == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    } else
    {
        printf("Test Result:------ FAIL -----!\n\n");
        printf("DEBUG INFO: Test failed for the input combination TXVEX=%d, RXVEX0=%d, RXVEX1=%d, VHA=%d, ANT=%d, INRATE=%d, OUTRATE=%d, "
               "MODE=%d, DLCLK=%d\n\n", tx_vex, rx_vex0, rx_vex1, vha_num, ant_num, in_rate, out_rate, mode, dl_clk);
    }

#if DEBUG
    int num_samples;

    num_samples =(g_max_blocks * g_vectors_per_block[dl_clk][in_rate]) * NUM_OF_ELEMENTS_PER_VEC;
    printf("INFO: Number of input samples = %d\n", num_samples);
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + 0x0000, num_samples, "Tx VEX input samples (Band0)");
    print_registers(VEX_BASE(tx_vex) + VEX_VMEM_OFFSET + 0x2000, num_samples, "Tx VEX input samples (Band1)");
    num_samples =(g_max_blocks * g_vectors_per_block[dl_clk][out_rate]) * NUM_OF_ELEMENTS_PER_VEC;
    printf("INFO: Number of output samples = %d\n", num_samples);
    print_registers(VEX_BASE(rx_vex0) + VEX_VMEM_OFFSET + 0x0000, num_samples, "Rx VEX input samples");
    print_registers(VEX_BASE(rx_vex0) + VEX_VMEM_OFFSET + 0xc000, num_samples, "Rx VEX Output ref samples copy");
    print_registers(VEX_BASE(rx_vex0) + VEX_VMEM_OFFSET + 0xe000, num_samples, "Rx VEX Output samples");
    print_registers(VEX_BASE(rx_vex1) + VEX_VMEM_OFFSET + 0x0000, num_samples, "Rx VEX input samples");
    print_registers(VEX_BASE(rx_vex1) + VEX_VMEM_OFFSET + 0xc000, num_samples, "Rx VEX Output ref samples copy");
    print_registers(VEX_BASE(rx_vex1) + VEX_VMEM_OFFSET + 0xe000, num_samples, "Rx VEX Output samples");
#endif

    printf("HOST: End of the Test execution....!\n");

    return rv;

}

/**
 * function         test_configure()
 * @brief           Function configuring all the blocks required to run this test
 * @param [in]      tx_vex, rx_vex0, rx_vex1, vha_num, ant_num, in_rate, out_rate, mode, dl_clk
 * @return          status
 */

int test_configure(
    uint32_t tx_vex,
    uint32_t rx_vex0,
    uint32_t rx_vex1,
    uint32_t vha_num,
    uint32_t ant_num,
    sys_rate_t in_rate,
    sys_rate_t out_rate,
    filter_mode_t mode,
    uint32_t dl_clk)
{
    int rv;
    uint32_t dest_id, dest_id0, dest_id1;
    uint64_t vex_base_addr;

    rv = 0;
    // Configure VHA registers
    dest_id0 = rx_vex0;                                    // VHA will stream to rx_vex
    dest_id1 = rx_vex1;
    if(rv = test_configure_vha(vha_num, ant_num, in_rate, out_rate, mode, dl_clk, dest_id0, dest_id1))
    {
        printf("ERROR: Failed to configure VHA%d (rv = %d) Exiting test..!\n", vha_num, rv);
        return rv;
    }

    // Configure the CIO2STRM registers of tx_vex
    dest_id = vha_host_id[vha_num][ant_num];               // tx_vex will stream to VHA
    if(rv = vex_cio2strm_configure_for_2_streams(tx_vex, dest_id))
    {
        printf("ERROR: Failed to configure CIO2STRM of VEX%d (rv = %d) Exiting test..!\n", tx_vex, rv);
        return rv;
    }

    // Configure STRM2CIO registers of rx_vex0 and rx_vex1
    if(rv = vex_strm2cio_configure(rx_vex0))
    {
        printf("ERROR: Failed to configure STRM2CIO of VEX%d (rv = %d Exiting test..!\n", rx_vex0, rv);
        return rv;
    }
    if(rv = vex_strm2cio_configure(rx_vex1))
    {
        printf("ERROR: Failed to configure STRM2CIO of VEX%d (rv = %d) Exiting test..!\n", rx_vex1, rv);
        return rv;
    }

    // SDF init: An SDF gate should be initialized so that the receiving VEX will wait for a configured
    //  number of flits followed by a token flit to reach to it.
    vex_base_addr = VEX_BASE(rx_vex0);
    if(rv = write_reg_18a(VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_ADR(vex_base_addr),
                          HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate,
                          VE32_CELL_LM_SDFGATE_BPCA_BP_DMEM_WR_MASK,
                          "BPCA_BP_DMEM"))
        return rv;
    vex_base_addr = VEX_BASE(rx_vex1);
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
    uint32_t dest_id0,
    uint32_t dest_id1)
{
    vha_antenna_t* vha_ant;
    vha_duc_t* duc0;
    vha_duc_t* duc1;
    vha_mod_t* mod;
    vha_ant_t* ant_reg;
    vha_t* vha_reg;
    swg_t* swg;
    nsip_hbi_t* cm;
    uint64_t vha_base_addr, vha_apb_base_addr, cm_base_addr, vha_reg_base_addr, swg_base_addr;
    uint64_t duc0_base_addr, duc1_base_addr, mod_base_addr, ant_reg_base_addr, vex_base_addr;
    uint32_t value;
    int i, rv = 0;

    uint64_t fclk, fout0, fout1, fs, num_cordics, delta_phase;
    uint64_t angle_bw_cordics, incr_angle, incr_val;
    uint64_t init_angle[4] = {0, 0, 0, 0};
    uint64_t init_val[4] = {0, 0, 0, 0};

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

    duc1 = &(vha_ant->duc[1]);
    duc1_base_addr = vha_apb_base_addr + VHA_DUC_OFFSET(1);
    duc1->CFG.value = value;
    if(rv = write_reg_18a(VHA_DUC_CFG_ADR(duc1_base_addr),
                          duc1->CFG.value,
                          VHA_DUC_CFG_WR_MASK,
                          "VHA_DUC1_CONFIG"))
        return rv;

    // VHA_MOD block settings
    mod = &(vha_ant->mod);
    mod_base_addr = vha_apb_base_addr + VHA_MOD_OFFSET;
    mod->CFG.value = 3;                                 // active_bands = both
    mod->EN.value = ((1 << (out_rate - 2)) - 1);
    if (5 == out_rate)
    {
        mod->EN.value = ((1 << (out_rate - 1)) - 1);
    }
    if(rv = write_reg_18a(VHA_MOD_CFG_ADR(mod_base_addr),
                          mod->CFG.value,
                          VHA_MOD_CFG_WR_MASK,
                          "VHA_MOD_CFG"))
        return rv;

    if(rv = write_reg_18a(VHA_MOD_EN_ADR(mod_base_addr),
                          mod->EN.value,
                          VHA_MOD_EN_WR_MASK,
                          "VHA_MOD_EN"))
        return rv;

    // VHA_ANT_REG block settings
    ant_reg = &(vha_ant->ant_reg);
    ant_reg_base_addr = vha_apb_base_addr + VHA_ANT_REG_OFFSET;
    value = g_vectors_per_block[dl_clk][in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_DL_IF_CFG[0].value = (4 << 8) | value;// cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_DL_IF_CFG[1].value = (4 << 8) | value;// cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_DL_CFG.value = (3 << 14) | (out_rate << 11) | (out_rate << 8) | (in_rate << 3) | in_rate;
                                                           // bit[15:14]: dl_of_enable,
                                                           // bit[13:11]: out_rate1
                                                           // bit[10:8]: out_rate0,
                                                           // bit[7:6]: mod_bypass,
                                                           // bit[5:3]: in_rate1
                                                           // bit[2:0]: in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    ant_reg->VHA_ANT_DL_OF_CFG[0].value = 0;
    ant_reg->VHA_ANT_DL_OF_CFG[1].value = 0;
    ant_reg->VHA_ANT_ARB_CFG.value = 0;                    // mode = 0 = strict priority
    ant_reg->VHA_ANT_INT_HIGH_EN.value = ((1 << VHA_ANT_NUM_INTERRUPTS) - 1);
                                                           // enable all the interrupts
    ant_reg->VHA_ANT_INT_LOW_EN.value = ((1 << VHA_ANT_NUM_INTERRUPTS) - 1);
                                                           // enable all the interrupts
    if(rv = write_reg_18a(VHA_ANT_DL_IF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_IF_CFG[0].value,
                          VHA_ANT_DL_IF_CFG_WR_MASK,
                          "VHA_ANT_DL_IF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_IF_CFG1_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_IF_CFG[1].value,
                          VHA_ANT_DL_IF_CFG_WR_MASK,
                          "VHA_ANT_DL_IF_CFG1"))
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
    if(rv = write_reg_18a(VHA_ANT_DL_OF_CFG1_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_OF_CFG[1].value,
                          VHA_ANT_DL_OF_CFG_WR_MASK,
                          "VHA_ANT_DL_OF_CFG1"))
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
    cm->INTR_INT_HIGH_EN.value = ((1 << NSIP_HBI_NUM_INTERRUPTS) - 1);
                                                           // enable all interrupts
    cm->INTR_INT_LOW_EN.value = ((1 << NSIP_HBI_NUM_INTERRUPTS) - 1);
                                                           // enable all interrupts
    //  B2H registers
    cm->B2H_FF_FIFO_CTRL.value = NSIP_HBI_B2H_FF_FIFO_CTRL_DEFAULT;
    cm->B2H_CSR_CREDIT_CS.value = NSIP_HBI_B2H_CSR_CREDIT_CS_DEFAULT;
    //   for Band0 input reception
    cm->B2H_CSR_ADDR_TBL[0].value = 0x80000000;            // bit31: valid
                                                           // bit[27:0]: map_byte_addr
    cm->B2H_CSR_ADDR_MASK_TBL[0].value = 0xffff;           // mask
    //   for Band1 input reception
    cm->B2H_CSR_ADDR_TBL[1].value = 0x80010000;            // bit31: valid
                                                           // bit[27:0]: map_byte_addr
    cm->B2H_CSR_ADDR_MASK_TBL[1].value = 0x1ffff;          // mask
    //  H2B registers
    cm->H2B_FF_FIFO_CTRL.value = NSIP_HBI_H2B_FF_FIFO_CTRL_DEFAULT;
    cm->H2B_CREDIT_READY_CS.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT;
    //    band combined samples will exit with tbl[0] parameters
    cm->H2B_BUF_SZ_HW_TBL[0].value = 1;                    // dest_buf_size = (1 + 1) x da_block_size
    cm->H2B_MD_ADDR_LKUP_TBL[0].value = STRM2CIO_2_VEX_DMEM_OFFSET;
                                                           // metadata if enabled will get written to address 0x00 data memory
    cm->H2B_TK_ADDR_LKUP_TBL[0].value = STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate;
                                                           // token will be written to the address 0x80 in data memory of VEX
    cm->H2B_ADDR_LKUP_TBL[0].value = (1 << 31) | HIVE_ADDR_vha2vex_p5_8iq_vbuffer_out;
                                                           // data will be written to the address 0x4000 in vector memory
    cm->H2B_MD_CTRL_TBL[0].value = g_md_control_tbl[dl_clk][out_rate];
                                                           // bit[9:0]: da_block_size
    cm->H2B_TK_ROUTE_LKUP_TBL[0].value = dest_id0;         // route the tokens to rx_vex0
    cm->H2B_MD_ROUTE_LKUP_TBL[0].value = dest_id0;         // route the metadata to rx_vex0
    cm->H2B_ROUTE_LKUP_TBL[0].value = dest_id0;            // route the data to rx_vex0
    cm->H2B_BUF_SZ_HW_TBL[2].value = 1;                    // dest_buf_size = (1 + 1) x da_block_size
    cm->H2B_MD_ADDR_LKUP_TBL[2].value = STRM2CIO_2_VEX_DMEM_OFFSET;
                                                           // metadata if enabled will get written to address 0x00 data memory
    cm->H2B_TK_ADDR_LKUP_TBL[2].value = STRM2CIO_2_VEX_DMEM_OFFSET + HIVE_ADDR_vha2vex_p5_8iq_consumer_sm_gate;
                                                           // token will be written to the address 0x80 in data memory of VEX
    cm->H2B_ADDR_LKUP_TBL[2].value = (1 << 31) | HIVE_ADDR_vha2vex_p5_8iq_vbuffer_out;
                                                           // data will be written to the address 0x4000 in vector memory
    cm->H2B_MD_CTRL_TBL[2].value = g_md_control_tbl[dl_clk][out_rate];
                                                           // bit[9:0]: da_block_size
    cm->H2B_TK_ROUTE_LKUP_TBL[2].value = dest_id1;         // route the tokens to rx_vex1
    cm->H2B_MD_ROUTE_LKUP_TBL[2].value = dest_id1;         // route the metadata to rx_vex1
    cm->H2B_ROUTE_LKUP_TBL[2].value = dest_id1;            // route the data to rx_vex1
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
    if(rv = write_reg_18a(NSIP_HBI_B2H_CSR_ADDR_TBL1_ADR(cm_base_addr),
                          cm->B2H_CSR_ADDR_TBL[1].value,
                          NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK,
                          "NSIP_HBI_B2H_ADDR_TBL1"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_B2H_CSR_ADDR_MASK_TBL1_ADR(cm_base_addr),
                          cm->B2H_CSR_ADDR_MASK_TBL[1].value,
                          NSIP_HBI_B2H_CSR_ADDR_TBL_WR_MASK,
                          "NSIP_HBI_B2H_ADDR_MASK_TBL1"))
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
    if(rv = write_reg_18a(NSIP_HBI_H2B_BUF_SZ_HW_TBL2_ADR(cm_base_addr),
                          cm->H2B_BUF_SZ_HW_TBL[2].value,
                          NSIP_HBI_H2B_BUF_SZ_HW_TBL_WR_MASK,
                          "NSIP_HBI_H2B_BUF_SZ_HW_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_TK_ADDR_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_TK_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_TK_ADDR_LKUP_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_MD_ADDR_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_MD_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_ADDR_LKUP_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_ADDR_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_ADDR_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_ADDR_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_ADDR_LKUP_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_CTRL_TBL2_ADR(cm_base_addr),
                          cm->H2B_MD_CTRL_TBL[2].value,
                          NSIP_HBI_H2B_MD_CTRL_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_CTRL_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_TK_ROUTE_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_TK_ROUTE_LKUP_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_MD_ROUTE_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_MD_ROUTE_LKUP_TBL2"))
        return rv;
    if(rv = write_reg_18a(NSIP_HBI_H2B_ROUTE_LKUP_TBL2_ADR(cm_base_addr),
                          cm->H2B_ROUTE_LKUP_TBL[2].value,
                          NSIP_HBI_H2B_ROUTE_LKUP_TBL_WR_MASK,
                          "NSIP_HBI_H2B_ROUTE_LKUP_TBL2"))
        return rv;

    // VHA_DL_SWG settings
    swg = &(vha->dl_swg);
    swg_base_addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
    printf("HOST: Going to configure the VHA DLSWG registers\n");
    fclk = 983040;                                         // System clock, in khz
    if(dl_clk) fclk = 1474000;                             // 1.5GHz
    fout0 = (fclk / 2);                                    // Min out_rate is 1Gsps (@983.04Mhz) or 1.5Gsps (@1.47GHz),
                                                           //  so take a safe freq of half of that as the carrier output
    fs = ((1 << (out_rate - 3)) * fclk);
    num_cordics = (fs / fclk);
    if(!num_cordics)
    {
        printf("ERROR: Cannot support this rate. Fs should be greater than or equal to Fclk. Exiting test..!");
        return FAILURE;
    }
    if(num_cordics > 4)
    {
        printf("ERROR: Only 4 cordics per SWG are present. Exiting..!\n");
        return FAILURE;
    }
    if((!fout0) || (fout0 > (fs / 2)))
    {
        printf("HOST: Cannot support generating %dKHz carrier frequency. Exiting..!\n", fout0);
        return FAILURE;
    }
    angle_bw_cordics = (360 * fout0) / (fclk * num_cordics);
    incr_angle = (angle_bw_cordics * num_cordics) % 360;
    incr_val = ((1UL << 38) * incr_angle / 360);
    printf("      fclk = %d KHz, fout0 = %d KHz, fs = %d KHz\n", fclk, fout0, fs);
    printf("      Number of Cordics = %d\n", num_cordics);
    printf("      Angle b/w cordics = %d degrees\n", angle_bw_cordics);
    printf("      Incr_val = %x_%x (%d degrees)\n", (incr_val >> 32), (incr_val & ((1UL << 32) - 1)),
                                                    ((incr_val * 360) / (1UL << 38)));
    for(i = 0; i < num_cordics; i++)
    {
          init_angle[i] = (angle_bw_cordics * (num_cordics - i - 1)) % 360;
          init_val[i] = ((1UL << 38) * init_angle[i] / 360);
          printf("      Init value for Cordic-%d is %x_%x (%d degrees)\n", i, (init_val[i] >> 32),
                             (init_val[i] & ((1UL << 32) - 1)), init_angle[i]);
    }

    swg->INCR_UPPER[0].value = ((incr_val >> 32) & 0x3f);
    swg->INCR_LOWER[0].value = (incr_val & ((1UL << 32) - 1));
    for(i = 0; i < num_cordics; i++)
    {
        swg->INIT_UPPER_2D0_INIT_UPPER[i].value = ((init_val[i] >> 32) & 0x3f);
        swg->INIT_LOWER_2D0_INIT_LOWER[i].value = (init_val[i] & ((1UL << 32) - 1));
    }
    swg->EN[0].value = (1 << num_cordics) - 1;             // cordics per swg
    swg->EN_PER_SWG.value = 3;                             // enable swg0 & swg1
    swg->EXT_BYP.value = 0;                                // bypass bfn for swg0 & swg1
    swg->INT_HIGH_EN.value = ((1 << SWG_NUM_INTERRUPTS) - 1);
                                                           // enable all interrupts
    swg->INT_LOW_EN.value = ((1 << SWG_NUM_INTERRUPTS) - 1);
                                                           // enable all interrupts

    // for swg0
    if(rv = write_reg_18a(SWG_INCR_UPPER0_ADR(swg_base_addr),
                          swg->INCR_UPPER[0].value,
                          SWG_INCR_UPPER_WR_MASK,
                          "SWG_INCR_UPPER"))
        return rv;

    if(rv = write_reg_18a(SWG_INCR_LOWER0_ADR(swg_base_addr),
                          swg->INCR_LOWER[0].value,
                          SWG_INCR_LOWER_WR_MASK,
                          "SWG_INCR_LOWER"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER0_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[0].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER1_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[1].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER2_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[2].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER3_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[3].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER3"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER0_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[0].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER1_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[1].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER2_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[2].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER3_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[3].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER3"))
        return rv;

    if(rv = write_reg_18a(SWG_EN0_ADR(swg_base_addr),
                          swg->EN[0].value,
                          SWG_EN_WR_MASK,
                          "SWG_ENABLE"))
        return rv;

    // for swg1
    fout1 = (fclk / 4);
    if(5 == out_rate) fout1 = fout0;
    num_cordics = (fs / fclk);
    if(!num_cordics)
    {
        printf("ERROR: Cannot support this rate. Fs should be greater than or equal to Fclk. Exiting test..!");
        return FAILURE;
    }
    if(num_cordics > 4)
    {
        printf("ERROR: Only 4 cordics per SWG are present. Exiting..!\n");
        return FAILURE;
    }
    if((!fout1) || (fout1 > (fs / 2)))
    {
        printf("HOST: Cannot support generating %dKHz carrier frequency. Exiting..!\n", fout1);
        return FAILURE;
    }
    angle_bw_cordics = (360 * fout1) / (fclk * num_cordics);
    incr_angle = (angle_bw_cordics * num_cordics) % 360;
    incr_val = ((1UL << 38) * incr_angle / 360);
    printf("      fclk = %d KHz, fout1 = %d KHz, fs = %d KHz\n", fclk, fout1, fs);
    printf("      Number of Cordics = %d\n", num_cordics);
    printf("      Angle b/w cordics = %d degrees\n", angle_bw_cordics);
    printf("      Incr_val = %x_%x (%d degrees)\n", (incr_val >> 32), (incr_val & ((1UL << 32) - 1)),
                                                    ((incr_val * 360) / (1UL << 38)));
    for(i = 0; i < num_cordics; i++)
    {
          init_angle[i] = (angle_bw_cordics * (num_cordics - i - 1)) % 360;
          init_val[i] = ((1UL << 38) * init_angle[i] / 360);
          printf("      Init value for Cordic-%d is %x_%x (%d degrees)\n", i, (init_val[i] >> 32),
                             (init_val[i] & ((1UL << 32) - 1)), init_angle[i]);
    }

    swg->INCR_UPPER[1].value = ((incr_val >> 32) & 0x3f);
    swg->INCR_LOWER[1].value = (incr_val & ((1UL << 32) - 1));
    for(i = 0; i < num_cordics; i++)
    {
        swg->INIT_UPPER_2D1_INIT_UPPER[i].value = ((init_val[i] >> 32) & 0x3f);
        swg->INIT_LOWER_2D1_INIT_LOWER[i].value = (init_val[i] & ((1UL << 32) - 1));
    }
    swg->EN[1].value = (1 << num_cordics) - 1;             // cordics per swg

    if(rv = write_reg_18a((SWG_INCR_UPPER1_ADR(swg_base_addr)),
                          swg->INCR_UPPER[1].value,
                          SWG_INCR_UPPER_WR_MASK,
                          "SWG_INCR_UPPER"))
        return rv;

    if(rv = write_reg_18a((SWG_INCR_LOWER1_ADR(swg_base_addr)),
                          swg->INCR_LOWER[1].value,
                          SWG_INCR_LOWER_WR_MASK,
                          "SWG_INCR_LOWER"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_UPPER_2D1_INIT_UPPER0_ADR(swg_base_addr)),
                          swg->INIT_UPPER_2D1_INIT_UPPER[0].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D1_INIT_UPPER0"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_UPPER_2D1_INIT_UPPER1_ADR(swg_base_addr)),
                          swg->INIT_UPPER_2D1_INIT_UPPER[1].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D1_INIT_UPPER1"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_UPPER_2D1_INIT_UPPER2_ADR(swg_base_addr)),
                          swg->INIT_UPPER_2D1_INIT_UPPER[2].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D1_INIT_UPPER2"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_UPPER_2D1_INIT_UPPER3_ADR(swg_base_addr) + 0x40),
                          swg->INIT_UPPER_2D1_INIT_UPPER[3].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D1_INIT_UPPER3"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_LOWER_2D1_INIT_LOWER0_ADR(swg_base_addr)),
                          swg->INIT_LOWER_2D1_INIT_LOWER[0].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D1_INIT_LOWER0"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_LOWER_2D1_INIT_LOWER1_ADR(swg_base_addr)),
                          swg->INIT_LOWER_2D1_INIT_LOWER[1].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D1_INIT_LOWER1"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_LOWER_2D1_INIT_LOWER2_ADR(swg_base_addr)),
                          swg->INIT_LOWER_2D1_INIT_LOWER[2].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D1_INIT_LOWER2"))
        return rv;

    if(rv = write_reg_18a((SWG_INIT_LOWER_2D1_INIT_LOWER3_ADR(swg_base_addr)),
                          swg->INIT_LOWER_2D1_INIT_LOWER[3].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D1_INIT_LOWER3"))
        return rv;

    if(rv = write_reg_18a((SWG_EN1_ADR(swg_base_addr)),
                          swg->EN[1].value,
                          SWG_EN_WR_MASK,
                          "SWG_ENABLE"))
        return rv;

    if(rv = write_reg_18a(SWG_EN_PER_SWG_ADR(swg_base_addr),
                          swg->EN_PER_SWG.value,
                          SWG_EN_PER_SWG_WR_MASK,
                          "SWG_EN_PER_SWG"))
        return rv;

    if(rv = write_reg_18a(SWG_EXT_BYP_ADR(swg_base_addr),
                          swg->EXT_BYP.value,
                          SWG_EXT_BYP_WR_MASK,
                          "SWG_EXT_BYP"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_HIGH_EN_ADR(swg_base_addr),
                          swg->INT_HIGH_EN.value,
                          SWG_INT_HIGH_EN_WR_MASK,
                          "SWG_INT_HIGH_EN"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_LOW_EN_ADR(swg_base_addr),
                          swg->INT_LOW_EN.value,
                          SWG_INT_LOW_EN_WR_MASK,
                          "SWG_INT_LOW_EN"))
        return rv;

    // VHA_REG block settings
    vha_reg = &(vha->vha_reg);
    vha_reg_base_addr = vha_base_addr + VHA_REG_OFFSET;
    vha_reg->VHA_CFG.value = 0x3fc | dl_clk;               // bit[9:8]: crux_clock_enable,
                                                           // bit[3:2]: dl_clock_enable,
                                                           // bit0: dl_clock_select (0->983MHz, 1->1GHz)
    vha_reg->VHA_DL_IF_CFG.value = (0x33 << (ant_num * 10));
                                                           // bit[15:12]: dl_ant1_band1_af_gate,
                                                           // bit[11:8]: dl_ant1_band0_af_gate,
                                                           // bit[7:4]: dl_ant0_band1_af_gate
                                                           // bit[3:0]: dl_ant0_band0_af_gate
                                                           // Combined trigger for band0 and band1
    vha_reg->VHA_DL_SWG_CFG.value = (0x33 << (ant_num * 2));
                                                           // bit[7:4]: dl_swg1_af_gate
                                                           // bit[3:0]: dl_swg0_af_gate
    vha_reg->VHA_DL_CTL.value = (3 << 4) | (3 << (ant_num * 2));
                                                           // bit[5:4]: enable swg0 & swg1
                                                           // bit[3:0]: dl_ififo_enable ant0/1_band0 & band1
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
    if(rv = write_reg_18a(VHA_DL_SWG_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_SWG_CFG.value,
                          VHA_DL_SWG_CFG_WR_MASK,
                          "VHA_DL_SWG_CFG"))
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
    uint32_t rx_vex0,
    uint32_t rx_vex1,
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
    if(rv = vex_strm2cio_check_status(rx_vex0))
        e_code |= 4;                                       // FAILURE code for STRM2CIO status wrong
    if(rv = vex_strm2cio_check_status(rx_vex1))
        e_code |= 8;                                       // FAILURE code for STRM2CIO status wrong


    test_show_regs(tx_vex, rx_vex0, rx_vex1, vha_num, ant_num);

    return e_code;
}

/*
 * function    : test_show_regs()
 * @brief      : this function all the registers of VHA and VEX streaming interfaces
 *
 */
void test_show_regs(
    uint32_t tx_vex,
    uint32_t rx_vex0,
    uint32_t rx_vex1,
    uint32_t vha_num,
    uint32_t ant_num)
{
    vha_show_regs(vha_num, ant_num);                       // VHA registers
    vex_cio2strm_show_regs(tx_vex);                        // CIO2STRM registers of tx_vex
    vex_strm2cio_show_regs(rx_vex0);                       // STRM2CIO registers of rx_vex
    vex_strm2cio_show_regs(rx_vex1);                       // STRM2CIO registers of rx_vex
}

// End of file
