static inline pn_transport_t *get_transport_internal(pn_ssl_t *ssl)
{
  
  return ((pn_transport_t *)ssl);
}