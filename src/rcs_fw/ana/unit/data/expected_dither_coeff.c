#include "dithercal.h"
#include "stdint.h"
#include "slicecal.h"
#include "dithercal.h"
#if (UNIT)
#if USE_ANALOG_SIMULATION_OUTPUT
int32_t expected_dither_coeff[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][NUM_DITHER_COEFFS]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {
        0, 0xab6, 0x585, 0x2bc, 0x150, 0xa3,
};
#else
int32_t expected_dither_coeff[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][NUM_DITHER_COEFFS]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {
        0x00000, 0x00869, 0x0042d, 0x0021a, 0x0010c, 0x00092,
};
#endif
#endif
