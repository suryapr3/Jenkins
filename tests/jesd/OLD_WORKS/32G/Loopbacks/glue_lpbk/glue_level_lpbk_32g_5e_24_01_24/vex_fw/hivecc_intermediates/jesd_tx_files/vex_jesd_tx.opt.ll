; ModuleID = 'vex_jesd_tx.c'
source_filename = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c"
target datalayout = "e-m:e-p:32:32-i64:32-n32"
target triple = "ve32"

@vbuffer_0 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_1 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:8192", align 128
@vbuffer_2 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:16384", align 128
@vbuffer_3 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:24576", align 128
@vbuffer_4 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:32768", align 128
@vbuffer_5 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:40960", align 128
@vbuffer_6 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_7 = dso_local local_unnamed_addr addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:57344", align 128
@g_dest_buffer0_base = dso_local global i32 0, section "addr:0", align 4
@g_dest_buffer1_base = dso_local global i32 0, section "addr:4", align 4
@g_dest_buffer2_base = dso_local global i32 0, section "addr:8", align 4
@g_dest_buffer3_base = dso_local global i32 0, section "addr:12", align 4
@g_dest_buffer4_base = dso_local global i32 0, section "addr:16", align 4
@g_dest_buffer5_base = dso_local global i32 0, section "addr:20", align 4
@g_dest_buffer6_base = dso_local global i32 0, section "addr:24", align 4
@g_dest_buffer7_base = dso_local global i32 0, section "addr:28", align 4
@g_host_indicator = dso_local global i32 0, section "addr:32", align 4
@g_vex_exit = dso_local global i32 0, section "addr:36", align 4
@g_timer_debug = dso_local global i32 0, section "addr:40", align 4
@g_debug = dso_local global i32 0, section "addr:44", align 4
@g_timeout_cycles = dso_local global i32 0, section "addr:48", align 4

; Function Attrs: noinline nounwind uwtable
define dso_local void @jesd_tx() local_unnamed_addr #0 !dbg !14 {
entry:
  store volatile i32 0, i32* @g_host_indicator, align 4, !dbg !17
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !18
  call void @llvm.ve32.printstring.md(i32 0), !dbg !19, !intrin_attr !20
  %0 = load volatile i32, i32* @g_timeout_cycles, align 4, !dbg !21
  call void @llvm.ve32.s.xsto.32(i32 0, i32 3, i32 3) #4, !dbg !22
  call void @llvm.ve32.s.xsto.32(i32 0, i32 4, i32 %0) #4, !dbg !25
  call void @llvm.ve32.s.xsto.32(i32 0, i32 6, i32 1) #4, !dbg !26
  call void @llvm.ve32.s.xsto.32(i32 0, i32 7, i32 16424) #4, !dbg !27
  call void @llvm.ve32.s.xsto.32(i32 0, i32 8, i32 -559038737) #4, !dbg !28
  br label %while.cond, !dbg !29

while.cond:                                       ; preds = %while.cond, %entry
  %1 = load volatile i32, i32* @g_host_indicator, align 4, !dbg !30
  %cmp = icmp eq i32 %1, 0, !dbg !31
  br i1 %cmp, label %while.cond, label %while.end, !dbg !29, !llvm.loop !32

while.end:                                        ; preds = %while.cond
  call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 1), !dbg !35
  %2 = load volatile i32, i32* @g_vex_exit, align 4, !dbg !36
  %cmp222 = icmp eq i32 %2, 0, !dbg !37
  br i1 %cmp222, label %for.cond.preheader, label %while.end37, !dbg !38

while.cond1.loopexit:                             ; preds = %while.end32
  %3 = load volatile i32, i32* @g_vex_exit, align 4, !dbg !36
  %cmp2 = icmp eq i32 %3, 0, !dbg !37
  br i1 %cmp2, label %for.cond.preheader, label %while.end37, !dbg !38, !llvm.loop !39

