ecc_j_to_a (const struct ecc_curve *ecc,
	    int op,
	    mp_limb_t *r, const mp_limb_t *p,
	    mp_limb_t *scratch)
{





  ecc->p.invert (&ecc->p, izp, p+2*ecc->p.size, izp + ecc->p.size);
  ecc_mod_sqr (&ecc->p, iz2p, izp, iz2p);

  if (ecc->use_redc)
    {
      
      mpn_zero (iz2p + ecc->p.size, ecc->p.size);
      ecc->p.reduce (&ecc->p, iz2p, iz2p);
    }

  
  ecc_mod_mul_canonical (&ecc->p, r, iz2p, p, iz3p);
  if (op)
    {
      
      if (op > 1)
	{
	  mp_limb_t cy;
	  
	  cy = mpn_sub_n (scratch, r, ecc->q.m, ecc->p.size);
	  cnd_copy (cy == 0, r, scratch, ecc->p.size);
	}
      return;
    }
  ecc_mod_mul (&ecc->p, iz3p, iz2p, izp, iz3p);
  ecc_mod_mul_canonical (&ecc->p, r + ecc->p.size, iz3p, p + ecc->p.size, tp);

#undef izp
#undef iz2p
#undef iz3p
#undef tp
}