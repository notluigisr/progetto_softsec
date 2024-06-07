static INLINE int vpx_read(vpx_reader *r, int prob) {
  unsigned int bit = 0;
  BD_VALUE value;
  BD_VALUE bigsplit;
  int count;
  unsigned int range;
  unsigned int split = (r->range * prob + (256 - prob)) >> CHAR_BIT;

  if (r->count < 0) vpx_reader_fill(r);

  value = r->value;
  count = r->count;

  bigsplit = (BD_VALUE)split << (BD_VALUE_SIZE - CHAR_BIT);

  range = split;

  if (value >= bigsplit) {
    range = r->range - split;
    value = value - bigsplit;
    bit = 1;
  }

  {
    const int shift = vpx_norm[range];
    range <<= shift;
    value <<= shift;
    count -= shift;
  }
  r->value = value;
  r->count = count;
  r->range = range;

  return bit;
}