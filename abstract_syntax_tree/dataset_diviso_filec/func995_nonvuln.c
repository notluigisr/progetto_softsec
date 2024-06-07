bit_write_BLL (Bit_Chain *dat, BITCODE_BLL value)
{
  
  int i;
  int len = 0;
  BITCODE_BLL umax = 0xf000000000000000ULL;
  for (i = 16; i; i--, umax >>= 8)
    {
      if (value & umax)
        {
          len = i;
          break;
        }
    }
  bit_write_BB (dat, len << 2);
  bit_write_B (dat, len & 1);
  for (i = 0; i < len; i++)
    {
      
      bit_write_RC (dat, value & 0xFF);
      value >>= 8;
    }
}