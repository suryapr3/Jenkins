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
 * @file    ax_v2d_bfn_all_sync.c
 * @brief   Code for validating all the V2D follower BFN commands.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_event.h"
#include "com_shared_memory.h"
#include "rcs_gpreg.h"

#include "bfn_csr.h"
#include "av2d_csr.h"
#include "nsip_hbi.h"
#include "ve32_bp_config_dmem.h"
#include "av2d_axi4.h"
#include "rcs_timer_gpreg.h"
#include "bfn_test.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32
#define ADJUSTMENT_VALUE 50

/* Lower Count value = (TEN_MS_COUNT - adjustment value) = (0x960000 - 50) = 0x65ffce
 * upper count value = -1 = FF
 * */
#define NEGETIVE_ADJUSTMENT_VALUE 0xFF95FFCE
#define PRESET_VALUE 0x1000050
#define V2D_INSTANCES   8
#define AVAILABLE_V2D_INSTANCES 4
#define V2D_BFN_BASE(v2d_num)    (V2D0_BFN_CSR_BASE + (v2d_num) * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE))

#define FOLLOWER_INCREMENT_CMD     0x00000003
#define FOLLOWER_NORMAL_CMD        0x00000000
#define BFN_COM_ISYNC_CLEAR        0x00000000
#define BFN_COM_ISYNC_TRIG         0x00000080
#define BFN_COM_ISYNC_LOAD         0x00000100
#define BFN_COM_ISYNC_READ         0x00000000
#define BFN_COM_ISYNC_VAL_DEF      0x00000000
#define BFN_COM_ISYNC_VAL_INC      0x00000010
#define BFN_COM_ISYNC_VAL_DEC      0x00000020
#define BFN_COM_ISYNC_VAL_CMD      0x00000030
#define BFN_COM_ISYNC_CMD_INC_LCNT 0x00000000
#define BFN_COM_ISYNC_CMD_INIT     0x00000002
#define BFN_COM_ISYNC_CMD_PRESET   0x00000001
#define BFN_COM_ISYNC_CMD_RESET    0x00000003
#define BFN_COM_ISYNC_CMD_INC_PRE  0x00000003
#define BFN_COM_ISYNC_CMD_ADJ      0x00000005
#define BFN_COM_ISYNC_CMD_CAP      0x00000007
#define BFN_COM_ISYNC_CMD          (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_CMD)   // 0x000000B0
#define BFN_COM_SYNC_PRESET        (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_PRESET) // 0x000000B1
#define BFN_COM_SYNC_INIT          (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_INIT)   // 0x000000B2
#define BFN_COM_SYNC_RESET         (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_RESET)  // 0x000000B3
#define BFN_COM_SYNC_CAP           (BFN_COM_ISYNC_CMD | BFN_COM_ISYNC_CMD_CAP)    // 0x000000B7
#define BFN_COM_SYNC_INC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_INC)   // 0x00000090
#define BFN_COM_SYNC_DEC           (BFN_COM_ISYNC_TRIG | BFN_COM_ISYNC_VAL_DEC)   // 0x000000A0
#define TIMESYNC_CTRL   0x00030031
#define TEN_MS_CNT_VALUE_1P5      (0xE0FFFF)
/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile uint32_t rsm_buf[TEST_BUFF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t write_rsm[TEST_BUFF_SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t dram_buff[TEST_BUFF_SIZE]  __attribute__((section(".dram0.data")));

volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));

int g_v2d_base = 0;
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    uint32_t v2d_num = 0, drf_clock = 0;
    int lc = 0, vex_num = 0, v2d_index = 0, wait_cnt = 0;

    drf_clock = rsm_buf[0];

    if (!com_shared_mem_wait_for_ready ())
    {
        // Update RSM flag for handshake with host code
        rsm_ax_shared_flag=0xDEADBEEF;
        wait_cnt++;
    }
    rsm_ax_shared_flag=0xC000C0C0;

    /*Function for BFN sync functionality*/
    bfn_sync_ver();

    // trigger host for bfn_sync ver test results check
    rsm_ax_shared_flag = 0xC000C001;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D001);

    /*Function to introduce the offset*/
    bfn_introduce_offset();

    rsm_ax_shared_flag = 0xC000C002;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D002);

    /*function to perform the correction*/
    bfn_correction();

    rsm_ax_shared_flag = 0xC000C003;

    restore_default();

    return (0);
}

/**
 * @brief           Function initializing the Follwer BFN with exteral sync pulse
 * @param [in]      None
 * @return          status
 */
