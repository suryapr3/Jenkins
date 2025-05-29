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
 * @file  common_funtions.c
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
#include "common_functions.h"

//Global definitions
char g_compile_time[] = "Compiled: " __DATE__" "__TIME__;
char g_abc_build_name[25] = "ABC_BUILD_UNKNOWN";
char g_abc_build_rtl[75] = "ABC_UNKNOWN_RTL";
int g_abc_build_version;

srp_hdl_t srp_hdl = NULL;

frio_build_t abc_frio_builds[] =
{
    { ABC_18A_0P8_0_1,  "ABC_18A_0P8_0_1",  "abc_soc-srvrgen4-z0_24ww16a" },
    { ABC_18A_0P8_0_2,  "ABC_18A_0P8_0_2",  "abc_soc-srvrgen4-z0_24ww16a" },
    { ABC_18A_0P8_0_3,  "ABC_18A_0P8_0_3",  "abc_soc-srvrgen4-z0_24ww16a" },
    { ABC_18A_0P8_0_4,  "ABC_18A_0P8_0_4",  "abc_soc-srvrgen4-z0_24ww16a" },
    { ABC_18A_0P8B_0_1, "ABC_18A_0P8B_0_1", "abc_soc-srvrgen4-z0_24ww29b" },
    { ABC_18A_0P8B_0_2, "ABC_18A_0P8B_0_2", "abc_soc-srvrgen4-z0_24ww29b" }
    // This list will grow as and when a new FRIO release comes up
};

/***********************************************************************************
 * @function       : abc_platform_detect()
 * @brief          : Function to detect the ABC FRIO platform details.
 * @param [in]     : void
 * @return         : status
 ***********************************************************************************/

int abc_platform_detect(void)
{
    char buf[20], ver[12], temp[12], rtl[50], name[25];
    FILE *fptr;
    int len, digit, version, found, i;
    int version_supported = 0;

    fptr = popen("/p/frio/tools/frioPciRead -F s7a3 -P 0x10", "r");
    for(i = 0; (fgets(buf, sizeof(buf), fptr)) != NULL; i++)
    {
        if(1 == i) strcpy(temp, buf);
    }
    pclose(fptr);

    for(i = 3; temp[i] != '\0'; i++)                       // skip first three characters by starting loop count (i) from 3
    {
        ver[i - 3] = temp[i];

        if(i == 10) break;                                 // HACK: 0p8 onwards, this loop is not getting exited.
                                                           //       May be due to missing \0 at the end, so force exit here
                                                           //       Total chars = 3 starting chars plus 8 digits = 11 (0-10)
    }
    ver[8] = '\0';
    len = strlen(ver);
    for(i = 0; i < len; i++)
    {
        digit = ver[i] - '0';                              // convert char to integer
        version = (version * 16) + digit;
    }

    found = 0;
    strcpy(rtl,  "UNKNOWN_RTL");
    strcpy(name, "UNKNOWN_BUILD");
    for(i = 0; i < ARRAY_SIZE(abc_frio_builds); i++)
    {
        if(version == abc_frio_builds[i].release_version)
        {
            found = 1;
            strcpy(name, abc_frio_builds[i].release_name);
            strcpy(rtl, abc_frio_builds[i].rtl_version);
        }
        if(found) break;
    }

    g_abc_build_version = version;
    strcpy(g_abc_build_name, name);
    strcpy(g_abc_build_rtl, rtl);
    LOG_PRINT("HOST: ABC FRIO build version: 0x%x (BUILD: %s) (RTL: %s)\n", g_abc_build_version, g_abc_build_name, g_abc_build_rtl);

    version_supported = ((version == ABC_18A_0P8_0_1) || (version == ABC_18A_0P8_0_2) || (version == ABC_18A_0P8_0_3) ||
                         (version == ABC_18A_0P8_0_4) || (version == ABC_18A_0P8B_0_1) || (version == ABC_18A_0P8B_0_2));
                                                           // Support withdrawn for the previous builds
    if(!version_supported)
    {
        LOG_ERROR("No support running tests on %s build\n", g_abc_build_name);
        return -1;
    }

    return 0;

}

/************************************************************************************
 * Function    : vha_reset()
 * Input args  : vha_num   = the VHA instance (0 to 7) to be RESETed.
 *             : reset     = 0 means to take out of RESET, = 1 means to keep in RESET
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to handle the resetting of VHA instances
 **********************************************************************************/

uint32_t vha_reset(uint32_t vha_num, reset_assert_active_high reset)
{
    // VHA reset from CAR has been removed from the design from 0p6 RTL onwards.
    // So, this is just a dummy function, which may get implemented in future.

    return 0;
}

/*****************************************************************************************************
 * Function    : vha_clock_config()
 * Input args  : vha_num = the VHA instance whose clocks need to be configured.
 *             : config  = a 32 bit value, whose bit positions determine the clocks to be configured.
 * Output args : return value of the regiter writes.
 * Brief       : From 0p6 RTL onwards, the VHA clocks are disabled by default. This routine is to
 *               enable various clocks of the VHA.
 *
 ******************************************************************************************************/

