#ifndef _vex2rcs_prog_transfer_h_
#define _vex2rcs_prog_transfer_h_

#define _hrt_dummy_use_blob_vex2rcs_prog()\
    { char *blob = _hrt_blob_vex2rcs_prog.data; blob = blob; }
#define _hrt_transfer_embedded_vex2rcs_prog(code_func, data_func, bss_func, view_table_func, icache_master_func, ...) \
  {\
      code_func(text, 0x0, (0x0), 0x100, __VA_ARGS__);\
      bss_func(ve32_simd0_vmem, (0x0 /* target offset */), (0x180 /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_transfer_additional_embedded_vex2rcs_prog(pseudo_op_func, pseudo_data_func, rf_sizes_func, func_ranges_func, ...) \
  {\
      pseudo_op_func((0x0 /* target offset */), (0x0 + 0x100 /* blob offset */), (0x2C /* size */), __VA_ARGS__);\
      pseudo_data_func((0x0 /* target offset */), (0x0 + 0x100 + 0x2c /* blob offset */), (0x46 /* size */), __VA_ARGS__);\
      func_ranges_func((0x0 /* target offset */), (0x0 + 0x100 + 0x2c + 0x46 /* blob offset */), (0x10 /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_cell_load_program_done_vex2rcs_prog(cell)\
  {\
      hrt_prog_mem_read(cell, 0);\
  \
  }

  #define _hrt_size_of_vex2rcs_prog ( 0x0 + 0x100 + 0x2c + 0x46 + 0x10 )
  #define _hrt_text_is_p2
  #define _hrt_section_size_vex2rcs_prog_text 0x100
  /* properties of section .text: */
  #define _hrt_text_instructions_of_vex2rcs_prog 0x00000004
  #define _hrt_text_instruction_size_of_vex2rcs_prog 0x00000040
  #define _hrt_text_instruction_aligned_size_of_vex2rcs_prog 0x00000040
  #define _hrt_text_target_of_vex2rcs_prog 0x00000000
  #define _hrt_text_source_of_vex2rcs_prog (0x0)
  #define _hrt_text_size_of_vex2rcs_prog 0x00000100

  /* properties of section .bss.simd0_vmem: */
  #define _hrt_bss_simd0_vmem_target_of_vex2rcs_prog 0x00000000
  #define _hrt_bss_simd0_vmem_size_of_vex2rcs_prog 0x00000180

  /* deprecated, compatibility properties of section .bss.simd0_vmem: */
  #ifndef _hrt_bss_of_vex2rcs_prog
  #define _hrt_bss_of_vex2rcs_prog
  #define _hrt_bss_target_of_vex2rcs_prog 0x00000000
  #define _hrt_bss_size_of_vex2rcs_prog 0x00000180
  #endif /* _hrt_bss_of_vex2rcs_prog */

  /* properties of section .pseudo.ops: */
  #define _hrt_pseudo_op_target_of_vex2rcs_prog 0x00000000
  #define _hrt_pseudo_op_size_of_vex2rcs_prog 0x0000002C

  /* properties of section .pseudo.data: */
  #define _hrt_pseudo_data_target_of_vex2rcs_prog 0x00000000
  #define _hrt_pseudo_data_size_of_vex2rcs_prog 0x00000046

  /* properties of section .function_ranges: */
  #define _hrt_func_ranges_target_of_vex2rcs_prog 0x00000000
  #define _hrt_func_ranges_size_of_vex2rcs_prog 0x00000270

  /* The CellId and the instruction-length */
  #define _hrt_elf_cell_id_of_vex2rcs_prog           0x00009E4F
  #define _hrt_elf_instruction_bytes_of_vex2rcs_prog 0x00000040

  #define _hrt_icache_instructions_of_vex2rcs_prog 0x00000000
  #define _hrt_icache_instruction_size_of_vex2rcs_prog 0x00000000
  #define _hrt_icache_instruction_aligned_size_of_vex2rcs_prog 0x00000000
  #define _hrt_icache_target_of_vex2rcs_prog 0x00000000
  #define _hrt_icache_source_of_vex2rcs_prog 0x00000000
  #define _hrt_icache_size_of_vex2rcs_prog 0x00000000

  #define _hrt_data_target_of_vex2rcs_prog 0x00000000
  #define _hrt_data_source_of_vex2rcs_prog 0x00000000
  #define _hrt_data_size_of_vex2rcs_prog 0x00000000



  #endif /* _vex2rcs_prog_transfer_h_ */
