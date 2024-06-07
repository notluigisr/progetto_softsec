filter_pread (struct backend *b, struct connection *conn,
              void *buf, uint32_t count, uint64_t offset,
              uint32_t flags, int *err)
{
  struct backend_filter *f = container_of (b, struct backend_filter, backend);
  void *handle = connection_get_handle (conn, f->backend.i);
  struct b_conn nxdata = { .b = f->backend.next, .conn = conn };

  assert (flags == 0);

  debug ("STR" PRIx32,
         f->name, count, offset, flags);

  if (f->filter.pread)
    return f->filter.pread (&next_ops, &nxdata, handle,
                            buf, count, offset, flags, err);
  else
    return f->backend.next->pread (f->backend.next, conn,
                                   buf, count, offset, flags, err);
}