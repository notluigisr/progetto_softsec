static BROTLI_INLINE BROTLI_BOOL SafeReadBlockLength(
    BrotliDecoderState* s, uint32_t* result, const HuffmanCode* table,
    BrotliBitReader* br) {
  uint32_t index;
  if (s->substate_read_block_length == BROTLI_STATE_READ_BLOCK_LENGTH_NONE) {
    if (!SafeReadSymbol(table, br, &index)) {
      return BROTLI_FALSE;
    }
  } else {
    index = s->block_length_index;
  }
  {
    uint32_t bits;
    uint32_t nbits = kBlockLengthPrefixCode[index].nbits;  
    if (!BrotliSafeReadBits(br, nbits, &bits)) {
      s->block_length_index = index;
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX;
      return BROTLI_FALSE;
    }
    *result = kBlockLengthPrefixCode[index].offset + bits;
    s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
    return BROTLI_TRUE;
  }
}