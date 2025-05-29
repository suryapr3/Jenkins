#ifndef _vex2rcs_prog_map_h_
#define _vex2rcs_prog_map_h_

#include "./vex2rcs_prog.blob.h"
#include "./vex2rcs_prog.transfer.h"

#ifndef _hrt_dummy_use_blob_vex2rcs_prog
#define _hrt_dummy_use_blob_vex2rcs_prog()
#endif

#define _hrt_cell_load_program_vex2rcs_prog(proc) _hrt_cell_load_program_embedded(proc, vex2rcs_prog)

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vinput
#define HIVE_MEM_vinput ve32_simd0_vmem
#define HIVE_ADDR_vinput 0x0
#define HIVE_SIZE_vinput 384
#else
#error Symbol vinput occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_vex2rcs_prog_vinput ve32_simd0_vmem
#define HIVE_ADDR_vex2rcs_prog_vinput 0x0
#define HIVE_SIZE_vex2rcs_prog_vinput 384

/* function vex2rcs_prog: 80 */

/* function vex2rcs_prog_entry: 0 */
#ifndef HIVE_MULTIPLE_PROGRAMS
#ifdef HIVE_ADDR_vex2rcs_prog_entry
#error Symbol vex2rcs_prog_entry occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#define HIVE_ADDR_vex2rcs_prog_entry 0x0
#endif
#define HIVE_ADDR_vex2rcs_prog_vex2rcs_prog_entry 0x0


#endif /* _vex2rcs_prog_map_h_ */
