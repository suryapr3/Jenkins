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
 * @file    com_trax.c
 * @brief   TRAX common functions.
 * @details Controls for TRAX CPU tracing buffer.
 * @todo
 */

#include <xtensa/core-macros.h>
#include <xtensa/xdm-regs.h>

#include "com_definitions.h"
#include "com_print.h"
#include "com_static_data_table.h"
#include "com_shared_memory.h"

#define TRAX_ID_REG               XDM_TRAX_ID
#define TRAX_CONTROL_REG          XDM_TRAX_CONTROL
#define TRAX_STATUS_REG           XDM_TRAX_STATUS
#define TRAX_ADDRESS_REG          XDM_TRAX_ADDRESS
#define TRAX_DATA_REG             XDM_TRAX_DATA
#define TRAX_TRIGGER_PC_REG       XDM_TRAX_TRIGGER
#define TRAX_PC_MATCH_CONTROL_REG XDM_TRAX_MATCH


#define GET_PCMS_BIT           (31)
// See also xtensa/traxreg.h

//! @brief bitfield structure of register TRAX_ID_REG (0x0).
typedef union {
    struct
    {
        uint32_t TRAX_ID_CFGID : 16; // Configuration ID. To the extent possible, the value of this field is unique for each possible
                                     // configuration of the TRAX unit.

        uint32_t TRAX_ID_STDCFG : 1; // Set if it is a Tensilica Standard configuration. Clear if custom-configured by the customer.
        uint32_t TRAX_ID_MINVER : 3; // Minor version number. New minor versions are intended to be backward compatible. Starts at zero. For
                                     // example, for version 2.0, MINVER is 0.
        uint32_t TRAX_ID_MAJVER : 4; // Major version number. New major versions are generally not backward compatible. Starts at one. Zero
                                     // value is reserved. For example, for version 2.0, MAJVER is 2.

        uint32_t TRAX_ID_PRODOPT : 4; // Product specific options.
        uint32_t TRAX_ID_PRODNO : 4;  // Product number (identifies device class/type). 0 = TRAX-PC
    };
    uint32_t value;
} trax_id_reg_t;

//! @brief bitfield structure of register TRAX_CONTROL_REG (0x1).
typedef union {
    struct
    {
        uint32_t TRAX_CONTROL_TREN : 1;   // Setting this bit enables writing to the TraceRAM.
        uint32_t TRAX_CONTROL_TRSTP : 1;  // Trace stop.
        uint32_t TRAX_CONTROL_PCMEN : 1;  // PC match causes Stop trigger.
        uint32_t : 1;                     // reserved;
        uint32_t TRAX_CONTROL_PTIEN : 1;  // PTI causes Stop trigger (level-sensitive).
        uint32_t TRAX_CONTROL_CTIEN : 1;  // CTI causes Stop trigger (level-sensitive).
        uint32_t : 1;                     // reserved;
        uint32_t TRAX_CONTROL_TMEN : 1;   // TraceRAM enable. Enables local trace memory.
        uint32_t : 1;                     // reserved;
        uint32_t TRAX_CONTROL_CNTU : 1;   // Selects what is counted by the countdown register DelayCount.
        uint32_t : 1;                     // reserved;
        uint32_t TRAX_CONTROL_TSEN : 1;   // Enables embedding timestamp information in TRAX messages.
        uint32_t TRAX_CONTROL_SMPER : 3;  // Synchronization message period
        uint32_t : 1;                     // reserved;
        uint32_t TRAX_CONTROL_PTOWT : 1;  // Processor Trigger Output (PTO) is enabled when stop triggered
        uint32_t TRAX_CONTROL_PTOWS : 1;  // Processor Trigger Output (PTO) is enabled when trace stop completes
        uint32_t : 2;                     // reserved;
        uint32_t TRAX_CONTROL_CTOWT : 1;  // Cross-Trigger Output (CTO) is enabled when stop triggered
        uint32_t TRAX_CONTROL_CTOWS : 1;  // Cross-Trigger Output (CTO) is enabled when trace stop completes
        uint32_t TRAX_CONTROL_ITCTO : 1;  // Integration Mode Cross Trigger output.
        uint32_t TRAX_CONTROL_ITCTIA : 1; // Integration Mode Cross Trigger input acknowledge.
        uint32_t TRAX_CONTROL_ATID : 7;   // ATB source ID
        uint32_t TRAX_CONTROL_ATEN : 1;   // ATB Enable, when set trace info is sent out on the ATB interface.
    };
    uint32_t value;
} trax_control_reg_t;

