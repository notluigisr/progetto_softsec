ECDSA_Signature_Operation::raw_sign(const uint8_t msg[], size_t msg_len,
                                    RandomNumberGenerator& rng)
   {
   BigInt m(msg, msg_len, m_group.get_order_bits());

#if defined(BOTAN_HAS_RFC6979_GENERATOR)
   const BigInt k = generate_rfc6979_nonce(m_x, m_group.get_order(), m, m_rfc6979_hash);
#else
   const BigInt k = m_group.random_scalar(rng);
#endif

   const BigInt k_inv = m_group.inverse_mod_order(k);
   const BigInt r = m_group.mod_order(
      m_group.blinded_base_point_multiply_x(k, rng, m_ws));

   const BigInt xrm = m_group.mod_order(m_group.multiply_mod_order(m_x, r) + m);
   const BigInt s = m_group.multiply_mod_order(k_inv, xrm);

   
   if(r.is_zero() || s.is_zero())
      throw Internal_Error("STR");

   return BigInt::encode_fixed_length_int_pair(r, s, m_group.get_order_bytes());
   }