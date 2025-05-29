#ifndef _jesd_rx_map_h_
#define _jesd_rx_map_h_


#ifndef _hrt_dummy_use_blob_jesd_rx
#define _hrt_dummy_use_blob_jesd_rx()
#endif

#define _hrt_cell_load_program_jesd_rx(proc) _hrt_cell_load_program_from_elf_file(proc, "jesd_rx")
#define _hrt_cell_load_program_done_jesd_rx(proc) _hrt_cell_load_program_done_ve32(proc)

/* function jesd_rx_entry: 0 */
#ifndef HIVE_MULTIPLE_PROGRAMS
#ifdef HIVE_ADDR_jesd_rx_entry
#error Symbol jesd_rx_entry occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#define HIVE_ADDR_jesd_rx_entry 0x0
#endif
#define HIVE_ADDR_jesd_rx_jesd_rx_entry 0x0

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_timer_debug
#define HIVE_MEM_g_timer_debug ve32_bp_dmem
#define HIVE_MEM_g_timer_debug_ve32_bp_dmem
#define HIVE_ADDR_g_timer_debug 0x28
#define HIVE_SIZE_g_timer_debug 4
#else
#if !defined (HIVE_MEM_g_timer_debug_ve32_bp_dmem) || HIVE_ADDR_g_timer_debug != 0x28 || HIVE_SIZE_g_timer_debug != 4
#error Symbol g_timer_debug occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_g_timer_debug ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_g_timer_debug 0x28
#define HIVE_SIZE_jesd_rx_g_timer_debug 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_0
#define HIVE_MEM_vbuffer_0 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_0_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_0 0x0
#define HIVE_SIZE_vbuffer_0 8192
#else
#if !defined (HIVE_MEM_vbuffer_0_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_0 != 0x0 || HIVE_SIZE_vbuffer_0 != 8192
#error Symbol vbuffer_0 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_vbuffer_0 ve32_simd0_vmem
#define HIVE_ADDR_jesd_rx_vbuffer_0 0x0
#define HIVE_SIZE_jesd_rx_vbuffer_0 8192

/* function jesd_rx: A */

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_consumer_sm_gate
#define HIVE_MEM_consumer_sm_gate ve32_bp_dmem
#define HIVE_ADDR_consumer_sm_gate 0x80
#define HIVE_SIZE_consumer_sm_gate 64
#else
#error Symbol consumer_sm_gate occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#endif
#define HIVE_MEM_jesd_rx_consumer_sm_gate ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_consumer_sm_gate 0x80
#define HIVE_SIZE_jesd_rx_consumer_sm_gate 64

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_tbs_in_blk
#define HIVE_MEM_g_tbs_in_blk ve32_bp_dmem
#define HIVE_MEM_g_tbs_in_blk_ve32_bp_dmem
#define HIVE_ADDR_g_tbs_in_blk 0x14
#define HIVE_SIZE_g_tbs_in_blk 4
#else
#if !defined (HIVE_MEM_g_tbs_in_blk_ve32_bp_dmem) || HIVE_ADDR_g_tbs_in_blk != 0x14 || HIVE_SIZE_g_tbs_in_blk != 4
#error Symbol g_tbs_in_blk occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_g_tbs_in_blk ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_g_tbs_in_blk 0x14
#define HIVE_SIZE_jesd_rx_g_tbs_in_blk 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_host_indicator
#define HIVE_MEM_g_host_indicator ve32_bp_dmem
#define HIVE_MEM_g_host_indicator_ve32_bp_dmem
#define HIVE_ADDR_g_host_indicator 0x20
#define HIVE_SIZE_g_host_indicator 4
#else
#if !defined (HIVE_MEM_g_host_indicator_ve32_bp_dmem) || HIVE_ADDR_g_host_indicator != 0x20 || HIVE_SIZE_g_host_indicator != 4
#error Symbol g_host_indicator occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_g_host_indicator ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_g_host_indicator 0x20
#define HIVE_SIZE_jesd_rx_g_host_indicator 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_vex_exit
#define HIVE_MEM_g_vex_exit ve32_bp_dmem
#define HIVE_MEM_g_vex_exit_ve32_bp_dmem
#define HIVE_ADDR_g_vex_exit 0x24
#define HIVE_SIZE_g_vex_exit 4
#else
#if !defined (HIVE_MEM_g_vex_exit_ve32_bp_dmem) || HIVE_ADDR_g_vex_exit != 0x24 || HIVE_SIZE_g_vex_exit != 4
#error Symbol g_vex_exit occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_g_vex_exit ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_g_vex_exit 0x24
#define HIVE_SIZE_jesd_rx_g_vex_exit 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_7
#define HIVE_MEM_vbuffer_7 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_7_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_7 0xC000
#define HIVE_SIZE_vbuffer_7 16384
#else
#if !defined (HIVE_MEM_vbuffer_7_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_7 != 0xC000 || HIVE_SIZE_vbuffer_7 != 16384
#error Symbol vbuffer_7 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_vbuffer_7 ve32_simd0_vmem
#define HIVE_ADDR_jesd_rx_vbuffer_7 0xC000
#define HIVE_SIZE_jesd_rx_vbuffer_7 16384

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_num_vecs_in
#define HIVE_MEM_g_num_vecs_in ve32_bp_dmem
#define HIVE_MEM_g_num_vecs_in_ve32_bp_dmem
#define HIVE_ADDR_g_num_vecs_in 0xC
#define HIVE_SIZE_g_num_vecs_in 4
#else
#if !defined (HIVE_MEM_g_num_vecs_in_ve32_bp_dmem) || HIVE_ADDR_g_num_vecs_in != 0xC || HIVE_SIZE_g_num_vecs_in != 4
#error Symbol g_num_vecs_in occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_g_num_vecs_in ve32_bp_dmem
#define HIVE_ADDR_jesd_rx_g_num_vecs_in 0xC
#define HIVE_SIZE_jesd_rx_g_num_vecs_in 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_out
#define HIVE_MEM_vbuffer_out ve32_simd0_vmem
#define HIVE_MEM_vbuffer_out_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_out 0x4000
#define HIVE_SIZE_vbuffer_out 32768
#else
#if !defined (HIVE_MEM_vbuffer_out_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_out != 0x4000 || HIVE_SIZE_vbuffer_out != 32768
#error Symbol vbuffer_out occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_rx_vbuffer_out ve32_simd0_vmem
#define HIVE_ADDR_jesd_rx_vbuffer_out 0x4000
#define HIVE_SIZE_jesd_rx_vbuffer_out 32768


#endif /* _jesd_rx_map_h_ */
