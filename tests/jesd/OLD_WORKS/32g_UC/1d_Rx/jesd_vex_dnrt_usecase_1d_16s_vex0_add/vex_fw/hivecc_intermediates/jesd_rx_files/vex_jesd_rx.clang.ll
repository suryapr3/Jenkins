; ModuleID = 'vex_jesd_rx.c'
target datalayout = "e-m:e-p:32:32-i64:32-v64:8"
target triple = "ve32"

@vbuffer_0 = common global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_7 = common global [128 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_out = common global [256 x <32 x i32>] zeroinitializer, section "addr:16384", align 128
@g_num_vecs_in = common global i32 0, section "addr:12", align 4
@g_tbs_in_blk = common global i32 0, section "addr:20", align 4
@g_host_indicator = common global i32 0, section "addr:32", align 4
@g_vex_exit = common global i32 0, section "addr:36", align 4
@g_timer_debug = common global i32 0, section "addr:40", align 4
@.str = private unnamed_addr constant [18 x i8] c"jesd_tx : start \0A\00", align 1
@consumer_sm_gate = common global [16 x i32] zeroinitializer, align 128
@.str1 = private unnamed_addr constant [28 x i8] c"fu mc_get_state{1,2,3} idx=\00", align 1
@.str2 = private unnamed_addr constant [129 x i8] c"{s1}0 :#request[15] #P/C[1]#in_use[16], 1:tbs[16]ptr[16], 2:message[16],{s2} 3:addres[32], {s3} 4:blocking[1], {sg} 5:value[32]\0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define void @jesd_rx() #0 {
entry:
  %A.addr.i19.i = alloca i32, align 4, !dbg !14
  %E.addr.i20.i = alloca i32, align 4, !dbg !14
  %A.addr.i17.i = alloca i32, align 4, !dbg !16
  %E.addr.i18.i = alloca i32, align 4, !dbg !16
  %A.addr.i15.i = alloca i32, align 4, !dbg !16
  %E.addr.i16.i = alloca i32, align 4, !dbg !16
  %A.addr.i13.i = alloca i32, align 4, !dbg !16
  %E.addr.i14.i = alloca i32, align 4, !dbg !16
  %A.addr.i11.i = alloca i32, align 4, !dbg !16
  %E.addr.i12.i = alloca i32, align 4, !dbg !16
  %A.addr.i9.i = alloca i32, align 4, !dbg !16
  %E.addr.i10.i = alloca i32, align 4, !dbg !16
  %A.addr.i7.i = alloca i32, align 4, !dbg !16
  %E.addr.i8.i = alloca i32, align 4, !dbg !16
  %A.addr.i.i = alloca i32, align 4, !dbg !18
  %E.addr.i.i3 = alloca i32, align 4, !dbg !18
  %ch_type.addr.i = alloca i32, align 4, !dbg !15
  %tbs.addr.i = alloca i32, align 4, !dbg !15
  %token_per_request.addr.i = alloca i32, align 4, !dbg !15
  %loc_ptr.addr.i = alloca i32, align 4, !dbg !15
  %sm_ch.addr.i = alloca i32, align 4, !dbg !15
  %temp0.i = alloca i32, align 4, !dbg !15
  %temp1.i = alloca i32, align 4, !dbg !15
  %temp2.i = alloca i32, align 4, !dbg !15
  %temp3.i = alloca i32, align 4, !dbg !15
  %temp4.i = alloca i32, align 4, !dbg !15
  %temp5.i = alloca i32, align 4, !dbg !15
  %E.addr.i = alloca i32, align 4, !dbg !19
  %E.addr.i.i = alloca i32, align 4, !dbg !21
  %iter_max = alloca i32, align 4
  %sm_ch = alloca i32, align 4
  %vex_dest_buffer = alloca i32, align 4
  %compare_offset = alloca i32, align 4
  %index = alloca i32, align 4
  %is_data_ready = alloca i32, align 4
  %idx = alloca i32, align 4
  %ptr = alloca i32, align 4
  %i = alloca i32, align 4
  %vout = alloca <32 x i32>, align 128
  %0 = load volatile i32* @g_num_vecs_in, align 4, !dbg !23
  store i32 %0, i32* %iter_max, align 4, !dbg !23
  store i32 0, i32* %sm_ch, align 4, !dbg !24
  store i32 16384, i32* %vex_dest_buffer, align 4, !dbg !25
  store i32 0, i32* %compare_offset, align 4, !dbg !26
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !27
  call void @OP___printstring(i8* getelementptr inbounds ([18 x i8]* @.str, i32 0, i32 0)), !dbg !28
  store i32 0, i32* %E.addr.i.i, align 4, !dbg !21
  %1 = load i32* %E.addr.i.i, align 4, !dbg !21
  call void @llvm.ve32.mc.reset(i32 %1) #4, !dbg !21
  %2 = load volatile i32* @g_tbs_in_blk, align 4, !dbg !15
  %3 = load i32* %sm_ch, align 4, !dbg !15
  store i32 65536, i32* %ch_type.addr.i, align 4, !dbg !15
  store i32 %2, i32* %tbs.addr.i, align 4, !dbg !15
  store i32 1, i32* %token_per_request.addr.i, align 4, !dbg !15
  store i32 0, i32* %loc_ptr.addr.i, align 4, !dbg !15
  store i32 %3, i32* %sm_ch.addr.i, align 4, !dbg !15
  %4 = load i32* %tbs.addr.i, align 4, !dbg !18
  %5 = load i32* %token_per_request.addr.i, align 4, !dbg !18
  %shl.i = shl i32 %5, 17, !dbg !18
  %add.i = add i32 %4, %shl.i, !dbg !18
  %6 = load i32* %ch_type.addr.i, align 4, !dbg !18
  %add1.i = add i32 %add.i, %6, !dbg !18
  %7 = load i32* %sm_ch.addr.i, align 4, !dbg !18
  store i32 %add1.i, i32* %A.addr.i.i, align 4, !dbg !18
  store i32 %7, i32* %E.addr.i.i3, align 4, !dbg !18
  %8 = load i32* %A.addr.i.i, align 4, !dbg !18
  %9 = load i32* %E.addr.i.i3, align 4, !dbg !18
  call void @llvm.ve32.mc.init(i32 %8, i32 %9) #4, !dbg !18
  %10 = load i32* %loc_ptr.addr.i, align 4, !dbg !14
  %11 = load i32* %sm_ch.addr.i, align 4, !dbg !14
  store i32 %10, i32* %A.addr.i19.i, align 4, !dbg !14
  store i32 %11, i32* %E.addr.i20.i, align 4, !dbg !14
  %12 = load i32* %A.addr.i19.i, align 4, !dbg !14
  %13 = load i32* %E.addr.i20.i, align 4, !dbg !14
  call void @llvm.ve32.mc.init.local.idc(i32 %12, i32 %13) #4, !dbg !14
  call void @OP___printstring(i8* getelementptr inbounds ([28 x i8]* @.str1, i32 0, i32 0)) #4, !dbg !16
  %14 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  %15 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 %14, i32 %15) #4, !dbg !16
  call void @OP___printstring(i8* getelementptr inbounds ([129 x i8]* @.str2, i32 0, i32 0)) #4, !dbg !16
  %16 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 0, i32* %A.addr.i17.i, align 4, !dbg !16
  store i32 %16, i32* %E.addr.i18.i, align 4, !dbg !16
  %17 = load i32* %A.addr.i17.i, align 4, !dbg !16
  %18 = load i32* %E.addr.i18.i, align 4, !dbg !16
  %19 = call i32 @llvm.ve32.mc.get.state(i32 %17, i32 %18) #4, !dbg !16
  store i32 %19, i32* %temp0.i, align 4, !dbg !16
  %20 = load i32* %temp0.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 0, i32 %20) #4, !dbg !16
  %21 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 1, i32* %A.addr.i15.i, align 4, !dbg !16
  store i32 %21, i32* %E.addr.i16.i, align 4, !dbg !16
  %22 = load i32* %A.addr.i15.i, align 4, !dbg !16
  %23 = load i32* %E.addr.i16.i, align 4, !dbg !16
  %24 = call i32 @llvm.ve32.mc.get.state(i32 %22, i32 %23) #4, !dbg !16
  store i32 %24, i32* %temp1.i, align 4, !dbg !16
  %25 = load i32* %temp1.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 1, i32 %25) #4, !dbg !16
  %26 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 2, i32* %A.addr.i13.i, align 4, !dbg !16
  store i32 %26, i32* %E.addr.i14.i, align 4, !dbg !16
  %27 = load i32* %A.addr.i13.i, align 4, !dbg !16
  %28 = load i32* %E.addr.i14.i, align 4, !dbg !16
  %29 = call i32 @llvm.ve32.mc.get.state(i32 %27, i32 %28) #4, !dbg !16
  store i32 %29, i32* %temp2.i, align 4, !dbg !16
  %30 = load i32* %temp2.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 2, i32 %30) #4, !dbg !16
  %31 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 3, i32* %A.addr.i11.i, align 4, !dbg !16
  store i32 %31, i32* %E.addr.i12.i, align 4, !dbg !16
  %32 = load i32* %A.addr.i11.i, align 4, !dbg !16
  %33 = load i32* %E.addr.i12.i, align 4, !dbg !16
  %34 = call i32 @llvm.ve32.mc.get.state(i32 %32, i32 %33) #4, !dbg !16
  store i32 %34, i32* %temp3.i, align 4, !dbg !16
  %35 = load i32* %temp3.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 3, i32 %35) #4, !dbg !16
  %36 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 4, i32* %A.addr.i9.i, align 4, !dbg !16
  store i32 %36, i32* %E.addr.i10.i, align 4, !dbg !16
  %37 = load i32* %A.addr.i9.i, align 4, !dbg !16
  %38 = load i32* %E.addr.i10.i, align 4, !dbg !16
  %39 = call i32 @llvm.ve32.mc.get.state(i32 %37, i32 %38) #4, !dbg !16
  store i32 %39, i32* %temp4.i, align 4, !dbg !16
  %40 = load i32* %temp4.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 4, i32 %40) #4, !dbg !16
  %41 = load i32* %sm_ch.addr.i, align 4, !dbg !16
  store i32 5, i32* %A.addr.i7.i, align 4, !dbg !16
  store i32 %41, i32* %E.addr.i8.i, align 4, !dbg !16
  %42 = load i32* %A.addr.i7.i, align 4, !dbg !16
  %43 = load i32* %E.addr.i8.i, align 4, !dbg !16
  %44 = call i32 @llvm.ve32.mc.get.state(i32 %42, i32 %43) #4, !dbg !16
  store i32 %44, i32* %temp5.i, align 4, !dbg !16
  %45 = load i32* %temp5.i, align 4, !dbg !16
  call void @_Z9OP___dumpii(i32 5, i32 %45) #4, !dbg !16
  br label %while.cond, !dbg !29

