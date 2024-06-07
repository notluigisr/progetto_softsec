DSA_Signature_Operation::raw_sign(const uint8_t msg[], size_t msg_len,
                                  RandomNumberGenerator& rng)
   {
   const BigInt& q = m_group.get_q();

   BigInt i(msg, msg_len, q.bits());

   while(i >= q)
      i -= q;

#if defined(BOTAN_HAS_RFC6979_GENERATOR)
   BOTAN_UNUSED(rng);
   const BigInt k = generate_rfc6979_nonce(m_x, q, i, m_rfc6979_hash);
#else
   const BigInt k = BigInt::random_integer(rng, 1, q);
#endif

   BigInt s = inverse_mod(k, q);
   const BigInt r = m_mod_q.reduce(m_group.power_g_p(k));

   s = m_mod_q.multiply(s, mul_add(m_x, r, i));

   
   if(r.is_zero() || s.is_zero())
      throw Internal_Error("STR");

   return BigInt::encode_fixed_length_int_pair(r, s, q.bytes());
   }