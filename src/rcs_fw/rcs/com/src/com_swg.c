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
/**
 * @file    com_swg.c
 * @brief   SWG configuration routines
 * @details
 */

/**
 * FB_SYS[0..1]: 6 NCO(0=rxfb0, 1=rxfb1, 2=tx_mod_q0/1, 3=rx_dmod_q0/1, 4=tx_mod_q1, 5=rx_dmod_q1), max_num_pp: 16
 * VHA[0..7][DL/UL]: NCO_0 = band0, NCO_1=band1, max_num_pp: 4
 * FB_ANT[0..1][EVEN/ODD]: 2 NCO, max_num_pp: 16
 *
 *
 * SWG Algorithm:
 * To calculate the initial values of the N Cordics, the user must first calculate Angle_between_cordics.
 *
 * Angle_between_cordics (in degrees) = 360 * (f_out in GHz)/(f_effective_sysclk in GHz)
 *
 * where:
 * f_out is the desired output frequency of sine wave generator, ie, desired freq shift
 * f_effective_sysclk is the effective sysclk after multiplying sysclk by N = number of active cordics (typically 8 or 16)
 *
 * note: theta == angle_between_cordics
 *
 * init_angle[Cordic_Number] (in degrees) = angle_between_cordics * [N - Cordic_Number -1]
 * where: cordic_number = 0, 1, 2,...N-1, where N = number of active cordics.
 *
 * The full range of the 38-bit register represents one revolution of a circle, i.e. 360 deg or 2 PI radians. Hence, a value of
 * 38’h10_0000_0000 represents 90 deg, 38’h20_0000_0000 represents 180 deg, and 38’h30_0000_0000 represents 270 deg.
 *
 * To convert degrees to an internal 38-bit value, use the following formula:
 *
 * converted_angle[37:0] = (angle_in_degrees/360) * 2^38.
 *
 * Although the N Cordics generate their N outputs in parallel, they are effectively used serially as though there was
 * a clock operating at a frequency = N * freq_sys_clk. As such, phase order of the outputs of N-phase Cordic sine wave
 * generator does matter. We want the earliest output of the N-Phase Cordic generator to line up with the earliest
 * sample in the data stream.
 * The earliest output of the N-Phase Cordic generator should be from Cordic[N-1].
 * The last output of the N-Phase Cordic generator should be from Cordic[0].
 * For example, if the DUC is supplying 16 samples to the Modulator and the NCO comprises a 16-Phase Cordic Sine Wave
 * Generator, then if we want the sine wave generator's first output to be equal to 0, we would set cordic_init[15] to
 * Zero degrees and this value would be multiplied by the value of input_sample[15].
 * The antenna modulator's Sine Wave Generator generates a single sinewave with N samples per clock cycle when operating
 * in NGSPS mode.
 *
 * theta = 360 * f_out / (f_sys * pp);
 * theta: angle between cordics
 * f_out: SWG output freq
 * f_sys: SWG operation freq
 * pp: num of polyphase
 *
 * init_theta_n = theta * (pp - n -1) = 360 * f_out / f_sys / pp * (pp - n -1);
 * init_theta_n: initial theta value used in nth cordic
 *
 * incr = theta * pp = 360* f_out / f_sys / pp * pp = 360 * f_out / f_sys;
 * incr: angle incremental for each cordic
 *
 * incr_conv = incr / 360 * (1 << 38) = f_out / f_sys * (1 << 38);
 * incr_conv: 38-bit reprentation of angle incremental for each cordic
 *
 * init_theta_conv_n = init_theta_n / 360 * (1 << 38) = incr_conv / pp * (pp - n -1);
 * init_theta_conv_n: 38-bit reprentation of initial theta value used in nth cordic
 *
 * VHA NCO: using filling event instead of BFNE to enable; clocked gated if not used; support 15KHz and 100KHz freq raster
 * band0_freq should always < band1_freq
 */

