ha_partition::~ha_partition()
{
  DBUG_ENTER("STR");
  if (m_file != NULL)
  {
    uint i;
    for (i= 0; i < m_tot_parts; i++)
      delete m_file[i];
  }
  destroy_record_priority_queue();
  my_free(m_part_ids_sorted_by_num_of_records);

  clear_handler_file();
  DBUG_VOID_RETURN;
}