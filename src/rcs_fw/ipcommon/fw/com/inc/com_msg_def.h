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
#ifndef COMMON_MSG_DEF_H
#define COMMON_MSG_DEF_H

#include "dl_req_msg.h"
#include "ul_req_msg.h"
#include "readback_msg.h"
#include "admin_msg.h"
#include "set_time_ref_msg.h"
#include "dl_spi_req_msg.h"
#include "ul_spi_req_msg.h"
#include <stdbool.h>
#include <stdint.h>

//! @brief Union of all macros
typedef union {
    dl_config_ant_grp_bf_t dl_config_ant_grp;
    dl_on_bf_t dl_on;
    dl_update_control_bf_t dl_update_control;
    dl_off_bf_t dl_off;
    ul_config_ant_grp_bf_t ul_config_ant_grp;
    ul_on_bf_t ul_on;
    ul_update_control_bf_t ul_update_control;
    ul_off_bf_t ul_off;
    ul_config_readback_bf_t ul_config_readback;
    dl_config_readback_bf_t dl_config_readback;
    ul_on_readback_bf_t ul_on_readback;
    dl_on_readback_bf_t dl_on_readback;
    warmup_readback_bf_t warmup_readback;
    debug_readback_bf_t debug_readback;
    error_readback_bf_t error_readback;
    bfn_sync_bf_t bfn_sync;
    set_time_ref_bf_t set_time_ref;
    cal_config_bf_t cal_config;
    sleep_control_bf_t sleep_control;
    reconfig_bf_t reconfig;
    shutdown_bf_t shutdown;
    warmup_bf_t warmup;
    boot_readback_bf_t boot_readback;
    dl_spi_on_bf_t dl_spi_on;
    dl_spi_off_bf_t dl_spi_off;
    ul_spi_on_bf_t ul_spi_on;
    ul_spi_off_bf_t ul_spi_off;
} msg_t;

#endif
