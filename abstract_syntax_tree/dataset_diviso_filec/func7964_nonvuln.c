Item *Item::const_charset_converter(THD *thd, CHARSET_INFO *tocs,
                                    bool lossless,
                                    const char *func_name)
{
  DBUG_ASSERT(const_item());
  DBUG_ASSERT(fixed);
  StringBuffer<64>tmp;
  String *s= val_str(&tmp);
  MEM_ROOT *mem_root= thd->mem_root;

  if (!s)
    return new (mem_root) Item_null(thd, (char *) func_name, tocs);

  if (!needs_charset_converter(s->length(), tocs))
  {
    if (collation.collation == &my_charset_bin && tocs != &my_charset_bin &&
        !this->check_well_formed_result(s, true))
      return NULL;
    return this;
  }

  uint conv_errors;
  Item_string *conv= (func_name ?
                      new (mem_root)
                      Item_static_string_func(thd, func_name,
                                              s, tocs, &conv_errors,
                                              collation.derivation,
                                              collation.repertoire) :
                      new (mem_root)
                      Item_string(thd, s, tocs, &conv_errors,
                                  collation.derivation,
                                  collation.repertoire));

  if (!conv || (conv_errors && lossless))
  {
    
    return NULL;
  }
  if (s->charset() == &my_charset_bin && tocs != &my_charset_bin &&
      !conv->check_well_formed_result(true))
    return NULL;
  return conv;
}