/**********************************************************************************************
* INTEL CONFIDENTIAL
* Copyright (C) 2022 Intel Corporation
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
*********************************************************************************************/
/**************************************************************************************
 * @file  apb2tap.c
****************************************************************************************/

#include "srp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_functions.h"
#include "com_definitions.h"
#include "all_comps.h"
#include "init.h"
#include "cli.h"
#include "logger.h"
#include "common_macro.h"
#include "srp_block_ids.h"
#include "time.h"


#define print(...) LOG_PRINT(__VA_ARGS__); printf(__VA_ARGS__)
#define ENABLE_TDO_STORAGE 0x10
#define MTC_RESET 4

typedef enum
{
    CLTAP_ACCESS_GRANTED = 0,
    CLTAP_REQ_ACCESS = 2,
    CLTAP_REQ_ACCESS_DONE = 4,
    APB2TAP_REQ_GRANTED = 8,
    APB2TAP_REQ_ACCESS = 0x10,
    APB2TAP_REQ_ACCESS_DONE = 0x20,
    TAPNW_DISABLE = 0x40,
    SYSCON_MBOX_TAP_SEL = 0x80
}mtc_status_t;

typedef enum
{
    request_en = 0,
    request_done = 1
}apb2tap_req_t;

uint32_t concatenate_hex(int count, ...) {
    va_list args;
    va_start(args, count);

    uint32_t result = 0;
    int total_bits = 0;  // Track total bit width

    for (int i = 0; i < count; i++) {  // Process left to right
        uint32_t value = va_arg(args, uint32_t);  // Read value
        int bit_start = va_arg(args, int);        // Read start bit
        int bit_end = va_arg(args, int);          // Read end bit

        // Calculate bit length (inclusive range)
        int bit_length = bit_start - bit_end + 1;

        // Extract bits: Shift right to align LSB, then mask the required bits
        uint32_t extracted_bits = (value >> bit_end) & ((1U << bit_length) - 1);

        // Shift previous result left by 'bit_length' to make space for new bits
        result = (result << bit_length) | extracted_bits;

        // Update total bit count
        total_bits += bit_length;
    }

    va_end(args);
    return result;
}

// To get status of fsm
uint32_t apb2tap_fsm_status()
{
    mtc_status_t status;
    uint32_t mtc_status;
    mtc_status = read_reg_18a(AXIS_MTC_TOP_MEM_APB2TAP_MON_ADDR_ADR,  "MTC_MON_REG_STATUS_REG");
    print("MTC Status: 0x%x\n", mtc_status);

    if (mtc_status & CLTAP_ACCESS_GRANTED)
    {
        print("CLTAP ACCESS IS GRANTED\n");
    }
    else if (mtc_status & APB2TAP_REQ_GRANTED)
    {
        print("APB2TAP REQ IS GRANTED\n");
    }
    else if (mtc_status & TAPNW_DISABLE)
    {
        print("TAPNW IS DISABLE\n");
    }

    return 0;
}

// To request for apb2tap request or done action of apb2tap
uint32_t apb2tap_req_access(apb2tap_req_t req_access)
{
    if(req_access == request_en)
    {
        write_reg_18a(AXIS_MTC_TOP_MEM_APB2TAP_CFG0_ADDR_ADR, 0x1, 0xffffffff, "APB2TAP REQ ACCESS CFG");
    }
    else if(req_access == request_done)
    {
        write_reg_18a(AXIS_MTC_TOP_MEM_APB2TAP_CFG0_ADDR_ADR, 0x2, 0xffffffff, "APB2TAP REQ ACESS DONE");
    }
    apb2tap_fsm_status();
    return 0;
}

// All TAP POINTS has 8 bit long IR and coresight has 4 bit long IR
// Refer MTC Design Specification to get to know about Task fromats and Instruction code.

/* Task Format 1
--------------------------------------------------------------------------------
| Bit[31] | Bit[30] | Bit[29]*  | Bit[28]*    | Bits[27:4] | Bits[3:0]          |
|--------|--------|-------------|-------------|------------|--------------------|
| 1      | 0      | TCK Action  | 0           | Not Used   | Instruction Code   |
--------------------------------------------------------------------------------
*/

/* Task Format 3
---------------------------------------------------------
| Bit[31] | Bit[30] | Bit[29:4]    | Bits[3:0]          |
|--------|--------|-------------   |-------------       |
| 1      | 0      | No. TCK cycle  | Instruction Code   |
---------------------------------------------------------
*/

/*
TASK FORMAT 4:
--------------------------------------------------------------------------------------------------------
|Bit [31]|  Bit [30] | Bit[29]*    | Bit[28]*   | Bits[27:16]    | Bits[15:4]           |  Bits[3:0]   |
--------------------------------------------------------------------------------------------------------
|1       |    1      |  TCK Action | End-State  |No.of shift data | No.of shiftinstruction |Instr. Code|
--------------------------------------------------------------------------------------------------------
|0       |    1      |  TDI test Data (Bit 30 =1, means more data follows).                            |
--------------------------------------------------------------------------------------------------------
|0       |    1      |  TDI Data                                                                       |
--------------------------------------------------------------------------------------------------------
|0       |    0      |  Last TDI Data (Bit 30 = 0).                                                    |
--------------------------------------------------------------------------------------------------------
*/
/*
Control Bit    Value    Description
[29]           0        Allow TCK clock to run in end states (Test-Logic-Reset, Run-Test/Idle, Pause-DR, or Pause-IR states).
               1        Stop TCK Clock in end states (Test-Logic-Reset, Run-Test/Idle, Pause-DR, or Pause-IR states).
[28]           0        Go to Run-Test/Idle State - Pause only if TCK[29] clock stopped.
               1        Start Next Command from the Select-DR-Scan State (Clock cannot be stopped, Control Bit [29] value ignored).
*/
// Most of the IR and DR will be written in Task Format 4, if changed then Task format will be mentioned
// In emulation what is TAP Chain?

