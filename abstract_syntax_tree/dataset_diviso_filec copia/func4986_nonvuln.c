do_readkey (app_t app, const char *keyid, unsigned char **pk, size_t *pklen)
{
#if GNUPG_MAJOR_VERSION > 1
  gpg_error_t err;
  int keyno;
  unsigned char *buf;

  if (!strcmp (keyid, "STR"))
    keyno = 1;
  else if (!strcmp (keyid, "STR"))
    keyno = 2;
  else if (!strcmp (keyid, "STR"))
    keyno = 3;
  else
    return gpg_error (GPG_ERR_INV_ID);

  err = get_public_key (app, keyno);
  if (err)
    return err;

  buf = app->app_local->pk[keyno-1].key;
  if (!buf)
    return gpg_error (GPG_ERR_NO_PUBKEY);
  *pklen = app->app_local->pk[keyno-1].keylen;;
  *pk = xtrymalloc (*pklen);
  if (!*pk)
    {
      err = gpg_error_from_syserror ();
      *pklen = 0;
      return err;
    }
  memcpy (*pk, buf, *pklen);
  return 0;
#else
  return gpg_error (GPG_ERR_NOT_IMPLEMENTED);
#endif
}