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

#ifndef rf_calib_nleq_read_input_to_map__HH
#define rf_calib_nleq_read_input_to_map__HH
#if DO_INJECT
#include "rf_calib_nleq_const.h"
#include <fstream>
#include <iostream>
void rf_calib_nleq_read_observed_signal_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t col);
void rf_calib_nleq_read_target_signal_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t col);
std::ifstream &rf_calib_nleq_obtain_observed_signal_ifstream_ref (void);
std::ifstream &rf_calib_nleq_obtain_target_signal_ifstream_ref (void);
std::ifstream &rf_calib_nleq_obtain_target_signal_ifstream_ref (void);
std::ifstream &rf_calib_nleq_obtain_matlab_nleq_coeff_ifstream_ref (void);

#endif
#endif
