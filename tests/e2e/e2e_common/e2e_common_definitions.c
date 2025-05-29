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

/*
 * @file     This file contains functions and declarations that are applicable for all the E2E tests.
 * **/
#include <stdio.h>
#include "e2e_common_definitions.h"
#include "common_functions.h"

#ifdef FLOW1_EN
#include "flow1_common_utils.h"
#endif
#ifdef FLOW2_EN
#include "flow2_common_utils.h"
#endif
#ifdef FLOW3_EN
#include "flow3_common_utils.h"
#endif
// Global declarations for the submodules getting used in this test
vha_dev_t vha_dev;
vha_dev_t *vha = &(vha_dev);

#define FILL_LEVEL_TRIGGER 1

//extern const int g_vectors_per_block[2][6];
extern int g_num_blocks_v2d_buffer;

/* All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
  The Last four entries order shouldn't be modified*/
#ifdef FLOW1_EN  
static register_config_tbl_t g_v2d_flow1_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Rx Path Settings
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, 0x800C, \
        AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"},

    /************************************************************************************************************/
    /* The last four entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer A*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PTR_BOUND0_OFFSET, 0x4FF0000, AV2D_CSR_TX_CSR_TX_PTR_BOUND_WR_MASK, "TX_PTR_BOUND0"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, 0x200, AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_STRM_CNT_WR_MASK, "TX_STRM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STRM_CNT0"}
    /************************************************************************************************************/
};
#endif

#ifdef FLOW2_EN
// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
static v2d_flow_tbl_t g_v2d_flow2_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last Five entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
};
#endif


// All the offsets are mapped to APB 0 , while writing to the register additional offset will be added if APB1 was used..
// Last Five entries order shouldn't be modified
#ifdef FLOW3_EN
static v2d_flow_tbl_t g_v2d_flow3_config_tbl[] = {
// Interrupt Enable
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_HIGH_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "V2D_INT_HIGH_EN"},
    {V2D_CSR_OFFSET + AV2D_CSR_INT_CSR_INT_LOW_EN_OFFSET, CSR_INT_VALUE, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "V2D_INT_LOW_EN"},

// Tx Path Settings
    // Rx Path Settings , F path
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_PACKET_SZ_OFFSET, RX_PACKET_SZ_VALUE, AV2D_CSR_RX_CSR_RX_PACKET_SZ_WR_MASK, "RX_PACKET_SZ"},
    /************************************************************************************************************/
    /* The last Five entries order shouldn't change as these values will be modified based on the sample rate which
     * is a run time parameter*/
    //TX from PDPD, TX_RX_LOOPBACK set
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_SIF_CTRL_OFFSET, AV2D_CSR_TX_CSR_TX_SIF_CTRL_TX_RX_LPBK_BF_MSK, \
        AV2D_CSR_TX_CSR_TX_SIF_CTRL_WR_MASK, "TX_SIF_CTRL"},
    /*Upper Bound [26:16]and Lower Bound [10:0]in flits for Buffer B*/
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND0_OFFSET, 0x7FF0000, AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_WR_MASK, "TX_PD_PTR_BOUND0"},
    /*sample rate set to 8 GSPS for VEX to V2D direction, meaning the samples coming from VEX are at 8 GSPS
      need to be picked up dynamically for the specific run*/
    {V2D_CSR_OFFSET + AV2D_CSR_PIF_CTRL_OFFSET, AV2D_CSR_PIF_CTRL_DEFAULT, AV2D_CSR_PIF_CTRL_WR_MASK, "PIF_CTRL"},
    // count in flits. 0 means 1 flit
    {V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_PD_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_WR_MASK, "TX_PD_STREAM_CNT0"},
    {V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_STRM_CNT0_OFFSET, 0x800000FF, AV2D_CSR_RX_CSR_RX_STRM_CNT_WR_MASK, "RX_STREAM_CNT0"},
    /************************************************************************************************************/
};
#endif
/***********************************************
 * STATIC FUNCTION DEFINATIONS                 *
 ***********************************************/

