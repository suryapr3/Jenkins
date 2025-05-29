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
 * @file    ax_v2d_pc_hbi_drop.c
 * @brief   Write the PDPD register with mode1 update from RCS and trigger the VEX to send the
 *          mode1 update while RCS transfer is ongoing.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */


#include "com_event.h"
#include "rcs_gpreg.h"
#include "tx_tests.h"
#include "com_definitions.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "rcs_dmac.h"
#include "string.h"
#include "com_event.h"
#include "nsip_hbi.h"
#include "crux_intf.h"
#include "av2d_axi4.h"
#include "pdpd.h"
#include "ve32_cell.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32
#define BITS_128_PER_VEC    8
#define WORDS_PER_VEC   32
#define NUM_VEX_CORES   2

#define VEX_BASE(vex_num)   VEXABC0_SC_VE32_CELL_BASE + ((vex_num) * (VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE))
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile  gpdma_desc_t __attribute__ ((section (".sram.rx.rw"))) descr_buffer[100];
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_buf[TEST_BUFF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) src_buffer[3856];
int g_pdpd_base;

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/

void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size);

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/**
 * @brief           Function for configuring gpdma descriptor
 * @param [in]      desc_index, dest address , source address and block size
 * @return          none
 */
void gpdma_set_descr (int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size)
{
    gpdma_desc_t desc;
    memset ((void *)&desc, 0, sizeof (gpdma_desc_t));
    desc.sar_lsb = src_addr;
    desc.dar_lsb = dst_addr;
    desc.block_ts = block_size;
    desc.ctl = dmac_ctl_reg;
    desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    memcpy (&descr_buffer, &desc, sizeof (gpdma_desc_t));
}

/**
 * @brief           Function for writing to V2D register with GPDMA transfer
 * @param [in]      block size, source msize, dest msize, source tranfer width, dest transfer width ,source buffer address and destination offset
 * @return          status
 */
int gpdma_test_LLI(
        int block_size,
        m_size_value_t src_msize,
        m_size_value_t dst_msize,
        tr_width_value_t src_tr_width,
        tr_width_value_t dst_tr_width,
        int src_buffer_address,
        uint32_t dest_offset)
{
    int dataCnt = 0, v2d_num = 0, v2d_base = 0, apb_num = 0;

    dmac_ctl_reg.SRC_TR_WIDTH = src_tr_width;
    dmac_ctl_reg.DST_TR_WIDTH = dst_tr_width;
    dmac_ctl_reg.SRC_MSIZE = src_msize;
    dmac_ctl_reg.DST_MSIZE = dst_msize;


    volatile rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = {.value = RCS_DMAC_CH1_INTSTATUS_DEFAULT};

    v2d_num = rsm_buf[2];
    apb_num = rsm_buf[3];
    //src_buffer[3840] = rsm_buf[3]; // Get the PASSTHRU value to be configured

    /*Get the Base address based on v2d num*/
    switch (v2d_num)
    {
        case 0:
            v2d_base = V2D0_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D0_PDPD_0_BASE;
            break;
        case 1:
            v2d_base = V2D1_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D1_PDPD_0_BASE;
            break;
        case 2:
            v2d_base = V2D2_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D2_PDPD_0_BASE;
            break;
        case 3:
            v2d_base = V2D3_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D3_PDPD_0_BASE;
            break;
        case 4:
            v2d_base = V2D4_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D4_PDPD_0_BASE;
            break;
        case 5:
            v2d_base = V2D5_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D5_PDPD_0_BASE;
            break;
        case 6:
            v2d_base = V2D6_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D6_PDPD_0_BASE;
            break;
        case 7:
            v2d_base = V2D7_AV2D_AXI4_0_BASE;
            g_pdpd_base = V2D7_PDPD_0_BASE;
            break;
    }

    /*Update the base based on apb_num*/
    v2d_base = v2d_base + ((apb_num) * (V2D0_AV2D_AXI4_1_BASE - V2D0_AV2D_AXI4_0_BASE));
    g_pdpd_base = g_pdpd_base + ((apb_num) * (V2D0_PDPD_1_BASE - V2D0_PDPD_0_BASE));

    /*Set the GPDMA descriptor*/
    gpdma_set_descr (0, (uint32_t)(v2d_base + dest_offset)/*dest address*/, ((uint32_t)src_buffer_address), block_size);
    RCS_DMAC_CFGREG_REG->value = 1;

    // Channel1 configuration.
    *RCS_DMAC_CH1_CFG_REG = dmac_cfg_reg;
    *RCS_DMAC_CH1_CTL_REG = dmac_ctl_reg;

    // Descr address.
    rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enable
    rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_DMAC_CHENREG_REG = chen_reg;

    /*Wait till the transfer is done*/
    rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);

    while (0 == (rcs_dmac_ch1_intstatus_reg.value & 0x1))
    {
        rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
    }

    return 0;
}


