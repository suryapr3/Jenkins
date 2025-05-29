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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "com_definitions.h"
#include "cli.h"
#include "init.h"
#include "logger.h"
#include "srp.h"
#include "all_comps.h"
#include "common_macro.h"
#include "common_functions.h"
#include "srp_block_ids.h"


int main(int argc, char **argv)
{
    uint32_t read_value;
    extern void * srp;
    int i;
    init();

    uint32_t base_address[] = {
    VEXABC0_S2C_STRM2CIO_BASE, VEXABC1_S2C_STRM2CIO_BASE, VEXABC2_S2C_STRM2CIO_BASE, VEXABC3_S2C_STRM2CIO_BASE, VEXABC4_S2C_STRM2CIO_BASE,
    VEXABC5_S2C_STRM2CIO_BASE, VEXABC6_S2C_STRM2CIO_BASE, VEXABC7_S2C_STRM2CIO_BASE, VEXABC8_S2C_STRM2CIO_BASE, VEXABC9_S2C_STRM2CIO_BASE,
    VEXABC10_S2C_STRM2CIO_BASE, VEXABC11_S2C_STRM2CIO_BASE, VEXABC12_S2C_STRM2CIO_BASE, VEXABC13_S2C_STRM2CIO_BASE, VEXABC14_S2C_STRM2CIO_BASE,
    VEXABC15_S2C_STRM2CIO_BASE, VEXABC16_S2C_STRM2CIO_BASE, VEXABC17_S2C_STRM2CIO_BASE, VEXABC18_S2C_STRM2CIO_BASE, VEXABC19_S2C_STRM2CIO_BASE,
    VEXABC20_S2C_STRM2CIO_BASE, VEXABC21_S2C_STRM2CIO_BASE, VEXABC22_S2C_STRM2CIO_BASE, VEXABC23_S2C_STRM2CIO_BASE, VEXABC24_S2C_STRM2CIO_BASE,
    VEXABC25_S2C_STRM2CIO_BASE, VEXABC26_S2C_STRM2CIO_BASE, VEXABC27_S2C_STRM2CIO_BASE, VEXABC28_S2C_STRM2CIO_BASE, VEXABC29_S2C_STRM2CIO_BASE,
    VEXABC30_S2C_STRM2CIO_BASE, VEXABC31_S2C_STRM2CIO_BASE, VEXABC32_S2C_STRM2CIO_BASE, VEXABC33_S2C_STRM2CIO_BASE, VEXABC34_S2C_STRM2CIO_BASE,
    VEXABC35_S2C_STRM2CIO_BASE, VEXABC36_S2C_STRM2CIO_BASE, VEXABC37_S2C_STRM2CIO_BASE, VEXABC38_S2C_STRM2CIO_BASE, VEXABC39_S2C_STRM2CIO_BASE
    };

    for(i=0; i<sizeof(base_address) / (sizeof(base_address[0])*2); i++)
    {
		LOG_PRINT("i is %d", i);
        if(((i>15)&& (i<32))  || (i==33) || (i==35) || (i==37) || (i==39)){
            continue;
        }
        else
        {
        read_reg_expect_18a(base_address[i]+STRM2CIO_MEM_BAR_OFFSET, \
                                    STRM2CIO_MEM_BAR_DEFAULT, \
                                    STRM2CIO_MEM_BAR_RD_MASK, "STRM2CIO_MEM_BAR_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_CREDIT_CNT_OFFSET, \
                                    STRM2CIO_CREDIT_CNT_DEFAULT, \
                                    STRM2CIO_CREDIT_CNT_RD_MASK, "STRM2CIO_CREDIT_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_FIFO_STAT_CTL_OFFSET, \
                                    STRM2CIO_FIFO_STAT_CTL_DEFAULT, \
                                    STRM2CIO_FIFO_STAT_CTL_RD_MASK, "STRM2CIO_FIFO_STAT_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_FIFO_STAT_OFFSET, \
                                    STRM2CIO_FIFO_STAT_DEFAULT, \
                                    STRM2CIO_FIFO_STAT_RD_MASK, "STRM2CIO_FIFO_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_CIO_STALL_CTL_OFFSET, \
                                    STRM2CIO_CIO_STALL_CTL_DEFAULT, \
                                    STRM2CIO_CIO_STALL_CTL_RD_MASK, "STRM2CIO_CIO_STALL_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_CIO_STALL_CNT_OFFSET, \
                                    STRM2CIO_CIO_STALL_CNT_DEFAULT, \
                                    STRM2CIO_CIO_STALL_CNT_RD_MASK, "STRM2CIO_CIO_STALL_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_WORD_CNT_CTL_OFFSET, \
                                    STRM2CIO_WORD_CNT_CTL_DEFAULT, \
                                    STRM2CIO_WORD_CNT_CTL_RD_MASK, "STRM2CIO_WORD_CNT_CTL_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_WORD_CNT_OFFSET, \
                                    STRM2CIO_WORD_CNT_DEFAULT, \
                                    STRM2CIO_WORD_CNT_RD_MASK, "STRM2CIO_WORD_CNT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_STRM_READY_FORCE_OFFSET, \
                                    STRM2CIO_STRM_READY_FORCE_DEFAULT, \
                                    STRM2CIO_STRM_READY_FORCE_RD_MASK, "STRM2CIO_STRM_READY_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_STOP_EN_OFFSET, \
                                    STRM2CIO_STOP_EN_DEFAULT, \
                                    STRM2CIO_STOP_EN_RD_MASK, "STRM2CIO_STOP_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_INT_STAT_OFFSET, \
                                    STRM2CIO_INT_STAT_DEFAULT, \
                                    STRM2CIO_INT_STAT_RD_MASK, "STRM2CIO_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_INT_EN_OFFSET, \
                                    STRM2CIO_INT_EN_DEFAULT, \
                                    STRM2CIO_INT_EN_RD_MASK, "STRM2CIO_INT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_INT_CLR_OFFSET, \
                                    STRM2CIO_INT_CLR_DEFAULT, \
                                    STRM2CIO_INT_CLR_RD_MASK, "STRM2CIO_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_INT_FORCE_OFFSET, \
                                    STRM2CIO_INT_FORCE_DEFAULT, \
                                    STRM2CIO_INT_FORCE_RD_MASK, "STRM2CIO_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_INT_MASKED_STAT_OFFSET, \
                                    STRM2CIO_INT_MASKED_STAT_DEFAULT, \
                                    STRM2CIO_INT_MASKED_STAT_RD_MASK, "STRM2CIO_INT_MASKED_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_A2C_INT_STAT_OFFSET, \
                                    STRM2CIO_A2C_INT_STAT_DEFAULT, \
                                    STRM2CIO_A2C_INT_STAT_RD_MASK, "STRM2CIO_A2C_INT_STAT_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_A2C_INT_EN_OFFSET, \
                                    STRM2CIO_A2C_INT_EN_DEFAULT, \
                                    STRM2CIO_A2C_INT_EN_RD_MASK, "STRM2CIO_A2C_INT_EN_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_A2C_INT_CLR_OFFSET, \
                                    STRM2CIO_A2C_INT_CLR_DEFAULT, \
                                    STRM2CIO_A2C_INT_CLR_RD_MASK, "STRM2CIO_A2C_INT_CLR_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_A2C_INT_FORCE_OFFSET, \
                                    STRM2CIO_A2C_INT_FORCE_DEFAULT, \
                                    STRM2CIO_A2C_INT_FORCE_RD_MASK, "STRM2CIO_A2C_INT_FORCE_OFFSET");

        read_reg_expect_18a(base_address[i]+STRM2CIO_A2C_INT_MASKED_STAT_OFFSET, \
                                    STRM2CIO_A2C_INT_MASKED_STAT_DEFAULT, \
                                    STRM2CIO_A2C_INT_MASKED_STAT_RD_MASK, "STRM2CIO_A2C_INT_MASKED_STAT_OFFSET");

    }

}
}
