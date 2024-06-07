fseeko (FILE * stream, off_t newpos, int whence)
{
  while (newpos != (long) newpos)
    {
      long pos = newpos < 0 ? LONG_MIN : LONG_MAX;
      if (fseek (stream, pos, whence) != 0)
	return -1;
      newpos -= pos;
      whence = SEEK_CUR;
    }
  return fseek (stream, (long) newpos, whence);
}