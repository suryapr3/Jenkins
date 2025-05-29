
#define _hrt_pass_params_jesd_rx()
#define _hrt_read_result_jesd_rx() 0

/* jesd_rx: check address known, default stub, hrt_start_jesd_rx, hrt_end_jesd_rx */

#ifndef HIVE_ADDR_jesd_rx_entry
#error -----------------------------------------------------------------------------------------
#error Address for function jesd_rx not defined, please include mapfile before including stubs file
#error -----------------------------------------------------------------------------------------
#endif

#define jesd_rx() hrt_run_jesd_rx()

#ifdef __GNUC__
HRT_INLINE void hrt_run_jesd_rx() __attribute__((unused));
#endif

HRT_INLINE void hrt_run_jesd_rx()
{
  _hrt_pass_params_jesd_rx();
  hrt_cell_run_function(CELL, jesd_rx);
}

#ifdef __GNUC__
HRT_INLINE void hrt_start_jesd_rx() __attribute__((unused));
#endif

HRT_INLINE void hrt_start_jesd_rx()
{
  _hrt_pass_params_jesd_rx();
  hrt_cell_start_function(CELL, jesd_rx);
}


