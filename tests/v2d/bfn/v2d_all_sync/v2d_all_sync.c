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
 * @file    v2d_all_sync.c
 * @details 1. This TC validates the sync of all V2D follower commands with RCS.
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

#define CLK_PER_1US (983)
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

/**
 * @brief           Function flag update
 * @param [in]      none
 * @return          status value
 */
int bfn_start_test_check(int *rd_wr_value)
{
    int i = 0, rv = 0;

    //for (i = 0; i < 10; i = (i + 5))
    {
        if ((rd_wr_value[i + 1] != rd_wr_value[i + 2]) || (rd_wr_value[i + 1] != rd_wr_value[i + 3]) ||
                (rd_wr_value[i + 1] != rd_wr_value[i + 4]) || (rd_wr_value[i + 2] != rd_wr_value[i + 3]) ||
                (rd_wr_value[i+ 2] != rd_wr_value[i + 4]) || (rd_wr_value[i + 3] != rd_wr_value[i + 4]))
        {
            rv |= 1;
        }

    }

    return rv;
}

int main(int argc, const char *argv[])
{
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    int rv = 0, v2d_num = 0, lc = 0, loop_wait_count = 0, drf_clock = 0;
    uint32_t rd_wr_value[32] = {0};
    int rcs_host_param[4] = {0}; // corresponds to v2d_num and drf clock

    init(); // Initializing the srp

    /*This is specific to FPGA*/
    follower_bfn_wa_fpga();

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    drf_clock = argv[0];

    printf ("INFO: argv[0] : %d = drf_clock %s", drf_clock, drf_clock_str[drf_clock]);


    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];

    rcs_config(&rcs_params);

    rcs_host_param[0] = drf_clock;

    /*Load the parameters to RCS RSM memory*/
    write_mem_18a(RSM_MEM_OFFSET, ARRAY_SIZE(rcs_host_param), rcs_host_param, "RCS_HOST_PARAM");

    // Clear the flags
    memset(rd_wr_value, 0, sizeof(rd_wr_value));
    write_mem_18a(g_rsm_buffer[0], 4, &rd_wr_value[0], "RSM_FLAGS");

    // start RCS core0
    rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    printf("HOST:RCS core was triggered");

    // wait for handshake from ax - bfn_sync_ver() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the BFN_SYNC_VER test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);
    } while(rd_wr_value[0] != 0xC000C001);

    read_mem_18a(g_dcode_buffer[0], 10, rd_wr_value, "DCODE_BUFFER");

    printf("BFN sync ver test");
    printf("After RESET RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[0], rd_wr_value[1], rd_wr_value[2], rd_wr_value[3], rd_wr_value[4]);
    printf("After 40 us RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[5], rd_wr_value[6], rd_wr_value[7], rd_wr_value[8], rd_wr_value[9]);

    if (bfn_start_test_check(rd_wr_value + 5))
    {
        printf("WARNING: V2D values are not in sync");
    }

    //clear the dram
    memset(rd_wr_value, 0, sizeof(rd_wr_value));
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_test
    rd_wr_value[0] = 0xC000D001;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - bfn_induce_offset() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the positive adjustment test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C002);

    read_mem_18a(g_dcode_buffer[0], 10, rd_wr_value, "DCODE_BUFFER");

    printf("BFN add offset test");
    printf("Beofe adding offset RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[0], rd_wr_value[1], rd_wr_value[2], rd_wr_value[3], rd_wr_value[4]);
    printf("After adding offset of 50 count for V2D3 , RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[5], rd_wr_value[6], rd_wr_value[7], rd_wr_value[8], rd_wr_value[9]);

    if (rd_wr_value[5] == rd_wr_value[9])
    {
        printf("ERROR: No offset was seen for V2D3 with respect to RCS");
        rv |= 1;
    }

    //clear the dram
    memset(rd_wr_value, 0, sizeof(rd_wr_value));
    write_mem_18a(g_dcode_buffer[0], 32, &rd_wr_value[0], "DCODE_BUFFER");

    // trigger next test bfn_correction
    rd_wr_value[0] = 0xC000D002;
    write_mem_18a(g_rsm_buffer[4], 1, &rd_wr_value[0], "rsm_com_shared_flag");

    // wait for handshake from ax - bfn_correction() test
    loop_wait_count = 0;
    do
    {
        rd_wr_value[0] = read_reg_18a(g_rsm_buffer[0], "SRAM_AX_FLAG");

        if (loop_wait_count >= 100)
        {
            printf("WARNING: breaking the positive adjustment test loop before RCS handshake");
            break;
        }

        loop_wait_count++;
        usleep(10000);

    } while(rd_wr_value[0] != 0xC000C003);


    read_mem_18a(g_dcode_buffer[0], 10, rd_wr_value, "DCODE_BUFFER");

    printf("BFN correction test");
    printf("Beofe correction RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[0], rd_wr_value[1], rd_wr_value[2], rd_wr_value[3], rd_wr_value[4]);
    printf("After correction RCS: %d, V2D0: %d, V2D1: %d, V2D2: %d, V2D3: %d",
            rd_wr_value[5], rd_wr_value[6], rd_wr_value[7], rd_wr_value[8], rd_wr_value[9]);

    if (bfn_start_test_check(rd_wr_value + 5))
    {
        printf("ERROR: No correction happened for V2D instances with respect to RCS");
        rv |= 1;
    }

    if (0 == rv)
    {
        printf("ALL Follower BFN command verification is successful");
    }


    return rv;
}
