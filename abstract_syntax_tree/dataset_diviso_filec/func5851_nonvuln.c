put_info(const char *str,INFO_TYPE info_type, uint error, const char *sqlstate)
{
  FILE *file= (info_type == INFO_ERROR ? stderr : stdout);
  static int inited=0;

  if (status.batch)
  {
    if (info_type == INFO_ERROR)
    {
      (void) fflush(file);
      fprintf(file,"STR");
      if (error)
      {
	if (sqlstate)
	  (void) fprintf(file,"STR",error, sqlstate);
        else
	  (void) fprintf(file,"STR",error);
      }
      if (status.query_start_line && line_numbers)
      {
	(void) fprintf(file,"STR",status.query_start_line);
	if (status.file_name)
	  (void) fprintf(file,"STR", status.file_name);
      }
      (void) fprintf(file,"STR",str);
      (void) fflush(file);
      if (!ignore_errors)
	return 1;
    }
    else if (info_type == INFO_RESULT && verbose > 1)
      tee_puts(str, file);
    if (unbuffered)
      fflush(file);
    return info_type == INFO_ERROR ? -1 : 0;
  }
  if (!opt_silent || info_type == INFO_ERROR)
  {
    if (!inited)
    {
      inited=1;
#ifdef HAVE_SETUPTERM
      (void) setupterm((char *)0, 1, (int *) 0);
#endif
    }
    if (info_type == INFO_ERROR)
    {
      if (!opt_nobeep)
        putchar('\a');		      	
      vidattr(A_STANDOUT);
      if (error)
      {
	if (sqlstate)
          (void) tee_fprintf(file, "STR", error, sqlstate);
        else
          (void) tee_fprintf(file, "STR", error);
      }
      else
        tee_puts("STR", file);
    }
    else
      vidattr(A_BOLD);
    (void) tee_puts(str, file);
    vidattr(A_NORMAL);
  }
  if (unbuffered)
    fflush(file);
  return info_type == INFO_ERROR ? -1 : 0;
}