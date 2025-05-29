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
 * @file    ax_v2d_quad_flow1_trigger.c
 * @brief   Trigger the delayed start of for the Ch0 of given quad along with start the corresponding vex cores.
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
#include "ve32_cell.h"
#include "rcs_timer_gpreg.h"
#include "bfn_test.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32
#define VEX_DMEM_OFFSET 0x10
#define V2D_PER_QUAD    2
#define VEX_PER_V2D 4

#define VEX_BASE(vex_num)   VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE))
#define V2D_BFN_BASE(v2d_num)    (V2D0_BFN_CSR_BASE + (v2d_num) * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE))

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
volatile uint32_t dram_buff[TEST_BUFF_SIZE]  __attribute__((section(".dram0.data")));
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));

const int g_v2d_instance_in_quad[][V2D_PER_QUAD] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7}
};

const int g_vex_instance_in_v2d[][VEX_PER_V2D] = {
    {0, 1, 8, 9},
    {2, 3, 10, 11},
    {4, 5, 12, 13},
    {6, 7, 14, 15}
};

int g_quad_instance = 0, g_drf_clock = 0;

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    uint32_t v2d_base = 0, vex_base = 0, g_quad_instance = 0, v2d_num = 0;
    int lc = 0, vex_num = 0, v2d_index = 0;

    /*BFNE start reg value to be configured with forced trigger value*/
    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};
    bfne_start_reg.value = 0xFFFFFFFF;

    /*To start the VEX core*/
    ve32_cell_mem_control_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_MEM_CONTROL_START_BF_MSK | VE32_CELL_MEM_CONTROL_RUN_BF_MSK};

    g_quad_instance = rsm_buf[0];
    g_drf_clock = rsm_buf[2];

    /*BFN sync verification*/
    quad_bfn_sync_ver();

    /*BFN configuration*/
    configure_v2d_force_bfn();

    switch (g_quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*start the VEX cores*/
    /*First start the RX core then the Tx Core*/
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        for (lc = 0; lc < (VEX_PER_V2D / 2); lc++)
        {
            v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
            /*RX VEX CORE*/
            vex_num = g_vex_instance_in_v2d[v2d_num][(2 * lc) + 1];
            vex_base = VEX_BASE(vex_num);
            *(VE32_CELL_MEM_CONTROL_REG(vex_base)) = ve32_cell_mem_control_reg;
            /*Tx VEX Core*/
            vex_num = g_vex_instance_in_v2d[v2d_num][(2 * lc)];
            vex_base = VEX_BASE(vex_num);
            *(VE32_CELL_MEM_CONTROL_REG(vex_base)) = ve32_cell_mem_control_reg;
        }
    }

    /*Trigger the FORCED BFN START*/
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    rsm_ax_shared_flag = 0xC000C0C0;

    return (0);
}

/**
 * @brief           Function for sync verification of QUAD
 * @param [in]      none
 * @return          none
 */
void quad_bfn_sync_ver()
{
    uint32_t rv = 0, v2d_num = 0, buff_index = 0, v2d_base = 0, v2d_index = 0, rcs_timestamp_value = 0, v2d_timestamp_value = 0,
             adjustment_value[V2D_PER_QUAD] = {0};

    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    // soft reset Follower V2D BFN
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x1;
        INTRINSIC_BARRIER;
        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x0;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = 0x32; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // Set the SYSREF
    RCS_TIMER_GPREG -> OPPS_VAL_TIMESYNC_CTRL.value = TIMESYNC_CTRL;    //0x00030031
    INTRINSIC_BARRIER;

    g_quad_instance = rsm_buf[0];
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = 0;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_LCNT_INC.value = 0x1;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = BFN_CSR_AW_ISYNC_TEN_MS_CNT_DEFAULT;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CNT_ADJ.value = BFN_CSR_AW_ISYNC_CNT_ADJ_DEFAULT;
        INTRINSIC_BARRIER;

        // Program the CTRL command for follower BFN to full load
        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // preload BFN values used with SYSREF load
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.LOAD_READ = 1;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG -> ICTRL.LOAD_READ = 0x1;
    INTRINSIC_BARRIER;

    quad_v2d_bfn_capture();

    rcs_timestamp_value = (RCS_TIMER_GPREG) -> BFN_CNT_VAL2_REG0.value;

    /*Calculate the adjustment values and preload the values with INIT command*/
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        v2d_timestamp_value = ((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

        if (v2d_timestamp_value > rcs_timestamp_value)
        {
            adjustment_value[v2d_num] = v2d_timestamp_value - rcs_timestamp_value;
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = 0xFF000000 | (0x960000 - adjustment_value[v2d_num]);
            INTRINSIC_BARRIER;
        }
        else
        {
            adjustment_value[v2d_num] = rcs_timestamp_value - v2d_timestamp_value;
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = adjustment_value[v2d_num];
            INTRINSIC_BARRIER;
        }

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;

    quad_v2d_bfn_capture();

    dram_buff[buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        dram_buff[buff_index++] = ((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

}

/**
 * @brief           Function for triggering the BFN capture command
 * @param [in]      none
 * @return          none
 */
void quad_v2d_bfn_capture()
{
    int v2d_num = 0, v2d_index = 0, v2d_base = 0;

    // Program the CTRL command for follower BFN to capture
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[g_quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_CAP;  //0x7
        INTRINSIC_BARRIER;
    }

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // 0xB7; // ISYNC + capture command
    INTRINSIC_BARRIER;

}

/**
 * @brief           Function for configuring the BFN registers
 * @param [in]      none
 * @return          none
 */
void configure_v2d_force_bfn()
{
    int v2d_base = 0, lc = 0;

    bfn_csr_general_csr_reg_t bfn_csr_general_csr_reg = {.value = BFN_CSR_GENERAL_CSR_DEFAULT};

    /*Enabling the BFN events*/
    bfn_csr_bfne_config_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CONFIG_DEFAULT};
    bfne_config_reg.ENABLE = 1;

    bfn_csr_start_lm_reg_t bfn_csr_start_lm_reg = {.value = BFN_CSR_START_LM_MATCH_EN_BF_MSK};

    g_quad_instance = rsm_buf[0];

    switch (g_quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*Enabling the BFN start Enable*/
    bfn_csr_general_csr_reg= *(BFN_CSR_GENERAL_CSR_REG(v2d_base));
    bfn_csr_general_csr_reg.value |= BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
    *(BFN_CSR_GENERAL_CSR_REG(v2d_base)) = bfn_csr_general_csr_reg;

    /*Enabling the BFN EVENT in the BFN config*/
    *(BFN_CSR_BFNE_CONFIG0_REG(v2d_base)) = bfne_config_reg;

    /*Writing the LM_START values with the required match values
     *for all the required channels*/
    bfn_csr_start_lm_reg.MATCH_VALUE = rsm_buf[1];

    for (lc = 0; lc < V2D_PER_QUAD; lc++)
    {
        v2d_base = v2d_base + (lc * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE));
        *(BFN_CSR_START_LM0_REG(v2d_base)) = bfn_csr_start_lm_reg;
        *(BFN_CSR_START_LM1_REG(v2d_base)) = bfn_csr_start_lm_reg;
    }
}
// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
