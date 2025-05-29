/* This linker script generated from xt-genldscripts.tpp for LSP scripts/lsp/hw/cal */
/* Linker Script for default link */
MEMORY
{
  srom0_seg :                         	org = 0x00000000, len = 0x20000
  sram0_0_seg :                       	org = 0x00200000, len = 0x4000
  sram0_1_seg :                       	org = 0x00204000, len = 0xC000
  sram0_2_seg :                       	org = 0x00210000, len = 0x8000
  sram0_3_seg :                       	org = 0x00218000, len = 0x8000
  sram0_4_seg :                       	org = 0x00220000, len = 0x8000
  sram0_5_seg :                       	org = 0x00228000, len = 0x8000
  sram0_6_seg :                       	org = 0x00230000, len = 0xFFEB
  sram0_7_seg :                       	org = 0x0023FFEC, len = 0x4
  sram0_8_seg :                       	org = 0x0023FFF0, len = 0x4
  sram0_9_seg :                       	org = 0x0023FFF4, len = 0x4
  sram0_10_seg :                      	org = 0x0023FFF8, len = 0x4
  sram0_11_seg :                      	org = 0x0023FFFC, len = 0x4
  iram0_0_seg :                       	org = 0x10000000, len = 0x300
  iram0_1_seg :                       	org = 0x10000300, len = 0x30
  iram0_2_seg :                       	org = 0x10000330, len = 0x180
  iram0_4_seg :                       	org = 0x10000800, len = 0x178
  iram0_5_seg :                       	org = 0x10000978, len = 0x8
  iram0_6_seg :                       	org = 0x10000980, len = 0x38
  iram0_7_seg :                       	org = 0x100009B8, len = 0x8
  iram0_8_seg :                       	org = 0x100009C0, len = 0x38
  iram0_9_seg :                       	org = 0x100009F8, len = 0x8
  iram0_10_seg :                      	org = 0x10000A00, len = 0x38
  iram0_11_seg :                      	org = 0x10000A38, len = 0x8
  iram0_12_seg :                      	org = 0x10000A40, len = 0x38
  iram0_13_seg :                      	org = 0x10000A78, len = 0x8
  iram0_14_seg :                      	org = 0x10000A80, len = 0x38
  iram0_15_seg :                      	org = 0x10000AB8, len = 0x8
  iram0_16_seg :                      	org = 0x10000AC0, len = 0x38
  iram0_17_seg :                      	org = 0x10000AF8, len = 0x8
  iram0_18_seg :                      	org = 0x10000B00, len = 0x38
  iram0_19_seg :                      	org = 0x10000B38, len = 0x48
  iram0_20_seg :                      	org = 0x10000B80, len = 0x40
  iram0_21_seg :                      	org = 0x10000BC0, len = 0x3F440
  dram0_0_seg :                       	org = 0x10040000, len = 0x4000
  dram0_1_seg :                       	org = 0x10044000, len = 0x9000
  dram0_4_seg :                       	org = 0x10050000, len = 0x30000
}

PHDRS
{
  srom0_phdr PT_LOAD;
  sram0_0_phdr PT_LOAD;
  sram0_1_phdr PT_LOAD;
  sram0_2_phdr PT_LOAD;
  sram0_3_phdr PT_LOAD;
  sram0_4_phdr PT_LOAD;
  sram0_5_phdr PT_LOAD;
  sram0_6_phdr PT_LOAD;
  sram0_7_phdr PT_LOAD;
  sram0_8_phdr PT_LOAD;
  sram0_9_phdr PT_LOAD;
  sram0_10_phdr PT_LOAD;
  sram0_11_phdr PT_LOAD;
  iram0_0_phdr PT_LOAD;
  iram0_1_phdr PT_LOAD;
  iram0_2_phdr PT_LOAD;
  iram0_3_phdr PT_LOAD;
  iram0_4_phdr PT_LOAD;
  iram0_5_phdr PT_LOAD;
  iram0_6_phdr PT_LOAD;
  iram0_7_phdr PT_LOAD;
  iram0_8_phdr PT_LOAD;
  iram0_9_phdr PT_LOAD;
  iram0_10_phdr PT_LOAD;
  iram0_11_phdr PT_LOAD;
  iram0_12_phdr PT_LOAD;
  iram0_13_phdr PT_LOAD;
  iram0_14_phdr PT_LOAD;
  iram0_15_phdr PT_LOAD;
  iram0_16_phdr PT_LOAD;
  iram0_17_phdr PT_LOAD;
  iram0_18_phdr PT_LOAD;
  iram0_19_phdr PT_LOAD;
  iram0_20_phdr PT_LOAD;
  iram0_21_phdr PT_LOAD;
  dram0_0_phdr PT_LOAD;
  dram0_1_phdr PT_LOAD;
  dram0_1_bss_phdr PT_LOAD;
  dram0_2_phdr PT_LOAD;
  dram0_3_phdr PT_LOAD;
  dram0_4_phdr PT_LOAD;
}


