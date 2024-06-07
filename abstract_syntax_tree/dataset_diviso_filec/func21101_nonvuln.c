static char *argv_group_get_help(RCmd *cmd, RCmdDesc *cd, bool use_color) {
	RStrBuf *sb = r_strbuf_new (NULL);
	fill_usage_strbuf (sb, cd, use_color);

	void **it_cd;
	size_t max_len = 0;

	r_cmd_desc_children_foreach (cd, it_cd) {
		RCmdDesc *child = *(RCmdDesc **)it_cd;
		max_len = update_max_len (child, max_len);
	}

	r_cmd_desc_children_foreach (cd, it_cd) {
		RCmdDesc *child = *(RCmdDesc **)it_cd;
		print_child_help (sb, child, max_len, use_color);
	}
	return r_strbuf_drain (sb);
}