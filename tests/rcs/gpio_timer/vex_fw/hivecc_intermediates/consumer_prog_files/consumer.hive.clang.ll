; ModuleID = 'consumer.hive.c'
source_filename = "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c"
target datalayout = "e-m:e-p:32:32-i64:32-f64:32-n32"
target triple = "ve32"

@consumer_sm_gate = dso_local global [16 x i32] zeroinitializer, section "addr:384", align 128
@count = dso_local global i32 0, section "addr:64", align 4
@gTimeStampData = dso_local addrspace(3) global <32 x i32> zeroinitializer, section "addr:0", align 128
@gTimeStampDataCopy = dso_local addrspace(3) global [10 x <32 x i32>] zeroinitializer, section "addr:256", align 128
@buffer_ra = dso_local global i32 0, align 4
@.str = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.1 = private unnamed_addr constant [43 x i8] c"------------consumer core:END------------\0A\00", align 1
@consumer_max_count = dso_local global i32 0, align 4
@consumer_token_per_request = dso_local global i32 0, align 4
@.str.2 = private unnamed_addr constant [28 x i8] c"fu mc_get_state{1,2,3} idx=\00", align 1
@.str.3 = private unnamed_addr constant [129 x i8] c"{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define dso_local void @consumer_prog() #0 !dbg !9 {
entry:
  %ch_type.addr.i = alloca i32, align 4
  %tbs.addr.i = alloca i32, align 4
  %token_per_request.addr.i = alloca i32, align 4
  %loc_ptr.addr.i = alloca i32, align 4
  %sm_ch.addr.i = alloca i32, align 4
  %temp0.i = alloca i32, align 4
  %temp1.i = alloca i32, align 4
  %temp2.i = alloca i32, align 4
  %temp3.i = alloca i32, align 4
  %temp4.i = alloca i32, align 4
  %temp5.i = alloca i32, align 4
  %ra = alloca i32, align 4
  %lc = alloca i32, align 4
  %rp = alloca i32, align 4
  %sm_ch = alloca i32, align 4
  %max_count = alloca i32, align 4
  %is_data_ready = alloca i32, align 4
  %idx = alloca i32, align 4
  %0 = load i32, i32* @buffer_ra, align 4, !dbg !12
  store i32 %0, i32* %ra, align 4, !dbg !13
  store i32 0, i32* %rp, align 4, !dbg !14
  store i32 1, i32* %sm_ch, align 4, !dbg !15
  call void @llvm.ve32.mc.reset(i32 0) #4, !dbg !16, !intrin_attr !20
  %1 = load i32, i32* %sm_ch, align 4, !dbg !21
  store i32 65536, i32* %ch_type.addr.i, align 4
  store i32 1, i32* %tbs.addr.i, align 4
  store i32 1, i32* %token_per_request.addr.i, align 4
  store i32 0, i32* %loc_ptr.addr.i, align 4
  store i32 %1, i32* %sm_ch.addr.i, align 4
  %2 = load i32, i32* %tbs.addr.i, align 4, !dbg !22
  %3 = load i32, i32* %token_per_request.addr.i, align 4, !dbg !22
  %shl.i = shl i32 %3, 17, !dbg !22
  %add.i = add i32 %2, %shl.i, !dbg !22
  %4 = load i32, i32* %ch_type.addr.i, align 4, !dbg !22
  %add1.i = add i32 %add.i, %4, !dbg !22
  %5 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !22
  call void @llvm.ve32.mc.init(i32 %add1.i, i32 %5) #4, !dbg !22, !intrin_attr !20
  %6 = load i32, i32* %loc_ptr.addr.i, align 4, !dbg !25
  %7 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !25
  call void @llvm.ve32.mc.init.local.idc(i32 %6, i32 %7) #4, !dbg !25, !intrin_attr !26
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.2, i32 0, i32 0)) #4, !dbg !27, !intrin_attr !28
  %8 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %9 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 %8, i32 %9) #4, !dbg !27, !intrin_attr !28
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([129 x i8], [129 x i8]* @.str.3, i32 0, i32 0)) #4, !dbg !27, !intrin_attr !28
  %10 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %11 = call i32 @llvm.ve32.mc.get.state(i32 0, i32 %10) #4, !dbg !27, !intrin_attr !29
  store i32 %11, i32* %temp0.i, align 4, !dbg !27
  %12 = load i32, i32* %temp0.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 0, i32 %12) #4, !dbg !27, !intrin_attr !28
  %13 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %14 = call i32 @llvm.ve32.mc.get.state(i32 1, i32 %13) #4, !dbg !27, !intrin_attr !29
  store i32 %14, i32* %temp1.i, align 4, !dbg !27
  %15 = load i32, i32* %temp1.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 1, i32 %15) #4, !dbg !27, !intrin_attr !28
  %16 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %17 = call i32 @llvm.ve32.mc.get.state(i32 2, i32 %16) #4, !dbg !27, !intrin_attr !29
  store i32 %17, i32* %temp2.i, align 4, !dbg !27
  %18 = load i32, i32* %temp2.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 2, i32 %18) #4, !dbg !27, !intrin_attr !28
  %19 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %20 = call i32 @llvm.ve32.mc.get.state(i32 3, i32 %19) #4, !dbg !27, !intrin_attr !29
  store i32 %20, i32* %temp3.i, align 4, !dbg !27
  %21 = load i32, i32* %temp3.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 3, i32 %21) #4, !dbg !27, !intrin_attr !28
  %22 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %23 = call i32 @llvm.ve32.mc.get.state(i32 4, i32 %22) #4, !dbg !27, !intrin_attr !29
  store i32 %23, i32* %temp4.i, align 4, !dbg !27
  %24 = load i32, i32* %temp4.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 4, i32 %24) #4, !dbg !27, !intrin_attr !28
  %25 = load i32, i32* %sm_ch.addr.i, align 4, !dbg !27
  %26 = call i32 @llvm.ve32.mc.get.state(i32 5, i32 %25) #4, !dbg !27, !intrin_attr !29
  store i32 %26, i32* %temp5.i, align 4, !dbg !27
  %27 = load i32, i32* %temp5.i, align 4, !dbg !27
  call void @llvm.ve32.dump(i32 5, i32 %27) #4, !dbg !27, !intrin_attr !28
  store i32 0, i32* @count, align 4, !dbg !30
  store i32 5, i32* %max_count, align 4, !dbg !31
  %28 = load i32, i32* @count, align 4, !dbg !32
  %29 = load i32, i32* %max_count, align 4, !dbg !33
  %cmp = icmp slt i32 %28, %29, !dbg !34
  %conv = zext i1 %cmp to i32, !dbg !34
  store i32 %conv, i32* %lc, align 4, !dbg !35
  br label %while.cond, !dbg !36

