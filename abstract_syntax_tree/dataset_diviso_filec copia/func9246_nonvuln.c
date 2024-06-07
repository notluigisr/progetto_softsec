  uint row_pack_length() const
  { return (bytes_in_rec + ((bit_len > 0) ? 1 : 0)); }