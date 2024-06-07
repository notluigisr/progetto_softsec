protocol_compute_eflags (struct connection *conn, uint16_t *flags)
{
  uint16_t eflags = NBD_FLAG_HAS_FLAGS;
  int fl;

  
  fl = backend_can_write (backend, conn);
  if (fl == -1)
    return -1;
  if (!fl)
    eflags |= NBD_FLAG_READ_ONLY;

  fl = backend_can_zero (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_WRITE_ZEROES;

  fl = backend_can_fast_zero (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_FAST_ZERO;

  fl = backend_can_trim (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_TRIM;

  fl = backend_can_fua (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_FUA;

  fl = backend_can_flush (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_FLUSH;

  fl = backend_is_rotational (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_ROTATIONAL;

  
  fl = backend_can_multi_conn (backend, conn);
  if (fl == -1)
    return -1;
  if (fl && (backend->thread_model (backend) >
             NBDKIT_THREAD_MODEL_SERIALIZE_CONNECTIONS))
    eflags |= NBD_FLAG_CAN_MULTI_CONN;

  fl = backend_can_cache (backend, conn);
  if (fl == -1)
    return -1;
  if (fl)
    eflags |= NBD_FLAG_SEND_CACHE;

  
  fl = backend_can_extents (backend, conn);
  if (fl == -1)
    return -1;

  if (conn->structured_replies)
    eflags |= NBD_FLAG_SEND_DF;

  *flags = eflags;
  return 0;
}