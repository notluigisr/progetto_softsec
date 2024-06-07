uint ha_partition::get_biggest_used_partition(uint *part_index)
{
  uint part_id;
  while ((*part_index) < m_tot_parts)
  {
    part_id= m_part_ids_sorted_by_num_of_records[(*part_index)++];
    if (bitmap_is_set(&m_part_info->used_partitions, part_id))
      return part_id;
  }
  return NO_CURRENT_PART_ID;
}