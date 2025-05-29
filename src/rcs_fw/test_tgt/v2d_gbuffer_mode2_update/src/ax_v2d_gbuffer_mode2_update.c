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
 * @file    ax_v2d_gubuffer_mode2_update.c
 * @brief   Write the PDPD Passthru shdw register with mode2 update from RCS.
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

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define TEST_BUFF_SIZE 32

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
volatile  gpdma_desc_t __attribute__ ((section (".sram.ax.rw"))) descr_buffer[100];
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_buf[TEST_BUFF_SIZE] __attribute__((section(".sram.reserved")));
volatile uint32_t __attribute__ ((section (".sram.ax.rw"))) src_buffer[4]; //128 bits.

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
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */
int gpdma_test_LLI(
        int block_size,
        m_size_value_t src_msize,
        m_size_value_t dst_msize,
        tr_width_value_t src_tr_width,
        tr_width_value_t dst_tr_width)
{
    int dataCnt = 0, v2d_num = 0, v2d_base = 0, apb_num = 0, pdpd_base = 0;
    pdpd_control_reg_t pdpd_control_reg = {.value = PDPD_CONTROL_UPDATE_PASSTHRU_BF_MSK};
    volatile rcs_dmac_ch1_intstatus_reg_t rcs_dmac_ch1_intstatus_reg = {.value = RCS_DMAC_CH1_INTSTATUS_DEFAULT};

    dmac_ctl_reg.SRC_TR_WIDTH = src_tr_width;
    dmac_ctl_reg.DST_TR_WIDTH = dst_tr_width;
    dmac_ctl_reg.SRC_MSIZE = src_msize;
    dmac_ctl_reg.DST_MSIZE = dst_msize;

    v2d_num = rsm_buf[0];
    apb_num = rsm_buf[1];
    src_buffer[0] = rsm_buf[2]; // Get the PASSTHRU value to be configured

    /*Get the Base address based on v2d num*/
    switch (v2d_num)
    {
        case 0:
            v2d_base = V2D0_AV2D_AXI4_0_BASE;
            pdpd_base = V2D0_PDPD_0_BASE;
            break;
        case 1:
            v2d_base = V2D1_AV2D_AXI4_0_BASE;
            pdpd_base = V2D1_PDPD_0_BASE;
            break;
        case 2:
            v2d_base = V2D2_AV2D_AXI4_0_BASE;
            pdpd_base = V2D2_PDPD_0_BASE;
            break;
        case 3:
            v2d_base = V2D3_AV2D_AXI4_0_BASE;
            pdpd_base = V2D3_PDPD_0_BASE;
            break;
        case 4:
            v2d_base = V2D4_AV2D_AXI4_0_BASE;
            pdpd_base = V2D4_PDPD_0_BASE;
            break;
        case 5:
            v2d_base = V2D5_AV2D_AXI4_0_BASE;
            pdpd_base = V2D5_PDPD_0_BASE;
            break;
        case 6:
            v2d_base = V2D6_AV2D_AXI4_0_BASE;
            pdpd_base = V2D6_PDPD_0_BASE;
            break;
        case 7:
            v2d_base = V2D7_AV2D_AXI4_0_BASE;
            pdpd_base = V2D7_PDPD_0_BASE;
            break;
    }

    /*Update the base based on apb_num*/
    v2d_base = v2d_base + ((apb_num) * (V2D0_AV2D_AXI4_1_BASE - V2D0_AV2D_AXI4_0_BASE));
    pdpd_base = pdpd_base + ((apb_num) * (V2D0_PDPD_1_BASE - V2D0_PDPD_0_BASE));

    /*Set the GPDMA descriptor*/
    gpdma_set_descr (0, (uint32_t)(v2d_base + AV2D_AXI4_AV2D_AXI4_PC_M2_OFFSET)/*dest address*/, ((uint32_t)src_buffer), block_size);
    RCS_DMAC_CFGREG_REG->value = 1;

    // Channel1 configuration.
    *RCS_DMAC_CH1_CFG_REG = dmac_cfg_reg;
    *RCS_DMAC_CH1_CTL_REG = dmac_ctl_reg;

    // Descr address.
    rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enabl
    rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_DMAC_CHENREG_REG = chen_reg;

    rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);

    while (0 == (rcs_dmac_ch1_intstatus_reg.value & 0x1))
    {
        rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTATUS_REG);
    }

    /*Set the Control register for copying the SHADOW PASSTHRU to LIVE*/
    *(PDPD_CONTROL_REG(pdpd_base)) = pdpd_control_reg;

    rsm_ax_shared_flag=0x5588;
    return 0;
}


int main(int argc, char **argv)
{
    xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();
    gpdma_test_LLI(0/*(block_size + 1) * src_tr width*/, DATA_ITEM_1/*number of transactions*/, DATA_ITEM_1/*dst_msize*/,
            BITS_128/*src_tr_width 128 bit transfer*/, BITS_128/*dst_tr_width 128 bit trnasfer*/);
    return (0);
}


