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
 * @file  coresight_main.c
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
#include "coresight_common.h"
#include "coresight_head.h"

// Function to get etmb core address based on core name
uint32_t get_etmb_core_address(int core_num, char core_name[])
{
    if(strcmp(core_name, "VEX") == 0)
    {
        print("VEX core selected for core_num: %d\n", core_num);
        if(core_num > 39 || core_num < 0)
        {
            print("Invalid core num for vex\n");
            return 1;            // return invalid address
        }

        // skip the non-available core if single chassis and not silicon
        if (!g_abc_build_multi_chassis && !g_abc_silicon)
        {
            if(((core_num > 15) && (core_num < 32))  || (core_num == 33) || (core_num == 35) || (core_num == 37) || (core_num == 39))
                return 1;       // return invalid address
        }

        if(vex_address_map[core_num].core_num == core_num)
            return vex_address_map[core_num].core_address;
    }
    else if(strcmp(core_name, "RCS") == 0)
    {
        print("RCS core selected, for core_num: %d\n", core_num);
        if(core_num > 3 || core_num < 0)
        {
            print("Invalid core num for RCS\n");
            return 1;           // return invalid address
        }
        LOG_PRINT("core_num: %d", core_num);
        if(rcs_address_map[core_num].core_num == core_num)
            return rcs_address_map[core_num].core_address;
        else
            print("Address cannot be found for RCS\n");
    }
    else
        print("No valid core selected\n");
}

void pre_coresight_config()
{
    // Check for ETF ready before configuration
    etf_ready();

    // Configure ETF
    configure_etf(HWF_MODE);

    // Check for ETR ready before configuration
    etr_ready();

    // Configure ETR
    configure_etr(ETR_CB_MODE);

    // Enable ETF and ETR
    etf_switch(ETF_EN);
    etr_switch(ETR_EN);
}

void post_coresight_config(int core_num, char core_name[], etr_switch_t flush_ctrl)
{
    // disable etm
   etm_switch(core_num, core_name, DISABLE);

    // Manual flush ETF
    etr_manual_flush(flush_ctrl);

   // Turn OFF ETF and ETR
   etf_switch(ETF_DIS);
   etr_switch(ETR_DIS);

}

void rsm_mem_read(uint32_t etr_size, uint32_t trace_id)
{
    uint32_t addr, buffer;
    int offset;

    // To write traces to trace.txt
    FILE *file = fopen("trace.txt", "a");
    fprintf(file, "ETR_SIZE: 0x%08x\n", etr_size);
    if(file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    fprintf(file, "Trace_id: 0x%08x\n", trace_id);
    //reading rsm_mem using coresight api
   for(offset = 0; offset <= etr_size; offset += 4)
   {
        addr = SYS_MEM_ADDR + offset;
        buffer = read_m_syscon_1_cs_dbg_18a(addr, NON_SECURE, "rsm_mem");
        print("buffer: 0x%08x, addr: 0x%x\n", buffer, addr);
        fprintf(file, "Trace data: 0x%08x\n, addr: 0x%08x\n", buffer, addr);
   }
}

void mem_cap_mem_read(uint32_t etr_size)
{
    int offset;
    uint32_t buffer, addr;

    // To write traces to trace.txt
    FILE *file = fopen("trace.txt", "w");
    fprintf(file, "ETR_SIZE: 0x%08x\n", etr_size);
    if(file == NULL)
    {
        perror("Failed to open file");
        return;
    }

   //reading mem_cap using coresight api
   for(offset = 0; offset <= etr_size; offset += 4)
   {
       addr = SYS_MEM_ADDR + offset;
       buffer = read_reg_18a(addr, "sram");
       print("buffer: 0x%08x, addr: 0x%x\n", buffer, addr);
       fprintf(file, "Trace data: 0x%08x\n, addr: 0x%08x\n", buffer, addr);
   }
}

/* Function to select breakpoint
iac: Instruction address controller for breakpoint */
void dtc_select_breakpoint(uint32_t etmb_base_address, int iac)
{
    uint32_t bp_sel;
    if (iac > 7 || iac < 0) {
        print("... Error: the iac value should be [0..7]\n");
        return;
    }
    print("... dtc_select_breakpoint iac(%d)\n", iac);

    bp_sel = read_m_cs_dbg_18a(etmb_base_address + ETMB_DBGBPIACSELR_OFFSET, SECURE, "DBGBPIACSELR REG");
    print("... Pre-value of bp_sel: 0x%x\n", bp_sel);

    bp_sel |= (1 << iac);
    printf("... Post-value of bp_sel: %x\n", bp_sel);
    write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGBPIACSELR_OFFSET, bp_sel, SECURE, "DBGPROCPCR REG");
}

/* function to set breakpoint at the required address
 pc:  program counter */
void dtc_set_breakpoint(uint32_t etmb_base_address, int iac, uint32_t pc)
{
    // Array of IACVALR offsets
    uint32_t iacvalr_offsets[] = {
        ETMB_IACVALR0_OFFSET,
        ETMB_IACVALR1_OFFSET,
        ETMB_IACVALR2_OFFSET,
        ETMB_IACVALR3_OFFSET,
        ETMB_IACVALR4_OFFSET,
        ETMB_IACVALR5_OFFSET,
        ETMB_IACVALR6_OFFSET,
        ETMB_IACVALR7_OFFSET
    };
    if (iac > 7 || iac < 0) {
        print("... Error: the iac value should be [0..7]\n");
        return;
    }
    write_m_cs_dbg_18a(etmb_base_address + iacvalr_offsets[iac], pc, SECURE, "IACVALR REG");
    dtc_select_breakpoint(etmb_base_address, iac);
    print("... Breakpoint is set at PC 0x%x in instruction address comparator (iac) 0x%x\n", pc, iac);
}

