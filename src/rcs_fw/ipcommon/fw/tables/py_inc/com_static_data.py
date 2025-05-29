import ctypes

class com_drf_rate_conf_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("f_clk", ctypes.c_uint32, 1),
        ("pll_clk", ctypes.c_uint32, 2),
        ("ant_rate", ctypes.c_uint32, 3),
        ("sys_rate", ctypes.c_uint32, 5),
        ("smpl_fmt", ctypes.c_uint32, 1),
        ("stage_active", ctypes.c_uint32, 11),
        ("smpl_per_clk", ctypes.c_uint32, 4),
        ("res_31_27", ctypes.c_uint32, 5) ]
class com_drf_rate_conf_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_drf_rate_conf_lut_bf_s), ('value', ctypes.c_uint32) ]

class com_fw_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("fw_env", ctypes.c_uint32, 2),
        ("fw_debug_level", ctypes.c_uint32, 3),
        ("fw_trace_buffer_config", ctypes.c_uint32, 8),
        ("fw_boot_iteration_delay", ctypes.c_uint32, 11),
        ("fw_boot_iterations", ctypes.c_uint32, 8) ]
class com_fw_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_fw_config_lut_bf_s), ('value', ctypes.c_uint32) ]

class com_jesd_hostid_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("host_id", ctypes.c_uint8, 7),
        ("res_7", ctypes.c_uint8, 1) ]
class com_jesd_hostid_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_jesd_hostid_lut_bf_s), ('value', ctypes.c_uint8) ]

class com_rxfb_hostid_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("chain0", ctypes.c_uint16, 7),
        ("chain1", ctypes.c_uint16, 7),
        ("res_15_14", ctypes.c_uint16, 2) ]
class com_rxfb_hostid_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_rxfb_hostid_lut_bf_s), ('value', ctypes.c_uint16) ]

class com_trax_addr_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("trax_trigger_pc", ctypes.c_uint32),
        ("trax_stop_pcml", ctypes.c_uint32, 5),
        ("trax_stop_pcms", ctypes.c_uint32, 1),
        ("trax_ctrl_pcmen", ctypes.c_uint32, 1),
        ("res_63_39", ctypes.c_uint32, 25) ]
class com_trax_addr_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_trax_addr_config_lut_bf_s), ('value', ctypes.c_uint32*2) ]

class com_v2d_hostid_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("apb0_port0", ctypes.c_uint32, 7),
        ("apb0_port1", ctypes.c_uint32, 7),
        ("apb1_port0", ctypes.c_uint32, 7),
        ("apb1_port1", ctypes.c_uint32, 7),
        ("res_31_28", ctypes.c_uint32, 4) ]
class com_v2d_hostid_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_v2d_hostid_lut_bf_s), ('value', ctypes.c_uint32) ]

class com_v2d_strm_buf_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("strm_cnt", ctypes.c_uint32, 10),
        ("wm", ctypes.c_uint32, 12),
        ("res_31_22", ctypes.c_uint32, 10) ]
class com_v2d_strm_buf_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_v2d_strm_buf_lut_bf_s), ('value', ctypes.c_uint32) ]

class com_v2d_strm_cfg_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("ac", ctypes.c_uint16, 3),
        ("b", ctypes.c_uint16, 3),
        ("d", ctypes.c_uint16, 3),
        ("g", ctypes.c_uint16, 3),
        ("f", ctypes.c_uint16, 3),
        ("blk_sz", ctypes.c_uint16, 1) ]
class com_v2d_strm_cfg_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_v2d_strm_cfg_lut_bf_s), ('value', ctypes.c_uint16) ]

class com_vex_hostid_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("v0", ctypes.c_uint32, 5),
        ("v1", ctypes.c_uint32, 5),
        ("v2", ctypes.c_uint32, 5),
        ("v3", ctypes.c_uint32, 5),
        ("v4", ctypes.c_uint32, 6),
        ("res_31_26", ctypes.c_uint32, 6) ]
class com_vex_hostid_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_vex_hostid_lut_bf_s), ('value', ctypes.c_uint32) ]

class com_vha_hostid_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("port0", ctypes.c_uint16, 7),
        ("port1", ctypes.c_uint16, 7),
        ("res_15_14", ctypes.c_uint16, 2) ]
class com_vha_hostid_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_vha_hostid_lut_bf_s), ('value', ctypes.c_uint16) ]

class com_vha_if_wm_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("if_wm_1_us", ctypes.c_uint16, 8),
        ("if_wm_p5_us", ctypes.c_uint16, 7),
        ("res_15", ctypes.c_uint16, 1) ]
class com_vha_if_wm_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_vha_if_wm_lut_bf_s), ('value', ctypes.c_uint16) ]

class com_vha_rate_conf_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("stage_active", ctypes.c_uint16, 4),
        ("high_rate", ctypes.c_uint16, 3),
        ("low_rate", ctypes.c_uint16, 3),
        ("mix_rate", ctypes.c_uint16, 3),
        ("smpl_per_clk", ctypes.c_uint16, 3) ]
class com_vha_rate_conf_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', com_vha_rate_conf_lut_bf_s), ('value', ctypes.c_uint16) ]

