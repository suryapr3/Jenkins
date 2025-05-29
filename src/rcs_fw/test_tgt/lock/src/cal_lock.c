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
 * @file    cal_lock.c
 * @brief   lock test file on CAL core
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

#if (CPU_CAL)
#else
#error "Not CAL CPU"
#endif

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "com_event.h"
#include "com_lock.h"

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
uint32_t const SIZE = 16;
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
volatile uint32_t write_dram[SIZE]  __attribute__((section(".dram0.data")));

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main(int argc, char **argv)
{
	int32_t val = 0xcccc0000;
	int32_t waitCnt = 0;
	rsm_cal_shared_flag = 0;

    xthal_enable_interrupts();

    write_rsm[5] = 0x11;

    // wait for handshake from tx core
    while((rsm_tx_shared_flag != 0xaaaa0000)) // || (rsm_tx_shared_flag != 0xaaaa0001))
	{
		write_rsm[2] = waitCnt++;
	}
    write_rsm[5] = 0x22;

	// acquire lock
	com_lock_acquire(e_LOCK_TEST);
	write_rsm[5] = 0x33;
	// write the locked region
	p_system_data->test = val;
	write_rsm[5] = 0x44;
	// update the written val to the flag
	rsm_cal_shared_flag = p_system_data->test;
	// release lock
	com_lock_release(e_LOCK_TEST);
	write_rsm[5] = 0x55;


    return (0);
}