for.cond.preheader:                               ; preds = %while.end, %while.cond1.loopexit
  br label %for.cond5.preheader, !dbg !41

for.cond5.preheader:                              ; preds = %for.cond.preheader, %while.end32
  %i.020 = phi i32 [ 0, %for.cond.preheader ], [ %inc35, %while.end32 ]
  %newindvar = phi i32 [ 31, %for.cond.preheader ], [ %newindvar.dec, %while.end32 ]
  %mul = shl nuw i32 %i.020, 1, !dbg !42
  %4 = load volatile i32, i32* @g_dest_buffer0_base, align 4, !dbg !42
  %arrayidx = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_0, i32 0, i32 %mul, !dbg !42
  %5 = bitcast <32 x i32> addrspace(3)* %arrayidx to <128 x i8> addrspace(3)*, !dbg !42
  %6 = load <128 x i8>, <128 x i8> addrspace(3)* %5, align 128, !dbg !42
  call void @llvm.ve32.v.xsto.1024.i(i32 %4, i32 0, <128 x i8> %6), !dbg !42
  %7 = load volatile i32, i32* @g_dest_buffer1_base, align 4, !dbg !43
  %arrayidx10 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_1, i32 0, i32 %mul, !dbg !43
  %8 = bitcast <32 x i32> addrspace(3)* %arrayidx10 to <128 x i8> addrspace(3)*, !dbg !43
  %9 = load <128 x i8>, <128 x i8> addrspace(3)* %8, align 128, !dbg !43
  call void @llvm.ve32.v.xsto.1024.i(i32 %7, i32 0, <128 x i8> %9), !dbg !43
  %10 = load volatile i32, i32* @g_dest_buffer2_base, align 4, !dbg !44
  %arrayidx13 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_2, i32 0, i32 %mul, !dbg !44
  %11 = bitcast <32 x i32> addrspace(3)* %arrayidx13 to <128 x i8> addrspace(3)*, !dbg !44
  %12 = load <128 x i8>, <128 x i8> addrspace(3)* %11, align 128, !dbg !44
  call void @llvm.ve32.v.xsto.1024.i(i32 %10, i32 0, <128 x i8> %12), !dbg !44
  %13 = load volatile i32, i32* @g_dest_buffer3_base, align 4, !dbg !45
  %arrayidx16 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_3, i32 0, i32 %mul, !dbg !45
  %14 = bitcast <32 x i32> addrspace(3)* %arrayidx16 to <128 x i8> addrspace(3)*, !dbg !45
  %15 = load <128 x i8>, <128 x i8> addrspace(3)* %14, align 128, !dbg !45
  call void @llvm.ve32.v.xsto.1024.i(i32 %13, i32 0, <128 x i8> %15), !dbg !45
  %16 = load volatile i32, i32* @g_dest_buffer4_base, align 4, !dbg !46
  %arrayidx19 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_4, i32 0, i32 %mul, !dbg !46
  %17 = bitcast <32 x i32> addrspace(3)* %arrayidx19 to <128 x i8> addrspace(3)*, !dbg !46
  %18 = load <128 x i8>, <128 x i8> addrspace(3)* %17, align 128, !dbg !46
  call void @llvm.ve32.v.xsto.1024.i(i32 %16, i32 0, <128 x i8> %18), !dbg !46
  %19 = load volatile i32, i32* @g_dest_buffer5_base, align 4, !dbg !47
  %arrayidx22 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_5, i32 0, i32 %mul, !dbg !47
  %20 = bitcast <32 x i32> addrspace(3)* %arrayidx22 to <128 x i8> addrspace(3)*, !dbg !47
  %21 = load <128 x i8>, <128 x i8> addrspace(3)* %20, align 128, !dbg !47
  call void @llvm.ve32.v.xsto.1024.i(i32 %19, i32 0, <128 x i8> %21), !dbg !47
  %22 = load volatile i32, i32* @g_dest_buffer6_base, align 4, !dbg !48
  %arrayidx25 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_6, i32 0, i32 %mul, !dbg !48
  %23 = bitcast <32 x i32> addrspace(3)* %arrayidx25 to <128 x i8> addrspace(3)*, !dbg !48
  %24 = load <128 x i8>, <128 x i8> addrspace(3)* %23, align 128, !dbg !48
  call void @llvm.ve32.v.xsto.1024.i(i32 %22, i32 0, <128 x i8> %24), !dbg !48
  %25 = load volatile i32, i32* @g_dest_buffer7_base, align 4, !dbg !49
  %arrayidx28 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 %mul, !dbg !49
  %26 = bitcast <32 x i32> addrspace(3)* %arrayidx28 to <128 x i8> addrspace(3)*, !dbg !49
  %27 = load <128 x i8>, <128 x i8> addrspace(3)* %26, align 128, !dbg !49
  call void @llvm.ve32.v.xsto.1024.i(i32 %25, i32 0, <128 x i8> %27), !dbg !49
  %28 = load volatile i32, i32* @g_dest_buffer0_base, align 4, !dbg !42
  %add.1 = or i32 %mul, 1, !dbg !42
  %arrayidx.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_0, i32 0, i32 %add.1, !dbg !42
  %29 = bitcast <32 x i32> addrspace(3)* %arrayidx.1 to <128 x i8> addrspace(3)*, !dbg !42
  %30 = load <128 x i8>, <128 x i8> addrspace(3)* %29, align 128, !dbg !42
  call void @llvm.ve32.v.xsto.1024.i(i32 %28, i32 0, <128 x i8> %30), !dbg !42
  %31 = load volatile i32, i32* @g_dest_buffer1_base, align 4, !dbg !43
  %arrayidx10.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_1, i32 0, i32 %add.1, !dbg !43
  %32 = bitcast <32 x i32> addrspace(3)* %arrayidx10.1 to <128 x i8> addrspace(3)*, !dbg !43
  %33 = load <128 x i8>, <128 x i8> addrspace(3)* %32, align 128, !dbg !43
  call void @llvm.ve32.v.xsto.1024.i(i32 %31, i32 0, <128 x i8> %33), !dbg !43
  %34 = load volatile i32, i32* @g_dest_buffer2_base, align 4, !dbg !44
  %arrayidx13.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_2, i32 0, i32 %add.1, !dbg !44
  %35 = bitcast <32 x i32> addrspace(3)* %arrayidx13.1 to <128 x i8> addrspace(3)*, !dbg !44
  %36 = load <128 x i8>, <128 x i8> addrspace(3)* %35, align 128, !dbg !44
  call void @llvm.ve32.v.xsto.1024.i(i32 %34, i32 0, <128 x i8> %36), !dbg !44
  %37 = load volatile i32, i32* @g_dest_buffer3_base, align 4, !dbg !45
  %arrayidx16.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_3, i32 0, i32 %add.1, !dbg !45
  %38 = bitcast <32 x i32> addrspace(3)* %arrayidx16.1 to <128 x i8> addrspace(3)*, !dbg !45
  %39 = load <128 x i8>, <128 x i8> addrspace(3)* %38, align 128, !dbg !45
  call void @llvm.ve32.v.xsto.1024.i(i32 %37, i32 0, <128 x i8> %39), !dbg !45
  %40 = load volatile i32, i32* @g_dest_buffer4_base, align 4, !dbg !46
  %arrayidx19.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_4, i32 0, i32 %add.1, !dbg !46
  %41 = bitcast <32 x i32> addrspace(3)* %arrayidx19.1 to <128 x i8> addrspace(3)*, !dbg !46
  %42 = load <128 x i8>, <128 x i8> addrspace(3)* %41, align 128, !dbg !46
  call void @llvm.ve32.v.xsto.1024.i(i32 %40, i32 0, <128 x i8> %42), !dbg !46
  %43 = load volatile i32, i32* @g_dest_buffer5_base, align 4, !dbg !47
  %arrayidx22.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_5, i32 0, i32 %add.1, !dbg !47
  %44 = bitcast <32 x i32> addrspace(3)* %arrayidx22.1 to <128 x i8> addrspace(3)*, !dbg !47
  %45 = load <128 x i8>, <128 x i8> addrspace(3)* %44, align 128, !dbg !47
  call void @llvm.ve32.v.xsto.1024.i(i32 %43, i32 0, <128 x i8> %45), !dbg !47
  %46 = load volatile i32, i32* @g_dest_buffer6_base, align 4, !dbg !48
  %arrayidx25.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_6, i32 0, i32 %add.1, !dbg !48
  %47 = bitcast <32 x i32> addrspace(3)* %arrayidx25.1 to <128 x i8> addrspace(3)*, !dbg !48
  %48 = load <128 x i8>, <128 x i8> addrspace(3)* %47, align 128, !dbg !48
  call void @llvm.ve32.v.xsto.1024.i(i32 %46, i32 0, <128 x i8> %48), !dbg !48
  %49 = load volatile i32, i32* @g_dest_buffer7_base, align 4, !dbg !49
  %arrayidx28.1 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 %add.1, !dbg !49
  %50 = bitcast <32 x i32> addrspace(3)* %arrayidx28.1 to <128 x i8> addrspace(3)*, !dbg !49
  %51 = load <128 x i8>, <128 x i8> addrspace(3)* %50, align 128, !dbg !49
  call void @llvm.ve32.v.xsto.1024.i(i32 %49, i32 0, <128 x i8> %51), !dbg !49
  br label %while.cond29, !dbg !50

