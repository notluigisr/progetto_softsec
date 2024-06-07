  const uchar *unpack(uchar* to, const uchar *from, const uchar *from_end,
                      uint param_data __attribute__((unused)))
  {
    return unpack_int32(to, from, from_end);
  }