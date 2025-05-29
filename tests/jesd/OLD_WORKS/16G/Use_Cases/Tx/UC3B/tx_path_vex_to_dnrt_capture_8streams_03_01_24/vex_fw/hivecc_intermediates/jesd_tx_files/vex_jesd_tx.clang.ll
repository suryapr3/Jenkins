; ModuleID = 'vex_jesd_tx.c'
source_filename = "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c"
target datalayout = "e-m:e-p:32:32-i64:32-n32"
target triple = "ve32"

@vbuffer_0 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_1 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:8192", align 128
@vbuffer_2 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:16384", align 128
@vbuffer_3 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:24576", align 128
@vbuffer_4 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:32768", align 128
@vbuffer_5 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:40960", align 128
@vbuffer_6 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_7 = dso_local addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:57344", align 128
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
@.str = private unnamed_addr constant [18 x i8] c"jesd_tx : start \0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @jesd_tx() #0 !dbg !9 {
entry:
  %cycles.addr.i = alloca i32, align 4
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %iter_max = alloca i32, align 4
  %num_vec_per_stream = alloca i32, align 4
  store i32 32, i32* %iter_max, align 4, !dbg !12
  store i32 2, i32* %num_vec_per_stream, align 4, !dbg !13
  store volatile i32 0, i32* @g_host_indicator, align 4, !dbg !14
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !15
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str, i32 0, i32 0)), !dbg !16, !intrin_attr !17
  %0 = load volatile i32, i32* @g_timeout_cycles, align 4, !dbg !18
  store i32 %0, i32* %cycles.addr.i, align 4
  call void @llvm.ve32.s.xsto.32(i32 0, i32 3, i32 3) #3, !dbg !19
  %1 = load i32, i32* %cycles.addr.i, align 4, !dbg !22
  call void @llvm.ve32.s.xsto.32(i32 0, i32 4, i32 %1) #3, !dbg !22
  call void @llvm.ve32.s.xsto.32(i32 0, i32 6, i32 1) #3, !dbg !23
  call void @llvm.ve32.s.xsto.32(i32 0, i32 7, i32 16424) #3, !dbg !24
  call void @llvm.ve32.s.xsto.32(i32 0, i32 8, i32 -559038737) #3, !dbg !25
  br label %while.cond, !dbg !26

while.cond:                                       ; preds = %while.body, %entry
  %2 = load volatile i32, i32* @g_host_indicator, align 4, !dbg !27
  %cmp = icmp eq i32 %2, 0, !dbg !28
  br i1 %cmp, label %while.body, label %while.end, !dbg !26

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !26, !llvm.loop !29

while.end:                                        ; preds = %while.cond
  call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 1), !dbg !32
  br label %while.cond1, !dbg !33

while.cond1:                                      ; preds = %for.end36, %while.end
  %3 = load volatile i32, i32* @g_vex_exit, align 4, !dbg !34
  %cmp2 = icmp eq i32 %3, 0, !dbg !35
  br i1 %cmp2, label %while.body3, label %while.end37, !dbg !33

while.body3:                                      ; preds = %while.cond1
  store i32 0, i32* %i, align 4, !dbg !36
  br label %for.cond, !dbg !37

for.cond:                                         ; preds = %for.inc34, %while.body3
  %4 = load i32, i32* %i, align 4, !dbg !38
  %5 = load i32, i32* %iter_max, align 4, !dbg !39
  %cmp4 = icmp slt i32 %4, %5, !dbg !40
  br i1 %cmp4, label %for.body, label %for.end36, !dbg !41

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4, !dbg !42
  br label %for.cond5, !dbg !43

for.cond5:                                        ; preds = %for.inc, %for.body
  %6 = load i32, i32* %j, align 4, !dbg !44
  %7 = load i32, i32* %num_vec_per_stream, align 4, !dbg !45
  %cmp6 = icmp slt i32 %6, %7, !dbg !46
  br i1 %cmp6, label %for.body7, label %for.end, !dbg !47

