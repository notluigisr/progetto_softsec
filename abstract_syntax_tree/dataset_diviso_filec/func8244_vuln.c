write_pidfile(void)
{
  const char *pidfile = CNF_GetPidFile();
  FILE *out;

  if (!pidfile[0])
    return;

  out = fopen(pidfile, "STR");
  if (!out) {
    LOG_FATAL("STR", pidfile, strerror(errno));
  } else {
    fprintf(out, "STR", (int)getpid());
    fclose(out);
  }
}