int test_configure_vha_duc_ddc(
    uint32_t vha_num,
    uint32_t ant_num,
    uint32_t in_rate,                  /* Vijay will pass 0 here */
    uint32_t out_rate,                 /* Vijay will pass 1 here */
    filter_mode_t mode,
    uint32_t clk)
{
    vha_antenna_t *vha_ant;
    vha_duc_t *duc0;
    vha_ddc_t *ddc0;
    vha_dmod_t *dmod;
    vha_mod_t *mod;
    vha_ant_t *ant_reg;
    vha_t *vha_reg;
    nsip_hbi_t *cm;
    uint64_t vha_base_addr, vha_apb_base_addr, vha_reg_base_addr;
    uint64_t duc0_base_addr, mod_base_addr, ant_reg_base_addr, cm_base_addr;
    uint64_t ddc0_base_addr, dmod_base_addr;
    uint32_t value, dl_in_rate, dl_out_rate, ul_in_rate, ul_out_rate;
    int i, rv;

    rv = 0;
    dl_in_rate = in_rate;
    dl_out_rate = out_rate;
    ul_in_rate = out_rate;
    ul_out_rate = in_rate;

    vha_base_addr = VHA_BASE(vha_num);
    vha_apb_base_addr = vha_base_addr + VHA_APB_OFFSET(ant_num);
    if((vha_base_addr < 0x03c00000) || (vha_base_addr > 0x03ce0000))
    {
        printf("ERROR: Cannot configure VHA with base_addr = %x\n", vha_base_addr);
        return -1;
    }
    vha->base_addr = vha_base_addr;
    vha_ant = &(vha->ant[ant_num]);
    vha_ant->base_addr = vha_apb_base_addr;

    printf("HOST: vha_base_addr = 0x%x\n", vha_base_addr);
    // VHA_DUC block settings
    duc0 = &(vha_ant->duc[0]);
    duc0_base_addr = vha_apb_base_addr + VHA_DUC_OFFSET(0);
    value = mode;                                          // bit0: 0-> auto, 1-> manual
    if(mode == MANUAL)
    {
        for(i = 1; ((i <= 4) && ((dl_out_rate - (i - 1)) > dl_in_rate)); i++)
        {
            value |= (1 << i);                             // bit[4:1] = stage_active
        }
    }
    duc0->CFG.value = value;
    if(rv = write_reg_18a(VHA_DUC_CFG_ADR(duc0_base_addr),
                          duc0->CFG.value,
                          VHA_DUC_CFG_WR_MASK,
                          "VHA_DUC0_CFG"))
        return rv;

    // VHA_MOD block settings
    mod = &(vha_ant->mod);
    mod_base_addr = vha_apb_base_addr + VHA_MOD_OFFSET;
    mod->CFG.value = 0;                                 // active_bands = 0
    if(rv = write_reg_18a(VHA_MOD_CFG_ADR(mod_base_addr),
                          mod->CFG.value,
                          VHA_MOD_CFG_WR_MASK,
                          "VHA_MOD_CFG"))
        return rv;

    // VHA_ANT_REG block settings
    ant_reg = &(vha_ant->ant_reg);
    ant_reg_base_addr = vha_apb_base_addr + VHA_ANT_REG_OFFSET;
    value = g_vectors_per_block[clk][dl_in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_DL_IF_CFG[0].value = (4 << 8) | value;// cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_DL_CFG.value = (1 << 14) | (dl_out_rate << 8) | (3 << 6) | dl_in_rate;
                                                           // bit14: dl_of_enable band0,
                                                           // bit[10:8]: dl_out_rate0,
                                                           // bit[7:6]: mod_bypass,
                                                           // bit[2:0]: dl_in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    if(clk & !dl_out_rate)
    {
        ant_reg->VHA_ANT_CFG.value = 0x1;                  // Hack: if the dl_out_rate is p187, then the
                                                           //  blk size (6flits) will not be the multiple
                                                           //  of 4, so make it to multiple of 2.
    }
    ant_reg->VHA_ANT_DL_OF_CFG[0].value = 0;               // no split
    ant_reg->VHA_ANT_ARB_CFG.value = 0;                    // mode = 0 = strict priority
    ant_reg->VHA_ANT_INT_HIGH_EN.value = 0x7ff;            // enable all the interrupts
    ant_reg->VHA_ANT_INT_LOW_EN.value = 0x7ff;             // enable all the interrupts
    if(rv = write_reg_18a(VHA_ANT_DL_IF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_IF_CFG[0].value,
                          VHA_ANT_DL_IF_CFG_WR_MASK,
                          "VHA_ANT_DL_IF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_CFG.value,
                          VHA_ANT_DL_CFG_WR_MASK,
                          "VHA_ANT_DL_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_CFG.value,
                          VHA_ANT_CFG_WR_MASK,
                          "VHA_ANT_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_OF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_OF_CFG[0].value,
                          VHA_ANT_DL_OF_CFG_WR_MASK,
                          "VHA_ANT_DL_OF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_ARB_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_ARB_CFG.value,
                          VHA_ANT_ARB_CFG_WR_MASK,
                          "VHA_ANT_ARB_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_HIGH_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_HIGH_EN.value,
                          VHA_ANT_INT_HIGH_EN_WR_MASK,
                          "VHA_ANT_INT_HIGH_EN"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_LOW_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_LOW_EN.value,
                          VHA_ANT_INT_LOW_EN_WR_MASK,
                          "VHA_ANT_INT_LOW_EN"))
        return rv;


    // VHA_DDC block settings
    ddc0 = &(vha_ant->ddc[0]);
    ddc0_base_addr = vha_apb_base_addr + VHA_DDC_OFFSET(0);
    value = mode;                                          // bit0: 0-> auto, 1-> manual
    if(mode == MANUAL)
    {
        for(i = 1; ((i <= 4) && ((ul_in_rate - (i - 1)) > ul_out_rate)); i++)
        {
            value |= (1 << i);                             // bit[4:1] = stage_active
        }
    }
    ddc0->CFG.value = value;
    if(rv = write_reg_18a(VHA_DDC_CFG_ADR(ddc0_base_addr),
                          ddc0->CFG.value,
                          VHA_DDC_CFG_WR_MASK,
                          "VHA_DDC0_CFG"))
        return rv;

    // VHA_DMOD block settings
    dmod = &(vha_ant->dmod);
    dmod_base_addr = vha_apb_base_addr + VHA_DMOD_OFFSET;
    dmod->CFG.value = 0;                                 // active_bands = 0
    if(rv = write_reg_18a(VHA_DMOD_CFG_ADR(dmod_base_addr),
                          dmod->CFG.value,
                          VHA_DMOD_CFG_WR_MASK,
                          "VHA_DMOD_CFG"))
        return rv;
    value = g_vectors_per_block[clk][ul_in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_UL_IF_CFG.value = (4 << 9) | value;   // cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_UL_CFG.value = (1 << 8) | (ul_out_rate << 4) | (1 << 3) | ul_in_rate;
                                                           // bit8: ul_of_enable band0,
                                                           // bit[6:4]: ul_out_rate0,
                                                           // bit3: dmod_bypass,
                                                           // bit[2:0]: ul_in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    if(clk & !ul_out_rate)
    {
        ant_reg->VHA_ANT_CFG.value = 0x1;                  // Hack: if the ul_out_rate is p187, then the
                                                           //  blk size (6flits) will not be the multiple
                                                           //  of 4, so make it to multiple of 2.
    }
    ant_reg->VHA_ANT_UL_OF_CFG[0].value = 0;               // no split
    if(rv = write_reg_18a(VHA_ANT_UL_IF_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_IF_CFG.value,
                          VHA_ANT_UL_IF_CFG_WR_MASK,
                          "VHA_ANT_UL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_UL_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_CFG.value,
                          VHA_ANT_UL_CFG_WR_MASK,
                          "VHA_ANT_UL_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_CFG.value,
                          VHA_ANT_CFG_WR_MASK,
                          "VHA_ANT_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_UL_OF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_OF_CFG[0].value,
                          VHA_ANT_UL_OF_CFG_WR_MASK,
                          "VHA_ANT_UL_OF_CFG0"))
        return rv;

    // VHA_REG block settings
    vha_reg = &(vha->vha_reg);
    vha_reg_base_addr = vha_base_addr + VHA_REG_OFFSET;
    vha_reg->VHA_CFG.value = 0x3fc | clk;               // bit[9:8]: crux_clock_enable,
                                                           // bit[3:2]: dl_clock_enable,
                                                           // bit0: dl_clock_select (0->983MHz, 1->1GHz)
    vha_reg->VHA_DL_IF_CFG.value = ((1 + (3 * ant_num)) << (ant_num * 8));
                                                           // bit[11:8]: dl_ant1_band0_af_gate,
                                                           // bit[3:0]: dl_ant0_band0_af_gate
    vha_reg->VHA_DL_CTL.value = (1 << (2 * ant_num));      // dl_ififo_enable ant0/1_band0
    vha_reg->VHA_UL_IF_CFG.value = ((1 + (1 * ant_num)) << (ant_num * 2));
                                                           // bit[3:2]: ul_ant1_af_gate,
                                                           // bit[1:0]: ul_ant0_af_gate
    vha_reg->VHA_UL_CTL.value = (1 << (1 * ant_num));      // ul_ififo_enable ant0/1_band0
    if(rv = write_reg_18a(VHA_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_CFG.value,
                          VHA_CFG_WR_MASK,
                          "VHA_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_IF_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_IF_CFG.value,
                          VHA_DL_IF_CFG_WR_MASK,
                          "VHA_DL_IF_CFG"))
        return rv;

    if(rv = write_reg_18a(VHA_DL_CTL_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_CTL.value,
                          VHA_DL_CTL_WR_MASK,
                          "VHA_DL_CTL"))
        return rv;

    if(rv = write_reg_18a(VHA_UL_IF_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_UL_IF_CFG.value,
                          VHA_UL_IF_CFG_WR_MASK,
                          "VHA_UL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_UL_CTL_ADR(vha_reg_base_addr),
                          vha_reg->VHA_UL_CTL.value,
                          VHA_UL_CTL_WR_MASK,
                          "VHA_UL_CTL"))
    printf("INFO: VHA%d configuration completed\n", vha_num);

    return rv;
}


/**
 * function         test_configure_vha()
 * @brief           Function configuring all the required VHA registers to run this test
 * @param [in]      vha_num, ant_num, in_rate, out_rate, mode, dl_clk
 * @return          status
 */

int test_configure_vha_mod_demod(
    uint32_t vha_num,
    uint32_t ant_num,
    uint32_t in_rate,                  /* Vijay will pass 0 here */
    uint32_t out_rate,                 /* Vijay will pass 1 here */
    filter_mode_t mode,
    uint32_t clk)
{
    vha_antenna_t *vha_ant;
    vha_duc_t *duc0;
    vha_ddc_t *ddc0;
    vha_dmod_t *dmod;
    vha_mod_t *mod;
    vha_ant_t *ant_reg;
    vha_t *vha_reg;
    nsip_hbi_t *cm;
    swg_t * swg;
    uint64_t vha_base_addr, vha_apb_base_addr, vha_reg_base_addr, swg_base_addr;
    uint64_t duc0_base_addr, mod_base_addr, ant_reg_base_addr, cm_base_addr;
    uint64_t ddc0_base_addr, dmod_base_addr;
    uint32_t value, dl_in_rate, dl_out_rate, ul_in_rate, ul_out_rate;
    int i, rv;
    uint64_t fclk, fout, fs, num_cordics, delta_phase;
    uint64_t angle_bw_cordics, incr_angle, incr_val;
    uint64_t init_angle[4] = {0, 0, 0, 0};
    uint64_t init_val[4] = {0, 0, 0, 0};
    uint32_t dl_clk = 0, ul_clk = 0;

    rv = 0;
    dl_in_rate = in_rate;
    dl_out_rate = out_rate;
    ul_in_rate = out_rate;
    ul_out_rate = in_rate;

    vha_base_addr = VHA_BASE(vha_num);
    vha_apb_base_addr = vha_base_addr + VHA_APB_OFFSET(ant_num);
    if((vha_base_addr < 0x03c00000) || (vha_base_addr > 0x03ce0000))
    {
        printf("ERROR: Cannot configure VHA with base_addr = %x\n", vha_base_addr);
        return -1;
    }
    vha->base_addr = vha_base_addr;
    vha_ant = &(vha->ant[ant_num]);
    vha_ant->base_addr = vha_apb_base_addr;

    printf("HOST: vha_base_addr = 0x%x\n", vha_base_addr);
    // First configure the DL settings
    // VHA_DUC block settings
    duc0 = &(vha_ant->duc[0]);
    duc0_base_addr = vha_apb_base_addr + VHA_DUC_OFFSET(0);
    value = mode;                                          // bit0: 0-> auto, 1-> manual
    if(mode == MANUAL)
    {
        for(i = 1; ((i <= 4) && ((dl_out_rate - (i - 1)) > dl_in_rate)); i++)
        {
            value |= (1 << i);                             // bit[4:1] = stage_active
        }
    }
    duc0->CFG.value = value;
    if(rv = write_reg_18a(VHA_DUC_CFG_ADR(duc0_base_addr),
                          duc0->CFG.value,
                          VHA_DUC_CFG_WR_MASK,
                          "VHA_DUC0_CFG"))
        return rv;

    // VHA_MOD block settings
    mod = &(vha_ant->mod);
    mod_base_addr = vha_apb_base_addr + VHA_MOD_OFFSET;
    mod->CFG.value = 1;                                 // active_bands = band0
    mod->EN.value = ((1 << (out_rate - 2)) - 1);
    if (5 == out_rate)
    {
        mod->EN.value = ((1 << (out_rate - 1)) - 1);
    }
    if(rv = write_reg_18a(VHA_MOD_CFG_ADR(mod_base_addr),
                          mod->CFG.value,
                          VHA_MOD_CFG_WR_MASK,
                          "VHA_MOD_CFG"))
        return rv;

    if(rv = write_reg_18a(VHA_MOD_EN_ADR(mod_base_addr),
                          mod->EN.value,
                          VHA_MOD_EN_WR_MASK,
                          "VHA_MOD_EN"))
        return rv;

    // VHA_ANT_REG block settings
    ant_reg = &(vha_ant->ant_reg);
    ant_reg_base_addr = vha_apb_base_addr + VHA_ANT_REG_OFFSET;
    value = g_vectors_per_block[clk][dl_in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_DL_IF_CFG[0].value = (4 << 8) | value;// cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_DL_CFG.value = (1 << 14) | (dl_out_rate << 8) | (3 << 6) | dl_in_rate;
                                                           // bit14: dl_of_enable band0,
                                                           // bit[10:8]: dl_out_rate0,
                                                           // bit[7:6]: mod_bypass,
                                                           // bit[2:0]: dl_in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    if(clk & !dl_out_rate)
    {
        ant_reg->VHA_ANT_CFG.value = 0x1;                  // Hack: if the dl_out_rate is p187, then the
                                                           //  blk size (6flits) will not be the multiple
                                                           //  of 4, so make it to multiple of 2.
    }
    ant_reg->VHA_ANT_DL_OF_CFG[0].value = 0;               // no split
    ant_reg->VHA_ANT_ARB_CFG.value = 0;                    // mode = 0 = strict priority
    ant_reg->VHA_ANT_INT_HIGH_EN.value = 0x7ff;            // enable all the interrupts
    ant_reg->VHA_ANT_INT_LOW_EN.value = 0x7ff;             // enable all the interrupts
    if(rv = write_reg_18a(VHA_ANT_DL_IF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_IF_CFG[0].value,
                          VHA_ANT_DL_IF_CFG_WR_MASK,
                          "VHA_ANT_DL_IF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_CFG.value,
                          VHA_ANT_DL_CFG_WR_MASK,
                          "VHA_ANT_DL_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_CFG.value,
                          VHA_ANT_CFG_WR_MASK,
                          "VHA_ANT_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_DL_OF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_DL_OF_CFG[0].value,
                          VHA_ANT_DL_OF_CFG_WR_MASK,
                          "VHA_ANT_DL_OF_CFG0"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_ARB_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_ARB_CFG.value,
                          VHA_ANT_ARB_CFG_WR_MASK,
                          "VHA_ANT_ARB_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_HIGH_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_HIGH_EN.value,
                          VHA_ANT_INT_HIGH_EN_WR_MASK,
                          "VHA_ANT_INT_HIGH_EN"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_INT_LOW_EN_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_INT_LOW_EN.value,
                          VHA_ANT_INT_LOW_EN_WR_MASK,
                          "VHA_ANT_INT_LOW_EN"))
        return rv;

    

    // VHA_DL_SWG settings
    swg = &(vha->dl_swg);
    swg_base_addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
    printf("HOST: Going to configure the VHA DLSWG0 registers\n");
    fclk = 983040;                                         // System clock, in khz
    if(dl_clk) fclk = 1474000;                             // 1.5GHz
    fout = (fclk / 2);                                     // Min out_rate is 1Gsps (@983.04Mhz) or 1.5Gsps (@1.47GHz),
                                                           //  so take a safe freq of half of that as the carrier output
    fs = ((1 << (out_rate - 3)) * fclk);
    //fout = fclk / 4;
    //fout = ((3 * fclk) / 8);
    num_cordics = (fs / fclk);
    if(!num_cordics)
    {
        printf("ERROR: Cannot support this rate. Fs should be greater than or equal to Fclk. Exiting test..!");
        return -1 ;
    }
    if(num_cordics > 4)
    {
        printf("ERROR: Only 4 cordics per SWG are present. Exiting..!\n");
        return -1;
    }
    if((!fout) || (fout > (fs / 2)))
    {
        printf("HOST: Cannot support generating %dKHz carrier frequency. Exiting..!\n", fout);
        return -1;
    }
    angle_bw_cordics = (360 * fout) / (fclk * num_cordics);
    incr_angle = (angle_bw_cordics * num_cordics) % 360;
    incr_val = ((1UL << 38) * incr_angle / 360);
    printf("      fclk = %d KHz, fout = %d KHz, fs = %d KHz\n", fclk, fout, fs);
    printf("      Number of Cordics = %d\n", num_cordics);
    printf("      Angle b/w cordics = %d degrees\n", angle_bw_cordics);
    printf("      Incr_val = %x_%x (%d degrees)\n", (incr_val >> 32), (incr_val & ((1UL << 32) - 1)),
                                                    ((incr_val * 360) / (1UL << 38)));
    for(i = 0; i < num_cordics; i++)
    {
          init_angle[i] = (angle_bw_cordics * (num_cordics - i - 1)) % 360;
          init_val[i] = ((1UL << 38) * init_angle[i] / 360);
          printf("      Init value for Cordic-%d is %x_%x (%d degrees)\n", i, (init_val[i] >> 32),
                             (init_val[i] & ((1UL << 32) - 1)), init_angle[i]);
    }

    swg->INCR_UPPER[0].value = ((incr_val >> 32) & 0x3f);
    swg->INCR_LOWER[0].value = (incr_val & ((1UL << 32) - 1));
    for(i = 0; i < num_cordics; i++)
    {
        swg->INIT_UPPER_2D0_INIT_UPPER[i].value = ((init_val[i] >> 32) & 0x3f);
        swg->INIT_LOWER_2D0_INIT_LOWER[i].value = (init_val[i] & ((1UL << 32) - 1));
    }
    swg->EN[0].value = (1 << num_cordics) - 1;             // cordics per swg
    swg->EN_PER_SWG.value = 1;                             // only enable dlswg0 for band0
    swg->EXT_BYP.value = 0;                                // bypass bfn for dlswg0
    swg->INT_HIGH_EN.value = 0x7;                          // enable all interrupts
    swg->INT_LOW_EN.value = 0x7;                           // enable all interrupts

    if(rv = write_reg_18a(SWG_INCR_UPPER0_ADR(swg_base_addr),
                          swg->INCR_UPPER[0].value,
                          SWG_INCR_UPPER_WR_MASK,
                          "SWG_INCR_UPPER"))
        return rv;

    if(rv = write_reg_18a(SWG_INCR_LOWER0_ADR(swg_base_addr),
                          swg->INCR_LOWER[0].value,
                          SWG_INCR_LOWER_WR_MASK,
                          "SWG_INCR_LOWER"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER0_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[0].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER1_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[1].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER2_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[2].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER3_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[3].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER3"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER0_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[0].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER1_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[1].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER2_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[2].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER3_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[3].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER3"))
        return rv;

    if(rv = write_reg_18a(SWG_EN0_ADR(swg_base_addr),
                          swg->EN[0].value,
                          SWG_EN_WR_MASK,
                          "SWG_ENABLE"))
        return rv;

    if(rv = write_reg_18a(SWG_EN_PER_SWG_ADR(swg_base_addr),
                          swg->EN_PER_SWG.value,
                          SWG_EN_PER_SWG_WR_MASK,
                          "SWG_EN_PER_SWG"))
        return rv;

    if(rv = write_reg_18a(SWG_EXT_BYP_ADR(swg_base_addr),
                          swg->EXT_BYP.value,
                          SWG_EXT_BYP_WR_MASK,
                          "SWG_EXT_BYP"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_HIGH_EN_ADR(swg_base_addr),
                          swg->INT_HIGH_EN.value,
                          SWG_INT_HIGH_EN_WR_MASK,
                          "SWG_INT_HIGH_EN"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_LOW_EN_ADR(swg_base_addr),
                          swg->INT_LOW_EN.value,
                          SWG_INT_LOW_EN_WR_MASK,
                          "SWG_INT_LOW_EN"))
        return rv;

    // Now the UL settings
    // VHA_DDC block settings
    ddc0 = &(vha_ant->ddc[0]);
    ddc0_base_addr = vha_apb_base_addr + VHA_DDC_OFFSET(0);
    value = mode;                                          // bit0: 0-> auto, 1-> manual
    if(mode == MANUAL)
    {
        for(i = 1; ((i <= 4) && ((ul_in_rate - (i - 1)) > ul_out_rate)); i++)
        {
            value |= (1 << i);                             // bit[4:1] = stage_active
        }
    }
    ddc0->CFG.value = value;
    if(rv = write_reg_18a(VHA_DDC_CFG_ADR(ddc0_base_addr),
                          ddc0->CFG.value,
                          VHA_DDC_CFG_WR_MASK,
                          "VHA_DDC0_CFG"))
        return rv;

    // VHA_DMOD block settings
    dmod = &(vha_ant->dmod);
    dmod_base_addr = vha_apb_base_addr + VHA_DMOD_OFFSET;
    dmod->CFG.value = 1;                                 // active_bands = 1
    dmod->EN.value = ((1 << (ul_in_rate - 2)) - 1);
    if (5 == in_rate)
    {
        dmod->EN.value = ((1 << (ul_in_rate - 1)) - 1);
    }
    if(rv = write_reg_18a(VHA_DMOD_CFG_ADR(dmod_base_addr),
                          dmod->CFG.value,
                          VHA_DMOD_CFG_WR_MASK,
                          "VHA_DMOD_CFG"))
        return rv;

    if(rv = write_reg_18a(VHA_DMOD_EN_ADR(dmod_base_addr),
                          dmod->EN.value,
                          VHA_DMOD_EN_WR_MASK,
                          "VHA_DMOD_EN"))
        return rv;

    // VHA_ANT_REG block settings
    value = g_vectors_per_block[clk][ul_in_rate] * 2;      // adjust the input fifo watermark depending
                                                           //  upon the input rate
    ant_reg->VHA_ANT_UL_IF_CFG.value = (4 << 9) | value;   // cc_if_wm = 4, if_wm
    ant_reg->VHA_ANT_UL_CFG.value = (1 << 8) | (ul_out_rate << 4) | (1 << 3) | ul_in_rate;
                                                           // bit8: ul_of_enable band0,
                                                           // bit[6:4]: ul_out_rate0,
                                                           // bit3: dmod_bypass,
                                                           // bit[2:0]: ul_in_rate0
    ant_reg->VHA_ANT_CFG.value = 0x3;                      // bit[1:0]: burst_size = 4
    if(clk & !ul_out_rate)
    {
        ant_reg->VHA_ANT_CFG.value = 0x1;                  // Hack: if the ul_out_rate is p187, then the
                                                           //  blk size (6flits) will not be the multiple
                                                           //  of 4, so make it to multiple of 2.
    }
    ant_reg->VHA_ANT_UL_OF_CFG[0].value = 0;               // no split
    if(rv = write_reg_18a(VHA_ANT_UL_IF_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_IF_CFG.value,
                          VHA_ANT_UL_IF_CFG_WR_MASK,
                          "VHA_ANT_UL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_UL_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_CFG.value,
                          VHA_ANT_UL_CFG_WR_MASK,
                          "VHA_ANT_UL_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_CFG_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_CFG.value,
                          VHA_ANT_CFG_WR_MASK,
                          "VHA_ANT_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_ANT_UL_OF_CFG0_ADR(ant_reg_base_addr),
                          ant_reg->VHA_ANT_UL_OF_CFG[0].value,
                          VHA_ANT_UL_OF_CFG_WR_MASK,
                          "VHA_ANT_UL_OF_CFG0"))
        return rv;


    // VHA_UL_SWG settings
    swg = &(vha->ul_swg);
    swg_base_addr = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;
    printf("HOST: Going to configure the VHA UL SWG0 registers\n");
    fclk = 983040;                                         // System clock, in khz
    if(ul_clk) fclk = 1474000;                             // 1.5GHz
    fs = ((1 << (ul_in_rate - 3)) * fclk);
    num_cordics = (fs / fclk);
    fout = (fclk / 2);                                       // Generate a safe freq of half of the sampling rate
    if(!num_cordics)
    {
        printf("ERROR: Cannot support this rate. Fs should be greater than or equal to Fclk. Exiting test..!");
        return -1 ;
    }
    if(num_cordics > 4)
    {
        printf("ERROR: Only 4 cordics per SWG are present. Exiting..! num_cordics = %d, fs = %d, fclk = %d\n", num_cordics, fs, fclk);
        return -1;
    }
    if((!fout) || (fout > (fs / 2)))
    {
        printf("HOST: Cannot support generating %dKHz carrier frequency. Exiting..!\n", fout);
        return -1;
    }
    angle_bw_cordics = (360 * fout) / (fclk * num_cordics);
    incr_angle = (angle_bw_cordics * num_cordics) % 360;
    incr_val = ((1UL << 38) * incr_angle / 360);
    printf("      fclk = %d KHz, fout = %d KHz, fs = %d KHz\n", fclk, fout, fs);
    printf("      Number of Cordics = %d\n", num_cordics);
    printf("      Angle b/w cordics = %d degrees\n", angle_bw_cordics);
    printf("      Incr_val = %x_%x (%d degrees)\n", (incr_val >> 32), (incr_val & ((1UL << 32) - 1)),
                                                    ((incr_val * 360) / (1UL << 38)));
    for(i = 0; i < num_cordics; i++)
    {
          init_angle[i] = (angle_bw_cordics * (num_cordics - i - 1)) % 360;
          init_val[i] = ((1UL << 38) * init_angle[i] / 360);
          printf("      Init value for Cordic-%d is %x_%x (%d degrees)\n", i, (init_val[i] >> 32),
                             (init_val[i] & ((1UL << 32) - 1)), init_angle[i]);
    }

    swg->INCR_UPPER[0].value = ((incr_val >> 32) & 0x3f);
    swg->INCR_LOWER[0].value = (incr_val & ((1UL << 32) - 1));
    for(i = 0; i < num_cordics; i++)
    {
        swg->INIT_UPPER_2D0_INIT_UPPER[i].value = ((init_val[i] >> 32) & 0x3f);
        swg->INIT_LOWER_2D0_INIT_LOWER[i].value = (init_val[i] & ((1UL << 32) - 1));
    }
    swg->EN[0].value = (1 << num_cordics) - 1;             // cordics per swg
    swg->EN_PER_SWG.value = 1;                             // only enable dlswg0 for band0
    swg->EXT_BYP.value = 0;                                // bypass bfn for dlswg0
    swg->INT_HIGH_EN.value = 0x7;                          // enable all interrupts
    swg->INT_LOW_EN.value = 0x7;                           // enable all interrupts

    if(rv = write_reg_18a(SWG_INCR_UPPER0_ADR(swg_base_addr),
                          swg->INCR_UPPER[0].value,
                          SWG_INCR_UPPER_WR_MASK,
                          "SWG_INCR_UPPER"))
        return rv;

    if(rv = write_reg_18a(SWG_INCR_LOWER0_ADR(swg_base_addr),
                          swg->INCR_LOWER[0].value,
                          SWG_INCR_LOWER_WR_MASK,
                          "SWG_INCR_LOWER"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER0_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[0].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER1_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[1].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER2_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[2].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_UPPER_2D0_INIT_UPPER3_ADR(swg_base_addr),
                          swg->INIT_UPPER_2D0_INIT_UPPER[3].value,
                          SWG_INIT_UPPER_2D_WR_MASK,
                          "SWG_INIT_UPPER_2D0_INIT_UPPER3"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER0_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[0].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER0"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER1_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[1].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER1"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER2_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[2].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER2"))
        return rv;

    if(rv = write_reg_18a(SWG_INIT_LOWER_2D0_INIT_LOWER3_ADR(swg_base_addr),
                          swg->INIT_LOWER_2D0_INIT_LOWER[3].value,
                          SWG_INIT_LOWER_2D_WR_MASK,
                          "SWG_INIT_LOWER_2D0_INIT_LOWER3"))
        return rv;

    if(rv = write_reg_18a(SWG_EN0_ADR(swg_base_addr),
                          swg->EN[0].value,
                          SWG_EN_WR_MASK,
                          "SWG_ENABLE"))
        return rv;

    if(rv = write_reg_18a(SWG_EN_PER_SWG_ADR(swg_base_addr),
                          swg->EN_PER_SWG.value,
                          SWG_EN_PER_SWG_WR_MASK,
                          "SWG_EN_PER_SWG"))
        return rv;

    if(rv = write_reg_18a(SWG_EXT_BYP_ADR(swg_base_addr),
                          swg->EXT_BYP.value,
                          SWG_EXT_BYP_WR_MASK,
                          "SWG_EXT_BYP"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_HIGH_EN_ADR(swg_base_addr),
                          swg->INT_HIGH_EN.value,
                          SWG_INT_HIGH_EN_WR_MASK,
                          "SWG_INT_HIGH_EN"))
        return rv;

    if(rv = write_reg_18a(SWG_INT_LOW_EN_ADR(swg_base_addr),
                          swg->INT_LOW_EN.value,
                          SWG_INT_LOW_EN_WR_MASK,
                          "SWG_INT_LOW_EN"))
        return rv;

    // VHA_REG block settings (Common settings for DL & UL)
    vha_reg = &(vha->vha_reg);
    vha_reg_base_addr = vha_base_addr + VHA_REG_OFFSET;
    vha_reg->VHA_CFG.value = 0x3fc | (clk << 1) | clk;  // bit[9:8]: crux_clock_enable,
                                                           // bit[3:2]: dl_clock_enable,
                                                           // bit1: ul_clock_select (0->983MHz, 1->1GHz)
                                                           // bit0: dl_clock_select (0->983MHz, 1->1GHz)
    vha_reg->VHA_DL_IF_CFG.value = ((1 + (3 * ant_num)) << (ant_num * 8));
                                                           // bit[11:8]: dl_ant1_band0_af_gate,
                                                           // bit[3:0]: dl_ant0_band0_af_gate
    vha_reg->VHA_DL_SWG_CFG.value = (1 << (2 * ant_num));  // bit[3:0]: dl_swg0_af_gate
    vha_reg->VHA_DL_CTL.value = (1 << 4) | (1 << (2 * ant_num));
                                                           // bit4: band0 dl_swg_enable
                                                           // bit[3:0]: dl_ififo_enable ant0/1_band0

    vha_reg->VHA_UL_IF_CFG.value = ((1 + (1 * ant_num)) << (ant_num * 2));
                                                           // bit[3:2]: ul_ant1_af_gate,
                                                           // bit[1:0]: ul_ant0_af_gate
    vha_reg->VHA_UL_SWG_CFG.value = (1 << (1 * ant_num));  // bit[3:0]: dl_swg0_af_gate
    vha_reg->VHA_UL_CTL.value = (1 << 2) | (1 << (1 * ant_num));
                                                           // bit2: ul_swg0_enable
                                                           // bit[1:0]: ul_ififo_enable
    if(rv = write_reg_18a(VHA_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_CFG.value,
                          VHA_CFG_WR_MASK,
                          "VHA_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_IF_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_IF_CFG.value,
                          VHA_DL_IF_CFG_WR_MASK,
                          "VHA_DL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_SWG_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_SWG_CFG.value,
                          VHA_DL_SWG_CFG_WR_MASK,
                          "VHA_DL_SWG_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_DL_CTL_ADR(vha_reg_base_addr),
                          vha_reg->VHA_DL_CTL.value,
                          VHA_DL_CTL_WR_MASK,
                          "VHA_DL_CTL"))
        return rv;

    if(rv = write_reg_18a(VHA_UL_IF_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_UL_IF_CFG.value,
                          VHA_UL_IF_CFG_WR_MASK,
                          "VHA_UL_IF_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_UL_SWG_CFG_ADR(vha_reg_base_addr),
                          vha_reg->VHA_UL_SWG_CFG.value,
                          VHA_UL_SWG_CFG_WR_MASK,
                          "VHA_UL_SWG_CFG"))
        return rv;
    if(rv = write_reg_18a(VHA_UL_CTL_ADR(vha_reg_base_addr),
                          vha_reg->VHA_UL_CTL.value,
                          VHA_UL_CTL_WR_MASK,
                          "VHA_UL_CTL"))
        return rv;

    printf("INFO: VHA%d configuration completed\n", vha_num);

    return rv;
}

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex Id, V2d Id, APB Id and sys_rate
 * @return          status
 */
#ifdef FLOW1_EN 
int configure_v2d_flow1(int v2d_num, int apb_num, int drf_clock, sys_rate_t sys_rate)
{
    int i,rv = 0;
	//g_v2d_flow1_config_tbl

    for (i = 0; i< (ARRAY_SIZE(g_v2d_flow1_config_tbl) - 4); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow1_config_tbl[i].addr), \
                    g_v2d_flow1_config_tbl[i].value, g_v2d_flow1_config_tbl[i].mask, g_v2d_flow1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow1_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow1_config_tbl[i].addr), \
                    ((((g_num_blocks_v2d_buffer) * (g_flow1_vectors_per_block[sys_rate] * 2)) - 1) << 16), g_v2d_flow1_config_tbl[i].mask, g_v2d_flow1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow1_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow1_config_tbl[i].addr), \
                    g_v2d_flow1_config_tbl[i].value | (drf_clock << 7) |sys_rate, g_v2d_flow1_config_tbl[i].mask, g_v2d_flow1_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow1_config_tbl); i++)
    {
       if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow1_config_tbl[i].addr), g_flow1_tx_strm_cnt0_offset[sys_rate], \
                g_v2d_flow1_config_tbl[i].mask, g_v2d_flow1_config_tbl[i].name))
           return rv;
    }
    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_VALUE, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), RX_GNRL_CSR_VALUE, \
            AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf ("INFO: V2D Flow 1 configuration completed");

    return rv;
}
#endif

