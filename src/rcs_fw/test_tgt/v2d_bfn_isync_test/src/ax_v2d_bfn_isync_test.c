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
 * @file    ax_v2d_bfn.c
 * @brief   Code for validating the follower BFN commands.
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
#define FOLLOWER_PRESET_VALUE 0x1000050

#define FOLLOWER_INCREMENT_CMD     0x00000003
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
#define TIMESYNC_CTRL             (0x00050031)
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

    uint32_t v2d_num = 0;
    int lc = 0, vex_num = 0, v2d_index = 0, wait_cnt = 0;

    v2d_num = rsm_buf[0];

    switch (v2d_num)
    {
        case 0:
            g_v2d_base = V2D0_BFN_CSR_BASE;
            break;
        case 1:
            g_v2d_base = V2D1_BFN_CSR_BASE;
            break;
        case 2:
            g_v2d_base = V2D2_BFN_CSR_BASE;
            break;
        case 3:
            g_v2d_base = V2D3_BFN_CSR_BASE;
            break;
        case 4:
            g_v2d_base = V2D4_BFN_CSR_BASE;
            break;
        case 5:
            g_v2d_base = V2D5_BFN_CSR_BASE;
            break;
        case 6:
            g_v2d_base = V2D6_BFN_CSR_BASE;
            break;
        case 7:
            g_v2d_base = V2D7_BFN_CSR_BASE;
            break;
    }

    if (!com_shared_mem_wait_for_ready ())
    {
        // Update RSM flag for handshake with host code
        rsm_ax_shared_flag=0xDEADBEEF;
        wait_cnt++;
    }
    rsm_ax_shared_flag=0xC000C0C0;

    /*Function starts the BFN functionality*/
    bfn_start();

    // trigger host for bfn_start test results check
    rsm_ax_shared_flag = 0xC000C001;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D001);

    /*Function to test the capture command*/
    bfn_test_capture_cmd();

    rsm_ax_shared_flag = 0xC000C002;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D002);

    /*function to test the postive adjustment cmd*/
    bfn_positive_adjustment_cmd();

    rsm_ax_shared_flag = 0xC000C003;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D003);

    /*function to test the negative adjustment cmd*/
    bfn_negative_adjustment_cmd();

    rsm_ax_shared_flag = 0xC000C004;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D004);

    /*function to test the preset cmd*/
    bfn_test_preset_cmd();
    rsm_ax_shared_flag = 0xC000C005;

    // handshake with host for starting next test
    wait_cnt = 0;
    do
    {
        wait_cnt++;
    } while(rsm_com_shared_flag != 0xC000D005);

    /*function to validate the sync adjustment cmd*/
    bfn_sync_adj_cmd();
    rsm_ax_shared_flag = 0xC000C006;

    restore_default();

    return (0);
}

/**
 * @brief           Function initializing the Follwer BFN with exteral sync pulse
 * @param [in]      None
 * @return          status
 */
