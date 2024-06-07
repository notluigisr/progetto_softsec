static BROTLI_INLINE uint32_t CommandDistanceContext(const Command* self) {
  uint32_t r = self->cmd_prefix_ >> 6;
  uint32_t c = self->cmd_prefix_ & 7;
  if ((r == 0 || r == 2 || r == 4 || r == 7) && (c <= 2)) {
    return c;
  }
  return 3;
}