//! @brief bitfield structure of register TRAX_STATUS_REG (0x2).
typedef union {
    struct
    {
        uint32_t TRAX_STATUS_TRACT : 1;
        uint32_t TRAX_STATUS_TRIG : 1;
        uint32_t TRAX_STATUS_PCMTG : 1;
        uint32_t TRAX_STATUS_PJTR : 1;
        uint32_t TRAX_STATUS_PTITG : 1;
        uint32_t TRAX_STATUS_CTITG : 1;
        uint32_t : 2; // reserved;

        uint32_t TRAX_STATUS_MEMSZ : 5;
        uint32_t : 3; // reserved;

        uint32_t TRAX_STATUS_PTO : 1;
        uint32_t TRAX_STATUS_CTO : 1;
        uint32_t : 4;                    // reserved;
        uint32_t TRAX_STATUS_ITCTOA : 1; // For 3.0
        uint32_t TRAX_STATUS_ITCTI : 1;  // For 3.0

        uint32_t TRAX_STATUS_ITATR : 1; // For 3.0
        uint32_t : 7;                   // reserved;
    };
    uint32_t value;
} trax_status_reg_t;

//! @brief bitfield structure of register TRAX_ADDR_REG (0x2).
typedef union {
    struct
    {
        uint32_t TRAX_ADDRESS_TADDR : 8;  // MEMSZ - 2 = 512b = 10b addr - 2  = 8
        uint32_t : 13;                    // 21 - 8 = 13, reserved;
        uint32_t TRAX_ADDRESS_TWRAP : 10; //
        uint32_t TRAX_ADDRESS_TWSAT : 1;
    };
    uint32_t value;
} trax_address_reg_t;

//! @brief bitfield structure of register MISC_PWRSTAT (0x58).
typedef union {
    struct
    {
        uint32_t PWRSTAT_REG_CORE_DOMAIN_ON : 1;
        uint32_t PWRSTAT_REG_WAKEUP_RESET : 1;
        uint32_t PWRSTAT_REG_CACHES_LOST_POWER : 1;
        uint32_t : 1;
        uint32_t PWRSTAT_REG_CORE_STILL_NEEDED : 1;
        uint32_t : 3;
        uint32_t PWRSTAT_REG_MEM_DOMAIN_ON : 1;
        uint32_t : 3;
        uint32_t PWRSTAT_REG_DEBUG_DOMAIN_ON : 1;
        uint32_t : 15;
        uint32_t PWRSTAT_REG_DEBUG_WAS_RESET : 1;
        uint32_t : 3;
    };
    uint32_t value;
} pwrstat_reg_t;

//! @brief bitfield structure of register MISC_PWRCTL (0x59).
typedef union {
    struct
    {
        uint32_t PWRCTL_REG_CORE_SHUTOFF : 1;
        uint32_t : 7;
        uint32_t PWRCTL_REG_MEM_WAKEUP : 1;
        uint32_t : 3;
        uint32_t PWRCTL_REG_DEBUG_WAKEUP : 1;
        uint32_t : 15;
        uint32_t PWRCTL_REG_DEBUG_RESET : 1;
        uint32_t : 3;
    };
    uint32_t value;
} pwrctl_reg_t;

/**
 * @brief Function to write a value into a TRAX register
 *
 * @param [in] regno   The register number to be written
 * @param [in[ value   The value to be written at that register location
 *
 */

INTRINSIC_ALWAYS_INLINE static void com_trax_write_register (uint32_t const regno, uint32_t const value);
static uint32_t trax_initialized = 0;

/**
 * @brief Function to read a TRAX register
 *
 * @param [in] regno  The register number to be read (APB, not ERI addressed: valid range 0x0 - 0xFFF)
 * @param [out] data  Location where the read value is kept
 */
INTRINSIC_ALWAYS_INLINE static void com_trax_read_register (uint32_t *const data, uint32_t const regno)
{
    uint32_t const address = XDM_APB_TO_ERI (regno);
    *data = XTHAL_RER (address);
    FW_PRINT (FW_DEBUG, "COM_TRAX_READ_REGISTER:  [Address] 0x%x => [Data] 0x%x", regno, *data);
}

/**
 * @brief Function to write a value into a register
 *
 * @param [in] regno  : The register number to be written
 * @param [in] value  : The value to be written at that register location
 *
 */
