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
#ifndef AX_JESD_CONFIG_H
#define AX_JESD_CONFIG_H

#include <stdbool.h>
#include <stdint.h>

#define QUAD_NOT_USED 0xFAAF
typedef enum
{
    jesd_clk_1ghz,
    jesd_clk_1p5ghz,
} jesd_clk_t;

typedef enum
{
    jesd_204c,
    jesd_204d,
} jesd_mode_t;

typedef enum
{
    bfn_event,
    rxantenna_start,
} jesd_tx_start_t;

typedef enum
{
    div_char_clk_by_two,
    div_char_clk_by_four,
    div_char_clk_by_eight,
} jesd_char_clk_div_t;

typedef enum
{
    div_smpl_clk_by_one,
    div_smpl_clk_by_two,
    div_smpl_clk_by_four,
    div_smpl_clk_by_eight,
} jesd_smpl_clk_div_t;

typedef struct
{
    uint32_t use_case_idx;
    uint32_t jesd_quad_map[4]; // JESD link to respective quad mapping
} jesd_cfg_t;

/**
 * @brief JESD TX enable
 * @param [in]  jesd_cfg: JESD TX config data
 * @return
 */
void ax_jesd_tx_enable (uint8_t quad_mask);

/**
 * @brief JESD RX enable
 * @param [in]  jesd_cfg: JESD RX config data
 * @return
 */
void ax_jesd_rx_enable (uint8_t quad_mask);

/**
 * @brief JESD config routine
 * @param [in]  jesd_cfg: JESD TX config data
 * @return
 */
void ax_config_jesd_tx ();

/**
 * @brief JESD config routine
 * @param [in]  jesd_cfg: JESD RX config data
 * @return
 */
void ax_config_jesd_rx ();

#endif
