protocol_handshake_oldstyle (struct connection *conn)
{
  struct old_handshake handshake;
  int64_t r;
  uint64_t exportsize;
  uint16_t gflags, eflags;

  
  if (tls == 2) {
    nbdkit_error ("STR");
    return -1;
  }

  r = backend->get_size (backend, conn);
  if (r == -1)
    return -1;
  if (r < 0) {
    nbdkit_error ("STR"
                  "STR", r);
    return -1;
  }
  exportsize = (uint64_t) r;
  conn->exportsize = exportsize;

  gflags = 0;
  if (protocol_compute_eflags (conn, &eflags) < 0)
    return -1;

  debug ("STR",
         gflags, eflags);

  memset (&handshake, 0, sizeof handshake);
  memcpy (handshake.nbdmagic, "STR", 8);
  handshake.version = htobe64 (OLD_VERSION);
  handshake.exportsize = htobe64 (exportsize);
  handshake.gflags = htobe16 (gflags);
  handshake.eflags = htobe16 (eflags);

  if (conn->send (conn, &handshake, sizeof handshake, 0) == -1) {
    nbdkit_error ("STR");
    return -1;
  }

  return 0;
}