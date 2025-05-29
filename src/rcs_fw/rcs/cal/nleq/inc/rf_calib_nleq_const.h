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

#ifndef RF_CALIB_NLEQ_CONST__H
#define RF_CALIB_NLEQ_CONST__H
#include "com_eigen.h"
using namespace Eigen;
#define RF_CALIB_NLEQ_CAPTURE_SIZE                            1600 // Must be multiple of 64
#define RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR   12
#define RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_POST_CURSOR  11
#define RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_PRE_CURSOR  12 // Must be multiple of 4
#define RF_CALIB_NLEQ_INTERPOLATION_FILTER_OUTPUT_POST_CURSOR 11
#define RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR                    RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR
#define RF_CALIB_NLEQ_BASIS_GEN_POST_CURSOR                   RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_POST_CURSOR
#define RF_CALIB_NLEQ_ADC_NUM_PHASE                           16
#define RF_CALIB_NLEQ_BASIS_LENGTH                            18
#define RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH                    20
#define RF_CALIB_NLEQ_F_MATRIX_ROWS                           (RF_CALIB_NLEQ_CAPTURE_SIZE) / (RF_CALIB_NLEQ_ADC_NUM_PHASE)
#define RF_CALIB_NLEQ_INTERP_POLYPHASE_CHOICE                 1
#define RF_CALIB_NLEQ_BASIS_CHOICE                            1
#define RF_CALIB_NLEQ_BASIS_DELAY                             1
#define RF_CALIB_NLEQ_BASIS_LINEAR                            0
#define RF_CALIB_NLEQ_BASIS_SQUARE                            1
#define RF_CALIB_NLEQ_BASIS_CUBE                              2
#define RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR                 10
#define RF_CALIB_NLEQ_LINEAR_FILTER_POSTCURSOR                10
#define RF_CALIB_NLEQ_NUM_REF_SIGNALS                         3
#define RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH             24 // Must be multiple of 4
#define RF_CALIB_NLEQ_INTERPOLATION_FACTOR                    3
#define RF_CALIB_NLEQ_DMA_IN_FRACTIONAL_BITS                  15
#define RF_CALIB_NLEQ_COEFF_OUTPUT_NUM_FRACTIONAL_BITS        12
#define RF_CALIB_NLEQ_NON_TARGET_UN_CORRECTED_SIZE                                    \
    (RF_CALIB_NLEQ_CAPTURE_SIZE + RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR \
     + RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_POST_CURSOR)
#define RF_CALIB_NLEQ_NON_TARGET_REMAINDER       (4 - ((RF_CALIB_NLEQ_NON_TARGET_UN_CORRECTED_SIZE) % 4))
#define RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE ((RF_CALIB_NLEQ_NON_TARGET_UN_CORRECTED_SIZE) + (RF_CALIB_NLEQ_NON_TARGET_REMAINDER))
#endif
