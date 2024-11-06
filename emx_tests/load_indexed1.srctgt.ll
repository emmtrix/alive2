declare noundef <2 x i32> @_Z23__emx_simd_load_indexedPiDv2_l(i32* noundef, <2 x i64> noundef)

define <2 x i32> @src(i32* noundef %x, <2 x i64> noundef %indices) {
entry:
  %call = call noundef <2 x i32> @_Z23__emx_simd_load_indexedPiDv2_l(i32* noundef %x, <2 x i64> noundef %indices)
  ret <2 x i32> %call
}

define <2 x i32> @tgt(i32* noundef %x, <2 x i64> noundef %indices) {
entry:
  %0 = bitcast i32* %x to i8*
  %vecext = extractelement <2 x i64> %indices, i64 0
  %add.ptr = getelementptr i8, i8* %0, i64 %vecext
  %1 = bitcast i8* %add.ptr to i32*
  %2 = load i32, i32* %1, align 4
  %vecinit = insertelement <2 x i32> undef, i32 %2, i64 0
  %3 = bitcast i32* %x to i8*
  %vecext1 = extractelement <2 x i64> %indices, i64 1
  %add.ptr2 = getelementptr i8, i8* %3, i64 %vecext1
  %4 = bitcast i8* %add.ptr2 to i32*
  %5 = load i32, i32* %4, align 4
  %vecinit3 = insertelement <2 x i32> %vecinit, i32 %5, i64 1
  ret <2 x i32> %vecinit3
}