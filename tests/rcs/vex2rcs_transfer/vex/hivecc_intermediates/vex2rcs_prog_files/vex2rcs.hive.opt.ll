; ModuleID = 'vex2rcs.hive.c'
source_filename = "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c"
target datalayout = "e-m:e-p:32:32-i64:32-f64:32-n32"
target triple = "ve32"

@vinput = dso_local local_unnamed_addr addrspace(3) global [3 x <32 x i32>] zeroinitializer, align 128

; Function Attrs: noinline nounwind uwtable
define dso_local void @vex2rcs_prog() local_unnamed_addr #0 !dbg !15 {
entry:
  %0 = load <128 x i8>, <128 x i8> addrspace(3)* bitcast ([3 x <32 x i32>] addrspace(3)* @vinput to <128 x i8> addrspace(3)*), align 128, !dbg !18
  call void @llvm.ve32.v.xsto.1024.i(i32 0, i32 0, <128 x i8> %0), !dbg !18
  %1 = load <128 x i8>, <128 x i8> addrspace(3)* bitcast (<32 x i32> addrspace(3)* getelementptr inbounds ([3 x <32 x i32>], [3 x <32 x i32>] addrspace(3)* @vinput, i32 0, i32 1) to <128 x i8> addrspace(3)*), align 128, !dbg !18
  call void @llvm.ve32.v.xsto.1024.i(i32 0, i32 0, <128 x i8> %1), !dbg !18
  %2 = load <128 x i8>, <128 x i8> addrspace(3)* bitcast (<32 x i32> addrspace(3)* getelementptr inbounds ([3 x <32 x i32>], [3 x <32 x i32>] addrspace(3)* @vinput, i32 0, i32 2) to <128 x i8> addrspace(3)*), align 128, !dbg !18
  call void @llvm.ve32.v.xsto.1024.i(i32 0, i32 0, <128 x i8> %2), !dbg !18
  call void @llvm.ve32.printstring.md(i32 1), !dbg !19, !intrin_attr !20
  call void @llvm.ve32.printstring.md(i32 0), !dbg !21, !intrin_attr !20
  ret void, !dbg !22
}

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #1

; Function Attrs: nofree nosync nounwind readnone
declare void @llvm.ve32.printstring.md(i32) #2

; Function Attrs: nounwind
define void @vex2rcs_prog_entry() local_unnamed_addr #3 !dbg !23 {
  call void @vex2rcs_prog(), !dbg !24
  ret void, !dbg !24
}

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nounwind writeonly }
attributes #2 = { nofree nosync nounwind readnone }
attributes #3 = { nounwind "frame-pointer"="all" "hive_entry" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}
!hive.inststrings.strings = !{!9, !10}
!volcano.source.file = !{!11}
!volcano.command.line = !{!12}
!volcano.machine.path = !{!13}
!volcano.machine.name = !{!14}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = !{!"------------vex2rcs core:END------------\0A"}
!10 = !{!"\0A"}
!11 = !{!"/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c"}
!12 = !{!"/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/vex2rcs.hive.c -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.stubs.h -backend-report /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.rpt.json --o-optimized-ir /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.opt.ll --o-clang-ir /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.clang.ll -emit-after-pp /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex -I. -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/hrt/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/systems/abc_vex40_system/common/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/include -I/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/host/include -o-dot-s /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.s -DVOLCANO=1 -o /nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex/hivecc_intermediates/vex2rcs_prog_files/vex2rcs.hive.o "}
!13 = !{!"/nfs/site/disks/xne_00001/workspace/hw/vex_sdk/multicores_0p8/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"}
!14 = !{!"ve32"}
!15 = distinct !DISubprogram(name: "vex2rcs_prog", scope: !16, file: !16, line: 12, type: !17, scopeLine: 13, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!16 = !DIFile(filename: "vex2rcs.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/akashmur/emulval_0p8_jun21/abc_emul-srvrgen4/tests/rcs/vex2rcs_transfer/vex")
!17 = !DISubroutineType(types: !2)
!18 = !DILocation(line: 15, column: 2, scope: !15)
!19 = !DILocation(line: 17, column: 3, scope: !15)
!20 = !{!"VOLATILE"}
!21 = !DILocation(line: 18, column: 3, scope: !15)
!22 = !DILocation(line: 19, column: 1, scope: !15)
!23 = distinct !DISubprogram(name: "vex2rcs_prog_entry", scope: !16, file: !16, line: 12, type: !17, scopeLine: 13, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!24 = !DILocation(line: 13, scope: !23)
