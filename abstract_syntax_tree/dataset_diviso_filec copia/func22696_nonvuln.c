backend_open (struct backend *b, struct connection *conn, int readonly)
{
  struct b_conn_handle *h = &conn->handles[b->i];
  int r;

  debug ("STR", b->name, readonly);

  assert (h->handle == NULL);
  assert (h->can_write == -1);
  if (readonly)
    h->can_write = 0;
  r = b->open (b, conn, readonly);
  if (r == 0) {
    assert (h->handle != NULL);
    if (b->i) 
      assert (conn->handles[b->i - 1].handle);
  }
  else
    assert (h->handle == NULL);
  return r;
}