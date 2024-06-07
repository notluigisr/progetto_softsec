R_API int r_cmd_alias_set_cmd(RCmd *cmd, const char *k, const char *v) {
	RCmdAliasVal val;
	val.data = (ut8 *)v;
	if (!val.data) {
		return 1;
	}
	val.sz = strlen (v) + 1;
	val.is_str = true;
	val.is_data = false;

	return ht_pp_update (cmd->aliases, k, &val);
}