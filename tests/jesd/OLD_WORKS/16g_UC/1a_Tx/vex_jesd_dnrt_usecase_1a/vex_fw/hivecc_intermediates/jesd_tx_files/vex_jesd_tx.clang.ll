; ModuleID = 'vex_jesd_tx.c'
target datalayout = "e-m:e-p:32:32-i64:32-v64:8"
target triple = "ve32"

@vbuffer_0 = common global [64 x <32 x i32>] zeroinitializer, section "addr:0", align 128
@vbuffer_1 = common global [64 x <32 x i32>] zeroinitializer, section "addr:8192", align 128
@vbuffer_2 = common global [64 x <32 x i32>] zeroinitializer, section "addr:16384", align 128
@vbuffer_3 = common global [64 x <32 x i32>] zeroinitializer, section "addr:24576", align 128
@vbuffer_4 = common global [64 x <32 x i32>] zeroinitializer, section "addr:32768", align 128
@vbuffer_5 = common global [64 x <32 x i32>] zeroinitializer, section "addr:40960", align 128
@vbuffer_6 = common global [64 x <32 x i32>] zeroinitializer, section "addr:49152", align 128
@vbuffer_7 = common global [64 x <32 x i32>] zeroinitializer, section "addr:57344", align 128
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
@.str = private unnamed_addr constant [18 x i8] c"jesd_tx : start \0A\00", align 1

