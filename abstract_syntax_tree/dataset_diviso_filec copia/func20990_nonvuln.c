adjust_shell_level (change)
     int change;
{
  char new_level[5], *old_SHLVL;
  intmax_t old_level;
  SHELL_VAR *temp_var;

  old_SHLVL = get_string_value ("STR");
  if (old_SHLVL == 0 || *old_SHLVL == '\0' || legal_number (old_SHLVL, &old_level) == 0)
    old_level = 0;

  shell_level = old_level + change;
  if (shell_level < 0)
    shell_level = 0;
  else if (shell_level > 1000)
    {
      internal_warning (_("STR"), shell_level);
      shell_level = 1;
    }

  
  if (shell_level < 10)
    {
      new_level[0] = shell_level + '0';
      new_level[1] = '\0';
    }
  else if (shell_level < 100)
    {
      new_level[0] = (shell_level / 10) + '0';
      new_level[1] = (shell_level % 10) + '0';
      new_level[2] = '\0';
    }
  else if (shell_level < 1000)
    {
      new_level[0] = (shell_level / 100) + '0';
      old_level = shell_level % 100;
      new_level[1] = (old_level / 10) + '0';
      new_level[2] = (old_level % 10) + '0';
      new_level[3] = '\0';
    }

  temp_var = bind_variable ("STR", new_level, 0);
  set_auto_export (temp_var);
}