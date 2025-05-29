#ifndef _jesd_tx_map_h_
#define _jesd_tx_map_h_


#ifndef _hrt_dummy_use_blob_jesd_tx
#define _hrt_dummy_use_blob_jesd_tx()
#endif

#define _hrt_cell_load_program_jesd_tx(proc) _hrt_cell_load_program_from_elf_file(proc, "jesd_tx")
#define _hrt_cell_load_program_done_jesd_tx(proc) _hrt_cell_load_program_done_ve32(proc)

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_6
#define HIVE_MEM_vbuffer_6 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_6_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_6 0xC000
#define HIVE_SIZE_vbuffer_6 8192
#else
#if !defined (HIVE_MEM_vbuffer_6_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_6 != 0xC000 || HIVE_SIZE_vbuffer_6 != 8192
#error Symbol vbuffer_6 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_6 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_6 0xC000
#define HIVE_SIZE_jesd_tx_vbuffer_6 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_debug
#define HIVE_MEM_g_debug ve32_bp_dmem
#define HIVE_MEM_g_debug_ve32_bp_dmem
#define HIVE_ADDR_g_debug 0x2C
#define HIVE_SIZE_g_debug 4
#else
#if !defined (HIVE_MEM_g_debug_ve32_bp_dmem) || HIVE_ADDR_g_debug != 0x2C || HIVE_SIZE_g_debug != 4
#error Symbol g_debug occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_debug ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_debug 0x2C
#define HIVE_SIZE_jesd_tx_g_debug 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer2_base
#define HIVE_MEM_g_dest_buffer2_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer2_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer2_base 0x8
#define HIVE_SIZE_g_dest_buffer2_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer2_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer2_base != 0x8 || HIVE_SIZE_g_dest_buffer2_base != 4
#error Symbol g_dest_buffer2_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer2_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer2_base 0x8
#define HIVE_SIZE_jesd_tx_g_dest_buffer2_base 4

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
#define HIVE_MEM_jesd_tx_g_timer_debug ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_timer_debug 0x28
#define HIVE_SIZE_jesd_tx_g_timer_debug 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer3_base
#define HIVE_MEM_g_dest_buffer3_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer3_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer3_base 0xC
#define HIVE_SIZE_g_dest_buffer3_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer3_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer3_base != 0xC || HIVE_SIZE_g_dest_buffer3_base != 4
#error Symbol g_dest_buffer3_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer3_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer3_base 0xC
#define HIVE_SIZE_jesd_tx_g_dest_buffer3_base 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_timeout_cycles
#define HIVE_MEM_g_timeout_cycles ve32_bp_dmem
#define HIVE_MEM_g_timeout_cycles_ve32_bp_dmem
#define HIVE_ADDR_g_timeout_cycles 0x30
#define HIVE_SIZE_g_timeout_cycles 4
#else
#if !defined (HIVE_MEM_g_timeout_cycles_ve32_bp_dmem) || HIVE_ADDR_g_timeout_cycles != 0x30 || HIVE_SIZE_g_timeout_cycles != 4
#error Symbol g_timeout_cycles occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_timeout_cycles ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_timeout_cycles 0x30
#define HIVE_SIZE_jesd_tx_g_timeout_cycles 4

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
#define HIVE_MEM_jesd_tx_vbuffer_0 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_0 0x0
#define HIVE_SIZE_jesd_tx_vbuffer_0 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer7_base
#define HIVE_MEM_g_dest_buffer7_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer7_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer7_base 0x1C
#define HIVE_SIZE_g_dest_buffer7_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer7_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer7_base != 0x1C || HIVE_SIZE_g_dest_buffer7_base != 4
#error Symbol g_dest_buffer7_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer7_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer7_base 0x1C
#define HIVE_SIZE_jesd_tx_g_dest_buffer7_base 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_5
#define HIVE_MEM_vbuffer_5 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_5_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_5 0xA000
#define HIVE_SIZE_vbuffer_5 8192
#else
#if !defined (HIVE_MEM_vbuffer_5_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_5 != 0xA000 || HIVE_SIZE_vbuffer_5 != 8192
#error Symbol vbuffer_5 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_5 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_5 0xA000
#define HIVE_SIZE_jesd_tx_vbuffer_5 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer0_base
#define HIVE_MEM_g_dest_buffer0_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer0_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer0_base 0x0
#define HIVE_SIZE_g_dest_buffer0_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer0_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer0_base != 0x0 || HIVE_SIZE_g_dest_buffer0_base != 4
#error Symbol g_dest_buffer0_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer0_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer0_base 0x0
#define HIVE_SIZE_jesd_tx_g_dest_buffer0_base 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer1_base
#define HIVE_MEM_g_dest_buffer1_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer1_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer1_base 0x4
#define HIVE_SIZE_g_dest_buffer1_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer1_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer1_base != 0x4 || HIVE_SIZE_g_dest_buffer1_base != 4
#error Symbol g_dest_buffer1_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer1_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer1_base 0x4
#define HIVE_SIZE_jesd_tx_g_dest_buffer1_base 4

/* function jesd_tx: 8 */