#if 1
// Below consider 12 TAP nodes to APB2TAP, tdo capture gives 0x800
uint32_t dfx_tap_ownership(int case_seq)
{
    uint32_t tdo_capture, eot_status, execute_reg, Numberof_tck_cycle, cfg_config_ctl, rate_sel, start_stopn, mtc_config0;
    uint32_t Instruction_code, Instruction, Numberof_shift_instruction_bits, Numberof_shift_data_bits, Bit_31_30;
    uint32_t task_format_4_data, task_format_3_data, task_format_1_data, host_mux_config;
    uint32_t BYPASS_P1TDI = 0x3;
    uint32_t BYPASS_P1TDO = 0x3;
    uint32_t BYPASS_IR_IPF1 = 0x3;
    uint32_t BYPASS_IR_IPF2 = 0x3;
    uint32_t BYPASS_IR_IPF3 = 0x3;
    uint32_t BYPASS_IR_IPF4 = 0x3;
    uint32_t BYPASS_IR_IPF5 = 0x3;
    uint32_t BYPASS_IR_IPF6 = 0x3;
    uint32_t BYPASS_IR_FUNC = 0x3;
    uint32_t BYPASS_IR_REPEATER = 0x3;
    uint32_t BYPASS_IR_HOST_TAP = 0x3;
    uint32_t BYPASS_IR_DFT_FORWARD = 0x3;
    uint32_t BYPASS_IR_DRF_1_S_DTS = 0xff;
    uint32_t BYPASS_IR_DRF_1_N_DTS = 0xff;
    uint32_t BYPASS_IR_DRF_0_S_DTS = 0xff;
    uint32_t BYPASS_IR_DRF_0_N_DTS = 0xff;
    uint32_t BYPASS_IR_RCS_DTS = 0xff;
    uint32_t BYPASS_IR_SYSCON_DTS = 0xff;
    uint32_t BYPASS_IR_CORESIGHT = 0xf;
    uint32_t BYPASS_IR_FC = 0xff;
    uint32_t BYPASS_IR_MBOX = 0xff;
    uint32_t BYPASS_DR = 0;
    uint32_t TAP_OWNERSHIP_IR_DFX_AGG = 0xf0;
    uint32_t TAP_OWNERSHIP_DR_DFX_AGG;

    // request apb2tap access
    apb2tap_req_access(request_en);

    // enable TDO storage in shift dr
    write_reg_18a(AXIS_MTC_TOP_CFG1_ADDR_ADR, ENABLE_TDO_STORAGE, 0xffffffff, "MTC_TOP_CFG1_REG");

    // The IR and DR will be written in MTC_PROGRAM_RAM register array in sequence of execution

    // Write IR to get ownership of dfx, and rest TAP points in bypass mode,
    // Task format 4 will be used to write IR and DR len
    /* IR TAP Ownership
     * Write Instruction to get Dfx ownership: 0xF0, rest Tap points in Bypass*/
    /* TAP Chain (12 nodes) : TDI --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight -->
     *                        RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> TDO
     * IR Len - 2 (TDI) + 4 x 8 + 4 (Coresight) + 5 x 8 + 2 (TDO) => 80 => 0x50

     */
    switch(case_seq)
    {
        case 1:
            print("Configured TAP chain 1: TDI --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                   RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS\n");
        /* TAP Chain (12 nodes) : TDI --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight -->
             *                        RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS
             * IR Len - 2 (TDI) + 4 x 8 + 4 (Coresight) + 5 x 8 + 2 (TDO) => 80 => 0x50

             */
            Instruction_code = 3;
            //Numberof_shift_instruction_bits = 0x50;
            Numberof_shift_instruction_bits = 0x4e;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM0_REG");

            // Bit 30 => 1, rest 1 [29:0]
            //Instruction = (BYPASS_IR_DRF_1_N_DTS & 0xf) << 26  | BYPASS_IR_DRF_0_N_DTS << 18 | BYPASS_IR_DRF_0_S_DTS << 10  \
                          | BYPASS_IR_DRF_1_S_DTS << 2 | BYPASS_P1TDO;
            Instruction = (BYPASS_IR_DRF_1_N_DTS & 0x3f) << 24  | BYPASS_IR_DRF_0_N_DTS << 16 | BYPASS_IR_DRF_0_S_DTS << 8  \
                          | BYPASS_IR_DRF_1_S_DTS;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // Bit 30 => 1, rest 1 [29:0]
            //Instruction = (BYPASS_IR_FC & 0x3f) << 24  | BYPASS_IR_SYSCON_DTS << 16 | BYPASS_IR_CORESIGHT << 12  \
                          | BYPASS_IR_RCS_DTS << 4 | BYPASS_IR_DRF_1_N_DTS & 0xf;
            Instruction = BYPASS_IR_FC  << 22  | BYPASS_IR_SYSCON_DTS << 14 | BYPASS_IR_CORESIGHT << 10  \
                          | BYPASS_IR_RCS_DTS << 2 | (BYPASS_IR_DRF_1_N_DTS & 0xc0) >> 6;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            // [1:0]: all 1, [9:2]: all 1, [17:10]: 0xf0, [19:18]:all 1
            //Instruction = BYPASS_P1TDI  << 18  | TAP_OWNERSHIP_IR_DFX_AGG << 10  \
                          | BYPASS_IR_MBOX << 2 | BYPASS_IR_FC & 0x3;
            Instruction = BYPASS_P1TDI  << 16  | TAP_OWNERSHIP_IR_DFX_AGG << 8 | BYPASS_IR_MBOX;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            /* DR TAP Ownership
             * DR Len - 3 x Dfx + 11 ( Rest in Bypass) => 14 => 0xe
             * RTDR = 3'b010 ( 1 - TO write to request tap ownership){wait, request, grant}
             * so DR = 0_1000_0000_0000 => 0x800 (0 for rest 11 tap points as bypass)
             */
            Instruction_code = 4;
            //Numberof_shift_data_bits = 0xe;
            Numberof_shift_data_bits = 0xd;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            //task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 9 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_3_data, 0xffffffff, "MEM6_REG");

            // Send DR (MTC task format 4) to read out TAP_OWNERSHIP_DR_DFX_AGG and check grant status
            Instruction_code = 4;
            //Numberof_shift_data_bits = 0xe;
            Numberof_shift_data_bits = 0xd;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2;
            Bit_31_30 = 0;
            //task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 9 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM7_REG");

            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            //tdo_capture  = tdo_capture >> 26;
            tdo_capture  = tdo_capture >> 24;
            break;

        case 2:
            print("Configured TAP chain: TDI --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                   RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> TDO\n");
           /* TAP Chain (12 nodes) : TDI --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight -->
             *                        RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> TDO
             * IR Len - 2 (TDI) + 4 x 8 + 4 (Coresight) + 5 x 8 + 2 (TDO) => 80 => 0x50

             */

            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x50;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM0_REG");

            // Bit 30 => 1, rest 1 [29:0]
            Instruction = (BYPASS_IR_DRF_1_N_DTS & 0xf) << 26  | BYPASS_IR_DRF_0_N_DTS << 18 | BYPASS_IR_DRF_0_S_DTS << 10  \
                          | BYPASS_IR_DRF_1_S_DTS << 2 | BYPASS_P1TDO;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // Bit 30 => 1, rest 1 [29:0]
            Instruction = (BYPASS_IR_FC & 0x3f) << 24  | BYPASS_IR_SYSCON_DTS << 16 | BYPASS_IR_CORESIGHT << 12  \
                          | BYPASS_IR_RCS_DTS << 4 | BYPASS_IR_DRF_1_N_DTS & 0xf;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            // [1:0]: all 1, [9:2]: all 1, [17:10]: 0xf0, [19:18]:all 1
            Instruction = BYPASS_P1TDI  << 18  | TAP_OWNERSHIP_IR_DFX_AGG << 10  \
                          | BYPASS_IR_MBOX << 2 | BYPASS_IR_FC & 0x3;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            /* DR TAP Ownership
             * DR Len - 3 x Dfx + 11 ( Rest in Bypass) => 14 => 0xe
             * RTDR = 3'b010 ( 1 - TO write to request tap ownership){wait, request, grant}
             * so DR = 0_1000_0000_0000 => 0x800 (0 for rest 11 tap points as bypass)
             */
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xe;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_3_data, 0xffffffff, "MEM6_REG");

            // Send DR (MTC task format 4) to read out TAP_OWNERSHIP_DR_DFX_AGG and check grant status
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xe;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM7_REG");

            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 26;

            break;

        case 3:
            print("Configured TAP Chain: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight \
                    --> IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6\n");
            /* TAP Chain (12 nodes) :Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6
             * IR Len - 2 (Func_forward) + 4 x 8 + 4 (Coresight) + 6 x 2 => 50 => 0x32

             */
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x32;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM0_REG");

            // Bit 30 => 1, rest 1 [29:0]
            Instruction = (BYPASS_IR_FC & 0x3f) << 23 | BYPASS_IR_SYSCON_DTS << 16 | BYPASS_IR_CORESIGHT << 12 | BYPASS_IR_IPF1 << 10 | BYPASS_IR_IPF2 << 8 \
                          | BYPASS_IR_IPF3 << 6 | BYPASS_IR_IPF4 << 4 | BYPASS_IR_IPF5 << 2 | BYPASS_IR_IPF6;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // [1:0]: all 1, [9:2]: all 1, [17:10]: 0xf0, [19:18]:all 1
            Instruction = BYPASS_IR_FUNC << 18 | TAP_OWNERSHIP_IR_DFX_AGG << 10  \
                          | BYPASS_IR_MBOX << 2 | (BYPASS_IR_FC & 0xc0) >> 6;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            /* DR TAP Ownership
             * DR Len - 3 x Dfx + 11 ( Rest in Bypass) => 14 => 0xe
             * RTDR = 3'b010 ( 1 - TO write to request tap ownership){wait, request, grant}
             * so DR = 0_1000_0000_0000 => 0x800 (0 for rest 11 tap points as bypass)
             */
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xe;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_3_data, 0xffffffff, "MEM6_REG");

            // Send DR (MTC task format 4) to read out TAP_OWNERSHIP_DR_DFX_AGG and check grant status
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xe;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // writing DR for TAP ownership
            // 10 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 10 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM7_REG");

            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 26;

            break;

        case 4:
            print("Configured TAP Chain 4: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6 --> DFT_FORWARD --> HOST_TAP\n");
            /*
             * Before configuring above chain, configure Network host tap to bring zone_repeater_tap out of chain &
             * to bring dfT_forward & IPF1-IPF6 in chain
                To achieve this, TAP chain will be: ZONE1_REPEATER --> HOST_TAP
                IR LEN: 2 + 2 => 4 or 6
                DR_LEN : 7 (attached to Network Host tap each in Bypass) + 3 ( 3 bits to configure MUX of network host tap) \
                         + 1 (ZONE1_REPEATER in Bypass) => 11 or 13
                DR =>  000_0000_0110=> 0x6 ( 1 - 2nd bit of mux, 1 - 1st bit of MUX, 0 - 0th bit of MUX, and rest TAPS in BYPASS)
                Now bring the ipf1 to ipf6 in chain

                */
            //  Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 4;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM0_REG");

            // writing IR in Task format 4
            Instruction = BYPASS_IR_REPEATER << 2 | 0;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // Writing DR Len in Task format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xb;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            // writing DR in Task format 4
            //host_mux_config = 6;
            host_mux_config = 3;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | host_mux_config;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            // Now as DFT_FORWARD is in chain now try DFx Tap ownership with full tap chain
            /* TAP Chain 4: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6 --> DFT_FORWARD --> HOST_TAP
               IR LEN => 2 (FUNC_FORWARD) + 4 x 8 + 4 (Coresight) + 6 x 2 + 2 + 2 => 54 => 0x36 or => 58 => 0x3a
               DR LEN => 3 (DFx) + 13 ( Rest in Bypass) => 16 => 0x10 or 18 => 0x12
               DR => 0100_0000_0000_0000 => 0x2000 or 0x4000
            */
            // Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x36;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = (BYPASS_IR_FC & 3) << 28 | BYPASS_IR_SYSCON_DTS << 20 | BYPASS_IR_CORESIGHT << 16 | BYPASS_IR_IPF1 << 14 | BYPASS_IR_IPF2 << 12 \
                          | BYPASS_IR_IPF3 << 10 | BYPASS_IR_IPF4 << 8 | BYPASS_IR_IPF5 << 6 | BYPASS_IR_IPF6 << 4 | BYPASS_IR_HOST_TAP << 2 | BYPASS_IR_DFT_FORWARD;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Bit 30 => 0, [23:22] => 3, [21:14] => 0xf0, [13:6] => all 1, [5:0] => all 1
            Instruction = BYPASS_IR_FUNC  << 22 | TAP_OWNERSHIP_IR_DFX_AGG << 14 | BYPASS_IR_MBOX << 6| (BYPASS_IR_FC & 0xfc) >> 2;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_4_data, 0xffffffff, "MEM6_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0x10;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM7_REG");

            // writing DR for TAP ownership
            // 12 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 12 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM8_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_3_data, 0xffffffff, "MEM9_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0x10;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR10_ADR, task_format_4_data, 0xffffffff, "MEM10_REG");

            // writing DR for TAP ownership
            // 12 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 12 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR11_ADR, task_format_4_data, 0xffffffff, "MEM11_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR12_ADR, task_format_1_data, 0xffffffff, "MEM12_REG");

            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 31;
            break;

        case 5:
            print("Configured TAP Chain 5: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> DFT_FORWARD --> HOST_TAP\n");

            /* TAP Chain 4: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> DFT_FORWARD --> HOST_TAP
               IR LEN => 2 (FUNC_FORWARD) + 4 x 8 + 4 (Coresight) + 5 x 8 + 2 + 2 => 82 => 0x52
               DR LEN => 3 (DFx{wait, request, grant}) + 12 ( Rest in Bypass) => 15 => 0xf
               DR => 0001_0000_0000_0000 => 0x1000
            */
            // Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x52;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = (BYPASS_IR_DRF_0_N_DTS & 3) << 28 | BYPASS_IR_DRF_0_S_DTS << 20 | BYPASS_IR_DRF_1_N_DTS << 12 | BYPASS_IR_DRF_1_S_DTS << 4 \
                          | BYPASS_IR_HOST_TAP << 2 | BYPASS_IR_DFT_FORWARD;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Bit 30 => 0, [23:22] => 3, [21:14] => 0xf0, [13:6] => all 1, [5:0] => all 1
            Instruction = (BYPASS_IR_SYSCON_DTS & 0xf) << 26 | BYPASS_IR_CORESIGHT << 22 | BYPASS_IR_MBOX << 14 | BYPASS_IR_RCS_DTS << 6 | (BYPASS_IR_DRF_0_N_DTS & 0xfc) >> 2;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM6_REG");

            // [1:0]: all 1, [9:2]: all 1, [17:10]: 0xf0, [19:18]:all 1
            Instruction = BYPASS_IR_FUNC  << 28  | TAP_OWNERSHIP_IR_DFX_AGG << 20  \
                          | BYPASS_IR_MBOX << 12 | BYPASS_IR_FC << 4 | (BYPASS_IR_SYSCON_DTS & 0xf);
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xf;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM7_REG");

            // writing DR for TAP ownership
            // 11 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 11 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM8_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_3_data, 0xffffffff, "MEM9_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xf;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM10_REG");
