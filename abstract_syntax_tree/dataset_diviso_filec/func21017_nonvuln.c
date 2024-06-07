pn_ssl_resume_status_t pn_ssl_resume_status(pn_ssl_t *ssl0)
{
  pni_ssl_t *ssl = get_ssl_internal(ssl0);
  if (!ssl || !ssl->ssl) return PN_SSL_RESUME_UNKNOWN;
  switch (SSL_session_reused( ssl->ssl )) {
   case 0: return PN_SSL_RESUME_NEW;
   case 1: return PN_SSL_RESUME_REUSED;
   default: break;
  }
  return PN_SSL_RESUME_UNKNOWN;
}