// Function to get debug status
uint32_t get_debug_status(uint32_t etmb_base_address)
{
    uint32_t dbgctrl_status = read_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCTRLSTATR_OFFSET, SECURE, "DBGCTRL_STATUS REG");
    print("DBGCTRL_STATUS:0x%x\t", dbgctrl_status);
    return dbgctrl_status;
}

// To switch the debug controller
void dtc_switch(uint32_t etmb_base_address, dtc_switch_t debug_ctrl)
{
    switch (debug_ctrl)
    {
        case ON:
            write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_ON, SECURE, "DTC_ON");
            LOG_PRINT("Debug Controller is ON");
            break;

        case OFF:
            write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_OFF, SECURE, "DTC_OFF");
            LOG_PRINT("Debug Controller is OFF");
            break;

        case STOP:
            write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_STOP, SECURE, "DTC_STOP");
            LOG_PRINT("Debug Controller is STOPPED");
            break;

        case CONTINUE:
            write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_CONTINUE, SECURE, "DTC_CONTINUE");
            LOG_PRINT("Debug Controller is in Continue mode");
            break;

        case STEP:
            write_m_cs_dbg_18a(etmb_base_address + ETMB_DBGCMDR_OFFSET, DTC_COMMAND_STEP, SECURE, "DTC_STEP");
            LOG_PRINT("Debug Controller is in Step mode");
            break;

        default:
            break;
    }
}

// Get processor status
uint32_t get_processor_status(uint32_t etmb_base_address)
{
    uint32_t proc_status = read_m_cs_dbg_18a(etmb_base_address + ETMB_DBGPROCSTATR_OFFSET, SECURE, "DBGPROC_STATUS REG");
    print("DBGPROC_STATUS: 0x%x\t", proc_status);

    return proc_status;
}

// Get processor program counter count
uint32_t get_proc_pc(uint32_t etmb_base_address)
{
    uint32_t pc = read_m_cs_dbg_18a(etmb_base_address + ETMB_DBGPROCPCR_OFFSET, SECURE, "PROC_PCR REG");
    print("PROC_PCR: 0x%x\n", pc);
    return pc;
}

// To return status if DTC or processor is stopped
int dtc_run_until_stopped(uint32_t etmb_base_address)
{
    int status = 0;
    int wait_until_stopped = 0, start_time = 0, time_out = 0;
    int g_max_time = 60; // 60 seconds

    while (!wait_until_stopped)
    {
          uint32_t pc = get_proc_pc(etmb_base_address);
          uint32_t dbg_status = get_debug_status(etmb_base_address);
          uint32_t proc_status = get_processor_status(etmb_base_address);

          print("PC: 0x%x\n", pc);
          print("dbg_status: %d\n", dbg_status);
          print("proc_status: 0x%x\n", proc_status);

         if(dbg_status == DTC_STATE_STOPPED)
         {
           wait_until_stopped = 1;
           status = 1;
           print("... DTC is in stop state\n");
         }

         if(proc_status == PROC_STATE_IDLING && pc > 0)
         {
           wait_until_stopped = 1;
           status = 2; // Program is finished
           print("... Processor is in idling state\n");
         }
    }
    return status;
}

// DTC to wait until stop is asserted
int dtc_wait_until_stopped(uint32_t etmb_base_address)
{
    int g_max_wait_time = 60; // 60 seconds
    time_t start_time = time(NULL);
    int status = dtc_run_until_stopped(etmb_base_address);
    int time_spend = time(NULL) - start_time;
    if (time_spend > g_max_wait_time)
    {
        print("Timed out!\n");
        status = -1;
    }
    print("... Waited time: %.2f second(s)\n", time_spend);
    return status;
}

/* Functin to configuration before processor start,
   setting breakpoints, switching on DTC */
void pre_proc_run(int core_num, char core_name[])
{
    uint32_t etmb_base_address = get_etmb_core_address(core_num, core_name);
    dtc_set_breakpoint(etmb_base_address, 0, 0);
    dtc_switch(etmb_base_address, ON);
}

/* Function to check status after processor start,
 * and configuring DTC */
void post_proc_run(int core_num, char core_name[])
{
    uint32_t etmb_base_address = get_etmb_core_address(core_num, core_name);

    // Wait till DTC is stopped
    dtc_wait_until_stopped(etmb_base_address);

    // Check the program counter status
    uint32_t pc = get_proc_pc(etmb_base_address);
    if(pc == 0)
    {
        dtc_switch(etmb_base_address, STEP);
    }
    dtc_switch(etmb_base_address, CONTINUE);

    // Check the status of DTC
    uint32_t run_status = dtc_wait_until_stopped(etmb_base_address);
    if(run_status == 2)
    {
        print("Processor is in idiling state and pc > 0, so program is finished\n");
    }
    else
    {
        print("Processor not able to start, Time out\n");
    }
}
