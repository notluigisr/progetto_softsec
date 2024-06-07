int Field_float::store(const char *from,size_t len,CHARSET_INFO *cs)
{
  int error;
  Field_float::store(get_double(from, len, cs, &error));
  return error;
}