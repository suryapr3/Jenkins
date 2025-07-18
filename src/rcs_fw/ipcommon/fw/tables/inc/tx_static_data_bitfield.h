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

#ifndef __TX_STATIC_DATA_BITFIELD__
#define __TX_STATIC_DATA_BITFIELD__

#include <stdint.h>
#include "com_rf_def.h"

/*
 * Configuration Table Based on DAC Rates. This table indexed by dac config index (need 4-bit)
 */
typedef union {
    struct
    {
        uint32_t num_phases : 3;        // set the num of active encoder phases (0x0=16; 0x1=12, 0x2=8, 0x3=6, 0x4=4, 0x6=2)
        uint32_t clkmux_div : 1;        // enable TX clock multiplexer divided path(e.g. for 8G mode)
        uint32_t mode3q : 1;            // clock divider three quarter mode
        uint32_t div6 : 1;              // clock divider divide by six mode
        uint32_t dis_rf : 1;            // disable divided RF output to the clock multiplexer. Save power when the RF clock is
                                        // directly used
        uint32_t rf_prog : 2;           // chooses the divider output to the clock multiplexer. Value 3 means don't care (X)
        uint32_t dis_serhi : 1;         // disable the divided output to the high-rate serializer
        uint32_t serhi_prog : 2;        // chooses the high-rate serializer output of the divider
        uint32_t dis_serlo : 1;         // disable the divided output to the low-rate serializer
        uint32_t serlo_prog : 2;        // chooses the low-rate serializer output of the divider
        uint32_t ser_bypass_s16to4 : 1; // bypass base rate serializer
        uint32_t ser_bypass4to2 : 1;    // bypass the low-rate serializer
        uint32_t res_31_17 : 15;        // reserved
    };
    uint32_t value;
} tx_dac_conf_lut_bf_t;

/*
 * This table maps JESD channels to antennas on the TX path. If a meta update is required for a particular antenna this
 * table determines which channels in the CM is controling the path. This table is indexed by antenna.
 */
typedef union {
    struct
    {
        uint32_t tx_jesd_ch_meta_sel; // Select the JESD channel(s) that map to the antenna.
    };
    uint32_t value;
} tx_jesd_ant_meta_mapping_lut_bf_t;

/*
 * PDPD LUT config/enable table. Indexed by [pdpd_cfg]
 */
typedef union {
    struct
    {
        uint8_t ext_cfg : 7;        // these 7 bits set the first 7 bits of register pdpd_cfg_reg
        uint8_t clut_interp_en : 1; // this bit controls (enabling/disabling) MGP/DDR coef LUT interpolation
    };
    uint8_t value;
} tx_pdpd_cfg_lut_bf_t;

/*
 * PDPD extra term delay (extr_dly) relative to other terms, passthrough delay(pt_dly), field'adv' is for extr_dly. The num
 * of entey of this table should be extended based on use case. Indexed by [pdpd_dly]
 */
typedef union {
    struct
    {
        uint16_t et_dly : 7; // Set Extra Terms delay/advance value
        uint16_t adv : 1;    // advance/delay indication: 0 for delay, 1 for advance
        uint16_t pt_dly : 7; // delay value for passthrough term
        uint16_t res_15 : 1; // reserved
    };
    uint16_t value;
} tx_pdpd_dly_lut_bf_t;

/*
 * PDPD mode selection table. Indexed by [pdpd_mod] This table indexed by supported pdpd mode index (need 3-bit)
 */
typedef union {
    struct
    {
        uint16_t gang_mod : 1;                 // enable ganging mode
        uint16_t wr_pc_m1 : 1;                 // flow G using mode1 to update LUT. Mode 1 using NSIP4, mode2 using NSIP5
        uint16_t rx_pd_strm_en : 1;            // enable flow D stream
        uint16_t rx_pd_en : 1;                 // enable flow D
        uint16_t tx_pd_strm_en : 1;            // enable flow B
        uint16_t pd_extra_only : 1;            // enable flow C and disable flow B
        uint16_t extra_static_en : 1;          // enable extra term
        uint16_t tx_strm_en : 1;               // enable flow A or C stream
        uint16_t pd_extra_en : 1;              // select flow A or C. 0: flow A, 1: flow C
        e_pd_cap_mem_sel_t pd_cap_mem_sel : 2; // select PDPD capture mem source
        uint16_t v2d_input_ptr_sel : 2;        // v2d input pointer bound selection, 0 for V2D_AC_BUF0_LUT, 1 for V2D_B_BUF0_LUT,
                                               // 2 for V2D_AC_BUF1_LUT and V2D_B_BUF1_LUT
        uint16_t use_flow_ac : 1;              // using path A/C input
        uint16_t use_flow_b : 1;               // using path B input
        uint16_t use_flow_d : 1;               // having path D output
    };
    uint16_t value;
} tx_pdpd_mod_lut_bf_t;

