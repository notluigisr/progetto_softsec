my_decimal *Item_default_value::val_decimal(my_decimal *decimal_value)
{
  calculate();
  return Item_field::val_decimal(decimal_value);
}