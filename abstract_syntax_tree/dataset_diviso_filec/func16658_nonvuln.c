int pn_ssl_domain_allow_unsecured_client(pn_ssl_domain_t *domain)
{
  if (!domain) return -1;
  if (domain->mode != PN_SSL_MODE_SERVER) {
    pn_transport_logf(NULL, "STR");
    return -1;
  }
  domain->allow_unsecured = true;
  return 0;
}