while.cond29:                                     ; preds = %for.cond5.preheader, %while.cond29
  %52 = load volatile i32, i32* @g_timer_debug, align 4, !dbg !51
  %cmp30.not = icmp eq i32 %52, -559038737, !dbg !52
  br i1 %cmp30.not, label %while.end32, label %while.cond29, !dbg !50, !llvm.loop !53

while.end32:                                      ; preds = %while.cond29
  store volatile i32 57005, i32* @g_timer_debug, align 4, !dbg !55
  %53 = load volatile i32, i32* @g_debug, align 4, !dbg !56
  %inc33 = add i32 %53, 1, !dbg !56
  store volatile i32 %inc33, i32* @g_debug, align 4, !dbg !56
  %inc35 = add nuw nsw i32 %i.020, 1, !dbg !57
  %newindvar.dec = sub i32 %newindvar, 1, !dbg !41
  %54 = icmp eq i32 %newindvar, 0, !dbg !41
  br i1 %54, label %while.cond1.loopexit, label %for.cond5.preheader, !dbg !41, !llvm.loop !58

while.end37:                                      ; preds = %while.cond1.loopexit, %while.end
  call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 2), !dbg !60
  ret void, !dbg !61
}

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.s.xsto.32(i32, i32, i32) #1

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #1

