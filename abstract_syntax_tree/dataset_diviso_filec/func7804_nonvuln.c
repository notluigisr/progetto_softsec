int Item::save_decimal_in_field(Field *field, bool no_conversions)
{
  my_decimal decimal_value;
  my_decimal *value= val_decimal(&decimal_value);
  if (null_value)
    return set_field_to_null_with_conversions(field, no_conversions);
  field->set_notnull();
  return field->store_decimal(value);
}