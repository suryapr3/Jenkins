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
 * @file    tx_alarm.c
 * @TC Description:
 *          This HOST driver will be generating various interrupts which will generate TX ALARM
 *          randomly by setting bits in INTERRUPT FORCE registers of the V2D which will set the
 *          corresponding status bit. Once the status bit was set HOST will check whether ALARM
 *          STATUS register bit and corresponding STICKY register is set or not, after that
 *          Clear the interrupts from HOST, verify from HOST whether corresponding interrupts along
 *          with ALARM STATUS is cleared or not.
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "common_utils.h"

/***********************************************
 * LOCAL/PRIVATE MACROS AND DEFINES            *
 ***********************************************/
#define V2D_NUM_ANT                    ( 2 )
/*All NSIP interrupts will trigger the TX ALARM*/
#define NUM_NSIP_HBI_INTERRUPTS        ( 21 )
/*V2D CSR Interrupts that causes Tx Alarm*/
#define NUM_V2D_DBE_INTERRUPTS         ( 2 )
#define NUM_V2D_UNDERRUN_INTERRUPTS    ( 2 )

#define TX_ALARM_VALUE                 ((1 << TRX_SYS_CSR_TX_ALARM0_STAT_V2D_BF_OFF) | (1 << TRX_SYS_CSR_TX_ALARM0_STAT_E1_BF_OFF) | (1 << TRX_SYS_CSR_TX_ALARM0_STAT_Y1_BF_OFF))

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
    V2D_CSR_UNDERRUN = 2,
    V2D_CSR_DBE = 3
}interrupt_test_module_t;

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
/*Bit positions for UNDERRUN INTERRUPT.

EXTRA_UNDERRUN is handled under the EXTRA_UNDERRUN_ENABLE flag, as the TX_UNDERRUN( A path) and EXTRA_UNDERRUN( C path)
cannot occur simultaneously in any of the use cases . EXTRA_UNDERRUN is handled separately,
in alignment with the RTL implementation*/
const int v2d_csr_underrun_bit_pos[NUM_V2D_UNDERRUN_INTERRUPTS] = {
#if (1 == EXTRA_UNDERRUN_ENABLE)
    AV2D_CSR_INT_CSR_INT_STAT_PD_EXTRA_UNDERRUN_BF_OFF,
#else
    AV2D_CSR_INT_CSR_INT_STAT_TX_UNDERRUN_BF_OFF,
#endif
    AV2D_CSR_INT_CSR_INT_STAT_PD_MAIN_UNDERRUN_BF_OFF};

/*BIT positions for DBE(Double Bit Error)*/
const int v2d_csr_dbe_bit_pos[NUM_V2D_DBE_INTERRUPTS] = {
    AV2D_CSR_INT_CSR_INT_STAT_TX_BUF_0_ECC_DBE_BF_OFF, AV2D_CSR_INT_CSR_INT_STAT_TX_BUF_1_ECC_DBE_BF_OFF};

/***********************************************
 * STATIC FUNCTION PROTOTYPES                  *
 ***********************************************/
int v2d_interrupt_configure(int v2d_num, int apb_num, interrupt_state_enable_t interrupt_state_enable);
int validate_interrupt(int v2d_num, int apb_num, interrupt_test_module_t dut, int force, int mask_enabled);
int run_test(int v2d_num, int apb_num, int* mask);
int reset_v2d_interrupt_configuration(int v2d_num, int apb_num);
int tx_sticky_bit_check(int v2d_num, int apb_num, int exp_value, int mask_enabled, int interrupt_resetted);

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
    if (rv = write_reg_18a(PDPD_INT_LOW_EN_ADR(addr), 0x0, PDPD_INT_LOW_EN_WR_MASK, "PDPD_HIGH_EN"))
        return rv;

    /*NSIP_HBI_0 HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_0_HIGH_EN"))
        return rv;

    /*NSIP_HBI_0 LOW EN INT*/
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
        return rv;

    /*NSIP_HBI_1 HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
    if (write_reg_18a(NSIP_HBI_INTR_INT_HIGH_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_HIGH_EN_WR_MASK, "NSIP_HBI_1_HIGH_EN"))
        return rv;

    /*NSIP_HBI_1 LOW EN INT*/
    if (rv = write_reg_18a(NSIP_HBI_INTR_INT_LOW_EN_ADR(addr), 0x0, NSIP_HBI_INTR_INT_LOW_EN_WR_MASK, "NSIP_HBI_0_LOW_EN"))
        return rv;

    /*V2D_CSR_UNDERRUN HIGH EN INT*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_HIGH_EN_ADR(addr), 0x0, AV2D_CSR_INT_CSR_INT_HIGH_EN_WR_MASK, "V2D_CSR_HIGH_EN"))
        return rv;

    /*V2D_CSR_UNDERRUN LOW EN INT*/
    if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_LOW_EN_ADR(addr), 0x0, AV2D_CSR_INT_CSR_INT_LOW_EN_WR_MASK, "V2D_CSR_LOW_EN"))
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
 * @brief           Tx Alarm Check
 * @param [in]      v2d_num, apb_num, exp_value and alram_masked or not
 * @return          status value
 */
