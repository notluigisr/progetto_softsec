int ha_partition::index_read_last_map(uchar *buf, const uchar *key,
                                      key_part_map keypart_map)
{
  DBUG_ENTER("STR");

  m_ordered= TRUE;				
  end_range= 0;
  m_index_scan_type= partition_index_read_last;
  m_start_key.key= key;
  m_start_key.keypart_map= keypart_map;
  m_start_key.flag= HA_READ_PREFIX_LAST;
  DBUG_RETURN(common_index_read(buf, TRUE));
}