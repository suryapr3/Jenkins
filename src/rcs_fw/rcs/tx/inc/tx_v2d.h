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
#ifndef __TX_V2D_H__
#define __TX_V2D_H__

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

#include "tx_daco.h"

/**
 * @brief           Enable clocks for V2D sub-blocks based on the use case
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      ant_mask_in_grp: 2-bit (LSB) mask specifying whcih ANTs (local) to use in one GROUP
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_en_clk (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                            uint8_t const ant_mask_in_grp);

/**
 * @brief           set V2D data FIFO based on fifo_start_src setting
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_data_start_cfg (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                    uint8_t const chnl);

/**
 * @brief           V2D toplevel config sequence
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT index local to this V2D group
 * @return          none
 */
void tx_v2d_cfg_seq (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl);

/**
 * @brief           enable V2D on TX, used in warmup seq
 * @param [in]      quad_idx: quad index (0 to 3)
 * @param [in]      ant_mask_in_quad: antenna mask in quad
 * @return          none
 */
void tx_v2d_en (uint8_t const quad_idx, uint8_t ant_mask_in_quad);

/**
 * @brief           read the current PDPD sample count
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          the current PDPD sample count value
 */
uint32_t INTRINSIC_ALWAYS_INLINE tx_v2d_smpl_cnt (volatile v2d_t *const p_v2d, uint8_t const chnl);

/**
 * @brief           set Bypass PDPD Enable sample count trigger when entering antenna calibration mode
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_bypass_en_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                uint8_t const chnl);

/**
 * @brief           set Bypass PDPD Disable sample count trigger when exiting antenna calibration mode
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_bypass_dis_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                 uint8_t const chnl);

/**
 * @brief           set Zero Stuff PDPD Enable sample count trigger (eg, when TX is disabled)
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_zerostuff_en_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                   uint8_t const chnl);

/**
 * @brief           set Zero Stuff PDPD Disable sample count trigger (eg, when TX is enabled)
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_zerostuff_dis_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                    uint8_t const chnl);

/**
 * @brief           set GMP/DDR Coef. Update sample count trigger
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_c_lut_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                 uint8_t const chnl);

/**
 * @brief           set Non-Linear Coef. Update sample count trigger
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_nl_lut_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                                  uint8_t const chnl);

/**
 * @brief           set Passthru Coef. Update sample count trigger
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT to use
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_pt_updt_trigger_smpl_cnt (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d,
                                                              uint8_t const chnl);

/**
 * @brief           configure V2D TX to RX loopback, used in warmup seq
 * @param [in]      quad_idx: quad index (0 to 3)
 * @param [in]      ant_mask_in_quad: antenna mask in quad
 * @return          none
 */
void INTRINSIC_ALWAYS_INLINE tx_v2d_lpbk_cfg (uint8_t const quad_idx, uint8_t ant_mask_in_quad);

/**
 * @brief           Seq to reset TX RF V2D path
 * @param [in]      p_v2d: pointer to V2D module
 * @return          none
 */
void tx_v2d_reset_seq (volatile v2d_t *const p_v2d);

#endif // __TX_V2D_H__

