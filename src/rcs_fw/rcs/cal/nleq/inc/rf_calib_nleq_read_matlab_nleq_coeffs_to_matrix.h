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

#ifndef rf_calib_nleq_read_input_to_matrix__HH
#define rf_calib_nleq_read_input_to_matrix__HH
#if DO_INJECT
#include "rf_calib_nleq_const.h"
#include <fstream>
#include <iostream>
void rf_calib_nleq_read_matlab_nleq_coeffs_to_matrix (rf_calib_double_matrix_dy_dy &output, uint32_t output_colum, uint32_t input_column,
                                                      uint32_t input_offset, uint32_t num_to_read);
static void rf_calib_nleq_read_input_to_matrix (rf_calib_double_matrix_dy_dy &output, uint32_t output_column, uint32_t input_column,
                                                uint32_t input_offset, uint32_t num_to_read, std::ifstream &infile);
std::ifstream &rf_calib_nleq_obtain_matlab_nleq_coeff_ifstream_ref (void);
#endif
#endif
