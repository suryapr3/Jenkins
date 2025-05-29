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
 * @file    flow3_common_utils.c
 * @brief   HOST utility functions for validating the PDPD block with GMP And DDR terms enabled.
 * @details
 * @todo    Write documentation for source file sample_source.h
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/

#include "flow3_common_utils.h"
#include "common_utils.h"

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/
/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */
int flow3_configure_pdpd(int v2d_num, int apb_num, int test_config)
{
    int rv = 0;
    int i_value = 0, q_value = 0, update_passthru = 0, update_c_lut = 1, post_c_center_value = POST_C_CENTER_VALUE_UNITY_GAIN;
    pdpd_rate_t pdpd_out_rate;

    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf("INFO: PDPD configuration Started");
#if  LIVEIQ_SAMPLES
    //i_value = v2d_liveIQ_param.passthru_coeft_i;
    //q_value = v2d_liveIQ_param.passthru_coeft_q;
// coding for differnt termTypes need to be added

    //if (rv = pdpd_config_reg_config(v2d_num, apb_num, v2d_liveIQ_param.passthru_dly, pdpd_out_rate))
	if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, v2d_liveIQ_param.passthru_dly, pdpd_out_rate))
    {
        printf ("PDPD config reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_reg_config(v2d_num, apb_num, v2d_liveIQ_param.passthru_coeft_i, v2d_liveIQ_param.passthru_coeft_q))  
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_ddr_reg_config_generic(v2d_num, apb_num, &v2d_liveIQ_param, test_config))
    {
        printf("ERROR:pdpd ddr reg config failed\n");
        return rv;
    }
    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, post_c_center_value))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    /* setting other taps for post filter to zero */
    if (rv = pdpd_post_c_reg_config( v2d_num,  apb_num, 0 /* value */))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    update_passthru = 0;  
    update_c_lut = 0;// initilaised to zero as directly  writing to live reg and not SHADW via APB, no shadow to live tranfer to be triggered
    //if (rv = pdpd_control_reg_config(v2d_num, apb_num, update_passthru, update_c_lut))
     if (rv = pdpd_ctrl_reg_config(v2d_num, apb_num, update_passthru, update_c_lut))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }
#else 
    i_value = PASSTHRU_I_COEFF_UNITY_GAIN;
    q_value = PASSTHRU_Q_COEFF_UNITY_GAIN;
      
    if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, FLOW3_PASSTHRU_DELAY, pdpd_out_rate))
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
#endif //LIVEIQ_SAMPLES

    return rv;
}

/**
 * @brief           Function configuring all the required  pdpd registers from host in case of
 *                  g buffer update happening either from VEX or AXI.
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */
int gbuffer_update_configure_pdpd(int v2d_num, int apb_num, int test_config)
{
    int rv = 0;
    int num_gmp_terms, num_ddr_terms, post_c_center_value = POST_C_CENTER_VALUE_UNITY_GAIN;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, FLOW3_PASSTHRU_DELAY, pdpd_out_rate))
    {
        printf ("PDPD config reg config failed\n");
        return rv;
    }
    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, post_c_center_value))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    switch(pdpd_out_rate)
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
            if (rv = pdpd_gmp_static_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        case PDPD_RATE_IQ_4:
            /* 16GMP terms and 8 DDR terms */
            if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        case PDPD_RATE_IQ_8:
            /* 8GMP terms and 4 DDR terms */
            if (rv = pdpd_gmp_static_config_iq_8(v2d_num, apb_num, num_gmp_terms, PASSTHRU_DELAY))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_iq_8(v2d_num, apb_num, num_ddr_terms, PASSTHRU_DELAY))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        default:
            printf("ERROR: PDPD rate not supported \n");
            rv = 1;
            break;
    }
    return rv;
}


/**
 * @brief           Function configuring all the required  pdpd registers from host in case of
 *                  g buffer update happening either from VEX or AXI.
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */
int dynamic_gbuffer_update_configure_pdpd(int v2d_num, int apb_num, int test_config, int num_gmp_terms, int num_ddr_terms)
{
    int rv = 0;
    int post_c_center_value = POST_C_CENTER_VALUE_UNITY_GAIN;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;
    pdpd_cfg_reg_t pdpd_cfg_reg;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_cfg_reg_config(v2d_num, apb_num, FLOW3_PASSTHRU_DELAY, pdpd_out_rate))
    {
        printf ("PDPD config reg config failed\n");
        return rv;
    }

    /*update the PDPD CONFIG for immediate update*/
    pdpd_cfg_reg.value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_cfg_config_tbl[0].offset, "PDPD_CFG_REG");
    pdpd_cfg_reg.EXT_CTRL_UPDATE_C_LUT = 1;
    pdpd_cfg_reg.EXT_CTRL_UPDATE_PASSTHRU = 1;
    pdpd_cfg_reg.EXT_CTRL_UPDATE_NL_LUT = 1;

    if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + g_v2d_pdpd_cfg_config_tbl[0].offset, pdpd_cfg_reg.value, \
                g_v2d_pdpd_cfg_config_tbl[0].mask, g_v2d_pdpd_cfg_config_tbl[0].name))
        return rv;


    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, post_c_center_value))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    switch(pdpd_out_rate)
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
            if (rv = pdpd_gmp_static_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        case PDPD_RATE_IQ_4:
            /* 16GMP terms and 8 DDR terms */
            if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        case PDPD_RATE_IQ_8:
            /* 8GMP terms and 4 DDR terms */
            if (rv = pdpd_gmp_static_config_iq_8(v2d_num, apb_num, num_gmp_terms, PASSTHRU_DELAY))
            {
                printf("ERROR:GMP STATIC_CONFIG failed\n");
                return rv;
            }
            /* DDR STATIC */
            if (rv = pdpd_ddr_static_config_iq_8(v2d_num, apb_num, num_ddr_terms, PASSTHRU_DELAY))
            {
                printf("ERROR:DDR_STATIC_CONFIG failed\n");
                return rv;
            }
            break;
        default:
            printf("ERROR: PDPD rate not supported \n");
            rv = 1;
            break;
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
            printf("ERROR: PDPD rate NOT supported \n");
            rv = 1;
            break;
    }
    return rv;
}
#if LIVEIQ_SAMPLES 
/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for all termTypes
 * the other version is specific for tyermTyep=1
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and test_config
 * @return          status
 */

