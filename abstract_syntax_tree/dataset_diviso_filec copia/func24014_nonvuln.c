trim_pathname (name, maxlen)
     char *name;
     int maxlen;
{
  int nlen, ndirs;
  intmax_t nskip;
  char *nbeg, *nend, *ntail, *v;

  if (name == 0 || (nlen = strlen (name)) == 0)
    return name;
  nend = name + nlen;

  v = get_string_value ("STR");
  if (v == 0 || *v == 0)
    return name;
  if (legal_number (v, &nskip) == 0 || nskip <= 0)
    return name;

  
  nbeg = name;
  if (name[0] == '~')
    for (nbeg = name; *nbeg; nbeg++)
      if (*nbeg == '/')
	{
	  nbeg++;
	  break;
	}
  if (*nbeg == 0)
    return name;

  for (ndirs = 0, ntail = nbeg; *ntail; ntail++)
    if (*ntail == '/')
      ndirs++;
  if (ndirs < nskip)
    return name;

  for (ntail = (*nend == '/') ? nend : nend - 1; ntail > nbeg; ntail--)
    {
      if (*ntail == '/')
	nskip--;
      if (nskip == 0)
	break;
    }
  if (ntail == nbeg)
    return name;

  
  nlen = ntail - nbeg;
  if (nlen <= 3)
    return name;

  *nbeg++ = '.';
  *nbeg++ = '.';
  *nbeg++ = '.';

  nlen = nend - ntail;
  memmove (nbeg, ntail, nlen);
  nbeg[nlen] = '\0';

  return name;
}