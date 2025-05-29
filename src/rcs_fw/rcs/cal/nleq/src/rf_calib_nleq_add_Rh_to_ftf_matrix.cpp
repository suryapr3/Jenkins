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
 * @file    rf_calib_nleq_add_Rh_to_ftf_matrix.cpp
 * @brief   Add the Rh component to FTF matrix and transpose the output
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_add_Rh_to_ftf_matrix.h"
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
 * @brief           Add the Rh component, converted into a matrix to FTF and transpose the output
 * @param [in]      ftf: Reference to FTF matrix
 * @param [in]      rh_diagonal: Column matrix which will be converted into the same dimension as FTF
 * @param [out]     ftf_plus_Rh: Transpose of FTF+rh_diagonal
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_add_Rh_to_ftf_matrix (rf_calib_float_matrix_dy_dy &ftf, rf_calib_double_matrix_dy_dy &rh_diagonal,
                                         rf_calib_double_matrix_dy_dy &ftf_plus_Rh)
{
    ftf_plus_Rh = rh_diagonal + ftf.template cast<double> ();
    ftf_plus_Rh.template triangularView<Eigen::Upper> () = ftf_plus_Rh.transpose ();
    return;
}
