bool Item_subselect::exec()
{
  subselect_engine *org_engine= engine;

  DBUG_ENTER("STR");
  DBUG_ASSERT(fixed);

  
  if (thd->is_error() || thd->killed)
    DBUG_RETURN(true);

  DBUG_ASSERT(!thd->lex->context_analysis_only);
  
  DBUG_EXECUTE_IF("STR", DBUG_RETURN(true););

  bool res= engine->exec();

#ifndef DBUG_OFF
  ++exec_counter;
#endif
  if (engine != org_engine)
  {
    
    DBUG_RETURN(exec());
  }
  DBUG_RETURN(res);
}