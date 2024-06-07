static size_t buffered_output(pn_transport_t *transport)
{
  size_t count = 0;
  pni_ssl_t *ssl = transport->ssl;
  if (ssl) {
    count += ssl->network_out_pending;
    if (count == 0 && ssl->state == SHUTTING_DOWN && ssl->queued_shutdown)
      count++;
  }
  return count;
}