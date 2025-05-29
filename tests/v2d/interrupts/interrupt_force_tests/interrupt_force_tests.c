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
 *          INTERRUPT FORCE registers of the V2D which will trigger the registerd ISR in the RCS.
 *          As part of RCS ISR , RCS will write the interrupt value to the shared memory location.
 *          Clear the interrupts from RCS, verify from HOST whether corresponding interrupts were
 *          seen or not and the status registers was reset or not.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "common_utils.h"
#include "v2d_host_rcs_common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define V2D_NUM_ANT                    ( 2 )
#define NUM_NSIP_HBI_INTERRUPTS        ( 21 )
#define NUM_V2D_CSR_INTERRUPTS         ( 32 )

/***********************************************
 * LOCAL/PRIVATE TYPEDEFS (structs, enums)     *
 ***********************************************/

typedef enum
{
    HIGH_EN = 0,
    LOW_EN
}interrupt_state_enable_t;

typedef enum
{
    NSIP_HBI0 = 0,
    NSIP_HBI1 = 1,
    V2D_CSR
}interrupt_test_module_t;
/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

// used for handshaing between HOST and RCS
int g_rsm_buffer[] = {0x23FFEC};

// may change once new functions are added, check .map file
int g_dcode_buffer[] = {0xE4030};
/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int v2d_interrupt_configure(int v2d_num, int apb_num, interrupt_state_enable_t interrupt_state_enable);
int irq_handler(int v2d_num, int apb_num, interrupt_test_module_t dut, int force);
int run_test(int v2d_num, int apb_num);
int reset_v2d_interrupt_configuration(int v2d_num, int apb_num);

/**
 * @brief           Resettigng the V2D interrupt configure
 * @param [in]      v2d_num, apb_num
 * @return          status value
 */
int reset_v2d_interrupt_configuration(int v2d_num, int apb_num)
{
    int rv = 0;
    uint32_t addr = 0;

    addr = PDPD_BASE_ADDR(v2d_num, apb_num);

    /*PDPD HIGH EN INT*/
    if (rv = write_reg_18a(PDPD_INT_HIGH_EN_ADR(addr), 0x0, PDPD_INT_HIGH_EN_WR_MASK, "PDPD_HIGH_EN"))
        return rv;

    /*PDPD LOW EN INT*/
    if (rv = write_reg_18a(PDPD_INT_LOW_EN_ADR(addr), 0x1, PDPD_INT_LOW_EN_WR_MASK, "PDPD_HIGH_EN"))
        return rv;

    /*NSIP_HBI_0 HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_0_HIGH_EN"))
        return rv;

    /*NSIP_HBI_0 LOW EN INT*/
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
        return rv;

    /*NSIP_HBI_1 HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
    if (write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_1_HIGH_EN"))
        return rv;

    /*NSIP_HBI_1 LOW EN INT*/
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
        return rv;

    /*V2D_CSR_UNDERRUN HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_HIGH_EN_ADR(addr), 0x0, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_CSR_HIGH_EN"))
        return rv;

    /*V2D_CSR_UNDERRUN LOW EN INT*/
    if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_LOW_EN_ADR(addr), 0xFFFFFFFF, AV2D_CSR_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_CSR_LOW_EN"))
        return rv;

    return rv;
}


/**
 * @brief           V2D interrupt configure
 * @param [in]      v2d_num, apb_num and interrupt_state
 * @return          status value
 */
int v2d_interrupt_configure(int v2d_num, int apb_num, interrupt_state_enable_t interrupt_state_enable)
{
    int rv = 0;
    uint32_t addr = 0;

    reset_v2d_interrupt_configuration(v2d_num, apb_num);

    if (HIGH_EN == interrupt_state_enable)
    {
        /*PDPD HIGH EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num);
        if (rv = write_reg_18a(PDPD_INT_HIGH_EN_ADR(addr), 0x1, PDPD_INT_HIGH_EN_WR_MASK, "PDPD_HIGH_EN"))
            return rv;

        /*NSIP_HBI_0 HIGH EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
        if (rv = write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_0_HIGH_EN"))
            return rv;

        /*NSIP_HBI_1 HIGH EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
        if (write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_1_HIGH_EN"))
            return rv;

        /*V2D_CSR HIGH EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
        if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_HIGH_EN_ADR(addr), 0xFFFFFFFF, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_CSR_HIGH_EN"))
            return rv;
    }
    else
    {
        /*PDPD LOW EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num);
        if (rv = write_reg_18a(PDPD_INT_LOW_EN_ADR(addr), 0x1, PDPD_INT_LOW_EN_WR_MASK, "PDPD_HIGH_EN"))
            return rv;

        /*NSIP_HBI_0 LOW EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
        if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
            return rv;

        /*NSIP_HBI_1 LOW EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
        if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x1FFFFF, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
            return rv;

        /*V2D_CSR LOW EN INT*/
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
        if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_LOW_EN_ADR(addr), 0xFFFFFFFF, AV2D_CSR_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_CSR_LOW_EN"))
            return rv;
    }

    return rv;
}

