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
#include "com_assert.h"
#include "com_print.h"
#include "com_rx_ana.h"
#include "ana_isr.h"
#include "ant_csr.h"
#include "cpu.h"
#include "com_heap.h"
#include "ana_common.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
// prid: ant0=0x3  ant1=0x203 ant2=0x403  ant3=0x603 (take bit 9 and 10)
#define PRID_2_ANA_ID(n) ((n & 0x600) >> 9)

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
uint32_t csr_base;
uint32_t ant_cpu_base;
uint8_t ana_Heap[ANA_HEAP_SIZE] __attribute__ ((section (".dram0_calib_heap")));

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main (int argc, char **argv)
{
    com_heap_create (ana_Heap, ANA_HEAP_SIZE);
    uint32_t const ana_id = PRID_2_ANA_ID (xthal_get_prid ());
    FW_PRINT (FW_INFO, "ANA main %d", ana_id);
    RT_ASSERT (ana_id < 4);

    switch (ana_id)
    {
        case 0:
            csr_base = ANT0_CSR_BASE;
            ant_cpu_base = ANT0_CPU_BASE;
            break;
        case 1:
            csr_base = ANT1_CSR_BASE;
            ant_cpu_base = ANT1_CPU_BASE;
            break;
        case 2:
            csr_base = ANT2_CSR_BASE;
            ant_cpu_base = ANT2_CPU_BASE;
            break;
        case 3:
            csr_base = ANT3_CSR_BASE;
            ant_cpu_base = ANT3_CPU_BASE;
            break;
        default: FW_PRINT (FW_INFO, " This CPU is ID is wrong"); break;
    }

    ana_isr_initialize (ana_id);

    // Initialize mailbox interrupt
    cpu_ant_int_high_en_reg_t int_high_en_reg = {.value = CPU_ANT_INT_HIGH_EN_DEFAULT};
    int_high_en_reg.CPU2RCS_MAILBOX = 1;
    *CPU_ANT_INT_HIGH_EN_REG (ant_cpu_base) = int_high_en_reg;

    // Send boot message
    cpu_cpu2rcs_mailbox_reg_t cpu2rcs_mb_reg = {.value = CPU_CPU2RCS_MAILBOX_DEFAULT};
    // cpu2rcs_mb_reg.MAIL_MESSAGE = 0x80000000;
    cpu2rcs_mb_reg.MAIL_MESSAGE = (0x80000000 | ana_id);
    *CPU_CPU2RCS_MAILBOX_REG (ant_cpu_base) = cpu2rcs_mb_reg;

    while (1)
    {
        INTRINSIC_WAIT_FOR_IRQ;
        FW_PRINT (FW_INFO, " ANA: Start calibration");
        // Sriram do calibration here
        // send back status

        // while (((ANT_CSR_SCRATCH_REG (csr_base)->value) >> 31) == 0) {}
        // cal done, inform RCS, trigger interrupt
        // int_high_en_reg.CPU2RCS_MAILBOX = 1;
        // *CPU_ANT_INT_HIGH_EN_REG (ant_cpu_base) = int_high_en_reg;

        // cpu2rcs_mb_reg.MAIL_MESSAGE = 1;
        // *CPU_CPU2RCS_MAILBOX_REG (ant_cpu_base) = cpu2rcs_mb_reg;
        INTRINSIC_BARRIER;
    }
    return (0);
}