int vha_clock_config(uint32_t vha_num, uint32_t config)
{
    uint64_t base_addr;
    uint32_t reg_val, rv;

    rv = SUCCESS;
    base_addr = VHA0_BASE + (vha_num * 0x20000);
    reg_val = read_reg_18a(VHA_CFG_ADR(base_addr), "VHA_CFG");
    LOG_INFO("VHA_CFG for VHA%d is %x\n", vha_num, reg_val);

    LOG_INFO("Will update VHA_CFG to %x to enable the clocks\n", config);
    if(rv = write_reg_18a(VHA_CFG_ADR(base_addr), config, VHA_CFG_WR_MASK, "VHA_CFG"));
        return rv;

    reg_val = read_reg_18a(VHA_CFG_ADR(base_addr), "VHA_CFG");
    LOG_INFO("VHA_CFG for VHA%d after writing is %x\n", vha_num, reg_val);

    if(reg_val != config)
    {
        LOG_ERROR("Tried to configure VHA_CFG to %x, but it is getting set to %x\n"
                  "Exiting...\n", config, reg_val);
        return FAILURE;
    }

    return rv;

}

/**********************************************************************************************
 * Function    : v2d_reset()
 * Input args  : v2d_num   = the V2D instance (0 to 7) to be reset.
 *             : reset     = 0 means to take out of RESET, = 1 means to keep in RESET
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to handle the resetting of V2D instances
 ***********************************************************************************************/

uint32_t v2d_reset(v2d_instance_t v2d_num, reset_assert_active_high reset)
{
    // V2D reset from CAR has been removed from the design from 0p6 RTL onwards.
    // So, this is just a dummy function, which may get implemented in future.

    return 0;
}

/**********************************************************************************************
 * Function    : vex_reset_cycle()
 * Input args  : void
 * Output args : error
 * Brief       : this funtion is used to handle the resetting of VEX
 ***********************************************************************************************/
uint32_t vex_reset_cycle (void)
{
    uint32_t error=0;
    uint32_t read_data;

    LOG_INFO("Asserting the reset and disabling the CLKs\n");

    error = write_reg_18a(CAR_CLK_DIS0_ADR,0xFFFFFFFF, 0xFFFFFFFF,"car_CLK_disable0");  //0x02408000 -> 0xffffffff
    read_data = read_reg_18a(CAR_CLK_DIS0_ADR,"car_CLK_disable0");

    error = write_reg_18a(CAR_CLK_DIS1_ADR,0xFF, 0xFFFFFFFF,"car_CLK_disable1");        //0x02408004 -> 0xff
    read_data = read_reg_18a(CAR_CLK_DIS1_ADR,"car_CLK_disable1");

    error = write_reg_18a(CAR_SOFT_RST0_ADR,0x00000000, 0xFFFFFFFF,"car_soft_reset0");        //0x02408008 -> 0x00000000
    read_data = read_reg_18a(CAR_SOFT_RST0_ADR,"car_soft_reset0");

    error = write_reg_18a(CAR_SOFT_RST1_ADR,0x00, 0xFFFFFFFF,"car_soft_reset1");              //0x240800C -> 0x00
    read_data = read_reg_18a(CAR_SOFT_RST1_ADR,"car_soft_reset1");

    LOG_INFO("Deasserting the reset and enabling the CLKs\n");

    error = write_reg_18a(CAR_CLK_DIS0_ADR,0x00000000, 0xFFFFFFFF,"car_CLK_disable0");        //0x02408000 -> 0x00000000
    read_data = read_reg_18a(CAR_CLK_DIS0_ADR,"car_CLK_disable0");

    error = write_reg_18a(CAR_CLK_DIS1_ADR,0x00, 0xFFFFFFFF,"car_CLK_disable1");              //0x02408004 -> 0x00
    read_data = read_reg_18a(CAR_CLK_DIS1_ADR,"car_CLK_disable1");

    error = write_reg_18a(CAR_SOFT_RST0_ADR,0xFFFFFFFF, 0xFFFFFFFF,"car_soft_reset0");        //0x02408008 -> 0xffffffff
    read_data = read_reg_18a(CAR_SOFT_RST0_ADR,"car_soft_reset0");

    error = write_reg_18a(CAR_SOFT_RST1_ADR,0x000000FF, 0xFFFFFFFF,"car_soft_reset1");        //0x0240800c -> 0xff
    read_data = read_reg_18a(CAR_SOFT_RST1_ADR,"car_soft_reset1");

    read_data = read_reg_18a(CAR_VEX_RST_RELEASE0_ADR,"car_mem_car_vex_reset_release0");      // 0x02408080
    read_data = read_reg_18a(CAR_VEX_RST_RELEASE1_ADR,"car_mem_car_vex_reset_release1");      // 0x02408084

    return error;
}

/*************************************************************************************
 * Function    : subsys_reset_cycle()
 * Brief       : this funtion is used to assert and de-assert the reset of the sub-systems
 * To-do       : function needs to be updated for individual subsystem reset control
 *************************************************************************************/

void subsys_reset_cycle (void)
{
    uint32_t error = 0;
    uint32_t read_data;

    LOG_INFO("Asserting the reset of subsystems from sys con\n");
    error = write_reg_18a(SYS_CTRL_RST_CTRL_ADR, 0x00000000, 0xFFFFFFFF, "reset_control");     //0x01E10010
    read_data = read_reg_18a(SYS_CTRL_RST_CTRL_ADR, "reset_control");

    LOG_INFO("Deasserting the reset of subsystems from sys con\n");
    error += write_reg_18a(SYS_CTRL_RST_CTRL_ADR, 0xFFFFFFFF, 0xFFFFFFFF, "reset_control");    //0x01E10010
    read_data = read_reg_18a(SYS_CTRL_RST_CTRL_ADR, "reset_control");

}