while.cond:                                       ; preds = %for.end, %entry
  %46 = load volatile i32* @g_vex_exit, align 4, !dbg !30
  %cmp = icmp eq i32 %46, 0, !dbg !30
  br i1 %cmp, label %while.body, label %while.end, !dbg !30

while.body:                                       ; preds = %while.cond
  store i32 0, i32* %index, align 4, !dbg !32
  %47 = load i32* %sm_ch, align 4, !dbg !33
  %48 = call { i32, i32 } @llvm.ve32.mc.request(i32 1, i32 %47), !dbg !33, !intrin_attr !34
  %49 = extractvalue { i32, i32 } %48, 1, !dbg !33
  store i32 %49, i32* %idx, !dbg !33
  %50 = extractvalue { i32, i32 } %48, 0, !dbg !33
  store i32 %50, i32* %is_data_ready, align 4, !dbg !33
  store i32 0, i32* %i, align 4, !dbg !35
  br label %for.cond, !dbg !35

for.cond:                                         ; preds = %for.inc, %while.body
  %51 = load i32* %i, align 4, !dbg !37
  %52 = load i32* %iter_max, align 4, !dbg !37
  %cmp1 = icmp slt i32 %51, %52, !dbg !37
  br i1 %cmp1, label %for.body, label %for.end, !dbg !37

