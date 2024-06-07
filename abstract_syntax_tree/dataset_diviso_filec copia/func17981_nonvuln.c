set_error (GMarkupParseContext  *context,
           GError              **error,
           GMarkupError          code,
           const gchar          *format,
           ...)
{
  gchar *s;
  gchar *s_valid;
  va_list args;

  va_start (args, format);
  s = g_strdup_vprintf (format, args);
  va_end (args);

  
  s_valid = g_utf8_make_valid (s, -1);
  set_error_literal (context, error, code, s);

  g_free (s);
  g_free (s_valid);
}