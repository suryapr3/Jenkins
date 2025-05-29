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
#ifndef AX_DACO_H
#define AX_DACO_H

#include "com_rf_def.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_NUM_QUAD      4
#define MAX_NUM_JESD_LINK 4
#define QUAD_NOT_USED     0xFAAF
typedef enum
{
    e_CFG_ANTENNA_MASK_QUAD_FAIL,
    e_CFG_SUCCESS

} e_cfg_ret_type_t;

typedef struct
{
    uint32_t mask;
    uint32_t use_case_idx;
    uint32_t jesd_quad_map[MAX_NUM_QUAD]; // JESD link to respective quad mapping
} cfg_jesd_t;

typedef struct
{
    uint32_t ant_mask;
    uint32_t num_cfg_quads;
    uint32_t cfg_quads[MAX_NUM_QUAD];
} cfg_ant_quad_info_t;

typedef struct
{
    e_ewpll_sel_t ewpll_sel; // east or west pll select for digital clock
    e_pll_clk_t east_pll_clock;
    e_pll_clk_t west_pll_clock;
    e_sys_clk_t bfn_digrf_clk;
} cfg_pll_info_t;

typedef struct
{
    bool is_first_cfg;
    cfg_pll_info_t cfg_pll_info;

    // antenna - quad info
    cfg_ant_quad_info_t tx_cfg_quads;
    cfg_ant_quad_info_t rx_cfg_quads;

    // jesd-link info
    cfg_jesd_t jesd_tx_cfg;
    cfg_jesd_t jesd_rx_cfg;
} ax_daco_t;

/**
 * @brief           returns ax daco addr
 * @param [in]      none
 * @return          ax_daco addr
 */
ax_daco_t *ax_daco_get_addr (void);

/**
 * @brief           sets antenna mask and quad mask
 * @param [in]      antenna mask , opcode of config message, and tx/rx configured quad info
 * @return          configuration success or failure
 */
e_cfg_ret_type_t ax_daco_set_quad_antenna_mask (uint16_t antenna_mask, uint32_t opcode, cfg_ant_quad_info_t *p_cfg_ant_quad);

/**
 * @brief           clear auxiliary core daco
 * @param [in]      ax daco
 * @return          none
 */
void ax_daco_clear (ax_daco_t *const p_ax_daco);

#endif
