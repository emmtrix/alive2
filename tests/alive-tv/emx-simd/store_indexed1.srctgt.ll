declare void @_Z24__emx_simd_store_indexedPiDv2_iDv2_lDv2_h(i32* noundef, <2 x i32> noundef, <2 x i64> noundef, <2 x i8> noundef)

define void @src(i32* noundef %x, <2 x i32> noundef %value, <2 x i64> noundef %indices, <2 x i8> noundef %enable) {
entry:
  call void @_Z24__emx_simd_store_indexedPiDv2_iDv2_lDv2_h(i32* noundef %x, <2 x i32> noundef %value, <2 x i64> noundef %indices, <2 x i8> noundef %enable)
  ret void
}

define void @tgt(i32* noundef %x, <2 x i32> noundef %value, <2 x i64> noundef %indices, <2 x i8> noundef %enable) {
entry:
  %vecext = extractelement <2 x i8> %enable, i64 0
  %tobool.not = icmp eq i8 %vecext, 0
  br i1 %tobool.not, label %if.end, label %if.then

if.then:                                          ; preds = %entry
  %vecext1 = extractelement <2 x i32> %value, i64 0
  %0 = bitcast i32* %x to i8*
  %vecext2 = extractelement <2 x i64> %indices, i64 0
  %add.ptr = getelementptr i8, i8* %0, i64 %vecext2
  %1 = bitcast i8* %add.ptr to i32*
  store i32 %vecext1, i32* %1, align 4
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %vecext3 = extractelement <2 x i8> %enable, i64 1
  %tobool4.not = icmp eq i8 %vecext3, 0
  br i1 %tobool4.not, label %if.end9, label %if.then5

if.then5:                                         ; preds = %if.end
  %vecext6 = extractelement <2 x i32> %value, i64 1
  %2 = bitcast i32* %x to i8*
  %vecext7 = extractelement <2 x i64> %indices, i64 1
  %add.ptr8 = getelementptr i8, i8* %2, i64 %vecext7
  %3 = bitcast i8* %add.ptr8 to i32*
  store i32 %vecext6, i32* %3, align 4
  br label %if.end9

if.end9:                                          ; preds = %if.then5, %if.end
  ret void
}