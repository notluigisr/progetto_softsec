tls_client_start(int fd, host_item *host, address_item *addr, uschar *dhparam,
  uschar *certificate, uschar *privatekey, uschar *verify_certs, uschar *crl,
  uschar *require_ciphers, uschar *require_mac, uschar *require_kx,
  uschar *require_proto, int timeout)
{
static uschar txt[256];
uschar *expciphers;
X509* server_cert;
int rc;

rc = tls_init(host, dhparam, certificate, privatekey, addr);
if (rc != OK) return rc;

tls_certificate_verified = FALSE;
verify_callback_called = FALSE;

if (!expand_check(require_ciphers, US"STR", &expciphers))
  return FAIL;



if (expciphers != NULL)
  {
  uschar *s = expciphers;
  while (*s != 0) { if (*s == '_') *s = '-'; s++; }
  DEBUG(D_tls) debug_printf("STR", expciphers);
  if (!SSL_CTX_set_cipher_list(ctx, CS expciphers))
    return tls_error(US"STR", host, NULL);
  }

rc = setup_certs(verify_certs, crl, host, FALSE);
if (rc != OK) return rc;

if ((ssl = SSL_new(ctx)) == NULL) return tls_error(US"STR", host, NULL);
SSL_set_session_id_context(ssl, sid_ctx, Ustrlen(sid_ctx));
SSL_set_fd(ssl, fd);
SSL_set_connect_state(ssl);



DEBUG(D_tls) debug_printf("STR");
sigalrm_seen = FALSE;
alarm(timeout);
rc = SSL_connect(ssl);
alarm(0);

if (rc <= 0)
  return tls_error(US"STR" : NULL);

DEBUG(D_tls) debug_printf("STR");


server_cert = SSL_get_peer_certificate (ssl);
if (server_cert)
  {
  tls_peerdn = US X509_NAME_oneline(X509_get_subject_name(server_cert),
    CS txt, sizeof(txt));
  tls_peerdn = txt;
  }
else
  tls_peerdn = NULL;

construct_cipher_name(ssl);   

tls_active = fd;
return OK;
}