int pdpd_gmp_ddr_reg_config_generic(int v2d_num, int apb_num, v2d_liveIQ_param_t* v2d_liveIQ_param, int test_config)
{
    int rv = 0;
    pdpd_rate_t pdpd_in_rate, pdpd_out_rate;

    pdpd_in_rate = g_test_config_tbl[test_config][0];
    pdpd_out_rate = g_test_config_tbl[test_config][1];
	// Only supports the case case pdpd_in_rate and pdpd_out_rate are the same. 
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
			rv = pdpd_gmp_ddr_reg_config_p5_1_2_generic(v2d_num, apb_num ,v2d_liveIQ_param); 
          
            break;
        case PDPD_RATE_IQ_4:
        /* 16GMP terms and 8 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_iq_4_generic(v2d_num, apb_num, v2d_liveIQ_param);
           // if (rv){
			//	            printf("ERROR: PDPD rpdpd_gmp_ddr_reg_config_iq_4_generic FAILED \n");
			//}
     
            break;
        case PDPD_RATE_IQ_8:
        /* 8GMP terms and 4 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_iq_8_generic(v2d_num, apb_num, v2d_liveIQ_param);            
            // if (rv){
			//	            printf("ERROR: PDPD pdpd_gmp_ddr_reg_config_iq_8_generic FAILED \n");
			//}             
            break;
            
        default:
            printf("ERROR: PDPD rate NOT supported \n");
            rv = 1;
            break;
    }
    return rv;
}

#endif //LIVEIQ_SAMPLES

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
    if (rv = pdpd_gmp_static_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY))
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
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
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
 
#if LIVEIQ_SAMPLES
/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 0.5, 1 and 2 Gsps, for all the possible termTypes 1to 5
 * th other version is specifcally only for the termType=1;
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_p5_1_2_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param)
{

    int i,rv = 0;
#if LIVEIQ_SAMPLES 
#if !LIVEIQ_PASSTHRU_TEST
    /* GMP and DDR  Staic, dynamic Shadow adn shift reg configuration  */
    if (rv = pdpd_gmp_ddr_config_p5_1_2_generic_wrapper(v2d_num, apb_num, v2d_liveIQ_param))
   {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv; 
    }
#endif
#else
    /* GMP Static */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, GMP_C_I_VALUE, GMP_C_I_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    /* GMP dynamic shdw */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_I_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, passthru_dly))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_p5_1_2(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
#endif //0
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}

#endif //LIVEIQ_SAMPLES 
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
    if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
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
#if LIVEIQ_SAMPLES

/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 4 Gsps
 *                  shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_iq_4_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;
#if LIVEIQ_SAMPLES 
#if !LIVEIQ_PASSTHRU_TEST
    /* GMP and DDR  Staic, dynamic Shadow adn shift reg configuration  */
    if (rv = pdpd_gmp_ddr_config_iq_4_generic_wrapper(v2d_num, apb_num, v2d_liveIQ_param))
   {
        printf("ERROR:GMP DDR GENERIC CONFIG for 4gsps FAILED\n");
        return rv; 
    }
#endif
#else
    /* GMP Static */
    if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
#endif //LIVEIQ_SAMPLES
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}
#endif  //LIVEIQ_SAMPLES

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
    if (rv = pdpd_gmp_static_config_iq_8(v2d_num, apb_num, num_gmp_terms, PASSTHRU_DELAY))
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
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_8(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_8(v2d_num, apb_num, num_ddr_terms, PASSTHRU_DELAY))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_8(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
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

#if LIVEIQ_SAMPLES

/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 4 Gsps
 *                  shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_iq_8_generic(int v2d_num, int apb_num ,v2d_liveIQ_param_t* v2d_liveIQ_param)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_DDR_TERMS;
#if LIVEIQ_SAMPLES 
#if !LIVEIQ_PASSTHRU_TEST
    /* GMP and DDR  Staic, dynamic Shadow adn shift reg configuration  */
    if (rv = pdpd_gmp_ddr_config_iq_8_generic_wrapper(v2d_num, apb_num, v2d_liveIQ_param))
   {
        printf("ERROR:GMP DDR GENERIC CONFIG  for 8gsps Failed\n");
        return rv; 
    }
#endif
#else
    /* GMP Static */
    if (rv = pdpd_gmp_static_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_gmp_terms, FLOW3_GMP_SHIFT_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_PASSTHRU_DELAY, pdpd_in_rate))
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
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config_iq_4(v2d_num, apb_num, num_ddr_terms, FLOW3_DDR_SHIFT_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
#endif //LIVEIQ_SAMPLES
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}
#endif  //LIVEIQ_SAMPLES
/**
 * @brief           Function to get the ref output file
 * @param [in]      post_filter_mode and test_config
 * @return          file_name
 */
char* get_ref_file_flow3(int post_filter_mode, int test_config)
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
                    return "ref_output_frac_os_1.txt";
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

