static int audit_set_backlog_limit(u32 limit)
{
	return audit_do_config_change("STR", &audit_backlog_limit, limit);
}