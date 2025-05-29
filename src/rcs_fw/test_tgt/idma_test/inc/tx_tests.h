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
 * @file    sample_source.c
 * @brief   Brief description of source file.
 * @details Detailed description if necessary.
 * @todo    Write documentation for source file sample_source.c
 */


/***********************************************
 * GLOBAL DATA DEFINITIONS (consts, vars)      *
 ***********************************************/

/***********************************************
 * FUNCTION PROTOTYPES                         *
 ***********************************************/
uint8_t  idma_tests ();
unsigned int dcode_tests();
unsigned int dcode_read_pcie_write_core_tests(unsigned int pattern);
unsigned int  rsm_read_pcie_write_core_tests(unsigned int pattern);
void idma_cb_test (void *arg);
void idma_test_desc_1d ();
void idma_test_1d_poll_dcode_to_dcode();
void idma_test_1d_poll_dcode_to_rsm();
void idma_test_1d_poll_rsm_to_dcode();
void idma_test_desc_1d_dcode_to_dcode ();
void idma_test_desc_1d_rsm_to_dcode();
void idma_test_desc_1d_dcode_to_rsm();
void idma_test_broadcast ();
void idma_test_broadcast_rsm_to_dcode();
void idma_test_broadcast_dcode_to_rsm();
void idma_test_broadcast_src_pitch ();
void idma_test_broadcast_dcode_to_rsm_src_pitch();
void idma_test_broadcast_rsm_to_dcode_src_pitch ();
void idma_test_desc_1d_dcode_to_dcode(uint32_t num_bytes,uint32_t blk_size );
void idma_test_desc_2d_dcode_to_dcode(uint32_t num_bytes,uint32_t blk_size);
void idma_test_desc_1d_dcode_to_rsm(uint32_t num_bytes,uint32_t blk_size);
void idma_test_desc_2d_dcode_to_rsm(uint32_t num_bytes,uint32_t blk_size);
void idma_test_desc_1d_rsm_to_dcode(uint32_t num_bytes,uint32_t blk_size);
void idma_test_desc_2d_rsm_to_dcode(uint32_t num_bytes,uint32_t blk_size);
void idma_test_desc_2d_dcode_to_iram(uint32_t num_bytes,uint32_t blk_size);
void idma_negative_test();
uint32_t idma_reg_read (void const *const p_addr);