#if 1
            // writing DR for TAP ownership
            // 11 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 0; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 11 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM11_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM12_REG");
#endif
            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 30;
            break;

        case 6:
            print("Configured TAP Chain 6: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> DFT_FORWARD\n");

            /* TAP Chain 4: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> DFT_FORWARD
               IR LEN => 2 (FUNC_FORWARD) + 4 x 8 + 4 (Coresight) + 2 => 40 => 0x28
               DR LEN => 3 (DFx{wait, request, grant}) + 6 ( Rest in Bypass) => 9 => 9
               DR => 0_0100_0000 => 0x40
            */
            // Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x26;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM0_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = BYPASS_IR_MBOX << 20 | BYPASS_IR_FC << 12 | BYPASS_IR_SYSCON_DTS << 4 | BYPASS_IR_CORESIGHT;
            //Instruction = BYPASS_IR_MBOX << 22 | BYPASS_IR_FC << 14 | BYPASS_IR_SYSCON_DTS << 6 | BYPASS_IR_CORESIGHT << 2 \
                          | BYPASS_IR_DFT_FORWARD;
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // [9:8]: all 1, [7:0]: 0xf0
            Instruction = BYPASS_IR_FUNC  << 8  | TAP_OWNERSHIP_IR_DFX_AGG;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 9;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            // writing DR for TAP ownership
            // 5 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 5 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_3_data, 0xffffffff, "MEM5_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 9;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_4_data, 0xffffffff, "MEM6_REG");
