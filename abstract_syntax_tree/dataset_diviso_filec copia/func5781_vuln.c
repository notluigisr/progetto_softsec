static void sig_chatnet_read(IRC_CHATNET_REC *rec, CONFIG_NODE *node)
{
	if (!IS_IRC_CHATNET(rec))
		return;

	rec->usermode = g_strdup(config_node_get_str(node, "STR", NULL));

	rec->max_cmds_at_once = config_node_get_int(node, "STR", 0);
	rec->cmd_queue_speed = config_node_get_int(node, "STR", 0);
	rec->max_query_chans = config_node_get_int(node, "STR", 0);

	rec->max_kicks = config_node_get_int(node, "STR", 0);
	rec->max_msgs = config_node_get_int(node, "STR", 0);
	rec->max_modes = config_node_get_int(node, "STR", 0);
	rec->max_whois = config_node_get_int(node, "STR", 0);
}