; Function Attrs: noinline nounwind uwtable
define void @jesd_tx() #0 {
entry:
  %A.addr.i61 = alloca i32, align 4, !dbg !11
  %B.addr.i62 = alloca i32, align 4, !dbg !11
  %C.addr.i63 = alloca i32, align 4, !dbg !11
  %A.addr.i58 = alloca i32, align 4, !dbg !12
  %B.addr.i59 = alloca i32, align 4, !dbg !12
  %D0.addr.i60 = alloca <128 x i8>, align 128, !dbg !12
  %A.addr.i55 = alloca i32, align 4, !dbg !18
  %B.addr.i56 = alloca i32, align 4, !dbg !18
  %D0.addr.i57 = alloca <128 x i8>, align 128, !dbg !18
  %A.addr.i52 = alloca i32, align 4, !dbg !19
  %B.addr.i53 = alloca i32, align 4, !dbg !19
  %D0.addr.i54 = alloca <128 x i8>, align 128, !dbg !19
  %A.addr.i49 = alloca i32, align 4, !dbg !20
  %B.addr.i50 = alloca i32, align 4, !dbg !20
  %D0.addr.i51 = alloca <128 x i8>, align 128, !dbg !20
  %A.addr.i46 = alloca i32, align 4, !dbg !21
  %B.addr.i47 = alloca i32, align 4, !dbg !21
  %D0.addr.i48 = alloca <128 x i8>, align 128, !dbg !21
  %A.addr.i43 = alloca i32, align 4, !dbg !22
  %B.addr.i44 = alloca i32, align 4, !dbg !22
  %D0.addr.i45 = alloca <128 x i8>, align 128, !dbg !22
  %A.addr.i40 = alloca i32, align 4, !dbg !23
  %B.addr.i41 = alloca i32, align 4, !dbg !23
  %D0.addr.i42 = alloca <128 x i8>, align 128, !dbg !23
  %A.addr.i38 = alloca i32, align 4, !dbg !24
  %B.addr.i39 = alloca i32, align 4, !dbg !24
  %D0.addr.i = alloca <128 x i8>, align 128, !dbg !24
  %A.addr.i = alloca i32, align 4, !dbg !25
  %B.addr.i = alloca i32, align 4, !dbg !25
  %C.addr.i = alloca i32, align 4, !dbg !25
  %A.addr.i10.i = alloca i32, align 4, !dbg !26
  %B.addr.i11.i = alloca i32, align 4, !dbg !26
  %C.addr.i12.i = alloca i32, align 4, !dbg !26
  %A.addr.i7.i = alloca i32, align 4, !dbg !28
  %B.addr.i8.i = alloca i32, align 4, !dbg !28
  %C.addr.i9.i = alloca i32, align 4, !dbg !28
  %A.addr.i4.i = alloca i32, align 4, !dbg !29
  %B.addr.i5.i = alloca i32, align 4, !dbg !29
  %C.addr.i6.i = alloca i32, align 4, !dbg !29
  %A.addr.i1.i = alloca i32, align 4, !dbg !30
  %B.addr.i2.i = alloca i32, align 4, !dbg !30
  %C.addr.i3.i = alloca i32, align 4, !dbg !30
  %A.addr.i.i = alloca i32, align 4, !dbg !31
  %B.addr.i.i = alloca i32, align 4, !dbg !31
  %C.addr.i.i = alloca i32, align 4, !dbg !31
  %cycles.addr.i = alloca i32, align 4, !dbg !27
  %i = alloca i32, align 4
  %j = alloca i32, align 4
  %iter_max = alloca i32, align 4
  %num_vec_per_stream = alloca i32, align 4
  store i32 32, i32* %iter_max, align 4, !dbg !32
  store i32 2, i32* %num_vec_per_stream, align 4, !dbg !33
  store volatile i32 0, i32* @g_host_indicator, align 4, !dbg !34
  store volatile i32 0, i32* @g_vex_exit, align 4, !dbg !35
  call void @OP___printstring(i8* getelementptr inbounds ([18 x i8]* @.str, i32 0, i32 0)), !dbg !36
  store i32 2048, i32* %cycles.addr.i, align 4, !dbg !27
  store i32 0, i32* %A.addr.i.i, align 4, !dbg !31
  store i32 3, i32* %B.addr.i.i, align 4, !dbg !31
  store i32 3, i32* %C.addr.i.i, align 4, !dbg !31
  %0 = load i32* %A.addr.i.i, align 4, !dbg !31
  %1 = load i32* %B.addr.i.i, align 4, !dbg !31
  %2 = load i32* %C.addr.i.i, align 4, !dbg !31
  call void @llvm.ve32.s.xsto.32(i32 %0, i32 %1, i32 %2) #2, !dbg !31
  %3 = load i32* %cycles.addr.i, align 4, !dbg !26
  store i32 0, i32* %A.addr.i10.i, align 4, !dbg !26
  store i32 4, i32* %B.addr.i11.i, align 4, !dbg !26
  store i32 %3, i32* %C.addr.i12.i, align 4, !dbg !26
  %4 = load i32* %A.addr.i10.i, align 4, !dbg !26
  %5 = load i32* %B.addr.i11.i, align 4, !dbg !26
  %6 = load i32* %C.addr.i12.i, align 4, !dbg !26
  call void @llvm.ve32.s.xsto.32(i32 %4, i32 %5, i32 %6) #2, !dbg !26
  store i32 0, i32* %A.addr.i7.i, align 4, !dbg !28
  store i32 6, i32* %B.addr.i8.i, align 4, !dbg !28
  store i32 1, i32* %C.addr.i9.i, align 4, !dbg !28
  %7 = load i32* %A.addr.i7.i, align 4, !dbg !28
  %8 = load i32* %B.addr.i8.i, align 4, !dbg !28
  %9 = load i32* %C.addr.i9.i, align 4, !dbg !28
  call void @llvm.ve32.s.xsto.32(i32 %7, i32 %8, i32 %9) #2, !dbg !28
  store i32 0, i32* %A.addr.i4.i, align 4, !dbg !29
  store i32 7, i32* %B.addr.i5.i, align 4, !dbg !29
  store i32 16424, i32* %C.addr.i6.i, align 4, !dbg !29
  %10 = load i32* %A.addr.i4.i, align 4, !dbg !29
  %11 = load i32* %B.addr.i5.i, align 4, !dbg !29
  %12 = load i32* %C.addr.i6.i, align 4, !dbg !29
  call void @llvm.ve32.s.xsto.32(i32 %10, i32 %11, i32 %12) #2, !dbg !29
  store i32 0, i32* %A.addr.i1.i, align 4, !dbg !30
  store i32 8, i32* %B.addr.i2.i, align 4, !dbg !30
  store i32 -559038737, i32* %C.addr.i3.i, align 4, !dbg !30
  %13 = load i32* %A.addr.i1.i, align 4, !dbg !30
  %14 = load i32* %B.addr.i2.i, align 4, !dbg !30
  %15 = load i32* %C.addr.i3.i, align 4, !dbg !30
  call void @llvm.ve32.s.xsto.32(i32 %13, i32 %14, i32 %15) #2, !dbg !30
  br label %while.cond, !dbg !37

