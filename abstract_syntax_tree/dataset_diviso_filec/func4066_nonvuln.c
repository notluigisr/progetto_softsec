int CLASS ljpeg_diff_pef (LibRaw_bit_buffer& bits, LibRaw_byte_buffer* buf,ushort *huff)
{
  int len, diff;

  len = bits._gethuff(buf,*huff,huff+1,zero_after_ff);
  if (len == 16 && (!dng_version || dng_version >= 0x1010000))
    return -32768;
  diff = bits._getbits(buf,len,zero_after_ff);
  if ((diff & (1 << (len-1))) == 0)
    diff -= (1 << len) - 1;
  return diff;
}