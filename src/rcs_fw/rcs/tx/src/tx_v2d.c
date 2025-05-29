/* INTEL CONFIDENTIAL
 *
 * Copyright  2024 Intel Corporation All Rights Reserved.
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
#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_assert.h"
#include "com_print.h"
#include "tx_v2d.h"
#include "com_lock.h"
#include <stddef.h>
#include "com_static_data_table.h"
#include "tx_static_data_table.h"
#include "com_msgs_enum.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
// FIXME:
#define TX_V2D_FIXME 0

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
typedef enum
{
    e_JESD_RX_START_QN, // JesdRxStartQN
    e_TRXANT_VALID,     // JESD link
    e_BFNE,             // BFN Event
    e_NOT_USED
} e_v2d_tx_fifo_start_src_t;

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
/**
 * @brief           helper func to calculate offset for accessing tx_v2d_if_params_lut
 * @param [in]      num_strm: num of stream used on this I/F, eg, this is num of vex cores when connected to VEX
 * @return          offset in tx_v2d_if_params_lut indexing
 */
static INTRINSIC_ALWAYS_INLINE uint8_t get_v2d_if_param_ofs (uint8_t num_strm);

/**
 * @brief           Load PDPD coefficient LUTs
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_load_coef_lut (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                       uint8_t const chnl);

/**
 * @brief           config PDPD extra-terms
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_cfg_extra_term (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                        uint8_t const chnl);

/**
 * @brief           config/enable LUT usage and rate
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_pdpd_lut_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                      uint8_t const chnl);

/**
 * @brief           Configure DPD sample interface
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_sif_ctrl (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                  uint8_t const chnl);

/**
 * @brief           PDPD Interface Configuration
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_pif_ctrl (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                  uint8_t const chnl);

/**
 * @brief           set A/C flow input buffer pointer location and stream counter
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_nsip_malloc_ac (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                        uint8_t const chnl);

/**
 * @brief           set B flow input buffer pointer location and stream counter
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_nsip_malloc_b (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                       uint8_t const chnl);

/**
 * @brief           enable D flow and set stream counter
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_nsip_malloc_d (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                       uint8_t const chnl);

/**
 * @brief           Start TX buffer based on a watermark (FIFO fill level) instead of JESD start (or BFN) triggers.
 *                  Note: For normal JESD triggered TX buffer start, leave this register at default (disabled).
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_buf_wm (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl);

/**
 * @brief           Start TX buffer based on JESD start triggers.
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_jesdrx_start_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                          uint8_t const chnl);

/**
 * @brief           enable the TX configuration
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
static INTRINSIC_ALWAYS_INLINE void v2d_en (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl);
/***********************************************
 * STATIC FUNCTION DEFINITIONS                  *
 ***********************************************/
uint8_t get_v2d_if_param_ofs (uint8_t num_strm)
{
    uint8_t ofs = 0;
    if (num_strm == 4)
    {
        ofs = 3;
    }
    else if (num_strm == 2)
    {
        ofs = 1;
    }
    return ofs;
}

/**
 * for G flow writes via AXI:
 * Mode1: offset address range via AXI: 0x000 to 0x3fff
 * Mode2: offset address range via AXI: 0x4000 to 0x7fff
 * see HAS p644
 */
