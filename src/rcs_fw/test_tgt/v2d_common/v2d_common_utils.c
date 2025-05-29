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
 * @file    v2d_common_utils.c
 * @brief   functions which will be used by V2D emulation.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */

/***********************************************
 * LOCAL INCLUDE STATEMENTS                    *
 ***********************************************/
#include "v2d_common_utils.h"

/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/
const int g_v2d_instance_in_quad[][V2D_PER_QUAD] = {
    {0, 1},
    {2, 3},
    {4, 5},
    {6, 7}
};

const int g_vex_instance_in_v2d[][VEX_PER_V2D] = {
    {0, 1, 8, 9},
    {2, 3, 10, 11},
    {4, 5, 12, 13},
    {6, 7, 14, 15}
};

/*Samples per block for the PDPD rate*/
const int g_samples_per_blk[2][5] = {
    {256, 512, 1024, 2048, 4096},
    {384, 768, 1536, 3072, 6144},
};

rcs_dmac_ch1_ctl_reg_t dmac_ctl_reg = {
    .SRC_TR_WIDTH = 4,//2,//1,//4, // 128 bit.
    .DST_TR_WIDTH = 4,//2,//1,//4,
    .SHADOWREG_OR_LLI_VALID = 1, // valid.
    .SRC_MSIZE = 4,              // 4x128 burst.
    .DST_MSIZE = 4,
    .ARLEN_EN = 1, // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1, // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR=1,
    .DST_STAT_EN=1,
    .SRC_STAT_EN=1,
    .NONPOSTED_LASTWRITE_EN=0,
};

rcs_dmac_ch2_ctl_reg_t dmac_ctl2_reg = {
    .SRC_TR_WIDTH = 4,//2,//1,//4, // 128 bit.
    .DST_TR_WIDTH = 4,//2,//1,//4,
    .SHADOWREG_OR_LLI_VALID = 1, // valid.
    .SRC_MSIZE = 4,              // 4x128 burst.
    .DST_MSIZE = 4,
    .ARLEN_EN = 1, // hw choose burst.
    .ARLEN = 0x5,
    .AWLEN_EN = 1, // hw choose burst.
    .AWLEN = 0x3,
    .IOC_BLKTFR=1,
    .DST_STAT_EN=1,
    .SRC_STAT_EN=1,
    .NONPOSTED_LASTWRITE_EN=0,
};

rcs_dmac_ch1_cfg_reg_t dmac_cfg_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
    .DST_MULTBLK_TYPE = 3, // LLI
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,        // Flow control select: M2M
    .HS_SEL_SRC = 0,   // SW handshake
    .HS_SEL_DST = 1,   //
    .SRC_HWHS_POL = 0, // HS polarity
    .DST_HWHS_POL = 0, //
    .SRC_PER = 1,      // HS interface sel
    .DST_PER = 1,
    .CH_PRIOR = 0x7,    // Prio (don't care).
    .LOCK_CH = 0,     // Keep channel (don't care).
    .LOCK_CH_L = 1,   // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF, // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};

rcs_dmac_ch2_cfg_reg_t dmac_cfg2_reg = {.SRC_MULTBLK_TYPE = 3, // LL!
    .DST_MULTBLK_TYPE = 3, // LLI
    .RD_UID = 0,
    .WR_UID = 0,
    .TT_FC = 0,        // Flow control select: M2M
    .HS_SEL_SRC = 0,   // SW handshake
    .HS_SEL_DST = 1,   //
    .SRC_HWHS_POL = 0, // HS polarity
    .DST_HWHS_POL = 0, //
    .SRC_PER = 1,      // HS interface sel
    .DST_PER = 1,
    .CH_PRIOR = 0x7,    // Prio (don't care).
    .LOCK_CH = 0,     // Keep channel (don't care).
    .LOCK_CH_L = 1,   // Keep channel duration (don't care).
    .SRC_OSR_LMT = 0xF, // Outstanding transaction limit
    .DST_OSR_LMT = 0x6
};

/**
 * @brief           Function for configuring the BFN registers
 * @param [in]      quad_instance, capture_enable, size per channel
 * @return          none
 */
void quad_configure_v2d_bfn(int quad_instance, int capture_enable, int size, int match_value)
{
    int v2d_base = 0, lc = 0;

    bfn_csr_general_csr_reg_t bfn_csr_general_csr_reg = {.value = BFN_CSR_GENERAL_CSR_DEFAULT};

    /*Enabling the BFN events*/
    bfn_csr_bfne_cfg_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CFG_DEFAULT};
    bfne_config_reg.ENABLE = 1;

    bfn_csr_cap_data_ctrl_reg_t cap_data_ctrl_reg = {.value = BFN_CSR_CAP_DATA_CTRL_DEFAULT};

    bfn_csr_start_lm_reg_t bfn_csr_start_lm_reg = {.value = BFN_CSR_START_LM_MATCH_EN_BF_MSK};

    switch (quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*Enabling the BFN start Enable*/
    bfn_csr_general_csr_reg= *(BFN_CSR_GENERAL_CSR_REG(v2d_base));
    bfn_csr_general_csr_reg.value |= BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
    *(BFN_CSR_GENERAL_CSR_REG(v2d_base)) = bfn_csr_general_csr_reg;

    /*Enabling the BFN EVENT in the BFN config*/
    *(BFN_CSR_BFNE_CFG0_REG(v2d_base)) = bfne_config_reg;

    bfne_config_reg.value = BFN_CSR_BFNE_CFG_DEFAULT;
    bfne_config_reg.ENABLE = 1;
    bfne_config_reg.MODE = 0;   // SINGLE
    bfne_config_reg.OUTPUT_MODE = 1; // pulse

    /*Writing the LM_START values with the required match values
     *for all the required channels*/
    bfn_csr_start_lm_reg.MATCH_VALUE = match_value;

    if (capture_enable)
    {
        /*CAP_DATA_CTRL register population*/
        cap_data_ctrl_reg.CAPTURE_EN_0 = 1;
        cap_data_ctrl_reg.CAPTURE_SIZE_0 = size;
        cap_data_ctrl_reg.CAPTURE_EN_1 = 1;
        cap_data_ctrl_reg.CAPTURE_SIZE_1 = size;
    }

    for (lc = 0; lc < V2D_PER_QUAD; lc++)
    {
        v2d_base = v2d_base + (lc * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE));

        if (capture_enable)
        {
            *(BFN_CSR_START_LM2_REG(v2d_base)) = bfn_csr_start_lm_reg;
            *(BFN_CSR_START_LM3_REG(v2d_base)) = bfn_csr_start_lm_reg;
            ((bfn_csr_t*) (v2d_base)) -> CAP_DATA_CTRL = cap_data_ctrl_reg;
        }
    }
}

