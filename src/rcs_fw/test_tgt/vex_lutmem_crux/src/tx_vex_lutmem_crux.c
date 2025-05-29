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
#include "com_definitions.h"
#include "com_print.h"
#include "com_shared_memory.h"
#include "com_timing.h"
#include "string.h"
#include "com_event.h"
#include "nsip_hbi.h"
#include "crux_intf.h"

#define MAKE128CONST(hi,lo) (((( uint128_t)hi << 64) | lo))

#define U32_TO_U128(val_a, val_b, val_c, val_d) \
    (((uint128_t)val_a << 96) | ((uint128_t)val_b << 64) | ((uint128_t)val_c << 32) | ((uint128_t)val_d))
#define U64_TO_U128(val_a, val_b) (((uint128_t)val_a << 64) | (val_b))
#define U128LW64(val_a)           ((uint64_t)val_a)
#define U128UP64(val_a)           ((uint64_t) (val_a >> 64))

uint32_t const SIZE = 16;
volatile uint32_t rsm_ax_shared_flag __attribute__((section(".sram.ax.flag")));
volatile uint32_t rsm_tx_shared_flag __attribute__((section(".sram.tx.flag")));
volatile uint32_t rsm_rx_shared_flag __attribute__((section(".sram.rx.flag")));
volatile uint32_t rsm_cal_shared_flag __attribute__((section(".sram.cal.flag")));
volatile uint32_t rsm_com_shared_flag __attribute__((section(".sram.com.flag")));


volatile uint32_t write_rsm[SIZE] __attribute__((section(".sram.ax.rw")));
volatile uint32_t write_dram[SIZE]  __attribute__((section(".dram0.data")));


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
uint32_t dataCnt,errCnt = 0,count = 0,cnt = 0,value;
/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/

uint32_t crux_access_test();

int main(int argc, char **argv)
{
    xthal_enable_interrupts();
    com_shared_mem_wait_for_ready ();
    // clear all flags
    rsm_ax_shared_flag = 0;
    rsm_rx_shared_flag = 0;
    rsm_tx_shared_flag = 0;
    //rsm_cal_shared_flag = 0;
    rsm_com_shared_flag = 0;

    // run test
    crux_access_test();

    // update RSM flag to trigger host verification
    rsm_tx_shared_flag = 0xD0C2;

    // host code will trigger rx and cal execution via shared flags

    return (0);
}

uint32_t crux_access_test()
{

    uint64_t crux_wdata[] = {0x2222222222222222, 0x1111111111111111,
    0x4444444444444444, 0x3333333333333333,
    0x5555555555555555, 0x6666666666666666,
    0x7777777777777777, 0x8888888888888888};
    // write crux data registers
    crux_intf_wdata0_r_reg_t crux_wdata0_reg = {.value = 0x0};
    crux_wdata0_reg.DATA = U64_TO_U128(crux_wdata[1], crux_wdata[0]);
    *CRUX_INTF_WDATA0_R_REG = crux_wdata0_reg;
    //*((CRUX_INTF_CRUX_WDATA0_R_ADR)) = 0x5566778899aabbcc;
    //*((CRUX_INTF_CRUX_WDATA0_R_ADR) + (0xC)) = (uint64_t)0x55667788;


    crux_intf_wdata1_r_reg_t crux_wdata1_reg = {.value = 0};
    crux_wdata1_reg.DATA = U64_TO_U128(crux_wdata[3], crux_wdata[2]);
    *CRUX_INTF_WDATA1_R_REG = crux_wdata1_reg;

    crux_intf_wdata2_r_reg_t crux_wdata2_reg = {.value = 0};
    crux_wdata2_reg.DATA = U64_TO_U128(crux_wdata[5], crux_wdata[4]);
    *CRUX_INTF_WDATA2_R_REG = crux_wdata2_reg;

    crux_intf_wdata3_r_reg_t crux_wdata3_reg = {.value = 0};
    crux_wdata3_reg.DATA = U64_TO_U128(crux_wdata[7], crux_wdata[6]);
    *CRUX_INTF_WDATA3_R_REG = crux_wdata3_reg;

    // routing data
    crux_intf_wrouting_data_r_reg_t crux_wrouting_reg = {.value = 0x0};
    crux_wrouting_reg.SOP = 0x1;
    crux_wrouting_reg.EOP = 0x1;
    crux_wrouting_reg.BYPASS = 0x1;

    crux_wrouting_reg.HOST_ID = (uint16_t)write_rsm[0]; // Send to vex id programmed in write_rsm[0]
    
    // Configure RCS crux -> H2B_CREDIT_READY_CS - TBD from host
    nsip_hbi_h2b_credit_ready_cs_reg_t h2b_credit_ready_reg = {.value = NSIP_HBI_H2B_CREDIT_READY_CS_DEFAULT};
    h2b_credit_ready_reg.MAX_CREDITS = 0x3;
    *(NSIP_HBI_H2B_CREDIT_READY_CS_REG(RCS_CRUX_NSIP_HBI_BASE)) = h2b_credit_ready_reg;
    
    
    for(int i=0 ; i < 64 ; i++)
    {	
        crux_wrouting_reg.ADDRESS = 0x4000 + (i * 0x10);
        crux_wrouting_reg.FLIT_TYPE = 0x6; // 64 valid bytes in the streaming word

        *CRUX_INTF_WROUTING_DATA_R_REG = crux_wrouting_reg;
        *CRUX_INTF_WROUTING_DATA_R_REG = crux_wrouting_reg;

        // push the data
        crux_intf_tx_push_reg_t crux_tx_push = {.value = 0};
        crux_tx_push.PUSH = 0x1;
        *CRUX_INTF_TX_PUSH_REG = crux_tx_push;
    }
    return 0;
}

