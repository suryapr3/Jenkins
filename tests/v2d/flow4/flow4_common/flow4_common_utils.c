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
 * @file    flow4_common_utils.c
 * @brief   HOST utility functions for validating the PDPD block with GMP And DDR terms enabled.
 * @todo    Write documentation for source file sample_source.h
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include "flow4_common_utils.h"
#include "common_utils.h"


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */
int flow4_configure_pdpd(int v2d_num, int apb_num, int test_config)
{
    int rv = 0;
    int i_value = 0, q_value = 0, update_passthru = 0, update_c_lut = 1, post_c_center_value = POST_C_CENTER_VALUE_UNITY_GAIN;
    pdpd_rate_t pdpd_out_rate;

    i_value = PASSTHRU_I_COEFF_UNITY_GAIN;
    q_value = PASSTHRU_Q_COEFF_UNITY_GAIN;
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, FLOW4_PASSTHRU_DELAY, pdpd_out_rate))
    {
        printf ("PDPD config reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_reg_config(v2d_num, apb_num, i_value, q_value))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_ddr_reg_config(v2d_num, apb_num, test_config))
    {
        printf("ERROR:pdpd ddr reg config failed\n");
        return rv;
    }
    if (rv = pdpd_extra_static_reg_config(v2d_num, apb_num, FLOW4_EXTRA_DELAY))
    {
        printf("PDPD extra static config failed\n");
        return rv;
    }
    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, post_c_center_value))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    if (rv = pdpd_ctrl_reg_config(v2d_num, apb_num, update_passthru, update_c_lut))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }


    return rv;
}

/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */
int pdpd_gmp_ddr_reg_config(int v2d_num, int apb_num, int test_config)
{
    int rv = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    switch (pdpd_out_rate)
    {
        case PDPD_RATE_IQ_P5:
        case PDPD_RATE_IQ_1:
        case PDPD_RATE_IQ_2:
            /* 32 GMP and 16 DDR terms  for 1 stream of data or 1 antenna TX*/
            /* each GMP and DDR term is 65 I and Q*/
            /* In matlab example, this LUT is set as only the first 2 GMP terms set s 2exp11, the imaginary terms are zeros.
             * the rest of the GMP terms are all zeros both real (I) and imaginary (Q)
             * The DDR terms are are also set to zero. hence only GMP configuration is done in this example
             * GMP_static config
             * GMP- tap enable/disbale, magnitude delay, linear conjuagte enable,, select linear delay.
             * in the MATLAB exmaple it is set for the first two GMP terms whicha are the only non zero tersm as
             *  GMP- tap enable/disbale = 1, magnitude delay 0x0, , linear conjuagte enable->disabled, ,, slect linear delay->0x0.
             */
            rv = pdpd_gmp_ddr_reg_config_p5_1_2(v2d_num, apb_num);
            break;
        case PDPD_RATE_IQ_4:
        /* 16GMP terms and 8 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_iq_4(v2d_num, apb_num, pdpd_in_rate);
            break;
        case PDPD_RATE_IQ_8:
        /* 8GMP terms and 4 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_iq_8(v2d_num, apb_num);
            break;
        default:
            printf("ERROR: PDPD LUT MODE NOT supported \n");
            rv = 1;
            break;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 0.5, 1 and 2 Gsps
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_p5_1_2(int v2d_num, int apb_num)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW4_PASSTHRU_DELAY))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    /* GMP dynamic shdw */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW4_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW4_PASSTHRU_DELAY))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic shdw*/
    if (rv = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW4_DDR_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 4 Gsps
 *                  shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_iq_4(int v2d_num, int apb_num, pdpd_rate_t pdpd_in_rate)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW4_PASSTHRU_DELAY, pdpd_in_rate))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    /* GMP dynamic shdw */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_4(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW4_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW4_PASSTHRU_DELAY, pdpd_in_rate))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic shdw*/
    if (rv = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_4(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW4_DDR_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 8 Gsps
 *                  shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_iq_8(int v2d_num, int apb_num)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config_iq_8(v2d_num, apb_num, num_gmp_terms, FLOW4_PASSTHRU_DELAY))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    /* GMP dynamic shdw */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_iq_8(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_8(v2d_num, apb_num, num_gmp_terms, FLOW4_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_8(v2d_num, apb_num, num_ddr_terms, FLOW4_PASSTHRU_DELAY))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic shdw*/
    if (rv = pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config_iq_8(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_8(v2d_num, apb_num, num_ddr_terms, FLOW4_GMP_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    return rv;
}

/**
 * @brief           Function to get the ref output file
 * @param [in]      post_filter_mode and test_config
 * @return          file_name
 */
char* get_ref_file_flow4(int post_filter_mode, int test_config)
{

    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    int frac_os = 0;
    int rate_array[PDPD_NUM_SAMPLE_RATES] = {0, 1, 2, 4, 8};

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    frac_os = (pdpd_in_rate == pdpd_out_rate) ? 1 : (rate_array[pdpd_in_rate] / rate_array[pdpd_out_rate]);

    switch (frac_os)
    {
        case 1:
            {
                if (FILTER_MODE == post_filter_mode)
                    return "ref_output_filter_mode_frac_os_1.txt";
                else
                {
                    return "ref_output_frac_os_1.txt";
                }
                break;
            }
        case 2:
            {
                if (FILTER_MODE == post_filter_mode)
                    return "ref_output_filter_mode_frac_os_2.txt";
                else
                    return "ref_output_frac_os_2.txt";
                break;
            }
        case 4:
            {
                if (FILTER_MODE == post_filter_mode)
                    return "ref_output_filter_mode_frac_os_4.txt";
                else
                    return "ref_output_frac_os_4.txt";
                break;
            }
        case 8:
            {
                if (FILTER_MODE == post_filter_mode)
                    return "ref_output_filter_mode_frac_os_8.txt";
                else
                    return "ref_output_frac_os_8.txt";
                break;
            }
        default:
            {
                LOG_ERROR("frac_os is not valid so not able to get the proper ref output");
                exit(2);
            }
    }
}