/**
 * @brief           Function for sync verification of QUAD
 * @param [in]      none
 * @return          none
 */
void quad_bfn_sync_ver(int quad_instance, int drf_clock)
{
    uint32_t rv = 0, v2d_num = 0, buff_index = 0, v2d_base = 0, v2d_index = 0, rcs_timestamp_value = 0, v2d_timestamp_value = 0,
             adjustment_value[V2D_PER_QUAD] = {0};

    // soft reset Master BFN
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x1;
    INTRINSIC_BARRIER;
    RCS_TIMER_GPREG -> ICTRL.SOFT_RESET = 0x0;
    INTRINSIC_BARRIER;

    // soft reset Follower V2D BFN
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x1;
        INTRINSIC_BARRIER;
        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.SOFT_RESET = 0x0;
        INTRINSIC_BARRIER;
    }

    if (drf_clock)
    {
        RCS_TIMER_GPREG->TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = 0x32; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // Set the SYSREF
    RCS_TIMER_GPREG -> OPPS_VAL_TIMESYNC_CTRL.value = TIMESYNC_CTRL;    //0x00030031
    INTRINSIC_BARRIER;

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = 0;
        INTRINSIC_BARRIER;

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_LCNT_INC.value = 0x1;
        INTRINSIC_BARRIER;

        if (drf_clock)
        {
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = TEN_MS_CNT_VALUE_1P5;
            INTRINSIC_BARRIER;
        }
        else
        {
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_TEN_MS_CNT.value = BFN_CSR_AW_ISYNC_TEN_MS_CNT_DEFAULT;
            INTRINSIC_BARRIER;
        }

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CNT_ADJ.value = BFN_CSR_AW_ISYNC_CNT_ADJ_DEFAULT;
        INTRINSIC_BARRIER;

        // Program the CTRL command for follower BFN to full load
        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_INIT; // 0xB2; // ISYNC + init command
    INTRINSIC_BARRIER;

    // preload BFN values used with SYSREF load
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.LOAD_READ = 1;
        INTRINSIC_BARRIER;
    }

    RCS_TIMER_GPREG -> ICTRL.LOAD_READ = 0x1;
    INTRINSIC_BARRIER;

    quad_v2d_bfn_capture(quad_instance);

    rcs_timestamp_value = (RCS_TIMER_GPREG) -> BFN_CNT_VAL2_REG0.value;

    /*Calculate the adjustment values and preload the values with INIT command*/
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        v2d_timestamp_value = ((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT_SYNC.value;

        if (v2d_timestamp_value > rcs_timestamp_value)
        {
            adjustment_value[v2d_num] = v2d_timestamp_value - rcs_timestamp_value;
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = 0xFF000000 | (0x960000 - adjustment_value[v2d_num]);
            INTRINSIC_BARRIER;
        }
        else
        {
            adjustment_value[v2d_num] = rcs_timestamp_value - v2d_timestamp_value;
            ((bfn_csr_t*) v2d_base) -> AW_ISYNC_INC_PRE.value = adjustment_value[v2d_num];
            INTRINSIC_BARRIER;
        }

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_INIT;  //0x2
        INTRINSIC_BARRIER;
    }

    // trigger the isync_pulse
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_ISYNC_CMD; // 0xB0; // ISYNC command
    INTRINSIC_BARRIER;


}

/**
 * @brief           Function for triggering the BFN capture command
 * @param [in]      none
 * @return          none
 */
void quad_v2d_bfn_capture(int quad_instance)
{
    int v2d_num = 0, v2d_index = 0, v2d_base = 0;

    // Program the CTRL command for follower BFN to capture
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);

        ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.value = BFN_COM_ISYNC_CMD_CAP;  //0x7
        INTRINSIC_BARRIER;
    }

    // Program Master BFN for preset command along with ISYNC
    RCS_TIMER_GPREG->ICTRL.value = BFN_COM_SYNC_CAP; // 0xB7; // ISYNC + capture command
    INTRINSIC_BARRIER;

}

/**
 * @brief           Function for configuring the BFN registers
 * @param [in]      v2d_num, apb_num, capture_enable, size and match_value
 * @return          none
 */
