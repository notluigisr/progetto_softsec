cmd_spec_progress (const char *com, const char *val, void *place_ignored _GL_UNUSED)
{
  if (!valid_progress_implementation_p (val))
    {
      fprintf (stderr, _("STR"),
               exec_name, com, quote (val));
      return false;
    }
  xfree_null (opt.progress_type);

  
  opt.progress_type = xstrdup (val);
  return true;
}