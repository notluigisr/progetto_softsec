bool LEX::set_system_variable(THD *thd, enum_var_type var_type,
                              const LEX_CSTRING *name1,
                              const LEX_CSTRING *name2,
                              Item *val)
{
  sys_var *tmp;
  if (unlikely(check_reserved_words(name1)) ||
      unlikely(!(tmp= find_sys_var(thd, name2->str, name2->length, true))))
  {
    my_error(ER_UNKNOWN_STRUCTURED_VARIABLE, MYF(0),
             (int) name1->length, name1->str);
    return true;
  }
  if (unlikely(!tmp->is_struct()))
  {
    my_error(ER_VARIABLE_IS_NOT_STRUCT, MYF(0), name2->str);
    return true;
  }
  return set_system_variable(var_type, tmp, name1, val);
}