int tx_alarm_check(int v2d_num, int apb_num, int exp_value, int mask_enabled)
{
    int rv = 0;
    uint32_t trx_base = TRX_SYS_CSR_BASE(v2d_num);
    uint32_t value = 0;

    // if mask is enabled then no alarm should set
    exp_value = (mask_enabled) ? 0 : exp_value;

    if (0 == apb_num)
    {
        value = read_reg_18a(TRX_SYS_CSR_TX_ALARM0_STAT_ADR(trx_base), "TRX_ALARM0_STATUS");
        if (exp_value != value)
        {
            LOG_ERROR("TX_ALARM0 is not set, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
            rv = 1;
        }
    }
    else
    {
        value = read_reg_18a(TRX_SYS_CSR_TX_ALARM1_STAT_ADR(trx_base), "TRX_ALARM1_STATUS");
        if (exp_value != value)
        {
            LOG_ERROR("TX_ALARM1 is not set, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
            rv = 1;
        }
    }
    return rv;
}

/**
 * @brief           Tx sticky bit Check
 * @param [in]      v2d_num, apb_num, exp_value, alram_masked or not and interrupt_resetted or not
 * @return          status value
 */
int tx_sticky_bit_check(int v2d_num, int apb_num, int exp_value, int mask_enabled, int interrupt_resetted)
{
    int rv = 0;
    uint32_t trx_base = TRX_SYS_CSR_BASE(v2d_num);
    uint32_t value = 0;

    // if mask is enabled then no alarm should set
    exp_value = (mask_enabled) ? 0 : exp_value;

    if (0 == apb_num)
    {
        value = read_reg_18a(TRX_SYS_CSR_TX_ALARM0_STICKY_ADR(trx_base), "TRX_ALARM0_STICKY");
        if (exp_value != value)
        {
            LOG_ERROR("TX_STICKY0 is not set, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
            rv = 1;
        }

        /*If interrupt was cleared then the second read value should be a reset value*/
        if (interrupt_resetted)
        {
            exp_value = 0;
            value = read_reg_18a(TRX_SYS_CSR_TX_ALARM0_STICKY_ADR(trx_base), "TRX_ALARM0_STICKY");
            if (exp_value != value)
            {
                LOG_ERROR("TX_STICKY0 is not reset, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
                rv = 1;
            }
        }
    }
    else
    {
        value = read_reg_18a(TRX_SYS_CSR_TX_ALARM1_STICKY_ADR(trx_base), "TRX_ALARM1_STICKY");
        if (exp_value != value)
        {
            LOG_ERROR("TX_STICKY1 is not set, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
            rv = 1;
        }

        /*If interrupt was cleared then the second read value should be a reset value*/
        if (interrupt_resetted)
        {
            exp_value = 0;
            value = read_reg_18a(TRX_SYS_CSR_TX_ALARM1_STICKY_ADR(trx_base), "TRX_ALARM0_STICKY");
            if (exp_value != value)
            {
                LOG_ERROR("TX_STICKY1 is not reset, expected_value: 0x%x, actual_value: 0x%x", exp_value, value);
                rv = 1;
            }
        }

    }
    return rv;
}


/**
 * @brief           validate_interrupt
 * @param [in]      v2d_num, apb_num, interrupt module, force value and mask_enabled or not
 * @return          status value
 */
int validate_interrupt(int v2d_num, int apb_num, interrupt_test_module_t dut, int force, int mask_enabled)
{
    int rv = 0, interrupt_value = 0, set_value = 0;
    uint32_t addr = 0;

    switch(dut)
    {
        case NSIP_HBI0:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_0_OFFSET;
                interrupt_value = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(addr), "HBI0_INT_STATUS");

                if (interrupt_value != force)
                {
                    LOG_ERROR("NSIP_HBI0_INT validation failed, expected_value: 0x%x, actual_value: 0x%x",
                            force, interrupt_value);
                    return 1;
                }
                LOG_INFO("NSIP_HBI0 interrupt_set_value: 0x%x", force);

                if (rv = tx_alarm_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for NSIP_HBI0");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 0/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for NSIP_HBI0");
                }

                // Clear the interrupt
                if (rv = write_reg_18a(NSIP_HBI_INTR_INT_CLR_ADR(addr), force, NSIP_HBI_INTR_INT_CLR_WR_MASK, "HBI0_INT_CLEAR"))
                    return rv;

                if (rv = tx_alarm_check(v2d_num, apb_num, 0, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for NSIP_HBI0");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 1/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for NSIP_HBI0");
                }
                break;
            }
        case NSIP_HBI1:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_NSIP_HBI_1_OFFSET;
                interrupt_value = read_reg_18a(NSIP_HBI_INTR_INT_STAT_ADR(addr), "HBI1_INT_STATUS");

                if (interrupt_value != force)
                {
                    LOG_ERROR("NSIP_HBI1_INT validation failed, expected_value: 0x%x, actual_value: 0x%x",
                            force, interrupt_value);
                    return 1;
                }
                LOG_INFO("NSIP_HBI1 interrupt_set_value: 0x%x", force);

                if (rv = tx_alarm_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for NSIP_HBI1");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 0/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for NSIP_HBI1");
                }

                // Clear the interrupt
                if (rv = write_reg_18a(NSIP_HBI_INTR_INT_CLR_ADR(addr), force, NSIP_HBI_INTR_INT_CLR_WR_MASK, "HBI0_INT_CLEAR"))
                    return rv;

                if (rv = tx_alarm_check(v2d_num, apb_num, 0, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for NSIP_HBI1");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 1/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for NSIP_HBI1");
                }
                break;
            }
        case V2D_CSR_UNDERRUN:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
                interrupt_value = read_reg_18a(AV2D_CSR_INT_CSR_INT_STAT_ADR(addr), "V2D_CSR_INT_STATUS");

                if (interrupt_value != force)
                {
                    LOG_ERROR("V2D_CSR_UNDERRUN interrupt validation failed, expected_value: 0x%x, actual_value: 0x%x",
                            force, interrupt_value);
                    return 1;
                }
                LOG_INFO("V2D_CSR_UNDERRUN interrupt_set_value: 0x%x", force);

                if (rv = tx_alarm_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for V2D_UNDERRUN");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 0/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for V2D_UNDERRUN");
                }

                //clear the interrupt
                if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_CLR_ADR(addr), force, AV2D_CSR_INT_CSR_INT_CLR_WR_MASK, "V2D_CSR_INT_CLEAR"))
                    return rv;

                if (rv = tx_alarm_check(v2d_num, apb_num, 0, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for V2D_UNDERRUN");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 1/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for V2D_UNDERRUN");
                }
                break;
            }
        case V2D_CSR_DBE:
            {
                addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
                interrupt_value = read_reg_18a(AV2D_CSR_INT_CSR_INT_STAT_ADR(addr), "V2D_CSR_INT_STATUS");

                if (interrupt_value != force)
                {
                    LOG_ERROR("V2D_CSR_DBE interrupt validation failed, expected_value: 0x%x, actual_value: 0x%x",
                            force, interrupt_value);
                    return 1;
                }
                LOG_INFO("V2D_CSR_DBE interrupt_set_value: 0x%x", force);

                if (rv = tx_alarm_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for V2D_DBE");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 0/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for V2D_DBE");
                }

                //clear the interrupt
                if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_CLR_ADR(addr), force, AV2D_CSR_INT_CSR_INT_CLR_WR_MASK, "V2D_CSR_INT_CLEAR"))
                    return rv;

                if (rv = tx_alarm_check(v2d_num, apb_num, 0, mask_enabled))
                {
                    LOG_ERROR("tx_alarm_check failed for V2D_DBE");
                }

                if (rv = tx_sticky_bit_check(v2d_num, apb_num, TX_ALARM_VALUE, mask_enabled, 1/*is_interrupt_resetted*/))
                {
                    LOG_ERROR("tx_sticky_bit check failed for V2D_DBE");
                }
                break;
            }

        default:
            {
                LOG_ERROR("undefined dut value was passed: 0x%x", dut);
                rv = 1;
            }
    }
    return rv;
}

