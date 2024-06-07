finish_newstyle_options (struct connection *conn, uint64_t *exportsize)
{
  int64_t r;

  r = backend_get_size (backend, conn);
  if (r == -1)
    return -1;
  if (r < 0) {
    nbdkit_error ("STR"
                  "STR", r);
    return -1;
  }
  *exportsize = r;

  if (protocol_compute_eflags (conn, &conn->eflags) < 0)
    return -1;

  debug ("STR", conn->eflags);
  return 0;
}