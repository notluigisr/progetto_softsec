bool check_string_char_length(const LEX_CSTRING *str, uint err_msg,
                              size_t max_char_length, CHARSET_INFO *cs,
                              bool no_error)
{
  Well_formed_prefix prefix(cs, str->str, str->length, max_char_length);
  if (likely(!prefix.well_formed_error_pos() &&
             str->length == prefix.length()))
    return FALSE;

  if (!no_error)
  {
    ErrConvString err(str->str, str->length, cs);
    my_error(ER_WRONG_STRING_LENGTH, MYF(0), err.ptr(),
             err_msg ? ER(err_msg) : "",
             max_char_length);
  }
  return TRUE;
}