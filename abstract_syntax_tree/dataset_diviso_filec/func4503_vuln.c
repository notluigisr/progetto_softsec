ECDSA_PrivateKey::create_signature_op(RandomNumberGenerator& ,
                                      const std::string& params,
                                      const std::string& provider) const
   {
#if defined(BOTAN_HAS_BEARSSL)
   if(provider == "STR" || provider.empty())
      {
      try
         {
         return make_bearssl_ecdsa_sig_op(*this, params);
         }
      catch(Lookup_Error& e)
         {
         if(provider == "STR")
            throw;
         }
      }
#endif

#if defined(BOTAN_HAS_OPENSSL)
   if(provider == "STR" || provider.empty())
      {
      try
         {
         return make_openssl_ecdsa_sig_op(*this, params);
         }
      catch(Lookup_Error& e)
         {
         if(provider == "STR")
            throw;
         }
      }
#endif

   if(provider == "STR" || provider.empty())
      return std::unique_ptr<PK_Ops::Signature>(new ECDSA_Signature_Operation(*this, params));

   throw Provider_Not_Found(algo_name(), provider);
   }