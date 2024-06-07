Item *Item_string::safe_charset_converter(CHARSET_INFO *tocs)
{
  Item_string *conv;
  uint conv_errors;
  char *ptr;
  String tmp, cstr, *ostr= val_str(&tmp);
  cstr.copy(ostr->ptr(), ostr->length(), ostr->charset(), tocs, &conv_errors);
  if (conv_errors || !(conv= new Item_string(cstr.ptr(), cstr.length(),
                                             cstr.charset(),
                                             collation.derivation)))
  {
    
    return NULL;
  }
  if (!(ptr= current_thd->strmake(cstr.ptr(), cstr.length())))
    return NULL;
  conv->str_value.set(ptr, cstr.length(), cstr.charset());
  
  conv->str_value.mark_as_const();
  return conv;
}