ecc_mod_mul_canonical (const struct ecc_modulo *m, mp_limb_t *rp,
		       const mp_limb_t *ap, const mp_limb_t *bp, mp_limb_t *tp)
{
  mp_limb_t cy;
  mpn_mul_n (tp, ap, bp, m->size);
  m->reduce (m, tp + m->size, tp);

  cy = mpn_sub_n (rp, tp + m->size, m->m, m->size);
  cnd_copy (cy, rp, tp + m->size, m->size);
}