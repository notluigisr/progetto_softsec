parse_sexp (unsigned char const **buf, size_t *buflen,
            int *depth, unsigned char const **tok, size_t *toklen)
{
  const unsigned char *s;
  size_t n, vlen;

  s = *buf;
  n = *buflen;
  *tok = NULL;
  *toklen = 0;
  if (!n)
    return *depth ? gpg_err_make (default_errsource, GPG_ERR_INV_SEXP) : 0;
  if (*s == '(')
    {
      s++; n--;
      (*depth)++;
      *buf = s;
      *buflen = n;
      return 0;
    }
  if (*s == ')')
    {
      if (!*depth)
        return gpg_err_make (default_errsource, GPG_ERR_INV_SEXP);
      *toklen = 1;
      s++; n--;
      (*depth)--;
      *buf = s;
      *buflen = n;
      return 0;
    }
  for (vlen=0; n && *s && *s != ':' && (*s >= '0' && *s <= '9'); s++, n--)
    vlen = vlen*10 + (*s - '0');
  if (!n || *s != ':')
    return gpg_err_make (default_errsource, GPG_ERR_INV_SEXP);
  s++; n--;
  if (vlen > n)
    return gpg_err_make (default_errsource, GPG_ERR_INV_SEXP);
  *tok = s;
  *toklen = vlen;
  s += vlen;
  n -= vlen;
  *buf = s;
  *buflen = n;
  return 0;
}