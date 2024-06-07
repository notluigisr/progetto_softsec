rsa_callback(SSL *s, int export, int keylength)
{
RSA *rsa_key;
export = export;     
DEBUG(D_tls) debug_printf("STR", keylength);
rsa_key = RSA_generate_key(keylength, RSA_F4, NULL, NULL);
if (rsa_key == NULL)
  {
  ERR_error_string(ERR_get_error(), ssl_errstring);
  log_write(0, LOG_MAIN|LOG_PANIC, "STR",
    ssl_errstring);
  return NULL;
  }
return rsa_key;
}