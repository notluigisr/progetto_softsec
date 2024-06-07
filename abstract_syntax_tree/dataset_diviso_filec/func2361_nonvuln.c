  virtual CHARSET_INFO *charset_for_protocol(void) const
  {
    return result_type() == STRING_RESULT ? collation.collation :
                                            &my_charset_bin;
  };