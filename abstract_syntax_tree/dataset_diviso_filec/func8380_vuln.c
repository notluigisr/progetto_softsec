static BROTLI_INLINE void GetBlockLengthPrefixCode(uint32_t len, size_t* code,
    uint32_t* n_extra, uint32_t* extra) {
  *code = BlockLengthPrefixCode(len);
  *n_extra = kBlockLengthPrefixCode[*code].nbits;
  *extra = len - kBlockLengthPrefixCode[*code].offset;
}