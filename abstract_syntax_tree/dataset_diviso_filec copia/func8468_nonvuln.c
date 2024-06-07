int mutt_parse_rc_line ( char *line, BUFFER *token, BUFFER *err)
{
  int i, r = -1;
  BUFFER expn;

  if (!line || !*line)
    return 0;

  memset (&expn, 0, sizeof (expn));
  expn.data = expn.dptr = line;
  expn.dsize = mutt_strlen (line);

  *err->data = 0;

  SKIPWS (expn.dptr);
  while (*expn.dptr)
  {
    if (*expn.dptr == '#')
      break; 
    if (*expn.dptr == ';')
    {
      expn.dptr++;
      continue;
    }
    mutt_extract_token (token, &expn, 0);
    for (i = 0; Commands[i].name; i++)
    {
      if (!mutt_strcmp (token->data, Commands[i].name))
      {
	if (Commands[i].func (token, &expn, Commands[i].data, err) != 0)
	  goto finish;
        break;
      }
    }
    if (!Commands[i].name)
    {
      snprintf (err->data, err->dsize, _("STR"), NONULL (token->data));
      goto finish;
    }
  }
  r = 0;
finish:
  if (expn.destroy)
    FREE (&expn.data);
  return (r);
}