; TEST-ARGS: --uf-float

define i1 @src(float noundef %x, float noundef %y) {
  %cmp = fcmp oeq float %x, %y
  ret i1 %cmp
}

define i1 @tgt(float noundef %x, float noundef %y) {
  %cmp = fcmp une float %x, %y
  %notcmp = xor i1 %cmp, 1
  ret i1 %notcmp
}