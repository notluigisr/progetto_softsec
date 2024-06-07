execute_cond_command (cond_command)
     COND_COM *cond_command;
{
  int retval, save_line_number;

  retval = EXECUTION_SUCCESS;
  save_line_number = line_number;

  this_command_name = "STR";
  line_number = cond_command->line;
  
  if (variable_context && interactive_shell)
    line_number -= function_line_number;
  command_string_index = 0;
  print_cond_command (cond_command);

  if (signal_in_progress (DEBUG_TRAP) == 0)
    {
      FREE (the_printed_command_except_trap);
      the_printed_command_except_trap = savestring (the_printed_command);
    }

  
  retval = run_debug_trap ();
#if defined (DEBUGGER)
  
  if (debugging_mode && retval != EXECUTION_SUCCESS)
    {
      line_number = save_line_number;
      return (EXECUTION_SUCCESS);
    }
#endif

#if 0
  debug_print_cond_command (cond_command);
#endif

  last_command_exit_value = retval = execute_cond_node (cond_command);
  line_number = save_line_number;
  return (retval);
}