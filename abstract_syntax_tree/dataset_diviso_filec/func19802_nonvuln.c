without_job_control ()
{
  stop_making_children ();
  last_made_pid = NO_PID;	
}