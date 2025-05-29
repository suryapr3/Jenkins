/* INTEL CONFIDENTIAL
 *
 * Copyright  2023 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/
#ifndef _COM_DACO_H_
#define _COM_DACO_H_

#include "com_definitions.h"
#include "com_platform.h"
#include "cmem_sram.h"
#include "cmem_cfg.h"
#include "nleq.h"
#include "rxm.h"
#include "ddac.h"
#include "smc.h"
#include "swg.h"
#include "caldac.h"
#include "fb_ant_local.h"
#include "rxg.h"
#include "ddc.h"
#include "dmod.h"
#include "fb_sys_local.h"
#include "sram_cap.h"
#include "mem_cap_wrap.h"
#include "mem_cap_cfg.h"
#include "test.h"
#include "pll_local.h"
#include "nsip_hbi.h"
#include "com_rf_def.h"

// TODO: might merge into system level definitions:
#define MAX_NUM_BAND_PER_CHAIN (2)
#define NUM_ANT                (16)
#define NUM_QUAD               (4)
#define NUM_DRF                (2)                          // east, west
#define NUM_FBR_CHAIN_PER_DRF  (2)                          // chain0: from ant0/1/2/3 or 8/9/10/11, chain1: from ant4/5/6/7 or 12/13/14/15
#define NUM_ANT_PER_DRF        (NUM_ANT / NUM_DRF)          // 8
#define NUM_STRM_PER_QUAD      (NUM_ANT / NUM_QUAD)         // 4
#define NUM_CHNL_PER_GRP       (2)                          // GRP: v2d, vha, trx_ant, trx_sys
#define NUM_TRX_GRP            (NUM_ANT / NUM_CHNL_PER_GRP) // 8
#define NUM_GRP_PER_QUAD       (NUM_TRX_GRP / NUM_QUAD)     // 2
#define NUM_DRF_ANT_BLK        (NUM_ANT / NUM_QUAD)         // 4, drf_ant
#define NUM_QUAD_PER_DRF       (NUM_QUAD / NUM_DRF)         // 2

/*
 * antenna indexing at system level:                    ant_idx = 0..15
 * antenna indexing at quad level:                      strm_idx = 0..3
 * antenna indexing at V2D/VHA/TRX_ANT/TRX_SYS level:   chnl_idx = 0..1
 */
// indexing macros
#define QUAD_IDX(ant_idx)           ((ant_idx) / NUM_QUAD)
#define STRM_IDX(ant_idx)           ((ant_idx) % NUM_STRM_PER_QUAD)
#define TRX_GRP_IDX(ant_idx)        ((ant_idx) / NUM_CHNL_PER_GRP)
#define DRF_IDX(ant_idx)            ((ant_idx) / NUM_ANT_PER_DRF)
#define CHNL_IDX(ant_idx)           ((ant_idx) % NUM_CHNL_PER_GRP)
#define ANT_IDX(quad_idx, strm_idx) ((quad_idx)*4 + (strm_idx))

#if (CPU_TX) || (CPU_RX)
// helper macros for easy daco initialization:
#define DACO_MC_3_PARAM_(name, name1, idx)                      name = name1##idx
#define DACO_MC_4_PARAM_(name, name1, name2, idx)               name = name1##idx##_##name2
#define DACO_MC_5_PARAM_(name, name1, name2, idx1, idx2)        name = name1##idx1##_##name2##idx2
#define DACO_MC_6_PARAM_(name, name1, name2, name3, idx1, idx2) name = name1##idx1##_##name2##idx2##_##name3
#define DACO_MC_3_PARAM(name, name1, idx)                       DACO_MC_3_PARAM_ (name, name1, idx)
#define DACO_MC_4_PARAM(name, name1, name2, idx)                DACO_MC_4_PARAM_ (name, name1, name2, idx)
#define DACO_MC_5_PARAM(name, name1, name2, idx1, idx2)         DACO_MC_5_PARAM_ (name, name1, name2, idx1, idx2)
#define DACO_MC_6_PARAM(name, name1, name2, name3, idx1, idx2)  DACO_MC_6_PARAM_ (name, name1, name2, name3, idx1, idx2)

// params common to all quads:
typedef struct
{
    e_sys_clk_t clk_rate;   // drf clock rate
    uint16_t act_ant_mask;  // active ANTs, used by dynamic sequences
    uint16_t jesd_ant_mask; // JESD configured ANT mask
    uint16_t rf_ant_mask;   // lineup configured ANT mask
    uint8_t quad_mask;
} sys_params_t;