; Function Attrs: nofree nosync nounwind readnone
declare void @llvm.ve32.printstring.md(i32) #2

; Function Attrs: nounwind
define void @jesd_tx_entry() local_unnamed_addr #3 !dbg !62 {
  call void @jesd_tx(), !dbg !63
  ret void, !dbg !63
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nounwind writeonly }
attributes #2 = { nofree nosync nounwind readnone }
attributes #3 = { nounwind "frame-pointer"="all" "hive_entry" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}
!hive.inststrings.strings = !{!9}
!volcano.source.file = !{!10}
!volcano.command.line = !{!11}
!volcano.machine.path = !{!12}
!volcano.machine.name = !{!13}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c", directory: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = !{!"jesd_tx : start \0A"}
!10 = !{!"/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c"}
!11 = !{!"/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.stubs.h --o-optimized-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.opt.ll --o-clang-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.clang.ll -emit-after-pp /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw -I. -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/systems/abc_vex40_system/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/systems/abc_vex40_system/common/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230911_sles12_gcc720/iirci_master_20230911_2201_sles12_gcc720/pct/Linux/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230911_sles12_gcc720/iirci_master_20230911_2201_sles12_gcc720/pct/Linux/host/include -o-dot-s /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.s -DVOLCANO=1 -o /nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.o "}
!12 = !{!"/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"}
!13 = !{!"ve32"}
!14 = distinct !DISubprogram(name: "jesd_tx", scope: !15, file: !15, line: 109, type: !16, scopeLine: 110, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!15 = !DIFile(filename: "vex_jesd_tx.c", directory: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw")
!16 = !DISubroutineType(types: !2)
!17 = !DILocation(line: 115, column: 22, scope: !14)
!18 = !DILocation(line: 116, column: 16, scope: !14)
!19 = !DILocation(line: 118, column: 5, scope: !14)
!20 = !{!"VOLATILE"}
!21 = !DILocation(line: 119, column: 16, scope: !14)
!22 = !DILocation(line: 92, column: 5, scope: !23, inlinedAt: !24)
!23 = distinct !DISubprogram(name: "init_timer", scope: !15, file: !15, line: 89, type: !16, scopeLine: 90, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!24 = distinct !DILocation(line: 119, column: 5, scope: !14)
!25 = !DILocation(line: 94, column: 5, scope: !23, inlinedAt: !24)
!26 = !DILocation(line: 96, column: 5, scope: !23, inlinedAt: !24)
!27 = !DILocation(line: 98, column: 5, scope: !23, inlinedAt: !24)
!28 = !DILocation(line: 100, column: 5, scope: !23, inlinedAt: !24)
!29 = !DILocation(line: 121, column: 5, scope: !14)
!30 = !DILocation(line: 121, column: 12, scope: !14)
!31 = !DILocation(line: 121, column: 29, scope: !14)
!32 = distinct !{!32, !29, !33, !34}
!33 = !DILocation(line: 124, column: 5, scope: !14)
!34 = !{!"llvm.loop.mustprogress"}
!35 = !DILocation(line: 126, column: 5, scope: !14)
!36 = !DILocation(line: 128, column: 11, scope: !14)
!37 = !DILocation(line: 128, column: 22, scope: !14)
!38 = !DILocation(line: 128, column: 5, scope: !14)
!39 = distinct !{!39, !38, !40, !34}
!40 = !DILocation(line: 155, column: 5, scope: !14)
!41 = !DILocation(line: 130, column: 9, scope: !14)
!42 = !DILocation(line: 134, column: 8, scope: !14)
!43 = !DILocation(line: 135, column: 8, scope: !14)
!44 = !DILocation(line: 136, column: 8, scope: !14)
!45 = !DILocation(line: 137, column: 8, scope: !14)
!46 = !DILocation(line: 139, column: 8, scope: !14)
!47 = !DILocation(line: 140, column: 8, scope: !14)
!48 = !DILocation(line: 141, column: 8, scope: !14)
!49 = !DILocation(line: 142, column: 8, scope: !14)
!50 = !DILocation(line: 147, column: 13, scope: !14)
!51 = !DILocation(line: 147, column: 20, scope: !14)
!52 = !DILocation(line: 147, column: 34, scope: !14)
!53 = distinct !{!53, !50, !54, !34}
!54 = !DILocation(line: 149, column: 13, scope: !14)
!55 = !DILocation(line: 150, column: 27, scope: !14)
!56 = !DILocation(line: 151, column: 20, scope: !14)
!57 = !DILocation(line: 130, column: 37, scope: !14)
!58 = distinct !{!58, !41, !59, !34}
!59 = !DILocation(line: 152, column: 9, scope: !14)
!60 = !DILocation(line: 157, column: 5, scope: !14)
!61 = !DILocation(line: 159, column: 1, scope: !14)
!62 = distinct !DISubprogram(name: "jesd_tx_entry", scope: !15, file: !15, line: 109, type: !16, scopeLine: 110, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!63 = !DILocation(line: 110, scope: !62)
