static bool check_charset(sys_var *self, THD *thd, set_var *var)
{
  if (!var->value)
    return false;

  char buff[STRING_BUFFER_USUAL_SIZE];
  if (var->value->result_type() == STRING_RESULT)
  {
    String str(buff, sizeof(buff), system_charset_info), *res;
    if (!(res=var->value->val_str(&str)))
      var->save_result.ptr= NULL;
    else if (!(var->save_result.ptr= get_charset_by_csname(res->c_ptr(),
                                                           MY_CS_PRIMARY,
                                                           MYF(0))) &&
             !(var->save_result.ptr= get_old_charset_by_name(res->c_ptr())))
    {
      ErrConvString err(res);
      my_error(ER_UNKNOWN_CHARACTER_SET, MYF(0), err.ptr());
      return true;
    }
  }
  else 
  {
    int csno= (int)var->value->val_int();
    if (!(var->save_result.ptr= get_charset(csno, MYF(0))))
    {
      my_error(ER_UNKNOWN_CHARACTER_SET, MYF(0), llstr(csno, buff));
      return true;
    }
  }
  return false;
}