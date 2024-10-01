declare void @_Z24__emx_simd_store_stridedPiDv2_iiDv2_h(i32* noundef, <2 x i32> noundef, i32 noundef, <2 x i8> noundef)#1

define void @src(i32* noundef %x, <2 x i32> noundef %value, <2 x i8> noundef %enable) {
entry:
  call void @_Z24__emx_simd_store_stridedPiDv2_iiDv2_h(i32* noundef %x, <2 x i32> noundef %value, i32 noundef 4, <2 x i8> noundef %enable)
  ret void
}

define void @tgt(i32* noundef %x, <2 x i32> noundef %value, <2 x i8> noundef %enable) {
entry:
  %vecext = extractelement <2 x i8> %enable, i64 0
  %tobool.not = icmp eq i8 %vecext, 0
  br i1 %tobool.not, label %if.end, label %if.then

if.then:
  %vecext1 = extractelement <2 x i32> %value, i64 0
  store i32 %vecext1, i32* %x, align 4
  br label %if.end

if.end:
  %vecext2 = extractelement <2 x i8> %enable, i64 1
  %tobool3.not = icmp eq i8 %vecext2, 0
  br i1 %tobool3.not, label %if.end7, label %if.then4

if.then4:
  %vecext5 = extractelement <2 x i32> %value, i64 1
  %arrayidx6 = getelementptr inbounds i32, i32* %x, i64 1
  store i32 %vecext5, i32* %arrayidx6, align 4
  br label %if.end7

if.end7:
  ret void
}