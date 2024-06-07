int ha_myisam::index_first(uchar *buf)
{
  MYSQL_INDEX_READ_ROW_START(table_share->db.str, table_share->table_name.str);
  DBUG_ASSERT(inited==INDEX);
  ha_statistic_increment(&SSV::ha_read_first_count);
  int error=mi_rfirst(file, buf, active_index);
  table->status=error ? STATUS_NOT_FOUND: 0;
  MYSQL_INDEX_READ_ROW_DONE(error);
  return error;
}