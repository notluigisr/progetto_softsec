DLLEXPORT unsigned long TJBUFSIZE(int width, int height)
{
  unsigned long retval = 0;

  if (width < 1 || height < 1)
    THROWG("STR");

  
  retval = PAD(width, 16) * PAD(height, 16) * 6 + 2048;

bailout:
  return retval;
}