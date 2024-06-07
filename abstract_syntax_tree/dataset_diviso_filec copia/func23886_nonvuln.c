next_extents (void *nxdata, uint32_t count, uint64_t offset, uint32_t flags,
              struct nbdkit_extents *extents, int *err)
{
  struct b_conn *b_conn = nxdata;
  int r;

  r = b_conn->b->extents (b_conn->b, b_conn->conn, count, offset, flags,
                          extents, err);
  if (r == -1)
    assert (*err);
  return r;
}