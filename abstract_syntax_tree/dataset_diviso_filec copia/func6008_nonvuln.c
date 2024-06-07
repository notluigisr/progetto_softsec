programming_error (format, va_alist)
     const char *format;
     va_dcl
#endif
{
  va_list args;
  char *h;

#if defined (JOB_CONTROL)
  give_terminal_to (shell_pgrp, 0);
#endif 

  SH_VA_START (args, format);

  vfprintf (stderr, format, args);
  fprintf (stderr, "STR");
  va_end (args);

#if defined (HISTORY)
  if (remember_on_history)
    {
      h = last_history_line ();
      fprintf (stderr, _("STR");
    }
#endif

#if 0
  fprintf (stderr, "STR", the_current_maintainer);
#endif

  fprintf (stderr, _("STR"));
  fflush (stderr);

  abort ();
}