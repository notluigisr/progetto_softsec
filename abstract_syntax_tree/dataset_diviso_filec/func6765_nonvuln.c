String *Field_float::val_str(String *val_buffer,
			     String *val_ptr __attribute__((unused)))
{
  ASSERT_COLUMN_MARKED_FOR_READ;
  DBUG_ASSERT(!zerofill || field_length <= MAX_FIELD_CHARLENGTH);
  float nr;
  float4get(nr,ptr);

  uint to_length= 70;
  if (val_buffer->alloc(to_length))
  {
    my_error(ER_OUT_OF_RESOURCES, MYF(0));
    return val_buffer;
  }

  char *to=(char*) val_buffer->ptr();
  size_t len;

  if (dec >= FLOATING_POINT_DECIMALS)
    len= my_gcvt(nr, MY_GCVT_ARG_FLOAT, to_length - 1, to, NULL);
  else
  {
    
    len= my_fcvt(nr, dec, to, NULL);
  }
  val_buffer->length((uint) len);
  if (zerofill)
    prepend_zeros(val_buffer);
  val_buffer->set_charset(&my_charset_numeric);
  return val_buffer;
}