/*************************************************************************************
 * Function    : cold_reset_cycle()
 * Brief       : this funtion is used to reset the system to default value
 *************************************************************************************/

void cold_reset_cycle(void)
{
    uint32_t error = 0;
    uint32_t read_data;

    LOG_INFO("Asserting the reset of subsystems from sys con\n");
    error = write_reg_18a(SYS_CTRL_SYS_CTRL_ADR,0xa0000000, 0xf00307f1,"system_control");       //0x01e10008
    read_data = read_reg_18a(SYS_CTRL_SYS_CTRL_ADR,"system_control");
}

/*************************************************************************************
 * Function    : crux_reset_cycle()
 * Brief       : this funtion is used to reset the crux using car registers
 *************************************************************************************/
void crux_reset_cycle (void)
{
    uint32_t error = 0;
    uint32_t read_data;

    LOG_INFO("Asserting the reset of CRUX from CAR registers\n");

    error += write_reg_18a(CAR_NOC_CLK_GATE_ADR, 0x1, 0x1,"abc_noc_CLK disable");               //0x02408094
    read_data = read_reg_18a(CAR_NOC_CLK_GATE_ADR,"abc_noc_CLK disable");

    error += write_reg_18a(CAR_NOC_SOFT_RST_ADR,0X1, 0x1,"abc_noc_CLK_disable");                //0x02408098
    read_data = read_reg_18a(CAR_NOC_SOFT_RST_ADR,"abc_noc_CLK disable");

    LOG_INFO("Deasserting the reset of CRUX from CAR registers\n");

    error += write_reg_18a(CAR_NOC_CLK_GATE_ADR, 0x0, 0x1,"abc_noc_CLK disable");               //0x02408094 -> 0x0
    read_data = read_reg_18a(CAR_NOC_CLK_GATE_ADR,"abc_noc_CLK disable");

    error += write_reg_18a(CAR_NOC_SOFT_RST_ADR, 0x0, 0x1,"abc_noc_soft_reset");                //0x02408098 -> 0x0
    read_data = read_reg_18a(CAR_NOC_SOFT_RST_ADR,"abc_noc_soft_reset");

}
/*************************************************************************************
 * Function    : reenable_pcie_after_sys_reset()
 * Brief       : This funtion is used to reenable pcie after system reset
 *************************************************************************************/
void reenable_pcie_after_sys_reset (void)
{
         system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0x8");
         system("/p/frio/tools/frioPciWrite -F s6b3 -P 0x20000 0x9");
         system ("srpBusSelect -s spi");
         writeReg(0x01e10010, 0xffffffff, 0xffffffff);
         writeReg(0x01b01044, 0x00000001, 0x1);
         system ("srpBusSelect -s pci");

}
/*************************************************************************************
 * Function    : vex_mem_clear()
 * Input args  : vex_num   = the VEX instance (0 to 39) whose memories to be cleared.
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to clear the vector memory and data memory of
 *               a VEX dev.
 *************************************************************************************/

