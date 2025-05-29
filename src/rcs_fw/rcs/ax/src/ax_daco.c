/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/

/**
 * @file    ax_daco.c
 * @brief   Functions to initialize and clear ax daco
 * @details Auxiliary core daco functions
 */

#if (CPU_AX)
#else
#error "Not AX CPU"
#endif

#include <stdint.h>
#include <string.h>

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "ax_daco.h"
#include "com_print.h"
#include "com_assert.h"
#include "com_error.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
ax_daco_t ax_daco = {
    .is_first_cfg = true,

    .cfg_pll_info.ewpll_sel = e_EWPLL_SEL_EAST,

    .rx_cfg_quads.num_cfg_quads = 0,
    .tx_cfg_quads.num_cfg_quads = 0,

    .rx_cfg_quads.cfg_quads[0] = 0xFFFFFFFF,
    .rx_cfg_quads.cfg_quads[1] = 0xFFFFFFFF,
    .rx_cfg_quads.cfg_quads[2] = 0xFFFFFFFF,
    .rx_cfg_quads.cfg_quads[3] = 0xFFFFFFFF,

    .tx_cfg_quads.cfg_quads[0] = 0xFFFFFFFF,
    .tx_cfg_quads.cfg_quads[1] = 0xFFFFFFFF,
    .tx_cfg_quads.cfg_quads[2] = 0xFFFFFFFF,
    .tx_cfg_quads.cfg_quads[3] = 0xFFFFFFFF,

    .jesd_rx_cfg.use_case_idx = 0,
    .jesd_tx_cfg.use_case_idx = 0,

    .jesd_rx_cfg.mask = 0,
    .jesd_tx_cfg.mask = 0,

    .jesd_rx_cfg.jesd_quad_map[0] = QUAD_NOT_USED,
    .jesd_rx_cfg.jesd_quad_map[1] = QUAD_NOT_USED,
    .jesd_rx_cfg.jesd_quad_map[2] = QUAD_NOT_USED,
    .jesd_rx_cfg.jesd_quad_map[3] = QUAD_NOT_USED,

    .jesd_tx_cfg.jesd_quad_map[0] = QUAD_NOT_USED,
    .jesd_tx_cfg.jesd_quad_map[1] = QUAD_NOT_USED,
    .jesd_tx_cfg.jesd_quad_map[2] = QUAD_NOT_USED,
    .jesd_tx_cfg.jesd_quad_map[3] = QUAD_NOT_USED,
};

static ax_daco_t *p_ax_daco_addr = (ax_daco_t *)&ax_daco;
/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           returns ax daco addr
 * @param [in]      none
 * @return          ax_daco addr
 */
ax_daco_t *ax_daco_get_addr (void)
{
    return p_ax_daco_addr;
}

/**
 * @brief           clear auxiliary core daco
 * @param [in]      ax daco
 * @return          none
 */

void ax_daco_clear (ax_daco_t *const p_ax_daco)
{
    p_ax_daco->rx_cfg_quads.num_cfg_quads = 0;
    p_ax_daco->tx_cfg_quads.num_cfg_quads = 0;

    p_ax_daco->is_first_cfg = true;
    p_ax_daco->cfg_pll_info.ewpll_sel = e_EWPLL_SEL_EAST;

    p_ax_daco->rx_cfg_quads.cfg_quads[0] = 0xFFFFFFFF;
    p_ax_daco->rx_cfg_quads.cfg_quads[1] = 0xFFFFFFFF;
    p_ax_daco->rx_cfg_quads.cfg_quads[2] = 0xFFFFFFFF;
    p_ax_daco->rx_cfg_quads.cfg_quads[3] = 0xFFFFFFFF;

    p_ax_daco->tx_cfg_quads.cfg_quads[0] = 0xFFFFFFFF;
    p_ax_daco->tx_cfg_quads.cfg_quads[1] = 0xFFFFFFFF;
    p_ax_daco->tx_cfg_quads.cfg_quads[2] = 0xFFFFFFFF;
    p_ax_daco->tx_cfg_quads.cfg_quads[3] = 0xFFFFFFFF;

    p_ax_daco->jesd_rx_cfg.mask = 0;
    p_ax_daco->jesd_rx_cfg.use_case_idx = 0;
    memset (p_ax_daco->jesd_rx_cfg.jesd_quad_map, QUAD_NOT_USED, sizeof (p_ax_daco->jesd_rx_cfg.jesd_quad_map));

    p_ax_daco->jesd_tx_cfg.mask = 0;
    p_ax_daco->jesd_tx_cfg.use_case_idx = 0;
    memset (p_ax_daco->jesd_tx_cfg.jesd_quad_map, QUAD_NOT_USED, sizeof (p_ax_daco->jesd_rx_cfg.jesd_quad_map));
}

/**
 * @brief           sets antenna mask and quad mask
 * @param [in]      antenna mask and tx/rx configured quad info
 * @return          configuration success or failure
 */
e_cfg_ret_type_t ax_daco_set_quad_antenna_mask (uint16_t antenna_mask, uint32_t opcode, cfg_ant_quad_info_t *p_cfg_ant_quad)
{
    p_cfg_ant_quad->ant_mask |= antenna_mask;
    FW_PRINT (FW_INFO, "ax_daco_set_quad_antenna_mask antenna_mask : %d  ", antenna_mask);
    for (int quad_id = 0; quad_id < MAX_NUM_QUAD; quad_id++)
    {
        if (antenna_mask & (0xF << (quad_id * MAX_NUM_QUAD)))
        {
            // Error on already cfged quads
            for (int i = 0; i < p_cfg_ant_quad->num_cfg_quads; i++)
            {
                if (quad_id == p_cfg_ant_quad->cfg_quads[i])
                {
                    FW_PRINT (FW_ERR, "Already configured quad : %d ", quad_id);
                    FW_SEND_ERR_RB (e_CONFIG_MSG_ERR, e_CFG_ANTENNA_MASK_QUAD_ERR, opcode, quad_id);
                    return e_CFG_ANTENNA_MASK_QUAD_FAIL;
                }
            }
            p_cfg_ant_quad->cfg_quads[p_cfg_ant_quad->num_cfg_quads] = quad_id;
            p_cfg_ant_quad->num_cfg_quads++;
            RT_ASSERT (p_cfg_ant_quad->num_cfg_quads <= MAX_NUM_QUAD);
            FW_PRINT (FW_INFO, "quad id : %d num_cfg_quad :%d ", quad_id, p_cfg_ant_quad->num_cfg_quads);
        }
    }
    return e_CFG_SUCCESS;
}