/* function jesd_tx_entry: 0 */
#ifndef HIVE_MULTIPLE_PROGRAMS
#ifdef HIVE_ADDR_jesd_tx_entry
#error Symbol jesd_tx_entry occurs in multiple mapfiles, please rename or split host code into separate modules
#endif
#define HIVE_ADDR_jesd_tx_entry 0x0
#endif
#define HIVE_ADDR_jesd_tx_jesd_tx_entry 0x0

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_4
#define HIVE_MEM_vbuffer_4 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_4_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_4 0x8000
#define HIVE_SIZE_vbuffer_4 8192
#else
#if !defined (HIVE_MEM_vbuffer_4_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_4 != 0x8000 || HIVE_SIZE_vbuffer_4 != 8192
#error Symbol vbuffer_4 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_4 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_4 0x8000
#define HIVE_SIZE_jesd_tx_vbuffer_4 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer5_base
#define HIVE_MEM_g_dest_buffer5_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer5_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer5_base 0x14
#define HIVE_SIZE_g_dest_buffer5_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer5_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer5_base != 0x14 || HIVE_SIZE_g_dest_buffer5_base != 4
#error Symbol g_dest_buffer5_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer5_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer5_base 0x14
#define HIVE_SIZE_jesd_tx_g_dest_buffer5_base 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer4_base
#define HIVE_MEM_g_dest_buffer4_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer4_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer4_base 0x10
#define HIVE_SIZE_g_dest_buffer4_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer4_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer4_base != 0x10 || HIVE_SIZE_g_dest_buffer4_base != 4
#error Symbol g_dest_buffer4_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer4_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer4_base 0x10
#define HIVE_SIZE_jesd_tx_g_dest_buffer4_base 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_3
#define HIVE_MEM_vbuffer_3 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_3_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_3 0x6000
#define HIVE_SIZE_vbuffer_3 8192
#else
#if !defined (HIVE_MEM_vbuffer_3_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_3 != 0x6000 || HIVE_SIZE_vbuffer_3 != 8192
#error Symbol vbuffer_3 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_3 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_3 0x6000
#define HIVE_SIZE_jesd_tx_vbuffer_3 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_1
#define HIVE_MEM_vbuffer_1 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_1_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_1 0x2000
#define HIVE_SIZE_vbuffer_1 8192
#else
#if !defined (HIVE_MEM_vbuffer_1_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_1 != 0x2000 || HIVE_SIZE_vbuffer_1 != 8192
#error Symbol vbuffer_1 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_1 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_1 0x2000
#define HIVE_SIZE_jesd_tx_vbuffer_1 8192

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
#define HIVE_MEM_jesd_tx_g_host_indicator ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_host_indicator 0x20
#define HIVE_SIZE_jesd_tx_g_host_indicator 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_2
#define HIVE_MEM_vbuffer_2 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_2_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_2 0x4000
#define HIVE_SIZE_vbuffer_2 8192
#else
#if !defined (HIVE_MEM_vbuffer_2_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_2 != 0x4000 || HIVE_SIZE_vbuffer_2 != 8192
#error Symbol vbuffer_2 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_2 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_2 0x4000
#define HIVE_SIZE_jesd_tx_vbuffer_2 8192

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
#define HIVE_MEM_jesd_tx_g_vex_exit ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_vex_exit 0x24
#define HIVE_SIZE_jesd_tx_g_vex_exit 4

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_vbuffer_7
#define HIVE_MEM_vbuffer_7 ve32_simd0_vmem
#define HIVE_MEM_vbuffer_7_ve32_simd0_vmem
#define HIVE_ADDR_vbuffer_7 0xE000
#define HIVE_SIZE_vbuffer_7 8192
#else
#if !defined (HIVE_MEM_vbuffer_7_ve32_simd0_vmem) || HIVE_ADDR_vbuffer_7 != 0xE000 || HIVE_SIZE_vbuffer_7 != 8192
#error Symbol vbuffer_7 occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_vbuffer_7 ve32_simd0_vmem
#define HIVE_ADDR_jesd_tx_vbuffer_7 0xE000
#define HIVE_SIZE_jesd_tx_vbuffer_7 8192

#ifndef HIVE_MULTIPLE_PROGRAMS
#ifndef HIVE_MEM_g_dest_buffer6_base
#define HIVE_MEM_g_dest_buffer6_base ve32_bp_dmem
#define HIVE_MEM_g_dest_buffer6_base_ve32_bp_dmem
#define HIVE_ADDR_g_dest_buffer6_base 0x18
#define HIVE_SIZE_g_dest_buffer6_base 4
#else
#if !defined (HIVE_MEM_g_dest_buffer6_base_ve32_bp_dmem) || HIVE_ADDR_g_dest_buffer6_base != 0x18 || HIVE_SIZE_g_dest_buffer6_base != 4
#error Symbol g_dest_buffer6_base occurs in multiple mapfiles differently, please rename or split host code into separate modules
#endif
#endif
#endif
#define HIVE_MEM_jesd_tx_g_dest_buffer6_base ve32_bp_dmem
#define HIVE_ADDR_jesd_tx_g_dest_buffer6_base 0x18
#define HIVE_SIZE_jesd_tx_g_dest_buffer6_base 4


#endif /* _jesd_tx_map_h_ */
