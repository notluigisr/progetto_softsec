void close_thread_table(THD *thd, TABLE **table_ptr)
{
  TABLE *table= *table_ptr;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR", table->s->db.str,
                        table->s->table_name.str, table));
  DBUG_ASSERT(!table->file->keyread_enabled());
  DBUG_ASSERT(!table->file || table->file->inited == handler::NONE);

  
  DBUG_ASSERT(thd->mdl_context.is_lock_owner(MDL_key::TABLE,
                                             table->s->db.str,
                                             table->s->table_name.str,
                                             MDL_SHARED));
  table->mdl_ticket= NULL;

  if (table->file)
  {
    table->file->update_global_table_stats();
    table->file->update_global_index_stats();
  }

  

  mysql_mutex_lock(&thd->LOCK_thd_data);
  *table_ptr=table->next;
  mysql_mutex_unlock(&thd->LOCK_thd_data);

  if (! table->needs_reopen())
  {
    
    table->file->extra(HA_EXTRA_DETACH_CHILDREN);
    
    free_field_buffers_larger_than(table, MAX_TDC_BLOB_SIZE);
    table->file->ha_reset();
  }

  
  MYSQL_UNBIND_TABLE(table->file);

  tc_release_table(table);
  DBUG_VOID_RETURN;
}