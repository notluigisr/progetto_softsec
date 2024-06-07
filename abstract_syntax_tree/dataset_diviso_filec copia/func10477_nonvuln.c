protocol_handshake_oldstyle (struct connection *conn)
{
  struct old_handshake handshake;
  uint64_t exportsize;
  uint16_t gflags, eflags;

  
  if (tls == 2) {
    nbdkit_error ("STR");
    return -1;
  }

  if (protocol_common_open (conn, &exportsize, &eflags) == -1)
    return -1;

  gflags = 0;
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