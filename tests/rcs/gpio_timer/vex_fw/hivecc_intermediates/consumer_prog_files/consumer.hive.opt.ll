; ModuleID = 'consumer.hive.c'
source_filename = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c"
target datalayout = "e-m:e-p:32:32-i64:32-f64:32-n32"
target triple = "ve32"

@consumer_sm_gate = dso_local local_unnamed_addr global [16 x i32] zeroinitializer, section "addr:384", align 128
@count = dso_local local_unnamed_addr global i32 0, section "addr:64", align 4
@gTimeStampData = dso_local addrspace(3) global <32 x i32> zeroinitializer, section "addr:0", align 128
@gTimeStampDataCopy = dso_local addrspace(3) global [10 x <32 x i32>] zeroinitializer, section "addr:256", align 128
@buffer_ra = dso_local local_unnamed_addr global i32 0, align 4
@consumer_max_count = dso_local local_unnamed_addr global i32 0, align 4
@consumer_token_per_request = dso_local local_unnamed_addr global i32 0, align 4

; Function Attrs: noinline nounwind uwtable
define dso_local void @consumer_prog() local_unnamed_addr #0 !dbg !17 {
entry:
  %0 = load i32, i32* @buffer_ra, align 4, !dbg !20
  call void @llvm.ve32.mc.reset(i32 0) #5, !dbg !21, !intrin_attr !25
  call void @llvm.ve32.mc.init(i32 196609, i32 1) #5, !dbg !26, !intrin_attr !25
  call void @llvm.ve32.mc.init.local.idc(i32 0, i32 1) #5, !dbg !29, !intrin_attr !30
  call void @llvm.ve32.printstring.md(i32 3), !dbg !31, !intrin_attr !32
  call void @llvm.ve32.dump(i32 1, i32 1) #5, !dbg !31, !intrin_attr !32
  call void @llvm.ve32.printstring.md(i32 2), !dbg !31, !intrin_attr !32
  %1 = call i32 @llvm.ve32.mc.get.state(i32 0, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 0, i32 %1) #5, !dbg !31, !intrin_attr !32
  %2 = call i32 @llvm.ve32.mc.get.state(i32 1, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 1, i32 %2) #5, !dbg !31, !intrin_attr !32
  %3 = call i32 @llvm.ve32.mc.get.state(i32 2, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 2, i32 %3) #5, !dbg !31, !intrin_attr !32
  %4 = call i32 @llvm.ve32.mc.get.state(i32 3, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 3, i32 %4) #5, !dbg !31, !intrin_attr !32
  %5 = call i32 @llvm.ve32.mc.get.state(i32 4, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 4, i32 %5) #5, !dbg !31, !intrin_attr !32
  %6 = call i32 @llvm.ve32.mc.get.state(i32 5, i32 1) #5, !dbg !31, !intrin_attr !33
  call void @llvm.ve32.dump(i32 5, i32 %6) #5, !dbg !31, !intrin_attr !32
  store i32 0, i32* @count, align 4, !dbg !34
  br label %while.body, !dbg !35

while.body:                                       ; preds = %while.body.while.body_crit_edge, %entry
  %7 = phi i32 [ 0, %entry ], [ %.pre, %while.body.while.body_crit_edge ], !dbg !36
  %8 = call { i32, i32 } @llvm.ve32.mc.request(i32 1, i32 1), !dbg !37, !intrin_attr !38
  %9 = load volatile <32 x i32>, <32 x i32> addrspace(3)* @gTimeStampData, align 128, !dbg !39, !intrin_attr !40
  %inc = add i32 %7, 1, !dbg !36
  store i32 %inc, i32* @count, align 4, !dbg !36
  %arrayidx = getelementptr [10 x <32 x i32>], [10 x <32 x i32>] addrspace(3)* @gTimeStampDataCopy, i32 0, i32 %7, !dbg !41
  store volatile <32 x i32> %9, <32 x i32> addrspace(3)* %arrayidx, align 128, !dbg !42, !intrin_attr !40
  %cmp1 = icmp slt i32 %inc, 5, !dbg !43
  %10 = call i32 @llvm.ve32.mc.complete(i32 1), !dbg !44, !intrin_attr !30
  call void @llvm.ve32.v.xsto.32(i32 %0, i32 0, i32 %10), !dbg !45, !intrin_attr !46
  br i1 %cmp1, label %while.body.while.body_crit_edge, label %while.end, !dbg !35, !llvm.loop !47

while.body.while.body_crit_edge:                  ; preds = %while.body
  %.pre = load i32, i32* @count, align 4, !dbg !36
  br label %while.body, !dbg !35

while.end:                                        ; preds = %while.body
  %11 = load i32, i32* @count, align 4, !dbg !50
  call void @llvm.ve32.dump(i32 56, i32 %11), !dbg !51, !intrin_attr !32
  call void @llvm.ve32.printstring.md(i32 1), !dbg !52, !intrin_attr !32
  call void @llvm.ve32.printstring.md(i32 0), !dbg !53, !intrin_attr !32
  ret void, !dbg !54
}

