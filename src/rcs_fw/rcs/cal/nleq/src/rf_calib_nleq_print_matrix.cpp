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
 * @file    rf_calib_nleq_print_matrix.cpp
 * @brief   Implementation of printing the matrix values with formatting for both double and float versions of matrixes. With proper compile
 * time switches the implemetation will turn to simple returns
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_print_matrix.h"
#include "rf_calib_nleq_const.h"
#include <Eigen/Core>
#if DO_PRINTF_MATRIX
#include "rf_calib_nleq_log_message.h"
#include <string>
using namespace std;

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
 * @brief           Float matrix output print
 * @param [in]      m1: Reference to matrix whose contents will be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_matrix (rf_calib_float_matrix_dy_dy &m1)
{

    std::string sep = "\n----------------------------------------\n";
    IOFormat HeavyFmt (FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
    rf_calib_nleq_log_message_test (m1.format (HeavyFmt));
    return;
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Double matrix output print
 * @param [in]      m1: Reference to matrix whose contents will be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_matrix_double (rf_calib_double_matrix_dy_dy &m1)
{

    std::string sep = "\n----------------------------------------\n";
    IOFormat HeavyFmt (FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
    rf_calib_nleq_log_message_test (m1.format (HeavyFmt));
    return;
}
#else
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version Float matrix output print with simple return
 * @param [in]      m1: Reference to matrix whose contents will be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_matrix (rf_calib_float_matrix_dy_dy &m1) { return; }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version Double matrix output print with simple return
 * @param [in]      m1: Reference to matrix whose contents will be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_matrix_double (rf_calib_double_matrix_dy_dy &m1) { return; }

#endif
