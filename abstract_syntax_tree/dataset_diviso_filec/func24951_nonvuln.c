backend_extents (struct backend *b, struct connection *conn,
                 uint32_t count, uint64_t offset, uint32_t flags,
                 struct nbdkit_extents *extents, int *err)
{
  struct b_conn_handle *h = &conn->handles[b->i];
  int r;

  assert (h->can_extents >= 0);
  assert (backend_valid_range (b, conn, offset, count));
  assert (!(flags & ~NBDKIT_FLAG_REQ_ONE));
  debug ("STR",
         b->name, count, offset, !!(flags & NBDKIT_FLAG_REQ_ONE));

  if (h->can_extents == 0) {
    
    r = nbdkit_add_extent (extents, offset, count, 0 );
    if (r == -1)
      *err = errno;
    return r;
  }
  r = b->extents (b, conn, count, offset, flags, extents, err);
  if (r == -1)
    assert (*err);
  return r;
}