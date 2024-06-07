VAR *var_init(VAR *v, const char *name, int name_len, const char *val,
              int val_len)
{
  int val_alloc_len;
  VAR *tmp_var;
  if (!name_len && name)
    name_len = strlen(name);
  if (!val_len && val)
    val_len = strlen(val) ;
  if (!val)
    val_len= 0;
  val_alloc_len = val_len + 16; 
  if (!(tmp_var=v) && !(tmp_var = (VAR*)my_malloc(PSI_NOT_INSTRUMENTED,
                                                  sizeof(*tmp_var)
                                                  + name_len+2, MYF(MY_WME))))
    die("STR");

  if (name != NULL)
  {
    tmp_var->name= reinterpret_cast<char*>(tmp_var) + sizeof(*tmp_var);
    memcpy(tmp_var->name, name, name_len);
    tmp_var->name[name_len]= 0;
  }
  else
    tmp_var->name= NULL;

  tmp_var->alloced = (v == 0);

  if (!(tmp_var->str_val = (char*)my_malloc(PSI_NOT_INSTRUMENTED,
                                            val_alloc_len+1, MYF(MY_WME))))
    die("STR");

  if (val)
    memcpy(tmp_var->str_val, val, val_len);
  tmp_var->str_val[val_len]= 0;

  var_check_int(tmp_var);
  tmp_var->name_len = name_len;
  tmp_var->str_val_len = val_len;
  tmp_var->alloced_len = val_alloc_len;
  return tmp_var;
}