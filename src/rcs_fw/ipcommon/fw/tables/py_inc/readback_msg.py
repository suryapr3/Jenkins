import ctypes

class boot_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("boot_status", ctypes.c_uint32),
        ("commit_id", ctypes.c_uint32),
        ("iter", ctypes.c_uint32, 8),
        ("eb", ctypes.c_uint32, 8),
        ("minor", ctypes.c_uint32, 8),
        ("major", ctypes.c_uint32, 8),
        ("year", ctypes.c_uint32, 8),
        ("month", ctypes.c_uint32, 8),
        ("day", ctypes.c_uint32, 8),
        ("res1", ctypes.c_uint32, 8) ]
class boot_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', boot_readback_bf_s), ('value', ctypes.c_uint32*6) ]

class debug_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("level", ctypes.c_uint32, 2),
        ("debug_info_a", ctypes.c_uint32, 14),
        ("debug_info_b", ctypes.c_uint32, 16),
        ("debug_data_0", ctypes.c_uint32),
        ("debug_data_1", ctypes.c_uint32),
        ("debug_data_2", ctypes.c_uint32),
        ("debug_data_3", ctypes.c_uint32),
        ("debug_data_4", ctypes.c_uint32),
        ("debug_data_5", ctypes.c_uint32),
        ("debug_data_6", ctypes.c_uint32),
        ("debug_data_7", ctypes.c_uint32),
        ("debug_data_8", ctypes.c_uint32),
        ("debug_data_9", ctypes.c_uint32),
        ("debug_data_10", ctypes.c_uint32),
        ("debug_data_11", ctypes.c_uint32),
        ("debug_data_12", ctypes.c_uint32) ]
class debug_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', debug_readback_bf_s), ('value', ctypes.c_uint32*16) ]

class dl_config_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("config_status", ctypes.c_uint32, 1),
        ("quad0", ctypes.c_uint32, 1),
        ("quad1", ctypes.c_uint32, 1),
        ("quad2", ctypes.c_uint32, 1),
        ("quad3", ctypes.c_uint32, 1),
        ("res1", ctypes.c_uint32, 27) ]
class dl_config_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_config_readback_bf_s), ('value', ctypes.c_uint32*3) ]

class dl_on_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("avg_0", ctypes.c_int32, 24),
        ("cps_0", ctypes.c_uint32, 8),
        ("avg_1", ctypes.c_int32, 24),
        ("cps_1", ctypes.c_uint32, 8),
        ("avg_2", ctypes.c_int32, 24),
        ("cps_2", ctypes.c_uint32, 8),
        ("avg_3", ctypes.c_int32, 24),
        ("cps_3", ctypes.c_uint32, 8),
        ("avg_4", ctypes.c_int32, 24),
        ("cps_4", ctypes.c_uint32, 8),
        ("avg_5", ctypes.c_int32, 24),
        ("cps_5", ctypes.c_uint32, 8),
        ("avg_6", ctypes.c_int32, 24),
        ("cps_6", ctypes.c_uint32, 8),
        ("avg_7", ctypes.c_int32, 24),
        ("cps_7", ctypes.c_uint32, 8),
        ("peak_0", ctypes.c_int32, 12),
        ("peak_1", ctypes.c_int32, 12),
        ("res1", ctypes.c_uint32, 8),
        ("peak_2", ctypes.c_int32, 12),
        ("peak_3", ctypes.c_int32, 12),
        ("res2", ctypes.c_uint32, 8),
        ("peak_4", ctypes.c_int32, 12),
        ("peak_5", ctypes.c_int32, 12),
        ("res3", ctypes.c_uint32, 8),
        ("peak_6", ctypes.c_int32, 12),
        ("peak_7", ctypes.c_int32, 12),
        ("res4", ctypes.c_uint32, 8) ]
class dl_on_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_on_readback_bf_s), ('value', ctypes.c_uint32*14) ]

