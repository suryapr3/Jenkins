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
 * @file    spl_main.c
 * @brief   Entry function for spl code.;
 * @details  Entry function for secondary program loader code.
 * This file also contains the function to unpack the SPL code from SRAM into IRAM and DRAM;
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include <stdio.h>
#include <stdint.h>
#include "sys_ctrl.h"
#include "rcs_gpreg.h"
#include "com_rom_spl_shm.h"
// #include "com_print.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/
#define SPL_DONE 0xDEADBEEF
/***********************************************
 * STATIC VARIABLES                            *
 ***********************************************/
static shm_image_indicator_t *p_shm_image_ind = (shm_image_indicator_t *)(SPL_SHM_IMG_DESC_ADDR);
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * STATIC FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Disables the watchdog. Watchdog is enabled at the end of ROM code once SPL is loaded
 * @param [in]      void
 * @return          void.
 */

static void spl_disable_watchdog ()
{
    sys_ctrl_wdog_csr_reg_t sys_ctrl_wdog_csr_reg = {.value = SYS_CTRL_WDOG_CSR_DEFAULT};
    sys_ctrl_wdog_csr_reg.HALT = 1;
    *SYS_CTRL_WDOG_MAP0_WDOG_CSR_REG = sys_ctrl_wdog_csr_reg;
}

/**
 * @brief           Halts the CORE 0; RCS firmware gets loaded into the memories once the cores are halted .
 * @param [in]      void
 * @return          void.
 */
static void spl_halt_ax_core ()
{
    volatile rcs_gpreg_core0_ctrl_reg_t rcs_gpreg_core0_ctrl_reg = {.value = 0}; // default is 0x00000001

    rcs_gpreg_core0_ctrl_reg.CORE_STATVECTORSEC = 1;
    *RCS_GPREG_CORE0_CTRL_REG = rcs_gpreg_core0_ctrl_reg;

    rcs_gpreg_core0_altrstvec_reg_t rcs_gpreg_core0_altrstvec = {
        .ALTRESETVEC = 0x10000000}; // base address of IRAM - fw needs to boot from this location
    *RCS_GPREG_CORE0_ALTRSTVEC_REG = rcs_gpreg_core0_altrstvec;

    rcs_gpreg_core0_ctrl_reg.CORE_RUNSTALL_PROD = 1;
    *RCS_GPREG_CORE0_CTRL_REG = rcs_gpreg_core0_ctrl_reg;

}

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/

/**
 * @brief           Function to over-ride the default unpacking routine in the reset vector;
 * @param [in]      void
 * @return          void.
 */
void __reset_user_init ()
{
    ; // function to override default spl unpacking in reset vector
}

/**
 * @brief           entry into secondary program loader
 * @param [in]      argc, argv
 * @return          int.
 */
int main (int argc, char **argv)
{
    // FW_PRINT(FW_INFO, "Entering Secondary Program Loader." );
    spl_disable_watchdog ();
    p_shm_image_ind->shm_image_valid = SPL_DONE ;
    spl_halt_ax_core();
    return (0);
}
