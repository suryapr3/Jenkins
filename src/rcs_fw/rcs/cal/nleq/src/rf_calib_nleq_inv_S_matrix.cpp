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
 * @file    rf_calib_nleq_inv_S_matrix.cpp
 * @brief   Implementation of computing the inverse of S matrix using LDL solving
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_inv_S_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_inv_S_matrix.h"
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
 * @brief           Implement general matrix inversion using LDL decomposition
 * @param [in]      S: Reference to the S matrix to be inverted
 * @param [in]      identity: Reference to the identity matrix
 * @param [out]     S_inv:  Reference to the inverted output matrix
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_inv_S_matrix (rf_calib_double_matrix_dy_dy &S, rf_calib_double_matrix_dy_dy &identity,
                                 rf_calib_double_matrix_dy_dy &S_inv)
{

    S_inv = S.ldlt ().solve (identity);
    return;
}
