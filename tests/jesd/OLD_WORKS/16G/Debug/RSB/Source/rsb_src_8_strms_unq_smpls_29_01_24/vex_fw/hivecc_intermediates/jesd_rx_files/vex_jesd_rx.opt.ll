; ModuleID = 'vex_jesd_rx.c'
target datalayout = "e-m:e-p:32:32-i64:32-v64:8"
target triple = "ve32"

@g_num_vecs_in = common global i32 0, section "addr:12", align 4
@g_tbs_in_blk = common global i32 0, section "addr:20", align 4
@g_host_indicator = common global i32 0, section "addr:32", align 4
@g_vex_exit = common global i32 0, section "addr:36", align 4
@g_timer_debug = common global i32 0, section "addr:40", align 4
@consumer_sm_gate = common global [16 x i32] zeroinitializer, align 128
@vbuffer_0 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_7 = common addrspace(3) global [128 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_out = common addrspace(3) global [256 x <32 x i32>] zeroinitializer, section "addr:16384", align 128

; Function Attrs: noinline nounwind uwtable
define void @jesd_rx() #0 {
entry:
  %0 = load volatile i32* @g_num_vecs_in, align 4, !dbg !23
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !24
  tail call void @llvm.ve32.printstring.md(i32 2), !dbg !25
  tail call void @llvm.ve32.mc.reset(i32 0) #3, !dbg !26, !intrin_attr !28
  %1 = load volatile i32* @g_tbs_in_blk, align 4, !dbg !29
  %add1.i = add i32 %1, 196608, !dbg !30
  tail call void @llvm.ve32.mc.init(i32 %add1.i, i32 0) #3, !dbg !30, !intrin_attr !28
  tail call void @llvm.ve32.mc.init.local.idc(i32 0, i32 0) #3, !dbg !31, !intrin_attr !32
  tail call void @llvm.ve32.printstring.md(i32 0), !dbg !33
  tail call void @llvm.ve32.dump(i32 0, i32 0) #3, !dbg !33
  tail call void @llvm.ve32.printstring.md(i32 1), !dbg !33
  %2 = tail call i32 @llvm.ve32.mc.get.state(i32 0, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 0, i32 %2) #3, !dbg !33
  %3 = tail call i32 @llvm.ve32.mc.get.state(i32 1, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 1, i32 %3) #3, !dbg !33
  %4 = tail call i32 @llvm.ve32.mc.get.state(i32 2, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 2, i32 %4) #3, !dbg !33
  %5 = tail call i32 @llvm.ve32.mc.get.state(i32 3, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 3, i32 %5) #3, !dbg !33
  %6 = tail call i32 @llvm.ve32.mc.get.state(i32 4, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 4, i32 %6) #3, !dbg !33
  %7 = tail call i32 @llvm.ve32.mc.get.state(i32 5, i32 0) #3, !dbg !33, !intrin_attr !35
  tail call void @llvm.ve32.dump(i32 5, i32 %7) #3, !dbg !33
  %8 = load volatile i32* @g_vex_exit, align 4, !dbg !36
  %cmp17 = icmp eq i32 %8, 0, !dbg !36
  br i1 %cmp17, label %while.body.lr.ph, label %while.end, !dbg !36

while.body.lr.ph:                                 ; preds = %entry
  %cmp114 = icmp sgt i32 %0, 0, !dbg !38
  br i1 %cmp114, label %for.body.lr.ph.us, label %for.end

for.end.us:                                       ; preds = %for.body.us
  %9 = tail call i32 @llvm.ve32.mc.complete(i32 0) #3, !dbg !43, !intrin_attr !32
  %10 = load volatile i32* @g_vex_exit, align 4, !dbg !36
  %cmp.us = icmp eq i32 %10, 0, !dbg !36
  br i1 %cmp.us, label %for.body.lr.ph.us, label %while.end.loopexit, !dbg !36

for.body.us:                                      ; preds = %for.body.lr.ph.us, %for.body.us
  %compare_offset.116.us = phi i32 [ %compare_offset.018.us, %for.body.lr.ph.us ], [ %12, %for.body.us ]
  %newindvar = phi i32 [ %14, %for.body.lr.ph.us ], [ %newindvar.dec, %for.body.us ]
  %11 = tail call { <32 x i32>, i32 } @llvm.ve32.v.ldoi.1024.circ(i32 16384, i32 %compare_offset.116.us, i32 134250368, i32 32640), !dbg !44, !intrin_attr !46, !no_alias !47
  %12 = extractvalue { <32 x i32>, i32 } %11, 1, !dbg !44
  %newindvar.dec = sub i32 %newindvar, 1, !dbg !38
  %13 = icmp eq i32 %newindvar, 0, !dbg !38
  br i1 %13, label %for.end.us, label %for.body.us, !dbg !38

for.body.lr.ph.us:                                ; preds = %for.end.us, %while.body.lr.ph
  %compare_offset.018.us = phi i32 [ %12, %for.end.us ], [ 0, %while.body.lr.ph ]
  %14 = add i32 %0, -1, !dbg !48
  %15 = tail call { i32, i32 } @llvm.ve32.mc.request(i32 1, i32 0), !dbg !48, !intrin_attr !49
  br label %for.body.us, !dbg !38

for.end:                                          ; preds = %for.end, %while.body.lr.ph
  %16 = tail call { i32, i32 } @llvm.ve32.mc.request(i32 1, i32 0), !dbg !48, !intrin_attr !49
  %17 = tail call i32 @llvm.ve32.mc.complete(i32 0) #3, !dbg !43, !intrin_attr !32
  %18 = load volatile i32* @g_vex_exit, align 4, !dbg !36
  %cmp = icmp eq i32 %18, 0, !dbg !36
  br i1 %cmp, label %for.end, label %while.end, !dbg !36

while.end.loopexit:                               ; preds = %for.end.us
  %19 = extractvalue { <32 x i32>, i32 } %11, 0, !dbg !44
  store <32 x i32> %19, <32 x i32> addrspace(3)* getelementptr inbounds ([128 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 0), align 128, !dbg !50
  br label %while.end

while.end:                                        ; preds = %while.end.loopexit, %for.end, %entry
  ret void, !dbg !51
}

; Function Attrs: nounwind readonly
declare { i32, i32 } @llvm.ve32.mc.request(i32, i32) #1

; Function Attrs: nounwind readonly
declare { <32 x i32>, i32 } @llvm.ve32.v.ldoi.1024.circ(i32, i32, i32, i32) #1

; Function Attrs: nounwind readnone
declare i32 @llvm.ve32.mc.complete(i32) #2

; Function Attrs: nounwind readonly
declare i32 @llvm.ve32.mc.get.state(i32, i32) #1

; Function Attrs: nounwind readnone
declare void @llvm.ve32.mc.init.local.idc(i32, i32) #2

; Function Attrs: nounwind
declare void @llvm.ve32.mc.init(i32, i32) #3

; Function Attrs: nounwind
declare void @llvm.ve32.mc.reset(i32) #3

; Function Attrs: nounwind
declare void @llvm.ve32.dump(i32, i32) #3

; Function Attrs: nounwind
declare void @llvm.ve32.printstring.md(i32) #3

; Function Attrs: nounwind
define void @jesd_rx_entry() #4 {
  tail call void @jesd_rx(), !dbg !52
  ret void, !dbg !53
}

