uint Field_enum::is_equal(Create_field *new_field)
{
  TYPELIB *values= new_field->interval;

  
  if (new_field->sql_type != real_type() ||
      new_field->charset != field_charset ||
      new_field->pack_length != pack_length())
    return IS_EQUAL_NO;

  
  if (typelib->count > values->count)
    return IS_EQUAL_NO;

  
  if (! compare_type_names(field_charset, typelib, new_field->interval))
    return IS_EQUAL_NO;

  return IS_EQUAL_YES;
}