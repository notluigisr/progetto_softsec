String *Item_func_conv::val_str(String *str)
{
  DBUG_ASSERT(fixed == 1);
  String *res= args[0]->val_str(str);
  char *endptr,ans[65],*ptr;
  longlong dec;
  int from_base= (int) args[1]->val_int();
  int to_base= (int) args[2]->val_int();
  int err;

  
  if (args[0]->null_value || args[1]->null_value || args[2]->null_value ||
      from_base == INT_MIN || to_base == INT_MIN ||
      abs(to_base) > 36 || abs(to_base) < 2 ||
      abs(from_base) > 36 || abs(from_base) < 2 || !(res->length()))
  {
    null_value= 1;
    return NULL;
  }
  null_value= 0;
  unsigned_flag= !(from_base < 0);

  if (args[0]->field_type() == MYSQL_TYPE_BIT) 
  {
    
    dec= args[0]->val_int();
  }
  else
  {
    if (from_base < 0)
      dec= my_strntoll(res->charset(), res->ptr(), res->length(),
                       -from_base, &endptr, &err);
    else
      dec= (longlong) my_strntoull(res->charset(), res->ptr(), res->length(),
                                   from_base, &endptr, &err);
  }

  if (!(ptr= longlong2str(dec, ans, to_base)) ||
      str->copy(ans, (uint32) (ptr - ans), default_charset()))
  {
    null_value= 1;
    return NULL;
  }
  return str;
}