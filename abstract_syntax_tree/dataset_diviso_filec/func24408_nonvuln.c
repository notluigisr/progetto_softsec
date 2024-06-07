String *Field_tiny::val_str(String *val_buffer,
			    String *val_ptr __attribute__((unused)))
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  long nr= unsigned_flag ? (long) ptr[0] : (long) ((signed char*) ptr)[0];
  return val_str_from_long(val_buffer, 5, -10, nr);
}