uint32_t bfn_start()
{
    uint32_t rv = 0, drf_clock = 0;

    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    // soft reset Follower V2D BFN
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG -> INC_PRE_REG0.value = RCS_TIMER_GPREG_INC_PRE_REG0_DEFAULT;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG -> INC_PRE_REG1.value = RCS_TIMER_GPREG_INC_PRE_REG1_DEFAULT;
    INTRINSIC_BARRIER;

    // Program the CTRL command for follower BFN to full load
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0x0;
    INTRINSIC_BARRIER;

    /*Program the TEN_MS_CNT for 1P5G clock*/

    if (drf_clock)
    {
        RCS_TIMER_GPREG->TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;

    //read BFN count
    dram_buff[0] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (20000); //20us

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;

    //read BFN count
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (20000); //20us + 20us
    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;

    //read BFN count
    dram_buff[2] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (20000); //40us + 20us

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;
    //read BFN count
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (40000); //60us + 40us

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;
    //read BFN count
    dram_buff[4] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (80000); //100us + 80us

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;
    //read BFN count
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    com_timing_wait_ns (1000000); //180us + 1000us

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;
    //read BFN count
    dram_buff[6] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value;

    return rv;
}

/**
 * @brief           Function for presetting the both Main (to it's default value which is zero) and Follower BFN
 *                  to predefined value
 * @param [in]      None
 * @return          status
 */
uint32_t bfn_test_preset_cmd()
{
    uint32_t rv = 0;

    // Program the CTRL command for follower BFN
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = FOLLOWER_PRESET_VALUE;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG -> INC_PRE_REG0.value = RCS_TIMER_GPREG_INC_PRE_REG0_DEFAULT;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG -> INC_PRE_REG1.value = RCS_TIMER_GPREG_INC_PRE_REG1_DEFAULT;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG -> ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    //capture BFN count
    v2d_bfn_capture();

    dram_buff[0] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (10000); //10us

    // Program the CTRL command for follower BFN to preset
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_PRESET;  //0x1
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; // 0xB1; // ISYNC + preset command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[2] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (20000); //10us + 20us

    // Program the CTRL command for follower BFN to preset
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_PRESET;  //0x1
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; // 0xB1; // ISYNC + preset command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[4] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (40000); //30us + 40us

    // Program the CTRL command for follower BFN to preset
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_PRESET;  //0x1
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; // 0xB1; // ISYNC + preset command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[6] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[7] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    return 0;
}

/**
 * @brief           Function for capturing the follower BFN along with main BFN
 * @param [in]      None
 * @return          None
 */
void bfn_test_capture_cmd()
{
    // Program the CTRL command for follower BFN
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0;
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    /*PRESET command is required as currently the follower reset is not workig*/
    // Program the CTRL command for follower BFN to preset
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_PRESET;  //0x1
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; // 0xB1; // ISYNC + preset command
    INTRINSIC_BARRIER;

    com_timing_wait_ns (10000); //10us

    v2d_bfn_capture();

    dram_buff[0] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (20000); //10us + 20us

    v2d_bfn_capture();

    dram_buff[2] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (40000); //30us + 40us

    v2d_bfn_capture();

    dram_buff[4] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (60000); //70us + 60us

    v2d_bfn_capture();

    dram_buff[6] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[7] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
}

/**
 * @brief           Function for validating the positive adjustment
 * @param [in]      None
 * @return          None
 */
void bfn_positive_adjustment_cmd()
{

    v2d_bfn_capture();

    dram_buff[0] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    // Program the positive adjustment for follower BFN
    // To load the INC_PRE registers
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = ADJUSTMENT_VALUE;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    // Increment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[2] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (10000); //10us

    // Increment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[4] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (20000); //10us + 20us

    // Increment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[6] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[7] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
}

/**
 * @brief           Function for validating the negative adjustment
 * @param [in]      None
 * @return          None
 */
void bfn_negative_adjustment_cmd()
{

    v2d_bfn_capture();

    dram_buff[0] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    // Programe the positive adjustment for follower BFN
    // To load the INC_PRE registers
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = NEGETIVE_ADJUSTMENT_VALUE;
    INTRINSIC_BARRIER;

    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    // adjustment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[2] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (10000); //10us

    // adjustment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[4] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (20000); //10us + 20us

    // adjustment command to follower
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = FOLLOWER_INCREMENT_CMD;
    INTRINSIC_BARRIER;
    // Trigger the ISYNC pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[6] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[7] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
}

/**
 * @brief           Function for validating the sync adjustment
 * @param [in]      None
 * @return          None
 */
void bfn_sync_adj_cmd()
{
    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    /*Preset command was required as the follower soft reset is not working*/
    // Program the CTRL command for follower BFN to preset
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_PRESET;  //0x1
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_PRESET; // 0xB1; // ISYNC + preset command
    INTRINSIC_BARRIER;

    // Program the CTRL command for follower BFN
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_LCNT_INC.value = 0x1;
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = 0x2710;
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_INC_PRE.value = 0x4000004;
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CNT_ADJ.value = 2;
    INTRINSIC_BARRIER;

    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    v2d_bfn_capture();

    dram_buff[0] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[1] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    // Program the CTRL command for follower BFN
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_ADJ;  //0x5
    INTRINSIC_BARRIER;

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    com_timing_wait_ns (10000); //10us

    v2d_bfn_capture();

    dram_buff[2] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[3] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    dram_buff[8] = get_v2d_bfn_cnt();

    com_timing_wait_ns (10000); //10us + 10us

    v2d_bfn_capture();

    dram_buff[4] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[5] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

    com_timing_wait_ns (10000); //20us + 10us

    v2d_bfn_capture();

    dram_buff[6] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;
    dram_buff[7] = ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
}

/**
 * @brief           Function for restoring the default values of follower BFN
 * @param [in]      None
 * @return          None
 */
void restore_default()
{
    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

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

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;
}

/**
 * @brief           Function for reading the BFN count
 * @param [in]      None
 * @return          value
 */
uint32_t get_v2d_bfn_cnt()
{
    uint32_t value;

    //capture BFN count
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;

    //read BFN count
    return(((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_BFN_CNT.value);
}

/**
 * @brief           Function for sending the BFN capture command
 * @param [in]      None
 * @return          None
 */
void v2d_bfn_capture()
{
    // Program the CTRL command for follower BFN to capture
    ((bfn_csr_t*) g_v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_CAP;  //0x7
    INTRINSIC_BARRIER;

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // 0xB7; // ISYNC + capture command
    INTRINSIC_BARRIER;

}
// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
