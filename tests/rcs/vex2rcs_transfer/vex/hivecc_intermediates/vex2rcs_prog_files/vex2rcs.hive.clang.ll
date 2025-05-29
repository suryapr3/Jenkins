; ModuleID = 'vex2rcs.hive.c'
source_filename = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c"
target datalayout = "e-m:e-p:32:32-i64:32-f64:32-n32"
target triple = "ve32"

@vinput = dso_local addrspace(3) global [3 x <32 x i32>] zeroinitializer, align 128
@.str = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.1 = private unnamed_addr constant [42 x i8] c"------------vex2rcs core:END------------\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @vex2rcs_prog() #0 !dbg !9 {
entry:
  %i = alloca i32, align 4
  store i32 0, i32* %i, align 4, !dbg !12
  br label %for.cond, !dbg !13

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !14
  %cmp = icmp slt i32 %0, 3, !dbg !15
  br i1 %cmp, label %for.body, label %for.end, !dbg !16

for.body:                                         ; preds = %for.cond
  %1 = load i32, i32* %i, align 4, !dbg !17
  %arrayidx = getelementptr [3 x <32 x i32>], [3 x <32 x i32>] addrspace(3)* @vinput, i32 0, i32 %1, !dbg !17
  %2 = load <32 x i32>, <32 x i32> addrspace(3)* %arrayidx, align 128, !dbg !17
  %3 = bitcast <32 x i32> %2 to <128 x i8>, !dbg !17
  call void @llvm.ve32.v.xsto.1024.i(i32 0, i32 0, <128 x i8> %3), !dbg !17
  br label %for.inc, !dbg !17

for.inc:                                          ; preds = %for.body
  %4 = load i32, i32* %i, align 4, !dbg !18
  %inc = add i32 %4, 1, !dbg !18
  store i32 %inc, i32* %i, align 4, !dbg !18
  br label %for.cond, !dbg !16, !llvm.loop !19

for.end:                                          ; preds = %for.cond
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)), !dbg !21, !intrin_attr !22
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.1, i32 0, i32 0)), !dbg !23, !intrin_attr !22
  ret void, !dbg !24
}

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #1

; Function Attrs: nounwind readonly
declare void @llvm.ve32.printstring(i8*) #2

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "hive_entry" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nounwind writeonly }
attributes #2 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = distinct !DISubprogram(name: "vex2rcs_prog", scope: !10, file: !10, line: 12, type: !11, scopeLine: 13, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "vex2rcs.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex")
!11 = !DISubroutineType(types: !2)
!12 = !DILocation(line: 14, column: 11, scope: !9)
!13 = !DILocation(line: 14, column: 7, scope: !9)
!14 = !DILocation(line: 14, column: 18, scope: !9)
!15 = !DILocation(line: 14, column: 20, scope: !9)
!16 = !DILocation(line: 14, column: 3, scope: !9)
!17 = !DILocation(line: 15, column: 2, scope: !9)
!18 = !DILocation(line: 14, column: 26, scope: !9)
!19 = distinct !{!19, !16, !17, !20}
!20 = !{!"llvm.loop.mustprogress"}
!21 = !DILocation(line: 17, column: 3, scope: !9)
!22 = !{!"VOLATILE"}
!23 = !DILocation(line: 18, column: 3, scope: !9)
!24 = !DILocation(line: 19, column: 1, scope: !9)
