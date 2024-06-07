void Item_param::print(String *str, enum_query_type query_type)
{
  if (state == NO_VALUE)
  {
    str->append('?');
  }
  else if (state == DEFAULT_VALUE)
  {
    str->append("STR");
  }
  else if (state == IGNORE_VALUE)
  {
    str->append("STR");
  }
  else
  {
    char buffer[STRING_BUFFER_USUAL_SIZE];
    String tmp(buffer, sizeof(buffer), &my_charset_bin);
    const String *res;
    res= query_val_str(current_thd, &tmp);
    str->append(*res);
  }
}