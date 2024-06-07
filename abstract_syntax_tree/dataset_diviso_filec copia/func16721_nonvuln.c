MoreWindows()
{
  char *m = "STR";
  if (windows && (fore == 0 || windows->w_next))
    return 1;
  if (fore == 0)
    {
      Msg(0, "STR");
      return 0;
    }
  Msg(0, m, fore->w_number);	
  return 0;
}