/*  Default entry point:  */
ENTRY(_ResetVector)


/*  Memory boundary addresses:  */
_memmap_mem_srom_start = 0x0;
_memmap_mem_srom_end   = 0x20000;
_memmap_mem_iram0_start = 0x10000000;
_memmap_mem_iram0_end   = 0x10040000;
_memmap_mem_dram0_start = 0x10040000;
_memmap_mem_dram0_end   = 0x10080000;
_memmap_mem_sram_start = 0x200000;
_memmap_mem_sram_end   = 0x240000;

/*  Memory segment boundary addresses:  */
_memmap_seg_srom0_start = 0x0;
_memmap_seg_srom0_max   = 0x20000;
_memmap_seg_sram0_0_start = 0x200000;
_memmap_seg_sram0_0_max   = 0x204000;
_memmap_seg_sram0_1_start = 0x204000;
_memmap_seg_sram0_1_max   = 0x210000;
_memmap_seg_sram0_2_start = 0x210000;
_memmap_seg_sram0_2_max   = 0x218000;
_memmap_seg_sram0_3_start = 0x218000;
_memmap_seg_sram0_3_max   = 0x220000;
_memmap_seg_sram0_4_start = 0x220000;
_memmap_seg_sram0_4_max   = 0x228000;
_memmap_seg_sram0_5_start = 0x228000;
_memmap_seg_sram0_5_max   = 0x230000;
_memmap_seg_sram0_6_start = 0x230000;
_memmap_seg_sram0_6_max   = 0x23ffeb;
_memmap_seg_sram0_7_start = 0x23ffec;
_memmap_seg_sram0_7_max   = 0x23fff0;
_memmap_seg_sram0_8_start = 0x23fff0;
_memmap_seg_sram0_8_max   = 0x23fff4;
_memmap_seg_sram0_9_start = 0x23fff4;
_memmap_seg_sram0_9_max   = 0x23fff8;
_memmap_seg_sram0_10_start = 0x23fff8;
_memmap_seg_sram0_10_max   = 0x23fffc;
_memmap_seg_sram0_11_start = 0x23fffc;
_memmap_seg_sram0_11_max   = 0x240000;
_memmap_seg_iram0_0_start = 0x10000000;
_memmap_seg_iram0_0_max   = 0x10000300;
_memmap_seg_iram0_1_start = 0x10000300;
_memmap_seg_iram0_1_max   = 0x10000330;
_memmap_seg_iram0_2_start = 0x10000330;
_memmap_seg_iram0_2_max   = 0x100004b0;
_memmap_seg_iram0_4_start = 0x10000800;
_memmap_seg_iram0_4_max   = 0x10000978;
_memmap_seg_iram0_5_start = 0x10000978;
_memmap_seg_iram0_5_max   = 0x10000980;
_memmap_seg_iram0_6_start = 0x10000980;
_memmap_seg_iram0_6_max   = 0x100009b8;
_memmap_seg_iram0_7_start = 0x100009b8;
_memmap_seg_iram0_7_max   = 0x100009c0;
_memmap_seg_iram0_8_start = 0x100009c0;
_memmap_seg_iram0_8_max   = 0x100009f8;
_memmap_seg_iram0_9_start = 0x100009f8;
_memmap_seg_iram0_9_max   = 0x10000a00;
_memmap_seg_iram0_10_start = 0x10000a00;
_memmap_seg_iram0_10_max   = 0x10000a38;
_memmap_seg_iram0_11_start = 0x10000a38;
_memmap_seg_iram0_11_max   = 0x10000a40;
_memmap_seg_iram0_12_start = 0x10000a40;
_memmap_seg_iram0_12_max   = 0x10000a78;
_memmap_seg_iram0_13_start = 0x10000a78;
_memmap_seg_iram0_13_max   = 0x10000a80;
_memmap_seg_iram0_14_start = 0x10000a80;
_memmap_seg_iram0_14_max   = 0x10000ab8;
_memmap_seg_iram0_15_start = 0x10000ab8;
_memmap_seg_iram0_15_max   = 0x10000ac0;
_memmap_seg_iram0_16_start = 0x10000ac0;
_memmap_seg_iram0_16_max   = 0x10000af8;
_memmap_seg_iram0_17_start = 0x10000af8;
_memmap_seg_iram0_17_max   = 0x10000b00;
_memmap_seg_iram0_18_start = 0x10000b00;
_memmap_seg_iram0_18_max   = 0x10000b38;
_memmap_seg_iram0_19_start = 0x10000b38;
_memmap_seg_iram0_19_max   = 0x10000b80;
_memmap_seg_iram0_20_start = 0x10000b80;
_memmap_seg_iram0_20_max   = 0x10000bc0;
_memmap_seg_iram0_21_start = 0x10000bc0;
_memmap_seg_iram0_21_max   = 0x10040000;
_memmap_seg_dram0_0_start = 0x10040000;
_memmap_seg_dram0_0_max   = 0x10044000;
_memmap_seg_dram0_1_start = 0x10044000;
_memmap_seg_dram0_1_max   = 0x1004d000;
_memmap_seg_dram0_4_start = 0x10050000;
_memmap_seg_dram0_4_max   = 0x10080000;