// params common to specific quad:
typedef struct
{
    // bool has_dual_chnl;
    uint32_t drf_rate : 8;   // DRF rate selection to table com_drf_rate_conf_lut
    uint32_t topology : 3;   // topology selection to table *_topology_lut
    uint32_t fifo_delay : 4; // index to table tx_v2d_start_dly_lut, use 4-bit for now, might need to extend based on usecases supported
    uint32_t drf_filter_mode : 1; // set DUC/DDC filter stage selection mode: 0:auto or 1:manual
    uint32_t lpbk_mode : 3;       // e_loopback_mode_type_t
    uint32_t drf_mixer_freq : 24; // DRF mixing frequency, in KHz
    //  duplex_mod: tdd/fdd
    //  ibw
    //  obw
    //  num_cc
    //  rf_band
    //  has_cfr
    //   cfr_mod
    //  pimc // for FDD
} quad_com_params_t;

// VHA specific params:
typedef struct
{
    //  UL/DL:
    uint32_t vha_rate : 4;        // rate_sel vha rate selection to table com_vha_rate_cfg_lut
    uint32_t vha_filter_mode : 1; // stage_mod set VHA DUC/DDC filter stage selection mode: 0:auto or 1:manual
    uint32_t band0_freq : 24;     // Center channel frequency for band 0 during band combining(VHA), in KHz
    uint32_t band1_freq : 24;     // Center channel frequency for band 1 during band combining(VHA), in KHz
    uint32_t vha_mix_mask : 5;    // bit 0..1: active bands, bit 2: band0 conj indication, bit 3: band1 conj indication, bit 4: use same swg
                                  // indication. this is set by vha_swg_cfg
    // UL:
    // UL/DL:
    //  nco_conj_en: If using demodulation, conjugation needs to be specified.
    //               If Dual Band-Sharing is enabled, then conjugation must be enabled and for only Band0 or Band1 (never both).
    //  nco_params:
    //      DL: If using modulation, need parameters for DL_SWG0 configuration, and for Dual-Band, need DL_SWG1 configuration, too.
    //      UL: If using demodulation, need parameters for UL_SWG0 configuration, and for Dual-Band, need UL_SWG1 configuration, too.
    //  ds_mode: split band I/Q samples to two different destinations (split same oFIFO output to two), use N1/N2 to specify how many bursts
    //  (one burst = # of flits per burst) alternate to each destination: byp/en
    //           ???used for supporting 2 term and 4 term PDPD operating modes???
    // DL:
    //  dual_cast: all I/Q samples (ie: oFIFOs from same ant are duplicated copies ) sent to two different destination: ena/dis
    // UL/DL:
    //  nsip
    // add params
} vha_params_t;

// V2D specific params:
typedef struct
{
    uint32_t strm_cfg : 4; // index to subtable of v2d_strm_cfg_lut. FIXME: set to 4 bits for now, probably need extend it in
                           // the future based on different topologies supported
#if (CPU_TX)
    uint32_t tcnt_byp_en;      // Sample Count Trigger Value for enabling PDPD bypass
    uint32_t tcnt_byp_dis;     // Sample Count Trigger Value for disabling PDPD bypass
    uint32_t tcnt_zero_en;     // Sample Count Trigger Value for enabling PDPD zerostuffing
    uint32_t tcnt_zero_dis;    // Sample Count Trigger Value for disabling PDPD zerostuffing
    uint32_t tcnt_updt_c_lut;  // Sample Count Trigger Value for updating C_LUT
    uint32_t tcnt_updt_nl_lut; // Sample Count Trigger Value for updating NL_LUT
    uint32_t tcnt_updt_pt;     // Sample Count Trigger Value for updating PASSTHROUGH
    // DPD:
    //  dpd_complexity
    //  dpd_lut_segs
    uint32_t pdpd_op_mode : 2; // index to table tx_pdpd_pc_sel_lut, as type e_pdpd_op_mod_t
    uint32_t pdpd_mode : 3;    // index to table tx_pdpd_mod_lut, as type e_pdpd_mod_sel_t
    uint32_t pdpd_delay : 4;   // index to table tx_pdpd_dly_lut to select extra term delay/advance in clock respect to other terms, or
                               // passthrough delay.
    uint32_t pdpd_rate : 3;    // index to subtable of tx_pdpd_pc_sel_lut
    // pdpd_cfg; // pdpd_cfg_reg_t
    //  DNE, DE, DGNE, DGE, DPP, DGPP:
    //      gmp_init
    //      gmp_cfg
    //      ddr_init
    //      ddr_cfg
    //      cmn_cfg
    //      nl_init
    //      nl_cfg
    //      pt_coef
    //   ALL Modes:
    //       nsip
#endif
} v2d_params_t;

