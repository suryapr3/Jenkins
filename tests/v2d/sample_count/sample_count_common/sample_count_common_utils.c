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
 * @file    flow2_common_utils.c
 * @brief   HOST Configuration code for sending the data from VEX to V2D and receving it back.
 * @details 1. Host utilitis for flow2.
 * @todo    Write documentation for source file sample_source.h
 */
/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "sample_count_common_utils.h"


/***********************************************
 * GLOBAL FUNCTION DEFINITIONS                 *
 ***********************************************/


/**
 * @brief           Function configuring the GMP Dynamic SHIFT reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and num_gmp_terms
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config(int v2d_num, int apb_num, int num_gmp_terms)
{
    int i, rv = 0;

/*

typedef union {
  struct {
    uint32_t SHIFT : 4;
    ///< Number of bits to right SHIFT the coefficient LUT result.
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 28;
    ///< Reserved
    ///< AccessType="RO" BitOffset="4" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_RD_MASK (0x0000000fU)
#define PDPD_GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_WR_MASK (0x0000000fU)
* */

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg;
    uint32_t SHIFT =0;

    pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.SHIFT = SHIFT;

    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].value = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_reg.value;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = 0;
    }

    //set the reamining vlaues same as the first value.
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value = i;
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg(SRP_BLOCK_V2D, v2d_num, \
                    APB_OFFSET_GEN(apb_num) + (g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[i].value, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config_tbl[0].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd GMP static regsiter from host

 * @param [in]      V2d Id , APB Id and num_gmp_terms
 * @return          Status
 */
int pdpd_gmp_static_config(int v2d_num, int apb_num, int num_gmp_terms)
{
    int i, rv = 0;
    /* GMP Static */
    pdpd_gmp_static_reg_t pdpd_gmp_static_reg;

/*
typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t  : 16;
    ///< Reserved
    ///< AccessType="RO" BitOffset="16" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_static_reg_t;
* */

/* The below parameters need to be varied while testing , currently set to these specific values for specific testing*/

    uint32_t ENABLE = 0x1;
    uint32_t SEL_MAG = PASSTHRU_DELAY;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = PASSTHRU_DELAY;

#if 1
    pdpd_gmp_static_reg.ENABLE= ENABLE;
    pdpd_gmp_static_reg.SEL_MAG = SEL_MAG;
    pdpd_gmp_static_reg.CONJ_EN = CONJ_EN;
    pdpd_gmp_static_reg,SEL_LIN= SEL_LIN;
#else
    pdpd_gmp_static_reg.value = ((SEL_LIN & 0x7F) << 9) | ((CONJ_EN & 0x1) << 8) | ((SEL_MAG & 0x7F) << 1) | (ENABLE & 0x1);
#endif

    /* populating the entire applicable num_gmp_terms GMP_STATIC with the same value
     * this can be randomised later for the value and GMP positions*/
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_gmp_terms; i++)
    {
        g_v2d_pdpd_gmp_static_config_tbl[i].value = pdpd_gmp_static_reg.value;
        printf ("static_value : %x\n", g_v2d_pdpd_gmp_static_config_tbl[i].value);
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_gmp_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_gmp_static_config_tbl[i].value, g_v2d_pdpd_gmp_static_config_tbl[0].mask, \
                    g_v2d_pdpd_gmp_static_config_tbl[0].name))
            return rv;
    }
    return rv;
}


/**
 * @brief           Function configuring the GMP Dynamic reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id ,num_gmp_terms, i_value and q_value
 * @return          Status
 */
int pdpd_gmp_dynamic_shdw_gmp_c_config(int v2d_num, int apb_num, int num_gmp_terms)
{

    int i, j, rv = 0;

    /*
     * typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t;

#define PDPD_GMP_DYNAMIC_SHDW_GMP_C_SHDW_DEFAULT (0x00000000U)
#define PDPD_GMP_DYNAMIC_SHDW_GMP_C_SHDW_RD_MASK (0x1fff1fffU)
#define PDPD_GMP_DYNAMIC_SHDW_GMP_C_SHDW_WR_MASK (0x1fff1fffU)
* */

    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg_t pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg;

    uint32_t Q = 0;
    uint32_t I = 0;
#if 1
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.Q = Q;
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.I = I;
#else
    pdpd_gmp_dynamic_shdw_gmp_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    /* initialuse all coeffcients nad SHIFT values to zero , then set only the required coefficinets as explained above
     * then do the regwrite at the correct offset */
    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value = ((i & 0x1FFF) << 16 | (i & 0x1FFF));
        }
    }

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_gmp_dynamic_shdw_gmp_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;

}

