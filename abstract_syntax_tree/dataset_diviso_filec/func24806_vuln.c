execute_arith_for_command (arith_for_command)
     ARITH_FOR_COM *arith_for_command;
{
  intmax_t expresult;
  int expok, body_status, arith_lineno, save_lineno;

  body_status = EXECUTION_SUCCESS;
  loop_level++;
  save_lineno = line_number;

  if (arith_for_command->flags & CMD_IGNORE_RETURN)
    arith_for_command->action->flags |= CMD_IGNORE_RETURN;

  this_command_name = "STR";	

  
  line_number = arith_lineno = arith_for_command->line;
  if (variable_context && interactive_shell)
    line_number -= function_line_number;

  
  expresult = eval_arith_for_expr (arith_for_command->init, &expok);
  if (expok == 0)
    {
      line_number = save_lineno;
      return (EXECUTION_FAILURE);
    }

  while (1)
    {
      
      line_number = arith_lineno;
      expresult = eval_arith_for_expr (arith_for_command->test, &expok);
      line_number = save_lineno;

      if (expok == 0)
	{
	  body_status = EXECUTION_FAILURE;
	  break;
	}
      REAP ();
      if (expresult == 0)
	break;

      
      QUIT;
      body_status = execute_command (arith_for_command->action);
      QUIT;

      
      if (breaking)
	{
	  breaking--;
	  break;
	}

      if (continuing)
	{
	  continuing--;
	  if (continuing)
	    break;
	}

      
      line_number = arith_lineno;
      expresult = eval_arith_for_expr (arith_for_command->step, &expok);
      line_number = save_lineno;

      if (expok == 0)
	{
	  body_status = EXECUTION_FAILURE;
	  break;
	}
    }

  loop_level--;
  line_number = save_lineno;

  return (body_status);
}