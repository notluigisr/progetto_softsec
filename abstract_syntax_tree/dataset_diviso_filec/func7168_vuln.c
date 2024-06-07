static BROTLI_INLINE double FastLog2(size_t v) {
  if (v < sizeof(kLog2Table) / sizeof(kLog2Table[0])) {
    return kLog2Table[v];
  }
#if !(BROTLI_HAVE_LOG2)
  return log((double)v) * LOG_2_INV;
#else
  return log2((double)v);
#endif
}