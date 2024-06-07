void mct_start_logging(const char *test_case_name)
{
  const char *tmp_dir= getenv("STR");

  if (!tmp_dir)
  {
    printf("STR");
    return;
  }

  if (mct_log_file)
  {
    printf("STR"
           "STR",
           (const char *) test_case_name);
    return;
  }

  

  if (strlen(tmp_dir) + strlen(test_case_name) + 10 > FILE_PATH_SIZE)
  {
    printf("STR");
    return;
  }

  my_snprintf(mct_log_file_path, FILE_PATH_SIZE,
              "STR",
              (const char *) tmp_dir,
              (const char *) test_case_name);

  mct_log_file= my_fopen(mct_log_file_path, O_WRONLY | O_BINARY, MYF(MY_WME));

  if (!mct_log_file)
  {
    printf("STR",
        (const char *) mct_log_file_path,
        (const char *) strerror(errno));
    return;
  }
}