while.cond:                                       ; preds = %while.body, %entry
  %30 = load i32, i32* %lc, align 4, !dbg !37
  %tobool = icmp ne i32 %30, 0, !dbg !36
  br i1 %tobool, label %while.body, label %while.end, !dbg !36

while.body:                                       ; preds = %while.cond
  %31 = load i32, i32* %lc, align 4, !dbg !38
  %32 = load i32, i32* %sm_ch, align 4, !dbg !38
  %33 = call { i32, i32 } @llvm.ve32.mc.request(i32 %31, i32 %32), !dbg !38, !intrin_attr !39
  %34 = extractvalue { i32, i32 } %33, 1, !dbg !38
  store i32 %34, i32* %idx, align 4, !dbg !38
  %35 = extractvalue { i32, i32 } %33, 0, !dbg !38
  store i32 %35, i32* %is_data_ready, align 4, !dbg !38
  %36 = load volatile <32 x i32>, <32 x i32> addrspace(3)* @gTimeStampData, align 128, !dbg !40, !intrin_attr !41
  %37 = load i32, i32* @count, align 4, !dbg !42
  %inc = add i32 %37, 1, !dbg !42
  store i32 %inc, i32* @count, align 4, !dbg !42
  %arrayidx = getelementptr [10 x <32 x i32>], [10 x <32 x i32>] addrspace(3)* @gTimeStampDataCopy, i32 0, i32 %37, !dbg !43
  store volatile <32 x i32> %36, <32 x i32> addrspace(3)* %arrayidx, align 128, !dbg !44, !intrin_attr !41
  %38 = load i32, i32* @count, align 4, !dbg !45
  %39 = load i32, i32* %max_count, align 4, !dbg !46
  %cmp1 = icmp slt i32 %38, %39, !dbg !47
  %conv2 = zext i1 %cmp1 to i32, !dbg !47
  store i32 %conv2, i32* %lc, align 4, !dbg !48
  %40 = load i32, i32* %sm_ch, align 4, !dbg !49
  %41 = call i32 @llvm.ve32.mc.complete(i32 %40), !dbg !49, !intrin_attr !26
  store i32 %41, i32* %rp, align 4, !dbg !49
  %42 = load i32, i32* %ra, align 4, !dbg !50
  %43 = load i32, i32* %rp, align 4, !dbg !50
  call void @llvm.ve32.v.xsto.32(i32 %42, i32 0, i32 %43), !dbg !50, !intrin_attr !51
  br label %while.cond, !dbg !36, !llvm.loop !52