/**
 * @brief           run_test function which will trigger the force interrupts
 * @param [in]      v2d_num, apb_num
 * @return          status value
 */
int run_test(int v2d_num, int apb_num, int* mask)
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

            if (rv = validate_interrupt(v2d_num, apb_num, dut, force, mask[0]))
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

            if (rv = validate_interrupt(v2d_num, apb_num, dut, force, mask[1]))
            {
                LOG_ERROR("Force interrupt test failed for interrupt number 0x%x", lc);
                test_status |= 1;
            }
        }

        /*For V2D_CSR_UNDERRUN interrupts*/
        dut = V2D_CSR_UNDERRUN;
        force = 0;
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;

        for (lc = 0; lc < NUM_V2D_UNDERRUN_INTERRUPTS; lc++)
        {
            force = (1 << v2d_csr_underrun_bit_pos[lc]);

            if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_FORCE_ADR(addr), force, AV2D_CSR_INT_CSR_INT_FORCE_WR_MASK, "V2D_FORCE_INT"))
                return rv;

            if (rv = validate_interrupt(v2d_num, apb_num, dut, force, mask[2]))
            {
                LOG_ERROR("Force interrupt test failed for V2D interrupt number 0x%x", v2d_csr_underrun_bit_pos[lc]);
                test_status |= 1;
            }
        }

        /*For V2D_CSR_UNDERRUN interrupts*/
        dut = V2D_CSR_DBE;
        force = 0;
        addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;

        for (lc = 0; lc < NUM_V2D_DBE_INTERRUPTS; lc++)
        {
            force = (1 << v2d_csr_dbe_bit_pos[lc]);

            if (rv = write_reg_18a(AV2D_CSR_INT_CSR_INT_FORCE_ADR(addr), force, AV2D_CSR_INT_CSR_INT_FORCE_WR_MASK, "V2D_FORCE_INT"))
                return rv;

            if (rv = validate_interrupt(v2d_num, apb_num, dut, force, mask[3]))
            {
                LOG_ERROR("Force interrupt test failed for V2D interrupt number 0x%x", v2d_csr_dbe_bit_pos[lc]);
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
    int v2d_num = 0, apb_num = 0, rcs_core = 0,
        /*Corresponds to NSIP_HBI0, NSIP_HBI1, V2D_CSR_UNDERRUN, V2D_CSR_DBE*/
        mask_enabled[4] = {0};
    srp_rcs_config_t rcs_params;
    srp_rcs_rcp_t rcs_core_id = SRP_RCS_RCP_CTRL_AX;
    uint32_t addr = 0, tx_cfg_complete_val = 0;

    init();

    LOG_PRINT ("INFO: logger beginning");
    printf ("INFO: argc : %d", argc);

    v2d_num = argv[0];
    apb_num = argv[1];

    LOG_INFO("argv[0] : %d = v2d_num", v2d_num);
    LOG_INFO("argv[1] : %d = apb_num", apb_num);

    /*enabling the V2D clock for the given channel of V2D*/
    if (rv = v2d_clk_enable(v2d_num, apb_num))
    {
        LOG_ERROR("v2d_clk_enable failed");
        return rv;
    }

#if (1 == EXTRA_UNDERRUN_ENABLE)
    /* To trigger EXTRA_UNDERRUN TX_CFG_COMPLETE bit should be set in TX_GNRL_CSR register as per RTL implementation*/
    tx_cfg_complete_val = (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_CFG_COMPLETE_BF_OFF);
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;

    if (rv = write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_cfg_complete_val, \
                AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR"))
        return rv;
#endif

    /*Configuring the V2D*/
    if (rv |= v2d_interrupt_configure(v2d_num, apb_num, HIGH_EN))
    {
        LOG_ERROR("v2d_interrupt_configure failed");
    }

    /*all TX alarm sources are enabled*/
    mask_enabled[0] = 0;
    mask_enabled[1] = 0;
    mask_enabled[2] = 0;
    mask_enabled[3] = 0;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for HIGH_INT");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for HIGH_INT");
    }

    /*Configuring the V2D*/
    if (rv |= v2d_interrupt_configure(v2d_num, apb_num, LOW_EN))
    {
        LOG_ERROR("v2d_interrupt_configure failed");
    }

    /*NSIP interrupts are mapped to LOW. Alarms are not expected*/
    mask_enabled[0] = 1;
    mask_enabled[1] = 1;
    mask_enabled[2] = 0;
    mask_enabled[3] = 0;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm failed for LOW_INT");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for LOW_INT");
    }

    /*Configuring the V2D*/
    if (rv |= v2d_interrupt_configure(v2d_num, apb_num, HIGH_EN))
    {
        LOG_ERROR("v2d_interrupt_configure failed");
    }

    /*MASK the NSIB_HBI0, NSIP_HBI1 and V2D_CSR_UNDERRUN interrupts for Tx_ALARM generation*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    int tx_gnrl_csr_value = tx_cfg_complete_val | ((1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_CM_1_ERR_MASK_BF_OFF) | \
                            (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_CM_0_ERR_MASK_BF_OFF) | \
                            (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_UNDERRUN_MASK_BF_OFF) | \
                            (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_ECC_DBE_MASK_BF_OFF));

    if (rv = write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_gnrl_csr_value, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR_VALUE"))
        return rv;

    mask_enabled[0] = 1;
    mask_enabled[1] = 1;
    mask_enabled[2] = 1;
    mask_enabled[3] = 1;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for all sources masked");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for all sources masked");
    }

    /*MASK the NSIB_HBI0 for Tx_ALARM generation*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    tx_gnrl_csr_value = tx_cfg_complete_val | (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_CM_0_ERR_MASK_BF_OFF);

    if (rv |= write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_gnrl_csr_value, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR_VALUE"))
        return rv;

    mask_enabled[0] = 1;
    mask_enabled[1] = 0;
    mask_enabled[2] = 0;
    mask_enabled[3] = 0;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for NSIP0 masking");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for NSIP0 masking");
    }

    /*MASK the NSIB_HBI1 for Tx_ALARM generation*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    tx_gnrl_csr_value = tx_cfg_complete_val | (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_CM_1_ERR_MASK_BF_OFF);

    if (rv |= write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_gnrl_csr_value, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR_VALUE"))
        return rv;

    mask_enabled[0] = 0;
    mask_enabled[1] = 1;
    mask_enabled[2] = 0;
    mask_enabled[3] = 0;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for NSIP1 masking");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for NSIP1 masking");
    }

    /*MASK the V2D_CSR_UNDERRUN for Tx_ALARM generation*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    tx_gnrl_csr_value = tx_cfg_complete_val | (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_UNDERRUN_MASK_BF_OFF);

    if (rv |= write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_gnrl_csr_value, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR_VALUE"))
        return rv;

    mask_enabled[0] = 0;
    mask_enabled[1] = 0;
    mask_enabled[2] = 1;
    mask_enabled[3] = 0;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for V2D underrun masking");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for V2D underrun masking");
    }

    /*MASK the V2D_DBE for Tx_ALARM generation*/
    addr = PDPD_BASE_ADDR(v2d_num, apb_num) + V2D_CSR_OFFSET;
    tx_gnrl_csr_value = tx_cfg_complete_val | (1 << AV2D_CSR_TX_CSR_TX_GNRL_CSR_TX_ALARM_ECC_DBE_MASK_BF_OFF);

    if (rv |= write_reg_18a(AV2D_CSR_TX_CSR_TX_GNRL_CSR_ADR(addr), tx_gnrl_csr_value, \
            AV2D_CSR_TX_CSR_TX_GNRL_CSR_WR_MASK, "TX_GNRL_CSR_VALUE"))
        return rv;

    mask_enabled[0] = 0;
    mask_enabled[1] = 0;
    mask_enabled[2] = 0;
    mask_enabled[3] = 1;

    if (rv |= run_test(v2d_num, apb_num, mask_enabled))
    {
        LOG_ERROR("Tx alarm test failed for V2D DBE");
    }
    else
    {
        LOG_INFO("Tx alarm test passed for V2D DBE");
    }

    if (0 ==rv)
    {
        LOG_INFO("Tx alarm TC passed for v2d: %d, apb_id: %d", v2d_num, apb_num);
    }
    else
    {
        LOG_ERROR("Tx alarm TC passed for v2d: %d, apb_id: %d", v2d_num, apb_num);
    }

    return rv;
}

