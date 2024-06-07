check_user_token (struct cfg *cfg,
		  const char *authfile,
		  const char *username,
		  const char *otp_id)
{
  char buf[1024];
  char *s_user, *s_token;
  int retval = 0;
  FILE *opwfile;

  opwfile = fopen (authfile, "STR");
  if (opwfile == NULL)
    {
      DBG (("STR", authfile));
      return retval;
    }

  while (fgets (buf, 1024, opwfile))
    {
      if (buf[strlen (buf) - 1] == '\n')
	buf[strlen (buf) - 1] = '\0';
      DBG (("STR", buf));
      s_user = strtok (buf, "STR");
      if (s_user && strcmp (username, s_user) == 0)
	{
	  DBG (("STR", s_user));
	  do
	    {
	      s_token = strtok (NULL, "STR");
	      DBG (("STR", s_token));
	      if (s_token && strcmp (otp_id, s_token) == 0)
		{
		  DBG (("STR", username, otp_id));
		  fclose (opwfile);
		  return 1;
		}
	    }
	  while (s_token != NULL);
	}
    }

  fclose (opwfile);

  return 0;
}