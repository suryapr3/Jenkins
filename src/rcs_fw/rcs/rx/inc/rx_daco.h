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
#ifndef _RX_DACO_H_
#define _RX_DACO_H_

#include "com_daco.h"
#include "av2d_csr.h"
#include "bfn_csr.h"
#include "vha_ddc.h"
#include "vha_dmod.h"
#include "vha_ant.h"
#include "vha.h"
#include "adc_dig.h"
#include "asc.h"
#include "adc_cpu.h"
#include "ant_csr.h"
#include "ctl.h"
#include "trx_sys_csr.h"

#if (CPU_RX)
typedef enum
{
    e_ADC_FSM_RESET = 0,
    e_ADC_FSM_BOOTING,
    e_ADC_FSM_IDLE,
    e_ADC_FSM_BUSY,
    e_ADC_FSM_MAX
} e_adc_fsm_t;

// analog RF ctrl
typedef struct
{
    struct
    {
        adc_dig_t *p_adc_dig;
        asc_t *p_asc; // ASC registers are just W[17][23] and C[17] (other registers are XTalk)

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } strm[NUM_STRM_PER_QUAD]; // idx: ant_idx % NUM_STRM_PER_QUAD = STRM_IDX(ant_idx)
    uint32_t adc_cpu;          // adc_cpu.h
    adc_dig_t *p_adc_dig_fb;
    asc_t *p_asc_fb;
    ant_csr_t *p_csr;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} drf_ant_blk_t;
// x=drf_ant:0..3, y=strm:0..3
// ANTx_ADC_DIGy
// ANTx_ASCy
// ANTx_CPU_BASE
// ANTx_ADC_DIG_FB
// ANTx_ASC_FB
// ANTx_CMFF
// ANTx_CSR

typedef struct
{
    struct
    {
        nleq_t *p_nleq;
        smc_t *p_smc;
        rxm_t *p_rxm;

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
// TRX_ANTy_NLEQx
// TRX_ANTy_SMCx
// TRX_ANTy_RXMx
// TRX_ANTy_CTL

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
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    dmod_t *p_dmod;
    trx_sys_csr_t *p_trx_sys_csr;

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} trx_sys_t;
// y:0..7, x=chnl:0..1,
// TRX_SYSy_RXGx
// TRX_SYSy_DDCx
// TRX_SYSy_DMOD
// TRX_SYSy_CSR

typedef struct
{
    struct
    {
        struct
        {                           // ctrl i/f
            nsip_hbi_t *p_nsip_hbi; // nsip port 0: UL
            av2d_csr_t *p_av2d_csr;
        } av2d_apb;

        struct
        {
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
// V2Dy_AV2D_APB_x_NSIP_HBI_0
// V2Dy_AV2D_APB_x_CSR
// V2Dy_BFN_CSR

typedef struct
{
    struct
    {
        // vha_dmod(iFIFO ->bands) -> vha_ddc(per band:w1/2/3/4) -> vha_ant(oFIFO + split) -> nsip -> JESD/VEX
        vha_ddc_t *p_ddc[MAX_NUM_BAND_PER_CHAIN]; // idx: band_idx
        vha_dmod_t *p_dmod;
        vha_ant_t *p_vha_ant;
        nsip_hbi_t *p_nsip_hbi_csr;

        struct
        {
            // FIXME: keep tracking of previous value of registers for next update
        } regs;
    } chnl[NUM_CHNL_PER_GRP]; // idx: ant_idx % NUM_CHNL_PER_GRP = CHNL_IDX(ant_idx)
    vha_t *p_vha;
    swg_t *p_swg; // ul_swg

    struct
    {
        // FIXME: keep tracking of previous value of registers for next update
    } regs;
} vha_hw_t;
// y:0..7, x=chnl:0..1, z=band:0..1
// VHAy_ANTx_DDCz
// VHAy_ANTx_DMOD
// VHAy_ANTx
// VHAy_ANTx_NSIP_HBI
// VHAy
// VHAy_UL_SWG

typedef struct
{
    // bool fbr_en;
    e_adc_fsm_t adc_fsm;
    uint16_t cal_req;
    uint16_t cal_done;
    uint32_t digrf_mixer_freq;
    uint32_t fbr_idx;
} adc_params_t;

typedef struct
{
    // DRF:
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
} hw_t;

typedef struct
{
    bool is_first_cfg;                   // is first config
    sys_params_t sys_params;             // common parameters accross quads
    quad_params_t quad_params[NUM_QUAD]; // QUAD_IDX(ant_idx)
    adc_params_t adc_params[NUM_QUAD];   // adc parameters;
    hw_t hw;
} daco_t;

extern daco_t rx_daco;

/**
 * @brief           clear RX core daco
 * @param [in]      none
 * @return          none
 */
void rx_daco_clear ();
#endif

#endif
