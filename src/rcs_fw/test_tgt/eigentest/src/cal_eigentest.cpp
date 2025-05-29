 /**********************************************************************************************
 *
 * INTEL CONFIDENTIAL
 *
 * Copyright (C) 2022 Intel Corporation
 *
 * This software and the related documents "Material" are Intel copyrighted materials,
 * and your use of them is governed by the express license under which they were provided
 * to you "License". Unless the License provides otherwise, you may not use, modify,
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
 * @file    cal_eigentest.cpp
 * @brief   Perform a simple KP1 test of multiplying 2 5 by 5 matrixes and write the result
 *          to the shared memory
 * @details The input for the multiplication comes from the 2 fixed point arrays
 *          stored in the shared memory
 * @todo    Write documentation for source file cal_eigentest.cpp
 */


/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include <cstdint>
#include <stdint.h>
#include "com_eigen.h"
#include "com_print.h"
#include "rf_calib_com_heap.h"
#include "com_shared_memory.h"
/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define CALTEST_MATRIX_SIZE 25
#define CALTEST_MATRIX_ROW_SIZE 5
#define CALTEST_MATRIX_COLUMN_SIZE 5
#define CALTEST_INPUT_FRACTIONAL_BITS 28
#define CALTEST_OUTPUT_FRACTIONAL_BITS 23
#define CALTEST_TOLERANCE 0.000001
#define CALTEST_TEST_BENCH_LOADING_MAGIC 0x11112222
#define CALTEST_READ_TRACE_ADDRESS 0x220000
enum CALTEST_SRAM_FILL_VALUE : int32_t
{
    PATTERN_A = 0x5555AAAA,
    PATTERN_B = 0x7777BBBB
};

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums     *
 ***********************************************/
using rf_calib_float_map_dy_1 = Eigen::Map<Eigen::Matrix<float, Dynamic, 1>, Eigen::Aligned128, Stride<1, 1>>;
/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static int32_t __attribute__ ((section (".sram.reserved"))) rf_calib_kp1_test_signal_A_int[CALTEST_MATRIX_SIZE+1] = {
1351727940,
1742863099,
-1602079425,
1775435783,
568478634,
-1728550798,
-951342906,
201354592,
1964976896,
1996681055,
-1470540617,
2021180607,
1963517092,
-62811110,
1289694794,
-1538086464,
-336032732,
1785570484,
1255020924,
1973504944,
668901210,
-1994103156,
1499498951,
1863986806,
767661645,
CALTEST_TEST_BENCH_LOADING_MAGIC
};

static int32_t __attribute__ ((section (".sram.reserved"))) rf_calib_kp1_test_signal_B_int[CALTEST_MATRIX_SIZE+1] = {
1106985432,
1044245999,
-462881426,
667772454,
-1412242422,
884961210,
-2010762614,
-958108484,
-1949179035,
-1730305824,
1389240794,
836782564,
-785551752,
1933688976,
-1999538859,
-263090972,
-508702553,
1140385922,
1267873921,
-1344871923,
-43961585,
-233705488,
628409593,
899215101,
1093870970,
CALTEST_TEST_BENCH_LOADING_MAGIC
};

static int32_t __attribute__ ((section (".sram.reserved"))) rf_calib_kp1_result_output_int[CALTEST_MATRIX_SIZE+1] = {
    -186234901,
     301758380,
    -395508448,
     262172202,
     273701258,
     922180687,
     654740371,
   -1138414389,
    -930304886,
   -1155124218,
    -317235782,
     392896048,
    -366149101,
     332926129,
     434065594,
    -466008112,
     533893604,
     326600217,
    -285675518,
     206662842,
    -143299471,
    -124286504,
     524233977,
     301602630,
     341464564,
     CALTEST_TEST_BENCH_LOADING_MAGIC
};

