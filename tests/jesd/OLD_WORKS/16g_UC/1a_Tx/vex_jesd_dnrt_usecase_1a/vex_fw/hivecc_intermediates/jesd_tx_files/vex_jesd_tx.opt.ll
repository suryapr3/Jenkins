; ModuleID = 'vex_jesd_tx.c'
target datalayout = "e-m:e-p:32:32-i64:32-v64:8"
target triple = "ve32"

@g_dest_buffer0_base = common global i32 0, section "addr:0", align 4
@g_dest_buffer1_base = common global i32 0, section "addr:4", align 4
@g_dest_buffer2_base = common global i32 0, section "addr:8", align 4
@g_dest_buffer3_base = common global i32 0, section "addr:12", align 4
@g_dest_buffer4_base = common global i32 0, section "addr:16", align 4
@g_dest_buffer5_base = common global i32 0, section "addr:20", align 4
@g_dest_buffer6_base = common global i32 0, section "addr:24", align 4
@g_dest_buffer7_base = common global i32 0, section "addr:28", align 4
@g_host_indicator = common global i32 0, section "addr:32", align 4
@g_vex_exit = common global i32 0, section "addr:36", align 4
@g_timer_debug = common global i32 0, section "addr:40", align 4
@g_debug = common global i32 0, section "addr:44", align 4
@vbuffer_0 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_1 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:8192", align 128
@vbuffer_2 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:16384", align 128
@vbuffer_3 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:24576", align 128
@vbuffer_4 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:32768", align 128
@vbuffer_5 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:40960", align 128
@vbuffer_6 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_7 = common addrspace(3) global [64 x <32 x i32>] zeroinitializer, section "addr:57344", align 128

; Function Attrs: noinline nounwind uwtable
define void @jesd_tx() #0 {
entry:
  store volatile i32 0, i32* @g_host_indicator, align 4, !dbg !18
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !19
  tail call void @llvm.ve32.printstring.md(i32 0), !dbg !20
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 3, i32 3) #1, !dbg !21
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 4, i32 2048) #1, !dbg !23
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 6, i32 1) #1, !dbg !24
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 7, i32 16424) #1, !dbg !25
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 8, i32 -559038737) #1, !dbg !26
  br label %while.cond, !dbg !27

while.cond:                                       ; preds = %while.cond, %entry
  %0 = load volatile i32* @g_host_indicator, align 4, !dbg !28
  %cmp = icmp eq i32 %0, 0, !dbg !28
  br i1 %cmp, label %while.cond, label %while.end, !dbg !28

while.end:                                        ; preds = %while.cond
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 1) #1, !dbg !30
  %1 = load volatile i32* @g_vex_exit, align 4, !dbg !31
  %cmp221 = icmp eq i32 %1, 0, !dbg !31
  br i1 %cmp221, label %for.cond5.preheader, label %while.end37, !dbg !31

while.cond1.loopexit:                             ; preds = %while.end32
  %2 = load volatile i32* @g_vex_exit, align 4, !dbg !31
  %cmp2 = icmp eq i32 %2, 0, !dbg !31
  br i1 %cmp2, label %for.cond5.preheader, label %while.end37, !dbg !31

