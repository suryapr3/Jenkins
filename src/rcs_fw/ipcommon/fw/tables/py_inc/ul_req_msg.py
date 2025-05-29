import ctypes

class ul_config_ant_grp_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res_31_23", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("digrf_mixer_freq", ctypes.c_uint32, 24),
        ("drf_rate", ctypes.c_uint32, 8),
        ("ant_group_ul_ant_mask", ctypes.c_uint32, 16),
        ("vha_ul_latency", ctypes.c_uint32, 16),
        ("jesd_ul_idx", ctypes.c_uint32, 8),
        ("q0_j", ctypes.c_uint32, 2),
        ("q1_j", ctypes.c_uint32, 2),
        ("q2_j", ctypes.c_uint32, 2),
        ("q3_j", ctypes.c_uint32, 2),
        ("drf_latency", ctypes.c_uint32, 16),
        ("ant_group_ul_band_freq0", ctypes.c_uint32, 24),
        ("vha_rate", ctypes.c_uint32, 4),
        ("vha_filter_mode", ctypes.c_uint32, 1),
        ("topology", ctypes.c_uint32, 3),
        ("ant_group_ul_band_freq1", ctypes.c_uint32, 24),
        ("hw_tdd", ctypes.c_uint32, 1),
        ("strm_cfg", ctypes.c_uint32, 4),
        ("res_223_221", ctypes.c_uint32, 3) ]
class ul_config_ant_grp_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_config_ant_grp_bf_s), ('value', ctypes.c_uint32*7) ]

class ul_off_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("mode", ctypes.c_uint32, 2),
        ("res1", ctypes.c_uint32, 14),
        ("quad_mask0", ctypes.c_uint32, 4),
        ("quad_mask1", ctypes.c_uint32, 4),
        ("quad_mask2", ctypes.c_uint32, 4),
        ("quad_mask3", ctypes.c_uint32, 4),
        ("quad_delay1", ctypes.c_uint32, 12),
        ("res2", ctypes.c_uint32, 4),
        ("quad_delay2", ctypes.c_uint32, 12),
        ("res3", ctypes.c_uint32, 4),
        ("quad_delay3", ctypes.c_uint32, 12),
        ("res4", ctypes.c_uint32, 20) ]
class ul_off_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_off_bf_s), ('value', ctypes.c_uint32*5) ]

class ul_on_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("res1", ctypes.c_uint32, 16),
        ("quad_mask0", ctypes.c_uint32, 4),
        ("quad_mask1", ctypes.c_uint32, 4),
        ("quad_mask2", ctypes.c_uint32, 4),
        ("quad_mask3", ctypes.c_uint32, 4),
        ("gain_ant0", ctypes.c_int32, 8),
        ("gain_ant1", ctypes.c_int32, 8),
        ("gain_ant2", ctypes.c_int32, 8),
        ("gain_ant3", ctypes.c_int32, 8),
        ("gain_ant4", ctypes.c_int32, 8),
        ("gain_ant5", ctypes.c_int32, 8),
        ("gain_ant6", ctypes.c_int32, 8),
        ("gain_ant7", ctypes.c_int32, 8),
        ("gain_ant8", ctypes.c_int32, 8),
        ("gain_ant9", ctypes.c_int32, 8),
        ("gain_ant10", ctypes.c_int32, 8),
        ("gain_ant11", ctypes.c_int32, 8),
        ("gain_ant12", ctypes.c_int32, 8),
        ("gain_ant13", ctypes.c_int32, 8),
        ("gain_ant14", ctypes.c_int32, 8),
        ("gain_ant15", ctypes.c_int32, 8),
        ("quad_delay1", ctypes.c_uint32, 12),
        ("res2", ctypes.c_uint32, 4),
        ("quad_delay2", ctypes.c_uint32, 12),
        ("res3", ctypes.c_uint32, 4),
        ("quad_delay3", ctypes.c_uint32, 12),
        ("res4", ctypes.c_uint32, 20) ]
class ul_on_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_on_bf_s), ('value', ctypes.c_uint32*9) ]

class ul_update_control_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("update", ctypes.c_uint32, 4),
        ("res1", ctypes.c_uint32, 12),
        ("quad_mask0", ctypes.c_uint32, 4),
        ("quad_mask1", ctypes.c_uint32, 4),
        ("quad_mask2", ctypes.c_uint32, 4),
        ("quad_mask3", ctypes.c_uint32, 4),
        ("gain_ant0", ctypes.c_int32, 8),
        ("gain_ant1", ctypes.c_int32, 8),
        ("gain_ant2", ctypes.c_int32, 8),
        ("gain_ant3", ctypes.c_int32, 8),
        ("gain_ant4", ctypes.c_int32, 8),
        ("gain_ant5", ctypes.c_int32, 8),
        ("gain_ant6", ctypes.c_int32, 8),
        ("gain_ant7", ctypes.c_int32, 8),
        ("gain_ant8", ctypes.c_int32, 8),
        ("gain_ant9", ctypes.c_int32, 8),
        ("gain_ant10", ctypes.c_int32, 8),
        ("gain_ant11", ctypes.c_int32, 8),
        ("gain_ant12", ctypes.c_int32, 8),
        ("gain_ant13", ctypes.c_int32, 8),
        ("gain_ant14", ctypes.c_int32, 8),
        ("gain_ant15", ctypes.c_int32, 8),
        ("quad_delay1", ctypes.c_uint32, 12),
        ("res2", ctypes.c_uint32, 4),
        ("quad_delay2", ctypes.c_uint32, 12),
        ("res3", ctypes.c_uint32, 4),
        ("quad_delay3", ctypes.c_uint32, 12),
        ("res4", ctypes.c_uint32, 20) ]
class ul_update_control_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', ul_update_control_bf_s), ('value', ctypes.c_uint32*9) ]

