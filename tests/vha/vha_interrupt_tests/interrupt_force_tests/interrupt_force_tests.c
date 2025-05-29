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
/*
 * @file    interrupt_force_tests.c
 * @TC Description:
 *          This HOST driver will be generating various interrupts randomly by setting bits in
 *          INTERRUPT FORCE registers of the VHA. The status of these interrupts so generated
 *          will be checked in the INTERRUPT STATUS registers.
 */

#include "vha_common_definitions.h"

#define VHA_NUM_ANT                    (  2 )
#define VHA_ANT                        (  0 )
#define NSIP_HBI                       (  1 )
#define SWG                            (  2 )

// Global declarations for the submodules getting used in this test

// External variables
extern char g_compile_time[];

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int test_configure(uint32_t vha_num);
int test_configure_vha(uint32_t vha_num);
int test_run(uint32_t vha_num);
int test_irq_handler(uint32_t vha_num, int ant, uint32_t force, int module);
int test_check_status(uint32_t vha_num);
void test_show_regs(uint32_t vha_num);

/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */

int main(
    int argc,
    const char *argv[])
{
    uint32_t vha_num;
    int rv;

    init();                                                // Initialize the srp
    printf("\n");
    printf("Test: VHA Interrupt tests\n");
    printf("%s\n", g_compile_time);
    printf("BUILD_DIR: %s\n\n", BUILD_DIR);

    if(abc_platform_detect() < 0)                          // detect the build version
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    vha_num = (int)argv[0];
    printf("INFO: File    : %s\n", __FILE__);
    printf("INFO: argc    : %d\n", argc);
    printf("INFO: argv[0] : %d = vha_num = (VHA%d)\n", vha_num, vha_num);

    // Let's first do some sanity checks on the input arguments received
    if(vha_num > (NUM_VHA_INSTANCES - 1))
    {
        printf("ERROR: VHA number cannot be higher than 7, Exiting test..!\n");
        return FAILURE;
    }

    if(is_vha_present(vha_num) < 0)                        // check is the VHA present on this build
    {
        printf("Exiting..!\n");
        return FAILURE;
    }

    if(rv = vha_init(vha_num))
    {
        printf("ERROR: Failed to do vha_init(), rv = %d\n", rv);
        return rv;
    }

    // print registers before starting any configurations
    printf("HOST: Checking registers before doing any register configurations\n");
    if(rv = test_check_status(vha_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    if(rv = test_configure(vha_num))
    {
        printf("ERROR: Failed to do test_configure(), rv = %d\n", rv);
        return rv;
    }

    // print registers after the configurations are done
    printf("HOST: Finished register configurations, now checking registers\n");
    if(rv = test_check_status(vha_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        return FAILURE;
    }

    // Need to start FORCE-ing interrupts now.
    if(rv = test_run(vha_num))
    {
        printf("ERROR: test_run() failed, rv = %d\n", rv);
        // Do not return here, let the program dump the status with an ERROR message
    }

    // Looking for any abnormal statuses post a test run
    printf("HOST: Checking registers after a test completion\n");
    if(test_check_status(vha_num))
    {
        printf("ERROR: One or many register statuses are NOT clean. (rv = %d) Exiting test..!\n", rv);
        rv = FAILURE;
    }

    if(SUCCESS == rv)
    {
        printf("Test Result:------ PASS ------!\n\n");
    } else
    {
        printf("Test Result:------ FAIL -----!\n\n");
    }

    printf("HOST: End of the Test execution....!\n");

    return rv;

}

/**
 * function         test_configure()
 * @brief           Function configuring all the blocks required to run this test
 * @param [in]      vha_num
 * @return          status
 */

int test_configure(uint32_t vha_num)
{
    int rv;

    rv = 0;
    // Configure VHA registers
    if(rv = test_configure_vha(vha_num))
    {
        printf("ERROR: Failed to configure VHA%d (rv = %d) Exiting test..!\n", vha_num, rv);
        return rv;
    }

    return rv;
}

/**
 * function         test_configure_vha()
 * @brief           Function configuring all the required VHA registers to run this test
 * @param [in]      vha_num
 * @return          status
 */

int test_configure_vha(uint32_t vha_num)
{
    uint64_t addr;
    uint32_t value;
    int ant, cm, swg, rv;

    rv = 0;
    addr = VHA_BASE(vha_num);
    if((addr < 0x03c00000) || (addr > 0x03ce0000))
    {
        printf("ERROR: Cannot configure VHA with base_addr = %x\n", addr);
        return FAILURE;
    }

    // Enable the interrupts
    // VHA_ANT_INT_EN
    for(ant = 0; ant < VHA_NUM_ANT; ant++)
    {
        addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant) + VHA_ANT_REG_OFFSET;
        if(rv = write_reg_18a(VHA_ANT_INT_HIGH_EN_ADR(addr),
                              ((1 << VHA_ANT_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              VHA_ANT_INT_HIGH_EN_WR_MASK,
                              "VHA_ANT_INT_HIGH_EN"))
            return rv;

        if(rv = write_reg_18a(VHA_ANT_INT_LOW_EN_ADR(addr),
                              ((1 << VHA_ANT_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              VHA_ANT_INT_LOW_EN_WR_MASK,
                              "VHA_ANT_INT_LOW_EN"))
            return rv;
    }

    // NSIP_HBI_INTR_EN
    for(cm = 0; cm < 2; cm++)
    {
        addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(cm) + VHA_NSIP_OFFSET;
        if(rv = write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr),
                              ((1 << NSIP_HBI_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK,
                              "NSIP_HBI_INTR_INT_HIGH_EN"))
            return rv;

        if(rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr),
                              ((1 << NSIP_HBI_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              NSIP_HBI_INTR_INT_LOW_EN_WR_MASK,
                              "NSIP_HBI_INTR_INT_LOW_EN"))
            return rv;
    }

    // VHA_DL/UL_SWG_INT_EN
    for(swg = 0; swg < 2; swg++)
    {
        addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
        if(1 == swg) addr = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;

        if(rv = write_reg_18a(SWG_INT_HIGH_EN_ADR(addr),
                              ((1 << SWG_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              SWG_INT_HIGH_EN_WR_MASK,
                              "SWG_INT_HIGH_EN"))
            return rv;

        if(rv = write_reg_18a(SWG_INT_LOW_EN_ADR(addr),
                              ((1 << SWG_NUM_INTERRUPTS) - 1),/*enable all the interrupts*/
                              SWG_INT_LOW_EN_WR_MASK,
                              "SWG_INT_LOW_EN"))
            return rv;
    }

    printf("INFO: VHA%d configuration completed\n", vha_num);

    return rv;
}

/*
 * function    : test_run()
 * @brief      : this function is to force VHA interrupts
 *
 */
int test_run(uint32_t vha_num)
{
    uint64_t addr;
    int force, ant, cm, swg, module, rv;
    int i;

    rv = 0;
    // Start setting bits in INTERRUPT REGISTERs
    // VHA_ANT_INT_FORCE
    module = VHA_ANT;
    for(ant = 0; ant < 2; ant++)
    {
        addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant) + VHA_ANT_REG_OFFSET;
        force = 1;
        for(i = 0; i < VHA_ANT_NUM_INTERRUPTS; i++)
        {
             force = (1 << i);
             printf("INFO: Forcing Interrupt of VHA_ANT (VHA = %d, ANT = %d, force = %x)\n", vha_num, ant, force);
             if(rv = write_reg_18a(VHA_ANT_INT_FORCE_ADR(addr),
                                   force,
                                   VHA_ANT_INT_FORCE_WR_MASK,
                                   "VHA_ANT_INT_FORCE"))
                 return rv;

             if(rv = test_irq_handler(vha_num, ant, force, module))
             {
                  // Here means, something went wrong
                  printf("ERROR: test_irq_handler() returned rv = %d\n", rv);
                  return rv;
             } else
             {
                  printf("INFO: Interrupt test passed for VHA = %d, ANT = %d, force = %x\n\n", vha_num, ant, force);
             }
        }
    }

    // NSIP_HBI_INT_FORCE
    module = NSIP_HBI;
    for(cm = 0; cm < 2; cm++)
    {
        addr = VHA_BASE(vha_num) + VHA_APB_OFFSET(cm) + VHA_NSIP_OFFSET;
        force = 1;
        for(i = 0; i < NSIP_HBI_NUM_INTERRUPTS; i++)
        {
             force = (1 << i);
             printf("INFO: Forcing Interrupt of NSIP_HBI (VHA = %d, CM = %d, force = %x)\n", vha_num, cm, force);
             if(rv = write_reg_18a(NSIP_HBI_INTR_INT_FORCE_ADR(addr),
                                   force,
                                   NSIP_HBI_INTR_INT_FORCE_WR_MASK,
                                   "NSIP_HBI_INTR_INT_FORCE"))
                 return rv;

             if(rv = test_irq_handler(vha_num, cm, force, module))
             {
                  // Here means, something went wrong
                  printf("ERROR: test_irq_handler() returned rv = %d\n", rv);
                  return rv;
             } else
             {
                  printf("INFO: Interrupt test passed for VHA = %d, CM = %d, force = %x\n\n", vha_num, cm, force);
             }
        }
    }

    // SWG_INT_FORCE
    module = SWG;
    for(swg = 0; swg < 2; swg++)
    {
        addr = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
        if(1 == swg) addr = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;

        force = 1;
        for(i = 0; i < SWG_NUM_INTERRUPTS; i++)
        {
             force = (1 << i);
             printf("INFO: Forcing Interrupt of SWG (VHA = %d, SWG = %d, force = %x)\n", vha_num, swg, force);
             if(rv = write_reg_18a(SWG_INT_FORCE_ADR(addr),
                                   force,
                                   SWG_INT_FORCE_WR_MASK,
                                   "SWG_INT_FORCE"))
                 return rv;

             if(rv = test_irq_handler(vha_num, swg, force, module))
             {
                  // Here means, something went wrong
                  printf("ERROR: test_irq_handler() returned rv = %d\n", rv);
                  return rv;
             } else
             {
                  printf("INFO: Interrupt test passed for VHA = %d, SWG = %d, force = %x\n\n", vha_num, swg, force);
             }
        }
    }

    return rv;
}

/**
 * function         test_irq_handler()
 * @brief           Function to clear the interrupt set and check the correctness of the
 *                  bits set in different VHA status registers
 * @param [in]      vha_num, ant_num, force, module
 * @return          status
 */
int test_irq_handler(uint32_t vha_num, int ant, uint32_t force, int module)
{
    uint64_t addr0, addr1;
    uint32_t int_status, vha_int_high_stat, vha_int_low_stat, vha_int_mask;
    int rv;

    rv = 0;
    // First read the status registers
    addr0 = VHA_BASE(vha_num) + VHA_REG_OFFSET;
    vha_int_high_stat = read_reg_18a(VHA_INT_HIGH_STAT_ADR(addr0), "VHA_INT_HIGH_STAT");
    vha_int_low_stat = read_reg_18a(VHA_INT_LOW_STAT_ADR(addr0), "VHA_INT_LOW_STAT");
    printf("INFO: VHA_INT_HIGH_STAT = %x\nINFO: VHA_INT_LOW_STAT  = %x\n", vha_int_high_stat, vha_int_low_stat);
    if(module == VHA_ANT)
    {
        addr1 = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant) + VHA_ANT_REG_OFFSET;
        int_status = read_reg_18a(VHA_ANT_INT_STAT_ADR(addr1), "VHA_INT_STATUS");
        printf("INFO: ANT_INT_STATUS = %x\n", int_status);

        // Clear the interrupt at the earliest
        if(rv = write_reg_18a(VHA_ANT_INT_CLR_ADR(addr1),
                              int_status, /*WTC*/
                              VHA_ANT_INT_CLR_WR_MASK,
                              "VHA_ANT_INT_CLR"))
            return rv;

        vha_int_mask = (4 << ant);                         // bit2: ant0, bit3: ant1

    } else if(module == NSIP_HBI)
    {
        addr1 = VHA_BASE(vha_num) + VHA_APB_OFFSET(ant) + VHA_NSIP_OFFSET;
        int_status = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(addr1), "NSIP_HBI_INTR_INT_STATUS");
        printf("INFO: NSIP_INT_STATUS = %x\n", int_status);

        // Clear the interrupt at the earliest
        if(rv = write_reg_18a(NSIP_HBI_INTR_INT_CLR_ADR(addr1),
                              int_status, /*WTC*/
                              NSIP_HBI_INTR_INT_CLR_WR_MASK,
                              "NSIP_HBI_INTR_INT_CLR"))
            return rv;

        vha_int_mask = (1 << ant);                         // bit0: cm0, bit1: cm1

    } else if(module == SWG)
    {
        addr1 = VHA_BASE(vha_num) + VHA_DL_SWG_OFFSET;
        if(1 == ant) addr1 = VHA_BASE(vha_num) + VHA_UL_SWG_OFFSET;
        int_status = read_reg_18a(SWG_INT_STAT_ADR(addr1), "SWG_INT_STATUS");
        printf("INFO: SWG_INT_STATUS = %x\n", int_status);

        // Clear the interrupt at the earliest
        if(rv = write_reg_18a(SWG_INT_CLR_ADR(addr1),
                              int_status, /*WTC*/
                              SWG_INT_CLR_WR_MASK,
                              "SWG_INT_CLR"))
            return rv;

        vha_int_mask = (16 << ant);                        // bit4: dlswg, bit5: ulswg

    }

    // Now check whether the status register values are as expected or not
    if(int_status != force)
    {
        printf("ERROR: Tried to FORCE interrupt as %x, but INT_STATUS register is showing %x\n",
                                                                             force, int_status);
        return FAILURE;
    }

    if((vha_int_high_stat != vha_int_mask) || (vha_int_low_stat != vha_int_mask))
    {
        printf("ERROR: VHA_INT_HIGH/LOW_STAT registers are not getting set correctly.\n");
        printf("VHA_INT_HIGH_STAT = %x\nVHA_INT_LOW_STAT  = %x\n", vha_int_high_stat, vha_int_low_stat);
        return FAILURE;
    }

    return rv;
}

/*
 * function    : test_check_status()
 * @brief      : this function checks various statuses of VHA
 *
 */
int test_check_status(uint32_t vha_num)
{
    int rv, e_code;

    e_code = SUCCESS;
    rv = SUCCESS;
    if(rv = vha_check_status(vha_num, 0))                  // antenna0
        e_code = 1;                                        // FAILURE code for VHA status wrong
    if(rv = vha_check_status(vha_num, 1))                  // antenna1
        e_code = 2;                                        // FAILURE code for VHA status wrong

    test_show_regs(vha_num);

    return e_code;
}

/*
 * function    : test_show_regs()
 * @brief      : this function all the registers of VHA
 *
 */
void test_show_regs(uint32_t vha_num)
{
    vha_show_regs(vha_num, 0);                       // VHA registers, antenna0
    vha_show_regs(vha_num, 1);                       // VHA registers, antenna1
}

// End of file
