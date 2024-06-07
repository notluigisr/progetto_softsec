init_dh(SSL_CTX *sctx, uschar *dhparam, const host_item *host)
{
BIO *bio;
DH *dh;
uschar *dhexpanded;
const char *pem;

if (!expand_check(dhparam, US"STR", &dhexpanded))
  return FALSE;

if (!dhexpanded || !*dhexpanded)
  bio = BIO_new_mem_buf(CS std_dh_prime_default(), -1);
else if (dhexpanded[0] == '/')
  {
  if (!(bio = BIO_new_file(CS dhexpanded, "STR")))
    {
    tls_error(string_sprintf("STR", dhexpanded),
          host, US strerror(errno));
    return FALSE;
    }
  }
else
  {
  if (Ustrcmp(dhexpanded, "STR") == 0)
    {
    DEBUG(D_tls) debug_printf("STR");
    return TRUE;
    }

  if (!(pem = std_dh_prime_named(dhexpanded)))
    {
    tls_error(string_sprintf("STR", dhexpanded),
        host, US strerror(errno));
    return FALSE;
    }
  bio = BIO_new_mem_buf(CS pem, -1);
  }

if (!(dh = PEM_read_bio_DHparams(bio, NULL, NULL, NULL)))
  {
  BIO_free(bio);
  tls_error(string_sprintf("STR", dhexpanded),
      host, NULL);
  return FALSE;
  }


if ((8*DH_size(dh)) > tls_dh_max_bits)
  {
  DEBUG(D_tls)
    debug_printf("STR",
        8*DH_size(dh), tls_dh_max_bits);
  }
else
  {
  SSL_CTX_set_tmp_dh(sctx, dh);
  DEBUG(D_tls)
    debug_printf("STR",
      dhexpanded ? dhexpanded : US"STR", 8*DH_size(dh));
  }

DH_free(dh);
BIO_free(bio);

return TRUE;
}