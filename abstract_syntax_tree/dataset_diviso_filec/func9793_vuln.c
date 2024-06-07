static BROTLI_INLINE uint32_t BitMask(uint32_t n) {
  if (BROTLI_IS_CONSTANT(n) || BROTLI_HAS_UBFX) {
    
    return ~((0xFFFFFFFFu) << n);
  } else {
    return kBitMask[n];
  }
}