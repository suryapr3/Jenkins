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
 * @file    rf_calib_nleq_inverse_ftf_plus_Rh_matrix.cpp
 * @brief   Compute the inverse of the modified FTF matrix using LDL decomposition
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_inverse_ftf_plus_Rh_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_inverse_ftf_plus_Rh_matrix.h"
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
 * @brief           Implement inverse of FTF matrix using LDL decomposition
 * @param [in]      ftf_plus_Rh: Reference to the modified FTF matrix to be inverted
 * @param [out]     inv_ftf_plus_Rh: Reference to the output matrix to store the inverted matrix
 * @param [in]      rhs_identity:  Reference to the identity matrix of same dimension as ftf_plus_Rh to solve the equation
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_inverse_ftf_plus_Rh_matrix (rf_calib_double_matrix_dy_dy &ftf_plus_Rh, rf_calib_double_matrix_dy_dy &inv_ftf_plus_Rh,
                                               rf_calib_double_matrix_dy_dy &rhs_identity)
{
    inv_ftf_plus_Rh = ftf_plus_Rh.ldlt ().solve (rhs_identity);
    return;
}
