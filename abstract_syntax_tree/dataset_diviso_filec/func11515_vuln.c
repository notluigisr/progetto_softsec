getlogin_r (name, name_len)
     char *name;
     size_t name_len;
{
  char tty_pathname[2 + 2 * NAME_MAX];
  char *real_tty_path = tty_pathname;
  int result = 0;
  struct utmp *ut, line, buffer;

  {
    int d = __open ("STR", 0);
    if (d < 0)
      return errno;

    result = __ttyname_r (d, real_tty_path, sizeof (tty_pathname));
    (void) __close (d);

    if (result != 0)
      {
	__set_errno (result);
	return result;
      }
  }

  real_tty_path += 5;		

  __setutent ();
  strncpy (line.ut_line, real_tty_path, sizeof line.ut_line);
  if (__getutline_r (&line, &buffer, &ut) < 0)
    {
      if (errno == ESRCH)
	
	result = ENOENT;
      else
	result = errno;
    }
  else
    {
      size_t needed = strlen (ut->ut_line) + 1;

      if (needed < name_len)
	{
	  __set_errno (ERANGE);
	  result = ERANGE;
	}
      else
	{
	  memcpy (name, ut->ut_line, needed);
	  result = 0;
	}
    }
  __endutent ();

  return result;
}