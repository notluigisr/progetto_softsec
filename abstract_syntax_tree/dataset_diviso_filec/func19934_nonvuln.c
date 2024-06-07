_gcry_mpi_ec_bad_point (gcry_mpi_point_t point, mpi_ec_t ctx)
{
  int i;
  gcry_mpi_t x_bad;

  for (i = 0; (x_bad = ctx->t.scratch[i]); i++)
    if (!mpi_cmp (point->x, x_bad))
      return 1;

  return 0;
}