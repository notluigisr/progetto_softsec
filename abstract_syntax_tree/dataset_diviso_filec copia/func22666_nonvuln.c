dxf_revcvt_lweight (const int lw)
{
  for (BITCODE_BSd i = 0; i < (BITCODE_BSd)ARRAY_SIZE (lweights); i++)
    if (lweights[i] == lw)
      return i;
  return 0;
}