// DRF specific params in quad:
typedef struct
{
    // add params
} drf_params_t;

// calibration/CALDAC memory (CMEM) --- holding injected test signal
// rx/tx ant_idx 0/1/2/3 -> fbr0/fbr_chain 0
// rx/tx ant_idx 4/5/6/7 -> fbr0/fbr_chain 1
// rx/tx ant_idx 8/9/10/11 -> fbr1/fbr_chain 0
// rx/tx ant_idx 12/13/14/15 -> fbr1/fbr_chain 1

// TODO: common note to all daco related struc definitions:
//       might consider to move some of those anonymous structs out or use another typedef to help directly address to them if necessary
typedef struct
{
    struct
    {
        uint32_t cmem_sram; // cmem_sram.h, for injecting wideband seq for SMC cal
        cmem_cfg_t *p_cmem_cfg;
        nleq_t *p_nleq; // track shdw
        rxm_t *p_rxm;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } fbr_chain[NUM_FBR_CHAIN_PER_DRF]; // QUAD_IDX(ant_idx) % NUM_FBR_CHAIN_PER_DRF
    ddac_t *p_ddac_top;
    ddac_t *p_ddac_bot;
    smc_t *p_smc_even_top;
    smc_t *p_smc_even_bot;
    smc_t *p_smc_odd_top;
    smc_t *p_smc_odd_bot;
    swg_t *p_swg_even; // FIXME: [2]: 0/1: mixed together (dual tone) for even CALDAC
    swg_t *p_swg_odd;  // FIXME: [2]: 0/1: mixed together (dual tone) for odd CALDAC
    caldac_t *p_caldac;
    fb_ant_local_t *p_csr; // TODO: double check // track shdw

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} fb_ant_t;
// x=fb_ant:0..1, y=chain:0..1
// FB_ANTx_CMEMy_SRAM_BASE
// FB_ANTx_CMEM_CFGy
// FB_ANTx_NLEQy
// FB_ANTx_RXMy
// FB_ANTx_DDAC_TOP
// FB_ANTx_DDAC_BOT
// FB_ANTx_SMC_EVEN_TOP
// FB_ANTx_SMC_EVEN_BOT
// FB_ANTx_SMC_ODD_TOP
// FB_ANTx_SMC_ODD_BOT
// FB_ANTx_SWG_EVEN
// FB_ANTx_SWG_ODD
// FB_ANTx_CALDAC
// FB_ANTx_CSR

typedef struct
{
    struct
    {
        rxg_t *p_rxg;
        ddc_t *p_ddc;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } fbr_chain[NUM_FBR_CHAIN_PER_DRF]; // QUAD_IDX(ant_idx) % NUM_FBR_CHAIN_PER_DRF
    dmod_t *p_dmod;
    swg_t *p_swg0; // FIXME: [6]: 0:FB0, 1:FB1, 2:TX MOD Quad0/1, 3:RX DMOD Quad0/1, 4: TX MOD Quad 1, 5: RX DMOD Quad 1
                   // parameters: fb_nco, tx_nco, rx_nco
    fb_sys_local_t *p_ctl;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} fb_sys_t;
// x:0..1, y=chain:0..1
// FB_SYSx_RXGy
// FB_SYSx_DDCy
// FB_SYSx_DMOD
// FB_SYSx_SWG0
// FB_SYSx_CTL

// There are 2 memories in each MEM_FB blocks
// there is 1 memory each in the MEM_CAP blocks, with size=1.75MB (expandable to 2MB, using sector size 256KB), datawidth=128
// Used for capturing of calibration sample data from RX and TX chains (not for Feedback Receiver sample data)
typedef struct
{
    uint32_t mem_cap_sram;     // Calibration Capture Memory (sram_cap.h), MEM_CAP memories do not need to be initialized.
    mem_cap_wrap_t *p_mem_cap; // mem_cap_wrap.h
    mem_cap_cfg_t *p_mem_cap_cfg;
    test_t *p_mem_cap_test; // test.h
    pll_local_t *p_pll_local;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} mem_cap_t;
// x:0..1
// MEM_CAPx_SRAM_BASE
// MEM_CAPx
// MEM_CAPx_CFG
// MEM_CAPx_TEST
// MEM_CAPx_ANALOG_PLL

typedef struct
{
    quad_com_params_t com_params;
    vha_params_t vha_params;
    v2d_params_t v2d_params;
} quad_params_t;
#endif // (CPU_TX) || (CPU_RX)

#endif // _COM_DACO_H_