for.cond5.preheader:                              ; preds = %while.end32, %while.cond1.loopexit, %while.end
  %i.020 = phi i32 [ 0, %while.end ], [ %inc35, %while.end32 ], [ 0, %while.cond1.loopexit ]
  %mul = shl i32 %i.020, 1, !dbg !33
  %3 = load volatile i32* @g_dest_buffer0_base, align 4, !dbg !33
  %arrayidx = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_0, i32 0, i32 %mul, !dbg !33
  %4 = load <32 x i32> addrspace(3)* %arrayidx, align 128, !dbg !33
  %5 = bitcast <32 x i32> %4 to <128 x i8>, !dbg !33
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %3, i32 0, <128 x i8> %5) #1, !dbg !33
  %6 = load volatile i32* @g_dest_buffer1_base, align 4, !dbg !39
  %arrayidx10 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_1, i32 0, i32 %mul, !dbg !39
  %7 = load <32 x i32> addrspace(3)* %arrayidx10, align 128, !dbg !39
  %8 = bitcast <32 x i32> %7 to <128 x i8>, !dbg !39
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %6, i32 0, <128 x i8> %8) #1, !dbg !39
  %9 = load volatile i32* @g_dest_buffer2_base, align 4, !dbg !40
  %arrayidx13 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_2, i32 0, i32 %mul, !dbg !40
  %10 = load <32 x i32> addrspace(3)* %arrayidx13, align 128, !dbg !40
  %11 = bitcast <32 x i32> %10 to <128 x i8>, !dbg !40
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %9, i32 0, <128 x i8> %11) #1, !dbg !40
  %12 = load volatile i32* @g_dest_buffer3_base, align 4, !dbg !41
  %arrayidx16 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_3, i32 0, i32 %mul, !dbg !41
  %13 = load <32 x i32> addrspace(3)* %arrayidx16, align 128, !dbg !41
  %14 = bitcast <32 x i32> %13 to <128 x i8>, !dbg !41
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %12, i32 0, <128 x i8> %14) #1, !dbg !41
  %15 = load volatile i32* @g_dest_buffer4_base, align 4, !dbg !42
  %arrayidx19 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_4, i32 0, i32 %mul, !dbg !42
  %16 = load <32 x i32> addrspace(3)* %arrayidx19, align 128, !dbg !42
  %17 = bitcast <32 x i32> %16 to <128 x i8>, !dbg !42
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %15, i32 0, <128 x i8> %17) #1, !dbg !42
  %18 = load volatile i32* @g_dest_buffer5_base, align 4, !dbg !43
  %arrayidx22 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_5, i32 0, i32 %mul, !dbg !43
  %19 = load <32 x i32> addrspace(3)* %arrayidx22, align 128, !dbg !43
  %20 = bitcast <32 x i32> %19 to <128 x i8>, !dbg !43
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %18, i32 0, <128 x i8> %20) #1, !dbg !43
  %21 = load volatile i32* @g_dest_buffer6_base, align 4, !dbg !44
  %arrayidx25 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_6, i32 0, i32 %mul, !dbg !44
  %22 = load <32 x i32> addrspace(3)* %arrayidx25, align 128, !dbg !44
  %23 = bitcast <32 x i32> %22 to <128 x i8>, !dbg !44
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %21, i32 0, <128 x i8> %23) #1, !dbg !44
  %24 = load volatile i32* @g_dest_buffer7_base, align 4, !dbg !45
  %arrayidx28 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 %mul, !dbg !45
  %25 = load <32 x i32> addrspace(3)* %arrayidx28, align 128, !dbg !45
  %26 = bitcast <32 x i32> %25 to <128 x i8>, !dbg !45
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %24, i32 0, <128 x i8> %26) #1, !dbg !45
  %27 = load volatile i32* @g_dest_buffer0_base, align 4, !dbg !33
  %add.122 = or i32 %mul, 1, !dbg !33
  %arrayidx.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_0, i32 0, i32 %add.122, !dbg !33
  %28 = load <32 x i32> addrspace(3)* %arrayidx.1, align 128, !dbg !33
  %29 = bitcast <32 x i32> %28 to <128 x i8>, !dbg !33
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %27, i32 0, <128 x i8> %29) #1, !dbg !33
  %30 = load volatile i32* @g_dest_buffer1_base, align 4, !dbg !39
  %arrayidx10.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_1, i32 0, i32 %add.122, !dbg !39
  %31 = load <32 x i32> addrspace(3)* %arrayidx10.1, align 128, !dbg !39
  %32 = bitcast <32 x i32> %31 to <128 x i8>, !dbg !39
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %30, i32 0, <128 x i8> %32) #1, !dbg !39
  %33 = load volatile i32* @g_dest_buffer2_base, align 4, !dbg !40
  %arrayidx13.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_2, i32 0, i32 %add.122, !dbg !40
  %34 = load <32 x i32> addrspace(3)* %arrayidx13.1, align 128, !dbg !40
  %35 = bitcast <32 x i32> %34 to <128 x i8>, !dbg !40
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %33, i32 0, <128 x i8> %35) #1, !dbg !40
  %36 = load volatile i32* @g_dest_buffer3_base, align 4, !dbg !41
  %arrayidx16.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_3, i32 0, i32 %add.122, !dbg !41
  %37 = load <32 x i32> addrspace(3)* %arrayidx16.1, align 128, !dbg !41
  %38 = bitcast <32 x i32> %37 to <128 x i8>, !dbg !41
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %36, i32 0, <128 x i8> %38) #1, !dbg !41
  %39 = load volatile i32* @g_dest_buffer4_base, align 4, !dbg !42
  %arrayidx19.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_4, i32 0, i32 %add.122, !dbg !42
  %40 = load <32 x i32> addrspace(3)* %arrayidx19.1, align 128, !dbg !42
  %41 = bitcast <32 x i32> %40 to <128 x i8>, !dbg !42
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %39, i32 0, <128 x i8> %41) #1, !dbg !42
  %42 = load volatile i32* @g_dest_buffer5_base, align 4, !dbg !43
  %arrayidx22.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_5, i32 0, i32 %add.122, !dbg !43
  %43 = load <32 x i32> addrspace(3)* %arrayidx22.1, align 128, !dbg !43
  %44 = bitcast <32 x i32> %43 to <128 x i8>, !dbg !43
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %42, i32 0, <128 x i8> %44) #1, !dbg !43
  %45 = load volatile i32* @g_dest_buffer6_base, align 4, !dbg !44
  %arrayidx25.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_6, i32 0, i32 %add.122, !dbg !44
  %46 = load <32 x i32> addrspace(3)* %arrayidx25.1, align 128, !dbg !44
  %47 = bitcast <32 x i32> %46 to <128 x i8>, !dbg !44
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %45, i32 0, <128 x i8> %47) #1, !dbg !44
  %48 = load volatile i32* @g_dest_buffer7_base, align 4, !dbg !45
  %arrayidx28.1 = getelementptr [64 x <32 x i32>] addrspace(3)* @vbuffer_7, i32 0, i32 %add.122, !dbg !45
  %49 = load <32 x i32> addrspace(3)* %arrayidx28.1, align 128, !dbg !45
  %50 = bitcast <32 x i32> %49 to <128 x i8>, !dbg !45
  tail call void @llvm.ve32.v.xsto.1024.i(i32 %48, i32 0, <128 x i8> %50) #1, !dbg !45
  br label %while.cond29, !dbg !46

