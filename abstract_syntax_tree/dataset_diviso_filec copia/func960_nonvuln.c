  void set_valid_utf8(const LEX_CSTRING *name)
  {
    DBUG_ASSERT(Well_formed_prefix(system_charset_info, name->str,
                                   name->length).length() == name->length);
    str= name->str ; length= name->length;
  }