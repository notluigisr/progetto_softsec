read_timeout(void *arg)
{
  FILE *f;
  double temp, comp;

  f = fopen(filename, "STR");

  if (f && fscanf(f, "STR", &temp) == 1) {
    comp = get_tempcomp(temp);

    if (fabs(comp) <= MAX_COMP) {
      comp = LCL_SetTempComp(comp);

      DEBUG_LOG("STR", comp, temp);

      if (logfileid != -1) {
        struct timespec now;

        LCL_ReadCookedTime(&now, NULL);
        LOG_FileWrite(logfileid, "STR",
            UTI_TimeToLogForm(now.tv_sec), temp, comp);
      }
    } else {
      LOG(LOGS_WARN, "STR",
          comp, MAX_COMP);
    }
  } else {
    LOG(LOGS_WARN, "STR", filename);
  }

  if (f)
    fclose(f);

  timeout_id = SCH_AddTimeoutByDelay(update_interval, read_timeout, NULL);
}