/**
 * @brief           irq_handler
 * @param [in]      v2d_num, apb_num, interrupt module and force value
 * @return          status value
 */
int irq_handler(int v2d_num, int apb_num, interrupt_test_module_t dut, int force)
{
    int rv = 0, interrupt_value = 0, set_value = 0;
    uint32_t addr = 0;

    poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_INTERRUPT_DONE);

    switch(dut)
    {
        case NSIP_HBI0:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
                interrupt_value = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(addr), "HBI0_INT_STATUS");
                set_value = read_reg_18a(g_dcode_buffer[0], "RCS_RESULT");

                if ((0 != interrupt_value) && (set_value != force))
                {
                    LOG_ERROR("NSIP_HBI0_INT validation failed, value: 0x%x, set_value : 0x%x, force_value: 0x%x",
                            interrupt_value, set_value, force);
                    return 1;
                }
                LOG_INFO("NSIP_HBI0 interrupt_set_value: 0x%x", set_value);
                break;
            }
        case NSIP_HBI1:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
                interrupt_value = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(addr), "HBI1_INT_STATUS");
                set_value = read_reg_18a(g_dcode_buffer[0], "RCS_RESULT");

                if ((0 != interrupt_value) && (set_value != force))
                {
                    LOG_ERROR("NSIP_HBI0_INT validation failed, value: 0x%x, set_value : 0x%x, force_value: 0x%x",
                            interrupt_value, set_value, force);
                    return 1;
                }
                LOG_INFO("NSIP_HBI1 interrupt_set_value: 0x%x", set_value);
                break;
            }
        case V2D_CSR:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
                interrupt_value = read_reg_18a(AV2D_CSR_INT_CSR_INT_STAT_ADR(addr), "V2D_CSR_INT_STATUS");
                set_value = read_reg_18a(g_dcode_buffer[0], "RCS_RESULT");

                if ((0 != interrupt_value) && (set_value != force))
                {
                    LOG_ERROR("NSIP_HBI0_INT validation failed, value: 0x%x, set_value : 0x%x, force_value: 0x%x",
                            interrupt_value, set_value, force);
                    return 1;
                }
                LOG_INFO("V2D_CSR interrupt_set_value: 0x%x", set_value);
                break;
            }
        default:
            {
                LOG_ERROR("undefined dut value was passed: 0x%x", dut);
                rv = 1;
            }
    }

    write_reg_18a(g_rsm_buffer[0], HOST_VALIDATION_DONE, 0xFFFFFFFF, "RCS_HANDSHAKE_WRITE");
    return rv;
}

/**
 * @brief           run_test function which will trigger the force interrupts
 * @param [in]      v2d_num, apb_num
 * @return          status value
 */
int run_test(int v2d_num, int apb_num)
{
    int rv = 0, test_status = 0, force = 0, lc = 0;
    uint32_t addr = 0;
    interrupt_test_module_t dut;

    {
        dut = NSIP_HBI0;
        force = 0;
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;

        /*For NSIP_HBI_0 interrupts*/
        for (lc = 0; lc < NUM_NSIP_HBI_INTERRUPTS; lc++)
        {
            force = (1 << lc);

            if (rv = write_reg_18a(NSIP_HBI_INTR_INT_FORCE_ADR(addr), force, NSIP_HBI_INTR_INT_FORCE_WR_MASK, "HBI0_FORCE_INT"))
                return rv;

            if (rv = irq_handler(v2d_num, apb_num, dut, force))
            {
                LOG_ERROR("Force interrupt test failed for interrupt number 0x%x", lc);
                test_status |= 1;
            }
        }

        dut = NSIP_HBI1;
        force = 0;
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;

        /*For NSIP_HBI_1 interrupts*/
        for (lc = 0; lc < NUM_NSIP_HBI_INTERRUPTS; lc++)
        {
            force = (1 << lc);

            if (rv = write_reg_18a(NSIP_HBI_INTR_INT_FORCE_ADR(addr), force, NSIP_HBI_INTR_INT_FORCE_WR_MASK, "HBI1_FORCE_INT"))
                return rv;

            if (rv = irq_handler(v2d_num, apb_num, dut, force))
            {
                LOG_ERROR("Force interrupt test failed for interrupt number 0x%x", lc);
                test_status |= 1;
            }
        }

        /*For V2D_CSR interrupts*/
        dut = V2D_CSR;
        force = 0;
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;

        /*For NSIP_HBI_1 interrupts*/
        for (lc = 0; lc < NUM_V2D_CSR_INTERRUPTS; lc++)
        {
            force = (1 << lc);

            if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_FORCE_ADR(addr), force, AV2D_CSR_INT_CSR_INT_FORCE_WR_MASK, "V2D_FORCE_INT"))
                return rv;

            if (rv = irq_handler(v2d_num, apb_num, dut, force))
            {
                LOG_ERROR("Force interrupt test failed for interrupt number 0x%x", lc);
                test_status |= 1;
            }
        }
    }
    return test_status;
}

