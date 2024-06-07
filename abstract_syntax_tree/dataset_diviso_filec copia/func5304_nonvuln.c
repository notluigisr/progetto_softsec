static int add_name_string(File fptr, const char *name)
{
  int err;
  String name_string("", 0, system_charset_info);
  THD *thd= current_thd;
  ulonglong save_sql_mode= thd->variables.sql_mode;
  thd->variables.sql_mode&= ~MODE_ANSI_QUOTES;
  ulonglong save_options= thd->variables.option_bits;
  thd->variables.option_bits&= ~OPTION_QUOTE_SHOW_CREATE;
  append_identifier(thd, &name_string, name, strlen(name));
  thd->variables.sql_mode= save_sql_mode;
  thd->variables.option_bits= save_options;
  err= add_string_object(fptr, &name_string);
  return err;
}