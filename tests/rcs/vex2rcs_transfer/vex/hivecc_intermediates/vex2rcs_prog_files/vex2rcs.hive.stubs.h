
#define _hrt_pass_params_vex2rcs_prog()
#define _hrt_read_result_vex2rcs_prog() 0

/* vex2rcs_prog: check address known, default stub, hrt_start_vex2rcs_prog, hrt_end_vex2rcs_prog */

#ifndef HIVE_ADDR_vex2rcs_prog_entry
#error -----------------------------------------------------------------------------------------
#error Address for function vex2rcs_prog not defined, please include mapfile before including stubs file
#error -----------------------------------------------------------------------------------------
#endif

#define vex2rcs_prog() hrt_run_vex2rcs_prog()

#ifdef __GNUC__
HRT_INLINE void hrt_run_vex2rcs_prog() __attribute__((unused));
#endif

HRT_INLINE void hrt_run_vex2rcs_prog()
{
  _hrt_pass_params_vex2rcs_prog();
  hrt_cell_run_function(CELL, vex2rcs_prog);
}

#ifdef __GNUC__
HRT_INLINE void hrt_start_vex2rcs_prog() __attribute__((unused));
#endif

HRT_INLINE void hrt_start_vex2rcs_prog()
{
  _hrt_pass_params_vex2rcs_prog();
  hrt_cell_start_function(CELL, vex2rcs_prog);
}


