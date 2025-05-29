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

#include "tx_boot_test.h"
#include "com_event.h"
#include "rcs_gpreg.h"
#include "com_shared_memory.h"

volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));

uint32_t const SIZE = 16;
uint32_t write_rsm[SIZE] __attribute__((section(".sram.ax.rw")));
volatile uint32_t write_dram[SIZE]  __attribute__((section(".dram0.data")));

uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/



int main(int argc, char **argv)
{
    xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();
    boot_test();
    // Update RSM flag for handshake with host code
    rsm_ax_shared_flag=0x1234;

    return (0);
}

uint32_t boot_test()
{
    unsigned int dataCnt;
    for (dataCnt = 0;dataCnt < 16; dataCnt++)
    {
        write_dram[dataCnt] = 0x11111111;
        write_rsm[dataCnt]  = 0x22222222;
    }

    return 0;
}



