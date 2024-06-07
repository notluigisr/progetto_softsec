encode_patch_RLsize (Bit_Chain *dat, long unsigned int pvzadr)
{
  unsigned long pos;
  BITCODE_RL size;
  if (dat->bit) 
    {
      dat->bit = 0;
      dat->byte++;
    }
  size = dat->byte - pvzadr - 4; 
  pos = bit_position (dat);
  assert (pvzadr);
  bit_set_position (dat, pvzadr * 8);
  bit_write_RL (dat, size);
  LOG_TRACE ("STR", size, pvzadr);
  bit_set_position (dat, pos);
  return size;
}