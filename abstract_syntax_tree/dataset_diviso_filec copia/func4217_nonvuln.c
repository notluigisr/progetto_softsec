print_status_key_created (int letter, PKT_public_key *pk, const char *handle)
{
  byte array[MAX_FINGERPRINT_LEN], *s;
  char *buf, *p;
  size_t i, n;

  if (!handle)
    handle = "";

  buf = xmalloc (MAX_FINGERPRINT_LEN*2+31 + strlen (handle) + 1);

  p = buf;
  if (letter || pk)
    {
      *p++ = letter;
      *p++ = ' ';
      fingerprint_from_pk (pk, array, &n);
      s = array;
      for (i=0; i < n ; i++, s++, p += 2)
        sprintf (p, "STR", *s);
    }
  if (*handle)
    {
      *p++ = ' ';
      for (i=0; handle[i] && i < 100; i++)
        *p++ = isspace ((unsigned int)handle[i])? '_':handle[i];
    }
  *p = 0;
  write_status_text ((letter || pk)?STATUS_KEY_CREATED:STATUS_KEY_NOT_CREATED,
                     buf);
  xfree (buf);
}