; Function Attrs: nofree nounwind readonly
declare { i32, i32 } @llvm.ve32.mc.request(i32, i32) #1

; Function Attrs: nofree nosync nounwind readnone
declare i32 @llvm.ve32.mc.complete(i32) #2

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.32(i32, i32, i32) #3

; Function Attrs: nofree nosync nounwind readnone
declare void @llvm.ve32.dump(i32, i32) #2

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.mc.reset(i32) #3

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.mc.init(i32, i32) #3

; Function Attrs: nofree nosync nounwind readnone
declare void @llvm.ve32.mc.init.local.idc(i32, i32) #2

; Function Attrs: nofree nounwind readonly
declare i32 @llvm.ve32.mc.get.state(i32, i32) #1

; Function Attrs: nofree nosync nounwind readnone
declare void @llvm.ve32.printstring.md(i32) #2

; Function Attrs: nounwind
define void @consumer_prog_entry() local_unnamed_addr #4 !dbg !55 {
  call void @consumer_prog(), !dbg !56
  ret void, !dbg !56
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nofree nounwind readonly }
attributes #2 = { nofree nosync nounwind readnone }
attributes #3 = { nounwind writeonly }
attributes #4 = { nounwind "frame-pointer"="all" "hive_entry" }
attributes #5 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}
!hive.inststrings.strings = !{!9, !10, !11, !12}
!volcano.source.file = !{!13}
!volcano.command.line = !{!14}
!volcano.machine.path = !{!15}
!volcano.machine.name = !{!16}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = !{!"------------consumer core:END------------\0A"}
!10 = !{!"\0A"}
!11 = !{!"{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\0A"}
!12 = !{!"fu mc_get_state{1,2,3} idx="}
!13 = !{!"/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c"}
!14 = !{!"/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.stubs.h -backend-report /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.rpt.json --o-optimized-ir /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.opt.ll --o-clang-ir /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.clang.ll -emit-after-pp /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw -I. -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/host/include -o-dot-s /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.s -DVOLCANO=1 -o /nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/hivecc_intermediates/consumer_prog_files/consumer.hive.o "}
!15 = !{!"/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"}
!16 = !{!"ve32"}
!17 = distinct !DISubprogram(name: "consumer_prog", scope: !18, file: !18, line: 18, type: !19, scopeLine: 19, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!18 = !DIFile(filename: "consumer.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw")
!19 = !DISubroutineType(types: !2)
!20 = !DILocation(line: 20, column: 21, scope: !17)
!21 = !DILocation(line: 75, column: 5, scope: !22, inlinedAt: !24)
!22 = distinct !DISubprogram(name: "semaphore_gate_init", scope: !23, file: !23, line: 72, type: !19, scopeLine: 73, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!23 = !DIFile(filename: "cir_buf.hive.h", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw")
!24 = distinct !DILocation(line: 26, column: 3, scope: !17)
!25 = !{!"WRITE_STATE"}
!26 = !DILocation(line: 59, column: 5, scope: !27, inlinedAt: !28)
!27 = distinct !DISubprogram(name: "circ_buff_init", scope: !23, file: !23, line: 41, type: !19, scopeLine: 42, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!28 = distinct !DILocation(line: 35, column: 3, scope: !17)
!29 = !DILocation(line: 60, column: 5, scope: !27, inlinedAt: !28)
!30 = !{!"READ_STATE", !"WRITE_STATE"}
!31 = !DILocation(line: 61, column: 5, scope: !27, inlinedAt: !28)
!32 = !{!"VOLATILE"}
!33 = !{!"READ_STATE"}
!34 = !DILocation(line: 38, column: 9, scope: !17)
!35 = !DILocation(line: 42, column: 3, scope: !17)
!36 = !DILocation(line: 48, column: 30, scope: !17)
!37 = !DILocation(line: 47, column: 5, scope: !17)
!38 = !{!"READ_STATE", !"SYNC:0", !"WRITE_STATE"}
!39 = !DILocation(line: 48, column: 36, scope: !17)
!40 = !{!"SYNC_WITH:0", !"SYNC_WITH:1"}
!41 = !DILocation(line: 48, column: 6, scope: !17)
!42 = !DILocation(line: 48, column: 34, scope: !17)
!43 = !DILocation(line: 50, column: 17, scope: !17)
!44 = !DILocation(line: 52, column: 5, scope: !17)
!45 = !DILocation(line: 53, column: 5, scope: !17)
!46 = !{!"SYNC:1"}
!47 = distinct !{!47, !35, !48, !49}
!48 = !DILocation(line: 54, column: 3, scope: !17)
!49 = !{!"llvm.loop.mustprogress"}
!50 = !DILocation(line: 56, column: 22, scope: !17)
!51 = !DILocation(line: 56, column: 3, scope: !17)
!52 = !DILocation(line: 57, column: 3, scope: !17)
!53 = !DILocation(line: 58, column: 3, scope: !17)
!54 = !DILocation(line: 59, column: 1, scope: !17)
!55 = distinct !DISubprogram(name: "consumer_prog_entry", scope: !18, file: !18, line: 18, type: !19, scopeLine: 19, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!56 = !DILocation(line: 19, scope: !55)
