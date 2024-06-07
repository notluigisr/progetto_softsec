static my_bool find_thread_callback(THD *thd, find_thread_callback_arg *arg)
{
  if (arg->id == (arg->query_id ? thd->query_id : (longlong) thd->thread_id))
  {
    mysql_mutex_lock(&thd->LOCK_thd_kill);    
    arg->thd= thd;
    return 1;
  }
  return 0;
}