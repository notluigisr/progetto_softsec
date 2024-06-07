static void wait_query_thread_done(struct st_connection *con)
{
  DBUG_ASSERT(con->has_thread);
  if (!con->query_done)
  {
    pthread_mutex_lock(&con->result_mutex);
    while (!con->query_done)
      pthread_cond_wait(&con->result_cond, &con->result_mutex);
    pthread_mutex_unlock(&con->result_mutex);
  }
}