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
/**************************************************************************************
 * @file  common_funtions.h
****************************************************************************************/
#ifndef COMMON_DEFINITIONS_H

#define COMMON_DEFINITIONS_H

#include <stdbool.h>
#include <stdint.h>
#include "srp.h"
#include "srp_vex.h"
#include "srp_rcs.h"

#ifndef BUILD_DIR
#define BUILD_DIR "Unknown"
#endif

#define SUCCESS                        ( 0 )
#define FAILURE                        ( -1 )

// ABC FRIO build version constants
//  This list will grow as and when a new FRIO release comes up
#define ABC_18A_0P5_1_0                ( 0x00002339 )
#define ABC_18A_0P6_0_1                ( 0x00002351 )
#define ABC_18A_0P6_1_0                ( 0x23510100 )
#define ABC_18A_0P6_1_1                ( 0x23510101 )
#define ABC_18A_0P8_0_1                ( 0x24160001 )
#define ABC_18A_0P8_0_2                ( 0x24160002 )
#define ABC_18A_0P8_0_3                ( 0x24160003 )
#define ABC_18A_0P8_0_4                ( 0x24160004 )
#define ABC_18A_0P8B_0_1               ( 0x24290001 )
#define ABC_18A_0P8B_0_2               ( 0x24290002 )

// VEX specific constants
#define VEX_VM_SIZE                    ( 0x4000 )
#define VEX_DM_SIZE                    ( 0x1000 )
#define VEX_DMEM_OFFSET                ( 0x4000 )
#define VEX_VMEM_OFFSET                ( 0x28000 )

#define V2D_BFN_CSR_BASE(v2d_num)      ( V2D0_BFN_CSR_BASE + (v2d_num * (V2D1_BFN_CSR_BASE - V2D0_BFN_CSR_BASE)) )

#define STRM2CIO_2_VEX_DMEM_OFFSET     ( 0x18000 )

// For MEM_FB
#define FB0_SRAM_START                 (0x04400000)
#define FB1_SRAM_START                 (0x04600000)
#define FLITS_PER_1MB                  (16384)
#define SECTOR_END_PTR(sector_num)     (MEM_FB_SECTOR_END_PTR0_OFFSET + (sector_num) * \
        (MEM_FB_SECTOR_END_PTR1_OFFSET - MEM_FB_SECTOR_END_PTR0_OFFSET))
#define SECTOR_NEXT_PTR(sector_num)     (MEM_FB_SECTOR_NEXT_PTR0_OFFSET + (sector_num) * \
        (MEM_FB_SECTOR_NEXT_PTR1_OFFSET - MEM_FB_SECTOR_NEXT_PTR0_OFFSET))

// Global enum declarations
typedef struct {
    int release_version;
    char* release_name;
    char* rtl_version;
}frio_build_t;

typedef enum {
    RESET_ASSERT,
    RESET_DEASSERT
}reset_assert_active_high;

typedef struct register_config_tbl
{
    unsigned int offset;
    unsigned int value;
    int mask;
    char *name;
}register_config_t;

typedef enum{
    V2D0 = 0,
    V2D1,
    V2D2,
    V2D3,
    V2D4,
    V2D5,
    V2D6,
    V2D7,
    V2D_ALL = 0xFF
}v2d_instance_t;

typedef enum{
    DRF_CHANNEL_0 = 0,
    DRF_CHANNEL_1,
    DRF_CHANNEL_BOTH = 0xFF
}drf_channel_instance_t;

// for jesd reset
typedef enum {
    JESD_INSTANCE_0 = 1,
    JESD_INSTANCE_1 = 2,
    JESD_INSTANCE_2 = 4,
    JESD_INSTANCE_3 = 8,
    JESD_INSTANCE_MAX_COUNT = 2,       //frio supports only 2 instances,
    JESD_INSTANCE_ALL = 0xF,
}jesd_instances;

typedef enum {
    SINGLE_CAPTURE_MODE = 0,
    DOUBLE_CAPTURE_MODE,
    REPEAT_CAPTURE_MODE,
    CONTINUOUS_CAPTURE_MODE,
}capture_mode_t;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

int abc_platform_detect(void);
uint32_t vha_reset(uint32_t vha_num, reset_assert_active_high reset);
int vha_clock_config(uint32_t vha_num, uint32_t config);
uint32_t v2d_reset(v2d_instance_t v2d_num, reset_assert_active_high reset);
int v2d_clk_enable(v2d_instance_t v2d_num, drf_channel_instance_t ch_num);
int v2d_clk_disable(v2d_instance_t v2d_num, drf_channel_instance_t ch_num);
int v2d_bfn_gnrl_csr_config(v2d_instance_t v2d_num, int value);
void cold_reset_cycle(void);
uint32_t vex_reset_cycle(void);
void subsys_reset_cycle(void);
void crux_reset_cycle (void);
void reenable_pcie_after_sys_reset(void);
uint32_t vex_mem_clear(uint32_t vex_num, void* srp);
uint32_t vex_wait(uint32_t vexCoreId);
uint32_t jesd_reset(int jesd_instance_mask, int reset);
void jesd_204d_enable (void);
int  jump_to_ram(void);
int mem_fb_general_config(uint32_t mem_fb_base_address, int power_down_control_value);
int mem_fb_x_capture_configuration(capture_mode_t capture_mode, int size_per_capture, int v2d_num, int apb_num);
int quad_fb_mem_x_capture_configuration(capture_mode_t capture_mode, int quad_instance, int num_antennas, uint32_t size_per_antenna);
int quad_mem_fb_x_capture_configuration(capture_mode_t capture_mode, int quad_instance, int num_antennas, uint32_t size_per_antenna);

void rte_init(void);
void rte_deinit();

srp_st_t vex_loader(srp_vex_core_t core_id, const char *file_name);
void vex_start(srp_vex_core_t core_id, const uint32_t start_addr);

srp_st_t rcs_config(srp_rcs_config_t *rcs_params);
void rcs_rcp_start(srp_rcs_rcp_t rcp_id);

#endif // COMMON_DEFINITIONS_H
