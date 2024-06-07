      ECDSA_Signature_Operation(const ECDSA_PrivateKey& ecdsa,
                                const std::string& emsa) :
         PK_Ops::Signature_with_EMSA(emsa),
         m_group(ecdsa.domain()),
         m_x(ecdsa.private_value())
         {
#if defined(BOTAN_HAS_RFC6979_GENERATOR)
         m_rfc6979_hash = hash_for_emsa(emsa);
#endif
         }