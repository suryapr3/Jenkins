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

 * @file    host_utils.c

 * @brief   HOST utility functions for reading the data from test vector and comparision.

**
*********************************************************************************************/


#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <math.h>
#include "logger.h"

#define printf LOG_PRINT


// Read test vectors, Unsigned Int32 data type

int vector_read_hex_u32(
    FILE *fp,   // Vector Input file data type
    int *dPtr,  // Pointer to output array
    int num)    // Number of elements
{
    int i, fileEnd;
    int iVal;

    fileEnd = 0;

    for (i=0; i<num; i++)
    {
        fileEnd = fscanf(fp, "%x", &iVal);

        if (fileEnd != 1)
            return(-1);

        *dPtr = iVal;
        dPtr++;
    }
    return(i);
}

int vector_diff_u32(
    uint32_t *scalar1,  // point to an array of unsigned 32-bit values
    uint32_t *scalar2,  // point to an array of unsigned 32-bit values
    int error,  // error tolerance
    int num_elements,   // number of samples
    int debug   // debug flag
)
{

    int i, error_count;
    double max_error, dval;
    double total_error;
    long long v1, v2, diff;

    printf("# of output samples = %d\n",num_elements);

    max_error = 0.0;
    total_error = 0.0;
    error_count = 0;

    for ( i=0; i < num_elements; i++)
    {
        v1 = scalar1[i];
        v2 = scalar2[i];
        diff = v1^v2;

        dval = fabs((double)(v2 - v1));
        total_error += dval;
        if (dval > max_error)
            max_error = dval;

        if ( dval > error )
            error_count++;

        if (debug)
        {

          if ((int) dval != 0)
              //printf("ERROR:0x%08x 0x%08x %11d <----(%d)----\n",(int)v1, (int)v2, (int)diff, i);
              printf("ERROR:0x%x 0x%x  <----(%d)----\n",(int)v1, (int)v2, i);
          else
              printf("0x%x 0x%x %d\n",
                      (int)v1, (int)v2, (int)diff);
        }
    }
    if (num_elements)
        total_error /= (1*num_elements);
    if (error_count)
    {
    printf("Peak Error is %f Average Error is %f\n",
                max_error, total_error);
    }
    else
    {
        printf("HOST: Read data is matching with expected data\n");
    }

    return(error_count);
}


