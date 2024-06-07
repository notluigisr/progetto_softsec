  void add_status_to_global()
  {
    DBUG_ASSERT(status_in_global == 0);
    mysql_mutex_lock(&LOCK_status);
    add_to_status(&global_status_var, &status_var);
    
    status_var.global_memory_used= 0;
    status_in_global= 1;
    mysql_mutex_unlock(&LOCK_status);
  }