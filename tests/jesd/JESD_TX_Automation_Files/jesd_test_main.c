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
 * @file    jesd_test_main.c
 * @brief   This file demonstrate the sample file structure to follow.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "jesd_test_common.h"
//#include "jesd_sample_test.h"

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

/**
 * @brief           main entry point for all jesd tests
 * @param [in]      argc number of argument passed
 * @param [in]      argv array(list) of argument passed
 * @param [out]     none ( you can omit if not available)
 * @return          0 on sunccess or error code otherwise
 */

int main(
    int argc,
    const char *argv[])
{
    int rv = 0, val = 0, dev_id = 0, flags = 0;
    int testcase;
    
    printf("INFO: Logger beginning\n");
    printf("Test: JESD Rx path 16G\n");
    printf("INFO: argc : %d\n", argc);
    
    testcase        = atoi(argv[0]);
    
    printf("INFO: argv[0] : %d testcase_id     = %d\n",testcase, testcase);
  
    // Configure JESD test
    configure_jesd(testcase);
    
    // Test pass/fail criteria
    if(0 == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    } else
    {
        printf("Test Result:------ FAIL -----!\n\n");
    }

    printf("HOST: End of the Test execution....!\n");

    return rv;

}
