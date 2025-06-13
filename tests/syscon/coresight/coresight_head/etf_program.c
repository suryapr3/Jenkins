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
 * @file  etf_program.c
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

// Function to get status of etf
uint32_t etf_status()
{
    uint32_t status = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_STS_OFFSET, SECURE, "STATUS REG");

    // to return etf status
    return status;
}

// Function to check etf ready
void etf_ready()
{
    uint32_t TMCReady = 0;
    int run_time = 0;
    int max_run_time = 60; // 1 min
    uint32_t status;

    while(!TMCReady && run_time < max_run_time)
    {
        status = etf_status();
        TMCReady = (status & (1 << STS_BIT_TMCReady));
        sleep(TIME_INTERVAL);
        run_time += TIME_INTERVAL;
    }
    if(!TMCReady)
    {
        print("ETF is not ready yet");
    }
    else
    {
        print("ETF is ready, run_time: %d\n", run_time);
    }
}

// Function to read etf memory
uint32_t etf_mem_read(etf_switch_t etf_mem_en)
{
    int ind = 0;
    uint32_t val, trace_size = 0, etf_size;

    uint32_t status = etf_status();
    print("ETF_status: 0x%x\n", status);
    // get the buffer fill level
    int cbuflevel = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_CBUFLEVEL_OFFSET, SECURE, "ETF_CBUFLEVEL REG");
    print("ETF_CBUFLEVEL: %d\n", cbuflevel);

    // Read RWP and RRP, it should be non-zero
    uint32_t ETF_RRP = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RRP_OFFSET, SECURE, "RRP REG");
    uint32_t ETF_RWP = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RWP_OFFSET, SECURE, "RWP REG");
    print("ETF_RRP: 0x%x, ETF_RWP: 0x%x", ETF_RRP, ETF_RWP);
    etf_size = ETF_RWP - ETF_RRP;

    // switch ON if wants to read etr memory
    if(etf_mem_en == ETF_EN)
    {
        FILE *file = fopen("ETF_formatted_trace.txt", "w");
        if(file == NULL)
        {
          perror("Failed to open file");
          return 1;
        }

        while(val != 0xffffffff && (trace_size < etf_size))
        {
            val = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RRD_OFFSET, SECURE, "RAM READ REG");
            print("ETF Trace data: 0x%x, ind: %d\n", val, ind);
            fprintf(file, "ETF Trace data: 0x%x, ind: %d\n", val, ind);
            ind++,
            trace_size++;
        }
    }
    return cbuflevel;
}

// To know the RAM Size
uint32_t get_etf_ram_size()
{
    // To know the size of etf in respective etf_mode
    uint32_t ram_size = read_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RSZ_OFFSET, SECURE, "RAM SIZE REG");

    return ram_size;
}

// Function to initialize and configure the ETF
void configure_etf(etf_mode_t etf_mode)
{
    // Disable the ETF to configure it
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_CTL_OFFSET, ETF_DISABLE, SECURE, "CTL REG");

    // Configure the ETF etf_mode(Circular Buffer Mode, Software Fifo and Hardware Fifo Mode)
    switch(etf_mode)
    {
        case ETF_CB_MODE:
            write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_MODE_OFFSET, ETF_CB_BUFFER, SECURE, "MODE REG");
            print("ETF configured to Circular Buffer etf_mode\n");
            break;

        case SWF_MODE:
            write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_MODE_OFFSET, ETF_SWF_BUFFER, SECURE, "MODE REG");
            print("ETF configured to Software Buffer etf_mode\n");
            break;

        case HWF_MODE:
            write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_MODE_OFFSET, ETF_HWF_BUFFER, SECURE, "MODE REG");
            print("ETF configured to Hardware Buffer etf_mode\n");
            break;

        default:
            print("NO ETF etf_mode is selected");
    }

    uint32_t ram_size = get_etf_ram_size();
    print("RAM Size: 0x%x\n", ram_size);

    // Write watermark level to etf watermark register
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_BUFWM_OFFSET, ETF_WATERMARK_LVL, SECURE, "BUFWM REG");

    // Set RWP and RRP to the beginning as Trace data will be routed by ETR
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RRP_OFFSET, ETF_RRP_START, SECURE, "RRP reg");
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_RWP_OFFSET, ETF_RWP_START, SECURE, "RWP reg");

    // Enale triggering to capture 32 bits words in trace memory
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_TRG_OFFSET, ETF_TRG_EN, SECURE, "TRG reg");

    // Configure Formatter Control Register
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_FFCR_OFFSET, ETF_ENFT_ENTI, SECURE, "FFCR reg");

    // Configure Periodic synchronization counter
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_PSCR_OFFSET, ETF_PSCR_CNT, SECURE, "PSCR reg");
}

void etf_switch(etf_switch_t ctrl)
{
    if(ctrl == ETF_EN)
    {
        // Enable ETF
        write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_CTL_OFFSET, ETF_ENABLE, SECURE, "CTL REG");
    }
    else
    {
        // Disable ETF
        write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_CTL_OFFSET, ETF_DISABLE, SECURE, "CTL REG");
    }
}

// Function to enable flush of trace data
void etf_manual_flush()
{
    // Configure Flush Control Register
    write_m_cs_dbg_18a(ETF_BASE_ADDR + ETF_FFCR_OFFSET, ETF_FLUSH_EN, SECURE, "FFCR reg");
}
