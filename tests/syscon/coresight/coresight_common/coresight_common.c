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
 * @file  coresight_common.c
****************************************************************************************/

#include "common_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "all_comps.h"
#include "init.h"
#include "cli.h"
#include "logger.h"
#include "srp.h"
#include "srp_vex.h"
#include "srp_status.h"
#include "coresight_common.h"

// control status register declaration for axi and apb
css600_axiap_addrblk_0_csw_reg_t csw_axi;
css600_apbap_addrblk_0_csw_reg_t csw_apb;

/*****************************************************************************************
 * Function        : configure_apb_security
 * Brief           : function to enable control status register of coresight to initiate
                     transaction through APB Bus
 * @input parameter: security_t access
 *******************************************************************************************/

void configure_apb_security(security_t access)
{
    csw_apb.value = read_reg_18a(CSS600_APBAP_ADDRBLK_0_CSW_ADR, "CSS600_APBAP_CSW");

    if(access == SECURE)
    {
        csw_apb.PROT = 1;
        write_reg_18a(CSS600_APBAP_ADDRBLK_0_CSW_ADR, csw_apb.value, CSS600_APBAP_ADDRBLK_0_CSW_WR_MASK, "CSS600_APBAP_CSW");
    }
    else if(access == NON_SECURE)
    {
        csw_apb.PROT = 3;
        write_reg_18a(CSS600_APBAP_ADDRBLK_0_CSW_ADR, csw_apb.value, CSS600_APBAP_ADDRBLK_0_CSW_WR_MASK, "CSS600_APBAP_CSW");
    }
    read_reg_18a(CSS600_APBAP_ADDRBLK_0_CSW_ADR, "CSS600_APBAP_CSW");
}

/*****************************************************************************************
 * Function        : configure_axi_security
 * Brief           : function to enable control status register of coresight to initiate
                     transaction through AXI Bus
 * @input parameter: security_t access
 *******************************************************************************************/

void configure_axi_security(security_t access)
{
    csw_axi.value = read_reg_18a(CSS600_AXIAP_ADDRBLK_0_CSW_ADR, "CSS600_AXIAP_CSW");

    if(access == SECURE)
    {
        csw_axi.PROT = 1;
        write_reg_18a(CSS600_AXIAP_ADDRBLK_0_CSW_ADR, csw_axi.value, CSS600_AXIAP_ADDRBLK_0_CSW_WR_MASK, "CSS600_AXIAP_CSW");
    }
    else if(access == NON_SECURE)
    {
        csw_axi.PROT = 3;
        write_reg_18a(CSS600_AXIAP_ADDRBLK_0_CSW_ADR, csw_axi.value, CSS600_AXIAP_ADDRBLK_0_CSW_WR_MASK, "CSS600_AXIAP_CSW");
    }

    read_reg_18a(CSS600_AXIAP_ADDRBLK_0_CSW_ADR, "CSS600_AXIAP_CSW");
}

/*********************************************************************
 *Function         : write_cs_apb_18a
 *Description      : This function writes the data to the register with
 *                   correct write address through coresight APB
 * @input parameter: uint32_t address
 *                   uint32_t write_value, char regname[]
 *********************************************************************/

void write_cs_apb_18a(uint32_t address, uint32_t write_value, char regname[])
{
    uint32_t srp_write_status = 0;

    write_reg_18a(CSS600_APBAP_ADDRBLK_0_TAR_ADR, address, CSS600_APBAP_ADDRBLK_0_TAR_WR_MASK, "TAR");
    srp_write_status = srp_dev_write32(srp, CSS600_APBAP_ADDRBLK_0_DRW_ADR, write_value);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation to register %s at address 0x%x is not successful", regname, address);
    else
        LOG_INFO("data write operation to register %s at address 0x%x is successful", regname, address);
}