/*
 * PDPD operating mode, sample rate, coefficient LUT function types selection. indexed by [pdpd_op_mod][pdpd_rate]
 * Indexing: [op_mod][rate_comb_cfg_idx], here op_mod is 2-bit pdpd operating power mode selection (e_pdpd_op_mod_t);
 * rate_comb_cfg_idx is 3-bit PDPD config based on valid in_rate and out_rate combination
 */
typedef union {
    struct
    {
        e_pdpd_rate_t in_rate : 3;  // PDPD input sampling rate
        e_pdpd_rate_t out_rate : 3; // PDPD output sampling rate
        e_pc_lut_mod_t lut_mod : 2; // PDPD coefficient update LUT mode
    };
    uint8_t value;
} tx_pdpd_pc_sel_lut_bf_t;

/*
 * Firmware print configuration table. Configure base address for printing'fifo' for simulation.
 */
typedef union {
    struct
    {
        uint32_t print_monitor_base_address; // base address for the TX CPU print monitor
    };
    uint32_t value;
} tx_print_config_lut_bf_t;

/*
 * this table depicts the topology of TX lineup, ie, the data process blocks involved. as V2D and JESD are always involved,
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
} tx_topology_lut_bf_t;

/*
 * V2D NSIP memory allocation based on PDPD mode. This table is indexed based on v2d_input_ptr_sel in tx_pdpd_mod_lut and
 * num of VEX used (1, 2 or 4) for corresponding flow, indexing needs 2 + 2 bits
 */
typedef union {
    struct
    {
        uint32_t lower_bound : 11; // Lower Boundary for Tx A/C/B Buffer Pointers. This field defines pointer's starting location for a
                                   // circular buffer partition in the buffer memory
        uint32_t upper_bound : 11; // Upper Boundary for Tx A/C/B Buffer Pointers. This field defines pointer's ending location for a
                                   // circular buffer partition in the buffer memory. Indexed by [v2d_input_ptr_sel][offset]
        uint32_t b2h_strm_id : 2;  // NSIP HBI 0 (flow A/C) and HBI 1(flow B) input from stream ID mapping
        uint32_t h2b_strm_id : 2;  // NSIP HB1 ( apply to flow D for DPP & DGPP only) or HB0 (apply to flow F only) output to stream ID
                                   // mapping
        uint32_t res_31_26 : 6;    // reserved
    };
    uint32_t value;
} tx_v2d_if_params_lut_bf_t;

/*
 * setting of V2D buffer release method and delay. Num of entries of this table could be extended. Indexed by parameter
 * [fifo_dly]
 */
typedef union {
    struct
    {
        uint32_t start_src : 2;        // this indicate the source to trigger when to start the FIFO (at the input to TX analog block)
                                       // reading into TX analog block. from TX direction: 0:JesdRXStartQN --- in this case, the FIFO
                                       // should be half-filled when FIFO reading is started, 1:TRXANT valids [3:0], 2:BFN Timed
                                       // Event, 3:not used
        uint32_t trxant_merge_cfg : 5; // bit vector to select which JESD linkes [0..3] should be used as trigger start. Bit0=1:
                                       // select JESD link 0, bit1=1: select JESD link 1, etc
        uint32_t trxant_start_dly : 4; // Additional delay (must be between 2 and 25) when FIFO_START_SOURCE = ‘1’. (Not used when
                                       // FIFO_START_SOURCE = ‘0’.)
        uint32_t jesd_start_dly : 18;  // Specify total VEX array + V2D + DigRF latency + margin (less the internal fixed pipeline
                                       // delay) when FIFO_START_SOURCE =’0’.
        uint32_t res_31_29 : 3;        // reserved
        uint32_t lm_chnl0 : 18;        // Set JESD latency count (latency match value) using DigRF clocks (triggered when JESD is
                                       // started). It's jesd_start_dly + VEX/VHA process latency on channel 0
        uint32_t res_63_50 : 14;       // reserved
        uint32_t lm_chnl1 : 18;        // Set JESD latency count (latency match value) using DigRF clocks (triggered when JESD is
                                       // started). It's jesd_start_dly + VEX/VHA process latency on channel 1
        uint32_t res_95_82 : 14;       // reserved
    };
    uint32_t value[3];
} tx_v2d_start_dly_lut_bf_t;

#endif // __TX_STATIC_DATA_BITFIELD__
