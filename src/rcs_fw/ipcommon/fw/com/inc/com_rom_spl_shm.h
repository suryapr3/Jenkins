/* INTEL CONFIDENTIAL
 *
 * Copyright  2024 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors. Title to the Material remains with Intel
 * Corporation or its suppliers and licensors. The Material contains trade
 * secrets and proprietary and confidential information of Intel or its
 * suppliers and licensors. The Material is protected by worldwide copyright
 * and trade secret laws and treaty provisions. No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded, posted,
 * transmitted, distributed, or disclosed in any way without Intel's prior
 * express written permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 *
 *****************************************************************************/

#ifndef _COMMON_ROM_SPL_SHM_H_
#define _COMMON_ROM_SPL_SHM_H_

#define SPL_SHM_IMG_DESC_ADDR 0x0023FFF0 // SPL image details address
#define ROM_SPL_SHM_FSM_ADDR  0x0023FFE0 // Address to store the FSM state of ROM/SPL

#define SPL_IMG_VALID 0xA5A5A5A5 // ACK word to indicate SPL image is loaded in SHM

typedef struct
{
    uint32_t shm_image_loc;
    uint32_t shm_image_size;
    uint32_t shm_image_ver;
    uint32_t shm_image_valid;
} shm_image_indicator_t;

// ROM FSM states
typedef enum
{
    e_ROM_CFG_ERR_STATE = 0x80000000,
    e_ROM_CFG_START = 0x1,
    e_PCIE_INIT_START = 0x2,
    e_PCIE_INIT_END = 0x4,
    e_PCIE_SERDES_INIT_START = 0x8,
    e_PCIE_SERDES_INIT_END = 0x10,
    e_PCIE_CTRL_INIT_START = 0x20,
    e_PCIE_CTRL_INIT_END = 0x40,
    e_SBB_INIT_START = 0x80,
    e_SBB_INIT_END = 0x100,
    e_ROM_CFG_END = 0x200,
} e_rom_fsm_state;

#endif // _COMMON_ROM_SPL_SHM_H_