/**
 * @brief           Function configuring the DDR static regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and  num_ddr_terms
 * @return           Status
 */
int pdpd_ddr_static_config(int v2d_num, int apb_num, int num_ddr_terms)
{
    int i, rv = 0;

    /* DDR  Static */

/*
    typedef union {
  struct {
    uint32_t ENABLE : 1;
    ///< 0: This tap is not enabled
    ///< 1: This tap is enabled
    ///< AccessType="RW" BitOffset="0" ResetValue="0x0"
    uint32_t SEL_MAG : 7;
    ///< Magnitude sample delay
    ///< AccessType="RW" BitOffset="1" ResetValue="0x0"
    uint32_t CONJ_EN : 1;
    ///< 0: Do not conjugate the linear sample
    ///< 1: Conjugate the linear sample
    ///< AccessType="RW" BitOffset="8" ResetValue="0x0"
    uint32_t SEL_LIN : 7;
    ///< Linear sample delay
    ///< AccessType="RW" BitOffset="9" ResetValue="0x0"
    uint32_t SQU_EN : 1;
    ///< 0: Do not ENABLE the squared sample (DDR tap acts like GMP tap)
    ///< 1: Enable the squared sample
    ///< AccessType="RW" BitOffset="16" ResetValue="0x0"
    uint32_t SQU_SRC : 1;
    ///< 0: Squared sample is the magnitude squared
    ///< 1: Squared sample is the data squared
    ///< AccessType="RW" BitOffset="17" ResetValue="0x0"
    uint32_t SEL_SQU : 7;
    ///< Squared sample delay
    ///< AccessType="RW" BitOffset="18" ResetValue="0x0"
    uint32_t  : 7;
    ///< Reserved
    ///< AccessType="RO" BitOffset="25" ResetValue="None"
  } ;
  uint32_t value;
} pdpd_ddr_static_reg_t;
*/

    pdpd_ddr_static_reg_t pdpd_ddr_static_reg ;

    uint32_t ENABLE = 1;
    uint32_t SEL_MAG = PASSTHRU_DELAY;
    uint32_t CONJ_EN = 0;
    uint32_t SEL_LIN = PASSTHRU_DELAY;
    uint32_t SQU_EN = 0;
    uint32_t SQU_SRC = 0;
    uint32_t SEL_SQU = 0;

    pdpd_ddr_static_reg.ENABLE = ENABLE;
    pdpd_ddr_static_reg.SEL_MAG = SEL_MAG;
    pdpd_ddr_static_reg.CONJ_EN = CONJ_EN;
    pdpd_ddr_static_reg.SEL_LIN = SEL_LIN;
    pdpd_ddr_static_reg.SQU_EN = SQU_EN;
    pdpd_ddr_static_reg.SQU_SRC = SQU_SRC;
    pdpd_ddr_static_reg.SEL_SQU = SEL_SQU;

/* populating the entire applicable num_gmp_terms DDR_STATIC with the same value(g_v2d_pdpd_ddr_static_config_tbl[0])
 * this can be randomised later for the value and DDR positions*/

    g_v2d_pdpd_ddr_static_config_tbl[0].offset =  PDPD_DDR_STATIC0_OFFSET;
    g_v2d_pdpd_ddr_static_config_tbl[0].value = pdpd_ddr_static_reg.value; //set to 0 right now as no DDR term is configured
    g_v2d_pdpd_ddr_static_config_tbl[0].mask =  PDPD_DDR_STATIC_WR_MASK;
    g_v2d_pdpd_ddr_static_config_tbl[0].name =  "DDR_STATIC";

    printf("DDR_STATIC_VALUE: %x\n", pdpd_ddr_static_reg.value);

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_v2d_pdpd_ddr_static_config_tbl[i].value = pdpd_ddr_static_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a((PDPD_BASE_ADDR(v2d_num, apb_num) + (g_v2d_pdpd_ddr_static_config_tbl[0].offset) + (4 * i)), \
                    g_v2d_pdpd_ddr_static_config_tbl[i].value, g_v2d_pdpd_ddr_static_config_tbl[0].mask, \
                    g_v2d_pdpd_ddr_static_config_tbl[0].name))
            return rv;
    }

    return rv;
}

