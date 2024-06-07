curve25519_eh_to_x (mp_limb_t *xp, const mp_limb_t *p,
		    mp_limb_t *scratch)
{






  const struct ecc_curve *ecc = &_nettle_curve25519;
  mp_limb_t cy;

  
  
  ecc_mod_sub (&ecc->p, t0, wp, vp);
  
  ecc->p.invert (&ecc->p, t1, t0, tp);
  
  ecc_mod_add (&ecc->p, t0, wp, vp);
  ecc_mod_mul (&ecc->p, t0, t0, t1, tp);

  cy = mpn_sub_n (xp, t0, ecc->p.m, ecc->p.size);
  cnd_copy (cy, xp, t0, ecc->p.size);
#undef vp
#undef wp
#undef t0
#undef t1
#undef tp
}