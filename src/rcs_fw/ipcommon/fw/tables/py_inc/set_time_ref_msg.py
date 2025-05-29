import ctypes

class set_time_ref_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("res0", ctypes.c_uint32, 10),
        ("timestamp", ctypes.c_uint32) ]
class set_time_ref_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', set_time_ref_bf_s), ('value', ctypes.c_uint32*2) ]

