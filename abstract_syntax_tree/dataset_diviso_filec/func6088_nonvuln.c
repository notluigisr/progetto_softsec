bits2octets (unsigned char **r_frame,
             const void *bits, unsigned int nbits,
             gcry_mpi_t q, unsigned int qbits)
{
  gpg_err_code_t rc;
  gcry_mpi_t z1;

  
  rc = _gcry_mpi_scan (&z1, GCRYMPI_FMT_USG, bits, (nbits+7)/8, NULL);
  if (rc)
    return rc;
  if (nbits > qbits)
    mpi_rshift (z1, z1, nbits - qbits);

  
  if (mpi_cmp (z1, q) >= 0)
    mpi_sub (z1, z1, q);

  
  rc = int2octets (r_frame, z1, (qbits+7)/8);

  mpi_free (z1);
  return rc;
}