static BROTLI_INLINE uint32_t ReadBlockLength(const HuffmanCode* table,
                                              BrotliBitReader* br) {
  uint32_t code;
  uint32_t nbits;
  code = ReadSymbol(table, br);
  nbits = _kBrotliPrefixCodeRanges[code].nbits;  
  return _kBrotliPrefixCodeRanges[code].offset + BrotliReadBits24(br, nbits);
}