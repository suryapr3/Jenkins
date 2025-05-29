source_file "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c"
command "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.stubs.h -backend-report /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.rpt.json --o-optimized-ir /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.opt.ll --o-clang-ir /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.clang.ll -emit-after-pp /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw -I. -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/host/include -o-dot-s /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.s -DVOLCANO=1 -o /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.o "
machine.name "ve32"
machine.path "/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"
@consumer_prog()
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
schedule(consumer_prog.0)
  dtree consumer_prog.0
  successors : 0=consumer_prog.1[] ;
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
  n700: s_imm #1 => split(e1,e2,e3,e4,e5,e6,e7,e8,e9,e10,e11,e12,e13,e14) ;
    units (simd0_vcom0_spsu )
  }
  cycle 1: {
  n200: s_imm_u #@buffer_ra => e15 ;
    units (simd0_vlsu1_spsu )
  n500: s_imm #0 => split(e16,e17,e18,e19,e20,e21) ;
    units (bp_s1_psu )
    critical
  }
  cycle 2: {
  n300: s_ldo_32_i_PIPE_0_3 e15[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[3]] #0 => ;
    units (bp_s1_lsu_dm )
    succpipeop(n301);
  n800: s_immh #3 e1[hard simd0_vcom0_op0_BUS->simd0_vcom0_srf1_ip1->simd0_vcom0_srf1[0]] => e22 ;
    units (simd0_vcom0_spsu )
  n600: mc_reset_PIPE_0_1 e16[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[4]] => ;
    units (bp_s2_tsu )
    critical
    succpipeop(n601);
  }
  cycle 3: {
  n301: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n302);
  n601: mc_reset_PIPE_1_1  => ;
    units (bp_s2_tsu )
    critical
  n900: mc_init_PIPE_0_1 e22[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[2]] e2[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    critical
    succpipeop(n901);
  }
  cycle 4: {
  n302: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n303);
  n901: mc_init_PIPE_1_1  => ;
    units (bp_s2_tsu )
    critical
  n1000: mc_init_local_idc e17[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[4]] e3[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    critical
  }
  cycle 5: {
  n303: s_ldo_32_i_PIPE_3_3  => e23 ;
    units (bp_s1_lsu_dm )
  n1400: mc_get_state_PIPE_0_1 e18[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[4]] e4[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n1401);
  }
  cycle 6: {
  n1401: mc_get_state_PIPE_1_1  => e24 ;
    units (bp_s2_tsu )
  n1600: mc_get_state_PIPE_0_1 e5[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e6[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n1601);
  n1800: s_imm #2 => e25 ;
    units (bp_s0_psu )
  }
  cycle 7: {
  n1601: mc_get_state_PIPE_1_1  => e26 ;
    units (bp_s2_tsu )
  n1900: mc_get_state_PIPE_0_1 e25[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] e7[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n1901);
  n2100: s_imm #3 => e27 ;
    units (simd0_vcom0_spsu )
  }
  cycle 8: {
  n1901: mc_get_state_PIPE_1_1  => e28 ;
    units (bp_s2_tsu )
  n2200: mc_get_state_PIPE_0_1 e27[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[3]] e8[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n2201);
  n2400: s_imm #4 => e29 ;
    units (simd0_vlsu0_spsu )
  }
  cycle 9: {
  n2201: mc_get_state_PIPE_1_1  => e30 ;
    units (bp_s2_tsu )
  n2500: mc_get_state_PIPE_0_1 e29[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[14]] e9[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n2501);
  n2700: s_imm #5 => e31 ;
    units (bp_s1_psu )
  }
  cycle 10: {
  n2501: mc_get_state_PIPE_1_1  => e32 ;
    units (bp_s2_tsu )
  n2800: mc_get_state_PIPE_0_1 e31[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[15]] e10[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    critical
    succpipeop(n2801);
  n3700: s_imm_u #@gTimeStampData => e33 ;
    units (simd0_vlsu1_spsu )
  n3000: s_imm_u #@count => split(e34,e35,e36,e37) ;
    units (bp_s1_psu )
  }
  cycle 11: {
  n2801: mc_get_state_PIPE_1_1  => e38 ;
    units (bp_s2_tsu )
    critical
  //  n1100: %PRINTSTRING<S:32:1> "fu mc_get_state{1,2,3} idx=" => ;
  //  n1200: %DUMP<S:32:1> #1 e11 => ;
  //  n1300: %PRINTSTRING<S:32:1> "{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\0A" => ;
  n4300: s_imm_u #@gTimeStampDataCopy => e39 ;
    units (simd0_vlsu0_spsu )
  //  n1500: %DUMP<S:32:1> #0 e24 => ;
  //  n1700: %DUMP<S:32:1> #1 e26 => ;
  //  n2000: %DUMP<S:32:1> #2 e28 => ;
  //  n2300: %DUMP<S:32:1> #3 e30 => ;
  //  n2600: %DUMP<S:32:1> #4 e32 => ;
  n3100: s_sto_32_i e34[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[3]] #0 e19[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[2]] => ;
    units (bp_s1_lsu_dm )
    critical
  //  n2900: %DUMP<S:32:1> #5 e38 => ;
  }
  goto successor(0) fallthru ;
schedule(consumer_prog.1)
  dtree consumer_prog.1
  successors : 0=consumer_prog.2[] : 1=consumer_prog.3[] ;
  view ve32
  comment "LLVM BB name: while.body"
  cycle 12: {
  m41: %readreg<X:32:1> bp_rf1[6] => ;
    read
  n3900: s_add_i join(e20[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[2]],e50[hard bp_s1_op1_BUS->bp_rf1_wp0->bp_rf1[2]]) #1 => split(e40,e41) ;
    units (bp_s1_aru )
  }
  cycle 13: {
  n3400: mc_request_PIPE_0_1 e12[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e13[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => e42 ;
    units (bp_s2_tsu )
    critical
    synchronize
    sync_with s0
    succpipeop(n3401);
  n4800: s_le_i e40[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[31]] #4 => e43 ;
    units (bp_s1_aru )
  }
  cycle 14: {
  n3401: mc_request_PIPE_1_1  => e44 ;
    units (bp_s2_tsu )
    critical
  n3800: v_ldo_1024_i_PIPE_0_3 e33[hard simd0_vlsu1_op0_BUS->simd0_vlsu1_srf0_ip0->simd0_vlsu1_srf0[2]] #0 => ;
    units (simd0_vlsu1_vlsu )
    critical
    sync_with s0, s1
    succpipeop(n3801);
  n6300: s_jmpz_i #consumer_prog.3 e43[hard bp_s1_op0_BUS->bp_rf0_wp1->bp_rf0[1]] => e45 ;
    units (bp_s0_bru )
  }
  cycle 15: {
  n3801: v_ldo_1024_i_PIPE_1_3  => ;
    units (simd0_vlsu1_vlsu )
    critical
    succpipeop(n3802);
  }
  cycle 16: {
  n3802: v_ldo_1024_i_PIPE_2_3  => ;
    units (simd0_vlsu1_vlsu )
    critical
    succpipeop(n3803);
  }
  cycle 17: {
  n3803: v_ldo_1024_i_PIPE_3_3  => e46 ;
    units (simd0_vlsu1_vlsu )
    critical
  n4200: s_shl_i join(e21[hard bp_s1_op0_BUS->bp_rf0_wp1->bp_rf0[0]],e51[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[0]]) #7 => e47 ;
    units (bp_s0_shu )
  }
  cycle 18: {
  n4500: mc_complete_PIPE_0_1 e14[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[0]] => ;
    units (bp_s2_tsu )
    succpipeop(n4501);
  n4400: v_sto_1024 e47[hard bp_2_simd_op0_BUS->simd0_vlsu1_srf0_ip1->simd0_vlsu1_srf0[3]] e39[hard simd0_vlsu0_op0_BUS->simd0_vlsu1_srf0_ip0->simd0_vlsu1_srf0[1]] e46[hard simd0_vlsu1_vop0_BUS->simd0_vlsu0_vrf0_ip1->simd0_vlsu0_vrf0[0]] => ;
    units (simd0_vlsu1_vlsu )
    critical
    sync_with s0, s1
  }
  cycle 19: {
  n4501: mc_complete_PIPE_1_1  => e48 ;
    units (bp_s2_tsu )
  }
  cycle 20: {
  n4100: s_sto_32_i e35[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[3]] #0 e41[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[31]] => ;
    units (bp_s1_lsu_dm )
  n4700: v_xsto_32_i e23[hard bp_2_simd_op2_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[1]] #0 e48[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[2]] => ;
    units (simd0_vlsu0_vmlsu )
    critical
    synchronize
    sync_with s1
  m60: %writereg<X:32:1> bp_pc[0] e45[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(0) ;
  else goto successor(1);
schedule(consumer_prog.2)
  dtree consumer_prog.2
  successors : 0=consumer_prog.1[back] ;
  view ve32
  comment "LLVM BB name: while.body.while.body_crit_edge"
  cycle 21: {
  n6100: s_jmp_i #consumer_prog.1 => e49 ;
    units (bp_s0_bru )
    critical
  }
  cycle 22: {
  }
  cycle 23: {
  }
  cycle 24: {
  n5900: s_ldo_32_i_PIPE_0_3 e36[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[3]] #0 => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5901);
  }
  cycle 25: {
  n5901: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5902);
  }
  cycle 26: {
  n5902: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5903);
  }
  cycle 27: {
  n5903: s_ldo_32_i_PIPE_3_3  => split(e50,e51) ;
    units (bp_s1_lsu_dm )
  m72: %writereg<X:32:1> bp_pc[0] e49[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  goto successor(0);
schedule(consumer_prog.3)
  dtree consumer_prog.3
  view ve32
  comment "LLVM BB name: while.end"
  cycle 28: {
  n21700: s_pass e0[hard bp_rf1[1]] => e52 ;
    units (bp_s1_psu )
    critical
  }
  cycle 29: {
  n5600: s_jmp e52[hard bp_s1_op0_BUS->bp_rf0_wp1->bp_rf0[0]] => e53 ;
    units (bp_s0_bru )
    critical
  }
  cycle 30: {
  }
  cycle 31: {
  }
  cycle 32: {
  n5200: s_ldo_32_i_PIPE_0_3 e37[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[3]] #0 => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5201);
  }
  cycle 33: {
  n5201: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5202);
  }
  cycle 34: {
  n5202: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n5203);
  }
  cycle 35: {
  n5203: s_ldo_32_i_PIPE_3_3  => e54 ;
    units (bp_s1_lsu_dm )
  //  n5300: %DUMP<S:32:1> #56 e54 => ;
  //  n5400: %PRINTSTRING<S:32:1> "\0A" => ;
  //  n5500: %PRINTSTRING<S:32:1> "------------consumer core:END------------\0A" => ;
  m84: %writereg<X:32:1> bp_pc[0] e53[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  return;
}
@consumer_prog_entry()
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
schedule(consumer_prog_entry.0)
  dtree consumer_prog_entry.0
  successors : 0=consumer_prog_entry.1[] ;
  view ve32
  comment "LLVM BB name: "
  cycle 0: {
  m85: %readreg<X:32:1> bp_rf1[0] => ;
    read
  m86: %readreg<X:32:1> simd0_vlsu0_srf0[0] => ;
    read
  m87: %readreg<X:32:1> bp_rf1[6] => ;
    read
  m88: %readreg<X:32:1> simd0_vlsu0_srf0[3] => ;
    read
  m89: %readreg<X:32:1> simd0_vlsu1_srf0[0] => ;
    read
  n31600: s_jmp_i #@consumer_prog => e55 ;
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
  n34000: s_imm_u #1 => e56 ;
    units (bp_s0_psu )
  }
  cycle 5: {
  n34300: s_imm_u #16384 => e57 ;
    units (bp_s1_psu )
  n33700: s_imm_u #1 => e58 ;
    units (bp_s0_psu )
  }
  cycle 6: {
  n34600: s_imm_u #65536 => e59 ;
    units (bp_s1_psu )
  n33400: s_imm_u #1 => e60 ;
    units (bp_s0_psu )
  n31400: s_imm_u #consumer_prog_entry.1 => e61 ;
    units (simd0_vcom0_spsu )
  m110: %writereg<X:32:1> bp_rf1[1] e61[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[1]] => ;
    write
  m111: %writereg<X:32:1> simd0_vlsu1_srf0[0] e56[hard bp_2_simd_op0_BUS->simd0_vlsu1_srf0_ip1->simd0_vlsu1_srf0[0]] => ;
    write
  m112: %writereg<X:32:1> bp_rf1[0] e57[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[0]] => ;
    write
  m113: %writereg<X:32:1> simd0_vlsu0_srf0[0] e59[hard bp_2_simd_op1_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[0]] => ;
    write
  m114: %writereg<X:32:1> bp_rf1[6] e60[hard bp_s0_op0_BUS->bp_rf1_wp1->bp_rf1[6]] => ;
    write
  m115: %writereg<X:32:1> bp_pc[0] e55[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  m116: %writereg<X:32:1> simd0_vlsu0_srf0[3] e58[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[3]] => ;
    write
  }
  call[] #@consumer_prog;
  goto successor(0) fallthru ;
schedule(consumer_prog_entry.1)
  dtree consumer_prog_entry.1
  view ve32
  comment "LLVM BB name: "
  cycle 7: {
  m117: %readreg<X:32:1> bp_cr[0] => e62 ;
    read
  n31800: s_idle e62[hard bp_cr[0]] => e63 ;
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
  m126: %writereg<X:32:1> bp_cr[0] e63[hard bp_s0_cr_BUS->bp_cr_wp->bp_cr[0]] => ;
    write
  }
  return;
}
memory bp_dmem {
0x180    :global @consumer_sm_gate size=64 align=128 ;
0x40    :global @count size=4 align=4 ;
global @buffer_ra size=4 align=4 = {  { 4 : 0 }} ;
global @consumer_max_count size=4 align=4 = {  { 4 : 0 }} ;
global @consumer_token_per_request size=4 align=4 = {  { 4 : 0 }} ;
};
memory simd0_vmem {
0x0    :global @gTimeStampData size=128 align=128 ;
0x100    :global @gTimeStampDataCopy size=1280 align=128 ;
};
REGION 0 .. 1 : @consumer_prog:n900, @consumer_prog:n901
REGION 2 .. 3 : @consumer_prog:n1000
REGION 4 .. 5 : @consumer_prog:n1400, @consumer_prog:n1401, e24, @consumer_prog:n1600, @consumer_prog:n1601, e26, @consumer_prog:n1900, @consumer_prog:n1901, e28, @consumer_prog:n2200, @consumer_prog:n2201, e30, @consumer_prog:n2500, @consumer_prog:n2501, e32, @consumer_prog:n2800, @consumer_prog:n1100, @consumer_prog:n1200, @consumer_prog:n1300, @consumer_prog:n1500, @consumer_prog:n1700, @consumer_prog:n2000, @consumer_prog:n2300, @consumer_prog:n2600, @consumer_prog:n2801, e38, @consumer_prog:n2900
REGION 6 .. 7 : @consumer_prog:n600, @consumer_prog:n601
REGION 8 .. 9 : @consumer_prog, @consumer_prog:m0, e0, @consumer_prog:m1, @consumer_prog:m2, @consumer_prog:m3, @consumer_prog:m4, @consumer_prog:m5, @consumer_prog:n700, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, @consumer_prog:n500, e16, e17, e18, e19, e20, e21, @consumer_prog:n800, e22, @consumer_prog:n1800, e25, @consumer_prog:n2100, e27, @consumer_prog:n2400, e29, @consumer_prog:n2700, e31, @consumer_prog:n3700, e33, @consumer_prog:n4300, e39, @consumer_prog_entry, @consumer_prog_entry:m85, @consumer_prog_entry:m86, @consumer_prog_entry:m87, @consumer_prog_entry:m88, @consumer_prog_entry:m89, @consumer_prog_entry:m110
REGION 10 .. 11 : @consumer_prog_entry:consumer_prog_entry.0, @consumer_prog_entry:consumer_prog_entry.1, @consumer_prog_entry:n31600, e55, @consumer_prog_entry:n34000, e56, @consumer_prog_entry:n34300, e57, @consumer_prog_entry:n33700, e58, @consumer_prog_entry:n34600, e59, @consumer_prog_entry:n33400, e60, @consumer_prog_entry:n31400, e61, @consumer_prog_entry:n31800, e63, @consumer_prog_entry:m117, e62, @consumer_prog_entry:m126
REGION 12 .. 16 : @consumer_prog:consumer_prog.0
REGION 13 .. 14 : @consumer_prog:n200, e15, @consumer_prog:n300, @consumer_prog:n301, @consumer_prog:n302, @consumer_prog:n303, e23
REGION 15 .. 16 : @consumer_prog:n3000, e34, e35, e36, e37, @consumer_prog:n3100
REGION 17 .. 26 : @consumer_prog:consumer_prog.2
REGION 17 .. 30 : @consumer_prog:consumer_prog.1
REGION 18 .. 19 : @consumer_prog:n4800, e43, @consumer_prog:n6300, e45, @consumer_prog:n6100, e49
REGION 20 .. 21 : @consumer_prog:n3400, e42, @consumer_prog:m41, @consumer_prog:n3401, e44
REGION 22 .. 26 : @consumer_prog:n4200, e47
REGION 23 .. 26 : @consumer_prog:n3900, e40, e41, @consumer_prog:n4100, @consumer_prog:n5900, @consumer_prog:n5901, @consumer_prog:n5902, @consumer_prog:n5903, e50, e51
REGION 24 .. 26 : @consumer_prog:n4400
REGION 25 .. 26 : @consumer_prog:n3800, @consumer_prog:n3801, @consumer_prog:n3802, @consumer_prog:n3803, e46
REGION 27 .. 28 : @consumer_prog:n4500, @consumer_prog:n4501, e48
REGION 29 .. 30 : @consumer_prog:n4700
REGION 31 .. 40 : @consumer_prog:consumer_prog.3
REGION 32 .. 34 : @consumer_prog:n5300
REGION 33 .. 34 : @consumer_prog:n5200, @consumer_prog:n5201, @consumer_prog:n5202, @consumer_prog:n5203, e54
REGION 35 .. 36 : @consumer_prog:n5400
REGION 37 .. 38 : @consumer_prog:n5500
REGION 39 .. 40 : @consumer_prog:n21700, e52, @consumer_prog:n5600, e53
LOCATION 0 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":59,5
LOCATION 1 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":59,1000
LOCATION 2 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":60,5
LOCATION 3 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":60,1000
LOCATION 4 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":61,5
LOCATION 5 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":61,1000
LOCATION 6 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":75,5
LOCATION 7 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/cir_buf.hive.h":75,1000
LOCATION 8 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":18,0
LOCATION 9 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":18,1000
LOCATION 10 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":19,0
LOCATION 11 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":19,1000
LOCATION 12 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":20,0
LOCATION 13 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":20,21
LOCATION 14 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":20,1000
LOCATION 15 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":38,9
LOCATION 16 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":38,1000
LOCATION 17 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":42,0
LOCATION 18 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":42,3
LOCATION 19 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":42,1000
LOCATION 20 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":47,5
LOCATION 21 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":47,1000
LOCATION 22 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":48,6
LOCATION 23 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":48,30
LOCATION 24 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":48,34
LOCATION 25 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":48,36
LOCATION 26 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":48,1000
LOCATION 27 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":52,5
LOCATION 28 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":52,1000
LOCATION 29 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":53,5
LOCATION 30 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":53,1000
LOCATION 31 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":56,0
LOCATION 32 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":56,3
LOCATION 33 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":56,22
LOCATION 34 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":56,1000
LOCATION 35 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":57,3
LOCATION 36 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":57,1000
LOCATION 37 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":58,3
LOCATION 38 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":58,1000
LOCATION 39 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":59,1
LOCATION 40 = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c":59,1000
