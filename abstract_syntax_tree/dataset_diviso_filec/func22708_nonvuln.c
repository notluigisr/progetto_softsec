void drop_open_table(THD *thd, TABLE *table, const LEX_CSTRING *db_name,
                     const LEX_CSTRING *table_name)
{
  DBUG_ENTER("STR");
  if (table->s->tmp_table)
    thd->drop_temporary_table(table, NULL, true);
  else
  {
    DBUG_ASSERT(table == thd->open_tables);

    handlerton *table_type= table->s->db_type();
    table->file->extra(HA_EXTRA_PREPARE_FOR_DROP);
    close_thread_table(thd, &thd->open_tables);
    
    tdc_remove_table(thd, TDC_RT_REMOVE_ALL, db_name->str, table_name->str,
                     FALSE);
    
    quick_rm_table(thd, table_type, db_name, table_name, 0);
 }
  DBUG_VOID_RETURN;
}