/**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents ("Material") are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you ("License"). Unless the License provides otherwise, you may not use, modify,
 * copy, publish, distribute, disclose or transmit this software or the related documents
 * without Intel's prior written permission.
 * This software and the related documents are provided as is, with no express or implied
 * warranties, other than those that are expressly stated in the License.
 * No license under any patent, copyright, trade secret or other intellectual property
 * right is granted to or conferred upon you by disclosure or delivery of the Materials,
 * either expressly, by implication, inducement, estoppel or otherwise. Any license under
 * such intellectual property rights must be expressed and approved by Intel in writing.
 *
 *********************************************************************************************/

/**
 * @file    rf_cal_nleq_gen_ft_r_mi_x_lt_r_min_x_mat.cpp
 * @brief   Implementation of genarating LT_R_MIUNS_X and FT_R_MINUS_X matrizes
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_cal_nleq_gen_ft_r_mi_x_lt_r_min_x_mat.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_cal_nleq_gen_ft_r_mi_x_lt_r_min_x_mat.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Implement LT_R_MINUS_X and FT_R_MINUS_X matrixes
 * @param [in]      L_mat: Reference to L matrix
 * @param [in]      F_mat: Reference to F matrix
 * @param [in]      r_mat: Reference to R matrix
 * @param [in]      x_mat: Reference to X matrix
 * @param [out]     ft_r_minus_x: Reference to FT_R_MINUS_X where the output will be written
 * @param [out]     lt_r_minus_x: Reference to LT_R_MINUS_X where the output will be written
 * @param [in]      offset: offset into the R matrix L matrix to account for different phase of the ADC
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_ft_r_minus_x_lt_r_minus_x_matrix (rf_calib_float_matrix_dy_dy &L_mat, rf_calib_float_matrix_dy_dy &F_mat,
                                                         rf_calib_float_matrix_dy_dy &r_mat, rf_calib_float_matrix_dy_dy &x_mat,
                                                         rf_calib_float_matrix_dy_dy &ft_r_minus_x,
                                                         rf_calib_float_matrix_dy_dy &lt_r_minus_x, uint32_t offset)
{
    lt_r_minus_x.noalias () += (-L_mat.transpose ()
                                * (r_mat (seqN (offset + RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR,
                                                (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE), RF_CALIB_NLEQ_ADC_NUM_PHASE),
                                          all)
                                   - x_mat (seqN (offset + RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR,
                                                  (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE), RF_CALIB_NLEQ_ADC_NUM_PHASE),
                                            all)));
    ft_r_minus_x.noalias () += F_mat.transpose ()
                               * (r_mat (seqN (offset + RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR,
                                               (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE), RF_CALIB_NLEQ_ADC_NUM_PHASE),
                                         all)
                                  - x_mat (seqN (offset + RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR,
                                                 (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE), RF_CALIB_NLEQ_ADC_NUM_PHASE),
                                           all));
    return;
}
