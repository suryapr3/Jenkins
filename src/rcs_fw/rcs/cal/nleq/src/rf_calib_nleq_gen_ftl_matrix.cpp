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
 * @file    rf_calib_nleq_gen_ftl_matrix.cpp
 * @brief   Contains the implementation of the FTL matrix generation
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_gen_ftl_matrix.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_ftl_matrix.h"

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
 * @brief           Generate the FTL matrix from the F and L matrixes
 * @param [in]      F_mat: Reference to the F_matrix
 * @param [in]      L_mat: Reference to the L matrix
 * @param [out]     ftl: Reference to the ftl matrix where the output will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_ftl_matrix (rf_calib_float_matrix_dy_dy &F_mat, rf_calib_float_matrix_dy_dy &L_mat, rf_calib_float_matrix_dy_dy &ftl)
{
    ftl.noalias () += (-F_mat.transpose () * L_mat);
    return;
}
