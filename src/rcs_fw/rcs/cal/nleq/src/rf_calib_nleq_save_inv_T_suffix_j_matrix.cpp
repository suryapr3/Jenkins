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
 * @file    rf_calib_nleq_save_inv_T_suffix_j_matrix.cpp
 * @brief   Implementation of saving the INV_T_SUFFIX_J matrix into FTF to conserve space
 * @details For details of the re use of memory refer to the attached document at
 * https://wiki.ith.intel.com/display/ITSxnerfdspfw/Calibration+flow
 * @todo    Write documentation for source file rf_calib_nleq_save_inv_T_suffix_j_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_save_inv_T_suffix_j_matrix.h"
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
 * @brief           Save the T_suffix_j matrix into the memory of FTF matrix
 * @param [in]      T_suffix_j: Reference to the T_Suffix_j matrix
 * @param [out]     ftf: Reference to the FTF matrix
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_save_inv_T_suffix_j_matrix (rf_calib_double_matrix_dy_dy &T_suffix_j, rf_calib_double_matrix_dy_dy &ftf)
{
    ftf = T_suffix_j;
    return;
}