void v2d_load_coef_lut (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
#if 0
    // step 2-11
    // TODO: need to check how the GMP/DDR/NL LUT is arranged and change below loops accordingly
    // TODO: check below condition is necessary, especially for NDPF:
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    if ((e_PDPD_MOD_ND != pdpd_mode) && (e_PDPD_MOD_NDPF != pdpd_mode))
    {
        pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t gmp_c = {.value = PDPD_GMP_DYNAMIC_SHDW_GMP_C_SHDW_DEFAULT};
        pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t gmp_shift = {.value = PDPD_GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_DEFAULT};
        pdpd_gmp_static_reg_t gmp_static = {.value = PDPD_GMP_STATIC_DEFAULT};
        uint32_t const ofs = (PDPD_GMP_DYNAMIC_SHDW1_GMP_C_SHDW0_OFFSET - PDPD_GMP_DYNAMIC_SHDW0_GMP_C_SHDW0_OFFSET) / 4;
        pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t ddr_c = {.value = PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_DEFAULT};
        pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t ddr_shift = {.value = PDPD_DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_DEFAULT};
        pdpd_ddr_static_reg_t ddr_static = {.value = PDPD_DDR_STATIC_DEFAULT};
        uint32_t const ddr_ofs = PDPD_DDR_DYNAMIC_SHDW1_DDR_C_SHDW0_OFFSET - PDPD_DDR_DYNAMIC_SHDW0_DDR_C_SHDW0_OFFSET;
        pdpd_nl_c_shdw_reg_t nl_c = {.value = PDPD_NL_C_SHDW_DEFAULT};
        pdpd_passthru_c_shdw_reg_t passthrou_c = {.value = PDPD_PASSTHRU_C_SHDW_DEFAULT};
        pdpd_post_c_reg_t post_c = {.value = PDPD_POST_C_DEFAULT};
        pdpd_post_c_center_reg_t post_c_center = {.value = PDPD_POST_C_CENTER_DEFAULT};

        pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t *p_gmp_c = &p_v2d->chnl[chnl].p_pdpd->GMP_DYNAMIC_SHDW0_GMP_C_SHDW[0];
        pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t *p_gmp_shift = &p_v2d->chnl[chnl].p_pdpd->GMP_DYNAMIC_SHDW0_GMP_SHIFT_SHDW;
        pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t *p_ddr_c = &p_v2d->chnl[chnl].p_pdpd->DDR_DYNAMIC_SHDW0_DDR_C_SHDW[0];
        pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t *p_ddr_shift = &p_v2d->chnl[chnl].p_pdpd->DDR_DYNAMIC_SHDW0_DDR_SHIFT_SHDW;

        // Optional: Load all Generalized Memory Polynomial (GMP) tap coefficients with initial values as needed
        // TODO: replace magic num (32, 65) with defines
        //       65 is the num of interpolation point plus 1
        for (uint32_t m = 0; m < 32; m++)
        {
            // GMP Tap coefficients
            for (uint32_t n = 0; n < 65; n++)
            {
                gmp_c.Q = TX_V2D_FIXME; // FIXME using coef LUT table?
                gmp_c.I = TX_V2D_FIXME;
                p_gmp_c[m * ofs][n] = gmp_c;
            }

            // GMP Tap coefficient right shift (e. scaling) values
            gmp_shift.SHIFT = TX_V2D_FIXME; // FIXME gmp shift LUT table?
            p_gmp_shift[m * ofs] = gmp_shift;
            // Configure/Enable GMP taps
            gmp_static.ENABLE = TX_V2D_FIXME;
            gmp_static.SEL_MAG = TX_V2D_FIXME;
            gmp_static.CONJ_EN = TX_V2D_FIXME;
            gmp_static.SEL_LIN = TX_V2D_FIXME;
            p_v2d->chnl[chnl].p_pdpd->GMP_STATIC[m] = gmp_static;
        }

        // Optional: Load all Dynamic Deviation Reduction (DDR) tap coefficients with initial values as needed
        // TODO: replace magic num (32, 65) with defines
        for (uint32_t m = 0; m < 16; m++)
        {
            // I and Q DDR Tap coefficients
            for (uint32_t n = 0; n < 65; n++)
            {
                // GMP Tap coefficients
                ddr_c.Q = TX_V2D_FIXME; // FIXME using coef LUT table?
                ddr_c.I = TX_V2D_FIXME;
                p_ddr_c[m * ddr_ofs][n] = ddr_c;
            }
            // DDR Tap coefficient right shift (e. scaling) values
            ddr_shift.SHIFT = TX_V2D_FIXME; // FIXME ddr shift LUT table?
            p_ddr_shift[m * ddr_ofs] = ddr_shift;
            // Configure/Enable DDR taps
            // linear smpls:
            ddr_static.ENABLE = TX_V2D_FIXME; // FIXME
            ddr_static.SEL_MAG = TX_V2D_FIXME;
            ddr_static.CONJ_EN = TX_V2D_FIXME;
            ddr_static.SEL_LIN = TX_V2D_FIXME;
            // squared smpls:
            ddr_static.SQU_EN = TX_V2D_FIXME;
            ddr_static.SQU_SRC = TX_V2D_FIXME;
            ddr_static.SEL_SQU = TX_V2D_FIXME;
            p_v2d->chnl[chnl].p_pdpd->DDR_STATIC[m] = ddr_static;
        }
        // Optional: Load Nonlinear Magnitude LUT coefficients with initial values as needed
        // TODO: replace magic num (65) with defines
        // Nonlinear Mag. LUT coefficients
        for (uint32_t n = 0; n < 65; n++)
        {
            nl_c.NL = TX_V2D_FIXME; // FIXME NL LUT?
            p_v2d->chnl[chnl].p_pdpd->NL_C_SHDW[n] = nl_c;
        }

        // Load other configurations as needed
        // I and Q Passthrough coefficient. passthrough term is linear term to be added to non-linear terms
        passthrou_c.Q = TX_V2D_FIXME; // FIXME LUT
        passthrou_c.I = TX_V2D_FIXME; // FIXME
        // passthrou delay value see PASSTHRU_DLY in pdpd_cfg_reg_t
        p_v2d->chnl[chnl].p_pdpd->PASSTHRU_C_SHDW = passthrou_c;
    }
    if (e_PDPD_MOD_ND != pdpd_mode)
    {
        // Load Post Filter LUT coefficients with initial values
        // PDPD Post Filter tap coefficients
        for (uint32_t n = 0; n < 8; n++)
        {
            post_c.C = TX_V2D_FIXME; // FIXME POST_C LUT?
            p_v2d->chnl[chnl].p_pdpd->POST_C[n] = post_c;
        }
        // PDPD Post Filter center tap coefficient
        post_c_center.C = TX_V2D_FIXME; // FIXME
        p_v2d->chnl[chnl].p_pdpd->POST_C_CENTER = post_c_center;
    }
    FW_PRINT (FW_DEBUG, "v2d_load_coef_lut is done");
#endif
}

void v2d_cfg_extra_term (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    bool const gang_mod = get_tf (tx_pdpd_mod_lut, pdpd_mode, gang_mod);
    bool const extra_static_en = get_tf (tx_pdpd_mod_lut, pdpd_mode, extra_static_en);

    if (extra_static_en)
    {
        uint8_t const pdpd_delay = p_quad_params->v2d_params.pdpd_delay;
        pdpd_extra_static_reg_t reg = {.value = PDPD_EXTRA_STATIC_DEFAULT};
        reg.EN = extra_static_en;
        reg.SEL = get_tf (tx_pdpd_dly_lut, pdpd_delay, et_dly);  // Extra terms delay with respect to other terms FIXME: clock or sample?
        reg.ADVANCE = get_tf (tx_pdpd_dly_lut, pdpd_delay, adv); // 0: dealy, 1: advance
        p_v2d->chnl[chnl].p_pdpd->EXTRA_STATIC = reg;
        // in case of in ganging mode, config PDPD1 as well:
        if (gang_mod)
        {
            reg.value = PDPD_EXTRA_STATIC_DEFAULT;
            reg.EN = 0; // no support of extra term on PDPD1 in ganging mode
            p_v2d->chnl[chnl + 1].p_pdpd->EXTRA_STATIC = reg;
        }
    }

    FW_PRINT (FW_DEBUG, "v2d_cfg_extr_term is done");
}

