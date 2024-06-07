bash_dabbrev_expand (count, key)
     int count, key;
{
  int r, orig_suppress, orig_sort;
  rl_compentry_func_t *orig_func;
  rl_completion_func_t *orig_attempt_func;
  rl_compignore_func_t *orig_ignore_func;

  orig_func = rl_menu_completion_entry_function;
  orig_attempt_func = rl_attempted_completion_function;
  orig_ignore_func = rl_ignore_some_completions_function;
  orig_suppress = rl_completion_suppress_append;
  orig_sort = rl_sort_completion_matches;

  rl_menu_completion_entry_function = history_completion_generator;
  rl_attempted_completion_function = (rl_completion_func_t *)NULL;
  rl_ignore_some_completions_function = filename_completion_ignore;
  rl_filename_completion_desired = 0;
  rl_completion_suppress_append = 1;
  rl_sort_completion_matches = 0;

  
  dabbrev_expand_active = 1;
  if (rl_last_func == bash_dabbrev_expand)
    rl_last_func = rl_menu_complete;
  r = rl_menu_complete (count, key);
  dabbrev_expand_active = 0;

  rl_last_func = bash_dabbrev_expand;
  rl_menu_completion_entry_function = orig_func;
  rl_attempted_completion_function = orig_attempt_func;
  rl_ignore_some_completions_function = orig_ignore_func;
  rl_completion_suppress_append = orig_suppress;
  rl_sort_completion_matches = orig_sort;

  return r;
}