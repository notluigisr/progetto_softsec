bool check_string_byte_length(LEX_STRING *str, uint err_msg,
                              uint max_byte_length)
{
  if (str->length <= max_byte_length)
    return FALSE;

  my_error(ER_WRONG_STRING_LENGTH, MYF(0), str->str,
           err_msg ? ER(err_msg) : "", max_byte_length);

  return TRUE;
}