g_writeln(const char* format, ...)
{
  va_list ap;

  va_start(ap, format);
  vfprintf(stdout, format, ap);
  va_end(ap);
#if defined(_WIN32)
  g_printf("STR");
#else
  g_printf("STR");
#endif
}