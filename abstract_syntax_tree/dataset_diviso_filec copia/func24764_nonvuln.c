  Item_static_string_func(const char *name_par, const char *str, uint length,
                          CHARSET_INFO *cs,
                          Derivation dv= DERIVATION_COERCIBLE)
    :Item_string(NullS, str, length, cs, dv), func_name(name_par)
  {}