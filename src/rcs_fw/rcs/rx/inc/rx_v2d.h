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
#ifndef __RX_V2D_H__
#define __RX_V2D_H__

#if (CPU_RX)
#else
#error "Not RX CPU"
#endif

#include "rx_daco.h"

/**
 * @brief           V2D toplevel config sequence
 * @param [in]      p_quad_params: pointer to QUAD-wise parameter
 * @param [in]      p_v2d: pointer to V2D module
 * @param [in]      chnl: the ANT index local to this V2D group
 * @return          none
 */
void rx_v2d_cfg_seq (const quad_params_t *const p_quad_params, volatile v2d_t *const p_v2d, uint8_t const chnl);

/**
 * @brief           enable V2D on RX, used in warmup seq
 * @param [in]      quad_idx: quad index (0 to 3)
 * @param [in]      ant_mask_in_quad: antenna mask in quad
 * @return          none
 */
void rx_v2d_en (uint8_t const quad_idx, uint8_t ant_mask_in_quad);

#endif /* __RX_V2D_H__ */