_rom_store_table = 0;
PROVIDE(_memmap_reset_vector = 0x10000000);
PROVIDE(_memmap_vecbase_reset = 0x10000800);
/* Various memory-map dependent cache attribute settings: */
_memmap_cacheattr_wb_base = 0x00000001;
_memmap_cacheattr_wt_base = 0x00000003;
_memmap_cacheattr_bp_base = 0x00000004;
_memmap_cacheattr_unused_mask = 0xFFFFFFF0;
_memmap_cacheattr_wb_trapnull = 0x44444441;
_memmap_cacheattr_wba_trapnull = 0x44444441;
_memmap_cacheattr_wbna_trapnull = 0x44444442;
_memmap_cacheattr_wt_trapnull = 0x44444443;
_memmap_cacheattr_bp_trapnull = 0x44444444;
_memmap_cacheattr_wb_strict = 0x00000001;
_memmap_cacheattr_wt_strict = 0x00000003;
_memmap_cacheattr_bp_strict = 0x00000004;
_memmap_cacheattr_wb_allvalid = 0x44444441;
_memmap_cacheattr_wt_allvalid = 0x44444443;
_memmap_cacheattr_bp_allvalid = 0x44444444;
_memmap_region_map = 0x00000001;
PROVIDE(_memmap_cacheattr_reset = _memmap_cacheattr_bp_trapnull);