#if 1
            // Read for TAP ownership
            // 5 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 0; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 5 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM7_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM8_REG");
#endif
            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = start_stopn << 12 | rate_sel << 4 | cfg_config_ctl;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 9 bits. So that's a total of 18 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 16;
            break;

        case 7:
            print("Configured TAP Chain : Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                  IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6  --> RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> \
                  DRF_1_S_DTS --> DFT_FORWARD \n");

            /* TAP Chain 4: Func_forward --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    RCS_DTS --> DRF_0_N_DTS --> DRF_0_S_DTS --> DRF_1_N_DTS --> DRF_1_S_DTS --> DFT_FORWARD --> HOST_TAP
               IR LEN => 2 (FUNC_FORWARD) + 4 x 8 + 4 (Coresight) + 6 x 2 + 5 x 8 + 2  => 92 => 0x5c
               DR LEN => 3 (DFx{wait, request, grant}) + 17 ( Rest in Bypass) => 20 => 0x14
               DR => 0010_0000_0000_0000_0000 => 0x20000
            */
            // Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x5c;
            Bit_31_30 = 3;
            //task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            task_format_4_data = 0xc00005c3;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = 0x7fffffff; //(Bypass from dft_forward to DRF_0_S_DTS and 4 bits of DRF_0_N_DTS)
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = 0x7fffffff; //(Bypass from DRF_0_N_DTS 4 bits to Coresight and 2 bits of Syscon DTS)
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // [29:22]: 0xf0, rest in bypass
            Instruction = 0xfc3fffff;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0x14;
            Bit_31_30 = 3;
            task_format_4_data = 0xc0140004;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM7_REG");

            // writing DR for TAP ownership
            // 11 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 2; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = 0x20000;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM8_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = 0x8000010a;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, task_format_3_data, 0xffffffff, "MEM9_REG");

            // Writing DR len in Task Format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0x14;
            Bit_31_30 = 3;
            task_format_4_data = 0xc0140004;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, task_format_4_data, 0xffffffff, "MEM10_REG");
