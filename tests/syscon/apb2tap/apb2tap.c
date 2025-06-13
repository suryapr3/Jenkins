
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
uint32_t dfx_tap_ownership(int case_seq)
{
    uint32_t tdo_capture, eot_status, execute_reg, Numberof_tck_cycle, cfg_config_ctl, rate_sel, start_stopn, mtc_config0;
    uint32_t Instruction_code, Instruction, Numberof_shift_instruction_bits, Numberof_shift_data_bits, Bit_31_30;
    uint32_t task_format_4_data, task_format_3_data, task_format_1_data, host_mux_config;
    uint8_t BYPASS_IR_TEMP = 0x3;
    uint8_t BYPASS_P1TDO = 0x3;
    uint8_t BYPASS_IR_IPF1 = 0x3;
    uint8_t BYPASS_IR_IPF2 = 0x3;
    uint8_t BYPASS_IR_IPF3 = 0x3;
    uint8_t BYPASS_IR_IPF4 = 0x3;
    uint8_t BYPASS_IR_IPF5 = 0x3;
    uint8_t BYPASS_IR_IPF6 = 0x3;
    uint8_t BYPASS_IR_FUNC = 0x3;
    uint8_t BYPASS_IR_HOST_TAP = 3;
    uint8_t BYPASS_IR_REPEATER = 3;
    uint8_t BYPASS_IR_DFT_FORWARD = 3;
    uint8_t BYPASS_IR_DRF_1_S_DTS = 0xff;
    uint8_t BYPASS_IR_DRF_1_N_DTS = 0xff;
    uint8_t BYPASS_IR_DRF_0_S_DTS = 0xff;
    uint8_t BYPASS_IR_DRF_0_N_DTS = 0xff;
    uint8_t BYPASS_IR_RCS_DTS = 0xff;
    uint8_t BYPASS_IR_SYSCON_DTS = 0xff;
    uint8_t BYPASS_IR_CORESIGHT = 0xf;
    uint8_t BYPASS_IR_FC = 0xff;
    uint8_t BYPASS_IR_MBOX = 0xff;
    uint8_t BYPASS_DR = 0;
    uint8_t TAP_OWNERSHIP_IR_DFX_AGG = 0xf0;
    uint8_t TAP_OWNERSHIP_DR_DFX_AGG;

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
            print("Configured TAP Chain 4: Func_forward -->  Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6 --> DFT_FORWARD --> Network_Host \n");
            /*
             * Before configuring above chain, configure Network host tap to bring zone_repeater_tap out of chain &
             * to bring dfT_forward & IPF1-IPF6 in chain
                To achieve this, TAP chain will be: ZONE1_REPEATER --> HOST_TAP
                IR LEN: 2 + 2 => 4 or 6
                DR_LEN : 7 (attached to Network Host tap each in Bypass) + 3 ( 3 bits to configure MUX of network host tap) \
                         + 1 (ZONE1_REPEATER in Bypass) => 11 or 12
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
            Instruction = BYPASS_IR_REPEATER << 2 ;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR1_ADR, task_format_4_data, 0xffffffff, "MEM1_REG");

            // Writing DR Len in Task format 4
            Instruction_code = 4;
            Numberof_shift_data_bits = 0xb;
            //Numberof_shift_data_bits = 0xc;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_data_bits << 16 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR2_ADR, task_format_4_data, 0xffffffff, "MEM2_REG");

            // writing DR in Task format 4
            host_mux_config = 4;
            Bit_31_30 = 0;
            task_format_4_data = Bit_31_30 << 30 | host_mux_config;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR3_ADR, task_format_4_data, 0xffffffff, "MEM3_REG");

            // Now as DFT_FORWARD is in chain now try DFx Tap ownership with full tap chain
            /* TAP Chain 4: Func_forward  --> Dfx_aggr --> MBOX --> Fuse_Controller --> Syscon_DTS --> Coresight --> \
                    IPF1 --> IPF2 --> IPF3 --> IPF4 --> IPF5 --> IPF6 --> DFT_FORWARD --> HOST_TAP
               IR LEN => 2 (FUNC_FORWARD) +  4 x 8 + 4 (Coresight) + 6 x 2 + 2 + 2 => 54 => 0x36
               DR LEN => Func_forward bypass (1) + 3 (DFx) + 12 ( Rest in Bypass) => 16 => 0x10
               DR => 0010_0000_0000_0000 => 0x2000
            */
            // Writing IR Len in Task format 4
            Instruction_code = 3;
            Numberof_shift_instruction_bits = 0x36;
            Bit_31_30 = 3;
            task_format_4_data = Bit_31_30 << 30 | Numberof_shift_instruction_bits << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR4_ADR, task_format_4_data, 0xffffffff, "MEM4_REG");

            // Writing IR in Task format 4
            // Bit 30 => 1, rest 1 [29:0]
            Instruction = concatenate_hex(11, BYPASS_IR_FC, 1, 0, BYPASS_IR_SYSCON_DTS, 7, 0, BYPASS_IR_CORESIGHT, 3, 0 , \
                    BYPASS_IR_IPF1, 1, 0, BYPASS_IR_IPF2, 1, 0, BYPASS_IR_IPF3, 1, 0, BYPASS_IR_IPF4, 1, 0, \
                    BYPASS_IR_IPF5, 1, 0, BYPASS_IR_IPF6, 1, 0, BYPASS_IR_DFT_FORWARD, 1, 0, BYPASS_IR_HOST_TAP, 1, 0);

            //Instruction = concatenate_hex(11, BYPASS_IR_SYSCON_DTS, 7, 0, BYPASS_IR_CORESIGHT, 3, 0 , \
                    BYPASS_IR_IPF1, 1, 0, BYPASS_IR_IPF2, 1, 0,BYPASS_IR_IPF3, 1, 0,BYPASS_IR_IPF4, 1, 0, \
                    BYPASS_IR_IPF5, 1, 0, BYPASS_IR_IPF6, 1, 0, BYPASS_IR_DFT_FORWARD, 1, 0, BYPASS_IR_HOST_TAP, 1, 0, BYPASS_P1TDO, 1, 0);
            Bit_31_30 = 1;
            task_format_4_data = Bit_31_30 << 30 | Instruction;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR5_ADR, task_format_4_data, 0xffffffff, "MEM5_REG");

            // Bit 30 => 0, [25:22] => f, [21:14] => 0xf0, [13:6] => all 1, [5:0] => all 1
            //Instruction = concatenate_hex(4, BYPASS_IR_FUNC, 2, 0, TAP_OWNERSHIP_IR_DFX_AGG, 7, 0, BYPASS_IR_MBOX, 7, 0, BYPASS_IR_FC, 7, 0);
            Instruction = concatenate_hex(4, BYPASS_IR_FUNC, 1, 0, TAP_OWNERSHIP_IR_DFX_AGG, 7, 0, BYPASS_IR_MBOX, 7, 0, BYPASS_IR_FC, 7, 2);
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
            task_format_4_data = Bit_31_30 << 30 | BYPASS_DR | TAP_OWNERSHIP_DR_DFX_AGG << 12 | BYPASS_DR;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR8_ADR, task_format_4_data, 0xffffffff, "MEM8_REG");

            // Wait In Idle state for No. of clk cycle, Task Format 3
            Instruction_code = 0xa;
            Numberof_tck_cycle = 0x10;
            Bit_31_30 = 2;
            task_format_3_data = Bit_31_30 << 30 | Numberof_tck_cycle << 4 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR9_ADR, task_format_3_data, 0xffffffff, "MEM9_REG");

            // End of Test
            // Task Format 1 will be used for EOT, with Instruction code 4'b110 -> 0xc
            Instruction_code = 0xc;
            Bit_31_30 = 2;
            task_format_1_data = Bit_31_30 << 30 | Instruction_code;
            write_reg_18a(AXIS_MTC_TOP_PRGM_MEM_START_ADDR12_ADR, task_format_1_data, 0xffffffff, "MEM12_REG");

            // Starting the MTC and some cfg for MTC
            cfg_config_ctl = 3;
            rate_sel = 3;
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
            tdo_capture  = tdo_capture >> 12;
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

int main()
{
    init();
    //apb2tap_dfx_unlock();
    dfx_tap_ownership(1);
}
