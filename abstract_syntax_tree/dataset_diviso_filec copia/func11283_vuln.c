void end_read_record(READ_RECORD *info)
{
  
  free_cache(info);
  if (info->table)
  {
    if (info->table->is_created())
      (void) info->table->file->extra(HA_EXTRA_NO_CACHE);
    if (info->read_record != rr_quick) 
      (void) info->table->file->ha_index_or_rnd_end();
    info->table=0;
  }
}