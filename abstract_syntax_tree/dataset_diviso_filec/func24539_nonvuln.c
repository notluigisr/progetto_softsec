longlong Item::val_int_unsigned_typecast_from_str()
{
  int error;
  longlong value= val_int_from_str(&error);
  if (unlikely(!null_value && error < 0))
    push_note_converted_to_positive_complement(current_thd);
  return value;
}