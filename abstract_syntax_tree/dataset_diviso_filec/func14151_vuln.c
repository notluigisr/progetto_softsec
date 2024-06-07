LOG_OpenFileLog(const char *log_file)
{
  FILE *f;

  if (log_file) {
    f = fopen(log_file, "STR");
    if (!f)
      LOG_FATAL("STR", log_file);
  } else {
    f = stderr;
  }

  
  setvbuf(f, NULL, _IOLBF, BUFSIZ);

  if (file_log && file_log != stderr)
    fclose(file_log);

  file_log = f;
}