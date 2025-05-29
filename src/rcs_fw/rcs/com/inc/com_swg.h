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
#ifndef __COM_SWG_H__
#define __COM_SWG_H__

#if (CPU_TX) || (CPU_RX) || ((UNIT) && (CPU_AX))
#include "com_assert.h"
#include <stdint.h>
/**
 * @brief           get angle incremental for each cordic in the SWG
 * @param [in]      freq_shift_khz: frequency shift (in KHz) to apply
 * @param [in]      sys_clk_khz: e_CLK_983040_KHZ or e_CLK_1474560_KHZ
 * @param [in]      num_pp: num of poly-phase, same as smpl_per_clk
 * @return          64-bit value with lower 38 bits representive of angle incremental for each cordic in the SWG
 */
INTRINSIC_ALWAYS_INLINE static uint64_t cordic_incr_calc (uint32_t const freq_shift_khz, uint32_t const sys_clk_khz, uint8_t const num_pp)
{
    RT_ASSERT ((sys_clk_khz != 0) && (num_pp != 0));
    double incr = (double)freq_shift_khz / (double)sys_clk_khz / (double)num_pp;
    return incr * 0x4000000000ULL; // incr * (1 << 38)
}
#endif /* (CPU_TX) || (CPU_RX)  || ((UNIT) && (CPU_AX))*/

#if (CPU_TX) || (CPU_RX)
#include "com_daco.h"

#if (CPU_RX)
#include "rx_daco.h"
#endif
#if (CPU_TX)
#include "tx_daco.h"
#endif

/**
 * @brief           config VHA NCOs, also update vha_mix_mask to be used for VHA mod/dmod setting
 *                  ssumption:
 *                  a. if band0_freq == band0_freq == 0: e_VHA_MIX_BYPASS case, no NCO is used
 *                  b. if band0_freq * band1_freq != 0: dual band, band1_freq >= band0_freq
 *                          if band0_freq == band1_freq: e_VHA_MIX_DUAL_BAND_SHARED case: only NCO0 is used for both bands
 *                          else: e_VHA_MIX_DUAL_BAND case: NCO0 for band0 and NCO1 for band1
 *                  c. if band0_freq !=0 and band1_freq ==0: e_VHA_MIX_SINGLE_BAND case: use NCO0
 *                  d. no support for case like band1_freq !=0 and band0_freq ==0
 * @param [in]      p_quad_params: quad wise parameters
 * @param [in]      p_vha: pointer to specific VHA HW block
 * @return          none
 */
void com_vha_nco_cfg (quad_params_t *const p_quad_params, volatile vha_hw_t *const p_vha);

/**
 * @brief           config VHA mixer. to be called from *_vha_cfg_seq
 * @param [in]      p_quad_params: quad wise parameters
 * @param [in]      p_vha: pointer to specific VHA HW block
 * @return          none
 */
void com_vha_mix_cfg (const quad_params_t *const p_quad_params, volatile vha_hw_t *const p_vha, uint8_t const chnl_idx);

/**
 * @brief           seq to config FB_SYS NCOs
 * @param [in]      drf_idx: DRF index, range: 0..1
 * @param [in]      ant_mask_in_drf: DRF wise ANT mask
 * @return          none
 */
void com_sys_swg_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf);

/**
 * @brief           seq to config FB_ANT NCOs
 * @param [in]      drf_idx: DRF index, range: 0..1
 * @param [in]      ant_mask_in_drf: DRF wise ANT mask
 * @return          none
 */
void fb_ant_swg_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf);

#endif /* (CPU_TX) || (CPU_RX) */

#endif /* __COM_SWG_H__ */