INTRINSIC_ALWAYS_INLINE static void com_trax_write_register (uint32_t const value, uint32_t const regno)
{
    uint32_t const address = XDM_APB_TO_ERI (regno);
    XTHAL_WER (address, value);
    FW_PRINT (FW_DEBUG, "COM_TRAX_WRITE_REGISTER: [Address] 0x%x <= [Data] 0x%x", regno, value);
}

/**
 * @brief Function to read a value from TRAX memory.
 *
 * @param [in] addr     The memory address/index to read.
 * @return              The value at that address.
 *
 */
static uint32_t com_trax_read_memory (uint32_t const addr)
{
    com_trax_write_register (addr, TRAX_ADDRESS_REG);
    uint32_t data;
    com_trax_read_register (&data, TRAX_DATA_REG);
    return (data);
}

/**
 * @brief Initialize the TRAX hardware for recording to memory, enable clocks, reset, etc.
 *
 */
void com_trax_init (void)
{
    // if (0 == get_tf(SR_BOOT_CONFIG_LUT, 0, SR_TRAX_EN))
    //{
    //  FW_PRINT(FW_DEBUG,"TRAX disabled in SRAM");
    //  return;
    //}

    // Turn on debug power domain (if split) and wait for PON.
    pwrctl_reg_t pwrctl = {.value = 0};
    pwrctl.PWRCTL_REG_DEBUG_WAKEUP = 1;
    com_trax_write_register (pwrctl.value, XDM_MISC_PWRCTL);
    INTRINSIC_RSYNC;

    pwrstat_reg_t pwrstat = {.value = 0};
    com_trax_read_register (&pwrstat.value, XDM_MISC_PWRSTAT);

    int count = 10;
    while ((0 == pwrstat.PWRSTAT_REG_DEBUG_DOMAIN_ON) && (0 < count))
    {
        com_trax_read_register (&pwrstat.value, XDM_MISC_PWRSTAT);
        count--;
    }

    // Reset Debug logic.
    pwrctl.PWRCTL_REG_DEBUG_RESET = 1;
    com_trax_write_register (pwrctl.value, XDM_MISC_PWRCTL);
    INTRINSIC_RSYNC;

    for (int i = 0; i < 10; i++) INTRINSIC_NOP;

    // Reset Debug logic.
    pwrctl.PWRCTL_REG_DEBUG_RESET = 0;
    com_trax_write_register (pwrctl.value, XDM_MISC_PWRCTL);
    INTRINSIC_RSYNC;

    for (int i = 0; i < 10; i++) INTRINSIC_NOP;

    uint32_t const trigger_pc = get_tf (com_trax_addr_config_lut, 0, trax_trigger_pc);
    uint32_t pc_match_control = 0;
    uint32_t pcml = get_tf (com_trax_addr_config_lut, 0, trax_stop_pcml);
    uint32_t pcms = get_tf (com_trax_addr_config_lut, 0, trax_stop_pcms);
    pc_match_control = pcml;
    if (pcms)
    {
        pc_match_control = pcms << GET_PCMS_BIT | pcml;
    }
    com_trax_write_register (trigger_pc, TRAX_TRIGGER_PC_REG);
    com_trax_write_register (pc_match_control, TRAX_PC_MATCH_CONTROL_REG);

    trax_control_reg_t trax_control = {.value = 0};

    trax_control.TRAX_CONTROL_PCMEN = get_tf (com_trax_addr_config_lut, 0, trax_ctrl_pcmen);
    trax_control.TRAX_CONTROL_ATEN = 0;  // ATB interface disable.
    trax_control.TRAX_CONTROL_TMEN = 1;  // TraceRAM enable. Enables local trace memory.
    trax_control.TRAX_CONTROL_SMPER = 4; // 1 every 32

    com_trax_write_register (trax_control.value, TRAX_CONTROL_REG);

    trax_initialized = 1;
}

/**
 * @brief Stop a running TRAX trace.
 *
 */
int com_trax_stop (void)
{
    if (0 == trax_initialized)
    {
        FW_PRINT (FW_WARN, "TRAX stop called without initialize");
        return 0;
    }

    /* First check if trace if active. If not, nothing to halt */
    trax_status_reg_t trax_status;
    com_trax_read_register ((uint32_t *)&trax_status.value, TRAX_STATUS_REG);
    FW_PRINT (FW_INFO, "Trace StoPPp");
    if (0 == trax_status.TRAX_STATUS_TRACT)
    {
        FW_PRINT (FW_INFO, "Trace is already halted");
        return 0;
    }

    /* Trace is indeed active */
    trax_control_reg_t trax_control;
    com_trax_read_register ((uint32_t *)&trax_control.value, TRAX_CONTROL_REG);

    /*  Stop Tracing:  */
    trax_control.TRAX_CONTROL_TRSTP = 1;
    com_trax_write_register (trax_control.value, TRAX_CONTROL_REG);

    return 1;
}

