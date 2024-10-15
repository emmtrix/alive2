declare noundef <2 x i32> @_Z23__emx_simd_load_stridedPii(i32* noundef, i32 noundef)

define <2 x i32> @src(i32* noundef %x) {
entry:
  %load = call noundef <2 x i32> @_Z23__emx_simd_load_stridedPii(i32* noundef %x, i32 noundef 4)
  ret <2 x i32> %load
}

define <2 x i32> @tgt(i32* noundef %x) {
entry:
  %arrayidx = getelementptr inbounds i32, i32* %x, i64 0
  %0 = load i32, i32* %arrayidx, align 4
  %vecinit = insertelement <2 x i32> undef, i32 %0, i32 0
  %arrayidx1 = getelementptr inbounds i32, i32* %x, i64 1
  %1 = load i32, i32* %arrayidx1, align 4
  %vecinit2 = insertelement <2 x i32> %vecinit, i32 %1, i32 1
  ret <2 x i32> %vecinit2
}