/**
 * @brief           Function configuring the DDR  Dynamic Coef Shadow reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and num_ddr_terms
 * @return          Status
 */
int ppdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config(int v2d_num, int apb_num, int num_ddr_terms)
{
    int i, j, rv = 0;

/*

typedef union {
  struct {
    uint32_t Q : 13;
    ///< Quadrature Phase Coefficient
    ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="13" ResetValue="None"
    uint32_t I : 13;
    ///< In Phase Coefficient
    ///< AccessType="RW/V" BitOffset="16" ResetValue="0x0"
    uint32_t  : 3;
    ///< Reserved
    ///< AccessType="RO" BitOffset="29" ResetValue="None"
  } ;
  uint32_t value;
}
*


#define PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_DEFAULT (0x00000000U)
#define PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_RD_MASK (0x1fff1fffU)
#define PDPD_DDR_DYNAMIC_SHDW_DDR_C_SHDW_WR_MASK (0x1fff1fffU)
* */
    uint32_t Q = 1;
    uint32_t I = 1;

    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg;
#if 0
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.Q = Q;
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.I = I;
#else
    pdpd_ddr_dynamic_shdw_ddr_c_shdw_reg.value = ((I & 0x1FFF) << 16) | (Q & 0x1FFF);
#endif

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            //set all coefficinets to zero
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = 0;
        }
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value = (i & 0x1FFF) << 16 | (i & 0x1FFF);
        }
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].offset + (0x200 * i) + (4 * j)), \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[i][j].value, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].mask, \
                        g_pdpd_ddr_dynamic_shdw_ddr_c_shdw_config_tbl[0][0].name))
                return rv;
        }
    }
    return rv;
}

/**
 * @brief           Function configuring the DDR  Dynamic Shift Shadow reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and num_ddr_terms
 * @return          Status
 */
int pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config(int v2d_num, int apb_num, int num_ddr_terms)
{
    int i, rv = 0;;
/*
 *
     typedef union {
      struct {
        uint32_t SHIFT : 4;
        ///< Number of bits to right SHIFT the coefficient LUT result.
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 28;
        ///< Reserved
        ///< AccessType="RO" BitOffset="4" ResetValue="None"
      } ;
  uint32_t value;
} pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t;

    #define PDPD_DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_DEFAULT (0x00000000U)
    #define PDPD_DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_RD_MASK (0x0000000fU)
    #define PDPD_DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_WR_MASK (0x0000000fU)
 *
 * */
    uint32_t SHIFT = DDR_SHIFT_VALUE;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_t pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg ;
    pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.SHIFT = SHIFT;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < num_ddr_terms; i++)
    {
        g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg.value;
    }

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].offset + (0x200 * i)), \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[i].value, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].mask, \
                    g_pdpd_ddr_dynamic_shdw_ddr_shift_shdw_config_tbl[0].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the NL_C  shadow reg from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          Status
 */
