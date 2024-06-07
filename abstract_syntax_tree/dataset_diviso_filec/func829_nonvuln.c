set_file_times (int fd,
		const char *name, unsigned long atime, unsigned long mtime)
{
  struct timespec ts[2];
  
  memset (&ts, 0, sizeof ts);

  ts[0].tv_sec = atime;
  ts[1].tv_sec = mtime;

  
  if (fdutimens (fd, name, ts) < 0 && errno != EROFS)
    utime_error (name);
}