uint32_t vex_mem_clear(uint32_t vex_num, void *srp)
{
    char srpCommand[100];

    uint32_t vmem_base_addr[40] = {
        VEXABC0_VMEM_VE32_SIMD0_BASE, VEXABC1_VMEM_VE32_SIMD0_BASE, VEXABC2_VMEM_VE32_SIMD0_BASE, VEXABC3_VMEM_VE32_SIMD0_BASE,
        VEXABC4_VMEM_VE32_SIMD0_BASE, VEXABC5_VMEM_VE32_SIMD0_BASE ,VEXABC6_VMEM_VE32_SIMD0_BASE ,VEXABC7_VMEM_VE32_SIMD0_BASE,
        VEXABC8_VMEM_VE32_SIMD0_BASE , VEXABC9_VMEM_VE32_SIMD0_BASE, VEXABC10_VMEM_VE32_SIMD0_BASE , VEXABC11_VMEM_VE32_SIMD0_BASE ,
        VEXABC12_VMEM_VE32_SIMD0_BASE , VEXABC13_VMEM_VE32_SIMD0_BASE ,VEXABC14_VMEM_VE32_SIMD0_BASE ,VEXABC15_VMEM_VE32_SIMD0_BASE  ,
        VEXABC16_VMEM_VE32_SIMD0_BASE ,VEXABC17_VMEM_VE32_SIMD0_BASE ,VEXABC18_VMEM_VE32_SIMD0_BASE , VEXABC19_VMEM_VE32_SIMD0_BASE ,
        VEXABC20_VMEM_VE32_SIMD0_BASE , VEXABC21_VMEM_VE32_SIMD0_BASE  , VEXABC22_VMEM_VE32_SIMD0_BASE , VEXABC23_VMEM_VE32_SIMD0_BASE ,
        VEXABC24_VMEM_VE32_SIMD0_BASE  , VEXABC25_VMEM_VE32_SIMD0_BASE , VEXABC26_VMEM_VE32_SIMD0_BASE , VEXABC27_VMEM_VE32_SIMD0_BASE ,
        VEXABC28_VMEM_VE32_SIMD0_BASE , VEXABC29_VMEM_VE32_SIMD0_BASE ,VEXABC30_VMEM_VE32_SIMD0_BASE ,VEXABC31_VMEM_VE32_SIMD0_BASE ,
        VEXABC32_VMEM_VE32_SIMD0_BASE , VEXABC33_VMEM_VE32_SIMD0_BASE , VEXABC34_VMEM_VE32_SIMD0_BASE , VEXABC35_VMEM_VE32_SIMD0_BASE,
        VEXABC36_VMEM_VE32_SIMD0_BASE , VEXABC37_VMEM_VE32_SIMD0_BASE ,VEXABC38_VMEM_VE32_SIMD0_BASE , VEXABC39_VMEM_VE32_SIMD0_BASE

        };

    uint32_t dmem_base_addr[40] = {VEXABC0_DMEM_VE32_BP_CFG_BASE,VEXABC1_DMEM_VE32_BP_CFG_BASE,VEXABC2_DMEM_VE32_BP_CFG_BASE,
        VEXABC3_DMEM_VE32_BP_CFG_BASE,VEXABC4_DMEM_VE32_BP_CFG_BASE,VEXABC5_DMEM_VE32_BP_CFG_BASE,VEXABC6_DMEM_VE32_BP_CFG_BASE,
        VEXABC7_DMEM_VE32_BP_CFG_BASE,VEXABC8_DMEM_VE32_BP_CFG_BASE,VEXABC9_DMEM_VE32_BP_CFG_BASE,VEXABC10_DMEM_VE32_BP_CFG_BASE,
        VEXABC11_DMEM_VE32_BP_CFG_BASE,VEXABC12_DMEM_VE32_BP_CFG_BASE,VEXABC13_DMEM_VE32_BP_CFG_BASE,VEXABC14_DMEM_VE32_BP_CFG_BASE,
        VEXABC15_DMEM_VE32_BP_CFG_BASE,VEXABC16_DMEM_VE32_BP_CFG_BASE,VEXABC17_DMEM_VE32_BP_CFG_BASE,VEXABC18_DMEM_VE32_BP_CFG_BASE,
        VEXABC19_DMEM_VE32_BP_CFG_BASE,VEXABC20_DMEM_VE32_BP_CFG_BASE,VEXABC21_DMEM_VE32_BP_CFG_BASE,VEXABC22_DMEM_VE32_BP_CFG_BASE,
        VEXABC23_DMEM_VE32_BP_CFG_BASE,VEXABC24_DMEM_VE32_BP_CFG_BASE,VEXABC25_DMEM_VE32_BP_CFG_BASE,VEXABC26_DMEM_VE32_BP_CFG_BASE,
        VEXABC27_DMEM_VE32_BP_CFG_BASE,VEXABC28_DMEM_VE32_BP_CFG_BASE,VEXABC29_DMEM_VE32_BP_CFG_BASE,VEXABC30_DMEM_VE32_BP_CFG_BASE,
        VEXABC31_DMEM_VE32_BP_CFG_BASE,VEXABC32_DMEM_VE32_BP_CFG_BASE,VEXABC33_DMEM_VE32_BP_CFG_BASE,VEXABC34_DMEM_VE32_BP_CFG_BASE,
        VEXABC35_DMEM_VE32_BP_CFG_BASE,VEXABC36_DMEM_VE32_BP_CFG_BASE,VEXABC37_DMEM_VE32_BP_CFG_BASE,VEXABC38_DMEM_VE32_BP_CFG_BASE,
        VEXABC39_DMEM_VE32_BP_CFG_BASE


    };

    sprintf(srpCommand, "srpRamTest -s 16KB -W 0x%x 0", dmem_base_addr[vex_num]);
    system(srpCommand);

    sprintf(srpCommand, "srpRamTest -s 64KB -W 0x%x 0", vmem_base_addr[vex_num]);
    system(srpCommand);

    return 0;

}

/*
 * Function    : vex_wait()
 * Input args  : vex_num   = the VEX instance (0 to 39) whose status has to be checked
 * Output args : return value of the status of the VEX Core
 * Brief       : this funtion is used to check whether VEX Core is ready
 */

