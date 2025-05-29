import ctypes

class dl_config_ant_grp_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res_31_23", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("digrf_mixer_freq", ctypes.c_uint32, 24),
        ("drf_rate", ctypes.c_uint32, 8),
        ("ant_group_dl_ant_mask", ctypes.c_uint32, 16),
        ("hw_tdd", ctypes.c_uint32, 1),
        ("pdpd_rate", ctypes.c_uint32, 3),
        ("pdpd_mode", ctypes.c_uint32, 3),
        ("pdpd_delay", ctypes.c_uint32, 4),
        ("fifo_delay", ctypes.c_uint32, 4),
        ("drf_filter_mode", ctypes.c_uint32, 1),
        ("jesd_dl_idx", ctypes.c_uint32, 8),
        ("q0_j", ctypes.c_uint32, 2),
        ("q1_j", ctypes.c_uint32, 2),
        ("q2_j", ctypes.c_uint32, 2),
        ("q3_j", ctypes.c_uint32, 2),
        ("jesd_latency", ctypes.c_uint32, 16),
        ("fbr_mask", ctypes.c_uint32, 4),
        ("fbr_idx", ctypes.c_uint32, 8),
        ("res_191_172", ctypes.c_uint32, 20),
        ("vha_dl_latency", ctypes.c_uint32, 16),
        ("res_223_208", ctypes.c_uint32, 16),
        ("ant_group_dl_band_freq0", ctypes.c_uint32, 24),
        ("vha_rate", ctypes.c_uint32, 4),
        ("strm_cfg", ctypes.c_uint32, 4),
        ("ant_group_dl_band_freq1", ctypes.c_uint32, 24),
        ("vha_filter_mode", ctypes.c_uint32, 1),
        ("vha_dl_xn_en", ctypes.c_uint32, 1),
        ("pdpd_op_mode", ctypes.c_uint32, 2),
        ("topology", ctypes.c_uint32, 3),
        ("res_287", ctypes.c_uint32, 1) ]
class dl_config_ant_grp_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_config_ant_grp_bf_s), ('value', ctypes.c_uint32*9) ]

class dl_off_bf_s(ctypes.Structure):
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
class dl_off_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_off_bf_s), ('value', ctypes.c_uint32*5) ]

class dl_on_bf_s(ctypes.Structure):
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
        ("power_ant0", ctypes.c_int32, 8),
        ("power_ant1", ctypes.c_int32, 8),
        ("power_ant2", ctypes.c_int32, 8),
        ("power_ant3", ctypes.c_int32, 8),
        ("power_ant4", ctypes.c_int32, 8),
        ("power_ant5", ctypes.c_int32, 8),
        ("power_ant6", ctypes.c_int32, 8),
        ("power_ant7", ctypes.c_int32, 8),
        ("power_ant8", ctypes.c_int32, 8),
        ("power_ant9", ctypes.c_int32, 8),
        ("power_ant10", ctypes.c_int32, 8),
        ("power_ant11", ctypes.c_int32, 8),
        ("power_ant12", ctypes.c_int32, 8),
        ("power_ant13", ctypes.c_int32, 8),
        ("power_ant14", ctypes.c_int32, 8),
        ("power_ant15", ctypes.c_int32, 8),
        ("quad_delay1", ctypes.c_uint32, 12),
        ("res2", ctypes.c_uint32, 4),
        ("quad_delay2", ctypes.c_uint32, 12),
        ("res3", ctypes.c_uint32, 4),
        ("quad_delay3", ctypes.c_uint32, 12),
        ("res4", ctypes.c_uint32, 20) ]
class dl_on_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_on_bf_s), ('value', ctypes.c_uint32*9) ]

class dl_update_control_bf_s(ctypes.Structure):
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
        ("power_ant0", ctypes.c_int32, 8),
        ("power_ant1", ctypes.c_int32, 8),
        ("power_ant2", ctypes.c_int32, 8),
        ("power_ant3", ctypes.c_int32, 8),
        ("power_ant4", ctypes.c_int32, 8),
        ("power_ant5", ctypes.c_int32, 8),
        ("power_ant6", ctypes.c_int32, 8),
        ("power_ant7", ctypes.c_int32, 8),
        ("power_ant8", ctypes.c_int32, 8),
        ("power_ant9", ctypes.c_int32, 8),
        ("power_ant10", ctypes.c_int32, 8),
        ("power_ant11", ctypes.c_int32, 8),
        ("power_ant12", ctypes.c_int32, 8),
        ("power_ant13", ctypes.c_int32, 8),
        ("power_ant14", ctypes.c_int32, 8),
        ("power_ant15", ctypes.c_int32, 8),
        ("quad_delay1", ctypes.c_uint32, 12),
        ("res2", ctypes.c_uint32, 4),
        ("quad_delay2", ctypes.c_uint32, 12),
        ("res3", ctypes.c_uint32, 4),
        ("quad_delay3", ctypes.c_uint32, 12),
        ("res4", ctypes.c_uint32, 20) ]
class dl_update_control_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_update_control_bf_s), ('value', ctypes.c_uint32*9) ]