void v2d_pdpd_lut_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    uint8_t const pdpd_delay = p_quad_params->v2d_params.pdpd_delay;
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    e_pdpd_op_mod_t const pdpd_op_mode = p_quad_params->v2d_params.pdpd_op_mode;
    uint8_t const pdpd_rate = p_quad_params->v2d_params.pdpd_rate;
    e_pc_lut_mod_t const lut_mod = get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, lut_mod);
    bool const gang_mod = get_tf (tx_pdpd_mod_lut, pdpd_mode, gang_mod);

    pdpd_cfg_reg_t cfg = {.value = PDPD_CFG_DEFAULT};
    cfg.value &= get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) | ~(PDPD_CFG_CLUT_SEGMENTS_BF_MSK - 1);
    // cfg.EXT_CTRL_BYPASS
    // cfg.EXT_CTRL_ZERO_STUFF
    // cfg.EXT_CTRL_UPDATE_C_LUT
    // cfg.EXT_CTRL_UPDATE_NL_LUT
    // cfg.EXT_CTRL_UPDATE_PASSTHRU
    // cfg.NLMAG_ENABLE
    // cfg.NLMAG_INTERP
    cfg.CLUT_SEGMENTS = e_PDPD_LUT_SEGM_64; // FIXME: check with Bruce on this
    cfg.CLUT_INTERP = get_tf (tx_pdpd_cfg_lut, 0, clut_interp_en);
    cfg.CLUT_DUPL = lut_mod;
    cfg.PASSTHRU_DLY = get_tf (tx_pdpd_dly_lut, pdpd_delay, pt_dly); // 7-bit Passthru sample delay FIXME: delay in samples or clock?
    cfg.GANG_IN_EN = gang_mod;
    cfg.GANG_OUT_EN = 0; // 0: Ganged terms are NOT output to the partner PDPD instance.
    p_v2d->chnl[chnl].p_pdpd->CFG = cfg;
    // in case of in ganging mode, config PDPD1 as well:
    if (gang_mod)
    {
        cfg.GANG_IN_EN = 0;
        cfg.GANG_OUT_EN = gang_mod;
        p_v2d->chnl[chnl + 1].p_pdpd->CFG = cfg;
    }
    FW_PRINT (FW_DEBUG, "v2d_pdpd_lut_cfg is done");
}

// sample I/F control
void v2d_sif_ctrl (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    uint8_t const drf_rate = p_quad_params->com_params.drf_rate;

    // per HAS, flow C is configured at DPD egress rate (ie, DPD output sampling rate)
    //          flow B is configured at DPD ingress rate
    p_v2d->chnl[chnl].regs.sif.TX_SYS_RATE = get_tf (com_drf_rate_conf_lut, drf_rate, sys_rate);
    p_v2d->chnl[chnl].regs.sif.DRF_1P5G_CLK = get_tf (com_drf_rate_conf_lut, drf_rate, f_clk);
    if ((e_PDPD_MOD_ND == pdpd_mode) || (e_PDPD_MOD_DPP == pdpd_mode) || (e_PDPD_MOD_DGPP == pdpd_mode))
    {
        p_v2d->chnl[chnl].regs.sif.TX_USE_PD = 0;
    }
    else
    {
        p_v2d->chnl[chnl].regs.sif.TX_USE_PD = 1;
    }
    // Tx to Rx Loopback. When set, Tx data will be looped back to Rx side, nsip_hbi 0, on DRF Sample Interface.
    p_v2d->chnl[chnl].regs.sif.TX_RX_LPBK = 0;

    p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_SIF_CTRL = p_v2d->chnl[chnl].regs.sif;

    FW_PRINT (FW_DEBUG, "v2d_sif_ctrl is done");
}

// PDPD I/F control
void v2d_pif_ctrl (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    if (e_PDPD_MOD_ND != pdpd_mode)
    {
        e_pdpd_op_mod_t const pdpd_op_mode = p_quad_params->v2d_params.pdpd_op_mode;
        uint8_t const pdpd_rate = p_quad_params->v2d_params.pdpd_rate;
        bool const gang_mod = get_tf (tx_pdpd_mod_lut, pdpd_mode, gang_mod);

        // PDPD Interface Configuration
        av2d_csr_pif_ctrl_reg_t pif = {.value = AV2D_CSR_PIF_CTRL_DEFAULT};
        // PDPD Ingress Sampling Rate. This field controls PDPD sampling rate on input of PDPD.
        // This control affects data pattern on PDPD B Interfaces.
        pif.PD_IN_SYS_RATE = get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, in_rate); // 491Msps – 11.80Gsps
        // PDPD Egress Sampling Rate. This field controls PDPD sampling rate on output of PDPD.
        // This control affects data pattern on PDPD C Interface and PDPD output.
        pif.PD_OUT_SYS_RATE = get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, out_rate); // 491Msps – 11.80Gsps
        pif.PD_GANG_MODE = gang_mod;
        pif.PD_CAP_MEM_SEL = get_tf (tx_pdpd_mod_lut, pdpd_mode, pd_cap_mem_sel);
        // PDPD Extra Term Only. This bit enables the mode which has only extra term traffic, C path, and there is no main term
        // traffic, B path.
        pif.PD_EXTRA_ONLY = get_tf (tx_pdpd_mod_lut, pdpd_mode, pd_extra_only);
        // e_pc_lut_mod_t: 12/24/48 LUTs
        pif.PC_LUT_MODE = get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, lut_mod); // PDPD Coefficient Update LUT Mode.
        // This is the count value to timeout HBI and AXI data transfers for PDPD Coefficient update.
        // pif.PC_TIMEOUT_CNT = 0xFFFF;  // Default set to max
        p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->PIF_CTRL = pif;
        // TODO: check this is needed
        if (gang_mod)
        {
            p_v2d->chnl[chnl + 1].av2d_apb.p_av2d_csr->PIF_CTRL = pif;
        }
        FW_PRINT (FW_DEBUG, "v2d_pif_ctrl is done");
    }
}