#ifdef FLOW2_EN
int configure_v2d_flow2(int v2d_num, int apb_num, v2d_sys_rate_t in_rate, v2d_sys_rate_t out_rate, int drf_clock, int test_config, int pdpd_enable)
{
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = 0;
    if(pdpd_enable){
		
	   for(i=0;i<17;i++){
		  if(g_test_config_tbl[i][0]==in_rate & g_test_config_tbl[i][1]==out_rate )
		       test_config=i;
		  else
		       printf("Error: In_rate and out_rate not matching with any config\n");
	   }
	   printf("V2D flow2, pdpd enabled, test_config=%d\n",test_config);	
       pdpd_in_rate = g_test_config_tbl[test_config][0];
       pdpd_out_rate = g_test_config_tbl[test_config][1];
       lut_mode = g_test_config_tbl[test_config][2];
	}
	
    //~ pdpd_in_rate = g_test_config_tbl[0][0];
    //~ pdpd_out_rate = g_test_config_tbl[0][1];
    //~ lut_mode = g_test_config_tbl[0][2];
    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);

    printf ("Buffer: 0x%x", v2d_buffer_b);

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we disable this flag different VEX binary
     * will be loaded to the Tx VEX*/
    #if FILL_LEVEL_TRIGGER
        int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
        printf("fill_level_value : 0x%x", fill_level_value);
    #endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_v2d_flow2_config_tbl[i].value, g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_v2d_flow2_config_tbl[i].value | (drf_clock << 7), g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    (g_v2d_flow2_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow2_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow2_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow2_config_tbl[i].mask, g_v2d_flow2_config_tbl[i].name))
            return rv;
    }

    rv = flow2_configure_pdpd(v2d_num, apb_num, test_config, POST_C_CENTER_VALUE_UNITY_GAIN);
    printf("INFO: V2D pdpd configuration completed");

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we disable this flag different VEX binary
     * will be loaded to the TX vex fw*/
    #if FILL_LEVEL_TRIGGER
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
    #endif

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), TX_GNRL_CSR_VALUE, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), RX_GNRL_CSR_VALUE, \
            AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf("INFO: V2D Flow 2 configuration completed");

    return rv;
}
#endif

