  inline void set_killed(killed_state killed_arg,
                         int killed_errno_arg= 0,
                         const char *killed_err_msg_arg= 0)
  {
    mysql_mutex_lock(&LOCK_thd_kill);
    set_killed_no_mutex(killed_arg, killed_errno_arg, killed_err_msg_arg);
    mysql_mutex_unlock(&LOCK_thd_kill);
  }