#if (CPU_TX) || (CPU_RX)

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <stddef.h>
#include "com_swg.h"
#include "com_assert.h"
#include "com_static_data_table.h"
#include "com_lock.h"
#if (CPU_TX)
#include "tx_static_data_table.h"
#endif
#if (CPU_RX)
#include "rx_static_data_table.h"
#endif
#include <stdlib.h>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
enum e_sys_clk_khz_t
{
    e_CLK_983040_KHZ = 983040,
    e_CLK_1474560_KHZ = 1474560
};

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
 * @brief           get SYS clock in KHz
 * @param [in]      p_quad_params: quad wise parameters
 * @return          SYS clock in KHz;
 */
enum e_sys_clk_khz_t sys_clk_khz_get (const volatile quad_params_t *const p_quad_params);

/**
 * @brief           helper function to get start address of INIT_UPPER register array
 * @param [in]      p_swg: pointer to SWG HW register block, including FB_SYS, FB_ANT and VHA
 * @param [in]      nco_id: NCO id, value assignment as below:
 *                      FB_SYS[0..1]: 0: RXFB0, 1: RXFB1, 2: TX_MOD Q0 or Q0&1, 3: RX_DMOD Q0 or Q0&1, 4: TX_MOD Q1, 5: RX_DMOD Q1
 *                      VHA[0..7]:    0: BAND0 ANT0 & 1, 1: BAND1 Ant0 & 1; same for both UL/DL
 *                      FB_ANT[0..1]: 0 & 1 mixed together for dual-tone; same for EVEN/ODD
 *
 * @return          address of swg_init_upper_2d_reg_t
 */
volatile static swg_init_upper_2d_reg_t *get_init_upper (volatile swg_t *const p_swg, uint8_t const nco_id);

/**
 * @brief           helper function to get start address of INIT_LOWER register array
 * @param [in]      p_swg: pointer to SWG HW register block, including FB_SYS, FB_ANT and VHA
 * @param [in]      nco_id: NCO id, value assignment as below:
 *                      FB_SYS[0..1]: 0: RXFB0, 1: RXFB1, 2: TX_MOD Q0 or Q0&1, 3: RX_DMOD Q0 or Q0&1, 4: TX_MOD Q1, 5: RX_DMOD Q1
 *                      VHA[0..7]:    0: BAND0 ANT0 & 1, 1: BAND1 Ant0 & 1; same for both UL/DL
 *                      FB_ANT[0..1]: 0 & 1 mixed together for dual-tone; same for EVEN/ODD
 * @return          address of swg_init_lower_2d_reg_t
 */
volatile static swg_init_lower_2d_reg_t *get_init_lower (volatile swg_t *const p_swg, uint8_t const nco_id);

/**
 * @brief           To independently enable or disable each individual sine wave generator by setting the appropriate bit in bit position
 *                  (N_SWG-1):0.
 *                  When SWG is instantiated in FB_SYS, N_SWG=6;
 *                  When SWG is instantiated in VHA, N_SWG=2 for UL/DL respectively;
 *                  When SWG is instantiated in the CALDAC (FB_ANT), N_SWG = 2
 * @param [in]      p_swg: pointer to SWG HW register block, including FB_SYS, FB_ANT EVEN/ODD and VHA UL/DL
 * @param [in]      nco_en_mask: bit mask to enable SWG (2 or 6 LSBs): bit n for NCO id n
 *                  bit with value 1: enables the corresponding sinewave generator.
 *                  bit with value 0: disables the corresponding sine wave generator.
 * @return          none
 */
INTRINSIC_ALWAYS_INLINE static void nco_enable (volatile swg_t *const p_swg, uint8_t const nco_en_mask);

/**
 * @brief           config SWG
 * @param [in]      p_swg: pointer to SWG HW register block, including FB_SYS, FB_ANT and VHA
 * @param [in]      nco_id: NCO id, value assignment as below:
 *                      FB_SYS[0..1]: 0: RXFB0, 1: RXFB1, 2: TX_MOD Q0 or Q0&1, 3: RX_DMOD Q0 or Q0&1, 4: TX_MOD Q1, 5: RX_DMOD Q1
 *                      VHA[0..7]:    0: BAND0 ANT0 & 1, 1: BAND1 Ant0 & 1; same for both UL/DL
 *                      FB_ANT[0..1]: 0 & 1 mixed together for dual-tone; same for EVEN/ODD
 * @param [in]      num_pp: num of polyphases to use for corresponding SWG; max 4 for VHA, 16 for others
 * @param [in]      incr: 38-bit representive of angle incremental for each cordic in the SWG
 * @return          none
 */
