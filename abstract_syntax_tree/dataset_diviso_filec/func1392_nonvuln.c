bool check_reorganise_list(partition_info *new_part_info,
                           partition_info *old_part_info,
                           List<char> list_part_names)
{
  uint new_count, old_count;
  uint num_new_parts= new_part_info->partitions.elements;
  uint num_old_parts= old_part_info->partitions.elements;
  List_iterator<partition_element> new_parts_it(new_part_info->partitions);
  bool same_part_info= (new_part_info == old_part_info);
  DBUG_ENTER("STR");

  new_count= 0;
  do
  {
    List_iterator<partition_element> old_parts_it(old_part_info->partitions);
    char *new_name= (new_parts_it++)->partition_name;
    new_count++;
    old_count= 0;
    do
    {
      char *old_name= (old_parts_it++)->partition_name;
      old_count++;
      if (same_part_info && old_count == new_count)
        break;
      if (!(my_strcasecmp(system_charset_info, old_name, new_name)))
      {
        if (!is_name_in_list(old_name, list_part_names))
          DBUG_RETURN(TRUE);
      }
    } while (old_count < num_old_parts);
  } while (new_count < num_new_parts);
  DBUG_RETURN(FALSE);
}