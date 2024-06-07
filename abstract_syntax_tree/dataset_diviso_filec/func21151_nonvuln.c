THD::binlog_get_pending_rows_event(bool is_transactional) const
{
  Rows_log_event* rows= NULL;
  binlog_cache_mngr *const cache_mngr=
    (binlog_cache_mngr*) thd_get_ha_data(this, binlog_hton);

  
  if (cache_mngr)
  {
    binlog_cache_data *cache_data=
      cache_mngr->get_binlog_cache_data(use_trans_cache(this, is_transactional));

    rows= cache_data->pending();
  }
  return (rows);
}