int pdpd_nl_c_shdw_reg_config(int v2d_num, int apb_num, int nl_value)
{
    int i, rv = 0;
    /*
    typedef union {
      struct {
        uint32_t NL : 13;
        ///< Nonlinear Magnitude LUT Coefficient
        ///< AccessType="RW/V" BitOffset="0" ResetValue="0x0"
        uint32_t  : 19;
        ///< Reserved
        ///< AccessType="RO" BitOffset="13" ResetValue="None"
      } ;
  uint32_t value;
} pdpd_nl_c_shdw_reg_t;

    #define PDPD_NL_C_SHDW_DEFAULT (0x00000000U)
    #define PDPD_NL_C_SHDW_RD_MASK (0x00001fffU)
    #define PDPD_NL_C_SHDW_WR_MASK (0x00001fffU)
    * */
    pdpd_nl_c_shdw_reg_t pdpd_nl_c_shdw_reg;
    uint32_t NL = nl_value;
    pdpd_nl_c_shdw_reg.NL = NL;


    for (i = 0; i < V2D_PDPD_MAX_C_LUT_SEGMENTS; i++)
    {
        g_pdpd_nl_c_shdw_config_tbl[i].value = 0;
    }

    for (i = 0; i < V2D_PDPD_MAX_C_LUT_SEGMENTS ; i++)
    {
        g_pdpd_nl_c_shdw_config_tbl[i].value = pdpd_nl_c_shdw_reg.value;

        if (rv = write_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (g_pdpd_nl_c_shdw_config_tbl[0].offset + (4 * i)), \
                    g_pdpd_nl_c_shdw_config_tbl[i].value, g_pdpd_nl_c_shdw_config_tbl[0].mask, g_pdpd_nl_c_shdw_config_tbl[0].name))
            return rv;
    }
    return rv;
}

/**
 * @brief           Function configuring the pdpd pass thru coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int passthru_reg_check(int v2d_num, int apb_num, int i_value, int q_value)
{
    int rv = 0, passthru_reg_value = 0;

    passthru_reg_value = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_PASSTHRU_C_LIVE_OFFSET, "PDPD_PASSTHRU_C_LIVE");
    if (passthru_reg_value == (q_value & 0x7FFF | (i_value & 0x7FFF) << 16))
    {
        printf("HOST: --- SUCCESS --- passthru reg_check pass\n");
    }
    else
    {
        printf("HOST: --- FAIL --- passthru reg_check failed\nexpected: %X, received: %X\n",
                (q_value & 0x7FFF | (i_value & 0x7FFF) << 16), passthru_reg_value);
        rv = 1;
    }
    return rv;
}

/**
 * @brief           Function configuring the nl_c_live coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and nl_value
 * @return          status
 */
int nl_reg_check(int v2d_num, int apb_num, int nl_c_value)
{
    int rv = 0, nl_c_value_read= 0, i = 0;

    for (i = 0; i < V2D_PDPD_MAX_C_LUT_SEGMENTS ; i++)
    {
        nl_c_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (PDPD_NL_C_LIVE0_OFFSET + (4 * i)), "PDPD_NL_C_LIVE");

        if (nl_c_value_read != nl_c_value)
        {
            rv |= 1;
            printf("HOST: --- ERROR --- nl value check failed\nexpected: %X, received: %X, index: %X\n", nl_c_value, nl_c_value_read, i);
        }

    }
}


/**
 * @brief           Function configuring the nl_c_live coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and c_lut_value
 * @return          status
 */
int gmp_c_lut_reg_check(int v2d_num, int apb_num, int c_lut_value)
{
    int rv = 0, c_lut_value_read = 0, i = 0, j = 0;


    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            c_lut_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_GMP_DYNAMIC_LIVE0_GMP_C_LIVE0_OFFSET + (0x200 * i) + (0x4 *j), \
                    "GMP_DYNAMIC_LIVE_GMP_C_LIVE");

            if(c_lut_value != c_lut_value_read)
            {
                rv |= 1;
                printf("HOST: --- ERROR --- GMP_C_LIVE value check failed\nexpected: %X, received: %X, i: %X, j: %X\n",
                        c_lut_value, c_lut_value_read, i, j);

            }
        }
    }

}

/**
 * @brief           Function configuring the nl_c_live coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int gmp_c_lut_update_check(int v2d_num, int apb_num, int num_gmp_terms)
{
    int rv = 0, c_lut_value_read = 0, i = 0, j = 0, c_lut_value_expected = 0;


    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        c_lut_value_expected = (((i % num_gmp_terms) & 0x1FFF) << 16) | ((i % num_gmp_terms) & 0x1FFF);
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            c_lut_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_GMP_DYNAMIC_LIVE0_GMP_C_LIVE0_OFFSET + (0x200 * i) + (0x4 *j), \
                    "GMP_DYNAMIC_LIVE_GMP_C_LIVE");

            if(c_lut_value_expected != c_lut_value_read)
            {
                rv |= 1;
                printf("HOST: --- ERROR --- GMP_C_LIVE value check failed\nexpected: %X, received: %X, i: %X, j: %X\n",
                        c_lut_value_expected, c_lut_value_read, i, j);

            }
        }
    }

}


/**
 * @brief           Function configuring the nl_c_live coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id and c_lut_value
 * @return          status
 */
