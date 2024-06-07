int fill_schema_column_privileges(THD *thd, TABLE_LIST *tables, Item *cond)
{
#ifndef NO_EMBEDDED_ACCESS_CHECKS
  int error= 0;
  uint index;
  char buff[100];
  TABLE *table= tables->table;
  bool no_global_access= check_access(thd, SELECT_ACL, "STR",
                                      NULL, NULL, 1, 1);
  char *curr_host= thd->security_ctx->priv_host_name();
  DBUG_ENTER("STR");

  mysql_rwlock_rdlock(&LOCK_grant);

  for (index=0 ; index < column_priv_hash.records ; index++)
  {
    const char *user, *host, *is_grantable= "STR";
    GRANT_TABLE *grant_table= (GRANT_TABLE*) my_hash_element(&column_priv_hash,
							  index);
    if (!(user=grant_table->user))
      user= "";
    if (!(host= grant_table->host.get_host()))
      host= "";

    if (no_global_access &&
        (strcmp(thd->security_ctx->priv_user, user) ||
         my_strcasecmp(system_charset_info, curr_host, host)))
      continue;

    ulong table_access= grant_table->cols;
    if (table_access != 0)
    {
      if (!(grant_table->privs & GRANT_ACL))
        is_grantable= "STR";

      ulong test_access= table_access & ~GRANT_ACL;
      strxmov(buff, "STR", NullS);
      if (!test_access)
        continue;
      else
      {
        ulong j;
        int cnt;
        for (cnt= 0, j= SELECT_ACL; j <= TABLE_ACLS; cnt++, j<<= 1)
        {
          if (test_access & j)
          {
            for (uint col_index=0 ;
                 col_index < grant_table->hash_columns.records ;
                 col_index++)
            {
              GRANT_COLUMN *grant_column = (GRANT_COLUMN*)
                my_hash_element(&grant_table->hash_columns,col_index);
              if ((grant_column->rights & j) && (table_access & j))
              {
                if (update_schema_privilege(thd, table, buff, grant_table->db,
                                            grant_table->tname,
                                            grant_column->column,
                                            grant_column->key_length,
                                            command_array[cnt],
                                            command_lengths[cnt], is_grantable))
                {
                  error= 1;
                  goto err;
                }
              }
            }
          }
        }
      }
    }
  }
err:
  mysql_rwlock_unlock(&LOCK_grant);

  DBUG_RETURN(error);
#else
  return (0);
#endif
}