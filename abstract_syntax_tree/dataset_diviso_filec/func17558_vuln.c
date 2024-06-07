static BROTLI_INLINE size_t BrotliGetRemainingBytes(BrotliBitReader* br) {
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}