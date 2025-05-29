import ctypes

class tx_dac_conf_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("num_phases", ctypes.c_uint32, 3),
        ("clkmux_div", ctypes.c_uint32, 1),
        ("mode3q", ctypes.c_uint32, 1),
        ("div6", ctypes.c_uint32, 1),
        ("dis_rf", ctypes.c_uint32, 1),
        ("rf_prog", ctypes.c_uint32, 2),
        ("dis_serhi", ctypes.c_uint32, 1),
        ("serhi_prog", ctypes.c_uint32, 2),
        ("dis_serlo", ctypes.c_uint32, 1),
        ("serlo_prog", ctypes.c_uint32, 2),
        ("ser_bypass_s16to4", ctypes.c_uint32, 1),
        ("ser_bypass4to2", ctypes.c_uint32, 1),
        ("res_31_17", ctypes.c_uint32, 15) ]
class tx_dac_conf_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_dac_conf_lut_bf_s), ('value', ctypes.c_uint32) ]

class tx_jesd_ant_meta_mapping_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("tx_jesd_ch_meta_sel", ctypes.c_uint32) ]
class tx_jesd_ant_meta_mapping_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_jesd_ant_meta_mapping_lut_bf_s), ('value', ctypes.c_uint32) ]

class tx_pdpd_cfg_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("ext_cfg", ctypes.c_uint8, 7),
        ("clut_interp_en", ctypes.c_uint8, 1) ]
class tx_pdpd_cfg_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_pdpd_cfg_lut_bf_s), ('value', ctypes.c_uint8) ]

class tx_pdpd_dly_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("et_dly", ctypes.c_uint16, 7),
        ("adv", ctypes.c_uint16, 1),
        ("pt_dly", ctypes.c_uint16, 7),
        ("res_15", ctypes.c_uint16, 1) ]
class tx_pdpd_dly_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_pdpd_dly_lut_bf_s), ('value', ctypes.c_uint16) ]

class tx_pdpd_mod_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("gang_mod", ctypes.c_uint16, 1),
        ("wr_pc_m1", ctypes.c_uint16, 1),
        ("rx_pd_strm_en", ctypes.c_uint16, 1),
        ("rx_pd_en", ctypes.c_uint16, 1),
        ("tx_pd_strm_en", ctypes.c_uint16, 1),
        ("pd_extra_only", ctypes.c_uint16, 1),
        ("extra_static_en", ctypes.c_uint16, 1),
        ("tx_strm_en", ctypes.c_uint16, 1),
        ("pd_extra_en", ctypes.c_uint16, 1),
        ("pd_cap_mem_sel", ctypes.c_uint16, 2),
        ("v2d_input_ptr_sel", ctypes.c_uint16, 2),
        ("use_flow_ac", ctypes.c_uint16, 1),
        ("use_flow_b", ctypes.c_uint16, 1),
        ("use_flow_d", ctypes.c_uint16, 1) ]
class tx_pdpd_mod_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_pdpd_mod_lut_bf_s), ('value', ctypes.c_uint16) ]

class tx_pdpd_pc_sel_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("in_rate", ctypes.c_uint8, 3),
        ("out_rate", ctypes.c_uint8, 3),
        ("lut_mod", ctypes.c_uint8, 2) ]
class tx_pdpd_pc_sel_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_pdpd_pc_sel_lut_bf_s), ('value', ctypes.c_uint8) ]

class tx_print_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("print_monitor_base_address", ctypes.c_uint32) ]
class tx_print_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_print_config_lut_bf_s), ('value', ctypes.c_uint32) ]

class tx_topology_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("vex_vha", ctypes.c_uint8, 1),
        ("vha", ctypes.c_uint8, 1),
        ("vex_v2d", ctypes.c_uint8, 1),
        ("res_7_3", ctypes.c_uint8, 5) ]
class tx_topology_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_topology_lut_bf_s), ('value', ctypes.c_uint8) ]

class tx_v2d_if_params_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("lower_bound", ctypes.c_uint32, 11),
        ("upper_bound", ctypes.c_uint32, 11),
        ("b2h_strm_id", ctypes.c_uint32, 2),
        ("h2b_strm_id", ctypes.c_uint32, 2),
        ("res_31_26", ctypes.c_uint32, 6) ]
class tx_v2d_if_params_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_v2d_if_params_lut_bf_s), ('value', ctypes.c_uint32) ]

