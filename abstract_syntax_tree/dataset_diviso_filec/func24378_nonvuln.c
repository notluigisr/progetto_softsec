void TABLE_SHARE::destroy()
{
  uint idx;
  KEY *info_it;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR", db.str, table_name.str));

  if (ha_share)
  {
    delete ha_share;
    ha_share= NULL;                             
  }

  delete_stat_values_for_table_share(this);
  delete sequence;
  free_root(&stats_cb.mem_root, MYF(0));

  
  if (tmp_table == NO_TMP_TABLE)
  {
    mysql_mutex_destroy(&LOCK_share);
    mysql_mutex_destroy(&LOCK_ha_data);
  }
  my_hash_free(&name_hash);

  plugin_unlock(NULL, db_plugin);
  db_plugin= NULL;

  
  info_it= key_info;
  for (idx= keys; idx; idx--, info_it++)
  {
    if (info_it->flags & HA_USES_PARSER)
    {
      plugin_unlock(NULL, info_it->parser);
      info_it->flags= 0;
    }
  }

#ifdef WITH_PARTITION_STORAGE_ENGINE
  plugin_unlock(NULL, default_part_plugin);
#endif 

  PSI_CALL_release_table_share(m_psi);

  
  MEM_ROOT own_root= mem_root;
  free_root(&own_root, MYF(0));
  DBUG_VOID_RETURN;
}