void configure_v2d_bfn(int v2d_num, int apb_num, int capture_enable, int size, int match_value)
{
    int v2d_base = 0, lc = 0, quad_instance = 0;

    bfn_csr_general_csr_reg_t bfn_csr_general_csr_reg = {.value = BFN_CSR_GENERAL_CSR_DEFAULT};

    /*Enabling the BFN events*/
    bfn_csr_bfne_cfg_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CFG_DEFAULT};
    bfne_config_reg.ENABLE = 1;

    bfn_csr_cap_data_ctrl_reg_t cap_data_ctrl_reg = {.value = BFN_CSR_CAP_DATA_CTRL_DEFAULT};

    bfn_csr_start_lm_reg_t bfn_csr_start_lm_reg = {.value = BFN_CSR_START_LM_MATCH_EN_BF_MSK};

    quad_instance = get_quad_instance(v2d_num);

    switch (quad_instance)
    {
    case 0:
        v2d_base = V2D0_BFN_CSR_BASE;
        break;
    case 1:
        v2d_base = V2D2_BFN_CSR_BASE;
        break;
    case 2:
        v2d_base = V2D4_BFN_CSR_BASE;
        break;
    case 3:
        v2d_base = V2D6_BFN_CSR_BASE;
        break;
    }

    /*Enabling the BFN start Enable should be done only for even V2D's*/
    bfn_csr_general_csr_reg= *(BFN_CSR_GENERAL_CSR_REG(v2d_base));
    bfn_csr_general_csr_reg.value |= BFN_CSR_GENERAL_CSR_BFN_START_EN_BF_MSK;
    *(BFN_CSR_GENERAL_CSR_REG(v2d_base)) = bfn_csr_general_csr_reg;

    /*Enabling the BFN EVENT in the BFN config*/
    *(BFN_CSR_BFNE_CFG0_REG(v2d_base)) = bfne_config_reg;

    /*Writing the LM_START values with the required match values
     *for all the required channels*/
    bfn_csr_start_lm_reg.MATCH_VALUE = match_value;

    v2d_base = V2D_BFN_BASE(v2d_num);

    if (0 == apb_num)
    {
        *(BFN_CSR_START_LM2_REG(v2d_base)) = bfn_csr_start_lm_reg;
    }
    else
    {
        *(BFN_CSR_START_LM3_REG(v2d_base)) = bfn_csr_start_lm_reg;
    }

    cap_data_ctrl_reg = ((bfn_csr_t*) (v2d_base)) -> CAP_DATA_CTRL;

    if (capture_enable)
    {
        //Data Ctrl registers
        if (0 == apb_num)
        {
            cap_data_ctrl_reg.CAPTURE_EN_0 = 1;
            cap_data_ctrl_reg.CAPTURE_SIZE_0 = size;   /*1MB Data or 256k samples*/
        }
        else
        {
            cap_data_ctrl_reg.CAPTURE_EN_1 = 1;
            cap_data_ctrl_reg.CAPTURE_SIZE_1 = size;   /*1MB Data or 256k samples*/
        }

        ((bfn_csr_t*) (v2d_base)) -> CAP_DATA_CTRL = cap_data_ctrl_reg;
    }

}

/**
 * @brief           Function for configuring BFN cap_mode_ctrl register
 * @param [in]      v2d_num, on_off mode enable, continuous_mode, offset_count and onset_count
 * @return          void
 */
void configure_v2d_cap_mode_ctrl(int v2d_num, int on_off_mode_en, int continuous_mode_en, int off_set_count, int on_set_count)
{
    bfn_csr_cap_mode_ctrl_reg_t cap_mode_ctrl_reg = {.value = BFN_CSR_CAP_MODE_CTRL_DEFAULT};
    uint32_t v2d_base;

    cap_mode_ctrl_reg.ONOFF_MODE_EN = on_off_mode_en;
    cap_mode_ctrl_reg.CONTINUOUS_MODE = continuous_mode_en;
    cap_mode_ctrl_reg.OFF_SET_COUNT = off_set_count;
    cap_mode_ctrl_reg.ON_SET_COUNT = on_set_count;

    v2d_base = V2D_BFN_BASE(v2d_num);
    ((bfn_csr_t*) (v2d_base)) -> CAP_MODE_CTRL = cap_mode_ctrl_reg;

}

/**
 * @brief           Function for configuring BFN config register
 * @param [in]      v2d_num, reg_intance, output_mode and event_mode
 * @return          void
 */
void configure_v2d_bfn_config(int v2d_num, int reg_instance, bfn_event_output_mode_t output_mode, bfn_event_mode_t event_mode)
{
    bfn_csr_bfne_cfg_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CFG_DEFAULT};
    uint32_t v2d_base;

    bfne_config_reg.ENABLE = 1;
    bfne_config_reg.MODE = event_mode;   // SINGLE
    bfne_config_reg.OUTPUT_MODE = output_mode; // toggle

    v2d_base = V2D_BFN_BASE(v2d_num);
    ((bfn_csr_t*) (v2d_base)) -> BFNE_CFG[reg_instance] = bfne_config_reg;
}

/**
 * @brief           Function for configuring BFN config register for a QUAD
 * @param [in]      quad_instance, reg_intance, output_mode and event_mode
 * @return          void
 */
void quad_configure_v2d_bfn_config(int quad_instance, int reg_instance, bfn_event_output_mode_t output_mode, bfn_event_mode_t event_mode)
{

    bfn_csr_bfne_cfg_reg_t bfne_config_reg = {.value = BFN_CSR_BFNE_CFG_DEFAULT};
    int v2d_num = 0, v2d_index = 0;
    uint32_t v2d_base;

    bfne_config_reg.ENABLE = 1;
    bfne_config_reg.MODE = event_mode;   // SINGLE
    bfne_config_reg.OUTPUT_MODE = output_mode; // toggle

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);
        ((bfn_csr_t*) (v2d_base)) -> BFNE_CFG[reg_instance] = bfne_config_reg;
    }
}