// A/C flow NSIP Memory Allocation
void v2d_nsip_malloc_ac (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    if ((e_PDPD_MOD_DNE != pdpd_mode) && (e_PDPD_MOD_DGNE != pdpd_mode))
    {
        uint8_t const drf_rate = p_quad_params->com_params.drf_rate;
        uint8_t const strm_cfg = p_quad_params->v2d_params.strm_cfg;
        e_proc_blk_sz_t const blk_sz = get_tf (com_v2d_strm_cfg_lut, strm_cfg, blk_sz);
        uint8_t const ptr_sel = get_tf (tx_pdpd_mod_lut, pdpd_mode, v2d_input_ptr_sel);
        RT_ASSERT (ptr_sel == 0 || ptr_sel == 2); // path 'A' or 'C'
        uint8_t const num_strm = get_tf (com_v2d_strm_cfg_lut, strm_cfg, ac);
        // Input path ‘A’ Pointer Locations
        av2d_csr_tx_csr_tx_ptr_bound_reg_t ptr_bound;
        uint8_t const ofs = get_v2d_if_param_ofs (num_strm);
        // Set Stream Count ‘A’ or ‘C’ path
        av2d_csr_tx_csr_tx_strm_cnt_reg_t cnt = {.value = AV2D_CSR_TX_CSR_TX_STRM_CNT_DEFAULT};
        // Stream Count is used to read data flits out of Tx Buffer. It supports up to 1k 512-bit data flits. 0 means 1 flit.
        cnt.STREAM_CNT = get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf (com_drf_rate_conf_lut, drf_rate, sys_rate), strm_cnt); // A/C path
        cnt.STREAM_EN = 1;

        for (uint8_t v = 0; v < num_strm; v++)
        {
            // Input path ‘A’ Pointer Locations
            ptr_bound.value = AV2D_CSR_TX_CSR_TX_PTR_BOUND_DEFAULT;
            ptr_bound.AC_LOWER_BOUND = get_tf2d (tx_v2d_if_params_lut, ptr_sel, v + ofs, lower_bound); // Starting location
            ptr_bound.AC_UPPER_BOUND = get_tf2d (tx_v2d_if_params_lut, ptr_sel, v + ofs, upper_bound); // Ending location
            p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_PTR_BOUND[v] = ptr_bound;
            // Set Stream Count ‘A’ or ‘C’ path
            p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_STRM_CNT[v] = cnt;
        }

        FW_PRINT (FW_DEBUG, "v2d_nsip_malloc_ac is done");
    }
}

// B flow NSIP Memory Allocation
void v2d_nsip_malloc_b (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    if ((e_PDPD_MOD_ND != pdpd_mode) && (e_PDPD_MOD_NDPF != pdpd_mode))
    {
        uint8_t const strm_cfg = p_quad_params->v2d_params.strm_cfg;
        e_pdpd_op_mod_t const pdpd_op_mode = p_quad_params->v2d_params.pdpd_op_mode;
        uint8_t const pdpd_rate = p_quad_params->v2d_params.pdpd_rate;
        e_proc_blk_sz_t const blk_sz = get_tf (com_v2d_strm_cfg_lut, strm_cfg, blk_sz);

        uint8_t const ptr_sel = get_tf (tx_pdpd_mod_lut, pdpd_mode, v2d_input_ptr_sel);
        RT_ASSERT (ptr_sel == 1 || ptr_sel == 2);                            // B path
        uint8_t const num_strm = get_tf (com_v2d_strm_cfg_lut, strm_cfg, b); // B path
        uint8_t const ofs = get_v2d_if_param_ofs (num_strm);
        uint8_t const m = (ptr_sel == 2) ? 1 : 0;

        // Input path ‘B’ I/Q sample Pointer Locations.
        av2d_csr_tx_csr_tx_pd_ptr_bound_reg_t pd_ptr_bound;
        // Set Stream Count ‘B’ I/Q sample path
        av2d_csr_tx_csr_tx_pd_strm_cnt_reg_t pd_strm_cnt = {.value = AV2D_CSR_TX_CSR_TX_PD_STRM_CNT_DEFAULT};
        // Stream Count is used to read data flits out of Tx Buffer. It supports up to 1k 512-bit data flits. 0 means 1 flit
        pd_strm_cnt.STREAM_CNT =
            get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, in_rate), strm_cnt);
        pd_strm_cnt.STREAM_EN = 1; // Stream Enable.

        for (uint8_t v = 0; v < num_strm; v++)
        {
            // Input path ‘B’ I/Q sample Pointer Locations.
            pd_ptr_bound.value = AV2D_CSR_TX_CSR_TX_PD_PTR_BOUND_DEFAULT;
            pd_ptr_bound.B_LOWER_BOUND = get_tf2d (tx_v2d_if_params_lut, ptr_sel + m, v + ofs, lower_bound); // Starting location
            pd_ptr_bound.B_UPPER_BOUND = get_tf2d (tx_v2d_if_params_lut, ptr_sel + m, v + ofs, upper_bound); // Ending location
            p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_PD_PTR_BOUND[v] = pd_ptr_bound;
            // Set Stream Count ‘B’ I/Q sample path
            p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_PD_STRM_CNT[v] = pd_strm_cnt;
        }

        FW_PRINT (FW_DEBUG, "v2d_nsip_malloc_b is done");
    }
}

