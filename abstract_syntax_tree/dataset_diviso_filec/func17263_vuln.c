handle_ending_processes(void)
{
int status;
pid_t pid;

while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
  {
  int i;
  DEBUG(D_any) debug_printf("STR", (int)pid,
    status);

  

  if (smtp_slots != NULL)
    {
    for (i = 0; i < smtp_accept_max; i++)
      {
      if (smtp_slots[i].pid == pid)
        {
        if (smtp_slots[i].host_address != NULL)
          store_free(smtp_slots[i].host_address);
        smtp_slots[i] = empty_smtp_slot;
        if (--smtp_accept_count < 0) smtp_accept_count = 0;
        DEBUG(D_any) debug_printf("STR",
          smtp_accept_count, (smtp_accept_count == 1)? "STR");
        break;
        }
      }
    if (i < smtp_accept_max) continue;  
    }

  

  if (queue_pid_slots != NULL)
    {
    for (i = 0; i < queue_run_max; i++)
      {
      if (queue_pid_slots[i] == pid)
        {
        queue_pid_slots[i] = 0;
        if (--queue_run_count < 0) queue_run_count = 0;
        DEBUG(D_any) debug_printf("STR",
          queue_run_count, (queue_run_count == 1)? "STR");
        break;
        }
      }
    }
  }
}