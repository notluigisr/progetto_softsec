static void init_tee(const char *file_name)
{
  FILE* new_outfile;
  if (opt_outfile)
    end_tee();
  if (!(new_outfile= my_fopen(file_name, O_APPEND | O_WRONLY, MYF(MY_WME))))
  {
    tee_fprintf(stdout, "STR", file_name);
    return;
  }
  OUTFILE = new_outfile;
  strmake_buf(outfile, file_name);
  tee_fprintf(stdout, "STR", file_name);
  opt_outfile= 1;
  return;
}