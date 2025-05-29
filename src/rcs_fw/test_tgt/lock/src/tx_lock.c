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
#include "com_event.h"
#include "com_lock.h"
#include "rcs_gpreg.h"

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
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
int main(int argc, char **argv)
{
	int32_t waitCnt = 0;
    rsm_tx_shared_flag = 0;
    rsm_com_shared_flag = 0;
    int32_t val = 0xaaaa0000;

	xthal_enable_interrupts();

    rcs_gpreg_core1_control_reg_t rx_start_reg = {.value = RCS_GPREG_CORE1_CONTROL_DEFAULT};
    rx_start_reg.CORE_RUNSTALL = 0;
    *RCS_GPREG_CORE1_CONTROL_REG = rx_start_reg;

    rcs_gpreg_core2_control_reg_t cal_start_reg = {.value = RCS_GPREG_CORE2_CONTROL_DEFAULT};
    cal_start_reg.CORE_RUNSTALL = 0;
    *RCS_GPREG_CORE2_CONTROL_REG = cal_start_reg;


    com_lock_init();

    // acquire lock
	com_lock_acquire(e_LOCK_TEST);
	// write locked region
	p_system_data->test = val;
	// keep the lock and inform rx/cal to try write to p_system_data->test
	rsm_tx_shared_flag = p_system_data->test;

	// wait for rx/cal to try locked region write
	// until tx releases lock, rx/cal cant get it, blocking call!
	// Check if rx/cal got lock and modified the  locked variable
	while(p_system_data->test == val)
	{
		write_rsm[0] = waitCnt++;
		if(waitCnt > 0x1000) // give some time for rx/cal core to try
		{
			// set pass flag in RSM
			rsm_com_shared_flag = 0xBA55C0C0;
			break;
		}

	}

	// release lock, rx or cal should get lock now
	com_lock_release(e_LOCK_TEST);
	write_rsm[3] = 0xBB;
	while (rsm_rx_shared_flag != 0xbbbb0000)
	{
		write_rsm[0] = waitCnt++;
	}

	// wait for trigger from rx to access locked region
	if (rsm_rx_shared_flag == 0xbbbb0000) //|| (rsm_cal_shared_flag == 0xcccc0000))
	{
		write_rsm[3] = 0xCC;
		// try acquiring lock and update lock var
		// acquire lock
		com_lock_acquire(e_LOCK_TEST);
		write_rsm[3] = 0xDD;
		// write locked region
		p_system_data->test = 0xaaaa0001;
		// keep the lock and inform rx/cal to try write to p_system_data->test
		rsm_tx_shared_flag = p_system_data->test;
		write_rsm[3] = 0xEE;

		// release lock
		com_lock_release(e_LOCK_TEST);
		write_rsm[3] = 0xFF;
		//break; // break once lock acquired and tx able to update lock var

	}
	//write_rsm[3] = 0x1111;

	return (0);
}
