String *Field_date::val_str(String *val_buffer,
			    String *val_ptr __attribute__((unused)))
{
  MYSQL_TIME ltime;
  get_TIME(&ltime, ptr, 0);
  val_buffer->alloc(MAX_DATE_STRING_REP_LENGTH);
  uint length= (uint) my_date_to_str(&ltime,
                                     const_cast<char*>(val_buffer->ptr()));
  val_buffer->length(length);
  val_buffer->set_charset(&my_charset_numeric);

  return val_buffer;
}