while.end:                                        ; preds = %while.cond
  %44 = load i32, i32* @count, align 4, !dbg !55
  call void @llvm.ve32.dump(i32 56, i32 %44), !dbg !56, !intrin_attr !28
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str, i32 0, i32 0)), !dbg !57, !intrin_attr !28
  call void @llvm.ve32.printstring(i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.1, i32 0, i32 0)), !dbg !58, !intrin_attr !28
  ret void, !dbg !59
}

; Function Attrs: nounwind readonly
declare { i32, i32 } @llvm.ve32.mc.request(i32, i32) #1

; Function Attrs: nounwind readnone
declare i32 @llvm.ve32.mc.complete(i32) #2

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.v.xsto.32(i32, i32, i32) #3

; Function Attrs: nounwind readnone
declare void @llvm.ve32.dump(i32, i32) #2

; Function Attrs: nounwind readonly
declare void @llvm.ve32.printstring(i8*) #1

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.mc.reset(i32) #3

; Function Attrs: nounwind writeonly
declare void @llvm.ve32.mc.init(i32, i32) #3

; Function Attrs: nounwind readnone
declare void @llvm.ve32.mc.init.local.idc(i32, i32) #2

; Function Attrs: nounwind readonly
declare i32 @llvm.ve32.mc.get.state(i32, i32) #1

