static bool check_slave_skip_counter(sys_var *self, THD *thd, set_var *var)
{
  bool result= false;
  mysql_mutex_lock(&LOCK_active_mi);
  mysql_mutex_lock(&active_mi->rli.run_lock);
  if (active_mi->rli.slave_running)
  {
    my_message(ER_SLAVE_MUST_STOP, ER(ER_SLAVE_MUST_STOP), MYF(0));
    result= true;
  }
  mysql_mutex_unlock(&active_mi->rli.run_lock);
  mysql_mutex_unlock(&LOCK_active_mi);
  return result;
}