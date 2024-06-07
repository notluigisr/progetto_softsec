static bool write_log_final_change_partition(ALTER_PARTITION_PARAM_TYPE *lpt)
{
  partition_info *part_info= lpt->part_info;
  DDL_LOG_MEMORY_ENTRY *log_entry;
  DDL_LOG_MEMORY_ENTRY *exec_log_entry= part_info->exec_log_entry;
  char path[FN_REFLEN + 1];
  char shadow_path[FN_REFLEN + 1];
  DDL_LOG_MEMORY_ENTRY *old_first_log_entry= part_info->first_log_entry;
  uint next_entry= 0;
  DBUG_ENTER("STR");

  
  part_info->first_log_entry= NULL;
  build_table_filename(path, sizeof(path) - 1, lpt->db,
                       lpt->table_name, "", 0);
  build_table_shadow_filename(shadow_path, sizeof(shadow_path) - 1, lpt);
  mysql_mutex_lock(&LOCK_gdl);
  if (write_log_changed_partitions(lpt, &next_entry, (const char*)path))
    goto error;
  if (write_log_dropped_partitions(lpt, &next_entry, (const char*)path,
                      lpt->alter_info->flags & ALTER_REORGANIZE_PARTITION))
    goto error;
  if (write_log_replace_delete_frm(lpt, next_entry, shadow_path, path, TRUE))
    goto error;
  log_entry= part_info->first_log_entry;
  part_info->frm_log_entry= log_entry;
  
  if (write_execute_ddl_log_entry(log_entry->entry_pos,
                                    FALSE, &exec_log_entry))
    goto error;
  release_part_info_log_entries(old_first_log_entry);
  mysql_mutex_unlock(&LOCK_gdl);
  DBUG_RETURN(FALSE);

error:
  release_part_info_log_entries(part_info->first_log_entry);
  mysql_mutex_unlock(&LOCK_gdl);
  part_info->first_log_entry= old_first_log_entry;
  part_info->frm_log_entry= NULL;
  my_error(ER_DDL_LOG_ERROR, MYF(0));
  DBUG_RETURN(TRUE);
}