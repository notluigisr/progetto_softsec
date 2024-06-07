void trans_register_ha(THD *thd, bool all, handlerton *ht_arg)
{
  THD_TRANS *trans;
  Ha_trx_info *ha_info;
  DBUG_ENTER("STR");
  DBUG_PRINT("STR"));

  if (all)
  {
    trans= &thd->transaction.all;
    thd->server_status|= SERVER_STATUS_IN_TRANS;
    if (thd->tx_read_only)
      thd->server_status|= SERVER_STATUS_IN_TRANS_READONLY;
    DBUG_PRINT("STR"));
  }
  else
    trans= &thd->transaction.stmt;

  ha_info= thd->ha_data[ht_arg->slot].ha_info + (all ? 1 : 0);

  if (ha_info->is_started())
    DBUG_VOID_RETURN; 

  ha_info->register_ha(trans, ht_arg);

  trans->no_2pc|=(ht_arg->prepare==0);

  
  if (thd->transaction.implicit_xid.is_null())
    thd->transaction.implicit_xid.set(thd->query_id);

  DBUG_VOID_RETURN;
}