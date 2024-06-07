int TC_LOG_BINLOG::log_xid(THD *thd, my_xid xid)
{
  DBUG_ENTER("STR");
  binlog_cache_mngr *cache_mngr=
    (binlog_cache_mngr*) thd_get_ha_data(thd, binlog_hton);
  
  DBUG_RETURN(!binlog_commit_flush_stmt_cache(thd, cache_mngr) &&
              !binlog_commit_flush_trx_cache(thd, cache_mngr, xid));
}