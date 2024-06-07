Item_func_sp::execute()
{
  THD *thd= current_thd;
  
  

  if (execute_impl(thd))
  {
    null_value= 1;
    context->process_error(thd);
    if (thd->killed)
      thd->send_kill_message();
    return TRUE;
  }

  

  null_value= sp_result_field->is_null();

  return null_value;
}