/*********************************************************************
 *Function         : read_cs_apb_18a
 *Description      : This function is for reading the register at
 *                   correct address through coresight APB
 * @input parameter: uint32_t address
 *                   char regname[]
 * @return         : 0 => read is successful
 *                 : -1 => read is not successful
 *********************************************************************/

uint32_t read_cs_apb_18a(uint32_t address, uint32_t *data, char regname[])
{
    uint32_t srp_read_status = 0;
    uint32_t buffer;

    write_reg_18a(CSS600_APBAP_ADDRBLK_0_TAR_ADR, address, CSS600_APBAP_ADDRBLK_0_TAR_WR_MASK, "TAR");
    srp_read_status = srp_dev_read32(srp, CSS600_APBAP_ADDRBLK_0_DRW_ADR, &buffer);
    if(srp_read_status != SRP_ST_SUCCESS)
    {
        LOG_ERROR("data read operation from register %s at address 0x%x is not successful", regname, address);
        return -1;
    }

    *data = buffer;
    return 0;

}

/*********************************************************************
 *Function         : write_cs_axi_18a
 *Description      : This function writes the data to the register with
 *                   correct write address through coresight AXI
 * @input parameter: uint32_t address
 *                   uint32_t write_value, char regname[]
 *********************************************************************/

void write_cs_axi_18a(uint32_t address, uint32_t write_value, char regname[])
{
    uint32_t srp_write_status = 0;

    write_reg_18a(CSS600_AXIAP_ADDRBLK_0_TAR_ADR, address, CSS600_AXIAP_ADDRBLK_0_TAR_WR_MASK, "TAR");
    srp_write_status = srp_dev_write32(srp, CSS600_AXIAP_ADDRBLK_0_DRW_ADR, write_value);
    if(srp_write_status != SRP_ST_SUCCESS)
        LOG_ERROR("data write operation to register %s at address 0x%x is not successful", regname, address);
    else
        LOG_INFO("data write operation to register %s at address 0x%x is successful", regname, address);
}

/*********************************************************************
 *Function         : read_cs_axi_18a
 *Description      : This function is for reading the register at
 *                   correct address through coresight AXI
 * @input parameter: uint32_t address
 *                   char regname[]
 * @return         : 0 => read is successful
 *                  -1 => read is not successful
 *********************************************************************/

uint32_t read_cs_axi_18a(uint32_t address, uint32_t *data, char regname[])
{
    uint32_t srp_read_status = 0;
    uint32_t buffer;

    write_reg_18a(CSS600_AXIAP_ADDRBLK_0_TAR_ADR, address, CSS600_AXIAP_ADDRBLK_0_TAR_WR_MASK, "TAR");
    srp_read_status = srp_dev_read32(srp, CSS600_AXIAP_ADDRBLK_0_DRW_ADR, &buffer);
    if(srp_read_status != SRP_ST_SUCCESS)
    {
        LOG_ERROR("data read operation from register %s at address 0x%x is not successful", regname, address);
        return -1;
    }

    *data = buffer;
    return 0;
}

/*********************************************************************
 *Function         : write_m_cs_dbg_18a
 *Description      : This function initiates the write transaction
                     through APB
 * @input parameter: uint32_t address, uint32_t write_value,
 *                   security_t access, char regname[]
 * @return         : returns the error status
 *********************************************************************/

uint32_t write_m_cs_dbg_18a(uint32_t address, uint32_t write_value, security_t access, char regname[])
{
    uint32_t error_status;

    // clearing the previous error if any
    write_reg_18a(CSS600_APBAP_ADDRBLK_0_TRR_ADR, 0x1, CSS600_APBAP_ADDRBLK_0_TRR_WR_MASK, "TRR");
    configure_apb_security(access);
    write_cs_apb_18a(address, write_value, regname);

    error_status = read_reg_18a(CSS600_APBAP_ADDRBLK_0_TRR_ADR, "error response");
    if(error_status)
    {
        LOG_ERROR("write from host through APB at address:0x%x is not successful", address);
        LOG_ERROR("Transfer response: 0x%x", error_status);
    }
    else
        LOG_INFO("write from host through APB at address:0x%x is successful", address);

    return error_status;
}