/**
 * @brief           Function for configuring BFN INCR register
 * @param [in]      v2d_num, reg_instance and value
 * @return          void
 */
void configure_v2d_bfn_incr(int v2d_num, int reg_instance, int value)
{
    bfn_csr_bfne_incr_reg_t bfne_incr_reg = {.value = BFN_CSR_BFNE_INCR_DEFAULT};
    uint32_t v2d_base;

    bfne_incr_reg.value = value;

    v2d_base = V2D_BFN_BASE(v2d_num);
    ((bfn_csr_t*) (v2d_base)) -> BFNE_INCR[reg_instance] = bfne_incr_reg;
}

/**
 * @brief           Function for configuring BFN INCR register for QUAD
 * @param [in]      quad_instance, reg_instance and value
 * @return          void
 */
void quad_configure_v2d_bfn_incr(int quad_instance, int reg_instance, int value)
{
    bfn_csr_bfne_incr_reg_t bfne_incr_reg = {.value = BFN_CSR_BFNE_INCR_DEFAULT};
    int v2d_num = 0, v2d_index = 0;
    uint32_t v2d_base;

    bfne_incr_reg.value = value;

    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[quad_instance][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);
        ((bfn_csr_t*) (v2d_base)) -> BFNE_INCR[reg_instance] = bfne_incr_reg;
    }
}

/**
 * @brief           Function for getting the quad instnce from v2d_num
 * @param [in]      v2d_num
 * @return          quad instance
 */
int get_quad_instance(int v2d_num)
{
    int quad_instance = 0;

    if ((0 == v2d_num) || (1 == v2d_num))
    {
        quad_instance = 0;
    }
    else if ((2 == v2d_num) || (3 == v2d_num))
    {
        quad_instance = 1;
    }
    else if ((4 == v2d_num) || (5 == v2d_num))
    {
        quad_instance = 2;
    }
    else if ((6 == v2d_num) || (7 == v2d_num))
    {
        quad_instance = 3;
    }

    return quad_instance;

}

/**
 * @brief           Function for generating the REF block
 * @param [in]      pointer to ref pattern array and samples per block
 * @return          NONE
 */
void generate_ref_block(int *ref_pattern, int samples_per_block)
{
    int i = 0, j = 0, data_index = 0;
    int vectors_per_block = samples_per_block / NUM_OF_ELEMENTS_PER_VEC;

    for (i = 0; i < vectors_per_block; i++)
    {
        for (j = 0; j < NUM_OF_ELEMENTS_PER_VEC; j++)
        {
            ref_pattern[data_index] = (((i * 2 * NUM_OF_ELEMENTS_PER_VEC + (j * 2)) << 16) | (i * NUM_OF_ELEMENTS_PER_VEC + (j * 2)));
            data_index++;
        }
    }
}

/**
 * @brief           Function for comparing the mem_fb memory in repeat mode
 * @param [in]      pointer to structure of mem_compare.
 * @return          Zero in case of success or block number in case of failure
 */
int mem_fb_compare_repeat(fb_mem_compare_t *fb_mem_compare)
{
    /*This function has written considering the ping address always be sector 0*/
    int read_address[2] = {0};  // for ping and pong addresses
    int lc = 0, additional_factor = 0, start_skip_blocks = 0, add_val = 0, rv = 0, blc_cnt = 0, skip_blocks_between_captures = 0;
    uint32_t fb_mem_config_base = 0, sram_base = 0, v2d_time = 0, capture_end_time = 0, v2d_base = 0, count = 0;

    fb_mem_config_base = ((fb_mem_compare -> v2d_num) > 3) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;
    sram_base = ((fb_mem_compare -> v2d_num) > 3) ? MEM_FB1_SRAM_BASE : MEM_FB0_SRAM_BASE;
    v2d_base = V2D_BFN_BASE((fb_mem_compare -> v2d_num));
    additional_factor = (fb_mem_compare -> add_factor);

    if (((fb_mem_compare->v2d_num) % 4) < 2)
    {
        read_address[0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT0.value) * 64);  // Ping address in Bytes
        read_address[1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR0.value) * 64);  // Pong address in Bytes
    }
    else
    {
        read_address[0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT1.value) * 64);  // Ping address in Bytes
        read_address[1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR0.value) * 64);  // Pong address in Bytes
    }

    /*capture end time for the first capture*/
    capture_end_time = ((fb_mem_compare -> capture_start_value) + ((fb_mem_compare -> capture_blocks) * (fb_mem_compare -> clks_per_blk)));
    capture_end_time %= ((bfn_csr_t*) v2d_base) -> AW_ISYNC_TEN_MS_CNT.value;

    /*Calculate the skip blocks*/
    start_skip_blocks = (fb_mem_compare -> capture_delay_value) / (fb_mem_compare -> clks_per_blk);
    skip_blocks_between_captures = (fb_mem_compare -> skip_cycles) / (fb_mem_compare -> clks_per_blk);

    add_val = additional_factor + (start_skip_blocks * additional_factor);

    /*Wait till first capture done*/
    do
    {
        v2d_time = get_current_time(fb_mem_compare -> v2d_num);
        v2d_time &= 0xFFFFFF;
    }while(v2d_time < capture_end_time);

    dram_buff[5] = v2d_time;

    for (lc = 0 ; lc < (fb_mem_compare -> num_captures); lc++)
    {
        int start_address = read_address[lc % 2];

        for (blc_cnt = 0; blc_cnt < (fb_mem_compare -> capture_blocks); blc_cnt++)
        {
            if (x_capture_compare((int *) start_address, (fb_mem_compare -> ref_pattern), (fb_mem_compare -> samples_per_block), add_val))
                return (count + 1);

            add_val = add_val + additional_factor;
            start_address += ((fb_mem_compare -> samples_per_block) * 4);
            count++;
        }

        /*Calculate capture end time for subsequent captures and wait*/
        capture_end_time += (fb_mem_compare -> skip_cycles) + ((fb_mem_compare -> capture_blocks) * (fb_mem_compare -> clks_per_blk));
        capture_end_time %= ((bfn_csr_t*) v2d_base) -> AW_ISYNC_TEN_MS_CNT.value;

        do
        {
            v2d_time = get_current_time(fb_mem_compare -> v2d_num);
            v2d_time &= 0XFFFFFF;
        }while(v2d_time < capture_end_time);
        dram_buff[5] = v2d_time;
        dram_buff[6] = get_current_time(fb_mem_compare -> v2d_num);


        /*Modify the add valus based the blocks that will be skipped between captures*/
        add_val += (skip_blocks_between_captures * additional_factor);
    }

    dram_buff[6] = get_current_time(fb_mem_compare -> v2d_num);

    return rv;
}