int ddr_c_lut_reg_check(int v2d_num, int apb_num, int c_lut_value)
{
    int rv = 0, c_lut_value_read = 0, i = 0, j = 0;


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            c_lut_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_DDR_DYNAMIC_LIVE0_DDR_C_LIVE0_OFFSET + (0x200 * i) + (0x4 *j), \
                    "DDR_DYNAMIC_LIVE_DDR_C_LIVE");

            if(c_lut_value != c_lut_value_read)
            {
                rv |= 1;
                printf("HOST: --- ERROR --- GMP_C_LIVE value check failed\nexpected: %X, received: %X, i: %X, j: %X\n",
                        c_lut_value, c_lut_value_read, i, j);

            }
        }
    }
}

/**
 * @brief           Function configuring the nl_c_live coefficient sample count update regsiter from host
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int ddr_c_lut_update_check(int v2d_num, int apb_num, int num_ddr_terms)
{
    int rv = 0, c_lut_value_read = 0, i = 0, j = 0, c_lut_value_expected = 0;


    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        c_lut_value_expected = (((i % num_ddr_terms) & 0x1FFF) << 16) | ((i % num_ddr_terms) & 0x1FFF);
        for (j = 0; j < V2D_PDPD_MAX_C_LUT_SEGMENTS; j++)
        {
            c_lut_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + PDPD_DDR_DYNAMIC_LIVE0_DDR_C_LIVE0_OFFSET + (0x200 * i) + (0x4 *j), \
                    "DDR_DYNAMIC_LIVE_DDR_C_LIVE");

            if(c_lut_value_expected != c_lut_value_read)
            {
                rv |= 1;
                printf("HOST: --- ERROR --- GMP_C_LIVE value check failed\nexpected: %X, received: %X, i: %X, j: %X\n",
                        c_lut_value_expected, c_lut_value_read, i, j);

            }
        }
    }
}


/**
 * @brief           Function checking the gmp_shift register
 * @param [in]      V2d Id , APB Id and gmp_shift_value
 * @return          status
 */
int gmp_c_shift_reg_check(int v2d_num, int apb_num, int gmp_shift_value)
{
    int rv = 0, gmp_shift_value_read = 0, i = 0;

    for (i = 0; i < V2D_PDPD_MAX_GMP_TERMS; i++)
    {
        gmp_shift_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (PDPD_GMP_DYNAMIC_LIVE0_GMP_SHIFT_LIVE_OFFSET + (0x200 * i)), \
                "GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE");

        if (gmp_shift_value != gmp_shift_value_read)
        {
            rv |= 1;
            printf("HOST: --- ERROR --- nl value check failed\nexpected: %X, received: %X, index: %X\n",
                    gmp_shift_value, gmp_shift_value_read, i);
        }

    }
}

/**
 * @brief           Function checking the ddr_shift register
 * @param [in]      V2d Id , APB Id and ddr_shift_value
 * @return          status
 */
int ddr_c_shift_reg_check(int v2d_num, int apb_num, int ddr_shift_value)
{
    int rv = 0, ddr_shift_value_read = 0, i = 0;

    for (i = 0; i < V2D_PDPD_MAX_DDR_TERMS; i++)
    {
        ddr_shift_value_read = read_reg_18a(PDPD_BASE_ADDR(v2d_num, apb_num) + (PDPD_DDR_DYNAMIC_LIVE0_DDR_SHIFT_LIVE_OFFSET + (0x200 * i)), \
                "DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE");

        if (ddr_shift_value != ddr_shift_value_read)
        {
            rv |= 1;
            printf("HOST: --- ERROR --- nl value check failed\nexpected: %X, received: %X, index: %X\n",
                    ddr_shift_value, ddr_shift_value_read, i);
        }

    }
}


