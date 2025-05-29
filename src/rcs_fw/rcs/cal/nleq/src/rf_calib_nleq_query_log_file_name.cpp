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
 * @file    rf_calib_nleq_query_log_file_name.cpp
 * @brief   Query and obtain the filenames of observed signal, target signal and the log output.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file rf_calib_nleq_query_log_file_name.cpp
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_query_log_file_name.h"
#include <Eigen/Core>
#include <cstddef>
using namespace std;
#if LOG_TO_FILE
#include <cstdio>
#endif
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
#if LOG_TO_FILE
char file_name[] = "nleq_output_float_double.txt";
char input_file_name_observed_signal[] = "rf_calib_nleq_observed_signal_reformatted.txt";
char input_file_name_target_signal[] = "rf_calib_nleq_target_signal_reformatted.txt";
char input_file_name_matlab_nleq_coeff[] = "rf_calib_nleq_matlab_nleq_coeff.txt";
#endif
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
 * @brief           Obtain the log file name
 * @param [in]      None
 * @return          char* pointing to the log file name
 * -------------------------------------------------------------------------------------------------------------------*/

#if LOG_TO_FILE
const char *rf_calib_nleq_query_log_file_name (void) { return (file_name); }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the observed signal file name
 * @param [in]      None
 * @return          char* pointing to the observed signal file name
 * -------------------------------------------------------------------------------------------------------------------*/
const char *rf_calib_nleq_query_input_file_name_observed_signal (void) { return (input_file_name_observed_signal); }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the target signal file name
 * @param [in]      None
 * @return          char* pointing to the target signal file name
 * -------------------------------------------------------------------------------------------------------------------*/
const char *rf_calib_nleq_query_input_file_name_target_signal (void) { return (input_file_name_target_signal); }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the MATLAB nleq coefficient output file name
 * @param [in]      None
 * @return          char* pointing to the  MATLAB nleq coefficient output file name
 * -------------------------------------------------------------------------------------------------------------------*/
const char *rf_calib_nleq_query_input_file_name_latlab_nleq_coeff (void) { return (input_file_name_matlab_nleq_coeff); }

#else
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version of obtain the log file name
 * @param [in]      None
 * @return          NULL
 * -------------------------------------------------------------------------------------------------------------------*/

const char *rf_calib_nleq_query_log_file_name (void) { return (NULL); }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version of obtain the observed signal file name
 * @param [in]      None
 * @return          NULL
 * -------------------------------------------------------------------------------------------------------------------*/
const char *rf_calib_nleq_query_input_file_name_observed_signal (void) { return (NULL); }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Dummy version of obtain the target signal file name
 * @param [in]      None
 * @return          NULL
 * -------------------------------------------------------------------------------------------------------------------*/
const char *rf_calib_nleq_query_input_file_name_target_signal (void) { return (NULL); }

#endif
