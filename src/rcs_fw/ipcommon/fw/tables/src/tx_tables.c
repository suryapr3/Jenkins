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

#include "tx_static_data_table.h"
#include "tx_static_data_data.h"

#ifdef __XTENSA__
#define DATA_ATTRIB __attribute__ ((section (".dram0.tx_tables.data")))
#else
#define DATA_ATTRIB
#endif

tx_static_data_t DATA_ATTRIB tx_static_data_init = {.tx_dac_conf_lut.tx_dac_conf_lut = TX_DAC_CONF_LUT_DATA,
                                                    .tx_jesd_ant_meta_mapping_lut.tx_jesd_ant_meta_mapping_lut =
                                                        TX_JESD_ANT_META_MAPPING_LUT_DATA,
                                                    .tx_pdpd_cfg_lut.tx_pdpd_cfg_lut = TX_PDPD_CFG_LUT_DATA,
                                                    .tx_pdpd_dly_lut.tx_pdpd_dly_lut = TX_PDPD_DLY_LUT_DATA,
                                                    .tx_pdpd_mod_lut.tx_pdpd_mod_lut = TX_PDPD_MOD_LUT_DATA,
                                                    .tx_pdpd_pc_sel_lut.tx_pdpd_pc_sel_lut = TX_PDPD_PC_SEL_LUT_DATA,
                                                    .tx_print_config_lut.tx_print_config_lut = TX_PRINT_CONFIG_LUT_DATA,
                                                    .tx_topology_lut.tx_topology_lut = TX_TOPOLOGY_LUT_DATA,
                                                    .tx_v2d_if_params_lut.tx_v2d_if_params_lut = TX_V2D_IF_PARAMS_LUT_DATA,
                                                    .tx_v2d_start_dly_lut.tx_v2d_start_dly_lut = TX_V2D_START_DLY_LUT_DATA};