while.cond:                                       ; preds = %while.body, %entry
  %16 = load volatile i32* @g_host_indicator, align 4, !dbg !38
  %cmp = icmp eq i32 %16, 0, !dbg !38
  br i1 %cmp, label %while.body, label %while.end, !dbg !38

while.body:                                       ; preds = %while.cond
  br label %while.cond, !dbg !40

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %A.addr.i61, align 4, !dbg !11
  store i32 9, i32* %B.addr.i62, align 4, !dbg !11
  store i32 1, i32* %C.addr.i63, align 4, !dbg !11
  %17 = load i32* %A.addr.i61, align 4, !dbg !11
  %18 = load i32* %B.addr.i62, align 4, !dbg !11
  %19 = load i32* %C.addr.i63, align 4, !dbg !11
  call void @llvm.ve32.s.xsto.32(i32 %17, i32 %18, i32 %19) #2, !dbg !11
  br label %while.cond1, !dbg !42

while.cond1:                                      ; preds = %for.end36, %while.end
  %20 = load volatile i32* @g_vex_exit, align 4, !dbg !43
  %cmp2 = icmp eq i32 %20, 0, !dbg !43
  br i1 %cmp2, label %while.body3, label %while.end37, !dbg !43

while.body3:                                      ; preds = %while.cond1
  store i32 0, i32* %i, align 4, !dbg !45
  br label %for.cond, !dbg !45

for.cond:                                         ; preds = %for.inc34, %while.body3
  %21 = load i32* %i, align 4, !dbg !46
  %22 = load i32* %iter_max, align 4, !dbg !46
  %cmp4 = icmp slt i32 %21, %22, !dbg !46
  br i1 %cmp4, label %for.body, label %for.end36, !dbg !46

for.body:                                         ; preds = %for.cond
  store i32 0, i32* %j, align 4, !dbg !49
  br label %for.cond5, !dbg !49

for.cond5:                                        ; preds = %for.inc, %for.body
  %23 = load i32* %j, align 4, !dbg !50
  %24 = load i32* %num_vec_per_stream, align 4, !dbg !50
  %cmp6 = icmp slt i32 %23, %24, !dbg !50
  br i1 %cmp6, label %for.body7, label %for.end, !dbg !50

