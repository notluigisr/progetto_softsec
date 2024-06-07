tls_client_basic_ctx_init(SSL_CTX * ctx,
    host_item * host, smtp_transport_options_block * ob, tls_ext_ctx_cb * cbinfo
			  )
{
int rc;


if (  (  !ob->tls_verify_hosts
      && (!ob->tls_try_verify_hosts || !*ob->tls_try_verify_hosts)
      )
   || (verify_check_given_host(&ob->tls_verify_hosts, host) == OK)
   )
  client_verify_optional = FALSE;
else if (verify_check_given_host(&ob->tls_try_verify_hosts, host) == OK)
  client_verify_optional = TRUE;
else
  return OK;

if ((rc = setup_certs(ctx, ob->tls_verify_certificates,
      ob->tls_crl, host, client_verify_optional, verify_callback_client)) != OK)
  return rc;

if (verify_check_given_host(&ob->tls_verify_cert_hostnames, host) == OK)
  {
  cbinfo->verify_cert_hostnames =
#ifdef EXPERIMENTAL_INTERNATIONAL
    string_domain_utf8_to_alabel(host->name, NULL);
#else
    host->name;
#endif
  DEBUG(D_tls) debug_printf("STR",
		    cbinfo->verify_cert_hostnames);
  }
return OK;
}