/**
 * @brief           Function for comparing the mem_fb memory for a QUAD in repeat mode
 * @param [in]      pointer to array of ref pattern, pointer to structure of mem_compare.
 * @return          Zero in case of success or block number in case of failure
 */
int quad_mem_fb_compare_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_params)
{
    int read_address[4][2] = {0};    // Ping and Pong address for 4 antennas
    int lc = 0, additional_factor = 0, skip_blocks_antenna[5] = {0}, add_val = 0, rv = 0xFFFF, blc_cnt = 0, skip_blocks_between_captures = 0,
        v2d_num = 0, buffer_index = 0, v2d_index = 0, count = 0, antenna_index = 0, cnt = 0, ant_num = 0;
    uint32_t fb_mem_config_base = 0, sram_base = 0, v2d_time = 0, capture_end_time[4] = {0}, v2d_base = 0, clks_per_blk = 0,
             capture_start_value[4] = {0}, bfn_incr_value = 0, samples_per_block = 0, start_address = 0;

    v2d_num = g_v2d_instance_in_quad[(v2d_rcs_host_params->quad_instance)][v2d_index];
    fb_mem_config_base = (v2d_num > 3) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;
    sram_base = (v2d_num > 3) ? MEM_FB1_SRAM_BASE : MEM_FB0_SRAM_BASE;
    additional_factor = v2d_rcs_host_params->add_factor;
    clks_per_blk = (v2d_rcs_host_params -> drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    add_val = additional_factor;
    samples_per_block = g_samples_per_blk[(v2d_rcs_host_params -> drf_clock)][(v2d_rcs_host_params -> pdpd_rate)];

    if ((v2d_num % 4) < 2)
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT0.value) * 64);  // Ping address in Bytes
    }
    else
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT1.value) * 64);  // Ping address in Bytes
    }

    read_address[1][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR0.value) * 64);  // for second antenna
    read_address[2][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR1.value) * 64);  // for third antenna
    read_address[3][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR2.value) * 64);  // for fourth antenna

    // Pong addresses
    read_address[0][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR3.value) * 64);  // for first antenna
    read_address[1][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR4.value) * 64);  // for second antenna
    read_address[2][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR5.value) * 64);  // for third antenna
    read_address[3][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR6.value) * 64);  // for fourth antenna

    /*Populate capture start value*/
    for (v2d_index = 0; v2d_index < V2D_PER_QUAD; v2d_index++)
    {
        v2d_num = g_v2d_instance_in_quad[(v2d_rcs_host_params -> quad_instance)][v2d_index];
        v2d_base = V2D_BFN_BASE(v2d_num);
        capture_start_value[antenna_index] = ((bfn_csr_t*) (v2d_base)) -> BFNE_START[1].value;
        capture_end_time[antenna_index] = capture_start_value[antenna_index] + ((v2d_rcs_host_params -> capture_blocks) * clks_per_blk);
        antenna_index++;
        capture_start_value[antenna_index] = ((bfn_csr_t*) (v2d_base)) -> BFNE_START[2].value;
        capture_end_time[antenna_index] = capture_start_value[antenna_index] + ((v2d_rcs_host_params -> capture_blocks) * clks_per_blk);
        antenna_index++;
    }

    /*Get the BFN increment value*/
    bfn_incr_value = ((bfn_csr_t*) (v2d_base)) -> BFNE_INCR[1].value;

    /*Calculate the blocks need to be skipped due to delay in antenna capture*/
    skip_blocks_antenna[0] = (v2d_rcs_host_params -> ant0_cycles) / clks_per_blk;
    skip_blocks_antenna[1] = (v2d_rcs_host_params -> ant1_cycles) / clks_per_blk;
    skip_blocks_antenna[2] = (v2d_rcs_host_params -> ant2_cycles) / clks_per_blk;
    skip_blocks_antenna[3] = (v2d_rcs_host_params -> ant3_cycles) / clks_per_blk;

    /*skip blocks beteen captures*/
    skip_blocks_between_captures = (v2d_rcs_host_params -> skip_cycles) / clks_per_blk;
    add_val += (skip_blocks_antenna[0] * additional_factor);

    for (cnt = 0; cnt < (v2d_rcs_host_params -> num_captures); cnt++)
    {
        dram_buff[5] = get_current_time(v2d_num);
        for (ant_num = 0; ant_num < (v2d_rcs_host_params -> num_antennas); ant_num++)
        {
            /*Wait till capture was ended*/
            do
            {
                v2d_time = get_current_time(v2d_num);
            }while(v2d_time < (capture_end_time[ant_num] + (cnt * bfn_incr_value)));

            start_address = read_address[ant_num][cnt % 2];

            for (lc = 0; lc < (v2d_rcs_host_params -> capture_blocks); lc++)
            {
                dram_buff[10] = start_address;
                if (x_capture_compare((int *) start_address, ref_pattern, samples_per_block, add_val))
                    return (count + 1);

                add_val += additional_factor;
                start_address += (samples_per_block * 4);
                count++;
            }
            add_val += (skip_blocks_antenna[ant_num + 1] * additional_factor);
        }
        add_val += (skip_blocks_between_captures * additional_factor);
        dram_buff[11] = get_current_time(v2d_num);
    }

    dram_buff[12] = 0xFFFF;
    return count;
}


