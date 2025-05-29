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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "rf_calib_nleq_gen_L_matrix.h"
#include "rf_calib_nleq_const.h"
#include <Eigen/Core>

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
 * @brief           Generate the L matrix from the captured target signal
 * @param [in]      rf_calib_dma_in_target_float: Reference to the captured target signal matrix
 * @param [out]     L: Reference to the L matrix where the output will be written
 * @param [in]      offset:  Offset into the rf_calib_dma_in_target_float matrix from where the data should be used in the L matrix
 * generation
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_L_matrix (rf_calib_float_matrix_dy_dy &rf_calib_dma_in_target_float, rf_calib_float_matrix_dy_dy &L, uint32_t offset)
{

    for (uint32_t i = 0; i < RF_CALIB_NLEQ_F_MATRIX_ROWS; ++i)
    {
        L.block<1, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH / 2> (i, 0) =
            rf_calib_dma_in_target_float (
                seq (offset + i * RF_CALIB_NLEQ_ADC_NUM_PHASE + 20, offset + i * RF_CALIB_NLEQ_ADC_NUM_PHASE + 11, fix<-1>), all)
                .transpose ();
        L.block<1, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH / 2> (i, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH / 2) =
            rf_calib_dma_in_target_float (
                seq (offset + i * RF_CALIB_NLEQ_ADC_NUM_PHASE + 9, offset + i * RF_CALIB_NLEQ_ADC_NUM_PHASE, fix<-1>), all)
                .transpose ();
    }
    return;
}
