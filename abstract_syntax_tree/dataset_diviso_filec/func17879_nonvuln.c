parse_ber_header (unsigned char const **buffer, size_t *size,
                  int *r_class, int *r_tag,
                  int *r_constructed, int *r_ndef,
                  size_t *r_length, size_t *r_nhdr)
{
  int c;
  unsigned long tag;
  const unsigned char *buf = *buffer;
  size_t length = *size;

  *r_ndef = 0;
  *r_length = 0;
  *r_nhdr = 0;

  
  if (!length)
    return gpg_err_make (default_errsource, GPG_ERR_EOF);
  c = *buf++; length--; ++*r_nhdr;

  *r_class = (c & 0xc0) >> 6;
  *r_constructed = !!(c & 0x20);
  tag = c & 0x1f;

  if (tag == 0x1f)
    {
      tag = 0;
      do
        {
          tag <<= 7;
          if (!length)
            return gpg_err_make (default_errsource, GPG_ERR_EOF);
          c = *buf++; length--; ++*r_nhdr;
          tag |= c & 0x7f;

        }
      while (c & 0x80);
    }
  *r_tag = tag;

  
  if (!length)
    return gpg_err_make (default_errsource, GPG_ERR_EOF);
  c = *buf++; length--; ++*r_nhdr;

  if ( !(c & 0x80) )
    *r_length = c;
  else if (c == 0x80)
    *r_ndef = 1;
  else if (c == 0xff)
    return gpg_err_make (default_errsource, GPG_ERR_BAD_BER);
  else
    {
      unsigned long len = 0;
      int count = c & 0x7f;

      if (count > sizeof (len) || count > sizeof (size_t))
        return gpg_err_make (default_errsource, GPG_ERR_BAD_BER);

      for (; count; count--)
        {
          len <<= 8;
          if (!length)
            return gpg_err_make (default_errsource, GPG_ERR_EOF);
          c = *buf++; length--; ++*r_nhdr;
          len |= c & 0xff;
        }
      *r_length = len;
    }

  
  if (*r_class == CLASS_UNIVERSAL && !*r_tag)
    *r_length = 0;

  *buffer = buf;
  *size = length;
  return 0;
}