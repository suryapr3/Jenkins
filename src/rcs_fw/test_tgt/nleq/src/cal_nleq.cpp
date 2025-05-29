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
 * @file    rf_calib_nleq_driver.cpp
 * @brief   The main driver function for implementing the NLEQ calibration
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#define EIGEN_NO_AUTOMATIC_RESIZING
#include <Eigen/Core>
#if DO_PRINTF
#include <cstdlib>
#include <iostream>
using namespace std;
#include "rf_calib_nleq_query_log_file_name.h"
#include <fstream>
#include <string>
#endif
#include "rf_cal_nleq_gen_ft_r_mi_x_lt_r_min_x_mat.h"
#include "rf_calib_com_heap.h"
#include "rf_calib_nleq_add_Rg_to_S_matrix.h"
#include "rf_calib_nleq_add_Rh_to_ftf_matrix.h"
#include "rf_calib_nleq_const.h"
#include "rf_calib_nleq_convert_ltl_to_full_matrix.h"
#include "rf_calib_nleq_convert_map_to_float_matrix.h"
#include "rf_calib_nleq_convert_signal_periodic.h"
#include "rf_calib_nleq_gen_F_matrix.h"
#include "rf_calib_nleq_gen_L_matrix.h"
#include "rf_calib_nleq_gen_Rh_matrix.h"
#include "rf_calib_nleq_gen_S_j_update_S_j_1_matrix.h"
#include "rf_calib_nleq_gen_ftf_matrix.h"
#include "rf_calib_nleq_gen_ftl_matrix.h"
#include "rf_calib_nleq_gen_ltl_matrix.h"
#include "rf_calib_nleq_gen_q_j_update_q_j_1_matrix.h"
#include "rf_calib_nleq_gen_x_suffix_NT_matrix.h"
#include "rf_calib_nleq_gen_x_suffix_l_matrix.h"
#include "rf_calib_nleq_interpolate.h"
#include "rf_calib_nleq_inv_S_matrix.h"
#include "rf_calib_nleq_inverse_ftf_plus_Rh_matrix.h"
#include "rf_calib_nleq_log_message.h"
#include "rf_calib_nleq_print_matrix.h"
#include "rf_calib_nleq_print_simulation_result.h"
#include "rf_calib_nleq_profile.h"
#include "rf_calib_nleq_qua_comp_exp_obt_diff.h"
#include "rf_calib_nleq_read_matlab_nleq_coeffs_to_matrix.h"
#include "rf_calib_nleq_read_observed_and_target_signals_to_map.h"
#include "rf_calib_nleq_save_inv_T_suffix_j_matrix.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
#if DO_PRINTF
static std::ofstream file_output_log;
static std::ifstream file_input_observed_signal;
static std::ifstream file_input_target_signal;
static std::ifstream file_input_matlab_nleq_coeff;
#endif
#if DO_PROFILE
static xt_counter_t start_time;
static xt_counter_t end_time;
#else
static uint32_t start_time;
static uint32_t end_time;
#endif

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static bool rf_calib_nleq_query_and_open_log_file (char *p_file_name);
static bool rf_calib_nleq_query_and_close_log_file (char *p_file_name);
static bool rf_calib_nleq_query_and_open_input_file_observed_signal (char *p_file_name);
static bool rf_calib_nleq_query_and_open_input_file_target_signal (char *p_file_name);
static bool rf_calib_nleq_query_and_close_input_file_observed_signal (char *p_file_name);
static bool rf_calib_nleq_query_and_close_input_file_target_signal (char *p_file_name);
static bool rf_calib_nleq_query_and_open_input_file_matlab_nleq_coeff (char *p_file_name);
static bool rf_calib_nleq_query_and_close_input_file_matlab_nleq_coeff (char *p_file_name);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Query the log file name and open the file for writing
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

