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

#ifndef RF_CALIB_NLEQ_dot_product_optimized_H
#define RF_CALIB_NLEQ_dot_product_optimized_H
#include "rf_calib_nleq_const.h"
void rf_calib_dot_product_2_opt (const float *__restrict p_input_1, const float *__restrict p_input_2, int size,
                                 float *__restrict p_output);
void rf_calib_dot_product_1_opt (const float *__restrict p_input_1, const float *__restrict p_input_2, int size,
                                 float *__restrict p_output);
void rf_calib_dot_product_4_opt (const float *__restrict p_input_base, const float *__restrict p_input_start, int size,
                                 float *__restrict p_output);
#endif
