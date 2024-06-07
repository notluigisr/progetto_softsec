tor_tls_get_by_ssl(const SSL *ssl)
{
  tor_tls_t search, *result;
  memset(&search, 0, sizeof(search));
  search.ssl = (SSL*)ssl;
  result = HT_FIND(tlsmap, &tlsmap_root, &search);
  return result;
}