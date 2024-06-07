CAMLprim value caml_string_set16(value str, value index, value newval)
{
  unsigned char b1, b2;
  intnat val;
  intnat idx = Long_val(index);
  if (idx < 0 || idx + 1 >= caml_string_length(str)) caml_array_bound_error();
  val = Long_val(newval);
#ifdef ARCH_BIG_ENDIAN
  b1 = 0xFF & val >> 8;
  b2 = 0xFF & val;
#else
  b2 = 0xFF & val >> 8;
  b1 = 0xFF & val;
#endif
  Byte_u(str, idx) = b1;
  Byte_u(str, idx + 1) = b2;
  return Val_unit;
}