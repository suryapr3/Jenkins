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
#if DO_INJECT
#include "rf_calib_nleq_read_observed_and_target_signals_to_map.h"
#include "rf_calib_nleq_const.h"
#include <fstream>
#include <iostream>
#include <string>

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define MAXBUFSIZE (10000)
using namespace std;

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static int16_t buff[MAXBUFSIZE];

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
static void rf_calib_nleq_read_input_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t output_column, uint32_t input_column,
                                             ifstream &infile);

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read the input from the file referred by th file handle, from the specified column and specified offset into a map
 * structure. The number of items to read is also an input
 * @param [out]     output: Reference to the map where the read values will be stored
 * @param [in]      output_column: The column in the matrix "output" where the read data will be written
 * @param [in]      input_column:  The column from the input file that will be read
 * @param [in]      infile:        Reference to the input file handle
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

static void rf_calib_nleq_read_input_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t output_column, uint32_t input_column, ifstream &infile)
{
    int rows = 0;
    // Read numbers from file into buffer.
    infile.clear ();
    infile.seekg (0);
    int16_t temp;
    string line;
    while (getline (infile, line))
    {
        int temp_cols = 0;
        stringstream stream (line);
        while (stream >> temp)
        {
            if (temp_cols == input_column)
            {
                buff[rows++] = temp;
                break;
            }
            else
            {
                ++temp_cols;
            }
        }
        temp_cols = 0;
    }
    if (rows != 0)
    {
        // Populate matrix with numbers.
        for (int i = 0; i < rows; i++) { output (i, output_column) = buff[i]; }
    }
    return;
}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read the observed signal file content to a map structure
 * @param [out]     output: Reference to the output map
 * @param [in]      input_column: column number from the file to be read
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_read_observed_signal_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t input_column)
{
    ifstream &infile = rf_calib_nleq_obtain_observed_signal_ifstream_ref ();
    rf_calib_nleq_read_input_to_map (output, 0, input_column, infile);
    return;
}
/* ---------------------------------------------------------------------------------------------------------------------
 * @brief           Read the target signal file content to a map structure
 * @param [out]     output: Reference to the output map
 * @param [in]      input_column: column number from the file to be read
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/

void rf_calib_nleq_read_target_signal_to_map (rf_calib_int16_t_map_dy_1 &output, uint32_t input_column)
{
    ifstream &infile = rf_calib_nleq_obtain_target_signal_ifstream_ref ();
    rf_calib_nleq_read_input_to_map (output, 0, input_column, infile);
    return;
}

#endif
