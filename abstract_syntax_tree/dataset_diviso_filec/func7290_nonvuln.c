int ha_partition::assign_to_keycache(THD *thd, HA_CHECK_OPT *check_opt)
{
  DBUG_ENTER("STR");

  DBUG_RETURN(handle_opt_partitions(thd, check_opt, ASSIGN_KEYCACHE_PARTS));
}