#if 1
            // writing DR for TAP ownership
            // 11 Bypass node before DFx
            TAP_OWNERSHIP_DR_DFX_AGG = 0; // {wait, request, grant}
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | TAP_OWNERSHIP_DR_DFX_AGG << 11 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM11_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_1_data, 0xffffffff, "MEM12_REG");
#endif
            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 1;
            start_stopn = 1;
            mtc_config0 = 0x1013;
            write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, mtc_config0, 0xffffffff, "CF0_REG");

            // reading if end of test is reached
            eot_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
            while(eot_status & 0x4 == 0)
            {
                print("Not yet reached end of state...\n");
            }

            // Check grant status
            // We had sent 2 DRs in the test program. Each had 14 bits. So that's a total of 28 bits. So, the TDO RAM would have 28 bits. The upper 3 bits in each DR is the TAP_OWNERSHIP_DR_DFX_AGG. TAP_OWNERSHIP_DR_DFX_AGG = {wait, request, grant}. And we expect the second DR that comes back to have the grant bit set.
            tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR0_ADR, "CAPTURE_TDO_REG");
            print("tdo_capture: 0x%x\n", tdo_capture);
            tdo_capture  = tdo_capture >> 30;
            break;

        default:
            print("No Tap chain case is selected\n");
            break;
    }
    // Resetting the MTC, doing the soft reset
    write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, 0, 0xffffffff, "CF0_REG");
    write_reg_18a(AXIS_MTC_TOP_EXECUTE1_ADDR_ADR, MTC_RESET, 0xffffffff, "EXECUTE1_REG");
    if(tdo_capture == 3)
    {
        print("DFx Tap Ownership is granted\n");
    }
    else
    {
        print("DFx Tap Ownership is not granted\n");
    }
}
#endif

#if 0
uint32_t apb2tap_dfx_unlock()
{
    uint32_t tdo_capture, eod_status, execute_reg;
    uint32_t bypass_data = 0;

    // using SYSCON_PRODUCTION_KEY_HASH
    uint32_t intel_key_metal_password[12] = {
        0x4da6c81d, 0x95069cab, 0xa865b9c2, 0x57acd0d6,
        0x03ef8fe2, 0x219e24c3, 0x3dc6d5a7, 0xc07a08be,
        0x521bddd0, 0x7a4da172, 0x8df3d5b7, 0xd4377d28
    };
#if 0
    // old metal key password
    uint32_t intel_key_metal_password[12] = {
        0xf6a9ca04, 0xb55ce0c8, 0x457582d6, 0xa99ce792,
        0x2f5f8fcb, 0x46633e91, 0x578534d3, 0xf73d2387,
        0x082d1675, 0xcfd490b1, 0x1938cad6, 0x76f8415b
    };
#endif
    // request apb2tap access
    apb2tap_req_access(request_en);
    print("bypass_data: 0x%x\n", bypass_data);

    // enable TDO storage in shift dr
    write_reg_18a(AXIS_MTC_TOP_CFG1_ADDR_ADR, ENABLE_TDO_STORAGE, 0xffffffff, "MTC_TOP_CFG1_REG");

#if 0
    tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR1_ADR, "CAPTURE_TDO_REG");
    print("tdo_capture: 0x%x\n", tdo_capture);
