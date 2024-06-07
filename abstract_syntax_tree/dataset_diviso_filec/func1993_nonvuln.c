void Field_time_with_dec::make_send_field(Send_field *field)
{
  Field::make_send_field(field);
  field->decimals= dec;
}