uint32_t vex_wait(uint32_t vexCoreId)
{
    uint32_t  rv, status_data,flags= 0x0;
    uint32_t cell_addr[40] = {
        VEXABC0_SC_VE32_CELL_BASE,VEXABC1_SC_VE32_CELL_BASE,VEXABC2_SC_VE32_CELL_BASE,VEXABC3_SC_VE32_CELL_BASE,
        VEXABC4_SC_VE32_CELL_BASE,VEXABC5_SC_VE32_CELL_BASE,VEXABC6_SC_VE32_CELL_BASE,VEXABC7_SC_VE32_CELL_BASE,
        VEXABC8_SC_VE32_CELL_BASE,VEXABC9_SC_VE32_CELL_BASE,VEXABC10_SC_VE32_CELL_BASE,VEXABC11_SC_VE32_CELL_BASE,
        VEXABC12_SC_VE32_CELL_BASE,VEXABC13_SC_VE32_CELL_BASE,VEXABC14_SC_VE32_CELL_BASE,VEXABC15_SC_VE32_CELL_BASE,
        VEXABC16_SC_VE32_CELL_BASE,VEXABC17_SC_VE32_CELL_BASE,VEXABC18_SC_VE32_CELL_BASE,VEXABC19_SC_VE32_CELL_BASE,
        VEXABC20_SC_VE32_CELL_BASE,VEXABC21_SC_VE32_CELL_BASE,VEXABC22_SC_VE32_CELL_BASE,VEXABC23_SC_VE32_CELL_BASE,
        VEXABC24_SC_VE32_CELL_BASE,VEXABC25_SC_VE32_CELL_BASE,VEXABC26_SC_VE32_CELL_BASE,VEXABC27_SC_VE32_CELL_BASE,
        VEXABC28_SC_VE32_CELL_BASE,VEXABC29_SC_VE32_CELL_BASE,VEXABC30_SC_VE32_CELL_BASE,VEXABC31_SC_VE32_CELL_BASE,
        VEXABC32_SC_VE32_CELL_BASE,VEXABC33_SC_VE32_CELL_BASE,VEXABC34_SC_VE32_CELL_BASE,VEXABC35_SC_VE32_CELL_BASE,
        VEXABC36_SC_VE32_CELL_BASE,VEXABC37_SC_VE32_CELL_BASE,VEXABC38_SC_VE32_CELL_BASE,VEXABC39_SC_VE32_CELL_BASE
    };

    do
    {
        status_data = read_reg_18a(cell_addr[vexCoreId]+ VE32_CELL_STAT_OFFSET, "status_reg");

        if (status_data & VE32_CELL_STAT_IDLING_BF_MSK)
        {

            break;
        }
       sleep(1);

    } while (1);
}



/**************************************************************************************************
 * Function    : v2d_clk_enable()
 * Input args  : V2D instance number and Channel number.
 *               V2D instance number value and channel number value should be 0xFF, to enable
 *               all V2D's and all Channels.
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to set the clocks for corresponding V2D channel
 * ************************************************************************************************/

int v2d_clk_enable (v2d_instance_t v2d_num, drf_channel_instance_t ch_num)
{

    int rv = 0, lc = 0;
    bfn_csr_general_csr_reg_t bfn_csr_general_csr;

    bfn_csr_general_csr.value = 0;

    if (DRF_CHANNEL_0 == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_0_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_0_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_0_CLK_EN = 1;
    }
    else if (DRF_CHANNEL_1 == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_1_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_1_CLK_EN = 1;
    }
    else if (DRF_CHANNEL_BOTH == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_0_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_0_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_0_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_1_CLK_EN = 1;
    }
    else
    {
        LOG_ERROR("ch_num is not valid");
        return 1;
    }

    if (V2D_ALL != v2d_num)
    {
        int read_value = read_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(v2d_num)), "BFN_GENERAL_CSR");
        bfn_csr_general_csr.value |= read_value;

        if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(v2d_num)), bfn_csr_general_csr.value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                    "BFN_GENERAL_CSR"))
            return rv;
    }
    else
    {
        for (lc = V2D0; lc < V2D4; lc++)
        {
            int read_value = read_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(lc)), "BFN_GENERAL_CSR");
            bfn_csr_general_csr.value |= read_value;

            if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(lc)), bfn_csr_general_csr.value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                        "BFN_GENERAL_CSR"))
                return rv;
        }
    }
    return rv;
}

/******************************************************************************************************
 * Function    : v2d_clk_disable()
 * Input args  : V2D instance number and Channel number.
 *               V2D instance number value and channel number value should be 0xFF, to enable
 *               all V2D's and all Channels.
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to disable the clocks for corresponding V2D channel
 ******************************************************************************************************/

int v2d_clk_disable (v2d_instance_t v2d_num, drf_channel_instance_t ch_num)
{

    int rv = 0, lc = 0;
    bfn_csr_general_csr_reg_t bfn_csr_general_csr;

    bfn_csr_general_csr.value = 0;

    if (DRF_CHANNEL_0 == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_0_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_0_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_0_CLK_EN = 1;
    }
    else if (DRF_CHANNEL_1 == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_1_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_1_CLK_EN = 1;
    }
    else if (DRF_CHANNEL_BOTH == ch_num)
    {
        bfn_csr_general_csr.CHANNEL_0_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_0_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_0_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_CRUX_CLK_EN = 1;
        bfn_csr_general_csr.CHANNEL_1_DRF_CLK_EN = 1;
        bfn_csr_general_csr.PDPD_1_CLK_EN = 1;
    }
    else
    {
        LOG_ERROR("ch_num is not valid");
        return 1;
    }

    if (V2D_ALL != v2d_num)
    {
        int read_value = read_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(v2d_num)), "BFN_GENERAL_CSR");
        bfn_csr_general_csr.value = read_value & ~(bfn_csr_general_csr.value);

        if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(v2d_num)), bfn_csr_general_csr.value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                    "BFN_GENERAL_CSR"))
            return rv;
    }
    else
    {
        for (lc = V2D0; lc < V2D4; lc++)
        {
            int read_value = read_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(lc)), "BFN_GENERAL_CSR");
            bfn_csr_general_csr.value = read_value & ~(bfn_csr_general_csr.value);

            if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(lc)), bfn_csr_general_csr.value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                        "BFN_GENERAL_CSR"))
                return rv;
        }
    }
    return rv;
}

/*****************************************************************************************************************
 * Function    : v2d_bfn_gnrl_csr_config()
 * Input args  : V2D instance number and config value.
 *               V2D instance number value should be 0xFF, to enable
 *               all V2D's and all Channels.
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is used to configure the BFN_GNRL_CSR register for corresponding V2D channel
 ****************************************************************************************************************/

