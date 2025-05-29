
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



#include "../inc/vex_lutmem_crux.h"
#include "com_event.h"
#include "rcs_gpreg.h"
#include "crux_intf.h"
#include "nsip_hbi.h"


#define U32_TO_U128(val_a, val_b, val_c, val_d) \
    (((uint128_t)val_a << 96) | ((uint128_t)val_b << 64) | ((uint128_t)val_c << 32) | ((uint128_t)val_d))
#define U64_TO_U128(val_a, val_b) (((uint128_t)val_a << 64) | (val_b))
#define U128LW64(val_a)           ((uint64_t)val_a)
#define U128UP64(val_a)           ((uint64_t) (val_a >> 64))


volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));

volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.tx.rw")));
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
int main(int argc, char **argv)
{
	int waitCnt = 0;
	xthal_enable_interrupts();

	// wait for handshake from host
	do
	{
		waitCnt++;
		if(waitCnt > 0xFFFFFFF)
		{
			rsm_com_shared_flag = 0xDEADC001; // core1 didnt finish, host to check and print error
			return 0;
		}
	} while (rsm_com_shared_flag != 0xC2C2);

	cal2vex_transfer_test();
	// update RSM flag for handshake with host code
	rsm_rx_shared_flag = 0xD0C2;

	// cal core will be triggered by host
	return (0);
}

uint32_t cal2vex_transfer_test()
{

	uint64_t crux_wdata[] = {	0x2222222211111111, 0x3333333322222222,
								0x4444444433333333, 0x5555555544444444,
								0x6666666655555555, 0x7777777766666666,
								0x8888888877777777, 0x9999999988888888};
	// write crux data
	crux_intf_crux_wdata0_r_reg_t crux_wdata0_reg = {.value = 0x0};
	crux_wdata0_reg.DATA = U64_TO_U128(crux_wdata[1], crux_wdata[0]);
	*CRUX_INTF_CRUX_WDATA0_R_REG = crux_wdata0_reg;
	//*((CRUX_INTF_CRUX_WDATA0_R_ADR)) = 0x5566778899aabbcc;
	//*((CRUX_INTF_CRUX_WDATA0_R_ADR) + (0xC)) = (uint64_t)0x55667788;


	crux_intf_crux_wdata1_r_reg_t crux_wdata1_reg = {.value = 0};
	crux_wdata1_reg.DATA = U64_TO_U128(crux_wdata[3], crux_wdata[2]);
	*CRUX_INTF_CRUX_WDATA1_R_REG = crux_wdata1_reg;

	crux_intf_crux_wdata2_r_reg_t crux_wdata2_reg = {.value = 0};
	crux_wdata2_reg.DATA = U64_TO_U128(crux_wdata[5], crux_wdata[4]);
	*CRUX_INTF_CRUX_WDATA2_R_REG = crux_wdata2_reg;

	crux_intf_crux_wdata3_r_reg_t crux_wdata3_reg = {.value = 0};
		crux_wdata3_reg.DATA = U64_TO_U128(crux_wdata[7], crux_wdata[6]);
	*CRUX_INTF_CRUX_WDATA3_R_REG = crux_wdata3_reg;

	// routing data
	crux_intf_crux_wrouting_data_r_reg_t crux_wrouting_reg = {.value = 0x0};
#if 1 // enable once 18A html is matching for the register:INTF_ID is removed
	crux_wrouting_reg.SOP = 0x1;
	crux_wrouting_reg.EOP = 0x1;
	crux_wrouting_reg.BYPASS = 0x1;

	crux_wrouting_reg.HOST_ID = (uint16_t)write_rsm[0]; // Send to vex id programmed in write_rsm[0]
	//crux_wrouting_reg.HOST_ID = 0;
	crux_wrouting_reg.ADDRESS = 0x0; // VMEM address in VEX0
	crux_wrouting_reg.FLIT_TYPE = 0x6; // 64 valid bytes in the streaming word
	*CRUX_INTF_CRUX_WROUTING_DATA_R_REG = crux_wrouting_reg;
#endif
	//crux_wrouting_reg.value = 0x40000C6; // comment out once html matches
	*CRUX_INTF_CRUX_WROUTING_DATA_R_REG = crux_wrouting_reg;

	// Configure RCS crux -> H2B_CREDIT_READY_CS - TBD from host
	nsip_hbi_h2b_credit_ready_cs_reg_t h2b_credit_ready_reg = {.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT};
	h2b_credit_ready_reg.MAX_CREDITS = 0x3;
	*(NSIP_HBI_H2B_CREDIT_READY_CS_REG(RCS_CRUX_NSIP_HBI_BASE)) = h2b_credit_ready_reg;
	// push the data
	crux_intf_crux_tx_push_reg_t crux_tx_push = {.value = 0};
	crux_tx_push.PUSH = 0x1;
	*CRUX_INTF_CRUX_TX_PUSH_REG = crux_tx_push;


	return 0;
}