for.body7:                                        ; preds = %for.cond5
  %8 = load volatile i32, i32* @g_dest_buffer0_base, align 4, !dbg !48
  %9 = load i32, i32* %i, align 4, !dbg !48
  %mul = mul i32 %9, 2, !dbg !48
  %10 = load i32, i32* %j, align 4, !dbg !48
  %add = add i32 %mul, %10, !dbg !48
  %arrayidx = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_0, i32 0, i32 %add, !dbg !48
  %11 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx, align 128, !dbg !48
  %12 = bitcast <32 x i32> %11 to <128 x i8>, !dbg !48
  call void @llvm.ve32.v.xsto.1024.i(i32 %8, i32 0, <128 x i8> %12), !dbg !48
  %13 = load volatile i32, i32* @g_dest_buffer1_base, align 4, !dbg !49
  %14 = load i32, i32* %i, align 4, !dbg !49
  %mul8 = mul i32 %14, 2, !dbg !49
  %15 = load i32, i32* %j, align 4, !dbg !49
  %add9 = add i32 %mul8, %15, !dbg !49
  %arrayidx10 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_1, i32 0, i32 %add9, !dbg !49
  %16 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx10, align 128, !dbg !49
  %17 = bitcast <32 x i32> %16 to <128 x i8>, !dbg !49
  call void @llvm.ve32.v.xsto.1024.i(i32 %13, i32 0, <128 x i8> %17), !dbg !49
  %18 = load volatile i32, i32* @g_dest_buffer2_base, align 4, !dbg !50
  %19 = load i32, i32* %i, align 4, !dbg !50
  %mul11 = mul i32 %19, 2, !dbg !50
  %20 = load i32, i32* %j, align 4, !dbg !50
  %add12 = add i32 %mul11, %20, !dbg !50
  %arrayidx13 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_2, i32 0, i32 %add12, !dbg !50
  %21 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx13, align 128, !dbg !50
  %22 = bitcast <32 x i32> %21 to <128 x i8>, !dbg !50
  call void @llvm.ve32.v.xsto.1024.i(i32 %18, i32 0, <128 x i8> %22), !dbg !50
  %23 = load volatile i32, i32* @g_dest_buffer3_base, align 4, !dbg !51
  %24 = load i32, i32* %i, align 4, !dbg !51
  %mul14 = mul i32 %24, 2, !dbg !51
  %25 = load i32, i32* %j, align 4, !dbg !51
  %add15 = add i32 %mul14, %25, !dbg !51
  %arrayidx16 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_3, i32 0, i32 %add15, !dbg !51
  %26 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx16, align 128, !dbg !51
  %27 = bitcast <32 x i32> %26 to <128 x i8>, !dbg !51
  call void @llvm.ve32.v.xsto.1024.i(i32 %23, i32 0, <128 x i8> %27), !dbg !51
  %28 = load volatile i32, i32* @g_dest_buffer4_base, align 4, !dbg !52
  %29 = load i32, i32* %i, align 4, !dbg !52
  %mul17 = mul i32 %29, 2, !dbg !52
  %30 = load i32, i32* %j, align 4, !dbg !52
  %add18 = add i32 %mul17, %30, !dbg !52
  %arrayidx19 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_4, i32 0, i32 %add18, !dbg !52
  %31 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx19, align 128, !dbg !52
  %32 = bitcast <32 x i32> %31 to <128 x i8>, !dbg !52
  call void @llvm.ve32.v.xsto.1024.i(i32 %28, i32 0, <128 x i8> %32), !dbg !52
  %33 = load volatile i32, i32* @g_dest_buffer5_base, align 4, !dbg !53
  %34 = load i32, i32* %i, align 4, !dbg !53
  %mul20 = mul i32 %34, 2, !dbg !53
  %35 = load i32, i32* %j, align 4, !dbg !53
  %add21 = add i32 %mul20, %35, !dbg !53
  %arrayidx22 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_5, i32 0, i32 %add21, !dbg !53
  %36 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx22, align 128, !dbg !53
  %37 = bitcast <32 x i32> %36 to <128 x i8>, !dbg !53
  call void @llvm.ve32.v.xsto.1024.i(i32 %33, i32 0, <128 x i8> %37), !dbg !53
  %38 = load volatile i32, i32* @g_dest_buffer6_base, align 4, !dbg !54
  %39 = load i32, i32* %i, align 4, !dbg !54
  %mul23 = mul i32 %39, 2, !dbg !54
  %40 = load i32, i32* %j, align 4, !dbg !54
  %add24 = add i32 %mul23, %40, !dbg !54
  %arrayidx25 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_6, i32 0, i32 %add24, !dbg !54
  %41 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx25, align 128, !dbg !54
  %42 = bitcast <32 x i32> %41 to <128 x i8>, !dbg !54
  call void @llvm.ve32.v.xsto.1024.i(i32 %38, i32 0, <128 x i8> %42), !dbg !54
  %43 = load volatile i32, i32* @g_dest_buffer7_base, align 4, !dbg !55
  %44 = load i32, i32* %i, align 4, !dbg !55
  %mul26 = mul i32 %44, 2, !dbg !55
  %45 = load i32, i32* %j, align 4, !dbg !55
  %add27 = add i32 %mul26, %45, !dbg !55
  %arrayidx28 = getelementptr [64 x <32 x i32>], [64 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 %add27, !dbg !55
  %46 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx28, align 128, !dbg !55
  %47 = bitcast <32 x i32> %46 to <128 x i8>, !dbg !55
  call void @llvm.ve32.v.xsto.1024.i(i32 %43, i32 0, <128 x i8> %47), !dbg !55
  br label %for.inc, !dbg !56

for.inc:                                          ; preds = %for.body7
  %48 = load i32, i32* %j, align 4, !dbg !57
  %inc = add i32 %48, 1, !dbg !57
  store i32 %inc, i32* %j, align 4, !dbg !57
  br label %for.cond5, !dbg !47, !llvm.loop !58

for.end:                                          ; preds = %for.cond5
  br label %while.cond29, !dbg !59

while.cond29:                                     ; preds = %while.body31, %for.end
  %49 = load volatile i32, i32* @g_timer_debug, align 4, !dbg !60
  %cmp30 = icmp ne i32 %49, -559038737, !dbg !61
  br i1 %cmp30, label %while.body31, label %while.end32, !dbg !59

while.body31:                                     ; preds = %while.cond29
  br label %while.cond29, !dbg !59, !llvm.loop !62

while.end32:                                      ; preds = %while.cond29
  store volatile i32 57005, i32* @g_timer_debug, align 4, !dbg !64
  %50 = load volatile i32, i32* @g_debug, align 4, !dbg !65
  %inc33 = add i32 %50, 1, !dbg !65
  store volatile i32 %inc33, i32* @g_debug, align 4, !dbg !65
  br label %for.inc34, !dbg !66

for.inc34:                                        ; preds = %while.end32
  %51 = load i32, i32* %i, align 4, !dbg !67
  %inc35 = add i32 %51, 1, !dbg !67
  store i32 %inc35, i32* %i, align 4, !dbg !67
  br label %for.cond, !dbg !41, !llvm.loop !68

for.end36:                                        ; preds = %for.cond
  br label %while.cond1, !dbg !33, !llvm.loop !69

while.end37:                                      ; preds = %while.cond1
  call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 2), !dbg !71
  ret void, !dbg !72
}

