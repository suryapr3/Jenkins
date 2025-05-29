/* INTEL CONFIDENTIAL
 *
 * Copyright 2024 Intel Corporation All Rights Reserved.
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

#include "com_static_data_table.h"
#include "com_static_data_data.h"

#ifdef __XTENSA__
#define DATA_ATTRIB __attribute__ ((section (".dram0.com_tables.data")))
#else
#define DATA_ATTRIB
#endif

com_static_data_t DATA_ATTRIB com_static_data_init = {.com_drf_rate_conf_lut.com_drf_rate_conf_lut = COM_DRF_RATE_CONF_LUT_DATA,
                                                      .com_fw_config_lut.com_fw_config_lut = COM_FW_CONFIG_LUT_DATA,
                                                      .com_jesd_hostid_lut.com_jesd_hostid_lut = COM_JESD_HOSTID_LUT_DATA,
                                                      .com_rxfb_hostid_lut.com_rxfb_hostid_lut = COM_RXFB_HOSTID_LUT_DATA,
                                                      .com_trax_addr_config_lut.com_trax_addr_config_lut = COM_TRAX_ADDR_CONFIG_LUT_DATA,
                                                      .com_v2d_hostid_lut.com_v2d_hostid_lut = COM_V2D_HOSTID_LUT_DATA,
                                                      .com_v2d_strm_buf_lut.com_v2d_strm_buf_lut = COM_V2D_STRM_BUF_LUT_DATA,
                                                      .com_v2d_strm_cfg_lut.com_v2d_strm_cfg_lut = COM_V2D_STRM_CFG_LUT_DATA,
                                                      .com_vex_hostid_lut.com_vex_hostid_lut = COM_VEX_HOSTID_LUT_DATA,
                                                      .com_vha_hostid_lut.com_vha_hostid_lut = COM_VHA_HOSTID_LUT_DATA,
                                                      .com_vha_if_wm_lut.com_vha_if_wm_lut = COM_VHA_IF_WM_LUT_DATA,
                                                      .com_vha_rate_conf_lut.com_vha_rate_conf_lut = COM_VHA_RATE_CONF_LUT_DATA};
