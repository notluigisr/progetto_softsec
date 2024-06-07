Item_decimal::Item_decimal(THD *thd, double val, int precision, int scale):
  Item_num(thd)
{
  double2my_decimal(E_DEC_FATAL_ERROR, val, &decimal_value);
  decimals= (uint8) decimal_value.frac;
  fixed= 1;
  max_length= my_decimal_precision_to_length_no_truncation(decimal_value.intg +
                                                           decimals,
                                                           decimals,
                                                           unsigned_flag);
}