ec_p_init (mpi_ec_t ctx, enum gcry_mpi_ec_models model,
           enum ecc_dialects dialect,
           int flags,
           gcry_mpi_t p, gcry_mpi_t a, gcry_mpi_t b)
{
  int i;
  static int use_barrett;

  if (!use_barrett)
    {
      if (getenv ("STR"))
        use_barrett = 1;
      else
        use_barrett = -1;
    }

  

  ctx->model = model;
  ctx->dialect = dialect;
  ctx->flags = flags;
  if (dialect == ECC_DIALECT_ED25519)
    ctx->nbits = 256;
  else
    ctx->nbits = mpi_get_nbits (p);
  ctx->p = mpi_copy (p);
  ctx->a = mpi_copy (a);
  ctx->b = mpi_copy (b);

  ctx->t.p_barrett = use_barrett > 0? _gcry_mpi_barrett_init (ctx->p, 0):NULL;

  _gcry_mpi_ec_get_reset (ctx);

  
  for (i=0; i< DIM(ctx->t.scratch); i++)
    ctx->t.scratch[i] = mpi_alloc_like (ctx->p);

  
  













}