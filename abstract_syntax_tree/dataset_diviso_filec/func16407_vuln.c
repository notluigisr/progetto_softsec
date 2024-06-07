int ha_partition::drop_partitions(const char *path)
{
  List_iterator<partition_element> part_it(m_part_info->partitions);
  char part_name_buff[FN_REFLEN];
  uint num_parts= m_part_info->partitions.elements;
  uint num_subparts= m_part_info->num_subparts;
  uint i= 0;
  uint name_variant;
  int  ret_error;
  int  error= 0;
  DBUG_ENTER("STR");

  
  DBUG_ASSERT(!strcmp(path, get_canonical_filename(m_file[0], path,
                                                   part_name_buff)));
  do
  {
    partition_element *part_elem= part_it++;
    if (part_elem->part_state == PART_TO_BE_DROPPED)
    {
      handler *file;
      
      name_variant= NORMAL_PART_NAME;
      if (m_is_sub_partitioned)
      {
        List_iterator<partition_element> sub_it(part_elem->subpartitions);
        uint j= 0, part;
        do
        {
          partition_element *sub_elem= sub_it++;
          part= i * num_subparts + j;
          create_subpartition_name(part_name_buff, path,
                                   part_elem->partition_name,
                                   sub_elem->partition_name, name_variant);
          file= m_file[part];
          DBUG_PRINT("STR", part_name_buff));
          if ((ret_error= file->ha_delete_table(part_name_buff)))
            error= ret_error;
          if (deactivate_ddl_log_entry(sub_elem->log_entry->entry_pos))
            error= 1;
        } while (++j < num_subparts);
      }
      else
      {
        create_partition_name(part_name_buff, path,
                              part_elem->partition_name, name_variant,
                              TRUE);
        file= m_file[i];
        DBUG_PRINT("STR", part_name_buff));
        if ((ret_error= file->ha_delete_table(part_name_buff)))
          error= ret_error;
        if (deactivate_ddl_log_entry(part_elem->log_entry->entry_pos))
          error= 1;
      }
      if (part_elem->part_state == PART_IS_CHANGED)
        part_elem->part_state= PART_NORMAL;
      else
        part_elem->part_state= PART_IS_DROPPED;
    }
  } while (++i < num_parts);
  (void) sync_ddl_log();
  DBUG_RETURN(error);
}