/**
 * @brief           Function for comparing the mem_fb memory for two channel in a QUAD in repeat mode
 * @param [in]      pointer to array of ref pattern, pointer to structure of mem_compare.
 * @return          number of blocks in case of success or block number in case of failure
 */
int quad_mem_fb_compare_2_ch_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_params)
{
    int read_address[4][2] = {0};    // Ping and Pong address for 4 antennas
    int lc = 0, additional_factor = 0, skip_blocks_antenna[5] = {0}, add_val = 0, blc_cnt = 0, skip_blocks_between_captures = 0,
        v2d_num = 0, buffer_index = 0, v2d_index = 0, count = 0, antenna_index = 0, cnt = 0, ant_num = 0, apb_num = 0;
    uint32_t fb_mem_config_base = 0, sram_base = 0, v2d_time = 0, capture_end_time[4] = {0}, v2d_base = 0, clks_per_blk = 0,
             capture_start_value[4] = {0}, bfn_incr_value = 0, samples_per_block = 0, start_address = 0;

    dram_buff[12] = 0xDEAD;
    v2d_num = g_v2d_instance_in_quad[(v2d_rcs_host_params->quad_instance)][v2d_index];
    fb_mem_config_base = (v2d_num > 3) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;
    sram_base = (v2d_num > 3) ? MEM_FB1_SRAM_BASE : MEM_FB0_SRAM_BASE;
    additional_factor = v2d_rcs_host_params->add_factor;
    clks_per_blk = (v2d_rcs_host_params -> drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    add_val = additional_factor;
    samples_per_block = g_samples_per_blk[(v2d_rcs_host_params -> drf_clock)][(v2d_rcs_host_params -> pdpd_rate)];

    if ((v2d_num % 4) < 2)
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT0.value) * 64);  // Ping address in Bytes
    }
    else
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT1.value) * 64);  // Ping address in Bytes
    }

    read_address[1][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR0.value) * 64);  // for second antenna

    // Pong addresses
    read_address[0][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR1.value) * 64);  // for first antenna
    read_address[1][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR2.value) * 64);  // for second antenna

    /*Populate capture start value*/
    for (lc = 0; lc < (v2d_rcs_host_params -> num_antennas); lc++)
    {
        v2d_num = g_v2d_instance_in_quad[v2d_rcs_host_params -> quad_instance][((v2d_rcs_host_params) -> configured_channel[lc]) / 2];
        apb_num = (v2d_rcs_host_params -> configured_channel[lc]) % 2;
        v2d_base = V2D_BFN_BASE(v2d_num);
        capture_start_value[antenna_index] = ((bfn_csr_t*) (v2d_base)) -> BFNE_START[apb_num + 1].value;
        capture_end_time[antenna_index] = capture_start_value[antenna_index] + ((v2d_rcs_host_params -> capture_blocks) * clks_per_blk);
        antenna_index++;
    }

    /*Get the BFN increment value*/
    v2d_num = g_v2d_instance_in_quad[v2d_rcs_host_params -> quad_instance][((v2d_rcs_host_params) -> configured_channel[0]) / 2];
    apb_num = (v2d_rcs_host_params -> configured_channel[0]) % 2;
    v2d_base = V2D_BFN_BASE(v2d_num);
    bfn_incr_value = ((bfn_csr_t*) (v2d_base)) -> BFNE_INCR[apb_num + 1].value;

    /*Calculate the blocks need to be skipped due to delay in antenna capture*/
    skip_blocks_antenna[0] = (v2d_rcs_host_params -> ant0_cycles) / clks_per_blk;
    skip_blocks_antenna[1] = (v2d_rcs_host_params -> ant1_cycles) / clks_per_blk;
    skip_blocks_antenna[2] = (v2d_rcs_host_params -> ant2_cycles) / clks_per_blk;
    skip_blocks_antenna[3] = (v2d_rcs_host_params -> ant3_cycles) / clks_per_blk;

    /*skip blocks beteen captures*/
    skip_blocks_between_captures = (v2d_rcs_host_params -> skip_cycles) / clks_per_blk;
    add_val += (skip_blocks_antenna[0] * additional_factor);

    for (cnt = 0; cnt < (v2d_rcs_host_params -> num_captures); cnt++)
    {
        dram_buff[5] = get_current_time(v2d_num);
        for (ant_num = 0; ant_num < (v2d_rcs_host_params -> num_antennas); ant_num++)
        {
            /*Wait till capture was ended*/
            do
            {
                v2d_time = get_current_time(v2d_num);
            }while(v2d_time < (capture_end_time[ant_num] + (cnt * bfn_incr_value)));

            start_address = read_address[ant_num][cnt % 2];

            for (lc = 0; lc < (v2d_rcs_host_params -> capture_blocks); lc++)
            {
                dram_buff[10] = start_address;
                if (x_capture_compare((int *) start_address, ref_pattern, samples_per_block, add_val))
                    return (count + 1);

                add_val += additional_factor;
                start_address += (samples_per_block * 4);
                count++;
            }
            add_val += (skip_blocks_antenna[ant_num + 1] * additional_factor);
        }
        add_val += (skip_blocks_between_captures * additional_factor);
        dram_buff[11] = get_current_time(v2d_num);
    }

    dram_buff[12] = 0xFFFF;
    return count;
}

