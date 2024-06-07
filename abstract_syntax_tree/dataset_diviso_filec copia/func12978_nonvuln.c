filter_close (struct backend *b, struct connection *conn)
{
  struct backend_filter *f = container_of (b, struct backend_filter, backend);
  void *handle = connection_get_handle (conn, b->i);

  if (handle && f->filter.close)
    f->filter.close (handle);
  backend_close (b->next, conn);
}