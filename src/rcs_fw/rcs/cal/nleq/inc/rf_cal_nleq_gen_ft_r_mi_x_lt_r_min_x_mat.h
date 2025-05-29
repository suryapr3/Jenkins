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

#ifndef RF_CALIB_NLEQ_gen_ft_r_minus_x_lt_r_minus_x_matrix_H
#define RF_CALIB_NLEQ_gen_ft_r_minus_x_lt_r_minus_x_matrix_H
#include "rf_calib_nleq_const.h"
void rf_calib_nleq_gen_ft_r_minus_x_lt_r_minus_x_matrix (rf_calib_float_matrix_dy_dy &L_mat, rf_calib_float_matrix_dy_dy &F_mat,
                                                         rf_calib_float_matrix_dy_dy &r_mat, rf_calib_float_matrix_dy_dy &x_mat,
                                                         rf_calib_float_matrix_dy_dy &ft_r_minus_x,
                                                         rf_calib_float_matrix_dy_dy &lt_r_minus_x, uint32_t offset);
#endif
