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
 * @file  etr_program.c
****************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"
#include "common_functions.h"
#include "srp_block_ids.h"
#include "coresight_common.h"
#include "coresight_head.h"

// Function to read etr memory
uint32_t etr_mem_read(etr_switch_t mem_en)
{
    int ind = 0;
    uint32_t val, etr_size = 0, trace_size = 0;

    // get the buffer fill level
    uint32_t cbuflevel = get_etr_buffer_level();
    print("ETR_CBUFLEVEL: 0x%x\n", cbuflevel);

    uint32_t ram_size = get_etr_ram_size();
    print("ETR RAM size: 0x%x\n", ram_size);

   uint32_t status = etr_status();
   print("ETR status: 0x%x\n", status);

    // Read RWP and RRP
    uint32_t RRP = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RRP_OFFSET, SECURE, "ETR_RRP REG");
    uint32_t RWP = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RWP_OFFSET, SECURE, "ETR_RWP REG");
    print("ETR_RRP, ETR_RWP: 0x%x, 0x%x\n", RRP, RWP);
    etr_size = RWP - RRP;

    // switch ON if wants to read etr memory
    if(mem_en == ETR_EN)
    {
        FILE *file = fopen("ETR_formatted_trace.txt", "w");
        if(file == NULL)
        {
          perror("Failed to open file");
          return 1;
        }

        while(val != 0xffffffff && (trace_size < etr_size))
        {
            val = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RRD_OFFSET, SECURE, "RAM READ REG");
            print("ETR Trace data: 0x%x, ind: %d\n", val, ind);
            fprintf(file, "ETR Trace data: 0x%x, ind: %d\n", val, ind);
            ind++,
            trace_size++;
        }
    }
    return etr_size;
}

// To know the RAM Size
uint32_t get_etr_ram_size()
{
    // To know the size of ETR memory
    uint32_t ram_size = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RSZ_OFFSET, SECURE, "RAM SIZE REG");

    return ram_size;
}

// Function to initialize and configure the ETR
void configure_etr(etr_mode_t etr_mode) {

    // Disable the ETR to configure it
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_CTL_OFFSET, ETR_DISABLE, SECURE, "CTL reg");

    // Configure the ETR etr_mode(Circular Buffer, Software FIFO 1, Software FIFO 2)
    switch(etr_mode)
    {
        case ETR_CB_MODE:
            write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_MODE_OFFSET, ETR_CB_BUFFER, SECURE, "MODE REG");
            LOG_PRINT("ETR configured to Circular Buffer etr_mode");
            break;

        case SWF_MODE_1:
            write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_MODE_OFFSET, ETR_SWF1_BUFFER, SECURE, "MODE REG");
            LOG_PRINT("ETR configured to Software Buffer etr_mode 1");
            break;

        case SWF_MODE_2:
            write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_MODE_OFFSET, ETR_SWF2_BUFFER, SECURE, "MODE REG");
            LOG_PRINT("ETR configured to Software Buffer etr_mode 2");
            break;

        default:
            LOG_PRINT("NO ETR etr_mode is selected");
    }

    // Ram size of ETR
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RSZ_OFFSET, ETR_RSZ , SECURE, "TRG REG");

    // Write watermark level to ETR watermark register for FIFO etr_mode configuration
    if(etr_mode == SWF_MODE_1 || etr_mode == SWF_MODE_2)
        write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_BUFWM_OFFSET, ETR_WATERMARK_LVL, SECURE, "MODE REG");

    // Enable triggering to capture 32 bits words in trace memory
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_TRG_OFFSET, ETR_TRG_EN , SECURE, "TRG REG");

    // Configure Periodic synchronization counter
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_PSCR_OFFSET, ETR_PSCR_CNT, SECURE, "PSCR reg");

    // To enable the secure transaction over AXI to memory
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_AXI_CTL_OFFSET, ETR_AXI_SECURE_EN, SECURE, "AXICTL REG");
    read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_AXI_CTL_OFFSET, SECURE, "AXICTL REG");

    // configure FFCR
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_FFCR_OFFSET, ETR_FORMATTER_EN, SECURE, "FFCR reg");

    // Set RWP and RRP to the beginning of system memory address
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RRP_OFFSET, SYS_MEM_ADDR, SECURE, "RRP reg");
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RWP_OFFSET, SYS_MEM_ADDR, SECURE, "RWP reg");

    // Loading the system memory address to Data buffer address register to write into system memory
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_DBALO_OFFSET, SYS_MEM_ADDR , SECURE, "DBALO REG");

    // Set Data buffer address register for remaining upper 32 bits of system memory
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_DBAHI_OFFSET, 0x0 , SECURE, "DBAHI REG");

    // To set the upper 32 bit of Trace memory if > 32 bits
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RWPHI_OFFSET, 0x0 , SECURE, "RWPHI REG");
    write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_RRPHI_OFFSET, 0x0 , SECURE, "RRPHI REG");
}

// Get the buffer fill level
uint32_t get_etr_buffer_level()
{
    uint32_t fill_level = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_CBUFLEVEL_OFFSET, SECURE, "CBUFLEVEL REG");
    return fill_level;
}

// Function to get status of ETR
uint32_t etr_status()
{
    uint32_t status = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_STS_OFFSET, SECURE, "STATUS REG");

    // to return ETR status
    return status;
}

// Function to check ETR TMC Ready state
void etr_ready()
{
    uint32_t TMCReady = 0;
    int run_time = 0;
    int max_run_time = 60; // 1 min
    uint32_t status;

    while(!TMCReady && run_time < max_run_time)
    {
        status = etr_status();
        print("\rETR status: 0x%x....", status);

        TMCReady = (status & (1 << STS_BIT_TMCReady));
        sleep(TIME_INTERVAL);
        run_time += TIME_INTERVAL;
    }
    if(!TMCReady)
    {
        print("ETR is not ready yet\n");
    }
    else
    {
        print("ETR is ready, run_time: %d\n", run_time);
    }
}

// Function to enable/disable etr
void etr_switch(etr_switch_t ctrl)
{
    uint32_t status;
    int wait = 0;
    if(ctrl == ETR_EN)
    {
        // Enable ETR
        write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_CTL_OFFSET, ETR_ENABLE, SECURE, "CTL REG");
    }
    else
    {
        // Disable ETR
        write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_CTL_OFFSET, ETR_DISABLE, SECURE, "CTL REG");
    }

    uint32_t etr_ctl = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_CTL_OFFSET, SECURE, "ETR_CTL");
    print("ETR_CTL: 0x%x\n", etr_ctl);
}

// Function to manual flush
void etr_manual_flush(etr_switch_t flush_ctrl)
{
    uint32_t flush_status ;
    int run_time = 0;

    // Do Manual flush if required
    if(flush_ctrl == ETR_EN)
    {
        // Manual flush will drain the trace data to trace memory after the TMC is enabled
        write_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_FFCR_OFFSET, ETR_MANUAL_FLUSH, SECURE, "FFCR reg");
        flush_status = read_m_cs_dbg_18a(ETR_BASE_ADDR + ETR_FFSR_OFFSET, SECURE, "FFSR REG");
        print("flush status: 0x%x\n", flush_status);

        // Check for etr ready
        etr_ready();
    }
}