int v2d_bfn_gnrl_csr_config(v2d_instance_t v2d_num, int value)
{
    int rv = 0, lc = 0;

    if (V2D_ALL != v2d_num)
    {
        if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(v2d_num)), value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                    "BFN_GENERAL_CSR"))
            return rv;
    }
    else
    {
        for (lc = V2D0; lc < V2D4; lc++)
        {
            if (rv = write_reg_18a(BFN_CSR_GENERAL_CSR_ADR(V2D_BFN_CSR_BASE(lc)), value, BFN_CSR_GENERAL_CSR_WR_MASK, \
                        "BFN_GENERAL_CSR"))
                return rv;
        }
    }
    return rv;
}

/*****************************************************************************************************************************
 * Function    : jesd_reset ()
 * Input args  : jesd_instance_mask   = the JESD instance (0 to 3) to be RESETed.
 *             : reset = for future use
 * Output args : return value of the status of the register writes.
 * Brief       : this funtion is to bring JESD out of RESET. We can select the instances we want to reset by using the mask.
 *               eg: jesd_instance_mask = F, it will reset all the instances,
 * ex: jesd_reset( JESD_INSTANCE_0 | JESD_INSTANCE_3, 0);  => 1001 => 0x9
 * ex: jesd_reset( JESD_INSTANCE_ALL, 0);
 *****************************************************************************************************************************/

uint32_t jesd_reset(int jesd_instance_mask, int reset)
{
    int error = 0;
    int i = 0;

    system("frioPciWrite -F s6a1 -P 0x20000 0x3");
    for(i =0; (i < JESD_INSTANCE_MAX_COUNT); i++)
    {
        if((1 << i) & jesd_instance_mask)
        {
            error =  write_read_expect_18a(DLNK_HUB_BASE + DLNK_HUB_APB_JESD_MAP0_JESD_MEM_DIS_OFFSET + 0x10*i,
                                           DLNK_HUB_APB_JESD_MEM_DIS_DEFAULT, 0x0, 0x0, DLNK_HUB_APB_JESD_MEM_DIS_RD_MASK,
                                           DLNK_HUB_APB_JESD_MEM_DIS_WR_MASK, "DLNK_HUB_APB_JESD_MEM_DIS");
            error += write_read_expect_18a(DLNK_HUB_BASE + DLNK_HUB_APB_JESD_MAP0_JESD_CLK_EN_OFFSET + 0x10*i,
                                           DLNK_HUB_APB_JESD_CLK_EN_DEFAULT, 0x7f, 0x7f, DLNK_HUB_APB_JESD_CLK_EN_RD_MASK,
                                           DLNK_HUB_APB_JESD_CLK_EN_WR_MASK, "DLNK_HUB_APB_JESD_CLK_EN");
            error += write_read_expect_18a(DLNK_HUB_BASE + DLNK_HUB_APB_JESD_MAP0_JESD_GLITCH_SUPPRESS_N_OFFSET + 0x10*i,
                                           DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_DEFAULT, 0x3, 0x3,
                                           DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_RD_MASK, DLNK_HUB_APB_JESD_GLITCH_SUPPRESS_N_WR_MASK,
                                           "MAP0_JESD_GLITCH_SUPPRESS");
            error += write_read_expect_18a(DLNK_HUB_BASE + DLNK_HUB_APB_JESD_MAP0_JESD_SW_RST_N_OFFSET + 0x10*i,
                                           DLNK_HUB_APB_JESD_SW_RST_N_DEFAULT, 0xf3, 0xf3, DLNK_HUB_APB_JESD_SW_RST_N_RD_MASK,
                                           DLNK_HUB_APB_JESD_SW_RST_N_WR_MASK, "DLNK_HUB_APB_JESD_SW_RST");
            printf("JESD instances-%d is enabled\n", i);
        } else
        {
            printf("JESD instances-%d is not-enabled\n", i);
        }
    }

    return error;
}

/*****************************************************************************************
 * Function    : jesd_204d_enable
 * Brief       : To enable 204d
 *******************************************************************************************/
void jesd_204d_enable (void)
{
    int i;
    uint32_t base_address[] = {DLNK_JESD0_CMN_CSR_BASE, DLNK_JESD1_CMN_CSR_BASE};

    for(i=0; i<sizeof(base_address) / sizeof(base_address[0]); i++)
    {
        write_read_expect_18a(base_address[i]+JESD_CMN_CSR_TX_JESD_MODE_OFFSET, JESD_CMN_CSR_TX_JESD_MODE_DEFAULT, \
                              0x1, 0x1, JESD_CMN_CSR_TX_JESD_MODE_RD_MASK, JESD_CMN_CSR_TX_JESD_MODE_WR_MASK, \
                              "JESD_CMN_CSR_TX_JESD_MODE_OFFSET");

         write_read_expect_18a(base_address[i]+JESD_CMN_CSR_RX_JESD_MODE_OFFSET, JESD_CMN_CSR_RX_JESD_MODE_DEFAULT, \
                                0x1, 0x1, JESD_CMN_CSR_RX_JESD_MODE_RD_MASK, JESD_CMN_CSR_RX_JESD_MODE_WR_MASK, \
                                "JESD_CMN_CSR_RX_JESD_MODE_OFFSET");
    }
}

