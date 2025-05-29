import ctypes

class ax_bfn_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("bfn_rmt_chk_en", ctypes.c_uint8, 1),
        ("ext_src_sel", ctypes.c_uint8, 2),
        ("extsync_gpio_sel", ctypes.c_uint8, 5) ]
class ax_bfn_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_bfn_config_lut_bf_s), ('value', ctypes.c_uint8) ]

class ax_bfn_selfsync_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("self_sync_offset", ctypes.c_uint32) ]
class ax_bfn_selfsync_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_bfn_selfsync_lut_bf_s), ('value', ctypes.c_uint32) ]

class ax_jesd_comp_param_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("comp_top_reg", ctypes.c_uint32, 20),
        ("significand_width", ctypes.c_uint32, 4),
        ("exponent_width", ctypes.c_uint32, 3),
        ("jesd_format", ctypes.c_uint32, 1),
        ("input_iq_format", ctypes.c_uint32, 1),
        ("signed_format", ctypes.c_uint32, 1),
        ("agc_bit", ctypes.c_uint32, 1),
        ("exponent_method", ctypes.c_uint32, 1),
        ("comp_vmlga_reg", ctypes.c_uint32),
        ("comp_vnsh_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl0_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl1_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl2_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl3_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl4_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl5_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl6_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl7_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl8_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl9_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl10_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl11_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl12_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl13_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl14_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl15_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl16_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl17_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl18_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl19_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl20_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl21_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl22_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl23_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl24_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl25_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl26_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl27_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl28_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl29_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl30_reg", ctypes.c_uint32),
        ("comp_bitformat_ctl31_reg", ctypes.c_uint32) ]
class ax_jesd_comp_param_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_jesd_comp_param_lut_bf_s), ('value', ctypes.c_uint32*35) ]

class ax_jesd_configuration_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("jesd_1p5g_clk", ctypes.c_uint32, 1),
        ("jesd_sample_width_n", ctypes.c_uint32, 1),
        ("jesd_octets_per_frame_f", ctypes.c_uint32, 5),
        ("jesd_samples_per_frame_s", ctypes.c_uint32, 1),
        ("jesd_hd_flag", ctypes.c_uint32, 1),
        ("jesd_sample_to_char_ratio", ctypes.c_uint32, 3),
        ("jesd_soni", ctypes.c_uint32, 3),
        ("res_15", ctypes.c_uint32, 1),
        ("tx_sample_neg", ctypes.c_uint32, 3),
        ("tx_sample_pos", ctypes.c_uint32, 3),
        ("jesd_num_min_emb", ctypes.c_uint32, 2),
        ("tx_latency_delay", ctypes.c_uint32, 8) ]
class ax_jesd_configuration_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_jesd_configuration_lut_bf_s), ('value', ctypes.c_uint32) ]

class ax_jesd_decomp_param_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("decomp_top_reg", ctypes.c_uint32, 4),
        ("significand_width", ctypes.c_uint32, 4),
        ("exponent_width", ctypes.c_uint32, 3),
        ("jesd_format", ctypes.c_uint32, 1),
        ("input_iq_format", ctypes.c_uint32, 1),
        ("signed_format", ctypes.c_uint32, 1),
        ("exponent_method", ctypes.c_uint32, 1),
        ("res_31_15", ctypes.c_uint32, 17),
        ("decomp_vnsh_ctl", ctypes.c_uint32),
        ("decomp_mantissa_ctl0", ctypes.c_uint32),
        ("decomp_mantissa_ctl1", ctypes.c_uint32),
        ("decomp_mantissa_ctl2", ctypes.c_uint32),
        ("decomp_mantissa_ctl3", ctypes.c_uint32),
        ("decomp_mantissa_ctl4", ctypes.c_uint32),
        ("decomp_mantissa_ctl5", ctypes.c_uint32),
        ("decomp_mantissa_ctl6", ctypes.c_uint32),
        ("decomp_mantissa_ctl7", ctypes.c_uint32),
        ("decomp_mantissa_ctl8", ctypes.c_uint32),
        ("decomp_mantissa_ctl9", ctypes.c_uint32),
        ("decomp_mantissa_ctl10", ctypes.c_uint32),
        ("decomp_mantissa_ctl11", ctypes.c_uint32),
        ("decomp_mantissa_ctl12", ctypes.c_uint32),
        ("decomp_mantissa_ctl13", ctypes.c_uint32),
        ("decomp_mantissa_ctl14", ctypes.c_uint32),
        ("decomp_mantissa_ctl15", ctypes.c_uint32),
        ("decomp_mantissa_ctl16", ctypes.c_uint32),
        ("decomp_mantissa_ctl17", ctypes.c_uint32),
        ("decomp_mantissa_ctl18", ctypes.c_uint32),
        ("decomp_mantissa_ctl19", ctypes.c_uint32),
        ("decomp_mantissa_ctl20", ctypes.c_uint32),
        ("decomp_mantissa_ctl21", ctypes.c_uint32),
        ("decomp_mantissa_ctl22", ctypes.c_uint32),
        ("decomp_mantissa_ctl23", ctypes.c_uint32),
        ("decomp_mantissa_ctl24", ctypes.c_uint32),
        ("decomp_mantissa_ctl25", ctypes.c_uint32),
        ("decomp_mantissa_ctl26", ctypes.c_uint32),
        ("decomp_mantissa_ctl27", ctypes.c_uint32),
        ("decomp_mantissa_ctl28", ctypes.c_uint32),
        ("decomp_mantissa_ctl29", ctypes.c_uint32),
        ("decomp_mantissa_ctl30", ctypes.c_uint32),
        ("decomp_mantissa_ctl31", ctypes.c_uint32),
        ("decomp_exp_ctl0", ctypes.c_uint32),
        ("decomp_exp_ctl1", ctypes.c_uint32),
        ("decomp_exp_ctl2", ctypes.c_uint32),
        ("decomp_exp_ctl3", ctypes.c_uint32),
        ("decomp_exp_ctl4", ctypes.c_uint32),
        ("decomp_exp_ctl5", ctypes.c_uint32),
        ("decomp_exp_ctl6", ctypes.c_uint32),
        ("decomp_exp_ctl7", ctypes.c_uint32) ]
