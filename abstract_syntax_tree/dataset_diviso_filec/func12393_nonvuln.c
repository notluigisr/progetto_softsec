int ha_partition::create(const char *name, TABLE *table_arg,
			 HA_CREATE_INFO *create_info)
{
  char t_name[FN_REFLEN];
  DBUG_ENTER("STR");

  strmov(t_name, name);
  DBUG_ASSERT(*fn_rext((char*)name) == '\0');
  if (del_ren_cre_table(t_name, NULL, table_arg, create_info))
  {
    handler::delete_table(t_name);
    DBUG_RETURN(1);
  }
  DBUG_RETURN(0);
}