while.cond29:                                     ; preds = %while.cond29, %for.cond5.preheader
  %51 = load volatile i32* @g_timer_debug, align 4, !dbg !46
  %cmp30 = icmp eq i32 %51, -559038737, !dbg !46
  br i1 %cmp30, label %while.end32, label %while.cond29, !dbg !46

while.end32:                                      ; preds = %while.cond29
  store volatile i32 57005, i32* @g_timer_debug, align 4, !dbg !48
  %52 = load volatile i32* @g_debug, align 4, !dbg !49
  %inc33 = add i32 %52, 1, !dbg !49
  store volatile i32 %inc33, i32* @g_debug, align 4, !dbg !49
  %inc35 = add i32 %i.020, 1, !dbg !50
  %cmp4 = icmp slt i32 %inc35, 32, !dbg !51
  br i1 %cmp4, label %for.cond5.preheader, label %while.cond1.loopexit, !dbg !51

while.end37:                                      ; preds = %while.cond1.loopexit, %while.end
  tail call void @llvm.ve32.s.xsto.32(i32 0, i32 9, i32 2) #1, !dbg !54
  ret void, !dbg !55
}

; Function Attrs: nounwind
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #1

; Function Attrs: nounwind
declare void @llvm.ve32.s.xsto.32(i32, i32, i32) #1

; Function Attrs: nounwind
declare void @llvm.ve32.printstring.md(i32) #1

; Function Attrs: nounwind
define void @jesd_tx_entry() #2 {
  tail call void @jesd_tx(), !dbg !56
  ret void, !dbg !57
}

