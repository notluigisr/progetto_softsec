elg_sign (gcry_sexp_t *r_sig, gcry_sexp_t s_data, gcry_sexp_t keyparms)
{
  gcry_err_code_t rc;
  struct pk_encoding_ctx ctx;
  gcry_mpi_t data = NULL;
  ELG_secret_key sk = {NULL, NULL, NULL, NULL};
  gcry_mpi_t sig_r = NULL;
  gcry_mpi_t sig_s = NULL;

  _gcry_pk_util_init_encoding_ctx (&ctx, PUBKEY_OP_SIGN,
                                   elg_get_nbits (keyparms));

  
  rc = _gcry_pk_util_data_to_mpi (s_data, &data, &ctx);
  if (rc)
    goto leave;
  if (DBG_CIPHER)
    log_mpidump ("STR", data);
  if (mpi_is_opaque (data))
    {
      rc = GPG_ERR_INV_DATA;
      goto leave;
    }

  
  rc = sexp_extract_param (keyparms, NULL, "STR",
                           &sk.p, &sk.g, &sk.y, &sk.x, NULL);
  if (rc)
    goto leave;
  if (DBG_CIPHER)
    {
      log_mpidump ("STR", sk.p);
      log_mpidump ("STR", sk.g);
      log_mpidump ("STR", sk.y);
      if (!fips_mode ())
        log_mpidump ("STR", sk.x);
    }

  sig_r = mpi_new (0);
  sig_s = mpi_new (0);
  sign (sig_r, sig_s, data, &sk);
  if (DBG_CIPHER)
    {
      log_mpidump ("STR", sig_r);
      log_mpidump ("STR", sig_s);
    }
  rc = sexp_build (r_sig, NULL, "STR", sig_r, sig_s);

 leave:
  _gcry_mpi_release (sig_r);
  _gcry_mpi_release (sig_s);
  _gcry_mpi_release (sk.p);
  _gcry_mpi_release (sk.g);
  _gcry_mpi_release (sk.y);
  _gcry_mpi_release (sk.x);
  _gcry_mpi_release (data);
  _gcry_pk_util_free_encoding_ctx (&ctx);
  if (DBG_CIPHER)
    log_debug ("STR", gpg_strerror (rc));
  return rc;
}