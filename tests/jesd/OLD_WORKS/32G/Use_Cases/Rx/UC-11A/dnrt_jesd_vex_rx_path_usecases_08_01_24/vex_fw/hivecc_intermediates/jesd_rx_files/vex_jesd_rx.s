source_file "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c"
command "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.stubs.h --o-optimized-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.opt.ll --o-clang-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.clang.ll -emit-after-pp /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw -I. -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/hrt/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/common/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/host/include -o-dot-s /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.s -DVOLCANO=1 -o /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.o "
machine.name "ve32"
machine.path "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"
@jesd_rx()
{
frame bp_dmem
  size = 16
  inputs_size = 0
  locals_size = 4
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 12
frame simd0_vmem
  size = 0
  inputs_size = 0
  locals_size = 0
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 0
pragma $type-splitting=1
schedule(jesd_rx.0)
  dtree jesd_rx.0
  successors : 0=jesd_rx.1[] : 1=jesd_rx.7[] ;
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
  n6700: s_imm_u #@g_num_vecs_in => e1 ;
    units (simd0_vlsu0_spsu )
  }
  cycle 1: {
  n6800: s_ldo_32_i_PIPE_0_3 e1[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[3]] #0 => ;
    units (bp_s1_lsu_dm )
    succpipeop(n6801);
  n7000: s_imm_u #@g_vex_exit => split(e2,e3,e4,e5) ;
    units (simd0_vcom0_spsu )
    critical
  n6900: s_imm #0 => split(e6,e7,e8,e9,e10,e11,e12,e13,e14,e15,e16,e17,e18,e19) ;
    units (bp_s0_psu )
  }
  cycle 2: {
  n6801: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n6802);
  n7400: s_imm_u #@g_tbs_in_blk => e20 ;
    units (simd0_vlsu1_spsu )
  n7100: s_sto_32_i e2[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[2]] #0 e6[hard bp_s0_op0_BUS->bp_rf1_wp1->bp_rf1[4]] => ;
    units (bp_s1_lsu_dm )
    critical
  n7300: mc_reset_PIPE_0_1 e7[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    critical
    succpipeop(n7301);
  }
  cycle 3: {
  n6802: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    succpipeop(n6803);
  n7500: s_ldo_32_i_PIPE_0_3 e20[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[31]] #0 => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n7501);
  n7301: mc_reset_PIPE_1_1  => ;
    units (bp_s2_tsu )
    critical
  }
  cycle 4: {
  n6803: s_ldo_32_i_PIPE_3_3  => split(e21,e22) ;
    units (bp_s1_lsu_dm )
  n7501: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n7502);
  }
  cycle 5: {
  n7502: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n7503);
  n7600: s_immh #3 e8[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[1]] => e23 ;
    units (simd0_vlsu0_spsu )
  }
  cycle 6: {
  n7503: s_ldo_32_i_PIPE_3_3  => e24 ;
    units (bp_s1_lsu_dm )
    critical
  }
  cycle 7: {
  n7700: s_add e24[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[1]] e23[hard simd_2_bp_op0_BUS->bp_rf0_wp0->bp_rf0[2]] => e25 ;
    units (bp_s0_aru )
    critical
  }
  cycle 8: {
  n7800: mc_init_PIPE_0_1 e25[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e9[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    critical
    succpipeop(n7801);
  }
  cycle 9: {
  n8800: s_imm #2 => e26 ;
    units (simd0_vcom0_spsu )
  n7801: mc_init_PIPE_1_1  => ;
    units (bp_s2_tsu )
    critical
  n7900: mc_init_local_idc e10[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] e11[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
  }
  cycle 10: {
  n8900: mc_get_state_PIPE_0_1 e26[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[2]] e12[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n8901);
  n10100: s_ldo_32_i_PIPE_0_3 e3[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[2]] #0 => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n10101);
  n9700: s_imm #5 => e27 ;
    units (bp_s0_psu )
  }
  cycle 11: {
  n8901: mc_get_state_PIPE_1_1  => e28 ;
    units (bp_s2_tsu )
  n9800: mc_get_state_PIPE_0_1 e27[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[15]] e13[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n9801);
  n10101: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n10102);
  n9400: s_imm #4 => e29 ;
    units (simd0_vlsu0_spsu )
  }
  cycle 12: {
  n9801: mc_get_state_PIPE_1_1  => e30 ;
    units (bp_s2_tsu )
  n8300: mc_get_state_PIPE_0_1 e14[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] e15[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n8301);
  n10102: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n10103);
  n9100: s_imm #3 => e31 ;
    units (simd0_vlsu1_spsu )
  }
  cycle 13: {
  n8301: mc_get_state_PIPE_1_1  => e32 ;
    units (bp_s2_tsu )
  n9500: mc_get_state_PIPE_0_1 e29[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[14]] e16[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n9501);
  n10103: s_ldo_32_i_PIPE_3_3  => e33 ;
    units (bp_s1_lsu_dm )
    critical
  n8500: s_imm #1 => split(e34,e35,e36) ;
    units (bp_s0_psu )
  }
  cycle 14: {
  n9501: mc_get_state_PIPE_1_1  => e37 ;
    units (bp_s2_tsu )
  n9200: mc_get_state_PIPE_0_1 e31[hard simd_2_bp_op0_BUS->bp_rf2_wp0->bp_rf2[3]] e17[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n9201);
  n15800: s_jmpnz_i #jesd_rx.7 e33[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[31]] => e38 ;
    units (bp_s0_bru )
    critical
  }
  cycle 15: {
  n9201: mc_get_state_PIPE_1_1  => e39 ;
    units (bp_s2_tsu )
  n8600: mc_get_state_PIPE_0_1 e34[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e18[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n8601);
  }
  cycle 16: {
  n8601: mc_get_state_PIPE_1_1  => e40 ;
    units (bp_s2_tsu )
  }
  cycle 17: {
  n7200: %PRINTSTRING<X:8:1> "jesd_tx : start \n" => ;
  n8000: %PRINTSTRING<X:8:1> "fu mc_get_state{1,2,3} idx=" => ;
  n8100: %DUMP<S:32:1> #0 e19 => ;
  n8200: %PRINTSTRING<X:8:1> "{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\n" => ;
  n38900: s_pass e0[hard bp_rf1[1]] => e41 ;
    units (bp_s1_psu )
  n8400: %DUMP<S:32:1> #0 e32 => ;
  n8700: %DUMP<S:32:1> #1 e40 => ;
  n9000: %DUMP<S:32:1> #2 e28 => ;
  n9300: %DUMP<S:32:1> #3 e39 => ;
  n9600: %DUMP<S:32:1> #4 e37 => ;
  n9900: %DUMP<S:32:1> #5 e30 => ;
  m51: %writereg<X:32:1> bp_pc[0] e38[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(1) ;
  else goto successor(0);
schedule(jesd_rx.1)
  dtree jesd_rx.1
  successors : 0=jesd_rx.9[] : 1=jesd_rx.5[] ;
  view ve32
  comment "LLVM BB name: while.body.lr.ph"
  cycle 18: {
  n10600: s_le_i e21[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[0]] #0 => e42 ;
    units (bp_s0_aru )
    critical
  }
  cycle 19: {
  n15600: s_jmpnz_i #jesd_rx.5 e42[hard bp_s0_op0_BUS->bp_rf0_wp0->bp_rf0[3]] => e43 ;
    units (bp_s0_bru )
    critical
  }
  cycle 20: {
  }
  cycle 21: {
  }
  cycle 22: {
  n10400: s_imm #0 => split(e44,e45,e46,e47,e48) ;
    units (bp_s1_psu )
  m62: %writereg<X:32:1> bp_pc[0] e43[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(1) ;
  else goto successor(0);
schedule(jesd_rx.9)
  dtree jesd_rx.9
  successors : 0=jesd_rx.4[] ;
  view ve32
  comment "LLVM BB name: (null)"
  cycle 23: {
  n39200: s_pass e44[hard bp_s1_op0_BUS->bp_rf0_wp0->bp_rf0[2]] => e49 ;
    units (bp_s0_psu )
  n12800: s_imm #32640 => split(e50,e51) ;
    units (simd0_vlsu0_spsu )
    critical
  }
  cycle 24: {
  n13000: s_imm #16384 => e52 ;
    units (bp_s1_psu )
  n12900: s_immh #2048 e50[hard simd_2_bp_op0_BUS->bp_rf0_wp0->bp_rf0[3]] => e53 ;
    units (bp_s0_psu )
    critical
  }
  goto successor(0) fallthru ;
schedule(jesd_rx.4)
  dtree jesd_rx.4
  successors : 0=jesd_rx.3[] ;
  view ve32
  comment "LLVM BB name: for.body.lr.ph.us"
  cycle 25: {
  m73: %readreg<X:32:1> bp_rf1[6] => ;
    read
  n12200: mc_request_PIPE_0_1 e35[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e45[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => e54 ;
    units (bp_s2_tsu )
    critical
    synchronize
    sync_with s0
    succpipeop(n12201);
  }
  cycle 26: {
  n12201: mc_request_PIPE_1_1  => e55 ;
    units (bp_s2_tsu )
    critical
  n12500: s_sub_i e22[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[0]] #1 => e56 ;
    units (bp_s0_aru )
  }
  goto successor(0) fallthru ;
schedule(jesd_rx.3)
  dtree jesd_rx.3
  successors : 0=jesd_rx.2[] : 1=jesd_rx.3[back] ;
  view ve32
  comment "LLVM BB name: for.body.us"
  cycle 27: {
  n39500: s_pass join(e56[hard bp_s0_op0_BUS->bp_rf0_wp0->bp_rf0[2]],e63 back[hard bp_s0_op0_BUS->bp_rf0_wp0->bp_rf0[2]]) => split(e57,e58) ;
    units (bp_s0_psu )
    critical
  }
  cycle 28: {
  n13100: v_ldoi_1024_circ_PIPE_0_3 e52[hard bp_2_simd_op1_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[2]] join(e59 back[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[4]],e60 back[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[4]],e49[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[4]]) e53[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[5]] e51[hard simd0_vlsu0_op0_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[1]] => split(e59,e60) ;
    units (simd0_vlsu0_vlsu )
    sync_with s0
    succpipeop(n13101);
  n16100: s_jmpnz_i #jesd_rx.3 e57[hard bp_s0_op0_BUS->bp_rf0_wp1->bp_rf0[3]] => e61 ;
    units (bp_s0_bru )
    critical
  }
  cycle 29: {
  n13101: v_ldoi_1024_circ_PIPE_1_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n13102);
  }
  cycle 30: {
  n13102: v_ldoi_1024_circ_PIPE_2_3  => ;
    units (simd0_vlsu0_vlsu )
    succpipeop(n13103);
  }
  cycle 31: {
  n13103: v_ldoi_1024_circ_PIPE_3_3  => e62 ;
    units (simd0_vlsu0_vlsu )
  n13500: s_sub_i e58[hard bp_s0_op0_BUS->bp_rf0_wp1->bp_rf0[3]] #1 => e63 ;
    units (bp_s0_aru )
  m89: %writereg<X:32:1> bp_pc[0] e61[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(1) ;
  else goto successor(0);
schedule(jesd_rx.2)
  dtree jesd_rx.2
  successors : 0=jesd_rx.4[back] : 1=jesd_rx.6[] ;
  view ve32
  comment "LLVM BB name: for.end.us"
  cycle 32: {
  m90: %readreg<X:32:1> bp_rf1[6] => ;
    read
  n14300: s_ldo_32_i_PIPE_0_3 e4[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[2]] #0 => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n14301);
  }
  cycle 33: {
  n14301: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n14302);
  }
  cycle 34: {
  n14302: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n14303);
  }
  cycle 35: {
  n14303: s_ldo_32_i_PIPE_3_3  => e64 ;
    units (bp_s1_lsu_dm )
    critical
  }
  cycle 36: {
  n16200: s_jmpz_i #jesd_rx.4 e64[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[2]] => e65 ;
    units (bp_s0_bru )
    critical
  }
  cycle 37: {
  }
  cycle 38: {
  n14000: mc_complete_PIPE_0_1 e46[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n14001);
  }
  cycle 39: {
  n14001: mc_complete_PIPE_1_1  => e66 ;
    units (bp_s2_tsu )
  m98: %writereg<X:32:1> bp_pc[0] e65[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(1) ;
  else goto successor(0);
schedule(jesd_rx.6)
  dtree jesd_rx.6
  successors : 0=jesd_rx.7[] ;
  view ve32
  comment "LLVM BB name: while.end.loopexit"
  cycle 40: {
  n16300: s_jmp_i #jesd_rx.7 => e67 ;
    units (bp_s0_bru )
    critical
  }
  cycle 41: {
  }
  cycle 42: {
  n14600: s_imm_u #@vbuffer_7 => e68 ;
    units (bp_s0_psu )
  }
  cycle 43: {
  n14700: v_sto_1024_i e68[hard bp_2_simd_op0_BUS->simd0_vlsu0_srf0_ip1->simd0_vlsu0_srf0[1]] #0 e62[hard simd0_vlsu0_vop0_BUS->simd0_vlsu0_vrf0_ip0->simd0_vlsu0_vrf0[0]] => ;
    units (simd0_vlsu0_vlsu )
  m106: %writereg<X:32:1> bp_pc[0] e67[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  goto successor(0);
schedule(jesd_rx.5)
  dtree jesd_rx.5
  successors : 0=jesd_rx.5[back] : 1=jesd_rx.7[] ;
  view ve32
  comment "LLVM BB name: for.end"
  cycle 44: {
  m107: %readreg<X:32:1> bp_rf1[6] => ;
    read
  n11700: s_ldo_32_i_PIPE_0_3 e5[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[2]] #0 => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n11701);
  }
  cycle 45: {
  n11701: s_ldo_32_i_PIPE_1_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n11702);
  }
  cycle 46: {
  n11702: s_ldo_32_i_PIPE_2_3  => ;
    units (bp_s1_lsu_dm )
    critical
    succpipeop(n11703);
  }
  cycle 47: {
  n11703: s_ldo_32_i_PIPE_3_3  => e69 ;
    units (bp_s1_lsu_dm )
    critical
  }
  cycle 48: {
  n16400: s_jmpz_i #jesd_rx.5 e69[hard bp_s1_op1_BUS->bp_rf0_wp0->bp_rf0[0]] => e70 ;
    units (bp_s0_bru )
    critical
  }
  cycle 49: {
  n11100: mc_request_PIPE_0_1 e36[hard bp_s0_op0_BUS->bp_rf2_wp0->bp_rf2[0]] e47[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => e71 ;
    units (bp_s2_tsu )
    synchronize
    sync_with s0
    succpipeop(n11101);
  }
  cycle 50: {
  n11101: mc_request_PIPE_1_1  => e72 ;
    units (bp_s2_tsu )
  n11400: mc_complete_PIPE_0_1 e48[hard bp_s1_op0_BUS->bp_rf2_wp0->bp_rf2[1]] => ;
    units (bp_s2_tsu )
    succpipeop(n11401);
  }
  cycle 51: {
  n11401: mc_complete_PIPE_1_1  => e73 ;
    units (bp_s2_tsu )
  m115: %writereg<X:32:1> bp_pc[0] e70[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  if () goto successor(1) ;
  else goto successor(0);
schedule(jesd_rx.7)
  dtree jesd_rx.7
  view ve32
  comment "LLVM BB name: while.end"
  cycle 52: {
  n14800: s_jmp e41[hard bp_s1_op0_BUS->bp_rf0_wp1->bp_rf0[1]] => e74 ;
    units (bp_s0_bru )
    critical
  }
  cycle 53: {
  }
  cycle 54: {
  }
  cycle 55: {
  m121: %writereg<X:32:1> bp_pc[0] e74[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  }
  return;
}
@jesd_rx_entry()
{
  entry
frame bp_dmem
  size = 16
  inputs_size = 0
  locals_size = 4
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 12
frame simd0_vmem
  size = 0
  inputs_size = 0
  locals_size = 0
  callee_spill_size = 0
  caller_spill_size = 0
  arguments_size = 0
pragma $type-splitting=1
schedule(jesd_rx_entry.0)
  dtree jesd_rx_entry.0
  successors : 0=jesd_rx_entry.1[] ;
  view ve32
  comment "LLVM BB name: "
  cycle 0: {
  m122: %readreg<X:32:1> bp_rf1[0] => ;
    read
  m123: %readreg<X:32:1> simd0_vlsu0_srf0[0] => ;
    read
  m124: %readreg<X:32:1> bp_rf1[6] => ;
    read
  m125: %readreg<X:32:1> simd0_vlsu0_srf0[3] => ;
    read
  m126: %readreg<X:32:1> simd0_vlsu1_srf0[0] => ;
    read
  n2400: s_imm_u #1 => e75 ;
    units (bp_s1_psu )
  }
  cycle 1: {
  n2700: s_imm_u #1 => e76 ;
    units (bp_s1_psu )
  }
  cycle 2: {
  n3000: s_imm_u #16384 => e77 ;
    units (bp_s1_psu )
  n400: s_jmp_i #@jesd_rx => e78 ;
    units (bp_s0_bru )
    critical
  }
  cycle 3: {
  n2100: s_imm_u #1 => e79 ;
    units (bp_s1_psu )
  }
  cycle 4: {
  n3300: s_imm_u #65536 => e80 ;
    units (bp_s1_psu )
  }
  cycle 5: {
  n200: s_imm_u #jesd_rx_entry.1 => e81 ;
    units (simd0_vcom0_spsu )
  n3600: s_sub_i e77[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[0]] #16 => e82 ;
    units (bp_s1_aru )
  m146: %writereg<X:32:1> bp_rf1[1] e81[hard simd_2_bp_op0_BUS->bp_rf1_wp0->bp_rf1[1]] => ;
    write
  m147: %writereg<X:32:1> simd0_vlsu0_srf0[3] e75[hard bp_2_simd_op1_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[3]] => ;
    write
  m148: %writereg<X:32:1> simd0_vlsu1_srf0[0] e76[hard bp_2_simd_op1_BUS->simd0_vlsu1_srf0_ip0->simd0_vlsu1_srf0[0]] => ;
    write
  m149: %writereg<X:32:1> bp_pc[0] e78[hard bp_s0_pc_BUS->bp_pc_wp->bp_pc[0]] => ;
    write
  m150: %writereg<X:32:1> bp_rf1[6] e79[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[6]] => ;
    write
  m151: %writereg<X:32:1> simd0_vlsu0_srf0[0] e80[hard bp_2_simd_op1_BUS->simd0_vlsu0_srf0_ip0->simd0_vlsu0_srf0[0]] => ;
    write
  }
  call[] #@jesd_rx;
  goto successor(0) fallthru ;
schedule(jesd_rx_entry.1)
  dtree jesd_rx_entry.1
  view ve32
  comment "LLVM BB name: "
  cycle 6: {
  m152: %readreg<X:32:1> bp_cr[0] => e83 ;
    read
  n600: s_idle e83[hard bp_cr[0]] => e84 ;
    units (bp_s0_suu )
    critical
  }
  cycle 7: {
  }
  cycle 8: {
  }
  cycle 9: {
  n3900: s_add_i e82[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[0]] #16 => e85 ;
    units (bp_s1_aru )
  m158: %writereg<X:32:1> bp_cr[0] e84[hard bp_s0_cr_BUS->bp_cr_wp->bp_cr[0]] => ;
    write
  m159: %writereg<X:32:1> bp_rf1[0] e85[hard bp_s1_op0_BUS->bp_rf1_wp1->bp_rf1[0]] => ;
    write
  }
  return;
}
memory bp_dmem {
0xc    :global @g_num_vecs_in size=4 align=4 ;
0x14    :global @g_tbs_in_blk size=4 align=4 ;
0x20    :global @g_host_indicator size=4 align=4 ;
0x24    :global @g_vex_exit size=4 align=4 ;
0x28    :global @g_timer_debug size=4 align=4 ;
global @consumer_sm_gate size=64 align=128 ;
};
memory simd0_vmem {
0x0    :global @vbuffer_0 size=8192 align=128 ;
0xc000    :global @vbuffer_7 size=16384 align=128 ;
0x4000    :global @vbuffer_out size=32768 align=128 ;
};
REGION 0 .. 1 : @jesd_rx_entry, @jesd_rx_entry:jesd_rx_entry.0, @jesd_rx_entry:m122, @jesd_rx_entry:m123, @jesd_rx_entry:m124, @jesd_rx_entry:m125, @jesd_rx_entry:m126, @jesd_rx_entry:n2400, e75, @jesd_rx_entry:n2700, e76, @jesd_rx_entry:n3000, e77, @jesd_rx_entry:n400, e78, @jesd_rx_entry:n2100, e79, @jesd_rx_entry:n3300, e80, @jesd_rx_entry:n200, e81, @jesd_rx_entry:n3600, e82, @jesd_rx_entry:m146, @jesd_rx_entry:n3900, e85, @jesd_rx, @jesd_rx:m0, e0, @jesd_rx:m1, @jesd_rx:m2, @jesd_rx:m3, @jesd_rx:m4, @jesd_rx:m5, @jesd_rx:n6900, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, e16, e17, e18, e19, @jesd_rx:n7600, e23, @jesd_rx:n8800, e26, @jesd_rx:n9700, e27, @jesd_rx:n9400, e29, @jesd_rx:n9100, e31, @jesd_rx:n8500, e34, e35, e36, @jesd_rx:n15800, e38, @jesd_rx:n38900, e41, @jesd_rx:n10600, e42, @jesd_rx:n15600, e43, @jesd_rx:n10400, e44, e45, e46, e47, e48, @jesd_rx:n39200, e49, @jesd_rx:n12800, e50, e51, @jesd_rx:n13000, e52, @jesd_rx:n12900, e53, @jesd_rx:n39500, e57, e58, @jesd_rx:n16100, e61, @jesd_rx:n16200, e65, @jesd_rx:n16300, e67, @jesd_rx:n16400, e70
REGION 0 .. 31 : @jesd_rx_entry:jesd_rx_entry.1
REGION 2 .. 15 : @jesd_rx:jesd_rx.0
REGION 3 .. 4 : @jesd_rx:n6700, e1, @jesd_rx:n6800, @jesd_rx:n6801, @jesd_rx:n6802, @jesd_rx:n6803, e21, e22
REGION 5 .. 6 : @jesd_rx:n7000, e2, e3, e4, e5, @jesd_rx:n7100
REGION 7 .. 8 : @jesd_rx:n7200
REGION 9 .. 10 : @jesd_rx:n7300, @jesd_rx:n7301
REGION 11 .. 12 : @jesd_rx:n7400, e20, @jesd_rx:n7500, @jesd_rx:n7501, @jesd_rx:n7502, @jesd_rx:n7503, e24, @jesd_rx:n7700, e25, @jesd_rx:n7800, @jesd_rx:n7801, @jesd_rx:n7900, @jesd_rx:n8900, @jesd_rx:n8901, e28, @jesd_rx:n9800, @jesd_rx:n9801, e30, @jesd_rx:n8300, @jesd_rx:n8301, e32, @jesd_rx:n9500, @jesd_rx:n9501, e37, @jesd_rx:n9200, @jesd_rx:n9201, e39, @jesd_rx:n8600, @jesd_rx:n8601, e40, @jesd_rx:n8000, @jesd_rx:n8100, @jesd_rx:n8200, @jesd_rx:n8400, @jesd_rx:n8700, @jesd_rx:n9000, @jesd_rx:n9300, @jesd_rx:n9600, @jesd_rx:n9900
REGION 13 .. 28 : @jesd_rx:jesd_rx.2, @jesd_rx:jesd_rx.5
REGION 14 .. 15 : @jesd_rx:n10100, @jesd_rx:n10101, @jesd_rx:n10102, @jesd_rx:n10103, e33, @jesd_rx:n14300, @jesd_rx:n14301, @jesd_rx:n14302, @jesd_rx:n14303, e64, @jesd_rx:n11700, @jesd_rx:n11701, @jesd_rx:n11702, @jesd_rx:n11703, e69
REGION 16 .. 18 : @jesd_rx:jesd_rx.4
REGION 17 .. 18 : @jesd_rx:n12200, e54, @jesd_rx:m73, @jesd_rx:n12500, e56, @jesd_rx:n12201, e55, @jesd_rx:n11100, e71, @jesd_rx:m107, @jesd_rx:n11101, e72
REGION 19 .. 23 : @jesd_rx:jesd_rx.3
REGION 20 .. 21 : @jesd_rx:n13500, e63
REGION 22 .. 23 : @jesd_rx:n13100, e59, e60, @jesd_rx:n13101, @jesd_rx:n13102, @jesd_rx:n13103, e62
REGION 24 .. 26 : @jesd_rx:jesd_rx.6
REGION 25 .. 26 : @jesd_rx:n14600, e68, @jesd_rx:n14700
REGION 27 .. 28 : @jesd_rx:n14000, @jesd_rx:m90, @jesd_rx:n14001, e66, @jesd_rx:n11400, @jesd_rx:n11401, e73
REGION 29 .. 31 : @jesd_rx:jesd_rx.7
REGION 30 .. 31 : @jesd_rx_entry:n600, e84, @jesd_rx_entry:m152, e83, @jesd_rx_entry:m158, @jesd_rx:n14800, e74
LOCATION 0 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":104,0
LOCATION 1 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":104,1000
LOCATION 2 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":106,0
LOCATION 3 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":106,5
LOCATION 4 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":106,1000
LOCATION 5 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":111,5
LOCATION 6 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":111,1000
LOCATION 7 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":113,5
LOCATION 8 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":113,1000
LOCATION 9 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":115,5
LOCATION 10 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":115,1000
LOCATION 11 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":125,5
LOCATION 12 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":125,1000
LOCATION 13 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":128,0
LOCATION 14 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":128,5
LOCATION 15 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":128,1000
LOCATION 16 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":133,0
LOCATION 17 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":133,9
LOCATION 18 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":133,1000
LOCATION 19 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":135,0
LOCATION 20 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":135,14
LOCATION 21 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":135,1000
LOCATION 22 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":139,11
LOCATION 23 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":139,1000
LOCATION 24 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":141,0
LOCATION 25 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":141,11
LOCATION 26 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":141,1000
LOCATION 27 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":145,3
LOCATION 28 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":145,1000
LOCATION 29 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":151,0
LOCATION 30 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":151,1
LOCATION 31 = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c":151,1000