attributes #0 = { noinline nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { nounwind "ipu_entry" "no-frame-pointer-elim"="true" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!9, !10}
!ipu.register_structs_list = !{!2}
!llvm.ident = !{!11}
!ipu.inststrings.strings = !{!12}
!ipu_stack_base = !{!13}
!volcano.source.file = !{!14}
!volcano.command.line = !{!15}
!volcano.machine.path = !{!16}
!volcano.machine.name = !{!17}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 ", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 2} ; [ DW_TAG_compile_unit ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c] [DW_LANG_C99]
!1 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !7, metadata !8}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_tx", metadata !"jesd_tx", metadata !"", i32 108, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_tx, null, null, metadata !2, i32 109} ; [ DW_TAG_subprogram ] [line 108] [def] [scope 109] [jesd_tx]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !2, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"init_timer", metadata !"init_timer", metadata !"", i32 88, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !2, i32 89} ; [ DW_TAG_subprogram ] [line 88] [def] [scope 89] [init_timer]
!8 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_tx_entry", metadata !"jesd_tx_entry", metadata !"", i32 108, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_tx_entry, metadata !2, null, metadata !2, i32 109} ; [ DW_TAG_subprogram ] [line 108] [def] [scope 109] [jesd_tx_entry]
!9 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!10 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!11 = metadata !{metadata !"clang version 3.5.0 "}
!12 = metadata !{metadata !"jesd_tx : start \0A"}
!13 = metadata !{void ()* @jesd_tx_entry, i32 16384}
!14 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c"}
!15 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/bin/volcano -c /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/common/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include/volcano -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/include -D__HIVECC -D__VIED_CELL -D__ve32 -m /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so --target-cpu ve32 -stubs /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.stubs.h --o-optimized-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.opt.ll --o-clang-ir /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.clang.ll -emit-after-pp /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.i -D__VOLCANO_MACHINE_NAME -D__VOLCANO_MACHINE_ve32 -Wall -O3 -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/include -DHRT_CELL -DHRT_SIM_SYSTEM -DSIM_SYSTEM_RUN -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/include/iss -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw -I. -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/hrt/include -I/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/systems/abc_vex_system/common/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/include -I/nfs/site/proj/ve_hw/Released_Packages/PCT/PCT_20230111_sles12_gcc720/iirci_master_20230111_2200_sles12_gcc720/pct/Linux/host/include -o-dot-s /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.s -DVOLCANO=1 -o /nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/hivecc_intermediates/jesd_tx_files/vex_jesd_tx.o "}
!16 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/Linux/vex/cores/ve32/sdk/lib64/processor_ast.so"}
!17 = metadata !{metadata !"ve32"}
!18 = metadata !{i32 114, i32 5, metadata !4, null}
!19 = metadata !{i32 115, i32 5, metadata !4, null}
!20 = metadata !{i32 117, i32 5, metadata !4, null}
!21 = metadata !{i32 91, i32 5, metadata !7, metadata !22}
!22 = metadata !{i32 118, i32 5, metadata !4, null}
!23 = metadata !{i32 93, i32 5, metadata !7, metadata !22}
!24 = metadata !{i32 95, i32 5, metadata !7, metadata !22}
!25 = metadata !{i32 97, i32 5, metadata !7, metadata !22}
!26 = metadata !{i32 99, i32 5, metadata !7, metadata !22}
!27 = metadata !{i32 120, i32 5, metadata !4, null}
!28 = metadata !{i32 120, i32 5, metadata !29, null}
!29 = metadata !{i32 786443, metadata !1, metadata !4, i32 120, i32 5, i32 1, i32 7} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!30 = metadata !{i32 125, i32 5, metadata !4, null}
!31 = metadata !{i32 127, i32 5, metadata !32, null}
!32 = metadata !{i32 786443, metadata !1, metadata !4, i32 127, i32 5, i32 1, i32 8} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!33 = metadata !{i32 133, i32 8, metadata !34, null}
!34 = metadata !{i32 786443, metadata !1, metadata !35, i32 132, i32 7, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!35 = metadata !{i32 786443, metadata !1, metadata !36, i32 131, i32 7, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!36 = metadata !{i32 786443, metadata !1, metadata !37, i32 130, i32 9, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!37 = metadata !{i32 786443, metadata !1, metadata !38, i32 129, i32 9, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!38 = metadata !{i32 786443, metadata !1, metadata !4, i32 128, i32 5, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!39 = metadata !{i32 134, i32 8, metadata !34, null}
!40 = metadata !{i32 135, i32 8, metadata !34, null}
!41 = metadata !{i32 136, i32 8, metadata !34, null}
!42 = metadata !{i32 138, i32 8, metadata !34, null}
!43 = metadata !{i32 139, i32 8, metadata !34, null}
!44 = metadata !{i32 140, i32 8, metadata !34, null}
!45 = metadata !{i32 141, i32 8, metadata !34, null}
!46 = metadata !{i32 146, i32 13, metadata !47, null}
!47 = metadata !{i32 786443, metadata !1, metadata !36, i32 146, i32 13, i32 1, i32 12} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!48 = metadata !{i32 149, i32 13, metadata !36, null}
!49 = metadata !{i32 150, i32 13, metadata !36, null}
!50 = metadata !{i32 129, i32 36, metadata !37, null}
!51 = metadata !{i32 129, i32 13, metadata !52, null}
!52 = metadata !{i32 786443, metadata !1, metadata !53, i32 129, i32 13, i32 2, i32 13} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!53 = metadata !{i32 786443, metadata !1, metadata !37, i32 129, i32 13, i32 1, i32 9} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!54 = metadata !{i32 156, i32 5, metadata !4, null}
!55 = metadata !{i32 158, i32 1, metadata !4, null}
!56 = metadata !{i32 108, i32 0, metadata !8, null}
!57 = metadata !{i32 158, i32 1, metadata !8, null}
