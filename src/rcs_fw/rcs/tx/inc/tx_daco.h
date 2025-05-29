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
#ifndef _TX_DACO_H_
#define _TX_DACO_H_

#include "com_daco.h"
#include "ant_csr.h"
#include "cdpd.h"
#include "txsr.h"
#include "txcpm.h"
#include "txm.h"
#include "ctl.h"
#include "txg.h"
#include "duc.h"
#include "mod.h"
#include "trx_sys_csr.h"
#include "pdpd.h"
#include "av2d_axi4.h"
#include "av2d_csr.h"
#include "bfn_csr.h"
#include "vha_duc.h"
#include "vha_mod.h"
#include "vha_ant.h"
#include "vha.h"

#include "mem_fb_dmac.h"
#include "sram.h"
#include "desc.h"
#include "mem_fb.h"

#if (CPU_TX)
// num of active encoder phases in DAC
typedef enum
{
    e_ACT_ENC_PHASE_16, // 16 active encoder phases
    e_ACT_ENC_PHASE_12, // 12 active encoder phases
    e_ACT_ENC_PHASE_8,  // 8 active encoder phases
    e_ACT_ENC_PHASE_6,  // 6 active encoder phases
    e_ACT_ENC_PHASE_4,  // 4 active encoder phases
    e_ACT_ENC_PHASE_2   // 2 active encoder phases
} e_act_enc_phases_t;

typedef enum
{
    e_PDPD_LUT_SEGM_64, // all GMP/DDR Coefficient LUTs have 64 segments
    e_PDPD_LUT_SEGM_32  // all GMP/DDR Coefficient LUTs have 32 segments
} e_pdpd_lut_segm_t;

// analog RF ctrl
// DDAC, CSA, TX analog cfg, TX FSM
typedef struct
{
    struct
    {
        ddac_t *p_ddac; // Digital DAC

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } strm[NUM_STRM_PER_QUAD]; // idx: ant_idx % NUM_STRM_PER_QUAD = STRM_IDX(ant_idx)
    ant_csr_t *p_csr;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} drf_ant_blk_t;
// x=drf_ant:0..3, y=strm:0..3
// ANTx_DDACy
// ANTx_CSR