attributes #0 = { noinline nounwind uwtable "frame-pointer"="all" "hive_entry" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "stackrealign" "target-cpu"="ve32" }
attributes #1 = { nounwind readonly }
attributes #2 = { nounwind readnone }
attributes #3 = { nounwind writeonly }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!3, !4, !5, !6, !7}
!llvm.ident = !{!8}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 13.0.1", isOptimized: false, runtimeVersion: 0, emissionKind: LineTablesOnly, enums: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/consumer.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw/sim_m64")
!2 = !{}
!3 = !{i32 7, !"Dwarf Version", i32 4}
!4 = !{i32 2, !"Debug Info Version", i32 3}
!5 = !{i32 1, !"wchar_size", i32 4}
!6 = !{i32 7, !"uwtable", i32 1}
!7 = !{i32 7, !"frame-pointer", i32 2}
!8 = !{!"clang version 13.0.1"}
!9 = distinct !DISubprogram(name: "consumer_prog", scope: !10, file: !10, line: 18, type: !11, scopeLine: 19, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!10 = !DIFile(filename: "consumer.hive.c", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw")
!11 = !DISubroutineType(types: !2)
!12 = !DILocation(line: 20, column: 21, scope: !9)
!13 = !DILocation(line: 20, column: 16, scope: !9)
!14 = !DILocation(line: 23, column: 7, scope: !9)
!15 = !DILocation(line: 24, column: 7, scope: !9)
!16 = !DILocation(line: 75, column: 5, scope: !17, inlinedAt: !19)
!17 = distinct !DISubprogram(name: "semaphore_gate_init", scope: !18, file: !18, line: 72, type: !11, scopeLine: 73, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!18 = !DIFile(filename: "cir_buf.hive.h", directory: "/nfs/site/disks/xne_00001/workspace/hw/chandrbi/emulval_0p8_10Jun/abc_emul-srvrgen4/tests/rcs/gpio_timer/vex_fw")
!19 = distinct !DILocation(line: 26, column: 3, scope: !9)
!20 = !{!"WRITE_STATE"}
!21 = !DILocation(line: 35, column: 37, scope: !9)
!22 = !DILocation(line: 59, column: 5, scope: !23, inlinedAt: !24)
!23 = distinct !DISubprogram(name: "circ_buff_init", scope: !18, file: !18, line: 41, type: !11, scopeLine: 42, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !2)
!24 = distinct !DILocation(line: 35, column: 3, scope: !9)
!25 = !DILocation(line: 60, column: 5, scope: !23, inlinedAt: !24)
!26 = !{!"READ_STATE", !"WRITE_STATE"}
!27 = !DILocation(line: 61, column: 5, scope: !23, inlinedAt: !24)
!28 = !{!"VOLATILE"}
!29 = !{!"READ_STATE"}
!30 = !DILocation(line: 38, column: 9, scope: !9)
!31 = !DILocation(line: 39, column: 7, scope: !9)
!32 = !DILocation(line: 40, column: 9, scope: !9)
!33 = !DILocation(line: 40, column: 17, scope: !9)
!34 = !DILocation(line: 40, column: 15, scope: !9)
!35 = !DILocation(line: 40, column: 6, scope: !9)
!36 = !DILocation(line: 42, column: 3, scope: !9)
!37 = !DILocation(line: 42, column: 10, scope: !9)
!38 = !DILocation(line: 47, column: 5, scope: !9)
!39 = !{!"READ_STATE", !"SYNC:0", !"WRITE_STATE"}
!40 = !DILocation(line: 48, column: 36, scope: !9)
!41 = !{!"SYNC_WITH:0", !"SYNC_WITH:1"}
!42 = !DILocation(line: 48, column: 30, scope: !9)
!43 = !DILocation(line: 48, column: 6, scope: !9)
!44 = !DILocation(line: 48, column: 34, scope: !9)
!45 = !DILocation(line: 50, column: 11, scope: !9)
!46 = !DILocation(line: 50, column: 19, scope: !9)
!47 = !DILocation(line: 50, column: 17, scope: !9)
!48 = !DILocation(line: 50, column: 8, scope: !9)
!49 = !DILocation(line: 52, column: 5, scope: !9)
!50 = !DILocation(line: 53, column: 5, scope: !9)
!51 = !{!"SYNC:1"}
!52 = distinct !{!52, !36, !53, !54}
!53 = !DILocation(line: 54, column: 3, scope: !9)
!54 = !{!"llvm.loop.mustprogress"}
!55 = !DILocation(line: 56, column: 22, scope: !9)
!56 = !DILocation(line: 56, column: 3, scope: !9)
!57 = !DILocation(line: 57, column: 3, scope: !9)
!58 = !DILocation(line: 58, column: 3, scope: !9)
!59 = !DILocation(line: 59, column: 1, scope: !9)
