SSL_CTX_use_certificate_bio(SSL_CTX *ctx, BIO *in, int type,
                            const char *key_passwd)
{
  int ret = 0;
  X509 *x = NULL;

  if(type == SSL_FILETYPE_ASN1) {
    
    x = d2i_X509_bio(in, NULL);
  }
  else if(type == SSL_FILETYPE_PEM) {
    
    x = PEM_read_bio_X509(in, NULL,
                          passwd_callback, (void *)key_passwd);
  }
  else {
    ret = 0;
    goto end;
  }

  if(x == NULL) {
    ret = 0;
    goto end;
  }

  ret = SSL_CTX_use_certificate(ctx, x);
 end:
  X509_free(x);
  return ret;
}