typedef struct
{
    struct
    {
        cdpd_t *p_cdpd; // Capacitive-DAC-DPD: DPD applied to CDAC input when adapting/calibrating the CDAC
        smc_t *p_smc;
        txm_t *p_txm;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    ctl_t *p_ctl;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} trx_ant_t;
// y:0..7, x=chnl:0..1
// TRX_ANTy_CDPDx
// TRX_ANTy_SMCx
// TRX_ANTy_TXMx
// TRX_ANTy_CTL

typedef struct
{
    struct
    {
        txg_t *p_txg;
        txcpm_t *p_txcpm;
        txsr_t *p_txsr;
        duc_t *p_duc;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    mod_t *p_mod;
    trx_sys_csr_t *p_trx_sys_csr;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} trx_sys_t;
// y:0..7, x=chnl:0..1,
// TRX_SYSy_TXGx
// TRX_SYSy_TXCPMx
// TRX_SYSy_TXSRx
// TRX_SYSy_DUCx
// TRX_SYSy_MOD
// TRX_SYSy_CSR

typedef struct
{
    struct
    {
        pdpd_t *p_pdpd;           // PA-DPD: DPD applied at PA input when adapting/calibrating the PA, only single band DPD supported
        av2d_axi4_t *p_av2d_axi4; // pdpd coef updt addr: AV2D_AXI4_PC_M1 and AV2D_AXI4_PC_M2. two update mode supported:
                                  // MODE1: Coefficient loading/update by writing all the 241 entries into the G-buffer.
                                  //        This is to update all the LUT coefficients, pass thru gain and the sample count
                                  // MODE2: Coefficient loading/update by writing just the last 241st entry into the G-buffer.
                                  //        This is to update only the pass thru gain coefficient and the sample count
                                  // MODE 1 and MODE 2 cannot be mixed for coefficient loading and the time interval between
                                  // a MODE 1 update followed by MODE 2 update will be at least greater than 200 clock cycles
        struct
        {
            nsip_hbi_t *p_nsip_hbi; // nsip port 1: DL
            av2d_csr_t *p_av2d_csr;
        } av2d_apb; // ctrl i/f

        struct
        {
            pdpd_cfg_reg_t cfg;
            av2d_csr_tx_csr_tx_sif_ctrl_reg_t sif;
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    bfn_csr_t *p_bfn_csr;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} v2d_t;
// y: 0..7, x=chnl: 0..1
// V2Dy_PDPD_x
// V2Dy_AV2D_AXI4_x
// V2Dy_AV2D_APB_x_NSIP_HBI_1
// V2Dy_AV2D_APB_x_CSR
// V2Dy_BFN_CSR

typedef struct
{
    struct
    {
        // JESD/VEX -> nsip -> vha_duc(iFIFO, per band DUC:w1/2/3/4) -> vha_mod -> vha_ant(oFIFO + split) -> nsip
        vha_duc_t *p_duc[MAX_NUM_BAND_PER_CHAIN]; // idx: band_idx
        vha_mod_t *p_mod;
        vha_ant_t *p_vha_ant; // each word, or flit, is 16 16i,16q samples = 512 bits
                              // cfg BURST_SIZE is for both UL&DL
                              // arb MODE is for both UL&DL
        nsip_hbi_t *p_nsip_hbi_csr;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    vha_t *p_vha;
    swg_t *p_swg; // dl_swg

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} vha_hw_t;
// y:0..7, x=chnl:0..1, z=band:0..1
// VHAy_ANTx_DUCz
// VHAy_ANTx_MOD
// VHAy_ANTx
// VHAy_ANTx_NSIP_HBI
// VHAy
// VHAy_DL_SWG

// There are 2 memories in each MEM_FB blocks: Feedback Memory (SRAM: size=1MB, datawidth=512) + DMA Descriptor (DESC: size=64KB,
// datawidth=128) there are two X channels and two correponding FBR channels, each pared x-channel & fbr-channel cover 4 antenna streams
// Used for capturing sample data from the feedback receivers, particularly for DPD adaptation
typedef struct
{
    struct
    {
        nsip_hbi_t *p_nsip_hbi; // quad_idx(ant_idx) % NUM_FBR_CHAIN_PER_DRF
        mem_fb_dmac_t *p_dmac;  // quad_idx(ant_idx) % NUM_FBR_CHAIN_PER_DRF

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } fbr_chain[NUM_FBR_CHAIN_PER_DRF];
    uint32_t mem_fb_sram; // Feedback Memory (MEM_FB SRAM sram.h): Used for capturing sample data from the feedback receivers, particularly
                          // for DPD adaptation
    mem_fb_t *p_mem_fb;   // cfg
    // DMA Descriptor Memory (MEM_FB DESC): Used for building DMA descriptor linked lists for transferring of Calibration or Feedback memory
    // to their proper destinations for processing (e.g. to VEX core to DPD adaptation, or to JESD for external FBR streaming).
    desc_t *p_desc; // descriptor memory needs to be initialized with the desired linked list to be used by the local DMAs.

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} mem_fb_cap_t;
// x:0..1, y=fbr_chain:0..1
// MEM_FBx_SRAM_BASE
// MEM_FBx_CONFIG
// MEM_FBx_NSIP_HBI_y
// MEM_FBx_DMAC_y
// MEM_FBx_DESC

typedef struct
{
    // DRF
    drf_ant_blk_t drf_ant[NUM_QUAD]; // QUAD_IDX(ant_idx)
    trx_ant_t trx_ant[NUM_TRX_GRP];  // TRX_GRP_IDX(ant_idx)
    trx_sys_t trx_sys[NUM_TRX_GRP];  // TRX_GRP_IDX(ant_idx)

    // FB:
    fb_ant_t fb_ant[NUM_DRF]; // DRF_IDX(ant_idx)
    fb_sys_t fb_sys[NUM_DRF]; // DRF_IDX(ant_idx)

    // V2D:
    v2d_t v2d[NUM_TRX_GRP]; // TRX_GRP_IDX(ant_idx)

    // VHA:
    vha_hw_t vha_hw[NUM_TRX_GRP]; // TRX_GRP_IDX(ant_idx)

    // capturing of calibration sample data from RX and TX chains:
    mem_cap_t mem_cap[NUM_DRF]; // DRF_IDX(ant_idx)

    // capturing sample data from FBRs:
    mem_fb_cap_t mem_fb_cap[NUM_DRF]; // DRF_IDX(ant_idx)
} hw_t;

typedef struct
{
    bool is_first_cfg;                   // is first config
    sys_params_t sys_params;             // parameters common accross quads
    quad_params_t quad_params[NUM_QUAD]; // QUAD_IDX(ant_idx)
    drf_params_t drf_params[NUM_DRF];    // QUAD_IDX(ant_idx)
    hw_t hw;
} daco_t;

extern daco_t tx_daco;

/**
 * @brief           clear TX core daco
 * @param [in]      none
 * @return          none
 */
void tx_daco_clear ();
#endif

#endif
