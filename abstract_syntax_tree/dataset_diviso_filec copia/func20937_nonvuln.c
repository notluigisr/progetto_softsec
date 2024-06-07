static void release_log_entries(partition_info *part_info)
{
  mysql_mutex_lock(&LOCK_gdl);
  release_part_info_log_entries(part_info->first_log_entry);
  release_part_info_log_entries(part_info->exec_log_entry);
  mysql_mutex_unlock(&LOCK_gdl);
  part_info->first_log_entry= NULL;
  part_info->exec_log_entry= NULL;
}