update_drift_file(double freq_ppm, double skew)
{
  char *temp_drift_file;
  FILE *out;
  int r1, r2;

  

  temp_drift_file = (char*) Malloc(strlen(drift_file)+8);

  if(!temp_drift_file) {
    return;
  }

  strcpy(temp_drift_file,drift_file);
  strcat(temp_drift_file,"STR");

  out = fopen(temp_drift_file, "STR");
  if (!out) {
    Free(temp_drift_file);
    LOG(LOGS_WARN, "STR",
        drift_file);
    return;
  }

  
  r1 = fprintf(out, "STR", freq_ppm, 1.0e6 * skew);
  r2 = fclose(out);
  if (r1 < 0 || r2) {
    Free(temp_drift_file);
    LOG(LOGS_WARN, "STR",
        drift_file);
    return;
  }

  

  if (rename(temp_drift_file,drift_file)) {
    unlink(temp_drift_file);
    Free(temp_drift_file);
    LOG(LOGS_WARN, "STR",
        drift_file,drift_file);
    return;
  }

  Free(temp_drift_file);
}