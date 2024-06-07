stringprep_profile (const char *in,
		    char **out,
		    const char *profile, Stringprep_profile_flags flags)
{
  const Stringprep_profiles *p;
  char *str = NULL;
  size_t len = strlen (in) + 1;
  int rc;

  for (p = &stringprep_profiles[0]; p->name; p++)
    if (strcmp (p->name, profile) == 0)
      break;

  if (!p || !p->name || !p->tables)
    return STRINGPREP_UNKNOWN_PROFILE;

  do
    {
      free (str);
      str = (char *) malloc (len);
      if (str == NULL)
	return STRINGPREP_MALLOC_ERROR;

      strcpy (str, in);

      rc = stringprep (str, len, flags, p->tables);
      len += 50;
    }
  while (rc == STRINGPREP_TOO_SMALL_BUFFER);

  if (rc == STRINGPREP_OK)
    *out = str;
  else
    free (str);

  return rc;
}