for.body7:                                        ; preds = %for.cond5
  %25 = load volatile i32* @g_dest_buffer0_base, align 4, !dbg !12
  %26 = load i32* %i, align 4, !dbg !12
  %mul = mul i32 %26, 2, !dbg !12
  %27 = load i32* %j, align 4, !dbg !12
  %add = add i32 %mul, %27, !dbg !12
  %arrayidx = getelementptr [64 x <32 x i32>]* @vbuffer_0, i32 0, i32 %add, !dbg !12
  %28 = load <32 x i32>* %arrayidx, align 128, !dbg !12
  %29 = bitcast <32 x i32> %28 to <128 x i8>, !dbg !12
  store i32 %25, i32* %A.addr.i58, align 4, !dbg !12
  store i32 0, i32* %B.addr.i59, align 4, !dbg !12
  store <128 x i8> %29, <128 x i8>* %D0.addr.i60, align 128, !dbg !12
  %30 = load i32* %A.addr.i58, align 4, !dbg !12
  %31 = load i32* %B.addr.i59, align 4, !dbg !12
  %32 = load <128 x i8>* %D0.addr.i60, align 128, !dbg !12
  call void @llvm.ve32.v.xsto.1024.i(i32 %30, i32 %31, <128 x i8> %32) #2, !dbg !12
  %33 = load volatile i32* @g_dest_buffer1_base, align 4, !dbg !18
  %34 = load i32* %i, align 4, !dbg !18
  %mul8 = mul i32 %34, 2, !dbg !18
  %35 = load i32* %j, align 4, !dbg !18
  %add9 = add i32 %mul8, %35, !dbg !18
  %arrayidx10 = getelementptr [64 x <32 x i32>]* @vbuffer_1, i32 0, i32 %add9, !dbg !18
  %36 = load <32 x i32>* %arrayidx10, align 128, !dbg !18
  %37 = bitcast <32 x i32> %36 to <128 x i8>, !dbg !18
  store i32 %33, i32* %A.addr.i55, align 4, !dbg !18
  store i32 0, i32* %B.addr.i56, align 4, !dbg !18
  store <128 x i8> %37, <128 x i8>* %D0.addr.i57, align 128, !dbg !18
  %38 = load i32* %A.addr.i55, align 4, !dbg !18
  %39 = load i32* %B.addr.i56, align 4, !dbg !18
  %40 = load <128 x i8>* %D0.addr.i57, align 128, !dbg !18
  call void @llvm.ve32.v.xsto.1024.i(i32 %38, i32 %39, <128 x i8> %40) #2, !dbg !18
  %41 = load volatile i32* @g_dest_buffer2_base, align 4, !dbg !19
  %42 = load i32* %i, align 4, !dbg !19
  %mul11 = mul i32 %42, 2, !dbg !19
  %43 = load i32* %j, align 4, !dbg !19
  %add12 = add i32 %mul11, %43, !dbg !19
  %arrayidx13 = getelementptr [64 x <32 x i32>]* @vbuffer_2, i32 0, i32 %add12, !dbg !19
  %44 = load <32 x i32>* %arrayidx13, align 128, !dbg !19
  %45 = bitcast <32 x i32> %44 to <128 x i8>, !dbg !19
  store i32 %41, i32* %A.addr.i52, align 4, !dbg !19
  store i32 0, i32* %B.addr.i53, align 4, !dbg !19
  store <128 x i8> %45, <128 x i8>* %D0.addr.i54, align 128, !dbg !19
  %46 = load i32* %A.addr.i52, align 4, !dbg !19
  %47 = load i32* %B.addr.i53, align 4, !dbg !19
  %48 = load <128 x i8>* %D0.addr.i54, align 128, !dbg !19
  call void @llvm.ve32.v.xsto.1024.i(i32 %46, i32 %47, <128 x i8> %48) #2, !dbg !19
  %49 = load volatile i32* @g_dest_buffer3_base, align 4, !dbg !20
  %50 = load i32* %i, align 4, !dbg !20
  %mul14 = mul i32 %50, 2, !dbg !20
  %51 = load i32* %j, align 4, !dbg !20
  %add15 = add i32 %mul14, %51, !dbg !20
  %arrayidx16 = getelementptr [64 x <32 x i32>]* @vbuffer_3, i32 0, i32 %add15, !dbg !20
  %52 = load <32 x i32>* %arrayidx16, align 128, !dbg !20
  %53 = bitcast <32 x i32> %52 to <128 x i8>, !dbg !20
  store i32 %49, i32* %A.addr.i49, align 4, !dbg !20
  store i32 0, i32* %B.addr.i50, align 4, !dbg !20
  store <128 x i8> %53, <128 x i8>* %D0.addr.i51, align 128, !dbg !20
  %54 = load i32* %A.addr.i49, align 4, !dbg !20
  %55 = load i32* %B.addr.i50, align 4, !dbg !20
  %56 = load <128 x i8>* %D0.addr.i51, align 128, !dbg !20
  call void @llvm.ve32.v.xsto.1024.i(i32 %54, i32 %55, <128 x i8> %56) #2, !dbg !20
  %57 = load volatile i32* @g_dest_buffer4_base, align 4, !dbg !21
  %58 = load i32* %i, align 4, !dbg !21
  %mul17 = mul i32 %58, 2, !dbg !21
  %59 = load i32* %j, align 4, !dbg !21
  %add18 = add i32 %mul17, %59, !dbg !21
  %arrayidx19 = getelementptr [64 x <32 x i32>]* @vbuffer_4, i32 0, i32 %add18, !dbg !21
  %60 = load <32 x i32>* %arrayidx19, align 128, !dbg !21
  %61 = bitcast <32 x i32> %60 to <128 x i8>, !dbg !21
  store i32 %57, i32* %A.addr.i46, align 4, !dbg !21
  store i32 0, i32* %B.addr.i47, align 4, !dbg !21
  store <128 x i8> %61, <128 x i8>* %D0.addr.i48, align 128, !dbg !21
  %62 = load i32* %A.addr.i46, align 4, !dbg !21
  %63 = load i32* %B.addr.i47, align 4, !dbg !21
  %64 = load <128 x i8>* %D0.addr.i48, align 128, !dbg !21
  call void @llvm.ve32.v.xsto.1024.i(i32 %62, i32 %63, <128 x i8> %64) #2, !dbg !21
  %65 = load volatile i32* @g_dest_buffer5_base, align 4, !dbg !22
  %66 = load i32* %i, align 4, !dbg !22
  %mul20 = mul i32 %66, 2, !dbg !22
  %67 = load i32* %j, align 4, !dbg !22
  %add21 = add i32 %mul20, %67, !dbg !22
  %arrayidx22 = getelementptr [64 x <32 x i32>]* @vbuffer_5, i32 0, i32 %add21, !dbg !22
  %68 = load <32 x i32>* %arrayidx22, align 128, !dbg !22
  %69 = bitcast <32 x i32> %68 to <128 x i8>, !dbg !22
  store i32 %65, i32* %A.addr.i43, align 4, !dbg !22
  store i32 0, i32* %B.addr.i44, align 4, !dbg !22
  store <128 x i8> %69, <128 x i8>* %D0.addr.i45, align 128, !dbg !22
  %70 = load i32* %A.addr.i43, align 4, !dbg !22
  %71 = load i32* %B.addr.i44, align 4, !dbg !22
  %72 = load <128 x i8>* %D0.addr.i45, align 128, !dbg !22
  call void @llvm.ve32.v.xsto.1024.i(i32 %70, i32 %71, <128 x i8> %72) #2, !dbg !22
  %73 = load volatile i32* @g_dest_buffer6_base, align 4, !dbg !23
  %74 = load i32* %i, align 4, !dbg !23
  %mul23 = mul i32 %74, 2, !dbg !23
  %75 = load i32* %j, align 4, !dbg !23
  %add24 = add i32 %mul23, %75, !dbg !23
  %arrayidx25 = getelementptr [64 x <32 x i32>]* @vbuffer_6, i32 0, i32 %add24, !dbg !23
  %76 = load <32 x i32>* %arrayidx25, align 128, !dbg !23
  %77 = bitcast <32 x i32> %76 to <128 x i8>, !dbg !23
  store i32 %73, i32* %A.addr.i40, align 4, !dbg !23
  store i32 0, i32* %B.addr.i41, align 4, !dbg !23
  store <128 x i8> %77, <128 x i8>* %D0.addr.i42, align 128, !dbg !23
  %78 = load i32* %A.addr.i40, align 4, !dbg !23
  %79 = load i32* %B.addr.i41, align 4, !dbg !23
  %80 = load <128 x i8>* %D0.addr.i42, align 128, !dbg !23
  call void @llvm.ve32.v.xsto.1024.i(i32 %78, i32 %79, <128 x i8> %80) #2, !dbg !23
  %81 = load volatile i32* @g_dest_buffer7_base, align 4, !dbg !24
  %82 = load i32* %i, align 4, !dbg !24
  %mul26 = mul i32 %82, 2, !dbg !24
  %83 = load i32* %j, align 4, !dbg !24
  %add27 = add i32 %mul26, %83, !dbg !24
  %arrayidx28 = getelementptr [64 x <32 x i32>]* @vbuffer_7, i32 0, i32 %add27, !dbg !24
  %84 = load <32 x i32>* %arrayidx28, align 128, !dbg !24
  %85 = bitcast <32 x i32> %84 to <128 x i8>, !dbg !24
  store i32 %81, i32* %A.addr.i38, align 4, !dbg !24
  store i32 0, i32* %B.addr.i39, align 4, !dbg !24
  store <128 x i8> %85, <128 x i8>* %D0.addr.i, align 128, !dbg !24
  %86 = load i32* %A.addr.i38, align 4, !dbg !24
  %87 = load i32* %B.addr.i39, align 4, !dbg !24
  %88 = load <128 x i8>* %D0.addr.i, align 128, !dbg !24
  call void @llvm.ve32.v.xsto.1024.i(i32 %86, i32 %87, <128 x i8> %88) #2, !dbg !24
  br label %for.inc, !dbg !53

