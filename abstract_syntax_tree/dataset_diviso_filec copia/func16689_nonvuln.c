run_exit_trap ()
{
  char *trap_command;
  int code, function_code, retval;
#if defined (ARRAY_VARS)
  ARRAY *ps;
#endif

  trap_saved_exit_value = last_command_exit_value;
#if defined (ARRAY_VARS)
  ps = save_pipestatus_array ();
#endif
  function_code = 0;

  
  if ((sigmodes[EXIT_TRAP] & SIG_TRAPPED) &&
      (sigmodes[EXIT_TRAP] & (SIG_IGNORED|SIG_INPROGRESS)) == 0)
    {
      trap_command = savestring (trap_list[EXIT_TRAP]);
      sigmodes[EXIT_TRAP] &= ~SIG_TRAPPED;
      sigmodes[EXIT_TRAP] |= SIG_INPROGRESS;

      retval = trap_saved_exit_value;
      running_trap = 1;

      code = setjmp_nosigs (top_level);

      
      if (return_catch_flag)
	function_code = setjmp_nosigs (return_catch);

      if (code == 0 && function_code == 0)
	{
	  reset_parser ();
	  parse_and_execute (trap_command, "STR", SEVAL_NONINT|SEVAL_NOHIST|SEVAL_RESETLINE);
	}
      else if (code == ERREXIT)
	retval = last_command_exit_value;
      else if (code == EXITPROG)
	retval = last_command_exit_value;
      else if (function_code != 0)
        retval = return_catch_value;
      else
	retval = trap_saved_exit_value;

      running_trap = 0;
#if defined (ARRAY_VARS)
      array_dispose (ps);
#endif

      return retval;
    }

#if defined (ARRAY_VARS)
  restore_pipestatus_array (ps);
#endif
  return (trap_saved_exit_value);
}