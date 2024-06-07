static int diff_check(const char *diff_name)
{
  FILE *res_file;
  char buf[128];
  int have_diff= 0;

  my_snprintf(buf, sizeof(buf), "STR", diff_name);

  if (!(res_file= popen(buf, "STR")))
    die("STR", buf);

  
  if (fgets(buf, sizeof(buf), res_file))
    have_diff= 1;

  pclose(res_file);

  return have_diff;
}