for.inc:                                          ; preds = %for.body7
  %89 = load i32* %j, align 4, !dbg !54
  %inc = add i32 %89, 1, !dbg !54
  store i32 %inc, i32* %j, align 4, !dbg !54
  br label %for.cond5, !dbg !54

for.end:                                          ; preds = %for.cond5
  br label %while.cond29, !dbg !55

while.cond29:                                     ; preds = %while.body31, %for.end
  %90 = load volatile i32* @g_timer_debug, align 4, !dbg !56
  %cmp30 = icmp ne i32 %90, -559038737, !dbg !56
  br i1 %cmp30, label %while.body31, label %while.end32, !dbg !56

while.body31:                                     ; preds = %while.cond29
  br label %while.cond29, !dbg !58

while.end32:                                      ; preds = %while.cond29
  store volatile i32 57005, i32* @g_timer_debug, align 4, !dbg !60
  %91 = load volatile i32* @g_debug, align 4, !dbg !61
  %inc33 = add i32 %91, 1, !dbg !61
  store volatile i32 %inc33, i32* @g_debug, align 4, !dbg !61
  br label %for.inc34, !dbg !62

for.inc34:                                        ; preds = %while.end32
  %92 = load i32* %i, align 4, !dbg !63
  %inc35 = add i32 %92, 1, !dbg !63
  store i32 %inc35, i32* %i, align 4, !dbg !63
  br label %for.cond, !dbg !63

