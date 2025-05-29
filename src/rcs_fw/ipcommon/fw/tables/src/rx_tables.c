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

#include "rx_static_data_table.h"
#include "rx_static_data_data.h"

#ifdef __XTENSA__
#define DATA_ATTRIB __attribute__ ((section (".dram0.rx_tables.data")))
#else
#define DATA_ATTRIB
#endif

rx_static_data_t DATA_ATTRIB rx_static_data_init = {.rx_gain_lut.rx_gain_lut = RX_GAIN_LUT_DATA,
                                                    .rx_hwa_ant_meta_mapping_lut.rx_hwa_ant_meta_mapping_lut =
                                                        RX_HWA_ANT_META_MAPPING_LUT_DATA,
                                                    .rx_print_config_lut.rx_print_config_lut = RX_PRINT_CONFIG_LUT_DATA,
                                                    .rx_to_adc_cpu_config_lut.rx_to_adc_cpu_config_lut = RX_TO_ADC_CPU_CONFIG_LUT_DATA,
                                                    .rx_to_adc_cpu_delay_lut.rx_to_adc_cpu_delay_lut = RX_TO_ADC_CPU_DELAY_LUT_DATA,
                                                    .rx_topology_lut.rx_topology_lut = RX_TOPOLOGY_LUT_DATA,
                                                    .rx_vha_if_wm_lut.rx_vha_if_wm_lut = RX_VHA_IF_WM_LUT_DATA};
