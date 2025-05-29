#ifndef _consumer_prog_map_h_
#define _consumer_prog_map_h_

#include "./consumer_prog.blob.h"
#include "./consumer_prog.transfer.h"

#ifndef _hrt_dummy_use_blob_consumer_prog
#define _hrt_dummy_use_blob_consumer_prog()
#endif

#define _hrt_cell_load_program_consumer_prog(proc) _hrt_cell_load_program_embedded(proc, consumer_prog)

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_consumer_max_count
#define HIVE_MEM_consumer_max_count ve32_bp_dmem
#define HIVE_ADDR_consumer_max_count 0x1C4
#define HIVE_SIZE_consumer_max_count 4
#else
#error Symbol consumer_max_count occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_consumer_prog_consumer_max_count ve32_bp_dmem
#define HIVE_ADDR_consumer_prog_consumer_max_count 0x1C4
#define HIVE_SIZE_consumer_prog_consumer_max_count 4

/* function consumer_prog_entry: 0 */
#ifndef HIVE_MULTIPLE_PROGRAMS
#ifdef HIVE_ADDR_consumer_prog_entry
#error Symbol consumer_prog_entry occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#define HIVE_ADDR_consumer_prog_entry 0x0
#endif
#define HIVE_ADDR_consumer_prog_consumer_prog_entry 0x0

/* function consumer_prog: 80 */

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_consumer_token_per_request
#define HIVE_MEM_consumer_token_per_request ve32_bp_dmem
#define HIVE_ADDR_consumer_token_per_request 0x1C8
#define HIVE_SIZE_consumer_token_per_request 4
#else
#error Symbol consumer_token_per_request occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_consumer_prog_consumer_token_per_request ve32_bp_dmem
#define HIVE_ADDR_consumer_prog_consumer_token_per_request 0x1C8
#define HIVE_SIZE_consumer_prog_consumer_token_per_request 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_consumer_sm_gate
#define HIVE_MEM_consumer_sm_gate ve32_bp_dmem
#define HIVE_MEM_consumer_sm_gate_ve32_bp_dmem
#define HIVE_ADDR_consumer_sm_gate 0x180
#define HIVE_SIZE_consumer_sm_gate 64
#else
#if !defined (HIVE_MEM_consumer_sm_gate_ve32_bp_dmem) || HIVE_ADDR_consumer_sm_gate != 0x180 || HIVE_SIZE_consumer_sm_gate != 64
#error Symbol consumer_sm_gate occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_consumer_prog_consumer_sm_gate ve32_bp_dmem
#define HIVE_ADDR_consumer_prog_consumer_sm_gate 0x180
#define HIVE_SIZE_consumer_prog_consumer_sm_gate 64

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_count
#define HIVE_MEM_count ve32_bp_dmem
#define HIVE_MEM_count_ve32_bp_dmem
#define HIVE_ADDR_count 0x40
#define HIVE_SIZE_count 4
#else
#if !defined (HIVE_MEM_count_ve32_bp_dmem) || HIVE_ADDR_count != 0x40 || HIVE_SIZE_count != 4
#error Symbol count occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_consumer_prog_count ve32_bp_dmem
#define HIVE_ADDR_consumer_prog_count 0x40
#define HIVE_SIZE_consumer_prog_count 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_gTimeStampDataCopy
#define HIVE_MEM_gTimeStampDataCopy ve32_simd0_vmem
#define HIVE_MEM_gTimeStampDataCopy_ve32_simd0_vmem
#define HIVE_ADDR_gTimeStampDataCopy 0x100
#define HIVE_SIZE_gTimeStampDataCopy 1280
#else
#if !defined (HIVE_MEM_gTimeStampDataCopy_ve32_simd0_vmem) || HIVE_ADDR_gTimeStampDataCopy != 0x100 || HIVE_SIZE_gTimeStampDataCopy != 1280
#error Symbol gTimeStampDataCopy occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_consumer_prog_gTimeStampDataCopy ve32_simd0_vmem
#define HIVE_ADDR_consumer_prog_gTimeStampDataCopy 0x100
#define HIVE_SIZE_consumer_prog_gTimeStampDataCopy 1280

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_gTimeStampData
#define HIVE_MEM_gTimeStampData ve32_simd0_vmem
#define HIVE_MEM_gTimeStampData_ve32_simd0_vmem
#define HIVE_ADDR_gTimeStampData 0x0
#define HIVE_SIZE_gTimeStampData 128
#else
#if !defined (HIVE_MEM_gTimeStampData_ve32_simd0_vmem) || HIVE_ADDR_gTimeStampData != 0x0 || HIVE_SIZE_gTimeStampData != 128
#error Symbol gTimeStampData occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_consumer_prog_gTimeStampData ve32_simd0_vmem
#define HIVE_ADDR_consumer_prog_gTimeStampData 0x0
#define HIVE_SIZE_consumer_prog_gTimeStampData 128

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_buffer_ra
#define HIVE_MEM_buffer_ra ve32_bp_dmem
#define HIVE_ADDR_buffer_ra 0x1C0
#define HIVE_SIZE_buffer_ra 4
#else
#error Symbol buffer_ra occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_consumer_prog_buffer_ra ve32_bp_dmem
#define HIVE_ADDR_consumer_prog_buffer_ra 0x1C0
#define HIVE_SIZE_consumer_prog_buffer_ra 4


#endif /* _consumer_prog_map_h_ */
