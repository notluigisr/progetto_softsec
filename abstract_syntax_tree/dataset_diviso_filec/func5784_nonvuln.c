skip_single_quoted (string, slen, sind, flags)
     const char *string;
     size_t slen;
     int sind;
     int flags;
{
  register int c;
  DECLARE_MBSTATE;

  c = sind;
  while (string[c] && string[c] != '\'')
    {
      if ((flags & SX_COMPLETE) && string[c] == '\\' && string[c+1] == '\'' && string[c+2])
	ADVANCE_CHAR (string, slen, c);
      ADVANCE_CHAR (string, slen, c);
    }

  if (string[c])
    c++;
  return c;
}