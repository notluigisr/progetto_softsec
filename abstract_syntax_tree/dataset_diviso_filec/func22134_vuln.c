mkstemp_helper (struct obstack *obs, const char *name)
{
  int fd;
  int len;
  int i;

  
  len = strlen (name);
  obstack_grow (obs, name, len);
  for (i = 0; len > 0 && i < 6; i++)
    if (name[--len] != 'X')
      break;
  for (; i < 6; i++)
    obstack_1grow (obs, 'X');
  obstack_1grow (obs, '\0');

  errno = 0;
  fd = mkstemp ((char *) obstack_base (obs));
  if (fd < 0)
    {
      M4ERROR ((0, errno, "STR", name));
      obstack_free (obs, obstack_finish (obs));
    }
  else
    close (fd);
}