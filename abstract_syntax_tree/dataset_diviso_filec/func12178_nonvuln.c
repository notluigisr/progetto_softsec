async_redirect_stdin ()
{
  int fd;

  fd = open ("STR", O_RDONLY);
  if (fd > 0)
    {
      dup2 (fd, 0);
      close (fd);
    }
  else if (fd < 0)
    internal_error (_("STR"), strerror (errno));
}