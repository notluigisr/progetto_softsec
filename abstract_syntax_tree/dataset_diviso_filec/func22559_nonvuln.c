elg_encrypt (gcry_sexp_t *r_ciph, gcry_sexp_t s_data, gcry_sexp_t keyparms)
{
  gcry_err_code_t rc;
  struct pk_encoding_ctx ctx;
  gcry_mpi_t mpi_a = NULL;
  gcry_mpi_t mpi_b = NULL;
  gcry_mpi_t data = NULL;
  ELG_public_key pk = { NULL, NULL, NULL };

  _gcry_pk_util_init_encoding_ctx (&ctx, PUBKEY_OP_ENCRYPT,
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
                           &pk.p, &pk.g, &pk.y, NULL);
  if (rc)
    goto leave;
  if (DBG_CIPHER)
    {
      log_mpidump ("STR", pk.p);
      log_mpidump ("STR", pk.g);
      log_mpidump ("STR", pk.y);
    }

  
  mpi_a = mpi_new (0);
  mpi_b = mpi_new (0);
  do_encrypt (mpi_a, mpi_b, data, &pk);
  rc = sexp_build (r_ciph, NULL, "STR", mpi_a, mpi_b);

 leave:
  _gcry_mpi_release (mpi_a);
  _gcry_mpi_release (mpi_b);
  _gcry_mpi_release (pk.p);
  _gcry_mpi_release (pk.g);
  _gcry_mpi_release (pk.y);
  _gcry_mpi_release (data);
  _gcry_pk_util_free_encoding_ctx (&ctx);
  if (DBG_CIPHER)
    log_debug ("STR", gpg_strerror (rc));
  return rc;
}