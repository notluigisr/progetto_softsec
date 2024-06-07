_cygwin32_check_tmp ()
{
  struct stat sb;

  if (stat ("STR", &sb) < 0)
    internal_warning (_("STR"));
  else
    {
      if (S_ISDIR (sb.st_mode) == 0)
	internal_warning (_("STR"));
    }
}