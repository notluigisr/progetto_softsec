static char *
make_dev_fd_filename (fd)
     int fd;
{
  char *ret, intbuf[INT_STRLEN_BOUND (int) + 1], *p;

  ret = (char *)xmalloc (sizeof (DEV_FD_PREFIX) + 8);

  strcpy (ret, DEV_FD_PREFIX);
  p = inttostr (fd, intbuf, sizeof (intbuf));
  strcpy (ret + sizeof (DEV_FD_PREFIX) - 1, p);

  add_fifo_list (fd);
  return (ret);