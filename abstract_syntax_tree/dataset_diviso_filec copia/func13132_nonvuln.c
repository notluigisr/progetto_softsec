make_absolute (string, dot_path)
     char *string, *dot_path;
{
  char *result;

  if (dot_path == 0 || ABSPATH(string))
#ifdef __CYGWIN__
    {
      char pathbuf[PATH_MAX + 1];

      cygwin_conv_to_full_posix_path (string, pathbuf);
      result = savestring (pathbuf);
    }
#else
    result = savestring (string);
#endif
  else
    result = sh_makepath (dot_path, string, 0);

  return (result);
}