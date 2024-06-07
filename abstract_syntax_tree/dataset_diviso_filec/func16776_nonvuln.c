Event_db_repository::fill_schema_events(THD *thd, TABLE_LIST *i_s_table,
                                        const char *db)
{
  TABLE *schema_table= i_s_table->table;
  Open_tables_backup open_tables_backup;
  TABLE_LIST event_table;
  int ret= 0;

  DBUG_ENTER("STR");
  DBUG_PRINT("STR"));

  event_table.init_one_table(&MYSQL_SCHEMA_NAME, &MYSQL_EVENT_NAME, 0, TL_READ);

  if (open_system_tables_for_read(thd, &event_table, &open_tables_backup))
    DBUG_RETURN(TRUE);

  if (table_intact.check(event_table.table, &event_table_def))
  {
    close_system_tables(thd, &open_tables_backup);
    my_error(ER_EVENT_OPEN_TABLE_FAILED, MYF(0));
    DBUG_RETURN(TRUE);
  }

  
  if (db)
    ret= index_read_for_db_for_i_s(thd, schema_table, event_table.table, db);
  else
    ret= table_scan_all_for_i_s(thd, schema_table, event_table.table);

  close_system_tables(thd, &open_tables_backup);

  DBUG_PRINT("STR", ret));
  DBUG_RETURN(ret);
}