/**
 * @brief           Main function
 * @param [in]      argc, *argv[]
 * @return          status value
 */
int main(int argc, const char *argv[])
{
    int rv = 0;
    int v2d_num = 0, apb_num = 0, rcs_core = 0;
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    // corresponds to v2d_num, apb_num
    int rcs_host_param[2] = {0}, rd_wr_value[32] = {0};

    init();

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    v2d_num = argv[0];
    apb_num = argv[1];
    rcs_core = argv[3];

    LOG_INFO("argv[0] : %d = v2d_num", v2d_num);
    LOG_INFO("argv[1] : %d = apb_num", apb_num);
    LOG_INFO("argv[2] : %d = rcs_core", rcs_core);

    /*enabling the V2D clock for the given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        LOG_ERROR("v2d_clk_enable failed");
        return rv;
    }

    // halt and soft reset all cores
    rcsHaltsoftReset();

    memset(&rcs_params, 0, sizeof(rcs_params));

    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_AX].img_file = g_rcs_file_path[0];
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_RX].img_file = "rcs_fw/rx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CTRL_TX].img_file = "rcs_fw/tx_hw.elf";
    rcs_params.rcs_cfg[SRP_RCS_RCP_CALIB].img_file = "rcs_fw/cal_hw.elf";

    rcs_config(&rcs_params);

    rcs_host_param[0] = v2d_num;
    rcs_host_param[1] = apb_num;

    memset(rd_wr_value, 0, sizeof(rd_wr_value));

    /*Clear the RSM memories*/
    write_mem_18a(g_dcode_buffer[0], 32, rd_wr_value, "DCODE_BUFFER");
    write_mem_18a(g_rsm_buffer[0], 1, rd_wr_value, "RSM_FLAG");
    write_mem_18a(RSM_MEM_OFFSET, 32, rd_wr_value, "RSM_MEMORY");

    /*Load the parameters to RCS RSM memory*/
    write_mem_18a(RSM_MEM_OFFSET, ARRAY_SIZE(rcs_host_param), rcs_host_param, "RCS_HOST_PARAM");

    /*Configuring the V2D*/
    if (rv = v2d_interrupt_configure(v2d_num, apb_num, HIGH_EN))
    {
        LOG_ERROR("v2d_interrupt_configure failed");
    }

    /*start RCS core*/
    if (SRP_RCS_RCP_CTRL_AX == rcs_core)
    {
        rcs_rcp_start(SRP_RCS_RCP_CTRL_AX);
    }
    else if (SRP_RCS_RCP_CTRL_RX == rcs_core)
    {
        rcs_rcp_start(SRP_RCS_RCP_CTRL_RX);
    }
    else if (SRP_RCS_RCP_CTRL_TX == rcs_core)
    {
        rcs_rcp_start(SRP_RCS_RCP_CTRL_TX);
    }
    else if (SRP_RCS_RCP_CALIB == rcs_core)
    {
        rcs_rcp_start(SRP_RCS_RCP_CALIB);
    }

    printf("HOST:RCS core was triggered");

    poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_READY);

    if (rv = run_test(v2d_num, apb_num))
    {
        LOG_ERROR("FORCE interrupt_test failed for HIGH_INT");
    }
    else
    {
        LOG_INFO("FORCE interrupt test passed for HIGH_INT");
    }

    /*Configuring the V2D*/
    if (rv = v2d_interrupt_configure(v2d_num, apb_num, LOW_EN))
    {
        LOG_ERROR("v2d_interrupt_configure failed");
    }

    if (rv = run_test(v2d_num, apb_num))
    {
        LOG_ERROR("FORCE interrupt_test failed for LOW_INT");
    }
    else
    {
        LOG_INFO("FORCE interrupt test passed for LOW_INT");
    }

    write_reg_18a(g_rsm_buffer[0], HOST_TEST_COMPLETE, 0xFFFFFFFF, "RCS_HANDSHAKE_WRITE");

    poll_rsm_flag_rcs(g_rsm_buffer[0], RCS_COMPLETE);

    if (0 ==rv)
    {
        LOG_INFO("Force interrupt TC passed for v2d: %d, apb_id: %d, RCS_CORE: %d", v2d_num, apb_num, rcs_core);
    }
    else
    {
        LOG_ERROR("Force interrupt TC passed for v2d: %d, apb_id: %d, RCS_CORE: %d", v2d_num, apb_num, rcs_core);
    }

    return rv;
}

