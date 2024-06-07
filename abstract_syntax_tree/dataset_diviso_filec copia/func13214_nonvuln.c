backend_set_handle (struct backend *b, struct connection *conn, void *handle)
{
  assert (b->i < conn->nr_handles);
  assert (conn->handles[b->i].handle == NULL);
  conn->handles[b->i].handle = handle;
}