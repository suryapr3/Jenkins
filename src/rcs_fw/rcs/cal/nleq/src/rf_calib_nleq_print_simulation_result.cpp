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
 * @file    rf_calib_nleq_print_simulation_result.cpp
 * @brief   Implementation of simulation result output printing using fixed point outputs. compiles into simple return with compile time
 * switches
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_print_simulation_result.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_const.h"
#include <Eigen/Core>
#if DO_PRINTF
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
 * @brief           Implement printing out an integer matrix with proper formatting
 * @param [in]      m1: Reference to an integer matrix which needs to be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_simulation_result (rf_calib_int_matrix_dy_dy &m1)
{

    std::string sep = "\n----------------------------------------\n";
    IOFormat HeavyFmt (FullPrecision, 0, ", ", ";\n", "[", "]", "[", "]");
    rf_calib_nleq_log_message_test (m1.format (HeavyFmt));
    return;
}
#else
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version of implementation to print out an integer matrix with proper formatting
 * @param [in]      m1: Reference to an integer matrix which needs to be printed out
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_print_simulation_result (rf_calib_int_matrix_dy_dy &m1) { return; }
#endif
