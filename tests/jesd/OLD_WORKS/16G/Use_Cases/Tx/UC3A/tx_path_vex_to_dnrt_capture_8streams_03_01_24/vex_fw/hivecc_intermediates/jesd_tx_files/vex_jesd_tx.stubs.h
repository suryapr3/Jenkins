
#define _hrt_pass_params_jesd_tx()
#define _hrt_read_result_jesd_tx() 0

/* jesd_tx: check address known, default stub, hrt_start_jesd_tx, hrt_end_jesd_tx */

#ifndef HIVE_ADDR_jesd_tx_entry
#error -----------------------------------------------------------------------------------------
#error Address for function jesd_tx not defined, please include mapfile before including stubs file
#error -----------------------------------------------------------------------------------------
#endif

#define jesd_tx() hrt_run_jesd_tx()

#ifdef __GNUC__
HRT_INLINE void hrt_run_jesd_tx() __attribute__((unused));
#endif

HRT_INLINE void hrt_run_jesd_tx()
{
  _hrt_pass_params_jesd_tx();
  hrt_cell_run_function(CELL, jesd_tx);
}

#ifdef __GNUC__
HRT_INLINE void hrt_start_jesd_tx() __attribute__((unused));
#endif

HRT_INLINE void hrt_start_jesd_tx()
{
  _hrt_pass_params_jesd_tx();
  hrt_cell_start_function(CELL, jesd_tx);
}


