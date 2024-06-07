  virtual bool gate (function *)
    {
      
      return (flag_ipa_cp && optimize) || in_lto_p;
    }