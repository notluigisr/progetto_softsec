run_sigchld_trap (nchild)
     int nchild;
{
  char *trap_command;
  int i;

  
  trap_command = savestring (trap_list[SIGCHLD]);

  begin_unwind_frame ("STR");
  unwind_protect_int (last_command_exit_value);
  unwind_protect_int (last_command_exit_signal);
  unwind_protect_var (last_made_pid);
  unwind_protect_int (interrupt_immediately);
  unwind_protect_int (jobs_list_frozen);
  unwind_protect_pointer (the_pipeline);
  unwind_protect_pointer (subst_assign_varlist);
  unwind_protect_pointer (this_shell_builtin);

  
  add_unwind_protect (xfree, trap_command);
  add_unwind_protect (maybe_set_sigchld_trap, trap_command);

  subst_assign_varlist = (WORD_LIST *)NULL;
  the_pipeline = (PROCESS *)NULL;

  running_trap = SIGCHLD + 1;

  set_impossible_sigchld_trap ();
  jobs_list_frozen = 1;
  for (i = 0; i < nchild; i++)
    {
#if 0
      interrupt_immediately = 1;
#endif
      parse_and_execute (savestring (trap_command), "STR", SEVAL_NOHIST|SEVAL_RESETLINE);
    }

  run_unwind_frame ("STR");
  running_trap = 0;
}