// D flow NSIP Memory Allocation
void v2d_nsip_malloc_d (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    if (e_PDPD_MOD_DGPP == pdpd_mode || e_PDPD_MOD_DPP == pdpd_mode)
    {
        uint8_t const strm_cfg = p_quad_params->v2d_params.strm_cfg;
        e_pdpd_op_mod_t const pdpd_op_mode = p_quad_params->v2d_params.pdpd_op_mode;
        uint8_t const pdpd_rate = p_quad_params->v2d_params.pdpd_rate;
        e_proc_blk_sz_t const blk_sz = get_tf (com_v2d_strm_cfg_lut, strm_cfg, blk_sz);

        uint8_t const num_strm = get_tf (com_v2d_strm_cfg_lut, strm_cfg, d); // D flow

        com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
        // Packet Size for PDPD Stream, ie, for D flow. Each 2 bits define a packet size for a stream. There are total 4 streams. The packet
        // length equals to 2^pkt_sz[1:0].
        // TODO: check with Arch to see using fixed value or usecase dependent.
        av2d_csr_rx_csr_rx_packet_sz_reg_t sz = p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PACKET_SZ;
        // TODO: those fields should be replaced with 8-bit field vector in register
        sz.PD_PKT_SZ_STREAM_0 = 0; // set to 1 flit for now.
        sz.PD_PKT_SZ_STREAM_1 = 0;
        sz.PD_PKT_SZ_STREAM_2 = 0;
        sz.PD_PKT_SZ_STREAM_3 = 0;
        p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PACKET_SZ = sz;

        av2d_csr_rx_csr_rx_gnrl_csr_reg_t csr = p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_GNRL_CSR;
        // csr.RX_CFG_COMPLETE
        // csr.RX_STARTED
        // csr.RX_PD_CFG_COMPLETE
        // csr.RX_PD_STARTED
        // Ensure RX PDPD egress data is enabled
        csr.RX_PD_EN = 1; // When high, this bit enables Rx logic, to receive PDPD egress traffic.
        p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_GNRL_CSR = csr;
        com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL

        av2d_csr_rx_csr_rx_pd_strm_cnt_reg_t cnt = {.value = AV2D_CSR_RX_CSR_RX_PD_STRM_CNT_DEFAULT};
        // Set Stream Count ‘D’ path for PDPD egress feedback to VEX.
        // Stream Count is in flits and used to assign data from DRF to VEX streams. It supports up to 1k 512-bit data flits. 0 means 1
        // flit. The value should be multiple of packet size, 2^RX(PD)_PKT_SZ_Stream_N.
        cnt.STREAM_CNT =
            get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, out_rate), strm_cnt);
        cnt.STREAM_EN = 1;
        for (uint8_t v = 0; v < num_strm; v++) { p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->RX_CSR_RX_PD_STRM_CNT[v] = cnt; }

        FW_PRINT (FW_DEBUG, "v2d_nsip_malloc_b is done");
    }
}

// per HAS, V2D buf (total 32K 16I,16Q complex samples) is accessed in flit (512-bit), 4 A/C buffers, 4 B buffers, size could be of
// 128 samples (8-flit) to 32K samples (2k flits), these buffers can be different in size
// max mem allocation between A and B flows can be up to a max of 16K samples (1K flits), one cannot split the allocation for eg, 8K for A
// and the rest of 24K for B buffer allocation assumes 2.5 * vex_block_processing_size (0.5us) for B/A&C; for low sample rate (<=2GSPS),
// 3 * vex_block_processing_size
// NOTE: only one VEX can write to G-buf at one time
void v2d_buf_wm (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    uint8_t const fifo_delay = p_quad_params->com_params.fifo_delay;
    if (e_NOT_USED == get_tf (tx_v2d_start_dly_lut, fifo_delay, start_src))
    {
        e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
        uint8_t const drf_rate = p_quad_params->com_params.drf_rate;
        bool const pd_extra_en = get_tf (tx_pdpd_mod_lut, pdpd_mode, pd_extra_en);
        uint8_t const strm_cfg = p_quad_params->v2d_params.strm_cfg;
        e_proc_blk_sz_t const blk_sz = get_tf (com_v2d_strm_cfg_lut, strm_cfg, blk_sz);

        av2d_csr_tx_buf_wm_tx_start_wm_reg_t wm = {.value = AV2D_CSR_TX_BUF_WM_TX_START_WM_DEFAULT};
        if ((e_PDPD_MOD_DNE != pdpd_mode) && (e_PDPD_MOD_DGNE != pdpd_mode))
        {
            // Start Watermark for A/C Path. If enabled by START_AC_WM_EN, this value will be compared with A/C path first enabled Stream's
            // filling watermark in Tx Buffers. If there is a match, Tx A path DigRF or PDPD C path only transmission will start. Maximum
            // value is 0x800 for 2k in flits.
            wm.START_AC_WATERMARK = get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf (com_drf_rate_conf_lut, drf_rate, sys_rate), wm);
            // Start On Watermark Enable for A/C Path. When set, BFN/JESD controlled starts will be ignored and when filling watermark in Tx
            // Buffer for A/C path first enabled Stream matches with START_AC_WATERMARK, Tx A path DigRF or PDPD C path only sampling data
            // transmission will start. After setting this bit to high, software should not clear this bit.
            wm.START_AC_WM_EN = 1;
        }
        if ((e_PDPD_MOD_ND != pdpd_mode) && (e_PDPD_MOD_NDPF != pdpd_mode))
        {
            e_pdpd_op_mod_t const pdpd_op_mode = p_quad_params->v2d_params.pdpd_op_mode;
            uint8_t const pdpd_rate = p_quad_params->v2d_params.pdpd_rate;
            // Start Watermark for B Path. If enabled by START_B_WM_EN, this value will be compared with B path first enabled Stream's
            // filling watermark in Tx Buffers. If there is a match, PDPD B or B+C path transmission will start. Maximum value is 0x800 for
            // 2k in flits.
            wm.START_B_WATERMARK =
                get_tf2d (com_v2d_strm_buf_lut, blk_sz, get_tf2d (tx_pdpd_pc_sel_lut, pdpd_op_mode, pdpd_rate, in_rate), wm);
            // Start On Watermark Enable for B Path. When set, BFN/JESD controlled starts will be ignored and when filling watermark in Tx
            // Buffer for B path first enabled Stream matches with START_B_WATERMARK, PDPD B or B+C path sampling data transmission will
            // start. After setting this bit to high, software should not clear this bit.
            wm.START_B_WM_EN = 1;
        }

        p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_BUF_WM_TX_START_WM = wm;

        FW_PRINT (FW_DEBUG, "v2d_buf_wm is done");
    }
}