; Function Attrs: nounwind readonly
declare void @llvm.ve32.printstring(i8*) #1

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.s.xsto.32(i32, i32, i32) #2

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "hive_entry" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nounwind readonly }
attributes #2 = { nounwind writeonly }
attributes #3 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/vex_jesd_tx.c", directory: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = distinct !DISubprogram(name: "jesd_tx", scope: !10, file: !10, line: 109, type: !11, scopeLine: 110, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "vex_jesd_tx.c", directory: "/nfs/site/disks/zsc14.xne_abc_fe_001/users/msbhuvan/18a_vex_ws/vex-trunk/vex_core/vex/applications/ve32/examples/tx_path_vex_jesd_dnrt_usecase_5c_07_12_23/vex_fw")
!11 = !DISubroutineType(types: !2)
!12 = !DILocation(line: 112, column: 9, scope: !9)
!13 = !DILocation(line: 113, column: 9, scope: !9)
!14 = !DILocation(line: 115, column: 22, scope: !9)
!15 = !DILocation(line: 116, column: 16, scope: !9)
!16 = !DILocation(line: 118, column: 5, scope: !9)
!17 = !{!"VOLATILE"}
!18 = !DILocation(line: 119, column: 16, scope: !9)
!19 = !DILocation(line: 92, column: 5, scope: !20, inlinedAt: !21)
!20 = distinct !DISubprogram(name: "init_timer", scope: !10, file: !10, line: 89, type: !11, scopeLine: 90, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!21 = distinct !DILocation(line: 119, column: 5, scope: !9)
!22 = !DILocation(line: 94, column: 5, scope: !20, inlinedAt: !21)
!23 = !DILocation(line: 96, column: 5, scope: !20, inlinedAt: !21)
!24 = !DILocation(line: 98, column: 5, scope: !20, inlinedAt: !21)
!25 = !DILocation(line: 100, column: 5, scope: !20, inlinedAt: !21)
!26 = !DILocation(line: 121, column: 5, scope: !9)
!27 = !DILocation(line: 121, column: 12, scope: !9)
!28 = !DILocation(line: 121, column: 29, scope: !9)
!29 = distinct !{!29, !26, !30, !31}
!30 = !DILocation(line: 124, column: 5, scope: !9)
!31 = !{!"llvm.loop.mustprogress"}
!32 = !DILocation(line: 126, column: 5, scope: !9)
!33 = !DILocation(line: 128, column: 5, scope: !9)
!34 = !DILocation(line: 128, column: 11, scope: !9)
!35 = !DILocation(line: 128, column: 22, scope: !9)
!36 = !DILocation(line: 130, column: 15, scope: !9)
!37 = !DILocation(line: 130, column: 13, scope: !9)
!38 = !DILocation(line: 130, column: 21, scope: !9)
!39 = !DILocation(line: 130, column: 25, scope: !9)
!40 = !DILocation(line: 130, column: 23, scope: !9)
!41 = !DILocation(line: 130, column: 9, scope: !9)
!42 = !DILocation(line: 132, column: 13, scope: !9)
!43 = !DILocation(line: 132, column: 11, scope: !9)
!44 = !DILocation(line: 132, column: 18, scope: !9)
!45 = !DILocation(line: 132, column: 22, scope: !9)
!46 = !DILocation(line: 132, column: 20, scope: !9)
!47 = !DILocation(line: 132, column: 7, scope: !9)
!48 = !DILocation(line: 134, column: 8, scope: !9)
!49 = !DILocation(line: 135, column: 8, scope: !9)
!50 = !DILocation(line: 136, column: 8, scope: !9)
!51 = !DILocation(line: 137, column: 8, scope: !9)
!52 = !DILocation(line: 139, column: 8, scope: !9)
!53 = !DILocation(line: 140, column: 8, scope: !9)
!54 = !DILocation(line: 141, column: 8, scope: !9)
!55 = !DILocation(line: 142, column: 8, scope: !9)
!56 = !DILocation(line: 144, column: 10, scope: !9)
!57 = !DILocation(line: 132, column: 43, scope: !9)
!58 = distinct !{!58, !47, !56, !31}
!59 = !DILocation(line: 147, column: 13, scope: !9)
!60 = !DILocation(line: 147, column: 20, scope: !9)
!61 = !DILocation(line: 147, column: 34, scope: !9)
!62 = distinct !{!62, !59, !63, !31}
!63 = !DILocation(line: 149, column: 13, scope: !9)
!64 = !DILocation(line: 150, column: 27, scope: !9)
!65 = !DILocation(line: 151, column: 20, scope: !9)
!66 = !DILocation(line: 152, column: 9, scope: !9)
!67 = !DILocation(line: 130, column: 37, scope: !9)
!68 = distinct !{!68, !41, !66, !31}
!69 = distinct !{!69, !33, !70, !31}
!70 = !DILocation(line: 155, column: 5, scope: !9)
!71 = !DILocation(line: 157, column: 5, scope: !9)
!72 = !DILocation(line: 159, column: 1, scope: !9)
