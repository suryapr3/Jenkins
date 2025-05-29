source_file "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c"
command "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.stubs.h -backend-report /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.rpt.json --o-optimized-ir /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.opt.ll --o-clang-ir /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.clang.ll -emit-after-pp /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex -I. -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/host/include -o-dot-s /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.s -DVOLCANO=1 -o /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.o "
machine.name "ve32"
machine.path "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"
@vex2rcs_prog()
{
frame bp_dmem
  size = 20
  inputs_size = 16
  locals_size = 4
  callee_spill_size = 0
  caller_spill_size = 16
  arguments_size = 0
frame simd0_vmem
  size = 0
  inputs_size = 0
  locals_size = 0
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 0
pragma $type-splitting=1
schedule(vex2rcs_prog.0)
  dtree vex2rcs_prog.0
  view ve32
  comment "LLVM BB name: entry"
  cycle 0: {
  m0: %readreg<X:32:1> bp_rf1[1] => e0 ;
    read
  m1: %readreg<X:32:1> bp_rf1[0] => ;
    read
  m2: %readreg<X:32:1> simd0_vlsu0_srf0[0] => ;
    read
  m3: %readreg<X:32:1> bp_rf1[6] => ;
    read
  m4: %readreg<X:32:1> simd0_vlsu0_srf0[3] => ;
    read
  m5: %readreg<X:32:1> simd0_vlsu1_srf0[0] => ;
    read
  n100: s_imm_u #@vinput => split(e1,e2,e3) ;
    units (simd0_vlsu0_spsu )
    critical
  n4800: s_pass e0[hard bp_rf1[1]] => e4 ;
    units (bp_s1_psu )
  }
  cycle 1: {
  n200: v_ldo_1024_i_PIPE_0_3 e1[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[2]] #0 => ;
    units (simd0_vlsu0_vlsu )
    critical
    succpipeop(n201);
  n1100: s_jmp e4[hard bp_s1_op0_BUS->bp_rf0_wp1->bp_rf0[0]] => e5 ;
    units (bp_s0_bru )
  }
  cycle 2: {
  n201: v_ldo_1024_i_PIPE_1_3  => ;
    units (simd0_vlsu0_vlsu )
    critical
    succpipeop(n202);
  n500: v_ldo_1024_i_PIPE_0_3 e2[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[2]] #128 => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n501);
  }
  cycle 3: {
  n202: v_ldo_1024_i_PIPE_2_3  => ;
    units (simd0_vlsu0_vlsu )
    critical
    succpipeop(n203);
  n501: v_ldo_1024_i_PIPE_1_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n502);
  n700: v_ldo_1024_i_PIPE_0_3 e3[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[2]] #256 => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n701);
  }
  cycle 4: {
  n203: v_ldo_1024_i_PIPE_3_3  => e6 ;
    units (simd0_vlsu0_vlsu )
    critical
  n502: v_ldo_1024_i_PIPE_2_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n503);
  n701: v_ldo_1024_i_PIPE_1_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n702);
  n300: s_imm #0 => split(e7,e8,e9) ;
    units (simd0_vlsu0_spsu )
  }
  cycle 5: {
  n503: v_ldo_1024_i_PIPE_3_3  => e10 ;
    units (simd0_vlsu0_vlsu )
  n702: v_ldo_1024_i_PIPE_2_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n703);
  n400: v_xsto_1024_i e7[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[1]] #0 e6[hard simd0_vlsu0_vop0_BUS->simd0_vlsu0_vrf0_ip1->simd0_vlsu0_vrf0[0]] => ;
    units (simd0_vlsu0_vmlsu )
    critical
  }
  cycle 6: {
  n703: v_ldo_1024_i_PIPE_3_3  => e11 ;
    units (simd0_vlsu0_vlsu )
  n600: v_xsto_1024_i e8[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[1]] #0 e10[hard simd0_vlsu0_vop0_BUS->simd0_vlsu0_vrf0_ip1->simd0_vlsu0_vrf0[1]] => ;
    units (simd0_vlsu0_vmlsu )
    critical
  }
  cycle 7: {
  //  n900: %PRINTSTRING<S:32:1> "\0A" => ;
  //  n1000: %PRINTSTRING<S:32:1> "------------vex2rcs core:END------------\0A" => ;
  n800: v_xsto_1024_i e9[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[1]] #0 e11[hard simd0_vlsu0_vop0_BUS->simd0_vlsu0_vrf0_ip1->simd0_vlsu0_vrf0[2]] => ;
    units (simd0_vlsu0_vmlsu )
    critical
  m26: %writereg<X:32:1> bp_pc[0] e5[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  return;
}
@vex2rcs_prog_entry()
{
  entry
frame bp_dmem
  size = 20
  inputs_size = 16
  locals_size = 4
  callee_spill_size = 0
  caller_spill_size = 16
  arguments_size = 0
frame simd0_vmem
  size = 0
  inputs_size = 0
  locals_size = 0
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 0
pragma $type-splitting=1
schedule(vex2rcs_prog_entry.0)
  dtree vex2rcs_prog_entry.0
  successors : 0=vex2rcs_prog_entry.1[] ;
  view ve32
  comment "LLVM BB name: "
  cycle 0: {
  m27: %readreg<X:32:1> bp_rf1[0] => ;
    read
  m28: %readreg<X:32:1> simd0_vlsu0_srf0[0] => ;
    read
  m29: %readreg<X:32:1> bp_rf1[6] => ;
    read
  m30: %readreg<X:32:1> simd0_vlsu0_srf0[3] => ;
    read
  m31: %readreg<X:32:1> simd0_vlsu1_srf0[0] => ;
    read
  n8300: s_jmp_i #@vex2rcs_prog => e12 ;
    units (bp_s0_bru )
    critical
  }
  cycle 1: {
  }
  cycle 2: {
  }
  cycle 3: {
  }
  cycle 4: {
  n10700: s_imm_u #1 => e13 ;
    units (bp_s0_psu )
  }
  cycle 5: {
  n11000: s_imm_u #16384 => e14 ;
    units (bp_s1_psu )
  n10400: s_imm_u #1 => e15 ;
    units (bp_s0_psu )
  }
  cycle 6: {
  n11300: s_imm_u #65536 => e16 ;
    units (bp_s1_psu )
  n10100: s_imm_u #1 => e17 ;
    units (bp_s0_psu )
  n8100: s_imm_u #vex2rcs_prog_entry.1 => e18 ;
    units (simd0_vcom0_spsu )
  m52: %writereg<X:32:1> bp_rf1[1] e18[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[1]] => ;
    write
  m53: %writereg<X:32:1> bp_rf1[6] e17[hard bp_s0_op0_BUS->bp_rf1_wp1->bp_rf1[6]] => ;
    write
  m54: %writereg<X:32:1> simd0_vlsu0_srf0[3] e15[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[3]] => ;
    write
  m55: %writereg<X:32:1> bp_rf1[0] e14[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[0]] => ;
    write
  m56: %writereg<X:32:1> simd0_vlsu1_srf0[0] e13[hard bp_2_simd_op0_BUS->simd0_vlsu1_srf0_ip1->simd0_vlsu1_srf0[0]] => ;
    write
  m57: %writereg<X:32:1> bp_pc[0] e12[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  m58: %writereg<X:32:1> simd0_vlsu0_srf0[0] e16[hard bp_2_simd_op1_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[0]] => ;
    write
  }
  call[] #@vex2rcs_prog;
  goto successor(0) fallthru ;
schedule(vex2rcs_prog_entry.1)
  dtree vex2rcs_prog_entry.1
  view ve32
  comment "LLVM BB name: "
  cycle 7: {
  m59: %readreg<X:32:1> bp_cr[0] => e19 ;
    read
  n8500: s_idle e19[hard bp_cr[0]] => e20 ;
    units (bp_s0_suu )
    critical
  }
  cycle 8: {
  }
  cycle 9: {
  }
  cycle 10: {
  }
  cycle 11: {
  }
  cycle 12: {
  }
  cycle 13: {
  m68: %writereg<X:32:1> bp_cr[0] e20[hard bp_s0_cr_BUS->bp_cr_wp->bp_cr[0]] => ;
    write
  }
  return;
}
memory simd0_vmem {
global @vinput size=384 align=128 = {  { 384 : 0 }} ;
};
REGION 0 .. 1 : @vex2rcs_prog, @vex2rcs_prog:m0, e0, @vex2rcs_prog:m1, @vex2rcs_prog:m2, @vex2rcs_prog:m3, @vex2rcs_prog:m4, @vex2rcs_prog:m5, @vex2rcs_prog:n100, e1, e2, e3, @vex2rcs_prog:n300, e7, e8, e9, @vex2rcs_prog_entry, @vex2rcs_prog_entry:m27, @vex2rcs_prog_entry:m28, @vex2rcs_prog_entry:m29, @vex2rcs_prog_entry:m30, @vex2rcs_prog_entry:m31, @vex2rcs_prog_entry:m52
REGION 2 .. 3 : @vex2rcs_prog_entry:vex2rcs_prog_entry.0, @vex2rcs_prog_entry:vex2rcs_prog_entry.1, @vex2rcs_prog_entry:n8300, e12, @vex2rcs_prog_entry:n10700, e13, @vex2rcs_prog_entry:n11000, e14, @vex2rcs_prog_entry:n10400, e15, @vex2rcs_prog_entry:n11300, e16, @vex2rcs_prog_entry:n10100, e17, @vex2rcs_prog_entry:n8100, e18, @vex2rcs_prog_entry:n8500, e20, @vex2rcs_prog_entry:m59, e19, @vex2rcs_prog_entry:m68
REGION 4 .. 12 : @vex2rcs_prog:vex2rcs_prog.0
REGION 5 .. 6 : @vex2rcs_prog:n200, @vex2rcs_prog:n201, @vex2rcs_prog:n500, @vex2rcs_prog:n202, @vex2rcs_prog:n501, @vex2rcs_prog:n700, @vex2rcs_prog:n203, e6, @vex2rcs_prog:n502, @vex2rcs_prog:n701, @vex2rcs_prog:n503, e10, @vex2rcs_prog:n702, @vex2rcs_prog:n400, @vex2rcs_prog:n703, e11, @vex2rcs_prog:n600, @vex2rcs_prog:n800
REGION 7 .. 8 : @vex2rcs_prog:n900
REGION 9 .. 10 : @vex2rcs_prog:n1000
REGION 11 .. 12 : @vex2rcs_prog:n4800, e4, @vex2rcs_prog:n1100, e5
LOCATION 0 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":12,0
LOCATION 1 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":12,1000
LOCATION 2 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":13,0
LOCATION 3 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":13,1000
LOCATION 4 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":15,0
LOCATION 5 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":15,2
LOCATION 6 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":15,1000
LOCATION 7 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":17,3
LOCATION 8 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":17,1000
LOCATION 9 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":18,3
LOCATION 10 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":18,1000
LOCATION 11 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":19,1
LOCATION 12 = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c":19,1000
