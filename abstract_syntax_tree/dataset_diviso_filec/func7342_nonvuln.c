void Vers_history_point::print(String *str, enum_query_type query_type,
                               const char *prefix, size_t plen) const
{
  const static LEX_CSTRING unit_type[]=
  {
    { STRING_WITH_LEN("") },
    { STRING_WITH_LEN("STR") },
    { STRING_WITH_LEN("STR") }
  };
  str->append(prefix, plen);
  str->append(unit_type + unit);
  item->print(str, query_type);
}