class ax_jesd_decomp_param_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_jesd_decomp_param_lut_bf_s), ('value', ctypes.c_uint32*42) ]

class ax_jesd_input_param_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("sysref_rate", ctypes.c_uint32, 2),
        ("compression_type", ctypes.c_uint32, 4),
        ("decompression_type", ctypes.c_uint32, 2),
        ("jesd_tx_start_type", ctypes.c_uint32, 1),
        ("jesd_rx_start_type", ctypes.c_uint32, 1),
        ("res_31_10", ctypes.c_uint32, 22) ]
class ax_jesd_input_param_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_jesd_input_param_lut_bf_s), ('value', ctypes.c_uint32) ]

class ax_jesd_rate_index_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("jesd_sample_rate", ctypes.c_uint32, 4),
        ("jesd_num_streams", ctypes.c_uint32, 4),
        ("jesd_num_lanes_l", ctypes.c_uint32, 4),
        ("jesd_serdes_bit_rate", ctypes.c_uint32, 4),
        ("jesd_num_converters_m", ctypes.c_uint32, 4),
        ("jesd_char_clk", ctypes.c_uint32, 4),
        ("jesd_sample_clk", ctypes.c_uint32, 4),
        ("res_30_28", ctypes.c_uint32, 3),
        ("jesd_204d", ctypes.c_uint32, 1) ]
class ax_jesd_rate_index_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_jesd_rate_index_lut_bf_s), ('value', ctypes.c_uint32) ]

class ax_print_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("print_monitor_base_address", ctypes.c_uint32) ]
class ax_print_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ax_print_config_lut_bf_s), ('value', ctypes.c_uint32) ]

AX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM = 4
class ax_print_config_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_print_config_lut", ax_print_config_lut_bf_t * AX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM) ]

AX_JESD_RATE_INDEX_LUT_MAX_ENTRY_NUM = 96
class ax_jesd_rate_index_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_jesd_rate_index_lut", ax_jesd_rate_index_lut_bf_t * AX_JESD_RATE_INDEX_LUT_MAX_ENTRY_NUM) ]

AX_JESD_CONFIGURATION_LUT_MAX_ENTRY_NUM = 96
class ax_jesd_configuration_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_jesd_configuration_lut", ax_jesd_configuration_lut_bf_t * AX_JESD_CONFIGURATION_LUT_MAX_ENTRY_NUM) ]

AX_JESD_COMP_PARAM_LUT_MAX_ENTRY_NUM = 5
class ax_jesd_comp_param_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_jesd_comp_param_lut", ax_jesd_comp_param_lut_bf_t * AX_JESD_COMP_PARAM_LUT_MAX_ENTRY_NUM) ]

class ax_jesd_input_param_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_jesd_input_param_lut", ax_jesd_input_param_lut_bf_t) ]

AX_JESD_DECOMP_PARAM_LUT_MAX_ENTRY_NUM = 4
class ax_jesd_decomp_param_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_jesd_decomp_param_lut", ax_jesd_decomp_param_lut_bf_t * AX_JESD_DECOMP_PARAM_LUT_MAX_ENTRY_NUM) ]

class ax_bfn_config_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_bfn_config_lut", ax_bfn_config_lut_bf_t) ]

AX_BFN_SELFSYNC_LUT_MAX_ENTRY_NUM = 2
class ax_bfn_selfsync_lut_t(ctypes.Structure):
    _fields_ = [ ("ax_bfn_selfsync_lut", ax_bfn_selfsync_lut_bf_t * AX_BFN_SELFSYNC_LUT_MAX_ENTRY_NUM) ]

class ax_static_data_t(ctypes.Structure):
    _fields_ = [
        ("ax_print_config_lut", ax_print_config_lut_t),
        ("ax_jesd_rate_index_lut", ax_jesd_rate_index_lut_t),
        ("ax_jesd_configuration_lut", ax_jesd_configuration_lut_t),
        ("ax_jesd_comp_param_lut", ax_jesd_comp_param_lut_t),
        ("ax_jesd_input_param_lut", ax_jesd_input_param_lut_t),
        ("ax_jesd_decomp_param_lut", ax_jesd_decomp_param_lut_t),
        ("ax_bfn_config_lut", ax_bfn_config_lut_t),
        ("ax_bfn_selfsync_lut", ax_bfn_selfsync_lut_t) ]

# ax_static_data start address: _dram0_ax_tables_data_start