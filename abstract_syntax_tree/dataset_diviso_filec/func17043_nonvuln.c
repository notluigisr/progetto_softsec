int Field_varstring::key_cmp(const uchar *key_ptr, uint max_key_length)
{
  size_t length=  length_bytes == 1 ? (uint) *ptr : uint2korr(ptr);
  size_t local_char_length= max_key_length / field_charset->mbmaxlen;

  local_char_length= my_charpos(field_charset, ptr + length_bytes,
                          ptr + length_bytes + length, local_char_length);
  set_if_smaller(length, local_char_length);
  return field_charset->coll->strnncollsp(field_charset, 
                                          ptr + length_bytes,
                                          length,
                                          key_ptr+
                                          HA_KEY_BLOB_LENGTH,
                                          uint2korr(key_ptr));
}