/*****************************************************************************************
 * Function    : jump_to_ram()
 * Brief       : adding jump instruction at ROM addresses to jump to RAM, It is valid only for FRIO
 *******************************************************************************************/
int jump_to_ram(void)
{
    // adding jump instruction at ROM addresses 0x00 and 0x04 to jump to RAM
    write_reg_18a(0x00000000, 0x0040100c, 0xffffff, "ROM_ADDR_00");
    write_reg_18a(0x00000004, 0x0000a001, 0x00ffff, "ROM_ADDR_04");
}

/**
 * @brief           Function for configuring the MEM_FB general configuration
 * @param [in]      base address and power down value
 * @return          status
 */
int mem_fb_general_config(uint32_t mem_fb_base_address, int power_down_control_value)
{
    int rv = 0;

    // EN the HIGH INT
    if (write_reg_18a(MEM_FB_INT_FB_HIGH_EN_ADR(mem_fb_base_address),
                      MEM_FB_INT_FB_HIGH_EN_WR_MASK,
                      MEM_FB_INT_FB_HIGH_EN_WR_MASK,
                      "MEM_FB_MEM_INT_HIGH_EN"))
        return rv;

    // EN the LOW INT
    if (write_reg_18a(MEM_FB_INT_FB_LOW_EN_ADR(mem_fb_base_address),
                MEM_FB_INT_FB_LOW_EN_WR_MASK,
                MEM_FB_INT_FB_LOW_EN_WR_MASK, \
                "MEM_FB_MEM_INT_LOW_EN"))
        return rv;

    // POWER DOWN CONTROL for unused sectors
    if (write_reg_18a(MEM_FB_PWR_DOWN_CTRL_ADR(mem_fb_base_address),
                      power_down_control_value,
                      MEM_FB_PWR_DOWN_CTRL_WR_MASK, \
                      "MEM_FB_MEM_POWER_DOWN_CONTROL"))
        return rv;

    return rv;
}

/**
 * @brief           Function for configuring the FB_MEM
 * @param [in]      capture mode, size_per_capture, v2d_num and apb_num
 * @return          status
 */
int mem_fb_x_capture_configuration(capture_mode_t capture_mode, int size_per_capture, int v2d_num, int apb_num)
{

    /* This configuration is based on the assumption that entire 1MB space wil be utilized or capture size is less than 1MB*/
    int mem_fb_base_address = 0, power_down_control_value = MEM_FB_PWR_DOWN_CTRL_DEFAULT, mem_fb_instance = 0, start_sector = 0,
        rv = 0, sector_end_ptr_value = 0;

    mem_fb_instance = (v2d_num > V2D3) ? 1 : 0;
    mem_fb_base_address = (mem_fb_instance) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;

    start_sector = 0;
    // All 32 sectors are powered up
    power_down_control_value = 0;

    if ((SINGLE_CAPTURE_MODE == capture_mode) || (CONTINUOUS_CAPTURE_MODE == capture_mode))
    {
        sector_end_ptr_value = size_per_capture;
    }
    else if (DOUBLE_CAPTURE_MODE == capture_mode)
    {
        sector_end_ptr_value = (2 * (size_per_capture + 1) - 1);
    }

    if (mem_fb_general_config(mem_fb_base_address, power_down_control_value))
        LOG_ERROR("MEM_FB basic configuration failed");

    if ((v2d_num % 4) < 2)
    {
        /*V2D0 and V2D1 should go to PORT0*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT0_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT0_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT0"))
            return rv;
    }
    else
    {
        /*V2D2 and V2D3 should go to PORT1*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT1_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT1_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT1"))
            return rv;

    }

    /*END address of the 32nd Sector as we are utilizing the complete 1MB space in this Test Case*/
    if (write_reg_18a(mem_fb_base_address + SECTOR_END_PTR(start_sector),
                      sector_end_ptr_value,
                      MEM_FB_SECTOR_END_PTR_WR_MASK,
                      "SECTOR_END_PTR"))
        return rv;

    // EN the FB MEM, this should be last register of FB_MEM to be configured
    if (write_reg_18a(MEM_FB_EN_ADR(mem_fb_base_address),
                      0x1,
                      MEM_FB_EN_WR_MASK,
                      "MEM_FB_MEM_EN"))
        return rv;

    return rv;
}

/**
 * @brief           Function for configuring the FB_MEM for a QUAD capture
 * @param [in]      capture mode, quad_instance, num_antennas and size_per_antenna
 * @return          status
 */
int quad_mem_fb_x_capture_configuration(capture_mode_t capture_mode, int quad_instance, int num_antennas, uint32_t size_per_antenna)
{

    /* This configuration is based on the assumption that entire 1MB space wil be utilized*/
    int mem_fb_base_address = 0, power_down_control_value = MEM_FB_PWR_DOWN_CTRL_DEFAULT, mem_fb_instance = 0, start_sector = 0,
        rv = 0, i = 0;

    mem_fb_instance = (quad_instance > 1) ? 1 : 0;
    mem_fb_base_address = (mem_fb_instance) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;

    start_sector = 0;

    // All 32 sectors are powered up
    power_down_control_value = 0;

    /*In double configuration Buffer should be allocated to more antennas*/
    if (DOUBLE_CAPTURE_MODE == capture_mode)
    {
        num_antennas = 2 * num_antennas;
    }

    if (mem_fb_general_config(mem_fb_base_address, power_down_control_value))
        LOG_ERROR("MEM_FB basic configuration failed");

    if (0 == (quad_instance % 2))
    {
        /*V2D0 and V2D1 should go to PORT0*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT0_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT0_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT0"))
            return rv;
    }
    else
    {
        /*V2D2 and V2D3 should go to PORT1*/
        if (write_reg_18a(MEM_FB_MEM_PTR_PORT1_ADR(mem_fb_base_address),
                          0x0,
                          MEM_FB_MEM_PTR_PORT1_WR_MASK,
                          "MEM_FB_MEM_PTR_PORT1"))
            return rv;
    }

    for (i = 0; i < num_antennas; i++)
    {

        if (write_reg_18a(mem_fb_base_address + SECTOR_END_PTR(start_sector + i),
                          ((size_per_antenna * (i + 1)) - 1),
                          MEM_FB_SECTOR_END_PTR_WR_MASK,
                          "SECTOR_END_PTR"))
            return rv;


        if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + i),
                          (size_per_antenna * (i + 1)),
                          MEM_FB_SECTOR_END_PTR_WR_MASK,
                          "SECTOR_NEXT_PTR"))
            return rv;
    }

    //The Next ptr should be 0 as we are utilizing the complete 1MB space
    if (write_reg_18a(mem_fb_base_address + SECTOR_NEXT_PTR(start_sector + (num_antennas - 1)),
                      0x0,
                      MEM_FB_SECTOR_NEXT_PTR_WR_MASK,
                      "SECTOR_NEXT_PTR"))
        return rv;

    // EN the FB MEM, this should be the last registeer of FB_MEM to be configured
    if (write_reg_18a(MEM_FB_EN_ADR(mem_fb_base_address),
                      0x1,
                      MEM_FB_EN_WR_MASK,
                      "MEM_FB_MEM_EN"))
        return rv;

    return rv;
}


