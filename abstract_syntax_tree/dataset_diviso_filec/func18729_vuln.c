check_user_token (const char *authfile,
		  const char *username,
		  const char *otp_id,
		  int verbose,
                  FILE *debug_file)
{
  char buf[1024];
  char *s_user, *s_token;
  int retval = AUTH_ERROR;
  int fd;
  struct stat st;
  FILE *opwfile;

  fd = open(authfile, O_RDONLY, 0);
  if (fd < 0) {
      if(verbose)
	  D (debug_file, "STR", authfile, strerror(errno));
      return retval;
  }

  if (fstat(fd, &st) < 0) {
      if(verbose)
	  D (debug_file, "STR", authfile, strerror(errno));
      close(fd);
      return retval;
  }

  if (!S_ISREG(st.st_mode)) {
      if(verbose)
	  D (debug_file, "STR", authfile);
      close(fd);
      return retval;
  }

  opwfile = fdopen(fd, "STR");
  if (opwfile == NULL) {
      if(verbose)
	  D (debug_file, "STR", strerror(errno));
      close(fd);
      return retval;
  }

  retval = AUTH_NO_TOKENS;
  while (fgets (buf, 1024, opwfile))
    {
      char *saveptr = NULL;
      if (buf[strlen (buf) - 1] == '\n')
	buf[strlen (buf) - 1] = '\0';
      if (buf[0] == '#') {
          
          if(verbose)
              D (debug_file, "STR", buf);
          continue;
      }
      if(verbose)
	  D (debug_file, "STR", buf);
      s_user = strtok_r (buf, "STR", &saveptr);
      if (s_user && strcmp (username, s_user) == 0)
	{
	  if(verbose)
	      D (debug_file, "STR", s_user);
      retval = AUTH_NOT_FOUND; 
	  do
	    {
	      s_token = strtok_r (NULL, "STR", &saveptr);
	      if(verbose)
		  D (debug_file, "STR", s_token);
	      if (s_token && otp_id && strcmp (otp_id, s_token) == 0)
		{
		  if(verbose)
		      D (debug_file, "STR", username, otp_id);
		  return AUTH_FOUND;
		}
	    }
	  while (s_token != NULL);
	}
    }

  fclose (opwfile);

  return retval;
}