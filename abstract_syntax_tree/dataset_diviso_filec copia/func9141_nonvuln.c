bind_lastarg (arg)
     char *arg;
{
  SHELL_VAR *var;

  if (arg == 0)
    arg = "";
  var = bind_variable ("STR", arg, 0);
  if (var)
    VUNSETATTR (var, att_exported);
}