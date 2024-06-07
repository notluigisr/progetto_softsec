int ha_partition::create(const char *name, TABLE *table_arg,
			 HA_CREATE_INFO *create_info)
{
  char t_name[FN_REFLEN];
  DBUG_ENTER("STR");

  if (create_info->used_fields & HA_CREATE_USED_CONNECTION)
  {
    my_error(ER_CONNECT_TO_FOREIGN_DATA_SOURCE, MYF(0),
             "STR");
    DBUG_RETURN(1);
  }

  strmov(t_name, name);
  DBUG_ASSERT(*fn_rext((char*)name) == '\0');
  if (del_ren_cre_table(t_name, NULL, table_arg, create_info))
  {
    handler::delete_table(t_name);
    DBUG_RETURN(1);
  }
  DBUG_RETURN(0);
}