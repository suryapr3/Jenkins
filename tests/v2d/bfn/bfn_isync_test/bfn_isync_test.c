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
/**
 * @file    bfn_isync_test.c
 * @details 1. This TC validates the various follower BFN commands.
   @TC Description:
        1. All the configuration will be done from RCS Ax core for the given V2D instance.
        2. From the RCS send the follower BFN commands and store the corresponding response
           to RCS shared memory.
        3. Read the results from HOST and validate either TC is pass or fail.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

#define CLK_PER_1US_983M (983)
#define CLK_PER_1US_1P5  (1475)
#define PRESET_VALUE 0x1000050
#define PRESET_TOLERANCE    0x200
#define SYNC_ADJUSTMENT_VALUE   0x4000004
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
extern int g_abc_build_version;
// used for handshaing between HOST and RCS
int g_rsm_buffer[] = {0x23FFEC, 0x23FFF0, 0x23FFF4, 0x23FFF8, 0x23FFFC};

// may change once new functions are added, check .map file
int g_dcode_buffer[] = {0xE4030, 0xE4034, 0xE4038, 0xE403c};

int main(int argc, const char *argv[])
{
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    int rv = 0, v2d_num = 0, lc = 0, loop_wait_count = 0, drf_clock = 0, initial_difference = 0;
    uint32_t rd_wr_value[32] = {0};
    int rcs_host_param[4] = {0}; // corresponds to v2d_num and drf clock
    int error_limit = 0, clk_per_1us = 0;

    init(); // Initializing the srp

    /*This is specific to FPGA*/
    follower_bfn_wa_fpga();

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    v2d_num = argv[0];
    drf_clock = argv[1];

    printf ("INFO: argv[0] : %d = v2d_num", v2d_num);
    printf ("INFO: argv[1] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);

    if (CLOCK_983M == drf_clock)
    {
        clk_per_1us = CLK_PER_1US_983M;
    }
    else
    {
        clk_per_1us = CLK_PER_1US_1P5;
    }

    error_limit = 3 * clk_per_1us;

    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];

    rcs_config(&rcs_params);

    rcs_host_param[0] = v2d_num;
    rcs_host_param[1] = drf_clock;

    /*Load the parameters to RCS RSM memory*/
    write_mem_18a(RSM_MEM_OFFSET, ARRAY_SIZE(rcs_host_param), rcs_host_param, "RCS_HOST_PARAM");

    // Clear the flags
    rd_wr_value[0] = 0;
    write_mem_18a(g_rsm_buffer[0], 4, &rd_wr_value[0], "RSM_FLAGS");

    // start RCS core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");

    // wait for handshake from ax - bfn_start() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the BFN_START test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);
    } while(rd_wr_value[0] != 0xC000C001);

    read_mem_18a(g_dcode_buffer[0], 7, rd_wr_value, "DCODE_BUFFER");

    printf("TC1: BFN start test");
    printf("BFN live counter value : %d", rd_wr_value[0]);
    printf("BFN live counter after 20us : %d", rd_wr_value[1]);
    printf("BFN live counter after 40us : %d", rd_wr_value[2]);
    printf("BFN live counter after 60us : %d", rd_wr_value[3]);
    printf("BFN live counter after 100us : %d", rd_wr_value[4]);
    printf("BFN live counter after 180us : %d", rd_wr_value[5]);
    printf("BFN live counter after 1.18ms : %d", rd_wr_value[6]);

    if (((rd_wr_value[1] - rd_wr_value[0]) - (20 * clk_per_1us) > error_limit) ||
            ((rd_wr_value[2] - rd_wr_value[0]) - (40 * clk_per_1us) > error_limit) ||
            ((rd_wr_value[3] - rd_wr_value[0]) - (60 * clk_per_1us) > error_limit) ||
            (((rd_wr_value[4] - rd_wr_value[0]) - (100 * clk_per_1us)) > error_limit) ||
            ((rd_wr_value[5] - rd_wr_value[0]) - (180 * clk_per_1us) > error_limit) ||
            ((rd_wr_value[6] - rd_wr_value[0]) - (1180 * clk_per_1us) > error_limit))
    {
        printf("ERROR: BFN live counter test fail");
        rv |= 1;
    }
    else
    {
        printf("HOST: BFN live counter test pass");
    }

    //clear the dram
    rd_wr_value[0] = 0;
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test to start : BFN_CAPTURE_CMD
    rd_wr_value[0] = 0xC000D001;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - bfn_test_capture_cmd() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the CAPTURE_CMD test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C002);

    read_mem_18a(g_dcode_buffer[0], 8, rd_wr_value, "DCODE_BUFFER");

    printf("TC2: BFN capture command test");
    printf("BFN live counter after 10us RCS: %d, V2D: %d", rd_wr_value[0], rd_wr_value[1]);
    printf("BFN live counter after 30us RCS: %d, V2D: %d", rd_wr_value[2], rd_wr_value[3]);
    printf("BFN live counter after 70us RCS: %d, V2D: %d", rd_wr_value[4], rd_wr_value[5]);
    printf("BFN live counter after 130us RCS: %d, V2D: %d", rd_wr_value[6], rd_wr_value[7]);

    if ((rd_wr_value[0] != rd_wr_value[1]) ||
            (rd_wr_value[2] != rd_wr_value[3]) ||
            (rd_wr_value[4] != rd_wr_value[5]) ||
            (rd_wr_value[6] != rd_wr_value[7]))
    {
        printf("WARNING: Main BFN and V2D BFN are not in sync");
    }

    if ((rd_wr_value[1] - (10 * clk_per_1us) > error_limit) ||
            (rd_wr_value[3] - (30 * clk_per_1us) > error_limit) ||
            (rd_wr_value[5] - (70 * clk_per_1us) > error_limit) ||
            ((rd_wr_value[7] - (130 * clk_per_1us)) > error_limit))
    {
        printf("ERROR: BFN capture command test fail");
        rv |= 1;
    }
    else
    {
        printf("BFN capture command test pass");
    }

    //clear the dram
    rd_wr_value[0] = 0;
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_test
    rd_wr_value[0] = 0xC000D002;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - positive_adjustment_cmd() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the POSTIVIE_ADJUSTMENT_CMD test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C003);

    read_mem_18a(g_dcode_buffer[0], 8, rd_wr_value, "DCODE_BUFFER");

    printf("TC3: BFN postive adjustment command test");
    printf("BFN live counter before first adjustment RCS: %d, V2D: %d", rd_wr_value[0], rd_wr_value[1]);
    printf("BFN live counter after after first adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[2], rd_wr_value[3]);
    printf("BFN live counter after after second adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[4], rd_wr_value[5]);
    printf("BFN live counter after after third adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[6], rd_wr_value[7]);

    initial_difference = rd_wr_value[1] - rd_wr_value[0];

    if (((rd_wr_value[3] - rd_wr_value[2]) == initial_difference + 50) &&
            ((rd_wr_value[5] - rd_wr_value[4]) == initial_difference + 100) &&
            ((rd_wr_value[7] - rd_wr_value[6]) == initial_difference + 150))
    {
        printf("Follower BFN positive adjustment verification pass");
    }
    else
    {
        printf("ERROR:Follower BFN positive adjustment verification fail");
        rv |= 1;
    }

    //clear the dram
    rd_wr_value[0] = 0;
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_test
    rd_wr_value[0] = 0xC000D003;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - bfn_negative_adjustment_cmd() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the BFN_NEGATIVE_ADJUSTMENT test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C004);

    read_mem_18a(g_dcode_buffer[0], 8, rd_wr_value, "DCODE_BUFFER");

    printf("TC5: BFN negative adjustment command test");
    printf("BFN live counter before first adjustment RCS: %d, V2D: %d", rd_wr_value[0], rd_wr_value[1]);
    printf("BFN live counter after after first adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[2], rd_wr_value[3]);
    printf("BFN live counter after after second adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[4], rd_wr_value[5]);
    printf("BFN live counter after after third adjustment of 50 cycles RCS: %d, V2D: %d", rd_wr_value[6], rd_wr_value[7]);

    initial_difference = rd_wr_value[1] - rd_wr_value[0];

    if (((rd_wr_value[3] - rd_wr_value[2]) == initial_difference - 50) &&
            ((rd_wr_value[5] - rd_wr_value[4]) == initial_difference - 100) &&
            ((rd_wr_value[7] - rd_wr_value[6]) == initial_difference - 150))
    {
        printf("Follower BFN negetive adjustment verification pass");
    }
    else
    {
        printf("ERROR:Follower BFN negetive adjustment verification fail");
        rv |= 1;
    }

    //clear the dram
    rd_wr_value[0] = 0;
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_test
    rd_wr_value[0] = 0xC000D004;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - bfn_preset_cmd() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the PRESET_CMD test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C005);

    read_mem_18a(g_dcode_buffer[0], 8, rd_wr_value, "DCODE_BUFFER");

    printf("TC3: BFN preset command test");
    printf("BFN live counter before preset RCS: %d, V2D: %d", rd_wr_value[0], rd_wr_value[1]);
    printf("BFN live counter after first preset RCS: %d, V2D: %d", rd_wr_value[2], rd_wr_value[3]);
    printf("BFN live counter after second preset RCS: %d, V2D: %d", rd_wr_value[4], rd_wr_value[5]);
    printf("BFN live counter after third preset RCS: %d, V2D: %d", rd_wr_value[6], rd_wr_value[7]);

    if (rd_wr_value[2] == rd_wr_value[3])
    {
        printf("ERROR: preset test, both RCS and V2D have same value");
        rv |= 1;
    }

    if (((rd_wr_value[3] - PRESET_VALUE) > PRESET_TOLERANCE) ||
            ((rd_wr_value[5] - PRESET_VALUE) > PRESET_TOLERANCE) ||
            ((rd_wr_value[7] - PRESET_VALUE) > PRESET_TOLERANCE))
    {
        printf("ERROR: BFN preset command test fail");
    }
    else
    {
        printf("BFN preset command test pass");
    }

    //clear the dram
    rd_wr_value[0] = 0;
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_test
    rd_wr_value[0] = 0xC000D005;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    loop_wait_count = 0;
    // wait for handshake from ax - bfn_sync_adj_cmd() test
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the PRESET_CMD test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C006);

    read_mem_18a(g_dcode_buffer[0], 8, rd_wr_value, "DCODE_BUFFER");

    printf("BFN sync_adj command test");
    printf("BFN live counter before sync_adj RCS: %d, V2D: %d", rd_wr_value[0], rd_wr_value[1]);
    printf("BFN live counter after 10us RCS: %d, V2D: %d", rd_wr_value[2], rd_wr_value[3]);
    printf("BFN live counter after 20us RCS: %d, V2D: %d", rd_wr_value[4], rd_wr_value[5]);
    printf("BFN live counter after 30us RCS: %d, V2D: %d", rd_wr_value[6], rd_wr_value[7]);

    if (rd_wr_value[7] > SYNC_ADJUSTMENT_VALUE)
    {
        printf("SYNC_ADJ cmd verification pass");
    }
    else
    {
        printf("ERROR: SYNC_ADJ cmd verification fail");
    }

    if (0 == rv)
    {
        printf("ALL Follower BFN command verification is successful");
    }

    return rv;
}