/**
 * @brief           Function for comparing the mem_fb memory for two channel in a QUAD in repeat mode
 * @param [in]      pointer to array of ref pattern, pointer to structure of mem_compare.
 * @return          number of blocks in case of success or block number in case of failure
 */
int quad_mem_fb_compare_3_ch_repeat(int *ref_pattern, v2d_rcs_host_param_t *v2d_rcs_host_params)
{
    int read_address[4][2] = {0};    // Ping and Pong address for 4 antennas
    int lc = 0, additional_factor = 0, skip_blocks_antenna[5] = {0}, add_val = 0, blc_cnt = 0, skip_blocks_between_captures = 0,
        v2d_num = 0, buffer_index = 0, v2d_index = 0, count = 0, antenna_index = 0, cnt = 0, ant_num = 0, apb_num = 0;
    uint32_t fb_mem_config_base = 0, sram_base = 0, v2d_time = 0, capture_end_time[4] = {0}, v2d_base = 0, clks_per_blk = 0,
             capture_start_value[4] = {0}, bfn_incr_value = 0, samples_per_block = 0, start_address = 0;

    dram_buff[12] = 0xDEAD;
    v2d_num = g_v2d_instance_in_quad[(v2d_rcs_host_params->quad_instance)][v2d_index];
    fb_mem_config_base = (v2d_num > 3) ? MEM_FB1_CFG_BASE : MEM_FB0_CFG_BASE;
    sram_base = (v2d_num > 3) ? MEM_FB1_SRAM_BASE : MEM_FB0_SRAM_BASE;
    additional_factor = v2d_rcs_host_params->add_factor;
    clks_per_blk = (v2d_rcs_host_params -> drf_clock) ? (CYCLES_PER_BLOCK_1P5G) : (CYCLES_PER_BLOCK_983M);
    add_val = additional_factor;
    samples_per_block = g_samples_per_blk[(v2d_rcs_host_params -> drf_clock)][(v2d_rcs_host_params -> pdpd_rate)];

    if ((v2d_num % 4) < 2)
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT0.value) * 64);  // Ping address in Bytes
    }
    else
    {
        read_address[0][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> FB_MEM_PTR_PORT1.value) * 64);  // Ping address in Bytes
    }

    read_address[1][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR0.value) * 64);  // for second antenna
    read_address[2][0] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR1.value) * 64);  // for second antenna

    // Pong addresses
    read_address[0][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR2.value) * 64);  // for first antenna
    read_address[1][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR3.value) * 64);  // for second antenna
    read_address[2][1] = sram_base + ((((mem_fb_t*) fb_mem_config_base) -> SECTOR_NEXT_PTR4.value) * 64);  // for second antenna

    /*Populate capture start value*/
    for (lc = 0; lc < (v2d_rcs_host_params -> num_antennas); lc++)
    {
        v2d_num = g_v2d_instance_in_quad[v2d_rcs_host_params -> quad_instance][((v2d_rcs_host_params) -> configured_channel[lc]) / 2];
        apb_num = (v2d_rcs_host_params -> configured_channel[lc]) % 2;
        v2d_base = V2D_BFN_BASE(v2d_num);
        capture_start_value[antenna_index] = ((bfn_csr_t*) (v2d_base)) -> BFNE_START[apb_num + 1].value;
        capture_end_time[antenna_index] = capture_start_value[antenna_index] + ((v2d_rcs_host_params -> capture_blocks) * clks_per_blk);
        antenna_index++;
    }

    /*Get the BFN increment value*/
    v2d_num = g_v2d_instance_in_quad[v2d_rcs_host_params -> quad_instance][((v2d_rcs_host_params) -> configured_channel[0]) / 2];
    apb_num = (v2d_rcs_host_params -> configured_channel[0]) % 2;
    v2d_base = V2D_BFN_BASE(v2d_num);
    bfn_incr_value = ((bfn_csr_t*) (v2d_base)) -> BFNE_INCR[apb_num + 1].value;

    /*Calculate the blocks need to be skipped due to delay in antenna capture*/
    skip_blocks_antenna[0] = (v2d_rcs_host_params -> ant0_cycles) / clks_per_blk;
    skip_blocks_antenna[1] = (v2d_rcs_host_params -> ant1_cycles) / clks_per_blk;
    skip_blocks_antenna[2] = (v2d_rcs_host_params -> ant2_cycles) / clks_per_blk;
    skip_blocks_antenna[3] = (v2d_rcs_host_params -> ant3_cycles) / clks_per_blk;

    /*skip blocks beteen captures*/
    skip_blocks_between_captures = (v2d_rcs_host_params -> skip_cycles) / clks_per_blk;
    add_val += (skip_blocks_antenna[0] * additional_factor);

    for (cnt = 0; cnt < (v2d_rcs_host_params -> num_captures); cnt++)
    {
        dram_buff[5] = get_current_time(v2d_num);
        for (ant_num = 0; ant_num < (v2d_rcs_host_params -> num_antennas); ant_num++)
        {
            /*Wait till capture was ended*/
            do
            {
                v2d_time = get_current_time(v2d_num);
            }while(v2d_time < (capture_end_time[ant_num] + (cnt * bfn_incr_value)));

            start_address = read_address[ant_num][cnt % 2];

            for (lc = 0; lc < (v2d_rcs_host_params -> capture_blocks); lc++)
            {
                dram_buff[10] = start_address;
                if (x_capture_compare((int *) start_address, ref_pattern, samples_per_block, add_val))
                    return (count + 1);

                add_val += additional_factor;
                start_address += (samples_per_block * 4);
                count++;
            }
            add_val += (skip_blocks_antenna[ant_num + 1] * additional_factor);
        }
        add_val += (skip_blocks_between_captures * additional_factor);
        dram_buff[11] = get_current_time(v2d_num);
    }

    dram_buff[12] = 0xFFFF;
    return count;
}



