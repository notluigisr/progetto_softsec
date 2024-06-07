void Field_short::sql_type(String &res) const
{
  CHARSET_INFO *cs=res.charset();
  res.length(cs->cset->snprintf(cs,(char*) res.ptr(),res.alloced_length(),
			  "STR",(int) field_length));
  add_zerofill_and_unsigned(res);
}