class com_fw_config_lut_t(ctypes.Structure):
    _fields_ = [ ("com_fw_config_lut", com_fw_config_lut_bf_t) ]

class com_trax_addr_config_lut_t(ctypes.Structure):
    _fields_ = [ ("com_trax_addr_config_lut", com_trax_addr_config_lut_bf_t) ]

COM_DRF_RATE_CONF_LUT_MAX_ENTRY_NUM = 129
class com_drf_rate_conf_lut_t(ctypes.Structure):
    _fields_ = [ ("com_drf_rate_conf_lut", com_drf_rate_conf_lut_bf_t * COM_DRF_RATE_CONF_LUT_MAX_ENTRY_NUM) ]

COM_VHA_RATE_CONF_LUT_MAX_ENTRY_NUM = 11
class com_vha_rate_conf_lut_t(ctypes.Structure):
    _fields_ = [ ("com_vha_rate_conf_lut", com_vha_rate_conf_lut_bf_t * COM_VHA_RATE_CONF_LUT_MAX_ENTRY_NUM) ]

COM_VHA_IF_WM_LUT_SUB_TBL_NUM = 2
COM_VHA_IF_WM_LUT_MAX_ENTRY_NUM = 6
class com_vha_if_wm_lut_t(ctypes.Structure):
    _fields_ = [ ("com_vha_if_wm_lut", com_vha_if_wm_lut_bf_t * COM_VHA_IF_WM_LUT_SUB_TBL_NUM * COM_VHA_IF_WM_LUT_MAX_ENTRY_NUM) ]

COM_VEX_HOSTID_LUT_MAX_ENTRY_NUM = 8
class com_vex_hostid_lut_t(ctypes.Structure):
    _fields_ = [ ("com_vex_hostid_lut", com_vex_hostid_lut_bf_t * COM_VEX_HOSTID_LUT_MAX_ENTRY_NUM) ]

COM_V2D_HOSTID_LUT_MAX_ENTRY_NUM = 8
class com_v2d_hostid_lut_t(ctypes.Structure):
    _fields_ = [ ("com_v2d_hostid_lut", com_v2d_hostid_lut_bf_t * COM_V2D_HOSTID_LUT_MAX_ENTRY_NUM) ]

COM_VHA_HOSTID_LUT_MAX_ENTRY_NUM = 8
class com_vha_hostid_lut_t(ctypes.Structure):
    _fields_ = [ ("com_vha_hostid_lut", com_vha_hostid_lut_bf_t * COM_VHA_HOSTID_LUT_MAX_ENTRY_NUM) ]

COM_RXFB_HOSTID_LUT_MAX_ENTRY_NUM = 2
class com_rxfb_hostid_lut_t(ctypes.Structure):
    _fields_ = [ ("com_rxfb_hostid_lut", com_rxfb_hostid_lut_bf_t * COM_RXFB_HOSTID_LUT_MAX_ENTRY_NUM) ]

COM_JESD_HOSTID_LUT_MAX_ENTRY_NUM = 4
class com_jesd_hostid_lut_t(ctypes.Structure):
    _fields_ = [ ("com_jesd_hostid_lut", com_jesd_hostid_lut_bf_t * COM_JESD_HOSTID_LUT_MAX_ENTRY_NUM) ]

COM_V2D_STRM_CFG_LUT_MAX_ENTRY_NUM = 2
class com_v2d_strm_cfg_lut_t(ctypes.Structure):
    _fields_ = [ ("com_v2d_strm_cfg_lut", com_v2d_strm_cfg_lut_bf_t * COM_V2D_STRM_CFG_LUT_MAX_ENTRY_NUM) ]

COM_V2D_STRM_BUF_LUT_SUB_TBL_NUM = 2
COM_V2D_STRM_BUF_LUT_MAX_ENTRY_NUM = 12
class com_v2d_strm_buf_lut_t(ctypes.Structure):
    _fields_ = [ ("com_v2d_strm_buf_lut", com_v2d_strm_buf_lut_bf_t * COM_V2D_STRM_BUF_LUT_SUB_TBL_NUM * COM_V2D_STRM_BUF_LUT_MAX_ENTRY_NUM) ]

class com_static_data_t(ctypes.Structure):
    _fields_ = [
        ("com_fw_config_lut", com_fw_config_lut_t),
        ("com_trax_addr_config_lut", com_trax_addr_config_lut_t),
        ("com_drf_rate_conf_lut", com_drf_rate_conf_lut_t),
        ("com_vha_rate_conf_lut", com_vha_rate_conf_lut_t),
        ("com_vha_if_wm_lut", com_vha_if_wm_lut_t),
        ("com_vex_hostid_lut", com_vex_hostid_lut_t),
        ("com_v2d_hostid_lut", com_v2d_hostid_lut_t),
        ("com_vha_hostid_lut", com_vha_hostid_lut_t),
        ("com_rxfb_hostid_lut", com_rxfb_hostid_lut_t),
        ("com_jesd_hostid_lut", com_jesd_hostid_lut_t),
        ("com_v2d_strm_cfg_lut", com_v2d_strm_cfg_lut_t),
        ("com_v2d_strm_buf_lut", com_v2d_strm_buf_lut_t) ]

# com_static_data start address: _dram0_com_tables_data_start