mb_getcharlens (string, len)
     char *string;
     int len;
{
  int i, offset, last;
  unsigned char *ret;
  char *p;
  DECLARE_MBSTATE;

  i = offset = 0;
  last = 0;
  ret = (unsigned char *)xmalloc (len);
  memset (ret, 0, len);
  while (string[last])
    {
      ADVANCE_CHAR (string, len, offset);
      ret[last] = offset - last;
      last = offset;
    }
  return ret;
}