/**
 * @brief           Function configuring all the required registers from host
 * @param [in]      Vex num, V2d num APB num, drf_clock , test_config and post_filter_mode
 * @return          status value
 */
 #ifdef FLOW3_EN

int configure_v2d_flow3(int v2d_num, int apb_num, v2d_sys_rate_t in_rate, v2d_sys_rate_t out_rate, int drf_clock, int test_config, int pdpd_enable)
{
    int i, rv = 0, v2d_buffer_b = 0, pdpd_in_rate = 0, pdpd_out_rate = 0;
    lut_mode_t lut_mode = PDPD_LUT_48;
    if(pdpd_enable){
		
	   for(i=0;i<17;i++){
		  if(g_test_config_tbl[i][0]==in_rate & g_test_config_tbl[i][1]==out_rate )
		       test_config=i;
		  else
		       printf("Error: In_rate and out_rate not matching with any config\n");
	   }
	   printf("V2D flow2, pdpd enabled, test_config=%d\n",test_config);	
       pdpd_in_rate = g_test_config_tbl[test_config][0];
       pdpd_out_rate = g_test_config_tbl[test_config][1];
       lut_mode = g_test_config_tbl[test_config][2];
	}

    v2d_buffer_b = ((((g_num_blocks_v2d_buffer) * (g_vectors_per_block[drf_clock][pdpd_in_rate] * 2)) - 1) << 16);
    printf ("Buffer: 0x%x", v2d_buffer_b);

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
     #if FILL_LEVEL_TRIGGER
        // Fill level value should be 1.5 times of the B block size as per HAS
        int fill_level_value = VEC2FLIT(g_vectors_per_block[drf_clock][pdpd_in_rate]) + g_vectors_per_block[drf_clock][pdpd_in_rate];
        printf("fill_level_value : 0x%x", fill_level_value);
     #endif

    for (i = 0; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 5; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_v2d_flow3_config_tbl[i].value, g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 4; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_v2d_flow3_config_tbl[i].value | (drf_clock << 7), g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 3; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    v2d_buffer_b, g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 2; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    (g_v2d_flow3_config_tbl[i].value | (lut_mode << 12) | (pdpd_out_rate << 4) | pdpd_in_rate), \
                    g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl) - 1; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_in_rate], g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }
    for (; i < ARRAY_SIZE(g_v2d_flow3_config_tbl); i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_flow3_config_tbl[i].offset), \
                    g_tx_strm_cnt0_value[drf_clock][pdpd_out_rate], g_v2d_flow3_config_tbl[i].mask, g_v2d_flow3_config_tbl[i].name))
            return rv;
    }

    /*FILL_LEVEL_TRIGGER flag will be assosiated with corresponding VEX code as well, if we want to disable this flag
     * corresponding flag has to be disabled in the VEX code as well and VEX FW has to be re-compiled*/
    #if FILL_LEVEL_TRIGGER
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_BUF_WM_TX_START_WM_OFFSET, \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WM_EN_BF_MSK | (fill_level_value << AV2D_CSR_TX_BUF_WM_TX_START_WM_START_B_WATERMARK_BF_OFF), \
                AV2D_CSR_TX_BUF_WM_TX_START_WM_WR_MASK, "TX_START_WM"))
        return rv;
    #endif

    //~ if (FILTER_MODE == post_filter_mode)
    //~ {
        //~ if (rv = pdpd_post_c_reg_config(v2d_num, apb_num, POST_FILTER_COEFF))
        //~ {
            //~ printf("pdpd post c reg config failed");
            //~ return rv;
        //~ }
    //~ }

    rv = flow3_configure_pdpd(v2d_num, apb_num, test_config);
    printf("INFO: V2D pdpd configuration completed");

    /************************************************************************************************************/
    /* This should be the last register of Tx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_TX_CSR_TX_GNRL_CSR_OFFSET), \
                TX_GNRL_CSR_VALUE, AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
    /* This should be the last register of Rx to configure*/
    if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET + AV2D_CSR_RX_CSR_RX_GNRL_CSR_OFFSET), \
                RX_GNRL_CSR_VALUE, AV2D_CSR_RX_CSR_RX_GNRL_CSR_WR_MASK, "RX_GNRL_CSR"))
        return rv;
    /************************************************************************************************************/
    printf("INFO: V2D flow 3 configuration completed");

    return rv;
}

#endif