/**
 * @brief           Function for configuring the vex/rcs srp rte interface
 * @param [in]
 * @return
 */
void rte_init(void)
{
    int dev_id = 0;
    int flags = 0;
    srp_vex_config_t vex_params;
    srp_config_t cfg = { 0 };
    srp_st_t srp_st = SRP_ST_SUCCESS;

    memset(&vex_params, 0, sizeof(vex_params));

    /*
     * attempt to attach to an existing configuration instance.
     * if none exists then create a new one.
     */

    srp_st = srp_config_attach(dev_id, &srp_hdl);
    if (srp_st == SRP_ST_HANDLE_NOT_EXIST || srp_st == SRP_ST_NO_MEMORY) {
        SRP_CALL(srp_config(dev_id, &cfg, &srp_hdl));
    } else if (srp_st != SRP_ST_SUCCESS) {
        LOG_PRINT("%s : ERROR in SRP config %s:%d\n", srp_status_get(srp_st),
                  __FILE__, __LINE__);
        goto srp_return;
    }

    srp_st = srp_vex_config_get(srp_hdl, &vex_params);
    if (srp_st != SRP_ST_SUCCESS) {
        /* call the module configuration function */

        SRP_CALL(srp_vex_config(srp_hdl, &vex_params));
    }

srp_return:
    if (srp_st != SRP_ST_SUCCESS) {
        srp_status_print("Error", srp_st);
    }

    if (srp_hdl) {
        printf("\n detach ");
        //srp_config_detach(vex_srp_hdl);
    }
}

void rte_deinit()
{
    if (srp_hdl)
    {
        printf("destroying previous config instance\n");
        //SRP_CALL(srp_config_destroy(srp_hdl));
        srp_config_destroy(srp_hdl);
        srp_hdl = NULL;
    }
}

srp_st_t vex_loader(srp_vex_core_t core_id, const char *file_name)
{
    return srp_vex_loader(srp_hdl, core_id, file_name);
}

void vex_start(srp_vex_core_t core_id, const uint32_t start_addr)
{
    unsigned int vex_cell_offset = VEXABC1_SC_VE32_CELL_BASE - VEXABC0_SC_VE32_CELL_BASE;
    unsigned int vex_cell_base_addr = VEXABC0_SC_VE32_CELL_BASE + (core_id * vex_cell_offset);


    write_reg_18a( vex_cell_base_addr + VE32_CELL_START_ADDR_OFFSET, start_addr, 0xFFFFFFFF, "start_addr");
    write_reg_18a( vex_cell_base_addr + VE32_CELL_CTRL_OFFSET, VE32_CELL_CTRL_START_BF_MSK | VE32_CELL_CTRL_RUN_BF_MSK, 0xFFFFFFFF, "ctrl");
}

srp_st_t rcs_config(srp_rcs_config_t *rcs_params)
{
    srp_st_t srp_st = SRP_ST_SUCCESS;

    SRP_CALL(srp_rcs_config(srp_hdl, rcs_params));

    return srp_st;

srp_return:
   if (srp_st != SRP_ST_SUCCESS)
   {
        srp_status_print("Error", srp_st);
   }

   if (srp_hdl)
   {
        printf("\n detach ");
        //srp_config_detach(srp_hdl);
   }
   return srp_st;
}

void rcs_rcp_start(srp_rcs_rcp_t rcp_id)
{
    srp_rcs_rcp_start(srp_hdl, rcp_id);
}


// End of file