int main(int argc, char **argv)
{
    int num_vectors_to_write = 0, num_128_bit_writes = 0, num_transactions = 0, vex_num[NUM_VEX_CORES] = {0}, vex_base = 0, lc = 0;
    xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();

    volatile rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = {.value = RCS_DMAC_CH1_INTSTATUS_DEFAULT};
    pdpd_control_reg_t pdpd_control_reg = {.value = PDPD_CONTROL_UPDATE_PASSTHRU_BF_MSK | PDPD_CONTROL_UPDATE_C_LUT_BF_MSK};

    /*To start the VEX core*/
    ve32_cell_mem_control_reg_t ve32_cell_mem_control_reg = {.value = VE32_CELL_MEM_CONTROL_START_BF_MSK | VE32_CELL_MEM_CONTROL_RUN_BF_MSK};

    for (lc = 0; lc < NUM_VEX_CORES; lc++)
    {
        vex_num[lc] = rsm_buf[lc];
    }

    /*Number of vectors to write to the G Buffer will vary based on the Duplication factor in V2D*/
    num_vectors_to_write = rsm_buf[4];

    /*Converting vectors to 128 bit writes additonal value is for 241st entry*/
    /*The last entry can have only one beat*/
    num_128_bit_writes = (num_vectors_to_write * BITS_128_PER_VEC) + 1;
    src_buffer[num_vectors_to_write * WORDS_PER_VEC] = rsm_buf[5];  // PASSTHRU COEFF

    /*initiate the first AXI transfer to V2D*/
    gpdma_test_LLI(0/*(block_size + 1) * src_tr width*/, DATA_ITEM_1/*number of transactions*/, DATA_ITEM_1/*dst_msize*/,
            BITS_128/*src_tr_width 128 bit transfer*/, BITS_128/*dst_tr_width 128 bit trnasfer*/, (int) src_buffer/*source buffer address*/,
            AV2D_AXI4_AV2D_AXI4_PC_M1_OFFSET);

    /*Start the VEX cores*/
    vex_base = VEX_BASE(vex_num[0]);
    *(VE32_CELL_MEM_CONTROL_REG(vex_base)) = ve32_cell_mem_control_reg;

    /*initiate the second AXI transfer to V2D*/
    gpdma_test_LLI(num_128_bit_writes - 2/*(block_size + 1) * src_tr width*/, DATA_ITEM_1/*number of transactions*/, DATA_ITEM_1/*dst_msize*/,
            BITS_128/*src_tr_width 128 bit transfer*/, BITS_128/*dst_tr_width 128 bit trnasfer*/, (int) (src_buffer + 4)/*source buffer address*/,
            (AV2D_AXI4_AV2D_AXI4_PC_M1_OFFSET + 16));

    /*Set the Control register for copying the SHADOW PASSTHRU to LIVE*/
    *(PDPD_CONTROL_REG(g_pdpd_base)) = pdpd_control_reg;

    rsm_ax_shared_flag = 0x5588;
    return (0);
}


