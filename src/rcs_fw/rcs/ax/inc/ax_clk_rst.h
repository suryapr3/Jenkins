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
#ifndef AX_CLK_RST_H
#define AX_CLK_RST_H

#include "com_rf_def.h"

#define RST_JESD_NUM_MAX 4

typedef struct
{
    e_sys_clk_t clk_sys;
    e_clk_ref_desel_t clk_ref_desel;
    e_pll_band_sel_t pll_band_sel; // ignored if clk_ref_desel==e_CLK_REF_DESEL_REF
    e_ewpll_sel_t ewpll_sel;
    uint16_t jesd_mask;
    uint16_t ant_mask;
    bool en_jesd;
    bool en_v2d;
} platform_clk_sel_t;

/**
 * @brief           Enable clocks and bring components out of reset. Call from AX config message.
 * @param [in]      none.
 * @return          none.
 */
void ax_clk_rst_init (platform_clk_sel_t const *const p_freq_sel);

/**
 * @brief           Clear reset sequence internal state.
 * @param [in]      none.
 * @return          none.
 */
void ax_clk_rst_shutdown ();
#endif // AX_CLK_RST_H
