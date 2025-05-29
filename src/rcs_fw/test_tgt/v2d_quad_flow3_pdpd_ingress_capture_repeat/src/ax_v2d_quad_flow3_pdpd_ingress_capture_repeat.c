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
 * @file    ax_v2d_quad_flow3_pdpd_ingress_capture_repeat.c
 * @brief   Program the BFN for capturing the data for the QUAD in REPEAT mode along with starting
 *          the Rx and Tx Vex cores.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "v2d_common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32

/*Number of cycles to add to trigger the BFN START signal to V2D*/
#define TIMER_OFFSET   1500

#define FB_SAMPLES_PER_ANTENNA  65536   // 64K samples
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

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    xthal_enable_interrupts();

    v2d_rcs_host_param_t v2d_rcs_host_params;

    uint32_t v2d_base = 0, even_v2d_base = 0, vex_base = 0, quad_instance = 0, v2d_num = 0, pdpd_rate = 0, match_value = 0,
             capture_bfn_start_value = 0, antenna_index = 0, drf_clock = 0, clk_per_blk = 0, capture_halt_value = 0,
             dram_buff_index = 0, capture_duration_value = 0, sample_size = 0, capture_blocks_per_antenna = 0,
             skip_cycles = 0, samples_per_antenna = 0, ant_delay_values[4] = {0}, capture_duration = 0,
             capture_start_value[4] = {0};
    int lc = 0, vex_num = 0, v2d_index = 0, timer_value = 0, bfn_incr_value = 0;
    int ref_pattern[6144] = {0};

    bfn_csr_aw_isync_bfn_cnt_reg_t capture_halt_bfn = {.value = BFN_CSR_AW_ISYNC_BFN_CNT_DEFAULT};

    /*BFNE start reg value to be configured with corresponding timer value*/
    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};

    /*To start the VEX core*/
    ve32_cell_ctrl_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_CTRL_START_BF_MSK | VE32_CELL_CTRL_RUN_BF_MSK};

    quad_instance = ((v2d_rcs_host_param_t *) rsm_buf) -> quad_instance;
    match_value = ((v2d_rcs_host_param_t *) rsm_buf) -> match_value;
    pdpd_rate = ((v2d_rcs_host_param_t *) rsm_buf) -> pdpd_rate;
    drf_clock = ((v2d_rcs_host_param_t *) rsm_buf) -> drf_clock;
    capture_blocks_per_antenna = ((v2d_rcs_host_param_t *) rsm_buf) -> capture_blocks;
    skip_cycles = ((v2d_rcs_host_param_t *) rsm_buf) -> skip_cycles;

    clk_per_blk = (drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    samples_per_antenna = capture_blocks_per_antenna * g_samples_per_blk[drf_clock][pdpd_rate];
    ant_delay_values[0] = ((v2d_rcs_host_param_t *) rsm_buf) -> ant0_cycles;
    ant_delay_values[1] = ((v2d_rcs_host_param_t *) rsm_buf) -> ant1_cycles;
    ant_delay_values[2] = ((v2d_rcs_host_param_t *) rsm_buf) -> ant2_cycles;
    ant_delay_values[3] = ((v2d_rcs_host_param_t *) rsm_buf) -> ant3_cycles;
    sample_size = SAMPLES_TO_V2D_CAP_SIZE(samples_per_antenna) - 1;
    capture_duration = capture_blocks_per_antenna * clk_per_blk;

    /*This value should be time from the capture start time to the next capture start time*/
    bfn_incr_value = (4 * capture_blocks_per_antenna * clk_per_blk) + skip_cycles + ((v2d_rcs_host_param_t *) rsm_buf) -> ant1_cycles + \
                     ((v2d_rcs_host_param_t *) rsm_buf) -> ant2_cycles + ((v2d_rcs_host_param_t *) rsm_buf) -> ant3_cycles;

    /*Time at which to stop the antenna capture*/
    capture_halt_value = (((v2d_rcs_host_param_t *) rsm_buf) -> num_captures) * bfn_incr_value;

    /*Generate the ref block for MEM_FB comparison*/
    generate_ref_block(ref_pattern, g_samples_per_blk[drf_clock][pdpd_rate]);

    /*BFN configuration*/
    quad_configure_v2d_bfn(quad_instance, 1/*capture_enable*/, sample_size, match_value);

    /*configuring the BFNE_config registers*/
    quad_configure_v2d_bfn_config(quad_instance, 1/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_REPEAT);
    quad_configure_v2d_bfn_config(quad_instance, 2/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_REPEAT);

    /*BFNE config for HALT*/
    quad_configure_v2d_bfn_config(quad_instance, 3/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_TOGGLE, BFN_EVENT_MODE_SINGLE);

    /*configure the BFNE_INCR value*/
    quad_configure_v2d_bfn_incr(quad_instance, 1/*reg_instance*/, bfn_incr_value);
    quad_configure_v2d_bfn_incr(quad_instance, 2/*reg_instance*/, bfn_incr_value);

    /*BFN sync verification*/
    quad_bfn_sync_ver(quad_instance, drf_clock);

    /*Writing the BFN capture values to DRAM*/
    quad_v2d_bfn_capture(quad_instance);

    dram_buff[dram_buff_index++] = RCS_TIMER_GPREG -> BFN_CNT_VAL2_REG0.value;

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        dram_buff[dram_buff_index++] = ((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    }

    switch (quad_instance)
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

    timer_value = ((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;
    bfne_start_reg.value = timer_value + TIMER_OFFSET;

    /*Trigger the BFN START for Tx start*/
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    capture_bfn_start_value = bfne_start_reg.value + match_value;

    /*Trigger BFN for capture memory*/
    v2d_num = g_v2d_instance_in_quad[quad_instance][0]; // for even V2D
    even_v2d_base = V2D_BFN_BASE(v2d_num);

    /*For PDPD0 capture*/
    ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[1].value = capture_bfn_start_value + ant_delay_values[0];
    /*For PDPD1 capture*/
    ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[2].value = ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[1].value + capture_duration + \
                                                            ant_delay_values[1];

    /*Get the HALT value in frame and offset format*/
    capture_halt_bfn.OFFSET = capture_halt_value % (((bfn_csr_t*) (even_v2d_base)) -> AW_ISYNC_TEN_MS_CNT.value);
    capture_halt_bfn.FRAME = capture_halt_value / (((bfn_csr_t*) (even_v2d_base)) -> AW_ISYNC_TEN_MS_CNT.value);

    /*Trigger for capture halt*/
    ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[3].value = ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[1].value + capture_halt_bfn.value;

    v2d_num = g_v2d_instance_in_quad[quad_instance][1]; // for odd V2D
    v2d_base = V2D_BFN_BASE(v2d_num);

    /*For PDPD0 capture*/
    ((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value = ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[2].value + capture_duration + \
                                                       ant_delay_values[2];
    /*For PDPD1 capture*/
    ((bfn_csr_t*) (v2d_base)) -> BFNE_START[2].value = ((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value + capture_duration + \
                                                       ant_delay_values[3];

    /*Trigger for capture halt*/
    ((bfn_csr_t*) (v2d_base)) -> BFNE_START[3].value = ((bfn_csr_t*) (even_v2d_base)) -> BFNE_START[3].value;

    /*start the VEX cores*/
    /*First start the RX core then the Tx Core*/
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        for (lc = 0; lc < (VEX_PER_V2D / 2); lc++)
        {
            v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
            /*RX VEX CORE*/
            vex_num = g_vex_instance_in_v2d[v2d_num][(2 * lc) + 1];
            vex_base = VEX_BASE(vex_num);
            *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;
            /*Tx VEX Core*/
            vex_num = g_vex_instance_in_v2d[v2d_num][(2 * lc)];
            vex_base = VEX_BASE(vex_num);
            *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;
        }
    }

    /*Compare the MEM_FB samples for the QUAD*/
    dram_buff[4] = quad_mem_fb_compare_repeat(ref_pattern, (v2d_rcs_host_param_t *)rsm_buf);

    rsm_ax_shared_flag = 0xC000C0C0;

    return (0);
}

// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
