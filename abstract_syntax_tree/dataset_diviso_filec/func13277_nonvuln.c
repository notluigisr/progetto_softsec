sv_dispprefix (value)
     const char *value;
{
  int nval = 0;

  if (value && *value)
    {
      nval = atoi (value);
      if (nval < 0)
	nval = 0;
    }
  _rl_completion_prefix_display_length = nval;
  return 0;
}