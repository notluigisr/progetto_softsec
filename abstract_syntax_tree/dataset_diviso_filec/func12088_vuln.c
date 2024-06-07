gostdsa_vko (const struct ecc_scalar *priv,
		const struct ecc_point *pub,
		size_t ukm_length, const uint8_t *ukm,
		uint8_t *out)
{
  const struct ecc_curve *ecc = priv->ecc;
  unsigned bsize = (ecc_bit_size (ecc) + 7) / 8;
  mp_size_t size = ecc->p.size;
  mp_size_t itch = 4*size + ecc->mul_itch;
  mp_limb_t *scratch;

  if (itch < 5*size + ecc->h_to_a_itch)
      itch = 5*size + ecc->h_to_a_itch;

  assert (pub->ecc == ecc);
  assert (priv->ecc == ecc);
  assert (ukm_length <= bsize);

  scratch = gmp_alloc_limbs (itch);






  mpn_set_base256_le (UKM, size, ukm, ukm_length);

  
  if (mpn_zero_p (UKM, size))
    UKM[0] = 1;

  ecc_mod_mul (&ecc->q, TEMP, priv->p, UKM, TEMP); 
  ecc->mul (ecc, XYZ, TEMP, pub->p, scratch + 4*size); 
  ecc->h_to_a (ecc, 0, TEMP, XYZ, scratch + 5*size); 
  mpn_get_base256_le (out, bsize, TEMP, size);
  mpn_get_base256_le (out+bsize, bsize, TEMP_Y, size);
  gmp_free_limbs (scratch, itch);
}