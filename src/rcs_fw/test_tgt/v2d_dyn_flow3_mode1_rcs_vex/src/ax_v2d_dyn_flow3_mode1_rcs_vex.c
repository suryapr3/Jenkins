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
 * @file    ax_v2d_dyn_flow3_mode1_rcs_vex.c
 * @brief   Trigger the delayed start of for the given channel of given quad along with start the corresponding vex cores.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 *
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
#define TIMER_OFFSET   1000
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
volatile uint32_t lut_buffer[LUT_MEM_SIZE] __attribute__ ((section (".sram.ax.rw")));
volatile  gpdma_desc_t descr_buffer[100] __attribute__ ((section (".sram.rx.rw")));

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

void gbuffer_update();
/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function for updating the Gbuffer
 * @param [in]      NONE
 * @return          NONE
 */
void gbuffer_update()
{
    int num_vectors_to_write = 0, dest_addr = 0, v2d_num = 0, apb_num = 0, num_128_bit_writes = 0;

    /*Number of vectors to write to the G Buffer will vary based on the Duplication factor in V2D*/
    num_vectors_to_write = rsm_buf[7];
    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];

    /*Converting vectors to 128 bit writes additonal value is for 241st entry*/
    num_128_bit_writes = (num_vectors_to_write * BITS_128_PER_VEC) + (BITS_128_PER_VEC / 2);
    //src_buffer[num_vectors_to_write * WORDS_PER_VEC] = rsm_buf[8];  // PASSTHRU COEFF

    dest_addr = AV2D_AXI4_AV2D_AXI4_PC_M1_ADR(V2D_AXI_BASE(v2d_num, apb_num));
    rcs_gpdma_test_LLI((uint32_t)descr_buffer, num_128_bit_writes - 1/*(block_size + 1) * src_tr width*/, DATA_ITEM_1/*number of transactions*/,
                       DATA_ITEM_1/*dst_msize*/, BITS_128/*src_tr_width 128 bit transfer*/, BITS_128/*dst_tr_width 128 bit trnasfer*/,
                       (int)(lut_buffer), dest_addr);
}

int main (int argc, char **argv)
{

    xthal_enable_interrupts();

    uint32_t v2d_base = 0, vex_base = 0, v2d_num = 0, apb_num = 0, tx_vex_num = 0, adapt_vex_num = 0, drf_clock = 0, match_value = 0,
             quad_instance = 0, capture_duration_value;
    int lc = 0, vex_num = 0, v2d_index = 0, timer_value = 0, capture_delay_value = 0, dram_buff_index = 0, sample_size = 0;

    /*BFNE start reg value to be configured with corresponding timer value*/
    bfn_csr_bfne_start_reg_t bfne_start_reg = {.value = BFN_CSR_BFNE_START_DEFAULT};

    /*To start the VEX core*/
    ve32_cell_ctrl_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_CTRL_START_BF_MSK | VE32_CELL_CTRL_RUN_BF_MSK};

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];
    tx_vex_num = rsm_buf[2];
    adapt_vex_num = rsm_buf[3];
    drf_clock = rsm_buf[4];
    match_value = rsm_buf[5];
    capture_delay_value = rsm_buf[6];
    sample_size = 0x7FFF;   // Corresponds to 256K samples total 1MB

    /*BFN configuration*/
    configure_v2d_bfn(v2d_num, apb_num, 1/*capture_enable*/, sample_size/*Size*/, match_value);

    /*Configuring the capture mode for config registers*/
    if (0 == apb_num)
    {
        configure_v2d_bfn_config(v2d_num, 1/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_SINGLE);
    }
    else
    {
        configure_v2d_bfn_config(v2d_num, 2/*reg_instance*/, BFN_EVENT_OUTPUT_MODE_PULSE, BFN_EVENT_MODE_SINGLE);
    }

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

    rsm_ax_shared_flag = 0xDEAD;
    gbuffer_update();

    rsm_ax_shared_flag = RCS_GPDMA_TFR_DONE;

#ifndef REGRESSION
    while (HOST_VALIDATION_DONE != rsm_ax_shared_flag)
    {
        //Do nothing wait in this loop
    }
#endif

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
        //((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value = bfne_start_reg.value + match_value + capture_delay_value;
        //V2D popout will be started with immediate mode.
        ((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value = 0xFFFFFFFF;
    }
    else
    {
        //((bfn_csr_t*) (v2d_base)) -> BFNE_START[2].value = bfne_start_reg.value + match_value + capture_delay_value;
        //V2D popout will be started with immediate mode.
        ((bfn_csr_t*) (v2d_base)) -> BFNE_START[2].value = 0xFFFFFFFF;
    }

    /*Trigger the BFN START only for even V2D*/
    bfne_start_reg.value = 0xFFFFFFFF;

    v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
    v2d_base = V2D_BFN_BASE(v2d_num);
    *(BFN_CSR_BFNE_START0_REG(v2d_base)) = bfne_start_reg;

    /*start the VEX cores*/
    /*ADAPT VEX Core*/
    vex_base = VEX_BASE(adapt_vex_num);
    *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;

    /*Tx VEX Core*/
    vex_base = VEX_BASE(tx_vex_num);
    *(VE32_CELL_CTRL_REG(vex_base)) = ve32_cell_mem_control_reg;

    rsm_ax_shared_flag = RCS_COMPLETE;

    return (0);
}

// cmd rcs
// ../../repo/arborcrest/test_tgt/rtl/run_rcs.sh -utx idma -b sim -p tx
// cmd soc
// ../../repo/arborcrest/test_tgt/rtl/run_soc.sh -utx idma -b sim -p tx -d abcn5a0_unvex -m abc_lite_unvex -s 32G -args -w -r 450
