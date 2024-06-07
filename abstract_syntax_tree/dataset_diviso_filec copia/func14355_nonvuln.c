  void fix_length_and_charset_datetime(uint32 max_char_length_arg)
  {
    collation.set(&my_charset_numeric, DERIVATION_NUMERIC, MY_REPERTOIRE_ASCII);
    fix_char_length(max_char_length_arg);
  }