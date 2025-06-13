#ifndef _tst_map_h_
#define _tst_map_h_

#include "./tst.blob.h"
#include "./tst.transfer.h"

#ifndef _hrt_dummy_use_blob_tst
#define _hrt_dummy_use_blob_tst()
#endif

#define _hrt_cell_load_program_tst(proc) _hrt_cell_load_program_embedded(proc, tst)

/* function tst: 80 */

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_tst_output
#define HIVE_MEM_tst_output ve32_bp_dmem
#define HIVE_ADDR_tst_output 0x30
#define HIVE_SIZE_tst_output 12
#else
#error Symbol tst_output occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_tst_tst_output ve32_bp_dmem
#define HIVE_ADDR_tst_tst_output 0x30
#define HIVE_SIZE_tst_tst_output 12

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_tst_inputs
#define HIVE_MEM_tst_inputs ve32_bp_dmem
#define HIVE_ADDR_tst_inputs 0x0
#define HIVE_SIZE_tst_inputs 48
#else
#error Symbol tst_inputs occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_tst_tst_inputs ve32_bp_dmem
#define HIVE_ADDR_tst_tst_inputs 0x0
#define HIVE_SIZE_tst_tst_inputs 48

/* function tst_entry: 0 */
#ifndef HIVE_MULTIPLE_PROGRAMS
#ifdef HIVE_ADDR_tst_entry
#error Symbol tst_entry occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#define HIVE_ADDR_tst_entry 0x0
#endif
#define HIVE_ADDR_tst_tst_entry 0x0


#endif /* _tst_map_h_ */
