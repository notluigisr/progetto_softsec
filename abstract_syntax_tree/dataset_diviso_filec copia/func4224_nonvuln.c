static bool write_log_add_change_partition(ALTER_PARTITION_PARAM_TYPE *lpt)
{
  partition_info *part_info= lpt->part_info;
  DDL_LOG_MEMORY_ENTRY *log_entry;
  DDL_LOG_MEMORY_ENTRY *exec_log_entry= part_info->exec_log_entry;
  char tmp_path[FN_REFLEN + 1];
  char path[FN_REFLEN + 1];
  uint next_entry= 0;
  DDL_LOG_MEMORY_ENTRY *old_first_log_entry= part_info->first_log_entry;
  
  DBUG_ASSERT(old_first_log_entry);
  DBUG_ENTER("STR");

  build_table_filename(path, sizeof(path) - 1, lpt->db,
                       lpt->table_name, "", 0);
  build_table_shadow_filename(tmp_path, sizeof(tmp_path) - 1, lpt);
  mysql_mutex_lock(&LOCK_gdl);

  
  if (old_first_log_entry)
    next_entry= old_first_log_entry->entry_pos;
  if (write_log_dropped_partitions(lpt, &next_entry, (const char*)path,
                                   FALSE))
    goto error;
  log_entry= part_info->first_log_entry;

  if (write_execute_ddl_log_entry(log_entry->entry_pos,
                                  FALSE,
                                  
                                  &exec_log_entry))
    goto error;
  mysql_mutex_unlock(&LOCK_gdl);
  set_part_info_exec_log_entry(part_info, exec_log_entry);
  DBUG_RETURN(FALSE);

error:
  release_part_info_log_entries(part_info->first_log_entry);
  mysql_mutex_unlock(&LOCK_gdl);
  part_info->first_log_entry= old_first_log_entry;
  my_error(ER_DDL_LOG_ERROR, MYF(0));
  DBUG_RETURN(TRUE);
}