#endif
    // The IR and DR will be written in MTC_PROGRAM_RAM register array in sequence of execution

    // Write IR to get ownership of dfx, and rest TAP points in bypass mode,
    // Task format 4 will be used to write IR and DR len
    // 4c - IR len of all TAP points connected to APB2TAP
    /* IR TAP Ownership
     * Write Instruction to get Dfx ownership: 0xF0, rest Tap points in Bypass
     * pause IR will be used to load instruction as Instruction is long */
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, 0xc00004c3, 0xffffffff, "MEM0_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, 0x7fffffff, 0xffffffff, "MEM1_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, 0x7fffffff, 0xffffffff, "MEM2_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, 0xf0ff, 0xffffffff, "MEM3_REG");

    /* DR TAP Ownership
     * DR Len = 3 * (DFX, as DFx has 3 bit RTDR) + 9 * (Bypass bit for rest) = 12 -> 0xc
     * RTDR = 3'b010 ( 1 - TO write to request tap ownership)
     * so DR = 0100_0000_0000 => 0x400 (0 for rest tap points)
     */
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, 0xc00c0004, 0xffffffff, "MEM4_REG");

    // writing DR
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, 0x00000400, 0xffffffff, "MEM5_REG");

    // Wait In Idle state for No. of clk cycle, Task Format 3
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, 0x8000010a, 0xffffffff, "MEM6_REG");

    // Select Intel Personality
    // Write to TAP_CTRL Reg at address 40h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, 0xc00004c3, 0xffffffff, "MEM7_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, 0x7fffffff, 0xffffffff, "MEM8_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, 0x7fffffff, 0xffffffff, "MEM9_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR10_ADR, 0x40ff, 0xffffffff, "MEM10_REG");

    // Write DR Len
    // DR Len  = 1 * (32 of DFx) + 9 * 1's = 41 => 0x29
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR11_ADR, 0xc0290004, 0xffffffff, "MEM11_REG");

    // Write DR, default value  is 0x0, and change is not required as per requirment
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR12_ADR, 0x40000000, 0xffffffff, "MEM12_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR13_ADR, 0x00000000, 0xffffffff, "MEM13_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload0 register at address 50h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR14_ADR, 0xc00004c3, 0xffffffff, "MEM14_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR15_ADR, 0x7fffffff, 0xffffffff, "MEM15_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR16_ADR, 0x7fffffff, 0xffffffff, "MEM16_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR17_ADR, 0x50ff, 0xffffffff, "MEM17_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR18_ADR, 0xc0290004, 0xffffffff, "MEM18_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR19_ADR, ((1 << 30) | ((intel_key_metal_password[0] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM19_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR20_ADR, (intel_key_metal_password[0] & 0xffe00000) >> 20 , 0xffffffff, "MEM20_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR19_ADR, ((1 << 30) | (0x9ca04 << 9) | bypass_data) , 0xffffffff, "MEM19_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR20_ADR, 0xf6a , 0xffffffff, "MEM20_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload1 register at address 54h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR21_ADR, 0xc00004c3, 0xffffffff, "MEM21_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR22_ADR, 0x7fffffff, 0xffffffff, "MEM22_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR23_ADR, 0x7fffffff, 0xffffffff, "MEM23_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR24_ADR, 0x54ff, 0xffffffff, "MEM24_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR25_ADR, 0xc0290004, 0xffffffff, "MEM25_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR26_ADR, ((1 << 30) | ((intel_key_metal_password[1] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM26_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR26_ADR, ((1 << 30) | (0x1ce0c8 << 9) | bypass_data) , 0xffffffff, "MEM26_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR27_ADR, (intel_key_metal_password[1] & 0xffe00000) >> 20 , 0xffffffff, "MEM27_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR27_ADR, 0xb54, 0xffffffff, "MEM27_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload2 register at address 58h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR28_ADR, 0xc00004c3, 0xffffffff, "MEM28_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR29_ADR, 0x7fffffff, 0xffffffff, "MEM29_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR30_ADR, 0x7fffffff, 0xffffffff, "MEM30_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR31_ADR, 0x58ff, 0xffffffff, "MEM31_REG");

    // Write DR Len 
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR32_ADR, 0xc0290004, 0xffffffff, "MEM10_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR33_ADR, ((1 << 30) | ((intel_key_metal_password[2] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM33_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR33_ADR, ((1 << 30) | (0x1582d6 << 9) | bypass_data) , 0xffffffff, "MEM33_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR34_ADR, (intel_key_metal_password[2] & 0xffe00000) >> 20 , 0xffffffff, "MEM34_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR34_ADR, 0x456 , 0xffffffff, "MEM34_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload3 register at address 5ch
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR35_ADR, 0xc00004c3, 0xffffffff, "MEM35_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR36_ADR, 0x7fffffff, 0xffffffff, "MEM36_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR37_ADR, 0x7fffffff, 0xffffffff, "MEM37_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR38_ADR, 0x5cff, 0xffffffff, "MEM38_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR39_ADR, 0xc0290004, 0xffffffff, "MEM39_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR40_ADR, ((1 << 30) | ((intel_key_metal_password[3] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM40_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR40_ADR, ((1 << 30) | (0x1ce792<< 9) | bypass_data) , 0xffffffff, "MEM40_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR41_ADR, (intel_key_metal_password[3] & 0xffe00000) >> 20 , 0xffffffff, "MEM41_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR41_ADR, 0xa98 , 0xffffffff, "MEM41_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload4 register at address f3h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR42_ADR, 0xc00004c3, 0xffffffff, "MEM42_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR43_ADR, 0x7fffffff, 0xffffffff, "MEM43_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR44_ADR, 0x7fffffff, 0xffffffff, "MEM44_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR45_ADR, 0xf3ff, 0xffffffff, "MEM45_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR46_ADR, 0xc0290004, 0xffffffff, "MEM46_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR47_ADR, ((1 << 30) | ((intel_key_metal_password[4] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM47_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR47_ADR, ((1 << 30) | (0x1f8fcb << 9) | bypass_data) , 0xffffffff, "MEM47_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR48_ADR, (intel_key_metal_password[4] & 0xffe00000) >> 20 , 0xffffffff, "MEM48_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR48_ADR, 0x2f4, 0xffffffff, "MEM48_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload5 register at address f4h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR49_ADR, 0xc00004c3, 0xffffffff, "MEM49_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR50_ADR, 0x7fffffff, 0xffffffff, "MEM50_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR51_ADR, 0x7fffffff, 0xffffffff, "MEM51_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR52_ADR, 0xf4ff, 0xffffffff, "MEM52_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR53_ADR, 0xc0290004, 0xffffffff, "MEM53_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR54_ADR, ((1 << 30) | ((intel_key_metal_password[5] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM54_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR54_ADR, ((1 << 30) | (0x33e91<< 9) | bypass_data) , 0xffffffff, "MEM54_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR55_ADR, (intel_key_metal_password[5] & 0xffe00000) >> 20 , 0xffffffff, "MEM55_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR55_ADR, 0x466, 0xffffffff, "MEM55_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload6 register at address f5h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR56_ADR, 0xc00004c3, 0xffffffff, "MEM56_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR57_ADR, 0x7fffffff, 0xffffffff, "MEM57_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR58_ADR, 0x7fffffff, 0xffffffff, "MEM58_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR59_ADR, 0xf5ff, 0xffffffff, "MEM59_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR60_ADR, 0xc0290004, 0xffffffff, "MEM60_REG");
    // Write Password
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR61_ADR, ((1 << 30) | (0x534d3 << 9) | bypass_data) , 0xffffffff, "MEM61_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR61_ADR, ((1 << 30) | ((intel_key_metal_password[6] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM61_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR62_ADR, (intel_key_metal_password[6] & 0xffe00000) >> 20 , 0xffffffff, "MEM62_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR62_ADR, 0x578, 0xffffffff, "MEM62_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload7 register at address f6h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR63_ADR, 0xc00004c3, 0xffffffff,"MEM63_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR64_ADR, 0x7fffffff, 0xffffffff,"MEM64_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR65_ADR, 0x7fffffff, 0xffffffff, "MEM65_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR66_ADR, 0xf6ff, 0xffffffff, "MEM66_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR67_ADR, 0xc0290004, 0xffffffff, "MEM10_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR68_ADR, ((1 << 30) | ((intel_key_metal_password[7] & 0x1fffff) << 9) | bypass_data) , 0xffffffff,"MEM68_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR68_ADR, ((1 << 30) | (0x1d2387 << 9) | bypass_data) , 0xffffffff,"MEM68_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR69_ADR, (intel_key_metal_password[7] & 0xffe00000) >> 20 , 0xffffffff,"MEM69_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR69_ADR, 0xf72, 0xffffffff,"MEM69_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload8 register at address f8h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR70_ADR, 0xc00004c3, 0xffffffff, "MEM70_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR71_ADR, 0x7fffffff, 0xffffffff, "MEM71_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR72_ADR, 0x7fffffff, 0xffffffff, "MEM72_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR73_ADR, 0xf8ff, 0xffffffff, "MEM73_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR74_ADR, 0xc0290004, 0xffffffff, "MEM74_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR75_ADR, ((1 << 30) | ((intel_key_metal_password[8] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM75_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR75_ADR, ((1 << 30) | (0xd1675 << 9) | bypass_data) , 0xffffffff, "MEM75_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR76_ADR, (intel_key_metal_password[8] & 0xffe00000) >> 20 , 0xffffffff, "MEM76_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR76_ADR, 0x82, 0xffffffff, "MEM76_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload9 register at address f9h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR77_ADR, 0xc00004c3, 0xffffffff, "MEM77_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR78_ADR, 0x7fffffff, 0xffffffff, "MEM78_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR79_ADR, 0x7fffffff, 0xffffffff, "MEM79_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR80_ADR, 0xf9ff, 0xffffffff, "MEM80_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR81_ADR, 0xc0290004, 0xffffffff, "MEM81_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR82_ADR, ((1 << 30) | ((intel_key_metal_password[9] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM82_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR82_ADR, ((1 << 30) | (0x1490b1 << 9) | bypass_data) , 0xffffffff, "MEM82_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR83_ADR, (intel_key_metal_password[9] & 0xffe00000) >> 20 , 0xffffffff, "MEM83_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR83_ADR, 0xcfc , 0xffffffff, "MEM83_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload10 register at address fAh
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR84_ADR, 0xc00004c3, 0xffffffff, "MEM84_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR85_ADR, 0x7fffffff, 0xffffffff, "MEM85_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR86_ADR, 0x7fffffff, 0xffffffff, "MEM86_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR87_ADR, 0xfaff, 0xffffffff, "MEM87_REG");

    // Write DR Len
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR88_ADR, 0xc0290004, 0xffffffff, "MEM88_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR89_ADR, ((1 << 30) | ((intel_key_metal_password[10] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM89_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR89_ADR, ((1 << 30) | (0x18cad6 << 9) | bypass_data) , 0xffffffff, "MEM89_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR90_ADR, (intel_key_metal_password[10] & 0xffe00000) >> 20, 0xffffffff, "MEM90_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR90_ADR, 0x192, 0xffffffff, "MEM90_REG");

    // Write Intel metal key password into payload register of DFx
    // Write to Unlock payload11 register at address fBh
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR91_ADR, 0xc00004c3, 0xffffffff, "MEM91_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR92_ADR, 0x7fffffff, 0xffffffff, "MEM92_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR93_ADR, 0x7fffffff, 0xffffffff, "MEM93_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR94_ADR, 0xfbff, 0xffffffff, "MEM94_REG");

    // Write DR Len 
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR95_ADR, 0xc0290004, 0xffffffff, "MEM95_REG");
    // Write Password
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR96_ADR, ((1 << 30) | ((intel_key_metal_password[11] & 0x1fffff) << 9) | bypass_data) , 0xffffffff, "MEM96_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR96_ADR, ((1 << 30) | (0x18415b << 9) | bypass_data) , 0xffffffff, "MEM96_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR97_ADR, (intel_key_metal_password[11] & 0xffe00000) >> 20 , 0xffffffff, "MEM97_REG");
    //write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR97_ADR, 0x76e , 0xffffffff, "MEM97_REG");

    // IR and DR giving unlock bit as HIGH, to request for unlock
    // Write to TAP_CTRL Reg at address 40h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR98_ADR, 0xc00004c3, 0xffffffff, "MEM98_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR99_ADR, 0x7fffffff, 0xffffffff, "MEM99_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR100_ADR, 0x7fffffff, 0xffffffff, "MEM100_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR101_ADR, 0x40ff, 0xffffffff, "MEM101_REG");

    // Write DR Len
    // DR Len  = 1 * (32 of DFx) + 9 * 1's = 41 => 0x29
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR102_ADR, 0xc0290004, 0xffffffff, "MEM102_REG");

    // Write DR, default value  is 0x0, and change is not required as per requirment
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR103_ADR, 0x40001000, 0xffffffff, "MEM103_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR104_ADR, 0x00000000, 0xffffffff, "MEM104_REG");

    // IR and DR giving resume bit as HIGH, to do early boot ON
    // Write to TAP_CTRL Reg at address 40h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR105_ADR, 0xc00004c3, 0xffffffff, "MEM105_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR106_ADR, 0x7fffffff, 0xffffffff, "MEM106_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR107_ADR, 0x7fffffff, 0xffffffff, "MEM107_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR108_ADR, 0x40ff, 0xffffffff, "MEM108_REG");

    // Write DR Len
    // DR Len  = 1 * (32 of DFx) + 9 * 1's = 41 => 0x29
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR109_ADR, 0xc0290004, 0xffffffff, "MEM109_REG");

    // Write DR, default value  is 0x0, and change is not required as per requirment
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR110_ADR, 0x40000400, 0xffffffff, "MEM110_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR111_ADR, 0x00000000, 0xffffffff, "MEM111_REG");

    // End of Test
    // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR112_ADR, 0x8000000c, 0xffffffff, "MEM112_REG");

    // Starting the MTC and some config for MTC, rate_sel = 20 MHZ, config = MTC_EXTERNAL_MODE(Axxia Not included)
    write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, 0x1013, 0xffffffff, "CF0_REG");

    // reading if end of test is reached
    eod_status = read_reg_18a(AXIS_MTC_TOP_STAT2_ADDR_ADR, "STAT2_REG");
    while(eod_status & 0x4 == 0)
    {
        print("Not yet reached end of state...\n");
    }

    // Resetting the MTC, doing the soft reset
    write_reg_18a(AXIS_MTC_TOP_EXECUTE1_ADDR_ADR, 0x4, 0xffffffff, "EXECUTE1_REG");

