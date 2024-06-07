void Item_func_to_base64::fix_length_and_dec()
{
  maybe_null= args[0]->maybe_null;
  collation.set(default_charset(), DERIVATION_COERCIBLE, MY_REPERTOIRE_ASCII);
  if (args[0]->max_length > (uint) base64_encode_max_arg_length())
  {
    maybe_null= 1;
    fix_char_length_ulonglong((ulonglong) base64_encode_max_arg_length());
  }
  else
  {
    uint64 length= base64_needed_encoded_length((uint64) args[0]->max_length);
    DBUG_ASSERT(length > 0);
    fix_char_length_ulonglong((ulonglong) length - 1);
  }
}