class error_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("level", ctypes.c_uint32, 2),
        ("error_code", ctypes.c_uint32, 14),
        ("reason_code", ctypes.c_uint32, 16),
        ("error_data_0", ctypes.c_uint32),
        ("error_data_1", ctypes.c_uint32),
        ("error_data_2", ctypes.c_uint32),
        ("error_data_3", ctypes.c_uint32),
        ("error_data_4", ctypes.c_uint32),
        ("error_data_5", ctypes.c_uint32),
        ("error_data_6", ctypes.c_uint32),
        ("error_data_7", ctypes.c_uint32),
        ("error_data_8", ctypes.c_uint32),
        ("error_data_9", ctypes.c_uint32),
        ("error_data_10", ctypes.c_uint32),
        ("error_data_11", ctypes.c_uint32),
        ("error_data_12", ctypes.c_uint32) ]
class error_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', error_readback_bf_s), ('value', ctypes.c_uint32*16) ]

class ul_config_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("config_status", ctypes.c_uint32, 1),
        ("quad0", ctypes.c_uint32, 1),
        ("quad1", ctypes.c_uint32, 1),
        ("quad2", ctypes.c_uint32, 1),
        ("quad3", ctypes.c_uint32, 1),
        ("res1", ctypes.c_uint32, 27) ]
class ul_config_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_config_readback_bf_s), ('value', ctypes.c_uint32*3) ]

class ul_on_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("avg_0", ctypes.c_int32, 24),
        ("cgs_0", ctypes.c_uint32, 8),
        ("avg_1", ctypes.c_int32, 24),
        ("cgs_1", ctypes.c_uint32, 8),
        ("avg_2", ctypes.c_int32, 24),
        ("cgs_2", ctypes.c_uint32, 8),
        ("avg_3", ctypes.c_int32, 24),
        ("cgs_3", ctypes.c_uint32, 8),
        ("avg_4", ctypes.c_int32, 24),
        ("cgs_4", ctypes.c_uint32, 8),
        ("avg_5", ctypes.c_int32, 24),
        ("cgs_5", ctypes.c_uint32, 8),
        ("avg_6", ctypes.c_int32, 24),
        ("cgs_6", ctypes.c_uint32, 8),
        ("avg_7", ctypes.c_int32, 24),
        ("cgs_7", ctypes.c_uint32, 8),
        ("peak_0", ctypes.c_int32, 12),
        ("peak_1", ctypes.c_int32, 12),
        ("fovr_alarm_vector", ctypes.c_uint32, 8),
        ("peak_2", ctypes.c_int32, 12),
        ("peak_3", ctypes.c_int32, 12),
        ("res1", ctypes.c_uint32, 8),
        ("peak_4", ctypes.c_int32, 12),
        ("peak_5", ctypes.c_int32, 12),
        ("res2", ctypes.c_uint32, 8),
        ("peak_6", ctypes.c_int32, 12),
        ("peak_7", ctypes.c_int32, 12),
        ("res3", ctypes.c_uint32, 8) ]
class ul_on_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_on_readback_bf_s), ('value', ctypes.c_uint32*14) ]

class warmup_readback_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("src", ctypes.c_uint32, 3),
        ("res0", ctypes.c_uint32, 13),
        ("timestamp", ctypes.c_uint32),
        ("quad0_ul_status", ctypes.c_uint32, 8),
        ("quad1_ul_status", ctypes.c_uint32, 8),
        ("quad2_ul_status", ctypes.c_uint32, 8),
        ("quad3_ul_status", ctypes.c_uint32, 8),
        ("quad0_dl_status", ctypes.c_uint32, 8),
        ("quad1_dl_status", ctypes.c_uint32, 8),
        ("quad2_dl_status", ctypes.c_uint32, 8),
        ("quad3_dl_status", ctypes.c_uint32, 8),
        ("quad0_ul_latency", ctypes.c_uint32, 16),
        ("quad1_ul_latency", ctypes.c_uint32, 16),
        ("quad2_ul_latency", ctypes.c_uint32, 16),
        ("quad3_ul_latency", ctypes.c_uint32, 16),
        ("quad0_dl_latency", ctypes.c_uint32, 16),
        ("quad1_dl_latency", ctypes.c_uint32, 16),
        ("quad2_dl_latency", ctypes.c_uint32, 16),
        ("quad3_dl_latency", ctypes.c_uint32, 16) ]
class warmup_readback_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', warmup_readback_bf_s), ('value', ctypes.c_uint32*8) ]

