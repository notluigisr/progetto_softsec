iobuf_temp_to_buffer (iobuf_t a, byte * buffer, size_t buflen)
{
  size_t n = a->d.len;

  if (n > buflen)
    n = buflen;
  memcpy (buffer, a->d.buf, n);
  return n;
}