for.body:                                         ; preds = %for.cond
  store <32 x i32> undef, <32 x i32>* %vout, align 128, !dbg !40
  %53 = load i32* %vex_dest_buffer, align 4, !dbg !42, !no_alias !43
  %54 = load i32* %compare_offset, align 4, !dbg !42, !no_alias !43
  %55 = call { <32 x i32>, i32 } @llvm.ve32.v.ldoi.1024.circ(i32 %53, i32 %54, i32 134250368, i32 32640), !dbg !42, !intrin_attr !44, !no_alias !43
  %56 = extractvalue { <32 x i32>, i32 } %55, 1, !dbg !42
  store i32 %56, i32* %compare_offset, !dbg !42, !no_alias !43
  %57 = extractvalue { <32 x i32>, i32 } %55, 0, !dbg !42
  store <32 x i32> %57, <32 x i32>* %vout, align 128, !dbg !42, !no_alias !43
  %58 = load <32 x i32>* %vout, align 128, !dbg !45
  %59 = load i32* %index, align 4, !dbg !45
  %rem = srem i32 %59, 128, !dbg !45
  %arrayidx = getelementptr [128 x <32 x i32>]* @vbuffer_7, i32 0, i32 %rem, !dbg !45
  store <32 x i32> %58, <32 x i32>* %arrayidx, align 128, !dbg !45
  br label %for.inc, !dbg !46

