path_is_relative(const char *filename)
{
  if (filename && filename[0] == '/')
    return 0;
#ifdef MS_WINDOWS
  else if (filename && filename[0] == '\\')
    return 0;
  else if (filename && strlen(filename)>3 && TOR_ISALPHA(filename[0]) &&
           filename[1] == ':' && filename[2] == '\\')
    return 0;
#endif
  else
    return 1;
}