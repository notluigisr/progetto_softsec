int state_putwc (wchar_t wc, STATE *s)
{
  char mb[MB_LEN_MAX] = "";
  int rc;

  if ((rc = wcrtomb (mb, wc, NULL)) < 0)
    return rc;
  if (fputs (mb, s->fpout) == EOF)
    return -1;
  return 0;
}