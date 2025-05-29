#ifndef _consumer_prog_transfer_h_
#define _consumer_prog_transfer_h_

#define _hrt_dummy_use_blob_consumer_prog()\
    { char *blob = _hrt_blob_consumer_prog.data; blob = blob; }
#define _hrt_transfer_embedded_consumer_prog(code_func, data_func, bss_func, view_table_func, icache_master_func, ...) \
  {\
      code_func(text, 0x0, (0x0), 0x1C0, __VA_ARGS__);\
      bss_func(ve32_bp_dmem, (0x1C0 /* target offset */), (0xC /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_transfer_additional_embedded_consumer_prog(pseudo_op_func, pseudo_data_func, rf_sizes_func, func_ranges_func, ...) \
  {\
      pseudo_op_func((0x0 /* target offset */), (0x0 + 0x1c0 /* blob offset */), (0x12E /* size */), __VA_ARGS__);\
      pseudo_data_func((0x0 /* target offset */), (0x0 + 0x1c0 + 0x12e /* blob offset */), (0xE6 /* size */), __VA_ARGS__);\
      func_ranges_func((0x0 /* target offset */), (0x0 + 0x1c0 + 0x12e + 0xe6 /* blob offset */), (0x10 /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_cell_load_program_done_consumer_prog(cell)\
  {\
      hrt_prog_mem_read(cell, 0);\
  \
  }

  #define _hrt_size_of_consumer_prog ( 0x0 + 0x1c0 + 0x12e + 0xe6 + 0x10 )
  #define _hrt_text_is_p2
  #define _hrt_section_size_consumer_prog_text 0x1C0
  /* properties of section .text: */
  #define _hrt_text_instructions_of_consumer_prog 0x00000007
  #define _hrt_text_instruction_size_of_consumer_prog 0x00000040
  #define _hrt_text_instruction_aligned_size_of_consumer_prog 0x00000040
  #define _hrt_text_target_of_consumer_prog 0x00000000
  #define _hrt_text_source_of_consumer_prog (0x0)
  #define _hrt_text_size_of_consumer_prog 0x000001C0

  /* properties of section .bss.bp_dmem: */
  #define _hrt_bss_bp_dmem_target_of_consumer_prog 0x000001C0
  #define _hrt_bss_bp_dmem_size_of_consumer_prog 0x0000000C

  /* deprecated, compatibility properties of section .bss.bp_dmem: */
  #ifndef _hrt_bss_of_consumer_prog
  #define _hrt_bss_of_consumer_prog
  #define _hrt_bss_target_of_consumer_prog 0x000001C0
  #define _hrt_bss_size_of_consumer_prog 0x0000000C
  #endif /* _hrt_bss_of_consumer_prog */

  /* properties of section .pseudo.ops: */
  #define _hrt_pseudo_op_target_of_consumer_prog 0x00000000
  #define _hrt_pseudo_op_size_of_consumer_prog 0x0000012E

  /* properties of section .pseudo.data: */
  #define _hrt_pseudo_data_target_of_consumer_prog 0x00000000
  #define _hrt_pseudo_data_size_of_consumer_prog 0x000000E6

  /* properties of section .function_ranges: */
  #define _hrt_func_ranges_target_of_consumer_prog 0x00000000
  #define _hrt_func_ranges_size_of_consumer_prog 0x00000408

  /* The CellId and the instruction-length */
  #define _hrt_elf_cell_id_of_consumer_prog           0x00009E4F
  #define _hrt_elf_instruction_bytes_of_consumer_prog 0x00000040

  #define _hrt_icache_instructions_of_consumer_prog 0x00000000
  #define _hrt_icache_instruction_size_of_consumer_prog 0x00000000
  #define _hrt_icache_instruction_aligned_size_of_consumer_prog 0x00000000
  #define _hrt_icache_target_of_consumer_prog 0x00000000
  #define _hrt_icache_source_of_consumer_prog 0x00000000
  #define _hrt_icache_size_of_consumer_prog 0x00000000

  #define _hrt_data_target_of_consumer_prog 0x00000000
  #define _hrt_data_source_of_consumer_prog 0x00000000
  #define _hrt_data_size_of_consumer_prog 0x00000000



  #endif /* _consumer_prog_transfer_h_ */
