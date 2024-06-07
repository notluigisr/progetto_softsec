dup_point_edwards (mpi_point_t result, mpi_point_t point, mpi_ec_t ctx)
{














  

  
  ec_addm (B, X1, Y1, ctx);
  ec_pow2 (B, B, ctx);

  
  
  ec_pow2 (C, X1, ctx);
  ec_pow2 (D, Y1, ctx);

  
  if (ctx->dialect == ECC_DIALECT_ED25519)
    mpi_sub (E, ctx->p, C);
  else
    ec_mulm (E, ctx->a, C, ctx);

  
  ec_addm (F, E, D, ctx);

  
  ec_pow2 (H, Z1, ctx);

  
  ec_mul2 (J, H, ctx);
  ec_subm (J, F, J, ctx);

  
  ec_subm (X3, B, C, ctx);
  ec_subm (X3, X3, D, ctx);
  ec_mulm (X3, X3, J, ctx);

  
  ec_subm (Y3, E, D, ctx);
  ec_mulm (Y3, Y3, F, ctx);

  
  ec_mulm (Z3, F, J, ctx);

#undef X1
#undef Y1
#undef Z1
#undef X3
#undef Y3
#undef Z3
#undef B
#undef C
#undef D
#undef E
#undef F
#undef H
#undef J
}