/**
 * @brief           Function configuring all the required  pdpd registers from host
 * @param [in]      V2d Id , APB Id and lut_mode
 * @return          status
 */
int flow3_configure_pdpd(int v2d_num, int apb_num, lut_mode_t lut_mode)
{
    int rv = 0;
    int i_value = 0, q_value = 0, update_passthru = 0, update_c_lut = 0, post_c_center_value = POST_C_CENTER_VALUE_UNITY_GAIN,
        cnt_value = SAMPLE_CNT_VALUE;

    i_value = PASSTHRU_I_COEFF;
    q_value = PASSTHRU_Q_COEFF;

    printf("INFO: PDPD configuration Started");
    if (rv = pdpd_config_reg_config(v2d_num, apb_num, lut_mode))
    {
        printf ("PDPD reg config failed\n");
        return rv;
    }
    if (rv = pdpd_control_reg_config(v2d_num, apb_num, update_passthru, update_c_lut))
    {
        printf("PDPD control reg config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_live_reg_config(v2d_num, apb_num, i_value, q_value))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_passthru_c_shdw_reg_config(v2d_num, apb_num, PASSTHRU_SHDW_I_COEFF, PASSTHRU_SHDW_Q_COEFF))
    {
        printf("PDPD passthru coeff config failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_ddr_reg_config(v2d_num, apb_num, lut_mode))
    {
        printf("ERROR:pdpd ddr reg config failed\n");
        return rv;
    }
    if (rv = pdpd_post_c_center_config(v2d_num, apb_num, post_c_center_value))
    {
        printf("ERROR: pdpd post_c_center config failed\n");
        return rv;
    }
    if (rv = pdpd_tcnt_update_passthru_config(v2d_num, apb_num, cnt_value))
    {
        printf("PDPD tcnt_update_passthru config failed\n");
        return rv;
    }
    cnt_value += INCR_SAMPLE_CNT_VALUE;
    if (rv = pdpd_tcnt_update_nl_lut_config(v2d_num, apb_num, cnt_value))
    {
        printf("PDPD tcnt_update_nl_lut_config failed\n");
        return rv;
    }
    cnt_value += INCR_SAMPLE_CNT_VALUE;
    if (rv = pdpd_tcnt_update_c_lut_config(v2d_num, apb_num, cnt_value))
    {
        printf("PDPD tcnt_update_c_lut_config failed\n");
        return rv;
    }

    return rv;
}

/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id and pdpd_rate
 * @return          status
 */
int pdpd_gmp_ddr_reg_config(int v2d_num, int apb_num, lut_mode_t lut_mode)
{
    int rv = 0;

    switch (lut_mode)
    {
        case PDPD_LUT_48:
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
            rv = pdpd_gmp_ddr_reg_config_lut_48(v2d_num, apb_num);
            break;
        case PDPD_LUT_24:
        /* 16GMP terms and 8 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_lut_24(v2d_num, apb_num);
            break;
        case PDPD_RATE_IQ_8:
        /* 8GMP terms and 4 DDR terms */
            rv = pdpd_gmp_ddr_reg_config_lut_12(v2d_num, apb_num);
            break;
        default:
            printf(" PDPD RATE NOT supported \n");
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
int pdpd_gmp_ddr_reg_config_lut_48(int v2d_num, int apb_num)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS;
    num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config(v2d_num, apb_num, 0))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_gmp_dynamic_live_gmp_c_config(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_live_gmp_shift_live_reg_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }


    /* This values in the shadow register will be moved to corresponding live register at the programmed SAMPLE COUNT value*/
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config(v2d_num, apb_num, 0))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic live ( NOT required for AXI1 and VEX config , but needed for APB updtes */
    if (rv = pdpd_ddr_dynamic_live_ddr_c_live_reg_config(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_live_ddr_shift_live_reg_config( v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }


    /* This values in the shadow register will be moved to corresponding live register at the programmed SAMPLE COUNT value*/
    if (rv = ppdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_shdw_reg_config(v2d_num, apb_num, NL_C_VALUE))
    {
        printf("ERROR:NL_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}


/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 4 Gsps
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_lut_24(int v2d_num, int apb_num)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS / 2;
    num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS / 2;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config_lut_24(v2d_num, apb_num, 0, 0))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_gmp_dynamic_live_gmp_c_config(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_live_gmp_shift_live_reg_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* GMP C dynamic shadow ( not a must on APB config, but needed for AXI4 and VEX updates of coeffs */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_lut_24(v2d_num, apb_num, 0, 0))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic live ( NOT required for AXI1 and VEX config , but needed for APB updtes */
    if (rv = pdpd_ddr_dynamic_live_ddr_c_live_reg_config(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_live_ddr_shift_live_reg_config( v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }


    /* DDR C dynamic shadow ( not a must on APB config, but needed for AXI4 and VEX updates of coeffs */
    if (rv = ppdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_shdw_reg_config(v2d_num, apb_num, NL_C_VALUE))
    {
        printf("ERROR:NL_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }


    return rv;
}


/**
 * @brief           Function configuring the pdpd GMP and DDR coefficient regsiter from host for sample rate 8 Gsps
 * both live and shadow resister writes are implemented
 * @param [in]      V2d Id , APB Id
 * @return          status
 */
int pdpd_gmp_ddr_reg_config_lut_12(int v2d_num, int apb_num)
{

    int i, num_gmp_terms, num_ddr_terms, rv = 0;

    num_gmp_terms = V2D_PDPD_MAX_GMP_TERMS / 4;
    num_ddr_terms = V2D_PDPD_MAX_DDR_TERMS / 4;

    /* GMP Static */
    if (rv = pdpd_gmp_static_config_lut_12(v2d_num, apb_num, 0, 0))
    {
        printf("ERROR:GMP STATIC_CONFIG failed\n");
        return rv;
    }

    if (rv = pdpd_gmp_dynamic_live_gmp_c_config(v2d_num, apb_num, num_gmp_terms, GMP_C_I_VALUE, GMP_C_Q_VALUE))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_live_gmp_shift_live_reg_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_LIVE_GMP_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* GMP C dynamic shadow ( not a must on APB config, but needed for AXI4 and VEX updates of coeffs */
    if (rv = pdpd_gmp_dynamic_shdw_gmp_c_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_C_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_gmp_dynamic_shdw_gmp_shift_shdw_config(v2d_num, apb_num, num_gmp_terms))
    {
        printf("ERROR:GMP_DYNAMIC_SHDW_GMP_SHIFT_SHDW_CONFIG failed\n");
        return rv;
    }

    /* DDR STATIC */
    if (rv = pdpd_ddr_static_config_lut_12(v2d_num, apb_num, 0, 0))
    {
        printf("ERROR:DDR_STATIC_CONFIG failed\n");
        return rv;
    }

    /* DDR dynamic live ( NOT required for AXI1 and VEX config , but needed for APB updtes */
    if (rv = pdpd_ddr_dynamic_live_ddr_c_live_reg_config(v2d_num, apb_num, num_ddr_terms, DDR_C_I_VALUE, DDR_C_Q_VALUE))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_live_ddr_shift_live_reg_config( v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_LIVE_DDR_SHIFT_LIVE_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_live_reg_config(v2d_num, apb_num, NL_C_VALUE))
    {
        printf("ERROR:NL_C_LIVE_REG_CONFIG failed\n");
        return rv;
    }

    /* DDR C dynamic shadow ( not a must on APB config, but needed for AXI4 and VEX updates of coeffs */
    if (rv = ppdpd_ddr_dynamic_shdw_ddr_c_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_ddr_dynamic_shdw_ddr_shift_shdw_reg_config(v2d_num, apb_num, num_ddr_terms))
    {
        printf("ERROR:DDR_DYNAMIC_SHDW_DDR_SHIFT_SHDW_REG_CONFIG failed\n");
        return rv;
    }
    if (rv = pdpd_nl_c_shdw_reg_config(v2d_num, apb_num, NL_C_VALUE))
    {
        printf("ERROR:NL_C_SHDW_REG_CONFIG failed\n");
        return rv;
    }

    return rv;
}