static bool rf_calib_nleq_query_and_open_log_file (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_output_log.open (p_file_name, ios::out | ios::app);
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the log file name and close the file
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

static bool rf_calib_nleq_query_and_close_log_file (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_output_log.close ();
        return_val = file_output_log.good ();
    }
    return (return_val);

#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the observed signal file name and close the file
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool rf_calib_nleq_query_and_close_input_file_observed_signal (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_observed_signal.close ();
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the file containing the MATLAB computed NLEQ coefficients file name and close the file
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool rf_calib_nleq_query_and_close_input_file_matlab_nleq_coeff (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_matlab_nleq_coeff.close ();
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the target signal file name and close the file
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool rf_calib_nleq_query_and_close_input_file_target_signal (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_target_signal.close ();
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the file containing the MATLAB computed NLEQ coefficients file name and open the file for reading
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

static bool rf_calib_nleq_query_and_open_input_file_matlab_nleq_coeff (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_matlab_nleq_coeff.open (p_file_name, ios::in);
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the observed signal file name and open the file for reading
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool rf_calib_nleq_query_and_open_input_file_observed_signal (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_observed_signal.open (p_file_name, ios::in);
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Obtain the target signal file name and open the file for reading
 * @param [in]      p_file_name: pointer to the file name
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
static bool rf_calib_nleq_query_and_open_input_file_target_signal (char *p_file_name)
{
#if DO_PRINTF
    bool return_val = false;
    if (p_file_name)
    {
        file_input_target_signal.open (p_file_name, ios::in);
        return_val = file_output_log.good ();
    }
    return (return_val);
#else
    return (true);
#endif
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Main NLEQ calibration driver function
 * @param [in]      None
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

extern "C" int main (int argc, char *p_argv[])
{

#if DO_PRINTF
    rf_calib_nleq_query_and_open_log_file (p_argv[1]);
    rf_calib_nleq_query_and_open_input_file_observed_signal (p_argv[2]);
    rf_calib_nleq_query_and_open_input_file_target_signal (p_argv[3]);
    rf_calib_nleq_query_and_open_input_file_matlab_nleq_coeff (p_argv[4]);
#endif
    rf_calib_heap_create ();

    rf_calib_nleq_log_message_test ("Starting Simulation");
    rf_calib_float_matrix_dy_dy ftf[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    rf_calib_float_matrix_dy_dy ftf_try[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    rf_calib_nleq_log_message_test ("Create and initialize the array of FTF matrixes");
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    { ftf[i] = rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH); }
    rf_calib_nleq_log_message_test ("Create and initialize the array of FTL matrixes");
    rf_calib_float_matrix_dy_dy ftl[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    rf_calib_nleq_log_message_test ("Initializing the array of FTL matrixes");
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    { ftl[i] = rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH); }
    rf_calib_nleq_log_message_test ("creating LTL matrix");
    rf_calib_float_matrix_dy_dy rf_calib_ltl =
        rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
    rf_calib_nleq_log_message_test ("Create and initialize the array of ft_r_mius_x matrixes");
    rf_calib_float_matrix_dy_dy ft_r_minus_x[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    { ft_r_minus_x[i] = rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, 1); }
    rf_calib_nleq_log_message_test ("creating LT_R_MINUS_X matrix");
    rf_calib_float_matrix_dy_dy rf_calib_lt_r_minus_x = rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, 1);
    { // Begin a scope so that all temporary matrixes can be removed before starting the final iteration
        rf_calib_nleq_log_message_test ("creating interpolation output matrix");
        rf_calib_float_matrix_dy_dy rf_calib_interp_out (RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE, RF_CALIB_NLEQ_INTERPOLATION_FACTOR);
        rf_calib_nleq_log_message_test ("Creating the float version of DMA input vector-non target");
        rf_calib_float_matrix_dy_dy rf_calib_dma_in_float (RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE, 1);
        rf_calib_nleq_log_message_test ("Creating the float version of DMA input vector target");
        rf_calib_float_matrix_dy_dy rf_calib_dma_in_target_float (
            RF_CALIB_NLEQ_CAPTURE_SIZE + RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR + RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR, 1);
        rf_calib_nleq_log_message_test ("creating F matrix");
        rf_calib_float_matrix_dy_dy rf_calib_F (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE, RF_CALIB_NLEQ_BASIS_LENGTH);
        rf_calib_nleq_log_message_test ("creating L matrix");
        rf_calib_float_matrix_dy_dy rf_calib_L (RF_CALIB_NLEQ_CAPTURE_SIZE / RF_CALIB_NLEQ_ADC_NUM_PHASE,
                                                RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
        rf_calib_nleq_log_message_test ("creating the basis mapping array");
        uint32_t *p_basis_mapping = (uint32_t *)rf_calib_calloc (RF_CALIB_NLEQ_BASIS_LENGTH * 3, sizeof (uint32_t));
        rf_calib_float_matrix_dy_dy rf_calib_nleq_interp_filter =
            rf_calib_float_matrix_dy_dy::Zero (RF_CALIB_NLEQ_INTERPOLATION_FILTER_LENGTH, RF_CALIB_NLEQ_INTERPOLATION_FACTOR);
        for (uint32_t k = 0; k < RF_CALIB_NLEQ_NUM_REF_SIGNALS; ++k)
        {
            // DMA the non target captured signal
            // Perform the fixed point to float conversion
            // Store it in rf_calib_dma_in_float
            // Repeat the procedure for the target signal and store the floating point converted samples
            // after leaving RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR in the begining and RF_CALIB_NLEQ_LINEAR_FILTER_POSTCURSOR in the end
            // Release the dma_in array
            rf_calib_nleq_log_message_test ("Creating DMA input array for storing fixed point samples from capture memory");
            int32_t *dma_in = (int32_t *)rf_calib_calloc (RF_CALIB_NLEQ_CAPTURE_SIZE, sizeof (int32_t));
            rf_calib_int_map_dy_1 dma_in_int (dma_in, RF_CALIB_NLEQ_CAPTURE_SIZE);
#if DO_INJECT
            rf_calib_nleq_read_observed_signal_to_map (dma_in_int, k);
#endif
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_convert_map_to_float_matrix (dma_in_int, RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR,
                                                       rf_calib_dma_in_float);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:convert_observed_map_to_double_matrix ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_convert_signal_periodic (rf_calib_dma_in_float, RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_PRE_CURSOR,
                                                   RF_CALIB_NLEQ_INTERPOLATION_FILTER_INPUT_POST_CURSOR);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:convert_observed_signal_periodic ", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            rf_calib_nleq_log_message_test ("Observed periodic signal[", k, "]\n");
            rf_calib_nleq_print_matrix (rf_calib_dma_in_float);
            float *p_input = rf_calib_dma_in_float.data ();
            float *p_output = rf_calib_interp_out.data ();
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_interpolate_intrinsic (p_input, p_output);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:interpolate_observed_signal_intrinsic ", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            rf_calib_nleq_log_message_test ("Interpolator output for observed signal intrinsic[", k, "]\n");
            rf_calib_nleq_print_matrix (rf_calib_interp_out);
            rf_calib_interp_out.setZero (RF_CALIBB_NLEQ_NON_TARGET_CORRECTED_SIZE, RF_CALIB_NLEQ_INTERPOLATION_FACTOR);
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_interpolate (p_input, p_output);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:interpolate_observed_signal ", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_convert_signal_periodic (rf_calib_interp_out, RF_CALIB_NLEQ_BASIS_GEN_PRE_CURSOR,
                                                   RF_CALIB_NLEQ_BASIS_GEN_POST_CURSOR);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:convert_interpolate_observed_signal_periodic ", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            rf_calib_nleq_log_message_test ("Interpolator periodic output for observed signal[", k, "]\n");
            rf_calib_nleq_print_matrix (rf_calib_interp_out);
#if DO_INJECT
            rf_calib_nleq_read_target_signal_to_map (dma_in_int, k);
#endif
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_convert_map_to_float_matrix (dma_in_int, RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR, rf_calib_dma_in_target_float);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:convert_target_map_to_double_matrix ", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            start_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_convert_target_signal_periodic (rf_calib_dma_in_target_float, RF_CALIB_NLEQ_LINEAR_FILTER_PRECURSOR,
                                                          RF_CALIB_NLEQ_LINEAR_FILTER_POSTCURSOR);
            end_time = rf_calib_nleq_profile_read_counter ();
            rf_calib_nleq_log_message_test ("profile:convert_target_signal_periodic", "  ", start_time, "  ", end_time, "  ",
                                            end_time - start_time);
            rf_calib_nleq_log_message_test ("Target periodic signal[", k, "]\n");
            rf_calib_nleq_print_matrix (rf_calib_dma_in_target_float);
            rf_calib_free (dma_in);
            // Generate F matrix for all phases one by one
            for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
            {
                uint32_t offset = (i < (RF_CALIB_NLEQ_ADC_NUM_PHASE / 2)) ? i * 2 : 2 * (i % (RF_CALIB_NLEQ_ADC_NUM_PHASE / 2)) + 1;
                rf_calib_nleq_log_message_test ("F", i, "-", k, "\n");
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_F_matrix_new1 (rf_calib_interp_out, rf_calib_F, offset);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_F_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
                rf_calib_nleq_print_matrix (rf_calib_F);
                rf_calib_nleq_log_message_test ("L", i, "-", k, "\n");
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_L_matrix (rf_calib_dma_in_target_float, rf_calib_L, offset);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_L_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
                rf_calib_nleq_print_matrix (rf_calib_L);
                // Compute FTF matrix
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_ftf_matrix (rf_calib_F, ftf[i]);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_FTF_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
                rf_calib_nleq_log_message_test ("FTF[", i, "-", k, "]\n");
                rf_calib_nleq_print_matrix (ftf[i]);
                // Compute FTL matrix
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_ftl_matrix (rf_calib_F, rf_calib_L, ftl[i]);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_FTL_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
                rf_calib_nleq_log_message_test ("FTL[", i, "-", k, "]\n");
                rf_calib_nleq_print_matrix (ftl[i]);
                // Accumulate LTL
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_ltl_matrix (rf_calib_ltl, rf_calib_L);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_LTL_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
                rf_calib_nleq_log_message_test ("LTL[Iteration ", i, "-", k, "]\n");
                rf_calib_nleq_print_matrix (rf_calib_ltl);
                // Compute FT_R_MINUS_X matrix
                start_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_gen_ft_r_minus_x_lt_r_minus_x_matrix (rf_calib_L, rf_calib_F, rf_calib_dma_in_target_float,
                                                                    rf_calib_dma_in_float, ft_r_minus_x[i], rf_calib_lt_r_minus_x, offset);
                end_time = rf_calib_nleq_profile_read_counter ();
                rf_calib_nleq_log_message_test ("profile:gen_FT_R_MINUS_X_matrix_LT_R_MINUS_X", "  ", start_time, "  ", end_time, "  ",
                                                end_time - start_time);
                rf_calib_nleq_log_message_test ("FT_R_MINUS_X[", i, "-", k, "]\n");
                rf_calib_nleq_print_matrix (ft_r_minus_x[i]);
                rf_calib_nleq_log_message_test ("LT_R_MINUS_X[Iteration ", i, "-", k, "]\n");
                rf_calib_nleq_print_matrix (rf_calib_lt_r_minus_x);
            }
        }
        rf_calib_free (p_basis_mapping);
    } // End of Scope to remove all un needed matrixes
    rf_calib_double_matrix_dy_dy rf_calib_Rh (RF_CALIB_NLEQ_BASIS_LENGTH, 1);
    rf_calib_double_matrix_dy_dy ftf_double[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    rf_calib_nleq_log_message_test ("Create and initialize the array of FTF_Double matrixes");
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    { ftf_double[i] = rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH); }
    rf_calib_double_matrix_dy_dy rf_calib_Rh_diagonal =
        rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH);
    rf_calib_nleq_log_message_test ("creating the Rh diagonal matrix");
    rf_calib_nleq_gen_Rh_matrix (rf_calib_Rh, rf_calib_Rh_diagonal);

    // Add Rh component to the FTF matrix
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    {
        rf_calib_nleq_log_message_test ("FTF_plus_Rh[", i, "]\n");
        start_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_add_Rh_to_ftf_matrix (ftf[i], rf_calib_Rh_diagonal, ftf_double[i]);
        end_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_log_message_test ("profile:gen_FTF_plus_Rh_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
        rf_calib_nleq_print_matrix_double (ftf_double[i]);
    }
    start_time = rf_calib_nleq_profile_read_counter ();
    // Compute inverse of FTF+Rh matrix
    rf_calib_double_matrix_dy_dy inv_T_suffix_j =
        rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH);
    rf_calib_double_matrix_dy_dy rhs_identity;
    rhs_identity.setIdentity (RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH);
    // Perform the iterative solving for the coefficients
    // Convert the LTL lower triangular matrix to full matrix
    rf_calib_nleq_convert_ltl_to_full_matrix (rf_calib_ltl);
    rf_calib_double_matrix_dy_dy rf_calib_S_suffix_j =
        rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
    rf_calib_double_matrix_dy_dy rf_calib_S_suffix_j_1 =
        rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
    rf_calib_S_suffix_j_1 = rf_calib_ltl.template cast<double> ();
    rf_calib_double_matrix_dy_dy rf_calib_q_suffix_j = rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, 1);
    rf_calib_double_matrix_dy_dy rf_calib_q_suffix_j_1 = rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, 1);
    rf_calib_q_suffix_j_1 = rf_calib_lt_r_minus_x.template cast<double> ();
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:preparation_time_for_iteration", "  ", start_time, "  ", end_time, "  ",
                                    end_time - start_time);
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    {
        // Compute inv(T_suffix_j)
        rf_calib_nleq_log_message_test ("inv(T_suffix_j[", i, "])\n");
        start_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_inverse_ftf_plus_Rh_matrix (ftf_double[i], inv_T_suffix_j, rhs_identity);
        end_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_log_message_test ("profile:gen_Inv_T_Suffix_j", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
        rf_calib_nleq_print_matrix_double (inv_T_suffix_j);

        rf_calib_nleq_log_message_test ("S_suffix_j[", i, "]\n");
        start_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_gen_S_suffix_j_update_S_suffix_j_1_matrix (rf_calib_S_suffix_j_1, ftl[i], inv_T_suffix_j, rf_calib_S_suffix_j);
        end_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_log_message_test ("profile:gen_S_suffix_j_update_S_suffix_j_1_matrix", "  ", start_time, "  ", end_time, "  ",
                                        end_time - start_time);
        rf_calib_nleq_print_matrix_double (rf_calib_S_suffix_j);
        rf_calib_nleq_log_message_test ("q_suffix_j[", i, "]\n");
        start_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_gen_q_suffix_j_update_q_suffix_j_1_matrix (rf_calib_q_suffix_j_1, ftl[i], inv_T_suffix_j, ft_r_minus_x[i],
                                                                 rf_calib_q_suffix_j);
        end_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_log_message_test ("profile:gen_q_suffix_j_update_q_suffix_j_1_matrix", "  ", start_time, "  ", end_time, "  ",
                                        end_time - start_time);
        start_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_save_inv_T_suffix_j_matrix (inv_T_suffix_j, ftf_double[i]);
        end_time = rf_calib_nleq_profile_read_counter ();
        rf_calib_nleq_log_message_test ("profile:save_inv_T_suffix_j_matrix", "  ", start_time, "  ", end_time, "  ",
                                        end_time - start_time);
        rf_calib_nleq_print_matrix_double (rf_calib_q_suffix_j);
    }
    rf_calib_nleq_log_message_test ("[S_suffix_J]\n");
    rf_calib_nleq_print_matrix_double (rf_calib_S_suffix_j);
    rf_calib_nleq_log_message_test ("[q_suffix_j]\n");
    rf_calib_nleq_print_matrix_double (rf_calib_q_suffix_j);
    rf_calib_nleq_log_message_test ("[q_suffix_j-1]\n");
    rf_calib_nleq_print_matrix_double (rf_calib_q_suffix_j_1);
    rf_calib_nleq_log_message_test ("[S_suffix_J-1]\n");
    rf_calib_nleq_print_matrix_double (rf_calib_S_suffix_j_1);

    // Compute x_suffix_NT matrix
    // Construct Rg matrix
    start_time = rf_calib_nleq_profile_read_counter ();
    double temp = 7.62939453125000e-06 * RF_CALIB_NLEQ_CAPTURE_SIZE * RF_CALIB_NLEQ_NUM_REF_SIGNALS;
    rf_calib_double_matrix_dy_dy rf_calib_Rg = rf_calib_double_matrix_dy_dy ::Constant (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, 1, temp);
    rf_calib_double_matrix_dy_dy rhs_identity_ltl_size;
    rhs_identity_ltl_size.setIdentity (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
    rf_calib_double_matrix_dy_dy rf_calib_lte_x_suffix_NT = rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, 1);
    rf_calib_double_matrix_dy_dy inv_S =
        rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH, RF_CALIB_NLEQ_LINEAR_FILTER_LENGTH);
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:preparation_time_for_final_calculation", "  ", start_time, "  ", end_time, "  ",
                                    end_time - start_time);
    rf_calib_nleq_log_message_test ("Add Rg to S\n");
    start_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_add_Rg_to_S_matrix (rf_calib_S_suffix_j, rf_calib_Rg);
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:add_Rg_to_S_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
    rf_calib_nleq_log_message_test ("S_inverse\n");
    start_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_inv_S_matrix (rf_calib_S_suffix_j, rhs_identity_ltl_size, inv_S);
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:inv_S_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
    rf_calib_nleq_log_message_test ("x_suffix_NT\n");
    start_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_gen_x_suffix_NT_matrix (inv_S, rf_calib_q_suffix_j, rf_calib_lte_x_suffix_NT);
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:gen_x_suffix_NT_matrix", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
    rf_calib_nleq_print_matrix_double (rf_calib_lte_x_suffix_NT);

    rf_calib_nleq_log_message_test ("creating array of NLEQ filter coefficient matrixes");
    rf_calib_double_matrix_dy_dy x_suffix_l[RF_CALIB_NLEQ_ADC_NUM_PHASE];
    rf_calib_int_matrix_dy_dy rf_calib_nleq_coef_quantized[RF_CALIB_NLEQ_ADC_NUM_PHASE];

    start_time = rf_calib_nleq_profile_read_counter ();
    // Generate the rest of the NLEQ coefficients
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    {
        x_suffix_l[i] = rf_calib_double_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, 2);
        rf_calib_nleq_coef_quantized[i] = rf_calib_int_matrix_dy_dy::Zero (RF_CALIB_NLEQ_BASIS_LENGTH, 3);
        rf_calib_nleq_gen_x_suffix_l_matrix (ftf_double[i], ft_r_minus_x[i], ftl[i], rf_calib_lte_x_suffix_NT, x_suffix_l[i]);
    }
    end_time = rf_calib_nleq_profile_read_counter ();
    rf_calib_nleq_log_message_test ("profile:gen_final_filter_coeffs", "  ", start_time, "  ", end_time, "  ", end_time - start_time);
    for (uint32_t i = 0; i < RF_CALIB_NLEQ_ADC_NUM_PHASE; ++i)
    {
        rf_calib_nleq_log_message_test ("x_suffix_l[", i, "]\n");
        rf_calib_nleq_log_message_test ("Firmware\tMatlab\tDifference\n");
#if DO_INJECT
        rf_calib_nleq_read_matlab_nleq_coeffs_to_matrix (x_suffix_l[i], 1, 0, i * RF_CALIB_NLEQ_BASIS_LENGTH, RF_CALIB_NLEQ_BASIS_LENGTH);
#endif
        rf_calib_nleq_quantize_compute_expected_obtained_difference (x_suffix_l[i], rf_calib_nleq_coef_quantized[i]);
        rf_calib_nleq_print_simulation_result (rf_calib_nleq_coef_quantized[i]);
    }
#if DO_PRINTF
    rf_calib_nleq_query_and_close_log_file (p_argv[1]);
    rf_calib_nleq_query_and_close_input_file_observed_signal (p_argv[2]);
    rf_calib_nleq_query_and_close_input_file_target_signal (p_argv[3]);
    rf_calib_nleq_query_and_close_input_file_matlab_nleq_coeff (p_argv[4]);
#endif
    return(0);
}

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Return the refrence to the log file handle for external use
 * @param [in]      None
 * @return          Reference to the ofstream
 * -------------------------------------------------------------------------------------------------------------------*/

#if DO_PRINTF
std::ofstream &rf_calib_nleq_obtain_ofstream_ref (void) { return file_output_log; }

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Return the refrence to the observed signal file handle for external use
 * @param [in]      None
 * @return          Reference to the ofstream
 * -------------------------------------------------------------------------------------------------------------------*/

std::ifstream &rf_calib_nleq_obtain_observed_signal_ifstream_ref (void) { return file_input_observed_signal; }

/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Return the refrence to the target signal file handle for external use
 * @param [in]      None
 * @return          Reference to the ofstream
 * -------------------------------------------------------------------------------------------------------------------*/

std::ifstream &rf_calib_nleq_obtain_target_signal_ifstream_ref (void) { return file_input_target_signal; }
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Return the refrence to the MATLAB NLEQ coefficients file handle for external use
 * @param [in]      None
 * @return          Reference to the ofstream
 * -------------------------------------------------------------------------------------------------------------------*/

std::ifstream &rf_calib_nleq_obtain_matlab_nleq_coeff_ifstream_ref (void) { return file_input_matlab_nleq_coeff; }
#endif
