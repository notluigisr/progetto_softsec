String *Field_new_decimal::val_str(String *val_buffer,
                                   String *val_ptr __attribute__((unused)))
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  my_decimal decimal_value;
  uint fixed_precision= zerofill ? precision : 0;
  my_decimal2string(E_DEC_FATAL_ERROR, val_decimal(&decimal_value),
                    fixed_precision, dec, '0', val_buffer);
  val_buffer->set_charset(&my_charset_numeric);
  return val_buffer;
}