attributes #0 = { noinline nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readonly }
attributes #2 = { nounwind readnone }
attributes #3 = { nounwind }
attributes #4 = { nounwind "ipu_entry" "no-frame-pointer-elim"="true" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!12, !13}
!ipu.register_structs_list = !{!2}
!llvm.ident = !{!14}
!ipu.inststrings.strings = !{!15, !16, !17}
!ipu_stack_base = !{!18}
!volcano.source.file = !{!19}
!volcano.command.line = !{!20}
!volcano.machine.path = !{!21}
!volcano.machine.name = !{!22}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 ", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 2} ; [ DW_TAG_compile_unit ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c] [DW_LANG_C99]
!1 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !7, metadata !10, metadata !11}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_rx", metadata !"jesd_rx", metadata !"", i32 104, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_rx, null, null, metadata !2, i32 105} ; [ DW_TAG_subprogram ] [line 104] [def] [scope 105] [jesd_rx]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !2, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{i32 786478, metadata !8, metadata !9, metadata !"circ_buff_init", metadata !"circ_buff_init", metadata !"", i32 60, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !2, i32 61} ; [ DW_TAG_subprogram ] [line 60] [def] [scope 61] [circ_buff_init]
!8 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64"}
!9 = metadata !{i32 786473, metadata !8}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h]
!10 = metadata !{i32 786478, metadata !8, metadata !9, metadata !"semaphore_gate_init", metadata !"semaphore_gate_init", metadata !"", i32 92, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, null, null, null, metadata !2, i32 93} ; [ DW_TAG_subprogram ] [line 92] [def] [scope 93] [semaphore_gate_init]
!11 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_rx_entry", metadata !"jesd_rx_entry", metadata !"", i32 104, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_rx_entry, metadata !2, null, metadata !2, i32 105} ; [ DW_TAG_subprogram ] [line 104] [def] [scope 105] [jesd_rx_entry]
!12 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!13 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!14 = metadata !{metadata !"clang version 3.5.0 "}
!15 = metadata !{metadata !"fu mc_get_state{1,2,3} idx="}
!16 = metadata !{metadata !"{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\0A"}
!17 = metadata !{metadata !"jesd_tx : start \0A"}
!18 = metadata !{void ()* @jesd_rx_entry, i32 16384}
!19 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c"}
!20 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.stubs.h --o-optimized-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.opt.ll --o-clang-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.clang.ll -emit-after-pp /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw -I. -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/hrt/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/common/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/host/include -o-dot-s /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.s -DVOLCANO=1 -o /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_rx_files/vex_jesd_rx.o "}
!21 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"}
!22 = metadata !{metadata !"ve32"}
!23 = metadata !{i32 106, i32 5, metadata !4, null}
!24 = metadata !{i32 111, i32 5, metadata !4, null}
!25 = metadata !{i32 113, i32 5, metadata !4, null}
!26 = metadata !{i32 95, i32 5, metadata !10, metadata !27}
!27 = metadata !{i32 115, i32 5, metadata !4, null}
!28 = metadata !{metadata !"WRITE_STATE"}
!29 = metadata !{i32 125, i32 5, metadata !4, null}
!30 = metadata !{i32 78, i32 5, metadata !7, metadata !29}
!31 = metadata !{i32 79, i32 5, metadata !7, metadata !29}
!32 = metadata !{metadata !"WRITE_STATE", metadata !"READ_STATE"}
!33 = metadata !{i32 80, i32 5, metadata !34, metadata !29}
!34 = metadata !{i32 786443, metadata !8, metadata !7, i32 80, i32 5, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h]
!35 = metadata !{metadata !"READ_STATE"}
!36 = metadata !{i32 128, i32 5, metadata !37, null}
!37 = metadata !{i32 786443, metadata !1, metadata !4, i32 128, i32 5, i32 1, i32 4} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!38 = metadata !{i32 135, i32 14, metadata !39, null}
!39 = metadata !{i32 786443, metadata !1, metadata !40, i32 135, i32 14, i32 2, i32 6} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!40 = metadata !{i32 786443, metadata !1, metadata !41, i32 135, i32 14, i32 1, i32 5} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!41 = metadata !{i32 786443, metadata !1, metadata !42, i32 135, i32 9, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!42 = metadata !{i32 786443, metadata !1, metadata !4, i32 129, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!43 = metadata !{i32 145, i32 3, metadata !42, null}
!44 = metadata !{i32 139, i32 11, metadata !45, null}
!45 = metadata !{i32 786443, metadata !1, metadata !41, i32 136, i32 9, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!46 = metadata !{metadata !"SYNC_WITH:0"}
!47 = metadata !{metadata !"no_alias"}
!48 = metadata !{i32 133, i32 9, metadata !42, null}
!49 = metadata !{metadata !"SYNC:0", metadata !"WRITE_STATE", metadata !"READ_STATE"}
!50 = metadata !{i32 141, i32 11, metadata !45, null}
!51 = metadata !{i32 151, i32 1, metadata !4, null}
!52 = metadata !{i32 104, i32 0, metadata !11, null}
!53 = metadata !{i32 151, i32 1, metadata !11, null}
