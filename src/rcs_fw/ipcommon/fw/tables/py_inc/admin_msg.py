import ctypes

class bfn_sync_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("timestamp_msb", ctypes.c_uint32),
        ("bfn_sync_type", ctypes.c_uint32, 1),
        ("resv1", ctypes.c_uint32, 31) ]
class bfn_sync_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', bfn_sync_bf_s), ('value', ctypes.c_uint32*4) ]

class cal_config_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("sc_adc_en", ctypes.c_uint32, 1),
        ("sc_adc_ex", ctypes.c_uint32, 1),
        ("quad_mask_sc_adc", ctypes.c_uint32, 4),
        ("res1", ctypes.c_uint32, 2),
        ("cs_oadc_en", ctypes.c_uint32, 1),
        ("cs_oadc_ex", ctypes.c_uint32, 1),
        ("quad_mask_cs_oadc", ctypes.c_uint32, 4),
        ("res2", ctypes.c_uint32, 2),
        ("xt_oadc_en", ctypes.c_uint32, 1),
        ("xt_oadc_ex", ctypes.c_uint32, 1),
        ("quad_mask_xt_oadc", ctypes.c_uint32, 4),
        ("res3", ctypes.c_uint32, 2),
        ("smc_dac_en", ctypes.c_uint32, 1),
        ("smc_dac_ex", ctypes.c_uint32, 1),
        ("quad_mask_smc_dac", ctypes.c_uint32, 4),
        ("res4", ctypes.c_uint32, 2),
        ("smc_caldac_en", ctypes.c_uint32, 1),
        ("smc_caldac_ex", ctypes.c_uint32, 1),
        ("quad_mask_smc_caldac", ctypes.c_uint32, 4),
        ("res5", ctypes.c_uint32, 2),
        ("dskw_caldac_en", ctypes.c_uint32, 1),
        ("dskw_caldac_ex", ctypes.c_uint32, 1),
        ("quad_mask_dskw_caldac", ctypes.c_uint32, 4),
        ("res6", ctypes.c_uint32, 2),
        ("nleq_adc_en", ctypes.c_uint32, 1),
        ("nleq_adc_ex", ctypes.c_uint32, 1),
        ("quad_mask_nleq_adc", ctypes.c_uint32, 4),
        ("res7", ctypes.c_uint32, 2),
        ("dpd_dac_en", ctypes.c_uint32, 1),
        ("dpd_dac_ex", ctypes.c_uint32, 1),
        ("quad_mask_dpd_dac", ctypes.c_uint32, 4),
        ("res8", ctypes.c_uint32, 2) ]
class cal_config_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', cal_config_bf_s), ('value', ctypes.c_uint32*4) ]

class reconfig_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("ul_quad", ctypes.c_uint32, 4),
        ("dl_quad", ctypes.c_uint32, 4),
        ("res1", ctypes.c_uint32, 24) ]
class reconfig_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', reconfig_bf_s), ('value', ctypes.c_uint32*3) ]

class shutdown_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32) ]
class shutdown_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', shutdown_bf_s), ('value', ctypes.c_uint32*2) ]

class sleep_control_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("state", ctypes.c_uint32, 2),
        ("res1", ctypes.c_uint32, 30) ]
class sleep_control_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', sleep_control_bf_s), ('value', ctypes.c_uint32*3) ]

class warmup_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 9),
        ("timestamp", ctypes.c_uint32),
        ("ul_quad_en_mask", ctypes.c_uint32, 4),
        ("dl_quad_en_mask", ctypes.c_uint32, 4),
        ("loopback_mode_en", ctypes.c_uint32, 4),
        ("res2", ctypes.c_uint32, 20) ]
class warmup_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', warmup_bf_s), ('value', ctypes.c_uint32*3) ]

