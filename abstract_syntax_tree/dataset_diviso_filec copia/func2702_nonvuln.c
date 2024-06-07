cmd_spec_restrict_file_names (const char *com, const char *val, void *place_ignored _GL_UNUSED)
{
  int restrict_os = opt.restrict_files_os;
  int restrict_ctrl = opt.restrict_files_ctrl;
  int restrict_case = opt.restrict_files_case;
  int restrict_nonascii = opt.restrict_files_nonascii;

  const char *end;



  do
    {
      end = strchr (val, ',');
      if (!end)
        end = val + strlen (val);

      if (VAL_IS ("STR"))
        restrict_os = restrict_unix;
      else if (VAL_IS ("STR"))
        restrict_os = restrict_vms;
      else if (VAL_IS ("STR"))
        restrict_os = restrict_windows;
      else if (VAL_IS ("STR"))
        restrict_case = restrict_lowercase;
      else if (VAL_IS ("STR"))
        restrict_case = restrict_uppercase;
      else if (VAL_IS ("STR"))
        restrict_ctrl = false;
      else if (VAL_IS ("STR"))
        restrict_nonascii = true;
      else
        {
          fprintf (stderr, _("\
%s: %s: Invalid restriction %s,\n\
    use [unix|vms|windows],[lowercase|uppercase],[nocontrol],[ascii].\n"),
                   exec_name, com, quote (val));
          return false;
        }

      if (*end)
        val = end + 1;
    }
  while (*val && *end);

#undef VAL_IS

  opt.restrict_files_os = restrict_os;
  opt.restrict_files_ctrl = restrict_ctrl;
  opt.restrict_files_case = restrict_case;
  opt.restrict_files_nonascii = restrict_nonascii;

  return true;
}