int get_part_iter_for_interval_cols_via_map(partition_info *part_info,
                                            bool is_subpart,
                                            uint32 *store_length_array,
                                            uchar *min_value, uchar *max_value,
                                            uint min_len, uint max_len, 
                                            uint flags,
                                            PARTITION_ITERATOR *part_iter)
{
  uint32 nparts;
  get_col_endpoint_func  get_col_endpoint;
  DBUG_ENTER("STR");

  if (part_info->part_type == RANGE_PARTITION)
  {
    get_col_endpoint= get_partition_id_cols_range_for_endpoint;
    part_iter->get_next= get_next_partition_id_range;
  }
  else if (part_info->part_type == LIST_PARTITION)
  {
    get_col_endpoint= get_partition_id_cols_list_for_endpoint;
    part_iter->get_next= get_next_partition_id_list;
    part_iter->part_info= part_info;
    DBUG_ASSERT(part_info->num_list_values);
  }
  else
    assert(0);

  if (flags & NO_MIN_RANGE)
    part_iter->part_nums.start= part_iter->part_nums.cur= 0;
  else
  {
    
    nparts= store_tuple_to_record(part_info->part_field_array,
                                  store_length_array,
                                  min_value,
                                  min_value + min_len);
    part_iter->part_nums.start= part_iter->part_nums.cur=
      get_col_endpoint(part_info, TRUE, !(flags & NEAR_MIN),
                       nparts);
  }
  if (flags & NO_MAX_RANGE)
  {
    if (part_info->part_type == RANGE_PARTITION)
      part_iter->part_nums.end= part_info->num_parts;
    else 
    {
      DBUG_ASSERT(part_info->part_type == LIST_PARTITION);
      part_iter->part_nums.end= part_info->num_list_values;
    }
  }
  else
  {
    
    nparts= store_tuple_to_record(part_info->part_field_array,
                                  store_length_array,
                                  max_value,
                                  max_value + max_len);
    part_iter->part_nums.end= get_col_endpoint(part_info, FALSE,
                                               !(flags & NEAR_MAX),
                                               nparts);
  }
  if (part_iter->part_nums.start == part_iter->part_nums.end)
    DBUG_RETURN(0);
  DBUG_RETURN(1);
}