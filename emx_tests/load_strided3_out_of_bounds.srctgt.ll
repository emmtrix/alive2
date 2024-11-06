declare noundef <2 x i32> @_Z23__emx_simd_load_stridedPii(i32* noundef, i32 noundef)

; Load should result in poison on out of bounds lanes

; Only contains a single i32, but we attempt to load two i32s
@data = external global i32, align 4

define <2 x i32> @src() {
entry:
  %load = call noundef <2 x i32> @_Z23__emx_simd_load_stridedPii(i32* @data, i32 noundef 4)
  ret <2 x i32> %load
}

define <2 x i32> @tgt() {
entry:
  %arrayidx = getelementptr inbounds i32, i32* @data, i64 0
  %0 = load i32, i32* %arrayidx, align 4
  %vecinit = insertelement <2 x i32> poison, i32 %0, i32 0
  ret <2 x i32> %vecinit
}