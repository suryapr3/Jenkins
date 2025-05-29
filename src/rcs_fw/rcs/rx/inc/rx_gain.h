/* INTEL CONFIDENTIAL
 *
 * Copyright  2022 Intel Corporation All Rights Reserved.
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
#if (CPU_RX)
#include <stdlib.h>
#else
#error "Not RX CPU"
#endif

#ifndef RX_GAIN_H
#define RX_GAIN_H

/**
 * @brief           Set RX gain coefficient for FB_SYS
 * @param [in]      uint32_t: DRF index.
 * @param [in]      uint32_t: chain index.
 * @return          None.
 */
void rx_gain_fbsys_cfg (uint32_t const drf_idx, uint32_t const chain_idx);

/**
 * @brief           Set RX gain coefficient for TRX
 * @param [in]      uint32_t: group index.
 * @param [in]      uint32_t: channel index.
 * @return          None.
 */
void rx_gain_trxsys_cfg (uint32_t const grp_idx, uint32_t const chnl_idx);

#endif // RX_GAIN_H