for.end36:                                        ; preds = %for.cond
  br label %while.cond1, !dbg !64

while.end37:                                      ; preds = %while.cond1
  store i32 0, i32* %A.addr.i, align 4, !dbg !25
  store i32 9, i32* %B.addr.i, align 4, !dbg !25
  store i32 2, i32* %C.addr.i, align 4, !dbg !25
  %93 = load i32* %A.addr.i, align 4, !dbg !25
  %94 = load i32* %B.addr.i, align 4, !dbg !25
  %95 = load i32* %C.addr.i, align 4, !dbg !25
  call void @llvm.ve32.s.xsto.32(i32 %93, i32 %94, i32 %95) #2, !dbg !25
  ret void, !dbg !65
}

declare void @OP___printstring(i8*) #1

; Function Attrs: nounwind
declare void @llvm.ve32.v.xsto.1024.i(i32, i32, <128 x i8>) #2

; Function Attrs: nounwind
declare void @llvm.ve32.s.xsto.32(i32, i32, i32) #2

attributes #0 = { noinline nounwind uwtable "ipu_entry" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!8, !9}
!ipu.register_structs_list = !{!2}
!llvm.ident = !{!10}

!0 = metadata !{i32 786449, metadata !1, i32 12, metadata !"clang version 3.5.0 ", i1 false, metadata !"", i32 0, metadata !2, metadata !2, metadata !3, metadata !2, metadata !2, metadata !"", i32 2} ; [ DW_TAG_compile_unit ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c] [DW_LANG_C99]
!1 = metadata !{metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c", metadata !"/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64"}
!2 = metadata !{}
!3 = metadata !{metadata !4, metadata !7}
!4 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"jesd_tx", metadata !"jesd_tx", metadata !"", i32 108, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 0, i1 false, void ()* @jesd_tx, null, null, metadata !2, i32 109} ; [ DW_TAG_subprogram ] [line 108] [def] [scope 109] [jesd_tx]
!5 = metadata !{i32 786473, metadata !1}          ; [ DW_TAG_file_type ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!6 = metadata !{i32 786453, i32 0, null, metadata !"", i32 0, i64 0, i64 0, i64 0, i32 0, null, metadata !2, i32 0, null, null, null} ; [ DW_TAG_subroutine_type ] [line 0, size 0, align 0, offset 0] [from ]
!7 = metadata !{i32 786478, metadata !1, metadata !5, metadata !"init_timer", metadata !"init_timer", metadata !"", i32 88, metadata !6, i1 false, i1 true, i32 0, i32 0, null, i32 256, i1 false, null, null, null, metadata !2, i32 89} ; [ DW_TAG_subprogram ] [line 88] [def] [scope 89] [init_timer]
!8 = metadata !{i32 2, metadata !"Dwarf Version", i32 4}
!9 = metadata !{i32 2, metadata !"Debug Info Version", i32 1}
!10 = metadata !{metadata !"clang version 3.5.0 "}
!11 = metadata !{i32 125, i32 5, metadata !4, null}
!12 = metadata !{i32 133, i32 8, metadata !13, null}
!13 = metadata !{i32 786443, metadata !1, metadata !14, i32 132, i32 7, i32 0, i32 5} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!14 = metadata !{i32 786443, metadata !1, metadata !15, i32 131, i32 7, i32 0, i32 4} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!15 = metadata !{i32 786443, metadata !1, metadata !16, i32 130, i32 9, i32 0, i32 3} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!16 = metadata !{i32 786443, metadata !1, metadata !17, i32 129, i32 9, i32 0, i32 2} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!17 = metadata !{i32 786443, metadata !1, metadata !4, i32 128, i32 5, i32 0, i32 1} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!18 = metadata !{i32 134, i32 8, metadata !13, null}
!19 = metadata !{i32 135, i32 8, metadata !13, null}
!20 = metadata !{i32 136, i32 8, metadata !13, null}
!21 = metadata !{i32 138, i32 8, metadata !13, null}
!22 = metadata !{i32 139, i32 8, metadata !13, null}
!23 = metadata !{i32 140, i32 8, metadata !13, null}
!24 = metadata !{i32 141, i32 8, metadata !13, null}
!25 = metadata !{i32 156, i32 5, metadata !4, null}
!26 = metadata !{i32 93, i32 5, metadata !7, metadata !27}
!27 = metadata !{i32 118, i32 5, metadata !4, null}
!28 = metadata !{i32 95, i32 5, metadata !7, metadata !27}
!29 = metadata !{i32 97, i32 5, metadata !7, metadata !27}
!30 = metadata !{i32 99, i32 5, metadata !7, metadata !27}
!31 = metadata !{i32 91, i32 5, metadata !7, metadata !27}
!32 = metadata !{i32 111, i32 5, metadata !4, null}
!33 = metadata !{i32 112, i32 5, metadata !4, null}
!34 = metadata !{i32 114, i32 5, metadata !4, null}
!35 = metadata !{i32 115, i32 5, metadata !4, null}
!36 = metadata !{i32 117, i32 5, metadata !4, null}
!37 = metadata !{i32 120, i32 5, metadata !4, null}
!38 = metadata !{i32 120, i32 5, metadata !39, null}
!39 = metadata !{i32 786443, metadata !1, metadata !4, i32 120, i32 5, i32 1, i32 7} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!40 = metadata !{i32 123, i32 5, metadata !41, null}
!41 = metadata !{i32 786443, metadata !1, metadata !4, i32 121, i32 5, i32 0, i32 0} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!42 = metadata !{i32 127, i32 5, metadata !4, null}
!43 = metadata !{i32 127, i32 5, metadata !44, null}
!44 = metadata !{i32 786443, metadata !1, metadata !4, i32 127, i32 5, i32 1, i32 8} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!45 = metadata !{i32 129, i32 13, metadata !16, null}
!46 = metadata !{i32 129, i32 13, metadata !47, null}
!47 = metadata !{i32 786443, metadata !1, metadata !48, i32 129, i32 13, i32 2, i32 13} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!48 = metadata !{i32 786443, metadata !1, metadata !16, i32 129, i32 13, i32 1, i32 9} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!49 = metadata !{i32 131, i32 11, metadata !14, null}
!50 = metadata !{i32 131, i32 11, metadata !51, null}
!51 = metadata !{i32 786443, metadata !1, metadata !52, i32 131, i32 11, i32 2, i32 11} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!52 = metadata !{i32 786443, metadata !1, metadata !14, i32 131, i32 11, i32 1, i32 10} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!53 = metadata !{i32 143, i32 10, metadata !13, null}
!54 = metadata !{i32 131, i32 42, metadata !14, null}
!55 = metadata !{i32 146, i32 13, metadata !15, null}
!56 = metadata !{i32 146, i32 13, metadata !57, null}
!57 = metadata !{i32 786443, metadata !1, metadata !15, i32 146, i32 13, i32 1, i32 12} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!58 = metadata !{i32 148, i32 13, metadata !59, null}
!59 = metadata !{i32 786443, metadata !1, metadata !15, i32 147, i32 13, i32 0, i32 6} ; [ DW_TAG_lexical_block ] [/nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/sim_m64//nfs/site/disks/zsc14.xne_abc_fe_001/users/vpaidi/check_in/vex-trunk/vex_core/vex/applications/ve32/examples/vex_jesd_dnrt_usecase/vex_fw/vex_jesd_tx.c]
!60 = metadata !{i32 149, i32 13, metadata !15, null}
!61 = metadata !{i32 150, i32 13, metadata !15, null}
!62 = metadata !{i32 151, i32 9, metadata !15, null}
!63 = metadata !{i32 129, i32 36, metadata !16, null}
!64 = metadata !{i32 154, i32 5, metadata !17, null}
!65 = metadata !{i32 158, i32 1, metadata !4, null}