for.inc:                                          ; preds = %for.body
  %60 = load i32* %i, align 4, !dbg !47
  %inc = add i32 %60, 1, !dbg !47
  store i32 %inc, i32* %i, align 4, !dbg !47
  br label %for.cond, !dbg !47

for.end:                                          ; preds = %for.cond
  %61 = load i32* %index, align 4, !dbg !48
  %inc2 = add i32 %61, 1, !dbg !48
  store i32 %inc2, i32* %index, align 4, !dbg !48
  %62 = load i32* %sm_ch, align 4, !dbg !19
  store i32 %62, i32* %E.addr.i, align 4, !dbg !19
  %63 = load i32* %E.addr.i, align 4, !dbg !19
  %64 = call i32 @llvm.ve32.mc.complete(i32 %63) #4, !dbg !19
  store i32 %64, i32* %ptr, align 4, !dbg !19
  br label %while.cond, !dbg !49

while.end:                                        ; preds = %while.cond
  ret void, !dbg !50
}

declare void @OP___printstring(i8*) #1

; Function Attrs: nounwind readonly
declare { i32, i32 } @llvm.ve32.mc.request(i32, i32) #2

; Function Attrs: nounwind readonly
declare { <32 x i32>, i32 } @llvm.ve32.v.ldoi.1024.circ(i32, i32, i32, i32) #2

; Function Attrs: nounwind readnone
declare i32 @llvm.ve32.mc.complete(i32) #3

declare void @_Z9OP___dumpii(i32, i32) #1

; Function Attrs: nounwind readonly
declare i32 @llvm.ve32.mc.get.state(i32, i32) #2

; Function Attrs: nounwind readnone
declare void @llvm.ve32.mc.init.local.idc(i32, i32) #3

; Function Attrs: nounwind
declare void @llvm.ve32.mc.init(i32, i32) #4

; Function Attrs: nounwind
declare void @llvm.ve32.mc.reset(i32) #4

