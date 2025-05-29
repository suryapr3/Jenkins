import ctypes

class rx_gain_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("gain", ctypes.c_uint32, 16),
        ("shift", ctypes.c_uint32, 4),
        ("res_31_20", ctypes.c_uint32, 12) ]
class rx_gain_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_gain_lut_bf_s), ('value', ctypes.c_uint32) ]

class rx_hwa_ant_meta_mapping_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("rx_hwa_ch_meta_sel", ctypes.c_uint8) ]
class rx_hwa_ant_meta_mapping_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_hwa_ant_meta_mapping_lut_bf_s), ('value', ctypes.c_uint8) ]

class rx_print_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("print_monitor_base_address", ctypes.c_uint32) ]
class rx_print_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_print_config_lut_bf_s), ('value', ctypes.c_uint32) ]

class rx_to_adc_cpu_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("bsg_info_ramp_start", ctypes.c_uint32),
        ("bsg_info_ramp_end", ctypes.c_uint32),
        ("bsg_info_num_points", ctypes.c_uint32) ]
class rx_to_adc_cpu_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_to_adc_cpu_config_lut_bf_s), ('value', ctypes.c_uint32*3) ]

class rx_to_adc_cpu_delay_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("dc_source_settling", ctypes.c_uint32),
        ("sequencer_instruction", ctypes.c_uint32),
        ("firmware_sample_wait", ctypes.c_uint32) ]
class rx_to_adc_cpu_delay_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_to_adc_cpu_delay_lut_bf_s), ('value', ctypes.c_uint32*3) ]

class rx_topology_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("vex_vha", ctypes.c_uint8, 1),
        ("vha", ctypes.c_uint8, 1),
        ("vex_v2d", ctypes.c_uint8, 1),
        ("res_7_3", ctypes.c_uint8, 5) ]
class rx_topology_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_topology_lut_bf_s), ('value', ctypes.c_uint8) ]

class rx_vha_if_wm_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("if_wm_1_us", ctypes.c_uint32, 9),
        ("if_wm_p5_us", ctypes.c_uint32, 9),
        ("res_31_18", ctypes.c_uint32, 14) ]
class rx_vha_if_wm_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rx_vha_if_wm_lut_bf_s), ('value', ctypes.c_uint32) ]

RX_HWA_ANT_META_MAPPING_LUT_MAX_ENTRY_NUM = 8
class rx_hwa_ant_meta_mapping_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_hwa_ant_meta_mapping_lut", rx_hwa_ant_meta_mapping_lut_bf_t * RX_HWA_ANT_META_MAPPING_LUT_MAX_ENTRY_NUM) ]

RX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM = 4
class rx_print_config_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_print_config_lut", rx_print_config_lut_bf_t * RX_PRINT_CONFIG_LUT_MAX_ENTRY_NUM) ]

RX_VHA_IF_WM_LUT_SUB_TBL_NUM = 2
RX_VHA_IF_WM_LUT_MAX_ENTRY_NUM = 4
class rx_vha_if_wm_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_vha_if_wm_lut", rx_vha_if_wm_lut_bf_t * RX_VHA_IF_WM_LUT_SUB_TBL_NUM * RX_VHA_IF_WM_LUT_MAX_ENTRY_NUM) ]

class rx_gain_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_gain_lut", rx_gain_lut_bf_t) ]

RX_TOPOLOGY_LUT_MAX_ENTRY_NUM = 5
class rx_topology_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_topology_lut", rx_topology_lut_bf_t * RX_TOPOLOGY_LUT_MAX_ENTRY_NUM) ]

RX_TO_ADC_CPU_CONFIG_LUT_SUB_TBL_NUM = 2
RX_TO_ADC_CPU_CONFIG_LUT_MAX_ENTRY_NUM = 8
class rx_to_adc_cpu_config_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_to_adc_cpu_config_lut", rx_to_adc_cpu_config_lut_bf_t * RX_TO_ADC_CPU_CONFIG_LUT_SUB_TBL_NUM * RX_TO_ADC_CPU_CONFIG_LUT_MAX_ENTRY_NUM) ]

class rx_to_adc_cpu_delay_lut_t(ctypes.Structure):
    _fields_ = [ ("rx_to_adc_cpu_delay_lut", rx_to_adc_cpu_delay_lut_bf_t) ]

class rx_static_data_t(ctypes.Structure):
    _fields_ = [
        ("rx_hwa_ant_meta_mapping_lut", rx_hwa_ant_meta_mapping_lut_t),
        ("rx_print_config_lut", rx_print_config_lut_t),
        ("rx_vha_if_wm_lut", rx_vha_if_wm_lut_t),
        ("rx_gain_lut", rx_gain_lut_t),
        ("rx_topology_lut", rx_topology_lut_t),
        ("rx_to_adc_cpu_config_lut", rx_to_adc_cpu_config_lut_t),
        ("rx_to_adc_cpu_delay_lut", rx_to_adc_cpu_delay_lut_t) ]

# rx_static_data start address: _dram0_rx_tables_data_start