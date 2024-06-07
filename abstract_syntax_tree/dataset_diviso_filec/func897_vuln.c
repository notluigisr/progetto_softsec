bool ECDSA_Verification_Operation::verify(const uint8_t msg[], size_t msg_len,
                                          const uint8_t sig[], size_t sig_len)
   {
   if(sig_len != m_group.get_order_bytes() * 2)
      return false;

   const BigInt e(msg, msg_len, m_group.get_order_bits());

   const BigInt r(sig, sig_len / 2);
   const BigInt s(sig + sig_len / 2, sig_len / 2);

   if(r <= 0 || r >= m_group.get_order() || s <= 0 || s >= m_group.get_order())
      return false;

   const BigInt w = m_group.inverse_mod_order(s);

   const BigInt u1 = m_group.multiply_mod_order(e, w);
   const BigInt u2 = m_group.multiply_mod_order(r, w);
   const PointGFp R = m_gy_mul.multi_exp(u1, u2);

   if(R.is_zero())
      return false;

   const BigInt v = m_group.mod_order(R.get_affine_x());
   return (v == r);
   }