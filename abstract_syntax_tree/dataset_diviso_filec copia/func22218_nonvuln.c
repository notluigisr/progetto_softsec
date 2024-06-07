tls_servername_cb(SSL *s, int *ad ARG_UNUSED, void *arg)
{
const char *servername = SSL_get_servername(s, TLSEXT_NAMETYPE_host_name);
const tls_ext_ctx_cb *cbinfo = (tls_ext_ctx_cb *) arg;
int rc;

if (!servername)
  return SSL_TLSEXT_ERR_OK;

DEBUG(D_tls) debug_printf("STR", servername,
    reexpand_tls_files_for_sni ? "STR");


tls_sni = servername;

if (!reexpand_tls_files_for_sni)
  return SSL_TLSEXT_ERR_OK;



ctx_sni = SSL_CTX_new(SSLv23_server_method());
if (!ctx_sni)
  {
  ERR_error_string(ERR_get_error(), ssl_errstring);
  DEBUG(D_tls) debug_printf("STR", ssl_errstring);
  return SSL_TLSEXT_ERR_NOACK;
  }



SSL_CTX_set_info_callback(ctx_sni, SSL_CTX_get_info_callback(ctx));
SSL_CTX_set_mode(ctx_sni, SSL_CTX_get_mode(ctx));
SSL_CTX_set_options(ctx_sni, SSL_CTX_get_options(ctx));
SSL_CTX_set_timeout(ctx_sni, SSL_CTX_get_timeout(ctx));
SSL_CTX_set_tlsext_servername_callback(ctx_sni, tls_servername_cb);
SSL_CTX_set_tlsext_servername_arg(ctx_sni, cbinfo);
if (cbinfo->server_cipher_list)
  SSL_CTX_set_cipher_list(ctx_sni, CS cbinfo->server_cipher_list);

rc = tls_expand_session_files(ctx_sni, cbinfo);
if (rc != OK) return SSL_TLSEXT_ERR_NOACK;

rc = setup_certs(ctx_sni, tls_verify_certificates, tls_crl, NULL, FALSE);
if (rc != OK) return SSL_TLSEXT_ERR_NOACK;

DEBUG(D_tls) debug_printf("STR");
SSL_set_SSL_CTX(s, ctx_sni);

return SSL_TLSEXT_ERR_OK;
}