attributes #0 = { noinline nounwind uwtable "ipu_entry" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readonly }
attributes #3 = { nounwind readnone }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!11, !12}
!ipu.register_structs_list = !{!2}
!llvm.ident = !{!13}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 ", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 2} ; [ DW_TAG_compile_unit ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c] [DW_LANG_C99]
!1 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !7, metadata !10}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_rx", metadata !"jesd_rx", metadata !"", i32 104, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_rx, null, null, metadata !2, i32 105} ; [ DW_TAG_subprogram ] [line 104] [def] [scope 105] [jesd_rx]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !2, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{i32 786478, metadata !8, metadata !9, metadata !"circ_buff_init", metadata !"circ_buff_init", metadata !"", i32 60, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !2, i32 61} ; [ DW_TAG_subprogram ] [line 60] [def] [scope 61] [circ_buff_init]
!8 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64"}
!9 = metadata !{i32 786473, metadata !8}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h]
!10 = metadata !{i32 786478, metadata !8, metadata !9, metadata !"semaphore_gate_init", metadata !"semaphore_gate_init", metadata !"", i32 92, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, null, null, null, metadata !2, i32 93} ; [ DW_TAG_subprogram ] [line 92] [def] [scope 93] [semaphore_gate_init]
!11 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!12 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!13 = metadata !{metadata !"clang version 3.5.0 "}
!14 = metadata !{i32 79, i32 5, metadata !7, metadata !15}
!15 = metadata !{i32 125, i32 5, metadata !4, null}
!16 = metadata !{i32 80, i32 5, metadata !17, metadata !15}
!17 = metadata !{i32 786443, metadata !8, metadata !7, i32 80, i32 5, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/cir_buf.hive.h]
!18 = metadata !{i32 78, i32 5, metadata !7, metadata !15}
!19 = metadata !{i32 145, i32 3, metadata !20, null}
!20 = metadata !{i32 786443, metadata !1, metadata !4, i32 129, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!21 = metadata !{i32 95, i32 5, metadata !10, metadata !22}
!22 = metadata !{i32 115, i32 5, metadata !4, null}
!23 = metadata !{i32 106, i32 5, metadata !4, null}
!24 = metadata !{i32 107, i32 5, metadata !4, null}
!25 = metadata !{i32 108, i32 5, metadata !4, null}
!26 = metadata !{i32 109, i32 5, metadata !4, null}
!27 = metadata !{i32 111, i32 5, metadata !4, null}
!28 = metadata !{i32 113, i32 5, metadata !4, null}
!29 = metadata !{i32 128, i32 5, metadata !4, null}
!30 = metadata !{i32 128, i32 5, metadata !31, null}
!31 = metadata !{i32 786443, metadata !1, metadata !4, i32 128, i32 5, i32 1, i32 4} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!32 = metadata !{i32 130, i32 3, metadata !20, null}
!33 = metadata !{i32 133, i32 9, metadata !20, null}
!34 = metadata !{metadata !"SYNC:0"}
!35 = metadata !{i32 135, i32 14, metadata !36, null}
!36 = metadata !{i32 786443, metadata !1, metadata !20, i32 135, i32 9, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!37 = metadata !{i32 135, i32 14, metadata !38, null}
!38 = metadata !{i32 786443, metadata !1, metadata !39, i32 135, i32 14, i32 2, i32 6} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!39 = metadata !{i32 786443, metadata !1, metadata !36, i32 135, i32 14, i32 1, i32 5} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!40 = metadata !{i32 137, i32 5, metadata !41, null}
!41 = metadata !{i32 786443, metadata !1, metadata !36, i32 136, i32 9, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/jesd_vex_dnrt_usecase/vex_fw/vex_jesd_rx.c]
!42 = metadata !{i32 139, i32 11, metadata !41, null}
!43 = metadata !{metadata !"no_alias"}
!44 = metadata !{metadata !"SYNC_WITH:0"}
!45 = metadata !{i32 141, i32 11, metadata !41, null}
!46 = metadata !{i32 143, i32 3, metadata !41, null}
!47 = metadata !{i32 135, i32 39, metadata !36, null}
!48 = metadata !{i32 144, i32 3, metadata !20, null}
!49 = metadata !{i32 147, i32 5, metadata !20, null}
!50 = metadata !{i32 151, i32 1, metadata !4, null}
