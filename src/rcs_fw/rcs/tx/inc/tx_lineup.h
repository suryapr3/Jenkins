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
#ifndef __TX_LINEUP_H__
#define __TX_LINEUP_H__

#include "com_rf_def.h"

/**
 * @brief           TX lineup configuration
 * @param [in]      ant_mask: 16-bit mask specifying which ANTs to use
 * @return          none
 */
void tx_lineup_cfg (uint16_t ant_mask);

/**
 * @brief           TX lineup DRF level configuration
 * @param [in]      drf_idx: DRF index to indicate which DRF (east/west) to use
 * @param [in]      ant_mask_in_drf: 8-bit mask specifying whcih ANTs (local) to use in one DRF
 * @return          none
 */
void tx_drf_cfg (e_drf_sel_t const drf_idx, uint8_t ant_mask_in_drf);

/**
 * @brief           TX lineup QUAD level configuration
 * @param [in]      quad_idx: QUADS index to indicate which QUAD (0 to 3) to use
 * @param [in]      ant_mask_in_quad: 4-bit (LSB) mask specifying whcih ANTs (local) to use in one QUAD
 * @return          none
 */
void tx_quad_cfg (uint8_t const quad_idx, uint8_t ant_mask_in_quad);

/**
 * @brief           DRF ANT block GROUP level configuration
 * @param [in]      quad_idx: QUADS index to indicate which QUAD (0 to 3) to use
 * @param [in]      ant_mask_in_quad: 4-bit (LSB) mask specifying whcih ANTs (local) to use in one QUAD
 * @return          none
 */
void drf_ant_cfg_seq (uint8_t const quad_idx, uint8_t ant_mask_in_quad);

/**
 * @brief           TX lineup GROUP level configuration
 * @param [in]      grp_idx: GROUP index to indicate which GROUP (0 to 7) to use
 * @param [in]      ant_mask_in_grp: 2-bit (LSB) mask specifying whcih ANTs (local) to use in one GROUP
 * @return          none
 */
void tx_grp_cfg (uint8_t const grp_idx, uint8_t ant_mask_in_grp);

#endif /* __TX_LINEUP_H__ */
