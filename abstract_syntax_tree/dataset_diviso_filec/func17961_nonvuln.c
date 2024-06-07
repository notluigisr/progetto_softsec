String *Item::check_well_formed_result(String *str, bool send_error)
{
  
  CHARSET_INFO *cs= str->charset();
  uint wlen= str->well_formed_length();
  null_value= false;
  if (wlen < str->length())
  {
    THD *thd= current_thd;
    char hexbuf[7];
    uint diff= str->length() - wlen;
    set_if_smaller(diff, 3);
    octet2hex(hexbuf, str->ptr() + wlen, diff);
    if (send_error)
    {
      my_error(ER_INVALID_CHARACTER_STRING, MYF(0),
               cs->csname,  hexbuf);
      return 0;
    }
    if (thd->is_strict_mode())
    {
      null_value= 1;
      str= 0;
    }
    else
    {
      str->length(wlen);
    }
    push_warning_printf(thd, Sql_condition::WARN_LEVEL_WARN,
                        ER_INVALID_CHARACTER_STRING,
                        ER_THD(thd, ER_INVALID_CHARACTER_STRING), cs->csname,
                        hexbuf);
  }
  return str;
}