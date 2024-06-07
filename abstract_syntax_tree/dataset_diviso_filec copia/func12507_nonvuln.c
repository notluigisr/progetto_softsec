bool set_part_state(Alter_info *alter_info, partition_info *tab_part_info,
                    enum partition_state part_state)
{
  uint part_count= 0;
  uint num_parts_found= 0;
  List_iterator<partition_element> part_it(tab_part_info->partitions);

  do
  {
    partition_element *part_elem= part_it++;
    if ((alter_info->partition_flags & ALTER_PARTITION_ALL) ||
         (is_name_in_list(part_elem->partition_name,
          alter_info->partition_names)))
    {
      
      num_parts_found++;
      part_elem->part_state= part_state;
      DBUG_PRINT("STR",
                          part_state, part_elem->partition_name));
    }
    else
      part_elem->part_state= PART_NORMAL;
  } while (++part_count < tab_part_info->num_parts);

  if (num_parts_found != alter_info->partition_names.elements &&
      !(alter_info->partition_flags & ALTER_PARTITION_ALL))
  {
    
    part_it.rewind();
    part_count= 0;
    do
    {
      partition_element *part_elem= part_it++;
      part_elem->part_state= PART_NORMAL;
    } while (++part_count < tab_part_info->num_parts);
    return true;
  }
  return false;
}