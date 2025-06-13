#ifndef _tst_transfer_h_
#define _tst_transfer_h_

#define _hrt_dummy_use_blob_tst()\
    { char *blob = _hrt_blob_tst.data; blob = blob; }
#define _hrt_transfer_embedded_tst(code_func, data_func, bss_func, view_table_func, icache_master_func, ...) \
  {\
      code_func(text, 0x0, (0x0), 0x440, __VA_ARGS__);\
      bss_func(ve32_bp_dmem, (0x0 /* target offset */), (0x3C /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_transfer_additional_embedded_tst(pseudo_op_func, pseudo_data_func, rf_sizes_func, func_ranges_func, ...) \
  {\
      pseudo_op_func((0x0 /* target offset */), (0x0 + 0x440 /* blob offset */), (0x20 /* size */), __VA_ARGS__);\
      pseudo_data_func((0x0 /* target offset */), (0x0 + 0x440 + 0x20 /* blob offset */), (0x8 /* size */), __VA_ARGS__);\
      func_ranges_func((0x0 /* target offset */), (0x0 + 0x440 + 0x20 + 0x8 /* blob offset */), (0x10 /* size */), __VA_ARGS__);\
  \
  }

#define _hrt_cell_load_program_done_tst(cell)\
  {\
      hrt_prog_mem_read(cell, 0);\
  \
  }

  #define _hrt_size_of_tst ( 0x0 + 0x440 + 0x20 + 0x8 + 0x10 )
  #define _hrt_text_is_p2
  #define _hrt_section_size_tst_text 0x440
  /* properties of section .text: */
  #define _hrt_text_instructions_of_tst 0x00000011
  #define _hrt_text_instruction_size_of_tst 0x00000040
  #define _hrt_text_instruction_aligned_size_of_tst 0x00000040
  #define _hrt_text_target_of_tst 0x00000000
  #define _hrt_text_source_of_tst (0x0)
  #define _hrt_text_size_of_tst 0x00000440

  /* properties of section .bss.bp_dmem: */
  #define _hrt_bss_bp_dmem_target_of_tst 0x00000000
  #define _hrt_bss_bp_dmem_size_of_tst 0x0000003C

  /* deprecated, compatibility properties of section .bss.bp_dmem: */
  #ifndef _hrt_bss_of_tst
  #define _hrt_bss_of_tst
  #define _hrt_bss_target_of_tst 0x00000000
  #define _hrt_bss_size_of_tst 0x0000003C
  #endif /* _hrt_bss_of_tst */

  /* properties of section .pseudo.ops: */
  #define _hrt_pseudo_op_target_of_tst 0x00000000
  #define _hrt_pseudo_op_size_of_tst 0x00000020

  /* properties of section .pseudo.data: */
  #define _hrt_pseudo_data_target_of_tst 0x00000000
  #define _hrt_pseudo_data_size_of_tst 0x00000008

  /* properties of section .function_ranges: */
  #define _hrt_func_ranges_target_of_tst 0x00000000
  #define _hrt_func_ranges_size_of_tst 0x00000318

  /* The CellId and the instruction-length */
  #define _hrt_elf_cell_id_of_tst           0x00009E4F
  #define _hrt_elf_instruction_bytes_of_tst 0x00000040

  #define _hrt_icache_instructions_of_tst 0x00000000
  #define _hrt_icache_instruction_size_of_tst 0x00000000
  #define _hrt_icache_instruction_aligned_size_of_tst 0x00000000
  #define _hrt_icache_target_of_tst 0x00000000
  #define _hrt_icache_source_of_tst 0x00000000
  #define _hrt_icache_size_of_tst 0x00000000

  #define _hrt_data_target_of_tst 0x00000000
  #define _hrt_data_source_of_tst 0x00000000
  #define _hrt_data_size_of_tst 0x00000000



  #endif /* _tst_transfer_h_ */