// Configure V2D data start for startup timing from JESDRX_START
// see Figure 6-8
void v2d_jesdrx_start_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    uint8_t const fifo_delay = p_quad_params->com_params.fifo_delay;

    // ASSERT(chnl == 0 || chnl == 1);
    // step 1
    com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    bfn_csr_general_csr_reg_t gnrl_csr = p_v2d->p_bfn_csr->GENERAL_CSR;
    gnrl_csr.BFN_START_EN = 0; // ‘0’ (default) Disables BFN operation to use JESDRX_START
    p_v2d->p_bfn_csr->GENERAL_CSR = gnrl_csr;
    com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL

    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    // option 1 = V2D-PDPD Enabled : option 2 = V2D-PDPD not used (bypassed)
    uint8_t const opt = (e_PDPD_MOD_ND != pdpd_mode) ? 2 + chnl : chnl;
    // step 2/3/4/5
    // Enable and set the V2D JESDRX_START delay for PDPD When the VEX array begins outputting data at the end of its chain, it is
    // buffered at the input of the V2D. The latency of the VEX array should be known per the system use case, and the latency is used
    // to set up a timing delay (register START_LM) of the JESDRX_START signal of when to start the V2D after sufficient buffering of
    // the data input.
    bfn_csr_start_lm_reg_t lm = {.value = BFN_CSR_START_LM_DEFAULT};
    // Set/enable latency match value to start PDPD0 in V2D (2 per V2D)
    lm.MATCH_EN = 1; // Enable start match for Channel chnl
    // Set JESD latency count using DigRF clocks (triggered when JESD is started).
    // channel 0, ie, PDPD0 : channel 1, ie, PDPD1
    lm.MATCH_VALUE = chnl ? get_tf (tx_v2d_start_dly_lut, fifo_delay, lm_chnl0) : get_tf (tx_v2d_start_dly_lut, fifo_delay, lm_chnl0);
    p_v2d->p_bfn_csr->START_LM[opt] = lm;
    FW_PRINT (FW_DEBUG, "v2d_jesdrx_start_cfg is done");
}

