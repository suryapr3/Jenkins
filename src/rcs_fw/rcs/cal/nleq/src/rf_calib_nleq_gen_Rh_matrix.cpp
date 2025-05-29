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
 * @file    rf_calib_nleq_gen_Rh_matrix.cpp
 * @brief   Implements the generation of the Rh matrix which is a constant pre-defined matrix
 * @details Possibly this matrix should go into a table if changes are needed later
 * @todo    Write documentation for source file rf_calib_nleq_gen_Rh_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_Rh_matrix.h"
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
 * @brief           Generate the Rh_Diagonal matrix from the given Rh matrix
 * @param [in]      Rh_mat: Reference to a column matrix specifying the values which will form the diagonal of the Rh_Diagonal matrix
 * @param [out]     Rh_Diagonal: Reference to a square diagonal  matrix whose diagonal equals the values in Rh with rest
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_Rh_matrix (rf_calib_double_matrix_dy_dy &Rh_mat, rf_calib_double_matrix_dy_dy &Rh_Diagonal)
{
    Rh_mat (0, 0) = 0;
    Rh_mat (1, 0) = 9.53674316406250e-07 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (2, 0) = 9.53674316406250e-07 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (3, 0) = 9.53674316406250e-07 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (4, 0) = 7.62939453125000e-06 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (5, 0) = 7.62939453125000e-06 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (6, 0) = 7.62939453125000e-06 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (7, 0) = 7.62939453125000e-06 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (8, 0) = 7.62939453125000e-06 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (9, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (10, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (11, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (12, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (13, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (14, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (15, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (16, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_mat (17, 0) = 5.96046447753906e-08 * RF_CALIB_NLEQ_F_MATRIX_ROWS * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    Rh_Diagonal = Rh_mat.asDiagonal ();
    return;
}