class tx_v2d_start_dly_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("start_src", ctypes.c_uint32, 2),
        ("trxant_merge_cfg", ctypes.c_uint32, 5),
        ("trxant_start_dly", ctypes.c_uint32, 4),
        ("jesd_start_dly", ctypes.c_uint32, 18),
        ("res_31_29", ctypes.c_uint32, 3),
        ("lm_chnl0", ctypes.c_uint32, 18),
        ("res_63_50", ctypes.c_uint32, 14),
        ("lm_chnl1", ctypes.c_uint32, 18),
        ("res_95_82", ctypes.c_uint32, 14) ]
class tx_v2d_start_dly_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', tx_v2d_start_dly_lut_bf_s), ('value', ctypes.c_uint32*3) ]

TX_JESD_ANT_META_MAPPING_LUT_MAX_ENTRY_NUM = 16
class tx_jesd_ant_meta_mapping_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_jesd_ant_meta_mapping_lut", tx_jesd_ant_meta_mapping_lut_bf_t * TX_JESD_ANT_META_MAPPING_LUT_MAX_ENTRY_NUM) ]

TX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM = 4
class tx_print_config_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_print_config_lut", tx_print_config_lut_bf_t * TX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM) ]

TX_DAC_CONF_LUT_MAX_ENTRY_NUM = 12
class tx_dac_conf_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_dac_conf_lut", tx_dac_conf_lut_bf_t * TX_DAC_CONF_LUT_MAX_ENTRY_NUM) ]

TX_PDPD_MOD_LUT_MAX_ENTRY_NUM = 8
class tx_pdpd_mod_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_pdpd_mod_lut", tx_pdpd_mod_lut_bf_t * TX_PDPD_MOD_LUT_MAX_ENTRY_NUM) ]

TX_V2D_IF_PARAMS_LUT_SUB_TBL_NUM = 4
TX_V2D_IF_PARAMS_LUT_MAX_ENTRY_NUM = 7
class tx_v2d_if_params_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_v2d_if_params_lut", tx_v2d_if_params_lut_bf_t * TX_V2D_IF_PARAMS_LUT_SUB_TBL_NUM * TX_V2D_IF_PARAMS_LUT_MAX_ENTRY_NUM) ]

TX_TOPOLOGY_LUT_MAX_ENTRY_NUM = 5
class tx_topology_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_topology_lut", tx_topology_lut_bf_t * TX_TOPOLOGY_LUT_MAX_ENTRY_NUM) ]

TX_PDPD_PC_SEL_LUT_SUB_TBL_NUM = 3
TX_PDPD_PC_SEL_LUT_MAX_ENTRY_NUM = 6
class tx_pdpd_pc_sel_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_pdpd_pc_sel_lut", tx_pdpd_pc_sel_lut_bf_t * TX_PDPD_PC_SEL_LUT_SUB_TBL_NUM * TX_PDPD_PC_SEL_LUT_MAX_ENTRY_NUM) ]

class tx_pdpd_cfg_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_pdpd_cfg_lut", tx_pdpd_cfg_lut_bf_t) ]

class tx_v2d_start_dly_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_v2d_start_dly_lut", tx_v2d_start_dly_lut_bf_t) ]

class tx_pdpd_dly_lut_t(ctypes.Structure):
    _fields_ = [ ("tx_pdpd_dly_lut", tx_pdpd_dly_lut_bf_t) ]

class tx_static_data_t(ctypes.Structure):
    _fields_ = [
        ("tx_jesd_ant_meta_mapping_lut", tx_jesd_ant_meta_mapping_lut_t),
        ("tx_print_config_lut", tx_print_config_lut_t),
        ("tx_dac_conf_lut", tx_dac_conf_lut_t),
        ("tx_pdpd_mod_lut", tx_pdpd_mod_lut_t),
        ("tx_v2d_if_params_lut", tx_v2d_if_params_lut_t),
        ("tx_topology_lut", tx_topology_lut_t),
        ("tx_pdpd_pc_sel_lut", tx_pdpd_pc_sel_lut_t),
        ("tx_pdpd_cfg_lut", tx_pdpd_cfg_lut_t),
        ("tx_v2d_start_dly_lut", tx_v2d_start_dly_lut_t),
        ("tx_pdpd_dly_lut", tx_pdpd_dly_lut_t) ]

# tx_static_data start address: _dram0_tx_tables_data_start