/**
 * @brief           Function to get the current V2D time
 * @param [in]      v2d_num.
 * @return          Current time
 */
int get_current_time(int v2d_num)
{

    int v2d_base = 0;

    v2d_base = V2D_BFN_BASE(v2d_num);

    //capture BFN count
    ((bfn_csr_t*) v2d_base) -> AW_ISYNC_CTRL.BFN_CNT_SAMPLE = 1;
    INTRINSIC_BARRIER;

    return (((bfn_csr_t*) v2d_base) -> AW_ISYNC_BFN_CNT.value);
}

/**
 * @brief           Function for comparing the data
 * @param [in]      start_address, address to ref_pattern, number of samples to compare and add_factor
 * @return          status
 */
int x_capture_compare(int* start_address, int *ref_pattern, int samples, int add_val)
{
    int i = 0, rv = 0;

    for (i = 0; i < samples; i++)
    {
        if ((start_address[i]) != (ref_pattern[i] + add_val))
        {
            rv |= 1;
            dram_buff[7] = (ref_pattern[i] + add_val);
            dram_buff[8] = start_address[i];
            dram_buff[9] = add_val;
            break;
        }
    }
    return rv;
}

/**
 * @brief           Function for configuring gpdma descriptor
 * @param [in]      desc_index, dest address , source address and block size
 * @return          none
 */
void rcs_gpdma_set_descr(uint32_t descr_address, int desc_idx, uint32_t dst_addr, uint32_t src_addr,uint32_t block_size)
{
    gpdma_desc_t desc;
    memset ((void *)&desc, 0, sizeof(gpdma_desc_t));
    desc.sar_lsb = src_addr;
    desc.dar_lsb = dst_addr;
    desc.block_ts = block_size;
    desc.ctl = dmac_ctl_reg;
    desc.ctl.SHADOWREG_OR_LLI_LAST = 1;
    memcpy((void *)descr_address, &desc, sizeof(gpdma_desc_t));
}

/**
 * @brief           Function for writing to V2D register with GPDMA transfer
 * @param [in]      block size, source msize, dest msize, source tranfer width and dest transfer width
 * @return          status
 */
int rcs_gpdma_test_LLI(
        uint32_t descr_buffer,
        int block_size,
        m_size_value_t src_msize,
        m_size_value_t dst_msize,
        tr_width_value_t src_tr_width,
        tr_width_value_t dst_tr_width,
        int src_addr,
        int dest_addr)
{
    int dataCnt = 0, v2d_num = 0, v2d_base = 0, apb_num = 0, pdpd_base = 0;
    volatile rcs_dmac_ch1_intstat_reg_t rcs_dmac_ch1_intstatus_reg = {.value = RCS_DMAC_CH1_INTSTAT_DEFAULT};

    dmac_ctl_reg.SRC_TR_WIDTH = src_tr_width;
    dmac_ctl_reg.DST_TR_WIDTH = dst_tr_width;
    dmac_ctl_reg.SRC_MSIZE = src_msize;
    dmac_ctl_reg.DST_MSIZE = dst_msize;

    /*Set the GPDMA descriptor*/
    rcs_gpdma_set_descr((uint32_t)(descr_buffer), 0, (uint32_t)(dest_addr)/*dest address*/, ((uint32_t)src_addr), block_size);
    RCS_DMAC_CFGREG_REG->value = 1;

    // Channel1 configuration.
    *RCS_DMAC_CH1_CFG_REG = dmac_cfg_reg;
    *RCS_DMAC_CH1_CTL_REG = dmac_ctl_reg;

    // Descr address.
    rcs_dmac_ch1_llp_reg_t llp_reg = {.value = (uint64_t)descr_buffer};
    *RCS_DMAC_CH1_LLP_REG = llp_reg;

    // Channel 1 enable
    rcs_dmac_chenreg_reg_t chen_reg = {.value = 0};
    chen_reg.CH1_EN = 1;
    chen_reg.CH1_EN_WE = 1;
    *RCS_DMAC_CHENREG_REG = chen_reg;

    /*Wait till the transfer is done*/
    rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTAT_REG);

    while (0 == (rcs_dmac_ch1_intstatus_reg.value & 0x1))
    {
        rcs_dmac_ch1_intstatus_reg = *(RCS_DMAC_CH1_INTSTAT_REG);
    }

    return 0;
}
