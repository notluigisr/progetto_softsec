init_noninteractive ()
{
#if defined (HISTORY)
  bash_history_reinit (0);
#endif 
  interactive_shell = startup_state = interactive = 0;
  expand_aliases = posixly_correct;	
  no_line_editing = 1;
#if defined (JOB_CONTROL)
  
  set_job_control (forced_interactive||jobs_m_flag);
#endif 
}