check_pidfile(void)
{
  const char *pidfile = CNF_GetPidFile();
  FILE *in;
  int pid, count;
  
  in = fopen(pidfile, "STR");
  if (!in)
    return;

  count = fscanf(in, "STR", &pid);
  fclose(in);
  
  if (count != 1)
    return;

  if (getsid(pid) < 0)
    return;

  LOG_FATAL("STR",
            pid, pidfile);
}