static int32_t __attribute__ ((section (".sram.reserved"))) rf_calib_kp1_test_integer_output[CALTEST_MATRIX_SIZE] = 
{
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_A,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
    PATTERN_B,
};
static int32_t *p_output_address = (int32_t*)CALTEST_READ_TRACE_ADDRESS;
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars      *
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
 * @brief           
 * @param [in]      
 * @param [in]      
 * @param [in]      
 * @return          none
 * -------------------------------------------------------------------------------------------------------------------*/
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
int main(int argc, char *argv[])
{
    if (!com_shared_mem_wait_for_ready ())
    {
        FW_PRINT (FW_WARNING, "RSM Not ready.");
    } 
    //Wait for the loading to SRAM complete
    volatile int32_t *p_matrix_a_end = &rf_calib_kp1_test_signal_A_int[CALTEST_MATRIX_SIZE];
    volatile int32_t *p_matrix_b_end = &rf_calib_kp1_test_signal_B_int[CALTEST_MATRIX_SIZE];
    volatile int32_t *p_matrix_out_end = &rf_calib_kp1_result_output_int[CALTEST_MATRIX_SIZE];
    *p_output_address = (intptr_t)(&rf_calib_kp1_test_integer_output[0]);

    while((*p_matrix_a_end != CALTEST_TEST_BENCH_LOADING_MAGIC) || (*p_matrix_b_end != CALTEST_TEST_BENCH_LOADING_MAGIC) || (*p_matrix_out_end != CALTEST_TEST_BENCH_LOADING_MAGIC ))
    {
       //Loop till we see the magic pattern in the SRAM
        ;
    }

    FW_PRINT(FW_INFO,"RSM initialized by the RTE");
    //Start the simulation
    rf_calib_heap_create();
    FW_PRINT(FW_INFO, "Starting simple Eigen test");
    //Allocate storage to read from the shared memory
    int32_t *dma_in = (int32_t *)rf_calib_calloc (CALTEST_MATRIX_SIZE, sizeof (int32_t));
    rf_calib_int_map_dy_1 caltest_dma_in_int (dma_in, CALTEST_MATRIX_SIZE);
    rf_calib_int_map_dy_1 caltest_dma_out_int (rf_calib_kp1_test_integer_output, CALTEST_MATRIX_SIZE);
    rf_calib_int_map_dy_1 caltest_matlab_output_int (rf_calib_kp1_result_output_int,CALTEST_MATRIX_SIZE);
    for(int i=0; i<CALTEST_MATRIX_SIZE;++i)
    {
        dma_in[i] = rf_calib_kp1_test_signal_A_int[i];
    }
    //Convert the fixed point input matrix A to float and assign it to a matrix
    rf_calib_float_matrix_dy_dy caltest_A (CALTEST_MATRIX_ROW_SIZE, CALTEST_MATRIX_COLUMN_SIZE);
    float input_factor = 1.0 / pow (2.0, CALTEST_INPUT_FRACTIONAL_BITS);
    caltest_A = (caltest_dma_in_int.template cast<float> () * input_factor).reshaped(CALTEST_MATRIX_ROW_SIZE,CALTEST_MATRIX_COLUMN_SIZE);
    for(int i=0; i<CALTEST_MATRIX_SIZE;++i)
    {
        dma_in[i] = rf_calib_kp1_test_signal_B_int[i];
    }
    //Convert the fixed point input matrix A to float and assign it to a matrix
    rf_calib_float_matrix_dy_dy caltest_B (CALTEST_MATRIX_ROW_SIZE, CALTEST_MATRIX_COLUMN_SIZE);
    caltest_B = (caltest_dma_in_int.template cast<float> () * input_factor).reshaped(CALTEST_MATRIX_ROW_SIZE,CALTEST_MATRIX_COLUMN_SIZE);
    //Compute the matrix output
    rf_calib_float_matrix_dy_dy caltest_C (CALTEST_MATRIX_ROW_SIZE, CALTEST_MATRIX_COLUMN_SIZE); 
    caltest_C.noalias() =  caltest_A * caltest_B;
    FW_PRINT(FW_INFO,"Completed the Matrix multiplication");
    //Compare the computed output with the expected

    //Convert the fixed point expected output to float and assign it to a matrix
    rf_calib_float_matrix_dy_dy caltest_matlab_output_float (CALTEST_MATRIX_ROW_SIZE, CALTEST_MATRIX_COLUMN_SIZE);
    float output_factor = 1.0 / pow (2.0, CALTEST_OUTPUT_FRACTIONAL_BITS);
    caltest_matlab_output_float = (caltest_matlab_output_int.template cast<float> () * output_factor).reshaped(CALTEST_MATRIX_ROW_SIZE,CALTEST_MATRIX_COLUMN_SIZE);
    if(caltest_C.isApprox(caltest_matlab_output_float,CALTEST_TOLERANCE))
    {
        FW_PRINT(FW_INFO,"Test Pass");
        //convert caltest_C to fixed point equivalent
        float output_factor = pow (2.0, CALTEST_OUTPUT_FRACTIONAL_BITS);
        //Convert the float output to fixed point and write to the shared memory
        caltest_dma_out_int = (caltest_C * output_factor) .reshaped(CALTEST_MATRIX_SIZE,1).template cast<int32_t> ();
        //Print the result in the shared memory
        for(int i=0; i<CALTEST_MATRIX_COLUMN_SIZE;++i)
        {
            for(int j=0;j<CALTEST_MATRIX_ROW_SIZE;++j)
            {
                FW_PRINT(FW_INFO,"C(%d,%d) = %d",i,j,rf_calib_kp1_test_integer_output[i*CALTEST_MATRIX_COLUMN_SIZE+j]);    
            }
            
        }
    } 
    else
    {
        FW_PRINT(FW_INFO,"Test fails");
    }
    rf_calib_free(dma_in);
    return(0);
}
