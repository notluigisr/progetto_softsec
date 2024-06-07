ecc_ecdsa_sign (const struct ecc_curve *ecc,
		const mp_limb_t *zp,
		
		const mp_limb_t *kp,
		size_t length, const uint8_t *digest,
		mp_limb_t *rp, mp_limb_t *sp,
		mp_limb_t *scratch)
{




  

  ecc->mul_g (ecc, P, kp, P + 3*ecc->p.size);
  
  ecc->h_to_a (ecc, 2, rp, P, P + 3*ecc->p.size);

  
  ecc->q.invert (&ecc->q, kinv, kp, tp);
  
  
  ecc_hash (&ecc->q, hp, length, digest);

  ecc_mod_mul (&ecc->q, tp, zp, rp, tp);
  ecc_mod_add (&ecc->q, hp, hp, tp);
  ecc_mod_mul (&ecc->q, tp, hp, kinv, tp);

  mpn_copyi (sp, tp, ecc->p.size);
#undef P
#undef hp
#undef kinv
#undef tp
}