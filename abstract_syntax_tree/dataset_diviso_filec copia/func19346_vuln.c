curve448_eh_to_x (mp_limb_t *xp, const mp_limb_t *p, mp_limb_t *scratch)
{





  const struct ecc_curve *ecc = &_nettle_curve448;
  mp_limb_t cy;

  
  
  ecc->p.invert (&ecc->p, t0, up, tp);
  ecc_mod_mul (&ecc->p, t0, t0, vp, tp);
  ecc_mod_sqr (&ecc->p, t0, t0, tp);

  cy = mpn_sub_n (xp, t0, ecc->p.m, ecc->p.size);
  cnd_copy (cy, xp, t0, ecc->p.size);
#undef up
#undef vp
#undef t0
#undef tp
}