static inline signed int ReadProfileLong(const EndianType endian,
  unsigned char *buffer)
{
  union
  {
    unsigned int
      unsigned_value;

    signed int
      signed_value;
  } quantum;

  unsigned int
    value;

  if (endian == LSBEndian)
    {
      value=(unsigned int) ((buffer[3] << 24) | (buffer[2] << 16) |
        (buffer[1] << 8 ) | (buffer[0]));
      quantum.unsigned_value=(value & 0xffffffff);
      return(quantum.signed_value);
    }
  value=(unsigned int) ((buffer[0] << 24) | (buffer[1] << 16) |
    (buffer[2] << 8) | buffer[3]);
  quantum.unsigned_value=(value & 0xffffffff);
  return(quantum.signed_value);
}