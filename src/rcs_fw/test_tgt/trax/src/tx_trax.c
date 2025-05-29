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
 * @file    tx_lock.c
 * @brief   lock test file on TX core
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#if (CPU_TX)
#else
#error "Not TX CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_print.h"
#include "com_trax.h"
#include "com_shared_memory.h"

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
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main(int argc, char **argv)
{
    com_trax_init ();
    com_trax_start ();
    if (!com_shared_mem_wait_for_ready ()) FW_PRINT (FW_WARN, "RSM Not ready.");
    com_shared_mem_set_cpu_status (E_CPUID_TX0, E_CPU_STATUS_MAIN);

    int num = 10;
    int denom = 0;
    int quot = num/denom;

    FW_PRINT( FW_DEBUG, "Divide by 0 error: %d ", quot );

    com_trax_stop ();
    com_trax_store_trace ();

    while (1) { INTRINSIC_WAIT_FOR_IRQ; }
    return (0);
}
