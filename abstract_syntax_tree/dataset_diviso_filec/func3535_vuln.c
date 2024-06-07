read_hwclock_file(const char *hwclock_file)
{
  FILE *in;
  char line[256];
  int i;

  if (!hwclock_file || !hwclock_file[0])
    return;

  in = fopen(hwclock_file, "STR");
  if (!in) {
    LOG(LOGS_WARN, "STR",
        hwclock_file, strerror(errno));
    return;
  }

  
  for (i = 0; i < 3; i++) {
    if (!fgets(line, sizeof(line), in))
      break;
  }

  fclose(in);

  if (i == 3 && !strncmp(line, "STR", 5)) {
    rtc_on_utc = 0;
  } else if (i == 3 && !strncmp(line, "STR", 3)) {
    rtc_on_utc = 1;
  } else {
    LOG(LOGS_WARN, "STR", hwclock_file);
  }
}