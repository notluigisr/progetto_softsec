      DSA_Verification_Operation(const DSA_PublicKey& dsa,
                                 const std::string& emsa) :
         PK_Ops::Verification_with_EMSA(emsa),
         m_group(dsa.get_group()),
         m_y(dsa.get_y()),
         m_mod_q(dsa.group_q())
         {}