/*********************************************************************
 *Function         : read_m_cs_dbg_18a
 *Description      : This function initiates the read transaction
                     through APB
 * @input parameter: uint32_t address, security_t access,
 *                   char regname[]
 * @return         : buffer => read is successful and returns
 *                             the 32 bit value read data
 *                 : -1 => read is not successful
 *********************************************************************/

uint32_t read_m_cs_dbg_18a(uint32_t address, security_t access, char regname[])
{
    uint32_t error_status;
    uint32_t buffer;

    // clearing the previous errors if any
    write_reg_18a(CSS600_APBAP_ADDRBLK_0_TRR_ADR, 0x1, CSS600_APBAP_ADDRBLK_0_TRR_WR_MASK, "TRR");
    configure_apb_security(access);
    read_cs_apb_18a(address, &buffer, regname);

    error_status = read_reg_18a(CSS600_APBAP_ADDRBLK_0_TRR_ADR, "error response");
    if(error_status)
    {
        LOG_ERROR("read from host through APB at address:0x%x is not successful", address);
        LOG_ERROR("Transfer response: 0x%x", error_status);
        return -1;
    }
    else
    {
        LOG_INFO("read from host through APB at address:0x%x is successful and data read is 0x%x", address, buffer);
        return buffer;
    }

}

/*********************************************************************
 *Function         : write_m_syscon_1_cs_dbg_18a
 *Description      : This function initiates write transaction
                     through AXI
 * @input parameter: uint32_t address, uint32_t write_value,
 *                   security_t access, char regname[]
 * @return         : returns the error status
 *********************************************************************/

uint32_t write_m_syscon_1_cs_dbg_18a(uint32_t address, uint32_t write_value, security_t access, char regname[])
{
    uint32_t error_status;

    // clearing the previous error if any
    write_reg_18a(CSS600_AXIAP_ADDRBLK_0_TRR_ADR, 0x1, CSS600_AXIAP_ADDRBLK_0_TRR_WR_MASK, "TRR");
    configure_axi_security(access);
    write_cs_axi_18a(address, write_value, regname);

    error_status = read_reg_18a(CSS600_AXIAP_ADDRBLK_0_TRR_ADR, "error response");
    if(error_status)
    {
        LOG_ERROR("write from host through AXI at address:0x%x is not successful", address);
        LOG_ERROR("Transfer response: 0x%x", error_status);
    }
    else
        LOG_INFO("write from host through AXI at address:0x%x is successful", address);

    return error_status;
}

/*********************************************************************
 *Function         : read_m_syscon_1_cs_dbg__18a
 *Description      : This function initiates reads transaction
                     through AXI
 * @input parameter: uint32_t address, security_t access
 *                   char regname[]
 * @return         : buffer => read is successful and returns
 *                             the 32 bit value read data
 *                 : -1 => read is not successful
 *********************************************************************/

uint32_t read_m_syscon_1_cs_dbg_18a(uint32_t address, security_t access, char regname[])
{
    uint32_t error_status;
    uint32_t buffer;

    // clearing the previous error if any
    write_reg_18a(CSS600_AXIAP_ADDRBLK_0_TRR_ADR, 0x1, CSS600_AXIAP_ADDRBLK_0_TRR_WR_MASK, "TRR");
    configure_axi_security(access);
    read_cs_axi_18a(address, &buffer, regname);

    error_status = read_reg_18a(CSS600_AXIAP_ADDRBLK_0_TRR_ADR, "response register");
    if(error_status)
    {
        LOG_ERROR("read from host through AXI at address:0x%x is not successful", address);
        LOG_ERROR("Transfer response: 0x%x", error_status);
        return -1;
    }
    else
    {
        LOG_INFO("read from host through AXI at address:0x%x is successful and data read is 0x%x", address, buffer);
        return buffer;
    }
}
