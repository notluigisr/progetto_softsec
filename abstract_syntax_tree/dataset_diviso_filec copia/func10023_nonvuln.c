g_tls_connection_base_dtls_shutdown_async (GDtlsConnection     *conn,
                                           gboolean             shutdown_read,
                                           gboolean             shutdown_write,
                                           int                  io_priority,
                                           GCancellable        *cancellable,
                                           GAsyncReadyCallback  callback,
                                           gpointer             user_data)
{
  GTlsDirection direction = G_TLS_DIRECTION_NONE;

  if (shutdown_read)
    direction |= G_TLS_DIRECTION_READ;
  if (shutdown_write)
    direction |= G_TLS_DIRECTION_WRITE;

  g_tls_connection_base_close_internal_async (G_IO_STREAM (conn), direction,
                                              io_priority, cancellable,
                                              callback, user_data);
}