// Finally, enable the TX configuration for ALL modes (based on use case)
// General Configuration/Control of V2D
void v2d_en (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    bool const gang_mod = get_tf (tx_pdpd_mod_lut, pdpd_mode, gang_mod);
    av2d_csr_tx_csr_tx_gnrl_csr_reg_t csr = {.value = AV2D_CSR_TX_CSR_TX_GNRL_CSR_DEFAULT};
    // here BUFFER_0 and BUFFER_1 are the shared 32K mem on V2D input:
    // when both C & B flow exist, C flow always uses the lower half as buffer_0 and B flow always uses the upper half as buffer_1
    csr.BUFFER_0_POWER_DOWN = 0;
    csr.BUFFER_1_POWER_DOWN = 0;
    // csr.TX_ALARM_ECC_DBE_MASK
    // csr.TX_ALARM_UNDERRUN_MASK
    // csr.TX_ALARM_CM_0_ERR_MASK
    // csr.TX_ALARM_CM_1_ERR_MASK

    csr.PD_EXTRA_EN = get_tf (tx_pdpd_mod_lut, pdpd_mode, pd_extra_en);
    csr.TX_CFG_COMPLETE = 1;   // Configure done
                               // this is used for buffer partitionning
    csr.TX_CAPTURE_IDX_AC = 0; // 0b00 (test only)
    csr.TX_CAPTURE_IDX_B = 0;  // 0b00 (test only)
    // csr.TX_CAPTURE_DONE_AC
    // csr.TX_CAPTURE_DONE_B

    p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_GNRL_CSR = csr;

    // power down buf for PDPD1 in ganging mode
    if (gang_mod)
    {
        csr.BUFFER_0_POWER_DOWN = 1;
        csr.BUFFER_1_POWER_DOWN = 1;
        csr.PD_EXTRA_EN = 0;
        p_v2d->chnl[chnl + 1].av2d_apb.p_av2d_csr->TX_CSR_TX_GNRL_CSR = csr;
    }
    FW_PRINT (FW_DEBUG, "v2d_en is done");
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
void tx_v2d_en_clk (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const ant_mask_in_grp)
{
    e_pdpd_mod_sel_t const pdpd_mode = p_quad_params->v2d_params.pdpd_mode;
    bool const gang_mod = get_tf (tx_pdpd_mod_lut, pdpd_mode, gang_mod);

    com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    bfn_csr_general_csr_reg_t gnrl_csr = p_v2d->p_bfn_csr->GENERAL_CSR;
    gnrl_csr.BFN_START_EN |= 0;
    gnrl_csr.CHANNEL_0_CRUX_CLK_EN |= (ant_mask_in_grp & 1) ? 1 : 0;
    gnrl_csr.CHANNEL_1_CRUX_CLK_EN |= gang_mod ? 0 : (ant_mask_in_grp & 2) ? 1 : 0;
    gnrl_csr.CHANNEL_0_DRF_CLK_EN |= (ant_mask_in_grp & 1) ? 1 : 0;
    gnrl_csr.CHANNEL_1_DRF_CLK_EN |= gang_mod ? 0 : (ant_mask_in_grp & 2) ? 1 : 0;
    // Q: does PDPD clk affecting filter in V2D block?
    // A: per HAS, for NDPF, DPD HW will be disabled/clock gated, only post filter module will be exercised
    gnrl_csr.PDPD_0_CLK_EN = ((e_PDPD_MOD_ND != pdpd_mode) && (e_PDPD_MOD_NDPF != pdpd_mode) && (ant_mask_in_grp & 1)) ? 1 : 0;
    gnrl_csr.PDPD_1_CLK_EN = ((e_PDPD_MOD_ND != pdpd_mode) && (e_PDPD_MOD_NDPF != pdpd_mode) && (ant_mask_in_grp & 2)) ? 1 : 0;
    gnrl_csr.CHANNEL_0_HALT |= 0;
    gnrl_csr.CHANNEL_1_HALT |= 0;
    gnrl_csr.CHANNEL_0_DP_INIT_DONE |= 0;
    gnrl_csr.CHANNEL_1_DP_INIT_DONE |= 0;
    p_v2d->p_bfn_csr->GENERAL_CSR = gnrl_csr;
    com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL

    FW_PRINT (FW_DEBUG, "tx_v2d_en_clk is done");
}

// when to release data from V2D buffer (A/C, B)
// per HAS, the data is released from V2D buffer to dig RF using two schemes: Using a BFN timed event or Using a relative trigger - based
// event based on JESD startRx signal (v2DStartQuadn from MEM CAP)
void tx_v2d_data_start_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    uint8_t const fifo_delay = p_quad_params->com_params.fifo_delay;
    e_v2d_tx_fifo_start_src_t const fifo_start_src = get_tf (tx_v2d_start_dly_lut, fifo_delay, start_src);
    if (e_JESD_RX_START_QN == fifo_start_src)
    {
        v2d_jesdrx_start_cfg (p_quad_params, p_v2d, chnl);
    }
    else if (e_NOT_USED == fifo_start_src) // typically test only
    {
        v2d_buf_wm (p_quad_params, p_v2d, chnl);
    }
    FW_PRINT (FW_DEBUG, "tx_v2d_data_start_cfg is done");
}

// V2D cfg toplevel routine:
void tx_v2d_cfg_seq (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    v2d_load_coef_lut (p_quad_params, p_v2d, chnl); // FIXME
    v2d_cfg_extra_term (p_quad_params, p_v2d, chnl);
    v2d_pdpd_lut_cfg (p_quad_params, p_v2d, chnl);

    v2d_sif_ctrl (p_quad_params, p_v2d, chnl);
    v2d_pif_ctrl (p_quad_params, p_v2d, chnl);

    v2d_nsip_malloc_ac (p_quad_params, p_v2d, chnl);
    v2d_nsip_malloc_b (p_quad_params, p_v2d, chnl);
    v2d_nsip_malloc_d (p_quad_params, p_v2d, chnl);

    // assume B2H/H2B configured properly by RTE/SDF

    tx_v2d_data_start_cfg (p_quad_params, p_v2d, chnl);
    FW_PRINT (FW_DEBUG, "tx_v2d_cfg_seq is done");
}

// called in warmup sequence to make sure all V2D configuration is done before enabling the V2D
void tx_v2d_en (uint8_t const quad_idx, uint8_t ant_mask_in_quad)
{
    const quad_params_t *const p_quad_params = &tx_daco.quad_params[quad_idx];
    uint8_t g_idx = quad_idx * NUM_GRP_PER_QUAD;

    while (ant_mask_in_quad)
    {
        volatile v2d_t *const p_v2d = &tx_daco.hw.v2d[g_idx];
        uint8_t ant_mask_in_grp = ant_mask_in_quad & 0x3;
        uint8_t chnl = 0;
        while (ant_mask_in_grp)
        {
            if (ant_mask_in_grp & 1)
            {
                v2d_en (p_quad_params, p_v2d, chnl);
            }
            ant_mask_in_grp >>= 1;
            chnl++;
        }

        ant_mask_in_quad >>= NUM_GRP_PER_QUAD;
        g_idx++;
    }
}

// V2D dynamic routines:
// step 15-22
// Optional: When using Sample Count to trigger updates (see pdpd_cfg_reg_t and EXT_CTRL_* bitfields), the following registers
// specify the count in which the update will occur when controlled by RCS. These registers are typically used dynamically and may not be
// necessary during configuration.

uint32_t tx_v2d_smpl_cnt (volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    return p_v2d->chnl[chnl].p_pdpd->SAMPLE_CNT.COUNT; // Optional: Read the current Sample Count
}

// During periods such as antenna calibration and the TX is enabled, the PDPD must be bypassed enable PDPD bypass when entering antenna
// calibration mode
void tx_v2d_bypass_en_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_BYP_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_BYP_ENA.COUNT = p_quad_params->v2d_params.tcnt_byp_en;
    }
    else
    {
        FW_PRINT (FW_WARN, "v2d_bypass_en_trigger_smpl_cnt is called while BYPASS is ctrl reg triggered");
    }
}
// disable PDPD bypass when exiting antenna calibration mode
void tx_v2d_bypass_dis_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_BYP_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_BYP_DIS.COUNT = p_quad_params->v2d_params.tcnt_byp_dis;
    }
    else
    {
        FW_PRINT (FW_WARN, "v2d_bypass_dis_trigger_smpl_cnt is called while BYPASS is ctrl reg triggered");
    }
}

