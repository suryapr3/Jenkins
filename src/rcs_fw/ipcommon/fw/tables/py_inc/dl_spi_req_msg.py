import ctypes

class dl_spi_off_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("quad_mask", ctypes.c_uint32, 4),
        ("mode", ctypes.c_uint32, 2),
        ("seq_num0", ctypes.c_uint32, 4),
        ("timestamp", ctypes.c_uint32, 28),
        ("seq_num1", ctypes.c_uint32, 4) ]
class dl_spi_off_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_spi_off_bf_s), ('value', ctypes.c_uint32*2) ]

class dl_spi_on_bf_s(ctypes.Structure):
    _fields_ = [
        ("opcode", ctypes.c_uint32, 16),
        ("timing", ctypes.c_uint32, 2),
        ("ref_index", ctypes.c_uint32, 4),
        ("quad_mask", ctypes.c_uint32, 4),
        ("rb", ctypes.c_uint32, 1),
        ("res0", ctypes.c_uint32, 1),
        ("seq_num0", ctypes.c_uint32, 4),
        ("timestamp", ctypes.c_uint32, 28),
        ("seq_num1", ctypes.c_uint32, 4) ]
class dl_spi_on_bf_t(ctypes.Union):
    _anonymous_ = ("u",)
    _fields_ = [ ('u', dl_spi_on_bf_s), ('value', ctypes.c_uint32*2) ]

