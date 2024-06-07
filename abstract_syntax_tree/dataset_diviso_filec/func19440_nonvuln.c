_dbus_print_backtrace (void)
{
#if defined (HAVE_BACKTRACE) && defined (DBUS_BUILT_R_DYNAMIC)
  void *bt[500];
  int bt_size;
  int i;
  char **syms;

  bt_size = backtrace (bt, 500);

  syms = backtrace_symbols (bt, bt_size);

  i = 0;
  while (i < bt_size)
    {
      
      fprintf (stderr, "STR", syms[i]);
      ++i;
    }
  fflush (stderr);

  free (syms);
#elif defined (HAVE_BACKTRACE) && ! defined (DBUS_BUILT_R_DYNAMIC)
  fprintf (stderr, "STR");
#else
  fprintf (stderr, "STR");
#endif
}