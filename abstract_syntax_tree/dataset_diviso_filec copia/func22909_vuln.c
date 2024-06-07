      DSA_Signature_Operation(const DSA_PrivateKey& dsa, const std::string& emsa) :
         PK_Ops::Signature_with_EMSA(emsa),
         m_group(dsa.get_group()),
         m_x(dsa.get_x()),
         m_mod_q(dsa.group_q())
         {
#if defined(BOTAN_HAS_RFC6979_GENERATOR)
         m_rfc6979_hash = hash_for_emsa(emsa);
#endif
         }