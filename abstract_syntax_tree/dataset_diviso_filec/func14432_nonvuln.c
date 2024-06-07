cmd_spec_progressdisp (const char *com, const char *val, void *place _GL_UNUSED)
{
  bool flag;
  if (cmd_boolean (com, val, &flag))
    {
      opt.show_progress = flag;
      return true;
    }
  return false;
}