uint32_t bfn_sync_ver()
{
    uint32_t rv = 0, v2d_num = 0, buff_index = 0, drf_clock = 0;

    drf_clock = rsm_buf[0];

    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    // soft reset Follower V2D BFN
    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x1;
        INTRINSIC_BARRIER;
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x0;
        INTRINSIC_BARRIER;
    }

    if (drf_clock)
    {
        RCS_TIMER_GPREG->TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = 0x32; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // Set the SYSREF
    RCS_TIMER_GPREG -> OPPS_VAL_TIMESYNC_CTRL.value = TIMESYNC_CTRL;    //0x00030031
    INTRINSIC_BARRIER;

    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0;
        INTRINSIC_BARRIER;

        if (drf_clock)
        {
            ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
            INTRINSIC_BARRIER;
        }

        // Program the CTRL command for follower BFN to full load
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // preload BFN values used with SYSREF load
    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.LOAD_READ = 1;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG -> ICTRL.LOAD_READ = 0x1;
    INTRINSIC_BARRIER;

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

    com_timing_wait_ns (40000); //40us

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

    return rv;
}

/**
 * @brief           Function for introducing the offset to one of the followers
 * @param [in]      None
 * @return          None
 */
void bfn_introduce_offset()
{

    int v2d_num = 0, buff_index = 0;

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);
        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

    // Program the CTRL command for initialize the follwer BFN
    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = ADJUSTMENT_VALUE;
        INTRINSIC_BARRIER;
    }

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    com_timing_wait_ns (10000); //10us

    /*Trigger the correction command to only one follwer and for all other issue default command*/
    for (v2d_num = 0; v2d_num < (AVAILABLE_V2D_INSTANCES - 1); v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_NORMAL_CMD;  //0x0
        INTRINSIC_BARRIER;
    }

    g_v2d_base = V2D_BFN_BASE(v2d_num);

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;  //0x3
    INTRINSIC_BARRIER;

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);
        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

}

/**
 * @brief           Function to perform the correction
 * @param [in]      None
 * @return          None
 */
void bfn_correction()
{

    uint32_t v2d_num = 0, buff_index = 0, adjustment_value[AVAILABLE_V2D_INSTANCES] = {0};
    uint32_t rcs_timestamp_value, v2d_timestamp_value, drf_clock = 0;

    drf_clock = rsm_buf[0];

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);
        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

    rcs_timestamp_value = (RCS_TIMER_GPREG) -> BFN_CNT_VAL2_REG0.value;

    /*Calculate the adjustment values and preload the values with INIT command*/
    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        v2d_timestamp_value = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

        if (v2d_timestamp_value > rcs_timestamp_value)
        {
            adjustment_value[v2d_num] = v2d_timestamp_value - rcs_timestamp_value;
            if (drf_clock)
            {
                ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0xFF000000 | ((TEN_MS_CNT_VALUE_1P5 + 1)- adjustment_value[v2d_num]);
            }
            else
            {
                ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0xFF000000 | ((BFN_CSR_AW_ISYNC_TEN_MS_CNT_DEFAULT + 1)- adjustment_value[v2d_num]);
            }
            INTRINSIC_BARRIER;
        }
        else
        {
            adjustment_value[v2d_num] = rcs_timestamp_value - v2d_timestamp_value;
            ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = adjustment_value[v2d_num];
            INTRINSIC_BARRIER;
        }

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    com_timing_wait_ns (10000); //10us

    /*Perform the correction with increment command for the required follower BFN's*/
    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);

        if (adjustment_value[v2d_num])
        {
            ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;  //0x3
            INTRINSIC_BARRIER;
        }
        else
        {
            ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_NORMAL_CMD;  //0x3
            INTRINSIC_BARRIER;
        }
    }

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_all_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);
        dram_buff[buff_index++] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

}

/**
 * @brief           Function for restoring the default values of follower BFN
 * @param [in]      None
 * @return          None
 */
void restore_default()
{
    int v2d_num = 0;

    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    for (v2d_num = 0; v2d_num < AVAILABLE_V2D_INSTANCES; v2d_num++)
    {
        // soft reset Follower V2D BFN
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x1;
        INTRINSIC_BARRIER;
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x0;
        INTRINSIC_BARRIER;

        // Program the CTRL command for follower BFN
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_LCNT_INC.value = 0x1;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = BFN_CSR_AW_ISYNC_TEN_MS_CNT_DEFAULT;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CNT_ADJ.value = BFN_CSR_AW_ISYNC_CNT_ADJ_DEFAULT;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;
}

/**
 * @brief           Function for sending the BFN capture command
 * @param [in]      None
 * @return          None
 */
void v2d_bfn_all_capture()
{
    int v2d_num = 0;

    // Program the CTRL command for follower BFN to capture
    for (v2d_num = 0; v2d_num < 4; v2d_num++)
    {
        g_v2d_base = V2D_BFN_BASE(v2d_num);
        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_CAP;  //0x7
        INTRINSIC_BARRIER;
    }

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // 0xB7; // ISYNC + capture command
    INTRINSIC_BARRIER;

}
// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
