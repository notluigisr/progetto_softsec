Field_bit::compatible_field_size(uint field_metadata,
                                 Relay_log_info * __attribute__((unused)),
                                 uint16 mflags,
                                 int *order_var)
{
  DBUG_ENTER("STR");
  DBUG_ASSERT((field_metadata >> 16) == 0);
  uint from_bit_len=
    8 * (field_metadata >> 8) + (field_metadata & 0xff);
  uint to_bit_len= max_display_length();
  DBUG_PRINT("STR",
                       from_bit_len, to_bit_len));
  
  if (!(mflags & Table_map_log_event::TM_BIT_LEN_EXACT_F)) {
    from_bit_len= (from_bit_len + 7) / 8;
    to_bit_len= (to_bit_len + 7) / 8;
  }

  *order_var= compare(from_bit_len, to_bit_len);
  DBUG_RETURN(TRUE);
}