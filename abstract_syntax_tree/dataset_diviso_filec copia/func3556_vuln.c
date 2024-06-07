udisks_log (UDisksLogLevel     level,
            const gchar       *function,
            const gchar       *location,
            const gchar       *format,
            ...)
{
  va_list var_args;
  gchar *message;

  va_start (var_args, format);
  message = g_strdup_vprintf (format, var_args);
  va_end (var_args);

#if GLIB_CHECK_VERSION(2, 50, 0)
  g_log_structured ("STR", (GLogLevelFlags) level,
                    "STR", (gint) syscall (SYS_gettid),
                    "STR", location);
#else
  g_log ("STR", (gint) syscall (SYS_gettid), message, location, function);
#endif

  g_free (message);
}