ecc_eh_to_a (const struct ecc_curve *ecc,
	     int op,
	     mp_limb_t *r, const mp_limb_t *p,
	     mp_limb_t *scratch)
{








  mp_limb_t cy;

  assert(op == 0);

  
  ecc->p.invert (&ecc->p, izp, zp, tp);

  ecc_mod_mul (&ecc->p, tp, xp, izp, tp);
  cy = mpn_sub_n (r, tp, ecc->p.m, ecc->p.size);
  cnd_copy (cy, r, tp, ecc->p.size);

  ecc_mod_mul (&ecc->p, tp, yp, izp, tp);
  cy = mpn_sub_n (r + ecc->p.size, tp, ecc->p.m, ecc->p.size);
  cnd_copy (cy, r + ecc->p.size, tp, ecc->p.size);
}