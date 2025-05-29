#include "stdint.h"
#include "slicecal.h"
#if (UNIT)
#if USE_ANALOG_SIMULATION_OUTPUT
uint32_t expected_w0_w11[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][ASC_SLICE_W_TOTAL - 6]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {0x380d, 0x3806, 0x3aa9, 0x105a, 0x1069, 0x102a,
                                                                  0x49c,  0x486,  0x4c5,  0x195,  0xdc,   0x157};
#else
uint32_t expected_w0_w11[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][ASC_SLICE_W_TOTAL - 6]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {
        0x0430d, 0x04315, 0x0430f, 0x010c1, 0x010c6, 0x010c3, 0x0042e, 0x00433, 0x0042e, 0x0010d, 0x0010d, 0x0010b,
};
#endif
#endif