static void nco_conf (volatile swg_t *const p_swg, uint8_t const nco_id, uint8_t const num_pp, uint64_t const incr);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
void nco_enable (volatile swg_t *const p_swg, uint8_t const nco_en_mask)
{
    // ENABLE_PER_SWG: Bit-wise enable for enabling each individual NCO (#) supported within the SWG block.
    p_swg->EN_PER_SWG.ENABLE_PER_SWG = nco_en_mask; // 6-bit (up to 2 or 6 NCOs)
}

volatile swg_init_upper_2d_reg_t *get_init_upper (volatile swg_t *const p_swg, uint8_t const nco_id)
{
    volatile swg_init_upper_2d_reg_t *init_upper = NULL;
    if (0 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D0_INIT_UPPER[0];
    else if (1 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D1_INIT_UPPER[0];
    else if (2 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D2_INIT_UPPER[0];
    else if (3 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D3_INIT_UPPER[0];
    else if (4 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D4_INIT_UPPER[0];
    else if (5 == nco_id)
        init_upper = &p_swg->INIT_UPPER_2D5_INIT_UPPER[0];
    else
        FW_PRINT (FW_ERR, "get_init_upper: Wrong nco_id %u", nco_id);
    return init_upper;
}

volatile swg_init_lower_2d_reg_t *get_init_lower (volatile swg_t *const p_swg, uint8_t const nco_id)
{
    volatile swg_init_lower_2d_reg_t *init_lower = NULL;
    if (0 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D0_INIT_LOWER[0];
    else if (1 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D1_INIT_LOWER[0];
    else if (2 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D2_INIT_LOWER[0];
    else if (3 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D3_INIT_LOWER[0];
    else if (4 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D4_INIT_LOWER[0];
    else if (5 == nco_id)
        init_lower = &p_swg->INIT_LOWER_2D5_INIT_LOWER[0];
    else
        FW_PRINT (FW_ERR, "get_init_lower: Wrong nco_id %u", nco_id);
    return init_lower;
}

void nco_conf (volatile swg_t *const p_swg, uint8_t const nco_id, uint8_t const num_pp, uint64_t const incr)
{
    RT_ASSERT (num_pp <= 16);
    volatile swg_init_upper_2d_reg_t *const p_init_upper = get_init_upper (p_swg, nco_id);
    volatile swg_init_lower_2d_reg_t *const p_init_lower = get_init_lower (p_swg, nco_id);
    RT_ASSERT ((p_init_upper != NULL) && (p_init_lower != NULL));

    for (uint8_t pp = 0; pp < num_pp; pp++)
    {
        uint64_t const init = incr / num_pp * (num_pp - pp - 1);
        // This register contains the 6 MSbits of the 38-bit initial theta value for the given Cordic.
        // p_swg->INIT_UPPER[nco_id][pp].INIT_UPPER = init >> 32; // 6-bit
        p_init_upper[pp].INIT_UPPER = (init >> 32) & 0x3F; // 6-bit

        // This register contains the 32 LSbits of the 38-bit initial theta value for the given Cordic.
        // p_swg->INIT_LOWER[nco_id][pp].INIT_LOWER = init & 0xFFFFFFFF; // 32-bit
        p_init_lower[pp].INIT_LOWER = init & 0xFFFFFFFF; // 32-bit
    }
    /**
     * This register contains the 6 MSbits of the 38-bit theta incr value for all the Cordics of this SWG
     * The angle increment for each of the N Cordics, each with a unique initial angle is given by
     * increment (in degrees) = angle_between_cordics (in degrees) * N
     * where N = number of active cordics.
     */
    p_swg->INCR_UPPER[nco_id].INCR_UPPER = incr >> 32;
    // This register contains the 32 LSbits of the 38-bit theta incr value for all the Cordics of this SWG.
    p_swg->INCR_LOWER[nco_id].INCR_LOWER = incr & 0xFFFFFFFF;

    // TODO: Per Bruce, this might be used for Cal (to be update in the future)
    // if (in_cal_mod):
    // Upper portion (bits 37:32) of the SWG's incr value(up to 2 or 6 NCOs).
    // p_swg->INCR1_UPPER[nco_id].INCR_UPPER = COM_SWG_FIXME; // FIXME: 6-bit
    // Lower portion (bits 31:0) of the SWG's incr value(up to 2 or 6 NCOs)
    // p_swg->INCR1_LOWER[nco_id].INCR_LOWER = COM_SWG_FIXME; // FIXME: 32-bit

    /**
     * The user must program which of the CORDICs are enabled in a single SWG.
     * When operating the SWG at a rate of NGSPS, then bits N-1:0 must be set to 1. All other bits should be programmed to 0
     */
    p_swg->EN[nco_id].ENABLE = (1 << num_pp) - 1; // 16-bit
}

enum e_sys_clk_khz_t sys_clk_khz_get (const volatile quad_params_t *const p_quad_params)
{
    enum e_sys_clk_khz_t f_sys = e_CLK_983040_KHZ;
    if (get_tf (com_drf_rate_conf_lut, p_quad_params->com_params.drf_rate, f_clk))
    {
        f_sys = e_CLK_1474560_KHZ;
    }
    return f_sys;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
void com_vha_nco_cfg (quad_params_t *const p_quad_params, volatile vha_hw_t *const p_vha)
{
    // mix_cfg: mixer config info:
    // bit[1:0]: active bands, bit at position n with value 1 indicating band n is active
    // bit[2]: band0 conj, offset: 2 = VHA_MOD_CFG_CONJ_0_BF_OFF = VHA_DMOD_CFG_CONJ_0_BF_OFF
    // bit[3]: band1 conj, offset: 3 = VHA_MOD_CFG_CONJ_1_BF_OFF = VHA_DMOD_CFG_CONJ_1_BF_OFF
    // bit[4]: use same swg, offset: 4 = VHA_MOD_CFG_USE_SAME_SWG_BF_OFF = VHA_DMOD_CFG_USE_SAME_SWG_BF_OFF
    uint8_t mix_cfg = 0;

    bool has_vha = false;
#if (CPU_TX)
    has_vha = get_tf (tx_topology_lut, p_quad_params->com_params.topology, vha);
#endif
#if (CPU_RX)
    has_vha = get_tf (rx_topology_lut, p_quad_params->com_params.topology, vha);
#endif
    if (has_vha)
    {
        uint8_t const smpl_per_clk = get_tf (com_vha_rate_conf_lut, p_quad_params->vha_params.vha_rate, smpl_per_clk);
        enum e_sys_clk_khz_t const f_sys = sys_clk_khz_get (p_quad_params);
        uint8_t nco_en_mask = 0;
        int32_t nco0_freq = 0, nco1_freq = 0;
        if (p_quad_params->vha_params.band0_freq)
        {
            mix_cfg = 1; // mark band0
            nco0_freq = p_quad_params->com_params.drf_mixer_freq - p_quad_params->vha_params.band0_freq;
            if (nco0_freq < 0)
            {
                // always set down shift using conjugate
                mix_cfg |= 1 << 2; // band 0 swg conjugate
            }
            nco_conf (p_vha->p_swg, 0, smpl_per_clk, cordic_incr_calc (abs (nco0_freq), f_sys, smpl_per_clk));

            nco_en_mask = 1;
        }
        if (p_quad_params->vha_params.band1_freq)
        {
            mix_cfg |= 1 << 1; // mark band1
            nco1_freq = p_quad_params->com_params.drf_mixer_freq - p_quad_params->vha_params.band1_freq;
            if (nco1_freq < 0)
            {
                // always set down shift using conjugate
                mix_cfg |= 1 << 3; // band 1 swg conjugate
            }

            if (mix_cfg & 1)
            {
                if (abs (nco1_freq) != abs (nco0_freq)) // in e_VHA_MIX_DUAL_BAND case
                {
                    nco_en_mask |= 1 << 1;
                    nco_conf (p_vha->p_swg, 1, smpl_per_clk, cordic_incr_calc (abs (nco1_freq), f_sys, smpl_per_clk));
                }
                else // in e_VHA_MIX_DUAL_BAND_SHARED case
                {
                    mix_cfg |= 1 << 4; // use same SWG

                    if ((mix_cfg & (1 << 2)) == 0)
                    {
                        mix_cfg |= 1 << 3;
                    }
                    RT_ASSERT ((mix_cfg & (1 << 3)) && (mix_cfg & (1 << 2))); // to make sure CONJ_0 == !CONJ_1
                }
            }
        }
        nco_enable (p_vha->p_swg, nco_en_mask);
        p_quad_params->vha_params.vha_mix_mask = mix_cfg;
    }
}

// called from r/tx_vha_cfg_seq
void com_vha_mix_cfg (const quad_params_t *const p_quad_params, volatile vha_hw_t *const p_vha, uint8_t const chnl_idx)
{
#if (CPU_TX)
    volatile vha_mod_t *p_mix = p_vha->chnl[chnl_idx].p_mod;
#endif
#if (CPU_RX)
    volatile vha_dmod_t *p_mix = p_vha->chnl[chnl_idx].p_dmod;
#endif
    p_mix->CFG.value = p_quad_params->vha_params.vha_mix_mask;
    // p_mix->EN.value = ??;// FIXME
}

void com_sys_swg_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf)
{
#if (CPU_RX)
    volatile daco_t *const p_daco = &rx_daco;
    uint8_t quad_nco_id = 2; // FIXME: recheck
    uint8_t fbr_nco_id = 0;
#endif
#if (CPU_TX)
    volatile daco_t *const p_daco = &tx_daco;
    uint8_t quad_nco_id = 3; // FIXME: recheck
#endif
    uint8_t nco_en_mask = 0;

    volatile swg_t *const p_swg = p_daco->hw.fb_sys[drf_idx].p_swg0;
    uint8_t quad_idx = drf_idx * NUM_QUAD_PER_DRF;

    while (ant_mask_in_drf)
    {
        if (ant_mask_in_drf & ((1 << NUM_STRM_PER_QUAD) - 1))
        {
            const volatile quad_params_t *p_quad_params = &p_daco->quad_params[quad_idx];
            if (p_quad_params->com_params.drf_mixer_freq) // drf_mixer_freq == 0: bypass
            {
                uint8_t const smpl_per_clk = get_tf (com_drf_rate_conf_lut, p_quad_params->com_params.drf_rate, smpl_per_clk);
                enum e_sys_clk_khz_t const f_sys = sys_clk_khz_get (p_quad_params);
                uint64_t incr = cordic_incr_calc (p_quad_params->com_params.drf_mixer_freq, f_sys, smpl_per_clk);
#if (CPU_RX)
                nco_en_mask |= 1 << fbr_nco_id;
                nco_conf (p_swg, fbr_nco_id, smpl_per_clk, incr);
#endif
                nco_en_mask |= 1 << quad_nco_id;
                nco_conf (p_swg, quad_nco_id, smpl_per_clk, incr);
            }
        }
        ant_mask_in_drf >>= NUM_STRM_PER_QUAD; // next quad in one DRF
        quad_idx++;
        quad_nco_id += 2;
#if (CPU_RX)
        fbr_nco_id++;
#endif
    }
    if (nco_en_mask)
    {
        com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
        nco_en_mask |= p_swg->EN_PER_SWG.ENABLE_PER_SWG;
        nco_enable (p_swg, nco_en_mask);
        com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    }
}

void fb_ant_swg_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf)
{
    //  TODO: to be implemented
    // com_lock_acquire (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    // nco_enable (p_swg, nco_en_mask);
    // com_lock_release (e_LOCK_TRX_SHARED_REG); // e_LOCK_REG_V2D_CSR_RX_GNRL
    //  volatile swg_t *const p_swg_e = tx_daco.hw.fb_ant[drf_idx].p_swg_even;
    //  volatile swg_t *const p_swg_o = tx_daco.hw.fb_ant[drf_idx].p_swg_odd;
    //  p_swg_even, p_swg_odd
    //   caldac_even
    //   caldac_odd
}

#endif /* (CPU_TX) || (CPU_RX) */
