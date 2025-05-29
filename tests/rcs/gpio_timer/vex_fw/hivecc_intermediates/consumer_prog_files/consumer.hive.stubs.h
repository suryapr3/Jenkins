
#define _hrt_pass_params_consumer_prog()
#define _hrt_read_result_consumer_prog() 0

/* consumer_prog: check address known, default stub, hrt_start_consumer_prog, hrt_end_consumer_prog */

#ifndef HIVE_ADDR_consumer_prog_entry
#error -----------------------------------------------------------------------------------------
#error Address for function consumer_prog not defined, please include mapfile before including stubs file
#error -----------------------------------------------------------------------------------------
#endif

#define consumer_prog() hrt_run_consumer_prog()

#ifdef __GNUC__
HRT_INLINE void hrt_run_consumer_prog() __attribute__((unused));
#endif

HRT_INLINE void hrt_run_consumer_prog()
{
  _hrt_pass_params_consumer_prog();
  hrt_cell_run_function(CELL, consumer_prog);
}

#ifdef __GNUC__
HRT_INLINE void hrt_start_consumer_prog() __attribute__((unused));
#endif

HRT_INLINE void hrt_start_consumer_prog()
{
  _hrt_pass_params_consumer_prog();
  hrt_cell_start_function(CELL, consumer_prog);
}


