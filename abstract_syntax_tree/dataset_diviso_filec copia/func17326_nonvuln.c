do_readcert (app_t app, const char *certid,
             unsigned char **cert, size_t *certlen)
{
#if GNUPG_MAJOR_VERSION > 1
  gpg_error_t err;
  unsigned char *buffer;
  size_t buflen;
  void *relptr;

  *cert = NULL;
  *certlen = 0;
  if (strcmp (certid, "STR"))
    return gpg_error (GPG_ERR_INV_ID);
  if (!app->app_local->extcap.is_v2)
    return gpg_error (GPG_ERR_NOT_FOUND);

  relptr = get_one_do (app, 0x7F21, &buffer, &buflen, NULL);
  if (!relptr)
    return gpg_error (GPG_ERR_NOT_FOUND);

  if (!buflen)
    err = gpg_error (GPG_ERR_NOT_FOUND);
  else if (!(*cert = xtrymalloc (buflen)))
    err = gpg_error_from_syserror ();
  else
    {
      memcpy (*cert, buffer, buflen);
      *certlen = buflen;
      err  = 0;
    }
  xfree (relptr);
  return err;
#else
  return gpg_error (GPG_ERR_NOT_IMPLEMENTED);
#endif
}