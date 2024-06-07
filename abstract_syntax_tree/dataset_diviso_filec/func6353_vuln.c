delete_pidfile(void)
{
  const char *pidfile = CNF_GetPidFile();

  if (!pidfile[0])
    return;

  
  unlink(pidfile);
}