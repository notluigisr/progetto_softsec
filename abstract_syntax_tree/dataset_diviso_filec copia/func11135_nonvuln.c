new_connection (int sockin, int sockout, int nworkers)
{
  struct connection *conn;

  conn = calloc (1, sizeof *conn);
  if (conn == NULL) {
    perror ("STR");
    return NULL;
  }

  conn->status = 1;
  conn->nworkers = nworkers;
  conn->sockin = sockin;
  conn->sockout = sockout;
  pthread_mutex_init (&conn->request_lock, NULL);
  pthread_mutex_init (&conn->read_lock, NULL);
  pthread_mutex_init (&conn->write_lock, NULL);
  pthread_mutex_init (&conn->status_lock, NULL);

  conn->recv = raw_recv;
  conn->send = raw_send;
  conn->close = raw_close;

  return conn;
}