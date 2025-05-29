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
#include "rf_calib_nleq_gen_ftf_matrix.h"
#include "rf_calib_nleq_const.h"
#include "rf_calib_nleq_dot_product_optimized.h"

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
 * @brief           Generate the FTF matrix from the F matrix
 * @param [in]      F_mat: Reference to the F matrix
 * @param [out]     ftf: Reference to the ftf matrix where results will be written
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_gen_ftf_matrix (rf_calib_float_matrix_dy_dy &F_mat, rf_calib_float_matrix_dy_dy &ftf)
{
#if LTLFTF_EIGEN == 1
    ftf.noalias () += (F_mat.transpose () * F_mat);
    return;
#endif

#if LTLFTF_EIGEN_OPTIMIZED == 1
    ftf.template selfadjointView<Eigen::Lower> ().rankUpdate (F_mat.transpose ());
    return;
#endif

#if LTLFTF_HANDCODED
    float *temp = F_mat.data ();
    float *temp1 = ftf.data ();
    int size = RF_CALIB_NLEQ_F_MATRIX_ROWS;
    // 18 = 4*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);
    rf_calib_dot_product_2_opt (temp, temp + 1600, size, temp1 + 16);
    temp += size;
    temp1 += 19;
    // 17 = 2 + 3*4 + 2 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_4_opt (temp, temp + 600, size, temp1 + 6);
    rf_calib_dot_product_4_opt (temp, temp + 1000, size, temp1 + 10);
    rf_calib_dot_product_2_opt (temp, temp + 1400, size, temp1 + 14);
    rf_calib_dot_product_1_opt (temp, temp + 1600, size, temp1 + 16);
    temp += size;
    temp1 += 19;
    // 16 = 4*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_4_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 19;
    // 15 = 2 + 3*4 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_4_opt (temp, temp + 600, size, temp1 + 6);
    rf_calib_dot_product_4_opt (temp, temp + 1000, size, temp1 + 10);
    rf_calib_dot_product_1_opt (temp, temp + 1400, size, temp1 + 14);

    temp += size;
    temp1 += 19;
    // 14 = 3*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);
    rf_calib_dot_product_2_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 19;
    // 13 = 2 + 2*4 + 2 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_4_opt (temp, temp + 600, size, temp1 + 6);
    rf_calib_dot_product_2_opt (temp, temp + 1000, size, temp1 + 10);
    rf_calib_dot_product_1_opt (temp, temp + 1200, size, temp1 + 12);

    temp += size;
    temp1 += 19;
    // 12 = 3*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_4_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 19;
    // 11 = 2 + 2*4 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_4_opt (temp, temp + 600, size, temp1 + 6);
    rf_calib_dot_product_1_opt (temp, temp + 1000, size, temp1 + 10);

    temp += size;
    temp1 += 19;
    // 10 = 2*4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);
    rf_calib_dot_product_2_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 19;
    // 9 = 2 + 4 + 2 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_2_opt (temp, temp + 600, size, temp1 + 6);
    rf_calib_dot_product_1_opt (temp, temp + 800, size, temp1 + 8);

    temp += size;
    temp1 += 19;
    // 8 = 2*4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 19;
    // 7 = 2 + 4 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_4_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_1_opt (temp, temp + 600, size, temp1 + 6);

    temp += size;
    temp1 += 19;
    // 6 = 4 + 2
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);
    rf_calib_dot_product_2_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 19;
    // 5 = 2 + 2 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_2_opt (temp, temp + 200, size, temp1 + 2);
    rf_calib_dot_product_1_opt (temp, temp + 400, size, temp1 + 4);

    temp += size;
    temp1 += 19;
    // 4 = 4
    rf_calib_dot_product_4_opt (temp, temp, size, temp1);

    temp += size;
    temp1 += 19;
    // 3 = 2 + 1
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);
    rf_calib_dot_product_1_opt (temp, temp + 200, size, temp1 + 2);

    temp += size;
    temp1 += 19;
    // 2 = 2
    rf_calib_dot_product_2_opt (temp, temp, size, temp1);

    temp += size;
    temp1 += 19;
    // 1 = 1
    rf_calib_dot_product_1_opt (temp, temp, size, temp1);
    return;
#endif
}
