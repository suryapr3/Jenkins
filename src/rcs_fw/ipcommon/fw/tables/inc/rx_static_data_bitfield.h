/* INTEL CONFIDENTIAL
 *
 * Copyright 2024 Intel Corporation All Rights Reserved.
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

/**
 * this header file is generated by tool, any direct modification without going
 * through the table generation process will get lost
 */

#ifndef __RX_STATIC_DATA_BITFIELD__
#define __RX_STATIC_DATA_BITFIELD__

#include <stdint.h>

/*
 * RX gain information. It is a static value
 */
typedef union {
    struct
    {
        uint32_t gain : 16;      // Gain Parameter
        uint32_t shift : 4;      // Shift Parameter
        uint32_t res_31_20 : 12; // Reserved
    };
    uint32_t value;
} rx_gain_lut_bf_t;

/*
 * This table specifies which HWA DDC block is connected to which antenna. If Meta update is required for an antenna path,
 * the HWA corresponding is indicated here. This table is indexed by antenna.
 */
typedef union {
    struct
    {
        uint8_t rx_hwa_ch_meta_sel; // Select the HWA channel(s) associated with the antenna.
    };
    uint8_t value;
} rx_hwa_ant_meta_mapping_lut_bf_t;

/*
 * Firmware print configuration table. Configure base address for printing'fifo' for simulation.
 */
typedef union {
    struct
    {
        uint32_t print_monitor_base_address; // base address for the RX CPU print monitor
    };
    uint32_t value;
} rx_print_config_lut_bf_t;

/*
 * Rx to ADC CPU configuration table
 */
typedef union {
    struct
    {
        uint32_t bsg_info_ramp_start; // Start value of the ramp
        uint32_t bsg_info_ramp_end;   // End value of the ramp
        uint32_t bsg_info_num_points; // Number of points in the ramp segment
    };
    uint32_t value[3];
} rx_to_adc_cpu_config_lut_bf_t;

/*
 * Rx to ADC CPU configuration table
 */
typedef union {
    struct
    {
        uint32_t dc_source_settling;    // DC source settling delay
        uint32_t sequencer_instruction; // Wait between instructions in sequencer
        uint32_t firmware_sample_wait;  // Wait count in firmware to get ADC sample
    };
    uint32_t value[3];
} rx_to_adc_cpu_delay_lut_bf_t;

/*
 * this table depicts the topology of RX lineup, ie, the data process blocks involved. as V2D and JESD are always involved,
 * only process blocks between these two need to be speicified; indexed by [topology]
 */
typedef union {
    struct
    {
        uint8_t vex_vha : 1; // indicating data goes through VEX and VHA path or not: 1=yes, 0=no
        uint8_t vha : 1;     // indicating data goes through VHA or not: 1=yes, 0=no
        uint8_t vex_v2d : 1; // indicating data goes through VEX and V2D or not: 1=yes, 0=no
        uint8_t res_7_3 : 5; // reserved
    };
    uint8_t value;
} rx_topology_lut_bf_t;

/*
 * VHA UL input FIFO watermark setting table.
 */
typedef union {
    struct
    {
        uint32_t if_wm_1_us : 9;  // VHA UL input FIFO watermark for 1.04us
        uint32_t if_wm_p5_us : 9; // VHA UL input FIFO watermark for 0.52us
        uint32_t res_31_18 : 14;  // reserved
    };
    uint32_t value;
} rx_vha_if_wm_lut_bf_t;

#endif // __RX_STATIC_DATA_BITFIELD__
