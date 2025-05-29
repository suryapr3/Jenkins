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
 * @file    rf_calib_nleq_gen_q_j_update_q_j_1_matrix.cpp
 * @brief   Brief description of source file.
 * @details For a detailed description of the procedure refer to https://wiki.ith.intel.com/display/ITSxnerfdspfw/Calibration+flow
 * @todo    Write documentation for source file rf_calib_nleq_gen_q_j_update_q_j_1_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_q_j_update_q_j_1_matrix.h"
#include "rf_calib_nleq_const.h"
#include <Eigen/Core>

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
 * @brief           Generate Qj and update Qj-1. For detailed explanation refer to the NLEQ iterative procedure document mentioned in
 * https://wiki.ith.intel.com/display/ITSxnerfdspfw/Calibration+flow
 * @param [in]      q_suffix_j_1: Reference to the matrix q_suffix_j_1
 * @param [in]      C_suffix_j: Reference to the matrix C_suffix_j
 * @param [in]      inv_T_suffix_j:  Reference to the matrix inv_T_suffix_j
 * @param [in]      y_suffix_j:  Reference to the matrix y_suffix_j
 * @param [out]     q_suffix_j:  Reference to the matrix q_suffix_j where output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_q_suffix_j_update_q_suffix_j_1_matrix (rf_calib_double_matrix_dy_dy &q_suffix_j_1,
                                                              rf_calib_float_matrix_dy_dy &C_suffix_j,
                                                              rf_calib_double_matrix_dy_dy &inv_T_suffix_j,
                                                              rf_calib_float_matrix_dy_dy &y_suffix_j,
                                                              rf_calib_double_matrix_dy_dy &q_suffix_j)
{
    q_suffix_j.noalias () =
        q_suffix_j_1 - C_suffix_j.template cast<double> ().transpose () * inv_T_suffix_j * y_suffix_j.template cast<double> ();
    q_suffix_j_1 = q_suffix_j;
    return;
}
