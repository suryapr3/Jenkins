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
 * @file    rf_calib_nleq_gen_x_suffix_l_matrix.cpp
 * @brief   Generate xl matrix according to the document in https://wiki.ith.intel.com/display/ITSxnerfdspfw/Calibration+flow
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_x_suffix_l_matrix.h"
#include "rf_calib_nleq_const.h"

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
 * @brief           Generate xl matrix.
 * @param [in]      inv_T_suffix_j: File from which the message was printed.
 * @param [in]      y_suffix_l: Reference to y_suffix_l matrix
 * @param [in]      c_suffix_l:  Reference to c_suffix_l matrix
 * @param [in]      x_suffix_NT: Reference to x_suffix_NT
 * @param [out]     x_suffix_l:  Reference to x_suffix_l matrix where the output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_x_suffix_l_matrix (rf_calib_double_matrix_dy_dy &inv_T_suffix_j, rf_calib_float_matrix_dy_dy &y_suffix_l,
                                          rf_calib_float_matrix_dy_dy &c_suffix_l, rf_calib_double_matrix_dy_dy &x_suffix_NT,
                                          rf_calib_double_matrix_dy_dy &x_suffix_l)
{
    x_suffix_l.col (0).noalias () =
        inv_T_suffix_j * (y_suffix_l.template cast<double> () - c_suffix_l.template cast<double> () * x_suffix_NT);
    return;
}
