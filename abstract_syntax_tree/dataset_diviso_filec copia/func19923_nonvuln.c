alloc_and_load_pgp_certs (gnutls_openpgp_crt_t cert)
{
  gnutls_pcert_st *local_certs;
  int ret = 0;

  if (cert == NULL)
    return NULL;

  local_certs = gnutls_malloc (sizeof (gnutls_pcert_st));
  if (local_certs == NULL)
    {
      gnutls_assert ();
      return NULL;
    }

  ret = gnutls_pcert_import_openpgp (local_certs, cert, 0);
  if (ret < 0)
    {
      gnutls_assert ();
      return NULL;
    }

  if (ret < 0)
    {
      gnutls_assert ();
      gnutls_pcert_deinit (local_certs);
      gnutls_free (local_certs);
      return NULL;
    }

  return local_certs;
}