/**
 * @brief Start the TRAX trace.
 *
 */
void com_trax_start (void)
{
    FW_PRINT (FW_DEBUG, "TRAX start()...");
    if (0 == trax_initialized)
    {
        FW_PRINT (FW_WARN, "TRAX start called without initialize");
        return;
    }

    /*  Make sure that the trace is not already active:  */
    trax_status_reg_t trax_status;
    com_trax_read_register ((uint32_t *)&trax_status.value, TRAX_STATUS_REG);

    if (0 != trax_status.TRAX_STATUS_TRACT)
    {
        /* Trace is already active */
        return;
    }

    trax_control_reg_t trax_control;
    com_trax_read_register ((uint32_t *)&trax_control.value, TRAX_CONTROL_REG);

    /*  Clear the Enable bit to ensure 0-1 transition:  */
    trax_control.TRAX_CONTROL_TREN = 0;
    com_trax_write_register (trax_control.value, TRAX_CONTROL_REG);

    /*  Finally, enable trace:  */
    trax_control.TRAX_CONTROL_TREN = 1;
    com_trax_write_register (trax_control.value, TRAX_CONTROL_REG);
}

/**
 * @brief Start the TRAX trace.
 *
 * @param [out] p_trax_lut   The location to store the TRAX data.
 */
static void com_trax_read_core_data (uint32_t *const p_trax_lut)
{
    FW_PRINT (FW_WARN, "Read TRAX memory:core %d, addr: 0x%x", RCS_CPU, U32 (p_trax_lut));

    // add some magic numbers to indicate start of TRAX header in SRAM
    uint8_t const core_ID = (U8 (RCS_CPU << 4) & 0xF0);
    p_trax_lut[0] = 0xDDDA0000 + core_ID;
    // copy TRAX header
    FW_PRINT (FW_DEBUG, "Read TRAX memory: Header");
    for (uint32_t idx = 0; idx < TRAX_HEADER_SIZE_WORDS; idx++)
    {
        uint32_t reg_data = 0;
        com_trax_read_register (&reg_data, idx << 2);
        p_trax_lut[idx + 1] = reg_data;
    }

    FW_PRINT (FW_DEBUG, "Read TRAX memory: Data");

    // If TWRAP and TWSAT fields are all zero, the captured trace consists of all TraceRAM words
    // from index zero up to index TADDR-1, inclusive.
    trax_address_reg_t com_trax_address;
    com_trax_read_register ((uint32_t *)&com_trax_address.value, TRAX_ADDRESS_REG);
    uint32_t const taddr = com_trax_address.TRAX_ADDRESS_TADDR;
    uint32_t start = 0;
    uint32_t end = (taddr == 0 ? TRAX_MEM_SIZE_WORDS : taddr) - 1;

    // Otherwise the captured trace consists of TraceRAM words from index TADDR to the end, followed by
    // words from the start of TraceRAM up to index TADDR-1, inclusive
    if ((0 != com_trax_address.TRAX_ADDRESS_TWRAP) || (0 != com_trax_address.TRAX_ADDRESS_TWSAT))
    {
        start = taddr;
        end = start + TRAX_MEM_SIZE_WORDS - 1;
    }
    uint32_t idx_dst = TRAX_HEADER_SIZE_WORDS; // First word is indicator, not part of header.

    for (uint32_t idx = start; idx < end; idx++)
    {
        uint32_t const reg_data = com_trax_read_memory (idx % TRAX_MEM_SIZE_WORDS);
        p_trax_lut[idx_dst] = reg_data;
        idx_dst++;
    }
}

/**
 * @brief Store the TRAX trace to reserved memory.
 *
 */
void com_trax_store_trace (void)
{
    FW_PRINT (FW_DEBUG, "TRAX store trace to SRAM...");

    uint32_t *p_trax_lut = &p_system_data->trax_lut[RCS_CPU * TRAX_LUT_SIZE_WORDS];

    if (0 == trax_initialized)
    {
        FW_PRINT (FW_DEBUG, "TRAX store trace called without initialize!");
        return;
    }

    com_trax_read_core_data (p_trax_lut);
}