SECTIONS
{

  .srom.text : ALIGN(4)
  {
    _srom_text_start = ABSOLUTE(.);
    KEEP (*(.srom.text))
    . = ALIGN (4);
    _srom_text_end = ABSOLUTE(.);
  } >srom0_seg :srom0_phdr

  .srom.rodata : ALIGN(4)
  {
    _srom_rodata_start = ABSOLUTE(.);
    *(.srom.rodata)
    . = ALIGN (4);
    _srom_rodata_end = ABSOLUTE(.);
  } >srom0_seg :srom0_phdr

  .srom.literal : ALIGN(4)
  {
    _srom_literal_start = ABSOLUTE(.);
    *(.srom.literal)
    . = ALIGN (4);
    _srom_literal_end = ABSOLUTE(.);
    _memmap_seg_srom0_end = ALIGN(0x8);
  } >srom0_seg :srom0_phdr

  _memmap_mem_srom_max = ABSOLUTE(.);

  .sram.system_status.data : ALIGN(4)
  {
    _sram_system_status_data_start = ABSOLUTE(.);
    *(.sram.system_status.data)
    . = ALIGN (4);
    _sram_system_status_data_end = ABSOLUTE(.);
    _memmap_seg_sram0_0_end = ALIGN(0x8);
  } >sram0_0_seg :sram0_0_phdr


  .sram.table.data : ALIGN(4)
  {
    _sram_table_data_start = ABSOLUTE(.);
    *(.sram.table.data)
    . = ALIGN (4);
    _sram_table_data_end = ABSOLUTE(.);
    _memmap_seg_sram0_1_end = ALIGN(0x8);
  } >sram0_1_seg :sram0_1_phdr


  .sram.ax.rw : ALIGN(4)
  {
    _sram_ax_rw_start = ABSOLUTE(.);
    *(.sram.ax.rw)
    . = ALIGN (4);
    _sram_ax_rw_end = ABSOLUTE(.);
    _memmap_seg_sram0_2_end = ALIGN(0x8);
  } >sram0_2_seg :sram0_2_phdr


  .sram.rx.rw : ALIGN(4)
  {
    _sram_rx_rw_start = ABSOLUTE(.);
    *(.sram.rx.rw)
    . = ALIGN (4);
    _sram_rx_rw_end = ABSOLUTE(.);
    _memmap_seg_sram0_3_end = ALIGN(0x8);
  } >sram0_3_seg :sram0_3_phdr


  .sram.tx.rw : ALIGN(4)
  {
    _sram_tx_rw_start = ABSOLUTE(.);
    *(.sram.tx.rw)
    . = ALIGN (4);
    _sram_tx_rw_end = ABSOLUTE(.);
    _memmap_seg_sram0_4_end = ALIGN(0x8);
  } >sram0_4_seg :sram0_4_phdr


  .sram.cal.rw : ALIGN(4)
  {
    _sram_cal_rw_start = ABSOLUTE(.);
    *(.sram.cal.rw)
    . = ALIGN (4);
    _sram_cal_rw_end = ABSOLUTE(.);
    _memmap_seg_sram0_5_end = ALIGN(0x8);
  } >sram0_5_seg :sram0_5_phdr


  .sram.reserved : ALIGN(4)
  {
    _sram_reserved_start = ABSOLUTE(.);
    *(.sram.reserved)
    . = ALIGN (4);
    _sram_reserved_end = ABSOLUTE(.);
    _memmap_seg_sram0_6_end = ALIGN(0x8);
  } >sram0_6_seg :sram0_6_phdr


  .sram.ax.flag : ALIGN(4)
  {
    _sram_ax_flag_start = ABSOLUTE(.);
    *(.sram.ax.flag)
    . = ALIGN (4);
    _sram_ax_flag_end = ABSOLUTE(.);
    _memmap_seg_sram0_7_end = ALIGN(0x8);
  } >sram0_7_seg :sram0_7_phdr


  .sram.tx.flag : ALIGN(4)
  {
    _sram_tx_flag_start = ABSOLUTE(.);
    *(.sram.tx.flag)
    . = ALIGN (4);
    _sram_tx_flag_end = ABSOLUTE(.);
    _memmap_seg_sram0_8_end = ALIGN(0x8);
  } >sram0_8_seg :sram0_8_phdr


  .sram.rx.flag : ALIGN(4)
  {
    _sram_rx_flag_start = ABSOLUTE(.);
    *(.sram.rx.flag)
    . = ALIGN (4);
    _sram_rx_flag_end = ABSOLUTE(.);
    _memmap_seg_sram0_9_end = ALIGN(0x8);
  } >sram0_9_seg :sram0_9_phdr


  .sram.cal.flag : ALIGN(4)
  {
    _sram_cal_flag_start = ABSOLUTE(.);
    *(.sram.cal.flag)
    . = ALIGN (4);
    _sram_cal_flag_end = ABSOLUTE(.);
    _memmap_seg_sram0_10_end = ALIGN(0x8);
  } >sram0_10_seg :sram0_10_phdr


  .sram.com.flag : ALIGN(4)
  {
    _sram_com_flag_start = ABSOLUTE(.);
    *(.sram.com.flag)
    . = ALIGN (4);
    _sram_com_flag_end = ABSOLUTE(.);
    _memmap_seg_sram0_11_end = ALIGN(0x8);
  } >sram0_11_seg :sram0_11_phdr

  _memmap_mem_sram_max = ABSOLUTE(.);

  .ResetVector.text : ALIGN(4)
  {
    _ResetVector_text_start = ABSOLUTE(.);
    KEEP (*(.ResetVector.text))
    . = ALIGN (4);
    _ResetVector_text_end = ABSOLUTE(.);
  } >iram0_0_seg :iram0_0_phdr

  .ResetHandler.text : ALIGN(4)
  {
    _ResetHandler_text_start = ABSOLUTE(.);
    *(.ResetHandler.literal .ResetHandler.text)
    . = ALIGN (4);
    _ResetHandler_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_0_end = ALIGN(0x8);
  } >iram0_0_seg :iram0_0_phdr


  .MemoryExceptionVector.literal : ALIGN(4)
  {
    _MemoryExceptionVector_literal_start = ABSOLUTE(.);
    *(.MemoryExceptionVector.literal)
    . = ALIGN (4);
    _MemoryExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_1_end = ALIGN(0x8);
  } >iram0_1_seg :iram0_1_phdr


  .MemoryExceptionVector.text : ALIGN(4)
  {
    _MemoryExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.MemoryExceptionVector.text))
    . = ALIGN (4);
    _MemoryExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_2_end = ALIGN(0x8);
  } >iram0_2_seg :iram0_2_phdr



  .WindowVectors.text : ALIGN(4)
  {
    _WindowVectors_text_start = ABSOLUTE(.);
    KEEP (*(.WindowVectors.text))
    . = ALIGN (4);
    _WindowVectors_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_4_end = ALIGN(0x8);
  } >iram0_4_seg :iram0_4_phdr


  .Level2InterruptVector.literal : ALIGN(4)
  {
    _Level2InterruptVector_literal_start = ABSOLUTE(.);
    *(.Level2InterruptVector.literal)
    . = ALIGN (4);
    _Level2InterruptVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_5_end = ALIGN(0x8);
  } >iram0_5_seg :iram0_5_phdr


  .Level2InterruptVector.text : ALIGN(4)
  {
    _Level2InterruptVector_text_start = ABSOLUTE(.);
    KEEP (*(.Level2InterruptVector.text))
    . = ALIGN (4);
    _Level2InterruptVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_6_end = ALIGN(0x8);
  } >iram0_6_seg :iram0_6_phdr


  .Level3InterruptVector.literal : ALIGN(4)
  {
    _Level3InterruptVector_literal_start = ABSOLUTE(.);
    *(.Level3InterruptVector.literal)
    . = ALIGN (4);
    _Level3InterruptVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_7_end = ALIGN(0x8);
  } >iram0_7_seg :iram0_7_phdr


  .Level3InterruptVector.text : ALIGN(4)
  {
    _Level3InterruptVector_text_start = ABSOLUTE(.);
    KEEP (*(.Level3InterruptVector.text))
    . = ALIGN (4);
    _Level3InterruptVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_8_end = ALIGN(0x8);
  } >iram0_8_seg :iram0_8_phdr


  .Level4InterruptVector.literal : ALIGN(4)
  {
    _Level4InterruptVector_literal_start = ABSOLUTE(.);
    *(.Level4InterruptVector.literal)
    . = ALIGN (4);
    _Level4InterruptVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_9_end = ALIGN(0x8);
  } >iram0_9_seg :iram0_9_phdr


  .Level4InterruptVector.text : ALIGN(4)
  {
    _Level4InterruptVector_text_start = ABSOLUTE(.);
    KEEP (*(.Level4InterruptVector.text))
    . = ALIGN (4);
    _Level4InterruptVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_10_end = ALIGN(0x8);
  } >iram0_10_seg :iram0_10_phdr


  .DebugExceptionVector.literal : ALIGN(4)
  {
    _DebugExceptionVector_literal_start = ABSOLUTE(.);
    *(.DebugExceptionVector.literal)
    . = ALIGN (4);
    _DebugExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_11_end = ALIGN(0x8);
  } >iram0_11_seg :iram0_11_phdr


  .DebugExceptionVector.text : ALIGN(4)
  {
    _DebugExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.DebugExceptionVector.text))
    . = ALIGN (4);
    _DebugExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_12_end = ALIGN(0x8);
  } >iram0_12_seg :iram0_12_phdr


  .NMIExceptionVector.literal : ALIGN(4)
  {
    _NMIExceptionVector_literal_start = ABSOLUTE(.);
    *(.NMIExceptionVector.literal)
    . = ALIGN (4);
    _NMIExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_13_end = ALIGN(0x8);
  } >iram0_13_seg :iram0_13_phdr


  .NMIExceptionVector.text : ALIGN(4)
  {
    _NMIExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.NMIExceptionVector.text))
    . = ALIGN (4);
    _NMIExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_14_end = ALIGN(0x8);
  } >iram0_14_seg :iram0_14_phdr


  .KernelExceptionVector.literal : ALIGN(4)
  {
    _KernelExceptionVector_literal_start = ABSOLUTE(.);
    *(.KernelExceptionVector.literal)
    . = ALIGN (4);
    _KernelExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_15_end = ALIGN(0x8);
  } >iram0_15_seg :iram0_15_phdr


  .KernelExceptionVector.text : ALIGN(4)
  {
    _KernelExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.KernelExceptionVector.text))
    . = ALIGN (4);
    _KernelExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_16_end = ALIGN(0x8);
  } >iram0_16_seg :iram0_16_phdr


  .UserExceptionVector.literal : ALIGN(4)
  {
    _UserExceptionVector_literal_start = ABSOLUTE(.);
    *(.UserExceptionVector.literal)
    . = ALIGN (4);
    _UserExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_17_end = ALIGN(0x8);
  } >iram0_17_seg :iram0_17_phdr


  .UserExceptionVector.text : ALIGN(4)
  {
    _UserExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.UserExceptionVector.text))
    . = ALIGN (4);
    _UserExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_18_end = ALIGN(0x8);
  } >iram0_18_seg :iram0_18_phdr


  .DoubleExceptionVector.literal : ALIGN(4)
  {
    _DoubleExceptionVector_literal_start = ABSOLUTE(.);
    *(.DoubleExceptionVector.literal)
    . = ALIGN (4);
    _DoubleExceptionVector_literal_end = ABSOLUTE(.);
    _memmap_seg_iram0_19_end = ALIGN(0x8);
  } >iram0_19_seg :iram0_19_phdr


  .DoubleExceptionVector.text : ALIGN(4)
  {
    _DoubleExceptionVector_text_start = ABSOLUTE(.);
    KEEP (*(.DoubleExceptionVector.text))
    . = ALIGN (4);
    _DoubleExceptionVector_text_end = ABSOLUTE(.);
    _memmap_seg_iram0_20_end = ALIGN(0x8);
  } >iram0_20_seg :iram0_20_phdr


  .iram0.text : ALIGN(4)
  {
    _iram0_text_start = ABSOLUTE(.);
    *(.iram0.literal .iram.literal .iram.text.literal .iram0.text .iram.text)
    . = ALIGN (4);
    _iram0_text_end = ABSOLUTE(.);
  } >iram0_21_seg :iram0_21_phdr

  .text : ALIGN(4)
  {
    _stext = .;
    _text_start = ABSOLUTE(.);
    *(.entry.text)
    *(.init.literal)
    KEEP(*(.init))
    *(.literal.sort.* SORT(.text.sort.*))
    KEEP (*(.literal.keepsort.* SORT(.text.keepsort.*) .literal.keep.* .text.keep.* .literal.*personality* .text.*personality*))
    *(.literal .text .literal.* .text.* .stub .gnu.warning .gnu.linkonce.literal.* .gnu.linkonce.t.*.literal .gnu.linkonce.t.*)
    *(.fini.literal)
    KEEP(*(.fini))
    *(.gnu.version)
    . = ALIGN (4);
    _text_end = ABSOLUTE(.);
    _etext = .;
  } >iram0_21_seg :iram0_21_phdr

  .clib.text : ALIGN(4)
  {
    _clib_text_start = ABSOLUTE(.);
    *(.clib.literal .clib.text)
    . = ALIGN (4);
    _clib_text_end = ABSOLUTE(.);
  } >iram0_21_seg :iram0_21_phdr

  .rtos.text : ALIGN(4)
  {
    _rtos_text_start = ABSOLUTE(.);
    *(.rtos.literal .rtos.text)
    . = ALIGN (4);
    _rtos_text_end = ABSOLUTE(.);
  } >iram0_21_seg :iram0_21_phdr

  .note.gnu.build-id : ALIGN(4)
  {
    _note_gnu_build-id_start = ABSOLUTE(.);
    *(.note.gnu.build-id)
    . = ALIGN (4);
    _note_gnu_build-id_end = ABSOLUTE(.);
    _memmap_seg_iram0_21_end = ALIGN(0x8);
  } >iram0_21_seg :iram0_21_phdr

  _memmap_mem_iram0_max = ABSOLUTE(.);

  .dram0.com_tables.data : ALIGN(4)
  {
    _dram0_com_tables_data_start = ABSOLUTE(.);
    KEEP(*(.dram0.com_tables.data))
    . = ALIGN (4);
    _dram0_com_tables_data_end = ABSOLUTE(.);
  } >dram0_0_seg :dram0_0_phdr

  .dram0.cal_tables.data : ALIGN(4)
  {
    _dram0_cal_tables_data_start = ABSOLUTE(.);
    KEEP(*(.dram0.cal_tables.data))
    . = ALIGN (4);
    _dram0_cal_tables_data_end = ABSOLUTE(.);
    _memmap_seg_dram0_0_end = ALIGN(0x8);
  } >dram0_0_seg :dram0_0_phdr


  .dram0.rodata : ALIGN(4)
  {
    _dram0_rodata_start = ABSOLUTE(.);
    *(.dram0.rodata)
    *(.dram.rodata)
    . = ALIGN (4);
    _dram0_rodata_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .dram0.data : ALIGN(4)
  {
    _dram0_data_start = ABSOLUTE(.);
    *(.dram0.data)
    *(.dram.data)
    . = ALIGN (4);
    _dram0_data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .clib.rodata : ALIGN(4)
  {
    _clib_rodata_start = ABSOLUTE(.);
    *(.clib.rodata)
    . = ALIGN (4);
    _clib_rodata_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .rtos.rodata : ALIGN(4)
  {
    _rtos_rodata_start = ABSOLUTE(.);
    *(.rtos.rodata)
    . = ALIGN (4);
    _rtos_rodata_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .rodata : ALIGN(4)
  {
    _rodata_start = ABSOLUTE(.);
    *(.rodata)
    *(SORT(.rodata.sort.*))
    KEEP (*(SORT(.rodata.keepsort.*) .rodata.keep.*))
    *(.rodata.*)
    *(.gnu.linkonce.r.*)
    *(.rodata1)
    __XT_EXCEPTION_TABLE__ = ABSOLUTE(.);
    KEEP (*(.xt_except_table))
    KEEP (*(.gcc_except_table))
    *(.gnu.linkonce.e.*)
    *(.gnu.version_r)
    PROVIDE (__eh_frame_start = .);
    KEEP (*(.eh_frame))
    PROVIDE (__eh_frame_end = .);
    /*  C++ constructor and destructor tables, properly ordered:  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
    /*  C++ exception handlers table:  */
    __XT_EXCEPTION_DESCS__ = ABSOLUTE(.);
    *(.xt_except_desc)
    *(.gnu.linkonce.h.*)
    __XT_EXCEPTION_DESCS_END__ = ABSOLUTE(.);
    *(.xt_except_desc_end)
    *(.dynamic)
    *(.gnu.version_d)
    . = ALIGN(4);		/* this table MUST be 4-byte aligned */
    _bss_table_start = ABSOLUTE(.);
    LONG(_bss_start)
    LONG(_bss_end)
    _bss_table_end = ABSOLUTE(.);
    . = ALIGN (4);
    _rodata_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .clib.data : ALIGN(4)
  {
    _clib_data_start = ABSOLUTE(.);
    *(.clib.data)
    . = ALIGN (4);
    _clib_data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .clib.percpu.data : ALIGN(4)
  {
    _clib_percpu_data_start = ABSOLUTE(.);
    *(.clib.percpu.data)
    . = ALIGN (4);
    _clib_percpu_data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .rtos.percpu.data : ALIGN(4)
  {
    _rtos_percpu_data_start = ABSOLUTE(.);
    *(.rtos.percpu.data)
    . = ALIGN (4);
    _rtos_percpu_data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .rtos.data : ALIGN(4)
  {
    _rtos_data_start = ABSOLUTE(.);
    *(.rtos.data)
    . = ALIGN (4);
    _rtos_data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .data : ALIGN(4)
  {
    _data_start = ABSOLUTE(.);
    *(.data)
    *(SORT(.data.sort.*))
    KEEP (*(SORT(.data.keepsort.*) .data.keep.*))
    *(.data.*)
    *(.gnu.linkonce.d.*)
    KEEP(*(.gnu.linkonce.d.*personality*))
    *(.data1)
    *(.sdata)
    *(.sdata.*)
    *(.gnu.linkonce.s.*)
    *(.sdata2)
    *(.sdata2.*)
    *(.gnu.linkonce.s2.*)
    KEEP(*(.jcr))
    . = ALIGN (4);
    _data_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  __llvm_prf_names : ALIGN(4)
  {
    __llvm_prf_names_start = ABSOLUTE(.);
    *(__llvm_prf_names)
    . = ALIGN (4);
    __llvm_prf_names_end = ABSOLUTE(.);
  } >dram0_1_seg :dram0_1_phdr

  .bss (NOLOAD) : ALIGN(8)
  {
    . = ALIGN (8);
    _bss_start = ABSOLUTE(.);
    *(.dynsbss)
    *(.sbss)
    *(.sbss.*)
    *(.gnu.linkonce.sb.*)
    *(.scommon)
    *(.sbss2)
    *(.sbss2.*)
    *(.gnu.linkonce.sb2.*)
    *(.dynbss)
    *(.bss)
    *(SORT(.bss.sort.*))
    KEEP (*(SORT(.bss.keepsort.*) .bss.keep.*))
    *(.bss.*)
    *(.gnu.linkonce.b.*)
    *(COMMON)
    *(.clib.bss)
    *(.clib.percpu.bss)
    *(.rtos.percpu.bss)
    *(.rtos.bss)
    *(.dram0.bss)
    . = ALIGN (8);
    _bss_end = ABSOLUTE(.);
    _memmap_seg_dram0_1_end = ALIGN(0x8);
  } >dram0_1_seg :dram0_1_bss_phdr


  _end = 0x1004d000;
  PROVIDE(end = 0x1004d000);
  _heap_sentry = 0x1004f000;

  _stack_sentry = 0x1004f000;
  PROVIDE(__stack = 0x10050000);

  .dram0.calib_matrix : ALIGN(4)
  {
    _dram0_calib_matrix_start = ABSOLUTE(.);
    *(.dram0.calib_matrix)
    . = ALIGN (4);
    _dram0_calib_matrix_end = ABSOLUTE(.);
    _memmap_seg_dram0_4_end = ALIGN(0x8);
  } >dram0_4_seg :dram0_4_phdr


  _memmap_mem_dram0_max = ABSOLUTE(.);

  .debug  0 :  { *(.debug) }
  .line  0 :  { *(.line) }
  .debug_srcinfo  0 :  { *(.debug_srcinfo) }
  .debug_sfnames  0 :  { *(.debug_sfnames) }
  .debug_aranges  0 :  { *(.debug_aranges) }
  .debug_ranges   0 :  { *(.debug_ranges) }
  .debug_pubnames  0 :  { *(.debug_pubnames) }
  .debug_info  0 :  { *(.debug_info) }
  .debug_abbrev  0 :  { *(.debug_abbrev) }
  .debug_line  0 :  { *(.debug_line) }
  .debug_frame  0 :  { *(.debug_frame) }
  .debug_str  0 :  { *(.debug_str) }
  .debug_loc  0 :  { *(.debug_loc) }
  .debug_macinfo  0 :  { *(.debug_macinfo) }
  .debug_weaknames  0 :  { *(.debug_weaknames) }
  .debug_funcnames  0 :  { *(.debug_funcnames) }
  .debug_typenames  0 :  { *(.debug_typenames) }
  .debug_varnames  0 :  { *(.debug_varnames) }
  .debug.xt.map 0 :  { *(.debug.xt.map) }
  .xt.insn 0 :
  {
    KEEP (*(.xt.insn))
    KEEP (*(.gnu.linkonce.x.*))
  }
  .xt.prop 0 :
  {
    *(.xt.prop)
    *(.xt.prop.*)
    *(.gnu.linkonce.prop.*)
  }
  .xt.lit 0 :
  {
    *(.xt.lit)
    *(.xt.lit.*)
    *(.gnu.linkonce.p.*)
  }
  .xtensa.info 0 :
  {
    *(.xtensa.info)
  }
  .debug.xt.callgraph 0 :
  {
    KEEP (*(.debug.xt.callgraph .debug.xt.callgraph.* .gnu.linkonce.xt.callgraph.*))
  }
  .comment 0 :
  {
    KEEP(*(.comment))
  }
  .note.GNU-stack 0 :
  {
    *(.note.GNU-stack)
  }
}

