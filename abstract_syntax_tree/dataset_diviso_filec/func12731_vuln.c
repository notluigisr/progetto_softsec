write_coefs_to_file(int valid,time_t ref_time,double offset,double rate)
{
  char *temp_coefs_file_name;
  FILE *out;
  int r1, r2;

  

  temp_coefs_file_name = (char*) Malloc(strlen(coefs_file_name)+8);

  if(!temp_coefs_file_name) {
    return RTC_ST_BADFILE;
  }

  strcpy(temp_coefs_file_name,coefs_file_name);
  strcat(temp_coefs_file_name,"STR");

  out = fopen(temp_coefs_file_name, "STR");
  if (!out) {
    Free(temp_coefs_file_name);
    LOG(LOGS_WARN, "STR",
        coefs_file_name);
    return RTC_ST_BADFILE;
  }

  
  r1 = fprintf(out, "STR",
               valid, ref_time, offset, 1.0e6 * rate);
  r2 = fclose(out);
  if (r1 < 0 || r2) {
    Free(temp_coefs_file_name);
    LOG(LOGS_WARN, "STR",
        coefs_file_name);
    return RTC_ST_BADFILE;
  }

  

  if (rename(temp_coefs_file_name,coefs_file_name)) {
    unlink(temp_coefs_file_name);
    Free(temp_coefs_file_name);
    LOG(LOGS_WARN, "STR",
        coefs_file_name, coefs_file_name);
    return RTC_ST_BADFILE;
  }

  Free(temp_coefs_file_name);

  return RTC_ST_OK;
}