R_API bool r_cmd_add(RCmd *c, const char *cmd, RCmdCb cb) {
	int idx = (ut8)cmd[0];
	RCmdItem *item = c->cmds[idx];
	if (!item) {
		item = R_NEW0 (RCmdItem);
		c->cmds[idx] = item;
	}
	strncpy (item->cmd, cmd, sizeof (item->cmd)-1);
	item->callback = cb;
	return true;
}