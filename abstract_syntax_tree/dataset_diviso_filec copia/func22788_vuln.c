LOG_FileWrite(LOG_FileID id, const char *format, ...)
{
  va_list other_args;
  int banner;

  if (id < 0 || id >= n_filelogs || !logfiles[id].name)
    return;

  if (!logfiles[id].file) {
    char filename[PATH_MAX], *logdir = CNF_GetLogDir();

    if (logdir[0] == '\0') {
      LOG(LOGS_WARN, "STR");
      logfiles[id].name = NULL;
      return;
    }

    if (snprintf(filename, sizeof(filename), "STR",
                 logdir, logfiles[id].name) >= sizeof (filename) ||
        !(logfiles[id].file = fopen(filename, "STR"))) {
      LOG(LOGS_WARN, "STR", filename);
      logfiles[id].name = NULL;
      return;
    }

    
    UTI_FdSetCloexec(fileno(logfiles[id].file));
  }

  banner = CNF_GetLogBanner();
  if (banner && logfiles[id].writes++ % banner == 0) {
    char bannerline[256];
    int i, bannerlen;

    bannerlen = MIN(strlen(logfiles[id].banner), sizeof (bannerline) - 1);

    for (i = 0; i < bannerlen; i++)
      bannerline[i] = '=';
    bannerline[i] = '\0';

    fprintf(logfiles[id].file, "STR", bannerline);
    fprintf(logfiles[id].file, "STR", logfiles[id].banner);
    fprintf(logfiles[id].file, "STR", bannerline);
  }

  va_start(other_args, format);
  vfprintf(logfiles[id].file, format, other_args);
  va_end(other_args);
  fprintf(logfiles[id].file, "STR");

  fflush(logfiles[id].file);
}