void prune_partition_set(const TABLE *table, part_id_range *part_spec)
{
  int last_partition= -1;
  uint i;
  partition_info *part_info= table->part_info;

  DBUG_ENTER("STR");
  for (i= part_spec->start_part; i <= part_spec->end_part; i++)
  {
    if (bitmap_is_set(&(part_info->used_partitions), i))
    {
      DBUG_PRINT("STR", i));
      if (last_partition == -1)
        
        part_spec->start_part= i;
      last_partition= i;
    }
  }
  if (last_partition == -1)
    
    part_spec->start_part= part_spec->end_part + 1;  
  else 
    part_spec->end_part= last_partition;

  DBUG_VOID_RETURN;
}