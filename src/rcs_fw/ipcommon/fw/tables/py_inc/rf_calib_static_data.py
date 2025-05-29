import ctypes

class cal_print_config_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("print_monitor_base_address", ctypes.c_uint32) ]
class cal_print_config_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', cal_print_config_lut_bf_s), ('value', ctypes.c_uint32) ]

class rf_calib_control_lut_bf_s(ctypes.Structure):
    _fields_ = [
        ("nleq_calibration_enable", ctypes.c_uint32, 1),
        ("smc_calibration_enable", ctypes.c_uint32, 1),
        ("cdac_dpd_calibration_enable", ctypes.c_uint32, 1),
        ("", ctypes.c_uint32, 29) ]
class rf_calib_control_lut_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', rf_calib_control_lut_bf_s), ('value', ctypes.c_uint32) ]

class rf_calib_control_lut_t(ctypes.Structure):
    _fields_ = [ ("rf_calib_control_lut", rf_calib_control_lut_bf_t) ]

CAL_PRINT_CONFIG_LUT_MAX_ENTRY_NUM = 4
class cal_print_config_lut_t(ctypes.Structure):
    _fields_ = [ ("cal_print_config_lut", cal_print_config_lut_bf_t * CAL_PRINT_CONFIG_LUT_MAX_ENTRY_NUM) ]

class rf_calib_static_data_t(ctypes.Structure):
    _fields_ = [
        ("rf_calib_control_lut", rf_calib_control_lut_t),
        ("cal_print_config_lut", cal_print_config_lut_t) ]

# rf_calib_static_data start address: _dram0_cal_tables_data_start