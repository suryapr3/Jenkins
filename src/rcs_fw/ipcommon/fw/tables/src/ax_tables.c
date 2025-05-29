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

#include "ax_static_data_table.h"
#include "ax_static_data_data.h"

#ifdef __XTENSA__
#define DATA_ATTRIB __attribute__ ((section (".dram0.ax_tables.data")))
#else
#define DATA_ATTRIB
#endif

ax_static_data_t DATA_ATTRIB ax_static_data_init = {.ax_bfn_config_lut.ax_bfn_config_lut = AX_BFN_CONFIG_LUT_DATA,
                                                    .ax_bfn_selfsync_lut.ax_bfn_selfsync_lut = AX_BFN_SELFSYNC_LUT_DATA,
                                                    .ax_jesd_comp_param_lut.ax_jesd_comp_param_lut = AX_JESD_COMP_PARAM_LUT_DATA,
                                                    .ax_jesd_configuration_lut.ax_jesd_configuration_lut = AX_JESD_CONFIGURATION_LUT_DATA,
                                                    .ax_jesd_decomp_param_lut.ax_jesd_decomp_param_lut = AX_JESD_DECOMP_PARAM_LUT_DATA,
                                                    .ax_jesd_input_param_lut.ax_jesd_input_param_lut = AX_JESD_INPUT_PARAM_LUT_DATA,
                                                    .ax_jesd_rate_index_lut.ax_jesd_rate_index_lut = AX_JESD_RATE_INDEX_LUT_DATA,
                                                    .ax_print_config_lut.ax_print_config_lut = AX_PRINT_CONFIG_LUT_DATA};
