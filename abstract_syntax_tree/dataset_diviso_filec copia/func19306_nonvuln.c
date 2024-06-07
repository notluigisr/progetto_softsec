iobuf_writestr (iobuf_t a, const char *buf)
{
  int rc;

  for (; *buf; buf++)
    if ((rc=iobuf_writebyte (a, *buf)))
      return rc;
  return 0;
}