#if 0
    // Read the Execute1 reg, it is self clearing reg
    execute_reg = read_reg_18a(AXIS_MTC_TOP_EXECUTE1_ADDR_ADR, "EXECUTE1_REG");
    print("Execute_reg: 0x%x\n", execute_reg);
#endif

    // Read the status register of DFx to check the policy and personality
    // Write to STATUS Reg at address 30h
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR0_ADR, 0xc00004c3, 0xffffffff, "MEM0_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, 0x7fffffff, 0xffffffff, "MEM1_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, 0x7fffffff, 0xffffffff, "MEM2_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, 0x30ff, 0xffffffff, "MEM3_REG");

    // Write DR Len
    // DR Len  = 1 * (32 of DFx) + 9 * 1's = 41 => 0x29
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, 0xc0290004, 0xffffffff, "MEM4_REG");

    // Write DR, default value  is 0x0, and change is not required as per requirment
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, 0x40000000, 0xffffffff, "MEM5_REG");
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR6_ADR, 0x00000000, 0xffffffff, "MEM6_REG");

    // End of Test, used Task Format 1
    write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR7_ADR, 0x8000000c, 0xffffffff, "MEM6_REG");
    // Starting the MTC and some cfg for MTC
    write_reg_18a(AXIS_MTC_TOP_CFG0_ADDR_ADR, 0x1013, 0xffffffff, "CF0_REG");

    sleep(5);
    // Check the presonality and policy output
    tdo_capture = read_reg_18a(AXIS_MTC_TOP_TDO_CAP_MEM_START_ADDR1_ADR, "CAPTURE_TDO_REG");
    print("tdo_capture: 0x%x\n", tdo_capture);
    if(tdo_capture == 0x80)
    {
        print("DFx security unlock is successful\n");
    }
    else
    {
        print("DFx Security unlock is not successful\n");
    }

    return 0;
}
#endif

int main()
{
    init();
    //apb2tap_dfx_unlock();
    dfx_tap_ownership(4);
}
