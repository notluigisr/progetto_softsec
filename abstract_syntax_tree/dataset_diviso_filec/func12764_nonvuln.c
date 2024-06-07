filter_close (struct backend *b, struct connection *conn)
{
  struct backend_filter *f = container_of (b, struct backend_filter, backend);
  void *handle = connection_get_handle (conn, f->backend.i);

  debug ("STR", f->name);

  if (handle && f->filter.close)
    f->filter.close (handle);
  f->backend.next->close (f->backend.next, conn);
  connection_set_handle (conn, f->backend.i, NULL);
}