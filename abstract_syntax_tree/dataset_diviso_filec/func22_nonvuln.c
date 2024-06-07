bool ECDSA_PrivateKey::check_key(RandomNumberGenerator& rng,
                                 bool strong) const
   {
   if(!public_point().on_the_curve())
      return false;

   if(!strong)
      return true;

   return KeyPair::signature_consistency_check(rng, *this, "STR");
   }