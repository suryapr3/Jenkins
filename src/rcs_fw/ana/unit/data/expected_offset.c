#include "offset_cal.h"
#include "stdint.h"
#include "slicecal.h"
#include "offset_cal.h"
#if (UNIT)
#if USE_ANALOG_SIMULATION_OUTPUT
int32_t expected_offset_coeff[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][NUM_OFFSET_COEFFS]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {
        0x1fe18,
};
#else
int32_t expected_offset_coeff[NUM_ADC_IN_ONE_QUAD][NUM_SLICES_IN_ONE_ADC][NUM_OFFSET_COEFFS]
    __attribute__ ((section (".hwc_slice_cal_output_global"))) = {
        0x0000,
};
#endif
#endif
