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
 * @file    ax_v2d_flow3_pdpd_ingress_capture_repeat.c
 * @brief   Trigger the delayed start of for the given channel of quad along with start the corresponding vex cores.
 *          Start the MEM_FB capture based on the parameters passed.
 *          Stop the MEM_FB capture once the required number of captures done.
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

    uint32_t v2d_base = 0, vex_base = 0, v2d_num = 0, apb_num = 0, tx_vex_num = 0, rx_vex_num = 0, drf_clock = 0, match_value = 0,
             quad_instance = 0, capture_duration_value = 0, skip_cycles = 0, bfn_incr_value = 0,
             capture_blocks = 0, clks_per_blk = 0, num_captures = 0, capture_halt_value = 0;
    int lc = 0, vex_num = 0, v2d_index = 0, timer_value = 0, capture_delay_value = 0, dram_buff_index = 0, sample_size = 0, add_factor = 0,
        pdpd_rate = 0, compare_status = 0;
    int ref_pattern[6144] = {0};
    fb_mem_compare_t fb_mem_compare = {0};

    /*BFNE start reg value to be configured with corresponding timer value*/
    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};

    /*To start the VEX core*/
    ve32_cell_ctrl_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_CTRL_START_BF_MSK | VE32_CELL_CTRL_RUN_BF_MSK};

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];
    tx_vex_num = rsm_buf[2];
    rx_vex_num = rsm_buf[3];
    drf_clock = rsm_buf[4];
    match_value = rsm_buf[5];
    capture_delay_value = rsm_buf[6];
    skip_cycles = rsm_buf[8];
    capture_blocks = rsm_buf[9];
    sample_size = (SAMPLES_TO_V2D_CAP_SIZE(rsm_buf[7]) - 1);
    num_captures = rsm_buf[10];
    add_factor = rsm_buf[11];
    pdpd_rate = rsm_buf[12];

    clks_per_blk = (drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    bfn_incr_value = (capture_blocks * clks_per_blk) + skip_cycles;
    capture_halt_value = num_captures * bfn_incr_value;

    /*Generate the ref block for MEM_FB comparison*/
    generate_ref_block(ref_pattern, g_samples_per_blk[drf_clock][pdpd_rate]);

    /*populating the FB_COMPARE structure*/
    fb_mem_compare.ref_pattern = ref_pattern;
    fb_mem_compare.add_factor = add_factor;
    fb_mem_compare.skip_cycles = skip_cycles;
    fb_mem_compare.v2d_num = v2d_num;
    fb_mem_compare.capture_blocks = capture_blocks;
    fb_mem_compare.clks_per_blk = clks_per_blk;
    fb_mem_compare.capture_delay_value = capture_delay_value;
    fb_mem_compare.samples_per_block = g_samples_per_blk[drf_clock][pdpd_rate];
    fb_mem_compare.num_captures = num_captures;

    /*BFN configuration*/
    configure_v2d_bfn(v2d_num, apb_num, 1/*capture_enable*/, sample_size/*Size*/, match_value);

    /*Configuring the capture mode for config registers*/
    if (0 == apb_num)
    {
        configure_v2d_bfn_config(v2d_num, 1/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_REPEAT);
    }
    else
    {
        configure_v2d_bfn_config(v2d_num, 2/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_REPEAT);
    }

    /*Configure config register for HALT operation*/
    configure_v2d_bfn_config(v2d_num, 3/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_TOGGLE, BFN_EVENT_MODE_SINGLE);

    quad_instance = get_quad_instance(v2d_num);

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

    /*Trigger the BFN START only for even V2D*/
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    v2d_num = rsm_buf[0];
    v2d_base = V2D_BFN_BASE(v2d_num);

    /*Capture starts when first sample presented to PDPD
     * if we want to caputre the data anything other than start of the PDPD you should
     * modify this value*/
    if (0 == apb_num)
    {
        ((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value = bfne_start_reg.value + match_value + capture_delay_value;
        configure_v2d_bfn_incr(v2d_num, 1/*reg_instance*/, bfn_incr_value);
    }
    else
    {
        ((bfn_csr_t*) (v2d_base)) -> BFNE_START[2].value = bfne_start_reg.value + match_value + capture_delay_value;
        configure_v2d_bfn_incr(v2d_num, 2/*reg_instance*/, bfn_incr_value);
    }

    /*Timer program to halt the MEM_FB capture*/
    ((bfn_csr_t*) (v2d_base)) -> BFNE_START[3].value = bfne_start_reg.value + match_value + capture_delay_value + capture_halt_value;

    /*populate the capture start value in fb_mem_compare structure*/
    fb_mem_compare.capture_start_value = bfne_start_reg.value + match_value + capture_delay_value;

    /*start the VEX cores*/
    /*RX VEX CORE*/
    vex_base = VEX_BASE(rx_vex_num);
    *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;
    /*Tx VEX Core*/
    vex_base = VEX_BASE(tx_vex_num);
    *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;

    compare_status = mem_fb_compare_repeat(&fb_mem_compare);

    /*result of compare_status*/
    dram_buff[4] = compare_status;

    rsm_ax_shared_flag = 0xC000C0C0;

    return (0);
}
// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