// During periods such as when TX is disabled, zero stuffing of input data will reduce power consumption.
// DL Burst OFF
void tx_v2d_zerostuff_en_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_ZERO_STUFF_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_ZERO_STUFF_ENA.COUNT = p_quad_params->v2d_params.tcnt_zero_en;
    }
    else
    {
        FW_PRINT (FW_WARN, "v2d_zerostuff_en_trigger_smpl_cnt is called while ZEROSTUFF is ctrl reg triggered");
    }
}
// DL Burst ON
void tx_v2d_zerostuff_dis_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_ZERO_STUFF_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_ZERO_STUFF_DIS.COUNT = p_quad_params->v2d_params.tcnt_zero_dis;
    }
    else
    {
        FW_PRINT (FW_WARN, "tx_v2d_zerostuff_dis_trigger_smpl_cnt is called while ZEROSTUFF is ctrl reg triggered");
    }
}

// TODO: check those 'tcn' used in updt funcs can fit into table or not
//       or they can be the same value so combine into one func?
// use RCS to optionally control the coefficient update times
// in normal operation, VEX is response to do it: Once approximately every 30-100 usecs
void tx_v2d_c_lut_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_UPDATE_C_LUT_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_UPDATE_C_LUT.COUNT = p_quad_params->v2d_params.tcnt_updt_c_lut;
    }
    else
    {
        FW_PRINT (FW_WARN, "tx_v2d_c_lut_updt_trigger_smpl_cnt is called while C_LUT is ctrl reg triggered");
    }
}
// To modify the compression LUT
void tx_v2d_nl_lut_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_UPDATE_NL_LUT_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_UPDATE_NL_LUT.COUNT = p_quad_params->v2d_params.tcnt_updt_nl_lut;
    }
    else
    {
        FW_PRINT (FW_WARN, "tx_v2d_nl_lut_updt_trigger_smpl_cnt is called while NL_LUT is ctrl reg triggered");
    }
}
// step 22
void tx_v2d_pt_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl)
{
    if (get_tf (tx_pdpd_cfg_lut, 0, ext_cfg) & PDPD_CFG_EXT_CTRL_UPDATE_PASSTHRU_BF_MSK)
    {
        p_v2d->chnl[chnl].p_pdpd->TCNT_UPDATE_PASSTHRU.COUNT = p_quad_params->v2d_params.tcnt_updt_pt;
    }
    else
    {
        FW_PRINT (FW_WARN, "tx_v2d_pt_updt_trigger_smpl_cnt is called while PASSTHRU is ctrl reg triggered");
    }
}

// com_msgs_enum.h
void tx_v2d_lpbk_cfg (uint8_t const quad_idx, uint8_t ant_mask_in_quad)
{
    const quad_params_t *const p_quad_params = &tx_daco.quad_params[quad_idx];
    uint8_t g_idx = quad_idx * NUM_GRP_PER_QUAD;

    while (ant_mask_in_quad)
    {
        volatile v2d_t *const p_v2d = &tx_daco.hw.v2d[g_idx];
        uint8_t ant_mask_in_grp = ant_mask_in_quad & 0x3;
        uint8_t chnl = 0;
        while (ant_mask_in_grp)
        {
            if (ant_mask_in_grp & 1)
            {
                p_v2d->chnl[chnl].regs.sif.TX_RX_LPBK = (e_V2D_LOOPBACK == p_quad_params->com_params.lpbk_mode) ? 1 : 0;
                p_v2d->chnl[chnl].av2d_apb.p_av2d_csr->TX_CSR_TX_SIF_CTRL = p_v2d->chnl[chnl].regs.sif;
            }
            ant_mask_in_grp >>= 1;
            chnl++;
        }

        ant_mask_in_quad >>= NUM_GRP_PER_QUAD;
        g_idx++;
    }
}

// V2D TX reset Sequence
// call in group level
// TODO: consider moving this to ax core to be used for both UL & DL
void tx_v2d_reset_seq (volatile v2d_t *const p_v2d)
{
    // put in HALT:
    com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    bfn_csr_general_csr_reg_t gnrl_csr = p_v2d->p_bfn_csr->GENERAL_CSR;
    gnrl_csr.CHANNEL_0_HALT = 1; // halt chanle0
    gnrl_csr.CHANNEL_1_HALT = 1; // halt chanle1
    p_v2d->p_bfn_csr->GENERAL_CSR = gnrl_csr;

    // read and wait halt is done:
    while (!(p_v2d->p_bfn_csr->GENERAL_CSR.CHANNEL_0_HALT_DONE && p_v2d->p_bfn_csr->GENERAL_CSR.CHANNEL_1_HALT_DONE)) { ; }

    // remove HALT and reset:
    gnrl_csr.CHANNEL_0_HALT = 0;    // unhalt chanle0
    gnrl_csr.CHANNEL_1_HALT = 0;    // unhalt chanle1
    gnrl_csr.CHANNEL_0_DP_INIT = 1; // reset
    gnrl_csr.CHANNEL_1_DP_INIT = 1; // reset
    p_v2d->p_bfn_csr->GENERAL_CSR = gnrl_csr;
    // read and wait until reset is done:
    while (!(p_v2d->p_bfn_csr->GENERAL_CSR.CHANNEL_0_DP_INIT_DONE && p_v2d->p_bfn_csr->GENERAL_CSR.CHANNEL_1_DP_INIT_DONE)) { ; }
    com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL

    FW_PRINT (FW_DEBUG, "V2D reset is done");
}
