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
 * @file    rf_calib_nleq_convert_signal_periodic.cpp
 * @brief   Convert the captured target signal and the non target signal to be periodic
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_convert_signal_periodic.h"

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
 * @brief           Convert the non target signal to be periodic
 * @param [in]      a: Reference to the matrix which needs to be converted to be periodic
 * @param [in]      pre_cursor: Number of pre cursor samples
 * @param [in]      post_cursor:  Number of post cursor samples
 * @param [out]     The converted periodic output is returned in the input reference
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_convert_signal_periodic (rf_calib_float_matrix_dy_dy &a, uint32_t pre_cursor, uint32_t post_cursor)
{
    for (uint32_t i = 0; i < a.cols (); ++i)
    {
        a.col (i).topRows (pre_cursor) =
            a.col (i).middleRows (a.col (i).rows () - RF_CALIB_NLEQ_NON_TARGET_REMAINDER - post_cursor - pre_cursor, pre_cursor);
        a.col (i).middleRows (a.col (i).rows () - post_cursor - RF_CALIB_NLEQ_NON_TARGET_REMAINDER, post_cursor) =
            a.col (i).middleRows (pre_cursor, post_cursor);
    }
    return;
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Convert the target signal to be periodic
 * @param [in]      a: Reference to the matrix which needs to be converted to be periodic
 * @param [in]      pre_cursor: Number of pre cursor samples
 * @param [in]      post_cursor:  Number of post cursor samples
 * @param [out]     The converted periodic output is returned in the input reference
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_convert_target_signal_periodic (rf_calib_float_matrix_dy_dy &a, uint32_t pre_cursor, uint32_t post_cursor)
{
    for (uint32_t i = 0; i < a.cols (); ++i)
    {
        a.col (i).topRows (pre_cursor) = a.col (i).middleRows (a.col (i).rows () - post_cursor - pre_cursor, pre_cursor);
        a.col (i).bottomRows (post_cursor) = a.col (i).middleRows (pre_cursor, post_cursor);
    }
    return;
}
